---
title: "NTP BUG 2956: Small-step/big-step"
type: archives
date: "2016-01-07"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p5-release-announcement">4.2.8p5</a></td>
		<td>07 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2956">Bug 2956</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-5300">CVE-2015-5300</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p5,<br> and 4.3.0 up to, but not including 4.3.78.</td>
		<td>Resolved in 4.2.8p5.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.0</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:C/C:L/I:N/A:L">AV:N/AC:H/PR:H/UI:R/S:C/C:L/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is always started with the `-g` option, which is common and against long-standing recommendation, and if at the moment `ntpd` is restarted an attacker can immediately respond to enough requests from enough sources trusted by the target, which is difficult and not common, there is a window of opportunity where the attacker can cause `ntpd` to set the time to an arbitrary value. Similarly, if an attacker is able to respond to enough requests from enough sources trusted by the target, the attacker can cause `ntpd` to abort and restart, at which point it can tell the target to set the time to an arbitrary value if and only if `ntpd` was re-started against long-standing recommendation with the `-g` flag, or if `ntpd` was not given the `-g` flag, the attacker can move the target system's time by at most 900 seconds' time per attack. 

* * *
    
#### Mitigation

* Configure `ntpd` to get time from multiple sources.
* Upgrade to [4.2.8p5 or later.](/downloads)
* As we've long documented, only use the `-g` option to `ntpd` in cold-start situations.
* Monitor your `ntpd` instances.

* * *

#### Credit

This weakness was discovered by Aanchal Malhotra, Isaac E. Cohen, and Sharon Goldberg at Boston University.

* * *

#### Timeline

* 2016 Jan 7: Public release
* 2016 Jan 4: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Oct 16: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Oct 8: Initial notification; analysis begins