---
title: "NTP BUG 3412: ctl_getitem(): buffer read overrun leads to undefined behavior and information leak"
description: "A malicious mode 6 packet can be sent to an ntpd instance, and if the ntpd instance is from 4.2.8p6 thru 4.2.8p10, that will cause ctl_getitem() to read past the end of its buffer. This bug was resolved in NTP 4.2.8p11."
type: archives
date: "2018-02-27"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p11-release-announcement/">4.2.8p11</a></td>
		<td>27 Feb 2018</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3412">Bug 3412</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-7182">CVE-2018-7182</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p6, up to but not including ntp-4.2.8p11.</td>
		<td>Resolved in 4.2.8p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>INFO 0.0 - MED 5.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:L/Au:N/C:P/I:N/A:N)">AV:N/AC:L/Au:N/C:P/I:N/A:N 0.0 if C:N </a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>NONE 0.0 - MED 5.3</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:L/I:N/A:N">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:L/I:N/A:N 0.0 if C:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ctl_getitem()` is used by ntpd to process incoming mode 6 packets. A malicious mode 6 packet can be sent to an `ntpd` instance, and if the `ntpd` instance is from 4.2.8p6 thru 4.2.8p10, that will cause `ctl_getitem()` to read past the end of its buffer.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [ntp-4.2.8p11 or later](/downloads/).
* Have enough sources of time.
* Properly monitor your `ntpd` instances.
* If `ntpd` stops running, auto-restart it without `-g`. 

* * *

#### Credit

This weakness was discovered by Yihan Lian of Qihoo 360.

* * *

#### Timeline

* 2018 Feb 27: Public release
* 2018 Feb 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2018 Jan 23: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Notification from reporter