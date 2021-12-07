---
title: "NTP BUG 3596: Unauthenticated and unmonitored ntpd may be susceptible to IPv4 attack from highly predictable transmit timestamps "
type: archives
date: "2020-03-03"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p14-release-announcement">4.2.8p14</a></td>
		<td>03 Mar 2020</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3596">Bug 3596</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2020-13817">CVE-2020-13817</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>Likely all versions of <code>ntpd</code> up to, but not including ntp-4.2.8p14 and ntp-4.3.100.</td>
		<td>Resolved in ntp-4.2.8p14 and ntp-4.3.100.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>5.4</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:H/Au:N/C:N/I:N/A:C)">AV:N/AC:H/Au:N/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>5.9</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

A high-performance `ntpd` instance that gets its time from unauthenticated IPv4 time sources may be vulnerable to an off-path attacker who can query time from the victim's `ntpd` instance. The attacker must be able to send and the victim must be able to receive and process a large number of packets with the spoofed IPv4 address of the upstream server. After 8 or more successful attacks in a row, the attacker can either modify the victim's clock by a limited amount or cause `ntpd` to exit. This attack is most effective in cases where an unusually short poll interval is expressly configured on the victim's `ntpd`. 

* * *
    
#### Mitigation

* Have enough trustworthy sources of time.
* If you are serving time to a possibly hostile network, have your system get its time from other than unauthenticated IPv4 over the hostile network.
* Use NTP packet authentication where appropriate.
* Pay attention to error messages logged by `ntpd`.
* Monitor your `ntpd` instances. If the `pstats` command of `ntpq` shows the value for "bogus origin" is increasing then that association is likely under attack.
* If you must get unauthenticated time over IPv4 on a hostile network:
  * Use `restrict ... noserve` to prevent this attack (note that this is a heavy-handed protection), which blocks time service to the specified network.
  * Upgrade to [4.2.8p14 or later](/downloads) and appropriately use some or all of the following in your ntp.conf file:
    * `server ... xmtnonce`
    * `pool ... xmtnonce`
    * `restrict ... serverresponse fuzz`
    * `pollskewlist default 6|6` (for example) 

* * *

#### Credit

Reported by Miroslav Lichvar.

* * *

#### Timeline

* 2020 Mar 03: Public release
* 2020 Feb 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2019 Jun 05: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2019 May 30: Notification from reporter