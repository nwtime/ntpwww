---
title: "4.2.6-series"
type: archives
---

* * *

![gif](/archives/pic/barnstable.gif)[_P.T. Bridgeport Bear_; from _Pogo_, Walt Kelly](/reflib/pictures)

Pleased to meet you.

Last update: 	07-Nov-2009 20:43 UTC

A list of all links is on the [Site Map](/archives/4.2.6-series/sitemap) page.

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.6-series/#introduction)
*   [Building and Installing NTP](/archives/4.2.6-series/#building-and-installing-ntp)
*   [Configuring Clients and Servers](/archives/4.2.6-series/#configuring-clients-and-servers)
*   [Features and Options](/archives/4.2.6-series/#features-and-options)
*   [Resolving Problems](/archives/4.2.6-series/#resolving-problems)
*   [Further Information](/archives/4.2.6-series/#further-information)

* * *

#### Introduction

> Note: The NTP Version 4 software contained in this distribution is available without charge under the conditions set forth in the [Copyright Notice](/archives/4.2.6-series/copyright).

It is very important that readers understand that the NTP document collection began 25 years ago and remains today a work in progress. It has evolved as new features were invented and old features retired. It has been widely copied, cached and morphed to other formats, including man pages, with varying loss of fidelity. However, these HTML pages are the ONLY authoritative and definitive reference. Readers should always use the collection that comes with the distribution they use. A copy of the online collection is normally included in the most recent snapshot, but might not agree with an earlier snapshot or release version.

This distribution is an implementation of RFC-5905 "Network Time Protocol Version 4: Protocol and Algorithms Specification".  

The Network Time Protocol (NTP) is widely used to synchronize a computer to Internet time servers or other sources, such as a radio or satellite receiver or telephone modem service. It can also be used as a server for dependent clients. It provides accuracies typically less than a millisecond on LANs and up to a few milliseconds on WANs. Typical NTP configurations utilize multiple redundant servers and diverse network paths in order to achieve high accuracy and reliability. Authentication is provided using symmetric key cryptography and the MD5 message digest algorithm included in the distribution. If the OpenSSL cryptographic library is installed, the SHA or SHA1 message digest algorithms can be used. If the OpenSSL library is installed, additional options based on public key cryptography are available.

NTP time synchronization services are widely available in the public Internet. The public NTP subnet in early 2008 includes several thousand servers in most countries and on every continent of the globe, including Antarctica. These servers support a total population estimated at over 25 million computers in the global Internet. The NTP subnet operates with a hierarchy of levels, where each level is assigned a number called the stratum. Stratum 1 (primary) servers at the lowest level are directly synchronized to national time services. Stratum 2 (secondary) servers at the next higher level are synchronize to stratum 1 servers and so on. Normally, NTP clients and servers with a relatively small number of clients do not synchronize to public primary servers. There are several hundred public secondary servers operating at higher strata and are the preferred choice. 

Background information on computer network time synchronization is on the [Executive Summary - Computer Network Time Synchronization](/reflib/exec) page. Discussion on new features and interoperability with previous NTP versions is on the [NTP Version 4 Release Notes](/archives/4.2.6-series/release) page. Background information, bibliography and briefing slides are in the [Reference Library](/reflib).

* * *

#### Building and Installing NTP

NTP supports Unix, VMS and Windows (Vista, XP, NT4 and 2000) systems. The [Building and Installing the Distribution](/archives/4.2.6-series/build) page details the procedures for building and installing on a typical system. This distribution includes drivers for 44 radio and satellite receivers and telephone modem services in the US, Canada and Europe. A list of supported drivers is on the [Reference Clock Drivers](/archives/4.2.6-series/refclock) page. The default build includes the debugging options and all drivers that run on the target machine; however, options and drivers can be included or excluded using options on the [Configuration Options](/archives/4.2.6-series/config) page.

* * *

#### Configuring Clients and Servers

NTP is by its very nature a complex distributed network application and can be configured for widely divergent timekeeping scenarios. The documentation on these pages attempts to cover the entire suite of configuration, operation and maintenance features which this distribution supports. However, most applications will need only a few of these features. The [Quick Start](/archives/4.2.6-series/) page may be useful to get a simple workstation on the air with existing servers.

The most important factor in providing accurate, reliable time is the selection of modes and servers in the configuration file. A discussion on the available modes is on the [Association Management](/archives/4.2.6-series/assoc) page. The current public server list is maintained [here](https://support.ntp.org/bin/view/Servers/WebHome). In many cases the configuration can be automated using the schemes described on the [Automatic Server Discovery Schemes](/archives/4.2.6-series/manyopt) page.

* * *

#### Features and Options

This distribution includes a statistics data recording facility which can record performance statistics and events of various types for retrospective analysis. These include time and frequency statistics, significant events and usage statistics described on the [Monitoring Options](/archives/4.2.6-series/monopt) page.

Some programs included in this distribution use cryptographic algorithms to verify server authenticity. Where local security policy permits relatively weak symmetric key cryptography, the required software is included in this distribution. Where local policy requires stronger public key cryptography, the OpenSSL library available from https://www.openssl.org is required. This library is also used by the Secure Shell facility, so is often already installed. Additional details are on the [Authentication Options](/archives/4.2.6-series/authopt) page.

This distribution includes features that can restrict access in various ways as described on the [Access Control Options](/archives/4.2.6-series/accopt) page. This can be used to deny service if not authenticated, deny service requiring persistent resources or deny service altogether.

This distribution includes a simulation framework in which substantially all the runtime NTP operations and most features can be tested and evaluated. This has been very useful in exploring in vitro response to unusual circumstances or over time periods impractical in vivo. Details are on the [Network Time Protocol (NTP) Simulator](/archives/4.2.6-series/ntpdsim) page.

* * *

#### Resolving Problems

Like other things in modern Internet life, NTP problems can be devilishly intricate. This distribution includes a number of utilities designed to identify and repair problems using an integrated management protocol supported by the [ntpq](/archives/4.2.6-series/ntpq) utility program. In addition, the [ntpdc](/archives/4.2.6-series/ntpdc) utility program can be useful in some cases.

The [NTP Debugging Techniques](/archives/4.2.6-series/debug) and [Hints and Kinks](/archives/4.2.6-series/hints) pages contain useful information for identifying problems and devising solutions. Additional information on reference clock driver construction and debugging is in the [Debugging Hints for Reference Clock Drivers](/archives/4.2.6-series/rdebug) page.

Users are invited to report bugs and offer suggestions via the [NTP Bug Reporting Procedures](/archives/4.2.6-series/bugs) page.

* * *

#### Further Information

The [Site Map](/archives/4.2.6-series/sitemap) page contains a list of document collections arranged by topic. The Program Manual Pages collection may be the best place to start, followed by the Configuration Commands and Options collection. The [Command Index](/archives/4.2.6-series/comdex) collection contains a list of all configuration file commands together with a short function description. A great wealth of additional information is available via the External Links collection, including a book and numerous background papers and briefing presentations.

* * *

![gif](/archives/pic/pogo1a.gif)