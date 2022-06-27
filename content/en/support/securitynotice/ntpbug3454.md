---
title: "NTP BUG 3454: Unauthenticated packet can reset authenticated interleaved association"
description: "This bug allows a non-authenticated zero-origin (reset) packet to reset an authenticated interleaved peer association. This bug was resolved in 4.2.8p11."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3454">Bug 3454</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-7185">CVE-2018-7185</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.6, up to but not including ntp-4.2.8p11.</td>
		<td>Resolved in 4.2.8p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:M/Au:N/C:N/I:N/A:P)">AV:N/AC:M/Au:N/C:N/I:N/A:P</a><br> This could score between 2.9 and 6.8.</td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 3.1</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=(AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:N/A:L)">CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:N/A:L</a><br> This could score between 2.6 and 3.1.</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The NTP Protocol allows for both non-authenticated and authenticated associations, in client/server, symmetric (peer), and several broadcast modes. In addition to the basic NTP operational modes, symmetric mode and broadcast servers can support an interleaved mode of operation. In ntp-4.2.8p4 a bug was inadvertently introduced into the protocol engine that allows a non-authenticated zero-origin (reset) packet to reset an authenticated interleaved peer association. If an attacker can send a packet with a zero-origin timestamp and the source IP address of the "other side" of an interleaved association, the 'victim' `ntpd` will reset its association. The attacker must continue sending these packets in order to maintain the disruption of the association. In ntp-4.0.0 thru ntp-4.2.8p6, interleave mode could be entered dynamically. As of ntp-4.2.8p7, interleaved mode must be explicitly configured/enabled.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p11 or later](/downloads/).
* If you are unable to upgrade to 4.2.8p11 or later and have `peer HOST xleave` lines in your `ntp.conf` file, remove the `xleave` option.
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
* 2018 Feb 05: Notification from reporter