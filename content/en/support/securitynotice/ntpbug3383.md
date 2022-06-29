---
title: "NTP BUG 3383: Stack Buffer Overflow from Command Line (WINDOWS installer ONLY)"
description: "The Windows installer for NTP calls strcat(), blindly appending the string passed to the stack buffer in the addSourceToRegistry() function. Together with the initially copied Registry path, the combination causes a stack buffer overflow and effectively overwrites the stack frame. This bug was resolved in NTP 4.2.8p10."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3383">Bug 3383</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6452">CVE-2017-6452</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>Windows installer ONLY: All versions of the ntp-4 Windows installer, up to<br> but not including ntp-4.2.8p10, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 1.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:S/C:N/I:N/A:P)">AV:L/AC:H/Au:S/C:N/I:N/A:P</a></td>
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

The Windows installer for NTP calls `strcat()`, blindly appending the string passed to the stack buffer in the `addSourceToRegistry()` function. The stack buffer is 70 bytes smaller than the buffer in the calling `main()` function. Together with the initially copied Registry path, the combination causes a stack buffer overflow and effectively overwrites the stack frame. The passed application path is actually limited to 256 bytes by the operating system, but this is not sufficient to assure that the affected stack buffer is consistently protected against overflowing at all times.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p10 or later.](/downloads/)

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received