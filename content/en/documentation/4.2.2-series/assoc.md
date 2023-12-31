---
title: "Association Management"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/alice51.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Make sure who your friends are.

* * *

#### Table of Contents

*   [Association Modes](/documentation/4.2.2-series/assoc/#association-modes)
*   [Client/Server Mode](/documentation/4.2.2-series/assoc/#clientserver-mode)
*   [Symmetric Active/Passive Mode](/documentation/4.2.2-series/assoc/#symmetric-activepassive-mode)
*   [Broadcast/Multicast Modes](/documentation/4.2.2-series/assoc/#broadcastmulticast-modes)
*   [Multicasting](/documentation/4.2.2-series/assoc/#multicasting)
*   [Manycasting](/documentation/4.2.2-series/assoc/#manycasting)
*   [Burst Modes](/documentation/4.2.2-series/assoc/#burst-modes)

* * *

#### Association Modes

NTP Version 4 (NTPv4) incorporates new features and refinements to the NTP Version 3 (NTPv3) algorithms; however, it continues the tradition of backwards compatibility with older versions. A number of new operating modes for automatic server discovery and improved accuracy in occasionally connected networks are provided. Following is an overview of the new features; additional information is available on the [Configuration Options](/documentation/4.2.2-series/confopt/) and [Authentication Options](/documentation/4.2.2-series/authopt/) pages and in the papers, reports, memoranda and briefings in the [Reference Library](/reflib/).

There are two types of associations: persistent associations, which result from configuration file commands, and ephemeral associations, which result from protocol operations described below. A persistent association is never demobilized, although it may become dormant when the associated server becomes unreachable. An ephemeral association is mobilized when a message arrives from a server; for instance, a symmetric passive association is mobilized upon arrival of a symmetric active message. A broadcast client association is mobilized upon arrival of a broadcast server message, while a Manycast client association is mobilized upon arrival of a Manycast server message.

Ordinarily, successful mobilization of an ephemeral association requires the server to be cryptographically authenticated to the dependent client. This can be done using either symmetric-key or public-key cryptography, as described in the [Authentication Options](/documentation/4.2.2-series/authopt/) page. The cryptographic means insure an unbroken chain of trust between the dependent client and the primary servers at the root of the synchronization subnet. We call this chain the _provenance_ of the client and define new vocabulary as to proventicate a client or provide proventic credentials. Once mobilized, ephemeral associations are demobilized when either (a) the server becomes unreachable or (b) the server refreshes the key media without notifying the client.

There are three principal modes of operation: client/server, symmetric active/passive and broadcast. In addition, there are two modes using IP multicast support: multicast and manycast. These modes are selected based on the scope of service, intended flow of time and proventic values and means of configuration. Following is a summary of the operations in each mode.

* * *

#### Client/Server Mode

Client/server mode is probably the most common configuration in the Internet today. It operates in the classic remote-procedure-call (RPC) paradigm with stateless servers. In this mode a client sends a request to the server and expects a reply at some future time. In some contexts this would be described as a "pull" operation, in that the client pulls the time and proventic values from the server. A client is configured in client mode using the <code>server</code> (sic) command and specifying the server IPv4 or IPv6 DNS name or address; the server requires no prior configuration. The original NTPv3 authentication scheme is applicable in this mode, as well as the new NTPv4 Autokey proventication scheme. In addition, two burst modes described below can be used in appropriate cases.

* * *

#### Symmetric Active/Passive Mode

Symmetric active/passive mode is intended for configurations were a clique of low-stratum peers operate as mutual backups for each other. Each peer operates with one or more primary reference sources, such as a radio clock, or a subset of secondary servers known to be reliable and proventicated. Should one of the peers lose all reference sources or simply cease operation, the other peers will automatically reconfigure so that time and proventication values can flow from the surviving peers to all the others in the clique. In some contexts this would be described as a "push-pull" operation, in that the peer either pulls or pushes the time and proventic values depending on the particular configuration.

Symmetric peers operate with their sources in some NTP mode and with each other in symmetric mode. A peer is configured in symmetric active mode using the <code>peer</code> command and specifying the other peer IPv4 or IPv6 DNS name or address. The other peer can also be configured in symmetric active mode in a similar way. However, if the other peer is not specifically configured in this way, a symmetric passive association is mobilized upon arrival of a symmetric active message. Since an intruder can impersonate a symmetric active peer and inject false time values, symmetric mode should always be cryptographically validated. The original NTPv3 authentication scheme is applicable in this mode, as well as the new NTPv4 Autokey proventication scheme.

* * *

#### Broadcast/Multicast Modes

IPv4 broadcast mode in both NTPv3 and NTPv4 is limited to directly connected subnets such as Ethernets which support broadcast technology. Ordinarily, this technology does not operate beyond the first hop router or gateway. In IPv6 and where service is intended beyond the local subnet, IP multicasting can be used where supported by the operating system and the routers support the Internet Group Management Protocol (IGMP). Most current kernels and available routers do support IP multicast technology, although service providers are sometimes reluctant to deploy it.

IPv4 broadcast mode is intended for configurations involving one or a few servers and a possibly very large client population on the same subnet. A broadcast server is configured using the <code>broadcast</code> command and a IPv4 local subnet broadcast address. A broadcast client is configured using the <code>broadcastclient</code> command, in which case it responds to broadcast messages received on any interface. Since an intruder can impersonate a broadcast server and inject false time values, this mode should always be cryptographically validated. The original NTPv3 authentication scheme is applicable in this mode, as well as the new NTPv4 Autokey proventication scheme.

The server generates broadcast messages continuously at intervals specified by the <code>minpoll</code> keyword and with a time-to-live span specified by the <code>ttl</code> keyword. A broadcast client responds to the first message received by waiting a short interval to avoid implosion at the server. Then, the client polls the server in burst mode in order to quickly set the host clock and validate the source. This normally results in a volley of eight client/server cycles at 2-s intervals during which both the synchronization and cryptographic protocols run concurrently. Following the volley, the client computes the offset between the apparent broadcast time and the (unicast) client time. This offset is used to compensate for the propagation time between the broadcast server and client. Once the offset is computed, the server continues as before and the client sends no further messages. If for some reason the broadcast server does not respond to client messages, the client will time out the volley and continue in listen-only mode with a default propagation delay.

* * *

#### Multicasting

Multicasting can be used to extend the scope of a timekeeping subnet in two ways: multicasting and manycasting. A general discussion of IP multicast technology is beyond the scope of this page. In simple terms a host or router sending to a IPv4 or IPv6 multicast group address expects all hosts or routers listening on this address to receive the message. There is no intrinsic limit on the number of senders or receivers and senders can be receivers and vice versa. The IANA has assigned multicast group address IPv4 224.0.1.1 and IPv6 FF05::101 (site local) to NTP, but these addresses should be used only where the multicast span can be reliably constrained to protect neighbor networks. In general, administratively scoped IPv4 group addresses should be used, as described in RFC-2365, or GLOP group addresses, as described in RFC-2770.

A multicast server is configured using the <code>broadcast</code> command, but with a multicast group address instead of a broadcast address. A multicast client is configured using the <code>multicastclient</code> command with a multicast group address. However, there is a subtle difference between IPv4 broadcasting and multicasting. IPv4 broadcasting is specific to each interface and local subnet address. If more than one interface is attached to a machine, a separate <code>broadcast</code> command applies to each one separately. This provides a way to limit exposure in a firewall, for example. For IPv6 the same distinction can be made using link-local prefix FF02 for each interface and site-local FF05 for all interfacesl.

IP multicasting is a different paradigm. By design, multicast messages travel from the sender via a shortest-path or shared tree to the receivers, which may require these messages emit from one or all interfaces, but carry a common source address. However, it is possible to configure multiple multicast group addresses using multiple <code>broadcast</code> or <code>multicastclient</code> commands. Other than these particulars, multicast messages are processed just like broadcast messages. Note that the calibration feature in broadcast mode is extremely important, since IP multicast messages can travel far different paths through the IP routing fabric than ordinary IP unicast messages.

* * *

#### Manycasting

Manycasting is a automatic discovery and configuration paradigm new to NTPv4. It is intended as a means for a multicast client to troll the nearby network neighborhood to find cooperating manycast servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. The intended result is that each manycast client mobilizes client associations with some number of the "best" of the nearby anycast servers, yet automatically reconfigures to sustain this number of servers should one or another fail. Additional information is on the [Automatic NTP Configuration Options](/documentation/4.2.2-series/manyopt/) page.

* * *

#### Burst Modes

There are two burst modes where a single poll event triggers a burst of eight packets at 2-s intervals instead of the usual one. The <code>burst</code> mode sends a burst when the server is reachable, while the <code>iburst</code> mode sends a burst when the server is unreachable. Each mode is independently of the other and both can be used if necessary. The <code>calldelay</code> command can be used to increase the interval between the first and second packets in the burst in order to allow a modem to complete a call. Received server packets update the clock filter, which selects the best (most accurate) time values. When the last packet in the burst is sent, the next received packet updates the system variables and sets the system clock in the usual manner, as if only a single client/server cycle had occurred. The result is not only a rapid and reliable setting of the system clock, but a considerable reduction in network jitter.

The <code>iburst</code> keyword is used where it is important to set the clock quickly when an association is first mobilized or first becomes reachable or when the network attachment requires an initial calling or training procedure. The burst is initiated only when the server first becomes reachable and results in good accuracy with intermittent connections typical of PPP and ISDN services. Outlyers due to initial dial-up delays, etc., are avoided and the client sets the clock within a few seconds after the first message.

The <code>burst</code> keyword can be configured in cases of excessive network jitter or when the network attachment requires an initial calling or training procedure. The burst is initiated at each poll interval when the server is reachable. The burst does produce additional network overhead and can cause trouble if used indiscriminately. It should only be used where the poll interval is expected to settle to values at or above 1024 s.

