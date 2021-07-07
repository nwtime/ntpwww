---
title: "Analysis and Simulation of the NTP On-Wire Protocols"
type: archives
toc_hide: true
---

![gif](/archives/pic/pogo3a.gif)

from [_Pogo_](/reflib/pictures), Walt Kelly

If it walks like a duck...

Last update: 12-May-2012

* * *

#### Table of Contents

*  [Abstract](/reflib/onwire/#abstract)
*  [Introduction](/reflib/onwire/#introduction)
*  [Preliminaries](/reflib/onwire/#preliminaries)
*  [Basic Symmetric Mode](/reflib/onwire/#basic-symmetric-mode)
*  [Interleaved Symmetric Mode](/reflib/onwire/#interleaved-symmetric-mode)
*  [Interleaved Broadcast Mode](/reflib/onwire/#interleaved-broadcast-mode)
*  [Error Detection and Recovery](/reflib/onwire/#error-detection-and-recovery)
*  [Measured Performance](/reflib/onwire/#measured-performance)
*  [Appendix A. NTP Protocol State Machines](/reflib/onwire/#appendix-a-ntp-protocol-state-machines)
*  [Appendix B. The NTP Simulator Program <tt>xlev.c</tt>](/reflib/onwire/#appendix-b-the-ntp-simulator-program-ttxlevctt)
*  [Command Line Options](/reflib/onwire/#command-line-options)

* * *

#### Abstract

This document presents a detailed analysis of the NTP on-wire protocols, including basic and interleaved, symmetric and broadcast modes. The interleaved modes provide enhanced accuracy over the basic modes by timestamping in the driver, rather than in the application layer code. A comprehensive simulation is presented which quantifies the overall error rate subject to random message errors, duplications and omissions.

* * *

#### Introduction

The NTP protocol operations in client/server, symmetric and broadcast modes are described in the protocol specification RFC 5905. As pointed out in that document, the highest accuracy obtainable requires the use of timestamps captured as close to the media as possible; however, this requires intervention in the kernel driver or hardware device.

This document describes two new modes, _interleaved symmetric_ and _interleaved broadcast_, which can improve accuracy by avoiding output queuing and transmission delays. In the reference implementation the receive timestamp or _drivestamp_ is captured shortly after the input device interrupt and before adding the buffer to the input queue. This avoids delays due to queuing and buffering operations. The transmit timestamp or _softstamp_ is captured before the message digest is computed and before adding the buffer to the output queue. If nothing further were done, there would be additional delays due to the message digest, queuing, buffering and transmission operations.

The output delays can be avoided by capturing a transmit drivestamp after the output device interrupt and sending it as the transmit timestamp in the following packet. This is especially important in the case of slow network links such as DSL cable and satellite data links. With the state machine and protocol described in this document, operation is automatic and transparent to other clients with and without interleaved capabilities.

Interleaved symmetric mode is an extension of basic symmetric mode, while interleaved broadcast mode is an extension of basic broadcast mode. The interleaved modes require servers and peers to retain state, so these modes do not support client/server mode. Mode selection can be determined by a configuration option or automatically by the protocol. In all modes the protocol can detect duplicate, unsynchronized and bogus packets and, in addition, can detect packets that violate the interleaving rules.

The interleaved modes described in this document have been implemented and tested in the NTP reference implementation. In the present implementation, drivestamps are captured upon return from the I/O routines. They are more accurate than the softstamps used by the original basic modes, but not as accurate as those captured by the hardware (hardstamps), as in the IEEE 1588 Precision Time Protocol (PTP).

The plan for this document is first to consider general principles of correctness, error scenarios and protocol vulnerabilities. Then for each mode it describes the protocol state machine, its state variables, state transition rules and means for error detection and recovery. This is followed by a detailed description of each mode and and example Finally, an example is presented that shows how the protocol automatically reverts to basic mode when confronted with an NTPv4 implementation that does not support interleaved modes. [Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines) contains a set of flow charts accompanied by a short description of each.

[Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines) contains a detailed description of the state machines in the NTPv4 reference implementation. [Appendix B](/reflib/onwire/#appendix-b-the-ntp-simulator-program-ttxlevctt) describes a simulation program used to verify correct operation and to confirm reliable recovery from packet loss, duplicate packet, protocol restart and packets crossing in flight.

* * *

#### Preliminaries

The symmetric modes operate using a sequence of rounds, each consisting of a transmit packet followed by a receive packet, but either of both of these packets could be lost. A round is correct if both packets are correctly received. In order to verify correctness of the protocol, it is necessary to prove a liveness assertion; that is, the protocol always yields a correct round even if after an indefinite number of incorrect rounds.

Let _P_ be the probability of a correct round and _Q_ = 1 - _P_. Then, the probability of a correct round at the _k_th round is

`correct(_k_) = _PQ<sup>k</sup>_, (_k_ = 0, 1, ...), (1)`

so the overall success probability is the sum of (1) as _k_ approaches infinity. Representing the sum as a McLaurin series yields

`P[correct] = _P_ / (1 - _Q_). (2)`

Let _p_ be the probability that a packet is correctly received, then _P_ = _p_<sup>2</sup> and _Q_ = 1 - _p_<sup>2</sup>. Substituting in (2) we see that the limit approaches 1, which confirms the liveness assertion.

In the on-wire protocol there are no retransmission's; every packet carries at least one state variable which changes for every packet sent. Timestamps derived from the system clock are guaranteed to be monotone-definite increasing, as long as packets are sent at intervals much longer than the system clock tick. In this protocol the transmit timestamp is used as a nonce, which cannot be predicted. This is insured by inserting a random fuzz in the non-significant bits of the system clock as read. In principle, a violation of monotonicity could occur if the clock was intentionally set backwards. In addition, a packet can be dropped by the network due to congestion or a transmission error.

By the nature of the protocol, packets are highly unlikely to arrive out of order. They can be duplicated by the network due to collisions or link-level timeouts, or replayed by an intruder. Even if not authenticated, using the transmit timestamp as a nonce makes it highly unlikely that an intruder can manufacture a packet that results in a correct round.

The use of authentication is optional; but, if it is used, it is highly unlikely an intruder can replay a modified packet or manufacture a new packet acceptable to the receiver. Whether or not authenticated, an intruder can archive old packets and replay them in an attempt to disrupt the state machine. We assume that a replay can never arrive before the original packet and that it is highly unlikely that the original packet is lost to the intended receiver but not to the intruder.

* * *

#### Basic Symmetric Mode

Basic symmetric mode represents the current NTPv4 specification RFC 5905 supported by the reference implementation. Following is an example that illustrates typical operation in this mode starting from an unsynchronized condition.

![gif](/archives/pic/xlev5.gif)

**Figure 1. Basic Symmetric Mode**

Figure 1 illustrates the most general case where symmetric peers A and B independently measure the offset and delay relative to the other. Each packet transmitted is shown as an arrow with the receive timestamp at the head and the transmit timestamp at the tail. The timestamps shown are after arrival or departure of a packet and may overwrite earlier values. The shaded boxes hold timestamps captured from the system clock. The other boxes hold values copied from them, other state variables or packet headers. Those timestamps with asterisks (*) are softstamps; those without are drivestamps.

The figure shows three packet header variables, _t<sub>org</sub>_, _t<sub>rec</sub>_ and _t<sub>xmt</sub>_, and three state variables _org_, _rec_ and _aorg_. By convention, timestamps are shown in upper case, while state variables are shown in lower case. The state machine operates as follows. When a packet arrives, the transmit softstamp _t<sub>xmt</sub>_ is copied to _rec_ and the receive drivestamp to _dst_. When a packet departs, _rec_ is copied to _t<sub>org</sub>_, _dst_ to _t<sub>rec</sub>_ and the transmit softstamp to _org_ and _t<sub>xmt</sub>._ After the state variables have been updated, the timestamps are _T_<sub>1</sub> = _t<sub>org</sub>_ _T_<sub>2</sub> = _t<sub>rec</sub>_, _T_<sub>3</sub> = _t<sub>xmt</sub>_ and _T_<sub>4</sub> = _dst_. Thus,

`offset = [(_T_<sub>2</sub> - _T_<sub>1</sub>) + (_T_<sub>3</sub> - _T_<sub>4</sub>)] / 2`

`delay = (_T_<sub>4</sub> - _T_<sub>1</sub>) - (_T_<sub>3</sub> - _T_<sub>2</sub>)`

(Note that in these equations _T_<sub>1</sub> through _T_<sub>4</sub> represent bound variables and not the timestamps in Figure 1 and others below.)

Figure 1 applies also to client/server mode in which the server immediately returns a packet according to the above rules, but retains no state. Thus, if A is the client and B the server, the _T_<sub>3</sub> timestamp follows shortly after _T_<sub>2</sub> and the _T_<sub>7</sub> timestamp follows shortly after _T_<sub>6</sub>.

In the following descriptions, the packet contents are given in the form (_t<sub>org</sub>_, _t<sub>rec</sub>_, _t<sub>xmt</sub>_). To begin the round at _T_<sub>1</sub>, peer A sends (0, 0, _T_<sub>1</sub>) to B. Later, B sends (_T_<sub>1</sub>, _T_<sub>2</sub>, _T_<sub>3</sub>) to A. At _T_<sub>4</sub> the timestamps _T_<sub>1</sub>, _T_<sub>2</sub>, _T_<sub>3</sub> and the _dst_ variable _T_<sub>4</sub> are available to compute the offset and delay of B relative to A. In a similar fashion at _T_<sub>6</sub>, _T_<sub>3</sub>, _T_<sub>4</sub>, _t_<sub>5</sub> and _T_<sub>6</sub> are available to compute the offset and delay of A relative to B. The protocol is synchronized when both A and B have computed the offset and delay, in this case at _T_<sub>6</sub>.

In symmetric modes each peer independently polls the other peer, but not necessarily at identical intervals. Thus, one or the other peer might receive none, one or more than one packets between polls. This can result in lost packets and even cases where packets cross each other in flight. A peer is synchronized only when all four timestamps are available. The protocol is synchronized only when both peers are synchronized.

There are three exception conditions designed to deflect invalid, duplicate, unsynchronized or bogus packets.

*   A packet is invalid if (a) the packet is authenticated and the message authentication code (MAC) is invalid, (b) the packet header values violate the protocol specification, (c) the packet is a replay of the packet most recently received. In these cases the packet is discarded without updating the state variables.
*   A packet is unsynchronized if some header timestamps have not been initialized. In this case the state variables are updated, but the timestamps are not used to calculate offset and delay.
*   A packet is bogus ifthe packet origin timestamp _t<sub>org</sub>_ does not equal the origin state variable _org_; i.e., the packet does not belong to the current round. In this case the state variables are updated, but the values are not used to compute offset and delay.

After the state variables have been updated, _org_ is set to zero. Thus, all further packets, whether replays or not, will be considered bogus until the next poll is sent. As described in [Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines), the bogus test detects both dropped packet and old duplicates; that is, replays of packets other than the one most recent received.

An intruder can attempt to manufacture spurious packets with unrelated timestamps; however, a successful attack is not possible if the packets are authenticated. Even if not authenticated, the intruder cannot predict a valid _t<sub>org</sub>_, so the best it can do is disrupt the state machine without producing valid offset and delay values. If this is repeated sufficiently often, it amounts to a successful denial-of-service attack. If authentication is used, no attack of this type can succeed. So, the best the intruder can do is to replay old packets.

In basic symmetric mode, a replay of packet _T_<sub>1</sub>→_T_<sub>2</sub> will be discarded by peer B as a duplicate, but in client/server mode it will cause B to send a spurious packet _T_<sub>3</sub>→_T_<sub>4</sub> to A with invalid _T_<sub>3</sub>. However, as the original _T_<sub>3</sub>→_T_<sub>4</sub> has already arrived at A and set _org_ to zero, the replay will be discarded as bogus. In basic symmetric mode, a replay of some prior _T_<sub>1</sub>→_T_<sub>2</sub> would be detected as bogus by B, while in client/server mode the resulting _T_<sub>3</sub>→_T_<sub>4</sub> will be discarded as bogus by A.

Furthermore, consider what happens if packet _T_<sub>3</sub>→_T_<sub>4</sub> is lost. Peer A loses a round, but later transmits _T_<sub>5</sub>→_T_<sub>6</sub> and completes the round at _T_<sub>8</sub>. On the other hand, peer B detects a bogus packet _T_<sub>5</sub>→_T_<sub>6</sub> and loses a round, but completes the next round. As a general rule, the loss of a single packet causes both peers to to miss a round, but otherwise results in correct offset and delay values.

Finally, assume that packets _T_<sub>3</sub>→_T_<sub>4</sub> and _T_<sub>5</sub>→_T_<sub>6</sub> overlap in flight. In such a case both peers detect these as bogus and continue in the next round. If it happens that both peers use the same poll interval and continue in this this phase, this would violate the liveness assertion. For this reason, the reference implementation continually adjusts the phase of each peer so that each transmission is approximately midway between transmissions of the other peer. Additional details are in [Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines).

* * *

#### Interleaved Symmetric Mode

In interleaved modes the transmit timestamp, here called a drivestamp, is captured after the packet has been sent, so it cannot be sent in the same packet. A solution for this is the two-step or interleaved protocol described in this section. In this variant the transmit drivestamp for one packet is actually transmitted in the immediately following packet. The trick, however, is to implement the interleaved protocol without changing the NTP packet header format, without compromising backwards compatibility and without compromising the error recovery properties. Following is a typical example of operation starting from an unsynchronized condition.

![gif](/archives/pic/xlev6.gif)

**Figure 2. Interleaved Symmetric Mode**

Figure 2 illustrates a typical scenario involving peers A and B. Note that the receive (even-numbered) drivestamps are available immediately after the packet has been received, but the transmit (odd-numbered) drivestamps are available only after the packet has been sent.

In contrast to the basic protocol, which requires one round to calculate offset and delay, the interleaved protocol requires two rounds. The round that begins at _T_<sub>1</sub> is not complete until _T_<sub>8</sub> and the round that begins at _T_<sub>5</sub> is not complete until _T_<sub>12</sub>. However, the rate of offset/delay calculations is the same as the basic protocol. The NTP packet header fields are the same in the interleaved protocol as in the basic protocol, but carry different values.

The figure shows three packet header variables, _t<sub>org</sub>_, _t<sub>rec</sub>_ and _t<sub>xmt</sub>_, and four state variables, _rec_, _dst_, _aorg_ and _borg_. An additional state variable not shown is _xmt_, which is used only for duplicate detection and as a sanity check. There are two integer state variables not shown: _x_, which alternates between +1 and -1 for each packet sent, and _f_, which is used as a synchronization indicator. It is convenient to interpret the value _x_ = 0 as an instance of the basic mode protocol when both basic and interleaved modes are available.

When a packet is transmitted, _rec_ is copied to _t<sub>org</sub>_ and _dst_ to _t<sub>rec</sub>_. If _x_ = +1, the transmit drivestamp is copied to _aorg_ and _borg_ is copied to _t<sub>xmt</sub>_. If _x_ = -1, the transmit drivestamp is copied to _borg_ and _aorg_ is copied to _t<sub>xmt</sub>_. When a packet is received, the timestamps in (1) are _T_<sub>2</sub> = _rec_, _T_<sub>3</sub> = _t<sub>xmt</sub>_, and _T_<sub>4</sub> = _dst_. If _x_ = +1, _T_<sub>1</sub> = _aorg_; if _x_ = -1, _T_<sub>1</sub> = _borg_. After this, _t<sub>rec</sub>_ is copied to _rec_ and the receive drivestamp to _dst_.

The protocol must be synchronized before carrying valid timestamps. This is done when each peer transmits a synchronization packet to the other peer which sets its _f_ variable to 1. A detected error initiates a protocol restart which sets all state variables to 0, including the _f_ variable, but without affecting the _x_ variable.

There are four exception conditions designed to deflect invalid, duplicate, unsynchronized, or bogus packets, but they are slightly different than in the basic symmetric mode.

*   A packet is invalid if (a) the packet is authenticated and the message authentication code (MAC) is invalid, (b) the packet header values violate the protocol specification, (c) the packet is a replay of the packet most recently received. In these cases the packet is discarded without updating the state variables.
*   If any packet other than a synchronization packet is received while the _f_ variable is 0, the peer restarts the protocol and sends a synchronization packet.
*   A packet is unsynchronized if some header timestamps have not been initialized. In this case the state variables are updated, but the timestamps are not used to calculate offset and delay.
*   A packet is bogus if _t<sub>org</sub>_ does not match _T_<sub>4</sub>; i.e., the packet does not belong to the current round. In this case the peer restarts the protocol and sends a synchronization packet.

In Figure 2, _T<sub>8</sub>_ is the end of the interleaved round that begins at _T<sub>1</sub>_. After the state variables have been updated, the four timestamps _T<sub>1</sub>_, _T<sub>2</sub>_, _T<sub>3</sub>_ and _T<sub>4</sub>_ are available to determine the offset and delay of B relative to A. The reader can verify the four timestamps _T<sub>3</sub>_, _T<sub>4</sub>_, _T<sub>5</sub>_ and _T<sub>6</sub>_ are available at _T<sub>10</sub>_ to determine the offset and delay of A relative to B.

While replayed and bogus packets are detected and discarded as in basic symmetric mode, recovery generally requires two rounds, instead of one, in order to resynchronize the state variables. Additional details are in [Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines).

* * *

#### Interleaved Broadcast Mode

In broadcast mode the client responds to the first broadcast received by executing one round of the client/server protocol in order to calibrate the roundtrip delay. This round may be repeated at intervals as necessary. In addition, this round can be used to calibrate the difference between the time delivered via the broadcast spanning tree and the time delivered by the unicast spanning tree. This is most useful in large multicast systems using distance-vector multicasst protocol (DVMRP) or protocol-independent multicast (PIM) technology.

The IEEE 1588 Precision Time Protocol (PTP) master broadcasts a <tt>Sync</tt> message to the slaves, which capture the receive timestamp _T_<sub>2</sub>. Immediately thereafter the master broadcasts a <tt>Follow_up</tt> message including the transmit timestamp of the <tt>Sync</tt> message _T_<sub>1</sub>. Some time later each client separately sends a <tt>Delay_req</tt> message to the master and captures the transmit timestamp _T_<sub>3</sub>. The master returns a <tt>Delay_resp</tt> message containing the receive timestamp _T_<sub>4</sub> for the <tt>Delay_req</tt> message. The clients collect these fourtimestamps to calculate the offset and delay as in the NTP client/server protocol (1) with the offset sign inverted.

The principal difference between the interleaved broadcast protocol and PTP is that the broadcast transmit drivestamp _T_<sub>1</sub> is actually sent in the following broadcast message and the remaining timestamps are obtained by the same stateless protocol used in NTP client/server modes, although slightly modified.

The interleaved protocol uses the same packet header format as the basic protocol, but includes the transmit drivestamp captured in the previous packet. While softstamps are not used in the interleaved protocol, they are included to support both basic and interleaved modes with the same packet stream, as well as to detect errors in the interleaved mode. When interleaved broadcast mode is not supported, the the _t<sub>org</sub>_ and _t<sub>rec</sub>_ header fields are unused and ordinarily set to zero. When interleaved broadcast mode is supported, the clients will note that _t<sub>org</sub>_ is nonzero and switch to interleaved mode.

![gif](/archives/pic/xlev7.gif)

**Figure 3. Interleaved Broadcast Mode**

Figure 3 shows a typical scenario where the clock is updated as each broadcast packet arrives at _T_<sub>2</sub>, _T_<sub>4</sub>, _T_<sub>12</sub> and _T_<sub>14</sub>. . Note that the server B alternates between_aorg_ and _borg_ only in order to simplify the implementation when supporting the multiple modes described in this document, but otherwise this distinction is unimportant.

The figure shows three packet header variables, _t<sub>org</sub>_, _t<sub>rec</sub>_ and _t<sub>xmt</sub>_, and four state variables, _rec_, _dst_, _aorg_ and _borg_. Although not shown, an additional state variable _b_ is used as a switch and an additional state variable _d_ is used as the computed roundtrip delay. As in previous descriptions, state variable _xmt_ is used to detect duplicates, but not shown.

The calibration round is similar to the basic client/server round. It begins when the client sends a packet to the server at _T_<sub>5</sub> in the figure. When the stateless server replies at _T_<sub>8</sub>, _t<sub>rec</sub>_ is copied to _rec_ and state variable _b_ is set to one. It could be that either or both packets are lost, in which case the round is tried again at the next opportunity. If Autokey is in use, it may take several rounds during which the Autokey dance verifies the server; however, _b_ should be set only when the dance is complete.

Upon arrival of the next broadcast packet at _T_<sub>12</sub> and _b_ is set, the timestamps _T_<sub>1</sub> = _t<sub>org</sub>_, _T_<sub>2</sub> = _borg_, _T_<sub>3</sub> = _aorg_, and _T_<sub>4</sub> = _rec,_ are used as in (1) to calculated the offset and delay _d_. When _d_ has been initialized, _b_ is set to zero. However, note that the sign of the offset is reversed as in PTP. The client keeps the delay to use as later broadcast packets arrive.

For subsequent broadcast packets, the offset is

`offset = (_t<sub>org</sub>_+ _d_ / 2) - _dst_`.

An exceptional case occurs when a broadcast packet is received after the client packet at _T_<sub>5</sub> and before the server packet when _b_ is set. In this case the calculated delay has a negative sign, but is otherwise valid. In this case the actual delay is the calculated delay with positive sign.

There are three exception conditions designed to deflect invalid, duplicate, unsynchronized, or bogus packets.

*   A packet is invalid if (a) the packet is authenticated and the message authentication code (MAC) is invalid, (b) the packet header values violate the protocol specification, (c) the packet is a replay of the packet most recently received. In these cases the packet is discarded without updating the state variables.
*   A packet is unsynchronized if some header timestamps have not been initialized. In this case the state variables are updated, but the timestamps are not used to calculate offset.
*   Note that the difference between the transmit drivestamp _T_<sub>4</sub> and corresponding softstamp _rec_ (before _rec_ is updated) represents the output message digest and queuing delay. If this quantity is less than zero or greater than a maximum possible digest and queuing delay, the packet is bogus and not used to calculate offset.

In contrast to the basic and interleaved symmetric modes, interleaved broadcast mode is vulnerable to old duplicates, which can produce erroneous offset calculations. However, the result would ordinarily be considered spurious and discarded by the popcorn spike suppressor or clock state machine used in the reference implementation. This is the same means for defense used in the basic modes Additional details are in [Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines).

* * *

#### Error Detection and Recovery

In the scheme of things, error packets are rare, especially in fast LANs where propagation delays are very small and poll intervals are in the order of many seconds. However, there is one instance where this can be useful. It occurs when a peer is initially configured to operate in interleaved mode and is presented with a client capable only of basic mode.

![gif](/archives/pic/xlev8.gif)

**Figure 4. Error Recovery in Basic Symmetric Mode**

In Figure 4, peer A can operate only in basic interleaved mode, but peer B is initially configured in interleaved symmetric mode. When A begins operations, B stumbles along until failing the bogus test at _T_<sub>10</sub>. It then checks for a bogus packet in basic interleaved mode by comparing _aorg_ to _t<sub>org</sub>_. If they match, the packet is legitimate in basic symmetric mode, so B continues in this mode. If they do not match, the packet is bogus in interleaved symmetric mode, so B continues in this mode. After synchronizing again, both peers clank happily along in the same mode. In principle, the reverse case is possible, but not considered here.

* * *

#### Measured Performance

The interleaved modes have been implemented and tested in the reference implementation. However, a code surveyor might find it difficult to follow the code flow, as it is intertwined with the authentication and rate management systems. There is, however, a comprehensive test and simulation program described in the in the appendices called [xlev.c](/reflib/software/xlev.c) with header file [xlev.h](/reflib/software/xlev.h). It can be used to simulate all modes described in this document, as well as common error scenarios, including lost or duplicate packets, and protocol restarts. These can be controlled using a set of probability thresholds that can be specified as program options.

In a convincing test the simulator was run for about a million packets in interleaved symmetric mode. with the error probabilities set to about .05 for each of duplicates, old duplicates, dropped, protocol restarts and packet crosses in flight. The results for 1,035,714 packets sent found 793,704 successful packets, 45,643 duplicate packets, 181,161 bogus packets, 54,938 protocol restarts and 56,423 dropped packets for an overall throughput of 0.77. Even in this extreme case there were no undetected errors.

In interleaved modes the reference implementation uses timestamps captured at or near the device interrupt time (drivestamps). The receive drivestamp is captured upon return from the receive-packet interrupt routine and routine before the receive buffer is queued for later processing. The transmit drivestamp is captured upon return from the send-packet interrupt routine. Both timestamps are probably as accurate as possible without driver or hardware intervention.

The reference implementation also captures a softstamp before the message digest routine, as well as the drivestamp captured after the send-packet routine. The difference, called the interleaved or output delay, varies from 16 μs for a dual-core, 2.8 GHz Pentium 4 running FreeBSD 6.1 to 1100 μs for a Sun Blade 1500 running Solaris 10. In the following scenarios the network is a switched Ethernet operating at 100 Mb and the NTP packet is about 1000 bits or 10 μs.

On two identical Pentium 4 machines in symmetric mode, the measured output delay is 16 μs and remaining one-way delay components 45-150 μs. Two LAN segments account for 20 μs, which leaves 25-130 μs for input delay. The RMS jitter is 30-50 μs measured by the clock filter.

On two identical UltraSPARC machines running Solaris 10 in symmetric mode, the measured output delay is 160 μs and remaining one-way delay components 195 μs. Two LAN segments account for 20 μs, which leaves 175 μs for input delay. The RMS jitter is 40-60 μs measured by the clock filter. A natural conclusion is that the output delay is in general quite stable and most of the jitter is contributed by the network and input delays.

* * *

#### Appendix A. NTP Protocol State Machines

This appendix presents an overview of the protocol state machines used in the reference implementation to support the protocol modes described in this document. Simplified representations of these machines have been implemented in the NTP simulator described in [Appendix B](/reflib/onwire/#appendix-b-the-ntp-simulator-program-ttxlevctt). The figures in this appendix are derived almost intact from this program.

A single pair of state machines is used to support both basic and interleaved protocol modes. One of the machines is for the transmit process, which runs for each transmit packet; the other is for the receive process, which runs for each receive packet. The processes can run in one of five modes: client/server, basic symmetric, interleaved symmetric, basic broadcast and interleaved broadcast. In the description here, the transmit and receive state machines run in the same mode. There is no provision to automatically switch modes. In the broadcast modes there is no provision for the initial client/server volley to calibrate the delay.

| Variable | Name |
| ----- | ----- |
| _mode_ | Association Mode |
| _t<sub>org</sub>_ | Origin Timestamp |
| _t<sub>rec</sub>_ | Receive Timestamp |
| _t<sub>xmt</sub>_ | Transmit Timestamp |

**Table A.1 Packet Header Variables**

| Variable | Name |
| ----- | ----- |
| _rec_ | Receive Timestamp |
| _xmt_ | Transmit Timestamp |
| _dst_ | Destination Timestamp |
| _aorg_ | A Origin Timestamp |
| _borg_ | B Origin Timestamp |
| _x_ | Interleaved Switch |
| _f_ | Synchronization Switch |

**Table A.2 State Variables**

Tables A.1 and A.2 show the variables of interest in the following. They include three timestamp variables: _t<sub>org</sub>__, t<sub>rec</sub>_ and _t<sub>xmt</sub>_, which are included in the NTP packet header, five timestamp state variables _xmt_, _rec_, _dst_, _aorg_, _borg_, and two integer state variables _x_and _f_. Some state variables are not used in some modes. By convention in the following, the pseudo-state variable _clock_ designates the system clock at the time of reading.

There are in general four exceptions that can occur in the following diagrams:

*   Dropped - a transmitted packet is lost in the network due to congestion or data error.
*   Duplicate - a packet is received as a duplicate of the last packet sent.
*   Old duplicate - a packet is received as a duplicate of an earlier packet sent.
*   Restart - the protocol state machine has restarted with fresh state variables.

Depending on the mode, detection of these conditions can cause the loss of a packet, loss of a round or loss of two rounds.

![gif](/archives/pic/fig_1.gif)

**Figure A.1. Transmit Process**

Figure A.1 shows the operations of the transmit process in all five modes. Note that _x_ serves both as a switch to indicate basic mode (_x_ = 0) or interleaved mode (_x_ = ±1) to alternate the transmit timestamp between _aorg_ and _borg_. It is set at configuration time to 0 for basic mode or +1 for interleaved mode.

While presented for simplicity in the figure, the clock is actually read twice. Before calling the output packet routine, the clock is read and saved as the _t<sub>xmt</sub>_ softstamp sent in the packet. Upon return from the output interrupt routine, the clock is read again and saved as the _borg_ drivestamp to be sent in the next packet.

Note that in interleaved broadcast mode _t<sub>org</sub>_, ordinarily zero in previous NTP versions, is hijacked to hold the previous transmit drivestamp. This is how a broadcast client recognizes whether basic or interleaved mode is in use. Clients conforming to the NTPv4 specification ignore _t<sub>org</sub>_ and _T__<sub>rec</sub>_.

![gif](/archives/pic/fig_2.gif)

**Figure A.2. Receive Process - Broadcast Mode**

The function of the receive process is to determine the timestamps used to calculate offset and delay. Figures A.2, A.3, A.4 and A.5 show the receive process in all modes and how the various modes are determined. Note that these figures represent segments of one routine consisting of three if/else clauses. The clause is selected by the _mode_ variable in the NTP packet header and the _x_ state variable. If _x_ is zero, the mode is either client/server, basic symmetric or basic broadcast. If not, the mode is interleaved symmetric, since the broadcast modes, whether basic or interleaved, are determine from a packet header timestamp. In addition, an internal variable _err_ is used to convey status information for later use in the sanity checks. A variable called _f_ is set to 1 upon completion of an initial synchronization sequence. A routine called reset(), not shown, clears all state variables to zero with the exception of _x_.

In interleaved broadcast and interleaved symmetric modes, some errors are detected by a bounds check on a delay or offset statistic. The parameter MAX is assumed somewhat less than half the poll interval, but somewhat greater than the maximum roundtrip delay.

In broadcast modes only two timestamps, _T_<sub>3</sub> and _T_<sub>4</sub>, are required to compute offset, since the delay is computed during the client/server calibration volley. In other modes four timestamps, _T_<sub>1</sub>, _T_<sub>2</sub>, _T_<sub>3</sub> and _T_<sub>4</sub>, are required to compute offset and delay.

In basic broadcast mode, _t<sub>org</sub>_ is zero, so the _t<sub>xmt</sub>_ softstamp and _dst_ receive drivestamps are used to calculate offset. In interleaved broadcast mode, _t<sub>org</sub>_ is hijacked to hold the previous transmit drivestamp. This is how a broadcast client recognizes whether basic or interleaved mode. Clients conforming to the NTPv4 specification ignore _t<sub>org</sub>_ and _t<sub>rec</sub>_.

There are three exception conditions. At the beginning of the receive routine duplicate packets are discarded immediately without affecting the state machine. SYNC occurs when the broadcast client restarts, while DELY occurs when the first packet following a dropped packet is received. In this case the time computed from the previous transmit softstamp to the previous transmit hardstamp exceeds a credible queuing delay. In either case the timestamps are not used and only one packet is skipped. However, an old duplicate must be detected by means other than the state machine.

![gif](/archives/pic/fig_3.gif)

**Figure A.3. Receive Process - Basic Symmetric Mode**

Figure A.3 shows the receive process operations in client and basic symmetric modes where _x_ is 0. There are three exception conditions. SYNC occurs at protocol restart, ERRR occurs as the result of a protocol error, while BOGS occurs when the packet violates the loopback test. ERRR occurs only in case of a program error or a massive barrage of multiple unrelated errors, while BOGS occurs when the origin softstamp in the packet does not match the origin softstamp for the round. This usually occurs when a packet is dropped or when packets cross in flight.

If any of these conditions occur, the timestamps are not used and one or more packets are skipped. A dropped packet results in a bogus exception at the next received packet and a delay of one packet, while a protocol restart by either peer results in a delay of one packet. The other exceptions result in a delay of one round (two packets). There are no ambiguous conditions that are not detected by the state machine.

![gif](/archives/pic/fig_4.gif)

**Figure A.4. Receive process - Interleaved Symmetric Mode**

Figure A.4 shows the operations of the receive process in interleaved symmetric mode. The _x_ variable determines which of the two origin drivestamps _aorg_ or _borg_, is used. Ordinarily, it follows the same variable used a the transmit process, but if a packet is lost or the protocol is restarted, the peers will be out of phase, resulting in a bogus packet and protocol restart.

There are five intricately designed exceptions. SYNC occurs in two cases when the protocol is restarted in either or both peers. HOLD occurs when one peer is waiting for the other to complete the synchronization process. As in basic symmetric mode, ERRR occurs as the result of a protocol error, while BOGS occurs when a bogus packet is received as a result of a dropped packet or crossed packets in flight. The reset() routine is called when an exception is found by peer A, for example. It sets all state variables, including _f_, to 0 without changing the _x_ variable. This causes peer A to send a reset packet consisting of three zero timestamps to peer B, causing it to send a reset packet to A. When each peer receives the reset packet, it sets the _f_ variable to 1. If for some reason peer B does not respond to the reset sequence, peer A continues to send the reset sequence until B does respond. When both peers have set the _f_ variable to 1, operation continues normally.

If any of these conditions occur, the timestamps are not used and one or more packets are skipped. A protocol restart results in a delay of three packets, or when each peer has completed one round. Packets crossed in flight result in a delay of one round, where each peer detects a bogus packet from the other. Other exceptions result in a delay of two rounds (four packets). There are no ambiguous conditions that are not detected by the state machine.

![gif](/archives/pic/fig_5.gif)

**Figure A.5. Timestamp Order Detection**

When the three receive process segments have complete operations, variable _err_ contains the completion code. Figure A.5 shows the subsequent operations. If this code is not OK, an error has occurred and operation continues in the next round. However, even if OK there may still be errors due to invalid timestamp ordering. Especially if the frequency of lost packets and packet crosses in flight are uncomfortably high, like ten percent. This can result in some rather messy conditions where restarts occur during restarts or packet crosses in flight. These cases are detected by two rules:

As long as the clocks are never set backwards, _T_<sub>4</sub> must be later than _T_<sub>1</sub> and _T_<sub>4</sub> must be later than _T_<sub>4</sub>. This is called the valid test. In the delay computation all packets must be from the same round. If packets are from different rounds, the computed delay will be less than zero or greater than one poll interval. This is called the delay test.

Both tests are down for all modes, although T1 and T2 are not significant in broadcast mode.

if not OK If OK, a final sanity check is performed to detect what may seem a bizarre condition when two packets in a row have been lost. If so, either _T_<sub>4</sub> is less than _T_<sub>1</sub> or _T_<sub>3</sub> is less than _T_<sub>2</sub>. This cannot happen with a monotone-definite increasing clock, so in this case operation continues in the next round. If this and all other sanity checks are passed, the offset and delay are computed and operation continues in the next round.

* * *

#### Appendix B. The NTP Simulator Program <tt>xlev.c</tt>

The NTP simulation program file [<tt>xlev.c</tt>](/reflib/software/xlev.c) and header file [<tt>xlev.h</tt>](/reflib/software/xlev.h) are designed to exhaustively test the protocol state machine under conditions of random packet drops, random packet duplicates, random protocol restarts and occasions where packets cross in flight. To build, install both files and compile with <tt>gcc</tt>. A list of command line options is given below.

The program supports all NTP modes, including client/server mode, basic and interleaved symmetric modes, and basic and interleaved broadcast modes, although not all random functions are supported in client/server mode. It supports two peers A and B using the state machines described in [Appendix A](/reflib/onwire/#appendix-a-ntp-protocol-state-machines). In symmetric modes, peer A sends a packet to peer B, then B sends a packet to A. In broadcast modes, server A sends a packet to client B, but B sends no packets. Operation continues in this way for a specified number of rounds. When complete the program displays the number of packets sent, number of correct rounds and number of error rounds. An error round indicates that a the protocol state machine detected a condition where the offset/delay could not be reliably determined..

The program can produce a trace with one line after each received packet event. The format of this line is:

`nnnnn c pkt dd dd dd st dd dd dd dd dd f ts dd dd dd dd code`.

where _<tt>nnnnn</tt>_ shows the simulated time for the event, in seconds, while _<tt>c</tt>_ designates which peer receiving the event, A or B. In all but broadcast client mode, the trace lines alternate between A and B. The three decimal fields following <tt>pkt</tt> are the packet header fields in the order origin (_t<sub>org</sub>_), receive (_t<sub>rec</sub>_) and transmit (_t<sub>xmt</sub>_). The five decimal fields following <tt>st</tt> are the state variables in the order receive (_rec_) , transmit (_xmt_), destination (_dst_), a-origin (_aorg_) and b-origin (_borg_). The single letter _<tt>f</tt>_ shows the flags variable in hex. See the <tt>xlev.h</tt> file for decoding. The four decimal fields following <tt>ts</tt> are the timestamps in the order origin (_t_<sub>1</sub>), receiver (_t_<sub>2</sub>), transmit (_t_<sub>3</sub>) and destination (_t_<sub>4</sub>). The _<tt>code</tt>_ string specifies the disposition of the packet with values:

<dt><tt>ok</tt></dt>

The timestamps are valid and in the correct order.

<dt><tt>duplicate</tt></dt>

The packet is a duplicate of the immediately preceding packet sent to the same peer.

<dt><tt>bogus</tt></dt>

The packet failed the loopback test.

<dt><tt>sync</tt></dt>

The protocol has not yet synchronized.

<dt><tt>holdoff</tt></dt>

The protocol is in a temporary hold-off state.

<dt><tt>dropped</tt></dt>

The packet has been dropped.

<dt><tt>not ready</tt></dt>

A packet is received by this peer before the first packet has been sent.

<dt><tt>invalid</tt></dt>

The timestamp sequence order is incorrect; i.e., the destination timestamp is received later than the origin timestamp. This can happen in some modes when two successive packets are dropped.

<dt><tt>delay</tt></dt>

The calculated delay is less than zero or greater than the maximum anticipated roundtrip time.

<dt><tt>offset</tt></dt>

The magnitude of the calculated offset is greater than the poll interval.

<dt><tt>error</tt></dt>

All sanity checks have been passed, but the timestamp sequence order is incorrect. This should never happen, as it indicated a failure of the design.

In all except the <tt>ok</tt> case, the packet is dropped before the timestamps are used for offset/delay calculation.

* * *

#### Command Line Options

The following options can be used on the command line. Probabilities are specified as a fraction in the range 0 to 1, with default 0. The poll intervals default to 8 s. An occasional instance of a packet crossing in flight can be created by specifying poll intervals that are relatively prime. The <tt>-d</tt>, <tt>-p</tt> and <tt>-r</tt> options are not mutually exclusive and can be present on the same line.

<dt><tt>-a</tt></dt>

Specify the poll interval for the A peer.

<dt><tt>-b</tt></dt>

Specify the poll interval for the B peer.

<dt><tt>-d</tt> <_prob_></dt>

Specify he probability that the last packet sent will by duplicated.

<dt><tt>-m</tt> <_mode_></dt>

Specify the modes of A and B. Mode c is client/server, where A is the client and B the server; mode s is symmetric, where A and B are peers; mode b is broadcast, where A is the client and B the server. The default is s.

<dt><tt>-o</tt> <_prob_></dt>

Specify the probability that the packet before the last one sent will be duplicated.

<dt><tt>-p</tt> <_prob_></dt>

Specify the probability that a packet will be dropped.

<dt><tt>-r</tt> <_prob_></dt>

Specify the probability that the protocol will be restarted.

<dt><tt>-s</tt> <_maxsim_></dt>

Specify the maximum number of rounds in the simulation. The default is 40.

<dt><tt>-t</tt></dt>

Enable packet trace. The default is disable.

<dt><tt>-x</tt></dt>

Enable interleaved mode. The default is basic mode.