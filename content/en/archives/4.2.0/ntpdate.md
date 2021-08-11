---
title: "ntpdate - set the date and time via NTP"
type: archives
---

![gif](/archives/pic/rabbit.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

I told you it was eyeball and wristwatch.

Last update: 01:13 UTC Sunday, December 22, 2002

* * *

**Disclaimer:** The functionality of this program is now available in the <tt>ntpd</tt> program. See the `-q` command line option in the [<tt>ntpd</tt> - Network Time Protocol (NTP) daemon](/archives/4.2.0/ntpd) page. After a suitable period of mourning, the <tt>ntpdate</tt> program will be retired from this distribution.

* * *

#### Table of Contents

* [Synopsis](/archives/4.2.0/ntpdate/#synopsis)
* [Description](/archives/4.2.0/ntpdate/#description)
* [Command Line Options](/archives/4.2.0/ntpdate/#command-line-options)
* [Files](/archives/4.2.0/ntpdate/#files)
* [Bugs](/archives/4.2.0/ntpdate/#bugs)

* * *

#### Synopsis

<tt>ntpdate [ -bBdoqsuv ] [ -a _key_ ] [ -e _authdelay_ ] [ -k _keyfile_ ] [ -o _version_ ] [ -p _samples_ ] [ -t _timeout_ ] _server_ [ ... ]</tt>

* * *

#### Description

<tt>ntpdate</tt> sets the local date and time by polling the Network Time Protocol (NTP) server(s) given as the _server_ arguments to determine the correct time. It must be run as root on the local host. A number of samples are obtained from each of the servers specified and a subset of the NTP clock filter and selection algorithms are applied to select the best of these. Note that the accuracy and reliability of <tt>ntpdate</tt> depends on the number of servers, the number of polls each time it is run and the interval between runs.

<tt>ntpdate</tt> can be run manually as necessary to set the host clock, or it can be run from the host startup script to set the clock at boot time. This is useful in some cases to set the clock initially before starting the NTP daemon <tt>ntpd</tt>. It is also possible to run <tt>ntpdate</tt> from a <tt>cron</tt> script. However, it is important to note that <tt>ntpdate</tt> with contrived <tt>cron</tt> scripts is no substitute for the NTP daemon, which uses sophisticated algorithms to maximize accuracy and reliability while minimizing resource use. Finally, since <tt>ntpdate</tt> does not discipline the host clock frequency as does <tt>ntpd</tt>, the accuracy using <tt>ntpdate</tt> is limited.

Time adjustments are made by <tt>ntpdate</tt> in one of two ways. If <tt>ntpdate</tt> determines the clock is in error more than 0.5 second it will simply step the time by calling the system <tt>settimeofday()</tt> routine. If the error is less than 0.5 seconds, it will slew the time by calling the system <tt>adjtime()</tt> routine. The latter technique is less disruptive and more accurate when the error is small, and works quite well when <tt>ntpdate</tt> is run by <tt>cron</tt> every hour or two.

<tt>ntpdate</tt> will decline to set the date if an NTP server daemon (e.g., <tt>ntpd</tt>) is running on the same host. When running <tt>ntpdate</tt> on a regular basis from <tt>cron</tt> as an alternative to running a daemon, doing so once every hour or two will result in precise enough timekeeping to avoid stepping the clock.

Note that in contexts where a host name is expected, a <tt>-4</tt> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <tt>-6</tt> qualifier forces DNS resolution to the IPv6 namespace.

If NetInfo support is compiled into <tt>ntpdate</tt>, then the <tt>server</tt> argument is optional if <tt>ntpdate</tt> can find a time server in the NetInfo configuration for <tt>ntpd</tt>.

* * *

#### Command Line Options

<dt><tt>-4</tt></dt>

Force DNS resolution of following host names on the command line to the IPv4 namespace.

<dt><tt>-6</tt></dt>

Force DNS resolution of following host names on the command line to the IPv6 namespace.

<dt><tt>-a _key_</tt></dt>

Enable the authentication function and specify the key identifier to be used for authentication as the argument _key_ <tt>ntpdate</tt>. The keys and key identifiers must match in both the client and server key files. The default is to disable the authentication function.

<dt><tt>-B</tt></dt>

Force the time to always be slewed using the adjtime() system call, even if the measured offset is greater than +-128 ms. The default is to step the time using settimeofday() if the offset is greater than +-128 ms. Note that, if the offset is much greater than +-128 ms in this case, that it can take a long time (hours) to slew the clock to the correct value. During this time, the host should not be used to synchronize clients.

<dt><tt>-b</tt></dt>

Force the time to be stepped using the settimeofday() system call, rather than slewed (default) using the adjtime() system call. This option should be used when called from a startup file at boot time.

<dt><tt>-d</tt></dt>

Enable the debugging mode, in which <tt>ntpdate</tt> will go through all the steps, but not adjust the local clock. Information useful for general debugging will also be printed.

<dt><tt>-e _authdelay_</tt></dt>

Specify the processing delay to perform an authentication function as the value _authdelay_, in seconds and fraction (see <tt>ntpd</tt> for details). This number is usually small enough to be negligible for most purposes, though specifying a value may improve timekeeping on very slow CPUs. 

<dt><tt>-k _keyfile_</tt></dt>

Specify the path for the authentication key file as the string _keyfile_. The default is <tt>/etc/ntp.keys</tt>. This file should be in the format described in <tt>ntpd</tt>.

<dt><tt>-o _version_</tt></dt>

Specify the NTP version for outgoing packets as the integer _version_, which can be 1 or 2. The default is 3. This allows <tt>ntpdate</tt> to be used with older NTP versions.

<dt><tt>-p _samples_</tt></dt>

Specify the number of samples to be acquired from each server as the integer _samples_, with values from 1 to 8 inclusive. The default is 4.

<dt><tt>-q</tt></dt>

Query only - don't set the clock.

<dt><tt>-s</tt></dt>

Divert logging output from the standard output (default) to the system <tt>syslog</tt> facility. This is designed primarily for convenience of <tt>cron</tt> scripts.

<dt><tt>-t _timeout_</tt></dt>

Specify the maximum time waiting for a server response as the value _timeout_, in seconds and fraction. The value is rounded to a multiple of 0.2 seconds. The default is 1 second, a value suitable for polling across a LAN.

<dt><tt>-u</tt></dt>

Direct <tt>ntpdate</tt> to use an unprivileged port for outgoing packets. This is most useful when behind a firewall that blocks incoming traffic to privileged ports, and you want to synchronize with hosts beyond the firewall. Note that the <tt>-d</tt> option always uses unprivileged ports.

<dt><tt>-v</tt></dt>

Be verbose. This option will cause <tt>ntpdate</tt>'s version identification string to be logged.

* * *

#### Files

<tt>/etc/ntp.keys</tt> - encryption keys used by <tt>ntpdate</tt>.

* * *

#### Bugs

The slew adjustment is actually 50% larger than the measured offset, since this (it is argued) will tend to keep a badly drifting clock more accurate. This is probably not a good idea and may cause a troubling hunt for some values of the kernel variables <tt>tick</tt> and <tt>tickadj</tt>. 