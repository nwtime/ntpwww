---
title: "Older Releases Changelog"
type: archives
---

* [4.2.0](#420)
* [4.1.2](#412)
* [4.1.1](#411)
* [4.1.0](#410)
* [4.0.99](#4099)
* [4.0.98](#4098)
* [4.0.97](#4097)
* [4.0.96](#4096)
* [4.0.95](#4095)
* [4.0.94](#4094)
* [4.0.93](#4093)
* [4.0.92](#4092)
* [4.0.91](#4091)
* [4.0.90](#4090)
* [4.0.73](#4073)
* [4.0.72](#4072)

* * *

#### 4.2.0

**Release Date:** 2003 Oct 15

* [Bug 213: Fix](https://bugs.ntp.org/show_bug.cgi?id=213)
* [Bug 207: ntpdc crashes in monlinst with pre-IPv6 ntpd](https://bugs.ntp.org/show_bug.cgi?id=207)
* [Bug 205: Prevent a NULL dereference](https://bugs.ntp.org/show_bug.cgi?id=205)
* [Bug 197: Only check-kayout if we have PATH_PERL](https://bugs.ntp.org/show_bug.cgi?id=197)
* [Bug 185: Fix compilation error on Tru64 UNIX V4.0F with cc.](https://bugs.ntp.org/show_bug.cgi?id=185)
* [Bug 182: Clean up Solaris version checks](https://bugs.ntp.org/show_bug.cgi?id=182)
* [Bug 180: Verify mode 7 packet layout at build time.](https://bugs.ntp.org/show_bug.cgi?id=180)
* [Bug 174: Use Dave's fix.](https://bugs.ntp.org/show_bug.cgi?id=174)
* [Bug 168: Rainer Orth: Fix world-writable files](https://bugs.ntp.org/show_bug.cgi?id=168)
* [Bug 164, 165: Make sure NTP mode 7 request and response packets are layed out identically irrespective of 32 vs. 64-bit systems or struct in6_addr
 alignment requirements.](https://bugs.ntp.org/show_bug.cgi?id=164)
* [Bug 162: Only link programs with libreadline that use it (ntpdc and ntpq), From Rainer Orth.](https://bugs.ntp.org/show_bug.cgi?id=162)
* [Bug 161: Lose -pipe for gcc](https://bugs.ntp.org/show_bug.cgi?id=161)
* [Bug 136: PPS fixes for refclock_jupiter, from pe...@sectra.se (Peter Ekberg)](https://bugs.ntp.org/show_bug.cgi?id=136)
* [Bug 134: Log when we sync to a new source.](https://bugs.ntp.org/show_bug.cgi?id=134)
* [Bug 133: From fr...@tautology.immanent.net: Handle nonstandard EIA_NODATA return from getaddrinfo()](https://bugs.ntp.org/show_bug.cgi?id=133)
* [Bug 129: Improve and normalize some error messages.](https://bugs.ntp.org/show_bug.cgi?id=129)
* [Bug 128: ntpq coredump with IPv6](https://bugs.ntp.org/show_bug.cgi?id=128)
* [Bug 125: Add a missing newline from an fprintf](https://bugs.ntp.org/show_bug.cgi?id=125)
* [Bug 123: Fix build on NetBSD and more portable MD5 conditionalization](https://bugs.ntp.org/show_bug.cgi?id=123)
  * Clean up the includes in `a_md5encrypt.c`.
* [Bug 47: kill_asyncio() now takes 1 parameter - the lowest fd to close.](https://bugs.ntp.org/show_bug.cgi?id=47)
* More stuff than I have time to document
* IPv6 support
* Bugfixes
* call-gap filtering
* wwv and chu refclock improvements
* OpenSSL integration
* Make this build on NetBSD.
* Note that `ntp_resolver.c` is currently unused in the file.
* Broader support for IPv6 hostnames by `ntpdc` and `ntpq`. On NetBSD from NetBSD 1.5 to NetBSD 1.6.1, `getaddrinfo()` returned `EAI_NODATA` in some cases where [RFC 2553](https://www.rfc-editor.org/rfc/rfc2553) (and now [RFC 3493](https://www.rfc-editor.org/rfc/rfc3493)) required `EAI_NONAME`. Allow for that. The (mis-)interpretation was from the Kame project, so other platforms may be affected as well.
* Cuddle a comment.
* We log the initial state of the kernel discipline, and we log when we lose sync. So to restore parallelism, log when we reacquire sync, too.
* Fix merge botch.
* Simplify (re-enabled -> enabled).
* Move the "patching" info from `README.hackers` to `README.patches`.
* Have `README.hackers` and `README.patches` refer to each other.
* Add Win32 support for `ntp-keygen` and upgrade OpenSSL to 0.9.7b.
* `kill_asyncio` was changed for Unix but not Windows
* Initialize `.rnd` file if it doesn't exist.
* More cleanup to the `refclock_jupiter` clock.
* Remove references to IPv6 broadcast
* Replace debug notice - if we squeal when we lose kernel sync, we should also note when it is recovered.
* For BSDs, use `setrlimit()` to limit the stacksize to something considerably smaller than the default, similarly to what's done on AIX. This was culled from the NetBSD sources. Christos Zoulas gave credit for the patch, in the commit log, to Witold J. Wnuk (against ntp-4.0.99i, 2002-04-18). I've added a configure-time check for `setrlimit()`, and I had to up the pages from "8" to "20" to keep from dumping core in the resolver. (Apparently, the resolver now uses "a lot" of stack space to initialize, relatively speaking: the default is something like "512", but `p_vm_ssize` is only about "5" with the running program at any moment I look at it on both of the hosts I tested.) The bottom line is that it reduces the resident set size by about 2 Mb, from 4.5 Mb, or by about 44%.
* Make this build with pre-C99 compilers, too (which is, most of them!).
* Fix spelling, typos, usage. Mined from NetBSD CVS.
* Miscellaneous changes for Winnt support
* Correct usage, spelling of "lose", "loses", and "losing" where appropriate.
* Typo, reported by Michael Rios
* Try again to merge spelling fixes from ntp-stable.
* Corect a couple more misspelings of "occurred".
* `refclock_neoclock4x.c`: fix status reporting, update driver to v1.13
* Fix a warning compiling `refclock_arc.c`.
* Fix Multicast to not set the flag until used. Remove the unnecessary socket-querying code in `findinterface` and just look up the interface.
* Cleanup from Dave Mills.
* The order of the arguments were wrong.
* Avoid `gcc` warning, "cast discards qualifiers from pointer target type". (Frederick Bruckman)
* Add Danny Mayer to the contributor's list and fix Mark Andrew's address.
* `driver44.html`: Update the URL for the NeoClock4X website
* Autodetect `refclock_shm` prerequisites. Fix the defaults for the non-parse refclocks.
* assert edge typo fix from Peter Ekberg
* Typo fixes from Martin Burnicki
* Back out the last change but test the local addresses first.
* Fix missing conditional code around check for socket error
* Dave Mills: Fix an old bug, according to spec.
* While I don't know the original reason for using `-std1` for OSF, `-std1` is now a lose on 4.0d with a c99 compiler, and `AC_PROG_CC_STDC` can check for this.
* Call to `getaddrinfo` in `getnetnum` was wrong
* `ntp_crypto.c`: In `crypto_update()` in the loop when an expired certificate has been freed, its cp->link is still used in the next itteration of the loop. This is bad. :-) FreeBSD-current does not like that at all. This patch is my attempt to fix the problem.
* Clean up some `Makefile.am` fun.
* Add `ss_family` support
* `syslog` does `%m`, not `printf`.
* `chu_newchan()` is static.
* Clean up some type mismatches.
* `neol_atoi_len()` is static. Clean up some `fn` definitions.
* Undo `findinterface` changes
* Update `config` to check for IP version
* Put back the `SOCK_DGRAM` hints and the `ntp` service into `getaddrinfo`. Remove the `freeaddrinfo()` when `getaddrinfo` fails.
* Make the jupiter refclock aware of the year. I.e. don't trust the system clock to have the correct year.
* Default to `-4` if `isc_net_probeipv6()` fails.
* Problem deleting keys when rereading them from file.
  - Don't crash on odd number of keys in one hash.
  - Delete all keys, not just every other key.
* Remember all trusted keys in a hash bucket when deleting keys.
* `auto*` magic for `ntpdc-layout`
* Use the `Win32InitSockets` code now in `port/winnt/libisc/net.c` so we use common code. Need to force the isc headers to not include the `isc/ipv6.h` code.
* Use our `md5.h` header under RedHat. Reported by Reg Clemens.
* Clean up includes
* clean up `keyid` mess in `ntpq`.
* Move `-lcrypto` to its own variable and out of `LIBS`.
* Correctly remove trailing space from arguments of incoming request variables.
* Fix some problems in `layout.std` verification.
* Invoke the layout generation script using `./nl.pl`
* Also use `CPPFLAGS` for `nl.c`.
* Do `readline` on NetBSD.
* Another fix for `.` not in `$PATH`.
* `automake` subtlety, to permit the bootstrapped sources to build and install with BSD `make`.
* `configure.in`: Some HP-UX 11.11 systems don't have `sockaddr_storage` so we can't allow the native IPv6 headers to be used.
* Remove the old `ntptrace/` code.
* Don't try to create `ntptrace/Makefile`, now that `ntptrace` is gone.
* `peer_unfit()` needs to test for `FLAG_NOSELECT`. From Dave Mills.
* Remove the old `ntptrace/Makefile` from `configure.in`
* `ignore`: Added `firefly.sh include/ntp.patch include/ntp_control.patch include/ntp_request.patch jedi.sh ntpd/ntp_control.patch ntpd/ntp_peer.patch ntpd/ntp_proto.patch ntpd/ntp_request.patch ntpq/ntpq.patch` to the `ignore` list. 
* `ntp_proto.c, ntp_peer.c, ntp_control.c, ntp_control.h, ntp.h`: Add rank counter for each peer. This is incremented each time a peer reaches candidate status, or is actually selected as the system peer. By this method, peers that contribute most often to the system time will have a higher count.
* `ntp_timer.c, ntp_loopfilter.c, ntpd.h`: Reinitialize the interval timer after stepping the clock. The behavior of the timer after a clock step is not addressed by POSIX and is undefined, so the safest course is to reintitialize it when we step the clock. Solaris, for one, is known to stop triggering the timer after a step backward until the system clock "catches up".
* Add linked list to track remote addresses.
* Fix `add_addr_to_list` call
* Add debug to `address_okay`
* Comment out check for `Up` flag in A`ddress_Okay`
* `ntpq.c`: If `assoc_cache` is loaded, clamp association ids using & notation to allow specifying all associations without knowing how many there are.
* `ntpq.html`: Fix typos
* Fix for NetBSD 1.6.1.
* Changed `vaddr` to `remaddr` to avoid namespace collisions during build with NetBSD
* Also call `findbcastinter()` for `MDF_ACAST` | `MDF_MCAST` | `MDF_BCAST`. From Dave Mills.
* Add `HAVE_VSNPRINTF` macro to prevent extra declarations if already defined by the OS.
* `ntp_timer.c`: Double check that value isn't zero and thus disarm the timer.
* Some timers tweaks, including one build fix.
* Initialize the value of `v6_flag` in all cases in `sys_info()`, so that `ntpdc -c sysinfo` won't display the random, uninitialized value of peer6 for the system peer in the no syspeer case on IPv6-capable hosts. Problem noted and solution provided by Matthias Drochner, with a minor optimization by myself.
* Fixes for various and sundry compiler warnings, from NetBSD.
* Distribution directory cleanup
* Fix a couple more `gcc` warnings that are only seen on non-typical platforms.
* Changes from Dave Mills - `monitor` stuff, mostly.
* Check return value of localtime call to prevent NULL dereference.
* Cleanup from Dave Mills

* * *

#### 4.1.2

**Release Date:** 2003 Jul 17

* [Bug 136: PPS fixes for refclock_jupiter](https://bugs.ntp.org/show_bug.cgi?id=136)
* [Bug 129: Improve and normalize some error messages.](https://bugs.ntp.org/show_bug.cgi?id=129)
* [Bug 125: Add a missing newline from an fprintf](https://bugs.ntp.org/show_bug.cgi?id=125)
* [Bug 110: Don't log EINTR return from select()](https://bugs.ntp.org/show_bug.cgi?id=110)
* [Bug 47: kill_asyncio() now takes 1 parameter - the lowest fd to close.](https://bugs.ntp.org/show_bug.cgi?id=47)
* clock state machine bugfix
* Note that `ntp_resolver.c` is currently unused in the file.
* Cuddle a comment.
* Move the "patching" info from `README.hackers` to `README.patches`.
* Have `README.hackers` and `README.patches` refer to each other.
* Fix spelling, typos, usage. Mined from NetBSD CVS.
* Correct usage, spelling of "lose", "loses", and "losing" where appropriate.
* `refclock_neoclock4x.c`: fix status reporting, update driver to v1.13
* Fix a warning compiling `refclock_arc.c`.

* * *

#### 4.1.1

**Release Date:** 2002 Feb 26

* Lose the source port check on incoming packets
* `(x)ntpdc` compatibility patch
* Virtual IP improvements
* `ntp_loopfilter` fixes and improvements
* `ntpdc` improvements
* GOES refclock fix
* JJY driver
* BSDi port fixes
* HP MPE/iX port
* Win/NT port upgrade
* Dynix PTX port fixes
* Document conversion from CVS to BK
* `readline` support for `ntpq`
* Disable the delta-changelog and related scripts.
* Lint cleanup from Marc.
* Lose the source port check. Too many folks are going thru Port and Address Translators, and present wisdom says that one should not trust source ports anyway.
* mu can be 0, and the (old) debug info would divide `sys_jitter` by mu. Lose the division.
* `ntp_adjtime()` call cleanup.
* Trigger improvements.
* `LEAP_DELSECOND` support for CHU.

* * *

#### 4.1.0

**Release Date:** 2001 Aug 1

* CERT problem fixed (99k23)
* Huff-n-Puff filter
* Preparation for OpenSSL support
* Resolver changes/improvements are not backward compatible with mode 7 requests (which are implementation-specific anyway)
* leap second stuff
* manycast should work now
* `ntp-genkeys` does new good things.
* `scripts/ntp-close`
* PPS cleanup and improvements
* `readline` support for `ntpdc`
* Crypto/authentication rewrite
* WINNT builds with MD5 by default
* WINNT no longer requires Perl for building with Visual C++ 6.0
* algorithmic improvements, bugfixes
* Solaris `dosynctodr` info update
* `html/pic/*` is lots smaller
* New/updated drivers: Forum Graphic GPS, WWV/H, Heath GC-100 II, HOPF serial and PCI, ONCORE, ulink331
* Rewrite of the audio drivers
  * `ntpd/refclock_oncore.c` (`oncore_start`): Set `pps_enable=1`, just like the atom driver does.
  * `ntpd/refclock_nmea.c` (`nmea_ppsapi`): Set `pps_enable=1`, just like the atom driver does.
* `ntpd/ntp_config.c` (`getconfig`): `CONF_CLOCK_PANIC` was using the wrong `config` flag.

* * *

#### 4.0.99

**Release Date:** 2000 Jan 12

* Driver updates: CHU, DCF, GPS/VME, Oncore, PCF, Ulink, WWVB, burst
  * If you use the ONCORE driver with a HARDPPS kernel module, you _must_ have a properly specified `pps <filename> [assert/clear] [hardpps]` line in the `/etc/ntp.conf` file.
* PARSE cleanup
* PPS cleanup
* `ntpd, ntpq, ntpdate` cleanup and fixes
* NT port improvements
* AIX, BSDI, DEC OSF, FreeBSD, NetBSD, Reliant, SCO, Solaris port improvements
* `html/driver36.htm`: Cleanup
* `html/monopt.htm: Ditto
* ntpd/ntp_intres.c` (`ntp_intres`): Put `NTP_INTRES running` at a higher debug level
* `ntpd/refclock_wwv.c`: More improvements
* `ntpd/refclock_wwv.c`: Bugfixes/improvements
* `configure.in`: Get the quoting right on the `sys_errlist` check.
* `configure.in`: `<netinet/ip.h>` cannot be detected...
* `ntpd/ntp_io.h`: ...but every OS has it
* `ntpd/refclock_oncore.c`: Lint removal
* `ntpq/ntpq_ops.c`: Lint removal
* `ntpq/refclock_chu.c`: `chu_major()` is not an audio routine, lint
* `libntp/icom.c`: AIX doesn't have `<sys/termios.h>`
* `ntpd/refclock_chu.c`: NetBSD needs `sys/ioctl.h`
  * (`chu_debug`): NetBSD-specific debug output.

* * *

#### 4.0.98

**Release Date:** 1999 Sep 17

* Solaris kernel FLL bug is fixed in 106541-07
* Bug/lint cleanup
* PPS cleanup
* ReliantUNIX patches
* NetInfo support
  * Add to Mac OS (versions 10 and up).
    * `config.guess` and `config.sub`
  * Check for NetInfo API; add `HAVE_NETINFO` macro and friends.
    * `acconfig.h`, `config.h.in`, and  `configure.in`
  * Add support for reading configuration from NetInfo.
    * `include/ntp.h`, `ntpd/ntp_config.c`, and `ntpdate/ntpdate.c`
  * Get rid of unnecessary `eol` variable in tokenizer.
    * `ntpd/ntp_config.c`
  * Document NetInfo functionality.
    * `html/notes.htm`, `html/ntpd.htm`, and `html/ntpdate.htm`
  * Use `HAVE_KVM_OPEN` conditional around `kvm.h` include.
    * `util/tickadj.c`
* Ultralink driver: `acconfig.h, config.h.in, configure.in, html/driver34.htm, html/refclock.htm, include/ntp.h, libntp/clocktypes.c, ntpd/Makefile.am, ntpd/ntp_control.c, ntpd/refclock_conf.c`, and `ntpd/refclock_ulink.c`.
* Trimble OEM Ace-II support
* DCF77 power choices
* Oncore improvements
* `ntpd/refclock_atom.c`: PPS cleanup
* `ntpd/ntp_refclock.c` (`refclock_ioctl`): PPS cleanup
* `ntptrace/ntptrace.c` (`ReceiveBuf`): `addserver()` can return NIL.
* Lint cleanup: `libntp/ieee754io.c`, ntpd/ntp_proto.c`, and `ntpd/ntp_refclock.c`.
* `ntpd/ntp_refclock.c` (`refclock_ioctl`): Declaration cleanup.
* `ntpd/ntp_proto.c` (`init_proto`): `msyslog kern_enable` at `LOG_DEBUG`.
* `ntpd/refclock_atom.c`: Add missing declaration.
* `configure.in` (`ac_cv_make_ntptime`): Just look for struct `ntptimeval`, not `timespec` or `nsec` (Solaris 2.7 should get `ntptime` and it uses `msec`).      
  * (`ac_cv_var_oncore_ok`): Reorder so it's a "normal" clock

* * *

#### 4.0.97

**Release Date:** 1999 Aug 19

* NT patches
* AIX, SunOS, IRIX portability
* NeXT portability
* `ntptimeset` utility added
* cygwin portability patches: `libntp/systime.c, ntpd/ntp_loopfilter.c, ntpd/ntpd.c`, and `ports/winnt/libntp/nt_clockstuff.c`.
* `README.cvs`: Updated.
* Irix, SunOS, AIX, lint patches: `configure.in, include/ntp_machine.h, libntp/mexit.c, ntpd/ntp_config.c, ntpd/ntp_peer.c, ntpd/ntp_restrict.c, ntpd/refclock_arc.c`, and `ntpdate/ntpdate.c`.
* `util/ansi2knr.c`: New release (fix for bug reported by Marc Brett)
* `include/ntp_stdlib.h`: NeXT portability patch
* ntptimeset patches: `configure.in, dot.emacs` (cleanup), `ntpdate/Makefile.am, ntpdate/ntpdate.h, ntpdate/ntptime_config.c`, and `ntpdate/ntptimeset.c`.
* `ntpd/refclock_parse.c` (local_input): `ts.l_ui` -> `ts.fp.l_ui`

* * *

#### 4.0.96

**Release Date:** 1999 Aug 9

* `-lnsl, -lsocket, -lgen` configuration patches
* Y2K patches from AT&T
  * `Makefile.am` (`EXTRA_DIST`): Add in the y2k notes
  * `parseutil/dcfd.c`: Renamed `drift_comp` to `accum_drift`
  * `configure.in`: Added `MAKE_CHECK_Y2K` support; `check_y2k` needs `libparse`.
  * `ntpd/Makefile.am` (`check_PROGRAMS`): Use `MAKE_CHECK_Y2K`
  * `ntpd/Makefile.am` (`check-local`): Added.
  * `parseutil/Makefile.am` (`check-local`): Added.
  * `include/ntp.h`: Y2K Fixes
  * `libparse/parse.c`: Ditto
  * `ntpd/Makefile.am` (`check_PROGRAMS`): Ditto
  * `ntpd/refclock_acts.c`: Ditto
  * `ntpd/refclock_arc.c` (`arc_receive`): Ditto
  * `ntpd/refclock_heath.c`: Ditto
  * `ntpd/refclock_hpgps.c`: Ditto
  * `parseutil/Makefile.am` (`check-local`): Ditto
  * `parseutil/dcfd.c` (`check_y2k`): Ditto
  * `NOTES.y2kfixes`: Ditto
  * `readme.y2kfixes`: Ditto
  * `results.y2kfixes`: Ditto
  * `ntpd/check_y2k.c`: Ditto
* Linux portability cruft
* `parseutil/dcfd.c` (`main`): Replace `SA_ONSTACK` and `SV_ONSTACK` with `HAVE_SIGACTION` and `HAVE_SIGVEC`, respectively. HP-UX provides both of the former but only one of the latter.
* `configure.in`: Better tests for `-lnsl` and `-lsocket`. Handle `openlog()` and `-lgen` the same way.
* `configure.in`: Look for `sys/ppstime.h`.
* `ntpd/ntp_io.c` (`create_sockets`): Typo.
* `configure.in` (`ac_cv_struct_ntptimeval`): Explicitly look for struct `ntptimeval`.
  * (`ac_cv_var_kernel_pll`): Require struct `ntptimeval`.

* * *

#### 4.0.95

**Release Date:** 1999 Jul 28

* NT port cleanup/replacement
* a few portability fixes
* VARITEXT Parse clock added
* `ports/winnt`: New release
* `libntp/machines.c` (`ntp_set_tod`): Bugfix

* * *

#### 4.0.94

**Release Date:** 1999 Jul 21

* PPS updates (including `ntp.config` options)
* Lose the old DES stuff in favor of the (optional) RSAREF stuff
* html cleanup/updates
* numerous drivers cleaned up
* numerous portability patches and code cleanup
* `Makefile.am` (`SUBDIRS)`: `librsaref` (`dist-hook`): Lose CVS subdirs in the distribution tarball
* `include/Makefile.am` (`noinst_HEADERS`): Added `iosignal.h, recvbuff.h`
* `Makefile.am` (`dist-hook`): Don't call `dos2unix` anymore
* `acconfig.h`:
* `util/ntptime.c`: FreeBSD nano patches
* Cleanup `include/ntp.h: include/ntp_fp.h, include/ntp_io.h, include/ntp_machine.h, include/ntp_refclock.h, include/ntp_stdlib.h, include/ntpd.h, libntp/Makefile.am, libntp/emalloc.c, libntp/machines.c, libntp/mexit.c, libntp/msyslog.c, libntp/statestr.c, libntp/syssignal.c, libntp/systime.c, libparse/parse.c, libparse/parse_conf.c, ntpd/ntp_control.c, ntpd/ntp_intres.c, ntpd/ntp_io.c, ntpd/ntp_proto.c, ntpd/ntp_refclock.c, ntpd/ntp_request.c, ntpd/ntp_timer.c, ntpd/ntp_util.c, ntpd/ntpd.c, ntpd/refclock_nmea.c, ntpd/refclock_palisade.c, ntpd/refclock_palisade.h, ntpd/refclock_shm.c, ntpdate/ntpdate.c`, and `ntptrace/ntptrace.c`.
* Added to `libntp/recvbuff.c: libntp/iosignal.c, include/iosignal.h`, and `include/recvbuff.h`.
* `README`: Add `README.cvs`
* `configure.in` (`ac_cv_var_struct_ntptime_val_timespec`): Typo.
* `Makefile.am` (`EXTRA_DIST`): Lose `ntpmak`; `build` does a better job.
* `ntpq/Makefile.am` (`version.o`): Use `mkver`
* `ntptrace/Makefile.am` (`version.o`): Ditto
* `ntpdate/Makefile.am` (`version.o`): Ditto
* `ntpd/Makefile.am` (`version.o`): Ditto
* `ntpdc/Makefile.am` (`version.o`): Ditto
* `configure.in` (`AC_OUTPUT`): `scripts/mkver`
* `scripts/mkver.in:` Created. Note RSAREF in the version string
* `README.des`: Updated.
* `ntpq/Makefile.am` (`LDADD`): Add `LIBRSAREF`
* `ntpdc/Makefile.am` (`LDADD`): Add `LIBRSAREF`
* `ntpdate/Makefile.am` (`LDADD`): Add `LIBRSAREF`
* `ntpd/Makefile.am` (`LDADD`): Add `LIBRSAREF`
* `configure.in` (`AC_OUTPUT`): Added `librsaref/Makefile`. Added tests for making/using `librsaref.a`. Lose old DES stuff; `AC_DEFINE(DES)` if we find the `rsaref` stuff.
* `ntpd/refclock_trak.c` (`trak_receive`): disambiguate expression. At least now it is unambiguous. It may even still be correct.
* `ntp_update` (`UPDATE_OPTIONS`): Typo.
* `ntp_update`: Check out `copyright.htm` before `COPYRIGHT`
* `ntpd/ntp_config.c`: Support for PPS `assert/clear/hardpps`
* `ntpd/ntp_refclock.c` (`refclock_ioctl`): Ditto
  * (`refclock_gtlin`): Ditto
* `html/clockopt.htm`: Document.
* `html/monopt.htm`: We have four types of files now
* `ntpd/refclock_oncore.c`: If debug is on, tell when we are waiting for a valid almanac
* `include/ntp_machine.h` (`HAVE_TERMIOS`): `STREAMS` does not imply `HAVE_TERMIOS`!
* `include/parse.h` (`timercmp`): Macro defined if needed.
* `ntpd/ntp_config.c` (`SIGCHLD`): Macro defined as `SIGCLD` if needed. 
  * (`sys/wait.h`): File included only if `HAVE_SYS_WAIT_H`.
* `configure.in` (`sys/wait.h)`: File added to `AC_CHECK_HEADERS` list.
* `ntpd/refclock_irig.c` (`irig_debug`): NetBSD patches
* `util/ntptime.c` (`main`): `ntx.freq` bugfix (`-f` option)
* `configure.in`: Fix typo with `DECL_H_ERRNO` test
* `ntpd/ntp_loopfilter.c`: Lose `syscall` decl, it's handled in `l_stdlib.h` now.
* `ntpd/ntp_request.c`: Ditto
* `util/ntptime.c`: Ditto
* `ntpd/ntp_proto.c` (`proto_config`): Don't set `sys_bclient` on `PROTO_MULTICAST_ADD`, only caller can decide; remove wrong set on `PROTO_MULTICAST_DEL`.
* `ntpd/refclock_parse.c` (`stream_receive`): Cast `size_t` to `int` to match format.
  * (`local_receive`): Likewise.
  * (`trimbletaip_event`): Likewise.
  * (`stream_receive`): Cast struct timeval members to long to match format.
* `ntpd/ntp_util.c` (`stats_config`): Cast `size_t` to `int` to match format.
* libparse/clk_rawdcf.c (cvt_rawdcf): Cast ptr difference to int to match format.
* `ntpd/refclock_parse.c` (`gps16x_poll`): Likewise.
* `ntpd/ntp_filegen.c` (`filegen_open`): Use long format, cast arg to match.
* `ntpd/refclock_parse.c` (`list_err`): Use long format to match arg.
  * (`parse_statistics`): Likewise.
  * (`gps16x_message`): Likewise.
  * (`cvt_ts`): Use long format, cast args to match.
  * (`parse_start`): Add missing arg.
  * (`gps16x_message`): Swap args to match format.
* `ntpd/ntpd.c` (`ntpdmain`): Cast `uid` to long, adapt format.
* `ntpd/ntp_intres.c` (`readconf`): Use long format to match arg.
* `ntpd/ntp_io.c` (`getrecvbufs`): Likewise.
* `ntpd/ntp_proto.c` (`default_get_precision`): Likewise.
* `ntpd/ntp_loopfilter.c` (`local_clock`): Cast `clock_panic` to int to match format.
* `ntpd/ntp_io.c` (`io_multicast_add`): Print `s_addr member`, not struct `in_addr`, to match format.
* `include/ntp_stdlib.h`: Declare `msyslog()` as `printf`-like for `gcc` format checking.
* `ntpdc/ntpdc_ops.c` (`iostats`): Align `timereset` line.
* `ntpq/ntpq_ops.c` (`doopeers`): Properly align header.
* `ntpdc/ntpdc_ops.c` (`debug`): Removed declaration, already in `ntp_stdlib.h`.
* `ntpq/ntpq_ops.c`: Likewise.
* `ntpdate/ntpdate.c` (`debug`): Declare volatile to match `ntp_stdlib.h`.
* `ntpdc/ntpdc.c, ntpq/ntpq.c, ntptrace/ntptrace.c, util/tickadj.c, util/ntptime.c`: Likewise.
* `include/parse.h` (`debug`): Don't declare to avoid clash with `ntp_stdlib.h`.
* `include/Makefile.am` (`noinst_HEADERS`): Add new `ntp_syscall.h`.
* `configure.in`: Also check for `-lrt` for POSIX.1c functions.
* `configure.in`: Removed `-Wwrite-strings` from `CFLAGS`.
* `ntpdc/ntpdc.c` (`help`): Remove superfluous cast.
* `ntpq/ntpq.c` (`help`): Likewise.
* `ntpq/ntpq_ops.c` (`struct varlist`): `name` cannot be const char `*` since it may be `malloc`'ed.
* `ntpdc/ntpdc.c` (`sendrequest`): Declare `pass` as const char `*`, don't loose const in cast.
* `ntpq/ntpq.c` (`sendrequest`): Likewise.
* `ntpd/ntp_control.c` (`ctl_getitem`): Remove superfluous cast.
* `include/ntpd.h` (`struct ctl_var`): `text` cannot be const char `*` since it's `malloc`'ed.
* `include/l_stdlib.h`: Don't include `<netinet/in.h>`, add forward declaration of struct `in_addr` instead.
* `include/l_stdlib.h`: Fixed `syscall()` declaration.
* `configure.in`: Updated test to match.
* `configure.in`: Check if we need to declare `errno` and `h_errno`. Check for `<resolv.h>` which may provide a `h_errno` declaration and
`<arpa/nameserv.h>` which the latter needs.
* `acconfig.h`: Provide the necessary templates.
* `include/ntp_syscall.h`: New file, hides various implementations of `ntp_adjtime()` and `ntp_gettime()` syscalls.
* `ntpd/ntp_loopfilter.c`: Use it.
* `ntpd/ntp_request.c`: Likewise.
* `ntpd/refclock_local.c`: Likewise.
* `util/ntptime.c`: Likewise.
* `include/l_stdlib.h`: Include `<netinet/in.h>`, declare `inet_ntoa` if necessary. Moved `syscall()` declaration here.
* `kernel/sys/parsestreams.h`: Include `<sys/termios.h>` for its definition of struct `ppsclockev`. Include `<sys/ppsclock.h>` unconditionally for definition of `CIOGETEV` via `TIOCGPPSEV`.
* `kernel/sys/ppsclock.h`: Protect struct `ppsclockev` from redefinition.
* `include/ntp_refclock.h`: Protect it from multiple inclusion.
* `include/ntp_fp.h`: Likewise.
* `include/ntp.h`: Likewise.
* `include/ntpd.h`: Include `ntp_refclock.h` for `MAXDIAL` declaration.
* `libntp/authkeys.c`: Include `ntpd.h` for `current_time` declaration.
* `include/ntpd.h` (`getauthkeys, auth_agekeys, rereadkeys`): Moved prototypes to `ntp_stdlib.h`
* `include/ntp_stdlib.h`: Declare variables exported by `libntp`.
* `include/ntpd.h`: Likewise for `ntpd`.
* `libntp/authkeys.c` (`key_hash, authnokey, authfreekeys, cache_flags`): Made static.
* `libntp/systime.c` (`tvu_maxslew, tsf_maxslew, sys_clock_offset, sys_residual`): Likewise.
* `ntpd/ntp_intres.c` (`confentries`): Likewise.
* `ntpd/ntp_loopfilter.c` (`clock_offset, clock_panic`): Likewise.
  * (`pll_nano`): Likewise. Removed duplicate definition.
* `ntpd/ntp_peer.c` (`peer_free, current_association_ID, assocpeer_calls, init_peer_starttime`): Likewise.
* `ntpd/ntp_proto.c` (`sys_offset, sys_authdly`): Likewise.
* `ntpd/ntp_request.c` (`numrequests, numresppkts, errorcounter`): Likewise.
* `ntpd/ntp_restrict.c` (`res_calls, res_found, res_not_found, res_timereset, res_limited_refcnt`): Likewise.
* `ntpd/ntpd.c` (`was_alarmed, worker_thread`): Likewise.
* ntpq/ntpq_ops.c: Moved declaration of external variable from ntpq.c to file scope.
* `adjtimed/adjtimed.c`: Moved declarations of external variables to `ntpd.h` and `ntp_stdlib.h`.
* `clockstuff/propdelay.c`: Likewise.
* `libntp/a_md5encrypt.c, libntp/authencrypt.c, libntp/authkeys.c, libntp/mfp_mul.c, libntp/msyslog.c, libntp/systime.c`: Likewise.
* `ntpd/ntp_config.c, ntpd/ntp_control.c, ntpd/ntp_filegen.c, ntpd/ntp_intres.c, ntpd/ntp_io.c, ntpd/ntp_loopfilter.c, ntpd/ntp_monitor.c, ntpd/ntp_peer.c, ntpd/ntp_proto.c, ntpd/ntp_refclock.c, ntpd/ntp_request.c, ntpd/ntp_restrict.c, ntpd/ntp_timer.c, ntpd/ntp_util.c, ntpd/ntpd.c, ntpd/refclock_acts.c, ntpd/refclock_arbiter.c, ntpd/refclock_arc.c, ntpd/refclock_as2201.c, ntpd/refclock_atom.c, ntpd/refclock_bancomm.c, ntpd/refclock_chronolog.c, ntpd/refclock_chu.c, ntpd/refclock_datum.c, ntpd/refclock_dumbclock.c, ntpd/refclock_gpsvme.c, ntpd/refclock_heath.c, ntpd/refclock_hpgps.c, ntpd/refclock_irig.c, ntpd/refclock_jupiter.c, ntpd/refclock_leitch.c, ntpd/refclock_local.c, ntpd/refclock_msfees.c, ntpd/refclock_mx4200.c, ntpd/refclock_nmea.c, ntpd/refclock_oncore.c, ntpd/refclock_palisade.h, ntpd/refclock_parse.c, ntpd/refclock_pst.c, ntpd/refclock_shm.c, ntpd/refclock_tpro.c, ntpd/refclock_trak.c, ntpd/refclock_true.c, ntpd/refclock_usno.c, ntpd/refclock_wwvb.c`: Likewise.
* `ntpdate/ntpdate.c`: Likewise.
* `ntpdc/ntpdc.c, ntpdc/ntpdc_ops.c`: Likewise.
* `ntpq/ntpq.c`: Likewise.
* `ntptrace/ntptrace.c`: Likewise.
* `util/ntptime.c, til/tickadj.c:` Likewise.
* `include/ntp_machine.h`: Removed superfluous `yy/mm/dd` comments.
* `include/ntpd.h`: Likewise.
* `libntp/authencrypt.c`: Likewise.
* `libntp/a_md5encrypt.c`: Likewise.
* `libntp/caljulian.c`: Likewise.
* `libntp/ymd2yd.c`: Likewise.
* `libntp/syssignal.c`: Likewise.
* `libntp/ymd2yd.c`: Likewise.
* `ntpd/ntp_control.c`: Likewise.
* `ntpd/ntp_io.c`: Likewise.
* `ntpd/ntp_timer.c`: Likewise.
* `ntpdate/ntpdate.c`: Likewise.
* `ntpq/ntpq_ops.c`: Likewise.
* `ntpd/ntp_peer.c` (`findpeer`): Wrap debug output in `DEBUG/debug`.
* `dot.emacs`: Removed wrong indentation of substatements. Wrap in c-style.
* `ntpd/refclock_palisade.c`: Patches from Marc Brett
* `ntpd/refclock_palisade.h`: Ditto.
* `util/hist.c`: Ditto.
* `build: mips-dec-ultrix4.4` hates `set -e`
* `flock-build`: Created
* `build`: added `-l` option
* `README`: Removed `auto{make,conf}.patch` files
* `Makefile.am` (`$(srcdir)/COPYRIGHT`): Added (`EXTRA_DIST`): Remove `auto*.patches`
* `Makefile.am` (`dist-hook`): Call `dos2unix` on the `.htm` files
* `ntpd/refclock_palisade.h`: Clean up declarations.
* `configure.in` (`ac_cv_struct_ntptimeval_timespec`): Added.
  * (`ac_cv_make_ntptime`): Only if `ntptimeval` does not use `timespec`.
* `util/tickadj.c`: Linux Patches
* `configure.in`: 4.0.93a
* `ntpd/refclock_palisade.h`: Restore some lost patches
* `libparse/clk_wharton.c` (`cvt_wharton_400a, inp_wharton_400a`): Expect serial output format number 1, not 5.
  * (`clock_wharton_400a`) : Likewise.
* `ntpd/refclock_parse.c` (`parse_clockinfo`): For Wharton 400a clock, do not poll, but expect a message every second.
* `html/parsedata.htm`: Entry added for Wharton 400a clock.
* `html/driver8.htm`: Entry fixed for Wharton 400a clock.

* * *

#### 4.0.93

**Release Date:** 1999 May 16

* Oncore refclock needs PPS or one of two ioctls.
* Don't make `ntptime` under Linux.  It doesn't compile for too many folks.
* Autokey cleanup
* ReliantUnix patches
* html cleanup
* `tickadj` cleanup
* PARSE cleanup
* IRIX `-n32` cleanup
* byte order cleanup
* `ntptrace` improvements and patches
* `ntpdc` improvements and patches
* PPS cleanup
* mx4200 cleanup
* New clock state machine
* SCO cleanup
* Skip alias interfaces
* `configure.in` (`ntp_refclock`): ONCORE requires `PPSAPI, CIOGETEV`, or `TIOCGPPSEV`.
* `configure.in`: 4.0.92h2
* `configure.in` (`ac_cv_make_ntptime`): Not under Linux. Yes, it works for some people. We're tired of the complaints from the others.
* `libntp/authreadkeys.c` (`authreadkeys`): Reject autokey keys. Include `ntp.h` for `NTP_MAXKEY` definition, `ntp_fp.h` for types used in `ntp.h`.
* `libntp/authkeys.c` (`auth_delkeys`): Don't remove autokey keys, leave info on `KEY_TRUSTED` flag alone. Include `ntp.h` for `NTP_MAXKEY` definition.
* `configure.in`: 4.0.92h1
* `ntpd/refclock_oncore.c`: Patches
* `html/*.htm`: Remove unnecessary `&nbsp;`. Cleanup `<pre></pre>` sections.
* `configure.in`: Properly align `configure --help` output.
* `html/config.htm`: Include this version, removing Netscape `&nbsp;` cruft.
* `kernel/sys/parsestreams.h`: Only include `<sys/ppsclock.h>` if struct `ppsclockev` is missing from system headers.
* `util/tickadj.c` (`getoffsets`): Define `kernels[]` only if used.
  * (`openfile`): Rename `fd` to avoid shadowing global `fd`.
  * (`writevar`): Likewise.
  * (`readvar`): Likewise.
* `parseutil/dcfd.c` (`read_drift`): `drift_file` is const char `*`.
  * (`update_drift`): Likewise.
  * (adjust_clock): Likewise.
  * (`main`): Likewise.
* `ntpd/refclock_parse.c` (`gps16x_poll`): Adapt format to match `parse`->`localstate` type.
* `ntpd/ntp_refclock.c` (`refclock_gtlin`): Only define `gotit` label if used.
* `include/l_stdlib.h` (`openlog, syslog`): char `*` args are const.
* `configure.in` (`*-*-osf4*`): Enable declaration of `stime()`.
* `ntpd/refclock_oncore.c` (`oncore_msg_any`): Cast args to long to match prototype.
  * (`oncore_msg_En`): Likewise.
* `include/ntp_refclock.h` (`struct refclockstat`): Declare `p_lastcode` as const char `*`.
* `ntpq/ntpq_ops.c` (`struct varlist`): Define name as const.
* `ntpdc/ntpdc.c` (`tokenize`): Define `cp` as const char `*`, remove wrong cast instead.
* `ntpd/ntp_util.c` (`record_clock_stats`): Make `text` arg const.
* `include/ntpd.h` (`record_clock_stats`): Adapt declaration.
* Removed superfluous casts: `ntpd/refclock_oncore.c` (`oncore_start`), (`oncore_msg_Cf`), (`oncore_msg_Fa`), (`oncore_msg_Cj`), (`oncore_msg_Ea`), and (`oncore_msg_Bj`).
* `configure.in` (`*-*-solaris2.4`): Enable declarations of `gettimeofday()`, `settimeofday()`; they are 'protected' by `__cplusplus` in `<sys/time.h>`.
* `scripts/summary.pl`: Use `.` as default `statsdir`.
  * (`do_loop`): Accept new `loopstats` format with additional `sys_error` and `clock_stability` fields.
  * (`do_peer`): Accept new `peerstats` format with additional `skew` field.
* Upgraded `automake` (1.4a) and `autoconf` (2.14.1)
* `configure.in` (`ac_refclock_irig`): We no longer need `stropts.h`.
* `ntpd/refclock_irig.c`: Ditto
* `configure.in` (`*-*-irix6*`): Don't pass MIPSpro cc-only flag `-n32` to `gcc`.
* `ntpd/ntp_config.c` (`getconfig`): I`N_CLASSD()` expects address in host byte order, but struct `sockaddr_in.s_addr` is in network byte order.
* `ntpd/ntp_io.c` (`io_multicast_del`): Likewise.
* `configure.in`: 4.0.92h
* `ntptrace/ntptrace.c`: `-m maxhost` patch
* `util/ntptime.c`: Patches.
* `html/accopt.htm, html/assoc.htm, html/authopt.htm, html/biblio.htm, html/build.htm, html/clockopt.htm, html/confopt.htm, html/copyright.htm, html/debug.htm, html/exec.htm, html/extern.htm, html/hints.htm, html/index.htm, html/kern.htm, html/miscopt.htm, html/monopt.htm, html/notes.htm, html/ntpd.htm, html/ntpdate.htm, html/ntpdc.htm, html/ntpq.htm, html/ntptime.htm, html/ntptrace.htm, html/patches.htm, html/porting.htm, html/pps.htm, html/rdebug.htm, html/refclock.htm, html/release.htm, html/tickadj.htm, html/hints/solaris.html`: Fixed many typos and problems.
* `acconfig.h` (`DECL_CFSETISPEED_0, DECL_MRAND48_0, DECL_NLIST_0, DECL_SRAND48_0, DECL_STIME_0`): New templates.
* `include/l_stdlib.h`: Include `termios.h` to get definition of `speed_t`.
  * (`cfsetispeed, cfsetospeed, mrand48, nlist, srand48, stime`): New declarations.
  * (`openlog`): Declare 2- or 3-argument form.
* `configure.in`: Enable declarations of functions missing from Ultrix V4.3 system headers.
* `ntpd/refclock_oncore.c`: Include `<sys/types.h>`, Ultrix V4.3 `<sys/stat.h>` needs it for `dev_t`.
* `ntpdc/ntpdc_ops.c`: Reality checks.
* `configure.in`: NetBSD has stubs for the `timer_*` stuff and doesn't support PPSAPI. IRIG requires `<stropts.h>`.
* `ntpdc/ntpdc_ops.c`: (`kerninfo`) Report in seconds regardless of kernel precision. Report kernel flags as text.
* `configure.in`: 4.0.92g
* `ntpd/ntp_refclock.c` (`refclock_ioctl`): We don't want `PPS_HARDPPSONASSERT` by default.
* `ntpd/refclock_oncore.c`: Prefer `timepps.h` over `sys/timepps.h`
* `configure.in`: 4.0.92f
* `ntpd/ntp_refclock.c` (`refclock_open`): `VMIN` should be 1, not 0
* `ntpd/refclock_mx4200.c`: Patches/improvements
* `ntpd/ntpd.c` (`set_process_priority`): Lint
* `util/ntptime.c`: Lint, bit definition cleanup
* `ntpd/refclock_oncore.c`: Use `timepps.h` or `sys/timepps.h`
* `configure.in`: Look for either `timepps.h` or `sys/timepps.h`
* `ntpd/ntp_io.c` (`create_sockets`): Don't warn about `ENXIO`. (Several places)
* `libntp/mfp_mul.c` (`mfp_mul`): Lint.
* `configure.in`: 4.0.92e: Dave redesigned the clock state machine.
* `parseutil/dcfd.c`: added DCF77 module powersetup
* `ntpd/refclock_parse.c` (`parse_control`): using `gmprettydate` instead of `prettydate()`
  * (`mk_utcinfo`): new function for formatting GPS derived UTC information
  * (`gps16x_message`): changed to use `mk_utcinfo()`
  * (`trimbletsip_message`): changed to use `mk_utcinfo()` ignoring position information in unsynchronized mode
  * (`parse_start`): augument linux support for optional `ASYNC_LOW_LATENCY`
* `ntpd/ntp_control.c` (`ctl_putclock`): cleanup of end of buffer handling
* `libparse/parse.c` (`timepacket`): removed unnecessary code
* `libparse/clk_trimtsip.c` (`struct trimble`): new member `t_utcknown`
  * (`cvt_trimtsip`): fixed status monitoring, bad receiver states are now recognized
* `libntp/prettydate.c` (`gmprettydate`): new function for format date and time with respect to UTC
* `libntp/gpstolfp.c` (`GPSWRAP`): update GPS rollover to 990 weeks
* `include/trimble.h` (`CMD_RUTCPARAM`): control variable name unification
* `include/ntp_fp.h`: added prototype for `gmprettydate()`
* `libntp/systime.c`: definition
* `ntpd/ntp_proto.c`: sco5_oldclock declaration
* `configure.in`: `SCO5_CLOCK` for `*-*-sco3.2v5*`
* `util/tickadj.c` (`main`): `SCO5_OLDCLOCK` -> `SCO5_CLOCK`
* `ntpd/ntp_config.c` (`getconfig`): Indentation cleanup. Deal with `P` case better
* `ntpd/ntpd.c`: Declare `set_process_priority()`
* `ntpd/refclock_dumbclock.c`: Lint cleanup
* `configure.in`: 4.0.92d
* `configure.in`: Dave says we can't enable PARSE clocks by default. Also, Solaris 2.7 still has its kernel bug - disable kernel FLL there.
* `libparse/Makefile.am` (`parsesolaris.o`): Devious hack to deal with bug in `sys/systm.h`.
* `ntpd/refclock_parse.c`: fixed `#endifs`
  * (`stream_receive`): fixed formats
* `configure.in`: 4.0.92c
* Lint: `ntpd/refclock_chronolog.c`, `ntpd/refclock_dumbclock.c`, and `ntpd/refclock_oncore.c`.
* `ntpd/refclock_oncore.c` (`oncore_msg_any`): Call `GETTIMEOFDAY`, not `gettimeofday()`.
* `configure.in` (`MCAST`): Not in `i386-sequent-sysv4`
* `util/ntptime.c`: Linux cleanup.
* `configure.in`: Rename `SCO5_OLDCLOCK` to `SCO5_CLOCK`
* `acconfig.h`: Ditto
* `ntpd/ntp_proto.c`: `SCO5_CLOCK` stuff
  * (`init_proto`): Use the `SCO5_CLOCK` stuff
* `libntp/systime.c`: `SCO5_CLOCK` stuff
  * (`get_systime`): Use the `SCO5_CLOCK` stuff
  * (`adj_systime`): Use the `SCO5_CLOCK` stuff
* `ntpd/ntp_config.c`: Added `-P` option and associated baggage.
  * (`getstartup`): Update `help` text
  * (`getconfig`): Process `-P` option
  * (`getconfig`): Update `help` text
* `ntpd/ntpd.c` (`set_process_priority`): Created.
  * (`service_main`): remove process priority stuff - we want to do at after we start up the resolver, so call `set_process_priority()` after `getconfig()`.
* `ntpd/ntp_util.c` (`hourly_stats`): removed unused variable
* `libntp/ieee754io.c`: renamed `index` to `fieldindex` to avoid `index()` name clash
* `ntpd/refclock_parse.c` (`parse_start`): add initialization for Linux PPSkit
* `ntpd/ntp_io.c` (`create_sockets`): Skip interfaces that are really just aliases.
* `configure.in`: 4.0.92b
* `ntpd/ntpd.c` (`service_main`): Check for an error return from `sched_get_priority_max()`.
* `configure.in`: 4.0.92a
* `configure.in`: `configure.in` requires `autoconf` 2.13 or later.
* `acconfig.h: TERMIOS_NEEDS__SVID3`
* `configure.in`: Ditto
* `ntpd/refclock_palisade.h`: Ditto
* `include/ntp_refclock.h`: Ditto
* `ntpd/ntpd.c` (`service_main`): We want `sched_get_priority_max()`.
* `ntpd/ntp_refclock.c` (`refclock_open`): Zero the entire `c_cc[]` array.
* Updated `ansi2knr`

* * *

#### 4.0.92

**Release Date:** 1999 Feb 15

* chronolog and dumbclock refclocks
* SCO updates
* Cleanup/bugfixes
* Y2K patches
* Updated palisade driver
* Plug memory leak
* wharton kernel clock
* Oncore clock upgrades
* NMEA clock improvements
* PPS improvements
* AIX portability patches
* `ntpd/ntp_refclock.c`: Added `refclock_chronolog` and `refclock_dumbclock`.
* dropped SCO3 support `#defines`.
* changed `SCO5_TICKADJ #define` to `SCO5_OLDCLOCK`
* Added code in `libntp/systime.c` to accumulate changes until a whole tick can be added or dropped. Adjusted `gettimeofday()` output to include the contents of the accumulator.
* cleaned up `util/tickadj.c`; `tickadj -As` now does the right thing.
* `ntpq/ntpq.c`: Rename `delay()` to `auth_delay()`
* `ntpd/refclock_palisade.h`: Cleanup.
* `ntpd/ntp_refclock.c` (`refclock_ioctl`): Typo.
* `ntpd/ntp_io.c` (`create_sockets`): Only bind a given network once.
* `configure.in`: 4.0.91f
* `ntpd/refclock_parse.c` (`CLK_REALTYPE`): We really want `ttl`, not `hmode`.
* `ntpd/ntp_config.c` (`getconfig`): `mode` really should update the `ttl` member, not the `hmode` member.
* `ntpd/refclock_local.c`: More offset cleanup from Dave.
* `configure.in`: 4.0.91e
* `ntpd/refclock_local.c`: Bugfix.
* `ntpd/refclock_palisade.c`: Lint/IRIX portability cleanup
* `ntpd/refclock_palisade.h`: Re-enable the declaration of `float()`
* `ntpd/ntp_io.c` (`create_sockets`): Initialize size to 0
* `ntpd/refclock_parse.c` (`CLK_REALTYPE`): Use `hmode`, not `ttl`.
* `configure.in` (`ac_cv_var_no_parenb_ignpar`): Not under Linux.
* `ntpdc/ntpdc.c` (`my_delay`): Renamed, from `delay`.
* `configure.in`: 4.0.91d
* `ntpq/ntpq.c`: Y2K patches
* `html/driver29.htm`: New version
* `ntpd/refclock_palisade.c`: Ditto
* `ntpd/refclock_palisade.h`: Ditto
* upgrade `ansi2knr.c`
* Some stuff that Dave did.
* `configure.in`: 4.0.91c
* `ntpd/refclock_oncore.c`: Prototype cleanup. Enum cleanup.
* `ntpd/ntp_proto.c` (`clock_select`): Fix memory leak.
* `configure.in` (`ac_cv_struct_ppsclockev`): Might need `sys/time.h` to check for struct `clockppsev`. Return `pce`->`serial`, not `0;`
* `ntpd/refclock_oncore.c` (`oncore_msg_En`): Clean up.
* `ntpd/ntp_config.c` (`do_resolve_internal`): Missing `#ifdef DEBUG`
* `Makefile.am` (`SUBDIRS`): Lose authstuff
* `configure.in`: Ditto
* `configure.in`: 4.0.91b
* `ntpd/refclock_oncore.c`: use `HAVE_STRUCT_PPSCLOCKEV`
* `acconfig.h`: `HAVE_STRUCT_PPSCLOCKEV`
* `configure.in` (`ac_cv_struct_ppsclockev`): Added test
* `configure.in`: 4.0.91a
* `ntpd/refclock_nmea.c` (`nmea_receive`): Call `refclock_process()` every second (or each time a `nmea` string is received).
* `ntpd/ntp_refclock.c` (`refclock_ioctl`): Use `TIOCPPS` if we have it.
  * (refclock_ioctl): Use LDISC_CLKPPS, not LDISC_PPS when deciding how to set str.
* Lose unused `ntp_gettime()` stuff: `ntpd/ntp_loopfilter.c`, `ntpd/ntp_request.c`, `ntpd/refclock_local.c`.
* `ntpd/refclock_shm.c` (`shm_poll`): Fix the `refclock_process()` call.
* `ntpd/refclock_oncore.c`: patches and cleanup
* `configure.in`: ioctl/PPS checks, ONCORE cleanup
* `acconfig.h`: ONCORE cleanup
* `configure.in` (`CFLAGS`): `cc` on Sequent wants `-Wc,+abi-socket`. We also need to figure out why `-lsocket` isn't being detected; `-lsocket` is needed.
* AIX portability patches, header cleanup. `include/ntp_stdlib.h`, `ntptrace/ntptrace.c`, `ntpdate/ntpdate.c`, `ntpd/refclock_true.c`, `ntpd/refclock_mx4200.c`, `ntpd/refclock_jupiter.c`, `libntp/msyslog.c`.

* * *

#### 4.0.91

**Release Date:** 1999 Jan 10

* New ONCORE driver
* New MX4200 driver
* Palisade improvements
* `config` file bugfixes and problem reporting
* `autoconf` upgrade and cleanup
* HP-UX, IRIX lint cleanup
* AIX portability patches
* NT cleanup
* `include/ntp_stdlib.h: msyslog()` is declared differently if we're not `__STDC__`.
* `include/ntp_types.h`: It's `HAVE_PROTOTYPES`, not `USE_PROTOTYPES`.
* `include/ntp_machine.h`: Ditto.
* `configure.in`: Upgrade to autoconf-2.13. Do the prototypes check much earlier, as it might alter `CFLAGS` and things which will affect other tests.
* `ntpd/ntp_request.c` (`do_conf`): The problem was with a template for `version` on an IRIX C compiler.
* `libntp/authkeys.c: #include config.h` first.
* `util/tickadj.c` (`main`): `return()` instead of `exit()`.
* `ntpd/ntp_request.c` (`do_conf`): Disambiguate `||`.
* `ntpd/ntp_proto.c` (`clock_select`): Initialize variables.
* `scripts/ntpver.in`: Use `PATH_SH`
* `configure.in` (`PATH_SH`): Added.
* `configure.in`: 4.0.90h
* `html/driver30.htm`: Updated.
* `html/refclock.htm`: Refer to driver30
* `ntpd/refclock_oncore.c`: Vastly improve and make less FreeBSD centric.
* `include/ntp.h`: Portability/`lint` patches
* `libntp/binio.c`, `libntp/caljulian.c`, `libntp/caltontp.c`, `libntp/ieee754io.c`, `libntp/md5c.c`, `libntp/mfp_mul.c`, `libntp/msyslog.c`, `libntp/statestr.c`, `libntp/systime.c`, `libparse/clk_trimtsip.c`, `libparse/data_mbg.c`, `libparse/parse.c`, `ntpd/ntp_control.c`, `ntpd/ntp_filegen.c`, `ntpd/ntp_intres.c`, `ntpd/ntp_io.c`, `ntpd/ntp_peer.c`, `ntpd/ntp_proto.c`, `ntpd/ntp_util.c`, `ntpd/ntpd.c`, `ntpd/refclock_arc.c`, `ntpd/refclock_chu.c`, `ntpd/refclock_datum.c`, `ntpd/refclock_leitch.c`, `ntpd/refclock_parse.c`, `ntpd/refclock_usno.c`, `ntpq/ntpq.c`, `util/tickadj.c`: Ditto.
* `configure.in`: 4.0.90g
* `ntpd/ntp_config.c` (`getconfig`): `MODE` was setting `ttl`, not `hmode`.
* `configure.in`: 4.0.90f
* `ntpd/refclock_mx4200.c`: New version
* `ntpd/ntp_config.c` (`do_resolve_internal`): If fork fails, say why.
* `ntpd/ntpd.c` (`ntpdmain`): `fork()` can return a `-1`. Someday we'll report this condition.
* `configure.in`: 4.0.90e
* `ntpd/refclock_palisade.c`: Reformat code so `ansi2knr` will work
* `ntpd/refclock_palisade.h`: Ditto
* `configure.in`: 4.0.90d
* `configure.in` (`CFLAGS`): Use `-O2 -g3 -n32` by default for Irix6.2 and later.
* `configure.in`: 4.0.90c
* `ntpd/refclock_oncore.c` (`oncore_msg_En`): Convert to nano
* `include/ntp_request.h` (`RM_VN_MODE`): Add version parameter, so `xntpdc` will work across v3 and v4.
* `ntpd/ntp_request.c`: Track requested version
  * Use requested version in `RM_VN_MODE`: (`req_ack`), (`more_pkt`), (`flush_pkt`)
  * (`process_private`): Get requested version
* `ntpd/ntp_intres.c` (`request`): Use default version
* `ntpdc/ntpdc.c` (`sendrequest`): Ditto
* `ntpd/refclock_palisade.c`: Lint cleanup
* `ntpd/refclock_palisade.h`: Ditto.
* `configure.in`: 4.0.90b
* New code and cleanup for the NT stuff
* `configure.in`: 4.0.90a
* `libntp/systime.c` (`step_systime`): `net_set_tod` calls `clock_settime`.
* `libntp/machines.c` (`ntp_set_tod`): Take a 2nd arg for NT.
* `include/ntp_machine.h`: `ntp_set_tod()` has 2 args always.
* `ports/winnt/bldrel.bat`: Typo.
* `ntpd/ntp_intres.c` (`findhostaddr`): `h_errno` is a `#define` under AIX.
* `configure.in`: `clock_settime` is a stub in AIX4.
* Lose `libntp.mak`: `libntp/Makefile.am` (`EXTRA_DIST`), `ntpd/Makefile.am` (`EXTRA_DIST`), `ntpdate/Makefile.am` (`EXTRA_DIST`), `ntpdc/Makefile.am` (`EXTRA_DIST`), `ntpq/Makefile.am` (`EXTRA_DIST`).

* * *

#### 4.0.90

**Release Date:** 1998 Nov 21

* Nanoseconds
* New palisade driver
* New Oncore driver
* Nano changes from Dave Mills.
* `include/ntp_machine.h`: `STREAM` also needs `HAVE_SYS_STREAM_H`
* `configure.in`: 4.0.73e14
* `util/ntptime.c` (`main`): Protect `STA_NANO`
* `ntpd/refclock_oncore.c`: General overhaul and simplifications. The new manual clarifies a lot of fine points, and the driver has been suitably simplified. Uses Site Survey if possible, otherwise does it by hand. Should also work with non-UT models, as long as they talk the Motorola Binary Protocol. The driver doesn't (need to) know where the author lives anymore.
* `ntpd/refclock_palisade.h`: New version.
* `ntpd/refclock_palisade.c`: New version.
* `configure.in`: 4.0.83e13
* `ntpdc/ntpdc_ops.c` (`clkbug`): Patches
* `ntpd/ntp_refclock.c` (`refclock_buginfo`): Patches
* `configure.in`: 4.0.83e12
* `ntpd/ntp_util.c` (`hourly_stats`): Added `prio_set` stuff.
* `ntpd/ntpd.c` (`ntpdmain`): `HAVE_SETPGRP_0` typo.
* `parseutil/dcfd.c` (`detach`): Ditto.
* `ntpd/ntp_control.c` (`ctl_putpeer`): Sometimes, peer->dstadr is NIL.
* `ntpd/ntpd.c`: Some systems use `sys/sched.h`, not `sched.h` (Irix)
* `configure.in` (`CFLAGS`): `nextstep` needs `-posix`.
* `configure.in`: 4.0.83e11
* `configure.in` (`ac_refclock_palisade`): Needs `termios`.
* `libntp/mktime.c`: Some systems need `sys/types.h`
* `configure.in`: Added `AC_TYPE_SIZE_T` and `AC_CHECK_TYPE(time_t, long)`. The `time_t` stuff should only be needed on Older machines, so the fact that I'm using a long shouldn't be a problem (hollow laugh).
* `include/l_stdlib.h`: Sometimes we need to `#include <sys/types.h>`
* `libntp/Makefile.am (../include/des.h)`: Typo.
* `ntpd/ntp_intres.c` (`request`): Accept responses back thru V2.
* `configure.in`: 4.0.83e9
* `ntpd/ntpd.c` (`catch_danger`): Added.
  * (`ntpdmain`): AIX `SIGDANGER` stuff
* Here are some patches to suppress warnings from various compilers (IRIX 5.3, MipsPro C 7.1 on IRIX 6.4, AIX 4.1) and loaders (IRIX 5.3, IRIX 6.4). Shouldn't affect functionality at all: `configure.in, include/ntp_machine.h, include/ntp_string.h, libntp/machines.c, libparse/clk_hopf6021.c, libparse/clk_trimtsip.c, ntpd/refclock_leitch.c, ntpd/refclock_palisade.c, ntpd/refclock_parse.c`.
* `configure.in`: 4.073e8
* `configure.in`: AIX4 stubs the POSIX `timer_` stuff, `sched_setscheduler`, and `mlockall`.
* `configure.in`: OpenBSD stubs the POSIX `timer_` stuff.
* `configure.in`: 4.0.73e7
* `ntpd/refclock_parse.c`: Missing declaration
* `include/README`: Remove old `MCAST` descriptions
* `include/Makefile.am` (`noinst_HEADERS`): Lose `sun-in.h`.
* `ntpdate/ntpdate.c` (`timer`): Properly format the definition.
* `configure.in`: 4.0.73e6
* `include/Makefile.am` (`noinst_HEADERS`): Renamed `in.h` to `sun-in.h`
* `configure.in`: 4.0.73e5
* `ntpd/refclock_palisade.c`: SCO patch
* `libparse/clk_trimtsip.c` (`cvt_trimtsip`): Fix rollover bug.
* Typos, cleanup, and bugfixes: `libntp/authencrypt.c, libntp/systime.c, ntpd/refclock_acts.c, ntpd/refclock_arbiter.c, ntpd/refclock_arc.c, ntpd/refclock_as2201.c, ntpd/refclock_atom.c, ntpd/refclock_chu.c, ntpd/refclock_conf.c, ntpd/refclock_datum.c, ntpd/refclock_heath.c, ntpd/refclock_hpgps.c, ntpd/refclock_irig.c, ntpd/refclock_leitch.c, ntpd/refclock_nmea.c, ntpd/refclock_palisade.c, ntpd/refclock_parse.c, ntpd/refclock_pst.c, ntpd/refclock_trak.c, ntpd/refclock_true.c, ntpd/refclock_usno.c, ntpd/refclock_wwvb.c`.
* `ntpd/ntp_timer.c` (`timer`): Typo.
* `include/ntp_refclock.h`: in `refclockstat, clockdesc` should be const.
* `ntpd/ntp_io.c` (`create_sockets`): Typo.
* `ntpd/ntp_control.c` (`free_varlist`): Use the appropriate cast when calling `free()`.
  * (`set_var`): Use char `*td` for non-const char data.
  * (`ctl_getitem`): Use char `*` for non-const data.
* `ntpd/ntpd.c`: Added `nofork` declaration.
  * (`ntpdmain`): Initialize it.
* `ntpd/ntp_config.c`: added `nofork`.
* Updated `ntp_options`.
  * (`getstartup`): Updated `usage` string. Deal with `-n` flag.
  * (`getconfig`): Ditto.
* `ntpd/ntp_io.c` (`open_socket`): Use `ntoa()` to print out the address when `bind()` fails. (in 2 places)
* Only soft-fail if an interface is unavailable.
  * (`create_sockets`): Don't `SO_REUSEADDR` if the interface is unavailable.
* `configure.in`: If we `--disable-all-clocks`, then don't enable parse clocks by default.
* `ntpd/refclock_acts.c`: Patch cleanup
* `ntpd/ntp_refclock.c`: Patch cleanup
* `ntpd/ntp_timer.c`: Patch cleanup
* `libntp/machines.c`: IRIX needs `time.h`
* `ntpd/ntpd.c` (`service_main`): Better `AIX PROCLOCK` fix.
* `include/ntpd.h` (`MAXINTERFACES`): Moved here...
* `ntpd/ntp_io.c`: From here...
  * (`create_sockets`): Only deal with `MAXINTERFACES`.
  * (`create_sockets`): Only deal with specified interfaces.
* `ntpd/ntp_config.c` (`CONFIG_LISTEN`): Added
* Added `ifnum` and `listenaddrs[]`
  * (`getconfig`): Added defn for `addr`
  * (`getconfig`): Initialize `ifnum`.
* `ntpd/ntpd.c` (`service_main`): call `init_io` after `getconfig`
* `ntpd/refclock_palisade.c`: Use `NEED_HPUX9_TIOCM_STUFF`
* `acconfig.h` (`NEED_HPUX9_TIOCM_STUFF`): Added.
* `configure.in` (`REFCLOCK_PALISADE`): Needs `termio*.h`
  * (`NEED_HPUX9_TIOCM_STUFF`): Added.
* `ntpd/ntp_io.c` (`create_sockets`): Use `strchr` instead of `strstr`.
* `libntp/mktime.c: #include <sys/types.h>`
* `libntp/ieee754io.c: #include <sys/types.h>`
* `ntpd/refclock_acts.c` (`ACTS_MAXPOLL`): 14 -> 18.
* Import `current_nextdate`
  * (`acts_receive`): Update peer->nextdate with `current_nextdate`
  * (`acts_poll`): Call `acts_timeout()` (debugging)
* `ntpd/ntp_refclock.c`: Export `current_nextdate`.
  * (`refclock_transmit`): Check peer->valid >= `NTP_SHIFT - 2`, not `>`.
  * (`refclock_transmit`): `hpoll wiggles`, update `current_nextdate`
* `ntpd/ntp_timer.c: #include ntp_refclock.h`
  * (`MODE_MANUAL`): Added.
  * (`timer`): `MODE_MANUAL `stuff
* `configure.in`: Check for `inet_ntoa` in `-lbind`.
* `ntpd/ntpd.c: #undef PROCLOCK` for AIX.
* `configure.in` (`AC_TYPE_SIZE_T`): Added.
* `configure.in`: 4.0.73e
* p`orts/winnt/`: Replaced with new code (no `SHM` or `PALISADE`)
* `configure.in`: 4.0.73d
* `include/ntp_machine.h` (`HAVE_SRANDOM`): VxWorks patches
  * (`HAVE_RANDOM`): Ditto.
  * (`CALL`): Ditto.
* `ntpd/refclock_parse.c` (`local_input`): Typo.
* `configure.in`: 4.0.73c
* PARSE patches from Frank Kardel
* `libntp/machines.c` (`ntp_set_tod`): Get it right.
* `configure.in`: 4.0.73a
* `kernel/sys/timex.h` (`MOD_CANSCALE`): Add rest of patch to handle scaling.

* * *

#### 4.0.73

**Release Date:** 

* `README.hackers` added
* PARSE driver is working again
* Solaris 2.6 has nasty kernel bugs.  DO NOT enable `pll`!
* DES is out of the distribution.
* `ntpd/ntp_loopfilter.c` (`local_clock`): `MOD_CANSCALE` patches, and be careful with the integration if we're nearly perfect.
* `util/tickadj.c` (`main`): Typo fix.
* `ntpd/ntp_io.c` (`create_sockets`): Attempt to ignore alias interfaces.
* `ntpd/ntp_refclock.c`: PPS fixes
* `ntpd/refclock_msfees.c` (`msfees_start`): Portability fixes and PPS/STREAM enhancements
* `ntpd/ntp_refclock.c` (`refclock_gtlin`): Patch.
* `libntp/buftvtots.c` (`buftvtots`): using `WORD_BIGENDIAN` instead of `XNTP_BIG_ENDIAN`
* `libparse/clk_trimtsip.c` (`getflt`): fixed `ENDIAN` issue
  * (`getdbl`): fixed `ENDIAN` issue
  * (`getint`): use `get_msb_short()`
  * (`cvt_trimtsip`): use `gpstolfp()` for conversion
* `libntp/Makefile.am` (`libntp_a_SOURCES`): added `gpstolfp.c` source
* `libntp/binio.c`: added `{get,put}_msb_{short,long}()` functions
* `include/ntp_fp.h`: added `gpstolfp()` prototype
* `include/binio.h`: added `binio MSB` prototypes
* `parseutil/testdcf.c`: signed/unsigned SYSV clock name clash fixed
* `parseutil/dcfd.c`: signed/unsigned SYSV clock name clash fixed
  * year wrapping at 1998
  * ctype macros take ints as args
* `ntptrace/ntptrace.c` (`decodeipaddr`): ctype macros take ints as args
* `ntpq/ntpq_ops.c` (`doprintpeers`): signed/unsigned
* `ntpq/ntpq.c`: ctype macros take ints as args signed/unsigned
* signed/unsigned: `ntpdc/ntpdc.c`, `ntpd/refclock_usno.c`
* `ntpd/refclock_true.c` (`true_send`): signed/unsigned, name clashes
* `ntpd/refclock_parse.c`: signed/unsigned, name clashes
* `ntpd/refclock_nmea.c` (`nmea_receive`): ctype macros take ints as args
* `ntpd/refclock_heath.c` (`heath_receive`): prototypes (signed/unsigned issues)
* signed/unsigned issues: `ntpd/refclock_arc.c`: prototypes, `ntpd/refclock_acts.c`: prototypes, `ntpd/ntpd.c: prototypes`
* prototypes (signed/unsigned issues) fix SYSV clock name clash: `ntpd/ntp_util.c` (`getauthkeys`), `ntpd/ntp_request.c`
* `ntpd/ntp_io.c` (`input_handler`): variable naming, signed/unsigned
* `ntpd/ntp_intres.c` (`readconf`): signed/unsigned issues
* `ntpd/ntp_control.c`: prototypes (signed/unsigned issues) fix SYSV clock name clash
* `ntpd/ntp_config.c`: fix SYSV clock name clash. ctype macros take ints as args
* `libparse/parsestreams.c`: dirt (debug) removed
* `libparse/parsesolaris.c`: more prototypes, fix name clashes, allow for `ansi2knr`
* `libparse/parse.c: bcopy/memcpy` cleanup, fix SYSV clock name clash
* fix SYSV clock name clash: `libparse/clk_trimtsip.c` (`cvt_trimtsip`), `libparse/clk_trimtaip.c` (`cvt_trimtaip`), `libparse/clk_schmid.c` (`cvt_schmid`), `libparse/clk_rcc8000.c` (`cvt_rcc8000`), `libparse/clk_rawdcf.c` (`cvt_rawdcf`), `libparse/clk_hopf6021.c` (`cvt_hopf6021`), `libparse/clk_dcf7000.c` (`cvt_dcf7000`), `libparse/clk_computime.c`
* ctype macros take ints as args: `libntp/octtoint.c` (`octtoint)`, `libntp/mstolfp.c` (`mstolfp`), `libntp/hextolfp.c` (`hextolfp`), `libntp/hextoint.c` (`hextoint`), `libntp/decodenetnum.c` (`decodenetnum`), `libntp/atouint.c` (`atouint`), `libntp/atolfp.c` (`atolfp`), `libntp/atoint.c` (`atoint`)
* STREAM` macro gone in favor of `HAVE_SYS_STREAM_H`: `kernel/sys/parsestreams.h, `include/parse.h: STREAM`
* `ntpd/ntp_timer.c`: prototype fixes (`ansi2knr/knr` compiler)
* `ntpd/ntp_proto.c` (`make_keylist`): type cast for `e(!!!)malloc()`
* `libparse/Makefile.am`: adjust for `ansi2knr`
* `libntp/ieee754io.c: ansi2knr` compatibility
* `include/ntp_refclock.h`: added `pps_sample()` extern declaration and added `refclock_process_offset()` extern declaration
* `include/ntp.h`: fixed function `*` prototypes
* `ntpd/refclock_parse.c` (`bind`): added input routine
  * (`local_input`): added input routine
* `ntpd/ntp_io.c (input_handler): direct input processing for refclocks to save input recv buffers
* include/ntp_refclock.h`: added int <code>io_input\(struct recvbuf *)</code> pointer to allow direct processing of read refclock data in order to save many bug recv buffers on single character input (problem with "fast" machines)
* `parse_conf.c`: conditional compile macros fixed
* Conditional compile macros fixed `printf` prototype: `parse.c, clk_trimtaip.c, clk_schmid.c:, clk_rcc8000.c, clk_hopf6021.c, clk_dcf7000.c, clk_computime.c`.
* `ntpd/refclock_palisade.c`: fixed `termio.h` / `termios.h` inclusion
* `include/ntp_refclock.h`: made `refclockproc/clockdesc` const
* `ntpd/ntp_control.c` (`ctl_putpeer`): avoided ambigous `else` (`gcc`)
* `ntpd/refclock_parse.c` (`parse_start`): added `BURST` mode initialisation
* `scripts/stats/summary.sh` (`CLOCK`): allow for Y2K log files
* `libparse/clk_rawdcf.c`: simplified condidional compile expression
* `include/Makefile.am` (`noinst_HEADERS`): added new header files `mbg_gps166.h, binio.h, ascii.h, ieee754io.h`
* `ntpdc/ntpdc.c` (`sendrequest`): fixed `info_auth_keyid` setting; it got accidentally trashed every other round
* `configure.in`: PARSE clocks are enabled by default whenever possible (`termio.h` or `termios.h` present) and removed `RAWDCF_SETDTR` feature
* `acconfig.h`: removed `RAWDCF_SETDTR` option (now implicit by compilation and run time configuration)
* `ntpd/refclock_parse.c` (`rawdcf_init`): offer a RAWDCF clock (type 14) that attempts to set the DTR modem line for receiver power
* `libparse/clk_meinberg.c` (`cvt_meinberg`): support current standard Meinberg data formats
* `libparse/clk_rawdcf.c` (`pps_rawdcf`): trigger pps on zero going edge - that is simpler wiring (Rx->DCD).
* `parseutil/testdcf.c` (`wday`): const keyword
* `parseutil/dcfd.c` (`cvt_rawdcf`): sign issues and calling interfaces
* `ntpq/ntpq.c` (`MAXVARLEN`): adjusted internal buffer length for variable values
* `ntpd/refclock_parse.c`: adjust to new io handling (fixed formats only)
  * (`mkreadable`): don't include `>"< `in readable ASCII output (-> `ntpq` parsing)
  * output debug messages to `stdout` instead of `msyslog()`
  * fixed version information string
* `ntpd/refclock_atom.c` (`pps_sample`): new auxiliary pps interface
* `libparse/parsestreams.c` (`parserput`): get event status consistent with direct calls
  * (`zs_xsisr`): simulate CARRIER status to avoid unnecessary `M_xHANGUP` events
* `libparse/parsesolaris.c` (`parserput`): get event status consistent with direct calls
  * (`zs_xsisr`): simulate CARRIER status to avoid unnecessary `M_xHANGUP` events
* `libparse/parse.c`: removed old input cruft
  * new generic input help function: (`parse_restart`), (`parse_addchar`), (`parse_end`)
  * new generic pps help function: (`pps_one`), (`pps_zero`)
* `libparse/clk_trimtsip.c` (`clock_trimtsip =`): new input handling
* `libparse/clk_trimtaip.c` (`clock_trimtaip =`): new input handling
  * (`inp_trimtaip`): new input handler
* `libparse/clk_schmid.c` (`clock_schmid =`): new input handling
  * (`inp_schmid`): new input handler
* `libparse/clk_rcc8000.c` (`clock_rcc8000 =`): new input handling
  * (`inp_rcc8000`): new input handler
* `libparse/clk_rawdcf.c` (`clock_rawdcf =`): new input handling
  * (`snt_rawdcf`): adjusted to new input handling
  * (`inp_rawdcf`): new input handler
* `libparse/clk_meinberg.c` (`clock_meinberg`): new input handling
  * (`gps_input`): new input handler
  * (`mbg_input`): new input handler
* `libparse/clk_hopf6021.c` (`clock_hopf6021 =`): new input handling
  * (`inp_hopf6021`): new input handler
* `libparse/clk_dcf7000.c` (`clock_dcf7000 =`): new input handling
  * (`inp_dcf7000`): new input handler
* `libparse/clk_computime.c` (`clock_computime =`): new input handling
  * (`inp_computime`): new input handler
* `libparse/Makefile.am`: link kernel module with `libntp.a`
* `include/parse.h` (`struct parse`): removed old data structure cruft
  * (`new input model`) new `PARSE_INP*` macros for input handling, removed old `SYNC_*` macros from old input model
  * (`struct clockformat`): removed old parse functions in favor of the new input model
  * updated prototypes
* `include/ntp_refclock.h`: prototype for `refclock_atom pps_sample()` interface
* `acconfig.h`: added `PPS_SAMPLE` define
* `configure.in` (`LIBPARSE`): added `PPS_SAMPLE` configuration `<refclock_atom aux interface>`
* `libntp/systime.c` (`adj_systime`): debug output (> level 6) for `adjtime` results
* `libntp/mfp_mul.c` (`mfp_mul`): controlled debug output
* `libntp/ieee754io.c` (`get_byte`): controlled debug output
  * (`fetch_ieee754`): ditto
  * (`put_ieee754`): ditto
* `configure.in`: document DES is not usually present.
* `configure.in`: 4.0.72h
* `authstuff/Makefile.am` (`check-local-rsn`): `check-local` doesn't work with `RSAREF`.
* `libntp/machines.c`: the `settime()` choices were ordered badly.
* `configure.in` (`ac_cv_var_no_parenb_ignpar`): Undo the kernel PLL block I just installed - Dave wants to control this via `KERNEL_FLL_BUG`.
* `libntp/Makefile.am` (`libntp_a_DEPENDENCIES`): Set per `libntp_a_LIBADD`
* `configure.in`: Do a better job of blocking kernel PLL under solaris2.6.
* `configure.in`: 4.0.72f
  * (`ac_cv_struct_nlist_n_un`): Don't look for `ntp_adjtime` or `ntp_gettime` under solaris2.6.
* `ntpd/ntp_proto.c` (`process_packet`): Give verbose error messages
* `include/global.h` (`PROTOTYPES`): Drive via `HAVE_PROTOTYPES`.
* `configure.in` (`ac_cv_var_use_des`): Added. 4.0.72e.
* `libntp/Makefile.am` (`libntp_a_LIBADD`): Added `DESOBJS`
* `ntpd/refclock_arc.c` (`arc_receive`): Typo.
* `configure.in` (`ac_refclock_chu`): `AUDIO_CHU` support. Disabled by default, and currently only supported on SunOS and Solaris.
* `acconfig.h: AUDIO_CHU`
* `libntp/Makefile.am` (`EXTRA_DIST`): Added `mktime.c`
* `configure.in: AC_REPLACE_FUNCS(mktime)`.
  * (`--enable-dst-minutes=60`): Added, for (missing) `mktime()`.
* `ntpd/refclock_heath.c` (`heath_receive`): Use `mktime()` instead of the old hack.
* `configure.in` (`LIBOBJS`): Hack it before `AC_OUTPUT` to deal with `ANSI2KNR`-filtering rules.
* `libntp/strerror.c`: ANSIfy `strerror`'s definition.
* `libntp/statestr.c`: Only `#include <config.h>` if `HAVE_CONFIG_H` is `#define`'d.
* `configure.in`: Cygwin needs to check for the `advapi32` library. NT doesn't support a `root` user, so don't bother with `getuid()`. Also, don't bother with `umask()`.
* cygwin32 patches: `ntpd/ntp_io.c, ntpd/ntp_proto.c, ntpd/ntpd.c, ntpd/ntp_timer.c, ntpdate/ntpdate.c, libntp/machines.c, libntp/systime.c, include/ntp_machine.h, include/ntp_unixtime.h`.
* `configure.in` (`ac_cv_make_tickadj`): Added. Now that `tickadj` is the only(?) utility that cares about `tick` and `tickadj`, we don't need to have `NOKMEM` and no `PRESET_*` be fatal.
* `ntpd/ntp_loopfilter.c` (`local_clock`): Patch `STA_FLL` check
* various: Renamed `ACTS` to `CLOCK_ACTS, ARBITER` to `CLOCK_ARBITER, ARCRON_MSF` to `CLOCK_ARCRON_MSF, AS2201` to `CLOCK_AS2201, BANC` to `CLOCK_BANC, DATUM` to `CLOCK_DATUM, GPSVME` to `CLOCK_GPSVME, HEATH` to `CLOCK_HEATH, HPGPS` to `CLOCK_HPGPS, IRIG` to `CLOCK_IRIG, JUPITER` to `CLOCK_JUPITER, LEITCH` to `CLOCK_LEITCH, MSFEES` to `CLOCK_MSFEES, MX4200` to `CLOCK_MX4200, NMEA` to `CLOCK_NMEA, PALISADE` to `CLOCK_PALISADE, PARSE` to `CLOCK_PARSE, PPS720` to `CLOCK_PPS720, PST` to `CLOCK_PST, PTBACTS` to `CLOCK_PTBACTS, SHM_CLOCK` to `CLOCK_SHM, ONCORE` to `CLOCK_ONCORE, TPRO` to `CLOCK_TPRO, TRAK` to `CLOCK_TRAK, TRUETIME` to `CLOCK_TRUETIME, USNO` to `CLOCK_USNO, WWVB` to `CLOCK_WWVB`.
* `Makefile.am` (`ETAGS_ARGS`): Added `acconfig.h`
* various: Renamed `LOCAL_CLOCK` to `CLOCK_LOCAL`.
* `configure.in`: First cut at `*-pc-cygwin32` support
* `configure.in`: gdt-surveying code is gone. Sigh.
* many places: Renamed `ATOM` to `CLOCK_ATOM`
* `ntpd/ntp_timer.c` (`timer`): Only call `refclock_transmit` if `REFCLOCK` is `#define`'d.
* `configure.in (ntp_refclock)`: Use `CLOCK_CHU`, which no longer needs any special headers.
* `ntpd/refclock_chu.c`: Call it `CLOCK_CHU`
  * (`chu_receive`): Define it correctly.
* `include/winnt/sys/time.h` (`gettimeofday`): Prototypes are OK.
  * (`settimeofday`): Prototypes are OK.
* `ntpq/ntpq_ops.c`: `varlist` name and value aren't const.
* `ntpdc/ntpdc_ops.c` (`fudge`): The flags are `u_val`, not `val`.
* `ntpdc/ntpdc.c`: const cleanup, exit cleanup.
* `ntpd/refclock_wwvb.c` (`wwvb_receive`): Move the definition of `tz` somewhere more normal.
* `ntpd/ntp_request.c` (`do_trustkey`): `kp` gets `u_long` data, not `u_int32` (but Harlan thinks this patch may be wrong).
* `ntpd/ntp_refclock.c` (`refclock_process`): `clocktime` needs `offset.l_ui`, not `offset.l_i`.
* `ntpd/ntp_control.c` (`set_var`): `t` isn't const.
* `libntp/a_md5encrypt.c` (`session_key`): Cast 2nd arg to `MD5auth_setkey`.
* `include/ntpd.h: ctl_var`'s text field isn't const.
* `include/ntp_refclock.h: clockdesc` isn't const.
* `ntpd/ntp_loopfilter.c` (`local_clock`): Limit `ntv.constant` to `MAXTC`, and log error returns from `ntp_adjtime`.
* `configure.in` (`ac_cv_var_kernel_fll_bug`): `KERNEL_FLL_BUG`
* `acconfig.h: KERNEL_FLL_BUG`: added.
* `ntpd/ntp_loopfilter.c` (`local_clock`): Only avoid `STA_FLL` if `KERNEL_FLL_BUG` is `#define`'d (Solaris2.6)
* `automake-1.2d.patches`: Added `ansi2knr.o` rules.
* `ntpd/refclock_tpro.c: P()` stuff
* `configure.in`: Improve the `${CC} -pipe` test (cygwin-32's `gcc -pipe` silently does nothing).

* * *

#### 4.0.72

**Release Date:** 1998 Feb 18

* K&R C compiling should work again.
* IRIG patches.
* MX4200 driver patches.
* Jupiter driver added.
* Palisade driver added.  Needs work (ANSI, `ntoh/hton, sizeof` double, ???)
* `configure.in: AC_REPLACE_FUNCS(strerror)`, check for `poll.h`, and deal with the `--enable-JUPITER` stuff.
* `libntp/Makefile.am` (`libntp_a_LIBADD`): Added (for `strerror` support).
* `libntp/clocktypes.c`: Added `REFCLK_GPS_JUPITER`.
* `ntpdate/ntpdate.c`: `poll()` support
* `ntpd/Makefile.am`: Add `refclock_jupiter.c`
* `ntpd/refclock_conf.c`: Added `refclock_jupiter`
* `ntpd/refclock_mx4200.c` (`mx4200_pps`): Bugfixes.
* `include/ntp.h` (`REFCLK_GPS_JUPITER`): Added, and bumped `REFCLK_MAX`.
* `ntpd/ntp_proto.c: P()`
* `include/ntp_types.h`: Added `P()` prototyping hack back in.
* Ditto: `include/parse.h, include/ntpd.h, include/ntp_unixtime.h, include/ntp_stdlib.h, include/ntp_select.h, include/ntp_refclock.h, include/ntp_fp.h, include/md5.h, include/ntp_filegen.h, include/ntp_calendar.h, include/l_stdlib.h`.
* Sometimes, `TIOCMBIS` is in `sys/ioctl.h`: `configure.in` (`ACTS`), `configure.in (HEATH)`, `configure.in (PTBACTS)`, `configure.in (USNO)`.
* `ntpd/refclock_irig.c (irig_rf)`: Rename `sincos[]` to `sin_cos[]`.
* Use `random` or `mrand48`: `include/ntp.h (RANDPOLL)`,  `ntpd/ntp_config.c (do_resolve_internal)`, `ntpd/ntp_peer.c (unpeer)`, `ntpd/ntp_proto.c (make_keylist)`.
* `ntpd/ntpd.c (xntpdmain)`: Use `srandom` or `srand48`.
* `configure.in`: Look for `{s,}random()` and `[ms]rand48()`.
* Renamed `restrict()`: `ntpd/ntp_restrict.c (hack_restrict)`, `include/ntpd.h`, `ntpd/ntp_request.c (do_restrict)`, `ntpd/ntp_config.c (getconfig)`, `ntpd/ntp_io.c (create_sockets)`.
* `ntpd/refclock_irig.c`: Allow either `<sun/audioio.h>` or `<sys/audioio.h>`. From Dave Mills.
* `configure.in`: Under SunOS, it's `sun/audioio.h`.
* Updated header file info: `html/driver6.html`,  `html/irig.html`.
* `configure.in: sys/bsd_audioirig.h` replaced with `sys/audioio.h` for new irig driver that Dave installed.
* Many places: Lose the `P(())` prototype stuff
* `util/tickadj.c (writevar)`: Make offset an `off_t`
  * (`readvar`): Ditto
  * (`getoffsets`): Make offsets `off_t`
* `adjtimed/adjtimed.c (GetClockRate)`: Fix `lseek` arg 2.
  * (`SetClockRate`): Ditto
* Many things in many places from many people.
* `configure.in`: Added `AC_TYPE_OFF_T`
* `ntpd/refclock_palisade.c`: ANSIfied.
* `configure.in (AM_C_PROTOTYPES)`: Added.
* `Makefile.am (AUTOMAKE_OPTIONS)`: Added `ansi2knr`.