---
title: "NTP BUG 2947: ntpq protocol vulnerable to replay attacks"
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2947">Bug 2947</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-8140">CVE-2015-8140</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 5.4</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:A/AC:M/Au:N/C:P/I:P/A:P)">AV:A/AC:M/Au:N/C:P/I:P/A:P</a></td>
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

The `ntpq` protocol is vulnerable to replay attacks. The sequence number being included under the signature fails to prevent replay attacks for two reasons. Commands that don't require authentication can be used to move the sequence number forward, and NTP doesn't actually care what sequence number is used so a packet can be replayed at any time. If, for example, an attacker can intercept authenticated reconfiguration commands that would. for example, tell `ntpd` to connect with a server that turns out to be malicious and a subsequent reconfiguration directive removed that malicious server, the attacker could replay the configuration command to re-establish an association to malicious server. Yes, this is an unlikely scenario, but it could still happen.

* * *
    
#### Mitigation

* Configure `ntpd` to get time from multiple sources.
* Use restrict statments in your `ntp.conf` file to limit who is allowed to issue `ntpq` queries and remote configuration commands.
* Monitor your `ntpd` instances.

* * *

#### Credit

This weakness was discovered by Matt Street of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Oct 16: Initial notification from Cisco