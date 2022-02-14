---
title: "NTP BUG 2942: Off-path Denial of Service (DoS) attack on authenticated broadcast mode"
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement/">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2942">Bug 2942</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7979/">CVE-2015-7979</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 5.8</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:M/Au:N/C:N/I:P/A:P)">AV:N/AC:M/Au:N/C:N/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

An off-path attacker can send broadcast packets with bad authentication (wrong key, mismatched key, incorrect MAC, etc) to broadcast clients. It is observed that the broadcast client tears down the association with the broadcast server upon receiving just one bad packet.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to 4.2.8p6 or later.](/downloads/)
* Monitor your `ntpd` instances.
* If this sort of attack is an active problem for you, you have deeper problems to investigate. Also consider having smaller NTP broadcast domains.

* * *

#### Credit

This weakness was discovered by [Aanchal Malhotra](mailto:aanchal4@bu.edu) of Boston University.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco