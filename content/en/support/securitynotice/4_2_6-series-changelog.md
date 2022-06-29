---
title: "4.2.6-series Changelog"
description: "The changelogs for NTP versions 4.2.6 through 4.2.6p5."
type: archives
---

* [4.2.6p5](#426p5)
* [4.2.6p4](#426p4)
* [4.2.6p3](#426p3)
* [4.2.6p2](#426p2)
* [4.2.6p1](#426p1)
* [4.2.6](#426)

* * *

#### 4.2.6p5

**Release Date:** 2011 Dec 24

No changes from 4.2.6p5-RC3.

* * *

#### 4.2.6p5-RC3

**Release Date:**  2011 Dec 8

* [Bug 2082: 3-char refid sent by ntpd 4.2.6p5-RC2 ends with extra dot.](https://bugs.ntp.org/show_bug.cgi?id=2082)
* [Bug 2085: clock_update() sys_rootdisp calculation omits root delay.](https://bugs.ntp.org/show_bug.cgi?id=2085)
* [Bug 2086: get_systime() should not offset by sys_residual.](https://bugs.ntp.org/show_bug.cgi?id=2086)
* [Bug 2087: sys_jitter calculation overweights sys.peer jitter.](https://bugs.ntp.org/show_bug.cgi?id=2087)
* Ensure `NULL peer->dstadr` is not accessed in orphan parent selection.

* * *

#### 4.2.6p5-RC2

**Release Date:** 2011 Nov 30

* [Bug 2050: Orphan mode stratum counting to infinity.](https://bugs.ntp.org/show_bug.cgi?id=2050)
* [Bug 2059: optional billboard column `server` does not honor -n.](https://bugs.ntp.org/show_bug.cgi?id=2059)
* [Bug 2066: ntpq lopeers ipv6 "local" column overrun.](https://bugs.ntp.org/show_bug.cgi?id=2066)
* [Bug 2068: ntpd sends nonprintable stratum 16 refid to ntpq.](https://bugs.ntp.org/show_bug.cgi?id=2068)
* [Bug 2069: broadcastclient, multicastclient spin up duplicate ephemeral associations without broadcastdelay.](https://bugs.ntp.org/show_bug.cgi?id=2069)
* [Bug 2072: Orphan parent selection metric needs ntohl().](https://bugs.ntp.org/show_bug.cgi?id=2072)
* Exclude not-yet-determined `sys_refid` from use in loopback TEST12 (from David Mills).
* Never send KoD rate limiting response to `MODE_SERVER` response.

* * *

#### 4.2.6p5-RC1

**Release Date:** 2011 Oct 18

* [Bug 2034: Listening address configuration with prefix misapplied.](https://bugs.ntp.org/show_bug.cgi?id=2034)

* * *

#### 4.2.6p4

**Release Date:** 2011 Sep 22

* [Bug 1984: ntp/libisc fails to compile on OS X 10.7 (Lion).](https://bugs.ntp.org/show_bug.cgi?id=1984)
* [Bug 1985: logconfig =allall rejected.](https://bugs.ntp.org/show_bug.cgi?id=1985)
* [Bug 2001: ntpdc timerstats reports overruns as handled.](https://bugs.ntp.org/show_bug.cgi?id=2001)
* [Bug 2003: libntpq ntpq_read_assoc_peervars() broken.](https://bugs.ntp.org/show_bug.cgi?id=2003)
* **Backward Incompatible** `sntp: -l/--filelog -> -l/--logfile`, to be consistent with `ntpd`.
* `libopts/file.c` fix from Bruce Korb (`arg-type=file`).

* * *

#### 4.2.6p4-RC2

**Release Date:** 2011 Aug 04

* [Bug 1608: Parse Refclock driver should honor trusttime.](https://bugs.ntp.org/show_bug.cgi?id=1608)
* [Bug 1961: html2man update: distribute ntp-wait.html.](https://bugs.ntp.org/show_bug.cgi?id=1961)
* [Bug 1970: UNLINK_EXPR_SLIST() causes crash if list is empty.](https://bugs.ntp.org/show_bug.cgi?id=1970)
* [Bug 1972: checking for struct rtattr fails.](https://bugs.ntp.org/show_bug.cgi?id=1972)
* [Bug 1975: libntp/mktime.c won't work with 64-bit time_t](https://bugs.ntp.org/show_bug.cgi?id=1975)
* [Bug 1978: fix in 4.2.6p4-RC1 doesn't build on older Linux.](https://bugs.ntp.org/show_bug.cgi?id=1978)
* Backport several fixes for Coverity warnings from ntp-dev.
* Backport `if_nametoindex()` check for hpux.

* * *

#### 4.2.6p4-RC1

**Release Date:** 2011 Jul 10

* [Bug 1134: ntpd fails binding to tentative IPv6 addresses.](https://bugs.ntp.org/show_bug.cgi?id=1134)
* [Bug 1790: Update config.guess and config.sub to detect AIX6.](https://bugs.ntp.org/show_bug.cgi?id=1790)
* [Bug 1961: html2man needs an update.](https://bugs.ntp.org/show_bug.cgi?id=1961)
* Update the `NEWS` file.

* * *

#### 4.2.6p4-beta2

**Release Date:** 2011 May 25

* [Bug 1695: ntpdate takes longer than necessary.](https://bugs.ntp.org/show_bug.cgi?id=1695)
* [Bug 1832: ntpdate doesn't allow timeout > 2s.](https://bugs.ntp.org/show_bug.cgi?id=1832)
* [Bug 1933: WWVB/Spectracom driver timestamps LFs, not CRs.](https://bugs.ntp.org/show_bug.cgi?id=1933)
* Backport utility routines from ntp-dev: `mprintf(), emalloc_zero()`.

* * *

#### 4.2.6p4-beta1

**Release Date:** 2011 May 16

* [Bug 1554: peer may stay selected as system peer after becoming unreachable.](https://bugs.ntp.org/show_bug.cgi?id=1554)
* [Bug 1921: LOCAL, ACTS drivers with "prefer" excluded from initial candidate list.](https://bugs.ntp.org/show_bug.cgi?id=1921)
* [Bug 1923: orphan parent favored over LOCAL, ACTS drivers.](https://bugs.ntp.org/show_bug.cgi?id=1923)
* [Bug 1924: Billboard tally codes sometimes do not match operation, variables.](https://bugs.ntp.org/show_bug.cgi?id=1924)
* Enable `tickadj`-like taming of wildly off-spec Windows clock using `NTPD_TICKADJ_PPM` env. var. specifying baseline slew.
* Upgrade to AutoGen 5.11.9 (and require it).
* Upgrade to libopts 35.0.10 from AutoGen 5.11.9pre8.

* * *

#### 4.2.6p3

**Release Date:** 2011 Jan 03

* [Bug 1764: Palisade driver doesn't build on Linux](https://bugs.ntp.org/show_bug.cgi?id=1764)
* Create and use `scripts/check--help` when generating `.texi` files.
* Update `bk` triggers for the bk-5 release.
* Update `genCommitLog` for the bk-5 release.
* Update the copyright year.

* * *

#### 4.2.6p3-RC12

**Release Date:** 2010 Dec 25

* [Bug 1458: Can not compile NTP on FreeBSD 4.7.](https://bugs.ntp.org/show_bug.cgi?id=1458)
* [Bug 1510: Add modes 20/21 for driver 8 to support RAWDCF @ 75 baud.](https://bugs.ntp.org/show_bug.cgi?id=1510)
* [Bug 1618: Unreachable code in jjy_start(). (backport from ntp-dev)](https://bugs.ntp.org/show_bug.cgi?id=1618)
* [Bug 1719: ntp-keygen -V crash. (backport)](https://bugs.ntp.org/show_bug.cgi?id=1719)
* [Bug 1740: ntpdc treats many counters as signed. (backport)](https://bugs.ntp.org/show_bug.cgi?id=1740)
* [Bug 1741: Enable multicast reception on each address (Windows).](https://bugs.ntp.org/show_bug.cgi?id=1741)
* [Bug 1742: Fix a typo in an error message in the "build" script.](https://bugs.ntp.org/show_bug.cgi?id=1742)
* [Bug 1743: Display timezone offset when showing time for sntp in the local timezone.](https://bugs.ntp.org/show_bug.cgi?id=1743)
* [Bug 1751: Support for Atari FreeMiNT OS.](https://bugs.ntp.org/show_bug.cgi?id=1751)
* [Bug 1754: --version output should be more verbose.](https://bugs.ntp.org/show_bug.cgi?id=1754)
* [Bug 1757: oncore snprintf("%m") doesn't expand %m.](https://bugs.ntp.org/show_bug.cgi?id=1757)
* [Bug 1758: setsockopt IPV6_MULTICAST_IF with wrong ifindex.](https://bugs.ntp.org/show_bug.cgi?id=1758)
* [Bug 1760: ntpd Windows interpolation cannot be disabled.](https://bugs.ntp.org/show_bug.cgi?id=1760)
* [Bug 1762: manycastclient solicitation responses interfere.](https://bugs.ntp.org/show_bug.cgi?id=1762)
* Upgrade to libopts 34.0.9 from AutoGen 5.11.6pre7.
* Relax minimum Automake version to 1.10 with updated `libopts.m4`.
* Suppress `ntp-keygen` OpenSSL version display for `--help, --version`, display both build and runtime OpenSSL versions when they differ.
* Clean up `m4` quoting in `configure.ac, *.m4` files, resolving intermittent `AC_LANG_PROGRAM` possibly undefined errors.
* Clean up the SNTP documentation.
* Other manycastclient repairs:
  * Separate handling of scope ID embedded in many `in6_addr` from `ifindex` used for IPv6 multicasting `ioctls`.
  * Add `INT_PRIVACY endpt bit` flag for IPv6 [RFC 4941](https://www.rfc-editor.org/rfc/rfc4941) privacy addresses.
  * Enable outbound multicast from only one address per interface in the same subnet, and in that case prefer embedded MAC address modified
    EUI-64 IPv6 addresses first, then static, and last [RFC 4941](https://www.rfc-editor.org/rfc/rfc4941) privacy addresses.
  * Use `setsockopt(IP[V6]_MULTICAST_IF)` before each send to multicast to select the local source address, using the correct socket is not enough.

* * *

#### 4.2.6p3-RC11

**Release Date:** 2010 Nov 28

* [Bug 1725: ntpd sends multicast from only one address.](https://bugs.ntp.org/show_bug.cgi?id=1725)
* [Bug 1728: In ntp_openssl.m4, don't add -I/usr/include or -L/usr/lib to CPPFLAGS or LDFLAGS.](https://bugs.ntp.org/show_bug.cgi?id=1728)
* [Bug 1733: IRIX doesn't have 'head' (affects scripts/checkChangeLog).](https://bugs.ntp.org/show_bug.cgi?id=1733)
* Remove `log_msg()` and `debug_msg()` from `sntp` in favor of `msyslog()`.
* Use a single copy of `libopts/` in `sntp/`.
* Upgrade libopts to 33.3.8.
* Bump minimum Automake version to 1.11, required for `AM_COND_IF` use in `LIBOPTS_CHECK`.
* Improvements to the `build` script.

* * *

#### 4.2.6p3-RC10

**Release Date:** 2010 Nov 14

* [Bug 1681: More sntp logging cleanup.](https://bugs.ntp.org/show_bug.cgi?id=1681)
* [Bug 1683: Non-localhost on loopback exempted from nic rules.](https://bugs.ntp.org/show_bug.cgi?id=1683)

* * *

#### 4.2.6p3-RC9

**Release Date:** 2010 Nov 10

* [Bug 1574: sntp:set_time doesn't set tv_usec correctly.](https://bugs.ntp.org/show_bug.cgi?id=1574)
* [Bug 1681: sntp logging cleanup.](https://bugs.ntp.org/show_bug.cgi?id=1681)
* [Bug 1683: Interface binding does not seem to work as intended.](https://bugs.ntp.org/show_bug.cgi?id=1683)
* [Bug 1691: Use first NMEA sentence each second.](https://bugs.ntp.org/show_bug.cgi?id=1691)
* [Bug 1692: packageinfo.sh needs to be "sourced" using ./ .](https://bugs.ntp.org/show_bug.cgi?id=1692)
* [Bug 1709: ntpdate ignores replies with equal receive and transmit timestamps.](https://bugs.ntp.org/show_bug.cgi?id=1709)
* Backport `sntp` from -dev

* * *

#### 4.2.6p3-RC8

**Release Date:** 2010 Oct 29

* [Bug 1685: NMEA driver mode byte confusion.](https://bugs.ntp.org/show_bug.cgi?id=1685)
* First cut at using `scripts/checkChangeLog`.

* * *

#### 4.2.6p3-RC7

**Release Date:** 2010 Oct 25

* [Bug 1676: NMEA: $GPGLL did not work after fix for Bug 1571.](https://bugs.ntp.org/show_bug.cgi?id=1676)
* Added `scripts/checkChangeLog`.

* * *

#### 4.2.6p3-RC6

**Release Date:** 2010 Oct 24

* [Bug 1571: NMEA does not relate data to PPS edge.](https://bugs.ntp.org/show_bug.cgi?id=1571)
* [Bug 1572: NMEA time adjustment for GPZDG buggy.](https://bugs.ntp.org/show_bug.cgi?id=1572)
* [Bug 1675: Prohibit includefile remote config.](https://bugs.ntp.org/show_bug.cgi?id=1675)

* * *

#### 4.2.6p3-RC5

**Release Date:** 2010 Oct 22

* [Bug 1649: Require NMEA checksum if $GPRMC or previously seen.](https://bugs.ntp.org/show_bug.cgi?id=1649)
* [Bug 1669: NTP 4.2.6p2 fails to compile on IBM AIX 5.3.](https://bugs.ntp.org/show_bug.cgi?id=1669)

* * *

#### 4.2.6p3-RC4

**Release Date:** 2010 Oct 16

* [Bug 1584: wrong SNMP type for precision, resolution.](https://bugs.ntp.org/show_bug.cgi?id=1584)
* [Bug 1659: Need CLOCK_TRUETIME not CLOCK_TRUE.](https://bugs.ntp.org/show_bug.cgi?id=1659)
* [Bug 1665: is_anycast() u_int32_t should be u_int32.](https://bugs.ntp.org/show_bug.cgi?id=1665)
* `ntpsnmpd, libntpq` warning cleanup.

* * *

#### 4.2.6p3-RC3

**Release Date:** 2010 Oct 14

* [Bug 750: Non-existing device causes coredump with RIPE-NCC driver.](https://bugs.ntp.org/show_bug.cgi?id=750)
* [Bug 1080: ntpd on ipv6 routers very chatty.](https://bugs.ntp.org/show_bug.cgi?id=1080)
* [Bug 1567: Support Arbiter 1093C Satellite Clock on Windows.](https://bugs.ntp.org/show_bug.cgi?id=1567)
* [Bug 1581: printf format string mismatch leftover.](https://bugs.ntp.org/show_bug.cgi?id=1581)
* [Bug 1584: ntpsnmpd OID must be mib-2.197.](https://bugs.ntp.org/show_bug.cgi?id=1584)
* [Bug 1643: Range-check the decoding of the RIPE-NCC status codes.](https://bugs.ntp.org/show_bug.cgi?id=1643)
* [Bug 1644: cvo.sh should use lsb_release to identify linux distros.](https://bugs.ntp.org/show_bug.cgi?id=1644)
* [Bug 1659: Support Truetime Satellite Clocks on Windows.](https://bugs.ntp.org/show_bug.cgi?id=1659)
* [Bug 1660: On some systems, test is in /usr/bin, not /bin.](https://bugs.ntp.org/show_bug.cgi?id=1660)
* [Bug 1661: Re-indent refclock_ripencc.c.](https://bugs.ntp.org/show_bug.cgi?id=1661)

* * *

#### 4.2.6p3-RC2

**Release Date:** 2010 Sep 25

* [Bug 1635: "filegen ... enable" is not default.](https://bugs.ntp.org/show_bug.cgi?id=1635)
* [Bug 1636: yyparse() segfault after denied filegen remote config.](https://bugs.ntp.org/show_bug.cgi?id=1636)

* * *

#### 4.2.6p3-RC1

**Release Date:** 2010 Sep 18

* [Bug 1344: ntpd on Windows exits without logging cause.](https://bugs.ntp.org/show_bug.cgi?id=1344)

* * *

#### 4.2.6p3-beta1

**Release Date:** 2010 Sep 11

* [Bug 1573: Miscalculation of offset in sntp.](https://bugs.ntp.org/show_bug.cgi?id=1573)
* [Bug 1595: empty last line in key file causes duplicate key to be added](https://bugs.ntp.org/show_bug.cgi?id=1595)
* [Bug 1597: packet processing ignores RATE KoD packets, because of a bug in string comparison.](https://bugs.ntp.org/show_bug.cgi?id=1597)
* [Bug 1581: ntp_intres.c size_t printf format string mismatch.](https://bugs.ntp.org/show_bug.cgi?id=1581)

* * *

#### 4.2.6p2

**Release Date:** 2010 Jul 09

* [Bug 1581: size_t printf format string mismatches, IRIG string buffers undersized.  Mostly backported from earlier ntp-dev fixes by Juergen  Perlinger.](https://bugs.ntp.org/show_bug.cgi?id=1581)

* * *

#### 4.2.6p2-RC7

**Release Date:** 2010 Jun 19

* [Bug 1570: serial clock drivers get outdated input from kernel tty line buffer after startup](https://bugs.ntp.org/show_bug.cgi?id=1570)
* [Bug 1575: use 'snprintf' with LIB_BUFLENGTH in inttoa.c, tvtoa.c and utvtoa.c](https://bugs.ntp.org/show_bug.cgi?id=1575)
* [Bug 1576: sys/sysctl.h depends on sys/param.h on OpenBSD.](https://bugs.ntp.org/show_bug.cgi?id=1576)

* * *

#### 4.2.6p2-RC6

**Release Date:** 2010 Jun 12

* [Bug 715: libisc Linux IPv6 interface iteration drops multicast flags.](https://bugs.ntp.org/show_bug.cgi?id=715)

* * *

#### 4.2.6p2-RC5

**Release Date:** 2010 Jun 03

* [Bug 1561: ntpq, ntpdc "passwd" prompts for MD5 password w/SHA1.](https://bugs.ntp.org/show_bug.cgi?id=1561)
* [Bug 1565: sntp/crypto.c compile fails on MacOS over vsnprintf().](https://bugs.ntp.org/show_bug.cgi?id=1565)
* Windows port: do not exit in `ntp_timestamp_from_counter()` without first logging the reason.
* Support `passwd blah` syntax in `ntpq`.

* * *

#### 4.2.6p2-RC4

**Release Date:** 2010 May 19

* [Bug 1555: 4.2.6p2-RC3 sntp illegal C (mixed code and declarations).](https://bugs.ntp.org/show_bug.cgi?id=1555)

* * *

#### 4.2.6p2-RC3

**Release Date:** 2010 May 11

* [Bug 1325: unreachable code in sntp recv_bcst_data().](https://bugs.ntp.org/show_bug.cgi?id=1325)
* [Bug 1459: sntp MD5 authentication does not work with ntpd.](https://bugs.ntp.org/show_bug.cgi?id=1459)
* [Bug 1512: ntpsnmpd should connect to net-snmpd via a unix-domain socket by default.  Provide a command-line 'socket name' option.](https://bugs.ntp.org/show_bug.cgi?id=1512)
* [Bug 1538: update refclock_nmea.c's call to getprotobyname().](https://bugs.ntp.org/show_bug.cgi?id=1538)
* [Bug 1541: Fix wrong keyword for "maxclock".](https://bugs.ntp.org/show_bug.cgi?id=1541)
* [Bug 1552: update and complete broadcast and crypto features in sntp.](https://bugs.ntp.org/show_bug.cgi?id=1552)
* [Bug 1553: sntp/configure.ac OpenSSL support.](https://bugs.ntp.org/show_bug.cgi?id=1553)
* Escape unprintable characters in a `refid` in `ntpq -p` billboard.
* Simplify hash client code by providing OpenSSL `EVP_*()` API when built without OpenSSL.  (from ntp-dev)
* Do not depend on ASCII values for `('A' - '0'), ('a' - '0')` in `sntp`.
* Windows compiling `hints/winnt.html` update from G. Sunil Tej.

* * *

#### 4.2.6p2-RC2

**Release Date:** 2010 Apr 27

* [Bug 1465: Make sure time from TS2100 is not invalid (backport from ntp-dev).](https://bugs.ntp.org/show_bug.cgi?id=1465)
* [Bug 1528: Fix EDITLINE_LIBS link order for ntpq and ntpdc.](https://bugs.ntp.org/show_bug.cgi?id=1528)
* [Bug 1534: win32/include/isc/net.h conflicts with VC++ 2010 errno.h.](https://bugs.ntp.org/show_bug.cgi?id=1534)
* [Bug 1535: "restrict -4 default" and "restrict -6 default" ignored.](https://bugs.ntp.org/show_bug.cgi?id=1535)
* Remove `--with-arlib` from `br-flock`.

* * *

#### 4.2.6p2-RC1

**Release Date:** 2010 Apr 18

* [Bug 1503: Auto-enabling of monitor for "restrict ... limited" wrong.](https://bugs.ntp.org/show_bug.cgi?id=1503)
* [Bug 1504: ntpdate tickles ntpd "discard minimum 1" rate limit if "restrict ... limited" is used.](https://bugs.ntp.org/show_bug.cgi?id=1504)
* [Bug 1518: Windows ntpd should lock to one processor more conservatively.](https://bugs.ntp.org/show_bug.cgi?id=1518)
* [Bug 1522: Enable range syntax "trustedkey (301 ... 399)".](https://bugs.ntp.org/show_bug.cgi?id=1522)
* Update `html/authopt.html controlkey, requestkey`, and `trustedkey` docs.

* * *

#### 4.2.6p1

**Release Date:** 2010 Apr 09

* * *

#### 4.2.6p1-RC6

**Release Date:** 2010 Mar 31

* [Bug 1514: Typo in ntp_proto.c: fabs(foo < .4) should be fabs(foo) < .4.](https://bugs.ntp.org/show_bug.cgi?id=1514)
* [Bug 1464: synchronization source wrong for refclocks ARCRON_MSF (27) and SHM (28).](https://bugs.ntp.org/show_bug.cgi?id=1464)
* Correct Windows port's `refclock_open()` to return 0 on failure, not -1.
* Correct CHU, dumbclock, and WWVB drivers to check for 0 returned from `refclock_open()` on failure.
* Correct `SIMUL=4 ./flock-build -1` to prioritize `-1/--one`.

* * *

#### 4.2.6p1-RC5

**Release Date:** 2010 Feb 09

* [Bug 1140: Clean up debug.html, decode.html, and ntpq.html.](https://bugs.ntp.org/show_bug.cgi?id=1140)
* [Bug 1438: Remove dead code from sntp/networking.c.](https://bugs.ntp.org/show_bug.cgi?id=1438)
* [Bug 1477: 1st non-gmake make in clone w/VPATH can't make COPYRIGHT.](https://bugs.ntp.org/show_bug.cgi?id=1477)
* [Bug 1478: linking fails with undefined reference EVP_MD_pkey_type.](https://bugs.ntp.org/show_bug.cgi?id=1478)
* [Bug 1479: Compilation fails because of not finding readline headers.](https://bugs.ntp.org/show_bug.cgi?id=1479)
* [Bug 1480: snprintf() cleanup caused unterminated refclock IDs.](https://bugs.ntp.org/show_bug.cgi?id=1480)
* [Bug 1484: ushort is not defined in QNX6.](https://bugs.ntp.org/show_bug.cgi?id=1484)

* * *

#### 4.2.6p1-RC4

**Release Date:** 2010 Feb 04

* [Bug 1455: ntpd does not try /etc/ntp.audio as documented.](https://bugs.ntp.org/show_bug.cgi?id=1455)
* [Bug 1467: Fix bogus rebuild of sntp/sntp.html](https://bugs.ntp.org/show_bug.cgi?id=1467)
* [Bug 1470: "make distdir" in $srcdir builds keyword-gen, libntp.a.](https://bugs.ntp.org/show_bug.cgi?id=1470)
* [Bug 1473: "make distcheck" before build can't make sntp/version.m4.](https://bugs.ntp.org/show_bug.cgi?id=1473)
* [Bug 1474: ntp_keygen needs LCRYPTO after libntp.a.](https://bugs.ntp.org/show_bug.cgi?id=1474)
* Convert many `sprintf()` calls to `snprintf()`, also `strcpy(), strcat()`.
* Fix widely cut-n-pasted bug in refclock shutdown after failed start.
* Remove some dead code checking for `emalloc()` returning NULL.
* Remove `arlib`.

* * *

#### 4.2.6p1-RC3

**Release Date:** 2010 Jan 24

* Use `TZ=UTC` instead of `TZ=` when calling `date` in `scripts/mkver.in`.
* [Bug 1448: Some macros not correctly conditionally or absolutely defined on Windows.](https://bugs.ntp.org/show_bug.cgi?id=1448)
* [Bug 1449: ntpsim.h in ntp_config.c should be used conditionally.](https://bugs.ntp.org/show_bug.cgi?id=1449)
* [Bug 1450: Option to exclude warnings not unconditionally defined on Windows.](https://bugs.ntp.org/show_bug.cgi?id=1450)
* [Bug 1127: Properly check the return of X590_verify() - missed one.](https://bugs.ntp.org/show_bug.cgi?id=1127)
* [Bug 1439: .texi generation must wait until after binary is linked.](https://bugs.ntp.org/show_bug.cgi?id=1439)
* [Bug 1440: Update configure.ac to support kfreebsd.](https://bugs.ntp.org/show_bug.cgi?id=1440)
* [Bug 1445: IRIX does not have -lcap or support linux capabilities.](https://bugs.ntp.org/show_bug.cgi?id=1445)
* [Bug 1451: CID 115: sntp leaks KoD entry when updating existing.](https://bugs.ntp.org/show_bug.cgi?id=1451)
* [Bug 1453: Use $CC in config.cache filename in ./build script.](https://bugs.ntp.org/show_bug.cgi?id=1453)

* * *

#### 4.2.6p1-RC2

**Release Date:** 2009 Dec 25

* [Bug 1411: Fix status messages in refclock_oncore.c.](https://bugs.ntp.org/show_bug.cgi?id=1411)
* [Bug 1416: MAXDNAME undefined on Solaris 2.6.](https://bugs.ntp.org/show_bug.cgi?id=1416)
* [Bug 1419: ntpdate, ntpdc, sntp, ntpd ignore configure --bindir.](https://bugs.ntp.org/show_bug.cgi?id=1419)
* [Bug 1424: Fix check for rtattr (rtnetlink.h).](https://bugs.ntp.org/show_bug.cgi?id=1424)
* [Bug 1425: unpeer by association ID sets up for duplicate free().](https://bugs.ntp.org/show_bug.cgi?id=1425)
* [Bug 1426: scripts/VersionName needs . on the search path.](https://bugs.ntp.org/show_bug.cgi?id=1426)
* [Bug 1427: quote missing in ./build - shows up on NetBSD.](https://bugs.ntp.org/show_bug.cgi?id=1427)
* [Bug 1428: Use AC_HEADER_RESOLV to fix breaks from resolv.h](https://bugs.ntp.org/show_bug.cgi?id=1428)
* [Bug 1429: ntpd -4 option does not reliably force IPv4 resolution.](https://bugs.ntp.org/show_bug.cgi?id=1429)
* [Bug 1431: System headers must come before ntp headers in ntp_intres.c .](https://bugs.ntp.org/show_bug.cgi?id=1431)
* [Bug 1434: HP-UX 11 ip_mreq undeclared, _HPUX_SOURCE helps some.](https://bugs.ntp.org/show_bug.cgi?id=1434)
* [Bug 1435: sntp: Test for -lresolv using the same tests as in ntp.](https://bugs.ntp.org/show_bug.cgi?id=1435)

* * *

#### 4.2.6p1-RC1

**Release Date:** 2009 Dec 20

* [Bug 1409: Put refclock_neoclock4x.c under the NTP COPYRIGHT notice. This should allow debian and other distros to add this refclock driver in further distro releases.](https://bugs.ntp.org/show_bug.cgi?id=1409)
*  Detect R2 hardware releases.
* [Bug 1412: m4/os_cflags.m4 caches results that depend on $CC.](https://bugs.ntp.org/show_bug.cgi?id=1412)
* [Bug 1413: test OpenSSL headers regarding -Wno-strict-prototypes.](https://bugs.ntp.org/show_bug.cgi?id=1413)
* [Bug 1414: Enable "make distcheck" success with BSD make.](https://bugs.ntp.org/show_bug.cgi?id=1414)
* [Bug 1415: Fix Mac OS X link problem.](https://bugs.ntp.org/show_bug.cgi?id=1415)
* [Bug 1418: building ntpd/ntpdc/ntpq statically with ssl fails.](https://bugs.ntp.org/show_bug.cgi?id=1418)
* Build infrastructure updates to enable beta releases of ntp-stable.

* * *

#### 4.2.6

**Release Date:** 2009 Dec 09

* [Sec 1331: DoS with mode 7 packets.](/support/securitynotice/ntpbug1331/) (from4.2.4p8)

* * *

* CID 113: use `va_end()` in `refclock_true.c true_debug()`.
* CID 105, 106: ensure `ntpdc` arrays are not overrun even if callers misbehave.
* CID 101: pointer/array cleanup.
* CIDs 94-99: make it more clearly impossible for `sock_hash()` to return a negative number.
* CID 87: dead code in `ntpq.c atoascii()`.
* CID 83: added assertion to demonstrate `config_nic_rules()` does not call `strchr(NULL, '/')`.
* CID 81: `savedconfig` leaked in `save_config()`.
* CID 80: attempt to quiet Coverity false positive re: leaking "reason" in `main()`.
* CID 79: `kod_init_kod_db()` fails to `fclose(db_s)` in two error paths.
* Fix CID 72, a typo introduced at the latest fix to prettydate.c.
* CID 10: missing `free(up);` in `refclock_palisade.c` error return, again.


* * *

* [Bug 1400](https://bugs.ntp.org/show_bug.cgi?id=1400): An empty KOD DB file causes `sntp` to coredump.
* [Bug 1397](https://bugs.ntp.org/show_bug.cgi?id=1397): `shmget() refclock_shm` failing because of file mode.
* [Bug 1392](https://bugs.ntp.org/show_bug.cgi?id=1392): `intres` retries duplicate assocations endlessly.
* [Bug 1391](https://bugs.ntp.org/show_bug.cgi?id=1391): avoid invoking autogen twice for `.c` and `.h` files.
* [Bug 1389](https://bugs.ntp.org/show_bug.cgi?id=1389): buffer overflow in `refclock_oncore.c`
* [Bug 1387](https://bugs.ntp.org/show_bug.cgi?id=1387): Storage leak in `ntp_intres` (minor).
* [Bug 1386](https://bugs.ntp.org/show_bug.cgi?id=1386): Deferred DNS doesn't work on NetBSD
* [Bug 1384](https://bugs.ntp.org/show_bug.cgi?id=1384): `ntpq :config` core dumped with a blank password.
* [Bug 1382](https://bugs.ntp.org/show_bug.cgi?id=1382): p245 `configure --disable-dependency-tracking` won't build.
* [Bug 1381](https://bugs.ntp.org/show_bug.cgi?id=1381)L Version `.deps` generated include file dependencies to allow known dependency-breaking changes to force `.deps` to be cleaned, triggered by changing the contents of `deps-ver` and/or `sntp/deps-ver`.
* [Bug 1378](https://bugs.ntp.org/show_bug.cgi?id=1378): Unnecessary resetting of peers during interface update.
* [Bug 1376](https://bugs.ntp.org/show_bug.cgi?id=1376): Enable authenticated `ntpq` and `ntpdc` using newly-available digest types.
* [Bug 1371](https://bugs.ntp.org/show_bug.cgi?id=1371): deferred DNS lookup failing with `INFO_ERR_AUTH`.
* [Bug 1368](https://bugs.ntp.org/show_bug.cgi?id=1368): typos in `libntp --without-crypto` case
* [Bug 1366](https://bugs.ntp.org/show_bug.cgi?id=1366): `ioctl(TIOCSCTTY, 0)` fails on NetBSD *[0-2].* > 3.99.7.
* [Bug 1364](https://bugs.ntp.org/show_bug.cgi?id=1364): `clock_gettime()` not detected, need `-lrt` on Debian 5.0.3.
* [Bug 1363](https://bugs.ntp.org/show_bug.cgi?id=1363): CID 92 clarify fallthrough case in `clk_trimtsip.c`
* [Bug 1359](https://bugs.ntp.org/show_bug.cgi?id=1359): Debug message cleanup.
* [Bug 1358](https://bugs.ntp.org/show_bug.cgi?id=1358): AIX 4.3 `sntp/networking.c IPV6_JOIN_GROUP` undeclared.
* [Bug 1357](https://bugs.ntp.org/show_bug.cgi?id=1357): bogus assert from `refclock_shm`.
* [Bug 1356](https://bugs.ntp.org/show_bug.cgi?id=1356): core dump from `refclock_nmea` when can't open `/dev/gpsU`.
* [Bug 1355](https://bugs.ntp.org/show_bug.cgi?id=1355): ntp-dev won't compile on OpenBSD 4.6.
* [Bug 1354](https://bugs.ntp.org/show_bug.cgi?id=1354): libtool error building after bootstrap with Autoconf 2.64.
* [Bug 1353](https://bugs.ntp.org/show_bug.cgi?id=1353): `ntpq rv 0 settimeofday` always shows UNKNOWN on unix.
* [Bug 1347](https://bugs.ntp.org/show_bug.cgi?id=1347): `ntpd/complete.conf` missing multicastclient test case.
* [Bug 1346](https://bugs.ntp.org/show_bug.cgi?id=1346): keyword scanner broken where char defaults to unsigned.
* [Bug 1345](https://bugs.ntp.org/show_bug.cgi?id=1345): illegal `grep` option prevents compilation.
* [Bug 1343](https://bugs.ntp.org/show_bug.cgi?id=1343): `sntp` illegal C does not compile on Solaris 7.
* [Bug 1342](https://bugs.ntp.org/show_bug.cgi?id=1342): ignore|drop one IPv6 address on an interface blocks all addresses on that interface.
* [Bug 1341](https://bugs.ntp.org/show_bug.cgi?id=1341): NMEA driver requires working PPSAPI `#ifdef HAVE_PPSAPI`.
* [Bug 1339](https://bugs.ntp.org/show_bug.cgi?id=1339): redux, use unmodified `lib/isc/win32/strerror.c` and move `#define strerror...` to a header not used by `lib/isc` code.
* [Bug 1337](https://bugs.ntp.org/show_bug.cgi?id=1337): cast `setsockopt()` v4 address pointer to `void *`.
* [Bug 1335](https://bugs.ntp.org/show_bug.cgi?id=1335): Broadcast client degraded by wildcard default change.
* [Bug 1334](https://bugs.ntp.org/show_bug.cgi?id=1334): `ntpsnmpd` undefined reference to `ntpqOptions`.
* [Bug 1333](https://bugs.ntp.org/show_bug.cgi?id=1333): `ntpd --interface` precedence over `--novirtualips` lost.
* [Bug 1332](https://bugs.ntp.org/show_bug.cgi?id=1332): <code>ntpq -c 'rv 0 variablename'</code> returns extra stuff.
* [Bug 1330](https://bugs.ntp.org/show_bug.cgi?id=1330): disallow interface/nic rules when `--novirtualips` or `--interface` are used.
* [Bug 1327](https://bugs.ntp.org/show_bug.cgi?id=1327): `ntpq, ntpdc, ntp-keygen -d` & `-D` should work with `configure --disable-debugging`.
* [Bug 1324](https://bugs.ntp.org/show_bug.cgi?id=1324): support bracketed IPv6 numeric addresses for `restrict`.
* [Bug 1323](https://bugs.ntp.org/show_bug.cgi?id=1323): Implement `revoke #` to match documentation, deprecate `crypto revoke #`.
* [Bug 1321](https://bugs.ntp.org/show_bug.cgi?id=1321): build doesn't work if `.` isn't on `$PATH`.
* [Bug 1318](https://bugs.ntp.org/show_bug.cgi?id=1318): Allow multiple -`g` options on `ntpd` command line.
* [Bug 1317](https://bugs.ntp.org/show_bug.cgi?id=1317): Distribute `cvo.sh`.
* [Bug 1316](https://bugs.ntp.org/show_bug.cgi?id=1316): segfault if `refclock_nmea` can't open file.
* [Bug 1315](https://bugs.ntp.org/show_bug.cgi?id=1315): `interface ignore 0.0.0.0` is ignored.
* [Bug 1314](https://bugs.ntp.org/show_bug.cgi?id=1314): `saveconfig` emits `-4` and `-6` on when not given.
* [Bug 1312](https://bugs.ntp.org/show_bug.cgi?id=1312): `ntpq/ntpdc` MD5 passwords truncated to 8 chars on Suns.
* [Bug 1311](https://bugs.ntp.org/show_bug.cgi?id=1311): 4.2.5p211 doesn't build in no-debug mode.
* [Bug 1310](https://bugs.ntp.org/show_bug.cgi?id=1310): fix Thunderbolt mode in `refclock_palisade.c`
* [Bug 1308](https://bugs.ntp.org/show_bug.cgi?id=1308): support systems that lack `fork()`.
* [Bug 1303](https://bugs.ntp.org/show_bug.cgi?id=1303): remove top-level `autokey` directive.
* [Bug 1302](https://bugs.ntp.org/show_bug.cgi?id=1302): OpenSSL under Windows needs `applink` support.
* [Bug 1300](https://bugs.ntp.org/show_bug.cgi?id=1300): reject remote configuration of dangerous items.
* [Bug 1297](https://bugs.ntp.org/show_bug.cgi?id=1297): `yylex()` must always set `yylval` before returning.
* [Bug 1296](https://bugs.ntp.org/show_bug.cgi?id=1296): Added Support for Trimble Acutime Gold.
* [Bug 1295](https://bugs.ntp.org/show_bug.cgi?id=1295): leftover fix, do not crash on exit in `free_config_trap()` when `trap 1.2.3.4` is used without any further options.
* [Bug 1294](https://bugs.ntp.org/show_bug.cgi?id=1294): Use `OPENSSL_INC` and `OPENSSL_LIB` macros for Windows and remove unnecessary reference to `applink.c` for Windows
* [Bug 1293](https://bugs.ntp.org/show_bug.cgi?id=1293): make configuration dumper ready for release
* [Bug 1292](https://bugs.ntp.org/show_bug.cgi?id=1292): Workaround last VC6 unsigned `__int64` kink.
* [Bug 1290](https://bugs.ntp.org/show_bug.cgi?id=1290): Fix to use `GETTIMEOFDAY` macro
* [Bug 1289](https://bugs.ntp.org/show_bug.cgi?id=1289): Update project files for VC6, VS2003, VS2005, VS 2008
* [Bug 1286](https://bugs.ntp.org/show_bug.cgi?id=1286): `dumpcfg` omits `statsdir`, mangles `filegen`.
* [Bug 1285](https://bugs.ntp.org/show_bug.cgi?id=1285): Log `ntpq :config/config-from-file` events.
* [Bug 1284](https://bugs.ntp.org/show_bug.cgi?id=1284): infinite loop in `ntpd` dumping more than one `trustedkey`
* [Bug 1283](https://bugs.ntp.org/show_bug.cgi?id=1283): default to remembering KoD in `sntp`.
* [Bug 1281](https://bugs.ntp.org/show_bug.cgi?id=1281): Build `ntpd` on Windows without big SDK download, burn, and install by checking in essentially unchanging `messages.mc` build products to avoid requiring `mc.exe`, which is not included with VC++ 2008 EE.
* [Bug 1279](https://bugs.ntp.org/show_bug.cgi?id=1279): Cleanup for warnings from Veracode static analysis.
* [Bug 1276](https://bugs.ntp.org/show_bug.cgi?id=1276): CID 52: `crypto_xmit()` may call `crypto_alice[23]()` with NULL peer.
* [Bug 1275](https://bugs.ntp.org/show_bug.cgi?id=1275): CID 45, CID 46: old `sntp` uses uninitialized `guesses[0], precs[0]`.
* [Bug 1274](https://bugs.ntp.org/show_bug.cgi?id=1274): CID 67: ensure `resolve_hosts()` output count and pointers are consistent.
* [Bug 1273](https://bugs.ntp.org/show_bug.cgi?id=1273): CID 10: Palisade leaks unit struct in error path.
* [Bug 1272](https://bugs.ntp.org/show_bug.cgi?id=1272): `gsoc_sntp` IPv6 build problems under HP-UX 10.
* [Bug 1270](https://bugs.ntp.org/show_bug.cgi?id=1270): CID 70: `gsoc_sntp recv_bcst_data mdevadr.ipv6mr_interface` uninitialized.
* [Bug 1269](https://bugs.ntp.org/show_bug.cgi?id=1269): CID 74: use assertion to ensure `move_fd()` does not return negative descriptors.
* [Bug 1268](https://bugs.ntp.org/show_bug.cgi?id=1268): CID 63: `resolve_hosts()` leaks error message buffer.
* [Bug 1267](https://bugs.ntp.org/show_bug.cgi?id=1267): CID 44: old `sntp handle_saving()` writes stack garbage to file when clearing.
* [Bug 1266](https://bugs.ntp.org/show_bug.cgi?id=1266): CID 39: `datum_pts_start()` uninitialized `arg.c_ospeed`.
* [Bug 1265](https://bugs.ntp.org/show_bug.cgi?id=1265): CID 65: CID 66: `gsoc_sntp on_wire()` leaks `x_pkt, r_pkt`.
* [Bug 1264](https://bugs.ntp.org/show_bug.cgi?id=1264): CID 64: `gsoc_sntp on_wire()` frees wrong ptr receiving KoD.
* [Bug 1263](https://bugs.ntp.org/show_bug.cgi?id=1263): CID 37, CID 38m CID 40, CID 43: multiple refclocks uninitialized `tm_zone (arc, chronolog, dumbclock, pcf`).
* [Bug 1262](https://bugs.ntp.org/show_bug.cgi?id=1262): CID 35: `xpkt.mac` uninitialized in `simulate_server()`.
* [Bug 1261](https://bugs.ntp.org/show_bug.cgi?id=1261): CID 34: `simulate_server() rbuf.msg_flags` uninitialized.
* [Bug 1260](https://bugs.ntp.org/show_bug.cgi?id=1260): CID 60: `gsoc_sntp recvpkt()` fails to `free(rdata)`.
* [Bug 1259](https://bugs.ntp.org/show_bug.cgi?id=1259): CID 59: `gsoc_sntp recv_bcast_data()` fails to `free(rdata)` on error paths.
* [Bug 1258](https://bugs.ntp.org/show_bug.cgi?id=1258): CID 54: `gsoc_sntp resolve_hosts()` needs simplification.
* [Bug 1257](https://bugs.ntp.org/show_bug.cgi?id=1257): CID 57: `gsoc_sntp auth_init()` fails to `fclose(keyfile)`.
* [Bug 1256](https://bugs.ntp.org/show_bug.cgi?id=1256): CID 51: Coverity doesn't recognize our assertion macros as terminal.
* [Bug 1255](https://bugs.ntp.org/show_bug.cgi?id=1255): CID 55: `pkt_output()` leaks a copy of each packet.
* [Bug 1254](https://bugs.ntp.org/show_bug.cgi?id=1254): CID 56: `tv_to_str()` leaks a `struct` to each call.
* [Bug 1253](https://bugs.ntp.org/show_bug.cgi?id=1253): CID 50: `gsoc_sntp/crypto.c auth_init()` always returns a list with one entry.
* [Bug 1252](https://bugs.ntp.org/show_bug.cgi?id=1252): PPSAPI cleanup on `ntpd/refclock_wwvb.c`.
* [Bug 1251](https://bugs.ntp.org/show_bug.cgi?id=1251): CID 68: `search_entry()` mishandles `dst` argument.
* [Bug 1250](https://bugs.ntp.org/show_bug.cgi?id=1250): CID 53: `kod_init_kod_db()` overruns `kod_db malloc`'d buffer.
* [Bug 1248](https://bugs.ntp.org/show_bug.cgi?id=1248): `RES_MSSNTP` typo in `ntp_proto.c`.
* [Bug 1246](https://bugs.ntp.org/show_bug.cgi?id=1246): use a common template for singly-linked lists, convert most doubly-linked lists to singly-linked.
* [Bug 1245](https://bugs.ntp.org/show_bug.cgi?id=1245): Broken xmt time sent in `fast_xmit()` of 4.2.5p187.
* [Bug 1244](https://bugs.ntp.org/show_bug.cgi?id=1244): `NTP_INSIST(fd != maxactivefd)` failure in `intres` child
* [Bug 1243](https://bugs.ntp.org/show_bug.cgi?id=1243): `MD5auth_setkey` zero-fills key from first zero octet.
* [Bug 1242](https://bugs.ntp.org/show_bug.cgi?id=1242): Remove `--enable-wintime`, symmetric workaround is now always enabled.
* [Bug 1238](https://bugs.ntp.org/show_bug.cgi?id=1238): use only `fudge time2` to offset NMEA serial timestamp.
* [Bug 1237](https://bugs.ntp.org/show_bug.cgi?id=1237): Windows serial code treat `CR` and `LF` both as line terminators.
* [Bug 1236](https://bugs.ntp.org/show_bug.cgi?id=1236): Declaration order fixed.
* [Bug 1234](https://bugs.ntp.org/show_bug.cgi?id=1234): convert NMEA driver to use common PPSAPI code.
* [Bug 1233](https://bugs.ntp.org/show_bug.cgi?id=1233): atom refclock `fudge time1` sign flipped in 4.2.5p164.
* [Bug 1231](https://bugs.ntp.org/show_bug.cgi?id=1231): `ntpsnmpd` build fails after `sockaddr` union changes.
* [Bug 1229](https://bugs.ntp.org/show_bug.cgi?id=1229): `autokey` segfaults in `cert_install()`.
* [Bug 1226](https://bugs.ntp.org/show_bug.cgi?id=1226): Fix deferred DNS lookups.
* [Bug 1225](https://bugs.ntp.org/show_bug.cgi?id=1225): Broadcast address miscalculated on Windows 4.2.5p180
* [Bug 1218](https://bugs.ntp.org/show_bug.cgi?id=1218): Correct comment in `refclock_oncore` on `/etc/ntp.oncore*` configuration file search order.
* [Bug 1215](https://bugs.ntp.org/show_bug.cgi?id=1215): unpeer by association ID
* [Bug 1211](https://bugs.ntp.org/show_bug.cgi?id=1211): `keysdir free()`'d twice `#ifdef DEBUG`
* [Bug 1210](https://bugs.ntp.org/show_bug.cgi?id=1210): ONCORE driver terminates `ntpd` without logging a reason.
* [Bug 1208](https://bugs.ntp.org/show_bug.cgi?id=1208): `decodenetnum()` buffer overrun on `[ with no ]`
* [Bug 1206](https://bugs.ntp.org/show_bug.cgi?id=1206): Required compiler changes for Windows
* [Bug 1205](https://bugs.ntp.org/show_bug.cgi?id=1205): Add `ntpd --usepcc` and `--pccfreq` options on Windows
* [Bug 1204](https://bugs.ntp.org/show_bug.cgi?id=1204): Unix-style refclock device paths on Windows
* [Bug 1200](https://bugs.ntp.org/show_bug.cgi?id=1200): Enable IPv6 in Windows port
* [Bug 1196](https://bugs.ntp.org/show_bug.cgi?id=1196): `setsockopt(SO_EXCLUSIVEADDRUSE)` can fail on Windows 2000 and earlier with `WSAINVAL`, do not log a complaint in that case.
* [Bug 1193](https://bugs.ntp.org/show_bug.cgi?id=1193): Compile error: conflicting types for `emalloc`.
* [Bug 1192](https://bugs.ntp.org/show_bug.cgi?id=1192): `restrict -6 ...` reports a syntax error.
* [Bug 1190](https://bugs.ntp.org/show_bug.cgi?id=1190): NMEA refclock `fudge flag4 1` obscures position in timecode
* [Bug 1184](https://bugs.ntp.org/show_bug.cgi?id=1184): `ntpd` is deaf when restricted to second IP on the same net
* [Bug 1183](https://bugs.ntp.org/show_bug.cgi?id=1183): COM port support should extend past COM3
* [Bug 1182](https://bugs.ntp.org/show_bug.cgi?id=1182): Documentation typos and missing bits.
* [Bug 1180](https://bugs.ntp.org/show_bug.cgi?id=1180): `ntpd` won't start with more than ~1000 interfaces
* [Bug 1179](https://bugs.ntp.org/show_bug.cgi?id=1179): point out the problem with `-i/--jaildir` and `-u/--user` when they are disabled by `configure`.
* [Bug 1176](https://bugs.ntp.org/show_bug.cgi?id=1176): `refclock_parse.c` does not compile without PPSAPI.
* [Bug 1175](https://bugs.ntp.org/show_bug.cgi?id=1175): Instability in PLL daemon mode.
* [Bug 1174](https://bugs.ntp.org/show_bug.cgi?id=1174): `nmea_shutdown` assumes that nmea has a unit assigned
* [Bug 1173](https://bugs.ntp.org/show_bug.cgi?id=1173): NMEA refclock fails with Solaris PPSAPI
* [Bug 1171](https://bugs.ntp.org/show_bug.cgi?id=1171): line editing libs found without headers (Solaris 11)
* [Bug 1169](https://bugs.ntp.org/show_bug.cgi?id=1169): quiet compiler warnings
* [Bug 1166](https://bugs.ntp.org/show_bug.cgi?id=1166): Remove truncation of position (blanking) code in `refclock_nmea.c`
* [Bug 1165](https://bugs.ntp.org/show_bug.cgi?id=1165): Clean up small memory leaks in the config file parser
* [Bug 1161](https://bugs.ntp.org/show_bug.cgi?id=1161): `unpeer` AKA `unconfig` command for `ntpq :config`
* [Bug 1159](https://bugs.ntp.org/show_bug.cgi?id=1159): `ntpq` overlap diagnostic message test buggy
* [Bug 1154](https://bugs.ntp.org/show_bug.cgi?id=1154): mDNS registration should be done later, repeatedly and only if asked for.
* [Bug 1153](https://bugs.ntp.org/show_bug.cgi?id=1153): `refclock_nmea` should not mix UTC with GPS time
* [Bug 1152](https://bugs.ntp.org/show_bug.cgi?id=1152): adjust PARSE to new `refclock_pps` logic
* [Bug 1148](https://bugs.ntp.org/show_bug.cgi?id=1148): NMEA reference clock improvements
* [Bug 1142](https://bugs.ntp.org/show_bug.cgi?id=1142): `nodebug` builds shed no light on `-d, -D` option failure.
* [Bug 1141](https://bugs.ntp.org/show_bug.cgi?id=1141): `refclock_report` missing braces cause spurious `peer event: clock clk_unspec` log entries
* [Bug 1135](https://bugs.ntp.org/show_bug.cgi?id=1135): `ntpq` uses `sizeof(u_long)` where `sizeof(u_int32)` is meant.
* [Bug 1125](https://bugs.ntp.org/show_bug.cgi?id=1125): C runtime per-thread initialization on Windows
* [Bug 1121](https://bugs.ntp.org/show_bug.cgi?id=1121): [CID 47] double `fclose()` in `ntp-keygen.c`.
* [Bug 1120](https://bugs.ntp.org/show_bug.cgi?id=1120): [CID 51] INSIST that peer is non-null before we dereference it.
* [Bug 1119](https://bugs.ntp.org/show_bug.cgi?id=1119): [CID 52] Avoid a possible null-dereference in `ntp_crypto.c`.
* [Bug 1118](https://bugs.ntp.org/show_bug.cgi?id=1118): Fixed sign extension for 32 bit `time_t` in `caljulian()` and `prettydate()`.
* [Bug 1103](https://bugs.ntp.org/show_bug.cgi?id=1103): Fix 64-bit issues in the new calendar code.
* [Bug 1099](https://bugs.ntp.org/show_bug.cgi?id=1099): Fixed wrong behaviour in `sntp`'s `crypto.c`.
* [Bug 1095](https://bugs.ntp.org/show_bug.cgi?id=1095): overflow in `caljulian.c`.
* [Bug 1090](https://bugs.ntp.org/show_bug.cgi?id=1090): Fix bogus leap seconds in r`efclock_hpgps`.
* [Bug 1084](https://bugs.ntp.org/show_bug.cgi?id=1084): PPSAPI for `ntpd` on Windows with DLL backends
* [Bug 1078](https://bugs.ntp.org/show_bug.cgi?id=1078): `statsdir` configuration parsing is broken.
* [Bug 1072](https://bugs.ntp.org/show_bug.cgi?id=1072): clock_update should not allow updates older than `sys_epoch`.
* [Bug 1070](https://bugs.ntp.org/show_bug.cgi?id=1070): Fix use of `ntpq_parsestring()` in `ntpsnmpd`.
* [Bug 1069](https://bugs.ntp.org/show_bug.cgi?id=1069): `#undef netsnmp`'s `PACKAGE_*` macros.
* [Bug 1068](https://bugs.ntp.org/show_bug.cgi?id=1068): Older versions of `netsnmp` do not have `netsnmp_daemonize()`.
* [Bug 1067](https://bugs.ntp.org/show_bug.cgi?id=1067): Multicast DNS service registration must come after the fork on Solaris.
* [Bug 1066](https://bugs.ntp.org/show_bug.cgi?id=1066): Error messages should log as errors.
* [Bug 1065](https://bugs.ntp.org/show_bug.cgi?id=1065): Re-enable support for the `timingstats` file.
* [Bug 1064](https://bugs.ntp.org/show_bug.cgi?id=1064): Implement `--with-net-snmp-config=progname`
* [Bug 1063](https://bugs.ntp.org/show_bug.cgi?id=1063): `ntpSnmpSubagentObject.h` is missing from the distribution.
* [Bug 1062](https://bugs.ntp.org/show_bug.cgi?id=1062): Check `net-snmp` headers before deciding to build `ntpsnmpd`.
* [Bug 1057](https://bugs.ntp.org/show_bug.cgi?id=1057): `ntpdc unconfig` failure
* [Bug 1052](https://bugs.ntp.org/show_bug.cgi?id=1052): Add linuxPPS support to ONCORE driver.
* [Bug 1047](https://bugs.ntp.org/show_bug.cgi?id=1047): enable/disable options processing fix.
* [Bug 1046](https://bugs.ntp.org/show_bug.cgi?id=1046): `refnumtoa.c` is using the wrong header file.
* [Bug 1042](https://bugs.ntp.org/show_bug.cgi?id=1042): multicast listeners IPv4+6 ignore new interfaces.
* [Bug 1041](https://bugs.ntp.org/show_bug.cgi?id=1041): xmt -> aorg timestamp cleanup from Dave Mills, reported by Dave Hart.
* [Bug 1037](https://bugs.ntp.org/show_bug.cgi?id=1037): buffer in subroutine was 1 byte short.
* [Bug 1033](https://bugs.ntp.org/show_bug.cgi?id=1033): `ntpdc/ntpq` crash prompting for `keyid` on Windows
* [Bug 1028](https://bugs.ntp.org/show_bug.cgi?id=1028): Support for W32Time authentication via Samba.
* [Bug 1022](https://bugs.ntp.org/show_bug.cgi?id=1022): Fix compilation problems with yesterday's commit.
* [Bug 1011](https://bugs.ntp.org/show_bug.cgi?id=1011): `gmtime()` returns NULL on windows where it would not under Unix.
* [Bug 1003](https://bugs.ntp.org/show_bug.cgi?id=1003): `ntpdc unconfig` command doesn't prompt for `keyid`.
* [Bug 980](https://bugs.ntp.org/show_bug.cgi?id=980): Direct `help` to `stdout`.
* [Bug 995](https://bugs.ntp.org/show_bug.cgi?id=995): Remove spurious `;` from `ntp-keygen.c`.
* [Bug 992](https://bugs.ntp.org/show_bug.cgi?id=992): support interface event change on Linux from Miroslav Lichvar.
* [Bug 985](https://bugs.ntp.org/show_bug.cgi?id=985): Modifications to NMEA reference clock driver to support Accord GPS Clock.
* [Bug 983](https://bugs.ntp.org/show_bug.cgi?id=983): add `interface [listen | ignore | drop] ...` directive.
* [Bug 975](https://bugs.ntp.org/show_bug.cgi?id=975): Pass `no_needed `to `ntp_intres` as first part of fixing.
* [Bug 965](https://bugs.ntp.org/show_bug.cgi?id=965): CID 42: `ss_family` uninitialized.
* [Bug 861](https://bugs.ntp.org/show_bug.cgi?id=861): leap info was not being transmitted.
* [Bug 833](https://bugs.ntp.org/show_bug.cgi?id=833): ignore whitespace at end of remote configuration lines
* [Bug 828](https://bugs.ntp.org/show_bug.cgi?id=828): Fix IPv4/IPv6 address parsing.
* [Bug 761](https://bugs.ntp.org/show_bug.cgi?id=761): internal resolver does not seem to honor `-4/-6` qualifiers
* [Bug 663](https://bugs.ntp.org/show_bug.cgi?id=663): respect `ntpq -c` and `-p` order on command line.
* [Bug 610](https://bugs.ntp.org/show_bug.cgi?id=610): NMEA support for using PPSAPI on a different device.
* [Bug 508](https://bugs.ntp.org/show_bug.cgi?id=508): Fixed leap second handling for Windows.
* [Bug 474](https://bugs.ntp.org/show_bug.cgi?id=474): `--disable-ipv6` is broken.
* [Bug 399](https://bugs.ntp.org/show_bug.cgi?id=399): NMEA refclock driver does not honor `time1` offset if `flag3` set.
* [Bug 320](https://bugs.ntp.org/show_bug.cgi?id=320): `restrict default ignore` does not affect IPv6.
* [Bug 216](https://bugs.ntp.org/show_bug.cgi?id=216): New interpolation scheme for Windows eliminates `1ms` jitter

* * *

* Upgrade to autogen-5.10
* Include 4.2.4p7
* Include 4.2.4p7-RC7
* Include 4.2.4p7-RC6
* Include 4.2.4p7-RC5
* Include 4.2.4p7-RC4
* Include 4.2.4p7-RC3
* Include 4.2.4p7-RC2
* Include 4.2.4p7-RC1
* Include 4.2.4p6
* Include 4.2.4p5

* * *

**Docs**

* Documentation cleanup and updates.
* document `interface (alias nic)` and `unpeer`.
* `accopt.html` typo fixes from Dave Mills.
* `authopt` documentation changes from Dave Mills/Dave Hart.
* Autokey documentation cleanup from Dave Mills.
* Clockhop and documentation fixes from Dave Mills.
* `decode.html` and `driver20.html` updates from Dave Mills.
* `driver4.html` updates from Dave Mills.
* local refclock documentation updates from Dave Mills.
* Update NMEA refclock documentation in `html/drivers/driver20.html`
* Typo fix to `driver20.html`.
* `keygen.html` updates from Dave Mills.
* Update documentation for `ntpq --old-rv, saveconfig, saveconfigdir, ntpd -I -L` and `-M`, and interface/nic rules. (From Dave Hart)
* `prefer.html` updates from Dave Mills.
* `sntp` documentation updates and cleanup.

* * *

**sntp**

* `sntp`: clean up some error messages.
* `sntp`: Use the precision to control how many offset digits are shown.
* `sntp`: Show root dispersion.
* `sntp/main.c`: Remove duplicate `global adr_buf[]` (also defined in `networking.c`) which Piotr Grudzinski identified breaking his build.
* use all addresses resolved from each DNS name in `sntp`.
* install the binary and man page for `sntp`.
* `sntp`: out with the old, in with the new.
* Fix problem linking `msntp` on Solaris when `sntp` subdir is configured before parent caused by different `gethostent` library search order.
* remove deleted `gsoc_sntp/utilities.o` from repository so that `.o` build products can be cleaned up without corrupting the repository.
* Renamed `gsoc_sntp/:fetch-stubs` to `gsoc_sntp/fetch-stubs` to avoid file name problems under Windows.
* Update `gsoc_sntp`'s GCC warning code.
* Update Solaris `CFLAGS` for `gsoc_sntp`.
* Deal with `time.h` for `sntp` under linux.
* Provide `rpl_malloc()` for `sntp` for systems that need it.
* Handle `ss_len` and `socklen` type for `sntp`.
* Fixes to the `sntp configure.ac` script.
* `sntp` cleanup and fixes.
* Imported GSoC SNTP code from Johannes Maximilian Kuehn.
* Enable `gcc -Wstrict-overflow` for `gsoc_sntp` as well

* * *

**ntpd**

* Construct `ntpd` keyword scanner finite state machine at compile time rather than at runtime, shrink entries from 40+ to 8 bytes.
* Reclaim syntax tree memory after application in `ntpd` built with `configure --disable-saveconfig`.
* Add test of `ntpd --saveconfigquit` fidelity using new `complete.conf`.
* Add `ntpd --saveconfigquit <filename>` option for future build-time testing of `saveconfig` fidelity.
* Regenerate `ntpd/ntp_parser.c`

* * *

**refclocks**

* CHU frequency updates.
* Bracket private ONCORE debug statements with `#if 0` rather than `#ifdef DEBUG`
* Delete ONCORE debug statement that is now handled elsewhere.
* Change ONCORE driver to log using `msyslog` as well as to any `clockstats` file.
* Enable ONCORE, ARCRON refclocks on Windows (untested)
* Spectracom refclock added to Windows port of `ntpd`
* WWVB refclock cleanup from Dave Mills.
* Fixed the incorrect edge parameter being passed to `time_pps_kcbind` in NMEA refclock driver.

* * *

* Add `./configure --enable-force-defer-DNS` to help debugging.
* Cleanup from the `automake/autoconf` upgrades.
* Correct `*-opts.h` dependency so default `get` action isn't used.
* `ntp-keygen`, Autokey OpenSSL build vs. run version mismatch is now a non-fatal warning.
* new crypto signature cleanup.
* Fix authenticated `ntpdc`, broken in p240.
* Stub out `isc/mem.h`, shaving 47k from a MIPS `ntpd` binary.
* Shrink keyword scanner FSM entries from 64 to 32 bits apiece.
* `authkeys.c` cleanup from Dave Mills.
* Remove unused file from `sntp/Makefile.am`'s distribution list.
* Provide all of OpenSSL's signature methods for `ntp.keys` (FIPS 140-2).
* Allow `NTP_VPATH_HACK` configure test to handle newer `gmake` versions.
* Get rid of configure tests for `__ss_family` and `__ss_len` when the more common `ss_family` and `ss_len` are present.
* Do not attempt to execute built binaries from `ntpd/Makefile` when cross-compiling (`keyword-gen` and `ntpd --saveconfigquit`).
* Correct `in6addr_any` test in `configure.ac` to attempt link too.
* Broadcast and transit phase cleanup from Dave Mills.
* Change `ntpsnmpd/Makefile.am` include file order to fix FreeBSD build.
* Clockhop and `autokey` cleanup from Dave Mills.
* Remove `tos maxhop` `ntp.conf` knob.
* Update `libisc` code using `bind-9.6.1-P1.tar.gz`, rearrange our copy to mirror the upstream layout (`lib/isc/...`), and merge in NTP-local  modifications to `libisc`.  There is a new procedure to ease future `libisc` merges using a separate "upstream" `bk` repo.  That will enable normal `bk pull automerge` to handle carrying forward any local changes and should enable us to take updated `libisc` snapshots more often.
* Updated `build` and `flock-build` scripts.  `flock-build --one` is a way to perform a `flock-build` compatible solitary build, handy for a repo clone's first build on a machine with `autoconf, automake`, etc.
* Compiling `ntp_parser.y` using BSD `make` correctly places `ntp_parser.h` in the top-level `ntpd` directory instead of `A.*/ntpd`.
* `bootstrap` script updated to remove potentially stale `.deps` dirs.
* Remove unneeded `Makefile.am` files from the `lib/isc/include` tree.
* Rearrange `libisc` code to match the upstream layout in BIND.  This is step one of two, changing the layout but keeping our existing `libisc`.
* add implicit `nic ignore all` rule before any rules from `ntp.conf`, so `nic listen eth0` alone means the same as `-I eth0`.
* add wildcard match class for interface/nic rules.
* fix mistaken carryover of `prefixlen` from one rule to the next.
* Ensure IPv6 localhost address `::1` is included in `libisc`'s Windows IPv6 address enumeration, allowing `ntpq` and `ntpdc`'s hardcoding to 127.0.0.1 on Windows to end.
* correct parsing and processing of `setvar` directive.
* highlight location of `ntpq :config` syntax errors with `^`.
* clarify (former) `NO_ARG, SINGLE_ARG, MULTIPLE_ARG `renaming to `FOLLBY_TOKEN, FOLLBY_STRING, FOLLBY_STRINGS_TO_EOC`.
* `parser, saveconfig` cleanup to store `T_ identifiers` in syntax tree.
* use `nic listen 192.168.0.0/16` instead of `nic listen 192.168.0.0 prefixlen 16`.
* Correct syntax error line & column numbers.
* Make the code agree with the spec and the book (Dave Mills).
* clean up numerous `sntp/kod_management.c` bugs.
* Add `ntpq -c dumpcfg`, Google Summer of Code project of Max Kuehn
* The build script now has `.` at the end of `PATH` for `config.guess`.
* `cvo.sh`: Add support for CentOS, Fedora, Slackware, SuSE, and QNX.
* Use `scripts/cvo.sh` in the `build` script to get better subdir names.
* Log warning about `signd` blocking when `restrict mssntp` used.
* Added `restrict` keyword `mssntp` for Samba4 DC operation, by Dave Mills.
* `ntp_proto.c` cleanup from Dave Mills.
* `timepps-Solaris.h pps_handle_t` changed from pointer to scalar
* Add missing header dependencies to the `ntpdc` layout verification.
* Use a union for structs `sockaddr, sockaddr_storage, sockaddr_in`, and `sockaddr_in6` to remove casts and enable type checking.  Collapse some previously separate IPv4/IPv6 paths into a single codepath.
* Lose `FLAG_FIXPOLL`, from Dave Mills.
* Leap/expire cleanup from Dave Mills.
* Provide `erealloc()` and `estrdup()`, a la `emalloc()`.
* Improve `ntp.conf`'s parser error messages.
* Clean up `configure.ac NTP_CACHEVERSION` interface, display cache version when clearing.  Fixes a regression.
* Stale leapsecond file fixes from Dave Mills.
* Do not clear `config.cache` when it is  empty.
* loopfilter FLL/PLL crossover cleanup from Dave Mills.
* `ntp-keygen` cleanup from Dave Mills.
* crypto API cleanup from Dave Mills.
* Add `NTP_CACHEVERSION` mechanism to ignore incompatible `config.cache`
* Re-enable `gcc -Wstrict-prototypes` when not building with OpenSSL
* Enable `gcc -Wstrict-overflow`
* `ntpq/ntpdc` emit newline after accepting password on Windows
* `ntp-keygen.c`: Updates.
* Fix the error return and `syslog` function ID in `refclock_{param,ppsapi}`.
* Make sure `syspoll` is within the peer's `minpoll/maxpoll` bounds.
* `ntp_crypto.c`: Use `sign_siglen`, not `len`. sign key filename cleanup.
* Bump `NTP_MAXEXTEN` from 1024 to 2048, update values for some field lengths.
* `m4/ntp_lineeditlibs.m4:` fix warnings from newer Autoconf
* Crypto cleanup from Dave Mills.
* Correct `logconfig` keyword declaration to `MULTIPLE_ARG`
* Enable filename and line number leak reporting on Windows when built `DEBUG` for all the typical C runtime allocators such as `calloc, malloc`, and `strdup`.  Previously only `emalloc` calls were covered.
* Add `DEBUG-only` code to free dynamically allocated memory that would otherwise remain allocated at `ntpd` exit, to allow less forgivable leaks to stand out in leaks reported after exit.
* Ensure termination of strings in `ports/winnt/libisc/isc_strerror.c` and quiet compiler warnings.
* PPS and crypto cleanup in `ntp_proto.c` from Dave Mills.
* Code cleanup: requested_key -> request_key.
* quiet `ntp_parser.c malloc` redeclaration warning
* Mitigation and PPS/PPSAPI cleanup from Dave Mills.
* `timepps-Solaris.h` patches from Dave Hart.
* PPS/PPSAPI cleanup from Dave Mills.
* Mitigation and PPS cleanup from Dave Mills.
* remove a bunch of `#ifdef SYS_WINNT` from portable code
* 64-bit `time_t` cleanup for building on newer Windows compilers
* Only set CMOS clock during `ntpd` exit on Windows if the computer is shutting down or restarting.
* `bias` changes from Dave Mills.
* Cleanup/fixes for `ntp_proto.c` and `ntp_crypto.c` from Dave Mills.
* Design assertion fixes for `ntp_crypto.c` from Dave Mills.
 * Removed German umlaut from log msg for 4.2.5p142.
* Stats file logging cleanup from Dave Mills.
* Fixed mismatches in data types and OID definitions in `ntpSnmpSubAgent.c`
* added a premliminary MIB file to `ntpsnmpd (ntpv4-mib.mib)`
* Provide `INET6_ADDRSTRLEN` if it is missing.
* Use `int32`, not `int32_t`.
* Avoid the `sched*()` functions under OSF - link problems.
* New `caltontp.c` and `calyearstart.c` from Juergen Perlinger.
* Cleanup lint from the `ntp_scanner` files.
* Updated `caljulian.c` and `prettydate.c` from Juergen Perlinger.
* IPv6 interfaces were being looked for twice.
* SHM driver grabs more samples, add `clockstats`
* Clean up build process for `ntpsnmpd`.
* Add options processing to `ntpsnmpd`.
* Clean up the `libntpq.a` build.
* Regenerate `ntp_parser.[ch]` from `ntp_parser.y`
* Quiet some `libntpq`-related warnings.
* Import Heiko Gerstung's GSoC2008 NTP MIB daemon.
* Stop libtool-1.5 from looking for C++ or Fortran.
* Fix a corner case where a frequency update was reported but not set. When `LEAP_NOTINSYNC`->`LEAP_NOWARNING`, call `crypto_update()` if we have crypto_flags.
* header file cleanup.
* `configure.ac`: cleanup, add option for `wintime`, and lay the groundwork for the changes needed for [bug 1028](https://bugs.ntp.org/show_bug.cgi?id=1028).
* Fixes from Dave Mills: `bias` and `interleave` work.  Separate phase and frequency discipline (for long poll intervals).  Update TAI function to match current leapsecond processing.
* poll time updates from Dave Mills.

* * *

**Updates and cleanup from Dave Mills**

I've now spent eleven months of a sabbatical year - 7 days a week, 6-10 hours most days - working on NTP. I have carefully reviewed every major
algorithm, examined its original design and evolution from that design. I've trimmed off dead code and briar patches and did zillions of tests contrived to expose evil vulnerabilities. The development article is in rather good shape and should be ready for prime time.

1. The `protostats` statistics files have been very useful in exposing little twitches and turns when something hiccups, like a broken PPS signal. Most of what used to be `syslog` messages are now repackaged as `protostats` messages with optional `syslog` as well. These can also be sent as traps which might be handy to tiggle a beeper or celltext. These, the `sysstats` files and `cryptostats` files reveal the ambient health of a busy server, monitor traffic and error counts and spot crypto attacks.

2. Close inspection of the clock discipline behavior at long poll intervals (36 h) showed it not doing as well as it should. I redesigned the FLL loop to improve nominal accuracy from  several tens of milliseconds to something less than ten milliseconds.

3. Autokey (again). The enhanced error checking was becoming a major pain. I found a way to toss out gobs of ugly fat code and replace the function with a much simpler and more comprehensive scheme. It resists bait-and-switch attacks and quickly detect cases when the protocol is not correctly synchronized.

4. The interface code for the kernel PPS signal was not in sync with the kernel code itself. Some error checks were duplicated and some ineffective. I found none of the PPS-capable drivers, including the atom driver, do anything when the prefer peer fails; the kernel PPS signal remains in control. The atom driver now disables the kernel PPS when the prefer peer comes bum. This is important when the prefer peer is not a reference clock but a remote NTP server.

5. The `flake restrict` bit turned out to be really interesting, especially with symmetric modes and of those especially those using Autokey. Small changes in the recovery procedures when packets are lost now avoid almost all scenarios which previously required protocol resets.

6. I've always been a little uncomfortable when using the clock filter with long poll intervals because the samples become less and less correlated as the sample age exceeds the Allan intercept. Various schemes have been used over the years to cope with this fact. The latest one and the one that works the best is to use a modified sort metric where the delay is used when the age of the sample is less than the intercept and the sum of delay and dispersion above that. The net result is that, at small poll intervals the algorithm operates as a minimum filter, while at larger poll intervals it morphs to FIFO. Left unmodified, a sample could be used when twelve days old. This along with the FLL modifications has made a dramatic improvement at large poll intervals.

7. **Backward Incompatible**: The `state` variable is no longer reported or available via `ntpq` output.  The following system status bit names have been changed:
  - `sync_alarm` -> `leap_alarm`
  - `sync_atomic` -> `sync_pps`
  - `sync_lf_clock` -> `sync_lf_radio`
  - `sync_hf_clock` -> `sync_hf_radio`
  - `sync_uhf_clock` -> `sync_uhf_radio`
  - `sync_local_proto` -> `sync_local`
  - `sync_udp/time` -> `sync_other`
  
  Other names have been changed as well.  See the change history for `libntp/statestr.c` for more details. Other backward-incompatible changes in `ntpq` include:
  - `assID` -> `associd`
  - `rootdispersion` -> `rootdisp`
  - `pkt_head` -> `pkt_neader`
  
  See the change history for other details.