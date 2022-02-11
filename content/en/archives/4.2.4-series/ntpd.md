---
title: "ntpd - Network Time Protocol (NTP) daemon"
type: archives
---

![gif](/archives/pic/wingdorothy.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures/)

You need help from the monkeys.

Last update: 18:44 UTC Thursday, July 28, 2005

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.4-series/ntpd/#synopsis)
*   [Description](/archives/4.2.4-series/ntpd/#description)
*   [How NTP Operates](/archives/4.2.4-series/ntpd/#how-ntp-operates)
*   [Frequency Discipline](/archives/4.2.4-series/ntpd/#frequency-discipline)
*   [Operating Modes](/archives/4.2.4-series/ntpd/#operating-modes)
*   [Poll Interval Control](/archives/4.2.4-series/ntpd/#poll-interval-control)
*   [The huff-n'-puff Filter](/archives/4.2.4-series/ntpd/#the-huff-n-puff-filter)
*   [Notes](/archives/4.2.4-series/ntpd/#notes)
*   [Command Line Options](/archives/4.2.4-series/ntpd/#command-line-options)
*   [The Configuration File](/archives/4.2.4-series/ntpd/#the-configuration-file)
*   [Configuration Options](/archives/4.2.4-series/ntpd/#configuration-options)
*   [Files](/archives/4.2.4-series/ntpd/#files)

* * *

#### Synopsis

<code>ntpd [ -46aAbdDgLmnNqx ] [ -c _conffile_ ] [ -f _driftfile_ ] [ -i _jaildir_ ] [ -k _keyfile_ ] [ -l _logfile_ ] [ -p _pidfile_ ] [ -P _priority_ ] [ -r _broadcastdelay_ ] [ -s _statsdir_ ] [ -t _key_ ] [ -u _user_[:_group_] ] [ -U _interface_update_interval_ ] [ -v _variable_ ] [ -V _variable_ ]</code>

* * *  

#### Description

The <code>ntpd</code> program is an operating system daemon which sets and maintains the system time of day in synchronism with Internet standard time servers. It is a complete implementation of the Network Time Protocol (NTP) version 4, but also retains compatibility with version 3, as defined by RFC-1305, and version 1 and 2, as defined by RFC-1059 and RFC-1119, respectively. <code>ntpd</code> does most computations in 64-bit floating point arithmetic and does relatively clumsy 64-bit fixed point operations only when necessary to preserve the ultimate precision, about 232 picoseconds. While the ultimate precision is not achievable with ordinary workstations and networks of today, it may be required with future gigahertz CPU clocks and gigabit LANs.

* * *

#### How NTP Operates

The <code>ntpd</code> program operates by exchanging messages with one or more configured servers at designated poll intervals. When started, whether for the first or subsequent times, the program requires several exchanges from the majority of these servers so the signal processing and mitigation algorithms can accumulate and groom the data and set the clock. In order to protect the network from bursts, the initial poll interval for each server is delayed an interval randomized over a few seconds. At the default initial poll interval of 64s, several minutes can elapse before the clock is set. The initial delay to set the clock can be reduced using the <code>iburst</code> keyword with the <code>server</code> configuration command, as described on the [Configuration Options](/archives/4.2.4-series/confopt/) page.

Most operating systems and hardware of today incorporate a time-of-year (TOY) chip to maintain the time during periods when the power is off. When the machine is booted, the chip is used to initialize the operating system time. After the machine has synchronized to a NTP server, the operating system corrects the chip from time to time. In case there is no TOY chip or for some reason its time is more than 1000s from the server time, <code>ntpd</code> assumes something must be terribly wrong and the only reliable action is for the operator to intervene and set the clock by hand. This causes <code>ntpd</code> to exit with a panic message to the system log. The <code>-g</code> option overrides this check and the clock will be set to the server time regardless of the chip time. However, and to protect against broken hardware, such as when the CMOS battery fails or the clock counter becomes defective, once the clock has been set, an error greater than 1000s will cause <code>ntpd</code> to exit anyway.

Under ordinary conditions, <code>ntpd</code> adjusts the clock in small steps so that the timescale is effectively continuous and without discontinuities. Under conditions of extreme network congestion, the roundtrip delay jitter can exceed three seconds and the synchronization distance, which is equal to one-half the roundtrip delay plus error budget terms, can become very large. The <code>ntpd</code> algorithms discard sample offsets exceeding 128 ms, unless the interval during which no sample offset is less than 128 ms exceeds 900s. The first sample after that, no matter what the offset, steps the clock to the indicated time. In practice this reduces the false alarm rate where the clock is stepped in error to a vanishingly low incidence.

As the result of this behavior, once the clock has been set, it very rarely strays more than 128 ms, even under extreme cases of network path congestion and jitter. Sometimes, in particular when <code>ntpd</code> is first started, the error might exceed 128 ms. This may on occasion cause the clock to be set backwards if the local clock time is more than 128 s in the future relative to the server. In some applications, this behavior may be unacceptable. If the <code>-x</code> option is included on the command line, the clock will never be stepped and only slew corrections will be used.

The issues should be carefully explored before deciding to use the <code>-x</code> option. The maximum slew rate possible is limited to 500 parts-per-million (PPM) as a consequence of the correctness principles on which the NTP protocol and algorithm design are based. As a result, the local clock can take a long time to converge to an acceptable offset, about 2,000 s for each second the clock is outside the acceptable range. During this interval the local clock will not be consistent with any other network clock and the system cannot be used for distributed applications that require correctly synchronized network time.

In spite of the above precautions, sometimes when large frequency errors are present the resulting time offsets stray outside the 128-ms range and an eventual step or slew time correction is required. If following such a correction the frequency error is so large that the first sample is outside the acceptable range, <code>ntpd</code> enters the same state as when the <code>ntp.drift</code> file is not present. The intent of this behavior is to quickly correct the frequency and restore operation to the normal tracking mode. In the most extreme cases (<code>time.ien.it</code> comes to mind), there may be occasional step/slew corrections and subsequent frequency corrections. It helps in these cases to use the <code>burst</code> keyword when configuring the server.

* * *

#### Frequency Discipline

The <code>ntpd</code> behavior at startup depends on whether the frequency file, usually <code>ntp.drift</code>, exists. This file contains the latest estimate of clock frequency error. When the <code>ntpd</code> is started and the file does not exist, the <code>ntpd</code> enters a special mode designed to quickly adapt to the particular system clock oscillator time and frequency error. This takes approximately 15 minutes, after which the time and frequency are set to nominal values and the <code>ntpd</code> enters normal mode, where the time and frequency are continuously tracked relative to the server. After one hour the frequency file is created and the current frequency offset written to it. When the <code>ntpd</code> is started and the file does exist, the <code>ntpd</code> frequency is initialized from the file and enters normal mode immediately. After that the current frequency offset is written to the file at hourly intervals.

* * *

#### Operating Modes

<code>ntpd</code> can operate in any of several modes, including symmetric active/passive, client/server broadcast/multicast and manycast, as described in the [Association Management](/archives/4.2.4-series/assoc/) page. It normally operates continuously while monitoring for small changes in frequency and trimming the clock for the ultimate precision. However, it can operate in a one-time mode where the time is set from an external server and frequency is set from a previously recorded frequency file. A broadcast/multicast or manycast client can discover remote servers, compute server-client propagation delay correction factors and configure itself automatically. This makes it possible to deploy a fleet of workstations without specifying configuration details specific to the local environment.

By default, <code>ntpd</code> runs in continuous mode where each of possibly several external servers is polled at intervals determined by an intricate state machine. The state machine measures the incidental roundtrip delay jitter and oscillator frequency wander and determines the best poll interval using a heuristic algorithm. Ordinarily, and in most operating environments, the state machine will start with 64s intervals and eventually increase in steps to 1024s. A small amount of random variation is introduced in order to avoid bunching at the servers. In addition, should a server become unreachable for some time, the poll interval is increased in steps to 1024s in order to reduce network overhead.

In some cases it may not be practical for <code>ntpd</code> to run continuously. A common workaround has been to run the <code>ntpdate</code> program from a <code>cron</code> job at designated times. However, this program does not have the crafted signal processing, error checking and mitigation algorithms of <code>ntpd</code>. The <code>-q</code> option is intended for this purpose. Setting this option will cause <code>ntpd</code> to exit just after setting the clock for the first time. The procedure for initially setting the clock is the same as in continuous mode; most applications will probably want to specify the <code>iburst</code> keyword with the <code>server</code> configuration command. With this keyword a volley of messages are exchanged to groom the data and the clock is set in about 10 s. If nothing is heard after a couple of minutes, the daemon times out and exits. After a suitable period of mourning, the <code>ntpdate</code> program may be retired.

When kernel support is available to discipline the clock frequency, which is the case for stock Solaris, Tru64, Linux and FreeBSD, a useful feature is available to discipline the clock frequency. First, <code>ntpd</code> is run in continuous mode with selected servers in order to measure and record the intrinsic clock frequency offset in the frequency file. It may take some hours for the frequency and offset to settle down. Then the <code>ntpd</code> is stopped and run in one-time mode as required. At each startup, the frequency is read from the file and initializes the kernel frequency.

* * *

#### Poll Interval Control

This version of NTP includes an intricate state machine to reduce the network load while maintaining a quality of synchronization consistent with the observed jitter and wander. There are a number of ways to tailor the operation in order enhance accuracy by reducing the interval or to reduce network overhead by increasing it. However, the user is advised to carefully consider the consequences of changing the poll adjustment range from the default minimum of 64 s to the default maximum of 1,024 s. The default minimum can be changed with the <code>tinker minpoll</code> command to a value not less than 16 s. This value is used for all configured associations, unless overridden by the <code>minpoll</code> option on the configuration command. Note that most device drivers will not operate properly if the poll interval is less than 64 s and that the broadcast server and manycast client associations will also use the default, unless overridden.

In some cases involving dial up or toll services, it may be useful to increase the minimum interval to a few tens of minutes and maximum interval to a day or so. Under normal operation conditions, once the clock discipline loop has stabilized the interval will be increased in steps from the minimum to the maximum. However, this assumes the intrinsic clock frequency error is small enough for the discipline loop correct it. The capture range of the loop is 500 PPM at an interval of 64s decreasing by a factor of two for each doubling of interval. At a minimum of 1,024 s, for example, the capture range is only 31 PPM. If the intrinsic error is greater than this, the drift file <code>ntp.drift</code> will have to be specially tailored to reduce the residual error below this limit. Once this is done, the drift file is automatically updated once per hour and is available to initialize the frequency on subsequent daemon restarts.

* * *

#### The huff-n'-puff Filter

In scenarios where a considerable amount of data are to be downloaded or uploaded over telephone modems, timekeeping quality can be seriously degraded. This occurs because the differential delays on the two directions of transmission can be quite large. In many cases the apparent time errors are so large as to exceed the step threshold and a step correction can occur during and after the data transfer is in progress.

The huff-n'-puff filter is designed to correct the apparent time offset in these cases. It depends on knowledge of the propagation delay when no other traffic is present. In common scenarios this occurs during other than work hours. The filter maintains a shift register that remembers the minimum delay over the most recent interval measured usually in hours. Under conditions of severe delay, the filter corrects the apparent offset using the sign of the offset and the difference between the apparent delay and minimum delay. The name of the filter reflects the negative (huff) and positive (puff) correction, which depends on the sign of the offset.

The filter is activated by the <code>tinker</code> command and <code>huffpuff</code> keyword, as described in the [Miscellaneous Options](/archives/4.2.4-series/miscopt/) page.

* * *

#### Notes

If NetInfo support is built into <code>ntpd</code>, then <code>ntpd</code> will attempt to read its configuration from the NetInfo if the default ntp.conf file cannot be read and no file is specified by the <code>-c</code> option.

In contexts where a host name is expected, a <code>-4</code> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <code>-6</code> qualifier forces DNS resolution to the IPv6 namespace.

Various internal <code>ntpd</code> variables can be displayed and configuration options altered while the <code>ntpd</code> is running using the <code>[ntpq](/archives/4.2.4-series/ntpq/)</code> and <code>[ntpdc](/archives/4.2.4-series/ntpdc/)</code> utility programs.

When <code>ntpd</code> starts it looks at the value of <code>umask</code>, and if zero <code>ntpd</code> will set the <code>umask</code> to <code>022</code>.

* * *

#### Command Line Options

<code>**-a**</code>

: Require cryptographic authentication for broadcast client, multicast client and symmetric passive associations. This is the default.

<code>**-A**</code>

: Do not require cryptographic authentication for broadcast client, multicast client and symmetric passive associations. This is almost never a good idea.

<code>**-b**</code>

: Enable the client to synchronize to broadcast servers.

<code>**-c _conffile_**</code>

: Specify the name and path of the configuration file, default <code>/etc/ntp.conf</code>.

<code>**-d**</code>

: Specify debugging mode. This option may occur more than once, with each occurrence indicating greater detail of display.

<code>**-D _level_**</code>

: Specify debugging level directly.

<code>**-f _driftfile_**</code>

: Specify the name and path of the frequency file, default <code>/etc/ntp.drift</code>. This is the same operation as the <code>driftfile _driftfile_</code> configuration command.

<code>**-g**</code>

: Normally, <code>ntpd</code> exits with a message to the system log if the offset exceeds the panic threshold, which is 1000 s by default. This option allows the time to be set to any value without restriction; however, this can happen only once. If the threshold is exceeded after that, <code>ntpd</code> will exit with a message to the system log. This option can be used with the <code>-q</code> and <code>-x</code> options. See the <code>tinker</code> command for other options.

<code>**-i _jaildir_**</code>

: Chroot the server to the directory <code>_jaildir_</code>. This option also implies that the server attempts to drop root privileges at startup (otherwise, chroot gives very little additional security), and it is only available if the OS supports to run the server without full root privileges. You may need to also specify a <code>-u</code> option.

<code>**-k _keyfile_**</code>

: Specify the name and path of the symmetric key file, default <code>/etc/ntp.keys</code>. This is the same operation as the <code>keys _keyfile_</code> configuration command.

<code>**-l _logfile_**</code>

: Specify the name and path of the log file. The default is the system log file. This is the same operation as the <code>logfile _logfile_</code> configuration command.

<code>**-L**</code>

: Do not listen to virtual IPs. The default is to listen.

<code>**-n**</code>

: Don't fork.

<code>**-N**</code>

: To the extent permitted by the operating system, run the <code>ntpd</code> at the highest priority.

<code>**-p _pidfile_**</code>

: Specify the name and path of the file used to record the <code>ntpd</code> process ID. This is the same operation as the <code>pidfile _pidfile_</code> configuration command.

<code>**-P _priority_**</code>

: To the extent permitted by the operating system, run the <code>ntpd</code> at the specified priority.

<code>**-q**</code>

: Exit the <code>ntpd</code> just after the first time the clock is set. This behavior mimics that of the <code>ntpdate</code> program, which is to be retired. The <code>-g</code> and <code>-x</code> options can be used with this option. Note: The kernel time discipline is disabled with this option.

<code>**-r _broadcastdelay_**</code>

: Specify the default propagation delay from the broadcast/multicast server to this client. This is necessary only if the delay cannot be computed automatically by the protocol.

<code>**-s _statsdir_**</code>

: Specify the directory path for files created by the statistics facility. This is the same operation as the <code>statsdir _statsdir_</code> configuration command.

<code>**-t _key_**</code>

: Add a key number to the trusted key list. This option can occur more than once.

<code>**-u _user[:group]_**</code>

: Specify a user, and optionally a group, to switch to. This option is only available if the OS supports to run the server without full root privileges. Currently, this option is supported under NetBSD (configure with <code>-\-enable-clockctl</code>) and Linux (configure with <code>-\-enable-linuxcaps</code>).

<code>**-U _interface update interval_**</code>

: Number of seconds to wait between interface list scans to pick up new and delete network interface. Set to 0 to disable dynamic interface list updating. The default is to scan every 5 minutes.

<code>**-v _variable_**</code>
:<code>**-V _variable_**</code>

: Add a system variable listed by default.

<code>**-x**</code>

: Normally, the time is slewed if the offset is less than the step threshold, which is 128 ms by default, and stepped if above the threshold. This option sets the threshold to 600 s, which is well within the accuracy window to set the clock manually. Note: Since the slew rate of typical Unix kernels is limited to 0.5 ms/s, each second of adjustment requires an amortization interval of 2000 s. Thus, an adjustment as much as 600 s will take almost 14 days to complete. This option can be used with the <code>-g</code> and <code>-q</code> options. See the <code>tinker</code> command for other options. Note: The kernel time discipline is disabled with this option.

* * *

#### The Configuration File

Ordinarily, <code>ntpd</code> reads the <code>ntp.conf</code> configuration file at startup time in order to determine the synchronization sources and operating modes. It is also possible to specify a working, although limited, configuration entirely on the command line, obviating the need for a configuration file. This may be particularly useful when the local host is to be configured as a broadcast/multicast client, with all peers being determined by listening to broadcasts at run time.

Usually, the configuration file is installed in the <code>/etc</code> directory, but could be installed elsewhere (see the <code>-c _conffile_</code> command line option). The file format is similar to other Unix configuration files - comments begin with a <code>#</code> character and extend to the end of the line; blank lines are ignored.

Configuration commands consist of an initial keyword followed by a list of arguments, some of which may be optional, separated by whitespace. Commands may not be continued over multiple lines. Arguments may be host names, host addresses written in numeric, dotted-quad form, integers, floating point numbers (when specifying times in seconds) and text strings. Optional arguments are delimited by <code>[ ]</code> in the following descriptions, while alternatives are separated by <code>|</code>. The notation <code>[ ... ]</code> means an optional, indefinite repetition of the last item before the <code>[ ... ]</code>.

* * *

#### Configuration Options

[Server Options](/archives/4.2.4-series/confopt/)  
[Authentication Options](/archives/4.2.4-series/authopt/)  
[Monitoring Options](/archives/4.2.4-series/monopt/)  
[Access Control Options](/archives/4.2.4-series/accopt/)  
[Automatic NTP Configuration Options](/archives/4.2.4-series/manyopt/)  
[Reference Clock Options](/archives/4.2.4-series/clockopt/)  
[Miscellaneous Options](/archives/4.2.4-series/miscopt/)

* * *

#### Files


| File               | Default          | Option | Command       |
| ------------------ | ---------------- | ------ | ------------- |
| configuration file | `/etc/ntp.conf`  | `-c`   | none          |
| frequency file     | `/etc/ntp.drift` | `-f`   | `driftfile`   |
| process ID file    | none             | `-p`   | `pidfile`     |
| log file           | system log       | `-l`   | `logfile`     |
| include file       | none             | none   | `includefile` |
| statistics path    | `/var/NTP`       | `-s`   | `statsdir`    |
| keys path          | `/usr/local/etc` | `-k`   | `keysdir`     |