---
title: "NTP BUG 3384: Privileged execution of User Library code (WINDOWS PPSAPI ONLY)"
description: "Depending on how securely the Windows NT system is setup and configured, if ntpd is configured to use the PPSAPI under Windows this can easily lead to a code injection. This bug was resolved in NTP 4.2.8p10."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3384">Bug 3384</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6455">CVE-2017-6455</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All Windows versions of ntp-4 that use the PPSAPI, up to but not including<br> ntp-4.2.8p10, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 3.8</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:S/C:N/I:N/A:C)">AV:L/AC:H/Au:S/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 4.0</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:L/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H">CVSS:3.0/AV:L/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The Windows NT port has the added capability to preload DLLs defined in the inherited global local environment variable `PPSAPI_DLLS`. The code contained within those libraries is then called from the NTPD service, usually running with elevated privileges. Depending on how securely the machine is setup and configured, if `ntpd` is configured to use the PPSAPI under Windows this can easily lead to a code injection. 

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p10 or later.](https://downloads.nwtime.org/ntp/4.2.8/)

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received