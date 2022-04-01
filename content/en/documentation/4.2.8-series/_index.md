---
title: "4.2.8-series"
type: archives
---

* * *

![gif](/archives/pic/barnstable.gif)[_P.T. Bridgeport Bear_; from _Pogo_, Walt Kelly](/reflib/pictures/)

Pleased to meet you.

Last update: 31-Mar-2014 05:41

A list of all links is on the [Site Map](/archives/4.2.8-series/sitemap/) page.

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.8-series/#introduction)
*   [The Handbook](/archives/4.2.8-series/#the-handbook)
*   [Building and Installing NTP](/archives/4.2.8-series/#building-and-installing-ntp)
*   [Resolving Problems](/archives/4.2.8-series/#resolving-problems)
*   [Further Information](/archives/4.2.8-series/#further-information)

* * *

#### Introduction

> Note: The NTP Version 4 software contained in this distribution is available without charge under the conditions set forth in the [Copyright Notice](/archives/4.2.8-series/copyright/).

It is very important that readers understand that the NTP document collection began 25 years ago and remains today a work in progress. It has evolved as new features were invented and old features retired. It has been widely copied, cached and morphed to other formats, including man pages, with varying loss of fidelity. However, these HTML pages are the ONLY authoritative and definitive reference. Readers should always use the collection that comes with the distribution they use. A copy of the online collection is normally included in the most recent snapshot, but might not agree with an earlier snapshot or release version.

This distribution is an implementation of [RFC-5905 "Network Time Protocol Version 4: Protocol and Algorithms Specification"](/reflib/rfc/rfc5905.txt).

NTP is widely used to synchronize a computer to Internet time servers or other sources, such as a radio or satellite receiver or telephone modem service. It can also be used as a server for dependent clients. It provides accuracies typically less than a millisecond on LANs and up to a few milliseconds on WANs. Typical NTP configurations utilize multiple redundant servers and diverse network paths in order to achieve high accuracy and reliability.

This distribution includes a simulation framework in which substantially all the runtime NTP operations and most features can be tested and evaluated. This has been very useful in exploring in vitro response to unusual circumstances or over time periods impractical in vivo. Details are on the [Network Time Protocol (NTP) Simulator](/archives/4.2.8-series/ntpdsim/) page.

* * *

#### The Handbook

A good deal of tutorial and directive information is available on the handbook pages. These should be read in conjunction with the command and option information available on the pages listed on the sitemap page.

* [NTP Version 4 Release Notes](/archives/4.2.8-series/release/): Lists recent changes and new features in the current distribution.

* [Association Management](/archives/4.2.8-series/assoc/): Describes how to configure servers and peers and manage the various options. Includes automatic server discovery schemes.

* [Automatic Server Discovery Schemes](/archives/4.2.8-series/discover/): Describes automatic server discovery using broadcast, multicast, manycast and server pool scheme.

* [Access Control Support](/archives/4.2.8-series/access/): Describes the access control mechanisms that can be used to limit client access to various time and management functions.

* [Authentication Support](/archives/4.2.8-series/authentic/): Describes the authentication mechanisms for symmetric-key and public-key cryptography.

* [Rate Management](/archives/4.2.8-series/rate/): Describes the principles of rate management to minimize network load and defend against DoS attacks.

* [Reference Clock Support](/archives/4.2.8-series/refclock/): Describes the collection of radio clocks used to synchronize primary servers.

* [How NTP Works](/archives/4.2.8-series/warp/): Gives an overview of the NTP daemon architecture and how it works.

* * *

#### Building and Installing NTP

NTP supports Unix, VMS and Windows (2000 and later) systems. The [Building and Installing the Distribution](/archives/4.2.8-series/build/) page details the procedures for building and installing on a typical system. This distribution includes drivers for many radio and satellite receivers and telephone modem services in the US, Canada and Europe. A list of supported drivers is on the [Reference Clock Drivers](/archives/4.2.8-series/refclock/) page. The default build includes the debugging options and all drivers that run on the target machine; however, options and drivers can be included or excluded using options on the [Configuration Options](/archives/4.2.8-series/config/) page.

* * *

#### Resolving Problems

Like other things in modern Internet life, NTP problems can be devilishly intricate. This distribution includes a number of utilities designed to identify and repair problems using an integrated management protocol supported by the [<code>ntpq</code>](/archives/4.2.8-series/ntpq/) utility program.

The [NTP Debugging Techniques](/archives/4.2.8-series/debug/) and [Hints and Kinks](/archives/4.2.8-series/hints/) pages contain useful information for identifying problems and devising solutions. Additional information on reference clock driver construction and debugging is in the [Debugging Hints for Reference Clock Drivers](/archives/4.2.8-series/rdebug/) page.

Users are invited to report bugs and offer suggestions via the [NTP Bug Reporting Procedures](/archives/4.2.8-series/bugs/) page.

* * *

#### Further Information

The [Site Map](/archives/4.2.8-series/sitemap/) page contains a list of document collections arranged by topic. The Program Manual Pages collection may be the best place to start. The [Command Index](/archives/4.2.8-series/comdex/) collection contains a list of all configuration file commands together with a short function description. A great wealth of additional information is available in the [Reference Library](/reflib/), including a book and numerous background papers and briefing presentations.

Background information on computer network time synchronization is on the [Executive Summary - Computer Network Time Synchronization](/reflib/exec/) page. Discussion on new features and interoperability with previous NTP versions is on the [NTP Version 4 Release Notes](/archives/4.2.8-series/release/) page. Background information, bibliography and briefing slides suitable for presentations are on the [Network Time Synchronization Research Project](/reflib/ntp/) page.

* * *

![gif](/archives/pic/pogo1a.gif)