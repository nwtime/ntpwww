---
title: "ntpd - Network Time Protocol (NTP) daemon"
type: archives
---

![gif](/archives/pic/wingdorothy.gif)[from _The Wizard of Oz_, L. Frank Baum](http://www.eecis.udel.edu/~mills/pictures.html)

You need help from the monkeys.

Last update: 10-Mar-2014 05:14 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.8-series/ntpd/#synopsis)
*   [Description](/archives/4.2.8-series/ntpd/#description)
*   [Command Line Options](/archives/4.2.8-series/ntpd/#command-line-options)
*   [The Configuration File](/archives/4.2.8-series/ntpd/#the-configuration-file)
*   [Files](/archives/4.2.8-series/ntpd/#files)

* * *

#### Synopsis

<tt>ntpd [ -46aAbdDgLmnNqx ] [ -c _conffile_ ] [ -f _driftfile_ ] [ -i _jaildir_ ] [ -I _InterfaceOrAddress_ ] [ -k _keyfile_ ] [ -l _logfile_ ] [ -p _pidfile_ ] [ -P _priority_ ] [ -r _broadcastdelay_ ] [ -s _statsdir_ ] [ -t _key_ ] [ -u _user_[:_group_] ] [ -U _interface_update_interval_ ] [ -v _variable_ ] [ -V _variable_ ]</tt>

* * *  

#### Description

The <tt>ntpd</tt> program is an operating system daemon that synchronizes the system clock to remote NTP time servers or local reference clocks. It is a complete implementation of NTP version 4 defined by RFC-5905, but also retains compatible with version 3 defined by RFC-1305 and versions 1 and 2, defined by RFC-1059 and RFC-1119, respectively. The program can operate in any of several modes, including client/server, symmetric and broadcast modes, and with both symmetric-key and public key-cryptography

The <tt>ntpd</tt> program ordinarily requires a configuration file described on this page. It contains configuration commands described on the pages listed above. However a client can discover remote servers and configure them automatically. This makes it possible to deploy a fleet of workstations without specifying configuration details specific to the local environment. Further details are on the

The <tt>ntpd</tt> program normally operates continuously while adjusting the system time and frequency, but in some cases this might not be practical. With the <tt>-q</tt> option <tt>ntpd</tt> operates as in continuous mode, but exits just after setting the clock for the first time. Most applications will probably want to specify the <tt>iburst</tt> option with the <tt>server</tt> command. With this option a volley of messages is exchanged to groom the data and set the clock in about ten seconds. If nothing is heard after a few minutes, the daemon times out and exits without setting the clock.

* * *

#### Command Line Options

<dt><tt>-4</tt></dt>

Force DNS resolution of host names to the IPv4 namespace.

<dt><tt>-6</tt></dt>

Force DNS resolution of host names to the IPv6 namespace.

<dt><tt>-a</tt></dt>

Require cryptographic authentication for broadcast client, multicast client and symmetric passive associations. This is the same operation as the <tt>enable auth</tt> command and is the default.

<dt><tt>-A</tt></dt>

Do not require cryptographic authentication for broadcast client, multicast client and symmetric passive associations. This is the same operation as the <tt>disable auth</tt> command and almost never a good idea.

<dt><tt>-b</tt></dt>

Enable the client to synchronize to broadcast servers.

<dt><tt>-c _conffile_</tt></dt>

Specify the name and path of the configuration file. Without the option the default is <tt>/etc/ntp.conf</tt>.

<dt><tt>-d</tt></dt>

Disable switching into daemon mode, so <tt>ntpd</tt> stays attached to the starting terminal which will get all the debugging printout. Also, ^C will kill it. This option may occur more than once, with each occurrence indicating greater detail of display.

<dt><tt>-D _level_</tt></dt>

Specify debugging level directly, with <tt>level</tt> corresponding to the numbe of <tt>-d</tt> options..

<dt><tt>-f _driftfile_</tt></dt>

Specify the name and path of the frequency file. This is the same operation as the <tt>driftfile _driftfile_</tt> configuration command.

<dt><tt>-g</tt></dt>

Normally, <tt>ntpd</tt> exits with a message to the system log if the offset exceeds the panic threshold, which is 1000 s by default. This option allows the time to be set to any value without restriction; however, this can happen only once. If the threshold is exceeded after that, <tt>ntpd</tt> will exit with a message to the system log. This option can be used with the <tt>-q</tt> and <tt>-x</tt> options. See the <tt>tinker</tt> command for other options.

<dt><tt>-i _jaildir_</tt></dt>

Chroot the server to the directory _<tt>jaildir</tt>_. This option also implies that the server attempts to drop root privileges at startup (otherwise, chroot gives very little additional security), and it is only available if the OS supports to run the server without full root privileges. You may need to also specify a <tt>-u</tt> option.

<dt id="--interface"><tt>-I [_address_ | _interface name_]</tt></dt>

Open the network address given, or all the addresses associated with the given interface name. This option may appear multiple times. This option also implies not opening other addresses, except wildcard and localhost. This option is deprecated. Please consider using the configuration file [interface](miscopt.html#interface) command, which is more versatile.

<dt><tt>-k _keyfile_</tt></dt>

Specify the name and path of the symmetric key file. This is the same operation as the <tt>keys _keyfile_</tt> command.

<dt><tt>-l _logfile_</tt></dt>

Specify the name and path of the log file. The default is the system log file. This is the same operation as the <tt>logfile _logfile_</tt> command.

<dt id="--mdns"><tt>-m</tt></dt>

Once the system clock is synchronized, register with mDNS as an available server.

<dt id="--novirtualips"><tt>-L</tt></dt>

Do not listen to virtual interfaces, defined as those with names containing a colon. This option is deprecated. Please consider using the configuration file [interface](miscopt.html#interface) command, which is more versatile.

<dt><tt>-M</tt></dt>

Raise scheduler precision to its maximum (1 ms) using timeBeginPeriod. (Windows only)

<dt><tt>-n</tt></dt>

Don't fork.

<dt><tt>-N</tt></dt>

To the extent permitted by the operating system, run the <tt>ntpd</tt> at the highest priority.

<dt><tt>-p _pidfile_</tt></dt>

Specify the name and path of the file used to record the <tt>ntpd</tt> process ID. This is the same operation as the <tt>pidfile _pidfile_</tt> command.

<dt><tt>-P _priority_</tt></dt>

To the extent permitted by the operating system, run the <tt>ntpd</tt> at the specified priority.

<dt><tt>-q</tt></dt>

Exit the <tt>ntpd</tt> just after the first time the clock is set. This behavior mimics that of the <tt>ntpdate</tt> program, which is to be retired. The <tt>-g</tt> and <tt>-x</tt> options can be used with this option. Note: The kernel time discipline is disabled with this option.

<dt><tt>-r _broadcastdelay_</tt></dt>

Specify the default propagation delay from the broadcast/multicast server to this client. This is necessary only if the delay cannot be computed automatically by the protocol.

<dt><tt>-s _statsdir_</tt></dt>

Specify the directory path for files created by the statistics facility. This is the same operation as the <tt>statsdir _statsdir_</tt> command.

<dt><tt>-t _key_</tt></dt>

Add a key number to the trusted key list. This option can occur more than once. This is the same operation as the <tt>trustedkey _key_</tt> command.

<dt><tt>-u _user[:group]_</tt></dt>

Specify a user, and optionally a group, to switch to. This option is only available if the OS supports running the server without full root privileges. Currently, this option is supported under NetBSD (configure with <tt>--enable-clockctl</tt>) and Linux (configure with --<tt>enable-linuxcaps</tt>).

<dt><tt>-U _interface update interval_</tt></dt>

Number of seconds to wait between interface list scans to pick up old and delete network interface. Set to 0 to disable dynamic interface list updating. The default is to scan every 5 minutes.

<dt><tt>-v _variable_</tt>  
<tt>-V _variable_</tt></dt>

Add a system variable listed by default.

<dt><tt>-x</tt></dt>

Normally, the time is slewed if the offset is less than the step threshold, which is 128 ms by default, and stepped if above the threshold. This option sets the threshold to 600 s, which is well within the accuracy window to set the clock manually. Note: Since the slew rate of typical Unix kernels is limited to 0.5 ms/s, each second of adjustment requires an amortization interval of 2000 s. Thus, an adjustment as much as 600 s will take almost 14 days to complete. This option can be used with the <tt>-g</tt> and <tt>-q</tt> options. See the <tt>tinker</tt> command for other options. Note: The kernel time discipline is disabled with this option.

<dt><tt>--pccfreq _frequency_</tt></dt>

Substitute processor cycle counter for QueryPerformanceCounter unconditionally using the given frequency (in Hz). <tt>--pccfreq</tt> can be used on systems which do not use the PCC to implement QueryPerformanceCounter and have a fixed PCC frequency. The frequency specified must be accurate within 0.5 percent. <tt>--usepcc</tt> is equivalent on many systems and should be tried first, as it does not require determining the frequency of the processor cycle counter. For x86-compatible processors, the PCC is also referred to as <tt>RDTSC</tt>, which is the assembly-language instruction to retrieve the current value.  (Windows only)

<dt><tt>--usepcc</tt></dt>

Substitute processor cycle counter for QueryPerformanceCounter if they appear equivalent. This option should be used only if the PCC frequency is fixed. Power-saving functionality on many laptops varies the PCC frequency. (Windows only)

* * *

#### The Configuration File

Ordinarily, <tt>ntpd</tt> reads the <tt>ntp.conf</tt> configuration file at startup in order to determine the synchronization sources and operating modes. It is also possible to specify a working, although limited, configuration entirely on the command line, obviating the need for a configuration file. This may be particularly useful when the local host is to be configured as a broadcast client, with servers determined by listening to broadcasts at run time.

Usually, the configuration file is installed as<tt>/etc/ntp.conf</tt>, but could be installed elsewhere (see the <tt>-c _conffile_</tt> command line option). The file format is similar to other Unix configuration files - comments begin with a <tt>#</tt> character and extend to the end of the line; blank lines are ignored.

Configuration commands consist of an initial command keyword followed by a list of option keywords separated by whitespace. Commands may not be continued over multiple lines. Options may be host names, host addresses written in numeric, dotted-quad form, integers, floating point numbers (when specifying times in seconds) and text strings. Optional arguments are delimited by <tt>[ ]</tt> in the options pages, while alternatives are separated by <tt>|</tt>. The notation <tt>[ ... ]</tt> means an optional, indefinite repetition of the last item before the <tt>[ ... ]</tt>.

* * *

#### Files

* * *

| File | Default | Option | Option |
| ----- | ----- | ----- | ----- |
| configuration file | `/etc/ntp.conf` | `-c` | `conffile` |
| frequency file | none | `-f` | `driftfile` |
| leapseconds file | none | | `leapfile` |
| process ID file | none | `-p | `pidfile` |
| log file | system log | `-l` | `logfile` |
| include file | none | none | `includefile` |
| statistics path | `/var/NTP` | `-s` | `statsdir` |
| keys path | `/usr/local/etc` | none | `keysdir` |