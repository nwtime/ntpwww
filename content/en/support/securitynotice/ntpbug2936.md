---
title: "NTP BUG 2936: Skeleton Key: Any trusted key system can serve time"
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement/">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2936">Bug 2936</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7974">CVE-2015-7974</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.9</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:S/C:N/I:C/A:N)">AV:N/AC:H/Au:S/C:N/I:C/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Symmetric key encryption uses a shared trusted key. The reported title for this issue was "Missing key check allows impersonation between authenticated peers" and the report claimed "A key specified only for one server should only work to authenticate that server, other trusted keys should be refused." Except there has never been any correlation between this trusted key and server v. clients machines and there has never been any way to specify a key only for one server. We have treated this as an enhancement request, and ntp-4.2.8p6 includes other checks and tests to strengthen clients against attacks coming from broadcast servers.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* If this scenario represents a real or a potential issue for you, upgrade to [4.2.8p6 or later](/downloads/), and use the new field in the `ntp.keys` file that specifies the list of IPs that are allowed to serve time. Note that this alone will not protect against time packets with forged source IP addresses, however other changes in ntp-4.2.8p6 provide significant mitigation against broadcast attacks. MITM attacks are a different story.
* If you are unable to upgrade:
  * Don't use broadcast mode if you cannot monitor your client servers.
  * If you choose to use symmetric keys to authenticate time packets in a hostile environment where ephemeral time servers can be created, or if it is expected that malicious time servers will participate in an NTP broadcast domain, limit the number of participating systems that participate in the shared-key group. 
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by [Matt Street](mailto:mastreet@cisco.com) of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco