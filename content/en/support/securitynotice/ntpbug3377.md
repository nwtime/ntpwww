---
title: "NTP BUG 3377: Buffer Overflow in ntpq when fetching reslist from a malicious ntpd"
description: "A stack buffer overflow in ntpq can be triggered by a malicious ntpd server when ntpq requests the restriction list from the server due to a missing length check in the reslist() function. This bug was resolved in NTP 4.2.8p10."
type: archives
date: "2017-03-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p10-release-announcement/">4.2.8p10</a></td>
		<td>21 Mar 2017</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3377">Bug 3377</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6460">CVE-2017-6460</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of <code>ntpq</code>, up to but not including<br> ntp-4.2.8p10, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.9</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:S/C:N/I:N/A:C)">AV:N/AC:H/Au:S/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 4.2</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

A stack buffer overflow in `ntpq` can be triggered by a malicious `ntpd` server when `ntpq` requests the restriction list from the server. This is due to a missing length check in the `reslist()` function. It occurs whenever the function parses the server’s response and encounters a `flagstr` variable of an excessive length. The string will be copied into a fixed-size buffer, leading to an overflow on the function’s stack-frame. 

> Note well that this problem requires a malicious server, and affects `ntpq`, not `ntpd`.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p10 or later.](https://downloads.nwtime.org/ntp/4.2.8/) 
* If you can't upgrade your version of `ntpq` then if you want to know the `reslist` of an instance of `ntpd` that you do not control, know that if the target `ntpd` is malicious that it can send back a response that intends to crash your `ntpq` process.

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received