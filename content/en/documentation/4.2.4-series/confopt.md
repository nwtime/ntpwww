---
title: "Server Options"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/boom3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

The chicken is getting configuration advice.

* * *

#### Table of Contents

*   [Configuration Commands](/documentation/4.2.4-series/confopt/#configuration-commands)
*   [Command Options](/documentation/4.2.4-series/confopt/#command-options)
*   [Auxiliary Commands](/documentation/4.2.4-series/confopt/#auxiliary-commands)
*   [Bugs](/documentation/4.2.4-series/confopt/#bugs)

Following is a description of the configuration commands in NTPv4. There are two classes of commands, configuration commands that configure an association with a remote server, peer or reference clock, and auxilliary commands that specify environmental variables that control various related operations.

* * *

#### Configuration Commands

The various modes are determined by the command keyword and the required IP address. Addresses are classed by type as `s` a remote server or peer (IPv4 class A, B and C), `b` the broadcast address of a local interface, `m` a multicast address (IPv4 class D), or `r` a reference clock address (127.127.x.x). The options that can be used with these commands are listed below.

If the Basic Socket Interface Extensions for IPv6 (RFC-2553) is detected, support for the IPv6 address family is generated in addition to the default support of the IPv4 address family. IPv6 addresses can be identified by the presence of colons `:` in the address field. IPv6 addresses can be used almost everywhere where IPv4 addresses can be used, with the exception of reference clock addresses, which are always IPv4. Note that in contexts where a host name is expected, a <code>-4</code> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <code>-6</code> qualifier forces DNS resolution to the IPv6 namespace.

There are three types of associations: persistent, preemptable and ephemeral. Persistent associations are mobilized by a configuration command and never demobilized. Preemptable associations, which are new to NTPv4, are mobilized by a configuration command which includes the <code>prempt</code> flag and are demobilized by timeout or error. Ephemeral associations are mobilized upon arrival of designated messages and demobilized by timeout or error.

<code>**server _address_ [options ...]**</code>
: <code>**peer address [options ...]**</code>
: <code>**broadcast address [options ...]**</code>
: <code>**manycastclient address [options ...]**</code>

These four commands specify the time server name or address to be used and the mode in which to operate. The <code>address</code> can be either a DNS name or a IP address in dotted-quad notation. Additional information on association behavior can be found in the [Association Management](/documentation/4.2.4-series/assoc/) page. 

<code>**server**</code>

: For type s and r addresses (only), this command normally mobilizes a persistent client mode association with the specified remote server or local reference clock. If the <code>preempt</code> flag is specified, a preemptable association is mobilized instead. In client mode the client clock can synchronize to the remote server or local reference clock, but the remote server can never be synchronized to the client clock. This command should NOT be used for type <code>b</code> or <code>m</code> addresses. 

<code>**peer**</code>

: For type s addresses (only), this command mobilizes a persistent symmetric-active mode association with the specified remote peer. In this mode the local clock can be synchronized to the remote peer or the remote peer can be synchronized to the local clock. This is useful in a network of servers where, depending on various failure scenarios, either the local or remote peer may be the better source of time. This command should NOT be used for type <code>b</code>, <code>m</code> or <code>r</code> addresses. 

<code>**broadcast**</code> 

: For type <code>b</code> and <code>m</code> addresses (only), this command mobilizes a persistent broadcast mode association. Multiple commands can be used to specify multiple local broadcast interfaces (subnets) and/or multiple multicast groups. Note that local broadcast messages go only to the interface associated with the subnet specified, but multicast messages go to all interfaces. 

In broadcast mode the local server sends periodic broadcast messages to a client population at the <code>address</code> specified, which is usually the broadcast address on (one of) the local network(s) or a multicast address assigned to NTP. The IANA has assigned the multicast group address IPv4 224.0.1.1 and IPv6 ff05::101 (site local) exclusively to NTP, but other nonconflicting addresses can be used to contain the messages within administrative boundaries. Ordinarily, this specification applies only to the local server operating as a sender; for operation as a broadcast client, see the <code>broadcastclient</code> or <code>multicastclient</code> commands below. 

<code>**manycastclient**</code> 

: For type <code>m</code> addresses (only), this command mobilizes a preemptable manycast client mode association for the multicast group address specified. In this mode a specific address must be supplied which matches the address used on the <code>manycastserver</code> command for the designated manycast servers. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to avoid spraying large areas of the Internet with these messages and causing a possibly massive implosion of replies at the sender. 

The <code>manycastclient</code> command specifies that the host is to operate in client mode with the remote servers that are discovered as the result of broadcast/multicast messages. The client broadcasts a request message to the group address associated with the specified <code>address</code> and specifically enabled servers respond to these messages. The client selects the servers providing the best time and continues as with the <code>server</code> command. The remaining servers are discarded as if never heard. 

* * *

#### Command Options

<code>**autokey**</code>

: All packets sent to and received from the server or peer are to include authentication fields encrypted using the autokey scheme described in the [Authentication Options](/documentation/4.2.4-series/authopt/) page. This option is valid with all commands.

<code>**burst**</code>

: When the server is reachable, send a burst of eight packets instead of the usual one. The packet spacing is normally 2 s; however, the spacing between the first and second packets can be changed with the [<code>calldelay</code>](/documentation/4.2.4-series/miscopt/) command to allow additional time for a modem or ISDN call to complete. This option is valid only with the <code>server</code> command and is a recommended option with this command when the <code>maxpoll</code> option is 11 or greater.

<code>**iburst**</code>

: When the server is unreachable, send a burst of eight packets instead of the usual one. The packet spacing is normally 2 s; however, the spacing between the first and second packets can be changed with the [<code>calldelay</code>](/documentation/4.2.4-series/miscopt/) command to allow additional time for a modem or ISDN call to complete. This option is valid only with the <code>server</code> command and is a recommended option with this command.

<code>**key _key_**</code>

: All packets sent to and received from the server or peer are to include authentication fields encrypted using the specified _<code>key</code>_ identifier with values from 1 to 65534, inclusive. The default is to include no encryption field. This option is valid with all commands.

<code>**minpoll _minpoll_**</code>  
: <code>**maxpoll _maxpoll_**</code>

: These options specify the minimum and maximum poll intervals for NTP messages, in seconds as a power of two. The maximum poll interval defaults to 10 (1024 s), but can be increased by the <code>maxpoll</code> option to an upper limit of 17 (36.4 h). The minimum poll interval defaults to 6 (64 s), but can be decreased by the <code>minpoll</code> option to a lower limit of 4 (16 s). These option are valid only with the <code>server</code> and <code>peer</code> commands.

<code>**noselect**</code>

: Marks the server as unused, except for display purposes. The server is discarded by the selection algorithm. This option is valid only with the <code>server</code> and <code>peer</code> commands.

<code>**preempt**</code>

: Specifies the association as preemptable rather than the default persistent. This option is valid only with the <code>server</code> command.

<code>**prefer**</code>

: Mark the server as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.4-series/prefer/) page for further information. This option is valid only with the <code>server</code> and <code>peer</code> commands.

<code>**true**</code>

: Force the association to assume truechimer status; that is, always survive the selection and clustering algorithms. This option can be used with any association, but is most useful for reference clocks with large jitter on the serial port and precision pulse-per-second (PPS) signals.
> **Caution:** this option defeats the algorithms designed to cast out falsetickers and can allow these sources to set the system clock. This option is valid only with the <code>server</code> and <code>peer</code> commands.

<code>**ttl _ttl_**</code>

: This option is used only with broadcast server and manycast client modes. It specifies the time-to-live _<code>ttl</code>_ to use on broadcast server and multicast server and the maximum <code>ttl</code> for the expanding ring search with manycast client packets. Selection of the proper value, which defaults to 127, is something of a black art and should be coordinated with the network administrator. 

<code>**version _version_**</code>

: Specifies the version number to be used for outgoing NTP packets. Versions 1-4 are the choices, with version 4 the default. This option is valid only with the <code>server</code>, <code>peer</code> and <code>broadcast</code> commands.

* * *

#### Auxiliary Commands

<code>**broadcastclient [novolley]**</code>

: This command enables reception of broadcast server messages to any local interface (type b) address. Ordinarily, upon receiving a message for the first time, the broadcast client measures the nominal server propagation delay using a brief client/server exchange with the server, after which it continues in listen-only mode. If the <code>novolley</code> keyword is present, the exchange is not used and the value specified in the <code>broadcastdelay</code> command is used or, if the <code>broadcastdelay</code> command is not used, the default 4.0 ms. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/documentation/4.2.4-series/authopt/) page. Note that the <code>novolley</code> keyword is incompatible with public key authentication.

<code>**manycastserver _address_ [...]**</code>

: This command enables reception of manycast client messages to the multicast group address(es) (type <code>m</code>) specified. At least one address is required. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to limit the span of the reply and avoid a possibly massive implosion at the original sender. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/documentation/4.2.4-series/authopt/) page.

<code>**multicastclient _address_ [...]**</code>

: This command enables reception of multicast server messages to the multicast group address(es) (type <code>m</code>) specified. Upon receiving a message for the first time, the multicast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding multicast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/documentation/4.2.4-series/authopt/) page.

<code>**dynamic**</code>

: Allows a server/peer to be configured even if it is not reachable at configuration time. It is assumed that at some point in the future the network environment changed so that this server/peer can be reached. This option is usful to configure servers/peers on mobile systems with intermittent network access (e.g. wlan clients). 

* * *

#### Bugs

The syntax checking is not picky; some combinations of ridiculous and even hilarious options and modes may not be detected.