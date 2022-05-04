---
title: "sntp - Simple Network Time Protocol (SNTP) Client"
type: archives
---

![gif](/documentation/pic/dogsnake.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

S is for snakeoil.

* * *

#### Table of Contents

* [Synopsis](/documentation/4.2.8-series/sntp/#synopsis)
* [Description](/documentation/4.2.8-series/sntp/#description)
* [Options](/documentation/4.2.8-series/sntp/#options)
* [Return Value](/documentation/4.2.8-series/sntp/#return-value)
* [Author](/documentation/4.2.8-series/sntp/#author)

* * *

#### Synopsis

<code>sntp [{--help -?}][{-4 -6}][-a _keynum_][-b _bcaddress_][-B _bctimeout_][-c][-d][-D _debug-level_][-g _delay_][-K _kodfile_][-k _keyfile_][-l _logfile_][-M _steplimit_][-o _ntpver_][-r][-S][-s][-u _uctimeout_][--wait][--version][_address(es)_]</code>

* * *

#### Description

This program is a Simple Network Time Protocol (SNTP) client that can be used to query a Network Time Protocol (NTP) server and display the time offset of the system clock relative to the server clock. Run as root it can correct the system clock to this offset as well. It can be run as an interactive command or from a script by a <code>cron</code> job. The program implements the SNTP client protocol defined in [RFC 5905](/reflib/rfc/rfc5905.txt), including the full on-wire protocol but does not provide the sanity checks, access controls, security functions and mitigation algorithms as in the full NTP version 4 specification, also defined in RFC 5905.

By default, <code>sntp</code> writes the local date and time (i.e., not UTC) to the standard output in the format

`2011-08-04 00:40:36.642222 (+0000) +0.006611 +/- 0.041061 psp-os1 149.20.68.26 s3 no-leap`

where the <code>+0.006611 +/- 0.041061</code> indicates the time offset and error bound of the system clock relative to the server clock, in seconds. The hostname and/or the IP is displayed, as is the stratum of the server. Finally, the leap indicator status is displayed.

If <code>-b _bcaddress_</code> is not specified, the program sends a single message to each address and waits up to <code>_uctimeout_</code> (default 5) seconds for a unicast server response. Otherwise, it sends no message and waits up to <code>_bctimeout_</code> (default 68) seconds for a broadcast NTP message.

* * *

#### Options

<code>sntp</code> recognizes the following options:

<code>**-?, -\-help**</code>

: Displays usage information. The short form typically requires shell quoting, such as <code>-\?</code>, otherwise <code>?</code> is consumed by the shell.

<code>**-4, -\-ipv4**</code>

: When resolving hostnames to IP addresses, use IPv4 addresses only.

<code>**-6, -\-ipv6**</code>

: When resolving hostnames to IP addresses, use IPv6 addresses only.

<code>**-a _keynum_, -\-authentication _keynum_**</code>

: Enable authentication with the key ID <code>_keynum_</code>. <code>_keynum_</code> is a number specified in the keyfile along with an authentication secret (password or digest). See the <code>-k, --keyfile</code> option for more details.

<code>**-b _bcaddress_, -\-broadcast _bcaddress_**</code>

: Listen for NTP packets sent to the broadcast or multicast address <code>_bcaddress_</code>, which can be a DNS name or IP address. The default maximum time to listen for broadcasts/multicasts, 68 seconds, can be modified with the <code>-B, --bctimeout</code> option.

<code>**-B _bctimeout_, -\-bctimeout _bctimeout_**</code>

: Wait <code>_bctimeout_</code> seconds for broadcast or multicast NTP message before terminating. The default is 68 seconds, chosen because <code>ntpd</code> typically transmits broadcasts/multicasts every 64 seconds. Note that the short option is <code>-B</code>, an uppercase letter B.

<code>**-c, -\-concurrent**</code>

: Concurrently query all addresses returned for hostname. Requests from an NTP client to a single server should never be sent more often than once every two seconds. By default, all addresses resolved from a single hostname are assumed to be for a single instance of <code>ntpd</code>, and therefore <code>sntp</code> will send queries to these addresses one after another, waiting two seconds between queries. This option indicates multiple addresses returned for a hostname are on different machines, so <code>sntp</code> can send concurrent queries. This is appropriate when using <code>*.pool.ntp.org</code>, for example.

<code>**-d, -\-debug-level**</code>

: Increase debug verbosity level by one. May be specified multiple times. See also the <code>-D, --set-debug-level</code> option.

<code>**-D _debug-level_, -\-set-debug-level _debug-level_**</code>

: Set the debug verbosity level to <code>_debug-level_</code>. The default level is zero. Note that the short option is <code>-D</code>, an uppercase letter D. See also the <code>-d, --debug-level</code> option.

<code>**-g _delay_, -\-gap _delay_**</code>

: Specify the <code>_delay_</code> in milliseconds between outgoing queries, defaulting to 50. <code>sntp</code> sends queries to all provided hostnames/addresses in short succession, and by default terminates once the first valid response is received. With multiple time sources provided, all but one will not be used. To limit the number of queries whose responses will not be used, each query is separated from the preceding one by _delay_ milliseconds, to allow time for responses to earlier queries to be received. A larger _delay_ reduces the query load on the time sources, increasing the time to receive a valid response if the first source attempted is slow or unreachable.

<code>**-K _kodfile_, -\-kod _kodfile_**</code>

: Specifies the filename <code>_kodfile_</code> to be used for the persistent history of KoD (Kiss Of Death, or rate-limiting) responses received from servers. The default is <code>/var/db/ntp-kod</code>. If the file does not exist, a warning message will be displayed. The file will not be created. Note that the short option is <code>-K</code>, an uppercase letter K.

<code>**-k _keyfile_, -\-keyfile _keyfile_**</code>

: Specifies the filename <code>_keyfile_</code> used with the <code>-a</code> / <code>-\-authentication</code> option. The format of the file is described on the [<code>ntp-keygen</code> page](/documentation/4.2.8-series/keygen/).

<code>**-l _logfile_, -\-filelog _logfile_**</code>

: Specifies the filename in which to append a copy of status messages, which also appear on the terminal.

<code>**-M _steplimit_, -\-steplimit _steplimit_**</code>

: If both <code>-S</code> / <code>-\-step</code> and <code>-s</code> / <code>-\-slew</code> options are provided, an offset of less than <code>_steplimit_</code> milliseconds will be corrected by slewing the clock using adjtime(), while an offset of <code>_steplimit_</code> or more will be corrected by setting the clock to the corrected time. Note that the short option is <code>-M</code>, an uppercase letter M.

<code>**-o _ntpver_, -\-ntpversion _ntpver_**</code>

: Specifies the NTP protocol version number <code>_ntpver_</code> to include in requests, default 4. This option is rarely useful.

<code>**-r, -\-usereservedport**</code>

: By default, <code>sntp</code> uses a UDP source port number selected by the operating system. When this option is used, the reserved NTP port 123 is used, which most often requires <code>sntp</code> be invoked as the superuser (commonly "root"). This can help identify connectivity failures due to port-based firewalling which affect <code>ntpd</code>, which always uses source port 123.

<code>**-S, -\-step**</code>

: By default, <code>sntp</code> displays the clock offset but does not attempt to correct it. This option enables offset correction by stepping, that is, directly setting the clock to the corrected time. This typically requires <code>sntp</code> be invoked as the superuser ("root"). Note that the short option is <code>-S</code>, an uppercase letter S.

<code>**-s, -\-slew**</code>

: By default, <code>sntp</code> displays the clock offset but does not attempt to correct it. This option enables offset correction by slewing using <code>adjtime()</code>, which changes the rate of the clock for a period long enough to accomplish the required offset (phase) correction. This typically requires <code>sntp</code> be invoked as the superuser ("root").

<code>**-u _uctimeout_, -\-uctimeout _uctimeout_**</code>

: Specifies the maximum time <code>_uctimeout_</code> in seconds to wait for a unicast response before terminating.

<code>**-\-wait**</code>

: When neither <code>-S</code> / <code>-\-step</code> nor <code>-s</code> / <code>-\-slew</code> options are provided, <code>sntp</code> will by default terminate after the first valid response is received. This option causes <code>sntp</code> to instead wait for all pending queries' responses.

<code>**-\-version**</code>

: Display the <code>sntp</code> program's version number and the date and time it was compiled.

* * *

#### Return Value

The program returns an exit status of zero if a valid response is received and non-zero otherwise.

* * *

#### Author

This <code>sntp</code> was originally developed by Johannes Maximilian Kuehn. Harlan Stenn and Dave Hart modified it to query more than one server at a time. See the file <code>ChangeLog</code> in the distribution for details.