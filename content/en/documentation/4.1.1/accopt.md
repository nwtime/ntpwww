---
title: "Access Control Options"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/pogo6.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

The skunk watches for intruders and sprays.

* * *

#### Table of Contents

*  [Access Control Support](/documentation/4.1.1/accopt/#access-control-support)
*  [The Kiss-of-Death Packet](/documentation/4.1.1/accopt/#the-kiss-of-death-packet)
*  [Access Control Commands](/documentation/4.1.1/accopt/#access-control-commands)

* * *

#### Access Control Support

<code>ntpd</code> implements a general purpose address-and-mask based restriction list. The list is sorted by address and by mask, and the list is searched in this order for matches, with the last match found defining the restriction flags associated with the incoming packets. The source address of incoming packets is used for the match, with the 32- bit address being and'ed with the mask associated with the restriction entry and then compared with the entry's address (which has also been and'ed with the mask) to look for a match. Additional information and examples can be found in the  [Notes on Configuring NTP and Setting up a NTP Subnet](/documentation/4.1.1/notes/) page. 

The restriction facility was implemented in conformance with the access policies for the original NSFnet backbone time servers. While this facility may be otherwise useful for keeping unwanted or broken remote time servers from affecting your own, it should not be considered an alternative to the standard NTP authentication facility. Source address based restrictions are easily circumvented by a determined cracker.

* * *

#### The Kiss-of-Death Packet

Ordinarily, packets denied service are simply dropped with no further action except incrementing statistics counters. Sometimes a more proactive response is needed, such as a server message that explicitly requests the client to stop sending and leave a message for the system operator. A special packet format has been created for this purpose called the kiss-of-death packet. If the <code>kod</code> flag is set and either service is denied or the client limit is exceeded, the server it returns the packet and sets the leap bits unsynchronized, stratum zero and the ASCII string "DENY" in the reference source identifier field. If the <code>kod</code> flag is not set, the server simply drops the packet.

A client or peer receiving a kiss-of-death packet performs a set of sanity checks to minimize security exposure. If this is the first packet received from the server, the client assumes an access denied condition at the server. It updates the stratum and reference identifier peer variables and sets the access denied (test 4) bit in the peer flash variable. If this bit is set, the client sends no packets to the server. If this is not the first packet, the client assumes a client limit condition at the server, but does not update the peer variables. In either case, a message is sent to the system log.

* * *

#### Access Control Commands

<code>**_numeric_address_ [mask _numeric_mask_] [_flag_][...]**</code>

: The <code>_numeric_address_</code> argument, expressed in dotted-quad form, is the address of an host or network. The <code>mask</code> argument, also expressed in dotted-quad form, defaults to <code>255.255.255.255</code>, meaning that the <code>numeric_address</code> is treated as the address of an individual host. A default entry (address <code>0.0.0.0</code>, mask <code>0.0.0.0</code>) is always included and, given the sort algorithm, is always the first entry in the list.
> Note that, while <code>numeric_address</code> is normally given in dotted-quad format, the text string <code>default</code>, with no mask option, may be used to indicate the default entry.

In the current implementation, <code>flag</code> always restricts access, i.e., an entry with no flags indicates that free access to the server is to be given. The flags are not orthogonal, in that more restrictive flags will often make less restrictive ones redundant. The flags can generally be classed into two catagories, those which restrict time service and those which restrict informational queries and attempts to do run-time reconfiguration of the server. One or more of the following flags may be specified: 

<code>kod</code>

: If access is denied, send a kiss-of-death packet.

<code>ignore</code>

: Ignore all packets from hosts which match this entry. If this flag is specified neither queries nor time server polls will be responded to.

<code>noquery</code>

: Ignore all NTP mode 6 and 7 packets (i.e. information queries and configuration requests) from the source. Time service is not affected.

<code>nomodify</code>

: Ignore all NTP mode 6 and 7 packets which attempt to modify the state of the server (i.e. run time reconfiguration). Queries which return information are permitted.

<code>notrap</code>

: Decline to provide mode 6 control message trap service to matching hosts. The trap service is a subsystem of the mode 6 control message protocol which is intended for use by remote event logging programs.

<code>lowpriotrap</code>

: Declare traps set by matching hosts to be low priority. The number of traps a server can maintain is limited (the current limit is 3). Traps are usually assigned on a first come, first served basis, with later trap requestors being denied service. This flag modifies the assignment algorithm by allowing low priority traps to be overridden by later requests for normal priority traps.

<code>noserve</code>

: Ignore NTP packets whose mode is other than 6 or 7. In effect, time service is denied, though queries may still be permitted.

<code>nopeer</code>

: Provide stateless time service to polling hosts, but do not allocate peer memory resources to these hosts even if they otherwise might be considered useful as future synchronization partners.

<code>notrust</code>

: Treat these hosts normally in other respects, but never use them as synchronization sources. 

<code>limited</code>

: These hosts are subject to limitation of number of clients from the same net. Net in this context refers to the IP notion of net (class A, class B, class C, etc.). Only the first <code>client_limit</code> hosts that have shown up at the server and that have been active during the last <code>client_limit_period</code> seconds are accepted. Requests from other clients from the same net are rejected. Only time request packets are taken into account. Query packets sent by the <code>ntpq</code> and <code>ntpdc</code> programs are not subject to these limits. A history of clients is kept using the monitoring capability of <code>ntpd</code>. Thus, monitoring is always active as long as there is a restriction entry with the <code>limited</code> flag.

<code>ntpport</code>

: This is actually a match algorithm modifier, rather than a restriction flag. Its presence causes the restriction entry to be matched only if the source port in the packet is the standard NTP UDP port (123). Both <code>ntpport</code> and <code>non-ntpport</code> may be specified. The <code>ntpport</code> is considered more specific and is sorted later in the list.

<code>version</code>

: Ignore these hosts if not the current NTP version.

Default restriction list entries with the flags <code>ignore, interface, ntpport</code>, for each of the local host's interface addresses are inserted into the table at startup to prevent the server from attempting to synchronize to its own time. A default entry is also always present, though if it is otherwise unconfigured; no flags are associated with the default entry (i.e., everything besides your own NTP server is unrestricted).

<code>**clientlimit _limit_**</code>

: Set the <code>client_limit</code> variable, which limits the number of simultaneous access-controlled clients. The default value for this variable is 3.

<code>**clientperiod _period_**</code>

: Set the <code>client_limit_period</code> variable, which specifies the number of seconds after which a client is considered inactive and thus no longer is counted for client limit restriction. The default value for this variable is 3600 seconds.