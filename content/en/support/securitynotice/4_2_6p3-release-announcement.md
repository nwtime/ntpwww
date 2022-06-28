---
title: "4.2.6p3 Release Announcement"
description: "The release announcement for NTP 4.2.6p3, which was released on January 3, 2011."
type: archives
date: "2011-01-03"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.6p3, a Point Release of the NTP Reference Implementation from the NTP
Project, is now available. 

**Focus:** Bug fixes and portability improvements

**Severity:** Medium

This is a recommended upgrade.

This release includes build infrastructure updates, code clean-ups, minor bug fixes, fixes for a number of minor ref-clock issues, and
documentation revisions.

Portability improvements in this release affect AIX, Atari FreeMiNT, FreeBSD4, Linux and Microsoft Windows.

New features / changes in this release:

* * *

#### Build system

* Use `lsb_release` to get information about Linux distributions.
* `test` is in `/usr/bin` (instead of `/bin`) on some systems.
* Basic sanity checks for the `ChangeLog` file.
* Source certain build files with `./filename` for systems without . in `PATH`.
* IRIX portability fix.
* Use a single copy of the `libopts` code.
* `autogen/libopts` upgrade.
* `configure.ac m4` quoting cleanup.

* * *

#### ntpd

* Do not bind to `IN6_IFF_ANYCAST` addresses.
* Log the reason for exiting under Windows.
* Multicast fixes for Windows.
* Interpolation fixes for Windows.
* IPv4 and IPv6 Multicast fixes.
* Manycast solicitation fixes and general repairs.
* JJY refclock cleanup.
* NMEA refclock improvements.
* Oncore debug message cleanup.
* Palisade refclock now builds under Linux.
* Give RAWDCF more baudrates.
* Support Truetime Satellite clocks under Windows.
* Support Arbiter 1093C Satellite clocks under Windows.
* Make sure that the `filegen` configuration command defaults to `enable`.
* Range-check the status codes (plus other cleanup) in the RIPE-NCC driver.
* Prohibit `includefile` directive in remote configuration command.
* Fix `nic` interface bindings.
* Fix the way we link with openssl if openssl is installed in the base system.

* * *

#### ntp-keygen

* Fix `-V` coredump.
* OpenSSL version display cleanup.

* * *

#### ntpdc

* Many counters should be treated as unsigned.

* * *

#### ntpdate

* Do not ignore replies with equal receive and transmit timestamps.

* * *

#### ntpq

* libntpq warning cleanup.

* * *

#### ntpsnmpd

* Correct SNMP type for `precision` and `resolution`.
* Update the MIB from the draft version to [RFC 5907](/reflib/rfc/rfc5907.txt).

* * *

#### sntp

* Display timezone offset when showing time for `sntp` in the local timezone.
* Pay proper attention to RATE KoD packets.
* Fix a miscalculation of the offset.
* Properly parse empty lines in the key file.
* Logging cleanup.
* Use `tv_usec` correctly in `set_time()`.
* Documentation cleanup.