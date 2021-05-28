---
title: "Association Management"
type: archives
---

![gif](/archives/pic/alice51.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/~mills/pictures.html)

Make sure who your friends are.

Last update: 21:56 UTC Friday, December 28, 2007

* * *

#### Table of Contents

*   [Association Modes](/archives/4.2.6-series/assoc/#association-modes)
*   [Client/Server Mode](/archives/4.2.6-series/assoc/#clientserver-mode)
*   [Symmetric Active/Passive Mode](/archives/4.2.6-series/assoc/#symmetric-activepassive-mode)
*   [Broadcast/Multicast Modes](/archives/4.2.6-series/assoc/#broadcastmulticast-modes)
*   [Manycast Mode](/archives/4.2.6-series/assoc/#manycast-mode)
*   [Orphan Mode](/archives/4.2.6-series/assoc/#orphan-mode)
*   [Burst Options](/archives/4.2.6-series/assoc/#burst-options)

* * *

#### Association Modes

This page describes the various modes of operation provided in NTPv4. Details about the configuration commands and options are given on the [Configuration Options](/archives/4.2.6-series/confopt) page. Details about the cryptographic authentication schemes are given on the [Authentication Options](/archives/4.2.6-series/authopt) page. Details about the automatic server discovery schemes are described on the [Automatic Server Discovery Schemes](/archives/4.2.6-series/manyopt) page. Additional information is available in the papers, reports, memoranda and briefings on the [NTP Project](http://www.eecis.udel.edu/~mills/ntp.html) page.

There are three types of associations in NTP: persistent, preemptable and ephemeral. Persistent associations are mobilized by a configuration command and never demobilized. Preemptable associations, which are new to NTPv4, are mobilized by a configuration command which includes the prempt option and are demobilized by a "better" server or by timeout, but only if the number of survivors exceeds the threshold set by the tos maxclock configuration command. Ephemeral associations are mobilized upon arrival of designated messages and demobilized by timeout.

Ordinarily, successful mobilization of ephemeral associations requires the server to be cryptographically authenticated to the client. This can be done using either symmetric key or Autokey public key cryptography, as described in the [Authentication Options](/archives/4.2.6-series/authopt) page.

There are three principal modes of operation in NTP: client/server, symmetric active/passive and broadcast/multicast. There are three automatic server discovery schemes in NTP: broadcast/multicast, manycast and pool described on the [Automatic Server Discovery Schemes](/archives/4.2.6-series/manyopt) page. In addition, the orphan mode and burst options described on this page can be used in appropriate cases.

Following is a summary of the operations in each mode. Note that reference to option applies to the commands described on the [Configuration Options](/archives/4.2.6-series/confopt) page. See that page for applicability and defaults.

* * *

#### Client/Server Mode

Client/server mode is the most common configuration in the Internet today. It operates in the classic remote-procedure-call (RPC) paradigm with stateless servers and stateful clients. In this mode a host sends a client (mode 3) request to the specified server and expects a server (mode 4) reply at some future time. In some contexts this would be described as a "pull" operation, in that the host pulls the time and related values from the server.

A host is configured in client mode using the <tt>server</tt> (sic) command and specifying the server DNS name or IPv4 or IPv6 address; the server requires no prior configuration. The <tt>iburst</tt> option described later on this page is recommended for clients, as this speeds up initial synchronization from several minutes to several seconds. The <tt>burst</tt> option described later on this page can be useful to reduce jitter on very noisy dial-up or ISDN network links.

Ordinarily, the program automatically manages the poll interval between the default minimum and maximum values. The <tt>minpoll</tt> and <tt>maxpoll</tt> options can be used to bracket the range. Unless noted otherwise, these options should not be used with reference clock drivers.

* * *

#### Symmetric Active/Passive Mode

Symmetric active/passive mode is intended for configurations were a clique of low-stratum peers operate as mutual backups for each other. Each peer operates with one or more primary reference sources, such as a radio clock, or a set of secondary (stratum, 2) servers known to be reliable and authentic. Should one of the peers lose all reference sources or simply cease operation, the other peers will automatically reconfigure so that time and related values can flow from the surviving peers to all hosts in the subnet. In some contexts this would be described as a "push-pull" operation, in that the peer either pulls or pushes the time and related values depending on the particular configuration.

In symmetric active mode a peer symmetric active (mode 1) message to a designated peer. If a matching configured symmetric active association is found, the designated peer returns a symmetric active message. If no matching association is found, the designated peer mobilizes a ephemeral symmetric passive association and returns a symmetric passive (mode 2) message. Since an intruder can impersonate a symmetric active peer and cause a spurious symmetric passive association to be mobilized, symmetric passive mode should always be cryptographically validated.

A peer is configured in symmetric active mode using the <tt>peer</tt> command and specifying the other peer DNS name or IPv4 or IPv6 address. The <tt>burst</tt> and <tt>iburst</tt> options should not be used in symmetric modes, as this can upset the intended symmetry of the protocol and result in spurious duplicate or dropped messages.

As symmetric modes are most often used as root servers for moderate to large subnets where rapid response is required, it is generally best to set the minimum and maximum poll intervals of each root server to the same value using the <tt>minpoll</tt> and <tt>maxpoll</tt> options.

* * *

#### Broadcast/Multicast Modes

NTP broadcast and multicast modes are intended for configurations involving one or a few servers and a possibly very large client population. Broadcast mode can be used with Ethernet, FDDI and WiFi spans interconnected by hubs or switches. Ordinarily, broadcast packets do not extend beyond a level-3 router. Where service is intended beyond a level-3 router, multicast mode can be used. Additional information is on the [Automatic NTP Configuration Options](/archives/4.2.6-series/manyopt) page.

* * *

#### Manycast Mode

Manycast mode is a automatic discovery and configuration paradigm new to NTPv4. It is intended as a means for a multicast client to troll the nearby network neighborhood to find cooperating manycast servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. The intended result is that each manycast client mobilizes ephemeral client associations with some number of the "best" of the nearby manycast servers, yet automatically reconfigures to sustain this number of servers should one or another fail. Additional information is on the [Automatic NTP Configuration Options](/archives/4.2.6-series/manyopt) page.

* * *

#### Orphan Mode

Sometimes an NTP subnet becomes isolated from all UTC sources such as local reference clocks or Internet time servers. In such cases it may be necessary that the subnet servers and clients remain synchronized to a common timescale, not necessarily the UTC timescale. Previously, this function was provided by the local clock driver to simulate a UTC source. A server with this driver could be used to synchronize other hosts in the subnet directly or indirectly.

There are many disadvantages using the local clock driver, primarily that the subnet is vulnerable to single-point failures and multiple server redundancy is not possible. Orphan mode is intended to replace the local clock driver. It provides a single simulated UTC source with multiple servers and provides seamless switching as servers fail and recover.

A common configuration for private networks includes one or more core servers operating at the lowest stratum. Good practice is to configure each of these servers as backup for the others using symmetric or broadcast modes. As long as at least one core server can reach a UTC source, the entire subnet can synchronize to it.

If no UTC sources are available to any core server, one of them can provide a simulated UTC source for all other hosts in the subnet. However, only one core server can simulate the UTC source and all direct dependents, called orphan children, must select the same one, called the orphan parent.

A host is enabled for orphan mode using the <tt>tos orphan _stratum_</tt> command, where <tt>_stratum_</tt> is some stratum less than 16 and greater than any anticipated stratum that might occur with configured Internet time servers. However, sufficient headroom should remain so every subnet host dependent on the orphan children has stratum less than 16. Where no associations for other servers or reference clocks are configured, the orphan stratum can be set to 1. These are the same considerations that guide the local clock driver stratum selection.

A orphan parent with no sources shows reference ID `LOOP` if operating at stratum 1 and 127.0.0.1 (Unix loopback address) otherwise. While ordinary NTP clients use a selection metric based on delay and dispersion, orphan children use a metric computed from the IP address of each core server. Each orphan child chooses the orphan parent as the root server with the smallest metric.

For orphan mode to work well, each core server with available sources should operate at the same stratum. All core servers and orphan children should include the same `tos` command in the configuration file. Each orphan child should include in the configuration file all root servers.

![gif](/archives/pic/peer.gif)

For example, consider the peer network configuration above, where two or more campus primary or secondary (stratum 2) servers are configured with reference clocks or public Internet primary servers and with each other using symmetric modes. With this configuration a server that loses all sources continues to discipline the system clock using the other servers as backup. Only the core servers and orphan children need to be enabled for orphan mode.

![gif](/archives/pic/broad.gif)

For broadcast networks each core server is configured in both broadcast server and broadcast client modes as shown above. Orphan children operate as broadcast clients of all core servers. As in peer networks, the core servers back up each other and only they and the orphan children need to be enabled for orphan mode.

In normal operation subnet hosts operate below stratum 5, so the subnet is automatically configured as described in the NTP specification. If all UTC sources are lost, all core servers become orphans and the orphan children will select the same root server to become the orphan parent.

* * *

#### Burst Options

There are two burst options where a single poll event triggers a burst of eight packets at 2-s intervals instead of the normal one packet. They should be used only with the <tt>server</tt> and <tt>pool</tt> commands, but not with reference clock drivers nor symmetric peers. The <tt>burst</tt> option sends a burst when the server is reachable, while the <tt>iburst</tt> option sends a burst when the server is unreachable. Each mode is independently of the other and both can be used at the same time. In either mode the client sends one packet, waits for the reply, then sends the remaining packets in the burst. This may be useful to allow a modem to complete a call.

In both modes received server packets update the clock filter, which selects the best (most accurate) time values. When the last packet in the burst is sent, the next received packet updates the system variables and adjusts the system clock as if only a single packet exchange had occurred.

The <tt>iburst</tt> option is useful where the system clock must be set quickly or when the network attachment requires an initial calling or training sequence. The burst is initiated only when the server first becomes reachable. This improves accuracy with intermittent connections typical of PPP and ISDN services. Outliers due to initial dial-up delays, etc., are avoided and the client sets the clock within a few seconds after the first received packet.

The <tt>burst</tt> option can be configured in cases of excessive network jitter or when the network attachment requires an initial calling or training sequence. The burst is initiated at each poll interval when the server is reachable. The number of packets in the burst is determined by the poll interval so that the average interval between packets is no less than 16. At a poll interval of 16 s, only one packet is sent in the burst; at 32 s, two packets are sent and so forth until at 128 s and above eight packets are sent.