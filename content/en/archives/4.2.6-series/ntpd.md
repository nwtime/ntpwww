---
title: "ntpd - Network Time Protocol (NTP) daemon"
type: archives
---

![gif](/archives/pic/wingdorothy.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures)

You need help from the monkeys.

Last update: 14-oct-09 22:23

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.6-series/ntpd/#synopsis)
*   [Description](/archives/4.2.6-series/ntpd/#description)
*   [Setting the Time and Frequency](/archives/4.2.6-series/ntpd/#setting-the-time-and-frequency)
*   [Operating Modes](/archives/4.2.6-series/ntpd/#operating-modes)
*   [Poll Interval Control](/archives/4.2.6-series/ntpd/#poll-interval-control)
*   [Leap Second Processing](/archives/4.2.6-series/ntpd/#leap-second-processing)
*   [Additional Features](/archives/4.2.6-series/ntpd/#additional-features)
*   [Command Line Options](/archives/4.2.6-series/ntpd/#command-line-options)
*   [The Configuration File](/archives/4.2.6-series/ntpd/#the-configuration-file)
*   [Files](/archives/4.2.6-series/ntpd/#files)
*   [Exit Codes](/archives/4.2.6-series/ntpd/#exit-codes)

* * *

#### Synopsis

<tt>ntpd [ -46aAbdDgLmnNqx ] [ -c _conffile_ ] [ -f _driftfile_ ] [ -i _jaildir_ ] [ -I _iface_ ] [ -k _keyfile_ ] [ -l _logfile_ ] [ -p _pidfile_ ] [ -P _priority_ ] [ -r _broadcastdelay_ ] [ -s _statsdir_ ] [ -t _key_ ] [ -u _user_[:_group_] ] [ -U _interface_update_interval_ ] [ -v _variable_ ] [ -V _variable_ ]</tt>

* * *  

#### Description

The <tt>ntpd</tt> program is an operating system daemon that synchronizes the system clock to remote NTP time servers or local reference clocks. It is a complete implementation of the Network Time Protocol (NTP) version 4, but also retains compatibility with version 3, as defined by RFC-1305, and version 1 and 2, as defined by RFC-1059 and RFC-1119, respectively. The program can operate in any of several modes, as described on the [Association Management](/archives/4.2.6-series/assoc) page, and with both symmetric key and public key cryptography, as described on the [Authentication Options](/archives/4.2.6-series/manyopt) page.

The <tt>ntpd</tt> program ordinarily requires a configuration file. However a client can discover remote servers and configure them automatically. This makes it possible to deploy a fleet of workstations without specifying configuration details specific to the local environment. Further details are on the [Automatic Server Discovery](/archives/4.2.6-series/manyopt) page.

Once the NTP software distribution has been compiled and installed and the configuration file constructed, the next step is to verify correct operation and fix any bugs that may result. Usually, the command line that starts the daemon is included in the system startup file, so it is executed only at system boot time; however, the daemon can be stopped and restarted from root at any time. Once started, the daemon will begin sending and receiving messages, as specified in the configuration file.

* * *

#### Setting the Time and Frequency

The <tt>ntpd</tt> program operates by exchanging messages with one or more servers at designated intervals ranging from about one minute to about 17 minutes. When started, the program requires several exchanges while the algorithms accumulate and groom the data before setting the clock. The initial delay to set the clock can be reduced using options on the [Server Options](/archives/4.2.6-series/confopt) page.

Most compters today incorporate a time-of-year (TOY) chip to maintain the time during periods when the power is off. When the machine is booted, the chip is used to initialize the operating system time. In case there is no TOY chip or the TOY time is more than 1000 s from the server time, <tt>ntpd</tt> assumes something must be terribly wrong and exits with a panic message to the system operator. With the <tt>-g</tt> option the clock will be initially set to the server time regardless of the chip time. However, once the clock has been set, an error greater than 1000 s will cause <tt>ntpd</tt> to exit anyway.

Under ordinary conditions, <tt>ntpd</tt> slews the clock so that the time is effectively continuous and never runs backwards. If due to extreme network congestion an error spike exceeds the _step threshold_, by default 128 ms, the spike is discarded. However, if the error persists for more than the _stepout threshold_, by default 900 s, the system clock is stepped to the correct value. In practice the need for a step has is extremely rare and almost always the result of a hardware failure. With the <tt>-x</tt> option the step threshold is increased to 600 s. Other options are available using the <tt>tinker</tt> command on the [Miscellaneous Options](/archives/4.2.6-series/miscopt) page.

The issues should be carefully considered before using these options. The maximum slew rate possible is limited to 500 parts-per-million (PPM) by the Unix kernel. As a result, the clock can take 2000 s for each second the clock is outside the acceptable range. During this interval the clock will not be consistent with any other network clock and the system cannot be used for distributed applications that require correctly synchronized network time.

The frequency file, usually called <tt>ntp.drift</tt>, contains the latest estimate of clock frequency. If this file does not exist when <tt>ntpd</tt> is started, it enters a special mode designed to measure the particular frequency directly. The measurement takes 15 minutes, after which the frequency is set and <tt>ntpd</tt> resumes normal mode where the time and frequency are continuously adjusted. The frequency file is updated at intervals of an hour or more depending on the measured clock stability.

* * *

#### Operating Modes

The <tt>ntpd</tt> program normally operates continuously while adjusting the time and frequency, but in some cases it may not be practical to run it continuously. With the <tt>-q</tt> option <tt>ntpd</tt> operates as in continous mode, but exits just after setting the clock for the first time with the configured servers. Most applications will probably want to specify the <tt>iburst</tt> option with the <tt>server</tt> command. With this option a volley of messages is exchanged to groom the data and set the clock in about 10 s. If nothing is heard after a few minutes, the daemon times out and exits.

* * *

#### Poll Interval Control

NTP uses an intricate heuristic algorithm to automatically control the poll interval for maximum accuracy consistent with minimum network overhead. The algorithm measures the incidental offset and jitter to determine the best poll interval. When <tt>ntpd</tt> starts, the interval is the default minimum 64 s. Under normal conditions when the clock discipline has stabilized, the interval increases in steps to the default maximum 1024 s. In addition, should a server become unreachable after some time, the interval increases in steps to the maximum in order to reduce network overhead.

The default poll interval range is suitable for most conditions, but can be changed using options on the [Server Options](/archives/4.2.6-series/confopt) and [Miscellaneous Options](/archives/4.2.6-series/miscopt) pages. However, when using maximum intervals much larger than the default, the residual clock frequency error must be small enough for the discipline loop to capture and correct. The capture range is 500 PPM with a 64-s interval decreasing by a factor of two for each interval doubling. At a 36-hr interval, for example, the capture range is only 0.24 PPM.

#### The huff-n'-puff Filter

In scenarios where a considerable amount of data are to be downloaded or uploaded over telephone modems, timekeeping quality can be seriously degraded. This occurs because the differential delays on the two directions of transmission can be quite large. In many cases the apparent time errors are so large as to exceed the step threshold and a step correction can occur during and after the data transfer.

The huff-n'-puff filter is designed to correct the apparent time offset in these cases. It depends on knowledge of the propagation delay when no other traffic is present, such as during other than work hours. The filter remembers the minimum delay over the most recent interval measured usually in hours. Under conditions of severe delay, the filter corrects the apparent offset using the sign of the offset and the difference between the apparent delay and minimum delay. The name of the filter reflects the negative (huff) and positive (puff) correction, which depends on the sign of the offset. The filter is activated by the <tt>tinker huffpuff</tt> command, as described in the [Miscellaneous Options](/archives/4.2.6-series/miscopt) page.

* * *

#### Leap Second Processing

As provided by international agreement, an extra second is sometimes inserted in Coordinated Universal Time (UTC) at the end of a selected month, usually June or December. The National Institutes of Standards and Technology (NIST) provides an historic leapseconds file at <tt>time.nist.gov</tt> for retrieval via FTP. When this file, usually called <tt>ntp-leapseconds.list</tt>, is copied and installed in a directory. The <tt>leapfile</tt> configuration command specifies the path to this file. At startup, <tt>ntpd</tt> reads it and initializes three leapsecond values: the NTP seconds at the next leap event, the offset of UTC relative to International Atomic Time (TAI) after the leap and the NTP seconds when the leapseconds file expires and should be retrieved again.

If a host does not have the leapsecond values, they can be obtained over the net using the Autokey security protocol. Ordinarily, the leapseconds file is installed on the primary servers and the values flow from them via secondary servers to the clients. When multiple servers are involved, the values with the latest expiration time are used.

If the latest leap is in the past, nothing further is done other than to install the TAI offset. If the leap is in the future less than 28 days, the leap warning bits are set. If in the future less than 23 hours, the kernel is armed to insert one second at the end of the current day. If the kernel is enabled, the leap is done automatically at that time; otherwise, the clock is effectively stopped for one second at the leap. Additional details are in the [The NTP Timescale and Leap Seconds](/reflib/leap) white paper.

If none of the above provisions are available, dependent servers and clients tally the leap warning bits of surviving servers and reference clocks. When a majority of the survivors show warning, a leap is programmed at the end of the current month. During the month and day of insertion, they operate as above. In this way the leap is propagated at all dependent servers and clients.

* * *

#### Additional Features

A new experimental feature called interleaved modes can be used in NTP symmetric or broadcast modes. It is designed to improve accuracy by avoiding kernel latency and queueing delay, as described on the [NTP Interleaved Modes](/archives/4.2.6-series/xleave) page. It is activated by the <tt>xleave</tt> option with the <tt>peer</tt> or <tt>broadcast</tt> configuration commands. The NTP protocol automatically reconfigures in normal or interleaved mode as required. Ordinary broadcast clients can use the same servers as interleaved clients at the same time. Further details are in the white paper [NTP Interleaved On-Wire Protocol](/reflib/onwire) and the briefing [Interleaved Synchronization Protocols for LANs and Space Data Links](/reflib/brief/onwire/onwire.pdf).

If <tt>ntpd</tt>, is configured with NetInfo support, it will attempt to read its configuration from the NetInfo service if the default <tt>ntp.conf</tt> file cannot be read and no file is specified by the <tt>-c</tt> option.

In contexts where a host name is expected, a <tt>-4</tt> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <tt>-6</tt> qualifier forces DNS resolution to the IPv6 namespace.

Various internal <tt>ntpd</tt> variables can be displayed and configuration options altered while the <tt>ntpd</tt> is running using the <tt>[ntpq](/archives/4.2.6-series/ntpq)</tt> and <tt>[ntpdc](/archives/4.2.6-series/ntpdc)</tt> utility programs.

When <tt>ntpd</tt> starts it looks at the value of <tt>umask</tt>, and if zero <tt>ntpd</tt> will set the <tt>umask</tt> to <tt>022</tt>.

Unless the <tt>-n</tt>, <tt>-d</tt> or <tt>-D</tt> option is used, <tt>ntpd</tt> changes the current working directory to the root directory, so any options or commands specifying paths need to use an absolute path or a path relative to the root.

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

Specify the name and path of the configuration file, default <tt>/etc/ntp.conf</tt>.

<dt><tt>-d</tt></dt>

Specify debugging mode. This option may occur more than once, with each occurrence indicating greater detail of display.

<dt><tt>-D _level_</tt></dt>

Specify debugging level directly.

<dt><tt>-f _driftfile_</tt></dt>

Specify the name and path of the frequency file. This is the same operation as the <tt>driftfile _driftfile_</tt> command.

<dt><tt>-g</tt></dt>

Normally, <tt>ntpd</tt> exits with a message to the system log if the offset exceeds the panic threshold, which is 1000 s by default. This option allows the time to be set to any value without restriction; however, this can happen only once. If the threshold is exceeded after that, <tt>ntpd</tt> will exit with a message to the system log. This option can be used with the <tt>-q</tt> and <tt>-x</tt> options. See the <tt>tinker</tt> command for other options.

<dt><tt>-i _jaildir_</tt></dt>

Chroot the server to the directory _<tt>jaildir</tt>_. This option also implies that the server attempts to drop root privileges at startup (otherwise, chroot gives very little additional security), and it is only available if the OS supports to run the server without full root privileges. You may need to also specify a <tt>-u</tt> option.

<dt id="--interface"><tt>-I [_address_ | _interface name_]</tt></dt>

Open the network address given, or all the addresses associated with the given interface name. This option may appear multiple times. This option also implies not opening other addresses, except wildcard and localhost. This option is deprecated. Please consider using the configuration file [interface](/archives/4.2.6-series/miscopt#interface) command, which is more versatile.

<dt><tt>-k _keyfile_</tt></dt>

Specify the name and path of the symmetric key file. This is the same operation as the <tt>keys _keyfile_</tt> command.

<dt><tt>-l _logfile_</tt></dt>

Specify the name and path of the log file. The default is the system log file. This is the same operation as the <tt>logfile _logfile_</tt> command.

<dt id="--novirtualips"><tt>-L</tt></dt>

Do not listen to virtual interfaces, defined as those with names containing a colon. This option is deprecated. Please consider using the configuration file [interface](/archives/4.2.6-series/miscopt#interface) command, which is more versatile.

<dt><tt>-M</tt></dt>

Raise scheduler precision to its maximum (1 msec) using timeBeginPeriod. (Windows only)

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

Number of seconds to wait between interface list scans to pick up new and delete network interface. Set to 0 to disable dynamic interface list updating. The default is to scan every 5 minutes.

<dt><tt>-v _variable_</tt></dt>

<dt><tt>-V _variable_</tt></dt>

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

| File | Default | Option | Command |
| ----- | ----- | ----- | ----- |
| configuration file | `/etc/ntp.conf` | `-c` | none |
| frequency file | none | `-f` | `driftfile` |
| leapseconds file | none | | `leapfile` |
| process ID file | none | `-p | `pidfile` |
| log file | system log | `-l` | `logfile` |
| include file | none | none | `includefile` |
| statistics path | `/var/NTP` | `-s` | `statsdir` |
| keys path | `/usr/local/etc` | `-k` | `keysdir` |

#### Exit Codes

A non-zero exit code indicates an error. Any error messages are logged to the system log by default.

The exit code is 0 only when <tt>ntpd</tt> is terminated by a signal, or when the <tt>-q</tt> option is used and <tt>ntpd</tt> successfully sets the system clock.
