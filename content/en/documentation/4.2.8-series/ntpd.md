---
title: "ntpd - Network Time Protocol (NTP) daemon"
type: archives
---

![gif](/archives/pic/wingdorothy.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures/)

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

<code>ntpd [ -46aAbdDgLmnNqx ] [ -c _conffile_ ] [ -f _driftfile_ ] [ -i _jaildir_ ] [ -I _InterfaceOrAddress_ ] [ -k _keyfile_ ] [ -l _logfile_ ] [ -p _pidfile_ ] [ -P _priority_ ] [ -r _broadcastdelay_ ] [ -s _statsdir_ ] [ -t _key_ ] [ -u _user_[:_group_] ] [ -U _interface_update_interval_ ] [ -v _variable_ ] [ -V _variable_ ]</code>

* * *

#### Description

The <code>ntpd</code> program is an operating system daemon that synchronizes the system clock to remote NTP time servers or local reference clocks. It is a complete implementation of NTP version 4 defined by [RFC 5905](/reflib/rfc/rfc5905.txt), but also retains compatible with version 3 defined by [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf) and versions 1 and 2, defined by [RFC 1059](/reflib/rfc/rfc1059.txt) and [RFC 1119](/reflib/rfc/rfc1119/rfc1119b.pdf), respectively. The program can operate in any of several modes, including client/server, symmetric and broadcast modes, and with both symmetric-key and public key-cryptography

The <code>ntpd</code> program ordinarily requires a configuration file described on this page. It contains configuration commands described on the pages listed above. However a client can discover remote servers and configure them automatically. This makes it possible to deploy a fleet of workstations without specifying configuration details specific to the local environment. Further details are on the [Automatic Server Discovery](/archives/4.2.8-series/discover/) page.

The <code>ntpd</code> program normally operates continuously while adjusting the system time and frequency, but in some cases this might not be practical. With the <code>-q</code> option <code>ntpd</code> operates as in continuous mode, but exits just after setting the clock for the first time. Most applications will probably want to specify the <code>iburst</code> option with the <code>server</code> command. With this option a volley of messages is exchanged to groom the data and set the clock in about ten seconds. If nothing is heard after a few minutes, the daemon times out and exits without setting the clock.

* * *

#### Command Line Options

<code>**-4**</code>

: Force DNS resolution of host names to the IPv4 namespace.

<code>**-6**</code>

: Force DNS resolution of host names to the IPv6 namespace.

<code>**-a**</code>

: Require cryptographic authentication for broadcast client, multicast client and symmetric passive associations. This is the same operation as the <code>enable auth</code> command and is the default.

<code>**-A**</code>

: Do not require cryptographic authentication for broadcast client, multicast client and symmetric passive associations. This is the same operation as the <code>disable auth</code> command and almost never a good idea.

<code>**-b**</code>

: Enable the client to synchronize to broadcast servers.

<code>**-c _conffile_**</code>

: Specify the name and path of the configuration file. Without the option the default is <code>/etc/ntp.conf</code>.

<code>**-d**</code>

: Disable switching into daemon mode, so <code>ntpd</code> stays attached to the starting terminal which will get all the debugging printout. Also, <code>^C</code> will kill it. This option may occur more than once, with each occurrence indicating greater detail of display.

<code>**-D _level_**</code>

: Specify debugging level directly, with <code>level</code> corresponding to the number of <code>-d</code> options..

<code>**-f _driftfile_**</code>

: Specify the name and path of the frequency file. This is the same operation as the <code>driftfile _driftfile_</code> configuration command.

<code>**-g**</code>

: Normally, <code>ntpd</code> exits with a message to the system log if the offset exceeds the panic threshold, which is 1000 s by default. This option allows the time to be set to any value without restriction; however, this can happen only once. If the threshold is exceeded after that, <code>ntpd</code> will exit with a message to the system log. This option can be used with the <code>-q</code> and <code>-x</code> options. See the <code>tinker</code> command for other options.

<code>**-i _jaildir_**</code>

: Chroot the server to the directory _<code>jaildir</code>_. This option also implies that the server attempts to drop root privileges at startup (otherwise, chroot gives very little additional security), and it is only available if the OS supports to run the server without full root privileges. You may need to also specify a <code>-u</code> option.

<code>**-I [_address_ | _interface name_]**</code>

: Open the network address given, or all the addresses associated with the given interface name. This option may appear multiple times. This option also implies not opening other addresses, except wildcard and localhost. This option is deprecated. Please consider using the configuration file [interface](/archives/4.2.8-series/miscopt/) command, which is more versatile.

<code>**-k _keyfile_**</code>

: Specify the name and path of the symmetric key file. This is the same operation as the <code>keys _keyfile_</code> command.

<code>**-l _logfile_**</code>

: Specify the name and path of the log file. The default is the system log file. This is the same operation as the <code>logfile _logfile_</code> command.

<code>**-m**</code>

: Once the system clock is synchronized, register with mDNS as an available server.

<code>**-L**</code>

: Do not listen to virtual interfaces, defined as those with names containing a colon. This option is deprecated. Please consider using the configuration file [interface](/archives/4.2.8-series/miscopt/) command, which is more versatile.

<code>**-M**</code>

: Raise scheduler precision to its maximum (1 ms) using <code>timeBeginPeriod</code>. (Windows only)

<code>**-n**</code>

: Don't fork.

<code>**-N**</code>

: To the extent permitted by the operating system, run the <code>ntpd</code> at the highest priority.

<code>**-p _pidfile_**</code>

: Specify the name and path of the file used to record the <code>ntpd</code> process ID. This is the same operation as the <code>pidfile _pidfile_</code> command.

<code>**-P _priority_**</code>

: To the extent permitted by the operating system, run the <code>ntpd</code> at the specified priority.

<code>**-q**</code>

: Exit the <code>ntpd</code> just after the first time the clock is set. This behavior mimics that of the <code>ntpdate</code> program, which is to be retired. The <code>-g</code> and <code>-x</code> options can be used with this option.

> Note: The kernel time discipline is disabled with this option.

<code>**-r _broadcastdelay_**</code>

: Specify the default propagation delay from the broadcast/multicast server to this client. This is necessary only if the delay cannot be computed automatically by the protocol.

<code>**-s _statsdir_**</code>

: Specify the directory path for files created by the statistics facility. This is the same operation as the <code>statsdir _statsdir_</code> command.

<code>**-t _key_**</code>

: Add a key number to the trusted key list. This option can occur more than once. This is the same operation as the <code>trustedkey _key_</code> command.

<code>**-u _user[:group]_**</code>

: Specify a user, and optionally a group, to switch to. This option is only available if the OS supports running the server without full root privileges. Currently, this option is supported under NetBSD (configure with <code>-\-enable-clockctl</code>) and Linux (configure with <code>-\-enable-linuxcaps</code>).

<code>**-U _interface update interval_**</code>

: Number of seconds to wait between interface list scans to pick up old and delete network interface. Set to 0 to disable dynamic interface list updating. The default is to scan every 5 minutes.

<code>**-v _variable_**</code>
: <code>**-V _variable_**</code>

: Add a system variable listed by default.

<code>**-x**</code>

: Normally, the time is slewed if the offset is less than the step threshold, which is 128 ms by default, and stepped if above the threshold. This option sets the threshold to 600 s, which is well within the accuracy window to set the clock manually. Note: Since the slew rate of typical Unix kernels is limited to 0.5 ms/s, each second of adjustment requires an amortization interval of 2000 s. Thus, an adjustment as much as 600 s will take almost 14 days to complete. This option can be used with the <code>-g</code> and <code>-q</code> options. See the <code>tinker</code> command for other options.

> Note: The kernel time discipline is disabled with this option.

<code>**-\-pccfreq _frequency_**</code>

: Substitute processor cycle counter for QueryPerformanceCounter unconditionally using the given frequency (in Hz). <code>-\-pccfreq</code> can be used on systems which do not use the PCC to implement QueryPerformanceCounter and have a fixed PCC frequency. The frequency specified must be accurate within 0.5 percent. <code>-\-usepcc</code> is equivalent on many systems and should be tried first, as it does not require determining the frequency of the processor cycle counter. For x86-compatible processors, the PCC is also referred to as <code>RDTSC</code>, which is the assembly-language instruction to retrieve the current value.  (Windows only)

<code>**-\-usepcc**</code>

: Substitute processor cycle counter for QueryPerformanceCounter if they appear equivalent. This option should be used only if the PCC frequency is fixed. Power-saving functionality on many laptops varies the PCC frequency. (Windows only)

* * *

#### The Configuration File

Ordinarily, <code>ntpd</code> reads the <code>ntp.conf</code> configuration file at startup in order to determine the synchronization sources and operating modes. It is also possible to specify a working, although limited, configuration entirely on the command line, obviating the need for a configuration file. This may be particularly useful when the local host is to be configured as a broadcast client, with servers determined by listening to broadcasts at run time.

Usually, the configuration file is installed as<code>/etc/ntp.conf</code>, but could be installed elsewhere (see the <code>-c _conffile_</code> command line option). The file format is similar to other Unix configuration files - comments begin with a <code>#</code> character and extend to the end of the line; blank lines are ignored.

Configuration commands consist of an initial command keyword followed by a list of option keywords separated by whitespace. Commands may not be continued over multiple lines. Options may be host names, host addresses written in numeric, dotted-quad form, integers, floating point numbers (when specifying times in seconds) and text strings. Optional arguments are delimited by <code>[ ]</code> in the options pages, while alternatives are separated by <code>|</code>. The notation <code>[ ... ]</code> means an optional, indefinite repetition of the last item before the <code>[ ... ]</code>.

* * *

#### Files

* * *

| File | Default | Option | Option |
| ----- | ----- | ----- | ----- |
| configuration file | `/etc/ntp.conf` | `-c` | `conffile` |
| frequency file | none | `-f` | `driftfile` |
| leapseconds file | none | | `leapfile` |
| process ID file | none | `-p` | `pidfile` |
| log file | system log | `-l` | `logfile` |
| include file | none | none | `includefile` |
| statistics path | `/var/NTP` | `-s` | `statsdir` |
| keys path | `/usr/local/etc` | none | `keysdir` |