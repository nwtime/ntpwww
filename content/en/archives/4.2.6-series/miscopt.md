---
title: "Miscellaneous Options"
type: archives
---

![gif](/archives/pic/boom3.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

We have three, now looking for more.

Last update: 13-Nov-2009 19:08 UTC

* * *

<code>**broadcastdelay _seconds_**</code>

: The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the client and server. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate.

<code>**driftfile _driftfile_ { _tolerance_ ]**</code>

: This command specifies the complete path and name of the file used to record the frequency of the local clock oscillator. This is the same operation as the <code>-f</code> command linke option. If the file exists, it is read at startup in order to set the initial frequency and then updated once per hour or more with the current frequency computed by the daemon. If the file name is specified, but the file itself does not exist, the starts with an initial frequency of zero and creates the file when writing it for the first time. If this command is not given, the daemon will always start with an initial frequency of zero.

The file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). The file is updated by first writing the current drift value into a temporary file and then renaming this file to replace the old version. This implies that <code>ntpd</code> must have write permission for the directory the drift file is located in, and that file system links, symbolic or otherwise, should be avoided.

The parameter <code>tolerance</code> is the wander threshold to skip writing the new value. If the value of wander computed from recent frequency changes is greater than this threshold the file will be updated once per hour. If below the threshold, the file will not be written.

<code>**enable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats]**</code>  
: <code>**disable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats ]**</code>

: Provides a way to enable or disable various system options. Flags not mentioned are unaffected. Note that all of these flags can be controlled remotely using the [<code>ntpdc</code>](/archives/4.2.6-series/ntpdc) utility program.

<code>auth</code>

: Enables the server to synchronize with unconfigured peers only if the peer has been correctly authenticated using either public key or private key cryptography. The default for this flag is enable.

<code>bclient</code>

: Enables the server to listen for a message from a broadcast or multicast server, as in the <code>multicastclient</code> command with default address. The default for this flag is disable.

<code>calibrate</code>

: Enables the calibrate feature for reference clocks. The default for this flag is disable.

<code>kernel</code>

: Enables the kernel time discipline, if available. The default for this flag is enable if support is available, otherwise disable.

<code>monitor</code>

: Enables the monitoring facility. See the <code>ntpdc</code> program and the <code>monlist</code> command or further information. The default for this flag is enable.

<code>ntp</code>

: Enables time and frequency discipline. In effect, this switch opens and closes the feedback loop, which is useful for testing. The default for this flag is enable.

<code>stats</code>

: Enables the statistics facility. See the [Monitoring Options](/archives/4.2.6-series/monopt) page for further information. The default for this flag is disable.

<code>**includefile _includefile_**</code>

: This command allows additional configuration commands to be included from a separate file. Include files may be nested to a depth of five; upon reaching the end of any include file, command processing resumes in the previous configuration file. This option is useful for sites that run <code>ntpd</code> on multiple hosts, with (mostly) common options (e.g., a restriction list).

<code>**interface [listen | ignore | drop] [all | ipv4 | ipv6 | wildcard | _name_ | _address_[/_prefixlen_]]**</code>

