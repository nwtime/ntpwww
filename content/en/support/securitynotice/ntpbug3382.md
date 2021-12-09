---
title: "NTP BUG 3382: Data Structure terminated insufficiently (Windows installer ONLY)"
type: archives
date: "2017-02-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p10-release-announcement">4.2.8p10</a></td>
		<td>21 Mar 2017</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3382">Bug 3382</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6459">CVE-2017-6459</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>Windows installer ONLY: All ntp-4 versions of the Windows installer, up to<br> but not including ntp-4.2.8p10, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 1.0</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:L/AC:H/Au:S/C:N/I:N/A:P)">AV:L/AC:H/Au:S/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 1.8</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:L/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L">CVSS:3.0/AV:L/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The Windows installer for NTP calls `strcpy()` with an argument that specifically contains multiple null bytes. `strcpy()` only copies a single terminating null character into the target buffer instead of copying the required double null bytes in the `addKeysToRegistry()` function. As a consequence, a garbage registry entry can be created. The additional `arsize` parameter is erroneously set to contain two null bytes and the following call to `RegSetValueEx()` claims to be passing in a multi-string value, though this may not be true.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p10 or later.](/downloads)

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2017 Feb 09: Mozilla/Cure53 audit received