---
title: "NTP BUG 3378: Improper use of snprintf() in mx4200_send()"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3378">Bug 3378</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6451">CVE-2017-6451</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of NTP, up to but not including ntp-4.2.8p10,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 0.8</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2&vector=(AV:L/AC:H/Au:M/C:N/I:N/A:P)">AV:L/AC:H/Au:M/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 1.8</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:L/AC:H/PR:H/UI:R/S:U/C:N/I:L/A:N">CVSS:3.0/AV:L/AC:H/PR:H/UI:R/S:U/C:N/I:L/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The legacy MX4200 refclock is only built if is specifically enabled, and furthermore additional code changes are required to compile and use it. But it uses the `libc` function `snprintf() / vsnprintf()` incorrectly, which can lead to an out-of-bounds memory write due to an improper handling of the return value of `snprintf() / vsnprintf()`. Since the return value is used as an iterator and it can be larger than the buffer’s size, it is possible for the iterator to point somewhere outside of the allocated buffer space. This results in an out-of-bound memory write. This behavior can be leveraged to overwrite a saved instruction pointer on the stack and gain control over the execution flow. During testing it was not possible to identify any malicious usage for this vulnerability. Specifically, no way for an attacker to exploit this vulnerability was ultimately unveiled. However, it has the potential to be exploited, so the code should be fixed.

* * *
    
#### Mitigation

If you have a Magnavox MX4200 refclock:
* Upgrade to [4.2.8p10 or later.](/downloads/) 
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received