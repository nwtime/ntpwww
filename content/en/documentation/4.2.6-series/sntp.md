---
title: "sntp - Simple Network Time Protocol (SNTP) Client"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/dogsnake.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

S is for snakeoil.

Last update: 16:31 UTC Wednesday, March 12, 2008

* * *

#### Table of Contents

* [Synopsis](/documentation/4.2.6-series/sntp/#synopsis)
* [Description](/documentation/4.2.6-series/sntp/#description)
* [Options](/documentation/4.2.6-series/sntp/#options)
* [Return Value](/documentation/4.2.6-series/sntp/#return-value)
* [Author](/documentation/4.2.6-series/sntp/#author)

* * *

#### Synopsis

<code>sntp [{-h --help -?}][{ -v -V -W }][{-r -a}][-P prompt][-e minerr][-E maxerr][-c count][-d delay][address(es)]</code>

* * *

#### Description

This program is a Simple Network Time Protocol (SNTP) client that can be used to query a Network Time Protocol (NTP) server and display the time offset of the system clock relative to the server clock. Run as root it can correct the system clock to this offset as well. It can be run as an interactive command or from a script by a <code>cron</code> job. The program implements the SNTP protocol defined in RFC-4330, which is a subset of the NTP protocol defined in RFC-1305, but does not provide the sanity checks, access controls, security functions and mitigation algorithms as in the full NTP implementation.

By default, <code>sntp</code> writes the local date and time (i.e., not UTC) to the standard output in the format

`1996 Oct 15 20:17:25.123 + 4.567 +/- 0.089 secs`,

where the <code>+ 4.567 +/- 0.089 secs</code> indicates the time offset and error bound of the system clock relative to the server clock.

If a NTP server _address_ is explicitly specified, the program sends a single message to the server and waits up to _delay_ seconds for a unicast server message. Otherwise, it sends no message and waits up to _delay_ seconds for a broadcast server message.

* * *

#### Options

<code>sntp</code> recognizes the following options:

<code>**-h, -\-help**</code>

: displays usage information.

<code>**-v**</code>

: writes diagnostic messages and a limited amount of tracing to standard error. The <code>-v</code>, <code>-V</code> and <code>-W</code> give increasing levels of detail. 

<code>**-r**</code>

: steps the system clock to the correct time by the Unix <code>settimeofday</code> system call. Requires root privilege. 

<code>**-a**</code>

: slews the system clock to the correct time by the Unix <code>adjtime</code> system call. Requires root privilege.

<code>**-e _minerr_**</code>

: sets the minimum offset to <code>_minerr_</code> seconds. Measured offsets less than this are ignored. Acceptable values are from 0.001 to 1 with default 0.1 if unicast mode and 0.5 for broadcast mode.

<code>**-E _maxerr_**</code>

: sets the maximum offset to <code>_maxerr_</code> seconds. Measured offsets greater than this are ignored. Acceptable values are from 1 to 60 with default 5.

<code>**P _prompt_**</code>

: sets the maximum automatic offset to <code>_maxerr_</code> seconds. Acceptable values are from 1 to 3600 or <code>no</code>, with default 30. If the program is being run interactively, measured offsets greater than this will prompt the user for confirmation. Specifying <code>no</code> will disable this and the correction will be made regardless.

<code>**-c _count_**</code>

: sets the maximum number of NTP packets required to <code>_count_</code>. Acceptable values are from 1 to 25 in unicast mode and 5 to 25 in broadcast mode. The default is 5 in either mode. 

<code>**-d _delay_**</code>

: sets the maximum waiting time in broadcast mode to <code>_delay_</code> seconds. Acceptable values are from 1 to 3600, with default 15 in unicast mode and 300 in broadcast mode.

* * *

#### Return Value

The program returns an exit status of zero for success and non-zero otherwise.

* * *

#### Author

<code>sntp</code> was developed by N.M. Maclaren of the University of Cambridge Computing Service.