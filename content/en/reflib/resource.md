---
title: "Collaboration Resources"
description: "Following is a hodgepodge of programs and other resources which may be helpful for adventuring in computer network time synchronization."
type: archives
---

![gif](/documentation/pic/panda.gif)

FAX test image for SATNET (1979).

The baby panda was scanned at University College London and used as a FAX test image for a demonstration of the DARPA Atlantic SATNET Program and the first transatlantic Internet connection in 1979. The computing system used for that demonstration was called the [Fuzzball](/reflib/papers/fuzz.pdf). As it happened, this was also the first Internet multimedia presentation and the first to use NTP in regular operation. The image was widely copied and used for testing throughout much of the 1980s.

* * *

#### Table of Contents

*  [Resources for Collaborative Experiments](/reflib/resource/#resources-for-collaborative-experiments)
*  [Software and Documentation Resources](/reflib/resource/#software-and-documentation-resources)
*  [Network Time Protocol (NTP) Version 4](/reflib/resource/#network-time-protocol-ntp-version-4)
*  [The Fuzzball](/reflib/resource/#the-fuzzball)
*  [Precision Radio Clock for WWV Transmissions](/reflib/resource/#precision-radio-clock-for-wwv-transmissions)
*  [Gadget Box Level Converter](/reflib/resource/#gadget-box-level-converter)
*  [Unix Kernel Timekeeping Support](/reflib/resource/#unix-kernel-timekeeping-support)
*  [Spectracom 8170 WWVB Receiver](/reflib/resource/#spectracom-8170-wwvb-receiver)
*  [PSTI/Traconex 1020 WWV/H Receiver](/reflib/resource/#pstitraconex-1020-wwvh-receiver)
*  [LORAN-C Stabilized Precision Oscillator](/reflib/resource/#loran-c-stabilized-precision-oscillator)
*  [ICOM Radio Controller](/reflib/resource/#icom-radio-controller)
*  [MINIMUF Program for HF Radio Propagation Predictions](/reflib/resource/#minimuf-program-for-hf-radio-propagation-predictions)
*  [DSP Software Modem for RTTY and SITOR signals](/reflib/resource/#dsp-software-modem-for-rtty-and-sitor-signals)

* * *

#### Resources for Collaborative Experiments

We participate in many network experiments with our international partners in several countries. Some of these involve ongoing network performance evaluation and measurements with sites all over the world, others have specific goals and designated experiment plans. To support these experiments, we make available workstation and network resources to outside investigators. Some idea of the resources we can provide can be found in the [Internet Research Laboratory](/reflib/lab/) page.

* * *

#### Software and Documentation Resources

Following is a hodgepodge of programs and other resources which may be helpful for adventuring in computer network time synchronization.

In the case of software distributions, we have stashed Unix-friendly (`gz` file extensions) compressed tar archives. Many documents are available in PostScript (`.ps`) and Adobe PDF (`.pdf`) formats. Beware, some of these files, especially the PostScript ones, are rather large.

**Important: Respect the copyright information included in each distribution.**

* * *

#### Network Time Protocol (NTP) Version 4

The Network Time Protocol is used to synchronize clocks in Unix, VMS and Windows systems in an estimated population of over 25 million computers in most countries and all continents of the world. The current NTP Version 4 and previous versions have been used for over 30 year in almost all computer embedded and software systems currently available.

The NTP Version 4 software distribution, documentation and configuration information is available on thisweb site. An extensive review of the technology and application is available on the [Network Time Synchronization Research Project](/reflib/ntp/) page and the white papers in the [Reference Library](/reflib/).

The current NTP Version 4 protocol specification is at

*   Mills, D., J. Martin (Ed.), et al. Network Time Protocol Version 4: protocol and algorithm specification. Request for Comments RFC 5905, Internet Engineering Task Force, June, 2010. [ASCII](/reflib/rfc/rfc5905.txt)
*   Mills, D., B. Haberman (Ed.). Network Time Protocol Version 4: Autokey specification. Request for Comments RFC 5906, Internet Engineering Task Force, June, 2010. [ASCII](/reflib/rfc/rfc5906.txt)

NTP servers and clients can be protected using symmetric key cryptography and algorithms included in the public software distribution. The software distribution can be exported anywhere, since it does not include cryptographic algorithms subject to export control. However, the cryptographic algorithm interface is compatible with the OpenSSL cryptographic library, which is used by many ubiquitous applications, including TLS and SSH. As explained in the documentation, the SSL library can be obtained directly from the https://www.openssl.org web site.

* * *

#### The Fuzzball

[fuzzball.tar.gz](/reflib/software/fuzzball.tar.gz)

This is a compressed archive containing the source code used by the Fuzzball, a prototyping and test system used in the early Internet. The archive consists of four directories containing the source code in PDP11 assembler format. It can be built under the RT-11 operating system, either directly or in simulation. The system is described in:

*   Mills, D.L. The Fuzzball. _Proc. ACM SIGCOMM 88 Symposium_ (Palo Alto CA, August 1988), 115-122. [](/reflib/papers/fuzz.ps)[PDF](/reflib/papers/fuzz.pdf)

* * *

#### Precision Radio Clock for WWV Transmissions

![webp](/documentation/pic/dsp93.webp)

[wwv.tar.gz](/reflib/software/wwv.tar.gz)

This is a program for the DSP-93, a digital signal processor system based on the Texas Instruments TMS320C25 DSP chip. The program works with an inexpensive shortwave receiver to receive, demodulate and decode signals broadcast by NIST radio stations WWV, Ft. Collins, CO, and WWVH, Kauai, HI. The system can provide an ASCII timecode suitable to set the clock on a computer with accuracy less than a millisecond. The principal advantage using the DSP approach is successful operation with very weak signals, such as with an indoor antenna far from the transmitters. Further details are in the technical report:

*   Mills, D.L. A precision radio clock for WWV transmissions. Electrical Engineering Report 97-8-1, University of Delaware, August 1997, 25 pp. Abstract: [PDF](/reflib/reports/wwv/wwva.pdf), Body: [PDF](/reflib/reports/wwv/wwvb.pdf)

* * *

#### Gadget Box Level Converter

![webp](/documentation/pic/gadget.webp) [gadget.tar.Z](/reflib/software/gadget.tar.Z)

This is a compressed archive containing the schematics, artwork and related information for (a) a modem for the Canadian time/frequency radio service CHU, which can be used as a primary reference clock for NTP Version 2 and Version 3 daemons, and (b) a pulse shaper and line driver used to provide an external one-pulse-per-second signal from a radio clock to a serial port. See above and the NTP Version 3 distribution for an example of its use.

* * *

#### Unix Kernel Timekeeping Support

[nanokernel.tar.gz](/reflib/software/nanokernel.tar.gz)

This is a compressed archive containing sample code segments and documentation for Unix kernel modifications which implement a precision, disciplined clock. The sample code segments, which involve no licensed code, can be incorporated in the timer interrupt routine of Unix workstations. Complete kernels with these modifications have been constructed for SunOS, Ultrix, HP-UX, Digital OSF/1 and Linux kernels. Since these modifications involve licensed code, they are available only from the manufacturer's representatives. A technical report is also available:

*   Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PostScript](/reflib/reports/kern/kerna.ps) | [PDF](/reflib/reports/kern/kerna.pdf), Body: [PostScript](/reflib/reports/kern/kernb.ps) | [PDF](/reflib/reports/kern/kernb.pdf) Major revision and update of: Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)

* * *

#### Spectracom 8170 WWVB Receiver

[Schematics](/reflib/8170/8170.pdf)

* * *

#### PSTI/Traconex 1020 WWV/H Receiver

[DIPswitch Settings](/reflib/psti/psti.pdf)

* * *

#### LORAN-C Stabilized Precision Oscillator

[loran.tar.gz](/reflib/software/loran.tar.gz)

![gif](/documentation/pic/loran.gif)

![webp](/documentation/pic/loran1.webp)

**LORAN-C Receiver PC Card and Oscillator Unit**

This is a compressed archive containing the schematics, artwork and documentation for a computer-controlled LORAN-C timing receiver used as a precision source of standard time. The device is designed as an ISA bus peripheral for a PC. It provides a variety of signals useful for calibrating precision time equipment to an accuracy and stability of a few parts in 10<sup>10</sup>. A technical report is available:

*   Mills, D.L. A computer-controlled LORAN-C receiver for precision timekeeping. Electrical Engineering Department Report 92-3-1, University of Delaware, March 1992, 63 pp. Abstract: [PDF](/reflib/reports/loran/lorana.pdf), Body: [PDF](/reflib/reports/loran/loranb.pdf), Appendix A Host Computer Interface: [PDF](/reflib/reports/loran/loranc.pdf), Appendix B Program Listing: [PDF](/reflib/reports/loran/lorand.pdf), Appendix C Schematic Drawings: [PDF](/reflib/reports/loran/lorane.pdf)

* * *

#### ICOM Radio Controller

[icom.tar.gz](/reflib/software/icom.tar.gz)

This is a compressed archive containing a C-language program to control HF/VHF radios made by the ICOM Corporation. It can be used interactively or run from a shell script to adjust the frequency, mode and related parameters of one or more radios connected to the CI-V local network. It can also be used in conjunction with the MINIMUF distribution below to automatically tune radios as propagation conditions change throughout the seasons and hours.

* * *

#### MINIMUF Program for HF Radio Propagation Predictions

[minimuf.tar.gz](/reflib/software/minimuf.tar.gz)

This is a compressed archive containing a C-language program that computes high frequency radio propagation data between two geographic locations on the Earth. It is useful in setting propagation-delay switches on radio clocks. It can be used interactively or in a shell script in conjunction with the ICOM distribution above to automatically tune radios as propagation conditions change throughout the seasons and hours.

* * *

#### DSP Software Modem for RTTY and SITOR signals

[modem.tar.gz](/reflib/software/modem.tar.gz)

This is a compressed archive containing the program and documentation for an advanced linear receiver for radiotelegraph signals. The program is written for the TI TMS320C25 and the DSP-93 digital modem available from the Tucson Amateur Packet Radio organization (TAPR). A technical report is available:

*   Mills, D.L. An optimal linear receiver and codec for a class of radiotelegraph signals. Electrical Engineering Department Report 95-8-1, University of Delaware, August 1995, 91 pp. Abstract: [PDF](/reflib/reports/dsp93/dsp93a.pdf), Body: [PDF](/reflib/reports/dsp93/dsp93b.pdf), Appendix A Operations: [PDF](/reflib/reports/dsp93/dsp93c.pdf), Appendix B RTTY Analysis: [PDF](/reflib/reports/dsp93/dsp93d.pdf), Appendix C DCD Analysis:[PDF](/reflib/reports/dsp93/dsp93e.pdf)