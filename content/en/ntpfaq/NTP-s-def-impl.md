---
title: "4.3. Implementations and Platforms"
type: "archives"
--- 

This section discusses implementations of NTP for various platforms.

For platforms and operating systems other than those mentioned here, there may be software available under different conditions. Maybe there are binary program packages available for your computer system. A good starting point is to search this website (See [Q: 4.3.2.1.](NTP-s-def-impl.htm#Q-NTP-IMPL-UNIX)). Specific issues are presented in [Section 8.3](NTP-s-trbl-spec.htm).

4.3.1. [Official Providers](#official-providers)  
4.3.1.1. [Can I get some Standard Time using NTP?](#can-i-get-some-standard-time-using-ntp)  
4.3.1.2. [Which Protocols are supported by the Reference Implementation?](#which-protocols-are-supported-by-the-reference-implementation)  
4.3.2. [UNIX Systems](#unix-systems)  
4.3.2.1. [Which Implementations are available for UNIX?](#which-implementations-are-available-for-unix)
4.3.3. [Microsoft Windows](#microsoft-windows)  
4.3.3.1. [Is there any built-in Implementation?](#is-there-any-built-in-implementation)  
4.3.3.2. [Are there any other Implementations?](#are-there-any-other-implementations)
4.3.4. [VMS](#vms)  
4.3.4.1. [Which Implementations are available for VMS?](#which-implementations-are-available-for-vms)

* * *

#### 4.3.1. Official Providers

#### 4.3.1.1. Can I get some Standard Time using NTP?

Several national time keepers (NIST and USNO in USA, PTB in Germany) allow reading the time via NTP. See their home pages for details.

* * *

#### 4.3.1.2. Which Protocols are supported by the Reference Implementation?

The reference implementation supports the NTP protocol on port 123. It does not support the Time Protocol ([RFC 868]()) on port 37. NTP is both, newer and more precise than the older protocol.

* * *

#### 4.3.2. UNIX Systems

#### 4.3.2.1. Which Implementations are available for UNIX?

Fortunately there is an implementation of an NTP client and server available for free. The software is available as C source and it runs on most UNIX-compatible operating systems. The software consists of the following components:

ntpd
: A daemon process that is both client and server.

ntpdate
: A utility to set the time once, similar to the popular `rdate` command.

ntpq, ntpdc
: Monitoring and control programs that communicate via UDP with `ntpd`.

ntptrace
: A utility to back-trace the current system time, starting from the local server.

documentation in HTML
: The [documentation](/archives/4.2.8-series) for the software is definitely worth reading.

scripts
: There are also several scripts that might be useful or at least a source of ideas if you want to run and monitor NTP.

* * *

#### 4.3.3. Microsoft Windows

#### 4.3.3.1. Is there any built-in Implementation?

According to [Gilles Vollant](NTP-a-faq.htm#AU-GV), Windows/2000 includes a built-in SNTP client. Follow this procedure:

1.  Select a NTP server, using <code>net time /setsntp:_ntp-server_</code>. However "Only the domain controller that holds the PDC FSMO (Primary Domain Controller Flexible Single Master Operation) role can query an external time source to set the time."

2.  Start the `W32time` service with `net start W32Time`. You can also set the start option of the Windows Time Synchronization Service (`W32Time`) to `Automatic`, so the service will start when Windows/2000 starts.

For further information about NTP in Windows/2000 see:

* http://support.microsoft.com/support/kb/articles/q224/7/99.asp
* http://support.microsoft.com/support/kb/articles/q216/7/34.asp
* http://support.microsoft.com/support/kb/articles/q223/1/84.asp

[Marc Brett](NTP-a-faq.htm#AU-MB) contributed:

A Google search with `"NET TIME /SET /SETSNTP"` yields all sorts of clues, including several Microsoft Knowledgebase articles.
 
You may also want to run a Samba server on your Linux NTP box, and set it up as an SMB time server (`time server = true` in `smb.conf`) so your W2K boxes will find a it automagically.

* * *

#### 4.3.3.2. Are there any other Implementations?

The software discussed in [Which Implementations are available for UNIX?](NTP-s-def-impl.htm#Q-NTP-IMPL-UNIX) has been ported only lately to Windows/NT. Therefore there exists a variety of products to support NTP, most of them are only an NTP client however.

* [TimeServ](http://www.niceties.com/TimeServ.html) or ftp://ftp.microsoft.com/reskit/y2kfix/x86/timeserv/timeserv.htm

* [Tardis](https://www.mingham-smith.com/tardis.htm) is an SNTP client

> XXX _Note from the editor:_ More should be listed here, but isn't.

* * *

#### 4.3.4. VMS

#### 4.3.4.1. Which Implementations are available for VMS?

[Theo Jakobus](NTP-a-faq.htm#AU-TJ) wrote:

TCPIP supports NTP version 3, see http://www.openvms.compaq.com:8000/72final/6526/6526profile_contents_002.html#toc_chapter_10. The configuration is done in `SYS$SPECIFIC:[TCPIP$NTP]TCPIP$NTP.CONF`. I just added different time sources in Germany like: `server ntp.fhg.de server noc.belwue.de`. The service is activated using `$@SYS$MANAGER:TCPIP$CONFIG`. I'm getting the time using NTP and distributing the time to Digital systems using DTSS.