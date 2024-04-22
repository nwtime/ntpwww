---
title: "NTP BUG 2937: nextvar() missing length check in ntpq"
description: "ntpq may call nextvar() which executes a memcpy() into the name buffer without a proper length check against its maximum length of 256 bytes. This bug was resolved in NTP 4.2.8p6."
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement/">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2937">Bug 2937</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7975">CVE-2015-7975</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>1.2</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:N/C:N/I:N/A:P)">AV:L/AC:H/Au:N/C:N/I:N/A:P</a><br> If you score A:C, this becomes 4.0.</td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 2.9</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:L/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:L">CVSS:3.0/AV:L/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpq` may call `nextvar()` which executes a `memcpy()` into the name buffer without a proper length check against its maximum length of 256 bytes. Note well that we're taking about `ntpq` here. The usual worst-case effect of this vulnerability is that the specific instance of `ntpq` will crash and the person or process that did this will have stopped themselves.

* * *
    
#### Mitigation

* Upgrade to 4.2.8p6 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* If you are unable to upgrade:
  * If you have scripts that feed input to `ntpq` make sure there are some sanity checks on the input received from the "outside".
  * This is potentially more dangerous if `ntpq` is run as root. 

* * *

#### Credit

This weakness was discovered by [Jonathan Gardner](mailto:jonagard@cisco.com) of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco