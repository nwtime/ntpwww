---
title: "Access Control Support"
type: archives
---

![gif](/archives/pic/pogo6.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

The skunk watches for intruders and sprays.

Last update: 26-Jul-2017 20:10 UTC

* * *

The <code>ntpd</code> daemon implements a general purpose access control list (ACL) containing address/match entries sorted first by increasing address values and then by increasing mask values. A match occurs when the bitwise AND of the mask and the packet source address is equal to the bitwise AND of the mask and address in the list. The list is searched in order with the last match found defining the restriction flags associated with the entry.

The ACL is specified as a list of <code>restrict</code> commands in the following format:

<code>restrict _address_ [mask _mask_] [_flag_][...]</code>

The <code>_address_</code> argument expressed in dotted-quad form is the address of a host or network. Alternatively, the <code>_address_</code> argument can be a valid host DNS name. The <code>_mask_</code> argument expressed in IPv4 or IPv6 numeric address form defaults to all mask bits on, meaning that the <code>_address_</code> is treated as the address of an individual host. A default entry (address 0.0.0.0, mask 0.0.0.0 for IPv4 and address :: mask :: for IPv6) is always the first entry in the list. <code>restrict default</code>, with no mask option, modifies both IPv4 and IPv6 default entries. <code>restrict source</code> configures a template restriction automatically added at runtime for each association, whether configured, ephemeral, or preemptable, and removed when the association is demobilized.

Some flags have the effect to deny service, some have the effect to enable service and some are conditioned by other flags. The flags are not orthogonal, in that more restrictive flags will often make less restrictive ones redundant. The flags that deny service are classed in two categories, those that restrict time service and those that restrict informational queries and attempts to do run-time reconfiguration of the server.

An example may clarify how it works. Our campus has two class-B networks, 128.4 for the ECE and CIS departments and 128.175 for the rest of campus. Let's assume (not true!) that subnet 128.4.1 homes critical services like class rosters and spread sheets. A suitable ACL might look like this:

<pre>restrict default nopeer			# deny new associations
restrict 128.175.0.0 mask 255.255.0.0 		# allow campus access
restrict 128.4.0.0 mask 255.255.0.0 none	# allow ECE and CIS access
restrict 128.4.1.0 mask 255.255.255.0 notrust   # require authentication on subnet 1
restrict time.nist.gov				# allow access
</pre>

While this facility may be useful for keeping unwanted, broken or malicious clients from congesting innocent servers, it should not be considered an alternative to the NTP authentication facilities. Source address-based restrictions are easily circumvented by a determined cracker.

Default restriction list entries with the flags <code>ignore, ntpport</code>, for each of the local host's interface addresses are inserted into the table at startup to prevent the server from attempting to synchronize to its own time. A default entry is also always present, though if it is otherwise unconfigured; no flags are associated with the default entry (i.e., everything besides your own NTP server is unrestricted).
