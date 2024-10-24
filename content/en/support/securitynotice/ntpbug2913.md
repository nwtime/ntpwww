---
title: "NTP BUG 2913: mode 7 loop counter underrun"
description: "If ntpd is configured to enable mode 7 packets without using any available mode 7 authentication and restriction mechanisms, and the source IP address is allowed to send mode 7 queries, then an attacker can send a crafted packet to crash ntpd. This bug was resolved in NTP 4.2.8p4."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2913">Bug 2913</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7848">CVE-2015-7848</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.6</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is configured to enable mode 7 packets, and if the use of mode 7 packets is not properly protected thru the use of the available mode 7 authentication and restriction mechanisms, and if the (possibly spoofed) source IP address is allowed to send mode 7 queries, then an attacker can send a crafted packet to `ntpd` that will cause it to crash.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to [4.2.8p4 or later](https://downloads.nwtime.org/ntp/4.2.8/).
* If you are unable to upgrade:
  * In ntp-4.2.8, mode 7 is disabled by default. Don't enable it.
  * If you must enable mode 7:
    * configure the use of a `requestkey` to control who can issue mode 7 requests.
    * configure `restrict noquery` to further limit mode 7 requests to trusted sources. 
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Aleksandar Nikolic of Cisco Talos.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/) for [1593](/support/securitynotice/ntpbug1593/), [1774](/support/securitynotice/ntpbug1774/), [2382](/support/securitynotice/ntpbug2382/), [2899](/support/securitynotice/ntpbug2899/), and [2902](/support/securitynotice/ntpbug2902/)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902/); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899/); analysis begins