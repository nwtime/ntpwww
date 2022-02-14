---
title: "NTP BUG 3381: Copious amounts of Unused Code"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3381">Bug 3381</a></td>
		<td></td>
	</tr>
  </tbody>	
</table>

* * *
    
#### Description 

The report says: Statically included external projects potentially introduce several problems and the issue of having extensive amounts of code that is “dead” in the resulting binary must clearly be pointed out. The unnecessary unused code may or may not contain bugs and, quite possibly, might be leveraged for code-gadget-based branch-flow redirection exploits. Analogically, having source trees statically included as well means a failure in taking advantage of the free feature for periodical updates. This solution is offered by the system’s Package Manager. The three libraries identified are `libisc`, `libevent`, and `libopts`.

* * *
    
#### Resolution

* For `libisc`, we already only use a portion of the original library. We've found and fixed bugs in the original implementation (and offered the patches to ISC), and plan to see what has changed since we last upgraded the code. `libisc` is generally not installed, and when it it we usually only see the static `libisc.a` file installed. Until we know for sure that the bugs we've found and fixed are fixed upstream, we're better off with the copy we are using.
* Version 1 of `libevent` was the only production version available until recently, and we've been requiring version 2 for a long time. But if the build system has at least version 2 of `libevent` installed, we'll use the version that is installed on the system. Otherwise, we provide a copy of `libevent` that we know works.
* `libopts` is provided by GNU AutoGen, and that library and package undergoes frequent API version updates. The version of `autogen` used to generate the tables for the code must match the API version in `libopts`. AutoGen can be ... difficult to build and install, and very few developers really need it. So we have it on our build and development machines, and we provide the specific version of the `libopts` code in the distribution to make sure that the proper API version of `libopts` is available.
* As for the point about there being code in these libraries that NTP doesn't use, OK. But other packages used these libraries as well, and it is reasonable to assume that other people are paying attention to security and code quality issues for the overall libraries. It takes significant resources to analyze and customize these libraries to only include what we need, and to date we believe the cost of this effort does not justify the benefit. 

* * *

#### Credit

This issue was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received