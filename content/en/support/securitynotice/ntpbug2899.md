---
title: "NTP BUG 2899: Incomplete autokey data packet length checks"
type: archives
date: "2015-10-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p4-release-announcement">4.2.8p4</a></td>
		<td>21 Oct 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2899">Bug 2899</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7691">CVE-2015-7691</a><br> <a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7692">CVE-2015-7692</a><br> <a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7702">CVE-2015-7702</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.6</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Incorrect patch for [2671](/support/securitynotice/ntpbug2671), in `crypto_xmit()`. Missing length checks for autokey with GQ identity scheme.

The fix for [CVE-2014-9750](https://nvd.nist.gov/vuln/detail/CVE-2014-9750) was incomplete in that there were certain code paths where a packet with particular autokey operations that contained malicious data was not always being completely validated. Receipt of these packets can cause `ntpd` to crash.

* * *
    
#### Mitigation

* Don't use autokey.
* Upgrade to [4.2.8p4 or later](/downloads).
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Tenable Network Security.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits) for [1593](https://bugs.ntp.org/show_bug.cgi?id=1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899), and [2902](/support/securitynotice/ntpbug2902)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899); analysis begins