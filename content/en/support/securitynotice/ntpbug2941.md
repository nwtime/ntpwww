---
title: "NTP BUG 2941: NAK to the Future: Symmetric association authentication bypass via crypto-NAK"
type: archives
date: "2015-10-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p4-release-announcement/">4.2.8p4.md</a></td>
		<td>21 Oct 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2941">Bug 2941</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7871">CVE-2015-7871</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases between 4.2.5p186 up to but not including 4.2.8p4,<br> and 4.3.0 up to but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>6.4</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:L/Au:N/C:N/I:P/A:P)">AV:N/AC:L/Au:N/C:N/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Crypto-NAK packets can be used to cause `ntpd` to accept time from unauthenticated ephemeral symmetric peers by bypassing the authentication required to mobilize peer associations. This vulnerability appears to have been introduced in ntp-4.2.5p186 when the code handling mobilization of new passive symmetric associations (lines 1103-1165) was refactored.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to [4.2.8p4 or later](/downloads/).
* If you are unable to upgrade:
  * Apply the patch to the bottom of the `authentic` check block around line 1136 of `ntp_proto.c`. 
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by [Matthew Van Gundy](mailto:mvangund@cisco.com) of Cisco ASIG.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/) for [1593](/support/securitynotice/ntpbug1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899/), and [2902](/support/securitynotice/ntpbug2902/)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902/); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899/); analysis begins