---
title: "ntpdate - set the date and time via NTP"
type: archives
---

![gif](/archives/pic/rabbit.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

I told you it was eyeball and wristwatch.

* * *

> **Disclaimer:** The functionality of this program is now available in the <code>ntpd</code> program. See the `-q` command line option in the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/archives/4.1.0/ntpd) page. After a suitable period of mourning, the <code>ntpdate</code> program will be retired from this distribution.

* * *

#### Table of Contents

* [Synopsis](/archives/4.1.0/ntpdate/#synopsis)
* [Description](/archives/4.1.0/ntpdate/#description)
* [Command Line Options](/archives/4.1.0/ntpdate/#command-line-options)
* [Files](/archives/4.1.0/ntpdate/#files)
* [Bugs](/archives/4.1.0/ntpdate/#bugs)

* * *

#### Synopsis

<code>ntpdate [ -bBdoqsuv ] [ -a _key_ ] [ -e _authdelay_ ] [ -k _keyfile_ ] [ -o _version_ ] [ -p _samples_ ] [ -t _timeout_ ] _server_ [ ... ]</code>

* * *

#### Description

<code>ntpdate</code> sets the local date and time by polling the Network Time Protocol (NTP) server(s) given as the <code>_server_</code> arguments to determine the correct time. It must be run as root on the local host. A number of samples are obtained from each of the servers specified and a subset of the NTP clock filter and selection algorithms are applied to select the best of these. Note that the accuracy and reliability of <code>ntpdate</code> depends on the number of servers, the number of polls each time it is run and the interval between runs.

<code>ntpdate</code> can be run manually as necessary to set the host clock, or it can be run from the host startup script to set the clock at boot time. This is useful in some cases to set the clock initially before starting the NTP daemon <code>ntpd</code>. It is also possible to run <code>ntpdate</code> from a <code>cron</code> script. However, it is important to note that <code>ntpdate</code> with contrived <code>cron</code> scripts is no substitute for the NTP daemon, which uses sophisticated algorithms to maximize accuracy and reliability while minimizing resource use. Finally, since <code>ntpdate</code> does not discipline the host clock frequency as does <code>ntpd</code>, the accuracy using <code>ntpdate</code> is limited.

Time adjustments are made by <code>ntpdate</code> in one of two ways. If <code>ntpdate</code> determines the clock is in error more than 0.5 second it will simply step the time by calling the system <code>settimeofday()</code> routine. If the error is less than 0.5 seconds, it will slew the time by calling the system <code>adjtime()</code> routine. The latter technique is less disruptive and more accurate when the error is small, and works quite well when <code>ntpdate</code> is run by <code>cron</code> every hour or two.

<code>ntpdate</code> will decline to set the date if an NTP server daemon (e.g., <code>ntpd</code>) is running on the same host. When running <code>ntpdate</code> on a regular basis from <code>cron</code> as an alternative to running a daemon, doing so once every hour or two will result in precise enough timekeeping to avoid stepping the clock.

If NetInfo support is compiled into <code>ntpdate</code>, then the <code>server</code> argument is optional if <code>ntpdate</code> can find a time server in the NetInfo configuration for <code>ntpd</code>.

* * *

#### Command Line Options

<code>**-a _key_**</code>

: Enable the authentication function and specify the key identifier to be used for authentication as the argument <code>_key_</code> to <code>ntpdate</code>. The keys and key identifiers must match in both the client and server key files. The default is to disable the authentication function.

<code>**-B**</code>

: Force the time to always be slewed using the adjtime() system call, even if the measured offset is greater than +-128 ms. The default is to step the time using <code>settimeofday()</code> if the offset is greater than +-128 ms. Note that, if the offset is much greater than +-128 ms in this case, that it can take a long time (hours) to slew the clock to the correct value. During this time, the host should not be used to synchronize clients.

<code>**-b**</code>

: Force the time to be stepped using the <code>settimeofday()</code> system call, rather than slewed (default) using the <code>adjtime()</code> system call. This option should be used when called from a startup file at boot time.

<code>**-d**</code>

: Enable the debugging mode, in which <code>ntpdate</code> will go through all the steps, but not adjust the local clock. Information useful for general debugging will also be printed.

<code>**-e _authdelay_**</code>

: Specify the processing delay to perform an authentication function as the value <code>_authdelay_</code>, in seconds and fraction (see <code>ntpd</code> for details). This number is usually small enough to be negligible for most purposes, though specifying a value may improve timekeeping on very slow CPUs. 

<code>**-k _keyfile_**</code>

: Specify the path for the authentication key file as the string <code>_keyfile_</code>. The default is <code>/etc/ntp.keys</code>. This file should be in the format described in <code>ntpd</code>.

<code>**-o _version_**</code>

: Specify the NTP version for outgoing packets as the integer <code>_version_</code>, which can be 1 or 2. The default is 3. This allows <code>ntpdate</code> to be used with older NTP versions.

<code>**-p _samples_**</code>

: Specify the number of samples to be acquired from each server as the integer <code>_samples_</code>, with values from 1 to 8 inclusive. The default is 4.

<code>**-q**</code>

: Query only - don't set the clock.

<code>**-s**</code>

: Divert logging output from the standard output (default) to the system <code>syslog</code> facility. This is designed primarily for convenience of <code>cron</code> scripts.

<code>**-t _timeout_**</code>

: Specify the maximum time waiting for a server response as the value <code>_timeout_</code>, in seconds and fraction. The value is rounded to a multiple of 0.2 seconds. The default is 1 second, a value suitable for polling across a LAN.

<code>**-u**</code>

: Direct <code>ntpdate</code> to use an unprivileged port for outgoing packets. This is most useful when behind a firewall that blocks incoming traffic to privileged ports, and you want to synchronize with hosts beyond the firewall. Note that the <code>-d</code> option always uses unprivileged ports.

<code>**-v**</code>

: Be verbose. This option will cause <code>ntpdate</code>'s version identification string to be logged.

* * *

#### Files

<code>/etc/ntp.keys</code> - encryption keys used by <code>ntpdate</code>.

* * *

#### Bugs

The slew adjustment is actually 50% larger than the measured offset, since this (it is argued) will tend to keep a badly drifting clock more accurate. This is probably not a good idea and may cause a troubling hunt for some values of the kernel variables <code>tick</code> and <code>tickadj</code>.