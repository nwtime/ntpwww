---
title: "NTP BUG 2922: decodenetnum() will ASSERT botch instead of returning FAIL on some bogus values"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2922">Bug 2922</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7855">CVE-2015-7855</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.6</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C</a></br> Base Score: 4.6, worst case</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is fed a crafted mode 6 or mode 7 packet containing an unusually long data value where a network address is expected, the `decodenetnum()` function will abort with an assertion failure instead of simply returning a failure condition.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info)
* Upgrade to [4.2.8p4 or later](/downloads).
* If you are unable to upgrade:
  * mode 7 is disabled by default. Don't enable it.
  * Use `restrict noquery` to limit who can send mode 6 and mode 7 requests.
  * Configure and use the `controlkey` and `requestkey` authentication directives to limit who can send mode 6 and mode 7 requests.
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by John D "Doug" Birdwell with the Institute for Defense Analyses (IDA.org).

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits) for [1593](https://bugs.ntp.org/show_bug.cgi?id=1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899), and [2902](/support/securitynotice/ntpbug2902)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899); analysis begins