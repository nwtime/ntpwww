---
title: "Automatic NTP Configuration Options"
type: archives
--- 


![gif](/archives/pic/alice51.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/%7emills/pictures.html)

Make sure who your friends are.

Last update: 03:13 AM UTC Monday, October 13, 2003

* * *

#### Table of Contents

*   [Manycasting](/archives/4.2.0/manyopt/#manycasting)
*   [Manycast Interactions with Autokey](/archives/4.2.0/manyopt/#manycast-interactions-with-autokey)
*   [Manycast Options](/archives/4.2.0/manyopt/#manycast-options)

* * *

#### Manycasting

Manycasting is a automatic discovery and configuration paradigm new to NTPv4\. It is intended as a means for a multicast client to troll the nearby network neighborhood to find cooperating manycast servers, validate them using cryptographic means and evaluate their time values with respect to other servers that might be lurking in the vicinity. The intended result is that each manycast client mobilizes client associations with some number of the "best" of the nearby manycast servers, yet automatically reconfigures to sustain this number of servers should one or another fail.

Note that the manycasting paradigm does not coincide with the anycast paradigm described in RFC-1546, which is designed to find a single server from a clique of servers providing the same service. The manycast paradigm is designed to find a plurality of redundant servers satisfying defined optimality criteria.

Manycasting can be used with either symmetric key or public key cryptography. The public key infrastructure (PKI) offers the best protection against compromised keys and is generally considered stronger, at least with relatively large key sizes. It is implemented using the Autokey protocol and the OpenSSL cryptographic library available from https://www.openssl.org. The library can also be used with other NTPv4 modes as well and is highly recommended, especially for broadcast modes.

A persistent manycast client association is configured using the <tt>manycastclient</tt> command, which is similar to the <tt>server</tt> command but with a multicast (IPv4 class D or IPv6 prefix <tt>FF</tt>) group address. The IANA has designated IPv4 address 224.1.1.1 and IPv6 address FF05::101 (site local) for NTP. When more servers are needed, it broadcasts manycast client messages to this address at the minimum feasible rate and minimum feasible time-to-live (TTL) hops, depending on how many servers have already been found. There can be as many manycast client associations as different group address, each one serving as a template for a future ephemeral unicast client/server association.

Manycast servers configured with the <tt>manycastserver</tt> command listen on the specified group address for manycast client messages. Note the distinction between manycast client, which actively broadcasts messages, and manycast server, which passively responds to them. If a manycast server is in scope of the current TTL and is itself synchronized to a valid source and operating at a stratum level equal to or lower than the manycast client, it replies to the manycast client message with an ordinary unicast server message.

The manycast client receiving this message mobilizes an ephemeral client/server association according to the matching manycast client template, but only if cryptographically authenticated and the server stratum is less than or equal to the client stratum. Authentication is explicitly required and either symmetric key or public key (Autokey) can be used. Then, the client polls the server at its unicast address in burst mode in order to reliably set the host clock and validate the source. This normally results in a volley of eight client/server at 2-s intervals during which both the synchronization and cryptographic protocols run concurrently. Following the volley, the client runs the NTP intersection and clustering algorithms, which act to discard all but the "best" associations according to stratum and synchronization distance. The surviving associations then continue in ordinary client/server mode.

The manycast client polling strategy is designed to reduce as much as possible the volume of manycast client messages and the effects of implosion due to near-simultaneous arrival of manycast server messages. The strategy is determined by the <tt>manycastclient</tt>, <tt>tos</tt> and <tt>ttl</tt> configuration commands. The manycast poll interval is normally eight times the system poll interval, which starts out at the <tt>minpoll</tt> value specified in the <tt>manycastclient</tt>, command and, under normal circumstances, increments to the <tt>maxpolll</tt> value specified in this command. Initially, the TTL is set at the minimum hops specified by the <tt>ttl</tt> command. At each retransmission the TTL is increased until reaching the maximum hops specified by this command or a sufficient number client associations have been found. Further retransmissions use the same TTL.

The quality and reliability of the suite of associations discovered by the manycast client is determined by the NTP mitigation algorithms and the <tt>minclock</tt> and <tt>minsane</tt> values specified in the <tt>tos</tt> configuration command. At least <tt>minsane</tt> candidate servers must be available and the mitigation algorithms produce at least <tt>minclock</tt> survivors in order to synchronize the clock. Byzantine agreement principles require at least four candidates in order to correctly discard a single falseticker. For legacy purposes, <tt>minsane</tt> defaults to 1 and <tt>minclock</tt> defaults to 3\. For manycast service <tt>minsane</tt> should be explicitly set to 4\. assuming at least that number of servers are available.

If at least <tt>minclock</tt> servers are found, the manycast poll interval is immediately set to eight times <tt>maxpoll</tt>. If less than <tt>minclock</tt> servers are found when the TTL has reached the maximum hops, the manycast poll interval is doubled. For each transmission after that, the poll interval is doubled again until reaching the maximum of eight times <tt>maxpoll</tt>. Further transmissions use the same poll interval and TTL values. Note that while all this is going on, each client/server association found is operating normally it the system poll interval.

Administratively scoped multicast boundaries are normally specified by the network router configuration and, in the case of IPv6, the link/site scope prefix. By default, the increment for TTL hops is 32 starting from 31; however, the <tt>ttl</tt> configuration command can be used to modify the values to match the scope rules.

It is often useful to narrow the range of acceptable servers which can be found by manycast client associations. Because manycast servers respond only when the client stratum is equal to or greater than the server stratum, primary (stratum 1) servers fill find only primary servers in TTL range, which is probably the most common objective. However, unless configured otherwise, all manycast clients in TTL range will eventually find all primary servers in TTL range, which is probably not the most common objective in large networks. The <tt>tos</tt> command can be used to modify this behavior. Servers with stratum below <tt>floor</tt> or above <tt>ceiling</tt> specified in the <tt>tos</tt> command are strongly discouraged during the selection process; however, these servers may be temporally accepted if the number of servers within TTL range is less than <tt>minclock</tt>.

The above actions occur for each manycast client message, which repeats at the designated poll interval. However, once the ephemeral client association is mobilized, subsequent manycast server replies are discarded, since that would result in a duplicate association. If during a poll interval the number of client associations falls below <tt>minclock</tt>, all manycast client prototype associations are reset to the initial poll interval and TTL hops and operation resumes from the beginning. It is important to avoid frequent manycast client messages, since each one requires all manycast servers in TTL range to respond. The result could well be an implosion, either minor or major, depending on the number of servers in range. The recommended value for <tt>maxpoll</tt> is 12 (4,096 s).

It is possible and frequently useful to configure a host as both manycast client and manycast server. A number of hosts configured this way and sharing a common group address will automatically organize themselves in an optimum configuration based on stratum and synchronization distance. For example, consider an NTP subnet of two primary servers and a hundred or more dependent clients. With two exceptions, all servers and clients have identical configuration files including both <tt>multicastclient</tt> and <tt>multicastserver</tt> commands using, for instance, multicast group address 239.1.1.1\. The only exception is that each primary server configuration file must include commands for the primary reference source such as a GPS receiver.

The remaining configuration files for all secondary servers and clients have the same contents, except for the <tt>tos</tt> command, which is specific for each stratum level. For stratum 1 and stratum 2 servers, that command is not necessary. For stratum 3 and above servers the <tt>floor</tt> value is set to the intended stratum number. Thus, all stratum 3 configuration files are identical, all stratum 4 files are identical and so forth.

Once operations have stabilized in this scenario, the primary servers will find the primary reference source and each other, since they both operate at the same stratum (1), but not with any secondary server or client, since these operate at a higher stratum. The secondary servers will find the servers at the same stratum level. If one of the primary servers loses its GPS receiver, it will continue to operate as a client and other clients will time out the corresponding association and re-associate accordingly.

Some administrators prefer to avoid running <tt>ntpd</tt> continuously and run either <tt>ntpdate</tt> or <tt>ntpd -q</tt> as a cron job. In either case the servers must be configured in advance and the program fails if none are available when the cron job runs. A really slick application of manycast is with <tt>ntpd -q</tt>. The program wakes up, scans the local landscape looking for the usual suspects, selects the best from among the rascals, sets the clock and then departs. Servers do not have to be configured in advance and all clients throughout the network can have the same configuration file.

* * *

#### Manycast Interactions with Autokey

Each time a manycast client sends a client mode packet to a multicast group address, all manycast servers in scope generate a reply including the host name and status word. The manycast clients then run the Autokey protocol, which collects and verifies all certificates involved. Following the burst interval all but three survivors are cast off, but the certificates remain in the local cache. It often happens that several complete signing trails from the client to the primary servers are collected in this way.

About once an hour or less often if the poll interval exceeds this, the client regenerates the Autokey key list. This is in general transparent in client/server mode. However, about once per day the server private value used to generate cookies is refreshed along with all manycast client associations. In this case all cryptographic values including certificates is refreshed. If a new certificate has been generated since the last refresh epoch, it will automatically revoke all prior certificates that happen to be in the certificate cache. At the same time, the manycast scheme starts all over from the beginning and the expanding ring shrinks to the minimum and increments from there while collecting all servers in scope.

* * *

#### Manycast Options

<dt><tt>tos [ ceiling _ceiling_ | cohort {0 | 1} | floor _floor_ | minclock _minclock_ | minsane _minsane_ ]</tt></dt>

This command affects the clock selection and clustering algorithms. It can be used to select the quality and quantity of peers used to synchronize the system clock and is most useful in manycast mode. The variables operate as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>ceiling _ceiling_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Peers with strata above _ceiling_ will be discarded if there are at least _<tt>minclock</tt>_ peers remaining. This value defaults to 15, but can be changed to any number from 1 to 15.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>cohort { 0 | 1 }</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This is a binary flag which enables (0) or disables (1) manycast server replies to manycast clients with the same stratum level. This is useful to reduce implosions where large numbers of clients with the same stratum level are present. The default is to enable these replies.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>floor _floor_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Peers with strata below _floor_ will be discarded if there are at least _minclock_ peers remaining. This value defaults to 1, but can be changed to any number from 1 to 15.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>maxdist _maxdistance_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minclock _minclock_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The clustering algorithm repeatedly casts out outlyer associations until no more than _minclock_ associations remain. This value defaults to 3, but can be changed to any number from 1 to the number of configured sources.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minsane _minsane_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This is the minimum number of candidates available to the clock selection algorithm in order to produce one or more truechimers for the clustering algorithm. If fewer than this number are available, the clock is undisciplined and allowed to run free. The default is 1 for legacy purposes. However, according to principles of Byzantine agreement, _minsane_ should be at least 4 in order to detect and discard a single falseticker.

<dt><tt>ttl _hop_ ...</tt></dt>

This command specifies a list of TTL values in increasing order. Up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.