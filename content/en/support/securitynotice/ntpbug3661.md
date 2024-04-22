---
title: "NTP BUG 3661: Memory leak with CMAC keys"
description: "Systems that use a CMAC algorithm in ntp.keys will not release a bit of memory on each packet that uses a CMAC keyid, eventually causing ntpd to run out of memory and fail. This bug was resolved in NTP 4.2.8p15."
type: archives
date: "2020-06-23"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p15-release-announcement/">4.2.8p15</a><br> Development (4.3.101)</td>
		<td>23 Jun 2020</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3661">Bug 3661</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2020-15025">CVE-2020-15025</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p11 up to, but not including ntp-4.2.8p15<br>4.3.97 up to, but not including 4.3.101</td>
		<td>Resolved in 4.2.8p15 and 4.3.101</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>6.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:M/Au:S/C:N/I:N/A:C)">AV:N/AC:M/Au:S/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3.1 Score<b></th>
		<td>4.4</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:H&version=3.1">CVSS:3.1/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Systems that use a CMAC algorithm in `ntp.keys` will not release a bit of memory on each packet that uses a CMAC keyid, eventually causing `ntpd` to run out of memory and fail. The [CMAC cleanup](https://bugs.ntp.org/show_bug.cgi?id=3447), part of ntp-4.2.8p11, introduced a bug whereby the CMAC data structure was no longer completely removed.

* * *
    
#### Mitigation

* If you are using ntp-4.2.8p11 through ntp-4.2.8p14 or ntp-4.3.97 through ntp-4.3.100, either don't use CMAC keys, or make sure you have a way to restart `ntpd` if/when it crashes.
* Upgrade to [4.2.8p15 or later](https://downloads.nwtime.org/ntp/4.2.8/).

* * *

#### Credit

Reported by Martin Burnicki of Meinberg.

* * *

#### Timeline

* 2020 Jun 23: Public release
* 2020 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2020 Apr 07: [Advance Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2020 Apr 01: Notification from reporter