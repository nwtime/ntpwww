---
title: "Association Management"
description: "There are three types of associations in NTPv4: persistent, preemptable and ephemeral. The type of association determines when a command is mobilized and demobilized."
type: archives
---

![gif](/documentation/pic/alice51.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Make sure who your friends are.

* * *

#### Table of Contents

*   [Association Modes](/documentation/4.2.8-series/assoc/#association-modes)
*   [Client/Server Mode](/documentation/4.2.8-series/assoc/#clientserver-mode)
*   [Symmetric Active/Passive Mode](/documentation/4.2.8-series/assoc/#symmetric-activepassive-mode)
*   [Broadcast/Multicast Modes](/documentation/4.2.8-series/assoc/#broadcastmulticast-modes)
*   [Manycast and Pool Modes](/documentation/4.2.8-series/assoc/#manycast-and-pool-modes)
*   [Poll Interval Management](/documentation/4.2.8-series/assoc/#poll-interval-management)
*   [Burst Options](/documentation/4.2.8-series/assoc/#burst-options)

* * *

#### Association Modes

This page describes the various modes of operation provided in NTPv4. There are three types of associations in NTP: _persistent_, _preemptable_ and _ephemeral_. Persistent associations are mobilized by a configuration command and never demobilized. Preemptable associations, which are new to NTPv4, are mobilized by a configuration command which includes the <code>preempt</code> option or upon arrival of an automatic server discovery packet. They are demobilized by timeout or when preempted by a "better" server, as described on the [Automatic Server Discovery Schemes](/documentation/4.2.8-series/discover/) page. Ephemeral associations are mobilized upon arrival of broadcast or multicast server packets and demobilized by timeout.

Ordinarily, successful mobilization of ephemeral associations requires the server to be cryptographically authenticated to the client. This can be done using either symmetric key or Autokey public key cryptography, as described on the [Authentication Support](/documentation/4.2.8-series/authentic/) page.

There are three principal modes of operation in NTP: client/server, symmetric active/passive and broadcast/multicast. There are three automatic server discovery schemes in NTP: broadcast/multicast, manycast and pool described on the [Automatic Server Discovery Schemes](/documentation/4.2.8-series/discover/) page. In addition, the [burst options](/documentation/4.2.8-series/assoc/#burst-options) and [orphan mode](/documentation/4.2.8-series/orphan/) can be used in appropriate cases.

Following is a summary of the operations in each mode. Note that reference to option applies to the commands described on the [Server Commands and Options](/documentation/4.2.8-series/confopt/) page. See that page for applicability and defaults.

* * *

#### Client/Server Mode

Client/server mode is the most common configuration in the Internet today. It operates in the classic remote-procedure-call (RPC) paradigm with stateless servers and stateful clients. In this mode a host sends a client (mode 3) request to the specified server and expects a server (mode 4) reply at some future time. In some contexts this would be described as a "pull" operation, in that the host pulls the time and related values from the server.

A host is configured in client mode using the <code>server</code> (sic) command and specifying the server DNS name or IPv4 or IPv6 address; the server requires no prior configuration. The <code>iburst</code> option described later on this page is recommended for clients, as this speeds up initial synchronization from several minutes to several seconds. The <code>burst</code> option described later on this page can be useful to reduce jitter on very noisy dial-up or ISDN network links.

Ordinarily, the program automatically manages the poll interval between the default minimum and maximum values. The <code>minpoll</code> and <code>maxpoll</code> options can be used to bracket the range. Unless noted otherwise, these options should not be used with reference clock drivers.

* * *

#### Symmetric Active/Passive Mode

Symmetric active/passive mode is intended for configurations where a clique of low-stratum peers operate as mutual backups for each other. Each peer operates with one or more primary reference sources, such as a reference clock, or a set of secondary (stratum, 2) servers known to be reliable and authentic. Should one of the peers lose all reference sources or simply cease operation, the other peers will automatically reconfigure so that time and related values can flow from the surviving peers to all hosts in the subnet. In some contexts this would be described as a "push-pull" operation, in that the peer either pulls or pushes the time and related values depending on the particular configuration.

A symmetric active peer sends a symmetric active (mode 1) message to a designated peer. If a matching configured symmetric active association is found, the designated peer returns a symmetric active message. If no matching association is found, the designated peer mobilizes a ephemeral symmetric passive association and returns a symmetric passive (mode 2) message. Since an intruder can impersonate a symmetric active peer and cause a spurious symmetric passive association to be mobilized, symmetric passive mode should always be cryptographically validated.

A peer is configured in symmetric active mode using the <code>peer</code> command and specifying the other peer DNS name or IPv4 or IPv6 address. The <code>burst</code> and <code>iburst</code> options should not be used in symmetric modes, as this can upset the intended symmetry of the protocol and result in spurious duplicate or dropped messages.

As symmetric modes are most often used as root servers for moderate to large subnets where rapid response is required, it is generally best to set the minimum and maximum poll intervals of each root server to the same value using the <code>minpoll</code> and <code>maxpoll</code> options.

* * *

#### Broadcast/Multicast Modes

NTP broadcast and multicast modes are intended for configurations involving one or a few servers and a possibly very large client population. Broadcast mode can be used with Ethernet, FDDI and WiFi spans interconnected by hubs or switches. Ordinarily, broadcast packets do not extend beyond a level-3 router. Where service is intended beyond a level-3 router, multicast mode can be used. Additional information is on the [Automatic NTP Configuration Options](/documentation/4.2.8-series/discover/) page.

A server is configured to send broadcast or multicast messages using the <code>broadcast</code> command and specifying the subnet address for broadcast or the multicast group address for multicast. A broadcast client is enabled using the [<code>broadcastclient</code>](/documentation/4.2.8-series/confopt/#auxiliary-commands) command, while a multicast client is enabled using the [<code>multicastclient</code>](/documentation/4.2.8-series/confopt/#auxiliary-commands) command and specifying the multicast group address. Multiple commands of either type can be used. However, the association is not mobilized until the first broadcast or multicast message is actually received.

* * *

#### Manycast and Pool Modes

Manycast and pool modes are automatic discovery and configuration paradigms new to NTPv4. They are intended as a means for a client to troll the nearby network neighborhood to find cooperating willing servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. The intended result is that each client mobilizes ephemeral client associations with some number of the "best" of the nearby servers, yet automatically reconfigures to sustain this number of servers should one or another fail. Additional information is on the [Automatic Server Discovery Schemes](/documentation/4.2.8-series/discover/) page.

* * *

#### Poll Interval Management

NTP uses an intricate heuristic algorithm to automatically control the poll interval for maximum accuracy consistent with minimum network overhead. The algorithm measures the incidental offset and jitter to determine the best poll interval. When <code>ntpd</code> starts, the interval is the default minimum 64 s. Under normal conditions when the clock discipline has stabilized, the interval increases in steps to the default maximum 1024 s. In addition, should a server become unreachable after some time, the interval increases in steps to the maximum in order to reduce network overhead. Additional information about the algorithm is on the [Poll Program](/documentation/4.2.8-series/poll/) page.

The default poll interval range is suitable for most conditions, but can be changed using options on the [Server Commands and Options](/documentation/4.2.8-series/confopt/) and [Miscellaneous Options](/documentation/4.2.8-series/miscopt/) pages. However, when using maximum intervals much larger than the default, the residual clock frequency error must be small enough for the discipline loop to capture and correct. The capture range is 500 PPM with a 64-s interval decreasing by a factor of two for each interval doubling. At a 36-hr interval, for example, the capture range is only 0.24 PPM.

In the NTPv4 specification and reference implementation, the poll interval is expressed in log<sub>2</sub> units, properly called the _poll exponent._ It is constrained by the lower limit <code>minpoll</code> and upper limit <code>maxpoll</code> options of the [<code>server</code>](/documentation/4.2.8-series/confopt/#server-command-options) command. The limits default to 6 (64 s) and 10 (1024 s), respectively, which are appropriate for the vast majority of cases.

As a rule of thumb, the expected errors increase by a factor of two as the poll interval increases by a factor of four. The poll interval algorithm slowly increases the poll interval when jitter dominates the error budget, but quickly reduces the interval when wander dominates it. More information about this algorithm is on the [How NTP Works](/documentation/4.2.8-series/warp/) page.

There is normally no need to change the poll limits, as the poll interval is managed automatically as a function of prevailing jitter and wander. The most common exceptions are the following.

*   With fast, lightly loaded LANs and modern processors, the nominal Allan intercept is about 500 s. In these cases the expected errors can be further reduced using a poll exponent of 4 (16 s). In the case of the pulse-per-second (PPS) driver, this is the recommended value.
*   With symmetric modes the most stable behavior results when both peers are configured in symmetric active mode with matching poll intervals of 6 (64 s).
*   The poll interval should not be modified for reference clocks, with the single exception the ACTS telephone modem driver. In this case the recommended minimum and maximum intervals are 12 (1.1 hr) and 17 (36 hr), respectively.

* * *

#### Burst Options

Occasionally it is necessary to send packets temporarily at intervals less than the poll interval. For instance, with the <code>burst</code> and <code>iburst</code> options of the [<code>server</code>](/documentation/4.2.8-series/confopt/#server-command-options) command, the poll program sends a burst of several packets at 2-s intervals. In either case the poll program avoids sending needless packets if the server is not responding. The client begins a burst with a single packet. When the first packet is received from the server, the client continues with the remaining packets in the burst. If the first packet is not received within 64 s, it will be sent again for two additional retries before beginning backoff. The result is to minimize network load if the server is not responding. Additional details are on the [Poll Program](/documentation/4.2.8-series/poll/) page.

There are two burst options where a single poll event triggers a burst. They should be used only with the <code>server</code> and <code>pool</code> commands, but not with reference clock drivers nor symmetric mode peers. In both modes, received server packets update the clock filter, which selects the best (most accurate) time values. When the last packet in the burst is sent, the next received packet updates the system variables and adjusts the system clock as if only a single packet exchange had occurred.

The <code>iburst</code> option is useful where the system clock must be set quickly or when the network attachment requires an initial calling or training sequence, as in PPP or ISDN services. In general, this option is recommended for <code>server</code> and <code>pool</code> commands. A burst is sent only when the server is unreachable; in particular, when first starting up. Ordinarily, the clock is set within a few seconds after the first received packet. See the [Clock State Machine](/documentation/4.2.8-series/clock/) page for further details about the startup behavior.

The <code>burst</code> option is useful in cases of severe network jitter or when the network attachment requires an initial calling or training sequence. This option is recommended when the minimum poll exponent is larger than 10 (1024 s). A burst is sent only when the server is reachable. The number of packets in the burst is determined by the poll interval so that the average interval between packets (headway) is no less than the minimum poll interval for the association.