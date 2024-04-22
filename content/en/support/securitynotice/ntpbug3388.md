---
title: "NTP BUG 3388: Buffer Overflow in DPTS Clock"
description: "There is a potential for a buffer overflow in the legacy Datum Programmable Time Server refclock driver. This bug was resolved in NTP 4.2.8p10."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3388">Bug 3388</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6462">CVE-2017-6462</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of NTP, up to but not including ntp-4.2.8p10,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
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

There is a potential for a buffer overflow in the legacy Datum Programmable Time Server refclock driver. Here the packets are processed from the `/dev/datum` device and handled in `datum_pts_receive()`. Since an attacker would be required to somehow control a malicious `/dev/datum` device, this does not appear to be a practical attack and renders this issue “Low” in terms of severity.

* * *
    
#### Mitigation

* If you have a Datum reference clock installed and think somebody may maliciously change the device, upgrade to [4.2.8p10 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Properly monitor your `ntpd `instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received 