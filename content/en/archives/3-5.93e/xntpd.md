---
title: "xntpd - Network Time Protocol (NTP) daemon"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/xntpd/#synopsis)
*   [Description](/archives/3-5.93e/xntpd/#description)
*   [Command Line Options](/archives/3-5.93e/xntpd/#command-line-options)
*   [The Configuration File](/archives/3-5.93e/xntpd/#the-configuration-file)
*   [Files](/archives/3-5.93e/xntpd/#files)
*   [Bugs](/archives/3-5.93e/xntpd/#bugs)

* * *

#### Synopsis

<tt>xntpd [ -aAbdm ] [ -c _conffile_ ] [ -f _driftfile_ ] [ -k _keyfile_ ] [ -l _logfile_ ] [ -p _pidfile_ ] [ -r _broadcastdelay_ ] [ -s _statsdir_ ] [ -t _key_ ] [ -v _variable_ ] [ -V _variable_ ]</tt>

* * *  

#### Description

<tt>xntpd</tt> is an operating system daemon which sets and maintains the system time-of-day in synchronism with Internet standard time servers. <tt>xntpd</tt> is a complete implementation of the Network Time Protocol (NTP) version 3, as defined by RFC-1305, but also retains compatibility with version 1 and 2 servers as defined by RFC- 1059 and RFC-1119, respectively. <tt>xntpd</tt> does all computations in 64-bit fixed point arithmetic and requires no floating point support. While the ultimate precision of this design, about 232 picoseconds, is not achievable with ordinary workstations and networks of today, it may be required with future nanosecond CPU clocks and gigabit LANs. 

The daemon can operate in any of several modes, including symmetric active/passive, client/server and broadcast/multicast, as described in RFC-1305. A broadcast/multicast client can discover remote servers, compute server-client propagation delay correction factors and configure itself automatically. This makes it possible to deploy a fleet of workstations without specifying configuration details specific to the local environment.

Ordinarily, <tt>xntpd</tt> reads the <tt>ntp.conf</tt> configuration file at startup time in order to determine the synchronization sources and operating modes. It is also possible to specify a working, although limited, configuration entirely on the command line, obviating the need for a configuration file. This may be particularly appropriate when the local host is to be configured as a broadcast or multicast client, with all peers being determined by listening to broadcasts at run time.

Various internal <tt>xntpd</tt> variables can be displayed and configuration options altered while the daemon is running using the [ntpq](/archives/3-5.93e/ntpq) and [xntpdc](/archives/3-5.93e/xntpdc) utility programs.

When <tt>xntpd</tt> starts it looks at the value of <tt>umask</tt>, and if it's zero <tt>xntpd</tt> will set the <tt>umask</tt> to <tt>022</tt>. 

* * *

#### Command Line Options

<dt><tt>-a</tt></dt>

Enable authentication mode. The default is enabled, so this option is obsolete now. 

<dt><tt>-A</tt></dt>

Disable authentication mode.

<dt><tt>-b</tt></dt>

Synchronize using NTP broadcast messages.

<dt><tt>-c _conffile_</tt></dt>

Specify the name and path of the configuration file. 

<dt><tt>-d</tt></dt>

Specify debugging mode. This flag may occur multiple times, with each occurrence indicating greater detail of display.

<dt><tt>-f _driftfile_</tt></dt>

Specify the name and path of the drift file.

<dt><tt>-k _keyfile_</tt></dt>

Specify the name and path of the file containing the NTP authentication keys.

<dt><tt>-l _logfile_</tt></dt>

Specify the name and path of the log file. The default is the system log facility.

<dt><tt>-m</dt></tt>
    
Synchronize using NTP multicast messages on the IP multicast group address 224.0.1.1 (requires multicast kernel).

<dt><tt>-p _pidfile_</tt></dt>

Specify the name and path to record the <tt>xntpd</tt>'s process ID.  

<dt><tt>-r _broadcastdelay_</tt></dt>

Specify the default propagation delay from the broadcast/multicast server and this computer. This is used only if the delay cannot be computed automatically by the protocol.

<dt><tt>-s _statsdir_</tt></dt>

Specify the directory path for files created by the statistics facility. 

<dt><tt>-t _key_</tt></dt>

Add a key number to the trusted key list. 

<dt><tt>-v _variable_</tt></dt>

Add a system variable.

<dt><tt>-V _variable_</tt></dt>

Add a system variable listed by default.

* * *

#### The Configuration File

The <tt>xntpd</tt> configuration file is read at initial startup in order to specify the synchronization sources, modes and other related information. Usually, it is installed in the <tt>/etc</tt> directory, but could be installed elsewhere (see the <tt>-c _conffile_</tt> command line option). The file format is similar to other Unix configuration files - comments begin with a <tt>#</tt> character and extend to the end of the line; blank lines are ignored. Configuration commands consist of an initial keyword followed by a list of arguments, some of which may be optional, separated by whitespace. Commands may not be continued over multiple lines. Arguments may be host names, host addresses written in numeric, dotted-quad form, integers, floating point numbers (when specifying times in seconds) and text strings. Optional arguments are delimited by <tt>[ ]</tt> in the following descriptions, while alternatives are separated by <tt>|</tt>. The notation <tt>[ ... ]</tt> means an optional, indefinite repetition of the last item before the <tt>[ ... ]</tt>.

See the following pages for configuration and control options. While there is a rich set of options available, the only required option is one or more <tt>server, peer</tt> or <tt>broadcast</tt> commands described in the Configuration Options page. The [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/3-5.93e/notes) page contains an extended discussion of these options. 

[Configuration Options](/archives/3-5.93e/confopt)  
[Authentication Options](/archives/3-5.93e/authopt)  
[Monitoring Options](/archives/3-5.93e/monopt)  
[Access Control Options](/archives/3-5.93e/accopt)   
[Reference Clock Options](/archives/3-5.93e/clockopt)  
[Miscellaneous Options](/archives/3-5.93e/miscopt)

* * *

#### Files

<tt>/etc/ntp.conf</tt> - the default name of the configuration file

<tt>/etc/ntp.drift</tt> - the default name of the drift file 

<tt>/etc/ntp.keys</tt> - the default name of the key file 

* * *

#### Bugs

<tt>xntpd</tt> has gotten rather fat. While not huge, it has gotten larger than might be desirable for an elevated-priority daemon running on a workstation, particularly since many of the fancy features which consume the space were designed more with a busy primary server, rather than a high stratum workstation, in mind. 