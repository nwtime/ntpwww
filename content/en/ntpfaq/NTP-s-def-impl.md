---
title: "4.3. Implementations and Platforms"
type: "archives"
--- 

This section discusses implementations of NTP for various platforms.

For platforms and operating systems other than those mentioned here, there may be software available. Maybe there are binary program packages available for your computer system. A good starting point is to search this website. Specific products are presented in [Section 8.3](/ntpfaq/ntp-s-trbl-spec/).

4.3.1 [Official Providers](#431-official-providers)    
4.3.2 [UNIX Systems](#432-unix-systems)   
4.3.3 [Microsoft Windows](#433-microsoft-windows)      

* * *

#### 4.3.1 Official Providers

Several national time keepers allow reading the time via NTP:

* [NIST](https://www.nist.gov/time-frequency/) (USA)
* [USNO](https://www.usno.navy.mil/USNO/time/) (USA)
* [PTB](https://www.ptb.de/cms/en/ptb/fachabteilungen/abtq/gruppe-q4/ref-q42/time-synchronization-of-computers-using-the-network-time-protocol-ntp.html) (Germany)

* * *

#### 4.3.2 UNIX Systems

The reference implementation of the NTP client and server is [available for free](/downloads/). The software is available as C source and it runs on most UNIX-compatible operating systems. The software consists of the following components:

ntpd
: A daemon process that is both client and server.

ntpdate
: A utility to set the time once, similar to the popular `rdate` command.

ntpq, ntpdc
: Monitoring and control programs that communicate via UDP with `ntpd`.

ntptrace
: A utility to back-trace the current system time, starting from the local server.

documentation
: The [documentation](/archives/4.2.8-series/) for the software is definitely worth reading.

scripts
: There are also several scripts that might be useful or at least a source of ideas if you want to run and monitor NTP.

* * *

#### 4.3.3 Microsoft Windows

NTP is the default time synchronization protocol used by the Windows Time service in Windows Server 2012 and higher, Windows 10 or later, and Azure Stack HCI. In addition, SNTP support is included for backwards compatibility with older clients. Refer to [How the Windows Time Service Works](https://docs.microsoft.com/en-us/windows-server/networking/windows-time-service/how-the-windows-time-service-works/) for more information.

Meinberg provides a [GUI installer](https://www.meinbergglobal.com/english/sw/ntp.htm#ntp_stable) of the latest NTP version for Window XP and later.