: This command controls which network addresses <code>ntpd</code> opens, and whether input is dropped without processing. The first parameter determines the action for addresses which match the second parameter. That parameter specifies a class of addresses, or a specific interface name, or an address. In the address case, <code>_prefixlen_</code> determines how many bits must match for this rule to apply. <code>ignore</code> prevents opening matching addresses, <code>drop</code> causes <code>ntpd</code> to open the address and drop all received packets without examination. Multiple <code>interface</code> commands can be used. The last rule which matches a particular address determines the action for it. <code>interface</code> commands are disabled if any [<code>-I</code>](/archives/4.2.6-series/ntpd#--interface) or [<code>-L</code>](/archives/4.2.6-series/ntpd#--novirtualips) command-line options are used. If none of those options are used and no <code>interface</code> actions are specified in the configuration file, all available network addresses are opened. The <code>nic</code> command is an alias for <code>interface</code>.

<code>**leapfile _leapfile_**</code>

: This command loads the NIST leapseconds file and initializes the leapsecond values for the next leapsecond time, expiration time and TAI offset. The file can be obtained directly from NIST national time servers using <code>ftp</code> as the ASCII file <code>pub/leap-seconds</code>.

While not strictly a security function, the Autokey protocol provides means to securely retrieve the current or updated leapsecond values from a server.

<code>**logconfig _configkeyword_**</code>

: This command controls the amount and type of output written to the system <code>syslog</code> facility or the alternate <code>logfile</code> log file. All _<code>configkeyword</code>_ keywords can be prefixed with <code>=</code>, <code>+</code> and <code>-</code>, where <code>=</code> sets the <code>syslogmask</code>, <code>+</code> adds and <code>-</code> removes messages. <code>syslog messages</code> can be controlled in four classes (<code>clock</code>, <code>peer</code>, <code>sys</code> and <code>sync</code>). Within these classes four types of messages can be controlled: informational messages (<code>info</code>), event messages (<code>events</code>), statistics messages (<code>statistics</code>) and status messages (<code>status</code>).

Configuration keywords are formed by concatenating the message class with the event class. The <code>all</code> prefix can be used instead of a message class. A message class may also be followed by the <code>all</code> keyword to enable/disable all messages of the respective message class. By default, <code>logconfig</code> output is set to <code>allsync</code>.

Thus, a minimal log configuration could look like this:

`logconfig=syncstatus +sysevents`

This would just list the synchronizations state of <code>ntpd</code> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

`logconfig allsync +allclock`

This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

<code>**logfile _logfile_**</code>

: This command specifies the location of an alternate log file to be used instead of the default system <code>syslog</code> facility. This is the same operation as the <code>-l</code> command line option.

<code>**phone _dial_1 _dial_2 ...**</code>

: This command is used in conjunction with the ACTS modem driver (type 18). The arguments consist of a maximum of 10 telephone numbers used to dial USNO, NIST or European time services. The Hayes command ATDT is normally prepended to the number, which can contain other modem control codes as well.

<code>**saveconfigdir _directory_path_**</code>

: Specify the directory in which to write configuration snapshots requested with <code>ntpq</code>'s [saveconfig](/archives/4.2.6-series/ntpq#saveconfig) command. If <code>saveconfigdir</code> does not appear in the configuration file, saveconfig requests are rejected by ntpd.

<code>**setvar _variable_ [default]**</code>

: This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <code>_name_ = _value_</code> is followed by the <code>default</code> keyword, the variable will be listed as part of the default system variables (<code>ntpq rv</code> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <code>setvar</code> mechanism. There are three special variables that contain the names of all variable of the same group. The <code>sys_var_list</code> holds the names of all system variables. The <code>peer_var_list</code> holds the names of all peer variables and the <code>clock_var_list</code> holds the names of the reference clock variables.

<code>**tinker [ allan _allan_ | dispersion _dispersion_ | freq _freq_ | huffpuff _huffpuff_ | panic _panic_ | step _step_ | stepout _stepout_ ]**</code>

: This command alters certain system variables used by the clock discipline algorithm. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs. The options are as follows:

<code>allan _allan_</code>

: Specifies the Allan intercept, which is a parameter of the PLL/FLL clock discipline algorithm, in seconds with default 1500 s.

<code>dispersion _dispersion_</code>

: Specifies the dispersion increase rate in parts-per-million (PPM) with default 15 PPM.

<code>freq _freq_</code>

: Specifies the frequency offset in parts-per-million (PPM) with default the value in the frequency file.

<code>huffpuff _huffpuff_</code>

: Specifies the huff-n'-puff filter span, which determines the most recent interval the algorithm will search for a minimum delay. The lower limit is 900 s (15 m), but a more reasonable value is 7200 (2 hours).

<code>panic _panic_</code>

: Specifies the panic threshold in seconds with default 1000 s. If set to zero, the panic sanity check is disabled and a clock offset of any value will be accepted.

<code>step _step_</code>

: Specifies the step threshold in seconds. The default without this command is 0.128 s. If set to zero, step adjustments will never occur. 
> **Note: The kernel time discipline is disabled if the step threshold is set to zero or greater than 0.5 s.**

<code>stepout _stepout_</code>

: Specifies the stepout threshold in seconds. The default without this command is 900 s. If set to zero, popcorn spikes will not be suppressed.

<code>**tos [ beacon _beacon_ | ceiling _ceiling_ | cohort {0 | 1} | floor _floor_ | maxclock _maxclock_ | maxdist _maxdist_ | minclock _minclock_ | mindist _mindist_ | minsane _minsane_ | orphan _stratum_ ]**</code>

: This command alters certain system variables used by the clock selection and clustering algorithms. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs. It can be used to select the quality and quantity of peers used to synchronize the system clock and is most useful in dynamic server discovery schemes. The options are as follows:

<code>beacon _beacon_</code>

: The manycast server sends packets at intervals of 64 s if less than <code>maxclock</code> servers are available. Otherwise, it sends packets at the _<code>beacon</code>_ interval in seconds. The default is 3600 s. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

<code>ceiling _ceiling_</code>

: Specify the maximum stratum (exclusive) for acceptable server packets. The default is 16. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

<code>cohort { 0 | 1 }</code>

: Specify whether (1) or whether not (0) a server packet will be accepted for the same stratum as the client. The default is 0. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

<code>floor _floor_</code>

: Specify the minimum stratum (inclusive) for acceptable server packest. The default is 1. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

<code>maxclock _maxclock_</code>

: Specify the maximum number of servers retained by the server discovery schemes. The default is 10. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

<code>maxdist _maxdistance_</code>

: Specify the synchronization distance threshold used by the clock selection algorithm. The default is 1.5 s. This determines both the minimum number of packets to set the system clock and the maximum roundtrip delay. It can be decreased to improve reliability or increased to synchronize clocks on the Moon or planets.

<code>minclock _minclock_</code>

: Specify the number of servers used by the clustering algorithm as the minimum to include on the candidate list. The default is 3. This is also the number of servers to be averaged by the combining algorithm.

<code>mindist _mindistance_</code>

: Specify the minimum distance used by the selection and anticlockhop algorithm. Larger values increase the tolerance for outliers; smaller values increase the selectivity. The default is .001 s. In some cases, such as reference clocks with high jitter and a PPS signal, it is useful to increase the value to insure the intersection interval is always nonempty.

<code>minsane _minsane_</code>

: Specify the number of servers used by the selection algorithm as the minimum to set the system clock. The default is 1 for legacy purposes; however, for critical applications the value should be somewhat higher but less than <code>minclock</code>.

<code>orphan _stratum_</code>

: Specify the orphan stratum with default 16. If less than 16 this is the stratum assumed by the root servers. See the [Association Management](/archives/4.2.6-series/assoc) page for further details.

<code>**trap _host_address_ [port _port_number_] [interface _interfSace_address_]**</code>

: This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified, a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started.

<code>**ttl _hop_ ...**</code>

: This command specifies a list of TTL values in increasing order. up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.