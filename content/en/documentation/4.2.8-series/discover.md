---
title: "Automatic Server Discovery Schemes"
description: "NTPv4 provides three automatic server discovery schemes: broadcast/multicast, many cast, and server pool. The broadcast/multicast and many cast schemes are native to IPv4 and IPv6 while the server pool scheme uses DNS to resolve NTP server addresses."
type: archives
aliases:
    - /current-stable/discover/
---


![gif](/documentation/pic/alice51.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Make sure who your friends are.

* * *

#### Table of Contents

*   [Introduction](/documentation/4.2.8-series/discover/#introduction)
*   [Association Management](/documentation/4.2.8-series/discover/#association-management)
*   [Broadcast/Multicast Scheme](/documentation/4.2.8-series/discover/#broadcastmulticast-scheme)
*   [Manycast Scheme](/documentation/4.2.8-series/discover/#manycast-scheme)
*   [Server Pool Scheme](/documentation/4.2.8-series/discover/#server-pool-scheme)

* * *

#### Introduction

This page describes the automatic server discovery schemes provided in NTPv4. There are three automatic server discovery schemes: broadcast/multicast, many cast, and server pool, which are described on this page. The broadcast/multicast and many cast schemes utilize the ubiquitous broadcast or one-to-many paradigm native to IPv4 and IPv6. The server pool scheme uses DNS to resolve addresses of multiple volunteer servers scattered throughout the world.

All three schemes work in much the same way and might be described as _grab-n'-prune._ Through one means or another they grab a number of associations either directly or indirectly from the configuration file, order them from best to worst according to the NTP mitigation algorithms, and prune the surplus associations.

* * *

#### Association Management

All schemes use an iterated process to discover new preemptable client associations as long as the total number of client associations is less than the <code>maxclock</code> option of the <code>tos</code> command. The <code>maxclock</code> default is 10, but it should be changed in typical configuration to some lower number, usually two greater than the <code>minclock</code> option of the same command.

All schemes use a stratum filter to select just those servers with stratum considered useful. This can avoid large numbers of clients ganging up on a small number of low-stratum servers and avoid servers below or above specified stratum levels. By default, servers of all strata are acceptable; however, the <code>tos</code> command can be used to restrict the acceptable range from the <code>floor</code> option, inclusive, to the <code>ceiling</code> option, exclusive. Potential servers operating at the same stratum as the client will be avoided, unless the <code>cohort</code> option is present. Additional filters can be supplied using the methods described on the [Authentication Support](/documentation/4.2.8-series/authentic/) page.

The pruning process uses a set of unreach counters, one for each association created by the configuration or discovery processes. At each poll interval, the counter is increased by one. If an acceptable packet arrives for a persistent (configured) or ephemeral (broadcast/multicast) association, the counter is set to zero. If an acceptable packet arrives for a preemptable (manycast, pool) association and survives the selection and clustering algorithms, the counter is set to zero. If the counter reaches an arbitrary threshold of 10, the association becomes a candidate for pruning.

The pruning algorithm is very simple. If an ephemeral or preemptable association becomes a candidate for pruning, it is immediately demobilized. If a persistent association becomes a candidate for pruning, it is not demobilized, but its poll interval is set at the maximum. The pruning algorithm design avoids needless discovery/prune cycles for associations that wander in and out of the survivor list, but otherwise have similar characteristics.

Following is a summary of each scheme. Note that reference to option applies to the commands described on the [Configuration Options](/documentation/4.2.8-series/confopt/) page. See that page for applicability and defaults.

* * *

#### Broadcast/Multicast Scheme

A broadcast server generates messages continuously at intervals by default 64 s and time-to-live by default 127. These defaults can be overridden by the <code>minpoll</code> and <code>ttl</code> options, respectively. Not all kernels support the <code>ttl</code> option. A broadcast client responds to the first message received by waiting a randomized interval to avoid implosion at the server. It then polls the server in client/server mode using the <code>iburst</code> option in order to quickly authenticate the server, calibrate the propagation delay and set the client clock. This normally results in a volley of six client/server exchanges at 2-s intervals during which both the synchronization and cryptographic protocols run concurrently.

Following the volley, the server continues in listen-only mode and sends no further messages. If for some reason the broadcast server does not respond to these messages, the client will cease transmission and continue in listen-only mode with a default propagation delay. The volley can be avoided by using the <code>broadcastdelay</code> command with nonzero argument.

A server is configured in broadcast mode using the <code>broadcast</code> command and specifying the broadcast address of a local interface. If two or more local interfaces are installed with different broadcast addresses, a <code>broadcast</code> command is needed for each address. This provides a way to limit exposure in a firewall, for example. A broadcast client is configured using the <code>broadcastclient</code> command.

NTP multicast mode can be used to extend the scope using IPv4 multicast or IPv6 broadcast with defined span. The IANA has assigned IPv4 multicast address 224.0.1.1 and IPv6 address FF05::101 (site local) to NTP, but these addresses should be used only where the multicast span can be reliably constrained to protect neighbor networks. In general, administratively scoped IPv4 group addresses should be used, as described in [RFC 2365](https://www.rfc-editor.org/rfc/rfc2365.html), or GLOP group addresses, as described in [RFC 2770](https://www.rfc-editor.org/rfc/rfc2770.html).

A multicast server is configured using the <code>broadcast</code> command, but specifying a multicast address instead of a broadcast address. A multicast client is configured using the <code>multicastclient</code> command specifying a list of one or more multicast addresses. Note that there is a subtle distinction between the IPv4 and IPv6 address families. The IPv4 broadcast or mulitcast mode is determined by the IPv4 class. For IPv6 the same distinction can be made using the link-local prefix FF02 for each interface and site-local prefix FF05 for all interfaces.

It is possible and frequently useful to configure a host as both broadcast client and broadcast server. A number of hosts configured this way and sharing a common broadcast address will automatically organize themselves in an optimum configuration based on stratum and synchronization distance.

Since an intruder can impersonate a broadcast server and inject false time values, broadcast mode should always be cryptographically authenticated. By default, a broadcast association will not be mobilized unless cryptographically authenticated. If necessary, the <code>auth</code> option of the <code>disable</code> command will disable this feature. The feature can be selectively enabled using the <code>notrust</code> option of the <code>restrict</code> command.

With symmetric key cryptography each broadcast server can use the same or different keys. In one scenario on a broadcast LAN, a set of broadcast clients and servers share the same key along with another set that share a different key. Only the clients with matching key will respond to a server broadcast. Further information is on the [Authentication Support](/documentation/4.2.8-series/authentic/) page.

Public key cryptography can be used with some restrictions. If multiple servers belonging to different secure groups share the same broadcast LAN, the clients on that LAN must have the client keys for all of them. This scenario is illustrated in the example on the [Autokey Public Key Authentication](/documentation/4.2.8-series/autokey/) page.

* * *

#### Manycast Scheme

Manycast is an automatic server discovery and configuration paradigm new to NTPv4. It is intended as a means for a client to troll the nearby network neighborhood to find cooperating servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. It uses the grab-n'-drop paradigm with the additional feature that active means are used to grab additional servers should the number of associations fall below the <code>maxclock</code> option of the <code>tos</code> command.

The manycast paradigm is not the anycast paradigm described in [RFC 1546](https://www.rfc-editor.org/rfc/rfc1546.html), which is designed to find a single server from a clique of servers providing the same service. The manycast paradigm is designed to find a plurality of redundant servers satisfying defined optimality criteria.

A manycast client is configured using the <code>manycastclient</code> configuration command, which is similar to the <code>server</code> configuration command. It sends ordinary client mode messages, but with a broadcast address rather than a unicast address and sends only if less than <code>maxclock</code> associations remain and then only at the minimum feasible rate and minimum feasible time-to-live (TTL) hops. The polling strategy is designed to reduce as much as possible the volume of broadcast messages and the effects of implosion due to near-simultaneous arrival of manycast server messages. There can be as many manycast client associations as different addresses, each one serving as a template for future unicast client/server associations.

A manycast server is configured using the <code>manycastserver</code> command, which listens on the specified broadcast address for manycast client messages. If a manycast server is in scope of the current TTL and is itself synchronized to a valid source and operating at a stratum level equal to or lower than the manycast client, it replies with an ordinary unicast server message.

The manycast client receiving this message mobilizes a preemptable client association according to the matching manycast client template. This requires the server to be cryptographically authenticated and the server stratum to be less than or equal to the client stratum.

It is possible and frequently useful to configure a host as both manycast client and manycast server. A number of hosts configured this way and sharing a common multicast group address will automatically organize themselves in an optimum configuration based on stratum and synchronization distance.

The use of cryptograpic authentication is always a good idea in any server discovery scheme. Both symmetric key and public key cryptography can be used in the same scenarios as described above for the broadast/multicast scheme.

#### Server Pool Scheme

The idea of targeting servers on a random basis to distribute and balance the load is not a new one; however, the NTP pool scheme puts this on steroids. At present, several thousand operators around the globe have volunteered their servers for public access. In general, NTP is a lightweight service and servers used for other purposes don't mind an additional small load. The trick is to randomize over the population and minimize the load on any one server while retaining the advantages of multiple servers using the NTP mitigation algorithms.

To support this service, custom DNS software is used by pool.ntp.org and its subdomains to discover a random selection of participating servers in response to a DNS query. The client receiving this list mobilizes some or all of them, similar to the manycast discovery scheme, and prunes the excess. Unlike <code>manycastclient</code>, cryptographic authentication is not required. The pool scheme solicits a single server at a time, compared to <code>manycastclient</code> which solicits all servers within a multicast TTL range simultaneously. Otherwise, the pool server discovery scheme operates as manycast does.

The pool scheme is configured using one or more <code>pool</code> commands with DNS names indicating the pool from which to draw. The <code>pool</code> command can be used more than once; duplicate servers are detected and discarded. In principle, it is possible to use a configuration file containing a single line <code>pool pool.ntp.org</code>. The [NTP Pool Project](https://www.ntppool.org/en/use.html) offers instructions on using the pool with the <code>server</code> command, which is suboptimal but works with older versions of <code>ntpd</code> predating the <code>pool</code> command. With recent <code>ntpd</code>, consider replacing the multiple <code>server</code> commands in their example with a single <code>pool</code> command.
