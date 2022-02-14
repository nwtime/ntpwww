---
title: "NTP BUG 3415: Provide a way to prevent authenticated symmetric passive peering"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3415">Bug 3415</a><br> also see: <a href="https://bugs.ntp.org/show_bug.cgi?id=3012">Bug 3012</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-7170/">CVE-2018-7170</a><br> also see: <a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1549/">CVE-2016-1549</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 3.5</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:M/Au:S/C:N/I:P/A:N)">AV:N/AC:M/Au:S/C:N/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 3.1</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:L/A:N/E:F/RL:O/RC:C">CVSS:3.0/AV:N/AC:H/PR:L/UI:N/S:U/C:N/I:L/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpd` can be vulnerable to Sybil attacks. If a system is set up to use a trustedkey and if one is not using the feature introduced in ntp-4.2.8p6 allowing an optional 4th field in the `ntp.keys` file to specify which IPs can serve time, a malicious authenticated peer -- i.e. one where the attacker knows the private symmetric key -- can create arbitrarily-many ephemeral associations in order to win the clock selection of `ntpd` and modify a victim's clock. Three additional protections are offered in ntp-4.2.8p11. One is the new `noepeer` directive, which disables symmetric passive ephemeral peering. Another is the new `ippeerlimit` directive, which limits the number of peers that can be created from an IP. The third extends the functionality of the 4th field in the `ntp.keys` file to include specifying a subnet range.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [ntp-4.2.8p11 or later](/downloads/).
* Use the `noepeer` directive to prohibit symmetric passive ephemeral associations.
* Use the `ippeerlimit` directive to limit the number of peers that can be created from an IP.
* Use the 4th argument in the `ntp.keys` file to limit the IPs and subnets that can be time servers.
* Have enough sources of time.
* Properly monitor your `ntpd` instances.
* If `ntpd` stops running, auto-restart it without `-g`. 

* * *

#### Credit

This weakness was reported as [Bug 3012](https://bugs.ntp.org/show_bug.cgi?id=3012) by Matthew Van Gundy of Cisco ASIG, and separately by Stefan Moser as [Bug 3415](https://bugs.ntp.org/show_bug.cgi?id=3415).

* * *

#### Timeline

* 2018 Feb 27: Public release
* 2018 Feb 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2018 Jan 23: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Notification from reporter