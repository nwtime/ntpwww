---
title: "Configuration Options"
type: archives
---

![gif](/archives/pic/boom3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

The chicken is getting configuration advice.

* * *

#### Table of Contents

*   [Configuration Commands](/archives/4.1.2/confopt/#configuration-commands)
*   [Options](/archives/4.1.2/confopt/#options)
*   [Auxiliary Commands](/archives/4.1.2/confopt/#auxiliary-commands)
*   [Bugs](/archives/4.1.2/confopt/#bugs)

Following is a description of the configuration commands in NTPv4. These commands have the same basic functions as in NTPv3 and in some cases new functions and new arguments. There are two classes of commands, configuration commands that configure a persistent association with a remote server, peer or reference clock, and auxilliary commands that specify environmental variables that control various related operations.

* * *

#### Configuration Commands

The various modes are determined by the command keyword and the type of the required IP address. Addresses are classed by type as `s` a remote server or peer (IP class A, B and C), `b` the broadcast address of a local interface, `m` a multicast address (IP class D), or `r` a reference clock address (127.127.x.x). Note that only those options applicable to each command are listed below. Use of options not listed may not be caught as an error, but may result in some weird and even destructive behavior.

<dt><tt>server _address_ [key _key_ | autokey] [burst] [iburst] [version _version_] [prefer] [minpoll _minpoll_] [maxpoll _maxpoll_]</tt></dt>

<dt><tt>peer _address_ [key _key_ | autokey] [version _version_] [prefer] [minpoll _minpoll_] [maxpoll _maxpoll_]</tt></dt>

<dt><tt>broadcast _address_ [key _key_ | autokey] [version _version_] [minpoll _minpoll_] [ttl _ttl_]</tt></dt>

<dt><tt>manycastclient _address_ [key _key_ | autokey] [version _version_] [minpoll _minpoll_ [maxpoll _maxpoll_] [ttl _ttl_]</tt></dt>

These four commands specify the time server name or address to be used and the mode in which to operate. The <tt>address</tt> can be either a DNS name or a IP address in dotted-quad notation. Additional information on association behavior can be found in the [Association Management](/archives/4.1.2/assoc) page. 

<dt><tt>server</tt></dt>

For type s and r addresses, this command mobilizes a persistent client mode association with the specified remote server or local radio clock. In this mode the local clock can synchronized to the remote server, but the remote server can never be synchronized to the local clock. This command should NOT be used for type <tt>b</tt> or <tt>m</tt> addresses. 

<dt><tt>peer</tt></dt>

For type s addresses (only), this command mobilizes a persistent symmetric-active mode association with the specified remote peer. In this mode the local clock can be synchronized to the remote peer or the remote peer can be synchronized to the local clock. This is useful in a network of servers where, depending on various failure scenarios, either the local or remote peer may be the better source of time. This command should NOT be used for type <tt>b</tt>, <tt>m</tt> or <tt>r</tt> addresses. 

<dt><tt>broadcast</tt></dt> 

For type <tt>b</tt> and <tt>m</tt> addresses (only), this command mobilizes a persistent broadcast mode association. Multiple commands can be used to specify multiple local broadcast interfaces (subnets) and/or multiple multicast groups. Note that local broadcast messages go only to the interface associated with the subnet specified, but multicast messages go to all interfaces. 

In broadcast mode the local server sends periodic broadcast messages to a client population at the <tt>address</tt> specified, which is usually the broadcast address on (one of) the local network(s) or a multicast address assigned to NTP. The IANA has assigned the multicast group address 224.0.1.1 exclusively to NTP, but other nonconflicting addresses can be used to contain the messages within administrative boundaries. Ordinarily, this specification applies only to the local server operating as a sender; for operation as a broadcast client, see the <tt>broadcastclient</tt> or <tt>multicastclient</tt> commands below. 

<dt><tt>manycastclient</tt></dt> 

For type <tt>m</tt> addresses (only), this command mobilizes a preemptable manycast client mode association for the multicast group address specified. In this mode a specific address must be supplied which matches the address used on the <tt>manycastserver</tt> command for the designated manycast servers. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to avoid spraying large areas of the Internet with these messages and causing a possibly massive implosion of replies at the sender. 

The <tt>manycastclient</tt> command specifies that the host is to operate in client mode with the remote servers that are discovered as the result of broadcast/multicast messages. The client broadcasts a request message to the group address associated with the specified <tt>address</tt> and specifically enabled servers respond to these messages. The client selects the servers providing the best time and continues as with the <tt>server</tt> command. The remaining servers are discarded as if never heard. 

* * *

#### Options

<dt><tt>autokey</tt></dt>

All packets sent to and received from the server or peer are to include authentication fields encrypted using the autokey scheme described in the [Authentication Options](/archives/4.1.2/authopt) page. 

<dt><tt>burst</tt></dt>

when the server is reachable and at each poll interval, send a burst of eight packets instead of the usual one packet. The spacing between the first and the second packets is about 16s to allow a modem call to complete, while the spacing between the remaining packets is about 2s. This is designed to improve timekeeping quality with the <tt>server</tt> command and <tt>s</tt> addresses.

<dt><tt>iburst</tt></dt>

When the server is unreachable and at each poll interval, send a burst of eight packets instead of the usual one. As long as the server is unreachable, the spacing between packets is about 16s to allow a modem call to complete. Once the server is reachable, the spacing between packets is about 2s. This is designed to speed the initial synchronization acquisition with the <tt>server</tt> command and <tt>s</tt> addresses and when <tt>ntpd</tt> is started with the <tt>-q</tt> option. 

<dt><tt>key</tt> _<tt>key</tt>_</dt>

All packets sent to and received from the server or peer are to include authentication fields encrypted using the specified _<tt>key</tt>_ identifier with values from 1 to 65534, inclusive. The default is to include no encryption field. 

<dt><tt>minpoll _minpoll  
_</tt><tt>maxpoll _maxpoll_</tt></dt>

These options specify the minimum and maximum poll intervals for NTP messages, in seconds as a power of two. The maximum poll interval defaults to 10 (1024 s), but can be increased by the <tt>maxpoll</tt> option to an upper limit of 17 (36.4 h). The minimum poll interval defaults to 6 (64 s), but can be decreased by the <tt>minpoll</tt> option to a lower limit of 4 (16 s). 

<dt><tt>prefer</tt></dt>

Marks the server as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.1.2/prefer) page for further information. 

<dt><tt>ttl _ttl_</tt></dt>

This option is used only with broadcast server and manycast client modes. It specifies the time-to-live _<tt>ttl</tt>_ to use on broadcast server and multicast server and the maximum <tt>ttl</tt> for the expanding ring search with manycast client packets. Selection of the proper value, which defaults to 127, is something of a black art and should be coordinated with the network administrator. 

<dt><tt>version _version_</tt></dt>

Specifies the version number to be used for outgoing NTP packets. Versions 1-4 are the choices, with version 4 the default. 

* * *

#### Auxiliary Commands

<dt id="broadcastclient"><tt>broadcastclient</tt></dt>

This command enables reception of broadcast server messages to any local interface (type b) address. Upon receiving a message for the first time, the broadcast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding broadcast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric-key or public-key authentication as described in the [Authentication Options](/archives/4.1.2/authopt) page. 

<dt id="manycastserver"><tt>manycastserver _address_ [...]</tt></dt>

This command enables reception of manycast client messages to the multicast group address(es) (type <tt>m</tt>) specified. At least one address is required. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to limit the span of the reply and avoid a possibly massive implosion at the original sender. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.1.2/authopt) page.

<dt id="multicastclient"><tt>multicastclient _address_ [...]</tt></dt>

This command enables reception of multicast server messages to the multicast group address(es) (type <tt>m</tt>) specified. Upon receiving a message for the first time, the multicast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding multicast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.1.2/authopt) page.

* * *

#### Bugs

The syntax checking is not picky; some combinations of ridiculous and even hilarious options and modes may not be detected.