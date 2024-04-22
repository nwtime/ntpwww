---
title: "NTP BUG 3807: praecis_parse() in ntpd/refclock_palisade.c can write out-of-bounds "
description: "The vulnerability described here relies on an attacker gaining physical access to the Praecis unit."
date: "2023-05-30"
type: archives
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p16-release-announcement/">4.2.8p16</a></td>
		<td>30 May 2023</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/3807">Bug 3807</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2023-26555">CVE-2023-26555</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.1.2 up to, but not including ntp-4.2.8p16.</td>
		<td>Resolved in 4.2.8p16.</td>
	</tr>
	<tr>
		<th><b>CVSS3.1 Score<br> between:<b></th>
		<td>1.6 Low</td>
		<td><a href="https://www.first.org/cvss/calculator/3.1#CVSS:3.1/AV:P/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:L">CVSS:3.1/AV:P/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:L</a> (likely)</td>
	</tr>
    <tr>
         <th><b>and:</b></th>
         <td> 3.6 Low</td>
         <td><a href="https://www.first.org/cvss/calculator/3.1#CVSS:3.1/AV:P/AC:H/PR:H/UI:N/S:U/C:L/I:L/A:L">CVSS:3.1/AV:P/AC:H/PR:H/UI:N/S:U/C:L/I:L/A:L</a> (potentially)</td>
    </tr>		 
  </tbody>	
</table>

* * *
    
#### Description 

The Praecis reference clock gets time information from 3G CDMA cellphone towers, and relays it to `ntpd` over a serial port. Support for the Praecis refclock was added in November of 2002, before "defensive programming" was the norm. While once a useful means to transmit time, because CDMA signals have better building penetration than GPS, the use of CDMA networks are rapidly dwindling. At one time, there were 59 3G CDMA networks deployed around the world. As of now 49 have already shut down, and 5 of the remaining 10 are scheduled to shut down between now and 2025. The vulnerability described here relies on an attacker gaining physical access to the Praecis unit and, for example, uploading maliciously altered firmware that will send a response line of more than 100 bytes to an unpatched `ntpd` that is configured to get time from that serial connection using the Praecis driver, thus causing an overflow of an internal buffer. 

* * *
    
#### Mitigation

* If you are using a Praecis refclock and are worried about this vulnerability, upgrade to 4.2.8p16, or later, from the [NTP Project download site](https://downloads.nwtime.org/ntp/4.2.8/).  A patch to ntp-4.2.8p15 is [available](https://downloads.nwtime.org/ntp/4.2.8/ntp-4.2.8p15-3806-3807.patch). 

* * *

#### Credit

Reported by Ping Lee (spwpun).

* * *

#### Timeline

We apologize for the delay in issuing this report. We decided to take the time we needed to produce a thorough and comprehensive response in the face of the significant amount of materially incorrect information in the initial report and third party analysis of this issue. 

* 2023 May 30: Public release
* 2023 May 12: Public hotfix release
* 2023 May 10: Hotfix release to [Advance Security Partners: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2023 Apr 14: Public notification