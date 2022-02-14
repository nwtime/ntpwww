---
title: "NTP BUG 2938: ntpq saveconfig command allows dangerous characters in filenames"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2938">Bug 2938</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7976/">CVE-2015-7976</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.0</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:L/Au:S/C:N/I:P/A:N)">AV:N/AC:L/Au:S/C:N/I:P/A:N</a></td>
	</tr>
	
  </tbody>	
</table>

* * *
    
#### Description 

The `ntpq saveconfig` command does not do adequate filtering of special characters from the supplied filename. Note well: The ability to use the `saveconfig` command is controlled by the `restrict nomodify` directive, and the recommended default configuration is to disable this capability. If the ability to execute a `saveconfig` is required, it can easily (and should) be limited and restricted to a known small number of IP addresses.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Use `restrict default nomodify` in your `ntp.conf` file.
* Upgrade to 4.2.8p6 or later.](/downloads/)
* If you are unable to upgrade:
  * build NTP with `configure --disable-saveconfig` if you will never need this capability, or
  * use `restrict default nomodify` in your `ntp.conf file`. Be careful about what IPs have the ability to send modify requests to `ntpd`. 
* Monitor your `ntpd` instances.
* `saveconfig` requests are logged to `syslog` - monitor your `syslog` files.

* * *

#### Credit

This weakness was discovered by [Jonathan Gardner](mailto:jonagard@cisco.com) of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco