---
title: "NTP BUG 1331: DoS attack from certain NTP mode 7 packets"
description: "If an attacker spoofs the source address in a mode 7 response packet, both systems will continuously send each other error responses. If an attacker spoofs the recipient's address in a mode 7 response packet, the recipient will respond endlessly, consuming CPU and logging excessively. This bug was resolved in NTP 4.2.4p8."
type: archives
date: "2009-12-08"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td>4.2.4p8<br> 4.2.6</td>
		<td>08 December 2009</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=1331">Bug 1331</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2009-3563">CVE-2009-3563</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All releases from xntp2 (1989) (possibly earlier) through 4.2.4 before 4.2.4p8 and all versions of 4.2.5.</td>
		<td>Resolved in 4.2.4p8 and 4.2.6.</td>
	</tr>
  </tbody>	
</table>

* * *
    
#### Description 

NTP mode 7 (MODE_PRIVATE) is used by the `ntpdc` query and control utility. In contrast, `ntpq` uses NTP mode 6 (MODE_CONTROL), while routine NTP time transfers use modes 1 through 5. Upon receipt of an incorrect mode 7 request or a mode 7 error response from an address which is not listed in a `restrict ... noquery` or `restrict ... ignore` statement, `ntpd` will reply with a mode 7 error response (and log a message). In this case:

   * If an attacker spoofs the source address of `ntpd` host A in a mode 7 response packet sent to `ntpd` host B, both A and B will continuously send each other error responses, for as long as those packets get through.
   * If an attacker spoofs an address of `ntpd` host A in a mode 7 response packet sent to `ntpd` host A, A will respond to itself endlessly, consuming CPU and logging excessively. 

* * *
    
#### Mitigation

* Upgrade to 4.2.4p8 or 4.2.6, or later.
* Use `restrict ... noquery` or `restrict ... ignore` in your `ntp.conf` file to limit the source addresses to which `ntpd` will respond.
* Filter NTP mode 7 packets coming into and/or going out of your network. This will likely interfere with your ability to use `ntpdc` to manage NTP servers outside your network, or for a legitimate outsider to manage your servers. (If either of these is useful, a VPN is probably your friend.)
* Filter NTP mode 7 packets where both the source and destination ports are 123, the privileged NTP port. In most cases, legitimate `ntpdc` mode 7 requests will have a source port not equal to 123 and a destination port of 123, while most legitimate responses will have a source port of 123 and a destination port not equal to 123.
* Employ anti-spoofing IP address filters at your borders to prevent UDP traffic claiming to be from a local address that originate outside your network. Prefer ISPs which employ unicast reverse path filtering (uRPF) to limit the spoofed traffic entering your network. See [BCP 38/RFC 2827](https://www.rfc-editor.org/rfc/rfc2827) and [BCP 84/RFC3704](https://www.rfc-editor.org/rfc/rfc3704) (multihomed networks) for additional details. 

* * *

#### Credit

This vulnerability was discovered by Robin Park and Dmitri Vinokurov of Alcatel-Lucent.

* * *

#### Timeline

* 2009 Dec 8: Public release
* XXXX: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: Notification from reporter