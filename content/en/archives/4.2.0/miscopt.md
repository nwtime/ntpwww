---
title: "Miscellaneous Options"
type: archives
---

![gif](/archives/pic/boom3.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

We have three, now looking for more.

Last update: 01:50 UTC Friday, May 02, 2003

* * *

<dt><tt>broadcastdelay _seconds_</tt></dt>

The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the client and server. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate. The default when this command is not used is 0.004 seconds.

<dt><tt>calldelay _delay_</tt></dt>

This option controls the delay in seconds between the first and second packets sent in burst or iburst mode to allow additional time for a modem or ISDN call to complete.

<dt><tt>driftfile _driftfile_</tt></dt>

This command specifies the complete path and name of the file used to record the frequency of the local clock oscillator. This is the same operation as the <tt>-f</tt> command linke option. If the file exists, it is read at startup in order to set the initial frequency and then updated once per hour with the current frequency computed by the daemon. If the file name is specified, but the file itself does not exist, the starts with an initial frequency of zero and creates the file when writing it for the first time. If this command is not given, the daemon will always start with an initial frequency of zero.

The file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). The file is updated by first writing the current drift value into a temporary file and then renaming this file to replace the old version. This implies that <tt>ntpd</tt> must have write permission for the directory the drift file is located in, and that file system links, symbolic or otherwise, should be avoided.

<dt><tt>enable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats]</tt>  
<tt>disable [ auth | bclient | calibrate | kernel | monitor | ntp | pps | stats ]</tt></dt>

Provides a way to enable or disable various system options. Flags not mentioned are unaffected. Note that all of these flags can be controlled remotely using the [<tt>ntpdc</tt>](/archives/4.2.0/ntpdc) utility program.

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

&nbsp;&nbsp;&nbsp;&nbsp;<tt>pps</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the pulse-per-second (PPS) signal when frequency and time is disciplined by the precision time kernel modifications. See the [A Kernel Model for Precision Timekeeping](/archives/4.2.0/kern) page for further information. The default for this flag is disable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stats</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the statistics facility. See the [Monitoring Options](/archives/4.2.0/monopt) page for further information. The default for this flag is disable

<dt><tt>includefile _includefile_</tt></dt>

This command allows additional configuration commands to be included from a separate file. Include files may be nested to a depth of five; upon reaching the end of any include file, command processing resumes in the previous configuration file. This option is useful for sites that run <tt>ntpd</tt> on multiple hosts, with (mostly) common options (e.g., a restriction list).

<dt><tt>logconfig _configkeyword_</tt></dt>

This command controls the amount and type of output written to the system <tt>syslog</tt> facility or the alternate <tt>logfile</tt> log file. All _<tt>configkeyword</tt>_ keywords can be prefixed with <tt>=</tt>, <tt>+</tt> and <tt>-</tt>, where <tt>=</tt> sets the <tt>syslogmask</tt>, <tt>+</tt> adds and <tt>-</tt> removes messages. <tt>syslog messages</tt> can be controlled in four classes (<tt>clock</tt>, <tt>peer</tt>, <tt>sys</tt> and <tt>sync</tt>). Within these classes four types of messages can be controlled: informational messages (<tt>info</tt>), event messages (<tt>events</tt>), statistics messages (<tt>statistics</tt>) and status messages (<tt>status</tt>).

Configuration keywords are formed by concatenating the message class with the event class. The <tt>all</tt> prefix can be used instead of a message class. A message class may also be followed by the <tt>all</tt> keyword to enable/disable all messages of the respective message class. By default, <tt>logconfig</tt> output is set to <tt>allsync</tt>.

Thus, a minimal log configuration could look like this:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>logconfig=syncstatus +sysevents</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This would just list the synchronizations state of <tt>ntpd</tt> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>logconfig=allsync +clockall</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

<dt><tt>logfile _logfile_</tt></dt>

This command specifies the location of an alternate log file to be used instead of the default system <tt>syslog</tt> facility. This is the same operation as the <tt>-l</tt> command line option.

<dt><tt>setvar _variable_ [default]</tt></dt>

This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <tt>_name_ = _value_</tt> is followed by the <tt>default</tt> keyword, the variable will be listed as part of the default system variables (<tt>ntpq rv</tt> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <tt>setvar</tt> mechanism. There are three special variables that contain the names of all variable of the same group. The <tt>sys_var_list</tt> holds the names of all system variables. The <tt>peer_var_list</tt> holds the names of all peer variables and the <tt>clock_var_list</tt> holds the names of the reference clock variables.

<dt><tt>tinker [ allan _allan_ | dispersion _dispersion_ | freq _freq_ | huffpuff _huffpuff_ | panic _panic_ | step _step_ | stepout _stepout_ ]</tt></dt>

This command can be used to alter several system variables in very exceptional circumstances. It should occur in the configuration file before any other configuration options. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. In general, they interact in intricate ways that are hard to predict and some combinations can result in some very nasty behavior. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs anyway and this command is for them. Emphasis added: twisters are on their own and can expect no help from the support group.

The variables operate as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>allan _allan_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the Allan intercept, which is a parameter of the PLL/FLL clock discipline algorithm. The value in log2 seconds defaults to 7 (1024 s), which is also the lower limit.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>dispersion _dispersion_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the dispersion increase rate, normally .000015 s/s.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>freq _freq_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the initial value of the frequency offset in parts-per-million. This overrides the value in the frequency file, if present, and avoids the initial training state if it is not.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>huffpuff _huffpuff_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the experimental huff-n'-puff filter span, which determines the most recent interval the algorithm will search for a minimum delay. The lower limit is 900 s (15 m), but a more reasonable value is 7200 (2 hours). There is no default, since the filter is not enabled unless this command is given.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>panic _panic_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument is the panic threshold, by default 1000 s. If set to zero, the panic sanity check is disabled and a clock offset of any value will be accepted.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>step _step_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument is the step threshold, by default 0.128 s. It can be set to any positive number in seconds. If set to zero, step adjustments will never occur. **Note:** The kernel time discipline is disabled if the step threshold is set to zero or greater than the default.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stepout _stepout_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument is the stepout timeout, which by default is 900 s. It can be set to any positive number in seconds. If set to zero, the stepout pulses will not be suppressed.

<dt><tt>trap _host_address_ [port _port_number_] [interface _interface_address_]</tt></dt>

This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified, a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started.

<dt><tt>ttl _hop_ ...</tt></dt>

This command specifies a list of TTL values in increasing order. up to 8 values can be specified. In manycast mode these values are used in turn in an expanding-ring search. The default is eight multiples of 32 starting at 31.

#### Files

<tt>ntp.drift</tt> frequency compensation (PPM)