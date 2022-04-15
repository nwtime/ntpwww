---
title: "Executive Summary: Computer Network Time Synchronization"
type: archives
toc_hide: true
---

![gif](/documentation/pic/alice12.gif)

from [_Alice's Adventures in Wonderland_](/reflib/pictures/), Lewis Carroll

The executive is the one on the left.

* * *

#### Table of Contents

*  [Abstract](/reflib/exec/#abstract)
*  [Introduction](/reflib/exec/#introduction)
*  [Protocol Design Issues](/reflib/exec/#protocol-design-issues)
*  [Precision and Accuracy](/reflib/exec/#precision-and-accuracy)
*  [Security Issues](/reflib/exec/#security-issues)
*  [Computer Clock Modeling and Error Analysis](/reflib/exec/#computer-clock-modeling-and-error-analysis)
*  [Correctness Principles](/reflib/exec/#correctness-principles)
*  [Data Grooming Algorithms](/reflib/exec/#data-grooming-algorithms)
*  [Clock Discipline Algorithm](/reflib/exec/#clock-discipline-algorithm)
*  [Further Reading](/reflib/exec/#further-reading)

* * *

#### Abstract

The Network Time Protocol (NTP) and other protocols are used to synchronize the clocks in an estimated total of 25 million servers, workstations and PCs of the public Internet and private networks. This document contains an overview and functional description of NTP, and its design principles. The material in this document is intended for network architects, administrators and technical operating personel. Additional technical details on design and operation are discussed in related white papers in this collection.

* * *

####  Introduction

This document contains an overview and functional description of the Network Time Protocol (NTP), which is used to synchronize computer clocks in the Internet to a common timescale. The discussion is intended for site managers and administrators as well as technical planning and support staff. This document does not describe the architecture, protocols and algorithm in detail; for that, see the tutorial collection [How NTP Works](/documentation/4.2.8-series/warp/).

The standard timescale used by most nations of the world is Coordinated Universal Time (UTC), which is based on the Earth's rotation about its axis, and the Gregorian Calendar, which is based on the Earth's rotation about the Sun. The UTC timescale is disciplined with respect to International Atomic Time (TAI) by inserting leap seconds at intervals of about 18 months. UTC time is disseminated by various means, including radio and satellite navigation systems, telephone modems and portable clocks. Insertion of leap seconds in the NTP and POSIX timescale is discussed in the white paper [The NTP Timescale and Leap Seconds](/reflib/leap/).

Special purpose receivers are available for many time-dissemination services, including the Global Position System (GPS) and other services operated by various national governments. For reasons of cost and convenience, it is not possible to equip every computer with one of these receivers. However, it is possible to equip some number of computers acting as primary time servers to synchronize a much larger number of secondary servers and clients connected by a common network. In order to do this, a distributed network clock synchronization protocol is required which can read a server clock, transmit the reading to one or more clients and adjust each client clock as required. Protocols that do this include the Network Time Protocol (NTP), IEEE 1588 Precision Time Protocol (PTP), Digital Time Synchronization Service (DTSS), and others found in the literature (See [Further Reading](/reflib/exec/#further-reading/)).

* * *

#### Protocol Design Issues

The synchronization protocol determines the time offset of the server clock relative to the client clock. The various synchronization protocols in use today provide different means to do this, but they all follow the same general model. On request, the server sends a message including its current clock value or _timestamp_ and the client records its own timestamp upon arrival of the message. Additional information on the NTP timescale and timescale calculations is in the white papers [NTP Timestamp Calculations](/reflib/time/) and [The NTP Era and Era Numbering](/reflib/y2k/).

For the best accuracy, the client needs to measure the server-client propagation delay to determine its clock offset relative to the server. Since it is not possible to determine the one-way delays, unless the actual clock offset is known, the protocol measures the total roundtrip delay and calculates the propagation delay is half the roundtrip delay. This assumes the propagation delays are statistically equal in each direction. In general, this is a useful approximation; however, in the Internet of today, network paths and the associated delays can differ significantly due to the individual service providers.

The community served by the synchronization protocol can be very large. For instance, the NTP community in the Internet of today includes over 1000 public primary time servers synchronized by radio, satellite and telephone modem, and well over 25 million secondary servers and clients. In addition, there are many thousands of private communities in large government, corporate and institution networks.

Each community is organized as a tree graph or _subnet_, with the primary servers at the root and secondary servers and clients at increasing hop count, or stratum level, in corporate, department and desktop networks. It is usually necessary at each stratum level to employ redundant servers and diverse network paths in order to protect against broken software, hardware, networks and potential hostile attack.

Synchronization protocols work in one or more association modes, depending on the protocol design. Client/server mode, also called master/slave mode, is supported in NTP, PTP and DTSS. In this mode, a client synchronizes to a stateless server as in the conventional RPC model. NTP also supports symmetric mode, which allows either of two peer servers to synchronize to the other, in order to provide mutual backup.

NTP, PTP and DTSS support a broadcast mode which allows many clients to synchronize to one or a few servers, reducing network traffic when large numbers of clients are involved. In NTP, IP multicast can be used when the subnet spans multiple networks.

Configuration management can be a serious problem in large subnets. Various schemes which index public /reflibs and network directory services are used in NTP and DTSS to discover servers. Both protocols use broadcast modes to support large client populations; but, since listen-only clients cannot calibrate the delay, accuracy can suffer. In NTP and PTP, clients determine the delay at the time a server is first discovered by polling the server in client/server mode and then reverting to listen-only mode. In addition, NTP clients can broadcast a special "manycast" message to solicit responses from nearby servers and continue in client/server mode with the respondents. Additional details about the NTP protocol are in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/). Additional details about NTP and PTP interoperation are in the white paper [IEEE 1588 Precision Time Protocol](/reflib/ptp/).

* * *

#### Precision and Accuracy

The NTP accuracy expectations depend on the environment and application requirements. In practice, the single factor most affecting accuracy at the longer update intervals used on global network paths is ambient temperature variations. Under typical room temperature conditions, the clock oscillator frequency can vary in the order of one part-per-million (PPM). This results in synchronization accuracy in the order of a few milliseconds at update intervals of fifteen minutes. However, accuracy can be much improved to the order of one millisecond at update intervals of one minute, as used with primary reference clocks.

At the lower update intervals, the primary factor affecting accuracy is jitter due to network and operating system latencies. With a GPS receiver and pulse-per-second (PPS) signal, together with operating system support in typical Unix kernels, the accuracy is in the order of a few microseconds. This of course is a property of the hardware and operating system, not the NTP protocol.

As a rule of thumb, the accuracy over the Internet is proportional to the propagation delay. For a lightly loaded 100-Mb/s Ethernet, the accuracy is in the order of 100 μs. For an intercontinental Internet path, the accuracy can be up to several tens of milliseconds.

On network paths with large asymmetric propagation delays, such as when one direction is via satellite and the other via landline, the errors can reach 100 ms or more. There is no way these errors can be avoided, unless there is prior knowledge of the path characteristics.

* * *

#### Security Issues

A reliable network time service requires provisions to prevent accidental or malicious attacks on the servers and clients in the network. This requires that clients can determine that received messages are authentic; that is, were actually sent by the intended server and not manufactured or modified by an intruder.

NTP includes provisions to cryptographically authenticate individual servers using symmetric-key cryptography in which clients authenticate servers using shared secret keys. However, the secret keys must be distributed in advance using secure means beyond the scope of the protocol. This can be awkward and fragile with a large population of potential clients, possibly including hackers.

Modern public-key cryptography provides means to reliably bind the server identification credentials and related public values using public directory services. However, these means carry a high computing cost, especially when large numbers of time-critical clients are involved as often the case with NTP servers. In addition, there are problems unique to NTP in the interaction between the authentication and synchronization functions, since each requires the other for success.

The NTP Version 4 reference implementation includes a revised security model and authentication scheme supporting both symmetric and public-key cryptography. The public-key variant, called Autokey, is specially crafted to reduce the risk of intrusion, minimize the consumption of processor resources and minimize the vulnerability to hacker attack. Additional details can be found on the white paper [NTP Security Analysis](/reflib/security/).

* * *

#### Computer Clock Modeling and Error Analysis

Most computers include a quartz resonator-stabilized oscillator and hardware counter that interrupts the processor at intervals of a few milliseconds. At each interrupt, a quantity called _tick_ is added to a system variable representing the clock time. The clock can be read by system and application programs and set on occasion to an external reference.

Once set, the clock readings increment at a nominal rate, depending on the value of _tick_. Typical Unix system kernels provide a programmable mechanism to increase or decrease the value of _tick_ by a small, fixed amount in order to amortize a given time adjustment smoothly over multiple _tick_ intervals.

Clock errors are due to variations in network delay and latencies in computer hardware and software (jitter), as well as clock oscillator instability (wander). The time of a client relative to its server can be expressed

`_T_(_t_) = _T_(_t_<sub>0</sub>) + _R_(_t - t_<sub>0</sub>) + 1/2 _D_(_t - t_<sub>0</sub>)<sup>2</sup>`,

where _t_ is the current time, _T_ is the time offset at the last measurement update _t_<sub>0</sub>, _R_ is the frequency offset and _D_ is the drift due to resonator ageing. All three terms include systematic offsets that can be corrected and random variations that cannot. Some protocols, including PTP and DTSS, estimate only the first term in this expression, while others, including NTP, estimate the first two terms. Errors due to the third term, while important to model resonator aging in precision applications, are neglected, since they are usually dominated by errors in the first two terms.

The synchronization protocol estimates _T_(_t_<sub>0</sub>) (and _R_(_t_<sub>0</sub>), where relevant) at regular _update intervals_ τ and adjusts the clock to minimize _T_(_t_) in future. In common cases, _R_ can have systematic offsets of several hundred parts-per-million (PPM) with random variations of several PPM due to ambient temperature changes. If not corrected, the resulting errors can accumulate to seconds per day.

In order that these errors do not exceed a nominal specification, the protocol must periodically re-estimate _T_ and _R_ and compensate for variations by adjusting the clock at regular intervals. As a practical matter, for nominal accuracies of tens of milliseconds, this requires clients to exchange messages with servers at intervals in the order of tens of minutes.

Analysis of quartz-resonator stabilized oscillators show that errors are a function of the averaging time, which in turn depends on the interval between corrections. At correction intervals less than a few hundred seconds, errors are dominated by jitter, while, at intervals greater than this, errors are dominated by wander. The characteristics of each regime determine the algorithm used to discipline the clock. These errors accumulate at each stratum level from the root to the leaves of the subnet tree.

It is possible to quantify these errors by statistical means, as in NTP. This allows real-time applications to adjust audio or video playout delay, for example. However, the required statistics may be different for various classes of applications. Some applications need absolute error bounds guaranteed never to exceede, as provided by the following correctness principles.

* * *

#### Correctness Principles

Applications requiring reliable time synchronization such as air traffic control must have confidence that the local clock is correct within some bound relative to a given timescale such as UTC. There is a considerable body of literature that studies these issues with respect to various failure models such as fail-stop and Byzantine disagreement. While these models inspire much confidence in a theoretical setting, most require multiple message rounds for each measurement and would be impractical in a large computer network such as the Internet.

However, it can be shown that the worst-case error in reading a remote server clock cannot exceed one-half the roundtrip delay measured by the client. This is a valuable insight, since it permits strong statements about the correctness of the timekeeping system.

In the Probabilistic Clock Synchronization (PCS) scheme devised by Cristian, a maximum error tolerance is established in advance and time value samples associated with roundtrip delays that exceed twice this value are discarded. By the above argument, the remaining samples must represent time values within the specified tolerance. As the tolerance is decreased, more samples fail the test until a point where no samples survive. The tolerance can be adjusted for the best compromise between the highest accuracy consistent with acceptable sample survival rate.

In a scheme devised by Marzullo and exploited in NTP and DTSS, the worst-case error determined for each server determines a correctness interval. If each of a number of servers are in fact synchronized to a common timescale, the actual time must be contained in the intersection of their correctness intervals. If some intervals do not intersect, then the clique containing the maximum number of intersections is assumed correct _truechimers_ and the others assumed incorrect _falsetickers_. Only the truechimers are used to adjust the system clock.

System clock correctness principles require that clock readings must be always monotonic definite increasing, so that no two successive clock readings will be the same. As long as the reading latency exceeds the hardware resolution, this behavior is guaranteed. With reading latencies dropping below the microsecond in modern processors, the system clock in modern operating systems runs in nanoseconds, rather than the microseconds used in the original Unix kernel. With processor speeds exceeding 1 GHz, this assumption may be in jeopardy. Additional information on these topics is in the white paper [Timestamp Capture Principles](/reflib/stamp/).

* * *

#### Data Grooming Algorithms

By its very nature, clock synchronization is a continuous process, resulting in a sequence of measurements with each of possibly several servers and resulting in a clock adjustment. In some protocols, crafted algorithms are used to improve the time and frequency estimates and refine the clock adjustment. Algorithms described in the literature are based on trimmed-mean and median filter methods.

The clock filter algorithm used in NTP is based on the observation that the correctness interval depends on the roundtrip delay. The algorithm accumulates offset/delay samples in a window of several samples and selects the offset sample associated with the minimum delay. In general, larger window sizes provide better estimates; however, stability considerations limit the window size to about eight.

The same principle could be used when selecting the best subset of servers and combining their offsets to determine the clock adjustment. However, different servers often show different systematic offsets, so the best statistic for the central tendency of the server population may not be obvious.

Various kinds of clustering algorithms have been found useful for this purpose. The one used in NTP sorts the offsets by a quality metric, then calculates the variance of all servers relative to each server separately. The algorithm repeatedly discards the outlier with the largest variance until further discards will not improve the residual variance or until a minimum number of servers remain. The final clock adjustment is computed as a weighted average of the survivors.

* * *

#### Clock Discipline Algorithm

Modern computer clocks use a hardware counter to generate processor interrupts at intervals in the order of a few milliseconds. At each interrupt the processor increments the software system clock by the number of microseconds or nanoseconds between interrupts, often called the tick and sometimes the jiffy.

Most modern processors implement some kind of high resolution hardware counter that can be used to interpolate between ticks. The hardware resolution of the system clock is defined as the time between increments of this counter. However, the actual reading latency due to the kernel interface and interpolation code can range from a few tens of microseconds in older processors to under a microsecond in modern processors.

At the heart of the synchronization protocol is the algorithm used to adjust the system clock in accordance with the final adjustment determined by the data grooming algorithms. This is called the clock discipline algorithm or simply the discipline. Such algorithms can be classed according to whether they minimize the time offset or frequency offset or both. For instance, the discipline used in DTSS minimizes only the time offset, while the one used in NTP minimizes both time and frequency offsets. While the DTSS algorithm cannot remove residual errors due to systematic frequency errors, the NTP algorithm is more complicated and less forgiving of design and implementation mistakes.

All clock disciplines function as a feedback loop, with measured offsets used to adjust the clock oscillator phase and frequency to match the external synchronization source. The behavior of feedback loops is well understood and modeled by mathematical analysis.

The significant design parameter is the time constant, or responsiveness to external or internal variations in time or frequency. Optimum selection of time constant depends on the interval between update messages. In general, the longer these intervals, the larger the time constant and vice versa. In practice and with typical network configurations the optimal poll intervals vary between one and twenty minutes for network paths to some thousands of minutes for modem paths.

* * *

#### Further Reading

These are selections from the comprehensive [Bibliography on Computer Network Time Synchronization](/reflib/biblio/).

1.  Mills, David L. [_Network Time Synchronization: the Network Time Protocol on Earth and in Space, Second Edition._](/reflib/book/) CRC Press 2011, 466 pp.
2.  Mills, D., J. Martin (Ed.), et al. Network Time Protocol Version 4: protocol and algorithm specification. Request for Comments RFC 5905, Internet Engineering Task Force, June, 2010. [ASCII](/reflib/rfc/rfc5905.txt)
3.  Mills, D., B. Haberman (Ed.). Network Time Protocol Version 4: Autokey specification. Request for Comments RFC 5906, Internet Engineering Task Force, June, 2010. [ASCII](/reflib/rfc/rfc5906.txt)
4.  Mills, D.L. Network Time Protocol Version 4 Reference and Implementation Guide. Electrical and Computer Engineering Technical Report 06-06-1, University of Delaware, June 2006, 83 pp, [PDF](/reflib/reports/ntp4/ntp4.pdf)
5.  Mills, D.L. The Autokey security architecture, protocol and algorithms. Electrical and Computer Engineering Technical Report 06-1-1, University of Delaware, January 2006, 59 pp. [PDF](/reflib/reports/stime1/stime.pdf)
6.  Mills, D., D. Plonka and J. Montgomery. Simple network time protocol (SNTP) version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC 4330, University of Delaware, December 2005, 27 pp. [ASCII](/reflib/rfc/rfc4330.txt) Major revision and update of: _Ibid_. Network Working Group Report [RFC 2030](/reflib/rfc/rfc2030.txt), University of Delaware, October 1996, 20 pp.
7.  Mills, D.L. Public key cryptography for the Network Time Protocol. Electrical Engineering Report 00-5-1, University of Delaware, May 2000. 23 pp. Abstract: [](/reflib/reports/pkey/pkeya.ps)[PDF](/reflib/reports/pkey/pkeya.pdf), Body: [](/reflib/reports/pkey/pkeyb.ps)[PDF](/reflib/reports/pkey/pkeyb.pdf)
8.  Mogul, J., D. Mills, J. Brittenson, J. Stone and U. Windl. Pulse-per-second API for Unix-like operating systems, version 1. Request for Comments RFC 2783, Internet Engineering Task Force, March 2000, 31 pp. [ASCII](/reflib/rfc/rfc2783.txt)
9.  Mills, D.L. A brief history of NTP time: confessions of an Internet timekeeper. Submitted for publication; please do not cite or redistribute. [](/reflib/papers/history.ps)[PDF](/reflib/papers/history.pdf)
10.  Mills, D.L. Public key cryptography for the Network Time Protocol. Electrical Engineering Report 00-5-1, University of Delaware, May 2000. 23 pp. Abstract: [](/reflib/reports/pkey/pkeya.ps)[PDF](/reflib/reports/pkey/pkeya.pdf), Body: [](/reflib/reports/pkey/pkeyb.ps)[PDF](/reflib/reports/pkey/pkeyb.pdf)
11.  Minar, N. A survey of the NTP network. MIT Media Laboratory, December 1999, 10 pp. [PDF](/reflib/reports/ntp-survey99-minar.pdf)
12.  Mills, D.L. Cryptographic authentication for real-time network protocols. In: _AMS DIMACS Series in Discrete Mathematics and Theoretical Computer Science, Vol. 45_ (1999), 135-144. Paper: [](/reflib/papers/dimacs.ps)[PDF](/reflib/papers/dimacs.pdf), Slides: [PowerPoint](/reflib/brief/dimacs/dimacs.ppt)
13.  Mills, D.L. Adaptive hybrid clock discipline algorithm for the Network Time Protocol. _IEEE/ACM Trans. Networking 6, 5_ (October 1998), 505-514. [PDF](/reflib/papers/allan.pdf)
14.  Mills, D.L., A. Thyagarajan and B.C. Huffman. Internet timekeeping around the globe. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Long Beach CA, December 1997), 365-371. Paper: [](/reflib/papers/survey5.ps)[PDF](/reflib/papers/survey5.pdf) Slides: [](/reflib/brief/survey/survey.ps)[PowerPoint](/reflib/brief/survey/survey.ppt) | [PDF](/reflib/brief/survey/survey.pdf)
15.  Sethi, A.S., H. Gao, and D.L. Mills. Management of the Network Time Protocol (NTP) with SNMP. Computer and Information Sciences Report 98-09, University of Delaware, November 1997, 32 pp. [](/reflib/reports/ntp-mib-tr.ps)[PDF](/reflib/reports/ntp-mib-tr.pdf)

16.  Mills, D.L. Authentication scheme for distributed, ubiquitous, real-time protocols. _Proc. Advanced Telecommunications/Information Distribution Research Program (ATIRP) Conference_ (College Park MD, January 1997), 293-298. Paper: [](/reflib/papers/atirp.ps)[PDF](/reflib/papers/atirp.pdf) Slides:  [PDF](/reflib/brief/atirp/atirp.pdf)

17.  Mills, D.L. The network computer as precision timekeeper. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, December 1996), 96-108. Paper: [](/reflib/papers/ptti.ps)[PDF](/reflib/papers/ptti.pdf) Slides: [](/reflib/brief/ptti/ptti.ps)[PowerPoint](/reflib/brief/ptti/ptti.ppt) | [PDF](/reflib/brief/ptti/ptti.pdf)
18.  Mills, D.L. Simple network time protocol (SNTP) version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC 2030, University of Delaware, October 1996, 18 pp. [ASCII](/reflib/rfc/rfc2030.txt) Major revision and update of: _Ibid_. Network Working Group Report RFC 1769, University of Delaware, March 1995, 14 pp. [ASCII](/reflib/rfc/rfc1769.txt) Also published (with figures) as _Ibid_ Electrical Engineering Department Report 96-10-2, University of Delaware, October 1996, 14 pp. Abstract: [PDF](/reflib/reports/sntp4/sntp4a.pdf), Body: [[PDF](/reflib/reports/sntp4/sntp4b.pdf)
19.  Mills, D.L. Improved algorithms for synchronizing computer network clocks. _IEEE/ACM Trans. Networks 3, 3_ (June 1995), 245-254. [](/reflib/papers/tune2.ps)[PDF](/reflib/papers/tune2.pdf) Revised from: _ibid_. _Proc. ACM SIGCOMM 94 Symposium_ (London UK, September 1994), 317-327. [PDF](/reflib/papers/tune.pdf)
20.  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC 1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)
21.  Mills, D.L. Modelling and analysis of computer network clocks. Electrical Engineering Department Report 92-5-2, University of Delaware, May 1992, 29 pp. Abstract: [PDF](/reflib/reports/time/timea.pdf), Body: [PDF](/reflib/reports/time/timeb.pdf)
22.  Mills, D.L. Network Time Protocol (Version 3) specification, implementation and analysis. Network Working Group Report RFC 1305, University of Delaware, March 1992, 113 pp. Abstract: [](/reflib/rfc/rfc1305/rfc1305a.ps)[PDF](/reflib/rfc/rfc1305/rfc1305a.pdf), Body: [](/reflib/rfc/rfc1305/rfc1305b.ps)[PDF](/reflib/rfc/rfc1305/rfc1305b.pdf), Appendices: [](/reflib/rfc/rfc1305/rfc1305c.ps)[PDF](/reflib/rfc/rfc1305/rfc1305c.pdf) Revised from: Electrical Engineering Department Report 90-6-1, University of Delaware, June 1990, 103 pp. Abstract: [PDF](/reflib/reports/ntpv3/ntpv3a.pdf), Body: [PDF](/reflib/reports/ntpv3/ntpv3b.pdf), Appendices: [PDF](/reflib/reports/ntpv3/ntpv3c.pdf)
23.  Mills, D.L. On the chronology and metrology of computer network timescales and their application to the Network Time Protocol. _ACM Computer Communications Review 21, 5_ (October 1991), 8-17. [PDF](/reflib/papers/time.pdf)
24.  Mills, D.L. Internet time synchronization: the Network Time Protocol. _IEEE Trans. Communications COM-39, 10_ (October 1991), 1482-1493. [](/reflib/papers/trans.ps)[PDF](/reflib/papers/trans.pdf) Also in: Yang, Z., and T.A. Marsland (Eds.). _Global States and Time in Distributed Systems_. IEEE Computer Society Press, Los Alamitos, CA, 1994, 91-102. Condensed from: _Ibid_. Network Working Group Report [RFC 1129](/reflib/rfc/rfc1129/rfc1129b.pdf), University of Delaware, October 1989. Also published as: Electrical Engineering Department Report 89-9-1, University of Delaware, September 1989.
25.  Mills, D.L. On the accuracy and stability of clocks synchronized by the Network Time Protocol in the Internet system. _ACM Computer Communication Review 20, 1_ (January 1990), 65-75. [PDF](/reflib/papers/ccr.pdf)
26.  Mills, D.L. Measured performance of the Network Time Protocol in the Internet system. Network Working Group Report RFC 1128. University of Delaware, October 1989, 18 pp. Abstract: [PDF](/reflib/rfc/rfc1128/rfc1128a.pdf), Body: [PDF](/reflib/rfc/rfc1128/rfc1128b.pdf) Also published as: Electrical Engineering Department Report 89-9-3, University of Delaware, September 1989, 16 pp. Abstract: [PDF](/reflib/reports/glory/glorya.pdf), Body: [PDF](/reflib/reports/glory/gloryb.pdf)
27.  Cristian, F. Probabilistic clock synchronization. In Distributed Computing 3, Springer Verlag, 1989, 146-158.