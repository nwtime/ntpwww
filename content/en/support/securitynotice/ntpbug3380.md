---
title: "NTP BUG 3380: Off-by-one in Oncore GPS Receiver"
description: "There is a fencepost error in a recovery branch of the code for the Oncore GPS receiver if the communication link to the ONCORE is weak or distorted and the decoding doesn’t work. This bug was resolved in NTP 4.2.8p10."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3380">Bug 3380</a></td>
		<td></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of NTP, up to but not including ntp-4.2.8p10,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>NONE 0.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:N/C:N/I:N/A:N)">AV:L/AC:H/Au:N/C:N/I:N/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>NONE 0.0</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:L/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:N">CVSS:3.0/AV:L/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

There is a fencepost error in a "recovery branch" of the code for the Oncore GPS receiver if the communication link to the ONCORE is weak / distorted and the decoding doesn't work. 

* * *
    
#### Mitigation

* Upgrade to [4.2.8p10 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received