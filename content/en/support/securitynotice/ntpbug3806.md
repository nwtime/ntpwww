---
title: "NTP BUG 3806: mstolfp() needs bounds checking"
description: "This vulnerability only affects ntpq and does NOT affect ntpd."
#date: "2023-05-30"
type: archives
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td>4.2.8p16</td>
		<td>30 May 2023</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/3806">Bug 3806</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2023-26551">CVE-2023-26551</a><br><a href="https://nvd.nist.gov/vuln/detail/CVE-2023-26552">CVE-2023-26552</a><br><a href="https://nvd.nist.gov/vuln/detail/CVE-2023-26553">CVE-2023-26553</a><br><a href="https://nvd.nist.gov/vuln/detail/CVE-2023-26554">CVE-2023-26554</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-3 (and likely earlier) up to, but not including ntp-4.2.8p16.</td>
		<td>Resolved in ntp-4.2.8p16.</td>
	</tr>
	<tr>
		<th><b>CVSS3.1 Score<br> between<b></th>
		<td>2.0 Low</td>
		<td><a href="https://www.first.org/cvss/calculator/3.1#CVSS:3.1/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L">CVSS:3.1/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L</a> (likely)</td><br>
	</tr>
	<tr>
	    <th><b>and:</b></th>
		<td>3.9 Low</td>
		<td><a href="https://www.first.org/cvss/calculator/3.1#CVSS:3.1/AV:N/AC:H/PR:H/UI:R/S:U/C:L/I:L/A:L"> CVSS:3.1/AV:N/AC:H/PR:H/UI:R/S:U/C:L/I:L/A:L</a> (improbable)</td> 
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

This vulnerability only affects `ntpq` and does **NOT** affect `ntpd`. This vulnerability could have been reported via a single CVE. `ntpq` makes requests of a target `ntpd` from a short-lived random high port and displays the results to the user. An attacker can send a crafted response if they either control the queried `ntpd` or become a "man-in-the-middle" (MITM) on the network path. This crafted response causes a buffer overflow in the victim's `ntpq` client if it consists of a long ASCII character string that matches the pattern: `[+-]DIGIT*[.]DIGIT*`.

* * *
    
#### Mitigation

* Use `ntpq -c raw ...` .
* Apply the [patch](https://archive.ntp.org/ntp4/ntp-4.2.8p15-3806-3807.patch) to 4.2.8p15 (or earlier, perhaps with some modifications), and build and install `ntpq`.
* Upgrade to 4.2.8p16, or later, from the [NTP Project download site](/downloads/). 

* * *

#### Credit

Reported by "spwpun".

* * *

#### Timeline

* 2023 May 30: Public release
* 2023 May 12: Public hotfix release
* 2023 May 10: Hotfix release to [Advance Security Partners: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2023 Apr 14: Public notification