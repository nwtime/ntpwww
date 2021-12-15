---
title: "NTP BUG 2781: Authentication doesn't protect symmetric associations against DoS attacks"
type: archives
date: "2015-04-07"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p2-release-announcement">4.2.8p2</a></td>
		<td>07 Apr 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2781">Bug 2781</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-1799">CVE-2015-1799</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP releases starting with at least xntp3.3wy up to but not including ntp-4.2.8p2<br> where the installation uses symmetric key authentication.</td>
		<td>Resolved in 4.2.8p2.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>could be 4.3 or lower, and it could be higher than 5.4</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:A/AC:M/Au:N/C:P/I:P/A:P)">AV:A/AC:M/Au:N/C:P/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

An attacker knowing that NTP hosts A and B are peering with each other (symmetric association) can send a packet to host A with source address of B which will set the NTP state variables on A to the values sent by the attacker. Host A will then send on its next poll to B a packet with originate timestamp that doesn't match the transmit timestamp of B and the packet will be dropped. If the attacker does this periodically for both hosts, they won't be able to synchronize to each other. This is a known denial-of-service attack, described in [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire).

According to the document the NTP authentication is supposed to protect symmetric associations against this attack, but that doesn't seem to be the case. The state variables are updated even when authentication fails and the peers are sending packets with originate timestamps that don't match the transmit timestamps on the receiving side.

This seems to be a very old problem, dating back to at least xntp3.3wy. It's also in the NTPv3 [(RFC 1305)](/reflib/rfc/rfc1305/rfc1305b.pdf) and NTPv4 [(RFC 5905)](/reflib/rfc/rfc5905.txt)) specifications, so other NTP implementations with support for symmetric associations and authentication may be vulnerable too. An update to the NTP RFC to correct this error is in-process. 

* * *
    
#### Mitigation

* Upgrade to [4.2.8p2 or later.](/downloads)
* Note that for users of autokey, this specific style of MITM attack is simply a long-known potential problem. 
* Configure `ntpd` with appropriate time sources and monitor `ntpd`. Alert your staff if problems are detected.

* * *

#### Credit

This issue was discovered by Miroslav Lichvar, of Red Hat.

* * *

#### Timeline

* 2015 Apr 7: Public release
* 2015 Mar 22: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Mar 15: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Mar 6: Initial notification received; analysis begins