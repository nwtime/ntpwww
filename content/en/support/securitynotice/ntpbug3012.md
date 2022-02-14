---
title: "NTP BUG 3012: Sybil vulnerability: ephemeral association attack"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3012">Bug 3012</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1549/">CVE-2016-1549</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7 with significant additional protections for this issue in 4.2.8p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 3.5</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:M/Au:S/C:N/I:P/A:N)">AV:N/AC:M/Au:S/C:N/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 5.3</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:H/A:N">CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:H/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpd` can be vulnerable to Sybil attacks. If a system is set up to use a trustedkey and if one is not using the feature introduced in ntp-4.2.8p6 allowing an optional 4th field in the `ntp.keys` file to specify which IPs can serve time, a malicious authenticated peer -- i.e. one where the attacker knows the private symmetric key -- can create arbitrarily-many ephemeral associations in order to win the clock selection of `ntpd` and modify a victim's clock. 

* * *
    
#### Mitigation

* Implement BCP-38.
* Use the 4th argument in the `ntp.keys` file to limit the IPs that can be time servers.
* Properly monitor your `ntpd` instances.

* * *

#### Credit

This weakness was discovered by Matthew Van Gundy of Cisco ASIG.