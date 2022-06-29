---
title: "Access Control Commands and Options"
description: "Descriptions of the available commands and options for configuring NTP access control."
type: archives
---

![gif](/documentation/pic/pogo6.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

The skunk watches for intruders and sprays.

* * *

#### Commands and Options

Unless noted otherwise, further information about these commands is on the [Access Control Support](/documentation/4.2.8-series/access/) page.

<code>**discard [ average _avg_ ][ minimum _min_ ] [ monitor _prob_ ]**</code>

: Set the parameters of the rate control facility which protects the server from client abuse. If the <code>limited</code> flag is present in the ACL, packets that violate these limits are discarded. If, in addition, the <code>kod</code> flag is present, a kiss-o'-death packet is returned. See the [Rate Management](/documentation/4.2.8-series/rate/) page for further information. The options are:

<code>**average _avg_**</code>

: Specify the minimum average interpacket spacing (minimum average headway time) in log<sub>2</sub> s with default 3.

<code>**minimum _min_**</code>

: Specify the minimum interpacket spacing (guard time) in seconds with default 2.

<code>**monitor**</code>

Specify the probability of being recorded for packets that overflow the MRU list size limit set by <code>mru maxmem</code> or <code>mru maxdepth</code>. This is a performance optimization for servers with aggregate arrivals of 1000 packets per second or more.

<code>**restrict [-4 | -6] default [ippeerlimit _num_] [_flag_][...]**</code>
: <code>**restrict source [ippeerlimit _num_] [_flag_][...]**</code>
: <code>**restrict _address_ [mask _mask_] [ippeerlimit _num_] [_flag_][...]**</code>

The <code>_address_</code> argument expressed in IPv4 or IPv6 numeric address form is the address of a host or network. Alternatively, the <code>_address_</code> argument can be a valid host DNS name. The <code>_mask_</code> argument expressed in IPv4 or IPv6 numeric address form defaults to all mask bits on, meaning that the <code>_address_</code> is treated as the address of an individual host. A default entry (address 0.0.0.0, mask 0.0.0.0 for IPv4 and address :: mask :: for IPv6) is always the first entry in the list. <code>restrict default</code>, with no mask option, modifies both IPv4 and IPv6 default entries. <code>restrict source</code> configures a template restriction automatically added at runtime for each association, whether configured, ephemeral, or preemptible, and removed when the association is demobilized.

The optional <code>ippeerlimit</code> takes a numeric argument that indicates how many incoming (at present) peer requests will be permitted for each IP, regardless of whether or not the request comes from an authenticated source. A value of `-1` means "unlimited", which is the current default. A value of `0` means "none". Ordinarily one would expect at most 1 of these sessions to exist per IP, however if the remote side is operating thru a proxy there would be one association for each remote peer at that IP.

Some flags have the effect to deny service, some have the effect to enable service and some are conditioned by other flags. The flags are not orthogonal, in that more restrictive flags will often make less restrictive ones redundant. The flags that deny service are classed in two categories, those that restrict time service and those that restrict informational queries and attempts to do run-time reconfiguration of the server. One or more of the following flags may be specified:

<code>**flake**</code>

: Discard received NTP packets with probability 0.1; that is, on average drop one packet in ten. This is for testing and amusement. The name comes from Bob Braden's _flakeway_, which once did a similar thing for early Internet testing.

<code>**ignore**</code>

: Deny packets of all kinds, including <code>ntpq</code> and <code>ntpdc</code> queries.

<code>**kod**</code>

: Send a kiss-o'-death (KoD) packet if the <code>limited</code> flag is present and a packet violates the rate limits established by the <code>discard</code> command. KoD packets are themselves rate limited for each source address separately. If the <code>kod</code> flag is used in a restriction which does not have the <code>limited</code> flag, no KoD responses will result.

<code>**limited**</code>

: Deny time service if the packet violates the rate limits established by the <code>discard</code> command. This does not apply to <code>ntpq</code> and <code>ntpdc</code> queries.

<code>**lowpriotrap**</code>

: Declare traps set by matching hosts to be low priority. The number of traps a server can maintain is limited (the current limit is 3). Traps are usually assigned on a first come, first served basis, with later trap requestors being denied service. This flag modifies the assignment algorithm by allowing low priority traps to be overridden by later requests for normal priority traps.

<code>**mssntp**</code>

: Enable Microsoft Windows MS-SNTP authentication using Active Directory services.

> **NOTE:** Potential users should be aware that these services involve a TCP connection to another process that could potentially block, denying services to other users. Therefore, this flag should be used only for a dedicated server with no clients other than MS-SNTP.

<code>**noepeer**</code>

: Deny packets that would mobilize an ephemeral peering association, even if authenticated.

<code>**nomodify**</code>

: Deny <code>ntpq</code> and <code>ntpdc</code> queries which attempt to modify the state of the server (i.e., run time reconfiguration). Queries which return information are permitted.

<code>**noquery**</code>

: Deny <code>ntpq</code> and <code>ntpdc</code> queries. Time service is not affected.

<code>**nopeer**</code>

: Deny packets that might mobilize an association unless authenticated. This includes broadcast, symmetric-active and manycast server packets when a configured association does not exist. It also includes <code>pool</code> associations, so if you want to use servers from a <code>pool</code> directive and also want to use <code>nopeer</code> by default, you'll want a <code>restrict source</code> line as well that does _not_ include the <code>nopeer</code> directive. Note that this flag does not apply to packets that do not attempt to mobilize an association.

<code>**noserve**</code>

: Deny all packets except <code>ntpq</code> and <code>ntpdc</code> queries.

<code>**notrap**</code>

: Decline to provide mode 6 control message trap service to matching hosts. The trap service is a subsystem of the <code>ntpdc</code> control message protocol which is intended for use by remote event logging programs.

<code>**notrust**</code>

: Deny packets that are not cryptographically authenticated. Note carefully how this flag interacts with the <code>auth</code> option of the <code>enable</code> and <code>disable</code> commands. If <code>auth</code> is enabled, which is the default, authentication is required for all packets that might mobilize an association. If <code>auth</code> is disabled, but the <code>notrust</code> flag is not present, an association can be mobilized whether or not authenticated. If <code>auth</code> is disabled, but the <code>notrust</code> flag is present, authentication is required only for the specified address/mask range.

<code>**ntpport**</code>

: This is actually a match algorithm modifier, rather than a restriction flag. Its presence causes the restriction entry to be matched only if the source port in the packet is the standard NTP UDP port (123). A restrict line containing <code>ntpport</code> is considered more specific than one with the same address and mask, but lacking <code>ntpport</code>.

<code>**serverresponse fuzz**</code>

: When responding to server requests, fuzz the low order bits of the <code>reftime</code>.

<code>**version**</code>

: Deny packets that do not match the current NTP version.

Default restriction list entries with the flags <code>ignore, ntpport</code>, for each of the local host's interface addresses are inserted into the table at startup to prevent the server from attempting to synchronize to its own time. A default entry is also always present, though if it is otherwise unconfigured; no flags are associated with the default entry (i.e., everything besides your own NTP server is unrestricted).