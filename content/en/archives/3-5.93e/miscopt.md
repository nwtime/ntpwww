---
title: "Miscellaneous Options"
type: archives
---

#### Table of Contents

*  [Miscellaneous Commands](/archives/3-5.93e/miscopt/#miscellaneous-commands)
*  [Variables](/archives/3-5.93e/miscopt/#variables)

* * *

#### Miscellaneous Commands

<dt><tt>broadcastdelay _seconds_</tt></dt>

The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the local and remote servers. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate. The default when this command is not used is 0.004 seconds. 

<dt><tt>trap _host_address_ [port _port_number_] [interface _interface_address_]</tt></dt>

This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified. a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started. 

<dt><tt>setvar _variable_ [default]</tt></dt>

This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <tt>_name_ = _value_</tt> is followed by the <tt>default</tt> keyword, the variable will be listed as part of the default system variables (<tt>ntpq rv</tt> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <tt>setvar</tt> mechanism. 

There are three special variables that contain the names of all variable of the same group. The <tt>sys_var_list</tt> holds the names of all system variables. The <tt>peer_var_list</tt> holds the names of all peer variables and the <tt>clock_var_list</tt> holds the names of the reference clock variables.

<dt><tt>logfile _logfile_</tt></dt>

This command specifies the location of an alternate log file to be used instead of the default system <tt>syslog</tt> facility. 

<dt><tt>logconfig _configkeyword_</tt></dt>

This command controls the amount and type of output written to the system <tt>syslog</tt> facility or the alternate <tt>logfile</tt> log file. By default, all output is turned on. All _<tt>configkeyword</tt>_ keywords can be prefixed with <tt>=</tt>, <tt>+</tt> and <tt>-</tt>, where <tt>=</tt> sets the <tt>syslogmask</tt>, <tt>+</tt> adds and <tt>-</tt> removes messages. <tt>syslog messages</tt> can be controlled in four classes (<tt>clock</tt>, <tt>peer</tt>, <tt>sys</tt> and <tt>sync</tt>). Within these classes four types of messages can be controlled. 

Informational messages (<tt>info</tt>) control configuration information. Event messages (<tt>events</tt>) control logging of events (reachability, synchronization, alarm conditions). Statistical output is controlled with the (<tt>statistics</tt>) keyword. The final message group is the status messages. This describes mainly the synchronizations status. Configuration keywords are formed by concatenating the message class with the event class. The <tt>all</tt> prefix can be used instead of a message class. A message class may also be followed by the <tt>all</tt> keyword to enable/disable all messages of the respective message class. 

Thus, a minimal log configuration could look like this:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>logconfig = syncstatus +sysevents</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This would just list the synchronizations state of <tt>xntpd</tt> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>logconfig = syncall +clockall</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

* * *

#### Variables

Most variables used by the NTP protocol can be examined with the <tt>xntpdc</tt> (mode 7 messages) and the <tt>ntpq</tt> (mode 6 messages). Currently, very few variables can be modified via mode 6 messages. These variables are either created with the <tt>setvar</tt> directive or the leap warning bits. The leap warning bits can be set in the <tt>leapwarning</tt> variable up to one month ahead. Both the <tt>leapwarning</tt> and <tt>leapindication</tt> variables have a slightly different encoding than the usual leap bits interpretation:

<dt><tt>00</tt>

The daemon passes the leap bits of its synchronization source (usual mode of operation).

<dt><tt>01/10</tt>

A leap second is added/deleted (operator forced leap second).

<dt><tt>11</tt>

Leap information from the synchronizations source is ignored (thus <tt>LEAP_NOWARNING</tt> is passed on).