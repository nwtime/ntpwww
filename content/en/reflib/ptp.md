---
title: "IEEE 1588 Precision Time Protocol (PTP)"
type: archives
toc_hide: true
---

![gif](/archives/pic/alice47.gif)

from [_Alice's Adventures in Wonderland_](/reflib/pictures), Lewis Carroll

Public transport in Oz

Last update 18-May-2012

* * *

#### Table of Contents

*  [Abstract](/reflib/ptp/#abstract)
*  [Introduction](/reflib/ptp/#introduction)
*  [Timestamp Capture](/reflib/ptp/#timestamp-capture)
*  [On-Wire Protocols](/reflib/ptp/#onwire-protocols)
*  [Master-Slave Mode](/reflib/ptp/#masterslave-mode)
*  [Broadcast Mode](/reflib/ptp/#broadcast-mode)
*  [Routers and Switches](/reflib/ptp/#routers-and-switches)
*  [Conclusions](/reflib/ptp/#conclusions)
*  [References](/reflib/ptp/#references)

* * *

#### Abstract

This document explores the similarities and differences between the Network Time Protocol (NTP) and the IEEE 1588 Precision Time Protocol (PTP). For the configurations considered in this doecument, these protocols provide clock synchronization in high-speed local area networks. Of particular interest are the opportunities for interoperation between the protocols and how they can be used in a dual-protocol server and client.

* * *

#### Introduction

The Network Time Protocol (NTP) and Precision Time Protocol (PTP) are used to synchronize clocks in the Internet computing infrastructure. NTP has evolved over the last thirty years as documented in RFC 5905 <sup>[2](#myfootnote2)</sup>, while PTP has evolved over the last several years as documented in the IEEE standards <sup>[4](#myfootnote4)</sup>. The two protocols have a substantially different user community, accuracy and precision expectations and supporting hardware.

PTP is used most often to synchronize device clocks in special-purpose industrial automation and measurement networks. These devices are connected to dedicated, high-speed Ethernet LAN segments interconnected by switches. NTP is used most often to synchronize system clocks in general-purpose Unix, Windows and VMS workstations and servers. These machines are are connected by the global internet by routers and gateways and operate over a wide range of network speeds.

This document explores their individual characteristics, accuracy expectations and interoperability possibilities. Following is a summary of the similarities and differences between the two protocols.

<dt>Harware Timestamps</dt>

NTP requires no hardware provisions to capture timestamps other than a typical Unix timer interrupt or counter/timer motherboard chip. PTP normally includes hardware provisions in the servers, clients and switches to capture timestamps upon the passage of an Ethernet frame at the physical layer. Further information about timestamping for both NTP and PTP can be found in the white paper [Timestamp Capture Principles](/reflib/stamp).

<dt>On-Wire Protocol</dt>

The PTP on-wire protocol operates primarily in a broadcast mode where a grandmaster provides synchronization to multiple clients sharing the same network. Alternatively, the protocol can operate in a master/slave mode, where each client synchrhronizes to the grandmaster using a separate client/server message exchange. The NTP on-wire protocol can operate in broadcast, as well as master/slave, and symmetric modes where one or more primary servers provide synchronization to multiple clients on the same or different networks. This document is concerned primarily with broadcast configurations. Further information on NTP configurations can be found in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire).

<dt>Timescale</dt>

The PTP timescale is defined in seconds and nanoseconds. While the PTP specification defines no particular timescale and origin, the common assumption is that the POSIX timescale with origin 1 January 1970 is used, with or without leap seconds. The NTP timescale is defined in seconds and fraction with origin 1 January 1900, as described in the white paper [NTP Timestamp Calculations](/reflib/time). Discussion on UTC leap seconds is in the white paper [The NTP Timescale and Leap Seconds](/reflib/leap). Discussion on the extended NTP timescale and era considerations is in the white paper [The NTP Era and Era Numbering](/reflib/y2k).

<dt>Accuracy Expectations</dt>

The accuracy expectations of PTP synchronized clocks is in the order of 100 ns determined primarily by the resolution and stability of a dedicated clock oscillator and counter. The accuracy expectations of NTP vary widely, depending on the motherboard oscillator and counter. Typical results range from a few microseconds in PPS-assisted primary servers to tens of milliseconds in widely dispersed Internet networks.

<dt>Network Overhead</dt>

The network overhead in PTP networks is seldom an issue, as the update intervals are typically a few seconds over lightly loaded Ethernet LAN segments. The overhead in NTP networks is often of serious concern, as the network paths are often shared with demanding Internet applications including speech and video. In general, this requires update intervals in the range of one minute to several hours, depending on network characteristics and in some cases on network usage charges.

<dt>Optimization Algorithms</dt>

Both PTP and NTP use crafted algorithms to improve accuracy and select among a possibly complex set of network paths. PTP uses the Best Master Clock (BMC) algorithm to select the optimal path to the grandmaster as a function of various quality measures, including hop count. NTP uses a suite of mitigation algorithms, including the filter, select, cluster and combine algorithms, which depend on Byzantine agreement and statistical clustering principles.

<dt>Clock Discipline Algorithm</dt>

The PTP specification defines no algorithms to compensate for offset and frequency errors in either the device or system clocks. These algorithms are assumed to be implementation specific. The NTP specification defines a highly evolved, adaptive-parameter, hybrid phase-frequency lock loop. The discipline algorithm adjusts the system clock time and frequency in response to widely varying ambient conditions.

<dt>Security</dt>

Both NTP and PTP can provide message security in the form of symmetric key cryptography. In addition, NTP can provide a variant of public key cryptography called Autokey <sup>[3](#myfootnote3)</sup>. Further information that applies in part to both PTP and NTP can be found in the white paper [NTP Security Analysis](/reflib/security).

This document explores the technical issues implicit in the above. It characterizes PTP and NTP; in particular, the timestamp technology, on-wire protocol and discipline algorithms. It concludes with a discussion on NTP and PTP interoperability issues.

* * *

#### Timestamp Capture

PTP and NTP servers and clients use the on-wire protocols described in the next section to exchange timestamps used to synchronize the client clock to the server clock. The PTP and NTP protocols have much in common; both develop four timestamps, although in different ways. These timestamps are used to compute the clock offset and roundtrip delay for a client relative to a server.

PTP timestamps, properly called _preamble hardstamps,_ are captured by the Ethernet network interface card (NIC) hardware upon passage of a start of frame (SOF) symbol in the input and output frame data streams. The timestamp is captured at the media independent interface (MII) relative to a dedicated oscillator and counter within typically 100 ns.

Some 1588 Ethernet drivers use a dedicated input or output frame buffer to store a PTP protocol data unit (PDU) including a single timestamp field along with other related data. These designs us a field programmable gate array (FPGA) to monitor the frame data stream and can modify the timestamp fields on-fly. On output the timestamp field is updated after the frame has been sent. On input the field is updated after the frame has been received. If the timestamp field has been modified, the UDP checksum is recomputed before the frame is passed to the upper layer protocol.

NTP timestamps, properly called _trailer drivestamps,_ are captured by the Ethernet driver interrupt routine shortly after the checksum that terminates the frame. These timestamps are captured from the system clock, so include errors due to the operating system clock reading latencies. Relative to the preamble hardstamp, the trailer drivestamp is delayed by the frame and checksum transmission time plus a latency due to the interrupt queuing and processing time. As a result, NTP timestamps have a deterministic delay due to the transmission time plus a stochastic delay due to queuing and scheduling latencies. When calculating the clock offset, if the transmission rate and frame size are the same in both directions on the wire, the deterministic delays cancel out. However, the stochastic delay, amounting to a microsecond or two, remain.

It is important to emphasize that the overall synchronization accuracy and precision depends primarily on the accuracy and precision of the timestamps. In principle, either PTP or NTP can use either preamble hardstamps or trailer drivestamps, with the accuracy dependent on which method is used.

There is a valid argument that the continued downward cost of 1588  components, in particular the NIC engine, can lead to much less expensive 1588 NICs and switches. While the current NICs costs several hundred dollars, the Intel 1588 NIC chip, which includes timestamp capture buffers and an ARM processor on-chip, costs about $15 in quantity. However, the current NICs come with proprietor drivers bundled with Windows or Linux drivers that may not be appropriate for general applications.

* * *

#### On-Wire Protocols

The on-wire protocols used by PTP and NTP are intended to synchronize a secondary server or client to a primary server or grandmaster. While they are slightly difference, as described below, both accomplish the same thins. In a round initiated by either the client or server, the client or server A sends a request message to B. Then, B sends a response message to A.

In most applications, rounds are executed periodically,at intervals of a few seconds to a few tens of minutes.

In both PTP and NTP the protocol can operate in a point-to-point _master-slave mode_, or in a point-to-multipoint _broadcast mode_. In addition, NTP can operate in _symmetric mode_ in which either peer can provide synchronization to the other for backup..

![gif](/archives/pic/stamp2.gif)

**Figure 1. Master-Slave Mode**

* * *

#### Master-Slave Mode

Figure 1 illustrates how the NTP on-wire protocol operates in master-slave mode. Let A be the client and B the server. The roles are reversed in broadcast mode. .In this and subsequent figures in this document, messages are transmitted in the direction shown with timestamps captured at the beginning and end of transmission. First, A sends a client (mode 3) message to B, then B sends a server (mode 4) message to A. This is called a round. There are four timestamps involved, the _origin timestamp_ _T_<sub>1</sub> when the client message departs A, the _receive timestamp_ _T_<sub>2</sub> when this message arrives at B, the _transmit timestamp_ _T_<sub>3</sub> when the server message departs B, and the _destination timestamp_ _T_<sub>4</sub> when this message arrives at A.

In NTP master-slave mode, the on-wire protocol calculates the clock offset

`θ = [(_T_<sub>2</sub> − _T_<sub>1</sub>) + (_T_<sub>3</sub> − _T_<sub>4</sub>)] / 2`

and roundtrip delay

`δ = (_T_<sub>4</sub> − _T_<sub>1</sub>) − (_T_<sub>3</sub> − _T_<sub>2</sub>).`

While it is possible to use master-slave mode in PTP, this requires an awkward message exchange and is not likely to be used in practice.

* * *

#### Broadcast Mode

In broadcast mode for both NTP and PTP, the offset expression has an inverted sign, while the delay calculation is the same. Note that NTP can operate in either basic or interleaved broadcast mode. In this document, only NTP interleaved mode is considered. The on-wire protocol operations in broadcast mode are illustrated in Figure 2.

![gif](/archives/pic/bcst1.gif)

**Figure 2: Broadcast Mode**

In NTP interleaved broadcast mode, broadcast (mode 5) messages at _T_<sub>1</sub>, _T_<sub>3</sub>, _T_<sub>11</sub> and _T_<sub>13</sub> are sent by the broadcast server and received by each broadcast client separately at _T_<sub>2</sub>, _T_<sub>4</sub>, _T_<sub>12</sub> and _T_<sub>14</sub>, respectively. Each broadcast message includes the previous broadcast message transmit timestamp in a data field. For instance, the broadcast message sent at _T_<sub>3</sub> includes the transmit timestamp _T_<sub>1</sub>. Similarly, the broadcast messages sent at _T_<sub>11</sub> and _T_<sub>13</sub> include the transmit timestamps _T_<sub>3</sub> and _T_<sub>11</sub>, respectively. In order to calculate the roundtrip delay, a broadcast client can send a master-slave round, for example, beginning at _T_<sub>5</sub> and ending at _T_<sub>8</sub>.

Broadcast messages are sent by the broadcast server at regular intervals of about one minute in order to calculate the clock offset, while master-slave rounds are sent infrequently by each broadcast client in order to calibrate the roundtrip delay. In the master-slave round the receive timestamp _T_<sub>6</sub> of the request message sent at _T_<sub>5</sub> is captured by the broadcast server and returned in a data field of the response message received at _T_<sub>8</sub>. In the clock offset calculation, for example, the origin timestamp _T_<sub>3</sub> cannot be sent in the message at _T_<sub>3</sub>, so this timestamp is sent in the following broadcast message at _T_<sub>11</sub>. In this case, the origin timestamp is _T_<sub>3</sub>, receive timestamp _T_<sub>4</sub>, transmit timestamp _T_<sub>5</sub> and destination timestamp _T_<sub>6</sub>. although the complete set of timestamps is not available until _T_<sub>12</sub>. Thus, the clock offset determined at _T_<sub>12</sub> is

`θ = −[(_T_<sub>4</sub> − _T_<sub>3</sub>) + (_T_<sub>5</sub> − _T_<sub>6</sub>)] / 2`

and roundtrip delay

`δ = (_T_<sub>6</sub> − _T_<sub>3</sub>) − (_T_<sub>5</sub> − _T_<sub>4</sub>).`

In between master-slave rounds, the clock offset can be determined from the previous transmit and receive timestamps as at _T_<sub>14</sub>:

`θ = _T_<sub>11</sub> + δ / 2 −_T_<sub>12</sub>`

computed at _T_<sub>14</sub>.

The PTP on-wire broadcast protocol is similar to NTP, but using two messages to carry the broadcast timestamps, instead of the single message and interleaved design as in NTP. The protocol begins with a Synch message at _T_<sub>1</sub> in Figure 2. The broadcast client records the receive timestamp _T_<sub>2</sub>. The next message at _T_<sub>3</sub> is a Follow-Up message containing _T_<sub>1</sub> in a data field. The subsequent master-slave round beginning at _T_<sub>5</sub> is identical to that in NTP. The results are the originate timestamp _T_<sub>1</sub>, receive timestamp _T_<sub>2</sub>, transmit timestamp _T_<sub>5</sub> and destination timestamp_T_<sub>6</sub>. The clock offset is

`θ = −[(_T_<sub>2</sub> − _T_<sub>1</sub>) + (_T_<sub>5</sub> − _T_<sub>6</sub>)] / 2`

and roundtrip delay

`δ = (_T_<sub>6</sub> − _T_<sub>1</sub>) − (_T_<sub>5</sub> − _T_<sub>2</sub>).`

In between master-slave rounds, the clock offset can be determined from the previous transmit and receive timestamps as at _T_<sub>14</sub>:

`θ = _T_<sub>11</sub> + δ / 2 −_T_<sub>12</sub>.`

The only difference between NTP and PTP protocol is that NTP uses an interleaved design and single broadcast message, while PTP uses two messages, Sync and Follow-Up,. Subsequently, NTP uses a client (mode 3) and server (mode 4) exchange, while PTP uses a Delay_Req and Delay_Resp for the same purpose.

* * *

#### Routers and Switches

Routers are used to connect one network to another, while switches are used to connect computers to each other on the same network. Routers operate at the IP packet (level-3) layer and are usually slow compared to switches. Switches operate at the Ethernet frame (level 2) layer, usually well below capacity. While routers and switches can be used by either PTP or NTP, switching and queuing delays are much harder to control in routers than switches, so the advantages of PTP can be lost if multiple network hops are involved.

The transmission delay of a 1000-bit frame on a 100-mb/s LAN segment is about 10 μs , and this is highly repeatable for LANs with low traffic. This means that the flight time of the frame between one computer and another is twice this delay and the total roundtrip time is four times this delay. Note that in this and similar cases, the transmission delay is the same in either direction, even if multiple switch hops are involved.

A switch receives a frame on an ingress port and routes it to an egress port. This results in three sources of delay: propagation delay, transmission delay, and queuing delay. In general, the propagation and transmission delays can be predicted from knowledge of the channel parameters and frame length, but queuing delays cannot. However, as shown in the clock offset calculations in the previous section, if the overall delays between the server and client are the same in either direction, the accuracy of the clock offset calculation is not degraded. This applies to both NTP and PTP, even if hardware assisted timestamps are not available.

The queuing delay consists of two components, a stochastic contribution due to the hardware and operating system latencies, and a contribution when an egress frame is delayed while a previous frame is being transmitted. This is called _head-of-line_ (HOL) blocking. A working assumption in the NTP mitigation algorithms is that stochastic delays can be largely avoided by the the clock filter and popcorn spike suppressor algorithms. In principle, these algorithms can be used in PTP as well.

In order to preserve submicrosecond accuracy in PTP, the switches must have some provision to compensate for port-to-port residence time. This can be done in two ways, PTP boundary clocks (BC) and PTP transparent clocks (TC). BC switches function as secondary servers, as in NTP. They synchronize to an upstream server and provide synchronization to one or more downstream clients. A downstream BC client uses the same on-wire protocol as the grandmaster, including the BMC algorithm.

A TC switch uses a timestamp oscillator and counter to measure the residence time of a frame between its arrival at an upstream port and its departure from a downstream port. The timestamp counter need not be particularly accurate, as the residence time is typically only a few tens of microseconds. The switch latches a hardware timestamp upon arrival of a frame and records it in the frame buffer. The switch latches a timestamp upon departure of the frame and computes the residence time. The residence time is added to a field in the frame buffer upon departure. When the frame is received at the downstream destination , possibly after multiple switches, the accumulated value is used to correct the offset calculation.

There are no provisions in the NTP specification to employ the strategies used by PTP, but these could be added in an amendment. If this were done, the accuracy and precision of PTP could be extended to NTP.

* * *

#### Conclusions

In many respects, PTP and NTP have very similar objectives. They use an almost identical on-wire protocol that produces four timestamps, which are used to calculate clock offset and roundtrip delay. Both can operate in multiple strata where primary servers (grandmaster clocks) provide synchronization to secondary servers (boundary clocks), which in turn provide synchronization to clients (ordinary clocks).

As currently specified, PTP timestamps are derived from specialized hardware that tracks the SOF symbol in the frame data stream (hardstamps), while NTP timestamps are derived from the operating system driver (drivestamps). However, in principle, PTP could use drivestamps or NTP could use hardstamps with corresponding change in accuracy expectations. In fact, PTP with software derived timestamps (softstamps) has been used as a synchronization daemon in much the same way as SNTP. It would be an interesting project to adapt a 1588 NIC with PTP functionality to operate with NTP as well as PTP.

Perhaps the most useful design project would be an NTP reference clock driver based on PTP. In such a design the PTP subnet would operate in the normal manner with the same NTP daemon interface as a GPS reference clock. In effect, this would be a protocol translator mapping PTP to NTP. An alternative approach could use the PPS signal produced by some NICs, including the Network Instruments 1588, in the same manner as used with existing GPS receivers. However, there remains the issue of how to number the seconds, which presumably would be supplied using some other means.

Another useful development project would be to modify the Ethernet driver interface to support hardstamps provided by 1588 Ethernet chips, such as the Intel chip. This could provide a generic interface for PTP, NTP and perhaps other synchronization methods. For use with the current NTP reference implementation, this would require changes to the code both to provide receive hardstamps in the receive buffer, as well as means to provide transmit hardstamps via a reclaimed output buffer.

While a means to provide PTP synchronization to NTP clients is straightforward, a less obvious means would be to provide NTP synchronization to PTP clients. Without hardstamp capability, the PTP subnet would not perform as well as a PTP subnet with hardstamps, but might be useful in some scenarios where NTP is used as a tunnel between PTP clients. Designs such as this could be used to patch PTP islands together over Internet paths where dedicated Ethernet support is not available.

Since PTP is designed to operate in a relatively benign environment with low jitter and little threat of hostile interference, the paranoid mitigation algorithms used in NTP may not be appropriate for PTP. The PTP best master clock (BMC) algorithm is probably not well suited for NTP, while NTP algorithms to select and combine multiple sources may not be appropriate for PTP. In any case, if PTP is used to discipline the system clock, it would be wholly appropriate to use the precision kernel support originally designed for NTP, but could be used with other synchrotron designs as well.

* * *

#### References

<a name="myfootnote1">1</a>  Mills, D.L. Network Time Synchronization - the Network Time Protocol on Earth and in Space. CRC Press, 2011, 466 pp.

<a name="myfootnote2">2</a>  Mills, D., J. Martin (Ed.), et al. Network Time Protocol Version 4: protocol and algorithm specification. Request for Comments RFC 5905, Internet Engineering Task Force, June 2010.

<a name="myfootnote3">3</a>  Mills, D., B. Haberman (Ed.). Network Time Protocol Version 4: Autokey specification. Request for Comments RFC 5906, Internet Engineering Task Force, June 2010.

<a name="myfootnote4">4</a>  IEEE 1588 Precision Time Protocol (PTP) Version 2 Specification, IEEE, March 2008.
