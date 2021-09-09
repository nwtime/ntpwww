---
title: "NTP Version 4 Release Notes"
type: archives
---

![gif](/archives/pic/hornraba.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

The rabbit toots to make sure you read this.

Last update: 16:10 UTC Sunday, March 02, 2008

* * *

#### Table of Contents

*   [New Features](/archives/4.2.6-series/release/#new-features)
*   [Nasty Surprises](/archives/4.2.6-series/release/#nasty-surprises)

* * *

This release of the NTP Version 4 (NTPv4) daemon for Unix, VMS and Windows incorporates new features and refinements to the NTP Version 3 (NTPv3) algorithms. However, it continues the tradition of retaining backwards compatibility with older versions, including NTPv3 and NTPv2, but not NTPv1. Support for NTPv1 has been discontinued because of certain security vulnerabilities. The NTPv4 version has been under development for 25 years and the paint still isn't dry.

The code compiles and runs properly in all test host configurations available to the developer corps, including Sun Microsystems, Digital/Compaq/Hewlett Packard, FreeBSD and Linux. Other volunteers have verified it works in IRIX and Windows NT and XP. We invite comments and corrections about the various architectures, operating systems and hardware complement that can't be verified by the developer corps. Of particular interest are other Windows versions, VMS and various reference clock drivers.

This release has been compiled and tested on many systems, including SunOS 4.1.3, Solaris 2.5.1-2.10, Alpha Tru64 4.0-5.1, Ultrix 4.4, Linux 2.4.2, FreeBSD 4.5-6.2 and HP-UX 10.02. It has been compiled and tested by others on Windows NT4, 2000 and XP, but not yet on other Windows versions or for VMS. There are several new features apparently incompatible with Linux systems, including some modes used with the Autokey protocol. The developer corps looks for help elsewhere to resolve these differences.

This note summarizes the differences between this software release of NTPv4, called ntp-4.x.x, and the previous NTPv3 version, called xntp3-5.x.x.

* * *

#### New Features

1.  Support for the IPv6 addressing family is included in this distribution. If the Basic Socket Interface Extensions for IPv6 (RFC-2553) is detected, support for the IPv6 address family is generated in addition to the default support for the IPv4 address family.
2.  Most calculations are now done using 64-bit floating double format, rather than 64-bit fixed point format. The motivation for this is to reduce size, improve speed and avoid messy bounds checking.
3.  The clock discipline algorithm has been redesigned to improve accuracy, reduce the impact of network jitter and allow increased in poll intervals to 36 hours with only moderate sacrifice in accuracy.
4.  A new feature called "huffpuff" maximizes accuracy in cases of highly asymmetric network delays typical of ISDN and telephone modems.
5.  The clock selection algorithm has been redesigned to reduce "clockhopping" when the choice of servers changes frequently as the result of comparatively insignificant quality changes.
6.  This release includes support for the [nanokernel](/reflib/software/nanokernel.tar.gz) precision time kernel modifications, which are now in stock FreeBSD and optional in Linux kernels. With this support the system clock can be disciplined to the order of one nanosecon. The older microtime kernel modifications in Digital/Compaq/HP Tru64, Digital Ultrix and Sun Microsystems SunOS and Solaris, continue to be supported. In either case the support eliminates sawtooth error, which can be in the hundreds of microseconds.
7.  This release includes support for Autokey public-key cryptography, which is the preferred scheme for authenticating servers to clients. Additional information about Autokey cryptography is on the [Authentication Options](/archives/4.2.6-series/authopt) page and links from there. See also the new <code>cryptostats</code> monitoring statistics file in the [Monitoring Options](/archives/4.2.6-series/monopt) page.
8.  The OpenSSL cryptographic library has replaced the library formerly available from RSA Laboratories. All cryptographic routines except a version of the MD5 message digest routine have been removed from the base distribution.
9.  As the result of the above, the <code>authstuff</code> directory, intended as a development and testing aid for porting cryptographic routines to exotic architectures, has been removed. Testing and conformance validation tools are in the OpenSSL software distrbution.
10.  This release includes support for a discrete event simulator (DES), which allows the NTP algorithms to be tested in an embedded environment with systematic and pseudorandom network delay and oscillator wander distributions. This has been used to verify correct operation under conditions of extreme error and misconfiguration. See the [<code>ntpdsim</code> - Network Time Protocol (NTP) simulator](/archives/4.2.6-series/ntpdsim) page.
11.  NTPv4 includes three new server discovery schemes, which in most applications can avoid per-host configuration altogether. Two of these are based on IP multicast technology, while the remaining one is based on crafted DNS lookups. See the [Automatic NTP Configuration Schemes](/archives/4.2.6-series/manyopt) page for further information.
12.  This release includes comprehensive packet rate management tools to help reduce the level of spurious network traffic and protect the busiest servers from overload. See the [Rate Management and the Kiss-o'-Death Packet](/archives/4.2.6-series/rate) page for further information.
13.  This release includes support for the orphan mode, which replaces the local clock driver for most configurations. Orphan mode provides an automatic, subnet-wide synchronization feature with multiple sources. It can be used in isolated networks or in Internet subnets where the servers or Internet connection have failed. See the [Automatic NTP Configuration Options](/archives/4.2.6-series/manyopt) page for further information.
14.  There are two new burst mode features available where special conditions apply. One of these is enabled by the <code>iburst</code> keyword in the <code>server</code> configuration command. It is intended for cases where it is important to set the clock quickly when an association is first mobilized. The other is enabled by the <code>burst</code> keyword in the <code>server</code> configuration command. It is intended for cases where the network attachment requires an initial calling or training procedure. See the [Association Management](/archives/4.2.6-series/assoc) page for further information.
15.  The reference clock driver interface is smaller, more rational and more accurate.
16.  Support for pulse-per-second (PPS) signals has been extended to all drivers as an intrinsic function. Most of the drivers in NTPv3 have been converted to the NTPv4 interface and continue to operate as before. New drivers have been added for several GPS receivers now on the market for a total of 44 drivers. Audio drivers for the Canadian standard time and frequency station CHU, the US standard time and frequency stations WWV/H and for IRIG signals have been updated and capabilities added to allow direct connection of these signals to an audio port. See the [Reference Clock Audio Drivers](/archives/4.2.6-series/audio) page for further information.
17.  In all except a very few cases, all timing intervals are randomized, so that the tendency for NTPv3 to self-synchronize and bunch messages, especially with a large number of configured associations, is minimized.
18.  In NTPv3 a large number of weeds and useless code had grown over the years since the original NTP code was implemented 25 years ago. Using a powerful weedwacker, much of the shrubbery has been removed, with effect a substantial reduction in size of almost 40 percent.
19.  The entire distribution has been converted to gnu <code>automake</code>, which should greatly ease the task of porting to new and different programming environments, as well as reduce the incidence of bugs due to improper handling of idiosyncratic kernel functions. Version control is provided by Bitkeeper using an online repository at www.ntp.org. Trouble ticket reporting is provided using Bugzilla.
20.  Several new options have been added for the <code>ntpd</code> command line. For the inveterate knob twiddlers several of the more important performance variables can be changed to fit actual or perceived special conditions. In particular, the <code>tos</code> and <code>tos</code> commands can be used to adjust thresholds, throw switches and change limits.
21.  The <code>ntpd</code> daemon can be operated in a one-time mode similar to <code>ntpdate</code>, which program is headed for retirement. See the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/archives/4.2.6-series/ntpd) page for the new features.

* * *

#### Nasty Surprises

There are a few things different about this release that have changed since the latest NTP Version 3 release. Following are a few things to worry about:

1.  Some configuration commands have been removed, others added and some changed in minor ways. See the Commands and Options collection on the [Site Map](/archives/4.2.6-series/sitemap) page.
2.  When both IPv4 and IPv6 address families are in use, the host's resolver library may not choose the intended address family if a server has an IPv4 and IPv6 address associated with the same DNS name. The solution is to use the IPv4 or IPv6 address directly in such cases or use another DNS name that resolves to the intended address family. Older versions of <code>ntpdc</code> will show only the IPv4 associations with the <code>peers</code> and some other commands. Older versions of <code>ntpq</code> will show 0.0.0.0 for IPv6 associations with the <code>peers</code> and some other commands.
3.  There is a minor change to the reference ID field of the NTP packet header when operating with IPv6 associations. In IPv4 associations this field contains the 32-bit IPv4 address of the server, in order to detect and avoid loops. In IPv6 associations this field contains the first 32-bits of a MD5 hash formed from the IPv6 address. All programs in the distribution have been modified to work with both address families.
4.  The <code>tty_clk</code> and <code>ppsclock</code> pulse-per-second (PPS) line discipline/streams modules are no longer supported. The PPS function is now handled by the [PPS Clock Discipline](/archives/drivers/driver22) driver, which uses the new PPSAPI application program interface adopted by the IETF. Note that the <code>pps</code> configuration file command has been obsoleted by the driver. See the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.6-series/pps) page for further information.
5.  Support for the NTPv1 symmetric mode has been discontinued, since it hasn't worked for years. Support continues for the NTPv1 client mode, which is used by some SNTP clients.