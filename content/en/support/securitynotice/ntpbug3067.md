---
title: "NTP BUG 3067: Fix for bug 2085 broke initial sync calculations"
type: archives
date: "2016-11-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p9-release-announcement/">4.2.8p9</a></td>
		<td>21 Nov 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3067">Bug 3067</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-7433">CVE-2016-7433</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.7p385, up to but not including ntp-4.2.8p9, and ntp-4.3.0 up to, but not including ntp-4.3.94. But the root-distance calculation in general is incorrect in all versions of ntp-4 until this release.</td>
		<td>Resolved in 4.2.8p9.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 1.2</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:N/C:N/I:N/A:P)">AV:L/AC:H/Au:N/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 1.6</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:P/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:L">CVSS:3.0/AV:P/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

[Bug 2085](https://bugs.ntp.org/show_bug.cgi?id=2085) described a condition where the root delay was included twice, causing the jitter value to be higher than expected. Due to a misinterpretation of a small-print variable in The Book, the fix for this problem was incorrect, resulting in a root distance that did not include the peer dispersion. The calculations and formulae have been reviewed and reconciled, and the code has been updated accordingly.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p9 or later](/downloads/).
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered independently by Brian Utterback of Oracle, and Sharon Goldberg and Aanchal Malhotra of Boston University.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received