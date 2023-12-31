---
title: "4.2.6p2 Release Announcement"
description: "The release announcement for NTP 4.2.6p2, which was released on July 9, 2010."
type: archives
date: "2010-07-09"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.6p2, a Point Release of the NTP Reference Implementation from the
NTP Project, is now available.

This release includes build infrastructure updates, code clean-ups, minor bug fixes, fixes for a number of minor ref-clock issues, improved
KOD handling, OpenSSL related updates and documentation revisions.

Portability improvements in this release affect Irix, Linux, Mac OS, Microsoft Windows, OpenBSD and QNX6.

New features / changes in this release include:

* * *

#### ntpd
* Range syntax for the `trustedkey` configuration directive
* Unified IPv4 and IPv6 restrict lists

* * *

#### ntpdate
* Rate limiting and KOD handling

* * *

#### ntpsnmpd
* default connection to `net-snmpd` via a unix-domain socket
* command-line `socket name` option

* * *

#### ntpq / ntpdc
* support for the `passwd ...` syntax
* key-type specific password prompts

* * *

#### sntp
* MD5 authentication of an `ntpd`
* Broadcast and crypto
* OpenSSL support