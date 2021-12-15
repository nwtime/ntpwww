---
title: "NTP BUG 2666: non-cryptographic random number generator with weak seed used by ntp-keygen to generate symmetric keys"
type: archives
date: "2011-11-01"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_7p230-release-announcement">4.2.7p230</a></td>
		<td>01 Nov 2011</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2666">Bug 2666</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2014-9294">CVE-2014-9294</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases before 4.2.7p230.</td>
		<td>Resolved in 4.2.7p230.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>7.3</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:L/Au:M/C:P/I:P/A:C)">AV:N/AC:L/Au:M/C:P/I:P/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Prior to ntp-4.2.7p230 `ntp-keygen` used a weak seed to prepare a random number generator that was of good quality back in the late 1990s. The random numbers produced was then used to generate symmetric keys. In ntp-4.2.8 we use a current-technology cryptographic random number generator, either `RAND_bytes` from OpenSSL, or `arc4random()`. 

* * *
    
#### Mitigation

Any of:

* Upgrade to [4.2.7p230 or later](/downloads).
* Put `restrict ... noquery` in your `ntp.conf` file, for non-trusted senders. 

* * *

#### Credit

This vulnerability was discovered in ntp-4.2.6 by Stephen Roettger of the Google Security Team.

* * *

#### Timeline

* 2011 Nov 1: Public release
* XXXX: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* XXXX: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* XXXX: Notification from reporter