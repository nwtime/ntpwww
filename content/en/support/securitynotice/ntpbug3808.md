---
title: "NTP BUG 3808: ntpq will abort with an assertion failure if given a malformed RT-11 date"
description: "If ntpq were to receive a date format that hasn't been used in 30 years, it could abort with an assertion failure."
date: "2023-05-30"
type: archives
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p16-release-announcement/">4.2.8p16</a></td>
		<td>30 May 2023</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/3808">Bug 3808</a></td>
		<td></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td><code>ntpq</code> from ntp-4.2.6 up to, but not including ntp-4.2.8p16.</td>
		<td>Resolved in 4.2.8p16.</td>
	</tr>
	<tr>
		<th><b>CVSS3.1 Score:<b></th>
		<td>Unsure - this vulnerability requires conditions that do not seem to exist.</td>
		<td></td>
	</tr>
    <tr>		 
  </tbody>	
</table>

* * *
    
#### Description 

Ancient versions of NTP (pre-dating ntp3, which first came out in June of 1993) used an RT-11 date format for certain limited purposes. This date format hasn't been used in 30 years' time. If `ntpq` were to receive an RT-11 date format with out-of-range values (which has never been reported), then `ntpq` would abort with an assertion failure.

* * *
    
#### Mitigation

* Upgrade to 4.2.8p16, or later, from the [NTP Project download site](/downloads/).

* * *

#### Credit

Reported by Miroslav Lichvar.

* * *

#### Timeline

* 2023 May 30: Public release
* 2023 May 10: Hotfix release to [Advance Security Partners: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2023 May 10: Notification to [Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2023 Apr 20: Notification from reporter