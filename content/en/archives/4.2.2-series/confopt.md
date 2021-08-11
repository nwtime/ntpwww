---
title: "Server Options"
type: archives
---

![gif](/archives/pic/boom3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

The chicken is getting configuration advice.

Last update: 	20:57 UTC Monday, October 10, 2005

* * *

#### Table of Contents

*   [Configuration Commands](/archives/4.2.2-series/confopt/#configuration-commands)
*   [Command Options](/archives/4.2.2-series/confopt/#command-options)
*   [Auxiliary Commands](/archives/4.2.2-series/confopt/#auxiliary-commands)
*   [Bugs](/archives/4.2.2-series/confopt/#bugs)

Following is a description of the configuration commands in NTPv4. There are two classes of commands, configuration commands that configure an association with a remote server, peer or reference clock, and auxilliary commands that specify environmental variables that control various related operations.

* * *

#### Configuration Commands

The various modes are determined by the command keyword and the required IP address. Addresses are classed by type as `s` a remote server or peer (IPv4 class A, B and C), `b` the broadcast address of a local interface, `m` a multicast address (IPv4 class D), or `r` a reference clock address (127.127.x.x). The options that can be used with these commands are listed below.

If the Basic Socket Interface Extensions for IPv6 (RFC-2553) is detected, support for the IPv6 address family is generated in addition to the default support of the IPv4 address family. IPv6 addresses can be identified by the presence of colons `:` in the address field. IPv6 addresses can be used almost everywhere where IPv4 addresses can be used, with the exception of reference clock addresses, which are always IPv4. Note that in contexts where a host name is expected, a <tt>-4</tt> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <tt>-6</tt> qualifier forces DNS resolution to the IPv6 namespace.

There are three types of associations: persistent, preemptable and ephemeral. Persistent associations are mobilized by a configuration command and never demobilized. Preemptable associations, which are new to NTPv4, are mobilized by a configuration command which includes the <tt>prempt</tt> flag and are demobilized by timeout or error. Ephemeral associations are mobilized upon arrival of designated messages and demobilized by timeout or error.

<dt><tt>server _address_ [options ...]</tt></dt>

<dt><tt>peer address [options ...]</tt></dt>

<dt><tt>broadcast address [options ...]</tt></dt>

<dt><tt>manycastclient address [options ...]</tt></dt>

These four commands specify the time server name or address to be used and the mode in which to operate. The <tt>address</tt> can be either a DNS name or a IP address in dotted-quad notation. Additional information on association behavior can be found in the [Association Management](/archives/4.2.2-series/assoc) page. 

<dt><tt>server</tt></dt>

For type s and r addresses (only), this command normally mobilizes a persistent client mode association with the specified remote server or local reference clock. If the <tt>preempt</tt> flag is specified, a preemptable association is mobilized instead. In client mode the client clock can synchronize to the remote server or local reference clock, but the remote server can never be synchronized to the client clock. This command should NOT be used for type <tt>b</tt> or <tt>m</tt> addresses. 

<dt><tt>peer</tt></dt>

For type s addresses (only), this command mobilizes a persistent symmetric-active mode association with the specified remote peer. In this mode the local clock can be synchronized to the remote peer or the remote peer can be synchronized to the local clock. This is useful in a network of servers where, depending on various failure scenarios, either the local or remote peer may be the better source of time. This command should NOT be used for type <tt>b</tt>, <tt>m</tt> or <tt>r</tt> addresses. 

<dt><tt>broadcast</tt></dt> 

For type <tt>b</tt> and <tt>m</tt> addresses (only), this command mobilizes a persistent broadcast mode association. Multiple commands can be used to specify multiple local broadcast interfaces (subnets) and/or multiple multicast groups. Note that local broadcast messages go only to the interface associated with the subnet specified, but multicast messages go to all interfaces. 

In broadcast mode the local server sends periodic broadcast messages to a client population at the <tt>address</tt> specified, which is usually the broadcast address on (one of) the local network(s) or a multicast address assigned to NTP. The IANA has assigned the multicast group address IPv4 224.0.1.1 and IPv6 ff05::101 (site local) exclusively to NTP, but other nonconflicting addresses can be used to contain the messages within administrative boundaries. Ordinarily, this specification applies only to the local server operating as a sender; for operation as a broadcast client, see the <tt>broadcastclient</tt> or <tt>multicastclient</tt> commands below. 

<dt><tt>manycastclient</tt></dt> 

For type <tt>m</tt> addresses (only), this command mobilizes a preemptable manycast client mode association for the multicast group address specified. In this mode a specific address must be supplied which matches the address used on the <tt>manycastserver</tt> command for the designated manycast servers. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to avoid spraying large areas of the Internet with these messages and causing a possibly massive implosion of replies at the sender. 

The <tt>manycastclient</tt> command specifies that the host is to operate in client mode with the remote servers that are discovered as the result of broadcast/multicast messages. The client broadcasts a request message to the group address associated with the specified <tt>address</tt> and specifically enabled servers respond to these messages. The client selects the servers providing the best time and continues as with the <tt>server</tt> command. The remaining servers are discarded as if never heard. 

* * *

#### Command Options

<dt><tt>autokey</tt></dt>

All packets sent to and received from the server or peer are to include authentication fields encrypted using the autokey scheme described in the [Authentication Options](/archives/4.2.2-series/authopt) page. This option is valid with all commands.

<dt><tt>burst</tt></dt>

When the server is reachable, send a burst of eight packets instead of the usual one. The packet spacing is normally 2 s; however, the spacing between the first and second packets can be changed with the [<tt>calldelay</tt>](/archives/4.2.2-series/miscopt) command to allow additional time for a modem or ISDN call to complete. This option is valid only with the <tt>server</tt> command and is a recommended option with this command when the <tt>maxpoll</tt> option is 11 or greater.

<dt><tt>iburst</tt></dt>

When the server is unreachable, send a burst of eight packets instead of the usual one. The packet spacing is normally 2 s; however, the spacing between the first and second packets can be changed with the [<tt>calldelay</tt>](/archives/4.2.2-series/miscopt) command to allow additional time for a modem or ISDN call to complete. This option is valid only with the <tt>server</tt> command and is a recommended option with this command.

<dt><tt>key</tt> _<tt>key</tt>_</dt>

All packets sent to and received from the server or peer are to include authentication fields encrypted using the specified _<tt>key</tt>_ identifier with values from 1 to 65534, inclusive. The default is to include no encryption field. This option is valid with all commands.

<dt><tt>minpoll _minpoll  
_</tt><tt>maxpoll _maxpoll_</tt></dt>

These options specify the minimum and maximum poll intervals for NTP messages, in seconds as a power of two. The maximum poll interval defaults to 10 (1024 s), but can be increased by the <tt>maxpoll</tt> option to an upper limit of 17 (36.4 h). The minimum poll interval defaults to 6 (64 s), but can be decreased by the <tt>minpoll</tt> option to a lower limit of 4 (16 s). These option are valid only with the <tt>server</tt> and <tt>peer</tt> commands.

<dt><tt>noselect</tt></dt>

Marks the server as unused, except for display purposes. The server is discarded by the selection algorithm. This option is valid only with the <tt>server</tt> and <tt>peer</tt> commands.

<dt><tt>preempt</tt></dt>

Specifies the association as preemptable rather than the default persistent. This option is valid only with the <tt>server</tt> command.

<dt><tt>prefer</tt></dt>

Mark the server as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.2-series/prefer) page for further information. This option is valid only with the <tt>server</tt> and <tt>peer</tt> commands.

<dt><tt>true</tt></dt>

Force the association to assume truechimer status; that is, always survive the selection and clustering algorithms. This option can be used with any association, but is most useful for reference clocks with large jitter on the serial port and precision pulse-per-second (PPS) signals. **Caution:** this option defeats the algorithms designed to cast out falsetickers and can allow these sources to set the system clock. This option is valid only with the <tt>server</tt> and <tt>peer</tt> commands.

<dt><tt>ttl _ttl_</tt></dt>

This option is used only with broadcast server and manycast client modes. It specifies the time-to-live _<tt>ttl</tt>_ to use on broadcast server and multicast server and the maximum <tt>ttl</tt> for the expanding ring search with manycast client packets. Selection of the proper value, which defaults to 127, is something of a black art and should be coordinated with the network administrator. 

<dt><tt>version _version_</tt></dt>

Specifies the version number to be used for outgoing NTP packets. Versions 1-4 are the choices, with version 4 the default. This option is valid only with the <tt>server</tt>, <tt>peer</tt> and <tt>broadcast</tt> commands.

* * *

#### Auxiliary Commands

<dt id="broadcastclient"><tt>broadcastclient [novolley]</tt></dt>

This command enables reception of broadcast server messages to any local interface (type b) address. Ordinarily, upon receiving a message for the first time, the broadcast client measures the nominal server propagation delay using a brief client/server exchange with the server, after which it continues in listen-only mode. If the <tt>novolley</tt> keyword is present, the exchange is not used and the value specified in the <tt>broadcastdelay</tt> command is used or, if the <tt>broadcastdelay</tt> command is not used, the default 4.0 ms. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.2.2-series/authopt) page. Note that the <tt>novolley</tt> keyword is incompatible with public key authentication.

<dt id="manycastserver"><tt>manycastserver _address_ [...]</tt></dt>

This command enables reception of manycast client messages to the multicast group address(es) (type <tt>m</tt>) specified. At least one address is required. The NTP multicast address 224.0.1.1 assigned by the IANA should NOT be used, unless specific means are taken to limit the span of the reply and avoid a possibly massive implosion at the original sender. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.2.2-series/authopt) page.

<dt id="multicastclient"><tt>multicastclient _address_ [...]</tt></dt>

This command enables reception of multicast server messages to the multicast group address(es) (type <tt>m</tt>) specified. Upon receiving a message for the first time, the multicast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding multicast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.2.2-series/authopt) page.

* * *

#### Bugs

The syntax checking is not picky; some combinations of ridiculous and even hilarious options and modes may not be detected.