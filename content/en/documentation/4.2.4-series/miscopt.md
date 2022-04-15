---
title: "Miscellaneous Options"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/boom3.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

We have three, now looking for more.

* * *

<code>**broadcastdelay _seconds_**</code>

: The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the client and server. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate. The default when this command is not used is 0.004 seconds.

<code>**calldelay _delay_**</code>

: This option controls the delay in seconds between the first and second packets sent in burst or iburst mode to allow additional time for a modem or ISDN call to complete.

<code>**driftfile _driftfile_ [ _minutes_ [ _tolerance_ ] ]**</code>

: This command specifies the complete path and name of the file used to record the frequency of the local clock oscillator. This is the same operation as the <code>-f</code> command linke option. If the file exists, it is read at startup in order to set the initial frequency and then updated once per hour with the current frequency computed by the daemon. If the file name is specified, but the file itself does not exist, the starts with an initial frequency of zero and creates the file when writing it for the first time. If this command is not given, the daemon will always start with an initial frequency of zero.

The file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). The file is updated by first writing the current drift value into a temporary file and then renaming this file to replace the old version. This implies that <code>ntpd</code> must have write permission for the directory the drift file is located in, and that file system links, symbolic or otherwise, should be avoided.

The two optional values determine how often the file is written, and are particuarly useful when is it desirable to avoid spinning up the disk unnecessarily. The parameter <code>minutes</code> is how often the file will be written. If omitted or less than 1, the interval will be 60 minutes (one hour). The parameter <code>tolerance</code> is the threshold to skip writing the new value. If the new value is within <code>tolerance</code> percent of the last value written (compared out to 3 decimal places), the write will be skipped. The default is 0.0, which means that the write will occur unless the current and previous values are the same. A tolerance of .1 equates roughly to a difference in the 2nd decimal place.

<code>**enable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats]**</code>  
: <code>**disable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats ]**</code>

: Provides a way to enable or disable various system options. Flags not mentioned are unaffected. Note that all of these flags can be controlled remotely using the [<code>ntpdc</code>](/documentation/4.2.4-series/ntpdc/) utility program.

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

<code>pps</code>

: Enables the pulse-per-second (PPS) signal when frequency and time is disciplined by the precision time kernel modifications. See the [A Kernel Model for Precision Timekeeping](/documentation/4.2.4-series/kern/) page for further information. The default for this flag is disable.

<code>stats</code>

: Enables the statistics facility. See the [Monitoring Options](/documentation/4.2.4-series/monopt/) page for further information. The default for this flag is disable

<code>**includefile _includefile_**</code>

: This command allows additional configuration commands to be included from a separate file. Include files may be nested to a depth of five; upon reaching the end of any include file, command processing resumes in the previous configuration file. This option is useful for sites that run <code>ntpd</code> on multiple hosts, with (mostly) common options (e.g., a restriction list).

<code>**logconfig _configkeyword_**</code>

: This command controls the amount and type of output written to the system <code>syslog</code> facility or the alternate <code>logfile</code> log file. All <code>_configkeyword_</code> keywords can be prefixed with <code>=</code>, <code>+</code> and <code>-</code>, where <code>=</code> sets the <code>syslogmask</code>, <code>+</code> adds and <code>-</code> removes messages. <code>syslog messages</code> can be controlled in four classes (<code>clock</code>, <code>peer</code>, <code>sys</code> and <code>sync</code>). Within these classes four types of messages can be controlled: informational messages (<code>info</code>), event messages (<code>events</code>), statistics messages (<code>statistics</code>) and status messages (<code>status</code>).

Configuration keywords are formed by concatenating the message class with the event class. The <code>all</code> prefix can be used instead of a message class. A message class may also be followed by the <code>all</code> keyword to enable/disable all messages of the respective message class. By default, <code>logconfig</code> output is set to <code>allsync</code>.

Thus, a minimal log configuration could look like this:

`logconfig=syncstatus +sysevents`

This would just list the synchronizations state of <code>ntpd</code> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

`logconfig=allsync +allclock`

This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

<code>**logfile _logfile_**</code>

: This command specifies the location of an alternate log file to be used instead of the default system <code>syslog</code> facility. This is the same operation as the <code>-l</code> command line option.

<code>**phone _dial_1 _dial_2 ...**</code>

: This command is used in conjunction with the ACTS modem driver (type 18). The arguments consist of a maximum of 10 telephone numbers used to dial USNO, NIST or European time services. The Hayes command ATDT is normally prepended to the number, which can contain other modem control codes as well.

<code>**setvar _variable_ [default]**</code>

: This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <code>_name_ = _value_</code> is followed by the <code>default</code> keyword, the variable will be listed as part of the default system variables (<code>ntpq rv</code> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <code>setvar</code> mechanism. There are three special variables that contain the names of all variable of the same group. The <code>sys_var_list</code> holds the names of all system variables. The <code>peer_var_list</code> holds the names of all peer variables and the <code>clock_var_list</code> holds the names of the reference clock variables.

<code>**tinker [ allan _allan_ | dispersion _dispersion_ | freq _freq_ | huffpuff _huffpuff_ | panic _panic_ | step _step_ | stepout _stepout_ ]**</code>

: This command can be used to alter several system variables in very exceptional circumstances. It should occur in the configuration file before any other configuration options. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. In general, they interact in intricate ways that are hard to predict and some combinations can result in some very nasty behavior. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs anyway and this command is for them. Emphasis added: twisters are on their own and can expect no help from the support group.

The variables operate as follows:

<code>allan _allan_</code>

: The argument becomes the new value for the Allan intercept, which is a parameter of the PLL/FLL clock discipline algorithm. The value is in seconds with default 1500 s, which is appropriate for most computer clocks.

<code>dispersion _dispersion_</code>

: The argument becomes the new value for the dispersion increase rate, normally .000015 s/s.

<code>freq _freq_</code>

: The argument becomes the initial value of the frequency offset in parts-per-million. This overrides the value in the frequency file, if present, and avoids the initial training state if it is not.

<code>huffpuff _huffpuff_</code>

: The argument becomes the new value for the experimental huff-n'-puff filter span, which determines the most recent interval the algorithm will search for a minimum delay. The lower limit is 900 s (15 m), but a more reasonable value is 7200 (2 hours). There is no default, since the filter is not enabled unless this command is given.

<code>panic _panic_</code>

: The argument is the panic threshold, by default 1000 s. If set to zero, the panic sanity check is disabled and a clock offset of any value will be accepted.

<code>step _step_</code>

: The argument is the step threshold, by default 0.128 s. It can be set to any positive number in seconds. If set to zero, step adjustments will never occur. 
> **Note:** The kernel time discipline is disabled if the step threshold is set to zero or greater than the default.

<code>stepout _stepout_</code>

: The argument is the stepout timeout, by default 900 s. It can be set to any positive number in seconds. If set to zero, the stepout pulses will not be suppressed.

<code>**trap _host_address_ [port _port_number_] [interface _interface_address_]**</code>

: This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified, a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started.

<code>**ttl _hop_ ...**</code>

: This command specifies a list of TTL values in increasing order. up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.

#### Files

<code>ntp.drift</code> - frequency compensation (PPM)