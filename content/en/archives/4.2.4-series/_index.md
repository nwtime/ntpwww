---
title: "4.2.4-series"
type: archives
---

![gif](/archives/pic/barnstable.gif)[_P.T. Bridgeport Bear_; from _Pogo_, Walt Kelly](/reflib/pictures)

Pleased to meet you.

Last update: Thursday, July 28, 2005

* * *

#### Table of Contents

*  [Introduction](#introduction)
*  [Building and Installing NTP](#building-and-installing-ntp)
*  [Configuring Clients and Servers](#configuring-clients-and-servers)
*  [Program Manual Pages](#program-manual-pages)
*  [Supporting Documentation](#supporting-documentation)
*  [Background Information](#background-information)
*  [Application Notes](#application-notes)

* * *

#### Introduction

Note: The software contained in this distribution is available without charge under the conditions set forth in the [Copyright Notice](/archives/4.2.4-series/copyright).

The Network Time Protocol (NTP) is used to synchronize the time of a computer client or server to another server or reference time source, such as a radio or satellite receiver or modem. It provides accuracies typically within a millisecond on LANs and up to a few tens of milliseconds on WANs relative to Coordinated Universal Time (UTC) via a Global Positioning Service (GPS) receiver, for example. Typical NTP configurations utilize multiple redundant servers and diverse network paths in order to achieve high accuracy and reliability.

This software release implements NTP Version 4 (NTPv4), but is in general backwards compatible with previous versions except NTP Version 1, support for which is no longer viable. NTPv4 includes support for both symmetric key and public key cryptography to prevent accidental or malicious protocol attacks, as well as automatic server discovery using IP multicast means. This release includes full support for the IPv6 address family, where the operating system supports it, as well as the default IPv4 address family. Either or both families can be used at the same time on the same machine.

Background information on computer network time synchronization can be found on the [Executive Summary - Computer Network Time Synchronization](/reflib/exec) page. Discussion on protocol conformance issues and interoperability with previous NTP versions can be found on the [Protocol Conformance Statement](/reflib/biblio) page. Discussion on how NTP reckons the time can be found on the [NTP Timescale and Leap Seconds](/reflib/leap) page. Background information, bibliography and briefing slides suitable for presentations can be found on the [Network Time Synchronization Project](/reflib/ntp) page. Additional information can be found at the [NTP web site](http://www.ntp.org). Please send bug reports to [<bugs@mail.ntp.org>](mailto:bugs@mail.ntp.org).

* * *

#### Building and Installing NTP

NTP supports Unix and Windows (XP, NT4 and 2000) systems. The [Building and Installing the Distribution](/archives/4.2.4-series/build) page presents an overview of the procedures for compiling the distribution and installing it on a typical client or server. The build procedures inspect the system hardware and software environment and automatically select the appropriate options for that environment. While these procedures work with most computers and operating systems marketed today, exceptions requiring manual intervention do exist, as documented on the [Configuration Options](/archives/4.2.4-series/config) and [Release Notes](/archives/4.2.4-series/release) pages.

Bringing up a NTP primary server requires a radio or satellite receiver or modem. The distribution includes hardware drivers for some forty radio and satellite clocks and modem services. A list of supported drivers is given on the [Reference Clock Drivers](/archives/4.2.4-series/refclock) page. It is also possible to use an otherwise undisciplined machine as a primary or backup server, as described on the [Undisciplined Local Clock](/archives/drivers/driver1) page. For most popular workstations marketed by Sun, Silicon Graphics and Hewlett Packard, as well as widely available Unix clones such as FreeBSD and Linux, the automatic build procedures select all drivers that run on the target machine. While this increases the size of the executable binary somewhat, individual drivers can be included or excluded using the configure utility documented in the Configuration Options page.

Some programs included in this distribution use cryptographic algorithms to verify authenticity and credentials. Where local security policy permits relatively weak symmetric key cryptography, the required software is included in this distribution. However, where local policy requires stronger public key cryptography, additional software not in this distribution is required. This distribution uses the OpenSSL library available from https://www.openssl.org. This library is also used by the Secure Shell facility, so is often already installed on Unix workstations and servers. It includes support for most message digest and digital signature algorithms used in the industry, as well as X.509 certificate generation, signing and verification.

While public key cryptography is optional but highly recommended for all NTP operations, it is required for the NTPv4 Autokey protocol described on the [Autonomous Authentication](/reflib/autokey) page and is an integral component of the generic automatic configuration scheme described on the [Autonomous Configuration](/reflib/autocfg) page. In addition, access can be restricted in various ways described on the [Access Control Options](/archives/4.2.4-series/accopt) page.

* * *

#### Configuring Clients and Servers

NTP is by its very nature a complex distributed network application and can be configured and used for a great many widely divergent timekeeping scenarios. The documentation presented on these pages attempts to cover the entire suite of configuration, operation and maintenance facilities which this distribution supports. However, most applications will need only a few of these facilities. If this is the case, the [Quick Start](/archives/4.2.4-series/quick) page may be useful to get a simple workstation on the air with an existing server.

However, in order to participate in the existing NTP synchronization subnet and obtain accurate, reliable time, it is usually necessary to construct an appropriate configuration file, commonly called <tt>ntp.conf</tt>, which establishes the servers and/or external receivers or modems to be used by this particular machine. Directions for constructing this file are in the [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/4.2.4-series/notes) page. However, in many common cases involving simple network topologies and workstations, the configuration data can be specified entirely on the command line for the [<tt>ntpd</tt> - Network Time Protocol (NTP) daemon](/archives/4.2.4-series/ntpd).

The most important factor in providing accurate, reliable time is the selection of modes and servers to be used in the configuration file. A discussion on the available modes is on the [Association Management](/archives/4.2.4-series/assoc) page. NTP support for one or more computers is normally engineered as part of the existing public NTP synchronization subnet. The public subnet consists of a multiply redundant hierarchy of servers and clients, with each level in the hierarchy identified by stratum number. Primary servers operate at stratum one and provide synchronization to secondary servers operating at stratum two and so on to higher strata. In this hierarchy, clients are simply servers that have no dependents.

Configuring a corporate or campus NTP subnet can be an engineering challenge. NTP contains many features designed to survive system and network failures, software bugs, clock errors and hacker attacks. Surviving these hazards requires intricate design of the timekeeping network using good principles of server redundancy and path diversity. The Manycast mode, new to NTPv4, is designed to track the current server and network states and adjust the client/server configuration for the best available accuracy and reliability. More information on the Manycast mode is on the [Authentication Options](/archives/4.2.4-series/authopt) and [Automatic NTP Configuration Options](/archives/4.2.4-series/manyopt) pages.

The NTP subnet in early 2003 includes well over a hundred public primary (stratum 1) servers synchronized directly to UTC by radio, satellite or modem and located in every continent of the globe, including Antarctica. Normally, client workstations and servers with a relatively small number of clients do not synchronize to primary servers. There are well over a hundred public secondary (stratum 2) servers synchronized to the primary servers and providing synchronization to a total well over 100,000 clients and servers in the Internet. The current lists are maintained on the [Public NTP Time Server Lists ](http://support.ntp.org/bin/view/Servers/WebHome) page, which is updated frequently. There are thousands upon thousands of private primary and secondary servers not normally available to the public, many hiding behind firewalls. Clients are strongly discouraged against using these servers, since they sometimes hide in little ghettos behind dinky links to the outside world and unwanted traffic can bring up expensive ISDN lines, causing much grief and frustration. There are defensive means described on the Access Control Options page, including the Kiss-of-Death packet.

* * *

#### Resolving Problems

Like other things Internet, the NTP synchronization subnets tend to be large and devilishly intricate, with many opportunities for misconfiguration and network problems. The NTP engineering model is specifically designed to help isolate and repair such problems using an integrated management protocol, together with a suite of monitoring and debugging tools. There is an optional statistics data recording facility which can be used to record normal and aberrant operation, log problems to the system log facility, and retain records of client access. The [NTP Debugging Techniques](/archives/4.2.4-series/debug) and [Hints and Kinks](/archives/4.2.4-series/hints) pages contain useful information for identifying problems and devising solutions. In extreme cases, problems can be detected through the use of the [<tt>ntpdsim</tt> - Network Time Protocol (NTP) simulator](/archives/4.2.4-series/ntpdsim) included in this software distribution.

Users are requested to report bugs, offer suggestions and contribute additions to this distribution. The [Patching Procedures](/archives/4.2.4-series/patches) page suggests procedures which greatly simplify distribution updates, while the [Porting Hints](/archives/4.2.4-series/porting) page suggest ways to make porting this code to new hardware and operating systems easier. Additional information on reference clock driver construction and debugging can be found in the [Debugging Hints for Reference Clock Drivers](/archives/4.2.4-series/rdebug) page.

* * *

#### Program Manual Pages

*   [<tt>ntpd</tt> - Network Time Protocol (NTP) daemon](/archives/4.2.4-series/ntpd)
*   [<tt>ntpq</tt> - standard NTP query program](/archives/4.2.4-series/ntpq)
*   [<tt>ntpdc</tt> - special NTP query program](/archives/4.2.4-series/ntpdc)
*   [<tt>ntpdate</tt> - set the date and time via NTP](/archives/4.2.4-series/ntpdate)
*   [<tt>ntptrace</tt> - trace a chain of NTP servers back to the primary source](/archives/4.2.4-series/ntptrace)
*   [<tt>tickadj</tt> - set time-related kernel variables](/archives/4.2.4-series/tickadj)
*   [<tt>ntptime</tt> - read kernel time variables](/archives/4.2.4-series/ntptime)
*   [<tt>ntp-keygen</tt> - generate public and private keys](/archives/4.2.4-series/keygen)
*   [<tt>ntpdsim</tt> - Network Time Protocol (NTP) simulator](/archives/4.2.4-series/ntpdsim)

* * *

#### Supporting Documentation

*   [Copyright Notice](/archives/4.2.4-series/copyright)
*   [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/4.2.4-series/notes)
*   [NTP Version 4 Release Notes](/archives/4.2.4-series/release)
*   [Building and Installing the Distribution](/archives/4.2.4-series/build)
*   [Configuration Options](/archives/4.2.4-series/config)
*   [Reference Clock Drivers](/archives/4.2.4-series/refclock)
*   [NTP Debugging Techniques](/archives/4.2.4-series/debug)
*   [Debugging Reference Clock Drivers](/archives/4.2.4-series/rdebug)
*   [<tt>ntpd</tt> System Log Messages](/archives/4.2.4-series/msyslog)
*   [Patching Procedures](/archives/4.2.4-series/patches)
*   [Hints and Kinks](/archives/4.2.4-series/hints)
*   [Porting Hints](/archives/4.2.4-series/porting)

* * *

#### Background Information

*   [NTP Project and Reference Library](/reflib/ntp)
*   [Executive Summary - Computer Network Time Synchronization](/reflib/exec)
*   [The Network Time Protocol Timescale and Era Numbering](/reflib/y2k)
*   [NTP Timescale and Leap Seconds](/reflib/leap)
*   [Protocol Conformance Statement](/reflib/biblio)

* * *

#### Application Notes

*   [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.4-series/prefer)
*   [Association Management](/archives/4.2.4-series/assoc)
*   [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.4-series/pps)
*   [Time and Time Interval Measurement with Application to Computer and Network Performance Evaluation](/archives/4.2.4-series/measure)
*   [Kernel Model for Precision Timekeeping](/archives/4.2.4-series/kern)

* * *

![gif](/archives/pic/pogo1a.gif)