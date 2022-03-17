---
title: "Miscellaneous Options"
type: archives
noindex: true
---

#### Table of Contents

*  [Miscellaneous Commands](/archives/3-5.93e/miscopt/#miscellaneous-commands)
*  [Variables](/archives/3-5.93e/miscopt/#variables)

* * *

#### Miscellaneous Commands

<code>**broadcastdelay _seconds_**</code>

: The broadcast and multicast modes require a special calibration to determine the network delay between the local and remote servers. Ordinarily, this is done automatically by the initial protocol exchanges between the local and remote servers. In some cases, the calibration procedure may fail due to network or server access controls, for example. This command specifies the default delay to be used under these circumstances. Typically (for Ethernet), a number between 0.003 and 0.007 seconds is appropriate. The default when this command is not used is 0.004 seconds. 

<code>**trap _host_address_ [port _port_number_] [interface _interface_address_]**</code>

: This command configures a trap receiver at the given host address and port number for sending messages with the specified local interface address. If the port number is unspecified. a value of 18447 is used. If the interface address is not specified, the message is sent with a source address of the local interface the message is sent through. Note that on a multihomed host the interface used may vary from time to time with routing changes.

The trap receiver will generally log event messages and other information from the server in a log file. While such monitor programs may also request their own trap dynamically, configuring a trap receiver will ensure that no messages are lost when the server is started. 

<code>**setvar _variable_ [default]**</code>

: This command adds an additional system variable. These variables can be used to distribute additional information such as the access policy. If the variable of the form <code>_name_ = _value_</code> is followed by the <code>default</code> keyword, the variable will be listed as part of the default system variables (<code>ntpq rv</code> command). These additional variables serve informational purposes only. They are not related to the protocol other that they can be listed. The known protocol variables will always override any variables defined via the <code>setvar</code> mechanism. 

There are three special variables that contain the names of all variable of the same group. The <code>sys_var_list</code> holds the names of all system variables. The <code>peer_var_list</code> holds the names of all peer variables and the <code>clock_var_list</code> holds the names of the reference clock variables.

<code>**logfile _logfile_**</code>

: This command specifies the location of an alternate log file to be used instead of the default system <code>syslog</code> facility. 

<code>**logconfig _configkeyword_**</code>

: This command controls the amount and type of output written to the system <code>syslog</code> facility or the alternate <code>logfile</code> log file. By default, all output is turned on. All _<code>configkeyword</code>_ keywords can be prefixed with <code>=</code>, <code>+</code> and <code>-</code>, where <code>=</code> sets the <code>syslogmask</code>, <code>+</code> adds and <code>-</code> removes messages. <code>syslog messages</code> can be controlled in four classes (<code>clock</code>, <code>peer</code>, <code>sys</code> and <code>sync</code>). Within these classes four types of messages can be controlled. 

Informational messages (<code>info</code>) control configuration information. Event messages (<code>events</code>) control logging of events (reachability, synchronization, alarm conditions). Statistical output is controlled with the (<code>statistics</code>) keyword. The final message group is the status messages. This describes mainly the synchronizations status. Configuration keywords are formed by concatenating the message class with the event class. The <code>all</code> prefix can be used instead of a message class. A message class may also be followed by the <code>all</code> keyword to enable/disable all messages of the respective message class. 

Thus, a minimal log configuration could look like this:

`logconfig = syncstatus +sysevents`

This would just list the synchronizations state of <code>xntpd</code> and the major system events. For a simple reference server, the following minimum message configuration could be useful:

`logconfig = syncall +clockall`

This configuration will list all clock information and synchronization information. All other events and messages about peers, system events and so on is suppressed.

* * *

#### Variables

Most variables used by the NTP protocol can be examined with the <code>xntpdc</code> (mode 7 messages) and the <code>ntpq</code> (mode 6 messages). Currently, very few variables can be modified via mode 6 messages. These variables are either created with the <code>setvar</code> directive or the leap warning bits. The leap warning bits can be set in the <code>leapwarning</code> variable up to one month ahead. Both the <code>leapwarning</code> and <code>leapindication</code> variables have a slightly different encoding than the usual leap bits interpretation:

<code>**00**</code>

: The daemon passes the leap bits of its synchronization source (usual mode of operation).

<code>**01/10**</code>

: A leap second is added/deleted (operator forced leap second).

<code>**11**</code>

: Leap information from the synchronizations source is ignored (thus <code>LEAP_NOWARNING</code> is passed on).