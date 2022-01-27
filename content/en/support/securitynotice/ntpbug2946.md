---
title: "NTP BUG 2946: Origin Leak: ntpq and ntpdc Disclose Origin Timestamp to Unauthenticated Clients"
type: archives
date: "2016-04-26"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p7-release-announcement">4.2.8p7</a></td>
		<td>26 Apr 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2946">Bug 2946</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-8139">CVE-2015-8139</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 5.0</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:L/Au:N/C:P/I:P/A:N)">AV:N/AC:L/Au:N/C:P/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 5.3</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:L/A:N">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:L/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

To prevent off-path attackers from impersonating legitimate peers, clients require that the origin timestamp in a received response packet match the transmit timestamp from its last request to a given peer. Under assumption that only the recipient of the request packet will know the value of the transmit timestamp, this prevents an attacker from forging replies.

* * *
    
#### Mitigation

* Configure `ntpd` to get time from multiple sources.
* Configure `ntpd` with `restrict` statements to limit who is allowed to issue `ntpq` and `ntpdc` queries. Note that `ntpdc` queries are disabled by default.
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by [Matthew Van Gundy](mailto:mvangund@cisco.com) of Cisco ASIG.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Jan 12: Initial notification from Cisco