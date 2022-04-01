---
title: "4.1.2"
type: archives
noindex: true
---

![gif](/documentation/pic/barnstable.gif)[_P.T. Bridgeport Bear_; from _Pogo_, Walt Kelly](/reflib/pictures/)

Pleased to meet you.  

* * *

#### Table of Contents

*  [Introduction](#introduction)
*  [Building and Installing NTP](#building-and-installing-ntp)
*  [Configuring Clients and Servers](#configuring-clients-and-servers)
*  [Resolving Problems](#resolving-problems)
*  [Program Manual Pages](#program-manual-pages)
*  [Supporting Documentation](#supporting-documentation)
*  [Application Notes](#application-notes)

* * *

#### Introduction

Note: The software contained in this distribution is available without charge under the conditions set forth in the [Copyright Notice](/documentation/4.1.2/copyright/).

The Network Time Protocol (NTP) is used to synchronize the time of a computer client or server to another server or reference time source, such as a radio or satellite receiver or modem. It provides accuracies typically within a millisecond on LANs and up to a few tens of milliseconds on WANs relative to Coordinated Universal Time (UTC) via a Global Positioning Service (GPS) receiver, for example. Typical NTP configurations utilize multiple redundant servers and diverse network paths in order to achieve high accuracy and reliability. Some configurations include cryptographic authentication to prevent accidental or malicious protocol attacks and some provide automatic server discovery using IP multicast.

Background information on computer network time synchronization can be found on the [Executive Summary - Computer Network Time Synchronization](/documentation/4.1.2/exec/) page. Discussion on protocol conformance issues and interoperability with previous NTP versions can be found in the [Protocol Conformance Statement](/documentation/4.1.2/biblio/) page. Discussion on how NTP reckons the time can be found in the [NTP Timescale and Leap Seconds](/documentation/4.1.2/leap/) page. Background information, bibliography and briefing slides can be found in the [Reference Library](/reflib/).

* * *

#### Building and Installing NTP

NTP supports Unix and Windows (NT4 and 2000) systems. The [Building and Installing the Distribution](/documentation/4.1.2/build/) page presents an overview of the procedures for compiling the distribution and installing it on a typical client or server. The build procedures inspect the system hardware and software environment and automatically select the appropriate options for that environment. While these procedures work with most computers and operating systems marketed today, exceptions requiring manual intervention do exist, as documented in the [Configuration Options](/documentation/4.1.2/config/) and [Release Notes](/documentation/4.1.2/release/) pages. Note that support for strong cryptography requires cryptographic libraries not included in this distribution.

Bringing up a NTP primary server requires a radio or satellite receiver or modem. It is also possible to configure a machine on an isolated network with the local clock driver and have other machines synchronize to it. The distribution includes hardware drivers for the local clock and over three dozen radio clocks and modem services. A list of supported drivers is given in the [Reference Clock Drivers](/documentation/4.1.2/refclock/) page. For most popular workstations marketed by Digital/Compaq, Sun and Hewlett Packard, as well as widely available Unix clones such as FreeBSD and Linux, the automatic build procedures select all drivers that run on the target machine. While this increases the size of the executable binary somewhat, individual drivers can be included or excluded using the configure utility documented in the Configuration Options page.

* * *

#### Configuring Clients and Servers

NTP is by its very nature a complex distributed network application and can be configured and used for a great many widely divergent timekeeping scenarios. The documentation presented on these pages attempts to cover the entire suite of configuration, operation and maintenance facilities which this distribution supports. However, most applications will need only a few of these facilities. If this is the case, the [Quick Start](/documentation/4.1.2/quick/) page may be useful to get a simple workstation on the air with an existing server.

However, in order to participate in the existing NTP synchronization subnet and obtain accurate, reliable time, it is usually necessary to construct an appropriate configuration file, commonly called <code>ntp.conf</code>, which establishes the servers and/or external receivers or modems to be used by this particular machine. Directions for constructing this file are in the [Notes on Configuring NTP and Setting up a NTP Subnet](/documentation/4.1.2/notes/) page. However, in many common cases involving simple network topologies and workstations, the configuration data can be specified entirely on the command line for the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/documentation/4.1.2/ntpd/).

The most important factor in providing accurate, reliable time is the selection of modes and servers to be used in the configuration file. A discussion on the available modes is on the [Association Management](/documentation/4.1.2/assoc/) page. NTP support for one or more computers is normally engineered as part of the existing NTP synchronization subnet. The existing NTP subnet consists of a multiply redundant hierarchy of servers and clients, with each level in the hierarchy identified by stratum number. Primary servers operate at stratum one and provide synchronization to secondary servers operating at stratum two and so on to higher strata. In this hierarchy, clients are simply servers that have no dependents.

The NTP subnet in late 2000 includes over a hundred public primary (stratum 1) servers synchronized directly to UTC by radio, satellite or modem and located in every continent of the globe, including Antarctica. Normally, client workstations and servers with a relatively small number of clients do not synchronize to primary servers. There are over a hundred public secondary (stratum 2) servers synchronized to the primary servers and providing synchronization to a total in excess of 100,000 clients and servers in the Internet. The current lists are maintained in the [Public NTP Time Server Lists](https://support.ntp.org/bin/view/Servers/WebHome) page, which is updated frequently. There are numerous private primary and secondary servers not normally available to the public as well. You are strongly discouraged from using these servers, since they sometimes hide in little ghettos behind dinky links to the outside world and your traffic can bring up expensive ISDN lines, causing much grief and frustration.

* * *

#### Resolving Problems

Like other things Internet, the NTP synchronization subnets tend to be large and devilishly intricate, with many opportunities for misconfiguration and network problems. The NTP engineering model is specifically designed to help isolate and repair such problems using an integrated management protocol, together with a suite of monitoring and debugging tools. There is an optional data recording facility which can be used to record normal and aberrant operation, log problems to the system log facility, and retain records of client access. The [NTP Debugging Techniques](/documentation/4.1.2/debug/) and [Hints and Kinks](/documentation/4.1.2/hints/) pages contain useful information for identifying problems and devising solutions.

Users are requested to report bugs, offer suggestions and contribute additions to this distribution. The [Patching Procedures](/documentation/4.1.2/patches/) page suggests procedures which greatly simplify distribution updates, while the [Porting Hints](/documentation/4.1.2/porting/) page suggest ways to make porting this code to new hardware and operating systems easier. Additional information on reference clock driver construction and debugging can be found in the [Reference Clock Drivers](/documentation/4.1.2/refclock/) page.

* * *

#### Program Manual Pages

*   [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/documentation/4.1.2/ntpd/)
*   [<code>ntpq</code> - standard NTP query program](/documentation/4.1.2/ntpq/)
*   [<code>ntpdc</code> - special NTP query program](/documentation/4.1.2/ntpdc/)
*   [<code>ntpdate</code> - set the date and time via NTP](/documentation/4.1.2/ntpdate/)
*   [<code>ntptrace</code> - trace a chain of NTP servers back to the primary source](/documentation/4.1.2/ntptrace/)
*   [<code>tickadj</code> - set time-related kernel variables](/documentation/4.1.2/tickadj/)
*   [<code>ntptime</code> - read kernel time variables](/documentation/4.1.2/ntptime/)
*   [<code>ntp-genkeys</code> - generate public and private keys](/documentation/4.1.2/genkeys/)

* * *

#### Supporting Documentation

*   [NTP Project and Reference Library](/reflib/ntp/)
*   [Copyright Notice](/documentation/4.1.2/copyright/)
*   [Executive Summary - Computer Network Time Synchronization](/documentation/4.1.2/exec/)
*   [Protocol Conformance Statement](/documentation/4.1.2/biblio/)
*   [NTP Timescale and Leap Seconds](/documentation/4.1.2/leap/)
*   [Notes on Configuring NTP and Setting up a NTP Subnet](/documentation/4.1.2/notes/)
*   [NTP Version 4 Release Notes](/documentation/4.1.2/release/)
*   [Building and Installing the Distribution](/documentation/4.1.2/build/)
*   [Configuration Options](/documentation/4.1.2/config/)
*   [NTP Debugging Techniques](/documentation/4.1.2/debug/)
*   [Reference Clock Drivers](/documentation/4.1.2/refclock/)
*   [Patching Procedures](/documentation/4.1.2/patches/)
*   [Hints and Kinks](/documentation/4.1.2/hints/)
*   [Porting Hints](/documentation/4.1.2/porting/)

* * *

#### Application Notes

*   [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.1.2/prefer/)
*   [Association Management](/documentation/4.1.2/assoc/)
*   [Pulse-per-second (PPS) Signal Interfacing](/documentation/4.1.2/pps/)
*   [Gadget Box PPS Level Converter and CHU Modem](/documentation/4.1.2/gadget/)
*   [Time and Time Interval Measurement with Application to Computer and Network Performance Evaluation](/documentation/4.1.2/measure/)
*   [Kernel Model for Precision Timekeeping](/documentation/4.1.2/kern/)
*   [Kernel Programming Interface for Precision Time Signals](/documentation/4.1.2/kernpps/)

* * *

![gif](/documentation/pic/pogo1a.gif)