---
title: "NTP Version 4 Release Notes"
type: archives
---

![gif](/archives/pic/hornraba.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

The rabbit toots to make sure you read this.

This document was last updated 4 May 2001

* * *

#### Table of Contents

*   [NTP Version 4 Release Notes](/archives/4.1.0/release/#ntp-version-4-release-notes)
*   [Nasty Surprises](/archives/4.1.0/release/#nasty-surprises)
*   [Caveats](/archives/4.1.0/release/#caveats)

* * *

#### NTP Version 4 Release Notes

This release of the NTP Version 4 (NTPv4) daemon for Unix, VMS and Windows (NT4 and 2000) incorporates new features and refinements to the NTP Version 3 (NTPv3) algorithms. However, it continues the tradition of retaining backwards compatibility with older versions, except for symmetric mode in NTPv1. Client/server mode continues to be supported in NTPv1. The NTPv4 version has been under development for quite a while and isn't finished yet. In fact, quite a number of NTPv4 features have already been retrofitted in the current NTPv3, although this version is not actively maintained by the NTPv4 developer's group.

The primary purpose of this release is to verify the remaining new code compiles and runs in the various architectures, operating systems and hardware complement that can't be verified here. Of particular interest are Windows 2000, VMS and various reference clock drivers. As always, corrections and bugfixes are warmly received, especially in the form of context diffs.

This note summarizes the differences between this software release of NTPv4, called ntp-4.x.x, and the previous NTPv3 version, called xntp3-5.x.x. Additional information on protocol compatibility details is on the [Protocol Conformance Statement](/archives/4.1.0/biblio) page.

1.  Most calculations are now done using 64-bit floating double format, rather than 64-bit fixed point format. The motivation for this is to reduce size, improve speed and avoid messy bounds checking. Workstations of today are much faster than when the original NTP version was designed in the early 1980s, and it is rare to find a processor architecture that does not support floating double. The fixed point format is still used with raw timestamps, in order to retain the full precision of about 212 picoseconds. However, the algorithms which process raw timestamps all produce fixed point differences before converting to floating double. The differences are ordinarily quite small so can be expressed without loss of accuracy in this format.
2.  The clock discipline algorithm has been redesigned to improve accuracy, reduce the impact of network jitter and allow an increase in poll intervals to well over one day with only moderate sacrifice in accuracy. The NTPv4 design allows servers to increase the poll intervals even when synchronized directly to the peer. In NTPv3 the poll interval in such cases was clamped to the minimum, usually 64 s. For those servers with hundreds of clients, the new design can dramatically reduce the network load.
3.  This release includes support for the [_nanokernel_](/reflib/software/nanokernel.tar.gz) precision time kernel support, which is now in stock Linux and FreeBSD kernels. If a precision time source such as a GPS timing receiver or cesium clock is available, kernel timekeeping can be improved to the order less than one microsecond. The older precision time kernel for the Alpha continues to be supported.
4.  This release includes support for Autokey public-key cryptography, which is the preferred scheme for authenticating servers to clients. It uses NTP header extensions fields documented in: Mills, D.L. Public-Key cryptography for the Network Time Protocol. Internet Draft draft-ietf-stime-ntpauth-00.txt, University of Delaware, June 2000, 36 pp. [ASCII](/reflib/memos/draft-ietf-stime-ntpauth-00.txt) and implemented in this release. The design provides for orderly key refreshment and does not require public keys and related media to be copied from one machine to another. Specific information about Autokey cryptography is contained in the [Authentication Options](/archives/4.1.0/authopt) page and links from there. 
5.  NTPv4 includes two new association modes which in most applications can avoid per-host configuration altogether. Both of these are based on IP multicast technology and Autokey cryptography. They provide for automatic discovery and configuration of servers and clients without identifying servers or clients in advance. In multicast mode a server sends a message at fixed intervals using specified multicast group addresses, while clients listen on these addresses. Upon receiving the message, a client exchanges several messages with the server in order to calibrate the multicast propagation delay between the client and server. In manycast mode a client sends a message to a specified multicast group address and expects one or more servers to reply. Using engineered algorithms, the client selects an appropriate subset of servers from the messages received and continues in ordinary client/server operation. The manycast scheme can provide somewhat better accuracy than the multicast scheme at the price of additional network overhead. See the [Association Management](/archives/4.1.0/assoc) page for further information.
6. There are two burst mode features available where special conditions apply. One of these is enabled by the <tt>iburst</tt> keyword in the <tt>server</tt> configuration command. It is intended for cases where it is important to set the clock quickly when an association is first mobilized. The other is enabled by the <tt>burst</tt> keyword in the <tt>server</tt> configuration command. It is intended for cases where the network attachment requires an initial calling or training procedure. See the [Association Management](/archives/4.1.0/assoc) page for further information.
7. The reference clock driver interface is smaller, more rational and more accurate. Support for pulse-per-second (PPS) signals has been extended to all drivers as an intrinsic function. Most of the drivers in NTPv3 have been converted to this interface, but some, including the PARSE subinterface, have yet to be overhauled. New drivers have been added for several GPS receivers now on the market for a total of 39 drivers. Drivers for the Canadian standard time and frequency station CHU, the US standard time and frequency stations WWV/H and for IRIG signals have been updated and capabilities added to allow direct connection of these signals to the Sun audio port <tt>/dev/audio</tt>.
8. In all except a very few cases, all timing intervals are randomized, so that the tendency for NTPv3 to self-synchronize and bunch messages, especially with a large number of configured associations, is minimized.
9. In NTPv3 a large number of weeds and useless code had grown over the years since the original NTPv1 code was implemented almost twenty years ago. Using a powerful weedwacker, much of the shrubbery has been removed, with effect a substantial reduction in size of almost 40 percent.
10. The entire distribution has been converted to gnu <tt>automake</tt>, which should greatly ease the task of porting to new and different programming environments, as well as reduce the incidence of bugs due to improper handling of idiosyncratic kernel functions.


* * *

#### Nasty Surprises 

There are a few things different about this release that have changed since the latest NTP Version 3 release. Following are a few things to worry about: 

1.  As required by Defense Trade Regulations (DTR), the cryptographic routines supporting the Data Encryption Standard (DES) have been removed from the base distribution. These routines are readily available in most countries from RSA Laboratories. Directions for their use are in the [Building and Installing the Distribution](/archives/4.1.0/build) page.

2.  As the result of the above, the <tt>./authstuff</tt> directory, intended as a development and testing aid for porting cryptographic routines to exotic architectures, has been removed. Developers should note the NTP authentication routines use the interface defined in the <tt>rsaref2.0</tt> package available from RSA laboratories.

3.  The enable and disable commands have a few changes in their arguments see the <tt>ntpd</tt> [Configuration Options](/archives/4.1.0/confopt) page for details. Note that the <tt>authenticate</tt> command has been removed.

4.  The <tt>ppsclock</tt> line discipline/streams module is no longer supported. This function is now handled by the [PPS Clock Discipline](/archives/drivers/driver22) driver, which uses the new PPSAPI application program interface proposed by the IETF. Note that the <tt>pps</tt> configuration file command has been obsoleted by the driver. See the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.1.0/pps) page for further information.

5.  Several new options have been added for the <tt>ntpd</tt> command line. For the inveterate knob twiddlers several of the more important performance variables can be changed to fit actual or perceived special conditions. It is possible to operate the daemon in a one-time mode similar to <tt>ntpdate</tt>, which program is headed for retirement. See the [<tt>ntpd</tt> - Network Time Protocol (NTP) daemon](/archives/4.1.0/ntpd) page for the new features.

6.  To help reduce the level of spurious network traffic due to obsolete configuration files, a special control message called the kiss-of-death packet has been implemented. If enabled and a packet is denied service or exceeds the client limit, a compliant server will send this message to the client. A compliant client will cease further transmission and send a message to the system log. See the [Access Control Options](/archives/4.1.0/accopt) page for further information.

7.  An experimental filter algorithm called huff-n'-puff has been implemented to reduce errors under conditions of severe assymetric delays characteristic of <tt>ppp</tt> connections with telephone modems and downloading or uploading considerable traffic. See the [ntpd - Network Time Protocol (NTP) daemon](/archives/4.1.0/ntpd) page for further information.

* * *

#### Caveats

This release has been compiled and tested on several systems, including SunOS 4.1.3, Solaris 2.5.1-2.8, Alpha 4.0, Ultrix 4.4, Linux, FreeBSD and HP-UX 10.02. It has been compiled and tested on Windows NT, but not yet on any other Windows version or for VMS. We are relying on the NTP volunteer corps to do that. Known problems are summarized below:

1.  The latest NTPv4 <tt>ntpdc</tt> does not work with previous versions of <tt>ntpd</tt> and previous versions of <tt>ntpdc</tt> do not work with latest <tt>ntpd</tt>. This situation is regrettable and may be fixed in future; however, it is necessary in order for the autokey function to retrieve canonical names and certificates from directory services such as Secure DNS.

2.  The precision time support in stock Solaris 2.6 has bugs that were fixed in 2.7. A patch is available that fixes the 2.6 bugs. The 2.6 kernel discipline has been disabled by default. For testing, the kernel can be enabled using the <tt>enable kernel</tt> command either in the configuration file or via <tt>ntpdc</tt>.

3.  The HTML documentation has been partially updated. However, most of the NTPv3 documentation continues to apply to NTPv4. Until the update happens, what you see is what you get. We are always happy to accept comments, corrections and bug reports. However, we are most thrilled upon receipt of patches to fix the dang bugs.