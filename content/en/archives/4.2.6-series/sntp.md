---
title: "sntp - Simple Network Time Protocol (SNTP) Client"
type: archives
---

![gif](/archives/pic/dogsnake.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/~mills/pictures.html)

S is for snakeoil.

Last update: 16:31 UTC Wednesday, March 12, 2008

* * *

#### Table of Contents

* [Synopsis](/archives/4.2.6-series/sntp/#synopsis)
* [Description](/archives/4.2.6-series/sntp/#description)
* [Options](/archives/4.2.6-series/sntp/#options)
* [Return Value](/archives/4.2.6-series/sntp/#return-value)
* [Author](/archives/4.2.6-series/sntp/#author)

* * *

#### Synopsis

<tt>sntp [{-h --help -?}][{ -v -V -W }][{-r -a}][-P prompt][-e minerr][-E maxerr][-c count][-d delay][address(es)]</tt>

* * *

#### Description

This program is a Simple Network Time Protocol (SNTP) client that can be used to query a Network Time Protocol (NTP) server and display the time offset of the system clock relative to the server clock. Run as root it can correct the system clock to this offset as well. It can be run as an interactive command or from a script by a <tt>cron</tt> job. The program implements the SNTP protocol defined in RFC-4330, which is a subset of the NTP protocol defined in RFC-1305, but does not provide the sanity checks, access controls, security functions and mitigation algorithms as in the full NTP implementation.

By default, <tt>sntp</tt> writes the local date and time (i.e., not UTC) to the standard output in the format

<tt>1996 Oct 15 20:17:25.123 + 4.567 +/- 0.089 secs</tt>,

where the <tt>+ 4.567 +/- 0.089 secs</tt> indicates the time offset and error bound of the system clock relative to the server clock.

If a NTP server _address_ is explicitly specified, the program sends a single message to the server and waits up to _delay_ seconds for a unicast server message. Otherwise, it sends no message and waits up to _delay_ seconds for a broadcast server message.

* * *

#### Options

<tt>sntp</tt> recognizes the following options:

<dt><tt>-h, --help</tt></dt>

displays usage information.

<dt><tt>-v</tt></dt>

writes diagnostic messages and a limited amount of tracing to standard error. The <tt>-v</tt>, <tt>-V</tt> and <tt>-W</tt> give increasing levels of detail. 

<dt><tt>-r</tt></dt>

steps the system clock to the correct time by the Unix <tt>settimeofday</tt> system call. Requires root privilege. 

<dt><tt>-a</tt></dt>

slews the system clock to the correct time by the Unix <tt>adjtime</tt> system call. Requires root privilege.

<dt><tt>-e _minerr_</tt></dt>

sets the minimum offset to _minerr_ seconds. Measured offsets less than this are ignored. Acceptable values are from 0.001 to 1 with default 0.1 if unicast mode and 0.5 for broadcast mode.

<dt><tt>-E _maxerr_</tt></dt>

sets the maximum offset to _maxerr_ seconds. Measured offsets greater than this are ignored. Acceptable values are from 1 to 60 with default 5.

<dt><tt>P _prompt_</tt></dt>

sets the maximum automatic offset to _maxerr_ seconds. Acceptable values are from 1 to 3600 or <tt>no</tt>, with default 30. If the program is being run interactively, measured offsets greater than this will prompt the user for confirmation. Specifying <tt>no</tt> will disable this and the correction will be made regardless.

<dt><tt>-c _count_</tt></dt>

sets the maximum number of NTP packets required to _count_. Acceptable values are from 1 to 25 in unicast mode and 5 to 25 in broadcast mode. The default is 5 in either mode. 

<dt><tt>-d _delay_</tt></dt>

sets the maximum waiting time in broadcast mode to _delay_ seconds. Acceptable values are from 1 to 3600, with default 15 in unicast mode and 300 in broadcast mode.


* * *

#### Return Value

The program returns an exit status of zero for success and non-zero otherwise.

* * *

#### Author

<tt>sntp</tt> was developed by N.M. Maclaren of the University of Cambridge Computing Service.
