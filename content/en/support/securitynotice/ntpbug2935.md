---
title: "NTP BUG 2935: Deja Vu: Replay attack on authenticated broadcast mode"
description: "If an NTP network is configured for broadcast operations, then either a man-in-the-middle attacker or a malicious participant that has the same trusted keys as the victim can replay time packets. This bug was resolved in NTP 4.2.8p6."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2935">Bug 2935</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7973">CVE-2015-7973</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:A/AC:M/Au:N/C:N/I:P/A:P)">AV:A/AC:M/Au:N/C:N/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If an NTP network is configured for broadcast operations, then either a man-in-the-middle attacker or a malicious participant that has the same trusted keys as the victim can replay time packets.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to [4.2.8p6 or later](https://downloads.nwtime.org/ntp/4.2.8/).
* If you are unable to upgrade:
  * Don't use broadcast mode if you cannot monitor your client servers.
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by [Aanchal Malhotra](mailto:aanchal4@bu.edu) of Boston University.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco