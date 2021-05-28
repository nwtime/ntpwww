---
title: "Miscellaneous Options"
type: archives
---

![gif](/archives/pic/boom3.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

We have three, now looking for more.

Last update: 13-Nov-2009 19:08 UTC

* * *

<dt id="broadcastdelay"><tt>broadcastdelay _seconds_</tt></dt>

The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the client and server. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate.

<dt id="driftfile"><tt>driftfile _driftfile_ { _tolerance_ ]</tt></dt>

This command specifies the complete path and name of the file used to record the frequency of the local clock oscillator. This is the same operation as the <tt>-f</tt> command linke option. If the file exists, it is read at startup in order to set the initial frequency and then updated once per hour or more with the current frequency computed by the daemon. If the file name is specified, but the file itself does not exist, the starts with an initial frequency of zero and creates the file when writing it for the first time. If this command is not given, the daemon will always start with an initial frequency of zero.

The file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). The file is updated by first writing the current drift value into a temporary file and then renaming this file to replace the old version. This implies that <tt>ntpd</tt> must have write permission for the directory the drift file is located in, and that file system links, symbolic or otherwise, should be avoided.

The parameter <tt>tolerance</tt> is the wander threshold to skip writing the new value. If the value of wander computed from recent frequency changes is greater than this threshold the file will be updated once per hour. If below the threshold, the file will not be written.

<dt id="enable"><tt>enable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats]</tt>  
<tt>disable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats ]</tt></dt>

Provides a way to enable or disable various system options. Flags not mentioned are unaffected. Note that all of these flags can be controlled remotely using the [<tt>ntpdc</tt>](/archives/4.2.6-series/ntpdc) utility program.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>auth</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the server to synchronize with unconfigured peers only if the peer has been correctly authenticated using either public key or private key cryptography. The default for this flag is enable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>bclient</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the server to listen for a message from a broadcast or multicast server, as in the <tt>multicastclient</tt> command with default address. The default for this flag is disable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>calibrate</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the calibrate feature for reference clocks. The default for this flag is disable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>kernel</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the kernel time discipline, if available. The default for this flag is enable if support is available, otherwise disable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>monitor</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the monitoring facility. See the <tt>ntpdc</tt> program and the <tt>monlist</tt> command or further information. The default for this flag is enable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>ntp</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables time and frequency discipline. In effect, this switch opens and closes the feedback loop, which is useful for testing. The default for this flag is enable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stats</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the statistics facility. See the [Monitoring Options](/archives/4.2.6-series/monopt) page for further information. The default for this flag is disable.

<dt id="includefile"><tt>includefile _includefile_</tt></dt>

This command allows additional configuration commands to be included from a separate file. Include files may be nested to a depth of five; upon reaching the end of any include file, command processing resumes in the previous configuration file. This option is useful for sites that run <tt>ntpd</tt> on multiple hosts, with (mostly) common options (e.g., a restriction list).

<dt id="interface"><tt>interface [listen | ignore | drop] [all | ipv4 | ipv6 | wildcard | _name_ | _address_[/_prefixlen_]]</tt></dt>

