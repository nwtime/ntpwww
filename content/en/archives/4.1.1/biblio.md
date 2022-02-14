---
title: "Protocol Conformance Statement"
type: archives
---

![](/archives/pic/flatheads.gif)[From _The Wizard of Oz_, L. Frank Baum](/reflib/pictures/)

Say it three times and it must be right.  

* * *

The Network Time Protocol (NTP) is used to synchronize the time of a computer client or server to another server or reference time source, such as a radio or satellite receiver or modem. It provides accuracies typically within a millisecond on LANs up to a few tens of milliseconds on WANs relative to Coordinated Universal Time (UTC), as provided by a Global Positioning Service (GPS) receiver, for example. Typical NTP configurations utilize multiple redundant servers and diverse network paths, in order to achieve high accuracy and reliability. Some configurations include cryptographic authentication to prevent accidental or malicious protocol attacks.

Information on the NTP architecture, protocol and algorithms can be found in the following articles and reports, which are available online. General issues of the concepts and facilities assumed by NTP are discussed in the [Executive Summary - Computer Network Time Synchronization](/archives/4.1.1/exec/) page, while issues related to the NTP timescale and pending century are discussed in the Network Time Protocol Year 2000 Conformance Statement page, both of which are included in this software distribution. Network timekeeping technology continues to advance and may obsolete some of the following documents. For a current list of all papers, reports, briefings and other documents relevant to the NTP community, see the [Reference Library](/reflib/). A historical perspective is available in
Mills, D.L. A brief history of NTP time: confessions of an Internet timekeeper. Submitted for publication; please do not cite or redistribute. [PostScript](/reflib/papers/history.ps) | [PDF](/reflib/papers/history.pdf)

The NTP architecture, protocol and algorithm models are described in Mills, D.L. Internet time synchronization: the Network Time Protocol. _IEEE Trans. Communications COM-39, 10_ (October 1991), 1482-1493. [PostScript](/reflib/papers/trans.ps) | [PDF](/reflib/papers/trans.pdf). Also in: Yang, Z., and T.A. Marsland (Eds.). _Global States and Time in Distributed Systems_. IEEE Computer Society Press, Los Alamitos, CA, 1994, 91-102.

The NTP specification and implementation has evolved over the last two decades to the current Version 4 of the protocol. This version includes significant enhancements in accuracy and reliability, as determined by experience in an estimated total of well over 100,000 clients and servers in the Internet, while retaining backward compatibility with previous versions. This software distribution contains an implementation of the NTP Version 4 architecture, protocol and algorithms. While a formal specification of this version is not yet available, this version is fully compliant with the previous NTP Version 3 specification and implementation defined in Mills, D.L. Network Time Protocol (Version 3) specification, implementation and analysis. Network Working Group Report RFC-1305, University of Delaware, March 1992, 113 pp. Abstract: [PostScript](/reflib/rfc/rfc1305/rfc1305a.ps) | [PDF](/reflib/rfc/rfc1305/rfc1305a.pdf), Body: [PostScript](/reflib/rfc/rfc1305/rfc1305b.ps) | [PDF](/reflib/rfc/rfc1305/rfc1305b.pdf), Appendices: [PostScript](/reflib/rfc/rfc1305/rfc1305c.ps) | [PDF](/reflib/rfc/rfc1305/rfc1305c.pdf).

The NTP Version 4 implementation adds a number of extensions and refinements to the previous version, including an autonomous configuration and authentication capability, improved clock discipline algorithms capable of submicrosecond accuracy and many other refinements. Specific changes since the Version 3 specification was issued include:

1.  Support for precision-time kernel modifications, as described in

    Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PostScript](/reflib/papers/nano/nano2.ps) | [PDF](/reflib/papers/nano/nano2.pdf), Slides: [PostScript](/reflib/brief/nano/nano.ps) | [PowerPoint](/reflib/brief/nano/nano.ppt)

    Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PostScript](/reflib/reports/kern/kerna.ps) | [PDF](/reflib/reports/kern/kerna.pdf), Body: [PostScript](/reflib/reports/kern/kernb.ps) | [PDF](/reflib/reports/kern/kernb.pdf). Major revision and update of: Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)

2.  Support for IP Multicasting, as described the [Association Management](/archives/4.1.1/assoc/) page and in

    Mills, D.L, and A. Thyagarajan. Network time protocol version 4 proposed changes. Electrical Engineering Department Report 94-10-2, University of Delaware, October 1994, 32 pp. Abstract: [PostScript](/reflib/reports/acts/actsa.ps) | [PDF](/reflib/reports/acts/actsa.pdf), Body: [PostScript](/reflib/reports/acts/actsb.ps) | [PDF](/reflib/reports/acts/actsb.pdf)

3.  A new hybrid phase/frequency-lock clock discipline, which replaces the RFC-1305 local clock algorithm, as described in

    Mills, D.L. Improved algorithms for synchronizing computer network clocks. _IEEE/ACM Trans. Networks 3, 3_ (June 1995), 245-254. [PostScript](/reflib/papers/tune2.ps) | [PDF](/reflib/papers/tune2.pdf)

    Mills, D.L. Clock discipline algorithms for the Network Time Protocol Version 4. Electrical Engineering Report 97-3-3, University of Delaware, March 1997, 35 pp. Abstract: [PostScript](/reflib/reports/allan/securea.ps) | [PDF](/reflib/reports/allan/securea.pdf), Body: [PostScript](/reflib/reports/allan/secureb.ps) | [PDF](/reflib/reports/allan/secureb.pdf)

