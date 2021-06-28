---
title: "sntp - Simple Network Time Protocol (SNTP) Client"
type: archives
---

![gif](/archives/pic/dogsnake.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/~mills/pictures.html)

S is for snakeoil.

Last update: 1-Apr-2015 11:05 UTC

* * *

#### Table of Contents

* [Synopsis](/archives/4.2.8-series/sntp/#synopsis)
* [Description](/archives/4.2.8-series/sntp/#description)
* [Options](/archives/4.2.8-series/sntp/#options)
* [Return Value](/archives/4.2.8-series/sntp/#return-value)
* [Author](/archives/4.2.8-series/sntp/#author)

* * *

#### Synopsis

<tt>sntp [{--help -?}][{-4 -6}][-a _keynum_][-b _bcaddress_][-B _bctimeout_][-c][-d][-D _debug-level_][-g _delay_][-K _kodfile_][-k _keyfile_][-l _logfile_][-M _steplimit_][-o _ntpver_][-r][-S][-s][-u _uctimeout_][--wait][--version][_address(es)_]</tt>

* * *

#### Description

This program is a Simple Network Time Protocol (SNTP) client that can be used to query a Network Time Protocol (NTP) server and display the time offset of the system clock relative to the server clock. Run as root it can correct the system clock to this offset as well. It can be run as an interactive command or from a script by a <tt>cron</tt> job. The program implements the SNTP client protocol defined in RFC 5905, including the full on-wire protocol but does not provide the sanity checks, access controls, security functions and mitigation algorithms as in the full NTP version 4 specification, also defined in RFC 5905.

By default, <tt>sntp</tt> writes the local date and time (i.e., not UTC) to the standard output in the format

<tt>2011-08-04 00:40:36.642222 (+0000) +0.006611 +/- 0.041061 psp-os1 149.20.68.26 s3 no-leap</tt>

where the <tt>+0.006611 +/- 0.041061</tt> indicates the time offset and error bound of the system clock relative to the server clock, in seconds. The hostname and/or the IP is displayed, as is the stratum of the server. Finally, the leap indicator status is displayed.

If -b _bcaddress_ is not specified, the program sends a single message to each address and waits up to _uctimeout_ (default 5) seconds for a unicast server response. Otherwise, it sends no message and waits up to _bctimeout_ (default 68) seconds for a broadcast NTP message.

* * *

#### Options

<tt>sntp</tt> recognizes the following options:

<dt><tt>-?, --help</tt></dt>

displays usage information. The short form typically requires shell quoting, such as <tt>-\?</tt>, otherwise <tt>?</tt> is consumed by the shell.

<dt><tt>-4, --ipv4</tt></dt>

When resolving hostnames to IP addresses, use IPv4 addresses only.

<dt><tt>-6, --ipv6</tt></dt>

When resolving hostnames to IP addresses, use IPv6 addresses only.

<dt><tt>-a _keynum_, --authentication _keynum_</tt></dt>

Enable authentication with the key ID _keynum_. _keynum_ is a number specified in the keyfile along with an authentication secret (password or digest). See the <tt>-k, --keyfile</tt> option for more details.

<dt><tt>-b _bcaddress_, --broadcast _bcaddress_</tt></dt>

Listen for NTP packets sent to the broadcast or multicast address _bcaddress_, which can be a DNS name or IP address. The default maximum time to listen for broadcasts/multicasts, 68 seconds, can be modified with the <tt>-B, --bctimeout</tt> option.

<dt><tt>-B _bctimeout_, --bctimeout _bctimeout_</tt></dt>

Wait _bctimeout_ seconds for broadcast or multicast NTP message before terminating. The default is 68 seconds, chosen because ntpd typically transmits broadcasts/multicasts every 64 seconds. Note that the short option is <tt>-B</tt>, an uppercase letter B.

<dt><tt>-c, --concurrent</tt></dt>

Concurrently query all addresses returned for hostname. Requests from an NTP client to a single server should never be sent more often than once every two seconds. By default, all addresses resolved from a single hostname are assumed to be for a single instance of ntpd, and therefore sntp will send queries to these addresses one after another, waiting two seconds between queries. This option indicates multiple addresses returned for a hostname are on different machines, so sntp can send concurrent queries. This is appropriate when using *.pool.ntp.org, for example.

<dt><tt>-d, --debug-level</tt></dt>

Increase debug verbosity level by one. May be specified multiple times. See also the <tt>-D, --set-debug-level</tt> option.

<dt><tt>-D _debug-level_, --set-debug-level _debug-level_</tt></dt>

Set the debug verbosity level to _debug-level_. The default level is zero. Note that the short option is <tt>-D</tt>, an uppercase letter D. See also the <tt>-d, --debug-level</tt> option.

<dt><tt>-g _delay_, --gap _delay_</tt></dt>

Specify the _delay_ in milliseconds between outgoing queries, defaulting to 50. <tt>sntp</tt> sends queries to all provided hostnames/addresses in short succession, and by default terminates once the first valid response is received. With multiple time sources provided, all but one will not be used. To limit the number of queries whose responses will not be used, each query is separated from the preceding one by _delay_ milliseconds, to allow time for responses to earlier queries to be received. A larger _delay_ reduces the query load on the time sources, increasing the time to receive a valid response if the first source attempted is slow or unreachable.

<dt><tt>-K _kodfile_, --kod _kodfile_</tt></dt>

Specifies the filename _kodfile_ to be used for the persistent history of KoD (Kiss Of Death, or rate-limiting) responses received from servers. The default is <tt>/var/db/ntp-kod</tt>. If the file does not exist, a warning message will be displayed. The file will not be created. Note that the short option is <tt>-K</tt>, an uppercase letter K.

<dt><tt>-k _keyfile_, --keyfile _keyfile_</tt></dt>

Specifies the filename _keyfile_ used with the <tt>-a</tt>/<tt>--authentication</tt> option. The format of the file is described on the [<tt>ntp-keygen</tt> page](/archives/4.2.8-series/keygen).

<dt><tt>-l _logfile_, --filelog _logfile_</tt></dt>

Specifies the filename in which to append a copy of status messages, which also appear on the terminal.

<dt><tt>-M _steplimit_, --steplimit _steplimit_</tt></dt>

If both <tt>-S</tt>/<tt>--step</tt> and <tt>-s</tt>/<tt>--slew</tt> options are provided, an offset of less than _steplimit_ milliseconds will be corrected by slewing the clock using adjtime(), while an offset of _steplimit_ or more will be corrected by setting the clock to the corrected time. Note that the short option is <tt>-M</tt>, an uppercase letter M.

<dt><tt>-o _ntpver_, --ntpversion _ntpver_</tt></dt>

Specifies the NTP protocol version number _ntpver_ to include in requests, default 4. This option is rarely useful.

<dt><tt>-r, --usereservedport</tt></dt>

By default, <tt>sntp</tt> uses a UDP source port number selected by the operating system. When this option is used, the reserved NTP port 123 is used, which most often requires <tt>sntp</tt> be invoked as the superuser (commonly "root"). This can help identify connectivity failures due to port-based firewalling which affect <tt>ntpd</tt>, which always uses source port 123.

<dt><tt>-S, --step</tt></dt>

By default, <tt>sntp</tt> displays the clock offset but does not attempt to correct it. This option enables offset correction by stepping, that is, directly setting the clock to the corrected time. This typically requires <tt>sntp</tt> be invoked as the superuser ("root"). Note that the short option is <tt>-S</tt>, an uppercase letter S.

<dt><tt>-s, --slew</tt></dt>

By default, <tt>sntp</tt> displays the clock offset but does not attempt to correct it. This option enables offset correction by slewing using adjtime(), which changes the rate of the clock for a period long enough to accomplish the required offset (phase) correction. This typically requires <tt>sntp</tt> be invoked as the superuser ("root").

<dt><tt>-u _uctimeout_, --uctimeout _uctimeout_</tt></dt>

Specifies the maximum time _uctimeout_ in seconds to wait for a unicast response before terminating.

<dt><tt>--wait</tt></dt>

When neither <tt>-S</tt>/<tt>--step</tt> nor <tt>-s</tt>/<tt>--slew</tt> options are provided, <tt>sntp</tt> will by default terminate after the first valid response is received. This option causes <tt>sntp</tt> to instead wait for all pending queries' responses.

<dt><tt>--version</tt></dt>

Display the <tt>sntp</tt> program's version number and the date and time it was compiled.

* * *

#### Return Value

The program returns an exit status of zero for if a valid response is received and non-zero otherwise.

* * *

#### Author

This <tt>sntp</tt> was originally developed by Johannes Maximilian Kuehn. Harlan Stenn and Dave Hart modified it to query more than one server at a time. See the file <tt>ChangeLog</tt> in the distribution for details.