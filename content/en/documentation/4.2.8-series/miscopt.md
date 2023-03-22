---
title: "Miscellaneous Commands and Options"
description: "Descriptions of miscellaneous commands and options for configuring NTP."
type: archives
aliases:
    - /current-stable/miscopt/
---


![gif](/documentation/pic/boom3.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

We have three, now looking for more.

* * *

#### Commands and Options

<code>**broadcastdelay _delay_**</code>

: In broadcast and multicast modes, means are required to determine the network delay between the server and client. Ordinarily, this is done automatically by the initial calibration exchanges between the client and server. In some cases, the exchange might not be possible due to network or server access controls. The value of <code>_delay_</code> is by default zero, in which case the exchange is enabled. If <code>_delay_</code> is greater than zero, it becomes the roundtrip delay (s), as measured by the Unix <code>ping</code> program, and the exchange is disabled.

<code>**driftfile _driftfile_**</code>

: This command specifies the complete path and name of the file used to record the frequency of the local clock oscillator. This is the same operation as the <code>-f</code> command line option. This command is mutually exclusive with the <code>freq</code> option of the <code>tinker</code> command.

: If the file exists, it is read at startup in order to set the initial frequency and then updated once per hour or more with the current frequency computed by the daemon. If the file name is specified, but the file itself does not exist, the starts with an initial frequency of zero and creates the file when writing it for the first time. If this command is not given, the daemon will always start with an initial frequency of zero.

: The file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). The file is updated by first writing the current drift value into a temporary file and then renaming this file to replace the old version.

<code>**dscp _dscp_**</code>

: This command specifies the Differentiated Services Code Point (DSCP) value that is used in sent NTP packets. The default value is 46 for Expedited Forwarding (EF).

<code>**enable [auth | bclient | calibrate | kernel | mode7 | monitor | ntp | stats | unpeer_crypto_early | unpeer_crypto_nak_early | unpeer_digest_early]**</code>
: <code>**disable [auth | bclient | calibrate | kernel | mode7 | monitor | ntp | stats | unpeer_crypto_early | unpeer_crypto_nak_early | unpeer_digest_early]**</code>

: Provides a way to enable or disable various system options. Flags not mentioned are unaffected. Note that most of these flags can be modified remotely using [<code>ntpq</code>](/documentation/4.2.8-series/ntpq/) utility program's <code>:config</code> and <code>config-from-file</code> commands.

&emsp;<code>auth</code>
: Enables the server to synchronize with unconfigured peers only if the peer has been correctly authenticated using either public key or private key cryptography. The default for this flag is enable.

&emsp;<code>bclient</code>
: Enables the server to listen for a message from a broadcast or multicast server, as in the <code>multicastclient</code> command with default address. The default for this flag is disable.

&emsp;<code>calibrate</code>
: Enables the calibrate feature for reference clocks. The default for this flag is disable.

&emsp;<code>kernel</code>
: Enables the kernel time discipline, if available. The default for this flag is enable if support is available, otherwise disable.

&emsp;<code>mode7</code>
: Enables processing of NTP mode 7 implementation-specific requests which are used by the deprecated <code>ntpdc</code> program. The default for this flag is disable. This flag is excluded from runtime configuration using <code>ntpq</code>. The <code>ntpq</code> program provides the same capabilities as <code>ntpdc</code> using standard mode 6 requests.

&emsp;<code>monitor</code>
: Enables the monitoring facility. See the [<code>ntpq</code> program](/documentation/4.2.8-series/ntpq/) and the <code>monstats</code> and <code>mrulist</code> commands, as well as the [Access Control Options](/documentation/4.2.8-series/accopt/) for details. The monitoring facility is also enabled by the presence of [<code>limited</code>](/documentation/4.2.8-series/accopt/) in any <code>restrict</code> commands. The default for this flag is enable.

&emsp;<code>ntp</code>
: Enables time and frequency discipline. In effect, this switch opens and closes the feedback loop, which is useful for testing. The default for this flag is enable.

&emsp;<code>stats</code>
: Enables the statistics facility. See the [Monitoring Options](/documentation/4.2.8-series/monopt/) page for further information. The default for this flag is enabled. This flag is excluded from runtime configuration using <code>ntpq</code>.

&emsp;<code>unpeer_crypto_early</code>
: Enables the early resetting of an association in case of a crypto failure. This is generally a feature, but it can be used in a DoS attack. If you are seeing these packets being used as a DoS attack against your server, you should disable this flag. The default for this flag is enabled. This flag is excluded from runtime configuration using <code>ntpq</code>.

