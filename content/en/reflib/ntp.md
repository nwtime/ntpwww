---
title: "Network Time Synchronization Research Project"
type: archives
toc_hide: true
---

![gif](/archives/pic/alautun4a.gif)

[Maya glyph _alautun_](/reflib/maya/)

Researchers involved: David Mills, graduate students and many volunteers

Funding: Defense Advanced Research Projects Agency (DARPA), National Science Foundation (NSF), Navy Surface Weapons Center (NSWC) and Jet Propulsion Laboratory/NASA

Last update: 13-May-2012

* * *

#### Table of Contents

*  [Briefing Slides](/reflib/ntp/#briefing-slides)
*  [Importance of the Problem](/reflib/ntp/#importance-of-the-problem)
*  [Brief Description of Work and Results](/reflib/ntp/#brief-description-of-work-and-results)
*  [Future Plans](/reflib/ntp/#future-plans)
*  [Selected Publications](/reflib/ntp/#selected-publications)

* * *

#### Briefing Slides

[//]: <> (commented by DL July/2021: Note: The recommended format is PDF and Adobe Acrobat Reader 3 or later. Where available, PowerPoint presentations are provided.)

*   Network Time Protocol (NTP) General Overview [PDF](/reflib/brief/overview/overview.pdf)
*   NTP Architecture, Protocol and Algorithms [PDF](/reflib/brief/arch/arch.pdf)
*   NTP Procedure Descriptions and Flow Diagrams [PDF](/reflib/brief/flow/flow.pdf)
*   NTP Clock Discipline Principles [PDF](/reflib/brief/clock/clock.pdf)
*   NTP Security Model [PDF](/reflib/brief/autokey/autokey.pdf)
*   NTP Security Algorithms [PDF](/reflib/brief/secalgor/secalgor.pdf)
*   NTP Security Protocol [PDF](/reflib/brief/secproto/secproto.pdf)
*   NTP Precision Synchronization [PDF](/reflib/brief/precise/precise.pdf)
*   NTP Performance Analysis [PDF](/reflib/brief/perf/perf.pdf)
*   NTP Algorithm Analysis [PDF](/reflib/brief/algor/algor.pdf)
*   NTP Interleaved Protocol for LANs and Space Data Links [PowerPoint](/reflib/brief/onwire/onwire.ppt) | [PDF](/reflib/brief/onwire/onwire.pdf)
*   Long-Range Dependency Effects in NTP Timekeeping [PDF](/reflib/brief/hurst/hurst.pdf)

[//]: <> (commented by DL July/2021 as does not exist *   Mainframe Timekeeping with the IBM 9037 Sysplex [PDF](/reflib/brief/bof/ibm.pdf))

* * *

#### Importance of the Problem

The Network Time Protocol (NTP) is widely used in the Internet to synchronize computer clocks to national standard time. The NTP architecture, protocol and algorithms have evolved over more than three decades to the NTP Version 4 specification and reference implementations for Unix, VMS and Windows.

NTP time synchronization services are widely available in the public Internet, which today includes several thousand servers in most countries and on every continent of the globe, including Antarctica, and sometimes in space, on ships and on the sea floor. These servers support a total population estimated at over 25 million computers in the global Internet.

Previous funded research has resulted in a series of improvements in accuracy and reliability of the protocol and supporting algorithms. Used in the Internet of today with computers ranging from personal workstations to supercomputers, NTP provides accuracies generally in the range of 0.1 ms with fast LANs and computers and up to a few tens of milliseconds in the intercontinental Internet.

The current NTP Version 4 speculation [RFC 5905](/reflib/rfc/rfc5905.txt) and reference implementation represent a significant enhancement to the NTP Version 3 specification and implementation first developed in 1992. Specifically, these involve provisions for an autonomous configuration and autonomous authentication capability which provides for automatic server discovery and secure server authentication using both symmetric key and public key cryptography described in [RFC 5906](/reflib/rfc/rfc5906.txt).

* * *

#### Brief Description of Work and Results

We consider the NTP project and ongoing development a basically mature project, although there is always the opportunity for incremental advances.

There have been significant changes and additions  to the NTPv4 protocol specification [RFC 5905](/reflib/rfc/rfc5905.txt) and the Autokey specification [RFC 5906](/reflib/rfc/rfc5906.txt) since their publication in 2010. In addition, there have been significant unreported changes since the original drafts were written in 2006. The five-year delay in the IETF publishing process has meant that these changes have not kept pace with the current development and there are no current plans to update the documents in the near future.

However, there is a considerable body of progress reported in the online documentation [NTP Version 4 Release Notes](/archives/4.2.8-series/release/) and the white papers [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/) and [NTP Security Analysis](/reflib/security/). These documents should be reformatted as an Informational RFC and relevant sections should be incorporated in a RFC 5905 replacement or supplement. While the book cited below cites some of the improvements, the most recent are documented only  in the online documentation and white papers.

* * *

#### Future Plans

We anticipate future development of time synchronization technology for planetary networks and deep space missions, as described in the white paper [Time Synchronization for Space Data Links](/reflib/proximity/). We expect to continue the study of interoperability between NTP and the [IEEE 1588 Precision Time Protocol](/reflib/ptp/). These issues are discussed in a [book](/reflib/book/). We plan to incorporate certain minor enhancements to improve error recovery in the reference implementation, as described in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/).

We expect to refine the NTP Autokey protocol and incorporate refinements suggested in the white paper [NTP Security Analysis](/reflib/security/). We expect to continue the testing and verification program with UTC leap seconds, as described in the white paper [The NTP Timescale and Leap Seconds](/reflib/leap/) and to verify correct operation in case of era rollover, as described in the white paper [NTP Timescale Calculations](/reflib/stamp/).

We expect to further refine the Manycast model to improve stability in networks with large numbers of servers and clients. The means proposed to do this involve a whisper campaign where Manycast servers keep track of dependent clients by means of specific Autokey messages. The servers would then run load balancing and stratum selection algorithms suggested in a recent dissertation.

* * *

#### Selected Publications

1.  Mills, D.L. Network Time Synchronization - the Network Time Protocol on Earth and in Space. CRC Press, 2011, 466 pp.
2.  Mills, D., J. Martin (Ed.), et al. Network Time Protocol Version 4: protocol and algorithm specification. Request for Comments RFC 5905, Internet Engineering Task Force, June, 2010. [ASCII](/reflib/rfc/rfc5905.txt)
3.  Mills, D., B. Haberman (Ed.). Network Time Protocol Version 4: Autokey specification. Request for Comments RFC 5906, Internet Engineering Task Force, June, 2010. [ASCII](/reflib/rfc/rfc5906.txt)
4.  Mills, D.L. Network Time Protocol Version 4 reference and implementation guide. Electrical and Computer Engineering Technical Report 06-06-1, University of Delaware, June 2006, 83 pp, [PDF](/reflib/reports/ntp4/ntp4.pdf)
5.  Mills, D.L. The Autokey security architecture, protocol and algorithms. Electrical and Computer Engineering Technical Report 06-1-1, University of Delaware, January 2006, 59 pp. [PDF](/reflib/reports/stime1/stime.pdf)
6.  Mills, D., D. Plonka and J. Montgomery. Simple network time protocol (SNTP) version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC 4330, University of Delaware, December 2005, 27 pp. [ASCII](/reflib/rfc/rfc4330.txt) Major revision and update of: _Ibid_. Network Working Group Report RFC 2030, University of Delaware, October 1996, 20 pp.
7.  Mills, D.L., J. Levine, R. Schmidt and D. Plonka. Coping with overload on the Network Time Protocol public servers. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Washington DC, December 2004), 5-16. Paper: [PDF](/reflib/papers/ptti/ptti04a.pdf), Slides: [PDF](/reflib/brief/ptti/ptti04.pdf) | [PowerPoint](/reflib/brief/ptti/ptti04.ppt)
8.  Mills, D.L. The Autokey security architecture, protocol and algorithms. Electrical and Computer Engineering Technical Report 04-4-1, University of Delaware, April 2004, 57 pp. [PDF](/reflib/reports/stime1/stime.pdf)
9.  Mills, D.L. A brief history of NTP time: confessions of an Internet timekeeper. _ACM Computer Communications Review 33, 2_ (April 2003), 9-22. [Postscript](/reflib/papers/history.ps) | [PDF](/reflib/papers/history.pdf)
10.  Levine, J., and D. Mills. Using the Network Time Protocol to transmit International Atomic Time (TAI). _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PDF](/reflib/papers/leapsecond.pdf) Minar, N. A survey of the NTP network. MIT Media Laboratory, December 1999, 10 pp. [PDF](/reflib/reports/ntp-survey99-minar.pdf)
11.  Mills, D.L. Cryptographic authentication for real-time network protocols. In: _AMS DIMACS Series in Discrete Mathematics and Theoretical Computer Science, Vol. 45_ (1999), 135-144. Paper: [Postscript](/reflib/papers/dimacs.ps) | [PDF](/reflib/papers/dimacs.pdf), Slides: [PowerPoint](/reflib/brief/dimacs/dimacs.ppt)
12.  Mills, D.L. Adaptive hybrid clock discipline algorithm for the Network Time Protocol. _IEEE/ACM Trans. Networking 6, 5_ (October 1998), 505-514. [PDF](/reflib/papers/allan.pdf).
13.  Mills, D.L., A. Thyagarajan and B.C. Huffman. Internet timekeeping around the globe. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Long Beach CA, December 1997), 365-371. Paper: [PDF](/reflib/papers/survey5.pdf) Slides: [Postscript](/reflib/brief/survey/survey.ps) | [PowerPoint](/reflib/brief/survey/survey.ppt) | [PDF](/reflib/brief/survey/survey.pdf)
14.  Sethi, A.S., H. Gao, and D.L. Mills. Management of the Network Time Protocol (NTP) with SNMP. Computer and Information Sciences Report 98-09, University of Delaware, November 1997, 32 pp. [Postscript](/reflib/reports/ntp-mib-tr.ps) | [PDF](/reflib/reports/ntp-mib-tr.pdf)
15.  Mills, D.L. Clock discipline algorithms for the Network Time Protocol Version 4. Electrical Engineering Report 97-3-3, University of Delaware, March 1997, 35 pp. Abstract: [Postscript](/reflib/reports/allan/securea.ps) | [PDF](/reflib/reports/allan/securea.pdf), Body: [Postscript](/reflib/reports/allan/secureb.ps) | [PDF](/reflib/reports/allan/secureb.pdf)
16.  Mills, D.L. Authentication scheme for distributed, ubiquitous, real-time protocols. _Proc. Advanced Telecommunications/Information Distribution Research Program (ATIRP) Conference_ (College Park MD, January 1997), 293-298. Paper: [Postscript](/reflib/papers/atirp.ps) | [PDF](/reflib/papers/atirp.pdf) Slides: [PDF](/reflib/brief/atirp/atirp.pdf)
17.  Mills, D.L. The network computer as precision timekeeper. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, December 1996), 96-108. Paper: [PDF](/reflib/papers/ptti.pdf) Slides: [PDF](/reflib/brief/ptti/ptti.pdf)
18.  Mills, D.L. Proposed authentication enhancements for the Network Time Protocol version 4. Electrical Engineering Report 96-10-3, University of Delaware, October 1996, 36 pp. Abstract: [Postscript](/reflib/reports/secure/securea.ps) | [PDF](/reflib/reports/secure/securea.pdf), Body: [Postscript](/reflib/reports/secure/secureb.ps) | [PDF](/reflib/reports/secure/secureb.pdf)
19.  Mills, D.L. Simple network time protocol (SNTP) version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC 2030, University of Delaware, October 1996, 18 pp. [ASCII](/reflib/rfc/rfc2030.txt) Major revision and update of: _Ibid_. Network Working Group Report RFC 1769, University of Delaware, March 1995, 14 pp. [ASCII](/reflib/rfc/rfc1769.txt) Also published (with figures) as _Ibid_ Electrical Engineering Department Report 96-10-2, University of Delaware, October 1996, 14 pp. Abstract: [PDF](/reflib/reports/sntp4/sntp4a.pdf), Body: [PDF](/reflib/reports/sntp4/sntp4b.pdf)
20.  Mills, D.L. Improved algorithms for synchronizing computer network clocks. _IEEE/ACM Trans. Networks 3, 3_ (June 1995), 245-254. [Postscript](/reflib/papers/tune2.ps) | [PDF](/reflib/papers/tune2.pdf) Revised from: _ibid_. _Proc. ACM SIGCOMM 94 Symposium_ (London UK, September 1994), 317-327. [PDF](/reflib/papers/tune.pdf)
21.  Mills, D.L. Simple network time protocol (SNTP) version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC 2030, University of Delaware, October 1996, 18 pp. [ASCII](/reflib/rfc/rfc2030.txt) Major revision and update of: _Ibid_. Network Working Group Report RFC 1769, University of Delaware, March 1995, 14 pp. [ASCII](/reflib/rfc/rfc1769.txt) Also published (with figures) as _Ibid_ Electrical Engineering Department Report 96-10-2, University of Delaware, October 1996, 14 pp. Abstract: [PDF](/reflib/reports/sntp4/sntp4a.pdf), Body:[PDF](/reflib/reports/sntp4/sntp4b.pdf)
22.  Mills, D.L. Proposed authentication enhancements for the Network Time Protocol version 4. Electrical Engineering Report 96-10-3, University of Delaware, October 1996, 36 pp. Abstract: [Postscript](/reflib/reports/secure/securea.ps) | [PDF](/reflib/reports/secure/securea.pdf), Body: [Postscript](/reflib/reports/secure/secureb.ps) | [PDF](/reflib/reports/secure/secureb.pdf)
23.  Mills, D.L, and A. Thyagarajan. Network time protocol version 4 proposed changes. Electrical Engineering Department Report 94-10-2, University of Delaware, October 1994, 32 pp. Abstract: [Postscript](/reflib/reports/acts/actsa.ps) | [PDF](/reflib/reports/acts/actsa.pdf), Body: [Postscript](/reflib/reports/acts/actsb.ps) | [PDF](/reflib/reports/acts/actsb.pdf)
24.  Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [Postscript](/reflib/reports/kern/kerna.ps) | [PDF](/reflib/reports/kern/kerna.pdf), Body: [Postscript](/reflib/reports/kern/kernb.ps) | [PDF](/reflib/reports/kern/kernb.pdf) Major revision and update of: Network Working Group Report RFC 1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)
25.  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC 1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)
26.  Mills, D.L. Precision synchronization of computer network clocks. Electrical Engineering Department Report 93-11-1, University of Delaware, November 1993, 66 pp. Abstract: [PDF](/reflib/reports/fine/finea.pdf), Body: [PDF](/reflib/reports/fine/fineb.pdf)
27.  Mills, D.L. Modelling and analysis of computer network clocks. Electrical Engineering Department Report 92-5-2, University of Delaware, May 1992, 29 pp. Abstract: [PDF](/reflib/reports/time/timea.pdf), Body: [PDF](/reflib/reports/time/timeb.pdf)
28.  Mills, D.L. Network Time Protocol (Version 3) specification, implementation and analysis. Network Working Group Report RFC 1305, University of Delaware, March 1992, 113 pp. Abstract: [Postscript](/reflib/rfc/rfc1305/rfc1305a.ps) | [PDF](/reflib/rfc/rfc1305/rfc1305a.pdf), Body: [Postscript](/reflib/rfc/rfc1305/rfc1305b.ps) | [PDF](/reflib/rfc/rfc1305/rfc1305b.pdf), Appendices: [Postscript](/reflib/rfc/rfc1305/rfc1305c.ps) | [PDF](/reflib/rfc/rfc1305/rfc1305c.pdf) Revised from: Electrical Engineering Department Report 90-6-1, University of Delaware, June 1990, 103 pp. Abstract: [PDF](/reflib/reports/ntpv3/ntpv3a.pdf), Body: [PDF](/reflib/reports/ntpv3/ntpv3b.pdf), Appendices: [PDF](/reflib/reports/ntpv3/ntpv3c.pdf)
29.  Mills, D.L. On the chronology and metrology of computer network timescales and their application to the Network Time Protocol. _ACM Computer Communications Review 21, 5_ (October 1991), 8-17. [PDF](/reflib/papers/time.pdf)
30.  Mills, D.L. Internet time synchronization: the Network Time Protocol. _IEEE Trans. Communications COM-39, 10_ (October 1991), 1482-1493. [Postscript](/reflib/papers/trans.ps) | [PDF](/reflib/papers/trans.pdf) Also in: Yang, Z., and T.A. Marsland (Eds.). _Global States and Time in Distributed Systems_. IEEE Computer Society Press, Los Alamitos, CA, 1994, 91-102. Condensed from: _Ibid_. Network Working Group Report RFC 1129, University of Delaware, October 1989. Also published as: Electrical Engineering Department Report 89-9-1, University of Delaware, September 1989.
31.  Mills, D.L. On the accuracy and stability of clocks synchronized by the Network Time Protocol in the Internet system. _ACM Computer Communication Review 20, 1_ (January 1990), 65-75. [PDF](/reflib/papers/ccr.pdf)
32.  Mills, D.L. Internet time synchronization: the Network Time Protocol. Network Working Group Report RFC 1129, University of Delaware, October 1989, 27 pp. Abstract: [PDF](/reflib/rfc/rfc1129/rfc1129a.pdf), Body: [PDF](/reflib/rfc/rfc1129/rfc1129b.pdf) Also published as: Electrical Engineering Department Report 89-9-1, University of Delaware, September 1989.
33.  Mills, D.L. Measured performance of the Network Time Protocol in the Internet system. Network Working Group Report RFC 1128. University of Delaware, October 1989, 18 pp. Abstract: [PDF](/reflib/rfc/rfc1128/rfc1128a.pdf), Body: [PDF](/reflib/rfc/rfc1128/rfc1128b.pdf) Also published as: Electrical Engineering Department Report 89-9-3, University of Delaware, September 1989, 16 pp. Abstract: [PDF](/reflib/reports/glory/glorya.pdf), Body: [PDF](/reflib/reports/glory/gloryb.pdf)
34.  Mills, D.L. Network Time Protocol (Version 2) specification and implementation. Network Working Group Report RFC 1119, 61 pp. University ofDelaware, September 1989. Abstract: [PDF](/reflib/rfc/rfc1119/rfc1119a.pdf), Body: [PDF](/reflib/rfc/rfc1119/rfc1119b.pdf) Also published as: Electrical Engineering Department Report 89-9-2, University of Delaware, September 1989. Abstract: [PDF](/reflib/reports/ntpv2/ntpv2a.pdf), Body: [PDF](/reflib/reports/ntpv2/ntpv2b.pdf)
35.  Mills, D.L. Network Time Protocol (Version 1) specification and implementation. Network Working Group Report RFC 1059. University of Delaware, July 1988. [ASCII](/reflib/rfc/rfc1059.txt). Also published as: Electrical Engineering Department Report 88-4-1, University of Delaware, May 1988.
36.  Mills, D.L. A distributed-protocol authentication scheme. Network Working Group Report RFC-1004, University of Delaware, April 1987. [ASCII](/reflib/rfc/rfc1004.txt)