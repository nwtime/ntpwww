---
title: "NTP BUG 3767: An out-of-bounds KoD RATE ppoll value triggers an assertion abort in debug-enabled ntpd"
description: "Disable debugging when building NTP for production deployments."
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
		<td><a href="https://bugs.ntp.org/3767">Bug 3767</a></td>
		<td></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p14 up to, but not including ntp-4.2.8p16.</td>
		<td>Resolved in 4.2.8p16.</td>
	</tr>
	<tr>
		<th><b>CVSS3.1 Score<b></th>
		<td>2.2 Low</td>
		<td><a href="https://www.first.org/cvss/calculator/3.1#CVSS:3.1/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:L">CVSS:3.1/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

By default, the NTP software builds with debugging enabled. We expect most folks who build from source to be using NTP for development purposes, where it makes sense to enable debugging. Similarly, we expect production release engineers to build production releases with debugging disabled. An attacker who has control over an `ntpd` instance the victim queries, or who is "lucky enough" to guess the packet transmit timestamp of an unauthenticated client request and inject their response before the real server responds, can send a response with a KoD (kiss-of-death) RATE packet with an out-of-bounds value that will cause a debug-enabled victim's `ntpd` to abort with an assertion failure.  

* * *
    
#### Mitigation

* Use `configure --disable-debugging ...` when building the NTP software for production deployments.
* Upgrade to 4.2.8p16, or later, from the [NTP Project download site](https://downloads.nwtime.org/ntp/4.2.8/).

* * *

#### Credit

Reported by Miroslav Lichvar.

* * *

#### Timeline

* 2023 May 30: Public release
* 2023 May 10: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2023 Mar 20: Got found. Processes under review so this doesn't happen again
* 2022 Jun 30: Notification from reporter. Got lost.