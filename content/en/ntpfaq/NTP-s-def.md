---
title: "4. What is NTP?"
description: "This section of the NTP FAQ introduces and explains the basic features of NTP, the Network Time Protocol. The discussion is limited to the more theroretical aspects of NTP."
type: "archives"
--- 

#### 4.1. Overview

This section tries to introduce and explain the most basic features of NTP, the Network Time Protocol. The discussion here will be limited to the more theroretical aspects of NTP, while the [next section](/ntpfaq/ntp-s-algo/) will go further towards real life.

4.1.1 [What is NTP?](#411-what-is-ntp)  
4.1.2 [What is SNTP?](#412-what-is-sntp)  
4.1.3 [Why should Time be synchronized?](#413-why-should-time-be-synchronized)  
4.1.4 [What are the basic features of NTP?](#414-what-are-the-basic-features-of-ntp)  
4.1.5 [Which Operating Systems are supported?](#415-which-operating-systems-are-supported)  
4.1.6 [How many NTP servers are available in the Internet?](#416-how-many-ntp-servers-are-available-in-the-internet)  
4.1.7 [Which version of NTP should I use?](#417-which-version-of-ntp-should-i-use)  
4.1.8 [What's the difference between xntp and ntp?](#418-whats-the-difference-between-xntp-and-ntp)   

* * *

#### 4.1.1 What is NTP?

NTP stands for Network Time Protocol, and it is an Internet protocol used to synchronize the clocks of computers to some time reference. NTP is an Internet standard protocol originally developed by [Professor David L. Mills](mailto:mills@udel.edu) at the University of Delaware.

* * *

#### 4.1.2 What is SNTP?

SNTP (Simple Network Time Protocol) is basically also NTP, but lacks some internal algorithms that are not needed for all types of servers. As a full implementation of the NTP protocol seemed too complicated for many systems, a simplified version of the protocol, namely SNTP had been defined.

* * *

#### 4.1.3 Why should Time be synchronized?

Time usually just advances. If you have communicating programs running on different computers, time will still advance if you switch from one computer to another. Obviously if one system is ahead of the others, the others are behind that particular one. From the perspective of an external observer, switching between these systems would cause time to jump forward and back, a non-desirable effect.

As a consequence, isolated networks may run their own wrong time, but as soon as you connect to the Internet, effects will be visible. Imagine an email message arriving five minutes before it was sent, with a reply dated two minutes before the message was sent.

Even on a single computer some applications have trouble when the time jumps backwards. For example, database systems using transactions and crash recovery like to know the time of the last good state. Even if a database like Oracle uses integer numbers for transaction sequencing internally, users may want to perform time-based recovery.

Therefore, air traffic control was one of the first applications for NTP.

* * *

#### 4.1.4 What are the basic features of NTP?

There exist several protocols to synchronize computer clocks, each having distinguished features. Here is a list of NTP's features:

* NTP needs some _reference clock_ that defines the _true time_ to operate. All clocks are set towards that true time. It will not just make all systems agree on _some_ time, but will make them agree upon the true time as defined by some standard.
NTP uses [UTC](/ntpfaq/ntp-s-time/#22-what-is-utc) as reference time.

* NTP is a fault-tolerant protocol that will automatically select the best of several available time sources to synchronize to. Multiple candidates can be combined to minimize the accumulated error. Temporarily or permanently unreliable time sources will be detected and avoided.

* NTP is highly scalable. A synchronization network may consist of several reference clocks. Each node of such a network can exchange time information either bidirectional or unidirectional. Propagating time from one node to another forms a hierarchical graph with reference clocks at the top.

* Having available several time sources, NTP can select the best candidates to build its estimate of the current time. The protocol is highly accurate, using a resolution of less than a nanosecond (about 2<sup>^</sup>-32 seconds). In contrast, the protocol used by `rdate` and defined in [RFC 868](https://www.rfc-editor.org/rfc/rfc868.html) only uses a resolution of one second.

* Even when a network connection is temporarily unavailable, NTP can use measurements from the past to estimate current time and error.
* For formal reasons NTP will also maintain estimates for the accuracy of the local time.

* * *

#### 4.1.5 Which Operating Systems are supported?

The implementation described in [4.3.2 UNIX Systems](/ntpfaq/ntp-s-def-impl/#432-unix-systems) works for most popular UNIX operating systems, including AIX, FreeBSD, HP-UX, Linux, NetBSD, OpenBSD, and Solaris.

Meinberg provides a [GUI installer](https://www.meinbergglobal.com/english/sw/ntp.htm#ntp_stable) for Window XP and later.

For more detailed information see [Section 4.3](/ntpfaq/ntp-s-def-impl/).

* * *

#### 4.1.6 How many NTP servers are available in the Internet?

According to [A Survey of the NTP Network](/reflib/reports/ntp-survey99-minar.pdf)(1999) there were at least 175,000 hosts running NTP in the Internet. Among these there were over 300 valid _stratum-1_ servers. In addition there were over 20,000 servers at stratum 2, and over 80,000 servers at stratum 3.

* * *

#### 4.1.7 Which version of NTP should I use?

[RFC 5905 Network Time Protocol Version 4: Protocol and Algorithms Specification](/reflib/rfc/rfc5905.txt) is the current standard, obsoleting [RFC 1305 Network Time Protocol (Version 3) Specification, Implementation and Analysis](/reflib/rfc/rfc1305/rfc1305b.pdf).

It is recommended to run the latest [series](/documentation/4.2.8-series/) and patch level (currently 4.2.8p15) to ensure the system has the latest features and security fixes.

If you are worried about compatibility issues, older client versions can generally talk to newer version servers automagically as newer servers know how to answer older client queries, but the other direction requires manual configuration using [the `version` keyword](/documentation/4.2.8-series/confopt/#server-command-options).

See also [Section 6.4 Compatibility](/ntpfaq/ntp-s-compat/).

* * *

#### 4.1.8 What's the difference between xntp and ntp?

Obviously the difference is an `x`, and its meaning some years ago was (according to [Professor David L. Mills](mailto:mills@udel.edu)):

Dennis Fergusson intended the `x` as "experimental". I got maybe twenty messages over the years suggesting the `x` was not appropriate for code in use over a decade and I dropped it for NTPv4. See the paper on [NTP history](/reflib/memos/hist.txt).

In practice `xntp` refers to an implementation of version three or older while `ntp` refers to implementations of version four or later.