---
title: "3-5.93e"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*  [Introduction](/documentation/3-5.93e/#introduction)
*  [Building and Installing NTP](/documentation/3-5.93e/#building-and-installing-ntp)
*  [Configuring Clients and Servers](/documentation/3-5.93e/#configuring-clients-and-servers)
*  [Resolving Problems](/documentation/3-5.93e/#resolving-problems)
*  [Program Manual Pages](/documentation/3-5.93e/#program-manual-pages)
*  [Supporting Documentation](/documentation/3-5.93e/#supporting-documentation)
*  [Application Notes](/documentation/3-5.93e/#application-notes)

* * *

#### Introduction

Note: The software contained in this distribution is available without charge under the conditions set forth in the [Copyright Notice](/documentation/3-5.93e/copyright/).

The Network Time Protocol (NTP) is used to synchronize the time of a computer client or server to another server or reference time source, such as a radio or satellite receiver or modem. It provides client accuracies typically within a millisecond on LANs and up to a few tens of milliseconds on WANs relative to a primary server synchronized to Coordinated Universal Time (UTC) via a Global Positioning Service (GPS) receiver, for example. Typical NTP configurations utilize multiple redundant servers and diverse network paths, in order to achieve high accuracy and reliability. Some configurations include cryptographic authentication to prevent accidental or malicious protocol attacks. Information on the NTP architecture, protocol and algorithms can be found in the [Further Information and Bibliography](/documentation/3-5.93e/biblio/) page.

* * *

#### Building and Installing NTP

The [Building and Installing the Distribution](/documentation/3-5.93e/build/) page presents an overview of the procedures for compiling the distribution and installing it on a typical client or server. The build procedures inspect the system hardware and software environment and automatically select the appropriate options for that environment. While these procedures work with most computers and operating systems marketed today, exceptions requiring manual intervention do exist, as documented in the [Configuration Options](/documentation/3-5.93e/config/) and [Release Notes](/documentation/3-5.93e/release/) pages.

Bringing up a NTP primary server requires a radio or satellite receiver or modem. The distribution includes hardware drivers for over two dozen radio clocks and modem services. A list of the particular receivers and modem drivers supported in the distribution is given in the [Reference Clock Drivers](/documentation/3-5.93e/refclock/) page. For most popular workstations marketed by DEC, Sun and Hewlett Packard, the automatic build procedures select all drivers that run on the target machine. While this increases the size of the executable binary somewhat, individual drivers can be included or excluded using special scripts.

* * *

#### Configuring Clients and Servers

In order to participate in the existing NTP synchronization subnet and obtain accurate, reliable time, it is necessary to construct an appropriate configuration file, usually called <code>ntp.conf</code>, which establishes the servers and/or external receivers or modems to be used by this particular machine. Directions for constructing this file are in the [Notes on Configuring NTP and Setting up a NTP Subnet](/documentation/3-5.93e/notes/) page.

The most important factor in providing accurate, reliable time is the selection of modes and servers to be used in the configuration file. NTP support for one or more computers is normally engineered as part of the existing NTP synchronization subnet. The existing NTP subnet consists of a multiply redundant hierarchy of servers and clients, with each level in the hierarchy identified by stratum number. Primary servers operate at stratum one and provide synchronization to secondary servers operating at stratum two and so on to higher strata. In this hierarchy, clients are simply servers that have no dependents.

The NTP subnet presently includes over 50 public primary servers synchronized directly to UTC by radio, satellite or modem and located in North America, Europe and Asia. Normally, client workstations and servers with a relatively small number of clients do not synchronize to primary servers. There are about 100 public secondary servers synchronized to the primary servers and providing synchronization to a total in excess of 100,000 clients and servers in the Internet. The current lists are maintained in the [List of Public NTP Servers](https://support.ntp.org/Servers) page, which is updated frequently. There are numerous private primary and secondary servers not normally available to the public as well.

* * *

#### Resolving Problems

Like other things Internet, the NTP synchronization subnets tend to be large and devilishly intricate, with many opportunities for misconfiguration and network problems. The NTP engineering model is specifically designed to help isolate and repair such problems using an integrated management protocol, together with a suite of monitoring and debugging tools. There is an optional data recording facility which can be used to record normal and aberrant operation, log problems to the system log facility, and retain records of client access. The [NTP Debugging Techniques](/documentation/3-5.93e/debug/) and [Hints and Kinks](/documentation/3-5.93e/hints/) pages contain useful information for identifying problems and devising solutions.

Users are requested to report bugs, offer suggestions and contribute additions to this distribution. The [Patching Procedures](/documentation/3-5.93e/patches/) page suggests procedures which greatly simplify distribution updates, while the [Porting Hints](/documentation/3-5.93e/porting/) suggest ways to make porting this code to new hardware and operating systems easier. Additional information on reference clock driver construction and debugging can be found in the [Reference Clock Drivers](/documentation/3-5.93e/refclock/) page.

* * *

#### Program Manual Pages

* [<code>xntpd</code> - Network Time Protocol (NTP) daemon](/documentation/3-5.93e/xntpd/)  
* [<code>ntpq</code> - standard NTP query program](/documentation/3-5.93e/ntpq/)  
* [<code>xntpdc</code> - special NTP query program](/documentation/3-5.93e/xntpdc/)  
* [<code>ntpdate</code> - set the date and time via NTP](/documentation/3-5.93e/ntpdate/)  
* [<code>ntptrace</code> - trace a chain of NTP servers back to the primary source](/documentation/3-5.93e/ntptrace/)  
* [<code>tickadj</code> - set time-related kernel variables](/documentation/3-5.93e/tickadj/)  
* [<code>ntptime</code> - read kernel time variables](/documentation/3-5.93e/ntptime/)  
* [<code>authspeed</code> - determine authentication delays](/documentation/3-5.93e/authspeed/)  
* [<code>authcert</code> - DES validation program](/documentation/3-5.93e/authcert/)  
* [<code>md5</code> - generate message digest](/documentation/3-5.93e/md5cert/)

* * *

#### Supporting Documentation

* [Copyright Notice](/documentation/3-5.93e/copyright/)  
* [Notes on Configuring NTP and Setting up a NTP Subnet](/documentation/3-5.93e/notes/)  
* [Release Notes](/documentation/3-5.93e/release/)  
* [Building and Installing the Distribution](/documentation/3-5.93e/build/)  
* [Configuration Options](/documentation/3-5.93e/config/)  
* [NTP Debugging Techniques](/documentation/3-5.93e/debug/)  
* [Reference Clock Drivers](/documentation/3-5.93e/refclock/)  
* [Further Information and Bibliography](/documentation/3-5.93e/biblio/)  
* [Patching Procedures](/documentation/3-5.93e/patches/)  
* [Hints and Kinks](/documentation/3-5.93e/hints/)  
* [Porting Hints](/documentation/3-5.93e/porting/)

* * *

#### Application Notes

* [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/3-5.93e/prefer/)  
* [Gadget Box PPS Level Converter and CHU Modem](/documentation/3-5.93e/gadget/)  
* [IRIG Support Using Sun SPARC Audio](/documentation/3-5.93e/irig/)  
* [Time and Time Interval Measurement with Application to Computer and Network Performance Evaluation](/documentation/3-5.93e/measure/)  
* [A Kernel Model for Precision Timekeeping](/documentation/3-5.93e/kern/)  
* [A Kernel Programming Interface for Precision Time Signals](/documentation/3-5.93e/kernpps/)