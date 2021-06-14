---
title: "Further Information and Bibliography "
type: archives
---

#### Table of Contents

*  [Conformance Statement](/archives/3-5.93e/biblio/#conformance-statement)
*  [Selected Bibliography](/archives/3-5.93e/biblio/#selected-bibliography)

* * *

#### Conformance Statement

The Network Time Protocol (NTP) is used to synchronize the time of a computer client or server to another server or reference time source, such as a radio or satellite receiver or modem. It provides accuracies typically within a millisecond on LANs up to a few tens of milliseconds on WANs relative to Coordinated Universal Time (UTC), as provided by a Global Positioning Service (GPS) receiver, for example. Typical NTP configurations utilize multiple redundant servers and diverse network paths, in order to achieve high accuracy and reliability. Some configurations include cryptographic authentication to prevent accidental or malicious protocol attacks. Information on the NTP architecture, protocol and algorithms can be found in the following articles and reports, which are available online:

  Mills, D.L. Internet time synchronization: the Network Time Protocol. _IEEE Trans. Communications COM-39, 10_ (October 1991), 1482-1493. [(PDF)](https://www.eecis.udel.edu/~mills/database/papers/trans.pdf). Also in: Yang, Z., and T.A. Marsland (Eds.). _Global States and Time in Distributed Systems_. IEEE Computer Society Press, Los Alamitos, CA, 1994, 91-102. Condensed from: _Ibid_. Network Working Group Report RFC-1129, University of Delaware, October 1989. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/rfc/rfc1129/rfc1129a.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/rfc/rfc1129/rfc1129b.pdf). Also published as: Electrical Engineering Department Report 89-9-1, University of Delaware, September 1989.

The NTP specification and implementation has evolved over the last fifteen years to the current Version 3 of the protocol. This version includes significant enhancements in accuracy and reliability, as determined by experience in an estimated total of well over 100,000 clients and servers in the Internet, while retaining backward compatibility with previous versions. The formal specification of the NTP Version 3 protocol is contained in:

  Mills, D.L. Network Time Protocol (Version 3) specification, implementation and analysis. Network Working Group Report RFC-1305, University of Delaware, March 1992, 113 pp. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/reports/ntpv3/ntpv3a.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/reports/ntpv3/ntpv3b.pdf), [(Appendices: PDF)](https://www.eecis.udel.edu/~mills/database/reports/ntpv3/ntpv3c.pdf).

This software distribution contains a fully compliant implementation of the NTP Version 3 protocol, including an autonomous protocol daemon that disciplines the local host clock, as well as a set of supporting utility programs used to debug and manage one or more NTP servers in a network. It includes complete sources and documentation for well over two dozen Unix-based and Microsoft NT-based workstations and file servers. The implementation is fully compliant with RFC-1305 and, in addition, contains certain extensions compatible with, but not defined by, that document. These extensions include:

1.  Support for precision-time kernel modifications, as described in:
      Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/reports/kern/kerna.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/reports/kern/kernb.pdf). Major revision and update of: Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [(ASCII)](https://www.eecis.udel.edu/~mills/database/rfc/rfc1589.txt).

2.  Support for IP Multicasting, as described in:
      Mills, D.L, and A. Thyagarajan. Network time protocol version 4 proposed changes. Electrical Engineering Department Report 94-10-2, University of Delaware, October 1994, 32 pp. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/reports/acts/actsa.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/reports/acts/actsb.pdf).

3.  A new hybrid phase/frequency-lock clock discipline, which replaces the RFC-1305 local clock algorithm, as described in:

      Mills, D.L. Improved algorithms for synchronizing computer network clocks. _IEEE/ACM Trans. Networks_ (June 1995), 245-254. [(PDF)](https://www.eecis.udel.edu/~mills/database/papers/tune.pdf).

4.  Engineered refinements to radio clock drivers and interface code, as described in:
      Mills, D.L. Precision synchronization of computer network clocks. _ACM Computer Communication Review 24, 2_ (April 1994). 28-43. [Body: (PDF)](https://www.eecis.udel.edu/~mills/database/reports/fine/fineb.pdf).

5.  Support for over two dozen reference clock drivers for all known national and international radio, satellite and modem standard time services known at this time. See the [Reference Clock Drivers](/archives/3-5.93e/refclock) page.
6.  Support for the MD5 cryptographic hash algorithm, in addition to the DES-CBC algorithm described in RFC-1305, as described in the [<tt>xntpd</tt> - Network Time Protocol (NTP) daemon](/archives/3-5.93e/xntpd) page.
7.  The prefer-peer scheme, as described in the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/3-5.93e/prefer) page.

* * *

#### Selected Bibliography

A number of articles and reports have been written on the analysis, design, implementation and performance of NTP. A representative sample is included here, along with a short description of each. Additional information on NTP can be found at the web sites for [NTP](http://www.ntp.org) and [David L. Mills](http://www.eecis.udel.edu/~mills).

1.  A subset of NTP has been defined suitable for use where some degradation in accuracy and reliability is acceptable, so that the entire suite of specified algorithms need not be implemented. This subset is defined in:

    Mills, D.L. Simple Network Time Protocol (SNTP). Network Working Group Report RFC-1769, University of Delaware, March 1995, 14 pp. [(ASCII)](https://www.eecis.udel.edu/~mills/database/rfc/rfc1769.txt). Major revision and update of: _Ibid_. Network Working Group Report [RFC-1361](https://datatracker.ietf.org/doc/html/rfc1361), University of Delaware, August 1992, 10 pp.

2.  An assessment of the expected accuracy of NTP operating in the Internet is contained in the following:

    Mills, D.L. Measured performance of the Network Time Protocol in the Internet system. Network Working Group Report RFC-1128. University of Delaware, October 1989. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/rfc/rfc1128/rfc1128a.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/rfc/rfc1128/rfc1128b.pdf). Also published as: Electrical Engineering Department Report 89-9-3, University of Delaware, September 1989. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/reports/glory/glorya.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/reports/glory/gloryb.pdf).

    Mills, D.L. On the accuracy and stability of clocks synchronized by the Network Time Protocol in the Internet system. _ACM Computer Communication Review 20, 1_ (January 1990), 65-75. [(PDF)](https://www.eecis.udel.edu/~mills/database/papers/ccr.pdf).

3.  The following publication explores issues involved in the development of the NTP specification, including the development of its timescale and the treatment of leap seconds:

    Mills, D.L. On the chronology and metrology of computer network timescales and their application to the Network Time Protocol. _ACM Computer Communications Review 21, 5_ (October 1991), 8-17. [(PDF)](https://www.eecis.udel.edu/~mills/database/papers/time.pdf).

4.  A comprehensive analysis of the engineering model used in the NTP algorithms is given in the following report. This includes a performance analysis of the clock filter and selection algorithms, clock discipline feedback loop, and error budget.

    Mills, D.L. Modelling and analysis of computer network clocks. Electrical Engineering Department Report 92-5-2, University of Delaware, May 1992, 29 pp. [(Abstract: PDF)](https://www.eecis.udel.edu/~mills/database/reports/time/timea.pdf), [(Body: PDF)](https://www.eecis.udel.edu/~mills/database/reports/time/timeb.pdf).