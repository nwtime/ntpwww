---
title: "ntpdate - set the date and time via NTP"
description: "ntpdate is a historical program to set the local date and time by polling NTP servers. It has been replaced by the ntpd -q option."
type: archives
aliases:
    - /current-stable/ntpdate/
---

![gif](/documentation/pic/rabbit.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

I told you it was eyeball and wristwatch.

* * *

> Disclaimer: This program has known bugs and deficiencies and nobody has volunteered to fix them in a long time. The good news is the functionality originally intended for this program is available in the `ntpd` and `sntp` programs. See the [Deprecating `ntpdate` topic](https://support.ntp.org/Dev/DeprecatingNtpdate) for a thorough discussion and analysis of the issues. See the `-q` command line option in [`ntpd` - Network Time Protocol (NTP) daemon](/documentation/4.2.8-series/ntpd/) or [`sntp` - Simple Network Time Protocol (SNTP) Client](/documentation/4.2.8-series/sntp/). After a suitable period of mourning, the `ntpdate` program will be retired from this distribution.

#### Table of Contents

* [Synopsis](/documentation/4.2.8-series/ntpdate/#synopsis)
* [Description](/documentation/4.2.8-series/ntpdate/#description)
* [Command Line Options](/documentation/4.2.8-series/ntpdate/#command-line-options)
* [Diagnostics](/documentation/4.2.8-series/ntpdate/#diagnostics)
* [Files](/documentation/4.2.8-series/ntpdate/#files)
* [Bugs](/documentation/4.2.8-series/ntpdate/#bugs)

#### Synopsis

<code>ntpdate [ -46bBdqsuv ] [ -a _key_ ] [ -e _authdelay_ ] [ -k _keyfile_ ] [ -o _version_ ] [ -p _samples_ ] [ -t _timeout_ ] _server_ [ ... ]</code>

* * *

#### Description

`ntpdate` sets the local date and time by polling the Network Time Protocol (NTP) server(s) given as the <code>_server_</code> arguments to determine the correct time. It must be run as root on the local host. A number of samples are obtained from each of the servers specified and a subset of the NTP clock filter and selection algorithms are applied to select the best of these. Note that the accuracy and reliability of `ntpdate` depends on the number of servers, the number of polls each time it is run and the interval between runs.

`ntpdate` can be run manually as necessary to set the host clock, or it can be run from the host startup script to set the clock at boot time. This is useful in some cases to set the clock initially before starting the NTP daemon `ntpd`. It is also possible to run `ntpdate` from a `cron` script. However, it is important to note that `ntpdate` with contrived `cron` scripts is no substitute for the NTP daemon, which uses sophisticated algorithms to maximize accuracy and reliability while minimizing resource use. Finally, since `ntpdate` does not discipline the host clock frequency as does `ntpd`, the accuracy using `ntpdate` is limited.

Time adjustments are made by `ntpdate` in one of two ways. If `ntpdate` determines the clock is in error more than 0.5 second it will simply step the time by calling the system `settimeofday()` routine. If the error is less than 0.5 seconds, it will slew the time by calling the system `adjtime()` routine. The latter technique is less disruptive and more accurate when the error is small, and works quite well when `ntpdate` is run by `cron` every hour or two.

`ntpdate` will, if the `-u` flag was not specified, decline to set the date if an NTP server daemon (e.g., `ntpd`) is running on the same host. When running `ntpdate` on a regular basis from `cron` as an alternative to running a daemon, doing so once every hour or two will result in precise enough timekeeping to avoid stepping the clock.

Note that in contexts where a host name is expected, a `-4` qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a `-6` qualifier forces DNS resolution to the IPv6 namespace.

If NetInfo support is compiled into `ntpdate`, then the `server` argument is optional if `ntpdate` can find a time server in the NetInfo configuration for `ntpd`.

* * *

#### Command Line Options

<code>**-4**</code>
: Force DNS resolution of following host names on the command line to the IPv4 namespace.

<code>**-6**</code>
: Force DNS resolution of following host names on the command line to the IPv6 namespace.

<code>**-a _key_**</code>
: Enable the authentication function and specify the key identifier to be used for authentication as the argument <code>_key_</code>. The keys and key identifiers must match in both the client and server key files. The default is to disable the authentication function.

<code>**-B**</code>
: Force the time to always be slewed using the `adjtime()` system call, even if the measured offset is greater than +-500 ms. The default is to step the time using `settimeofday()` if the offset is greater than +-500 ms. Note that, if the offset is much greater than +-500 ms in this case, that it can take a long time (hours) to slew the clock to the correct value. During this time. the host should not be used to synchronize clients.

<code>**-b**</code>
: Force the time to be stepped using the `settimeofday()` system call, rather than slewed (default) using the `adjtime()` system call. This option should be used when called from a startup file at boot time.

<code>**-d**</code>
: Enable the debugging mode, in which `ntpdate` will go through all the steps, but not adjust the local clock and using an unprivileged port. Information useful for general debugging will also be printed.

<code>**-e _authdelay_**</code>
: Specify the processing delay to perform an authentication function as the value <code>_authdelay_</code>, in seconds and fraction (see `ntpd` for details). This number is usually small enough to be negligible for most purposes, though specifying a value may improve timekeeping on very slow CPUs.

<code>**-k _keyfile_**</code>
: Specify the path for the authentication key file as the string <code>_keyfile_</code>. The default is `/etc/ntp.keys`. This file should be in the format described in <code>ntpd</code>.

<code>**-o _version_**</code>
: Specify the NTP version for outgoing packets as the integer <code>_version_</code>, which can be <code>1, 2, 3</code> or <code>4</code>. The default is <code>4</code>. This allows `ntpdate` to be used with older NTP versions.

<code>**-p _samples_**</code>
: Specify the number of samples to be acquired from each server as the integer <code>_samples_</code>, with values from `1` to `8` inclusive. The default is `4`.

<code>**-q**</code>
: Query only - don't set the clock.

<code>**-s**</code>
: Divert logging output from the standard output (default) to the system <code>syslog</code> facility. This is designed primarily for convenience of `cron` scripts.

<code>**-t _timeout_**</code>
: Specify the maximum time waiting for a server response as the value <code>_timeout_</code>, in seconds and fraction. The value is rounded to a multiple of 0.2 seconds. The default is `2` seconds, a value suitable for polling across a LAN.

<code>**-u**</code>
: Direct `ntpdate` to use an unprivileged port for outgoing packets. This is most useful when behind a firewall that blocks incoming traffic to privileged ports, and you want to synchronize with hosts beyond the firewall. Note that the `-d` option always uses unprivileged ports.

<code>**-_v_**</code>
: Be verbose. This option will cause `ntpdate`'s version identification string to be logged.

* * *

#### Diagnostics

`ntpdate`'s exit status is zero if it finds a server and updates the clock, and nonzero otherwise.

* * *

#### Files

`/etc/ntp.keys` - encryption keys used by `ntpdate`.

* * *

#### Bugs

The slew adjustment is actually 50% larger than the measured offset, since this (it is argued) will tend to keep a badly drifting clock more accurate. This is probably not a good idea and may cause a troubling hunt for some values of the kernel variables `tick` and `tickadj`.