---
title: "NTP BUG 2917: Infinite loop if extended logging enabled and the logfile and keyfile are the same"
type: archives
date: "2015-10-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p4-release-announcement/">4.2.8p4</a></td>
		<td>21 Oct 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2917">Bug 2917</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7850">CVE-2015-7850</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.6, worst case</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is configured to allow remote configuration, and if the (possibly spoofed) source IP address is allowed to send remote configuration requests, and if the attacker knows the remote configuration password or if `ntpd` was configured to disable authentication, then an attacker can send a set of packets to `ntpd` that will cause it to crash and/or create a potentially huge log file. Specifically, the attacker could enable extended logging, point the key file at the log file, and cause what amounts to an infinite loop.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to [4.2.8p4 or later](/downloads/).
* If you are unable to upgrade, remote configuration of NTF's `ntpd` requires:
  * an explicitly configured "trusted" key. Only configure this if you need it.
  * access from permitted IP addresses. You choose the IPs.
  * authentication. Don't disable it. Practice key security safety. 
* If you use `ntpq` in scripts, make sure `ntpq` does what you expect in your scripts. 

* * *

#### Credit

This weakness was discovered by Yves Younan of Cisco Talos.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/) for [1593](/support/securitynotice/ntpbug1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899/), and [2902](/support/securitynotice/ntpbug2902/)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902/); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899/); analysis begins