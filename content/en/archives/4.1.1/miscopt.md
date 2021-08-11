---
title: "Miscellaneous Options"
type: archives
---

![gif](/archives/pic/boom3.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

We have three, now looking for more.

* * *

<dt><tt>broadcastdelay _seconds_</tt></dt>

The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the client and server. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate. The default when this command is not used is 0.004 seconds.

<dt><tt>driftfile _driftfile_</tt></dt>

This command specifies the name of the file used to record the frequency offset of the local clock oscillator. If the file exists, it is read at startup in order to set the initial frequency and then updated once per hour with the current frequency computed by the daemon. If the file does not exist or this command is not given, the initial frequency offset is assumed zero. In this case, it may take some hours for the frequency to stabilize and the residual timing errors to subside. 

The file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). The file is updated by first writing the current drift value into a temporary file and then renaming this file to replace the old version. This implies that <tt>ntpd</tt> must have write permission for the directory the drift file is located in, and that file system links, symbolic or otherwise, should be avoided.

<dt><tt>enable [ auth | bclient | calibrate | kernel | monitor | ntp | stats]</tt>  
<tt>disable [ auth | bclient | calibrate | kernel | monitor | ntp | stats ]</tt></dt>

Provides a way to enable or disable various system options. Flags not mentioned are unaffected. Note that all of these flags can be controlled remotely using the [<tt>ntpdc</tt>](/archives/4.1.1/ntpdc) utility program.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>bclient</tt>

&nbsp;&nbsp;&nbsp;&nbsp;When enabled, this is identical to the <tt>broadcastclient</tt> command. The default for this flag is <tt>disable</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>calibrate</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the calibration facility, which automatically adjusts the time1 values for each clock driver to display the same offset as the currently selected source or kernel discipline signal. See the [Reference Clock Drivers](/archives/4.1.1/refclock) for further information. The default for this flag is <tt>disable</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>kernel</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the precision-time kernel support for the <tt>ntp_adjtime()</tt> system call, if implemented. Ordinarily, support for this routine is detected automatically when the NTP daemon is compiled, so it is not necessary for the user to worry about this flag. It flag is provided primarily so that this support can be disabled during kernel development. The default for this flag is <tt>enable</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>monitor</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the monitoring facility. See the <tt>ntpdc</tt> program and the <tt>monlist</tt> command for further information. The default for this flag is <tt>enable</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>ntp</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the server to adjust its local clock by means of NTP. If disabled, the local clock free-runs at its intrinsic time and frequency offset. This flag is useful in case the local clock is controlled by some other device or protocol and NTP is used only to provide synchronization to other clients. In this case, the local clock driver can be used to provide this function and also certain time variables for error estimates and leap-indicators. See the [Reference Clock Drivers](/archives/4.1.1/refclock) page for further information. The default for this flag is <tt>enable</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stats</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the statistics facility. See the [Monitoring Options](/archives/4.1.1/monopt) page for further information. The default for this flag is <tt>enable</tt>.

<dt><tt>logconfig _configkeyword_</tt></dt>

This command controls the amount and type of output written to the system <tt>syslog</tt> facility or the alternate <tt>logfile</tt> log file. By default, all output is turned on. All _<tt>configkeyword</tt>_ keywords can be prefixed with <tt>=</tt>, <tt>+</tt> and <tt>-</tt>, where <tt>=</tt> sets the <tt>syslogmask</tt>, <tt>+</tt> adds and <tt>-</tt> removes messages. <tt>syslog messages</tt> can be controlled in four classes (<tt>clock</tt>, <tt>peer</tt>, <tt>sys</tt> and <tt>sync</tt>). Within these classes four types of messages can be controlled. 

Informational messages (<tt>info</tt>) control configuration information. Event messages (<tt>events</tt>) control logging of events (reachability, synchronization, alarm conditions). Statistical output is controlled with the (<tt>statistics</tt>) keyword. The final message group is the status messages. This describes mainly the synchronizations status. Configuration keywords are formed by concatenating the message class with the event class.
The <tt>all</tt> prefix can be used instead of a message class. A message class may also be followed by the <tt>all</tt> keyword to enable/disable all messages of the respective message class. 

Thus, a minimal log configuration could look like this:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>logconfig=syncstatus +sysevents</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This would just list the synchronizations state of <tt>ntpd</tt> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>logconfig=allsync +clockall</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

<dt><tt>logfile _logfile_</tt></dt>

This command specifies the location of an alternate log file to be used instead of the default system <tt>syslog</tt> facility. 

<dt><tt>setvar _variable_ [default]</tt></dt>

This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <tt>_name_ = _value_</tt> is followed by the <tt>default</tt> keyword, the variable will be listed as part of the default system variables (<tt>ntpq rv</tt> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <tt>setvar</tt> mechanism. There are three special variables that contain the names of all variable of the same group. The <tt>sys_var_list</tt> holds the names of all system variables. The <tt>peer_var_list</tt> holds the names of all peer variables and the <tt>clock_var_list</tt> holds the names of the reference clock variables.

<dt><tt>tinker [ step _step_ | panic _panic_ | dispersion _dispersion_ | stepout _stepout_ | minpoll _minpoll_ ]</tt></dt>

This command can be used to alter several system variables in very exceptional circumstances. It should occur in the configuration file before any other configuration options. The default values of these variables have been carefully optimized for a wide range of network speeds and reliability expectations. In general, they interact in intricate ways that are hard to predict and some combinations can result in some very nasty behavior. Very rarely is it necessary to change the default values; but, some folks can't resist twisting the knobs anyway and this command is for them. Emphasis added: twisters are on their own and can expect no help from the support group. 

All arguments are in floating point seconds or seconds per second. The <tt>minpoll</tt> argument is an integer in seconds to the power of two. The variables operate as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>step _step_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the step threshold, normally 0.128 s. If set to zero, step adjustments will never occur. In general, if the intent is only to avoid step adjustments, the step threshold should be left alone and the <tt>-x</tt> command line option be used instead.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>panic _panic_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the panic threshold, normally 1000 s. If set to zero, the panic sanity check is disabled and a clock offset of any value will be accepted.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>dispersion _dispersion_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the dispersion increase rate, normally .000015 s/s.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stepout _stepout_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the watchdog timeout, normally 900 s.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minpoll _minpoll_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the minimum poll interval used when configuring multicast client, manycast client and , symmetric passive mode association. The value defaults to 6 (64 s) and has a lower limit of 4 (16 s).

&nbsp;&nbsp;&nbsp;&nbsp;<tt>allan _allan_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the minimum Allan intercept, which is a parameter of the PLL/FLL clock discipline algorithm. The value defaults to 1024 s, which is also the lower limit.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>huffpuff _huffpuff_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The argument becomes the new value for the experimental huff-n'-puff filter span, which determines the most recent interval the algorithm will search for a minimum delay. The lower limit is 900 s (15 m), but a more reasonable value is 7200 (2 hours). There is no default, since the filter is not enabled unless this command is given.

<dt><tt>trap _host_address_ [port _port_number_] [interface _interface_address_]</tt></dt>

This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified, a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started.

#### Files

<tt>ntp.drift</tt> frequency compensation (PPM)