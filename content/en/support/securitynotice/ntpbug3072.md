---
title: "NTP BUG 3072: Attack on interface selection"
description: "If ntpd is running on a host with multiple interfaces in separate networks and the operating system doesn’t check the source address in received packets, an attacker can send a spoofed source address, causing ntpd to select the wrong interface for the source and preventing it from sending new requests until the list of interfaces is refreshed. This bug was resolved in NTP 4.2.8p9."
type: archives
date: "2016-11-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p9-release-announcement/">4.2.8p9</a></td>
		<td>21 Nov 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3072">Bug 3072</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-7429">CVE-2016-7429</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.7p385, up to but not including ntp-4.2.8p9,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p9.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 1.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:S/C:N/I:N/A:P)">AV:L/AC:H/Au:S/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 1.6</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:P/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L">CVSS:3.0/AV:P/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

When `ntpd` receives a server response on a socket that corresponds to a different interface than was used for the request, the peer structure is updated to use the interface for new requests. If `ntpd` is running on a host with multiple interfaces in separate networks and the operating system doesn't check source address in received packets (e.g. `rp_filter` on Linux is set to 0), an attacker that knows the address of the source can send a packet with spoofed source address which will cause `ntpd` to select wrong interface for the source and prevent it from sending new requests until the list of interfaces is refreshed, which happens on routing changes or every 5 minutes by default. If the attack is repeated often enough (once per second), `ntpd` will not be able to synchronize with the source.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page) 
* Upgrade to [4.2.8p9 or later.](/downloads/)
* If you are going to configure your OS to disable source address checks, also configure your firewall configuration to control what interfaces can receive packets from what networks. 
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Miroslav Lichvar of Red Hat.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received