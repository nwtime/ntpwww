---
title: "4.2.4-series Changelog"
description: "The changelogs for NTP versions 4.2.4 through 4.2.4p8."
type: archives
---

* [4.2.4p8](#424p8)
* [4.2.4p7](#424p7)
* [4.2.4p6](#424p6)
* [4.2.4p5](#424p5)
* [4.2.4p4](#424p4)
* [4.2.4p3](#424p3)
* [4.2.4p2](#424p2)
* [4.2.4p1](#424p1)
* [4.2.4p0](#424p0)
* [4.2.4](#424)

* * *

#### 4.2.4p8

**Release Date:** 2009 Dec 08

* [Sec 1331: DoS with mode 7 packets](/support/securitynotice/ntpbug1331/) - [CVE-2009-3563](https://nvd.nist.gov/vuln/detail/CVE-2009-3563)

* * *

#### 4.2.4p7

**Release Date:** 2009 May 18

* [Sec 1151: Remote exploit if autokey is enabled](/support/securitynotice/ntpbug1151/) - [CVE-2009-1252](https://nvd.nist.gov/vuln/detail/CVE-2009-1252)
* [Bug 1187: Update the copyright date.](https://bugs.ntp.org/show_bug.cgi?id=1187)
* [Bug 1191: ntpd fails on Win2000 - "Address already in use" after fix for Sec 1149](https://bugs.ntp.org/show_bug.cgi?id=1191)

* * *

#### 4.2.4p7-RC7

**Release Date:** 2009 May 12 

* ntp.isc.org -> ntp.org cleanup.
* [Bug 1178: Use prior FORCE_DNSRETRY behavior as needed at runtime, add configure --enable-ignore-dns-errors to be even more stubborn](https://bugs.ntp.org/show_bug.cgi?id=1178)

* * *

#### 4.2.4p7-RC6

**Release Date:** 2009 May 08

* [Bug 784: Make --enable-linuxcaps the default when available](https://bugs.ntp.org/show_bug.cgi?id=784)
* [Bug 1179: error messages for -u/--user and -i lacking droproot](https://bugs.ntp.org/show_bug.cgi?id=1179)
* Updated JJY reference clock driver from Takao Abe
* [Bug 1071: Log a message and exit before trying to use FD_SET with a descriptor larger than FD_SETSIZE, which will corrupt memory](https://bugs.ntp.org/show_bug.cgi?id=1071)
* On corruption of the iface list head in `add_interface`, log and exit

* * *

#### 4.2.4p7-RC5

**Release Date:** 2009 May 02

* [Bug 1172: 4.2.4p7-RC{3,4} fail to build on linux.](https://bugs.ntp.org/show_bug.cgi?id=1172)
* `flock-build` script unportable `set -m` use removed

* * *

#### 4.2.4p7-RC4

**Release Date:** 2009 Apr 29

* [Bug 1167: use gcc -Winit-self only if it is understood](https://bugs.ntp.org/show_bug.cgi?id=1167)

* * *

#### 4.2.4p7-RC3

**Release Date:** 2009 Apr 22

* [Bug 787: Bug fixes for 64-bit time_t on Windows](https://bugs.ntp.org/show_bug.cgi?id=787)
* [Bug 813: Conditional naming of Event](https://bugs.ntp.org/show_bug.cgi?id=813)
* [Bug 1147: System errors should be logged to msyslog()](https://bugs.ntp.org/show_bug.cgi?id=1147)
* [Bug 1155: Fix compile problem on Windows with VS2005](https://bugs.ntp.org/show_bug.cgi?id=1155)
* [Bug 1156: lock_thread_to_processor() should be declared in header](https://bugs.ntp.org/show_bug.cgi?id=1156)
* [Bug 1157: quiet OpenSSL warnings, clean up configure.ac](https://bugs.ntp.org/show_bug.cgi?id=1157)
* [Bug 1158: support for aix6.1](https://bugs.ntp.org/show_bug.cgi?id=1158)
* [Bug 1160: MacOS X is like BSD regarding F_SETOWN](https://bugs.ntp.org/show_bug.cgi?id=1160)

* * *

#### 4.2.4p7-RC2

**Release Date:** 2009 Apr 09

* [Sec 1144: limited buffer overflow in ntpq.](https://bugs.ntp.org/show_bug.cgi?id=1144)  [CVE-2009-0159](https://nvd.nist.gov/vuln/detail/CVE-2009-0159)
* [Sec 1149: use SO_EXCLUSIVEADDRUSE on Windows](https://bugs.ntp.org/show_bug.cgi?id=1149)

* * *

#### 4.2.4p7-RC1

**Release Date:** 2009 Mar 30

* [Bug 1131: UDP sockets should not use SIGPOLL on Solaris.](https://bugs.ntp.org/show_bug.cgi?id=1131)
* build system email address cleanup
* [Bug 774: parsesolaris.c does not compile under the new Solaris](https://bugs.ntp.org/show_bug.cgi?id=774)
* [Bug 873: Windows serial refclock proper TTY line discipline emulation](https://bugs.ntp.org/show_bug.cgi?id=873)
* [Bug 1014: Enable building with VC9 (in Visual Studio 2008, Visual C++ 2008, or SDK)](https://bugs.ntp.org/show_bug.cgi?id=1014)
* [Bug 1117: Deferred interface binding under Windows works only correctly if FORCE_DNSRETRY is defined](https://bugs.ntp.org/show_bug.cgi?id=1117)
* [BUG 1124: Lock QueryPerformanceCounter() client threads to same CPU](https://bugs.ntp.org/show_bug.cgi?id=1124)
* `DPRINTF` macro made safer, always evaluates to a statement and will not misassociate an else which follows the macro.

* * *

#### 4.2.4p6

**Release Date:** 2009 Jan 08

* [Sec 1111: Fix incorrect check of EVP_VerifyFinal()'s return value.](https://bugs.ntp.org/show_bug.cgi?id=1111)
* [Bug 1113: Fixed build errors with recent versions of openSSL.](https://bugs.ntp.org/show_bug.cgi?id=1113)
* Update the copyright year.

* * *

#### 4.2.4p5

**Release Date:** 2008 Aug 17

* [BUG 1051: Month off by one in leap second message written to clockstats file fixed.](https://bugs.ntp.org/show_bug.cgi?id=1051)
* [Bug 1038: Built-in getpass() function also prompts for password if not built with DEBUG.](https://bugs.ntp.org/show_bug.cgi?id=1038)
* [Bug 1000: allow implicit receive buffer allocation for Windows. fixes startup for windows systems with many interfaces. reduces dropped packets on network bursts. additionally fix timer() starvation during high load.](https://bugs.ntp.org/show_bug.cgi?id=1000)
* [Bug 997: ntpdate buffer too small and unsafe.](https://bugs.ntp.org/show_bug.cgi?id=997)
* [Bug 993: Fix memory leak when fetching system messages.](https://bugs.ntp.org/show_bug.cgi?id=993)
* [Bug 990: drop minimum time restriction for interface update interval.](https://bugs.ntp.org/show_bug.cgi?id=990)
* [Bug 987: Wake up the resolver thread/process when a new interface has become available.](https://bugs.ntp.org/show_bug.cgi?id=987)
* [Bug 982: ntpdate(and ntptimeset) buffer overrun if HAVE_POLL_H isn't set (dup of 908).](https://bugs.ntp.org/show_bug.cgi?id=982)
* [Bug 979: Provide ntptimeval if it is not otherwise present.](https://bugs.ntp.org/show_bug.cgi?id=979)
* [Bug 977: Fix mismatching #ifdefs for builds without IPv6.](https://bugs.ntp.org/show_bug.cgi?id=977)
* [Bug 970: Lose obsolete -g flag to ntp-keygen.](https://bugs.ntp.org/show_bug.cgi?id=970)
* [Bug 967: preemptable associations are lost forever on a step.](https://bugs.ntp.org/show_bug.cgi?id=967)
* [Bug 964: Change *-*-linux* to *-*-*linux* to allow for uclinux.](https://bugs.ntp.org/show_bug.cgi?id=964)
* [Bug 963: get_systime() is too noisy.](https://bugs.ntp.org/show_bug.cgi?id=963)
* [Bug 961: refclock_tpro.c:tpro_poll() calls refclock_receive() twice.](https://bugs.ntp.org/show_bug.cgi?id=961)
* [Bug 960: spurious syslog:crypto_setup:spurious crypto command](https://bugs.ntp.org/show_bug.cgi?id=960)
* [Bug 959: Refclock on Windows not properly releasing recvbuffs.](https://bugs.ntp.org/show_bug.cgi?id=959)
* [Bug 957: Windows only: Let command line parameters from the Windows SCM GUI override the standard parameters from the ImagePath registry key.](https://bugs.ntp.org/show_bug.cgi?id=957)
* [Bug 952: Use md5 code with a friendlier license.](https://bugs.ntp.org/show_bug.cgi?id=952)
* [Bug 940: ntp-keygen uses -v.  Disallow it as a shortcut for --version.](https://bugs.ntp.org/show_bug.cgi?id=940)
* [Bug 931: Require -lreadline to be asked for explicitly.](https://bugs.ntp.org/show_bug.cgi?id=931)
* [Bug 929: int32_t is undefined on Windows.  Casting wrong.](https://bugs.ntp.org/show_bug.cgi?id=929)
* [Bug 928: readlink missing braces.](https://bugs.ntp.org/show_bug.cgi?id=928)
* [Bug 918: Only use a native md5.h if MD5Init() is available.](https://bugs.ntp.org/show_bug.cgi?id=918)
* [Bug 917: config parse leaves files open](https://bugs.ntp.org/show_bug.cgi?id=917)
* [Bug 916: 'cryptosw' is undefined if built without OpenSSL.](https://bugs.ntp.org/show_bug.cgi?id=916)
* [Bug 915: ntpd cores during processing of x509 certificates.](https://bugs.ntp.org/show_bug.cgi?id=915)
* [Bug 912: detect conflicting enable/disable configuration on interfaces sharing an IP address](https://bugs.ntp.org/show_bug.cgi?id=912)
* [Bug 911: Fix error message in cmd_args.c.](https://bugs.ntp.org/show_bug.cgi?id=911)
* [Bug 909: Fix int32_t errors for ntohl().](https://bugs.ntp.org/show_bug.cgi?id=909)
* [Bug 908: ntpdate crashes sometimes.](https://bugs.ntp.org/show_bug.cgi?id=908)
* [Bug 905: ntp_crypto.c fails to compile without -DDEBUG.](https://bugs.ntp.org/show_bug.cgi?id=905)
* [Bug 899: Only show -i/--jaildir -u/--user options if we HAVE_DROPROOT.](https://bugs.ntp.org/show_bug.cgi?id=899)
* [Bug 897: Check RAND_status() - we may not need a .rnd file.](https://bugs.ntp.org/show_bug.cgi?id=897)
* [Bug 895: Log assertion failures via syslog(), not stderr.* ](https://bugs.ntp.org/show_bug.cgi?id=895)
* [Bug 894: Initialize keysdir before calling crypto_setup().](https://bugs.ntp.org/show_bug.cgi?id=894)
* [Bug 891: 'restrict' config file keyword does not work (partial fix).](https://bugs.ntp.org/show_bug.cgi?id=891)
* [Bug 890: the crypto command seems to be required now.](https://bugs.ntp.org/show_bug.cgi?id=890)
* [Bug 887: Fix error in ntp_types.h (for sizeof int != 4).](https://bugs.ntp.org/show_bug.cgi?id=887)
* [Bug 880: bug fixes for Windows build](https://bugs.ntp.org/show_bug.cgi?id=880)
* [Bug 864: Place ntpd service in maintenance mode if using SMF on Solaris](https://bugs.ntp.org/show_bug.cgi?id=864)
* [Bug 862: includefile nesting; preserve phonelist on reconfig.](https://bugs.ntp.org/show_bug.cgi?id=862)
* [Bug 861: Leap second cleanups from Dave Mills.](https://bugs.ntp.org/show_bug.cgi?id=861)](https://bugs.ntp.org/show_bug.cgi?id=861)
* [Bug 858: recent leapfile changes broke non-OpenSSL builds.](https://bugs.ntp.org/show_bug.cgi?id=858)
* [Bug 857: ntpdate debug mode adjusts system clock when it shouldn't.](https://bugs.ntp.org/show_bug.cgi?id=857)
* [Bug 853: get_node() must return a pointer to maximally-aligned memory.](https://bugs.ntp.org/show_bug.cgi?id=853)
* [Bug 850: Fix the wander threshold parameter on the driftfile command.](https://bugs.ntp.org/show_bug.cgi?id=850)
* [Bug 846: Correct includefile parsing.](https://bugs.ntp.org/show_bug.cgi?id=846)
* [Bug 843: Windows Completion port code was incorrectly merged from -stable.](https://bugs.ntp.org/show_bug.cgi?id=843)
* [Bug 841: Obsolete the "dynamic" keyword and make deferred binding to local interfaces the default.](https://bugs.ntp.org/show_bug.cgi?id=841)
  * Emit a warning if that keyword is used for configuration.
* [Bug 840: do fudge configuration AFTER peers (thus refclocks) have been configured.](https://bugs.ntp.org/show_bug.cgi?id=840)
* [Bug 839: Crypto password not read from ntp.conf.](https://bugs.ntp.org/show_bug.cgi?id=839)
* [Bug 833: ntpq config keyword is quote-mark unfriendly.](https://bugs.ntp.org/show_bug.cgi?id=833)
* [Bug 832: Add libisc/log.c headers to the distribution.](https://bugs.ntp.org/show_bug.cgi?id=832)
* [Bug 830: Fix the checking order of the interface options.](https://bugs.ntp.org/show_bug.cgi?id=830)
* [Bug 828: refid string not being parsed correctly.](https://bugs.ntp.org/show_bug.cgi?id=828)
* [Bug 827: New parsing code does not handle "fudge" correctly.](https://bugs.ntp.org/show_bug.cgi?id=827)
* [Bug 826: Fix redefinition of PI.](https://bugs.ntp.org/show_bug.cgi?id=826)
* [Bug 825: Correct logconfig -/+ keyword processing.](https://bugs.ntp.org/show_bug.cgi?id=825)
* [Bug 824: New parser code has some build problems with the SIM code.](https://bugs.ntp.org/show_bug.cgi?id=824)
* [Bug 822: set progname once, early.](https://bugs.ntp.org/show_bug.cgi?id=822)
* [Bug 819: remove erroneous #if 0 in Windows completion port code.](https://bugs.ntp.org/show_bug.cgi?id=819)
* [Bug 817: Use longnames for setting ntp variables on the command-line; Allowing '-v' with and without an arg to disambiguate usage is error-prone.](https://bugs.ntp.org/show_bug.cgi?id=817)
* [Bug 815: Fix warning compiling 4.2.5p22 under Windows with VC6.](https://bugs.ntp.org/show_bug.cgi?id=815)
* [Bug 812: ntpd should drop supplementary groups.](https://bugs.ntp.org/show_bug.cgi?id=812)
* [Bug 810: Fix ntp-keygen documentation.](https://bugs.ntp.org/show_bug.cgi?id=810)
* [Bug 808: Only write the drift file if we are in state 4.](https://bugs.ntp.org/show_bug.cgi?id=808)
* [Bug 798: ntpq \[p typo crashes ntpq/ntpdc.](https://bugs.ntp.org/show_bug.cgi?id=798)
* [Bug 796: Clean up duplicate #defines in ntp_control.c.](https://bugs.ntp.org/show_bug.cgi?id=796)
* [Bug 795: Moved declaration of variable to top of function.](https://bugs.ntp.org/show_bug.cgi?id=795)
* [Bug 788: Update macros to support VS 2005.](https://bugs.ntp.org/show_bug.cgi?id=788)
* [Bug 787: Bug fixes for 64-bit time_t on Windows.](https://bugs.ntp.org/show_bug.cgi?id=787)
* [Bug 786: Fix refclock_bancomm.c on Solaris.](https://bugs.ntp.org/show_bug.cgi?id=786)
* [Bug 782: Remove P() macros from Windows files.](https://bugs.ntp.org/show_bug.cgi?id=782)
* [Bug 778: ntpd fails to lock with drift=+500 when started with drift=-500.](https://bugs.ntp.org/show_bug.cgi?id=778)
* [Bug 774: parsesolaris.c does not compile under the new Solaris.](https://bugs.ntp.org/show_bug.cgi?id=774)
* [Bug 771: compare scopeid if available for IPv6 addresses](https://bugs.ntp.org/show_bug.cgi?id=771)
* [Bug 767: Fast sync to refclocks wanted.](https://bugs.ntp.org/show_bug.cgi?id=767)
* [Bug 764: When looking for -lreadline support, also try using -lncurses.](https://bugs.ntp.org/show_bug.cgi?id=764)
* [Bug 757 Lose ULONG_CONST().](https://bugs.ntp.org/show_bug.cgi?id=757)
* [Bug 756: Require ANSI C (function prototypes).](https://bugs.ntp.org/show_bug.cgi?id=756)
* [Bug 752: QoS: add parse/config handling code.](https://bugs.ntp.org/show_bug.cgi?id=752)
* [Bug 740: Fix kernel/daemon startup drift anomaly.](https://bugs.ntp.org/show_bug.cgi?id=740)
* [Bug 713: Fix bug reporting information.](https://bugs.ntp.org/show_bug.cgi?id=713)
* [Bug 698: timeBeginPeriod is called without timeEndPeriod in some NTP tools.](https://bugs.ntp.org/show_bug.cgi?id=698)
* [Bug 634: Re-instantiate syslog() and logfiles after the daemon fork.](https://bugs.ntp.org/show_bug.cgi?id=634)
* [Bug 629: Undo bug #629 fixes as they cause more problems than were  being solved](https://bugs.ntp.org/show_bug.cgi?id=629)
* [Bug 604: ntpd regularly dies on linux/alpha.](https://bugs.ntp.org/show_bug.cgi?id=604)
* [Bug 592: Trimble Thunderbolt GPS support.](https://bugs.ntp.org/show_bug.cgi?id=592)
* [Bug 569: Use the correct precision for the Leitch CSD-5300.](https://bugs.ntp.org/show_bug.cgi?id=569)
* [Bug 542: Tolerate missing directory separator at EO statsdir.](https://bugs.ntp.org/show_bug.cgi?id=542)
* [Bug 532: nptdate timeout is too long if several servers are supplied.](https://bugs.ntp.org/show_bug.cgi?id=532)
* [Bug 450: Windows only: Under original Windows NT we must not discard the wildcard socket to workaround a bug in NT's getsockname().](https://bugs.ntp.org/show_bug.cgi?id=450)
* [Bug 376/214: Enhancements to support multiple if names and IP addresses.](https://bugs.ntp.org/show_bug.cgi?id=376)
* much cleanup, fixes, and changes from Dave Mills.
* `ntp_control.c: LEAPTAB` is a filestamp, not an unsigned.  From Dave Mills.
* `ntp_config.c: ntp_minpoll` fixes from Dave Mills.
* `ntp-keygen` updates from Dave Mills.
* refresh epoch, throttle, and leap cleanup from Dave Mills.
* Documentation cleanup from Dave Mills.
* Clean up the `logfile/syslog` setup.
* The `-e` flag to `ntp-keygen` can write GQ keys now, too.
* `ntp_proto.c: sys_survivors` and `hpoll` cleanup from Dave Mills.
* `ntp_loopfilter.c: sys_poll` cleanup from Dave Mills.
* `refclock_wwv.c`: maximum-likelihood digit and DSYNC fixes from Dave Mills.
* `ntp_config.c`: [CID 48] missing `else` clause.
* Rename the `ntpq config` keyword to `:config`.
* Dave Mills shifted some orphan processing.
* Fix typos in the [Bug 963](https://bugs.ntp.org/show_bug.cgi?id=963) patch.
* bootstrap: squawk if `genver` fails.  Use `-f` with `cp` in case Dave does a `chown`.
* Remove obsolete simulator command-line options.
* `ntp_request.c`: [CID 36] zero `sin_zero`.
* Changes from Dave Mills:
  - `ntp_util.c`: cleanup.
  - `ntp_timer.c`: watch the non-burst packet rate.
  - `ntp_request.c`: cleanup.
  - `ntp_restrict.c`: `RES_LIMITED` cleanup.
  - `ntp_proto.c`: `RES_LIMITED`, rate buckets, counters, overall cleanup.
  - `ntp_peer.c`: disallow `peer_unconfig()`.
  - `ntp_monitor.c`: `RES_LIMITED` cleanup.
  - `ntp_loopfilter.c`: poll interval cleanup.
  - `ntp_crypto.c`: volley -> retry.  Cleanup TAI leap message.
  - `ntp_config`: average and minimum are <sup>^</sup>2 values.
  - `ntpdc`: `unknownversion` is really "declined", not "bad version".
  - Packet retry cleanup.
* Added `HAVE_INT32_T` to the Windows `config.h` to avoid duplicate definitions.
* `ntpd/ntp_timer.c`: add missing `sys_tai` parameter for `debug printf`
* Work around a `VPATH` difference in FreeBSD's `make` command.
* Update bugreport URL.
* Update `-I` documentation.
* A bug in the application of the negative-sawtooth for 12 channel receivers.
* The removal of unneeded startup code used for the original LinuxPPS, it now conforms to the PPSAPI and does not need special code.
* `ntp-keygen.c:` Coverity fixes [CID 33,47].
* Volley cleanup from Dave Mills.
* Fuzz cleanup from Dave Mills.
* `ntpsim.c`: add missing protypes and fix [CID 34], a nit.
* Upgraded bison at UDel.
* Update `br-flock` and `flock-build` machine lists.
* Fix the `#include` order in `tickadj.c` for picky machines.
* Orphan mode and other protocol cleanup from Dave Mills.
* more cleanup to `ntp_lineeditlibs.m4`.
* Documentation updates from Dave Mills.
* `-ledit` cleanup for `ntpdc` and `ntpq`.
* Association and other cleanup from Dave Mills.
* `NTP_UNREACH` changes from Dave Mills.
* Fix the readline history test.
* Lose obsolete crypto subcommands (Dave Mills).
* WWV is an HF source, not an LF source (Dave Mills).
* Crypto lint cleanup from Dave Mills.
* Crypto cleanup from Dave Mills.
* Avoid double peer stats logging.
* `ntp-keygen` cleanup from Dave Mills.
* `libopts` needs to be built after ElectricFence.
* Calysto cleanup for `ntpq`.
* `ntp-keygen -i` takes an arg.
* Cleanup and fixes from Dave Mills.
* Improve Calysto support.
* The `revoke` parameter is a crypto command.
* The `driftfile` wander threshold is a real number.
* `ntp_io.c`: Dead code cleanup - Coverity View 19.
* Leap file related cleanup from Dave Mills.
* `ntp_peer.c`: Set `peer->srcadr` before (not after) calling `set_peerdstadr()`.
* Initialize offset in `leap_file()` - Coverity View 17.
* Use the correct stratum on KISS codes.
* Fuzz bits cleanup.
* Show more digits in some debug `printf`'s.
* Use `drift_file_sw` internally to control writing the `drift` file.
* Implement the `wander_threshold` option for the `driftfile config` keyword.
* reformat `ntp_control.c;` do not use `c++ //` comments.
* Changes from Dave Mills: in/out-bound data rates, `leapsecond` cleanup, `driftfile` write cleanup, packet buffer length checks, documentation updates.
* More assertion checks and `malloc()->emalloc()`, courtesy of Calysto.
* more leap second infrastructure fixes from Dave Mills.
* Use `emalloc()` instead of `malloc()` in `refclock_datum.c` (Calysto).
* Start using 'design by contract' assertions.
* Allow null `driftfile`.
* Use `YYERROR_VERBOSE` for the new parser, and fix related `BUILT_SOURCES`.
* Initial leap file fixes from Dave Mills.
* Use a char for `DIR_SEP`, not a string.
* driftfile maintenance changes from Dave Mills.  Use `clock_phi` instead of `stats_write_tolerance`.
* Enable debugging capability in the `config` parser.
* Have `autogen` produce writable output files.
* Cleanup `FILE *` usage after `fclose()` in `ntp_filegen.c.`
* Initial import of `libisc/log.c` and friends.
* The new `config` code missed an `#ifdef` for building without refclocks.
* Distribute some files needed by the new `config` parsing code.
* Use autogen 5.9.1.
* Fix `clktest` command-line arg processing.
* Audio documentation updates from Dave Mills.
* New `config` file parsing code, from Sachin Kamboj.
* fuzz bit cleanup from Dave Mills.
* replay cleanup from Dave Mills.
* `refclock_wwv.c` fixes from Dave Mills.
* IRIG, CHU, WWV, WWVB refclock improvements from Dave Mills.
* codec (audio) and ICOM changes from Dave Mills.
* Correctly apply negative-sawtooth for oncore 12 channel receiver.
* Startup code for original LinuxPPS removed.  LinuxPPS now conforms to the PPSAPI.
* Update the copyright year.
* Build system cleanup (make `autogen`-generated files writable).
* `ntpdate.c`: Under Windows check whether NTP port in use under same conditions as under other OSs.
* `ntpdate.c`: Fixed some typos and indents (tabs/spaces).

* * *

#### 4.2.4p4

**Release Date:** 2007 Aug 28

* [Bug 902: Fix problems with the -6 flag.](https://bugs.ntp.org/show_bug.cgi?id=902)
* [Bug 889: avoid malloc() interrupted by SIGIO risk](https://bugs.ntp.org/show_bug.cgi?id=889)
* [Bug 886: Corrected sign handling on 64bit in ntpdc loopinfo command.](https://bugs.ntp.org/show_bug.cgi?id=886)
* [Bug 885: use emalloc() to get a message at the end of the memory unsigned types cannot be less than 0](https://bugs.ntp.org/show_bug.cgi?id=885)
  * default_ai_family is a short
  * lose trailing , from enum list
  * clarify ntp_restrict.c for easier automated analysis
* [Bug 884: don't access recv buffers after having them passed to the free list.](https://bugs.ntp.org/show_bug.cgi?id=884)
* [Bug 882: allow loopback interfaces to share addresses with other interfaces.](https://bugs.ntp.org/show_bug.cgi?id=882)
* [Bug 881: Corrected display of pll offset on 64bit systems.](https://bugs.ntp.org/show_bug.cgi?id=881)
* [Bug 878: Avoid ntpdc use of refid value as unterminated string.](https://bugs.ntp.org/show_bug.cgi?id=878)
* `ntpd/refclock_parse.c`: cleanup shutdown while the file descriptor is still open.
* Updated `include/copyright.def` (owner and year).

* * *

#### 4.2.4p3

**Release Date:** 2007 Jun 29

* [Bug 863: unable to stop ntpd on Windows as the handle reference for events changed](https://bugs.ntp.org/show_bug.cgi?id=863)

* * *

#### 4.2.4p2

**Release Date:** 2007 Jun 20

* [Bug 885: use emalloc() to get a message at the end of the memory](https://bugs.ntp.org/show_bug.cgi?id=885)
  * unsigned types cannot be less than 0
  * default_ai_family is a short
  * lose trailing , from enum list
* [Bug 884: don't access recv buffers after having them passed to the free list.](https://bugs.ntp.org/show_bug.cgi?id=884)
* [Bug 882: allow loopback interfaces to share addresses with other interfaces.](https://bugs.ntp.org/show_bug.cgi?id=882)
* [Bug 854: Broadcast address was not correctly set for interface addresses](https://bugs.ntp.org/show_bug.cgi?id=854)
* [Bug 829: reduce syslog noise, while there fix Enabled/Disable logging to reflect the actual configuration.](https://bugs.ntp.org/show_bug.cgi?id=829)
* [Bug 811: ntpd should not read a .ntprc file.](https://bugs.ntp.org/show_bug.cgi?id=811)
* [Bug 795: Moved declaration of variable to top of function.](https://bugs.ntp.org/show_bug.cgi?id=795)
* [Bug 789: Fix multicast client crypto authentication and make sure arriving multicast packets do not disturb the autokey dance.](https://bugs.ntp.org/show_bug.cgi?id=789)
* [Bug 785: improve handling of multicast interfaces (multicast routers still need to run a multicast routing software/daemon)](https://bugs.ntp.org/show_bug.cgi?id=785)
* [Bug 527: Don't write from source address length to wrong location](https://bugs.ntp.org/show_bug.cgi?id=527)
* `ntpd/refclock_parse.c`: cleanup shutdown while the file descriptor is still open.
* Upgraded `autogen` and `libopts`.

* * *

#### 4.2.4p1 

**Release Date:** (skipped)

* * *

#### 4.2.4p0

**Release Date:** 2007 Mar 7

* [Bug 793: Update Hans Lambermont's email address in ntpsweep.](https://bugs.ntp.org/show_bug.cgi?id=793)
* [Bug 776: Remove unimplemented "rate" flag from ntpdate.](https://bugs.ntp.org/show_bug.cgi?id=776)
* [Bug 770: Fix numeric parameters to ntp-keygen (Alain Guibert).](https://bugs.ntp.org/show_bug.cgi?id=770)
* [Bug 768: Fix io_setbclient() error message.](https://bugs.ntp.org/show_bug.cgi?id=768)
* [Bug 765: Use net_bind_service capability on linux.](https://bugs.ntp.org/show_bug.cgi?id=765)
* [Bug 760: The background resolver must be aware of the 'dynamic' keyword.](https://bugs.ntp.org/show_bug.cgi?id=760)
* [Bug 753: make union timestamp anonymous (Philip Prindeville).](https://bugs.ntp.org/show_bug.cgi?id=753)
* [Bug 586: Avoid lookups if AI_NUMERICHOST is set.](https://bugs.ntp.org/show_bug.cgi?id=586)
* `confopt.html`: move description for `dynamic` keyword into the right section.
* pick the right type for the `recv*()` length argument.

* * *

#### 4.2.4

**Release Date:** 2006 Dec 18

* [Bug 747: Drop <NOBR> tags from ntpdc.html.](https://bugs.ntp.org/show_bug.cgi?id=747)
* [Bug 746: Expert mouseCLOCK USB v2.0 support added.](https://bugs.ntp.org/show_bug.cgi?id=746)
* [Bug 741: "burst" doesn't work with !unfit peers.](https://bugs.ntp.org/show_bug.cgi?id=741)
* [Bug 739: ntpd -x should not take an argument.](https://bugs.ntp.org/show_bug.cgi?id=739)
* [Bug 737: Some systems need help providing struct iovec.](https://bugs.ntp.org/show_bug.cgi?id=737)
* [Bug 735: Fix a make/gmake VPATH issue on Solaris.](https://bugs.ntp.org/show_bug.cgi?id=735)
* [Bug 734: setsockopt(..., IP_MULTICAST_IF, ...) fails on 64-bit platforms.](https://bugs.ntp.org/show_bug.cgi?id=734)
* [Bug 732: C-DEX JST2000 patch from Hideo Kuramatsu.](https://bugs.ntp.org/show_bug.cgi?id=732)
* [Bug 728: parse documentation fixes.](https://bugs.ntp.org/show_bug.cgi?id=728)
* [Bug 721: check for __ss_family and __ss_len separately.](https://bugs.ntp.org/show_bug.cgi?id=721)
* [Bug 718: Use the recommended type for the saddrlen arg to getsockname().](https://bugs.ntp.org/show_bug.cgi?id=718)
* [Bug 717: Fix libopts compile problem.](https://bugs.ntp.org/show_bug.cgi?id=717)
* [Bug 715: Fix a multicast issue under Linux.](https://bugs.ntp.org/show_bug.cgi?id=715)
* [Bug 714: ntpq -p should conflict with -i, not -c.](https://bugs.ntp.org/show_bug.cgi?id=714)
* [Bug 708: Use thread affinity only for the clock interpolation thread.](https://bugs.ntp.org/show_bug.cgi?id=708)
* [Bug 706: ntpd can be running several times in parallel.](https://bugs.ntp.org/show_bug.cgi?id=706)
* [Bug 704: Documentation typos.](https://bugs.ntp.org/show_bug.cgi?id=704)
* [Bug 701: coverity: NULL dereference in ntp_peer.c](https://bugs.ntp.org/show_bug.cgi?id=701)
* [Bug 695: libopts does not protect against macro collisions.](https://bugs.ntp.org/show_bug.cgi?id=695)
* [Bug 693: __adjtimex is independent of ntp_{adj,get}time.](https://bugs.ntp.org/show_bug.cgi?id=693)
* [Bug 692: sys_limitrejected was not being incremented.](https://bugs.ntp.org/show_bug.cgi?id=692)
* [Bug 691: restrictions() assumption not always valid.](https://bugs.ntp.org/show_bug.cgi?id=691)
* [Bug 690: Fix a Windows DNS lookup buffer overflow.](https://bugs.ntp.org/show_bug.cgi?id=690)
* [Bug 689: Deprecate HEATH GC-1001 II; the driver never worked.](https://bugs.ntp.org/show_bug.cgi?id=689)
* [Bug 688: Fix documentation typos.](https://bugs.ntp.org/show_bug.cgi?id=688)
* [Bug 686: Handle leap seconds better under Windows.](https://bugs.ntp.org/show_bug.cgi?id=686)
* [Bug 685: Use the Windows multimedia timer.](https://bugs.ntp.org/show_bug.cgi?id=685)
* [Bug 684: Only allow debug options if debugging is enabled.](https://bugs.ntp.org/show_bug.cgi?id=684)
* [Bug 683: Use the right version string.](https://bugs.ntp.org/show_bug.cgi?id=683)
* [Bug 680: Fix the generated version string on Windows.](https://bugs.ntp.org/show_bug.cgi?id=680)
* [Bug 678: Use the correct size for control messages.](https://bugs.ntp.org/show_bug.cgi?id=678)
* [Bug 677: Do not check uint_t in configure.ac.](https://bugs.ntp.org/show_bug.cgi?id=677)
* [Bug 676: Use the right value for msg_namelen.](https://bugs.ntp.org/show_bug.cgi?id=676)
* [Bug 675: Make sure ntpd builds without debugging.](https://bugs.ntp.org/show_bug.cgi?id=675)
* [Bug 672: Fix cross-platform structure padding/size differences.](https://bugs.ntp.org/show_bug.cgi?id=672)
* [Bug 670: Resolved a Windows issue with the dynamic interface rescan code.](https://bugs.ntp.org/show_bug.cgi?id=670)
* [Bug 666: ntpq opeers displays jitter rather than dispersion.](https://bugs.ntp.org/show_bug.cgi?id=666)
* [Bug 660: New TIMESTAMP code fails tp build on Solaris Express.](https://bugs.ntp.org/show_bug.cgi?id=660)
* [Bug 659: libopts does not build under Windows.](https://bugs.ntp.org/show_bug.cgi?id=659)
* [Bug 658: HP-UX with cc needs -Wp,-H8166 in CFLAGS.](https://bugs.ntp.org/show_bug.cgi?id=658)
* [Bug 656: ntpdate doesn't work with multicast address.](https://bugs.ntp.org/show_bug.cgi?id=656)
* [Bug 638: STREAMS_TLI is deprecated - remove it.](https://bugs.ntp.org/show_bug.cgi?id=638)
* [Bug 637, 51?: Dynamic interface scanning can now be done.](https://bugs.ntp.org/show_bug.cgi?id=637)
* [Bug 635: Fix tOptions definition.](https://bugs.ntp.org/show_bug.cgi?id=635)
* [Bug 628: Fallback to ntp discipline not working for large offsets.](https://bugs.ntp.org/show_bug.cgi?id=628)
* [Bug 622: Dynamic interface tracking for ntpd.](https://bugs.ntp.org/show_bug.cgi?id=622)
* [Bug 603: Don't link with libelf if it's not needed.](https://bugs.ntp.org/show_bug.cgi?id=603)
* [Bug 523: ntpd service under Windows does't shut down properly.](https://bugs.ntp.org/show_bug.cgi?id=523)
* [Bug 500: sntp should always be built.](https://bugs.ntp.org/show_bug.cgi?id=500)
* [Bug 479: Fix the -P option.](https://bugs.ntp.org/show_bug.cgi?id=479)
* [Bug 452: Do not report kernel PLL/FLL flips.](https://bugs.ntp.org/show_bug.cgi?id=452)
* [Bug 421: Support the bc637PCI-U card.](https://bugs.ntp.org/show_bug.cgi?id=421)
* [Bug 342: Deprecate broken TRAK refclock driver.](https://bugs.ntp.org/show_bug.cgi?id=342)
* [Bug 340: Deprecate broken MSF EES refclock driver.](https://bugs.ntp.org/show_bug.cgi?id=340)
* [Bug 153: Don't do DNS lookups on address masks.](https://bugs.ntp.org/show_bug.cgi?id=153)
* [Bug 143: Fix interrupted system call on HP-UX.](https://bugs.ntp.org/show_bug.cgi?id=143)
* [Bug 42: Distribution tarballs should be signed.](https://bugs.ntp.org/show_bug.cgi?id=42)
* `monopt.html` fixes from Dave Mills.
* `driver8.html` updates.
* `sntp` now uses the returned precision to control decimal places.
* `sntp -u` will use an unprivileged port for its queries.
* K&R C support is being deprecated.
* WWV refclock improvements from Dave Mills.
* Support separate PPS devices for PARSE refclocks.
* Options processing now uses GNU AutoGen.