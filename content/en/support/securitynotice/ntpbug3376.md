---
title: "NTP BUG 3376: Makefile does not enforce Security Flags"
type: archives
date: "2017-03-21"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3376">Bug 3376</a></td>
		<td></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of NTP, up to but not including ntp-4.2.8p10, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>N/A</td>
		<td></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>N/A</td>
		<td></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The build process for NTP has not, by default, provided compile or link flags to offer "hardened" security options. Package maintainers have always been able to provide hardening security flags for their builds. As of ntp-4.2.8p10, the NTP build system has a way to provide OS-specific hardening flags. Please note that this is still not a really great solution because it is specific to NTP builds. It's inefficient to have every package supply, track and maintain this information for every target build. It would be much better if there was a common way for OSes to provide this information in a way that arbitrary packages could benefit from it. 

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info)
* Upgrade to [4.2.8p10 or later.](/downloads) 
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running.

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2017 Feb 09: Mozilla/Cure53 audit received