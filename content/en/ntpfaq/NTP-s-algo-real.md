---
title: "5.3. NTP in real Life"
description: "This section of the NTP FAQ discusses how well theory applies to real life situations."
type: "archives"
---

This section discusses how well the theory applies to real life situations.

5.3.1 [What if I write my own SNTP Server?](#531-what-if-i-write-my-own-sntp-server)  
5.3.2 [Why should I have more than one clock?](#532-why-should-i-have-more-than-one-clock)  
5.3.3 [Does the reference time depend on all configured servers, or is it based on which ever responds first?](#533-does-the-reference-time-depend-on-all-configured-servers-or-is-it-based-on-which-ever-responds-first)  
5.3.4 [What happens during a Leap Second?](#534-what-happens-during-a-leap-second)

* * *

#### 5.3.1 What if I write my own SNTP Server?

There is a quote (with partial omissions) on that subject by [Professor David L. Mills](https://www.nwtime.org/tribute-to-david-l-mills/):

(...) The SNTP specification forbids operation as a server unless a primary server connected to a reference clock. (...)

Running SNTP as a server is probably the single most serious hazard in the universe. You might not agree with the particular engineering design in my clock mitigation and discipline algorithms and security model but it is absolutely imperative that the correctness assertions be religiously observed. Even so, folks have come to expect a certain level of performance from the "standard" distribution which the algorithms are designed to achieve. These algorithms have purposely been omitted from the SNTP specification on the understanding that a SNTP server will always have a reference source and a SNTP client will never function as a server to dependent clients.

I've had a lotta years thinking about these models. There should be only two models. One, represented by SNTP, is intended for casual PCs and workstations where simplicity and ubiquity is intended. It has similar functionality as `date` and `rdate` and is totally stateless. The other, represented by NTP, is a widely understood, thoroughly researched and verified engineering design. The design should include a definitive specification and be rigidly implemented to spec so folks have a high level of confidence it does what the spec requires. I want only one such spec, not a plurality of specs and implementations that are not completely interoperable. The NTP subnet is not a community of distinct servers, but a intimately intertwined real-time coupled oscillators. Get one of these things wrong and large portions of the subnet could become unstable. Heck it happens once in a while, notwithstanding the recent bug.

Okay, tune for minimum flame. We are obviously not to that degree of rigor now. There are very, very many places where a definitive spec would contain options - should the huff-'n-puff filter be required? What I have been working on the last few years is to push the envelope to test as many different ideas as feasible and then decide as a group which should be in the core spec and which should be optional.

You may suggest there is nothing wrong with a SNTP subnet of clients and servers which is wholly contained and where synchronization is never leaked to the NTP subnet. I have no problem with this should it be practical. Past experience with undisciplined local clocks leaking to the NTP subnet suggests this will happen with SNTP servers. I don't think it is a good idea to provide a SNTP capability that casually invites newbie folks to disregard the spec. If we really do want to provide such a capability, there should be a serious disclaimer published in conspicuous places. How would it be if a stratum-2 SNTP server sneaked in the list of public servers? (...)

* * *

#### 5.3.2 Why should I have more than one clock?

NTP likes to estimate the errors of all clocks. Therefore all NTP servers return the time together with an estimate of the current error. When using multiple time servers, NTP also wants these servers to agree on some time, meaning there must be one error interval where the correct time must be.

[The 1999 survey](/reflib/reports/ntp-survey99-minar.pdf) suggests that not all NTP servers work as designed in theory. In fact there was a high percentage of stratum-1 servers with a bad time. Over 30% of the active stratum-1 servers had a clock error of over 10 seconds, and a few even had an error of more than a year. The author of the survey says: "Only 28% of the stratum 1 clocks found appear to actually be useful."

Time sources that are reachable and have a _dispersion_ smaller than the maximum become _candidates_ for time synchronization, thus contributing an error interval. In [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf) section 4.2 the algorithms are treated in greater detail.

If these candidates pass another validation test, they become _survivors_. Basically all values must lie within the error interval the majority of candidates defines. All other time sources are called _falsetickers_ subsequently.

Among the survivors those with significant high dispersion are removed and tagged as _outlyers_.

The final synchronization source is the survivor with the smallest dispersion.

From this description:

*   Just one time source will always be trusted.
*   Two time sources cannot be split into two parties where one has a majority.
*   For a three-server configuration a failing server will cause the two-server problem to appear.

* * *

#### 5.3.3 Does the reference time depend on all configured servers, or is it based on which ever responds first?

Neither of these is true since multiple time sources will be selected and combined to get an estimate of the time. Some criteria are:

*   Is the configured server _reachable_ (does it respond to queries)?
*   Do replies of the server satisfy basic sanity checks: delay, offset, jitter (dispersion), and stratum? Basically, lower values are preferred.
*   If a configured server gets that far, it will be called a candidate. Candidates are ordered by jitter; the one with the lowest jitter will be the new time reference, but all the others will contribute to the estimated time as well.

* * *

#### 5.3.4 What happens during a Leap Second?

The theory of leap seconds in explained in [Q: 2.4](/ntpfaq/ntp-s-time/#24-what-happens-during-a-leap-second). In reality there are two cases to consider:

*   If the operating system implements the [kernel discipline](/ntpfaq/ntp-s-algo-kernel/), `ntpd` will announce insertion and deletion of leap seconds to the kernel. The kernel will handle the leap seconds without further action necessary.
*   If the operating system does not implement the kernel discipline, the clock will show an error of one second relative to NTP's time immediately after the leap second. The situation will be handled just like an unexpected change of time: the operating system will continue with the wrong time for some time, but eventually `ntpd` will _step_ the time. Effectively this will cause the correction for leap seconds to be applied too late.