This command controls which network addresses <tt>ntpd</tt> opens, and whether input is dropped without processing. The first parameter determines the action for addresses which match the second parameter. That parameter specifies a class of addresses, or a specific interface name, or an address. In the address case, <tt>_prefixlen_</tt> determines how many bits must match for this rule to apply. <tt>ignore</tt> prevents opening matching addresses, <tt>drop</tt> causes <tt>ntpd</tt> to open the address and drop all received packets without examination. Multiple <tt>interface</tt> commands can be used. The last rule which matches a particular address determines the action for it. <tt>interface</tt> commands are disabled if any [<tt>-I</tt>](/archives/4.2.6-series/ntpd#--interface) or [<tt>-L</tt>](/archives/4.2.6-series/ntpd#--novirtualips) command-line options are used. If none of those options are used and no <tt>interface</tt> actions are specified in the configuration file, all available network addresses are opened. The <tt>nic</tt> command is an alias for <tt>interface</tt>.

<dt id="leapfile"><tt>leapfile _leapfile_</tt></dt>

This command loads the NIST leapseconds file and initializes the leapsecond values for the next leapsecond time, expiration time and TAI offset. The file can be obtained directly from NIST national time servers using <tt>ftp</tt> as the ASCII file <tt>pub/leap-seconds</tt>.

While not strictly a security function, the Autokey protocol provides means to securely retrieve the current or updated leapsecond values from a server.

<dt id="logconfig"><tt>logconfig _configkeyword_</tt></dt>

This command controls the amount and type of output written to the system <tt>syslog</tt> facility or the alternate <tt>logfile</tt> log file. All _<tt>configkeyword</tt>_ keywords can be prefixed with <tt>=</tt>, <tt>+</tt> and <tt>-</tt>, where <tt>=</tt> sets the <tt>syslogmask</tt>, <tt>+</tt> adds and <tt>-</tt> removes messages. <tt>syslog messages</tt> can be controlled in four classes (<tt>clock</tt>, <tt>peer</tt>, <tt>sys</tt> and <tt>sync</tt>). Within these classes four types of messages can be controlled: informational messages (<tt>info</tt>), event messages (<tt>events</tt>), statistics messages (<tt>statistics</tt>) and status messages (<tt>status</tt>).

Configuration keywords are formed by concatenating the message class with the event class. The <tt>all</tt> prefix can be used instead of a message class. A message class may also be followed by the <tt>all</tt> keyword to enable/disable all messages of the respective message class. By default, <tt>logconfig</tt> output is set to <tt>allsync</tt>.

Thus, a minimal log configuration could look like this:

<tt>logconfig=syncstatus +sysevents</tt>

This would just list the synchronizations state of <tt>ntpd</tt> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

<tt>logconfig allsync +allclock</tt>

This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

<dt id="logfile"><tt>logfile _logfile_</tt></dt>

This command specifies the location of an alternate log file to be used instead of the default system <tt>syslog</tt> facility. This is the same operation as the <tt>-l</tt> command line option.

<dt id="phone"><tt>phone _dial_1 _dial_2 ...</tt></dt>

This command is used in conjunction with the ACTS modem driver (type 18). The arguments consist of a maximum of 10 telephone numbers used to dial USNO, NIST or European time services. The Hayes command ATDT is normally prepended to the number, which can contain other modem control codes as well.

<dt id="saveconfigdir"><tt>saveconfigdir _directory_path_</tt></dt>

Specify the directory in which to write configuration snapshots requested with <tt>ntpq</tt>'s [saveconfig](/archives/4.2.6-series/ntpq#saveconfig) command. If <tt>saveconfigdir</tt> does not appear in the configuration file, saveconfig requests are rejected by ntpd.

<dt id="setvar"><tt>setvar _variable_ [default]</tt></dt>

This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <tt>_name_ = _value_</tt> is followed by the <tt>default</tt> keyword, the variable will be listed as part of the default system variables (<tt>ntpq rv</tt> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <tt>setvar</tt> mechanism. There are three special variables that contain the names of all variable of the same group. The <tt>sys_var_list</tt> holds the names of all system variables. The <tt>peer_var_list</tt> holds the names of all peer variables and the <tt>clock_var_list</tt> holds the names of the reference clock variables.

<dt id="tinker"><tt>tinker [ allan _allan_ | dispersion _dispersion_ | freq _freq_ | huffpuff _huffpuff_ | panic _panic_ | step _step_ | stepout _stepout_ ]</tt></dt>

This command alters certain system variables used by the clock discipline algorithm. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs. The options are as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>allan _allan_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the Allan intercept, which is a parameter of the PLL/FLL clock discipline algorithm, in seconds with default 1500 s.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>dispersion _dispersion_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the dispersion increase rate in parts-per-million (PPM) with default 15 PPM.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>freq _freq_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the frequency offset in parts-per-million (PPM) with default the value in the frequency file.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>huffpuff _huffpuff_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the huff-n'-puff filter span, which determines the most recent interval the algorithm will search for a minimum delay. The lower limit is 900 s (15 m), but a more reasonable value is 7200 (2 hours).

&nbsp;&nbsp;&nbsp;&nbsp;<tt>panic _panic_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the panic threshold in seconds with default 1000 s. If set to zero, the panic sanity check is disabled and a clock offset of any value will be accepted.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>step _step_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the step threshold in seconds. The default without this command is 0.128 s. If set to zero, step adjustments will never occur. **Note: The kernel time discipline is disabled if the step threshold is set to zero or greater than 0.5 s.**

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stepout _stepout_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the stepout threshold in seconds. The default without this command is 900 s. If set to zero, popcorn spikes will not be suppressed.

<dt id="tos"><tt>tos [ beacon _beacon_ | ceiling _ceiling_ | cohort {0 | 1} | floor _floor_ | maxclock _maxclock_ | maxdist _maxdist_ | minclock _minclock_ | mindist _mindist_ | minsane _minsane_ | orphan _stratum_ ]</tt></dt>

This command alters certain system variables used by the the clock selection and clustering algorithms. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs. It can be used to select the quality and quantity of peers used to synchronize the system clock and is most useful in dynamic server discovery schemes. The options are as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>beacon _beacon_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The manycast server sends packets at intervals of 64 s if less than <tt>maxclock</tt> servers are available. Otherwise, it sends packets at the _<tt>beacon</tt>_ interval in seconds. The default is 3600 s. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>ceiling _ceiling_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the maximum stratum (exclusive) for acceptable server packets. The default is 16\. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>cohort { 0 | 1 }</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify whether (1) or whether not (0) a server packet will be accepted for the same stratum as the client. The default is 0\. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>floor _floor_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the minimum stratum (inclusive) for acceptable server packest. The default is 1\. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>maxclock _maxclock_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the maximum number of servers retained by the server discovery schemes. The default is 10. See the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page for further details.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>maxdist _maxdistance_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the synchronization distance threshold used by the clock selection algorithm. The default is 1.5 s. This determines both the minimum number of packets to set the system clock and the maximum roundtrip delay. It can be decreased to improve reliability or increased to synchronize clocks on the Moon or planets.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minclock _minclock_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the number of servers used by the clustering algorithm as the minimum to include on the candidate list. The default is 3. This is also the number of servers to be averaged by the combining algorithm.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>mindist _mindistance_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the minimum distance used by the selection and anticlockhop algorithm. Larger values increase the tolerance for outliers; smaller values increase the selectivity. The default is .001 s. In some cases, such as reference clocks with high jitter and a PPS signal, it is useful to increase the value to insure the intersection interval is always nonempty.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minsane _minsane_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the number of servers used by the selection algorithm as the minimum to set the system clock. The default is 1 for legacy purposes; however, for critical applications the value should be somewhat higher but less than <tt>minclock</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>orphan _stratum_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specify the orphan stratum with default 16\. If less than 16 this is the stratum assumed by the root servers. See the [Association Management](/archives/4.2.6-series/assoc) page for further details.

</dl>



<dt id="trap"><tt>trap _host_address_ [port _port_number_] [interface _interfSace_address_]</tt></dt>

This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified, a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started.

<dt id="ttl"><tt>ttl _hop_ ...</tt></dt>

This command specifies a list of TTL values in increasing order. up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.