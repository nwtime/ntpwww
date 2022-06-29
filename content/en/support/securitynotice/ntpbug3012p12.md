---
title: "NTP BUG 3012(p12 update): Sybil vulnerability: ephemeral association attack"
description: "If a system is set up to use a trustedkey and is not using the optional 4th field in the ntp.keys file to specify which IPs can serve time, a malicious authenticated peer that knows the private symmetric key can create arbitrarily-many ephemeral associations in order to win the clock selection of ntpd and modify a victim’s clock. The resolution for this bug was improved in NTP 4.2.8p12."
type: archives
date: "2018-08-14"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p12-release-announcement/">4.2.8p12</a> (Improve <code>noepeer</code> behavior.)</td>
		<td>14 Aug 2018</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3012">Bug 3012</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-7170">CVE-2018-7170</a><br> While fixed in ntp-4.2.8p7 and with significant additional protections for this issue in 4.2.8p11, ntp-4.2.8p12 includes a fix for an edge case in the new <code>noepeer</code> support. Refer to <a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1549">CVE-2016-1549</a> for additional info. </td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7, and 4.3.0 up to, but not including 4.3.94.</td>
		<td>Resolved in 4.2.8p11. Improved in 4.2.8p12 and 4.3.94.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 3.5</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:M/Au:S/C:N/I:P/A:N)">AV:N/AC:M/Au:S/C:N/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 5.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:H/A:N">CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:H/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpd` can be vulnerable to Sybil attacks. If a system is set up to use a trustedkey and if one is not using the feature introduced in ntp-4.2.8p6 allowing an optional 4th field in the `ntp.keys` file to specify which IPs can serve time, a malicious authenticated peer -- i.e. one where the attacker knows the private symmetric key -- can create arbitrarily-many ephemeral associations in order to win the clock selection of `ntpd` and modify a victim's clock. Two additional protections are offered in ntp-4.2.8p11. One is the `noepeer` directive, which disables symmetric passive ephemeral peering. The other extends the functionality of the 4th field in the `ntp.keys` file to include specifying a subnet range. 

* * *
    
#### Mitigation

* Implement [BCP-38](http://bcp38.info/).
* Upgrade to [4.2.8p12 or later](/downloads/).
* Use the `noepeer` directive to prohibit symmetric passive ephemeral associations.
* Use the `ippeerlimit` directive to limit the number of peer associations from an IP.
* Use the 4th argument in the `ntp.keys` file to limit the IPs and subnets that can be time servers.
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was originally discovered by Matthew Van Gundy of Cisco ASIG. The edge-case hole in the noepeer processing was reported by Martin Burnicki of Meinberg.

* * *

#### Timeline

* 2018 Aug 14: Public release
* 2018 Jul 25: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)