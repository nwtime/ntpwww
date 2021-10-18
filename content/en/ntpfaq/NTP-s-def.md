---
title: "What is NTP?"
type: "archives"
--- 

#### 4.1. Overview

This section tries to introduce and explain the most basic features of NTP, the>Network Time Protocol. The discussion here will be limited to the more theroretical aspects of NTP, while the next section ([Section 5](NTP-s-algo.htm)) will go further towards real life.

4.1.1. [What is NTP?](#what-is-ntp)  
4.1.2. [What is SNTP?](#what-is-sntp)  
4.1.3. [Why should Time be synchronized?](#why-should-time-be-synchronized)  
4.1.4. [What are the basic features of NTP?](#what-are-the-basic-features-of-ntp)  
4.1.5. [Which Operating Systems are supported?](#which-operating-systems-are-supported)  
4.1.6. [How many NTP servers are available in the Internet?](#how-many-ntp-servers-are-available-in-the-internet)  
4.1.7. [Which version of NTP should I use?](#which-version-of-ntp-should-i-use)  
4.1.8. [What's the difference between xntp and ntp?](whats-the-difference-between-xntp-and-ntp)  
4.1.9. [What's new in Version 4?](#whats-new-in-version-4)  
4.1.10. [Where is NTP specified?](#where-is-ntp-specified)

* * *

#### 4.1.1 What is NTP?

NTP stands for Network Time Protocol, and it is an Internet protocol used to synchronize the clocks of computers to some time reference. NTP is an Internet standard protocol originally developed by [Professor David L. Mills](NTP-a-faq.htm#AU-DLM) at the University of Delaware.

* * *

#### 4.1.2. What is SNTP?

SNTP (Simple Network Time Protocol) is basically also NTP, but lacks some internal algorithms that are not needed for all types of servers. See [Q: 9.4.](NTP-s-related.htm#Q-RELATED-MORE-INFO) for more and detailed information.

As a full implementation of the NTP protocol seemed too complicated for many systems, a simplified version of the protocol, namely SNTP had been defined.

* * *

#### 4.1.3. Why should Time be synchronized?

Time usually just advances. If you have communicating programs running on different computers, time still should even advance if you switch from one computer to another. Obviously if one system is ahead of the others, the others are behind that particular one. From the perspective of an external observer, switching between these systems would cause time to jump forward and back, a non-desirable effect.

As a consequence, isolated networks may run their own wrong time, but as soon as you connect to the Internet, effects will be visible. Just imagine some EMail message arrived five minutes before it was sent, and there even was a reply two minutes before the message was sent.

Even on a single computer some applications have trouble when the time jumps backwards. For example, database systems using transactions and crash recovery like to know the time of the last good state.[<span class="footnote">[1]</span>](NTP-s-def.htm#FTN.AEN1291)

Therefore, air traffic control was one of the first applications for NTP.

* * *

#### 4.1.4. What are the basic features of NTP?

There exist several protocols to synchronize computer clocks, each having distinguished features. Here is a list of NTP's features:

* NTP needs some _reference clock_ that defines the _true time_ to operate. All clocks are set towards that true time. (It will not just make all systems agree on _some_ time, but will make them agree upon the true time as defined by some standard.)

  NTP uses UTC as reference time (See also [What is UTC?](NTP-s-time.htm#Q-UTC)).

* NTP is a fault-tolerant protocol that will automatically select the best of several available time sources to synchronize to. Multiple candidates can be combined to minimize the accumulated error. Temporarily or permanently insane time sources will be detected and avoided.

* NTP is highly scalable: A synchronization network may consist of several reference clocks. Each node of such a network can exchange time information either bidirectional or unidirectional. Propagating time from one node to another forms a hierarchical graph with reference clocks at the top.

* Having available several time sources, NTP can select the best candidates to build its estimate of the current time. The protocol is highly accurate, using a resolution of less than a nanosecond (about 2<sup>^</sup>-32 seconds). (The popular protocol used by `rdate` and defined in RFC 868 only uses a resolution of one second).

* Even when a network connection is temporarily unavailable, NTP can use measurements from the past to estimate current time and error.

* For formal reasons NTP will also maintain estimates for the accuracy of the local time.

* * *

#### 4.1.5. Which Operating Systems are supported?

The implementation described in [Which Implementations are available for  UNIX?](NTP-s-def-impl.htm#Q-NTP-IMPL-UNIX) works for most popular UNIX operating systems. Among those are: AIX, FreeBSD, HP-UX, Irix, Linux, NetBSD, SCO UNIX, OpenBSD, OSF/1, Solaris, System V.4.

According to a message in news://comp.protocols.time.ntp there's also a supported implementation for VMS: "UCX (the VMS TCP stack) has a full implementation of NTP built-in. As of v5 it's pretty much vanilla NTP, prior to that the command syntax and control file formats were proprietary. Check the manuals." See [Q: 4.3.4.1.](NTP-s-def-impl.htm#Q-NTP-IMPL-VMS) for more details.

In addition there are efforts to make it run on Windows/NT (see [Q: 8.3.11.2.3.](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-WINNT-IMPL-NTP)). Currently there are problems with time resolution, reference clock drivers, authentication and name resolution.

For more detailed information see [Section 4.3](NTP-s-def-impl.htm).

* * *

#### 4.1.6. How many NTP servers are available in the Internet?

According to _A Survey of the NTP Network_[<span class="footnote">[2]</span>](NTP-s-def.htm#FTN.FTN-NTP-SURVEY99) there were at least 175,000 hosts running NTP in the Internet. Among these there were over 300 valid _stratum-1_ servers. In addition there were over 20,000 servers at stratum 2, and over 80,000 servers at stratum 3.

* * *

#### 4.1.7. Which version of NTP should I use?

Unfortunately the answer to this question is not quite easy: Currently there are version three and version four implementations of NTP available. The latest software release being worked on is NTPv4, but the official Internet standard is still NTPv3. In addition, some vendors of operating systems customize and deliver their own versions. If you rely on support, you should also consider that.

If you are worried with compatibility issues, older version clients can generally talk to newer version servers automagically (as newer servers know how to answer the queries, hopefully), but the other direction requires manual interference (See `html/confopt.htm` about the `version` keyword).

NTPv4 introduces some new features that you may find desirable (See [Q: 4.1.9.](/ntpfaq/ntp-s-def#419-Q-DEF-OV-V4NEWS)). For example, if you use dial-up connections, version four can increase its polling interval above one day if the clock is stable enough. In addition the new algorithms can deal with high delay variations a bit better than the LAN-oriented version three. On the other hand, NTPv4 uses floating point operations where NTPv3 used integer arithmetic. This should not be a problem for current hardware, but might be an issue for older systems without a floating point unit.

There is also a security issue with all versions probably older than 4.0.99k23 that may allow denial of service or even unauthorized system access. Still vendors supplying older versions may have fixed their particular version.

See also [Section 6.4](NTP-s-compat.htm)

* * *

#### 4.1.8. What's the difference between xntp and ntp?

Obviously the difference is an `x`, and its meaning some years ago was (according to [Professor David L. Mills](NTP-a-faq.htm#AU-DLM)):

Dennis Fergusson intended the `x` as "experimental". I got maybe twenty messages over the years suggesting the `x` was not appropriate for code in use over a decade and I dropped it for NTPv4. See the paper on [NTP history](http://www.eecis.udel.edu/~mills/papers.htm).

In practice `xntp` refers to an implementation of version three or older while `ntp` refers to implementation of version four (or later).

* * *

#### 4.1.9. What's new in Version 4?

According to the [NTP Version 4 Release Notes](/archives/4.2.8-series/release), the new features of version four (as compared to version three) are:

* Use of floating-point arithmetic instead of fixed-point arithmetic.
* Redesigned clock discipline algorithm that improves accuracy, handling of network jitter, and polling intervals.
* Support for the nanokernel kernel implementation that provides nanosecond precision as well as improved algorithms.
* Public-Key cryptography known as autokey that avoids having common secret keys.
* Automatic server discovery (manycast mode).
* Fast synchronization at startup and after network failures (burst mode).
* New and revised drivers for reference clocks.
* Support for new platforms and operating systems.

* * *

#### 4.1.10. Where is NTP specified?

The official specification of NTP version 3 is [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf). Specifically, there is no specification for version 4 yet. Despite of some arguments to update the specification, there won't be one in the near future.

There was a recent discussion on the subject. [Hans P. Reiser](NTP-a-faq.htm#AU-HPR) wrote:

Several slides and papers on NTP illustrate the NTP Interval Intersection Algorithm with an example of 4 peers, `A` to `D`, showing two confidence intervals labeled "Correct DTS" and "Correct NTP". (Also shown in [Appendix of RFC 1305](/reflib/rfc/rfc1305/rfc1305c.pdf)), Fig. 16). While it is easy to understand the DTS case, I have some problems matching the shown NTP interval with the specified algorithms.

According to the algorithm as specified, e.g., in RFC 1305:
 
*   `f=0` (no falsetickers) will fail, so `f=1`
*   scan for low endpoint will yield left end of interval `C` (condition `i>=3` holds), by that time `c=1` (incremented at midpoint of `D`)
*   scan for high endpoint starts with `c=1, f=1, i=0` condition `i>=3` holds as soon as the right end of interval `B` is reached, by that time `c=2` (incremented at midpoint of `C`)
*   Now, `c>f`, so no success yet. Increment `f` to value 2

Some documents now say "declare failure if `f>=m/2`", which is the case now. Even if you make another pass with `f=2`, you will get an interval from left end of `A` to right end of `A`, thus again different from what is shown in RFC's Fig 16.

Do I get something really wrong here (and I really tried hard to locate any flaw in my argument), or is there really a error in the RFC example and all other places which use this example?

The answer written by [Professor David L. Mills](NTP-a-faq.htm#AU-DLM) reads:

(...) What's more, you exposed a significant error in both the documentation and the implementation.

See slide 15 from the [architecture and protocol briefing](). The statements preceeding the algorithm are correct; that is the intent of its design according to the set of formal correctness assertions worked out with the computer science theory community. Unfortunately, in my haste to bottle the algorithm in quick and easy gulps, something got lost in the description. The actual algorithm is constructed differently, but accomplishes the same thing. Pseudo code for the correctness model is in rfc1305 but (sigh) there is a leetle buggie in that description.
 
Just to be honest I rechecked the actual NTPv4 code and found a nasty surprise. The code is broken and does not exactly implement the formal model. Under some conditions it allows a falseticker to masquerade as a truechimer. Not to panic; the masquerade is subtle and will not result in significant error. However, I don't know how this happened; the core code is 14 years old, may have been noodled (but not by me) and hasn't been carefully reviewed since.

I repaired the code as per rfc1305 and bugfix and verified it does what the formal model intended. The repair is in the development version here and should be in the repository when other known bugs are fixed. Meanwhile, I fixed the description in the briefing.
 
The clock selection algorithm is at the very heart of the NTP design. While a formal description of its operation is now in the briefing, an informal description may be of interest to folks in this group. I know there are many skeptics who complain when the algorithm does something they don't like, rather than what the correctness assertions require.
 
If a candidate presented to the algorithm is reliably synchronized to UTC, its time offset value seen from afar cannot exceed an error bound equal to plus-minus half the roundtrip propagation delay to that candidate plus a little wiggle due to statistical variations (jitter). Once the offset value has been determined, the error bound increases at a fixed rate due to the maximum credible frequency error of the clock oscillator. The error bound, called the root synchronization distance, is continuously calculated by ntpd. The correctness interval is defined as twice this bound with midpoint equal to the offset value.
 
Now consider a number of correctness intervals aligned along the time axis at their respective offset values. Obviously, those points where the intervals all overlap form a clique representing the correct UTC time. If some interval does not overlap the others, there must be more than one clique, but only one clique can contain the correct time. If there is a clique containing more than half the number of intervals, its members must all be truechimers and the other cliques must contain only falsetickers. If there is no clique containing more than half the intervals, a correct time cannot be determined and the Byzantines lose the war.

Consider the common case of two intervals that do not overlap due to a systematic error. According to principle, one of the two must not be synchronized to UTC, but there is no way for the selection algorithm to know which one. So, by the above, a correct time cannot be determined. In prinicple, you could choose one based on other characteristics, like the size of the interval, but this would seriously complicate the algorithm and probably cause the theory community to disown me.

While the corrected code is strict to principle, it may be too strict for some who don't care that much about correctness principles. There may be a need for a tinker switch with appropriate warning disclaimers.

* * *

### Notes

[1]</span>](NTP-s-def.htm#AEN1291)</td>

Even if a database like Oracle uses integer numbers for transaction sequencing internally, users may want to perform time-based recovery. There's a document numbered 1013279.6 from Oracle that discusses the issue.

[2]</span>](NTP-s-def.htm#FTN-NTP-SURVEY99)</td>

_A Survey of the NTP Network_ by [Nelson Minar](NTP-a-faq.htm#AU-NM) is available via http://www.media.mit.edu/~nelson/research/ntp-survey99/.