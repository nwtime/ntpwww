---
title: "NTP BUG 1111: Multiple OpenSSL signature verification API misuse"
description: "Affected versions do not properly check the return value from the OpenSSL EVP_VerifyFinal function, which allows remote attackers to bypass validation of the certificate chain via a malformed SSL/TLS signature. This bug was resolved in NTP 4.2.4p6."
type: archives
date: "2009-01-08"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td>Stable (4.2.4p6)<br> Development (4.2.5p151)</td>
		<td>8 Jan 2009<br> 23 Dec 2008</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=1111">Bug 1111</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2009-0021">CVE-2009-0021</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>4.2.4 before 4.2.4p5 and 4.2.5 before 4.2.5p150.</td>
		<td>Resolved in 4.2.4p6 and 4.2.5p151.</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Affected versions do not properly check the return value from the OpenSSL `EVP_VerifyFinal` function, which allows remote attackers to bypass validation of the certificate chain via a malformed SSL/TLS signature, a different vulnerability than [CVE-2008-5077](https://nvd.nist.gov/vuln/detail/CVE-2008-5077) and [CVE-2009-0025](https://nvd.nist.gov/vuln/detail/CVE-2009-0025).

* * *
    
#### Mitigation



* * *

#### Credit



* * *

#### Timeline

* 2008 Dec 23: Public release
* XXXX: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* XXXX: Notification from reporter