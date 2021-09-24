---
title: "NTP Version 4 Release Notes"
type: archives
---

![gif](/archives/pic/hornraba.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

The rabbit toots to make sure you read this.

Last update: 3-Oct-2011 21:51 UTC

#### Table of Contents

*   [New Features](/archives/4.2.8-series/release/#new-features)
*   [Changes and Upgrades Since the NTPv3 Version (xntp3-5)](/archives/4.2.8-series/release/#changes-and-upgrades-since-the-ntpv3-version-xntp3-5)
*   [Nasty Surprises](/archives/4.2.8-series/release/#nasty-surprises)

* * *

NTP has been under development for almost 30 years, but the paint ain't dry even now. This release of the NTP Version 4 (NTPv4) distribution for Unix, VMS and Windows incorporates new features and refinements, but retaining backwards compatibility with older versions, including NTPv3 and NTPv2, but not NTPv1. Support for NTPv1 has been discontinued because of certain security vulnerabilities.

* * *

#### New Features

*   The behavior of the daemon at startup has been considerably improved. The time to measure the frequency and correct an initial offset error when started for the first time is now no more than ten minutes. Upon restart, it takes no more than five minutes to reduce the initial offset to less than one millisecond without adversely affecting the frequency. This avoids a subsequent frequency correction which could take up to several hours.
*   A new feature called interleaved mode can be used in NTP symmetric and broadcast modes. It is designed to improve accuracy by minimizing errors due to queuing and transmission delays. It is described on the [NTP Interleaved Modes](/archives/4.2.8-series/xleave) page.
*   The huff-n'-puff filter is designed to avoid large errors with DSL circuits and highly asymmetrical traffic, as when downloading large files. Details are on the [The Huff-n'-Puff Filter](/archives/4.2.8-series/huffpuff) page.
*   A new feature called orphan mode provides an automatic, subnet-wide synchronization feature with multiple sources. It provides reliable backup in isolated networks or in pr when Internet sources have become unavailable. See the [Orphan Mode](/archives/4.2.8-series/orphan) page for further information.
*   This release includes comprehensive packet rate management tools to help reduce the level of spurious network traffic and protect the busiest servers from overload. There is support for the optional Kiss-o'-Death (KoD) packet intended to slow down an abusive client. See the [Rate Management and the Kiss-o'-Death Packet](/archives/4.2.8-series/rate) page for further information.
*   There are two new burst mode features available where special conditions apply. One of these is enabled by the <code>iburst</code> keyword in the <code>server</code> configuration command. It is intended for cases where it is important to set the clock quickly when an association is first mobilized. The other is enabled by the <code>burst</code> keyword in the <code>server</code> configuration command. It is intended for cases where the network attachment requires an initial calling or training procedure. See the [Association Management](/archives/4.2.8-series/assoc) page for further information.
*   The OpenSSL cryptographic library has replaced the library formerly available from RSA Laboratories. All cryptographic routines except a version of the MD5 message digest algorithm have been removed from the base distribution. All 128-bit and 160-bit message digests algorithms are now supported for both symmetric key and public key cryptosystems. See the [Authentication Support](/archives/4.2.8-series/authentic) page for further information and the [Authentication Options](/archives/4.2.8-series/authopt) page for a list of supported digest algorithms.
*   This release includes support for Autokey public-key cryptography for authenticating public servers to clients, as described in [RFC 5906](/reflib/rfc/rfc5906.txt). This support requires the <code>-\-enable-autokey</code> option when building the distribution, which is the default if OpenSSL is available. The deployment of Autokey subnets is now considerably simpler than in earlier versions. A subnet naming scheme is now available to filter manycast and pool configurations. Additional information about Autokey is on the [Autokey Public Key Authentication](/archives/4.2.8-series/autokey) page and links from there.
*   The NTP discrete event simulator has been substantially upgraded, now including scenarios with multiple servers and time-sensitive scripts. This allows the NTP algorithms to be tested in an embedded environment with systematic and pseudo-random network delay and oscillator wander distributions. This has been used to verify correct operation under conditions of extreme error and misconfiguration. See the [<code>ntpdsim</code> - Network Time Protocol (NTP) simulator](/archives/4.2.8-series/ntpdsim) page. A technical description and performance analysis is given in the [white paper](/reflib/ntpsim).
*   NTPv4 includes three new server discovery schemes, which in most applications can avoid per-host configuration altogether. Two of these are based on IP multicast technology, while the remaining one is based on crafted DNS lookups. See the [Automatic NTP Configuration Schemes](/archives/4.2.8-series/discover) page for further information.
*   The status display and event report monitoring functions have been considerably expanded, including new statistics files and event reporting to files and the system log. See the [Event Messages and Status Words](/archives/4.2.8-series/decode) page for further information.
*   Several new options have been added for the <code>ntpd</code> command line. For the inveterate knob twiddlers several of the more important performance variables can be changed to fit actual or perceived special conditions. In particular, the <code>tinker</code> and <code>tos</code> commands can be used to adjust thresholds, throw switches and change limits.
*   The <code>ntpd</code> daemon can be operated in a one-time mode similar to <code>ntpdate</code>, which program is headed for retirement. See the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/archives/4.2.8-series/ntpd) page for the new features.
*   A number of white papers have been added to the [Reference Library](/reflib/papers).

* * *

#### Changes and Upgrades Since the NTPv3 Version (xntp3-5)

This section summarizes general changes since the publication of [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf). Specific changes made during the code upgrade of 2007-2008 are summarized in [Historical Notes](/archives/4.2.8-series/history).

*   If the [Basic Socket Interface Extensions for IPv6 (RFC 2553)](https://datatracker.ietf.org/doc/html/rfc2553) is detected, support for the IPv6 address family is supported in addition to the default support for the IPv4 address family. In contexts where a host name is expected, a <code>-4</code> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <code>-6</code> qualifier forces DNS resolution to the IPv6 namespace.
*   Many changes have been made in the NTP algorithms to improve performance and reliability. A clock state machine has been incorporated to improve behavior under transient conditions. The clock discipline algorithm has been redesigned to improve accuracy, reduce the impact of network disruptions and allow increased poll intervals to 36 hours with only moderate sacrifice in accuracy. The clock select, cluster and combine algorithms have been overhauled as the result of a thorough statistical analysis.
*   In all except a very few cases, all timing intervals are randomized, so that the tendency for NTPv3 to self-synchronize and bunch messages, especially with a large number of configured associations, is minimized.
*   Support for the precision time kernel modifications, which are now in stock FreeBSD and optional in Linux kernels, is included. With this support the system clock can be disciplined to the order of one nanosecond. The older microtime kernel modifications in Digital/Compaq/HP Tru64, Digital Ultrix and Sun Microsystems SunOS and Solaris, continue to be supported. In either case the support eliminates sawtooth error, which can be in the hundreds of microseconds. Further information is on the [Kernel Model for Precision Timekeeping](/archives/4.2.8-series/kern) page.
*   New reference clock drivers have been added for several GPS receivers now on the market for a total of 44 drivers. The reference clock driver interface is smaller, more rational, more flexible and more accurate. Most of the drivers in NTPv3 have been converted to the NTPv4 interface and continue to operate as before. A summary of the supported drivers is on the [Reference Clock Support](/archives/4.2.8-series/refclock) page. Audio drivers for the Canadian standard time and frequency station CHU, the US standard time and frequency stations WWV/H and for IRIG signals have been updated and capabilities added to allow direct connection of these signals to an audio port. See the [Reference Clock Audio Drivers](/archives/4.2.8-series/audio) page for further information.
*   Support for pulse-per-second (PPS) signals has been extended to all drivers as an intrinsic function. Further information is on the [Pulse-Per-Second (PPS) Signal Interfacing](/archives/4.2.8-series/pps) page. Typical performance with the PPS interface and a fast machine are in the low microseconds.
*   Several small changes have been made to make administration and maintenance more convenience. The entire distribution has been converted to gnu <code>automake</code>, which greatly eases the task of porting to new and different programming environments, as well as reduces the incidence of bugs due to improper handling of idiosyncratic kernel functions. Version control is provided by Bitkeeper using an online repository at https://bk.ntp.org/. Trouble ticket reporting is provided using Bugzilla. If <code>ntpd</code> is configured with NetInfo support, it will attempt to read its configuration from the NetInfo service if the default <code>ntp.conf</code> file cannot be read and no file is specified by the <code>-c</code> option. When <code>ntpd</code> starts it looks at the value of <code>umask</code>, and if zero <code>ntpd</code> will set the <code>umask</code> to <code>022</code>.

* * *

#### Nasty Surprises

There are a few things different about this release that have changed since the latest NTP Version 3 release. Following are a few things to worry about:

*   Some configuration commands have been removed, others added and some changed in minor ways. See the collection of Commands and Options on the [Command Index](/archives/4.2.8-series/comdex) page.
*   When both IPv4 and IPv6 address families are in use, the host's resolver library may not choose the intended address family if a server has an IPv4 and IPv6 address associated with the same DNS name. The solution is to use the IPv4 or IPv6 address directly in such cases or use another DNS name that resolves to the intended address family. Older versions of <code>ntpdc</code> will show only the IPv4 associations with the <code>peers</code> and some other commands. Older versions of <code>ntpq</code> will show <code>0.0.0.0</code> for IPv6 associations with the <code>peers</code> and some other commands.
*   There is a minor change to the reference ID field of the NTP packet header when operating with IPv6 associations. In IPv4 associations this field contains the 32-bit IPv4 address of the server, in order to detect and avoid loops. In IPv6 associations this field contains the first 32-bits of a MD5 hash formed from the IPv6 address. All programs in the distribution have been modified to work with both address families.
*   The <code>tty_clk</code> and <code>ppsclock</code> pulse-per-second (PPS) line discipline/streams modules are no longer supported. The PPS function is now handled by the [PPS Clock Discipline](/archives/drivers/driver22) driver, which uses the new PPSAPI application program interface adopted by the IETF. Note that the <code>pps</code> configuration file command has been obsoleted by the driver. See the [Pulse-Per-Second (PPS) Signal Interfacing](/archives/4.2.8-series/pps) page for further information.
*   Support for the NTPv1 symmetric mode has been discontinued, since it hasn't worked for years. Support continues for the NTPv1 client mode, which is used by some SNTP clients.
*   The <code>authstuff</code> directory, intended as a development and testing aid for porting cryptographic routines to exotic architectures, has been removed. Testing and conformance validation tools are available in the OpenSSL software distribution.