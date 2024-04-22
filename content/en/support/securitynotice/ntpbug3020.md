---
title: "NTP BUG 3020: Refclock impersonation vulnerability"
description: "If ntpd is configured to use a reference clock on operating systems which allow packets claiming to be from 127.0.0.0/8 that arrive over the physical network, an attacker can inject packets over the network that look like they are coming from that reference clock. This bug was resolved in NTP 4.2.8p7."
type: archives
date: "2016-04-26"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p7-release-announcement/">4.2.8p7</a></td>
		<td>26 Apr 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3020">Bug 3020</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1551">CVE-2016-1551</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>On a very limited number of OSes, all NTP releases up to, but not including 4.2.8p7, and 4.3.0 up to, but not including 4.3.92. By "very limited number of OSes" we mean no general-purpose OSes have yet been identified that have this vulnerability.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 2.6</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:N/C:N/I:P/A:N)">AV:N/AC:H/Au:N/C:N/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 3.7</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:L/A:N">CVSS:3.0/AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:L/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

While the majority OSes implement [martian packet](https://en.wikipedia.org/wiki/Martian_packet) filtering in their network stack, at least regarding 127.0.0.0/8, a rare few will allow packets claiming to be from 127.0.0.0/8 that arrive over physical network. On these OSes, if `ntpd` is configured to use a reference clock an attacker can inject packets over the network that look like they are coming from that reference clock.

* * *
    
#### Mitigation

* Implement martian packet filtering and [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Configure `ntpd` to use an adequate number of time sources.
* Upgrade to [4.2.8p7 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* If you are unable to upgrade and if you are running an OS that has this vulnerability, implement martian packet filters and lobby your OS vendor to fix this problem, or run your refclocks on computers that use OSes that are not vulnerable to these attacks and have your vulnerable machines get their time from protected resources.
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Matt Street and others of Cisco ASIG.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco