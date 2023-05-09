---
title: "NTP BUG 2779: ntpd accepts unauthenticated packets with symmetric key crypto"
description: "Packets without a MAC are accepted as if they had a valid MAC. This allows a MITM attacker to send false packets that are accepted by the client/peer without having to know the symmetric key. This bug was resolved in NTP 4.2.8p2."
type: archives
date: "2015-04-07"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p2-release-announcement/">4.2.8p2</a></td>
		<td>07 Apr 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2779">Bug 2779</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-1798">CVE-2015-1798</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases starting with ntp-4.2.5p99 up to but not including ntp-4.2.8p2<br> where the installation uses symmetric keys to authenticate remote associations.</td>
		<td>Resolved in 4.2.8p2.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>5.4</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:A/AC:M/Au:N/C:P/I:P/A:P)">AV:A/AC:M/Au:N/C:P/I:P/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

When `ntpd` is configured to use a symmetric key to authenticate a remote NTP server/peer, it checks if the NTP message authentication code (MAC) in received packets is valid, but not if there actually is any MAC included. Packets without a MAC are accepted as if they had a valid MAC. This allows a MITM attacker to send false packets that are accepted by the client/peer without having to know the symmetric key. The attacker needs to know the transmit timestamp of the client to match it in the forged reply and the false reply needs to reach the client before the genuine reply from the server. The attacker doesn't necessarily need to be relaying the packets between the client and the server.

Authentication using autokey doesn't have this problem as there is a check that requires the key ID to be larger than `NTP_MAXKEY`, which fails for packets without a MAC.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p2 or later.](/downloads/)
* Configure `ntpd` with enough time sources and monitor it properly. 

* * *

#### Credit

This issue was discovered by Miroslav Lichvar, of Red Hat.

* * *

#### Timeline

* 2015 Apr 7: Public release
* 2015 Mar 22: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Mar 15: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Mar 6: Initial notification received; analysis begins