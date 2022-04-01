---
title: "NTP BUG 1774: ntpd segfaults if cryptostats enabled when built without OpenSSL"
type: archives
date: "2015-10-23"
sitemap_exclude: true
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td>4.2.7p112 (Development)<br> <a href="/support/securitynotice/4_2_8-release-announcement/">4.2.8</a></td>
		<td>18 Aug 2010<br> 19 Dec 2014</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=1774">Bug 1774</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-5195">CVE-2015-5195</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to and including 4.2.7p111.</td>
		<td>Resolved in 4.2.8.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>1.7 (worst case)</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:P)">AV:N/AC:H/Au:M/C:N/I:N/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is not built with OpenSSL cryptography and `ntpd` is told to configure cryptography statistics, `ntpd` will crash.

* * *
    
#### Mitigation

* Don't specify cryptography statistics directives in unpatched releases of `ntpd` if your `ntpd` doesn't support cryptography.
* Upgrade to [4.2.8p4 or later](/downloads).
* Monitor your `ntpd` instances. 

* * *

#### Credit

This issue was tracked down by Steve Kostecke in 2011.