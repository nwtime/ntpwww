---
title: "NTP BUG 3008: ctl_getitem() return value not always checked"
type: archives
date: "2016-04-26"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p7-release-announcement">4.2.8p7/</a></td>
		<td>26 Apr 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3008">Bug 3008</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-2519/">CVE-2016-2519</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.9</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:H/Au:S/C:N/I:N/A:C)">AV:N/AC:H/Au:S/C:N/I:N/A:C</a></td>
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

`ntpq` and `ntpdc` can be used to store and retrieve information in `ntpd`. It is possible to store a data value that is larger than the size of the buffer that the `ctl_getitem()` function of `ntpd` uses to report the return value. If the length of the requested data value returned by `ctl_getitem()` is too large, the value `NULL` is returned instead. There are 2 cases where the return value from `ctl_getitem()` was not directly checked to make sure it's not `NULL`, but there are subsequent `INSIST()` checks that make sure the return value is not `NULL`. There are no data values ordinarily stored in `ntpd` that would exceed this buffer length. But if one has permission to store values and one stores a value that is "too large", then `ntpd` will abort if an attempt is made to read that oversized value. 

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info).
* Upgrade to [4.2.8p7 or later.](/downloads/)
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Yihan Lian of the Cloud Security Team, Qihoo 360.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco