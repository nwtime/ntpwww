---
title: "Configuration Options"
type: archives
noindex: true
---

![gif](/archives/pic/boom3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

The chicken is getting configuration advice.

* * *

#### Table of Contents

*   [Configuration Commands](/archives/4.1.1/confopt/#configuration-commands)
*   [Options](/archives/4.1.1/confopt/#options)
*   [Auxiliary Commands](/archives/4.1.1/confopt/#auxiliary-commands)
*   [Bugs](/archives/4.1.1/confopt/#bugs)

* * *

Following is a description of the configuration commands in NTPv4. These commands have the same basic functions as in NTPv3 and in some cases new functions and new arguments. There are two classes of commands, configuration commands that configure a persistent association with a remote server, peer or reference clock, and auxilliary commands that specify environmental variables that control various related operations.

* * *

#### Configuration Commands

The various modes are determined by the command keyword and the type of the required IP address. Addresses are classed by type as `s` a remote server or peer (IP class A, B and C), `b` the broadcast address of a local interface, `m` a multicast address (IP class D), or `r` a reference clock address (127.127.x.x). Note that only those options applicable to each command are listed below. Use of options not listed may not be caught as an error, but may result in some weird and even destructive behavior.

<code>**server _address_ [key _key_ | autokey] [burst] [iburst] [version _version_] [prefer] [minpoll _minpoll_] [maxpoll _maxpoll_]**</code>
: <code>**peer _address_ [key _key_ | autokey] [version _version_] [prefer] [minpoll _minpoll_] [maxpoll _maxpoll_]**</code>
: <code>**broadcast _address_ [key _key_ | autokey] [version _version_] [minpoll _minpoll_] [ttl _ttl_]**</code>
: <code>**manycastclient _address_ [key _key_ | autokey] [version _version_] [minpoll _minpoll_ [maxpoll _maxpoll_] [ttl _ttl_]**</code>

: These four commands specify the time server name or address to be used and the mode in which to operate. The <code>address</code> can be either a DNS name or a IP address in dotted-quad notation. Additional information on association behavior can be found in the [Association Management](/archives/4.1.1/assoc/) page. 

<code>**server**</code>

: For type s and r addresses, this command mobilizes a persistent client mode association with the specified remote server or local radio clock. In this mode the local clock can synchronized to the remote server, but the remote server can never be synchronized to the local clock. This command should NOT be used for type <code>b</code> or <code>m</code> addresses. 

<code>**peer**</code>

: For type s addresses (only), this command mobilizes a persistent symmetric-active mode association with the specified remote peer. In this mode the local clock can be synchronized to the remote peer or the remote peer can be synchronized to the local clock. This is useful in a network of servers where, depending on various failure scenarios, either the local or remote peer may be the better source of time. This command should NOT be used for type <code>b</code>, <code>m</code> or <code>r</code> addresses. 

<code>**broadcast**</code> 

: For type <code>b</code> and <code>m</code> addresses (only), this command mobilizes a persistent broadcast mode association. Multiple commands can be used to specify multiple local broadcast interfaces (subnets) and/or multiple multicast groups. Note that local broadcast messages go only to the interface associated with the subnet specified, but multicast messages go to all interfaces. 

In broadcast mode the local server sends periodic broadcast messages to a client population at the <code>address</code> specified, which is usually the broadcast address on (one of) the local network(s) or a multicast address assigned to NTP. The IANA has assigned the multicast group address 224.0.1.1 exclusively to NTP, but other nonconflicting addresses can be used to contain the messages within administrative boundaries. Ordinarily, this specification applies only to the local server operating as a sender; for operation as a broadcast client, see the <code>broadcastclient</code> or <code>multicastclient</code> commands below. 

<code>**manycastclient**</code> 

: For type <code>m</code> addresses (only), this command mobilizes a preemptable manycast client mode association for the multicast group address specified. In this mode a specific address must be supplied which matches the address used on the <code>manycastserver</code> command for the designated manycast servers. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to avoid spraying large areas of the Internet with these messages and causing a possibly massive implosion of replies at the sender. 

The <code>manycastclient</code> command specifies that the host is to operate in client mode with the remote servers that are discovered as the result of broadcast/multicast messages. The client broadcasts a request message to the group address associated with the specified <code>address</code> and specifically enabled servers respond to these messages. The client selects the servers providing the best time and continues as with the <code>server</code> command. The remaining servers are discarded as if never heard. 

* * *

#### Options

<code>**autokey**</code>

: All packets sent to and received from the server or peer are to include authentication fields encrypted using the autokey scheme described in the [Authentication Options](/archives/4.1.1/authopt/) page. 

<code>**burst**</code>

: When the server is reachable and at each poll interval, send a burst of eight packets instead of the usual one packet. The spacing between the first and the second packets is about 16s to allow a modem call to complete, while the spacing between the remaining packets is about 2s. This is designed to improve timekeeping quality with the <code>server</code> command and <code>s</code> addresses.

<code>**iburst**</code>

: When the server is unreachable and at each poll interval, send a burst of eight packets instead of the usual one. As long as the server is unreachable, the spacing between packets is about 16s to allow a modem call to complete. Once the server is reachable, the spacing between packets is about 2s. This is designed to speed the initial synchronization acquisition with the <code>server</code> command and <code>s</code> addresses and when <code>ntpd</code> is started with the <code>-q</code> option. 

<code>**key _key_**</code>

: All packets sent to and received from the server or peer are to include authentication fields encrypted using the specified <code>_key_</code> identifier with values from 1 to 65534, inclusive. The default is to include no encryption field. 

<code>**minpoll _minpoll_**</code> 
: <code>**maxpoll _maxpoll_**</code>

: These options specify the minimum and maximum poll intervals for NTP messages, in seconds as a power of two. The maximum poll interval defaults to 10 (1024 s), but can be increased by the <code>maxpoll</code> option to an upper limit of 17 (36.4 h). The minimum poll interval defaults to 6 (64 s), but can be decreased by the <code>minpoll</code> option to a lower limit of 4 (16 s). 

<code>**prefer**</code>

: Marks the server as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <code>prefer</code> Keyword](/archives/4.1.1/prefer/) page for further information. 

<code>**ttl _ttl_**</code>

: This option is used only with broadcast server and manycast client modes. It specifies the time-to-live <code>_ttl_</code> to use on broadcast server and multicast server and the maximum <code>ttl</code> for the expanding ring search with manycast client packets. Selection of the proper value, which defaults to 127, is something of a black art and should be coordinated with the network administrator. 

<code>**version _version_**</code>

: Specifies the version number to be used for outgoing NTP packets. Versions 1-4 are the choices, with version 4 the default. 

* * *

#### Auxiliary Commands

<code>**broadcastclient**</code>

: This command enables reception of broadcast server messages to any local interface (type b) address. Upon receiving a message for the first time, the broadcast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding broadcast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric-key or public-key authentication as described in the [Authentication Options](/archives/4.1.1/authopt/) page. 

<code>**manycastserver _address_ [...]**</code>

: This command enables reception of manycast client messages to the multicast group address(es) (type <code>m</code>) specified. At least one address is required. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to limit the span of the reply and avoid a possibly massive implosion at the original sender. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.1.1/authopt/) page.

<code>**multicastclient _address_ [...]**</code>

: This command enables reception of multicast server messages to the multicast group address(es) (type <code>m</code>) specified. Upon receiving a message for the first time, the multicast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding multicast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.1.1/authopt/) page.

* * *

#### Bugs

The syntax checking is not picky; some combinations of ridiculous and even hilarious options and modes may not be detected.