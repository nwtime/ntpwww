---
title: "NTP BUG 2672: ::1 can be spoofed on some OSes, so ACLs based on IPv6 ::1 addresses can be bypassed"
description: "Some kernels do not prevent ::1 source addresses from appearing on non-localhost IPv6 interfaces. Since NTP’s access control is based on source address and localhost addresses generally have no restrictions, an attacker can send malicious control and configuration packets by spoofing ::1 addresses from the outside. This bug was resolved in NTP 4.2.8p1."
type: archives
date: "2015-02-04"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p1-release-announcement/">4.2.8p1</a></td>
		<td>04 Feb 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2672">Bug 2672</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2014-9751">CVE-2014-9751</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases before 4.2.8p1, under at least some versions of MacOS and Linux.<br> *BSD has not been seen to be vulnerable.</td>
		<td>Resolved in 4.2.8p1.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>9</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:L/Au:N/C:P/I:P/A:C)">AV:N/AC:L/Au:N/C:P/I:P/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

While available kernels will prevent 127.0.0.1 addresses from "appearing" on non-localhost IPv4 interfaces, some kernels do not offer the same protection for ::1 source addresses on IPv6 interfaces. Since NTP's access control is based on source address and localhost addresses generally have no restrictions, an attacker can send malicious control and configuration packets by spoofing ::1 addresses from the outside. 

> **NOTE:** This is not really a bug in NTP, it's a problem with some OSes. If you have one of these OSes where ::1 can be spoofed, ALL ::1 -based ACL restrictions on any application can be bypassed!

* * *
    
#### Mitigation

* Upgrade to [4.2.8p1 or later](/downloads/).
*  Install firewall rules to block packets claiming to come from ::1 from inappropriate network interfaces.

* * *

#### Credit

This vulnerability was discovered by Stephen Roettger of the Google Security Team.

* * *

#### Timeline

* 2015 Feb 4: Public release
* : [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Initial notification received; analysis begins