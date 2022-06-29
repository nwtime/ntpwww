---
title: "NTP BUG 3071: Client rate limiting and server responses"
description: "An attacker who knows a system is misconfigured with rate limiting for all associations can periodically send packets with a spoofed source address to keep the rate limiting activated and prevent ntpd from accepting valid responses from its sources. This bug was resolved in NTP 4.2.8p9."
type: archives
date: "2016-11-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p9-release-announcement/">4.2.8p9</a></td>
		<td>21 Nov 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3071">Bug 3071</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-7426">CVE-2016-7426</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.5p203, up to but not including ntp-4.2.8p9,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p9</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 1.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:S/C:N/I:N/A:P)">AV:L/AC:H/Au:S/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 1.6</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:P/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L">CVSS:3.0/AV:P/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

When `ntpd` is configured with rate limiting for all associations (`restrict default limited` in `ntp.conf`), the limits are applied also to responses received from its configured sources. An attacker who knows the sources (e.g., from an IPv4 `refid` in server response) and knows the system is (mis)configured in this way can periodically send packets with spoofed source address to keep the rate limiting activated and prevent `ntpd` from accepting valid responses from its sources.

While this blanket rate limiting can be useful to prevent brute-force attacks on the origin timestamp, it allows this DoS attack. Similarly, it allows the attacker to prevent mobilization of ephemeral associations.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page) 
* If you choose to use `restrict default limited ...`, be sure to use `restrict source ...` (without `limited`) to avoid this attack.
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Miroslav Lichvar of Red Hat.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received