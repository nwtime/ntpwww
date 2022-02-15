---
title: "NTP BUG 2665: Weak default key in config_auth()"
type: archives
date: "2010-01-28"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/#427p11">4.2.7p11</a></td>
		<td>28 Jan 2010</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2665">Bug 2665</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2014-9293">CVE-2014-9293</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases before 4.2.7p11.</td>
		<td>Resolved in 4.2.7p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>7.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2&vector=(AV:N/AC:L/Au:M/C:P/I:P/A:C)">AV:N/AC:L/Au:M/C:P/I:P/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If no `auth` key is set in the configuration file, `ntpd` would generate a random key on the fly. There were two problems with this: 1) the generated key was 31 bits in size, and 2) it used the (now weak) `ntp_random()` function, which was seeded with a 32 bit value and can only provide 32 bits of entropy. This was sufficient back in the late 1990s when this code was written. Not today.

* * *
    
#### Mitigation

Any of:

* Upgrade to [4.2.7p11 or later](/downloads/).
* Put `restrict ... noquery` in your `ntp.conf file`, for non-trusted senders. 

* * *

#### Credit

This vulnerability was discovered in ntp-4.2.6 by Neel Mehta of the Google Security Team.

* * *

#### Timeline

* 2010 Jan 28: Public release
* XXXX: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: Notification from reporter