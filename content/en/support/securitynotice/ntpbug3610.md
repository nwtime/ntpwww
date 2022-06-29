---
title: "NTP BUG 3610: process_control() should bail earlier on short packets"
type: archives
description: "Fuzz testing detected that on systems that override the default and enable ntpdc (mode 7) packets, a short packet will cause ntpd to read uninitialized data. This bug was resolved in NTP 4.2.8p14."
date: "2020-03-03"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p14-release-announcement/">4.2.8p14</a></td>
		<td>03 Mar 2020</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3610">Bug 3610</a></td>
		<td></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of ntpd up to, but not including ntp-4.2.8p14 and ntp-4.3.100.</td>
		<td>Resolved in ntp-4.2.8p14 and ntp-4.3.100.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>0.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:L/Au:N/C:N/I:N/A:N)">AV:N/AC:L/Au:N/C:N/I:N/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>0.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:N/A:N">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:N/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Fuzz testing detected that on systems that override the default and enable `ntpdc` (mode 7) packets, a short packet will cause `ntpd` to read uninitialized data. 

* * *
    
#### Mitigation

* Leave mode7 disabled.
* Pay attention to error messages logged by `ntpd`.
* Monitor your `ntpd` instances. 

Upgrade to [4.2.8p14 or later](/downloads/).

* * *

#### Credit

Reported by Philippe Antoine (Catena cyber with oss-fuzz). 

* * *

#### Timeline

* 2020 Mar 03: Public release
* 2020 Feb 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jun 05: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 May 30: Notification from reporter