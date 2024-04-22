---
title: "NTP BUG 3385: ereallocarray() / eallocarray() underused"
description: "Although no considerable threat was identified as tied to a lack of use of this function, it is recommended to correctly apply oreallocarray() as a preferred option across all of the locations where it is possible. This bug was resolved in NTP 4.2.8p10."
type: archives
date: "2017-03-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p10-release-announcement/">4.2.8p10</a></td>
		<td>21 Mar 2017</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3385">Bug 3385</a></td>
		<td></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of NTP, up to but not including ntp-4.2.8p10, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

NTP makes use of several wrappers around the standard heap memory allocation functions that are provided by `libc`. This is mainly done to introduce additional safety checks concentrated on several goals. First, they seek to ensure that memory is not accidentally freed, secondly they verify that a correct amount is always allocated and, thirdly, that allocation failures are correctly handled. There is an additional implementation for scenarios where memory for a specific amount of items of the same size needs to be allocated. The handling can be found in the `oreallocarray()` function for which a further number-of-elements parameter needs to be provided. Although no considerable threat was identified as tied to a lack of use of this function, it is recommended to correctly apply `oreallocarray()` as a preferred option across all of the locations where it is possible.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p10 or later.](https://downloads.nwtime.org/ntp/4.2.8/)

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received