4.  Simple Network Monitoring Protocol (SNMP) monitoring tools, as described in

    Sethi, A.S., H. Gao, and D.L. Mills. Management of the Network Time Protocol (NTP) with SNMP. Computer and Information Sciences Report 98-09, University of Delaware, November 1998, 32 pp. [PostScript](/reflib/reports/ntp-mib-tr.ps) | [PDF](/reflib/reports/ntp-mib-tr.pdf)

5.  Engineered refinements to radio clock drivers and interface code, as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.1.1/pps/) page and

    Mogul, J., D. Mills, J. Brittenson, J. Stone and U. Windl. Pulse-per-second API for Unix-like operating systems, version 1. Request for Comments RFC-2783, Internet Engineering Task Force, March 2000, 31 pp. [ASCII](/reflib/rfc/rfc2783.txt)

    Mills, D.L. Precision synchronization of computer network clocks. _ACM Computer Communication Review 24, 2_ (April 1994). 28-43. [PostScript](/reflib/papers/fine.ps) | [PDF](/reflib/papers/fine.pdf)

6.  Support for over two dozen reference clock drivers for all known national and international radio, satellite and modem standard time services known at this time. See the [Reference Clock Drivers](/archives/4.1.1/refclock/) page.

7.  A new security model and authentication scheme based on public-key cryptography called _Autokey_, as described in the [Authentication Options](/archives/4.1.1/authopt/) page and in

    Mills, D.L. Public-Key cryptography for the Network Time Protocol. Internet Draft draft-ietf-stime-ntpauth-00.txt, University of Delaware, June 2000, 36 pp. [ASCII](/reflib/memos/draft-ietf-stime-ntpauth-00.txt)

    Mills, D.L. Public key cryptography for the Network Time Protocol. Electrical Engineering Report 00-5-1, University of Delaware, May 2000. 23 pp. Abstract: [PostScript](/reflib/reports/pkey/pkeya.ps) | [PDF](/reflib/reports/pkey/pkeya.pdf), Body: [PostScript](/reflib/reports/pkey/pkeyb.ps) | [PDF](/reflib/reports/pkey/pkeyb.pdf)

    Mills, D.L. Authentication scheme for distributed, ubiquitous, real-time protocols. _Proc. Advanced Telecommunications/Information Distribution Research Program (ATIRP) Conference_ (College Park MD, January 1997), 293-298. [PostScript](/reflib/papers/atirp.ps) | [PDF](/reflib/papers/atirp.pdf)

    Mills, D.L. Proposed authentication enhancements for the Network Time Protocol version 4. Electrical Engineering Report 96-10-3, University of Delaware, October 1996, 36 pp. Abstract: [PostScript](/reflib/reports/secure/securea.ps) | [PDF](/reflib/reports/secure/securea.pdf), Body: [PostScript](/reflib/reports/secure/secureb.ps) | [PDF](/reflib/reports/secure/secureb.pdf)

8.  Support for the MD5 cryptographic hash algorithm, in addition to the DES-CBC algorithm described in RFC-1305, as described in the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/archives/4.1.1/ntpd/) page.

9.  The prefer-peer scheme, as described in the [Mitigation Rules and the <code>prefer</code> Keyword](/archives/4.1.1/prefer/) page.

10.  Specification for the Simple Network Time Protocol (SNTP), as described in

     Mills, D.L. Simple network time protocol (SNTP) version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC-2030, University of Delaware, October 1996, 18 pp. [ASCII](/reflib/rfc/rfc2030.txt). Obsoletes RFC-1769 and RFC-1361.

11.  Support for International Atomic Time (TAI), as described in

     Levine, J., and D. Mills. Using the Network Time Protocol to transmit International Atomic Time (TAI). _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper:  [PDF](/reflib/papers/leapsecond.pdf)

12.  Performance surveys for NTP Version 4 can be found in

     Mills, D.L., A. Thyagarajan and B.C. Huffman. Internet timekeeping around the globe. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Long Beach CA, December 1997), 365-371. Paper: [PostScript](/reflib/papers/survey5.ps) | [PDF](/reflib/papers/survey5.pdf), Slides: [PostScript](/reflib/brief/survey/survey.ps) | [PowerPoint](/reflib/brief/survey/survey.ppt) | [PDF](/reflib/brief/survey/survey.pdf)
	 
	 Mills, D.L. The network computer as precision timekeeper. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, December 1996), 96-108. Paper: [PostScript](/reflib/papers/ptti.ps) | [PDF](/reflib/papers/ptti.pdf), Slides: [PostScript](/reflib/brief/ptti/ptti.ps) | [PowerPoint](/reflib/brief/ptti/ptti.ppt) | [PDF](/reflib/brief/ptti/ptti.pdf)