---
title: "NTP BUG 3453: Interleaved symmetric mode cannot recover from bad state"
description: "A third-party can inject a packet with a zero-origin timestamp, meaning the sender wants to reset the association, and the transmit timestamp in this bogus packet will be saved as the most recent received timestamp. This bug was resolved in NTP 4.2.8p11."
type: archives
date: "2018-02-27"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p11-release-announcement/">4.2.8p11</a></td>
		<td>27 Feb 2018</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3453">Bug 3453</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-7184">CVE-2018-7184</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td><code>ntpd</code> in ntp-4.2.8p4, up to but not including ntp-4.2.8p11.</td>
		<td>Resolved in 4.2.8p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:M/Au:N/C:P/I:N/A:N)">AV:N/AC:M/Au:N/C:P/I:N/A:N</a><br> Could score between 2.9 and 6.8.</td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 3.1</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:N/A:L">CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:N/A:L</a><br> Could score between 2.6 and 6.0.</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The fix for [NTP Bug 2952](/support/securitynotice/ntpbug2952/) was incomplete, and while it fixed one problem it created another. Specifically, it drops bad packets before updating the "received" timestamp. This means a third-party can inject a packet with a zero-origin timestamp, meaning the sender wants to reset the association, and the transmit timestamp in this bogus packet will be saved as the most recent "received" timestamp. The real remote peer does not know this value and this will disrupt the association until the association resets.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p11 or later](/downloads/).
* Use authentication with peer mode.
* Have enough sources of time.
* Properly monitor your `ntpd` instances.
* If `ntpd` stops running, auto-restart it without `-g`.

* * *

#### Credit

This weakness was discovered by Miroslav Lichvar of Red Hat.

* * *

#### Timeline

* 2018 Feb 27: Public release
* 2018 Feb 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2018 Jan 23: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Notification from reporter