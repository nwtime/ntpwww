---
title: "Server Options"
type: archives
---

![gif](/archives/pic/boom3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

The chicken is getting configuration advice.

Last update: 	25-Nov-2009 4:46

* * *

#### Table of Contents

*   [Configuration Commands](/archives/4.2.6-series/confopt/#configuration-commands)
*   [Command Options](/archives/4.2.6-series/confopt/#command-options)
*   [Auxiliary Commands](/archives/4.2.6-series/confopt/#auxiliary-commands)
*   [Bugs](/archives/4.2.6-series/confopt/#bugs)

Following is a description of the configuration commands in NTPv4. There are two classes of commands, configuration commands that configure an association with a remote server, peer or reference clock, and auxilliary commands that specify environmental variables that control various related operations.

The various modes described on the [Association Management](/archives/4.2.6-series/assoc) page are determined by the command keyword and the DNS name or IP address. Addresses are classed by type as (s) a remote server or peer (IPv4 class A, B and C), (b) the IP broadcast address of a local interface, (m) a multicast address (IPv4 class D), or (r) a reference clock address (127.127.x.x). For type m addresses the IANA has assigned the multicast group address IPv4 224.0.1.1 and IPv6 ff05::101 (site local) exclusively to NTP, but other nonconflicting addresses can be used.

If the Basic Socket Interface Extensions for IPv6 (RFC-2553) is detected, support for the IPv6 address family is generated in addition to the default IPv4 address family. IPv6 addresses can be identified by the presence of colons `:` in the address field. IPv6 addresses can be used almost everywhere where IPv4 addresses can be used, with the exception of reference clock addresses, which are always IPv4. Note that in contexts where a host name is expected, a `4` qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a `-6` qualifier forces DNS resolution to the IPv6 namespace.

* * *

#### Configuration Commands

These commands specify the time server name or address to be used and the mode in which to operate. The address can be either a DNS name or a IPv4 or IPv6 address in standard notation. In general, multiple commands of each type can be used for different server and peer addresses or multicast groups.

<dt id="server"><tt>server _address_ [options ...]</tt></dt>

For type s and r addresses (only), this command mobilizes a persistent client mode association with the specified remote server or local reference clock. If the <tt>preempt</tt> flag is specified, a preemptable client mode association is mobilized instead.

<dt><tt>peer _address_ [options ...]</tt></dt>

For type s addresses (only), this command mobilizes a persistent symmetric-active mode association with the specified remote peer.

<dt><tt>broadcast _address_ [options ...]</tt></dt> 

For type b and m addressees (only), this command mobilizes a persistent broadcast or multicast server mode association. Note that type b messages go only to the interface specified, but type m messages go to all interfaces.

<dt><tt>manycastclient _address_ [options ...]</tt></dt> 

For type m addresses (only), this command mobilizes a manycast client mode association for the multicast group address specified. In this mode the address must match the address specified on the <tt>manycastserver</tt> command of one or more designated manycast servers.

<dt><tt>pool _address_ [options ...]</tt></dt>

For type s messages (only) this command mobilizes a client mode association for servers implementing the pool automatic server discovery scheme described on the [Association Management](/archives/4.2.6-series/assoc) page. The address is a DNS name in the form <tt>_area_.pool.ntp.org</tt>, where <tt>_area_</tt> is a qualifier designating the server geographic area such as <tt>us</tt> or <tt>europe</tt>.

<dt><tt>unpeer [_address_ | _associd_]</tt></dt>

This command removes a previously configured association. An address or association ID can be used to identify the association. Either an IP address or DNS name can be used. This command is most useful when supplied via <tt>[ntpq](/archives/4.2.6-series/ntpq)</tt> runtime configuration commands <tt>:config</tt> and <tt>config-from-file</tt>.

* * *

#### Command Options

<dt><tt>autokey</tt></dt>

Send and receive packets authenticated by the Autokey scheme described in the [Authentication Options](/archives/4.2.6-series/authopt) page. This option is mutually exclusive with the <tt>key</tt> option.

<dt><tt>burst</tt></dt>

When the server is reachable, send a burst of eight packets instead of the usual one. The packet spacing is normally 2 s; however, the spacing between the first and second packets can be changed with the <tt>calldelay</tt> command to allow additional time for a modem or ISDN call to complete. This option is valid only with the <tt>server</tt> command and type s addressesa. It is a recommended option when the <tt>maxpoll</tt> option is greater than 10 (1024 s).

<dt><tt>iburst</tt></dt>

When the server is unreachable, send a burst of eight packets instead of the usual one. The packet spacing is normally 2 s; however, the spacing between the first and second packets can be changed with the <tt>calldelay</tt> command to allow additional time for a modem or ISDN call to complete. This option is valid only with the <tt>server</tt> command and type s addresses. It is a recommended option with this command.

<dt><tt>key</tt> _<tt>key</tt>_</dt>

Send and receive packets authenticated by the symmetric key scheme described in the [Authentication Options](/archives/4.2.6-series/authopt) page. The _<tt>key</tt>_ specifies the key identifier with values from 1 to 65534, inclusive. This option is mutually exclusive with the <tt>autokey</tt> option.

<dt><tt>minpoll _minpoll  
_</tt><tt>maxpoll _maxpoll_</tt></dt>

These options specify the minimum and maximum poll intervals for NTP messages, in seconds as a power of two. The maximum poll interval defaults to 10 (1024 s), but can be increased by the <tt>maxpoll</tt> option to an upper limit of 17 (36 h). The minimum poll interval defaults to 6 (64 s), but can be decreased by the <tt>minpoll</tt> option to a lower limit of 3 (8 s).

<dt><tt>mode _option_</tt></dt>

Pass the <tt>_option_</tt> to a reference clock driver, where <tt>_option_</tt> is an integer in the range from 0 to 255, inclusive. This option is valid only with type r addresses.

<dt><tt>noselect</tt></dt>

Marks the server or peer to be ignored by the selection algorithm but visible to the monitoring program. This option is ignored with the <tt>broadcast</tt> command.

<dt><tt>preempt</tt></dt>

Specifies the association as preemptable rather than the default persistent. This option is ignored with the <tt>broadcast</tt> command and is most useful with the <tt>manycastclient</tt> and <tt>pool</tt> commands.

<dt><tt>prefer</tt></dt>

Mark the server as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.6-series/prefer) page for further information. This option is valid only with the <tt>server</tt> and <tt>peer</tt> commands.

<dt><tt>true</tt></dt>

Mark the association to assume truechimer status; that is, always survive the selection and clustering algorithms. This option can be used with any association, but is most useful for reference clocks with large jitter on the serial port and precision pulse-per-second (PPS) signals. Caution: this option defeats the algorithms designed to cast out falsetickers and can allow these sources to set the system clock. This option is valid only with the <tt>server</tt> and <tt>peer</tt> commands.

<dt><tt>ttl _ttl_</tt></dt>

This option specifies the time-to-live _<tt>ttl</tt>_ for the <tt>broadcast</tt> command and the maximum _<tt>ttl</tt>_ for the expanding ring search used by the <tt>manycastclient</tt> command. Selection of the proper value, which defaults to 127, is something of a black art and should be coordinated with the network administrator. This option is invalid with type r addresses.

<dt><tt>version _version_</tt></dt>

Specifies the version number to be used f or outgoing NTP packets. Versions 1-4 are the choices, with version 4 the default.

<dt><tt>xleave</tt></dt>

Operate in interleaved mode (symmetric and broadcast modes only). (see [NTP Interleaved Modes](/archives/4.2.6-series/xleave))

* * *

#### Auxiliary Commands

<dt id="broadcastclient"><tt>broadcastclient</tt></dt>

Enable reception of broadcast server messages to any local interface (type b address). Ordinarily, upon receiving a broadcast message for the first time, the broadcast client measures the nominal server propagation delay using a brief client/server exchange, after which it continues in listen-only mode. If a nonzero value is specified in the <tt>broadcastdelay</tt> command, the value becomes the delay and the volley is not executed. Note: the <tt>novolley</tt> option has been deprecated for future enhancements. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.2.6-series/authopt) page. Note that the <tt>novolley</tt> keyword is incompatible with public key authentication.

<dt id="manycastserver"><tt>manycastserver _address_ [...]</tt></dt>

Enable reception of manycast client messages (type m)to the multicast group address(es) (type m) specified. At least one address is required. Note that, in order to avoid accidental or malicious disruption, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.2.6-series/authopt) page.

<dt id="multicastclient"><tt>multicastclient _address_ [...]</tt></dt>

Enable reception of multicast server messages to the multicast group address(es) (type m) specified. Upon receiving a message for the first time, the multicast client measures the nominal server propagation delay using a brief client/server exchange with the server, then enters the broadcast client mode, in which it synchronizes to succeeding multicast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the server and client should operate using symmetric key or public key authentication as described in the [Authentication Options](/archives/4.2.6-series/authopt) page.

* * *

#### Bugs

The syntax checking is not picky; some combinations of ridiculous and even hilarious options and modes may not be detected.