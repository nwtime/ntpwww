---
title: "Association Management"
type: archives
---

![gif](/archives/pic/alice51.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

Make sure who your friends are.

* * *

#### Table of Contents

*   [Association Modes](/archives/4.1.0/assoc/#association-modes)
*   [Client/Server Mode](/archives/4.1.0/assoc/#clientserver-mode)
*   [Symmetric Active/Passive Mode](/archives/4.1.0/assoc/#symmetric-activepassive-mode)
*   [Broadcast Mode](/archives/4.1.0/assoc/#broadcast-mode)
*   [IP Multicast Support](/archives/4.1.0/assoc/#ip-multicast-support)
*   [Multicasting](/archives/4.1.0/assoc/#multicasting)
*   [Manycasting](/archives/4.1.0/assoc/#manycasting)
*   [Burst Modes](/archives/4.1.0/assoc/#burst-modes)

* * *

#### Association Modes

NTP Version 4 (NTPv4) incorporates new features and refinements to the NTP Version 3 (NTPv3) algorithms; however, it continues the tradition of backwards compatibility with older versions. A number of new operating modes for automatic server discovery and improved accuracy in occasionally connected networks are provided. Following is an overview of the new features; additional information is available on the [Configuration Options](/archives/4.1.0/confopt/) and [Authentication Options](/archives/4.1.0/authopt/) pages and in the papers, reports, memoranda and briefings in the [Reference Library](/reflib/).

There are two types of associations: persistent associations, which result from configuration file commands, and ephemeral associations, which result from protocol operations described below. A persistent association is never demobilized, although it may become dormant when the associated server becomes unreachable. An ephemeral association is mobilized when a message arrives from a server; for instance, a symmetric passive association is mobilized upon arrival of a symmetric active message. A broadcast client association is mobilized upon arrival of a broadcast server message, while a manycast client association is mobilized upon arrival of a manycast server message.

Ordinarily, successful mobilization of an ephemeral association requires the server to be cryptographically authenticated to the dependent client. This can be done using either symmetric-key or public-key cryptography, as described in the [Authentication Options](/archives/4.1.0/authopt/) page. The cryptographic means insure an unbroken chain of trust between the dependent client and the primary servers at the root of the synchronization subnet. We call this chain the _provenance_ of the client and define new vocabulary as to proventicate a client or provide proventic credentials. Once mobilized, ephemeral associations are demobilized when either (a) the server becomes unreachable or (b) the server refreshes the key media without notifying the client.

There are three principal modes of operation: client/server, symmetric active/passive and broadcast. In addition, there are two modes using IP multicast support: multicast and manycast. These modes are selected based on the scope of service, intended flow of time and proventic values and means of configuration. Following is a summary of the operations in each mode.

* * *

#### Client/Server Mode

Client/server mode is probably the most common configuration in the Internet today. It operates in the classic remote-procedure-call (RPC) paradigm with stateless servers. In this mode a client sends a request to the server and expects a reply at some future time. In some contexts this would be described as a "pull" operation, in that the client pulls the time and proventic values from the server. A client is configured in client mode using the <code>server</code> (sic) command and specifying the server IPv4 or IPv6 DNS name or address; the server requires no prior configuration. The original NTPv3 authentication scheme is applicable in this mode, as well as the new NTPv4 Autokey proventication scheme. In addition, two burst modes described below can be used in appropriate cases.

* * *

#### Symmetric Active/Passive Mode

Symmetric active/passive mode is intended for configurations where a clique of low-stratum peers operate as mutual backups for each other. Each peer operates with one or more primary reference sources, such as a radio clock, or a subset of secondary servers known to be reliable and proventicated. Should one of the peers lose all reference sources or simply cease operation, the other peers will automatically reconfigure so that time and proventication values can flow from the surviving peers to all the others in the clique. In some contexts this would be described as a "push-pull" operation, in that the peer either pulls or pushes the time and proventic values depending on the particular configuration.

Symmetric peers operate with their sources in some NTP mode and with each other in symmetric mode. A peer is configured in symmetric active mode using the <code>peer</code> command and specifying the other peer DNS name or address. The other peer can also be configured in symmetric active mode in a similar way. However, if the other peer is not specifically configured in this way, a symmetric passive association is mobilized upon arrival of a symmetric active message. Since an intruder can impersonate a symmetric active peer and inject false time values, symmetric mode should always be cryptographically validated. The original NTPv3 authentication scheme is applicable in this mode, as well as the new NTPv4 Autokey proventication scheme.

* * *

#### Broadcast Mode

Broadcast mode is intended for configurations involving one or a few servers and a possibly very large client population. A broadcast server is configured using the <code>broadcast</code> command and a local subnet address. A broadcast client is configured using the <code>broadcastclient</code> command, in which case it responds to broadcast messages received on any interface. Since an intruder can impersonate a broadcast server and inject false time values, this mode should always be cryptographically validated. The original NTPv3 authentication scheme is applicable in this mode, as well as the new NTPv4 Autokey proventication scheme. 

The server generates broadcast messages continuously at intervals specified by the <code>minpoll</code> keyword and with a time-to-live span specified by the <code>ttl</code> keyword. A NTPv4 broadcast client responds to the first proventicated message received by waiting a short interval randomized over the <code>minpoll</code> interval, in order to avoid implosion at the server. Then, the client polls the server in burst mode in order to reliably set the host clock and validate the source. This normally results in a volley of eight client/server cycles over a 30-s interval during which both the synchronization and cryptographic protocols run concurrently. When the next broadcast message is received after the volley, the client computes the offset between the apparent broadcast time and the (unicast) client time. This offset is used to compensate for the propagation time between the broadcast server and client. Once the offset is computed, the server continues as before and the client sends no further messages. 

* * *

#### IP Multicast Support

Broadcast mode in both NTPv3 and NTPv4 is limited to directly connected subnets such as Ethernets which support broadcast technology. Ordinarily, this technology does not operate beyond the first hop router or gateway. Where service is intended beyond the local subnet, IP multicasting can be used where supported by the operating system and the routers support the Internet Group Management Protocol (IGMP). Most current kernels and available routers do support IP multicast technology, although service providers are sometimes reluctant to deploy it.

A general discussion of IP multicast technology is beyond the scope here. In simple terms a host or router sending to a IP multicast group (class D) address expects all hosts or routers listening on this address to receive the message. There is no intrinsic limit on the number of senders or receivers and senders can be receivers and vice versa. The IANA has assigned multicast group address 224.0.1.1 to NTP, but this address should be used only where the multicast span can be reliably constrained to protect neighbor networks. In general, administratively scoped group addresses should be used, as described in RFC-2365, or GLOP group addresses, as described in RFC-2770. 

* * *

#### Multicasting

IP multicasting can be used to extend the scope of a timekeeping subnet in two ways: multicasting and manycasting. A multicast client is configured using the <code>broadcast</code> command, but with a multicast group (class D) address instead of a local subnet broadcast address. However, there is a subtle difference between broadcasting and multicasting. Broadcasting is specific to each interface and local subnet address. If more than one interface is attached to a machine, a separate <code>broadcast</code> command applies to each one separately. This provides a way to limit exposure in a firewall, for example. 

IP multicasting is a different paradigm. A multicast message has the same format as a broadcast message and is configured with the same <code>broadcast</code> command, but with a multicast group address instead of a local subnet address. By design, multicast messages travel from the sender via a shortest-path or shared tree to the receivers, which may require these messages emit from one or all interfaces, but carry a common source address. However, it is possible to configure multiple multicast group addresses using multiple <code>broadcast</code> commands. Other than these particulars, multicast messages are processed just like broadcast messages. Note that the calibration feature in broadcast mode is extremely important, since IP multicast messages can travel far different paths through the IP routing fabric than ordinary IP unicast messages. 

* * *

#### Manycasting

Manycasting is a automatic discovery and configuration paradigm new to NTPv4. It is intended as a means for a multicast client to troll the nearby network neighborhood to find cooperating manycast servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. The intended result is that each manycast client mobilizes client associations with the "best" three of the available manycast servers, yet automatically reconfigures to sustain this number of servers should one or another fail.

Note that the manycasting paradigm does not coincide with the anycasting paradigm described in RFC-1546, which is designed to find a single server from a clique of servers providing the same service. The manycasting paradigm is designed to find a plurality of redundant servers, in this case willing NTP servers.

A persistent manycast client association is configured using the <code>server</code> command, but with a multicast (class D) group address instead of an ordinary IP (class A, B, C) address. It sends client mode messages to this address at the maximum feasible poll interval and minimum feasible time-to-live hops, depending on how many servers have already been found. There can be as many manycast client associations as different group addresses, each one serving as a template for a future ephemeral client/server mode association.

Manycast servers configured with the <code>manycastserver</code> command listen on the specified group address for manycast client messages. Note the distinction between manycast client, which is configured with a <code>server</code> command, and manycast server, which is configured with a <code>manycastserver</code> command. If a manycast server is in range of the current time-to-live and is itself synchronized to a valid source and operating at a stratum level equal to or lower than the manycast client, it replies to the manycast client message with an ordinary server mode message.

The manycast client receiving this message mobilizes an ephemeral client association as in ordinary client/server mode according to the matching manycast client template. Then, the client polls the server at its unicast address in burst mode in order to reliably set the host clock and validate the source. This normally results in a volley of eight client/server cycles over a 30-s interval during which both the synchronization and cryptographic protocols run concurrently. Following the volley, the client runs the NTP intersection and clustering algorithms, which act to discard all but the best three associations. The surviving associations then continue in ordinary client/server mode.

The manycast client polling program is designed to reduce as much as possible the volume of messages and the effects of implosion due to near-simultaneous arrival of manycast server messages. The program uses a poll interval eight times the system poll interval, which starts out at the <code>minpoll</code> value and under normal circumstances increases gradually to the <code>maxpolll</code> value. Initially, the time-to-live is set at one hop. At each retransmission the time-to-live is incremented by one until at least three manycast servers are found. Further retransmissions use the same time-to-live value.

If less than three servers are found when the time-to-live has reached the maximum specified by the <code>ttl</code> keyword, the poll interval is doubled. For each transmission after that, the poll interval is doubled again until reaching the maximum of eight times the value specified by the <code>maxpoll</code> keyword. Further transmissions use the same poll interval and time-to-live values.

The above scenario happens for each manycast client message, which repeats at the designated poll interval. However, once the ephemeral client association is mobilized, subsequent manycast server replies are discarded, since they will fail the message digest test. If during a poll interval the number of client associations falls below three, all manycast client prototype associations are reset to the initial poll interval and time-to-live values and operation resumes from the beginning. It is important in manycast mode to avoid frequent manycast client messages, since each one requires all manycast servers in range to respond. The result could well be an implosion, either minor or major, depending on the number of servers in range. The recommended value for <code>maxpoll</code> is 12 (4,096 s) and for <code>ttl</code> is 7.

It is possible and frequently useful to configure a host as both a manycast client and manycast server. A number of hosts configured this way and sharing a common group address will automatically organize themselves in an optimum configuration based on the smallest synchronization distance computed by the NTP mitigation algorithms. For example, consider an NTP subnet of two primary servers and maybe a dozen dependent clients. All servers and clients are configured as both multicast client and multicast server with multicast group address 239.1.1.1. In addition, the primary servers are configured for a primary reference source such as a GPS receiver. Once operations have stabilized in this scenario, the primary servers will affiliate with the primary reference source and each other, since they both operate at the same stratum (1), but not with any client, since clients operate at a higher stratum. The clients will find both primary servers and in addition, one of their own at the minimum synchronization distance. If one of the primary servers loses its GPS receiver, it will continue to operate as a client and other clients will time out the corresponding association and re-associate accordingly.

* * *

#### Burst Modes

There are two burst modes that can be enabled in client/server mode using the <code>iburst</code> and <code>burst</code> keywords. In either mode a single poll initiates a burst of eight client messages at intervals randomized over the range 1-4 s. However, the interval between the first and second messages is increased to about 16 s in order for a dialup modem to complete a call, if necessary. Received server messages update the NTPv4 clock filter, which selects the best (most accurate) time values. When the last client message in the burst is sent, the next received server message updates the system variables and sets the system clock in the usual manner, as if only a single client/server cycle had occurred. The result is not only a rapid and reliable setting of the system clock, but a considerable reduction in network jitter.

The <code>iburst</code> keyword can be configured for cases where it is important to set the clock quickly when an association is first mobilized or first becomes reachable or when the network attachment requires an initial calling or training procedure. The burst is initiated only when the server first becomes reachable and results in good accuracy with intermittent connections typical of PPP and ISDN services. Outlyers due to initial dial-up delays, etc., are avoided and the client sets the clock within 30 s after the first message.

The <code>burst</code> keyword can be configured in cases of excessive network jitter or when the network attachment requires an initial calling or training procedure. The burst is initiated at each poll interval when the server is reachable. The burst does produce additional network overhead and can cause trouble if used indiscriminately. It should only be used where the poll interval is expected to settle to values at or above 1024 s.