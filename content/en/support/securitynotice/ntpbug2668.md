---
title: "NTP BUG 2668: Buffer overflow in ctl_putdata()"
description: "A remote attacker can send a carefully crafted packet that can overflow a stack buffer and potentially allow malicious code to be executed with the privilege level of the ntpd process. This bug was resolved in NTP 4.2.8."
type: archives
date: "2014-12-18"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8-release-announcement/">4.2.8</a></td>
		<td>18 Dec 2014</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2668">Bug 2668</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2014-9295">CVE-2014-9295</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases before 4.2.8.</td>
		<td>Resolved in 4.2.8.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>7.5</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:L/Au:N/C:P/I:P/A:P)">AV:N/AC:L/Au:N/C:P/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

A remote attacker can send a carefully crafted packet that can overflow a stack buffer and potentially allow malicious code to be executed with the privilege level of the `ntpd` process.

* * *
    
#### Mitigation

Any of:

* Upgrade to [4.2.8 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Put `restrict ... noquery` in your `ntp.conf` file, for non-trusted senders.

* * *

#### Credit

This vulnerability was discovered by Stephen Roettger of the Google Security Team.

* * *

#### Timeline

* 2014 Dec 18: Public release
* : [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Initial notification received; analysis begins