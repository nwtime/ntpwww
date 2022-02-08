---
title: "NTP BUG 2920: Invalid length data provided by a custom refclock driver could cause a buffer overflow"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2920">Bug 2920</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7853">CVE-2015-7853</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>Potentially all ntp-4 releases running up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77 that have custom refclocks.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>0.0 usual case, 5.9 unusual worst case</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:L/AC:H/Au:M/C:C/I:C/A:C)">AV:L/AC:H/Au:M/C:C/I:C/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

A negative value for the `datalen` parameter will overflow a data buffer. NTF's `ntpd` driver implementations always set this value to 0 and are therefore not vulnerable to this weakness. If you are running a custom refclock driver in `ntpd` and that driver supplies a negative value for `datalen` (no custom driver of even minimal competence would do this) then `ntpd` would overflow a data buffer. It is even hypothetically possible in this case that instead of simply crashing `ntpd` the attacker could effect a code injection attack.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p4 or later](/downloads).
* If you are unable to upgrade:
  *  If you are running custom refclock drivers, make sure the signed `datalen` value is either zero or positive.
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Yves Younan of Cisco Talos.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits) for [1593](https://bugs.ntp.org/show_bug.cgi?id=1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899), and [2902](/support/securitynotice/ntpbug2902)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899); analysis begins