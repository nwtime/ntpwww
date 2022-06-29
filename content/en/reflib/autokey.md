---
title: "Autonomous Authentication"
description: "The goal of Autokey is to develop and test security protocols which resist attacks on the hosts deployed in the network. Hosts must determine that received NTP messages are authentic and be able to verify the authenticity of any message using only public information and without requiring external management intervention."
type: archives
---

![gif](/documentation/pic/rabbit.gif)

from [_Alice's Adventures in Wonderland_](/reflib/pictures/), Lewis Carroll

* * *

#### Table of Contents

*   [Briefing Slides](/reflib/autokey/#briefing-slides)
*   [Related Pages](/reflib/autokey/#related-pages)
*   [Importance of the Problem](/reflib/autokey/#importance-of-the-problem)
*   [Brief Description of Work and Results](/reflib/autokey/#brief-description-of-work-and-results)
*   [Leapseconds Table](/reflib/autokey/#leapseconds-table)
*   [Present Status](/reflib/autokey/#present-status)
*   [Future Plans](/reflib/autokey/#future-plans)
*   [Selected Publications](/reflib/autokey/#selected-publications)

* * *

#### Briefing Slides

*   NTP Security Model [PDF](/reflib/brief/autokey/autokey.pdf)
*   NTP Security Algorithms [PDF](/reflib/brief/secalgor/secalgor.pdf)
*   NTP Security Protocol [PDF](/reflib/brief/secproto/secproto.pdf)

* * *

#### Related Pages

*   [Autonomous Configuration](/reflib/autocfg/)
*   [Autokey Protocol](/reflib/proto/)
*   [Autokey Identity Schemes](/reflib/ident/)

* * *

#### Importance of the Problem

The missions considered in this project include autonomous networks that might be deployed from a reconnaissance vehicle over a battlefield or from a space probe over a planetary surface. Once deployed, the network must operate autonomously using an ad-hoc wireless infrastructure as servers are deployed or destroyed or the network is damaged or compromised and then repaired. In the traditional fog of war scenario, servers may be able to communicate directly only with nearby neighbors and in particular may be able to assess trust only intermittently and not always directly from a trusted source.

The goal of this project is to develop and test security protocols which resist accidental or malicious attacks on the hosts deployed in the network. They must determine that received messages are authentic; that is, were actually sent by the intended source and not manufactured or modified by an intruder. In addition, they must verify the authenticity of any message using only public information and without requiring external management intervention.

The network is protected by a set of cryptographic values, some of which are instantiated before deployment and some of which are generated when needed after deployment. Probably the most important value is the group key which must be instantiated in each server before deployment. A host proves to another host that it is a legitimate group member if it can prove it knows this value. In addition to the group key, every sensor has a host key used to sign messages and certificates and one or more certificates signed by the host key. While the group key must persist for the lifetime of the group, or at least for the lifetime of the mission, the host key and certificates can be refreshed from time to time.

In our model a subset of hosts is endowed by some means as trusted, either directly by command or indirectly by election in case the network becomes fragmented. The remaining hosts must authenticate from the trusted hosts, directly or indirectly, using only cryptographic values already instantiated. In other words, hosts can rely on no help other than already available from other hosts via the security protocol.

* * *

#### Brief Description of Work and Results

Our approach involves a cryptographically sound and efficient methodology for use in sensor networks, as well as other ubiquitous, distributed services deployed in the Internet. As demonstrated in the reports and briefings linked from this page, there is a place for Public-Key Infrastructure (PKI) schemes, but none of these schemes alone satisfies the requirements of a real-time network security model. The Photuris and ISAKMP schemes proposed by the IETF require per-association state variables, which contradicts the principles of the remote procedure call (RPC) paradigm in which hosts keep no state for a possibly large population of clients. An evaluation of the PKI model and algorithms as implemented in the OpenSSL cryptographic library leads to the conclusion that any scheme requiring every real-time message to carry a PKI digital signature could be vulnerable to a clogging attack.

We have used the Network Time Protocol (NTP) software and the widely distributed NTP synchronization subnet in the Internet as a testbed for distributed protocol development and testing. Not only does the deployment, configuration and management of the NTP subnet have features in common with other distributed applications, but a synchronization service itself must be an intrinsic feature of the network infrastructure.

While NTP Version 3 contains provisions to authenticate individual hosts using symmetric key cryptography, it contains no means for secure keys distribution. Public key cryptography provides for public key certificates that bind the host identification credentials to the associated keys. Using PKI key agreements and digital signatures with large client populations can cause significant performance degradations, especially in time critical applications such as NTP. In addition, there are problems unique to NTP in the interaction between the authentication and synchronization functions, since reliable key management requires reliable lifetime control and good timekeeping, while secure timekeeping requires reliable key management.

A revised security model and authentication scheme called Autokey was proposed in earlier reports and papers cited at the end of this page. It has been evolved and refined over time now in its third generation after the original described in the technical report and Version 1 described in previous Internet Drafts. The protocol has been simplified and made more rugged and stable in the event of network or host disruptions. An outline of the security model is given below; additional details of the model and how the protocol operates is on the [Autokey Protocol](/reflib/proto/) page.

The Autokey security model is based on multiple overlapping security compartments or groups. Each group is assigned a group key by a trusted authority and is then deployed to all group members by secure means. Autokey uses conventional IPSEC certificate trails to provide secure host authentication, but this does not provide protection against masquerade, unless the host identity is verified by other means. Autokey includes a suite of identity verification schemes based in part on zero-knowledge proofs. There are five schemes now implemented to prove identity: (1) private certificates (PC), (2) trusted certificates (TC), (3) a modified Schnorr algorithm (IFF aka Identify Friendly or Foe), (4) a modified Guillou-Quisquater algorithm (GQ), and (5) a modified Mu-Varadharajan algorithm (MV). These are described on the [Identity Schemes](/reflib/ident/) page.

The cryptographic data used by Autokey are generated by a utility program designed for this purpose. This program, called [`ntp-keygen`](/documentation/4.2.8-series/keygen/) in the NTP software distribution, generates several files. The lifetimes of all cryptographic values are carefully managed and frequently refreshed. Ordinarily, key lists are refreshed about once per hour and other public and private values are refreshed about once per day. The protocol design is specially tailored to make a smooth transition when these values are refreshed and to avoid vulnerabilities due to clogging and replay attacks.

* * *

#### Leapseconds Table

The National Institute of Science and Technology (NIST) archives an ASCII file containing the epoch for all historic and pending occasions of leap second insertion since 1972. While not strictly a security function, the Autokey scheme provides means to securely retrieve the leapseconds table from a host or peer. At present, the only function provided is to fetch the leapseconds table via the network; the daemon itself makes no use of the values. The latest version of the nanokernel software for SunOS, Alpha, FreeBSD and Linux cited below retrieves the latest TAI offset via NTP and provides this on request to client applications.

* * *

#### Present Status

Autokey version 2 has been implemented in a wide range of machine architectures and operating systems. It has been tested under actual and simulated attack and recovery scenarios. The current public software distribution for NTPv4 includes Autokey and also a prototype version of the Manycast autonomous configuration scheme described on the companion [Autonomous Configuration](/reflib/autocfg/) page.

All five identity schemes described above have been implemented and tested. At present, the means to activate which one is used in practice lies in the parameters and keys selected during the key generation process. There remains some testing to explore modes of interoperation when different schemes are used by different clients and hosts in the same NTP subnet.

* * *

#### Future Plans

The Autokey technology research and development process is basically mature, although refinements may be expected as the proof of concept phase continues with prototype testing in the Internet. We believe the technology is ready to exploit in other critical environments such as real sensor networks and critical mission command and control systems. However, what needs to be done first is to advance the standards track process.

The Internet draft on the Autokey protocol specification has been under major revision. The latest draft has been submitted to the IETF as a RFC for review. Upon approval, it will be circulated for comment and proposed as draft standard.

* * *

#### Selected Publications

1.  Mills, D.L. The Autokey security architecture, protocol and algorithms. Electrical and Computer Engineering Technical Report 06-1-1, University of Delaware, January 2006, 59 pp. [PDF](/reflib/reports/stime1/stime.pdf)

2.  Adams, C., S. Farrell. Internet X.509 public key infrastructure certificate management protocols. Network Working Group Request for Comments RFC-2510, Entrust Technologies, March 1999, 30 pp.

3.  Housley, R., et al. Internet X.509 public key infrastructure certificate and certificate revocation list (CRL) profile. Network Working Group Request for Comments RFC-3280, RSA Laboratories, April 2002, 129 pp.

4.  Levine, J., and D. Mills. Using the Network Time Protocol to transmit International Atomic Time (TAI). _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PDF](/reflib/papers/leapsecond.pdf)

5.  Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PostScript](/reflib/papers/nano/nano2.ps) | [PDF](/reflib/papers/nano/nano2.pdf), Slides: [PostScript](/reflib/brief/nano/nano.ps) | [PowerPoint](/reflib/brief/nano/nano.ppt)

6.  Mills, D.L. Public key cryptography for the Network Time Protocol. Electrical Engineering Report 00-5-1, University of Delaware, May 2000. 23 pp. Abstract: [PostScript](/reflib/reports/pkey/pkeya.ps) | [PDF](/reflib/reports/pkey/pkeya.pdf), Body: [PostScript](/reflib/reports/pkey/pkeyb.ps) | [PDF](/reflib/reports/pkey/pkeyb.pdf)

7.  Mills, D.L. Cryptographic authentication for real-time network protocols. In: _AMS DIMACS Series in Discrete Mathematics and Theoretical Computer Science, Vol. 45_ (1999), 135-144. Paper: [PostScript](/reflib/papers/dimacs.ps) | [PDF](/reflib/papers/dimacs.pdf), Slides: [PDF](/reflib/brief/dimacs/dimacs.pdf)

8.  Mills, D.L. Authentication scheme for distributed, ubiquitous, real-time protocols. _Proc. Advanced Telecommunications/Information Distribution Research Program (ATIRP) Conference_ (College Park MD, January 1997), 293-298. Paper: [PostScript](/reflib/papers/atirp.ps) | [PDF](/reflib/papers/atirp.pdf), Slides: [PDF](/reflib/brief/atirp/atirp.pdf)

9.  Mills, D.L. Proposed authentication enhancements for the Network Time Protocol version 4. Electrical Engineering Report 96-10-3, University of Delaware, October 1996, 36 pp. Abstract: [PostScript](/reflib/reports/secure/securea.ps) | [PDF](/reflib/reports/secure/securea.pdf), Body: [PostScript](/reflib/reports/secure/secureb.ps) | [PDF](/reflib/reports/secure/secureb.pdf)

10.  Mills, D.L, and A. Thyagarajan. Network time protocol version 4 proposed changes. Electrical Engineering Department Report 94-10-2, University of Delaware, October 1994, 32 pp. Abstract: [PostScript](/reflib/reports/acts/actsa.ps) | [PDF](/reflib/reports/acts/actsa.pdf), Body: [PostScript](/reflib/reports/acts/actsb.ps) | [PDF](/reflib/reports/acts/actsb.pdf)