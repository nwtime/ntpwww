---
title: "Access Control Commands and Options"
type: archives
---

![gif](/archives/pic/pogo6.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

The skunk watches for intruders and sprays.

Last update: 7-Jan-2018 23:56 UTC

* * *

#### Commands and Options

Unless noted otherwise, further information about these commands is on the [Access Control Support](/archives/4.2.8-series/access) page.

<dt id="discard"><tt>discard [ average _avg_ ][ minimum _min_ ] [ monitor _prob_ ]</tt></dt>

Set the parameters of the rate control facility which protects the server from client abuse. If the <tt>limited</tt> flag is present in the ACL, packets that violate these limits are discarded. If, in addition, the <tt>kod</tt> flag is present, a kiss-o'-death packet is returned. See the [Rate Management](/archives/4.2.8-series/rate) page for further information. The options are:

<dt><tt>average _avg_</tt></dt>

Specify the minimum average interpacket spacing (minimum average headway time) in log<sub>2</sub> s with default 3.

<dt><tt>minimum _min_</tt></dt>

Specify the minimum interpacket spacing (guard time) in seconds with default 2.

<dt><tt>monitor</tt></dt>

Specify the probability of being recorded for packets that overflow the MRU list size limit set by <tt>mru maxmem</tt> or <tt>mru maxdepth</tt>. This is a performance optimization for servers with aggregate arrivals of 1000 packets per second or more.

<dt id="restrict"><tt>restrict [-4 | -6] default [ippeerlimit _num_] [_flag_][...]</tt></dt>

<dt><tt>restrict source [ippeerlimit _num_] [_flag_][...]</tt></dt>

<dt><tt>restrict _address_ [mask _mask_] [ippeerlimit _num_] [_flag_][...]</tt></dt>

The <tt>_address_</tt> argument expressed in IPv4 or IPv6 numeric address form is the address of a host or network. Alternatively, the <tt>_address_</tt> argument can be a valid host DNS name. The <tt>_mask_</tt> argument expressed in IPv4 or IPv6 numeric address form defaults to all mask bits on, meaning that the <tt>_address_</tt> is treated as the address of an individual host. A default entry (address 0.0.0.0, mask 0.0.0.0 for IPv4 and address :: mask :: for IPv6) is always the first entry in the list. <tt>restrict default</tt>, with no mask option, modifies both IPv4 and IPv6 default entries. <tt>restrict source</tt> configures a template restriction automatically added at runtime for each association, whether configured, ephemeral, or preemptible, and removed when the association is demobilized.

The optional <tt>ippeerlimit</tt> takes a numeric argument that indicates how many incoming (at present) peer requests will be permitted for each IP, regardless of whether or not the request comes from an authenticated source. A value of -1 means "unlimited", which is the current default. A value of 0 means "none". Ordinarily one would expect at most 1 of these sessions to exist per IP, however if the remote side is operating thru a proxy there would be one association for each remote peer at that IP.

Some flags have the effect to deny service, some have the effect to enable service and some are conditioned by other flags. The flags are not orthogonal, in that more restrictive flags will often make less restrictive ones redundant. The flags that deny service are classed in two categories, those that restrict time service and those that restrict informational queries and attempts to do run-time reconfiguration of the server. One or more of the following flags may be specified:

<dt><tt>flake</tt></dt>

Discard received NTP packets with probability 0.1; that is, on average drop one packet in ten. This is for testing and amusement. The name comes from Bob Braden's _flakeway_, which once did a similar thing for early Internet testing.

<dt><tt>ignore</tt></dt>

Deny packets of all kinds, including <tt>ntpq</tt> and <tt>ntpdc</tt> queries.

<dt><tt>kod</tt></dt>

Send a kiss-o'-death (KoD) packet if the <tt>limited</tt> flag is present and a packet violates the rate limits established by the <tt>discard</tt> command. KoD packets are themselves rate limited for each source address separately. If the <tt>kod</tt> flag is used in a restriction which does not have the <tt>limited</tt> flag, no KoD responses will result.

<dt id="limited"><tt>limited</tt></dt>

Deny time service if the packet violates the rate limits established by the <tt>discard</tt> command. This does not apply to <tt>ntpq</tt> and <tt>ntpdc</tt> queries.

<dt><tt>lowpriotrap</tt></dt>

Declare traps set by matching hosts to be low priority. The number of traps a server can maintain is limited (the current limit is 3). Traps are usually assigned on a first come, first served basis, with later trap requestors being denied service. This flag modifies the assignment algorithm by allowing low priority traps to be overridden by later requests for normal priority traps.

<dt><tt>mssntp</tt></dt>

Enable Microsoft Windows MS-SNTP authentication using Active Directory services. 

{{% alert title="Note" color="warning" %}} 
Potential users should be aware that these services involve a TCP connection to another process that could potentially block, denying services to other users. Therefore, this flag should be used only for a dedicated server with no clients other than MS-SNTP.
{{% /alert %}}

<dt><tt>noepeer</tt></dt>

Deny packets that would mobilize an ephemeral peering association, even if authenticated.

<dt><tt>nomodify</tt></dt>

Deny <tt>ntpq</tt> and <tt>ntpdc</tt> queries which attempt to modify the state of the server (i.e., run time reconfiguration). Queries which return information are permitted.

<dt><tt>noquery</tt></dt>

Deny <tt>ntpq</tt> and <tt>ntpdc</tt> queries. Time service is not affected.

<dt><tt>nopeer</tt></dt>

Deny packets that might mobilize an association unless authenticated. This includes broadcast, symmetric-active and manycast server packets when a configured association does not exist. It also includes <tt>pool</tt> associations, so if you want to use servers from a <tt>pool</tt> directive and also want to use <tt>nopeer</tt> by default, you'll want a <tt>"restrict source ..."</tt> line as well that does _not_ include the <tt>nopeer</tt> directive. Note that this flag does not apply to packets that do not attempt to mobilize an association.

<dt><tt>noserve</tt></dt>

Deny all packets except <tt>ntpq</tt> and <tt>ntpdc</tt> queries.

<dt><tt>notrap</tt></dt>

Decline to provide mode 6 control message trap service to matching hosts. The trap service is a subsystem of the <tt>ntpdc</tt> control message protocol which is intended for use by remote event logging programs.

<dt><tt>notrust</tt></dt>

Deny packets that are not cryptographically authenticated. Note carefully how this flag interacts with the <tt>auth</tt> option of the <tt>enable</tt> and <tt>disable</tt> commands. If <tt>auth</tt> is enabled, which is the default, authentication is required for all packets that might mobilize an association. If <tt>auth</tt> is disabled, but the <tt>notrust</tt> flag is not present, an association can be mobilized whether or not authenticated. If <tt>auth</tt> is disabled, but the <tt>notrust</tt> flag is present, authentication is required only for the specified address/mask range.

<dt><tt>ntpport</tt></dt>

This is actually a match algorithm modifier, rather than a restriction flag. Its presence causes the restriction entry to be matched only if the source port in the packet is the standard NTP UDP port (123). A restrict line containing <tt>ntpport</tt> is considered more specific than one with the same address and mask, but lacking <tt>ntpport</tt>.

<dt><tt>serverresponse fuzz</tt></dt>

When responding to server requests, fuzz the low order bits of the <tt>reftime</tt>.

<dt><tt>version</tt></dt>

Deny packets that do not match the current NTP version.

Default restriction list entries with the flags <tt>ignore, ntpport</tt>, for each of the local host's interface addresses are inserted into the table at startup to prevent the server from attempting to synchronize to its own time. A default entry is also always present, though if it is otherwise unconfigured; no flags are associated with the default entry (i.e., everything besides your own NTP server is unrestricted).