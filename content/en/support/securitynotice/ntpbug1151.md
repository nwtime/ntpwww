---
title: "NTP BUG 1151: Remote exploit if autokey is enabled"
type: archives
date: "2009-03-04"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td>Stable (4.2.4p7)<br> Development (4.2.5p74)</td>
		<td>4 Mar 2009<br> 10 Sep 2007</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=1151">Bug 1151</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2009-1252">CVE-2009-1252</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All releases from 4.0.99m/4.1.70 (2001-08-15) through 4.2.4 before 4.2.4p7 and 4.2.5 before 4.2.5p74.</td>
		<td>Resolved in 4.2.4p and 4.2.5p74.</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

When Autokey Authentication is enabled (i.e. the `ntp.conf` file contains a `crypto pw ...` directive) a remote attacker can send a carefully crafted packet that can overflow a stack buffer and potentially allow malicious code to be executed with the privilege level of the `ntpd` process.

* * *
    
#### Mitigation

* Upgrade to 4.2.4p7 or 4.2.5p74, or later.
* Disable Autokey Authentication by removing, or commenting out, all configuration directives beginning with the `crypto` keyword in your `ntp.conf` file. 

* * *

#### Credit

This vulnerability was discovered by Chis Ries of CMU.

* * *

#### Timeline

* 2009 Mar 4: Public release
* XXXX: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* XXXX: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* XXXX: Notification from reporter