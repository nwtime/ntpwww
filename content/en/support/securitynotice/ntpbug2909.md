---
title: "NTP BUG 2909: Slow memory leak in CRYPTO_ASSOC"
type: archives
date: "2015-10-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p4-release-announcement/">4.2.8p4</a></td>
		<td>21 Oct 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2909">Bug 2909</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7701">CVE-2015-7701</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases that use autokey up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>0.0 best/usual case, 4.6 otherwise</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is configured to use autokey, then an attacker can send packets to `ntpd` that will, after several days of ongoing attack, cause it to run out of memory. 

* * *
    
#### Mitigation

* Don't use autokey.
* Upgrade to [4.2.8p4 or later](/downloads/).
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Tenable Network Security.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/) for [1593](/support/securitynotice/ntpbug1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899/), and [2902](/support/securitynotice/ntpbug2902/)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902/); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899/); analysis begins