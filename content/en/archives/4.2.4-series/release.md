---
title: "NTP Version 4 Release Notes"
type: archives
---

![gif](/archives/pic/hornraba.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

The rabbit toots to make sure you read this.

Last update: 19:17 UTC Monday, October 10, 2005

* * *

#### Table of Contents

*   [New Features](/archives/4.2.4-series/release/#new-features)
*   [Nasty Surprises](/archives/4.2.4-series/release/#nasty-surprises)

* * *

This release of the NTP Version 4 (NTPv4) daemon for Unix, VMS and Windows incorporates new features and refinements to the NTP Version 3 (NTPv3) algorithms. However, it continues the tradition of retaining backwards compatibility with older versions, including NTPv3 and NTPv2, but not NTPv1. Support for NTPv1 has been discontinued because of certain security vulnerabilities. The NTPv4 version has been under development for quite a while and isn't finished yet. In fact, quite a number of NTPv4 features have already been retrofitted in the older NTPv3, although this version is not actively maintained by the NTPv4 developer corps.

The code compiles and runs properly in all test host configurations available to the developer corps, including Sun Microsystems, Digital/Compaq, Hewlett Packard, FreeBSD and Linux. Other volunteers have verified it works in IRIX and Windows NT and XP. We invite comments and corrections about the various architectures, operating systems and hardware complement that can't be verified by the developer corps. Of particular interest are other Windows versions, VMS and various reference clock drivers. As always, corrections and bugfixes are warmly received, especially in the form of context diffs sent to [bugs@ntp.org](mailto:bugs@ntp.org).

This release has been compiled and tested on many systems, including SunOS 4.1.3, Solaris 2.5.1-2.10, Alpha Tru64 4.0-5.1, Ultrix 4.4, Linux 2.4.2, FreeBSD 4.5-5.3 and HP-UX 10.02. It has been compiled and tested by others on Windows NT4, 2000 and XP, but not yet on other Windows versions or for VMS. There are several new features apparently incompatible with Linux systems, including some modes used with the Autokey protocol. The developer corps looks for help elsewhere to resolve these differences.

This note summarizes the differences between this software release of NTPv4, called ntp-4.x.x, and the previous NTPv3 version, called xntp3-5.x.x. Additional information on protocol compatibility details is on the [Protocol Conformance Statement](/reflib/biblio/) page.

* * *

#### New Features

1.  Support for the IPv6 addressing family is included in this distribution. If the Basic Socket Interface Extensions for IPv6 (RFC-2553) is detected, support for the IPv6 address family is generated in addition to the default support for the IPv4 address family. Combination IPv6 and IPv4 configurations have been successfully tested in all protocol modes supported by NTP and using both symmetric and public key (Autokey) cryptography. However, users should note that IPv6 support is new and we have not had a lot of experience with it in various operational scenarios and local infrastructure environments. As always, feedback is welcome.

2.  Most calculations are now done using 64-bit floating double format, rather than 64-bit fixed point format. The motivation for this is to reduce size, improve speed and avoid messy bounds checking. Workstations of today are much faster than when the original NTP version was designed in the early 1980s, and it is rare to find a processor architecture that does not support floating double. The fixed point format is still used with raw timestamps, in order to retain the full precision of about 212 picoseconds. However, the algorithms which process raw timestamps all produce fixed point differences before converting to floating double. The differences are ordinarily quite small so can be expressed without loss of accuracy in this format.

3.  The clock discipline algorithm has been redesigned to improve accuracy, reduce the impact of network jitter and allow increased in poll intervals to well over one day with only moderate sacrifice in accuracy.

  *   A new feature called _huffpuff_ maximizes accuracy in cases of highly asymmetric network delays typical of ISDN and modem access circuits.
  *   The NTPv4 design allows clients to increase the poll intervals even when synchronized directly to the server. In NTPv3 the poll interval in such cases was clamped to the minimum, usually 64 s. For those servers with hundreds of clients, the new design can dramatically reduce the network load, especially when large numbers of potential clients, as in national laboratory services.
  *   A scheme designed to reduce "clockhopping" when the choice of servers changes frequently as the result of comparatively insignificant quality changes.

4.  This release includes support for the [_nanokernel_](/reflib/software/nanokernel.tar.gz) precision time kernel support, which is now in stock FreeBSD and optional Linux kernels. If a precision time source such as a GPS timing receiver or cesium clock is available, kernel timekeeping can be improved to the order of one microsecond. The older _microtime_ kernel for Digital/Compaq/HP Tru64, Digital Ultrix, as well as Sun Microsystems SunOS and Solaris, continues to be supported.

5.  This release includes support for Autokey public-key cryptography, which is the preferred scheme for authenticating servers to clients. Autokey Version 2 uses NTP [header extension fields and protocols](/reflib/brief/atirp2/atirp2.pdf). This release includes support for additional message digest and digital signature schemes supported by the OpenSSL software library, as well as new identity schemes based on cryptographic challenge/response algorithms. The new design greatly simplifies key generation and distribution and provides orderly key refreshment. Security procedures and media formats are consistent with industry standard X.509 Version 3 certificates and authority procedures. Specific improvements to the protocol include a reduction in the number of messages required and a method to protect the cookie used in client/server mode against disclosure. Additional information about Autokey cryptography is contained in the [Authentication Options](/archives/4.2.4-series/authopt/) page and links from there. See also the new <code>cryptostats</code> monitoring statistics file in the [Monitoring Options](/archives/4.2.4-series/monopt/) page.

6.  This release includes support for a discrete event simulator (DES), which allows the NTP algorithms to be tested in an embedded environment with systematic and pseudorandom network delay and oscillator wander distributions. This has been used to verify correct operation under conditions of extreme error and misconfiguration. See the [<code>ntpdsim</code> - Network Time Protocol (NTP) simulator](/archives/4.2.4-series/ntpdsim/) page.

7.  NTPv4 includes two new association modes which in most applications can avoid per-host configuration altogether. Both of these are based on IP multicast technology and Autokey cryptography. They provide automatic discovery, configuration and authentication of servers and clients without identifying servers or clients in advance. In multicast mode a server sends a message at fixed intervals using specified multicast group addresses, while clients listen on these addresses.

    Upon receiving the first message, a client exchanges several messages with the server in order to calibrate the multicast propagation delay between the client and server and run the authentication protocol. In manycast mode a client sends a message to a specified multicast group address and expects one or more servers to reply. Using engineered algorithms, the client selects an appropriate subset of servers from the messages received and continues an ordinary client/server campaign. The manycast scheme can provide somewhat better accuracy than the multicast scheme at the price of additional network overhead. See the [Automatic NTP Configuration Options](/archives/4.2.4-series/manyopt/) page for further information.

8.  This release includes support for the orphan mode, which replaces the local clock driver for most configurations. The local clock driver provides a synchronization source for networks not connected to the public Internet or reference clock driver. However, it does not opperate with multiple sources nor multiple failures. The orphan mode provides an automatic, subnet-wide synchronization feature with multiple sources. It can be used in isolated networks or in Internet subnets where the servers or Internet connection have failed. See the [Automatic NTP Configuration Options](/archives/4.2.4-series/manyopt/) page for further information.

9.  This release includes support for preemptable servers, which are provisionally mobilized in manycast mode or by participants in the pool scheme. Manycast mode is described in these notes. In the pool scheme multiple client associations are mobilized for a designated DNS name such as https://www.ntppool.org/en/. The DNS resolver randomizes replies over a set of volunteer service providers. The NTP mitigation algorithms select the best three from among the set and demobilizes the excess. See the [Automatic NTP Configuration Options](/archives/4.2.4-series/manyopt/) page for further information.

10.  There are two burst mode features available where special conditions apply. One of these is enabled by the <code>iburst</code> keyword in the <code>server</code> configuration command. It is intended for cases where it is important to set the clock quickly when an association is first mobilized. The other is enabled by the <code>burst</code> keyword in the <code>server</code> configuration command. It is intended for cases where the network attachment requires an initial calling or training procedure. See the [Association Management](/archives/4.2.4-series/assoc/) page for further information.

11.  The reference clock driver interface is smaller, more rational and more accurate. Support for pulse-per-second (PPS) signals has been extended to all drivers as an intrinsic function. Most of the drivers in NTPv3 have been converted to the NTPv4 interface and continue to operate as before. New drivers have been added for several GPS receivers now on the market for a total of 44 drivers. Audio drivers for the Canadian standard time and frequency station CHU, the US standard time and frequency stations WWV/H and for IRIG signals have been updated and capabilities added to allow direct connection of these signals to a Sun or FreeBSD audio port. See the [Reference Clock Audio Drivers](/archives/4.2.4-series/audio/) page for further information.

12.  In all except a very few cases, all timing intervals are randomized, so that the tendency for NTPv3 to self-synchronize and bunch messages, especially with a large number of configured associations, is minimized.

13.  In NTPv3 a large number of weeds and useless code had grown over the years since the original NTPv1 code was implemented almost twenty years ago. Using a powerful weedwacker, much of the shrubbery has been removed, with effect a substantial reduction in size of almost 40 percent.

14.  The entire distribution has been converted to gnu <code>automake</code>, which should greatly ease the task of porting to new and different programming environments, as well as reduce the incidence of bugs due to improper handling of idiosyncratic kernel functions. Version control is provided by [Bitkeeper](https://bk.ntp.org/).

15.  Several new options have been added for the <code>ntpd</code> command line. For the inveterate knob twiddlers several of the more important performance variables can be changed to fit actual or perceived special conditions. In particular, the tos command can be used to limit the accepted stratum range, specify minimum dispersion increment and maximum selection threshold, and activate orphan mode.

16.  The <code>ntpd</code> daemon can be operated in a one-time mode similar to <code>ntpdate</code>, which program is headed for retirement. See the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/archives/4.2.4-series/ntpd/) page for the new features.

* * *

#### Nasty Surprises

There are a few things different about this release that have changed since the latest NTP Version 3 release. Following are a few things to worry about:

1.  When both IPv4 and IPv6 address families are in use, the host's resolver library may not choose the intended address family if a server has an IPv4 and IPv6 address associated with the same DNS name. The solution is to use the IPv4 or IPv6 address directly in such cases or use another DNS name that resolves to the intended address family. Older versions of <code>ntpdc</code> will only show the IPv4 associations with the <code>peers</code> and other similar commands. Older versions of <code>ntpq</code> will show 0.0.0.0 for IPv6 associations with the <code>peers</code> and other similar commands.

2.  There is a minor change to the reference ID field of the NTP packet header when operating with IPv6 associations. In IPv4 associations this field contains the 32-bit IPv4 address of the server, in order to detect and avoid loops. In IPv6 associations this field contains the first 32-bits of a MD5 hash formed from the address (IPv4 or IPv6) each of the configured associations. Normally, this detail would not be of concern; however, the <code>ntptrace</code> program originally depended on that field in order to display a server traceback to the primary reference source. This program has now been replaced by a script that does the same function, but does not depend on the reference ID field. The <code>ntpdc</code> utility now uses a special version number to communicate with the <code>ntpd</code> server. The server uses this version number to select which address family to used in reply packets. The <code>ntpdc</code> program falls back to the older version behavior when communicating with older NTP versions.

3.  As required by Defense Trade Regulations (DTR), the cryptographic routines supporting the Data Encryption Standard (DES) have been removed from the base distribution of NTPv3. For NTPv4 a new interface has been implemented for the OpenSSL cryptographic library, which is widely available on the web at https://www.openssl.org. This library replaces the library formerly available from RSA Laboratories. Besides being somewhat faster and more widely available, the OpenSSL library supports many additional cryptographic algorithms, which are now selectable at run time. Directions for using OpenSSL are in the [Building and Installing the Distribution](/archives/4.2.4-series/build/) page.

4.  As the result of the above, the <code>./authstuff</code> directory, intended as a development and testing aid for porting cryptographic routines to exotic architectures, has been removed. Testing and conformance validation tools are in the OpenSSL software distrbution.

5.  The NTPv4 enable and disable commands have a few changes in the arguments. See the <code>ntpd</code> [Miscellaneous Options](/archives/4.2.4-series/miscopt/) page for details. Note that the <code>authenticate</code> command has been removed.

6.  To help reduce the level of spurious network traffic due to obsolete configuration files, a special control message called the _kiss-o'-death_ packet has been implemented. If enabled and a packet is denied service or exceeds the client limits, a compliant server will send this message to the client. A compliant client will cease further transmission and send a message to the system log. See the [Access Control Options](/archives/4.2.4-series/accopt/) page for further information.

7.  The <code>tty_clk</code> and <code>ppsclock</code> pulse-per-second (PPS) line discipline/streams modules are no longer supported. The PPS function is now handled by the [PPS Clock Discipline](/archives/drivers/driver22/) driver, which uses the new PPSAPI application program interface adopted by the IETF. Note that the <code>pps</code> configuration file command has been obsoleted by the driver. See the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.4-series/pps/) page for further information.

8.  Support for the NTPv1 symmetric mode has been discontinued, since it hasn't worked for years. Support continues for the NTPv1 client mode, which is used in some SNTP clients.

9.  The precision time support in stock Solaris 2.6 has bugs that were fixed in 2.7. A patch is available that fixes the 2.6 bugs. The 2.6 PPS kernel discipline has been disabled by default. For testing, the kernel can be enabled using the <code>enable kernel</code> command either in the configuration file or via <code>ntpdc</code>.

10.  The HTML documentation has been partially updated. However, most of the NTPv3 documentation continues to apply to NTPv4. Until a comprehensive update happens, what you see is what you get. We are always happy to accept comments, corrections and bug reports. However, we are most thrilled upon receipt of patches to fix the dang bugs. **Please send bug reports to [bugs@ntp.org](mailto:bugs@ntp.org), not the individual members on the team**.
