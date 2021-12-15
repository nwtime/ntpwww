---
title: "NTP BUG 2853: ntpd control message crash: Crafted NUL-byte in configuration directive"
type: archives
date: "2015-06-29"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p3-release-announcement">4.2.8p3</a></td>
		<td>29 Jun 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2853">Bug 2853</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-5146">CVE-2015-5146</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>4.2.5p3 up to, but not including 4.2.8p3-RC1,<br> and 4.3.0 up to, but not including 4.3.25.</td>
		<td>Resolved in 4.2.8p3.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.9 at likely worst, 1.4 or less at likely best</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:A/AC:M/Au:S/C:P/I:P/A:P)">AV:A/AC:M/Au:S/C:P/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Under limited and specific circumstances an attacker can send a crafted packet to cause a vulnerable `ntpd` instance to crash. This requires each of the following to be true:
  1. `ntpd` set up to allow for remote configuration (not allowed by default), and
  2. knowledge of the configuration password, and
  3. access to a computer entrusted to perform remote configuration. 

* * *
    
#### Mitigation

* Upgrade to [4.2.8p3 or later.](/downloads)
* Be prudent when deciding what IP addresses can perform remote configuration of an `ntpd` instance.
* Monitor your `ntpd` instances.

* * *

#### Credit

This weakness was discovered by Aleksis Kauppinen of Codenomicon.

* * *

#### Timeline

* 2015 Jun 29: Public release
* 2015 Jun 24: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Jun 22: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Jun 16: Notification received from FICORA; analysis begins