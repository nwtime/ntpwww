---
title: "Automatic NTP Configuration Options"
type: archives
--- 


![gif](/archives/pic/alice51.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/%7emills/pictures.html)

Make sure who your friends are.

Last update: 20:55 UTC Tuesday, October 11, 2005

* * *

#### Table of Contents

*   [Broadcasting](/archives/4.2.4-series/manyopt/#broadcasting)
*   [Manycasting](/archives/4.2.4-series/manyopt/#manycasting)
*   [Orphan Mode](/archives/4.2.4-series/manyopt/#orphan-mode)
*   [Server Discovery Options](/archives/4.2.4-series/manyopt/#server-discovery-options)

* * *

#### Broadcasting

Broadcasting is the simplest way to provide automatic server discovery. It uses the multi-destination paradigm, where the subnet spanning tree is constructed automatically, either by the switches in an Ethernet LAN or the DVMRP or PIM protocols when spanning multiple networks.

A broadcast or multicast server is mobilized by the broadcast configuration command. The addresses can be either from the IPv4 broadcast/mulitcast address family or the IPv6 address family. Multiple broadcast server associations can be specified for a single host.

A host is enabled for broadcast reception using the <tt>broadcastclient</tt> configuration command, with or without the <tt>novolley</tt> option. Upon receiving the first message from a broadcast server, the client mobilizes an ephemeral client association and exchanges a volley of client/server messages in order to quickly authenticate the source, set the clock and measure the propagation delay, then reverts to listen-only mode. A multicast client is mobilized in the same way using the <tt>multicastclient</tt> configuration command and specified multicast group address.

Broadcasting can be used with either symmetric key or public key cryptography. Public key cryptography offers the best protection against compromised keys and is generally considered stronger. By default, either of these two means is required, but this can be overridden by the <tt>disable auth</tt> command.

In both broadcast and multicast client operations the client association is demobilized in case of error or timeout due to loss of server or connectivity.

#### Manycasting

Manycasting is a automatic discovery and configuration paradigm new to NTPv4\. It is intended as a means for a client to troll the nearby network neighborhood to find cooperating servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. The intended result is that each client mobilizes associations with a given number of the "best" nearby servers, yet automatically reconfigures to sustain this number of servers should one or another fail.

Note that the manycast paradigm does not coincide with the anycast paradigm described in RFC-1546, which is designed to find a single server from a clique of servers providing the same service. The manycast paradigm is designed to find a plurality of redundant servers satisfying defined optimality criteria.

Manycasting can be used with either symmetric key or public key cryptography. Public key cryptography offers the best protection against compromised keys and is generally considered stronger. By default, either of these two means is required, but this can be overridden by the <tt>disable auth</tt> command.

A manycast client association is configured using the <tt>manycastclient</tt> configuration command, which is similar to the <tt>server</tt> configuration command, but with a broadcast or multicast address. Depending on address family. The manycast client sends ordinary client mode messages, but with a broadcast address rather than a unicast address. It sends only if less than a given threshold of servers have been found and then only at the minimum feasible rate and minimum feasible time-to-live (TTL) hops. There can be as many manycast client associations as different broadcast addresses, each one serving as a template for a future unicast client/server association.

Manycast servers configured with the <tt>manycastserver</tt> command listen on the specified broadcast address for manycast client messages. If a manycast server is in scope of the current TTL and is itself synchronized to a valid source and operating at a stratum level equal to or lower than the manycast client, it replies to the manycast client message with an ordinary unicast server message.

The manycast client receiving this message mobilizes a preemptable client association according to the matching manycast client template, but only if cryptographically authenticated and the server stratum is less than or equal to the client stratum. The client runs the NTP mitigation algorithms, which act to demobilize all but a threshold number of associations according to stratum and synchronization distance. The surviving associations then continue in ordinary client/server mode.

If for some reason the number of available servers falls below the threshold, the manycast client resumes sending broadcast messages. The polling strategy is designed to reduce as much as possible the volume of broadcast messages and the effects of implosion due to near-simultaneous arrival of manycast server messages. The strategy is determined by the <tt>tos</tt> and <tt>ttl</tt> configuration commands described below.

It is possible and frequently useful to configure a host as both manycast client and manycast server. A number of hosts configured this way and sharing a common group address will automatically organize themselves in an optimum configuration based on stratum and synchronization distance.

For example, consider an NTP subnet of two primary servers and several secondary servers and a number of dependent clients. With twoAll servers and clients have identical configuration files including both <tt>multicastclient</tt> and <tt>multicastserver</tt> commands using, for instance, multicast group address 239.1.1.1\. Each primary server configuration file must include commands for the primary reference source such as a GPS receiver.

The remaining configuration files for all secondary servers and clients have the same contents, except for the <tt>tos</tt> command, which is specific for each stratum level. For stratum 1 and stratum 2 servers, that command is not necessary. For stratum 3 and above servers the <tt>tos floor</tt> value is set to the intended stratum number. Thus, all stratum 3 configuration files use <tt>tos floor 3</tt>, all stratum 4 files use <tt>tos floor 4</tt> and so forth.

Once operations have stabilized, the primary servers will find the primary reference source and each other, since they both operate at the same stratum (1), but not with any secondary server or client, since these operate at a higher stratum. The secondary servers will find the servers at the same stratum level. If one of the primary servers loses its GPS receiver, it will continue to operate as a client and other clients will time out the corresponding association and re-associate accordingly.

#### Orphan Mode

Sometimes it is necessary to operate an NTP subnet in isolation, because a local reference clock is unavailable or connectivity to the Internet is not provided. In such cases it may be necessary that the subnet servers and clients remain synchronized to a common timescale, not necessarily the UTC timescale. Previously, this function was provided by the local clock driver, which could be configured for a server that could be reached, directly or indirectly from all other servers and clients in the subnet.

There are many disadvantages using the local clock driver: multiple source redundancy is not possible and the subnet is vulnerable to single-point failures. Orphan mode is intended to replace the need for the local clock driver. It operates in subnet configurations in all modes, including broadcast, and multiple servers and clients and handles seamless switching as primary sources fail and recover.

A server or client is enabled for orphan mode using the <tt>tos orphan _stratum_</tt> command, where <tt>_stratum_</tt> is some stratum less than 16 and greater than any anticipated stratum that might occur with ordinary Internet servers. This is the same consideration that guides the local clock driver stratum.

As long as the stratum of any orphan is less than the orphan stratum, the servers and clients operate in the normal way. However, if the stratum equals or exceeds this stratum, the server or client is considered an orphan. If under these conditions a host has no sources of the same or lower stratum, it is designated an orphan parent; otherwise, it is considered an orphan child. Orphan parents show offset zero, root delay zero and reference ID 127.0.0.1, which of course is the Unix loopback address. Orphan children show the mitigated offset of their servers, root delay randomized over a moderate range and reference ID of their system peer. An important distinction is that the entire subnet operates at the same orphan stratum and that the order of preference is the root delay, not the stratum and root distance as usual.

For the most flexible and reliable operation, all servers and clients in the subnet should include the <tt>orphan</tt> command in the configuration file and with the same orphan stratum. This provides mutual redundancy and diversity for all NTP modes of operation, including broadcast.

For example, consider the case where several campus secondary (stratum 2) servers are configured for public Internet primary servers and with each other using symmetric modes. These servers provide synchronization with a number of department servers using broadcast mode, where each of these servers is configured as both a broadcast server and broadcast client. Individual workstations on the department LAN are configured as broadcast clients only. All servers (not necessarily the clients) have the <tt>orphan 5</tt> command, for example.

In normal operation all servers and clients operate below stratum 5, so operate with the subnet configuration determined by stratum and root distance. If all sources are lost at any stratum level, the server or client continues operation as orphan parent. However, if sources at the orphan stratum are found, the host synchronizes to the source with lowest root delay. Since orphan root delay is determined randomly at startup, loops are avoided, even in broadcast modes where multiple servers are available.

#### Server Discovery Options

<dt><tt>tos [ ceiling _ceiling_ | cohort {0 | 1} | floor _floor_ | orphan _orphan_ | maxdistance _maxdistance_ | minclock _minclock_ | minsane _minsane_ ]</tt></dt>

This command affects the clock selection and clustering algorithms. It can be used to select the quality and quantity of peers used to synchronize the system clock and is most useful in manycast mode. The variables operate as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>beacon _beacon_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The manycast server sends packets at intervals of 64 s if less than _<tt>maxclock</tt>_ servers are available. Otherwise, it sends packets at the _<tt>beacon</tt>_ interval in seconds. The default is 3600 s.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>ceiling _ceiling_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Servers with stratum at or above _ceiling_ will be discarded if there are at least _<tt>minclock</tt>_ peers remaining. This value defaults to 15, but can be changed to any number from 1 to 15.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>cohort { 0 | 1 }</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This is a binary flag which enables (0) or disables (1) manycast server replies to manycast clients with the same stratum level. This is useful to reduce implosions where large numbers of clients with the same stratum level are present. The default is to enable these replies.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>floor _floor_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Peers with strata below _floor_ will be discarded if there are at least _minclock_ peers remaining. This value defaults to 1, but can be changed to any number from 1 to 15.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>orphan _stratum_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;If <tt>_stratum_</tt> is set at some value less than 16 a special orphan mode is enterred when no outside source of synchronization is available. To use orphan mode a number of participants are identically configured both as broadcast client and as broadcast server. One or more participants are configured to use an outside source, either a reference clock or another Internet server. When the source or sources fail, the system stratum is set at <tt>_stratum_</tt> and a leader is elected to serve as the reference source. When an outside source of synchronization is again available, the orphan mode is disabled.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>mindist _mindistance_</tt>

The slection algorithm normally pads each intersection a minimum of one millisecond to avoid needless classification. In some cases, such as reference clocks with high jitter and a PPS signal, it is useful to increase the padding. This command can be used for that purpose. As a general rule, set the mindistance to the maximum expected offset plus the maxiumum expected jitter, in seconds.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>maxdist _maxdistance_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The selection algorithm accumulates a number of packets before setting the clock in order to use the best data available. The number is determined by the synchronization distance for each association and a limit called the distance threshold. The synchronization distance starts at 16, then drops by a factor of about two as each packet is received. The default distance threshold is 1.0, which usually results in four packets. Setting maxdistance to some value between 1 and 16 can be used to change the number of packets required. For instance, setting it to 16 will set the clock on the first packet received; howver, setting it to this value essentially disables the mitigation and grooming algorithms.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minclock _minclock_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The clustering algorithm repeatedly casts out outlyer associations until no more than _minclock_ associations remain. This value defaults to 3, but can be changed to any number from 1 to the number of configured sources.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minsane _minsane_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This is the minimum number of candidates available to the clock selection algorithm in order to produce one or more truechimers for the clustering algorithm. If fewer than this number are available, the clock is undisciplined and allowed to run free. The default is 1 for legacy purposes. However, according to principles of Byzantine agreement, _minsane_ should be at least 4 in order to detect and discard a single falseticker.

<dt><tt>ttl _hop_ ...</tt></dt>

This command specifies a list of TTL values in increasing order. up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.