&emsp;<code>unpeer_crypto_nak_early</code>
: Enables the early resetting of an association in case of a crypto_NAK message. This is generally a feature, but it can be used in a DoS attack. If you are seeing these packets being used as a DoS attack against your server, you should disable this flag. The default for this flag is enabled. This flag is excluded from runtime configuration using <code>ntpq</code>.

&emsp;<code>unpeer_digest_early</code>
: Enables the early resetting of an association in case of an autokey digest failur. This is generally a feature, but it can be used in a DoS attack. If you are seeing these packets being used as a DoS attack against your server, you should disable this flag. The default for this flag is enabled. This flag is excluded from runtime configuration using <code>ntpq</code>.

<code>**includefile _includefile_**</code>
: This command allows additional configuration commands to be included from a separate file. Include files may be nested to a depth of five; upon reaching the end of any include file, command processing resumes in the previous configuration file. This option is useful for sites that run <code>ntpd</code> on multiple hosts, with (mostly) common options (e.g., a restriction list).

<code>**interface [listen | ignore | drop] [all | ipv4 | ipv6 | wildcard | _name_ | _address_[/_prefixlen_]]**</code>

: This command controls which network addresses <code>ntpd</code> opens, and whether input is dropped without processing. The first parameter determines the action for addresses which match the second parameter. That parameter specifies a class of addresses, or a specific interface name, or an address. In the address case, <code>_prefixlen_</code> determines how many bits must match for this rule to apply. <code>ignore</code> prevents opening matching addresses, <code>drop</code> causes <code>ntpd</code> to open the address and drop all received packets without examination. Multiple <code>interface</code> commands can be used. The last rule which matches a particular address determines the action for it. <code>interface</code> commands are disabled if any [<code>-I</code>](/documentation/4.2.8-series/ntpd/#command-line-options), [<code>--interface</code>](/documentation/4.2.8-series/ntpd/#command-line-options), [<code>-L</code>](/documentation/4.2.8-series/ntpd/#command-line-options), or [<code>--novirtualips</code>](/documentation/4.2.8-series/ntpd/#command-line-options) command-line options are used. If none of those options are used and no <code>interface</code> actions are specified in the configuration file, all available network addresses are opened. The <code>nic</code> command is an alias for <code>interface</code>.

<code>**leapfile _leapfile_ [checkhash|ignorehash]**</code>

: This command loads the IERS leapseconds file and initializes the leapsecond values for the next leapsecond time, expiration time and TAI offset. The file can be obtained directly from the IERS at https://hpiers.obspm.fr/iers/bul/bulc/ntp/leap-seconds.list. <code>ignorehash</code> instructs <code>ntpd</code> to ignore the hash signature on the file, <code>checkhash</code> (which is the default when omitted) needs a hash line in the file to be valid. Files without any hash signature are loaded in both cases.

: The <code>_leapfile_</code> is scanned when <code>ntpd</code> processes the <code>leapfile</code> directive or when <code>ntpd</code> detects that <code>_leapfile_</code> has changed. <code>ntpd</code> checks once a day to see if the <code>_leapfile_</code> has changed.

: While not strictly a security function, the Autokey protocol provides means to securely retrieve the current or updated leapsecond values from a server.

<code>**leapsmearinterval _seconds_**</code>

: This EXPERIMENTAL option is only available if <code>ntpd</code> was built with the <code>-\-enable-leap-smear</code> option to the <code>configure</code> script. It specifies the interval over which a leap second correction will be applied. Recommended values for this option are between 7200 (2 hours) and 86400 (24 hours). **DO NOT USE THIS OPTION ON PUBLIC-ACCESS SERVERS!** See [Bug 2855](https://bugs.ntp.org/show_bug.cgi?id=2855) for more information.

<code>**logconfig _configkeyword_**</code>

: This command controls the amount and type of output written to the system <code>syslog</code> facility or the alternate <code>logfile</code> log file. All <code>_configkeyword_</code> keywords can be prefixed with <code>=</code>, <code>+</code> and <code>-</code>, where <code>=</code> sets the <code>syslogmask</code>, <code>+</code> adds and <code>-</code> removes messages. <code>syslog messages</code> can be controlled in four classes (<code>clock</code>, <code>peer</code>, <code>sys</code> and <code>sync</code>). Within these classes four types of messages can be controlled: informational messages (<code>info</code>), event messages (<code>events</code>), statistics messages (<code>statistics</code>) and status messages (<code>status</code>).

: Configuration keywords are formed by concatenating the message class with the event class. The <code>all</code> prefix can be used instead of a message class. A message class may also be followed by the <code>all</code> keyword to enable/disable all messages of the respective message class. By default, <code>logconfig</code> output is set to <code>allsync</code>.

: Thus, a minimal log configuration could look like this:

: &emsp;`logconfig=syncstatus +sysevents`

: This would just list the synchronizations state of <code>ntpd</code> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

: &emsp;`logconfig=syncall +clockall`

: This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

<code>**logfile _logfile_**</code>

: This command specifies the location of an alternate log file to be used instead of the default system <code>syslog</code> facility. This is the same operation as the <code>-l</code> command line option.

<code>**mru [maxdepth _count_ | maxmem _kilobytes_ | mindepth _count_ | maxage _seconds_ | initalloc _count_ | initmem _kilobytes_ | incalloc _count_ | incmem _kilobytes_]**</code>

: Controls size limits of the monitoring facility Most Recently Used [(MRU) list](/documentation/4.2.8-series/ntpq/#control-message-commands) of client addresses, which is also used by the [rate control facility](/documentation/4.2.8-series/accopt/).

&emsp;<code>maxdepth _count_</code>  

&emsp;<code>maxmem _kilobytes_</code>
: Equivalent upper limits on the size of the MRU list, in terms of entries or kilobytes. The actual limit will be up to <code>incalloc</code> entries or <code>incmem</code> kilobytes larger. As with all of the <code>mru</code> options offered in units of entries or kilobytes, if both <code>maxdepth</code> and <code>maxmem</code> are used, the last one used controls. The default is 1024 kilobytes.

&emsp;<code>mindepth _count_</code>
: Lower limit on the MRU list size. When the MRU list has fewer than <code>mindepth</code> entries, existing entries are never removed to make room for newer ones, regardless of their age. The default is 600 entries.

&emsp;<code>maxage _seconds_</code>
: Once the MRU list has <code>mindepth</code> entries and an additional client address is to be added to the list, if the oldest entry was updated more than <code>maxage</code> seconds ago, that entry is removed and its storage reused. If the oldest entry was updated more recently, the MRU list is grown, subject to <code>maxdepth</code>/<code>maxmem</code>. The default is 64 seconds.

&emsp;<code>initalloc _count_</code> 

&emsp;<code>initmem _kilobytes_</code>
: Initial memory allocation at the time the monitoring facility is first enabled, in terms of entries or kilobytes. The default is 4 kilobytes.

&emsp;<code>incalloc _count_</code>  

&emsp;<code>incmem _kilobytes_</code>
: Size of additional memory allocations when growing the MRU list, in entries or kilobytes. The default is 4 kilobytes.

<code>**nonvolatile _threshold_**</code>
: Specify the <code>_threshold_</code> in seconds to write the frequency file, with default of 1e-7 (0.1 PPM). The frequency file is inspected each hour. If the difference between the current frequency and the last value written exceeds the threshold, the file is written and the <code>_threshold_</code> becomes the new threshold value. If the threshold is not exceeded, it is reduced by half. This is intended to reduce the frequency of unnecessary file writes for embedded systems with nonvolatile memory.

<code>**phone _dial_ ...**</code>
: This command is used in conjunction with the ACTS modem driver (type 18) or the JJY driver (type 40 mode 100 - 180). For the ACTS modem driver (type 18), the arguments consist of a maximum of 10 telephone numbers used to dial USNO, NIST or European time services. For the JJY driver (type 40 mode 100 - 180), the argument is one telephone number used to dial the telephone JJY service. The Hayes command ATDT is normally prepended to the number, which can contain other modem control codes as well.

<code>**pollskewlist [_poll_ _early late_]...[default _early late_]**</code>
: Enable skewing of our poll requests to our servers. <code>_poll_</code> is a number between 3 and 17 inclusive, identifying a specific poll interval. A poll interval is 2<sup>^</sup>n seconds in duration, so a poll value of 3 corresponds to 8 seconds and a poll interval of 17 corresponds to 131,072 seconds, or about a day and a half. The next two numbers must be between 0 and one-half of the poll interval, inclusive. `early` specifies how early the poll may start, while `late` specifies how late the poll may be delayed. With no arguments, internally specified default values are chosen.

<code>**reset [allpeers] [auth] [ctl] [io] [mem] [sys] [timer]**</code>
: Reset one or more groups of counters maintained by ntpd and exposed by <code>ntpq</code> and <code>ntpdc</code>.

<code>**rlimit [memlock _Nmegabytes_ | stacksize _N4kPages_ | filenum _Nfiledescriptors_]**</code>
: This command alters certain process storage allocation limits, and is only available on some operating systems. Options are as follows:

&emsp;<code>memlock _Nmegabytes_</code>
: Specify the number of megabytes of memory that should be allocated and locked. Probably only available under Linux, this option may be useful when dropping root (the <code>-i</code> option). The default is 32 megabytes on non-Linux machines, and -1 under Linux. -1 means "do not lock the process into memory". 0 means "lock whatever memory the process wants into memory".

&emsp;<code>stacksize _N4kPages_</code>
: Specifies the maximum size of the process stack on systems with the <code>mlockall()</code> function. Defaults to 50 4k pages (200 4k pages in OpenBSD).

&emsp;<code>filenum _Nfiledescriptors_</code>
: Specifies the maximum number of file descriptors ntp may have open at the same time. Defaults to system default.

<code>**saveconfigdir _directory_path_**</code>
: Specify the directory in which to write configuration snapshots requested with <code>ntpq</code>'s [saveconfig](/documentation/4.2.8-series/ntpq/#control-message-commands) command. If <code>saveconfigdir</code> does not appear in the configuration file, saveconfig requests are rejected by ntpd.

<code>**setvar _variable_ [default]**</code>
: This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <code>_name_ = _value_</code> is followed by the <code>default</code> keyword, the variable will be listed as part of the default system variables (<code>ntpq rv</code> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <code>setvar</code> mechanism. There are three special variables that contain the names of all variable of the same group. The <code>sys_var_list</code> holds the names of all system variables. The <code>peer_var_list</code> holds the names of all peer variables and the <code>clock_var_list</code> holds the names of the reference clock variables.

<code>**tinker [allan _allan_ | dispersion _dispersion_ | freq _freq_ | huffpuff _huffpuff_ | panic _panic_ | step _step_ | stepout _stepout_]**</code>
: This command alters certain system variables used by the clock discipline algorithm. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs. Options are as follows:

&emsp;<code>allan _allan_</code>
: Specifies the Allan intercept, which is a parameter of the PLL/FLL clock discipline algorithm, in log2 seconds with default 11 (2048 s).

&emsp;<code>dispersion _dispersion_</code>
: Specifies the dispersion increase rate in parts-per-million (PPM) with default 15 PPM.

&emsp;<code>freq _freq_</code>
: Specifies the frequency offset in parts-per-million (PPM). This option is mutually exclusive with the driftfile command.

&emsp;<code>huffpuff _huffpuff_</code>
: Specifies the huff-n'-puff filter span, which determines the most recent interval the algorithm will search for a minimum delay. The lower limit is 900 s (15 min), but a more reasonable value is 7200 (2 hours). See the [Huff-n'-Puff Filter](/documentation/4.2.8-series/huffpuff/) page for further information.

&emsp;<code>panic _panic_</code>
: Specifies the panic threshold in seconds with default 1000 s. If set to zero, the panic sanity check is disabled and a clock offset of any value will be accepted.

&emsp;<code>step _step_</code>
: Specifies the step threshold in seconds. The default without this command is 0.128 s. If set to zero, step adjustments will never occur. Note: The kernel time discipline is disabled if the step threshold is set to zero or greater than 0.5 s. Further details are on the [Clock State Machine](/documentation/4.2.8-series/clock/) page.

&emsp;<code>stepout _stepout_</code>
: Specifies the stepout threshold in seconds. The default without this command is 300 s. Since this option also affects the training and startup intervals, it should not be set less than the default. Further details are on the [Clock State Machine](/documentation/4.2.8-series/clock/) page.

<code>**tos [basedate _date_ | bcpollbstep _poll-gate_ | beacon _beacon_ | ceiling _ceiling_ | cohort {0 | 1} | floor _floor_ | maxclock _maxclock_ | maxdist _maxdist_ | minclock _minclock_ | mindist _mindist_ | minsane _minsane_ | orphan _stratum_ | orphanwait _delay_]**</code>
: This command alters certain system variables used by the the clock selection and clustering algorithms. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs. It can be used to select the quality and quantity of peers used to synchronize the system clock and is most useful in dynamic server discovery schemes. The options are as follows:

&emsp;<code>basedate _date_</code>
: Set NTP and GPS era anchor. <code>_date_</code> is either a date in ISO8601 format (<code>_YYYY-MM-DD_</code>) or an integer giving the days since 1900-01-01, the start of the NTP epoch. <code>ntpd</code> will clamp the system time to an era starting with the begin of this this day (00:00:00Z), covering a range of 2<sup>32</sup> seconds or roughly 136 years. The lowest accepted value is effectively 1970-01-02.

: The GPS era base is the next Sunday on or following the base date, but obviously not before 1980-01-06. GPS time stamps are mapped into the 1024 weeks following the GPS base.

: The default value is derived from the repository or build time stamp, minus 11 days. 1970-01-02 was chosen as lower bound so the _local_ time is always after 1970-01-01,00:00. Some systems get into trouble if this is not the case.

> &emsp;**ATTENTION:** If the system clock is before the effective (implied or specific) basedate, the system clock will be set to the base date once and immediately when <code>ntpd</code> starts. This helps systems that have lost time completely to recover. Though not noticeable under normal conditions, it _can_ happen. Check the logs if starting <code>ntpd</code> causes sudden clock moves.

&emsp;<code>bcpollbstep _poll-gate_</code>
: This option will cause the client to delay believing backward time steps from a broadcast server for <code>bcpollbstep</code> poll intervals. NTP Broadcast networks are expected to be trusted, and if the server's time gets stepped backwards then it's desireable that the clients follow this change as soon as possible. However, in spite of various protections built-in to the broadcast protocol, it is possible that an attacker could perform a carefully-constructed replay attack and cause clients to erroneously step their clocks backward. If the risk of a successful broadcast replay attack is greater than the risk of the clients being out of sync in the event that there is a backward step on the broadcast time servers, this option may be used to cause the clients to delay beliveving backward time steps until _poll-gate_ consecutive polls have been received. The default is 0, which means the client will accept these steps upon receipt. Any value from 0 to 4 can be specified.

&emsp;<code>beacon _beacon_</code>
: The manycast server sends packets at intervals of 64 s if less than <code>maxclock</code> servers are available. Otherwise, it sends packets at the <code>_beacon_</code> interval in seconds. The default is 3600 s. See the [Automatic Server Discovery](/documentation/4.2.8-series/discover/) page for further details.

&emsp;<code>ceiling _ceiling_</code>
: Specify the maximum stratum (exclusive) for acceptable server packets. The default is 16. See the [Automatic Server Discovery](/documentation/4.2.8-series/discover/) page for further details.

&emsp;<code>cohort { 0 | 1 }</code>
: Specify whether (1) or whether not (0) a server packet will be accepted for the same stratum as the client. The default is 0. See the [Automatic Server Discovery](/documentation/4.2.8-series/discover/) page for further details.

&emsp;<code>floor _floor_</code>
: Specify the minimum stratum (inclusive) for acceptable server packets. The default is 1. See the [Automatic Server Discovery](/documentation/4.2.8-series/discover/) page for further details.

&emsp;<code>maxclock _maxclock_</code>
: Specify the maximum number of servers retained by the server discovery schemes. The default is 10. See the [Automatic Server Discovery](/documentation/4.2.8-series/discover/) page for further details.

&emsp;<code>maxdist _maxdistance_</code>
: Specify the synchronization distance threshold used by the clock selection algorithm. The default is 1.5 s. This determines both the minimum number of packets to set the system clock and the maximum roundtrip delay. It can be decreased to improve reliability or increased to synchronize clocks on the Moon or planets.

&emsp;<code>minclock _minclock_</code>
: Specify the number of servers used by the clustering algorithm as the minimum to include on the candidate list. The default is 3. This is also the number of servers to be averaged by the combining algorithm.

&emsp;<code>mindist _mindistance_</code>
: Specify the minimum distance used by the selection and anticlockhop algorithm. Larger values increase the tolerance for outliers; smaller values increase the selectivity. The default is .001 s. In some cases, such as reference clocks with high jitter and a PPS signal, it is useful to increase the value to insure the intersection interval is always nonempty.

&emsp;<code>minsane _minsane_</code>
: Specify the number of servers used by the selection algorithm as the minimum to set the system clock. The default is 1 for legacy purposes; however, for critical applications the value should be somewhat higher but less than <code>minclock</code>.

&emsp;<code>orphan _stratum_</code>
: Specify the orphan stratum with default 16. If less than 16 this is the stratum assumed by the root servers. See the [Orphan Mode](/documentation/4.2.8-series/orphan/) page for further details.

&emsp;<code>orphanwait _delay_</code>
: Specify the delay in seconds from the time all sources are lost until orphan parent mode is enabled with default 300 s (five minutes). During this period, the local clock driver and the modem driver are not selectable, unless marked with the <code>prefer</code> keyword. This allows time for one or more primary sources to become reachable and selectable before using backup sources, and avoids transient use of the backup sources at startup.

<code>**trap _host_address_ [port _port_number_] [interface _interfSace_address_]**</code>
: This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified, a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

: The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started.

<code>**ttl _hop_ ...**</code>
: This command specifies a list of TTL values in increasing order. up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.