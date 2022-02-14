---
title: "NTP BUG 2671: vallen is not validated in several places in ntp_crypto.c, leading to a potential info leak or possibly crashing ntpd"
type: archives
date: "2015-02-04"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p1-release-announcement/">4.2.8p1</a></td>
		<td>04 Feb 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2671">Bug 2671</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2014-9750/">CVE-2014-9750</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases before 4.2.8p1 that are running autokey.</td>
		<td>Resolved in 4.2.8p1.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>7.5</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:L/Au:N/C:P/I:P/A:P)">AV:N/AC:L/Au:N/C:P/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The `vallen` packet value is not validated in several code paths in `ntp_crypto.c` which can lead to information leakage or a possible crash of `ntpd`.

* * *
    
#### Mitigation

Any of:

* Upgrade to [4.2.8p1 or later](/downloads/).
* Disable Autokey Authentication by removing, or commenting out, all configuration directives beginning with the `crypto` keyword in your `ntp.conf` file. 

* * *

#### Credit

This vulnerability was discovered by Stephen Roettger of the Google Security Team, with additional cases found by Sebastian Krahmer of the SUSE Security Team and Harlan Stenn of Network Time Foundation.

* * *

#### Timeline

* 2015 Feb 4: Public release
* : [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Initial notification received; analysis begins