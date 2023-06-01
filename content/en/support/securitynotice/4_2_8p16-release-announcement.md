---
title: "4.2.8p16 Release Announcement"
description: "The NTP Project at Network Time Foundation publicly released NTP 4.2.8p16 on May 30, 2023. This release fixes four security issues and provides 46 bugfixes."
type: archives
---

The NTP Project at Network Time Foundation publicly released ntp-4.2.8p16 on Tuesday, 30 May 2023.

This release fixes two security issues in `ntpd`:

* Low: [Sec 3807: praecis_parse() in ntpd/refclock_palisade.c can write out-of-bounds](/support/securitynotice/ntpbug3807/)
  
  The Praecis reference clock gets time information from 3G CDMA cellphone towers, and relays it to `ntpd` over a serial port. Support for the Praecis refclock was added in November of 2002, before "defensive programming" was the norm. While once a useful means to transmit time, because CDMA signals have better building penetration than GPS, the use of CDMA networks are rapidly dwindling. At one time, there were 59 3G CDMA networks deployed around the world. As of now 49 have already shut down, and 5 of the remaining 10 are scheduled to shut down between now and 2025. The vulnerability described here relies on an attacker gaining physical access to the Praecis unit and, for example, uploading maliciously altered firmware that will send a response line of more than 100 bytes to an unpatched `ntpd` that is configured to get time from that serial connection using the Praecis driver, thus causing an overflow of an internal buffer. 
  
  Reported by Ping Lee (spwpun).

* Low: [Sec 3767: An out-of-bounds KoD RATE ppoll value triggers an assertion abort in debug-enabled ntpd](/support/securitynotice/ntpbug3767/)
  
  By default, the NTP software builds with debugging enabled. We expect most folks who build from source to be using NTP for development purposes, where it makes sense to enable debugging. Similarly, we expect production release engineers to build production releases with debugging disabled. An attacker who has control over an `ntpd` instance the victim queries, or who is "lucky enough" to guess the packet transmit timestamp of an unauthenticated client request and inject their response before the real server responds, can send a response with a KoD (kiss-of-death) RATE packet with an out-of-bounds value that will cause a debug-enabled victim's `ntpd` to abort with an assertion failure. 
        
  Reported by Miroslav Lichvar. 

two security issues in `ntpq`:

* None: [Sec 3808: ntpq will abort with an assertion failure given a malformed RT-11 date](/support/securitynotice/ntpbug3808/)
  
  By default, the NTP software builds with debugging enabled. We expect most folks who build from source to be using NTP for development purposes, where it makes sense to enable debugging. Similarly, we expect production release engineers to build production releases with debugging disabled. An attacker who has control over an `ntpd` instance the victim queries, or who is "lucky enough" to guess the packet transmit timestamp of an unauthenticated client request and inject their response before the real server responds, can send a response with a KoD (kiss-of-death) RATE packet with an out-of-bounds value that will cause a debug-enabled victim's `ntpd` to abort with an assertion failure.
    
  Reported by Miroslav Lichvar. 

* Low: [Sec 3806: libntp/mstolfp() needs bounds checking](/support/securitynotice/ntpbug3806/)
  
  This vulnerability only affects `ntpq` and does **NOT** affect `ntpd`. This vulnerability could have been reported via a single CVE. `ntpq` makes requests of a target `ntpd` from a short-lived random high port and displays the results to the user. An attacker can send a crafted response if they either control the queried `ntpd` or become a "man-in-the-middle" (MITM) on the network path. This crafted response causes a buffer overflow in the victim's `ntpq` client if it consists of a long ASCII character string that matches the pattern: `[+-]DIGIT*[.]DIGIT*`.
  
  Reported by Ping Lee (spwpun). 

adds OpenSSL-3 support, provides 46 bugfixes, and 15 general improvements. 

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.