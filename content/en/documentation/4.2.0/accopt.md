---
title: "Access Control Options"
type: archives
noindex: true
---

![gif](/archives/pic/pogo6.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

The skunk watches for intruders and sprays.

Last update: 03:02 AM UTC Monday, October 13, 2003

* * *

#### Table of Contents

*  [Access Control Support](/archives/4.2.0/accopt/#access-control-support)
*  [The Kiss-of-Death Packet](/archives/4.2.0/accopt/#the-kiss-of-death-packet)
*  [Access Control Commands](/archives/4.2.0/accopt/#access-control-commands)

* * *

#### Access Control Support

The <code>ntpd</code> daemon implements a general purpose address/mask based restriction list. The list contains address/match entries sorted first by increasing address values and then by increasing mask values. A match occurs when the bitwise AND of the mask and the packet source address is equal to the bitwise AND of the mask and address in the list. The list is searched in order with the last match found defining the restriction flags associated with the entry. Additional information and examples can be found in the [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/4.2.0/notes/) page. 

The restriction facility was implemented in conformance with the access policies for the original NSFnet backbone time servers. Later the facility was expanded to deflect cryptographic and clogging attacks. While this facility may be useful for keeping unwanted or broken or malicious clients from congesting innocent servers, it should not be considered an alternative to the NTP authentication facilities. Source address based restrictions are easily circumvented by a determined cracker.

Clients can be denied service because they are explicitly included in the restrict list created by the <code>restrict</code> command or implicitly as the result of cryptographic or rate limit violations. Cryptographic violations include certificate or identity verification failure; rate limit violations generally result from defective NTP implementations that send packets at abusive rates. Some violations cause denied service only for the offending packet, others cause denied service for a timed period and others cause the denied service for an indefinite period. When a client or network is denied access for an indefinite period, the only way at present to remove the restrictions is by restarting the server.

* * *

#### The Kiss-of-Death Packet

Ordinarily, packets denied service are simply dropped with no further action except incrementing statistics counters. Sometimes a more proactive response is needed, such as a server message that explicitly requests the client to stop sending and leave a message for the system operator. A special packet format has been created for this purpose called the "kiss-o'-death" (KoD) packet. KoD packets have the leap bits set unsynchronized and stratum set to zero and the reference identifier field set to a four-byte ASCII code. If the <code>noserve</code> or <code>notrust</code> flag of the matching restrict list entry is set, the code is "DENY"; if the <code>limited</code> flag is set and the rate limit is exceeded, the code is "RATE". Finally, if a cryptographic violation occurs, the code is <code>CRYP</code>.

A client receiving a KoD performs a set of sanity checks to minimize security exposure, then updates the stratum and reference identifier peer variables, sets the access denied (TEST4) bit in the peer flash variable and sends a message to the log. As long as the TEST4 bit is set, the client will send no further packets to the server. The only way at present to recover from this condition is to restart the protocol at both the client and server. This happens automatically at the client when the association times out. It will happen at the server only if the server operator cooperates.

* * *

#### Access Control Commands

<code>**discard [ average _avg_ ][ minimum _min_ ] [ monitor _prob_ ]**</code>

: Set the parameters of the <code>limited</code> facility which protects the server from client abuse. The <code>average</code> subcommand specifies the minimum average packet spacing, while the <code>minimum</code> subcommand specifies the minimum packet spacing. Packets that violate these minima are discarded and a kiss-o'-death packet returned if enabled. The default minimum average and minimum are 5 and 2, respectively. The monitor subcommand specifies the probability of discard for packets that overflow the rate-control window. 

<code>**restrict _address_ [mask _mask_] [_flag_][...]**</code>

: The <code>_address_</code> argument expressed in dotted-quad form is the address of a host or network. Alternatively, the <code>address</code> argument can be a valid host DNS name. The <code>mask</code> argument expressed in dotted-quad form defaults to <code>255.255.255.255</code>, meaning that the <code>address</code> is treated as the address of an individual host. A default entry (address <code>0.0.0.0</code>, mask <code>0.0.0.0</code>) is always included and is always the first entry in the list. Note that text string <code>default</code>, with no mask option, may be used to indicate the default entry. 

In the current implementation, <code>flag</code> always restricts access, i.e., an entry with no flags indicates that free access to the server is to be given. The flags are not orthogonal, in that more restrictive flags will often make less restrictive ones redundant. The flags can generally be classed into two catagories, those which restrict time service and those which restrict informational queries and attempts to do run-time reconfiguration of the server. One or more of the following flags may be specified: 

<code>ignore</code>

: Deny packets of all kinds, including <code>ntpq</code> and <code>ntpdc</code> queries.

<code>kod</code>

: If this flag is set when an access violation occurs, a kiss-o'-death (KoD) packet is sent. KoD packets are rate limited to no more than one per second. If another KoD packet occurs within one second after the last one, the packet is dropped.

<code>limited</code>

: Deny service if the packet spacing violates the lower limits specified in the <code>discard</code> command. A history of clients is kept using the monitoring capability of <code>ntpd</code>. Thus, monitoring is always active as long as there is a restriction entry with the <code>limited</code> flag.

<code>lowpriotrap</code>

: Declare traps set by matching hosts to be low priority. The number of traps a server can maintain is limited (the current limit is 3). Traps are usually assigned on a first come, first served basis, with later trap requestors being denied service. This flag modifies the assignment algorithm by allowing low priority traps to be overridden by later requests for normal priority traps. 

<code>nomodify</code>

: Deny <code>ntpq</code> and <code>ntpdc</code> queries which attempt to modify the state of the server (i.e., run time reconfiguration). Queries which return information are permitted.

<code>noquery</code>

: Deny <code>ntpq</code> and <code>ntpdc</code> queries. Time service is not affected.

<code>nopeer</code>

: Deny packets which would result in mobilizing a new association.  This includes broadcast, symmetric-active and manycast client packets when a configured association does not exist. 

<code>noserve</code>

: Deny all packets except <code>ntpq</code> and <code>ntpdc</code> queries.

<code>notrap</code>

: Decline to provide mode 6 control message trap service to matching hosts. The trap service is a subsystem of the <code>ntpdc</code> control message protocol which is intended for use by remote event logging programs.

<code>notrust</code>

: Deny packets unless the packet is cryptographically authenticated. 

<code>ntpport</code>
: <code>non-ntpport</code>

: This is actually a match algorithm modifier, rather than a restriction flag. Its presence causes the restriction entry to be matched only if the source port in the packet is the standard NTP UDP port (123). Both <code>ntpport</code> and <code>non-ntpport</code> may be specified. The <code>ntpport</code> is considered more specific and is sorted later in the list.

<code>version</code>

: Deny packets that do not match the current NTP version.

Default restriction list entries with the flags <code>ignore, interface, ntpport</code>, for each of the local host's interface addresses are inserted into the table at startup to prevent the server from attempting to synchronize to its own time. A default entry is also always present, though if it is otherwise unconfigured; no flags are associated with the default entry (i.e., everything besides your own NTP server is unrestricted).