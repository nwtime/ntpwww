---
title: "NTP BUG 3505: NTPQ/NTPDC: Buffer Overflow in openhost()"
type: archives
date: "2018-08-14"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p12-release-announcement/">4.2.8p12</a></td>
		<td>14 Aug 2018</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3505">Bug 3505</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-12327/">CVE-2018-12327</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p12,<br> and 4.3.0 up to, but not including 4.3.94.</td>
		<td>Resolved in 4.2.8p12 and 4.3.94.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 1.7</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:L/AC:L/Au:S/C:P/I:N/A:N)">AV:L/AC:L/Au:S/C:P/I:N/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 2.8</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:L/AC:L/PR:L/UI:R/S:U/C:N/I:N/A:L">CVSS:3.0/AV:L/AC:L/PR:L/UI:R/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The `openhost()` function used by `ntpq` and `ntpdc` is vulnerable to a buffer overflow. This means that if one is able to provide `ntpq` or `ntpdc` with an excessively large hostname on the command line or a carefully-crafted byte stream, `ntpq` or `ntpdc` will suffer from the usual stack overflow problems.

* * *
    
#### Mitigation

Upgrade to [4.2.8p12 or later.](/downloads/)

* * *

#### Credit

Reported by Fakhri Zulkifli.

* * *

#### Timeline

* 2018 Aug 14: Public release
* 2018 Jul 25: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)