---
title: "NTP BUG 1532: DRDoS/Amplification Attack using ntpdc monlist command"
description: "Unrestricted access to the monlist feature in ntp_request.c in ntpd allows remote attackers to cause a denial of service (traffic amplification) via forged REQ_MON_GETLIST or REQ_MON_GETLIST_1 requests. This bug was resolved in NTP 4.2.7p26."
type: archives
date: "2010-04-24"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a 4.2.7p26</a></td>
		<td>24 Apr 2010</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=1532">Bug 1532</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2013-5211">CVE-2013-5211</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All releases prior to 4.2.7p26.</td>
		<td>Resolved in 4.2.7p26.</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Unrestricted access to the `monlist` feature in `ntp_request.c` in `ntpd` in NTP before 4.2.7p26 allows remote attackers to cause a denial of service (traffic amplification) via forged `REQ_MON_GETLIST` or `REQ_MON_GETLIST_1` requests, as exploited in the wild in December 2013.

* * *
    
#### Mitigation

* Upgrade to 4.2.7p26 or later.
* Users of versions before 4.2.7p26 should either:
  * Use `noquery` in your default restrictions to block all status queries.
  * Use `disable monitor` to disable the `ntpdc -c monlist` command while still allowing other status queries. 


* * *

#### Credit



* * *

#### Timeline

* 2010 Apr 24: Public release
* XXXX: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: Notification from reporter