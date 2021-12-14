---
title: "NTP BUG 2940: Stack exhaustion in recursive traversal of restriction list"
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2940">Bug 2940</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7978">CVE-2015-7978</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.3</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:M/Au:N/C:N/I:N/A:P)">AV:N/AC:M/Au:N/C:N/I:N/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

An unauthenticated `ntpdc reslist` command can cause a segmentation fault in `ntpd` by exhausting the call stack.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info)
* Upgrade to 4.2.8p6 or later.](/downloads)
* If you are unable to upgrade:
  * In ntp-4.2.8, mode 7 is disabled by default. Don't enable it.
  * If you must enable mode 7:
    * configure the use of a `requestkey` to control who can issue mode 7 requests.
    * configure `restrict noquery` to further limit mode 7 requests to trusted sources. 

* Monitor your `ntpd` instances.

* * *

#### Credit

This weakness was discovered by [Stephen Gray](mailto:stepgray@cisco.com) of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Oct 16: Initial notification from Cisco