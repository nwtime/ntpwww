---
title: "NTP BUG 2916: memory corruption in password store"
description: "If ntpd is configured to allow remote configuration, and the source IP address is allowed to send remote configuration requests, and the attacker knows the remote configuration password or ntpd was configured to disable authentication, then an attacker can send a set of packets to crash ntpd or perform a code injection attack. This bug was resolved in NTP 4.2.8p4."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2916">Bug 2916</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7849">CVE-2015-7849</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>6.8, worst case</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:M/C:C/I:C/A:C)">AV:N/AC:H/Au:M/C:N/I:C/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is configured to allow remote configuration, and if the (possibly spoofed) source IP address is allowed to send remote configuration requests, and if the attacker knows the remote configuration password or if `ntpd` was configured to disable authentication, then an attacker can send a set of packets to `ntpd` that may cause a crash or theoretically perform a code injection attack.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to [4.2.8p4 or later](https://downloads.nwtime.org/ntp/4.2.8/).
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
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/) for [1593](/support/securitynotice/ntpbug1593/), [1774](/support/securitynotice/ntpbug1774/), [2382](/support/securitynotice/ntpbug2382/), [2899](/support/securitynotice/ntpbug2899/), and [2902](/support/securitynotice/ntpbug2902/)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902/); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899/); analysis begins