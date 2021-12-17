---
title: "4.2.8-series Changelog"
type: archives
---

<details open>
<summary><b>Click to hide release list</b></summary>

* [4.2.8p15](#428p15)
* [4.2.8p14](#428p14)
* [4.2.8p13](#428p13)
* [4.2.8p12](#428p12)
* [4.2.8p11](#428p11)
* [4.2.8p10](#428p10)
* [4.2.8p9](#428p9)
* [4.2.8p8](#428p8)
* [4.2.8p7](#428p7)
* [4.2.8p6](#428p6)
* [4.2.8p5](#428p5)
* [4.2.8p4](#428p4)
* [4.2.8p3](#428p3)
* [4.2.8p2](#428p2)
* [4.2.8p1](#428p1)
* [4.2.8](#428)

</details>

* * *

#### 4.2.8p15

**Release Date:** 2020 Jun 23

* [Sec 3661: memory leak with AES128CMAC keys](/support/securitynotice/ntpbug3661)
* [Bug3670: Regression from bad merge of 3592 and 3596](https://bugs.ntp.org/show_bug.cgi?id=3670)
  - fixed a bad merge that happened before 4.2.8-p14
* [Bug 3667: decodenetnum fails with numeric port](https://bugs.ntp.org/show_bug.cgi?id=3667)
  - rewrite `decodenetnum()` in terms of `inet_pton`
* [Bug 3666: avoid unlimited receive buffer allocation](https://bugs.ntp.org/show_bug.cgi?id=3666)
  - limit number of receive buffers, with an iron reserve for refclocks
* [Bug 3664: Enable openSSL CMAC support on Windows](https://bugs.ntp.org/show_bug.cgi?id=3664)
* [Bug 3662: Fix build errors on Windows with VS2008](https://bugs.ntp.org/show_bug.cgi?id=3662)
* [Bug 3660: Manycast orphan mode startup discovery problem](https://bugs.ntp.org/show_bug.cgi?id=3660)
  - integrated patch from Charles Claggett
* [Bug 3659: Move definition of psl[] from ntp_config.h to ntp_config.h](https://bugs.ntp.org/show_bug.cgi?id=3659)
* [Bug 3657: Wrong "Autokey group mismatch" debug message](https://bugs.ntp.org/show_bug.cgi?id=3657)
* [Bug 3655: ntpdc memstats hash counts](https://bugs.ntp.org/show_bug.cgi?id=3655)
  - fix by Gerry garvey
* [Bug 3653: Refclock jitter RMS calculation](https://bugs.ntp.org/show_bug.cgi?id=3653)
  - thanks to Gerry Garvey
* [Bug 3646: Avoid sync with unsync orphan](https://bugs.ntp.org/show_bug.cgi?id=3646)
  - patch by Gerry Garvey
* [Bug 3644: Unsynchronized server [...] selected as candidate](https://bugs.ntp.org/show_bug.cgi?id=3644)
* [Bug 3639: refclock_jjy: TS-JJY0x can skip time sync depending on the STUS reply](https://bugs.ntp.org/show_bug.cgi?id=3639)
  - applied patch by Takao Abe

* * *

#### 4.2.8p14

**Release Date:** 2020 Mar 3

* [Sec 3610: process_control() should bail earlier on short packets](/support/securitynotice/ntpbug3610)
  - Reported by Philippe Antoine
* [Sec 3596: Highly predictable timestamp attack](/support/securitynotice/ntpbug3596)
  - Reported by Miroslav Lichvar
* [Sec 3592: DoS attack on client ntpd](/support/securitynotice/ntpbug3592)
  - Reported by Miroslav Lichvar
* [Bug 3637: Emit the version of ntpd in saveconfig](https://bugs.ntp.org/show_bug.cgi?id=3637)
* [Bug 3636: NMEA: combine time/date from multiple sentences](https://bugs.ntp.org/show_bug.cgi?id=3636)
* [Bug 3635: Make leapsecond file hash check optional](https://bugs.ntp.org/show_bug.cgi?id=3635)
* [Bug 3634: Typo in discipline.html, reported by Jason Harrison](https://bugs.ntp.org/show_bug.cgi?id=3634)
* [Bug 3628: raw DCF decoding - improve robustness with Zeller's congruence](https://bugs.ntp.org/show_bug.cgi?id=3628)
  - implement Zeller's congruence in `libparse` and `libntp`
* [Bug 3627: SIGSEGV on FreeBSD-12 with stack limit and stack gap](https://bugs.ntp.org/show_bug.cgi?id=3627)
  - integrated patch by Cy Schubert
* [Bug 3620: memory leak in ntpq sysinfo](https://bugs.ntp.org/show_bug.cgi?id=3620)
  - applied patch by Gerry Garvey
* [Bug 3619: Honour drefid setting in cooked mode and sysinfo](https://bugs.ntp.org/show_bug.cgi?id=3619)
  - applied patch by Gerry Garvey
* [Bug 3617: Add support for ACE III and Copernicus II receivers](https://bugs.ntp.org/show_bug.cgi?id=3617)
  - integrated patch by Richard Steedman
* [Bug 3615: accelerate refclock startup](https://bugs.ntp.org/show_bug.cgi?id=3615)
* [Bug 3613: Propagate noselect to mobilized pool servers](https://bugs.ntp.org/show_bug.cgi?id=3613)
  - Reported by Martin Burnicki
* [Bug 3612: Use-of-uninitialized-value in receive function](https://bugs.ntp.org/show_bug.cgi?id=3612)
  - Reported by Philippe Antoine
* [Bug 3611: NMEA time interpreted incorrectly](https://bugs.ntp.org/show_bug.cgi?id=3611)
  - officially document new `trust date` mode bit for NMEA driver
  - restore the (previously undocumented) `trust date` feature lost with [bug 3577](https://bugs.ntp.org/show_bug.cgi?id=3577)
* [Bug 3609: Fixing wrong falseticker in case of non-statistic jitter](https://bugs.ntp.org/show_bug.cgi?id=3609)
  - mostly based on a patch by Michael Haardt, implementing `fudge minjitter`
* [Bug 3608: libparse fails to compile on S11.4SRU13 and later](https://bugs.ntp.org/show_bug.cgi?id=3608)
  - removed `ffs()` and `fls()` prototypes as per Brian Utterback
* [Bug 3604: Wrong param byte order passing into record_raw_stats() in ntp_io.c](https://bugs.ntp.org/show_bug.cgi?id=3604)
  - fixed byte and parameter order
* [Bug 3601: Tests fail to link on platforms with ntp_cv_gc_sections_runs=no](https://bugs.ntp.org/show_bug.cgi?id=3601)
* [Bug 3599: Build fails on linux-m68k due to alignment issues](https://bugs.ntp.org/show_bug.cgi?id=3599)
  - added padding as suggested by John Paul Adrian Glaubitz 
* [Bug 3594: ntpd discards messages coming through nmead](https://bugs.ntp.org/show_bug.cgi?id=3594)
* [Bug 3593: ntpd discards silently nmea messages after the 5th string](https://bugs.ntp.org/show_bug.cgi?id=3593)
* [Bug 3590: Update refclock_oncore.c to the new GPS date API](https://bugs.ntp.org/show_bug.cgi?id=3590)
* [Bug 3585: Unity tests mix buffered and unbuffered output](https://bugs.ntp.org/show_bug.cgi?id=3585)
  - `stdout+stderr` are set to line buffered during test setup now
* [Bug 3583: synchronization error](https://bugs.ntp.org/show_bug.cgi?id=3583)
  - set clock to base date if system time is before that limit
* [Bug 3582: gpsdjson refclock fudgetime1 adjustment is doubled](https://bugs.ntp.org/show_bug.cgi?id=3582)
* [Bug 3580: Possible bug ntpq-subs (NULL dereference in dogetassoc)](https://bugs.ntp.org/show_bug.cgi?id=3580)
  - Reported by Paulo Neves
* [Bug 3577: Update refclock_zyfer.c to the new GPS date API](https://bugs.ntp.org/show_bug.cgi?id=3577)
  - also updates for `refclock_nmea.c` and `refclock_jupiter.c`
* [Bug 3576: New GPS date function API](https://bugs.ntp.org/show_bug.cgi?id=3576)
* [Bug 3573: nptdate: missleading error message](https://bugs.ntp.org/show_bug.cgi?id=3573)
* [Bug 3570: NMEA driver docs: talker ID not mentioned, typo](https://bugs.ntp.org/show_bug.cgi?id=3570)
* [Bug 3569: cleanup MOD_NANO/STA_NANO handling for `ntpadjtimex()`](https://bugs.ntp.org/show_bug.cgi?id=3569)
  - sidekick: service port resolution in `ntpdate`
* [Bug 3550: Reproducible build: Respect SOURCE_DATE_EPOCH](https://bugs.ntp.org/show_bug.cgi?id=3550)
  - applied patch by Douglas Royds
* [Bug 3542: ntpdc monlist parameters cannot be set](https://bugs.ntp.org/show_bug.cgi?id=3542)
* [Bug 3533: ntpdc peer_info ipv6 issues](https://bugs.ntp.org/show_bug.cgi?id=3533)
  - applied patch by Gerry Garvey
* [Bug 3531: make check: test-decodenetnum fails](https://bugs.ntp.org/show_bug.cgi?id=3531)
  - try to harden `decodenetnum()` against `getaddrinfo()` errors
  - fix wrong cond-compile tests in unit tests
* [Bug 3517: Reducing build noise](https://bugs.ntp.org/show_bug.cgi?id=3517)
* [Bug 3516: Require tooling from this decade](https://bugs.ntp.org/show_bug.cgi?id=3516)
  - patch by Philipp Prindeville
* [Bug 3515: Refactor ntpdmain() dispatcher loop and group common code](https://bugs.ntp.org/show_bug.cgi?id=3515)
  - patch by Philipp Prindeville
* [Bug 3511: Get rid of AC_LANG_SOURCE() warnings](https://bugs.ntp.org/show_bug.cgi?id=3511)
  - patch by Philipp Prindeville
* [Bug 3510: Flatten out the #ifdef nesting in ntpdmain()](https://bugs.ntp.org/show_bug.cgi?id=3510)
  - partial application of patch by Philipp Prindeville
* [Bug 3491: Signed values of LFP datatypes should always display a sign](https://bugs.ntp.org/show_bug.cgi?id=3491)
  - applied patch by Gerry Garvey & fixed unit tests
* [Bug 3490: Patch to support Trimble Resolution Receivers](https://bugs.ntp.org/show_bug.cgi?id=3490)
  - applied (modified) patch by Richard Steedman
* [Bug 3473: RefID of refclocks should always be text format](https://bugs.ntp.org/show_bug.cgi?id=3473)
  - applied patch by Gerry Garvey (with minor formatting changes)
* [Bug 3132: Building 4.2.8p8 with disabled local libopts fails](https://bugs.ntp.org/show_bug.cgi?id=3132)
  - applied patch by Miroslav Lichvar
* [Bug 3094: ntpd trying to listen for broadcasts on a completely ipv6 network](https://bugs.ntp.org/show_bug.cgi?id=3094)
* [Bug 2420: ntpd doesn't run and exits with retval 0 when invalid user is specified with -u](https://bugs.ntp.org/show_bug.cgi?id=2420)
  - monitor daemon child startup & propagate exit codes
* [Bug 1433: runtime check whether the kernel really supports capabilities](https://bugs.ntp.org/show_bug.cgi?id=1433)
  - (modified) patch by Kurt Roeckx
* Clean up sntp/networking `c:sendpkt()` error message.
* Provide more detail on unrecognized config file parser tokens.
* Startup log improvements.
* Update the copyright year.
* html/confopt.html cleanup.

* * *

#### 4.2.8p13

**Release Date:** 2019 Mar 7

* [Sec 3565: Crafted null dereference attack in authenticated mode 6 packet](/support/securitynotice/ntpbug3565)
  - reported by Magnus Stubman
* [Bug 3560: Fix build when HAVE_DROPROOT is not defined](https://bugs.ntp.org/show_bug.cgi?id=3560)
  - applied patch by Ian Lepore
* [Bug 3558: Crash and integer size bug](https://bugs.ntp.org/show_bug.cgi?id=3558)
  - isolate and fix Linux/Windows-specific code issue
* [Bug 3556: ntp_loopfilter.c snprintf compilation warnings](https://bugs.ntp.org/show_bug.cgi?id=3556)
  - provide better function for incremental string formatting
* [Bug 3555: Tidy up print alignment of debug output from ntpdate](https://bugs.ntp.org/show_bug.cgi?id=3555)
  - applied patch by Gerry Garvey
* [Bug 3554: config revoke stores incorrect value](https://bugs.ntp.org/show_bug.cgi?id=3554)
  - original finding by Gerry Garvey, additional cleanup needed
* [Bug 3549: Spurious initgroups() error message](https://bugs.ntp.org/show_bug.cgi?id=3549)
  - patch by Christous Zoulas
* [Bug 3548: Signature not verified on windows system](https://bugs.ntp.org/show_bug.cgi?id=3548)
  - finding by Chen Jiabin, plus another one by Harlan
* [Bug 3541: patch to fix STA_NANO struct timex units](https://bugs.ntp.org/show_bug.cgi?id=3541)
  - applied patch by Maciej Szmigiero
* [Bug 3540: Cannot set minsane to 0 anymore](https://bugs.ntp.org/show_bug.cgi?id=3540)
  - applied patch by Andre Charbonneau
* [Bug 3539: work_fork build fails when droproot is not supported](https://bugs.ntp.org/show_bug.cgi?id=3539)
  - applied patch by Baruch Siach
* [Bug 3538: Build fails for no-MMU targets](https://bugs.ntp.org/show_bug.cgi?id=3538)
  - applied patch by Baruch Siach
* [Bug 3535: libparse won't handle GPS week rollover](https://bugs.ntp.org/show_bug.cgi?id=3535)
  - refactored handling of GPS era based on `tos basedate` for parse (TSIP) and JUPITER clocks
* [Bug 3529: Build failures on Mac OS X 10.13 (High Sierra)](https://bugs.ntp.org/show_bug.cgi?id=3529)
  - patch by Daniel J. Luke; this does not fix a potential linker regression issue on MacOS.
* [Bug 3527: Backward Incompatible mode7 clockinfo fudgeval2 packet anomaly](https://bugs.ntp.org/show_bug.cgi?id=3527)
  - `--enable-bug3527-fix` support by HStenn
* [Bug 3526: Incorrect poll interval in packet](https://bugs.ntp.org/show_bug.cgi?id=3526)
  - applied patch by Gerry Garvey
* [Bug 3471: Check for openssl/[ch]mac.h](https://bugs.ntp.org/show_bug.cgi?id=3471)
  - added missing check, reported by Reinhard Max
* [Bug 1674: runtime crashes and sync problems affecting both x86 and x86_64](https://bugs.ntp.org/show_bug.cgi?id=1674)
  - this is a variant of [bug 3558](https://bugs.ntp.org/show_bug.cgi?id=3558) and should be fixed with it
* Implement `--disable-signalled-io`

* * *

#### 4.2.8p12

**Release Date:** 2018 Aug 14

* [Sec 3505: CVE-2018-12327 - Arbitrary Code Execution Vulnerability](/support/securitynotice/ntpbug3505)
  - fixed stack buffer overflow in the `openhost()` command-line call of `ntpq/ntpdc`
* [Sec 3012: noepeer tweaks](/support/securitynotice/ntpbug3012p12)
* [Bug 3521: Fix a logic bug in the INVALIDNAK checks](https://bugs.ntp.org/show_bug.cgi?id=3521)
* [Bug 3509: Add support for running as non-root on FreeBSD, Darwin, other TrustedBSD platforms](https://bugs.ntp.org/show_bug.cgi?id=3509)
  - applied patch by Ian Lepore
* [Bug 3506: Service Control Manager interacts poorly with NTPD](https://bugs.ntp.org/show_bug.cgi?id=3506)
  - changed interaction with SCM to signal pending startup
* [Bug 3486: Buffer overflow in `ntpq/ntpq.c:tstflags()`](https://bugs.ntp.org/show_bug.cgi?id=3486)
  - applied patch by Gerry Garvey
* [Bug 3485: Undefined sockaddr used in error messages in ntp_config.c](https://bugs.ntp.org/show_bug.cgi?id=3485)
  - applied patch by Gerry Garvey
* [Bug 3484: ntpq response from ntpd is incorrect when REFID is null](https://bugs.ntp.org/show_bug.cgi?id=3484)
  - rework of `ntpq nextvar()` key/value parsing
* [Bug 3482: Fixes for compilation warnings (ntp_io.c & ntpq-subs.c)](https://bugs.ntp.org/show_bug.cgi?id=3482)
  - applied patch by Gerry Garvey (with mods)
* [Bug 3480: Refclock sample filter not cleared on clock STEP](https://bugs.ntp.org/show_bug.cgi?id=3480)
  - applied patch by Gerry Garvey
* [Bug 3479: ctl_putrefid() allows unsafe characters through to ntpq](https://bugs.ntp.org/show_bug.cgi?id=3479)
  - applied patch by Gerry Garvey (with mods)
* [Bug 3476:ctl_putstr() sends empty unquoted string `[...]`](https://bugs.ntp.org/show_bug.cgi?id=3476)
  - applied patch by Gerry Garvey (with mods); not sure if that's bug or feature, though
* [Bug 3475: modify prettydate() to suppress output of zero time](https://bugs.ntp.org/show_bug.cgi?id=3475)
  - applied patch by Gerry Garvey
* [Bug 3474: Missing pmode in mode7 peer info response](https://bugs.ntp.org/show_bug.cgi?id=3474)
  - applied patch by Gerry Garvey
* [Bug 3471: Check for openssl/[ch]mac.h](https://bugs.ntp.org/show_bug.cgi?id=3471)
  - add `#define ENABLE_CMAC` support in `configure`.
* [Bug 3470: ntpd4.2.8p11 fails to compile without OpenSSL](https://bugs.ntp.org/show_bug.cgi?id=3470)
* [Bug 3469: Incomplete string compare [...] in is_refclk_addr](https://bugs.ntp.org/show_bug.cgi?id=3469)
  - patch by Stephen Friedl
* [Bug 3467: Potential memory fault in ntpq `[...]`](https://bugs.ntp.org/show_bug.cgi?id=3467)
  - fixed IO redirection and <kbd>CTRL-C</kbd> handling in `ntq` and `ntpdc`
* [Bug 3465: Default TTL values cannot be used](https://bugs.ntp.org/show_bug.cgi?id=3465)
* [Bug 3461: refclock_shm.c: clear error status on clock recovery](https://bugs.ntp.org/show_bug.cgi?id=3461)
  - initial patch by Hal Murray; also fixed `refclock_report()` trouble
* [Bug 3460: Fix typo in ntpq.texi](https://bugs.ntp.org/show_bug.cgi?id=3460)
  - reported by Kenyon Ralph. 
* [Bug 3456: Use uintptr_t rather than size_t to store an integer in a pointer](https://bugs.ntp.org/show_bug.cgi?id=3456)
  - According to Brooks Davis, there was only one location
* [Bug 3449: ntpq - display "loop" instead of refid `[...]`](https://bugs.ntp.org/show_bug.cgi?id=3449)
  - applied patch by Gerry Garvey
* [Bug 3445: Symmetric peer won't sync on startup](https://bugs.ntp.org/show_bug.cgi?id=3445)
  - applied patch by Gerry Garvey
* [Bug 3442: Fixes for ntpdate](https://bugs.ntp.org/show_bug.cgi?id=3442)
  - as suggested by Gerry Garvey, with modifications
  - New macro `REFID_ISTEXT()` which is also used in `ntpd/ntp_control.c`
* [Bug 3434: ntpd clears STA_UNSYNC on start](https://bugs.ntp.org/show_bug.cgi?id=3434)
  - applied patch by Miroslav Lichvar
* [Bug 3426: ntpdate.html -t default is 2 seconds](https://bugs.ntp.org/show_bug.cgi?id=3426)
* [Bug 3121: Drop root privileges for the forked DNS worker](https://bugs.ntp.org/show_bug.cgi?id=3121)
  - integrated patch by Reinhard Max
* [Bug 2821: minor build issues](https://bugs.ntp.org/show_bug.cgi?id=2821)
  - applied patches by Christos Zoulas, including real bug fixes
* html/authopt.html: cleanup.
* `ntpd/ntpd.c`: `DROPROOT` cleanup.
* Symmetric key range is 1-65535.  Update docs.
* html/authentic.html: cleanup.

* * *

#### 4.2.8p11 

**Release Date:** 2018 Feb 27

* [Sec 3454: Unauthenticated packet can reset authenticated interleave associations](/support/securitynotice/ntpbug3454)
* [Sec 3453: Interleaved symmetric mode cannot recover from bad state](/support/securitynotice/ntpbug3453)
* [Sec 3415: Permit blocking authenticated symmetric/passive associations](/support/securitynotice/ntpbug3415)
  - Implement ippeerlimit
* [Sec 3414: ntpq: decodearr() can write beyond its 'buf' limits](/support/securitynotice/ntpbug3414)
  - initial patch by Harlan Stenn, extended by JPerlinger
* [Sec 3412: ctl_getitem(): Don't compare names past NUL](/support/securitynotice/ntpbug3412)
* [Sec 3012: Sybil vulnerability: noepeer support](/support/securitynotice/ntpbug3012)
* [Bug 3457: OpenSSL FIPS mode regression](https://bugs.ntp.org/show_bug.cgi?id=3457)
* [Bug 3455: ntpd doesn't use scope id when binding multicast](https://bugs.ntp.org/show_bug.cgi?id=3455)
 - applied patch by Sean Haugh 
* [Bug 3452: PARSE driver prints uninitialized memory](https://bugs.ntp.org/show_bug.cgi?id=3452)
* [Bug 3450: Dubious error messages from plausibility checks in get_systime()](https://bugs.ntp.org/show_bug.cgi?id=3450)
  - removed error log caused by rounding/slew, ensured postcondition
* [Bug 3447: AES-128-CMAC (fixes)](https://bugs.ntp.org/show_bug.cgi?id=3447)
  - refactoring the MAC code, too
* [Bug 3441: Validate the assumption that AF_UNSPEC is 0](https://bugs.ntp.org/show_bug.cgi?id=3441)
* [Bug 3439: When running multiple commands / hosts in ntpq](https://bugs.ntp.org/show_bug.cgi?id=3439)
  - applied patch by ggarvey
* [Bug 3438: Negative values and values > 999 days in](https://bugs.ntp.org/show_bug.cgi?id=3438)
  - applied patch by ggarvey (with minor mods)
* [Bug 3437: ntpd tries to open socket with AF_UNSPEC domain](https://bugs.ntp.org/show_bug.cgi?id=3437)
  - applied patch (with mods) by Miroslav Lichvar
* [Bug 3435: anchor NTP era alignment](https://bugs.ntp.org/show_bug.cgi?id=3435)
* [Bug 3433: sntp crashes when run with -a](https://bugs.ntp.org/show_bug.cgi?id=3433)
* [Bug 3430: ntpq dumps core (SIGSEGV) for "keytype md2"](https://bugs.ntp.org/show_bug.cgi?id=3430)
  - fixed several issues with hash algos in `ntpd, sntp, ntpq, ntpdc` and the test suites
* [Bug 3424: Trimble Thunderbolt 1024 week millenium bug](https://bugs.ntp.org/show_bug.cgi?id=3424)
  - initial patch by Daniel Pouzzner
* [Bug 3423: QNX adjtime() implementation error checking is wrong](https://bugs.ntp.org/show_bug.cgi?id=3423)
* [Bug 3417: ntpq ifstats packet counters can be negative](https://bugs.ntp.org/show_bug.cgi?id=3417)
  - made `IFSTATS` counter quantities unsigned
* [Bug 3411: problem about SIGN(6) packet handling for ntp-4.2.8p10](https://bugs.ntp.org/show_bug.cgi?id=3411)
  - raised receive buffer size to 1200
* [Bug 3408: refclock_jjy.c: Avoid a wrong report of the coverity static analysis tool](https://bugs.ntp.org/show_bug.cgi?id=3408)
* [Bug 3405: update-leap.in: general cleanup, HTTPS support](https://bugs.ntp.org/show_bug.cgi?id=3405)
* [Bug 3404: Fix openSSL DLL usage under Windows](https://bugs.ntp.org/show_bug.cgi?id=3404)
  - fix/drop assumptions on OpenSSL libs directory layout
* [Bug 3399: NTP: linker error in 4.2.8p10 during Linux cross-compilation](https://bugs.ntp.org/show_bug.cgi?id=3399)
  - initial patch by timeflies@mail2tor.com
* [Bug 3398: tests fail with core dump](https://bugs.ntp.org/show_bug.cgi?id=3398)
  - patch contributed by Alexander Bluhm
* [Bug 3397: ctl_putstr() asserts that data fits in its buffer](https://bugs.ntp.org/show_bug.cgi?id=3397)
  - rework of formatting & data transfer stuff in `ntp_control.c`
  - avoids unecessary buffers and size limitations.
* [Bug 3394: Leap second deletion does not work on ntpd clients](https://bugs.ntp.org/show_bug.cgi?id=3394)
  - fixed handling of dynamic deletion w/o leap file
* [Bug 3391: ntpd segfaults on startup due to small warmup thread stack size](https://bugs.ntp.org/show_bug.cgi?id=3391)
  - increased mimimum stack size to 32kB
* [Bug 3367: Faulty LinuxPPS NMEA clock support in 4.2.8](https://bugs.ntp.org/show_bug.cgi?id=3367)
  - reverted handling of PPS kernel consumer to 4.2.6 behavior
* [Bug 3365: Updates driver40(-ja).html and miscopt.html](https://bugs.ntp.org/show_bug.cgi?id=3365)
* [Bug 3358: Spurious KoD log messages in .INIT. phase](https://bugs.ntp.org/show_bug.cgi?id=3358)
* [Bug 3016: wrong error position reported for bad ":config pool"](https://bugs.ntp.org/show_bug.cgi?id=3016)
  - fixed location counter & `ntpq` output
* [Bug 2900: libntp build order problem](https://bugs.ntp.org/show_bug.cgi?id=2900)
* [Bug 2878: Tests are cluttering up syslog](https://bugs.ntp.org/show_bug.cgi?id=2878)
* [Bug 2737: Wrong phone number listed for USNO](https://bugs.ntp.org/show_bug.cgi?id=2737)
* [Bug 2557: Fix Thunderbolt init](https://bugs.ntp.org/show_bug.cgi?id=2557)
* [Bug 948: Trustedkey config directive leaks memory](https://bugs.ntp.org/show_bug.cgi?id=948)
* Use `strlcpy()` to copy strings, not `memcpy()`.
* Typos.
* `test_ntp_scanner_LDADD` needs `ntpd/ntp_io.o`.
* `refclock_jjy.c`: Add missing `%s` to an `msyslog()` call.
* Build `ntpq` and `libntpq.a` with `NTP_HARD_*FLAGS`.
* Fix trivial warnings from `make check`.
* Fix bug in the override portion of the compiler hardening macro.
* `record_raw_stats()`: Log entire packet.  Log writes.
* AES-128-CMAC support.
* `sntp`: tweak key file logging.
* `sntp: pkt_output()`: Improve debug output.
* update-leap: updates from Paul McMath.
* When using `pkg-config`, report `--modversion`.
* Clean up `libevent` configure checks.
* `sntp`: show the IP of who sent us a crypto-NAK.
* Allow `.../N` to specify subnet bits for IPs in `ntp.keys`.
* `authistrustedip()` - use it in more places.
* New `sysstats: sys_lamport, sys_tsrounding`.
* Update `ntp.keys .../N` documentation.
* Distribute `testconf.yml`.
* Add `DPRINTF(2,...)` lines to `receive()` for packet drops.
* Rename the configuration flag `fifo` variables.
* Improve `saveconfig` output.
* Decode restrict flags on `receive()` debug output.
* Decode interface flags on `receive()` debug output.
* Warn the user if deprecated `driftfile name WanderThreshold` is used.
* Update the documentation in `ntp.conf.def`.
* `restrictions()` must return `restrict` flags and `ippeerlimit`.
* Update `ntpq peer` documentation to describe the `p` type.
* Rename restrict `flags` to `rflags`.  Use an enum for the values.
* Provide `dump_restricts()` for debugging.
* Use consistent 4th arg type for `[gs]etsockopt`.
* Some tests might need `LIBM`.
* update-leap: Allow `-h/--help` early.

* * *

#### 4.2.8p10 

2017/03/21 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 3389] NTP-01-016: Denial of Service via Malformed Config
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3388] NTP-01-014: Buffer Overflow in DPTS Clock
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3387] NTP-01-012: Authenticated DoS via Malicious Config Option
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3386] NTP-01-011: ntpq_stripquotes() returns incorrect Value
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3385] NTP-01-010: ereallocarray()/eallocarray() underused. HStenn
* [Sec 3384] NTP-01-009: Privileged execution of User Library code
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3383] NTP-01-008: Stack Buffer Overflow from Command Line
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3382] NTP-01-007: Data Structure terminated insufficiently
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3380] NTP-01-005: Off-by-one in Oncore GPS Receiver
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3379] NTP-01-004: Potential Overflows in ctl_put() functions
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3378] NTP-01-003: Improper use of snprintf() in mx4200_send()
  (Pentest report 01.2017) <perlinger@ntp.org>
* [Sec 3377] NTP-01-002: Buffer Overflow in ntpq when fetching reslist
  (Pentest report 01.2017) <perlinger@ntp.org
* [Sec 3376] Support build "hardening" flags.  stenn@ntp.org
* [Sec 3361] 0rigin (zero origin) DoS.  HStenn.
* [Bug 3393] clang scan-build findings <perlinger@ntp.org>
* [Bug 3363] Support for openssl-1.1.0 without compatibility modes
  - rework of patch set from <ntp.org@eroen.eu>. <perlinger@ntp.org>
* [Bug 3356] Bugfix 3072 breaks multicastclient <perlinger@ntp.org>
* [Bug 3216] libntp audio ioctl() args incorrectly cast to int
  on 4.4BSD-Lite derived platforms <perlinger@ntp.org>
  - original patch by Majdi S. Abbas
* [Bug 3215] 'make distcheck' fails with new BK repo format <perlinger@ntp.org>
* [Bug 3173] forking async worker: interrupted pipe I/O <perlinger@ntp.org>
  - initial patch by Christos Zoulas
* [Bug 3139] (...) time_pps_create: Exec format error <perlinger@ntp.org>
  - move loader API from 'inline' to proper source
  - augment pathless dlls with absolute path to NTPD
  - use 'msyslog()' instead of 'printf() 'for reporting trouble
* [Bug 3107] Incorrect Logic for Peer Event Limiting <perlinger@ntp.org>
  - applied patch by Matthew Van Gundy
* [Bug 3065] Quiet warnings on NetBSD <perlinger@ntp.org>
  - applied some of the patches provided by Havard. Not all of them
    still match the current code base, and I did not touch libopt.
* [Bug 3062] Change the process name of forked DNS worker <perlinger@ntp.org>
  - applied patch by Reinhard Max. See bugzilla for limitations.
* [Bug 2923] Trap Configuration Fail <perlinger@ntp.org>
  - fixed dependency inversion from [Bug 2837]
* [Bug 2896] Nothing happens if minsane < maxclock < minclock
  - produce ERROR log message about dysfunctional daemon. <perlinger@ntp.org>
* [Bug 2851] allow -4/-6 on restrict line with mask <perlinger@ntp.org>
  - applied patch by Miroslav Lichvar for ntp4.2.6 compat
* [Bug 2645] out-of-bound pointers in ctl_putsys and decode_bitflags
  - Fixed these and some more locations of this pattern.
    Probably din't get them all, though. <perlinger@ntp.org>
* Update copyright year.
* bk-7 trigger updates

---
(4.2.8p9-win) 2017/02/01 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 3144] NTP does not build without openSSL. <perlinger@ntp.org>
  - added missed changeset for automatic openssl lib detection
  - fixed some minor warning issues
* [Bug 3095]  More compatibility with openssl 1.1. <perlinger@ntp.org>
* configure.ac cleanup.  stenn@ntp.org
* openssl configure cleanup.  stenn@ntp.org

---
(4.2.8p9) 2016/11/21 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 3119] Trap crash <perlinger@ntp.org>
* [Sec 3118] Mode 6 information disclosure and DDoS vector <perlinger@ntp.org>
  - TRAP config via mode 6 packet requires AUTH now.
* [Sec 3114] Broadcast Mode Replay Prevention DoS
  - applied patches by Matthew Van Gundy. <perlinger@ntp.org>
  - with bcpollbstep, tweaks and cleanup by stenn@ntp.org
* [Sec 3113] Broadcast Mode Poll Interval Enforcement DoS <perlinger@ntp.org>
  - applied fix as suggested by Matthew Van Gundy
* [Sec 3110] Windows: ntpd DoS by oversized UDP packet
  - fixed error handling for truncated UDP packets. <perlinger@ntp.org>
* [Sec 3102] Zero origin issues.  HStenn.
* [Sec 3082] null pointer dereference in _IO_str_init_static_internal()
  - more hardening to read_mru_list(). perlinger@ntp.org
* [Sec 3072] Attack on interface selection <perlinger@ntp.org>
  - implemented Miroslav Lichvars <mlichvar@redhat.com> suggestion
    to skip interface updates based on incoming packets
* [Bug 3142] bug in netmask prefix length detection <perlinger@ntp.org>
* [Bug 3138] gpsdjson refclock should honor fudgetime1. stenn@ntp.org
* [Bug 3129] Unknown hosts can put resolver thread into a hard loop
  - moved retry decision where it belongs. <perlinger@ntp.org>
* [Bug 3125] NTPD doesn't fully start when ntp.conf entries are out of order
  using the loopback-ppsapi-provider.dll <perlinger@ntp.org>
* [Bug 3116] unit tests for NTP time stamp expansion. <perlinger@ntp.org>
* [Bug 3100] ntpq can't retrieve daemon_version <perlinger@ntp.org>
  - fixed extended sysvar lookup (bug introduced with bug 3008 fix)
* [Bug 3095] Compatibility with openssl 1.1 <perlinger@ntp.org>
  - applied patches by Kurt Roeckx <kurt@roeckx.be> to source
  - added shim layer for SSL API calls with issues (both directions)
* [Bug 3089] Serial Parser does not work anymore for hopfser like device
  - simplified / refactored hex-decoding in driver. <perlinger@ntp.org>
* [Bug 3084] update-leap mis-parses the leapfile name.  HStenn.
* [Bug 3068] Linker warnings when building on Solaris. perlinger@ntp.org
  - applied patch thanks to Andrew Stormont <andyjstormont@gmail.com>
* [Bug 3067] Root distance calculation needs improvement.  HStenn.
* [Bug 3066] NMEA clock ignores pps. perlinger@ntp.org
  - PPS-HACK works again.
* [Bug 3059] Potential buffer overrun from oversized hash <perlinger@ntp.org>
  - applied patch by Brian Utterback <brian.utterback@oracle.com>
* [Bug 3053] ntp_loopfilter.c frequency calc precedence error.  Sarah White.
* [Bug 3050]  Fix for bug #2960 causes [...] spurious error message.
  <perlinger@ntp.org>
  - patches by Reinhard Max <max@suse.com> and Havard Eidnes <he@uninett.no>
* [Bug 3047] Fix refclock_jjy C-DEX JST2000. abe@ntp.org
  - Patch provided by Kuramatsu.
* [Bug 3021] unity_fixture.c needs pragma weak <perlinger@ntp.org>
  - removed unnecessary & harmful decls of 'setUp()' & 'tearDown()'
* [Bug 3019] Windows: ERROR_HOST_UNREACHABLE block packet processing.
  DMayer and JPerlinger.
* [Bug 2998] sntp/tests/packetProcessing.c broken without openssl. JPerlinger
* [Bug 2961] sntp/tests/packetProcessing.c assumes AUTOKEY.  HStenn.
* [Bug 2959] refclock_jupiter: gps week correction <perlinger@ntp.org>
  - fixed GPS week expansion to work based on build date. Special thanks
    to Craig Leres for initial patch and testing.
* [Bug 2951] ntpd tests fail: multiple definition of `send_via_ntp_signd'
  - fixed Makefile.am <perlinger@ntp.org>
* [Bug 2689] ATOM driver processes last PPS pulse at startup,
             even if it is very old <perlinger@ntp.org>
  - make sure PPS source is alive before processing samples
  - improve stability close to the 500ms phase jump (phase gate)
* Fix typos in include/ntp.h.
* Shim X509_get_signature_nid() if needed.
* git author attribution cleanup
* bk ignore file cleanup
* remove locks in Windows IO, use rpc-like thread synchronisation instead

---
(4.2.8p8) 2016/06/02 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 3042] Broadcast Interleave.  HStenn.
* [Sec 3043] Autokey association reset.  perlinger@ntp.org, stenn@ntp.org
  - validate origin timestamps on bad MACs, too.  stenn@ntp.org
* [Sec 3044] Spoofed server packets are partially processed.  HStenn.
* [Sec 3045] Bad authentication demobilizes ephemeral associations. JPerlinger.
* [Sec 3046] CRYPTO_NAK crash.  stenn@ntp.org
* [Bug 3038] NTP fails to build in VS2015. perlinger@ntp.org
  - provide build environment
  - 'wint_t' and 'struct timespec' defined by VS2015
  - fixed print()/scanf() format issues
* [Bug 3052] Add a .gitignore file.  Edmund Wong.
* [Bug 3054] miscopt.html documents the allan intercept in seconds. SWhite.
* [Bug 3058] fetch_timestamp() mishandles 64-bit alignment. Brian Utterback,
  JPerlinger, HStenn.
* Update the NEWS file for 4.2.8p8.  HStenn.
* Fix typo in ntp-wait and plot_summary.  HStenn.
* Make sure we have an "author" file for git imports.  HStenn.
* Update the sntp problem tests for MacOS.  HStenn.

---
(4.2.8p7) 2016/04/26 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 2901] KoD packets must have non-zero transmit timestamps.  HStenn.
* [Sec 2936] Skeleton Key: Any system knowing the trusted key can serve
  time. Include passive servers in this check. HStenn.
* [Sec 2945] Additional KoD packet checks.  HStenn.
* [Sec 2978] Interleave can be partially triggered.  HStenn.
* [Sec 3007] Validate crypto-NAKs.  Danny Mayer.
* [Sec 3008] Always check the return value of ctl_getitem().
  - initial work by HStenn
  - Additional cleanup of ctl_getitem by perlinger@ntp.org
* [Sec 3009] Crafted addpeer with hmode > 7 causes OOB error. perlinger@ntp.org
   - added more stringent checks on packet content
* [Sec 3010] remote configuration trustedkey/requestkey values
  are not properly validated. perlinger@ntp.org
  - sidekick: Ignore keys that have an unsupported MAC algorithm
    but are otherwise well-formed
* [Sec 3011] Duplicate IPs on unconfig directives will cause an assertion botch
  - graciously accept the same IP multiple times. perlinger@ntp.org
* [Sec 3020] Refclock impersonation.  HStenn.
* [Bug 2831]  Segmentation Fault in DNS lookup during startup. perlinger@ntp.org
  - fixed yet another race condition in the threaded resolver code.
* [Bug 2858] bool support.  Use stdbool.h when available.  HStenn.
* [Bug 2879] Improve NTP security against timing attacks. perlinger@ntp.org
  - integrated patches by Loganaden Velvidron <logan@ntp.org>
    with some modifications & unit tests
* [Bug 2952] Symmetric active/passive mode is broken.  HStenn.
* [Bug 2960] async name resolution fixes for chroot() environments.
  Reinhard Max.
* [Bug 2994] Systems with HAVE_SIGNALED_IO fail to compile. perlinger@ntp.org
* [Bug 2995] Fixes to compile on Windows
* [Bug 2999] out-of-bounds access in 'is_safe_filename()'. perlinger@ntp.org
* [Bug 3013] Fix for ssl_init.c SHA1 test. perlinger@ntp.org
  - Patch provided by Ch. Weisgerber
* [Bug 3015] ntpq: config-from-file: "request contains an unprintable character"
  - A change related to [Bug 2853] forbids trailing white space in
    remote config commands. perlinger@ntp.org
* [Bug 3019] NTPD stops processing packets after ERROR_HOST_UNREACHABLE
  - report and patch from Aleksandr Kostikov.
  - Overhaul of Windows IO completion port handling. perlinger@ntp.org
* [Bug 3022] authkeys.c should be refactored. perlinger@ntp.org
  - fixed memory leak in access list (auth[read]keys.c)
  - refactored handling of key access lists (auth[read]keys.c)
  - reduced number of error branches (authreadkeys.c)
* [Bug 3023] ntpdate cannot correct dates in the future. perlinger@ntp.org
* [Bug 3030] ntpq needs a general way to specify refid output format.  HStenn.
* [Bug 3031] ntp broadcastclient unable to synchronize to an server
             when the time of server changed. perlinger@ntp.org
  - Check the initial delay calculation and reject/unpeer the broadcast
    server if the delay exceeds 50ms. Retry again after the next
    broadcast packet.
* [Bug 3036] autokey trips an INSIST in authistrustedip().  Harlan Stenn.
* Document ntp.key's optional IP list in authenetic.html.  Harlan Stenn.
* Update html/xleave.html documentation.  Harlan Stenn.
* Update ntp.conf documentation.  Harlan Stenn.
* Fix some Credit: attributions in the NEWS file.  Harlan Stenn.
* Fix typo in html/monopt.html.  Harlan Stenn.
* Add README.pullrequests.  Harlan Stenn.
* Cleanup to include/ntp.h.  Harlan Stenn.

---
(4.2.8p6) 2016/01/20 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 2935] Deja Vu: Replay attack on authenticated broadcast mode. HStenn.
* [Sec 2936] Skeleton Key: Any trusted key system can serve time. HStenn.
* [Sec 2937] ntpq: nextvar() missing length check. perlinger@ntp.org
* [Sec 2938] ntpq saveconfig command allows dangerous characters
  in filenames. perlinger@ntp.org
* [Sec 2939] reslist NULL pointer dereference.  perlinger@ntp.org
* [Sec 2940] Stack exhaustion in recursive traversal of restriction
  list. perlinger@ntp.org
* [Sec 2942]: Off-path DoS attack on auth broadcast mode.  HStenn.
* [Sec 2945] Zero Origin Timestamp Bypass. perlinger@ntp.org
* [Sec 2948] Potential Infinite Loop in ntpq ( and ntpdc) perlinger@ntp.org
* [Bug 2772] adj_systime overflows tv_usec. perlinger@ntp.org
* [Bug 2814] msyslog deadlock when signaled. perlinger@ntp.org
  - applied patch by shenpeng11@huawei.com with minor adjustments
* [Bug 2882] Look at ntp_request.c:list_peers_sum(). perlinger@ntp.org
* [Bug 2891] Deadlock in deferred DNS lookup framework. perlinger@ntp.org
* [Bug 2892] Several test cases assume IPv6 capabilities even when
             IPv6 is disabled in the build. perlinger@ntp.org
  - Found this already fixed, but validation led to cleanup actions.
* [Bug 2905] DNS lookups broken. perlinger@ntp.org
  - added limits to stack consumption, fixed some return code handling
* [Bug 2971] ntpq bails on ^C: select fails: Interrupted system call
  - changed stacked/nested handling of CTRL-C. perlinger@ntp.org
  - make CTRL-C work for retrieval and printing od MRU list. perlinger@ntp.org
* [Bug 2980] reduce number of warnings. perlinger@ntp.org
  - integrated several patches from Havard Eidnes (he@uninett.no)
* [Bug 2985] bogus calculation in authkeys.c perlinger@ntp.org
  - implement 'auth_log2()' using integer bithack instead of float calculation
* Make leapsec_query debug messages less verbose.  Harlan Stenn.
* Disable incomplete t-ntp_signd.c test.  Harlan Stenn.

---
(4.2.8p5) 2016/01/07 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 2956] small-step/big-step.  Close the panic gate earlier.  HStenn.
* CID 1339955: Free allocated memory in caljulian test.  HStenn.
* CID 1339962: Explicitly initialize variable in caljulian test.  HStenn.
* CID 1341527: Quiet a CHECKED_RETURN in sntp/tests/t-log.c.  HStenn.
* CID 1341533: Missing assertion in sntp/tests/t-log.c.  HStenn.
* CID 1341534: Resource leak in tests/ntpd/t-ntp_signd.c.  HStenn.
* CID 1341535: Resource leak in tests/ntpd/t-ntp_signd.c.  HStenn.
* CID 1341536: Resource leak in tests/ntpd/t-ntp_signd.c.  HStenn.
* CID 1341537: Resource leak in tests/ntpd/t-ntp_signd.c.  HStenn.
* CID 1341538: Memory leak in tests/ntpd/ntp_prio_q.c:262.  HStenn.
* CID 1341677: Nits in sntp/tests/keyFile.c.  HStenn.
* CID 1341678: Nits in sntp/tests/keyFile.c.  HStenn.
* CID 1341679: Nits in sntp/tests/keyFile.c.  HStenn.
* CID 1341680: Nits in sntp/tests/keyFile.c.  HStenn.
* CID 1341681: Nits in sntp/tests/keyFile.c.  HStenn.
* CID 1341682: Nit in libntp/authreadkeys.c.  HStenn.
* CID 1341684: Nit in tests/ntpd/t-ntp_signd.c.  HStenn.
* [Bug 2829] Look at pipe_fds in ntpd.c  (did so. perlinger@ntp.org)
* [Bug 2887] stratum -1 config results as showing value 99
  - fudge stratum should only accept values [0..16]. perlinger@ntp.org
* [Bug 2932] Update leapsecond file info in miscopt.html.  CWoodbury, HStenn.
* [Bug 2934] tests/ntpd/t-ntp_scanner.c has a magic constant wired in.  HMurray
* [Bug 2944] errno is not preserved properly in ntpdate after sendto call.
  - applied patch by Christos Zoulas.  perlinger@ntp.org
* [Bug 2952] Symmetric active/passive mode is broken.  HStenn.
* [Bug 2954] Version 4.2.8p4 crashes on startup with sig fault
  - fixed data race conditions in threaded DNS worker. perlinger@ntp.org
  - limit threading warm-up to linux; FreeBSD bombs on it. perlinger@ntp.org
* [Bug 2957] 'unsigned int' vs 'size_t' format clash. perlinger@ntp.org
  - accept key file only if there are no parsing errors
  - fixed size_t/u_int format clash
  - fixed wrong use of 'strlcpy'
* [Bug 2958] ntpq: fatal error messages need a final newline. Craig Leres.
* [Bug 2962] truncation of size_t/ptrdiff_t on 64bit targets. perlinger@ntp.org
  - fixed several other warnings (cast-alignment, missing const, missing prototypes)
  - promote use of 'size_t' for values that express a size
  - use ptr-to-const for read-only arguments
  - make sure SOCKET values are not truncated (win32-specific)
  - format string fixes
* [Bug 2965] Local clock didn't work since 4.2.8p4.  Martin Burnicki.
* [Bug 2967] ntpdate command suffers an assertion failure
  - fixed ntp_rfc2553.c to return proper address length. perlinger@ntp.org
* [Bug 2969]  Seg fault from ntpq/mrulist when looking at server with
              lots of clients. perlinger@ntp.org
* [Bug 2971] ntpq bails on ^C: select fails: Interrupted system call
  - changed stacked/nested handling of CTRL-C. perlinger@ntp.org
  - make CTRL-C work for retrieval and printing od MRU list. perlinger@ntp.org
* Unity cleanup for FreeBSD-6.4.  Harlan Stenn.
* Unity test cleanup.  Harlan Stenn.
* Libevent autoconf pthread fixes for FreeBSD-10.  Harlan Stenn.
* Header cleanup in tests/sandbox/uglydate.c.  Harlan Stenn.
* Header cleanup in tests/libntp/sfptostr.c.  Harlan Stenn.
* Quiet a warning from clang.  Harlan Stenn.
* Update the NEWS file.  Harlan Stenn.
* Update scripts/calc_tickadj/Makefile.am.  Harlan Stenn.

---
(4.2.8p4) 2015/10/21 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 2899] CVE-2014-9297  perlinger@ntp.org
* [Sec 2901] Drop invalid packet before checking KoD. Check for all KoD's.
  Danny Mayer.  Log incoming packets that fail TEST2.  Harlan Stenn.
* [Sec 2902] configuration directives "pidfile" and "driftfile"
  should be local-only. perlinger@ntp.org (patch by Miroslav Lichvar)
* [Sec 2909] added missing call to 'free()' in ntp_crypto.c. perlinger@ntp.org
* [Sec 2913] TALOS-CAN-0052: crash by loop counter underrun. perlinger@ntp.org
* [Sec 2916] TALOS-CAN-0054: memory corruption in password store. JPerlinger
* [Sec 2917] TALOS-CAN-0055: Infinite loop if extended logging enabled and
  the logfile and keyfile are the same. perlinger@ntp.org
* [Sec 1918] TALOS-CAN-0062: prevent directory traversal for VMS, too, when
  using 'saveconfig' command.  perlinger@ntp.org
* [Bug 2919] TALOS-CAN-0063: avoid buffer overrun in ntpq. perlinger@ntp.org
* [Sec 2020] TALOS-CAN-0064: signed/unsiged clash could lead to buffer overun
  and memory corruption. perlinger@ntp.org
* [Sec 2921] TALOS-CAN-0065: password length memory corruption. JPerlinger.
* [Sec 2922] decodenetnum() will ASSERT botch instead of returning FAIL
  on some bogus values.  Harlan Stenn.
* [Sec 2941] NAK to the Future: Symmetric association authentication
  bypass via crypto-NAK. Patch applied. perlinger@ntp.org
* [Bug 2332] (reopened) Exercise thread cancellation once before dropping
  privileges and limiting resources in NTPD removes the need to link
  forcefully against 'libgcc_s' which does not always work. J.Perlinger
* [Bug 2595] ntpdate man page quirks.  Hal Murray, Harlan Stenn.
* [Bug 2625] Deprecate flag1 in local refclock.  Hal Murray, Harlan Stenn.
* [Bug 2817] Stop locking ntpd into memory by default under Linux.  H.Stenn.
* [Bug 2821] minor build issues: fixed refclock_gpsdjson.c.  perlinger@ntp.org
* [Bug 2823] ntpsweep with recursive peers option doesn't work.  H.Stenn.
* [Bug 2849] Systems with more than one default route may never
  synchronize.  Brian Utterback.  Note that this patch might need to
  be reverted once Bug 2043 has been fixed.
* [Bug 2864] 4.2.8p3 fails to compile on Windows. Juergen Perlinger
* [Bug 2866] segmentation fault at initgroups().  Harlan Stenn.
* [Bug 2867] ntpd with autokey active crashed by 'ntpq -crv'. J.Perlinger
* [Bug 2873] libevent should not include .deps/ in the tarball.  H.Stenn
* [Bug 2874] Don't distribute generated sntp/tests/fileHandlingTest.h. H.Stenn
* [Bug 2875] sntp/Makefile.am: Get rid of DIST_SUBDIRS.  libevent must
  be configured for the distribution targets.  Harlan Stenn.
* [Bug 2883] ntpd crashes on exit with empty driftfile.  Miroslav Lichvar.
* [Bug 2886] Mis-spelling: "outlyer" should be "outlier".  dave@horsfall.org
* [Bug 2888] streamline calendar functions.  perlinger@ntp.org
* [Bug 2889] ntp-dev-4.3.67 does not build on Windows.  perlinger@ntp.org
* [Bug 2890] Ignore ENOBUFS on routing netlink socket.  Konstantin Khlebnikov.
* [Bug 2906] make check needs better support for pthreads.  Harlan Stenn.
* [Bug 2907] dist* build targets require our libevent/ to be enabled.  HStenn.
* [Bug 2912] no munlockall() under Windows.  David Taylor, Harlan Stenn.
* libntp/emalloc.c: Remove explicit include of stdint.h.  Harlan Stenn.
* Put Unity CPPFLAGS items in unity_config.h.  Harlan Stenn.
* tests/ntpd/g_leapsec.cpp typo fix.  Harlan Stenn.
* Phase 1 deprecation of google test in sntp/tests/.  Harlan Stenn.
* On some versions of HP-UX, inttypes.h does not include stdint.h.  H.Stenn.
* top_srcdir can change based on ntp v. sntp.  Harlan Stenn.
* sntp/tests/ function parameter list cleanup.  Damir TomiÄ‡.
* tests/libntp/ function parameter list cleanup.  Damir TomiÄ‡.
* tests/ntpd/ function parameter list cleanup.  Damir TomiÄ‡.
* sntp/unity/unity_config.h: handle stdint.h.  Harlan Stenn.
* sntp/unity/unity_internals.h: handle *INTPTR_MAX on old Solaris.  H.Stenn.
* tests/libntp/timevalops.c and timespecops.c fixed error printing.  D.TomiÄ‡.
* tests/libntp/ improvements in code and fixed error printing.  Damir TomiÄ‡.
* tests/libntp: a_md5encrypt.c, authkeys.c, buftvtots.c, calendar.c, caljulian.c,
  caltontp.c, clocktime.c, humandate.c, hextolfp.c, decodenetnum.c - fixed
  formatting; first declaration, then code (C90); deleted unnecessary comments;
  changed from sprintf to snprintf; fixed order of includes. Tomasz Flendrich
* tests/libntp/lfpfunc.c remove unnecessary include, remove old comments,
  fix formatting, cleanup. Tomasz Flendrich
* tests/libntp/lfptostr.c remove unnecessary include, add consts, fix formatting.
  Tomasz Flendrich
* tests/libntp/statestr.c remove empty functions, remove unnecessary include,
  fix formatting. Tomasz Flendrich
* tests/libntp/modetoa.c fixed formatting. Tomasz Flendrich
* tests/libntp/msyslog.c fixed formatting. Tomasz Flendrich
* tests/libntp/numtoa.c deleted unnecessary empty functions, fixed formatting.
  Tomasz Flendrich
* tests/libntp/numtohost.c added const, fixed formatting. Tomasz Flendrich
* tests/libntp/refnumtoa.c fixed formatting. Tomasz Flendrich
* tests/libntp/ssl_init.c fixed formatting. Tomasz Flendrich
* tests/libntp/tvtots.c fixed a bug, fixed formatting. Tomasz Flendrich
* tests/libntp/uglydate.c removed an unnecessary include. Tomasz Flendrich
* tests/libntp/vi64ops.c removed an unnecessary comment, fixed formatting.
* tests/libntp/ymd3yd.c removed an empty function and an unnecessary include,
fixed formatting. Tomasz Flendrich
* tests/libntp/timespecops.c fixed formatting, fixed the order of includes,
  removed unnecessary comments, cleanup. Tomasz Flendrich
* tests/libntp/timevalops.c fixed the order of includes, deleted unnecessary
  comments, cleanup. Tomasz Flendrich
* tests/libntp/sockaddrtest.h making it agree to NTP's conventions of formatting.
  Tomasz Flendrich
* tests/libntp/lfptest.h cleanup. Tomasz Flendrich
* tests/libntp/test-libntp.c fix formatting. Tomasz Flendrich
* sntp/tests/crypto.c is now using proper Unity's assertions, fixed formatting.
  Tomasz Flendrich
* sntp/tests/kodDatabase.c added consts, deleted empty function,
  fixed formatting. Tomasz Flendrich
* sntp/tests/kodFile.c cleanup, fixed formatting. Tomasz Flendrich
* sntp/tests/packetHandling.c is now using proper Unity's assertions,
  fixed formatting, deleted unused variable. Tomasz Flendrich
* sntp/tests/keyFile.c is now using proper Unity's assertions, fixed formatting.
  Tomasz Flendrich
* sntp/tests/packetProcessing.c changed from sprintf to snprintf,
  fixed formatting. Tomasz Flendrich
* sntp/tests/utilities.c is now using proper Unity's assertions, changed
  the order of includes, fixed formatting, removed unnecessary comments.
  Tomasz Flendrich
* sntp/tests/sntptest.h fixed formatting. Tomasz Flendrich
* sntp/tests/fileHandlingTest.h.in fixed a possible buffer overflow problem,
  made one function do its job, deleted unnecessary prints, fixed formatting.
  Tomasz Flendrich
* sntp/unity/Makefile.am added a missing header. Tomasz Flendrich
* sntp/unity/unity_config.h: Distribute it.  Harlan Stenn.
* sntp/libevent/evconfig-private.h: remove generated filefrom SCM.  H.Stenn.
* sntp/unity/Makefile.am: fix some broken paths.  Harlan Stenn.
* sntp/unity/unity.c: Clean up a printf().  Harlan Stenn.
* Phase 1 deprecation of google test in tests/libntp/.  Harlan Stenn.
* Don't build sntp/libevent/sample/.  Harlan Stenn.
* tests/libntp/test_caltontp needs -lpthread.  Harlan Stenn.
* br-flock: --enable-local-libevent.  Harlan Stenn.
* Wrote tests for ntpd/ntp_prio_q.c. Tomasz Flendrich
* scripts/lib/NTP/Util.pm: stratum output is version-dependent.  Harlan Stenn.
* Get rid of the NTP_ prefix on our assertion macros.  Harlan Stenn.
* Code cleanup.  Harlan Stenn.
* libntp/icom.c: Typo fix.  Harlan Stenn.
* util/ntptime.c: initialization nit.  Harlan Stenn.
* ntpd/ntp_peer.c:newpeer(): added a DEBUG_REQUIRE(srcadr).  Harlan Stenn.
* Add std_unity_tests to various Makefile.am files.  Harlan Stenn.
* ntpd/ntp_restrict.c: added a few assertions, created tests for this file.
  Tomasz Flendrich
* Changed progname to be const in many files - now it's consistent. Tomasz
  Flendrich
* Typo fix for GCC warning suppression.  Harlan Stenn.
* Added tests/ntpd/ntp_scanner.c test. Damir TomiÄ‡.
* Added declarations to all Unity tests, and did minor fixes to them.
  Reduced the number of warnings by half. Damir TomiÄ‡.
* Updated generate_test_runner.rb and updated the sntp/unity/auto directory
  with the latest Unity updates from Mark. Damir TomiÄ‡.
* Retire google test - phase I.  Harlan Stenn.
* Unity test cleanup: move declaration of 'initializing'.  Harlan Stenn.
* Update the NEWS file.  Harlan Stenn.
* Autoconf cleanup.  Harlan Stenn.
* Unit test dist cleanup. Harlan Stenn.
* Cleanup various test Makefile.am files.  Harlan Stenn.
* Pthread autoconf macro cleanup.  Harlan Stenn.
* Fix progname definition in unity runner scripts.  Harlan Stenn.
* Clean trailing whitespace in tests/ntpd/Makefile.am.  Harlan Stenn.
* Update the patch for bug 2817.  Harlan Stenn.
* More updates for bug 2817.  Harlan Stenn.
* Fix bugs in tests/ntpd/ntp_prio_q.c.  Harlan Stenn.
* gcc on older HPUX may need +allowdups.  Harlan Stenn.
* Adding missing MCAST protection.  Harlan Stenn.
* Disable certain test programs on certain platforms.  Harlan Stenn.
* Implement --enable-problem-tests (on by default).  Harlan Stenn.
* build system tweaks.  Harlan Stenn.
---
(4.2.8p3) 2015/06/29 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 2853] Crafted remote config packet can crash some versions of
  ntpd.  Aleksis Kauppinen, Juergen Perlinger, Harlan Stenn.
* [Sec 2853] Initial work on tests/sec-2853/.  Harlan Stenn.
* [Bug 1060] Buffer overruns in libparse/clk_rawdcf.c.  Helge Oldach.
* [Bug 2846] Report 'unsynchronized' status during the leap second.
  Fixed in Martin's changes to Bug 2855.  Martin Burnicki.
* [Bug 2859] Improve raw DCF77 robustness deconding.  Frank Kardel.
* [Bug 2860] ntpq ifstats sanity check is too stringent.  Frank Kardel.
* README.leapsmear added.  Martin Burnicki.
* README.leapsmear edited.  Harlan Stenn.
* tests/libntp/msyslog.c: fixed a gcc warning. Tomasz Flendrich.
* ntpd/ntp.conf.def: Document DSCP and leapsmearinterval.  Harlan Stenn.
* html/miscopt.html: Document leapsmearinterval, other cleanup.  Harlan Stenn.
---
(4.2.8p3-RC3) 2015/06/27 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2855] Parser fix for conditional leap smear code.  Harlan Stenn.
* [Bug 2855] Report leap smear in the REFID.  Harlan Stenn.
* [Bug 2856] ntpd should wait() on terminated child processes.  Paul Green.
* [Bug 2857] Stratus VOS does not support SIGIO.  Paul Green.
* html/drivers/driver22.html: typo fix.  Harlan Stenn.
* refidsmear test cleanup.  Tomasz Flendrich.
* refidsmear function support and tests.  Harlan Stenn.
* sntp/tests/Makefile.am: remove g_nameresolution.cpp as it tested
  something that was only in the 4.2.6 sntp.  Harlan Stenn.
* Modified tests/bug-2803/Makefile.am so it builds Unity framework tests.
  Damir TomiÄ‡
* Modified tests/libtnp/Makefile.am so it builds Unity framework tests.
  Damir TomiÄ‡
* Modified sntp/tests/Makefile.am so it builds Unity framework tests.
  Damir TomiÄ‡
* tests/sandbox/smeartest.c: Harlan Stenn, Damir Tomic, Juergen Perlinger.
* Converted from gtest to Unity: tests/bug-2803/. Damir TomiÄ‡
* Converted from gtest to Unity: tests/libntp/ a_md5encrypt, atoint.c,
  atouint.c, authkeys.c, buftvtots.c, calendar.c, caljulian.c,
  calyearstart.c, clocktime.c, hextoint.c, lfpfunc.c, modetoa.c,
  numtoa.c, numtohost.c, refnumtoa.c, ssl_init.c, statestr.c,
  timespecops.c, timevalops.c, uglydate.c, vi64ops.c, ymd2yd.c.
  Damir TomiÄ‡
* Converted from gtest to Unity: sntp/tests/ kodDatabase.c, kodFile.c,
  networking.c, keyFile.c, utilities.cpp, sntptest.h,
  fileHandlingTest.h. Damir TomiÄ‡
* Converted from gtest to Unity: sntp/tests/ caltontp.c, humandate.c,
  msyslog.c, prettydate.c, recvbuff.c, sfptostr.c, tstotv.c, tvtots.c,
  sntp/tests/packetProcessing.c. Tomasz Flendrich
---
(4.2.8p3-RC2) 2015/06/24 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2778] Implement "apeers"  ntpq command to include associd.
* [Bug 2805] ntpd fails to join multicast group.
* [Bug 2824] Convert update-leap to perl. (also see 2769)
* [Bug 2830] ntpd doesn't always transfer the correct TAI offset via autokey
   NTPD transfers the current TAI (instead of an announcement) now.
   This might still needed improvement.
   Update autokey data ASAP when 'sys_tai' changes.
   Fix unit test that was broken by changes for autokey update.
   Avoid potential signature length issue and use DPRINTF where possible
     in ntp_crypto.c.
* [Bug 2832] refclock_jjy.c supports the TDC-300.
* [Bug 2834] Correct a broken html tag in html/refclock.html
* [Bug 2836] DFC77 patches from Frank Kardel to make decoding more
  robust, and require 2 consecutive timestamps to be consistent.
* [Bug 2837] Allow a configurable DSCP value.
* [Bug 2837] add test for DSCP to ntpd/complete.conf.in
* [Bug 2842] Glitch in ntp.conf.def documentation stanza.
* [Bug 2842] Bug in mdoc2man.
* [Bug 2843] make check fails on 4.3.36
   Fixed compiler warnings about numeric range overflow
   (The original topic was fixed in a byplay to bug#2830)
* [Bug 2845] Harden memory allocation in ntpd.
* [Bug 2852] 'make check' can't find unity.h.  Hal Murray.
* [Bug 2854] Missing brace in libntp/strdup.c.  Masanari Iida.
* [Bug 2855] Implement conditional leap smear code.  Martin Burnicki.
* [Bug 2855] leap smear cleanup.  Harlan Stenn.
* Initial support for experimental leap smear code.  Harlan Stenn.
* Fixes to sntp/tests/fileHandlingTest.h.in.  Harlan Stenn.
* Report select() debug messages at debug level 3 now.
* sntp/scripts/genLocInfo: treat raspbian as debian.
* Unity test framework fixes.
  ** Requires ruby for changes to tests.
* Initial support for PACKAGE_VERSION tests.
* sntp/libpkgver belongs in EXTRA_DIST, not DIST_SUBDIRS.
* tests/bug-2803/Makefile.am must distribute bug-2803.h.
* automake-1.15 cleanup for sntp/tests/fileHandlingTest.h.in .  Harlan Stenn.
---
(4.2.8p3-RC1) 2015/05/12 Released by Harlan Stenn <stenn@ntp.org>

* CID 739725: Fix a rare resource leak in libevent/listener.c.
* CID 1295478: Quiet a pedantic potential error from the fix for Bug 2776.
* CID 1296235: Fix refclock_jjy.c and correcting type of the driver40-ja.html
* CID 1269537: Clean up a line of dead code in getShmTime().
* [Bug 2590] autogen-5.18.5.
* [Bug 2612] restrict: Warn when 'monitor' can't be disabled because
  of 'limited'.
* [Bug 2650] fix includefile processing.
* [Bug 2745] ntpd -x steps clock on leap second
   Fixed an initial-value problem that caused misbehaviour in absence of
   any leapsecond information.
   Do leap second stepping only of the step adjustment is beyond the
   proper jump distance limit and step correction is allowed at all.
* [Bug 2750] build for Win64
  Building for 32bit of loopback ppsapi needs def file
* [Bug 2776] Improve ntpq's 'help keytype'.
* [Bug 2782] Refactor refclock_shm.c, add memory barrier protection.
* [Bug 2792] If the IFF_RUNNING interface flag is supported then an
  interface is ignored as long as this flag is not set since the
  interface is not usable (e.g., no link).
* [Bug 2794] Clean up kernel clock status reports.
* [Bug 2800] refclock_true.c true_debug() can't open debug log because
  of incompatible open/fdopen parameters.
* [Bug 2804] install-local-data assumes GNU 'find' semantics.
* [Bug 2806] refclock_jjy.c supports the Telephone JJY.
* [Bug 2808] GPSD_JSON driver enhancements, step 1.
  Fix crash during cleanup if GPS device not present and char device.
  Increase internal token buffer to parse all JSON data, even SKY.
  Defer logging of errors during driver init until the first unit is
  started, so the syslog is not cluttered when the driver is not used.
  Various improvements, see http://bugs.ntp.org/2808 for details.
  Changed libjsmn to a more recent version.
* [Bug 2810] refclock_shm.c memory barrier code needs tweaks for QNX.
* [Bug 2813] HP-UX needs -D__STDC_VERSION__=199901L and limits.h.
* [Bug 2815] net-snmp before v5.4 has circular library dependencies.
* [Bug 2821] Add a missing NTP_PRINTF and a missing const.
* [Bug 2822] New leap column in sntp broke NTP::Util.pm.
* [Bug 2825] Quiet file installation in html/ .
* [Bug 2830] ntpd doesn't always transfer the correct TAI offset via autokey
   NTPD transfers the current TAI (instead of an announcement) now.
   This might still needed improvement.
* Add an assert to the ntpq ifstats code.
* Clean up the RLIMIT_STACK code.
* Improve the ntpq documentation around the controlkey keyid.
* ntpq.c cleanup.
* Windows port build cleanup.
---
(4.2.8p2) 2015/04/07 Released by Harlan Stenn <stenn@ntp.org>
(4.2.8p2-RC3) 2015/04/03 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2763] Fix for different thresholds for forward and backward steps.
* Initial import of the Unity test framework.
---
(4.2.8p2-RC2) 2015/04/03 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2592] FLAG_TSTAMP_PPS cleanup for refclock_parse.c.
* [Bug 2769] New script: update-leap
* [Bug 2769] cleannup for update-leap
* [Bug 2788] New flag -G (force_step_once).
* [Bug 2794] Clean up kernel clock status reports.
* [Bug 2795] Cannot build without OpenSLL (on Win32).
  Provided a Win32 specific wrapper around libevent/arc4random.c.
  fixed some minor warnings.
* [Bug 2796] ntp-keygen crashes in 'getclock()' on Win32.
* [Bug 2797] ntp-keygen trapped in endless loop for MD5 keys
  on big-endian machines.
* [Bug 2798] sntp should decode and display the leap indicator.
* Simple cleanup to html/build.html
---
(4.2.8p2-RC1) 2015/03/30 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2794] Don't let reports on normal kernel status changes
  look like errors.
* [Bug 2788] New flag -G (force_step_once).
* [Bug 2592] Account for PPS sources which can provide an accurate
  absolute time stamp, and status information.
  Fixed indention and removed trailing whitespace.
* [Bug 1787] DCF77's formerly "antenna" bit is "call bit" since 2003.
* [Bug 1960] setsockopt IPV6_MULTICAST_IF: Invalid argument.
* [Bug 2346] "graceful termination" signals do not do peer cleanup.
* [Bug 2728] See if C99-style structure initialization works.
* [Bug 2747] Upgrade libevent to 2.1.5-beta.
* [Bug 2749] ntp/lib/NTP/Util.pm needs update for ntpq -w, IPv6, .POOL. .
* [Bug 2751] jitter.h has stale copies of l_fp macros.
* [Bug 2756] ntpd hangs in startup with gcc 3.3.5 on ARM.
* [Bug 2757] Quiet compiler warnings.
* [Bug 2759] Expose nonvolatile/clk_wander_threshold to ntpq.
* [Bug 2763] Allow different thresholds for forward and backward steps.
* [Bug 2766] ntp-keygen output files should not be world-readable.
* [Bug 2767] ntp-keygen -M should symlink to ntp.keys.
* [Bug 2771] nonvolatile value is documented in wrong units.
* [Bug 2773] Early leap announcement from Palisade/Thunderbolt
* [Bug 2774] Unreasonably verbose printout - leap pending/warning
* [Bug 2775] ntp-keygen.c fails to compile under Windows.
* [Bug 2777] Fixed loops and decoding of Meinberg GPS satellite info.
  Removed non-ASCII characters from some copyright comments.
  Removed trailing whitespace.
  Updated definitions for Meinberg clocks from current Meinberg header files.
  Now use C99 fixed-width types and avoid non-ASCII characters in comments.
  Account for updated definitions pulled from Meinberg header files.
  Updated comments on Meinberg GPS receivers which are not only called GPS16x.
  Replaced some constant numbers by defines from ntp_calendar.h
  Modified creation of parse-specific variables for Meinberg devices
  in gps16x_message().
  Reworked mk_utcinfo() to avoid printing of ambiguous leap second dates.
  Modified mbg_tm_str() which now expexts an additional parameter controlling
  if the time status shall be printed.
* [Sec 2779] ntpd accepts unauthenticated packets with symmetric key crypto.
* [Sec 2781] Authentication doesn't protect symmetric associations against
  DoS attacks.
* [Bug 2783] Quiet autoconf warnings about missing AC_LANG_SOURCE.
* [Bug 2784] Fix for 2782 uses clock_gettime() instead of get_ostime().
* [Bug 2789] Quiet compiler warnings from libevent.
* [Bug 2790] If ntpd sets the Windows MM timer highest resolution
  pause briefly before measuring system clock precision to yield
  correct results.
* Comment from Juergen Perlinger in ntp_calendar.c to make the code clearer.
* Use predefined function types for parse driver functions
  used to set up function pointers.
  Account for changed prototype of parse_inp_fnc_t functions.
  Cast parse conversion results to appropriate types to avoid
  compiler warnings.
  Let ioctl() for Windows accept a (void *) to avoid compiler warnings
  when called with pointers to different types.
---
(4.2.8p1) 2015/02/04 Released by Harlan Stenn <stenn@ntp.org>

* Update the NEWS file.
* [Sec 2671] vallen in extension fields are not validated.
---
(4.2.8p1-RC2) 2015/01/29 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2627] shm refclock allows only two units with owner-only access
  rework: reverted sense of mode bit (so default reflects previous
  behaviour) and updated ducumentation.
* [Bug 2732] - Leap second not handled correctly on Windows 8
  use 'GetTickCount()' to get the true elapsed time of slew
  (This should work for all versions of Windows >= W2K)
* [Bug 2738] Missing buffer initialization in refclocK_parse.c::parsestate().
* [Bug 2739] Parse driver with PPS enabled occasionally evaluates
  PPS timestamp with wrong sign.
  Removed some German umlauts.
* [Bug 2740] Removed some obsolete code from the parse driver.
* [Bug 2741] Incorrect buffer check in refclocK_parse.c::parsestatus().
---
(4.2.8p1-RC1) 2015/01/24 Released by Harlan Stenn <stenn@ntp.org>

* Start the RC for 4.2.8p1.
* [Bug 2187] Update version number generation scripts.
* [Bug 2617] Fix sntp Usage documentation section.
* [Sec 2672] Code cleanup: On some OSes ::1 can be spoofed...
* [Bug 2736] Show error message if we cannot open the config file.
* Copyright update.
* Fix the package name.
---
(4.2.8p1-beta5) 2015/01/07 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2695] Windows build: __func__ not supported under Windows.
* [Bug 2728] Work around C99-style structure initialization code
  for older compilers, specifically Visual Studio prior to VS2013.
---
(4.2.8p1-beta4) 2015/01/04 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 1084] PPSAPI for ntpd on Windows with DLL backends
* [Bug 2695] Build problem on Windows (sys/socket.h).
* [Bug 2715] mdnstries option for ntp.conf from NetBSD.
* Fix a regression introduced to timepps-Solaris.h as part of:
  [Bug 1206] Required compiler changes for Windows
  (4.2.5p181) 2009/06/06
---
(4.2.8p1-beta3) 2015/01/02 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2627] shm refclock allows only two units with owner-only access
  Use mode bit 0 to select public access for units >= 2 (units 0 & 1 are
  always private.
* [Bug 2681] Fix display of certificate EOValidity dates on 32-bit systems.
* [Bug 2695] 4.2.8 does not build on Windows.
* [bug 2700] mrulist stopped working in 4.2.8.
* [Bug 2706] libparse/info_trimble.c build dependencies are broken.
* [Bug 2713] variable type/cast, parameter name, general cleanup from NetBSD.
* [Bug 2714] libevent may need to be built independently of any build of sntp.
* [Bug 2715] mdnstries option for ntp.conf from NetBSD.
---
(4.2.8p1-beta2) 2014/12/27 Released by Harlan Stenn <stenn@ntp.org>

* [Bug 2674] Install sntp in sbin on NetBSD.
* [Bug 2693] ntp-keygen doesn't build without OpenSSL and sntp.
* [Bug 2707] Avoid a C90 extension in libjsmn/jsmn.c.
* [Bug 2709] see if we have a C99 compiler (not yet required).
---
(4.2.8p1-beta1) 2014/12/23 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 2672] On some OSes ::1 can be spoofed, bypassing source IP ACLs.
* [Bug 2693] ntp-keygen doesn't build without OpenSSL.
* [Bug 2697] IN6_IS_ADDR_LOOPBACK build problems on some OSes.
* [Bug 2699] HAVE_SYS_SELECT_H is misspelled in refclock_gpsdjson.c.
---
(4.2.8) 2014/12/19 Released by Harlan Stenn <stenn@ntp.org>

* [Sec 730] Increase RSA_generate_key modulus.
* [Sec 2666] Use cryptographic random numbers for md5 key generation.
* [Sec 2667] buffer overflow in crypto_recv().
* [Sec 2668] buffer overflow in ctl_putdata().
* [Sec 2669] buffer overflow in configure().
* [Sec 2670] Missing return; from error clause.
* [Sec 2671] vallen in extension fields are not validated.
* [Sec 2672] On some OSes ::1 can be spoofed, bypassing source IP ACLs.
* [Bug 2691] Wrong variable name in refclock_ripencc.c.
(4.2.7p486-RC) 2014/12/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2687] RefClock 26/hpgps doesn't work at default line speed
(4.2.7p485-RC) 2014/12/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2686] refclock_gpsdjson needs strtoll(), which is not always present.
(4.2.7p484-RC) 2014/12/11 Released by Harlan Stenn <stenn@ntp.org>
(4.2.7p483) 2014/12/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2685] Better document the KOD file for sntp.
(4.2.7p482) 2014/12/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2641] sntp is installed in the wrong location in Solaris.
* [Bug 2678] nmea_control() now checks 'refclock_params()' result.
(4.2.7p481) 2014/11/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2314] Only enable PPS if kernel consumer binding succeeds.
* [Bug 2314] Kernel PPS binding EOPNOTSUPP is a failure condition.
* Rename pps_enable to hardpps_enable.
(4.2.7p480) 2014/11/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2677] PATH_MAX isn't #define'd under Windows.
  Regression from the patch fixing Bug 2639.
(4.2.7p479) 2014/11/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2651] Certificates with ASN timestamps w/ 4-digit years mis-parsed.
(4.2.7p478) 2014/11/14 Released by Harlan Stenn <stenn@ntp.org>
* [Sec 2630] buffer overrun in ntpq tokenize().
* [Bug 2639] Check return value of ntp_adjtime().
* [Bug 2650] includefile processing broken.
* [Bug 2661] ntpq crashes with mreadvar.
(4.2.7p477) 2014/11/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2657] Document that "restrict nopeer" intereferes with "pool".
(4.2.7p476) 2014/10/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2503] SHT utility outdated
(4.2.7p475) 2014/09/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2654] refclock_true.c doesn't identify the Mk III.
(4.2.7p474) 2014/09/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2536] ntpd sandboxing support (libseccomp2) cleanup.
* [Bug 2649] Clean up html/ page installation.
(4.2.7p473) 2014/09/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2649] Clean up html/ page installation.
(4.2.7p472) 2014/09/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2556] mrulist is missing from the generated ntpq man page.
(4.2.7p471) 2014/09/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2649] "make install" leaves wrong owner for files in html/.
* [Bug 2652] Windows hates directory names that contain a :.
(4.2.7p470) 2014/09/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2502] Autogen text replacement errors.
* autogen-5.18.5pre1
* html/ cleanups from Hal Murray.
(4.2.7p469) 2014/09/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2536] ntpd sandboxing support (libseccomp2) cleanup.
(4.2.7p468) 2014/08/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2556] ntpq man page cleanup.
* autogen-5.18.4
(4.2.7p467) 2014/08/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2639] Check return value of ntp_adjtime().
* [Bug 2640] STA_NANO can result in invalid ntv.constant.
(4.2.7p466) 2014/08/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2536] ntpd sandboxing support (libseccomp2) cleanup.
(4.2.7p465) 2014/08/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2538] NTP programs print exit code in help/usage text.
* [Bug 2595] Man page quirks: ntpdate references in ntpd.
* [Bug 2613] www.ntp.org/bugs.html tells folks to email doc bugs to DLM.
* [Bug 2636] Clutter in syslog if gpsd not running
   - found (hopefully) last cause for clutter in protocol version
   - log GPSD revision and release numbers with protocol version
(4.2.7p464) 2014/08/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2636] Fix coverity warning from previous patch.
(4.2.7p463) 2014/08/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2636] Clutter in syslog if gpsd not running
   - make driver work with GPSD protocol version 3.9
   - use exponential back-off for connection problems
   - implement rate-limit for syslog entries
(4.2.7p462) 2014/08/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2622] Synchronisation problem using SHM [...]
  Add 'control' function -- fudge values not available during start.
(4.2.7p461) 2014/08/14 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1128] ntpq truncates "remote" host information.
* More autogen-5.18.4pre14 cleanup.
(4.2.7p460) 2014/08/13 Released by Harlan Stenn <stenn@ntp.org>
* More autogen-5.18.4pre14 cleanup.
(4.2.7p459) 2014/08/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2630] Limit the ntpq command buffer to 512 bytes.
* FlexeLint cleanups.
* Try bison-3.0.2 instead of bison-2.5.
(4.2.7p458) 2014/08/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2633] Provide stdnoreturn.h for windows port.
(4.2.7p457) 2014/08/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2622] Synchronisation problem using SHM when time difference is
  more than four hours: Change SHM driver so TOY restricted API is not
  used any more. (Plus some minor cleanup in logic and flow control)
* Pass the configration source into the parser as argument rather
  than through a global variable.
* Fix nits in the ntpq man page.
* autogen-5.18.4pre14
(4.2.7p456) 2014/08/07 Released by Harlan Stenn <stenn@ntp.org>
* CID 739722: Change the way the extention and MAC fields are processed.
(4.2.7p455) 2014/08/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2565] ntpd sometimes logs unexpected getifaddrs() errors.
* CID 739722: Clean up the definition of the exten field of struct pkt.
(4.2.7p454) 2014/07/30 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2628] 'mon_getmoremem()' relies on undefined behaviour
(4.2.7p453) 2014/07/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2597] leap file loose ends (follow-up)
  - uniform expiration check messages for config and timer triggered
    leap file loads
  - timer triggered loads log messages only once per day
(4.2.7p452) 2014/07/18 Released by Harlan Stenn <stenn@ntp.org>
* Make all of the html/ .html files use the same format for "Last update".
(4.2.7p451) 2014/07/17 Released by Harlan Stenn <stenn@ntp.org>
* Fix the "Last update" entries in the html/ subtree.
(4.2.7p450) 2014/07/16 Released by Harlan Stenn <stenn@ntp.org>
* Distribute the scripts needed for the fix for Bug 2547.
(4.2.7p449) 2014/07/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2547] Automate update of "Last Update" datestamps in .html files.
* [Bug 2623] Missing {} in refclock_oncore.c.
* Quiet warnings from ntp_calendar.h: avoid using argument names.
* Fix typos in decode.html and debug.html .
(4.2.7p448) 2014/07/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2621] Avoid use of indeterminate address after 'free()'
  (minor C standard conformance issue)
* Quiet warnings from ntp_calendar.h: avoid using argument names.
(4.2.7p447) 2014/07/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2620] Use version.pm for checking version numbers in NTP::Util.
* [Bug 2624] Fix signed compare on 'l_fp'.
(4.2.7p446) 2014/06/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2597] leap file processing -- loose ends.
* [Bug 2614] use 'unsigned long' consistently in ntp_random.c
  to avoid possibly undefined behaviour in signed int overflow
* [Bug 2619] Save a signed int copy of the return value of i2d_DSA_SIG().
  Provide missing msyslog() message in crypto_alice().
* Fix a variable lifetime issue.
* Allow for version suffix in libevent in ntp_libevent.m4.
(4.2.7p445) 2014/06/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2556] mrulist isn't mentioned in the ntpq man page.
(4.2.7p444) 2014/05/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2597] leap file processing -- loose ends
  fixed coverity issues
(4.2.7p443) 2014/05/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2594] Update the year in sntp/include/copyright.def.
(4.2.7p442) 2014/05/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2589] Update VS2013 project files for libntp.
* [Bug 2600] Fix "Undisicplined Local Clock" driver1.html page.
(4.2.7p441) 2014/05/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2597] leap file processing -- loose ends
  log daily warning when leap info less than 28 days to expiration or
  already expired; nag hourly on last day before expiration; log when
  leapfile name is invalid
(4.2.7p440) 2014/04/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2536] ntpd sandboxing support (libseccomp2) cleanup.
* [Bug 2570] cleanup: fix log format for successful leapfile load
(4.2.7p439) 2014/04/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2589] fix VS2009 compile problem.
(4.2.7p438) 2014/04/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2546] Windows build documentation updates.
(4.2.7p437) 2014/03/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2537] ntpd truncates symmetric keys to 20 bytes.
* [Bug 2546] Documentation updates.
(4.2.7p436) 2014/03/31 Released by Harlan Stenn <stenn@ntp.org>
* Update to libopts-40.2.15, and autogen-5.18.3pre18.
* [Bug 2311] Add more tags to mdoc2xxx.
* [Bug 2502] Assorted text replacement errors in 4.2.7p345
* [Bug 2538] ntp programs print exit code as part of the "usage" text.
(4.2.7p435) 2014/03/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2570] cleanup: reduced logging noise, moved some functions
  into libntp.
(4.2.7p434) 2014/03/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2577] Update VS2013 solution and project files.
(4.2.7p433) 2014/03/10 Released by Harlan Stenn <stenn@ntp.org>
* Clean up last-update timestamps of html/*.html files.
* [Bug 2546] Documentation updates.
(4.2.7p432) 2014/03/09 Released by Harlan Stenn <stenn@ntp.org>
* CID 711660: Do a non-NULL pointer assertion check a bit earlier.
(4.2.7p431) 2014/03/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2572] cross-compiling fails for --with-yielding-select.
(4.2.7p430) 2014/03/04 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade to libevent-2.1.3-alpha-dev.
* [Bug 2572] cross-compiling fails for --with-yielding-select.
(4.2.7p429) 2014/03/03 Released by Harlan Stenn <stenn@ntp.org>
* CID 1165098: Remove logically dead code from refclock_true.c.
* CID 1189401: Use INSIST() instead of a belt-and-suspenders pointer check.
* In ntp_dir_sep.m4, we care about $host_os, not $target_os.
* [Bug 2170] Use AC_PREPROC_IFELSE instead of AC_EGREP_CPP.
* [Bug 2540] bootstrap script needs to 'touch' files in finer-grained groups.
* [Bug 2570] refuse to load leapsec file with bad/missing SHA1 hash
  -- change reading the hash line code: NIST omits leading zeros.
* [Bug 2576] refclock_gpsdjson.c doesn't compile if CLOCK_GPSDJSON is
  not enabled at configure time.
(4.2.7p428) 2014/03/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2570] refuse to load leapsec file with bad/missing SHA1 hash
* [Bug 2562] Distribute the code in libjsmn/ .
(4.2.7p427) 2014/03/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2562] GPSD_JSON: fix solaris issues (asprintf(), isfinite())
* [Bug 2562] first release of the GPSD client clock (type 46)
(4.2.7p426) 2014/02/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2113] Warn about ignored extra args in ntpq.
* [Bug 2540] bootstrap script needs to 'touch' files in finer-grained groups.
* [Bug 2561] Allow wildcards in the target of the "interface" command.
* [Bug 2572] cross-compiling fails for --with-yielding_select.
(4.2.7p425) 2014/02/26 Released by Harlan Stenn <stenn@ntp.org>
* Copyright file update.
(4.2.7p424) 2014/02/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2541] ntpd terminates itself with SIGHUP unexpectedly.
(4.2.7p423) 2014/02/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2565] Handle EINTR on getifaddrs().
(4.2.7p422) 2014/02/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2536] ntpd sandboxing support (libseccomp2).
(4.2.7p421) 2014/02/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 898] More documentation fixes.
* [Bug 2555] Autogen mdoc man pages all stamped with SunOS 5.10.
* calc_tickadj/Makefile.am man/mdoc page build cleanup.
(4.2.7p420) 2014/02/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 492] Clearly document ntpdate's pending deprecation.
* [Bug 1186] ntpd fails with link local IPv6 addresses.
* [Sec 2542] Strengthen the mrulist nonce.
(4.2.7p419) 2014/02/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2466] Wrap NMEA timestamps in 1024 week cycles.
(4.2.7p418) 2014/02/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2551] --disable-local-libevent breaks the build.
(4.2.7p417) 2014/02/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2539] doc and code tweaks for NMEA driver.
* Add check for enable stats to ntpd/complete.conf.in
* Fix typo in html/confopt.html
(4.2.7p416) 2014/01/31 Released by Harlan Stenn <stenn@ntp.org>
* Tweak the 'Modified' line on appropriate html pages.
* Note in the deprecation of ntpdc in its documentation.
* [Bug 2332] Be more careful about when we use 'libgcc_s'.
(4.2.7p415) 2014/01/28 Released by Harlan Stenn <stenn@ntp.org>
* Fix the man page installation for the scripts/ files.
(4.2.7p414) 2014/01/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 792] TrueTime TL-3 WWV refclock support.
* [Bug 898] Documentation fixes.
* [Bug 930] ntpdc docs refer to 'clockinfo', but mean 'clockstat'.
* [Bug 1002] ntp-keygen option and documentation updates: -p/--pvt-passwd
  is now -p/--password, and -q/--get-pvt-passwd is now -q/--export-passwd.
* [Bug 1349] statistics command not documented in HTML documentation.
  In html/monopt.html, add statistics id, definition, description, and
  correct typo.
  In html/scripts/monopt.txt, add statistics item, href, and comment.
  In ntpd/ntp.conf.def, under statistics correct four to eight kinds.
  In ntpd/complete.conf.in, add all eight kinds to statistics.
  In html/comdex.html, remove duplicate footer.
* [Bug 1734] Include man page for ntp.conf (fixed in 4.2.7p297).
* [Bug 2049] Clarify ntpdate's -d option behavior.
* [Bug 2366] ntpdc.html: burst/iburst only work on servers.
* [Bug 2493] ntptrace needs a man page (fixed in 4.2.7p402).
* [Bug 2545] Cleanup of scripts/monitoring/ntptrap.
(4.2.7p413) 2014/01/27 Released by Harlan Stenn <stenn@ntp.org>
* Require a version string for perl scripts that use autogen.
* html/ cleanup.
(4.2.7p412) 2014/01/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2540] bootstrap script needs to 'touch' files in finer-grained groups.
(4.2.7p411) 2014/01/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2532] Note in ntpdc docs that "enable pps" only works on older ntpd.
(4.2.7p410) 2014/01/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2332] Force reference to 'libgcc_s' when using GCC, because
  threading+restricted user+locked memory otherwise fails on Linux.
* [Bug 2530] Fix documentation for enable/disable mode7 and pps.
* Cleanup to the new scripts/*/Makefile.am files.
(4.2.7p409) 2014/01/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2060] Warn about restrictions with "kod" but not "limited".
(4.2.7p408) 2013/12/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2187] Update version number generation scripts.
(4.2.7p407) 2013/12/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2519] mktime.c does not compile on 64-bit Solaris but we do not
  need timegm() and the Solaris provides mktime().
* [Bug 2522] Revert Bug 2513 fix - it breaks backward compatibility.
(4.2.7p406) 2013/12/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2521] VPATH tweaks for perl -opts files.
(4.2.7p405) 2013/12/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2521] bootstrap script needs a tweak for perl -opts files.
* [Bug 2524] Add ntpsweep to sntp/loc/* files.
* [Bug 2526] Add "noinst" support to the sntp/loc/ framework.
(4.2.7p404) 2013/12/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 135] AIX5: "Address already in use" for IPv6 wildcard.
(4.2.7p403) 2013/12/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2513] Remove any PIDFILE in finish().
* [Bug 2516] Enable clock_gettime() support for AIX 5+.
* [Bug 2517] Fix peer status errors in decode.html.
(4.2.7p402) 2013/12/23 Released by Harlan Stenn <stenn@ntp.org>
* Incorporate Oliver Kindernay's GSoC 2013 scripts/ cleanup.
(4.2.7p401) 2013/11/30 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2491] VS20xx compile fixes.
(4.2.7p400) 2013/11/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2491] VS2013 project files.
(4.2.7p399) 2013/11/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2326] More leapsecond file notification cleanup.
* [Bug 2506] make sure routing updates are always tracked
* [Bug 2514] secs/* #define usage cleanup.
(4.2.7p398) 2013/11/25 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2326] More leapsecond file notification cleanup.
* Improve sntp KoD data file fopen() error message.
(4.2.7p397) 2013/11/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2326] More leapsecond file notification cleanup.
(4.2.7p396) 2013/11/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2326] Improve stale leapsecond notifications.
(4.2.7p395) 2013/11/12 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade to autogen-5.18.3pre5 and libopts-40.1.15.
(4.2.7p394) 2013/11/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1050] Change ONCORE log message for leap second announcement
  to avoid misunderstandings.
* [Bug 2499] Win32 user-space/loopback ppsapi provider drops samples.
* [Bug 2256] Improve configure's function searches in libraries.
(4.2.7p393) 2013/10/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2272] Use C99 integer types. ntp_calendar.h and ntp_types.h .
(4.2.7p392) 2013/10/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2375] Improve AIX compatibility.
* [Bug 2490] Fixed non-const initializer coming from [Bug 2250] fix.
(4.2.7p391) 2013/10/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2250] Rework of leap second handling machine.
* [Bug 2419] [rc-nmea] Improve clockstats reporting when receiver sends
  data without valid GPS fix.
(4.2.7p390) 2013/09/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2482] Cleanup of droproot and jail support for Solaris.
(4.2.7p389) 2013/09/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2473] revisited: NTPD exits after clock is stepped backwards
  Avoid possible unsigned underrun for startup condition when testing
  for clock backstep.
* [Bug 2481] ntpd aborts when both user and group are specified with -u.
* [Bug 2482] Add droproot and jail support for Solaris.
(4.2.7p388) 2013/09/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2473] NTPD exits after clock is stepped backwards externally
(4.2.7p387) 2013/09/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1642] ntpdsim can't find simnulate block in config file.
(4.2.7p386) 2013/09/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2472] (WinXP) Avoid self-termination of IO thread during exit().
(4.2.7p385) 2013/08/19 Released by Harlan Stenn <stenn@ntp.org>
* CID 975596: Copy/paste error: vallen should be siglen.
* CID 1009579: Check return status of X509_add_ext().
* [2085] Fix root distance and root dispersion calculations.
* [Bug 2426] Possibly uninitialized data in crypto_send() - CID 975596.
(4.2.7p384) 2013/08/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2450] --version has bogus short option.
(4.2.7p383) 2013/08/10 Released by Harlan Stenn <stenn@ntp.org>
* (no changes - force a rebuild for a new Coverity scan)
(4.2.7p382) 2013/08/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2454] Need way to set file descriptor limit - cleanup.
(4.2.7p381) 2013/08/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2451] rlimit command is missing from the table of contents in
  miscopt.html .
* [Bug 2452] provide io_handler/input_handler only on
  non HAVE_IO_COMPLETION_PORT platforms
* [Bug 2453] Need a way to avoid calling mlockall.
* [Bug 2454] Need way to set file descriptor limit.
* [Bug 2458] AM_CONFIG_HEADER is obsolete.
(4.2.7p380) 2013/08/03 Released by Harlan Stenn <stenn@ntp.org>
* CID 984511: Some systems have different printf needs for sizeof.
(4.2.7p379) 2013/08/02 Released by Harlan Stenn <stenn@ntp.org>
* CID 739724: Fix printf arg mismatch in a debug line.
* [Bug 2425] compile io_handler() in ntp_io.c unconditionally
* [Bug 2448] Fix checks for configure --with-stack-limit and --with-memlock
  values.
(4.2.7p378) 2013/08/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2425] move part of input handler code from ntpd.c to ntp_io.c
  and fix select()-only platforms calling input_handler directly.
* [Bug 2446] Quiet warnings from Oracle's Studio compiler.
* Upgrade to AutoGen-5.18.1pre3
* Upgrade to libopts-40.1.15.
(4.2.7p377) 2013/07/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2397] License/copyright cleanup.
* [Bug 2439] Fix check of EscapeCommFunction() in ports/winnt/libntp/termios.c.
(4.2.7p376) 2013/07/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2322] Oncore driver should send 0 PPS offset to GPS.
(4.2.7p375) 2013/07/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 883] log warning arguments swapped in refclock_gpsvme.c.
* [Bug 2368] Correct bug in previous attempt.
* [Bug 2413] Fix "make check" with automake >= 1.13.
* [Bug 2434] Line-buffer (v. block-buffer) stdout.
(4.2.7p374) 2013/07/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2368] make check troubles in libevent.
* [Bug 2425] setup SIGIO/SIGPOLL for asyncio on the read side
  of a socketpair for the worker thread.
(4.2.7p373) 2013/07/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2427] configure fails to detect recvmsg() on Solaris.
(4.2.7p372) 2013/07/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1466] Oncore should set FLAG_PPS.
* [Bug 2375] AIX 7 doesn't like a libevent validation check.
* [Bug 2423] Log command-line args at LOG_INFO.
* [Bug 2428] do_unconf() should reset 'items' before the 2nd loop.
(4.2.7p371) 2013/07/07 Released by Harlan Stenn <stenn@ntp.org>
* CID 1042586: Check the return value of clock_gettime() in worker_sleep().
* Upgrade to libopts-39.0.14 from 5.17.5pre10.
(4.2.7p370) 2013/07/06 Released by Harlan Stenn <stenn@ntp.org>
* Remove \n's from syslog output strings.
(4.2.7p369) 2013/07/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2415] RES_LIMITED flags check should use &, not &&.
* Have NTP_LIBNTP check for time.h and clock_getres().
* Fix ntpsweep to use sntp instead of ntpdate, from Oliver Kindernay.
(4.2.7p368) 2013/05/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2145] ntpq dumps core when displaying sys_var_list and more.
(4.2.7p367) 2013/04/25 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1485] Sometimes ntpd crashes
* [Bug 2382] Implement LOGTOD using ldexp() instead of shifting.
(4.2.7p366) 2013/04/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1866] Disable some debugging output in refclock_oncore.
(4.2.7p365) 2013/04/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2149] Log an error message if /proc/net/if_inet6 cannot be opened.
(4.2.7p364) 2013/03/26 Released by Harlan Stenn <stenn@ntp.org>
* Bump sntp/include/autogen-version.def .
(4.2.7p363) 2013/03/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2357] sntp/libopts/usage.c sometimes needs -lintl.
* Upgrade to libopts from 5.17.3pre10.
(4.2.7p362) 2013/03/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2364] "sed -i" is not portable.
(4.2.7p361) 2013/03/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2357] sntp/libopts/usage.c sometimes needs -lintl.
* [Bug 2365] "make check" fails in libevent.
(4.2.7p360) 2013/03/15 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade libevent (coverity fixes, etc.).
* EEXIST is OK for mkdir() in sntp/kod_management.c.
(4.2.7p359) 2013/03/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2359] Fix send_via_ntp_signd() prototype.
(4.2.7p358) 2013/02/27 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade to autogen-5.17.3pre4 and libopts-38.0.13.
* [Bug 2357] sntp/libopts/usage.c on NetBSD needs -lintl.
(4.2.7p357) 2013/02/22 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade to autogen-5.17.2pre and libopts-38.0.13.
(4.2.7p356) 2013/02/19 Released by Harlan Stenn <stenn@ntp.org>
* Added loc/debian.
(4.2.7p355) 2013/02/18 Released by Harlan Stenn <stenn@ntp.org>
* CID 739708: Check return status of fcntl() in refclock_arc.c.
* CID 739709: Check return status of fcntl() in refclock_datum.c.
* CID 739710: Check return status of mkdir() in sntp/kod_management.c.
* CID 739711: Ignore return status of remove() in ntp-keygen.c.
* CID 739723: Print sizeof as unsigned.
* CID 971094: Clean up time of check/time of use in check_leap_file().
(4.2.7p354) 2013/02/10 Released by Harlan Stenn <stenn@ntp.org>
* CID 97194: Check return from setsockopt().
* CID 739473,739532: Out-of-bounds access/illegal address computation.
* CID 739558: Double close.
* CID 739559: Double close.
* CID 739713: devmask/recmask copy/paste error.
* CID 739714: Fix code indentation level.
* CID 739715: Clean up sockaddr_dump().
(4.2.7p353) 2013/02/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2326] Check hourly for a new leapfile if the old one expired.
(4.2.7p352) 2013/01/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2326] Notice when a new leapfile has been installed.
(4.2.7p351) 2013/01/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2328] Don't apply small time adjustments on Windows versions
  which don't support this.
(4.2.7p350) 2013/01/21 Released by Harlan Stenn <stenn@ntp.org>
* Added sntp/loc/netbsd based on info from Christos Zoulas.
(4.2.7p349) 2013/01/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2321] Fixed Windows build, but autogen update still required.
(4.2.7p348) 2013/01/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2327] Rename sntp/ag-tpl/:Old to sntp/ag-tpl/Old.
* Cleanup to ntpsnmpd-opts.def.
* Cleanup to ntpq.texi.
* Documentation cleanup to the ntpd, ntpdc, ntpq and ntp-wait
  .def files.
* In ntp.conf.def, cleanup SEE ALSO, document 'rlimit' options.
* Add a reference to RFC5907 in the ntpsnmpd documentation.
(4.2.7p347) 2013/01/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2325] Re-enable mlockall() check under Linux post-1223 fix.
(4.2.7p346) 2013/01/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1223] reorganize inclusion of sys/resource.h.
(4.2.7p345) 2013/01/04 Released by Harlan Stenn <stenn@ntp.org>
* Update several .def files to use autogen-5.17 feature set.
(4.2.7p344) 2013/01/03 Released by Harlan Stenn <stenn@ntp.org>
* Refactor and enhance mdoc2texi.
* Make sure agtexi-file.tpl defines label-str.
* Cleanup to ntp.conf.def.
* Upgrade to autogen-5.17 and libopts-37.0.12.
(4.2.7p343) 2013/01/02 Released by Harlan Stenn <stenn@ntp.org>
* Update the copyright year.
(4.2.7p342) 2012/12/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2081 - Backward Incompatible] rawstats now logs everything.
(4.2.7p341) 2012/12/30 Released by Harlan Stenn <stenn@ntp.org>
(4.2.7p340) 2012/12/29 Released by Harlan Stenn <stenn@ntp.org>
* mdoc2texi fixes: trailing punctuation.
(4.2.7p339) 2012/12/26 Released by Harlan Stenn <stenn@ntp.org>
* mdoc2texi fixes: parseQuote, closing of list item tables.
* ntp-wait, ntpd, ntpdc, ntpq, ntpsnmpd autogen documentation updates.
(4.2.7p338) 2012/12/25 Released by Harlan Stenn <stenn@ntp.org>
* mdoc2texi fixes: Handle_ArCmFlIc, Handle_Fn, HandleQ.
* ntp-keygen autogen documentation updates.
* ntpq autogen docs.
(4.2.7p337) 2012/12/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1223] More final cleanup for rlimit changes.
(4.2.7p336) 2012/12/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1223] Final cleanup for rlimit changes.
(4.2.7p335) 2012/12/18 Released by Harlan Stenn <stenn@ntp.org>
* Update documentation templates and definitions.
* Create agtexi-file.tpl .
(4.2.7p334) 2012/12/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2114] Update tests for sntp's synch distance.
* Create ntp-keygen.{html,texi}.
(4.2.7p333) 2012/12/07 Released by Harlan Stenn <stenn@ntp.org>
* Autogen documentation cleanup.
(4.2.7p332) 2012/12/06 Released by Harlan Stenn <stenn@ntp.org>
* sntp documentation cleanup.
(4.2.7p331) 2012/12/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2114] Correctly calculate sntp's synch distance.
(4.2.7p330) 2012/12/03 Released by Harlan Stenn <stenn@ntp.org>
* autogen doc cleanup
(4.2.7p329) 2012/12/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2278] ACTS flag3 mismatch between code and driver18.html.
* Use an enum for the ACTS state table.
* html doc reconciliation with DLM's copy.
(4.2.7p328) 2012/11/30 Released by Harlan Stenn <stenn@ntp.org>
* html doc reconciliation with DLM's copy.
(4.2.7p327) 2012/11/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2024] Identify Events in the system status word in decode.html.'
* [Bug 2040] Provide a command-line option for the identity key bits.
* Create loc/darwin for Mac OSX
(4.2.7p326) 2012/11/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1214] 'proto: precision = ...' should be at INFO, not NOTICE.
* [Bug 2246] Clear sys_leap when voting says to disarm the leap.
(4.2.7p325) 2012/11/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2202] ntpq.html: there is no "acv" billboard.
* [Bug 2306] keep pps hack for Win32 even if user-mode/loopback
  PPS API is activated on a serial line.
(4.2.7p324) 2012/11/19 Released by Harlan Stenn <stenn@ntp.org>
* Reinstate doc fix to authentic.html from Mike T.
* [Bug 1223] cleanup for rlimit changes.
* [Bug 2098] Install DLM's HTML documentation.
* [Bug 2306] Added user-mode/loop-back PPS API provider for Win32
(4.2.7p323) 2012/11/18 Released by Harlan Stenn <stenn@ntp.org>
* html/ updates from Dave Mills.
(4.2.7p322) 2012/11/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1223] Allow configurable values for RLIMIT_STACK and
  RLIMIT_MEMLOCK.
* [Bug 1320] Log ntpd's initial command-line parameters. (updated fix)
* [Bug 2120] no sysexits.h under QNX.
* [Bug 2123] cleanup to html/leap.html.
(4.2.7p321) 2012/11/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1320] Log ntpd's initial command-line parameters.
(4.2.7p320) 2012/11/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 969] Clarify ntpdate.html documentation about -u and ntpd.
* [Bug 1217] libisc/ifiter_sysctl.c:internal_current(): Ignore RTM
  messages with wrong version
(4.2.7p319) 2012/11/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2296] Fix compile problem with building with old OpenSSL.
(4.2.7p318) 2012/11/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2301] Remove spurious debug output from ntpq.
(4.2.7p317) 2012/11/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 922] Allow interspersed -4 and -6 flags on the ntpq command line.
(4.2.7p316) 2012/10/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2296] Update fix for Bug 2294 to handle --without-crypto.
(4.2.7p315) 2012/10/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2294] ntpd crashes in FIPS mode.
(4.2.7p314) 2012/10/23 Released by Harlan Stenn <stenn@ntp.org>
* Document a tricky malloc() of dns_ctx in sntp.
(4.2.7p313) 2012/10/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2291] sntp should report why it cannot open file.kod.
* [Bug 2293] add support for SO_BINTIME, refine support for
  SO_TIMESTAMPNS (bug 1374)
(4.2.7p312) 2012/10/11 Released by Harlan Stenn <stenn@ntp.org>
* Clean up testing/debugging of fix for [Bug 938] from sntp/main.c .
(4.2.7p311) 2012/10/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 938] The argument to the -D flag takes a number, not a string.
* [Bug 1013] ntpdate's HTML page claims wrong default version.
* [Bug 1374] Support SO_TIMESTAMPNS.
(4.2.7p310) 2012/10/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1374] Support SO_TIMESTAMPNS.
* [Bug 2266] Remove deprecated refclock_trak.c from Windows Makefile
  equivalents.
* [Bug 2274] Bring libopts/enum.c back to (old) ANSI C compliance.
(4.2.7p309) 2012/10/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2287] ntpdate returns 0 even if adjtime() call fails.
(4.2.7p308) 2012/09/29 Released by Harlan Stenn <stenn@ntp.org>
* CID 97198: Check return from ioctl() calls in refclock_acts.c.
(4.2.7p307) 2012/09/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1997] Fix sntp broadcast timeouts.
* [Bug 2234] Fix incorrect ntptrace html documentation.
* [Bug 2262] Install html docs in $htmldir.
* Fix typo in html/select.html.
(4.2.7p306) 2012/09/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 752] ToS cleanup from Mike Tatarinov.
(4.2.7p305) 2012/09/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 752] Use proper ToS network packet markings for IPv4 and IPv6.
* [Bug 1232] Convert SHM refclock to use struct timespec.
* [Bug 2258] Add syslog message about leap insertion.
* [Bug 2263] broadcast server doesn't work for host with
  OS_MISSES_SPECIFIC_ROUTE_UPDATES.
* [Bug 2271] Decode refclock types when built with --disable-all-clocks.
* [Bug 2276] clk_sel240x.c #define's _XOPEN_SOURCE, breaking QNX6.
* Updates to driver28.html.
(4.2.7p304) 2012/09/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2264] Cleanup SEL240X Refclock.
* In refclock_wwv.c rename SECOND to WWV_SEC and MINUTE to WWV_MIN.
(4.2.7p303) 2012/09/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1232] Add nanosecond support to SHM driver.
(4.2.7p302) 2012/09/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2160] Log warning about expired leapseconds file.
(4.2.7p301) 2012/09/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2164] Greater precision needed for ntpq offset report.
* Clean the man5_MANS in ntpd/ .
(4.2.7p300) 2012/09/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2262] Install sntp.html into htmldir.
* [Bug 2270] Install fails due to repeated man5 page names.
(4.2.7p299) 2012/09/01 Released by Harlan Stenn <stenn@ntp.org>
* More cleanup to the bootstrap script.
(4.2.7p298) 2012/09/01 Released by Harlan Stenn <stenn@ntp.org>
* Handle additional man page sections in the bootstrap script.
* Remove extraneous parens.
* Add a missing "%s" syslog format string.
(4.2.7p297) 2012/09/01 Released by Harlan Stenn <stenn@ntp.org>
* Fix mdoc2man.
* Distribute ntp.conf.def and ntp.keys.def.
(4.2.7p296) 2012/08/31 Released by Harlan Stenn <stenn@ntp.org>
* Begin support for autogen maintaining ntp.conf and ntp.keys docs.
* Upgrade to autogen-5.16.2 and libopts-36.5.11.
* Potential bugfix for agtexi-cmd.tpl.
(4.2.7p295) 2012/08/11 Released by Harlan Stenn <stenn@ntp.org>
* Look for syslog's facilitynames[].
(4.2.7p294) 2012/08/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2242] configure fails to detect getifaddrs function on Solaris.
* [Bug 2249] Bad operator for 'test' in 'make check' of libevent.
* [Bug 2252] palisade: formats nanosecs to a 6-char field.
* Attempt to resolve strict-aliasing violation in refclock_tsyncpci.c.
* Fix && -> & typo in refclock_palisade.c debug statements.
(4.2.7p293) 2012/08/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2247] (more) Get rid of the TRAK refclock - deprecated since 2006.
* Documentation cleanup from Mike T.
* Cleanup kclk_sel240x.o rules in libparse/Makefile.am.
(4.2.7p292) 2012/08/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1545] Note why we are logging the Version string.
* [Bug 1872] Remove legacy ppsclock fdpps, #ifdef PPS.
* [Bug 2075] Fix spelling of 'incompatible'.
* [Bug 2247] Get rid of the TRAK refclock - deprecated since 2006.
* Clean up an exit status in ntpq.c.
(4.2.7p291) 2012/07/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2241] MDNS registration should only happen if requested.
(4.2.7p290) 2012/07/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1454] Add parse clock support for the SEL-240x GPS products.
* CID 709185: refclock_chu.c will leak fd==0 (better fix)
(4.2.7p289) 2012/07/16 Released by Harlan Stenn <stenn@ntp.org>
* CID 97123: Future-proof possible change to refclock_nmea.c.
* CID 97377: ntp-keygen.c's followlink() might not NUL-terminate.
* CID 709185: refclock_chu.c will leak fd==0 (which should be impossible).
(4.2.7p288) 2012/07/03 Released by Harlan Stenn <stenn@ntp.org>
* CID 709173: Make sure a libisc function we do not use is called properly.
(4.2.7p287) 2012/07/03 Released by Harlan Stenn <stenn@ntp.org>
* Remove 1024 associations-per-server limit from ntpq.
* Remove blank line between ntpq mreadvar associations.
(4.2.7p286) 2012/06/28 Released by Harlan Stenn <stenn@ntp.org>
* CID 97193: check return from sscanf() in ntp_config.c.
* CID 709169: check return from open("/dev/null", 0) and friends.
* CID 709207: Initialize "quality" for ulink_receive.
(4.2.7p285) 2012/06/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2227] Enable mrulist access control via "restrict ... nomrulist".
* Automake-1.12 wants us to use AM_PROG_AR.
* Conditionalize msyslog messages about rejected mode 6 requests due to
  nomodify and nomrulist restrictions under "logconfig +sysinfo".
* Increment sys_restricted in a few rejection paths due to nomodify
  restrictions where previosuly overlooked.
(4.2.7p284) 2012/06/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2225] libevent configure hangs.
* Update bundled libevent to git master, post libevent 2.1.1-alpha.
(4.2.7p283) 2012/06/16 Released by Harlan Stenn <stenn@ntp.org>
* In sntp/m4/ntp_openssl.m4, Support multiple package names for the
  crypto library.  Add legacy support for -Wl,-rpath.
(4.2.7p282) 2012/06/15 Released by Harlan Stenn <stenn@ntp.org>
* tickadj may need to be linked with PTHREAD_LIBS.
(4.2.7p281) 2012/06/14 Released by Harlan Stenn <stenn@ntp.org>
* U_INT32_MAX cleanup in include/ntp_types.h .
* When linking, ntp_keygen and tickadj need $(LIBM).
(4.2.7p280) 2012/06/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2224] Use-after-free in routing socket code after dropping root.
(4.2.7p279) 2012/06/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2211] findbcastinter(): possibly undefined variable iface used.
* [Bug 2220] Incorrect check for maximum association id in ntpq.
(4.2.7p278) 2012/06/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2204] Build with --enable-getifaddrs=glibc fails.
* [Bug 2178] refclock_tsyncpci.c reach register fails to shift.
* [Bug 2191] dcfd -Y y2kcheck on CentOS 6.2 x86_64 breaks make check.
(4.2.7p277) 2012/05/25 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2193] Building timestruct tests with Clang 3.1 fails.
(4.2.7p276) 2012/05/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2179] Remove sntp/header.h.
(4.2.7p275) 2012/04/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1744] Remove obsolete ntpdate/ntptime* items.
(4.2.7p274) 2012/04/25 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2174] ntpd rejects source UDP ports less than 123 as bogus.
(4.2.7p273) 2012/04/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2141] handle_sigio() calls get_systime(), which must be
  reentrant when SIGIO is used.  Sanity checks relative to the prior
  get_systime() are disabled in ntpd on systems with signaled I/O, but
  active in sntp and ntpdate.
* Correct authnumfreekeys accounting broken in 4.2.7p262.
(4.2.7p272) 2012/04/14 Released by Harlan Stenn <stenn@ntp.org>
* LCRYPTO is gone - replace with VER_SUFFIX.
* Change the link order for ntpsntpd.
* Remove extra 'nlist' check from configure.ac.
(4.2.7p271) 2012/04/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1122] openssl detection via pkg-config fails when no additional
  -Idir flags are needed.
* Avoid overwriting user variable LDFLAGS with OpenSSL flags, instead
  they are added to LDFLAGS_NTP.
(4.2.7p270) 2012/03/26 Released by Harlan Stenn <stenn@ntp.org>
* Update driver45.html page.
(4.2.7p269) 2012/03/25 Released by Harlan Stenn <stenn@ntp.org>
* Clean up configure.ac.
* Cleanup configure.ac's TSYNC PCI section.
(4.2.7p268) 2012/03/24 Released by Harlan Stenn <stenn@ntp.org>
* Update driver45.html page.
(4.2.7p267) 2012/03/23 Released by Harlan Stenn <stenn@ntp.org>
* Initial cut at a basic driver45.html page.
(4.2.7p266) 2012/03/21 Released by Harlan Stenn <stenn@ntp.org>
* Add refclock_tsyncpci.c (driver 45) supporting Spectracom TSYNC timing
  boards.
(4.2.7p265) 2012/03/20 Released by Harlan Stenn <stenn@ntp.org>
* Treat zero counter as indication of precise system time in Windows
  PPSAPI helper function pps_ntp_timestamp_from_counter(), enabling
  PPSAPI providers to use the Windows 8 precise clock directly.
(4.2.7p264) 2012/03/14 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2160] Note if leapseconds file is past its prime.
* Use GetSystemTimePreciseAsFileTime() on Windows 8.
(4.2.7p263) 2012/03/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2156] clock instability with LOCAL driver, from Miroslav Lichvar.
* [Bug 2159] Windows ntpd using leapfile erroneous leap second 20120401.
(4.2.7p262) 2012/02/29 Released by Harlan Stenn <stenn@ntp.org>
* Improve ntpd scalability for servers with many trusted keys.
(4.2.7p261) 2012/02/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2048] add the clock variable timecode to SHM refclock.
(4.2.7p260) 2012/02/24 Released by Harlan Stenn <stenn@ntp.org>
* Fix the check-scm-rev invocation in several Makefile.am's.
(4.2.7p259) 2012/02/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2148] ntpd 4.2.7p258 segfault with 0x0100000 bit in NMEA mode.
* refclock_nmea.c merge cleanup thanks to Juergen Perlinger.
(4.2.7p258) 2012/02/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2140] Rework of Windows I/O completion port handling to avoid
  garbling serial input in UNIX line discipline emulation.
* [Bug 2143] NMEA driver: discard data if quality indication not good,
  add statistic counters (mode bit enabled) to clockstats file.
(4.2.7p257) 2012/02/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2135] defer calls to 'io_input' to main thread under Windows.
(4.2.7p256) 2012/02/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2131] Set the system variable settimeofday only after clock step.
* [Bug 2134] --enable-C99-snprintf does not force rpl_snprintf use.
(4.2.7p255) 2012/01/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 603] Only link with nlist()-related libraries when needed:
  More cleanup.
(4.2.7p254) 2012/01/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 603] Only link with nlist()-related libraries when needed.
(4.2.7p253) 2012/01/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2126] Compile error on Windows with libopts from Autogen 5.14.
* Update one of the license URLs.
(4.2.7p252) 2012/01/25 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade to autogen-5.14 (and libopts-36.1.11).
(4.2.7p251) 2012/01/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2115] ntptrace should accept both rootdispersion and rootdisp.
(4.2.7p250) 2012/01/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2113] Warn about ignored extra args in ntpq.
* Update the copyright year.
(4.2.7p249) 2012/01/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2111] Remove minpoll delay before iburst for pool and
  manycastclient.
* Move refclock-specific scheduled timer code under #ifdef REFCLOCK
  and move "action" and "nextaction" data for same from struct peer to
  struct refclockproc.  These provide a way to schedule a callback some
  seconds in the future.
(4.2.7p248) 2012/01/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2109] "make clean check" is broken with gtest available.
* [Bug 2110] systime.c typo breaks build on microsecond clocks.
(4.2.7p247) 2012/01/07 Released by Harlan Stenn <stenn@ntp.org>
* Fix build break triggered by updating deps-ver and libntp/systime.c at
  the same time by explicitly depending systime_s.c on systime.c.
(4.2.7p246) 2012/01/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2104] ntpdc fault with oversize -c command.
* [Bug 2106] Fix warnings when using -Wformat-security.
* Refactor timespecops.h and timevalops.h into inline functions.
(4.2.7p245) 2011/12/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2100] conversion problem with timespec/timeval <--> l_fp fixed;
  added tests to expose the bug.
(4.2.7p244) 2011/12/25 Released by Harlan Stenn <stenn@ntp.org>
* Updates from 4.2.6p5.
(4.2.7p243) 2011/12/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2095] ntptrace now needs 'rv' instead of 'pstat', reported
  by Michael Tatarinov.
(4.2.7p242) 2011/12/21 Released by Harlan Stenn <stenn@ntp.org>
* Include missing html/icons/sitemap.png, reported by Michael Tatarinov.
* Documentation updates from Dave Mills.
(4.2.7p241) 2011/12/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2015] Overriding sys_tick should recalculate sys_precision.
* [Bug 2037] Fuzzed non-interpolated clock may decrease.
* [Bug 2068] "tos ceiling" default and cap changed to 15.
* Floor peer delay using system precision, as with jitter, reflecting
  inability to measure shorter intervals.
(4.2.7p240) 2011/12/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2092] clock_select() selection jitter miscalculated.
* [Bug 2093] Reintroduce smaller stratum factor to system peer metric.
(4.2.7p239) 2011/12/11 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p238) 2011/12/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2082] from 4.2.6p5-RC3: 3-char refid sent by ntpd 4.2.6p5-RC2
  ends with extra dot.
* [Bug 2085] from 4.2.6p5-RC3: clock_update() sys_rootdisp calculation
  omits root delay.
* [Bug 2086] from 4.2.6p5-RC3: get_systime() should not offset by
  sys_residual.
* [Bug 2087] from 4.2.6p5-RC3: sys_jitter calculation overweights
  sys.peer jitter.
* from 4.2.6p5-RC3: Ensure NULL peer->dstadr is not accessed in orphan
  parent selection.
(4.2.7p237) 2011/12/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2050] from 4.2.6p5-RC2: Orphan mode stratum counting to infinity.
* [Bug 2059] from 4.2.6p5-RC2: optional billboard column "server" does
  not honor -n.
* [Bug 2066] from 4.2.6p5-RC2: ntpq lopeers ipv6 "local" column overrun.
* [Bug 2068] from 4.2.6p5-RC2: ntpd sends nonprintable stratum 16 refid
  to ntpq.
* [Bug 2069] from 4.2.6p5-RC2: broadcastclient, multicastclient spin up
  duplicate ephemeral associations without broadcastdelay.
* [Bug 2072] from 4.2.6p5-RC2: Orphan parent selection metric needs
  ntohl().
* [Bug 2073] Correct ntpq billboard's MODE_PASSIVE t from 'u' to 'S'.
* from 4.2.6p5-RC2: Exclude not-yet-determined sys_refid from use in
  loopback TEST12 (from Dave Mills).
* from 4.2.6p5-RC2: Never send KoD rate limiting response to MODE_SERVER.
* Floor calculation of sys_rootdisp at sys_mindisp in clock_update (from
  Dave Mills).
* Restore 4.2.6 clock_combine() weighting to ntp-dev, reverting to pre-
  4.2.7p70 method while also avoiding divide-by-zero (from Dave Mills).
* Round l_fp traffic interval when converting to integer in rate limit
  and KoD calculation.
(4.2.7p236) 2011/11/16 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p235) 2011/11/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2052] Autokey CRYPTO_ASSOC host@group vallen needs checking.
(4.2.7p234) 2011/11/07 Released by Harlan Stenn <stenn@ntp.org>
* Clean up -libm entries regarding libntp.a
(4.2.7p233) 2011/11/06 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p232) 2011/11/05 Released by Harlan Stenn <stenn@ntp.org>
* Update the NEWS file so we note the default disable of mode 7 requests.
* Clean up some bitrotted code in libntp/socket.c.
(4.2.7p231) 2011/11/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1940] ignore auth key if hex decoding fails.
* Add ntpq reslist command to query access restrictions, similar to
  ntpdc's reslist.
(4.2.7p230) 2011/11/01 Released by Harlan Stenn <stenn@ntp.org>
* Disable mode 7 (ntpdc) query processing in ntpd by default.  ntpq is
  believed to provide all functionality ntpdc did, and uses a less-
  fragile protocol that's safer and easier to maintain.  If you do find
  some management via ntpdc is needed, you can use "enable mode7" in the
  ntpd configuration.
* Directly limit the number of datagrams in a mrulist response, rather
  than limiting the number of entries returned to indirectly limit the
  datagram count.
* Documentation updates from Dave Mills.
(4.2.7p229) 2011/10/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1995] fix wrong use of ZERO() macro in 'ntp_calendar.c'
(4.2.7p228) 2011/10/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1995] add compile time stamp based era unfolding for
  'step_systime()' and necessary support to 'ntp-calendar.c'.
(4.2.7p227) 2011/10/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2036] gcc 2.95.3 preprocessor can't nest #ifdef in macro args.
* A number of compiler warnings eliminated.
(4.2.7p226) 2011/10/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2035] ntpq -c mrulist sleeps 1 sec between queries, not 5 msec.
* Documentation updates from Dave Mills.
(4.2.7p225) 2011/10/15 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p224) 2011/10/14 Released by Harlan Stenn <stenn@ntp.org>
* ntpq mrulist shows intermediate counts every five seconds while
  retrieving list, and allows Ctrl-C interruption of the retrieval,
  showing the incomplete list as retrieved.  Reduce delay between
  successive mrulist retrieval queries from 30 to 5 msec.  Do not
  give up mrulist retrieval when a single query times out.
(4.2.7p223) 2011/10/12 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p222) 2011/10/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2029] "make check" clutters syslog.
* Log signal description along with number on ntpd exit.
(4.2.7p221) 2011/10/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2025] Switching between daemon and kernel loops can doubly-
  correct drift
* [Bug 2028] ntpd -n (nofork) redirects logging to stderr.
* Documentation updates from Dave Mills.
(4.2.7p220) 2011/10/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1945] mbg_gps166.h use of _TM_DEFINED conflicts with MS VC.
* [Bug 1946] parse_start uses open; does not work on Windows.
* [Bug 1947] Porting parse-based Wharton refclock driver to Windows.
* [Bug 2024] Remove unused system event code EVNT_CLKHOP.
(4.2.7p219) 2011/10/04 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p218) 2011/10/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2019] Allow selection of cipher for private key files.
* Documentation updates from Dave Mills.
* ntp-keygen private key cipher default now triple-key triple DES CBC.
* ntp-keygen -M is intended to ignore all other defaults and
  options, so do not attempt to open existing Autokey host certificate
  before generating symmetric keys and terminating.
* Restore IFF, MV, and GQ identity parameter filename convention to
  ntpkey_<scheme>par_<group/host> in ntpd, matching ntp-keygen.
* Change some error logging to syslog to ignore logconfig mask, such
  as reporting PPSAPI failure in NMEA and WWVB refclocks.
* ntp-keygen on Windows XP and later systems will now create links
  expected by ntpd.  They are hardlinks on Windows, soft on POSIX.
* Conditionalize NMEA serial open message under clockevent.
* Send all peer variables to trappers in report_event().
(4.2.7p217) 2011/09/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2020] ntp-keygen -s no longer sets host in cert file name.
* [Backward Incompatible] ntp-keygen -i option long name changed from
  misleading --issuer-name to --ident.
(4.2.7p216) 2011/09/27 Released by Harlan Stenn <stenn@ntp.org>
* sntp documentation tag cleanup.
* mdoc2man improvements.
(4.2.7p215) 2011/09/24 Released by Harlan Stenn <stenn@ntp.org>
* Use patched mdoc2man script, from Eric Feng.
* Sync with ntp-4.2.6p4 (a no-op).
(4.2.7p214) 2011/09/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1981] Initial offset convergence applies frequency correction 2x
  with kernel discipline.
* [Bug 2008] Initial offset convergence degraded with 500 PPM adjtime().
* [Bug 2009] EVNT_NSET adj_systime() mishandled by Windows ntpd.
(4.2.7p213) 2011/09/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1999] NMEA does not send PMOTG messages any more.
(4.2.7p212) 2011/09/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2003] from 4.2.6p4-RC3: ntpq_read_assoc_peervars() broken.
(4.2.7p211) 2011/09/01 Released by Harlan Stenn <stenn@ntp.org>
* Update libevent to git head (2.1 branch) as of 2.0.14-stable.
(4.2.7p210) 2011/08/31 Released by Harlan Stenn <stenn@ntp.org>
* Require -D4 or higher for ntpd SIGALRM debug trace from [Bug 2000].
(4.2.7p209) 2011/08/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2000] ntpd worker threads must block signals expected in main
  thread.
* [Bug 2001] add ntpq -c timerstats like ntpdc -c timerstats.
* [Bug 2001] from 4.2.6p4-RC3: ntpdc timerstats reports overruns as
  handled.
* Update sntp tests to track the change of root dispersion to
  synchronization distance.
(4.2.7p208) 2011/08/24 Released by Harlan Stenn <stenn@ntp.org>
* Fix the CLOCK_MONOTONIC TRACE() message.
(4.2.7p207) 2011/08/22 Released by Harlan Stenn <stenn@ntp.org>
* Restore the original CLOCK_MONOTONIC output format in sntp.
* Cleanups for ntp-wait-opts.def and ntp.keys.def .
(4.2.7p206) 2011/08/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1993] ntpd Windows port adj_systime() broken in 4.2.7p203.
* sntp documentation and behavior improvements suggested by
  Steven Sommars.
* Have sntp report synchronization distance instead of root dispersion.
* Clean up ntp-wait-opts.def .
(4.2.7p205) 2011/08/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1992] util/tg2 doesn't compile, needs libntp.
(4.2.7p204) 2011/08/16 Released by Harlan Stenn <stenn@ntp.org>
* Added support for Garmin's $PGRMF sentence to NMEA driver
* [Bug 1988] Better sntp send failed error message needed.
* [Bug 1989] sntp manual page sometimes refers to SNTP as a program.
* [Bug 1990] sntp output should include stratum.
(4.2.7p203) 2011/08/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1986] Require Visual C++ 2005 or later compilers in Windows port.
* Actually use long long for (u_)int64 by correcting spelling of
  SIZEOF_LONG_LONG in ntp_types.h.
* Force .exe minimum Windows version to 0x0400 to allow NT4 in
  vs2005/*.vcproj files.
* Fix make distcheck with --enable-libevent-regress problem with
  unwritable $srcdir.
* Correct init_logging()'s def_syslogmask type to u_int32 following
  change of ntp_syslogmask from u_long to u_int32 in p202.
(4.2.7p202) 2011/08/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1983] --without-sntp build breaks in sntp subdir.
* [Bug 1984] from 4.2.6p4-RC3: ntp/libisc fails to compile on OS X 10.7.
* [Bug 1985] from 4.2.6p4-RC3: "logconfig =allall" rejected.
(4.2.7p201) 2011/08/05 Released by Harlan Stenn <stenn@ntp.org>
* sntp: change -h/--headspace to -g/--gap, and change the default gap
  from 10 to 50ms
* [Backward Incompatible] from 4.2.6p4: sntp: -l/--filelog ->
  -l/--logfile, to be consistent with ntpd.
* Documentation updates from Dave Mills.
* From 4.2.6p4: libopts/file.c fix from Bruce Korb (arg-type=file).
(4.2.7p200) 2011/08/04 Released by Harlan Stenn <stenn@ntp.org>
* Sync with 4.2.6p4-RC2.
(4.2.7p199) 2011/07/29 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p198) 2011/07/28 Released by Harlan Stenn <stenn@ntp.org>
* remove old binsubdir stuff from SNTP, as NTP_LOCINFO does that now.
(4.2.7p197) 2011/07/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1975] from 4.2.6p4-RC2: libntp/mktime.c won't work with 64-bit
  time_t
* [Bug 1976] genLocInfo writes to srcdir break 'make distcheck'.
* [Bug 1977] Fix flag/description mismatches in ntp-keygen-opts.def.
* Do not force "legacy" when --with-locfile is not given, genLocInfo
  will find the correct default for the system.
* Fix warnings in ntp_request.c ([Bug 1973] oversight) and sntp/main.c
  (CID 159, apparent overrun due to union, actually correct).
* Update sntp/loc/solaris to conform to stock locations.
(4.2.7p196) 2011/07/27 Released by Harlan Stenn <stenn@ntp.org>
* DEFAULT INSTALLATION DIRECTORY CHANGES ON SOME OSes: to get the old
  behavior, pass --with-locfile=legacy to 'configure'
* [Bug 1972] from 4.2.6p4-RC2: checking for struct rtattr fails.
* [Bug 1973] Widen reference clock mode from 8 to 32 bits.
* Removed sntp/m4/ntp_bindir.m4 - no longer needed.
* Move loc/ to sntp/loc/ .
* Move scripts/cvo.sh to sntp/scripts/cvo.sh .
* Move scripts/genLocInfo to sntp/scripts/genLocInfo .
* Give NTP_LOCINFO an optional path-to argument.
* Remove hacks to get NTP_LOCINFO-related data to sntp/ .
* Move sntp/include/mansec2subst.sed to sntp/scripts/mansec2subst.sed .
* If no "more specific" loc file is found for redhat* or fedora*,
  look for a loc/redhat file.
* If no "more specific" loc file is found and uname says this is Linux,
  look for a loc/linux file.
* Improve the help text: --with-locfile=XXX .
* work around solaris /bin/sh issues for genLocInfo.
(4.2.7p195) 2011/07/25 Released by Harlan Stenn <stenn@ntp.org>
* Added loc/redhat.
(4.2.7p194) 2011/07/25 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1608] from 4.2.6p4-RC2: Parse Refclock driver should honor
  trusttime.
* Add support for installing programs and scripts to libexec.
* Added loc/solaris.
(4.2.7p193) 2011/07/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1970] from 4.2.6p4-RC2: UNLINK_EXPR_SLIST() causes crash if list
  is empty.
* Update libevent to 2.1 HEAD as of merge of 2.0.13-stable-dev.
* Match addr_eqprefix() sizeof and memcpy destination to make it clear
  to static analysis that there is no buffer overrun (CID 402).
(4.2.7p192) 2011/07/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1966] Broken FILES section for ntp.keys.def.
(4.2.7p191) 2011/07/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1948] Update man page section layout.
* [Bug 1963] add reset command for ntpq :config, similar to ntpdc's.
* [Bug 1964] --without-sntp should not build sntp.
(4.2.7p190) 2011/07/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1961] from 4.2.6p4: html2man update: distribute ntp-wait.html.
* Require autogen-5.12.
(4.2.7p189) 2011/07/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1134] from 4.2.6p4-RC1: ntpd fails binding to tentative IPv6
  addresses.
* [Bug 1790] from 4.2.6p4-RC1: Update config.guess and config.sub to
  detect AIX6.
(4.2.7p188) 2011/06/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1958] genLocInfo must export PATH.
* ntp-wait: some versions of ntpd spell "associd" differently.
(4.2.7p187) 2011/06/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1954] Fix typos in [s]bin_PROGRAMS in ntpd/Makefile.am.
* Implement --with-locfile=filename configure argument.  If filename is
  empty we'll look under loc/ for a good fit.  If the filename contains
  a / character, it will be treated as a "normal" pathname.  Otherwise,
  that explicit file will be searched for under loc/ .
(4.2.7p186) 2011/06/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1950] Control installation of event_rpcgen.py.
* Update .point-changed-filelist for the new man pages.
* Update the building of OS-specific programs.
* Finish conversion to genLocInfo.
* validate MANTAGFMT in genLocInfo.
* Documentation update from Dave Mills.
(4.2.7p185) 2011/06/21 Released by Harlan Stenn <stenn@ntp.org>
* ntp_locs.m4: handle the case where . is not in the PATH.
* More genLocInfo cleanup.
(4.2.7p184) 2011/06/20 Released by Harlan Stenn <stenn@ntp.org>
* Added ntp_locs.m4.
* genLocInfo improvements.
* Add the man page tag "flavor" to the loc.* files.
* Add/distribute genLocInfo.
(4.2.7p183) 2011/06/19 Released by Harlan Stenn <stenn@ntp.org>
* Update the autogen include list for scripts/Makefile.am.
* Added loc.freebsd (and distribute it).
* Added loc.legacy (and distribute it).
(4.2.7p182) 2011/06/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1304] Update sntp.html to reflect new implementation.
* Update .point-changed-filelist .
* ntpdc documentation fixes.
* Update ntp-wait autogen docs.
* Update the ntpd autogen docs.
* Update the ntpsnmpd autogen docs.
* Use autogen to produce ntp-keygen docs.
* Add "license name" to ntp.lic for autogen-5.11.10.
* Prepare for ntp.keys.5.
(4.2.7p181) 2011/06/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1938] addr_eqprefix() doesn't clear enough storage.
(4.2.7p180) 2011/06/06 Released by Harlan Stenn <stenn@ntp.org>
* Upgrade to libevent-2.0.12.
* More sntp.1 cleanups.
* Produce ntpq.1 with the new autogen macros.
* Remove the deprecated "detail" stanza from ntpdc-opts.def.
(4.2.7p179) 2011/06/03 Released by Harlan Stenn <stenn@ntp.org>
* Update cmd-doc.tlib to autogen-5.11.10pre5.
* Upgrade local autoopts templates to 5.11.10pre5.
(4.2.7p178) 2011/06/02 Released by Harlan Stenn <stenn@ntp.org>
* Update the std_def_list to include the ntp.lic file.
* Distribute the ntp.lic file.
* Add http://ntp.org/license to the ntp.lic file.
(4.2.7p177) 2011/06/01 Released by Harlan Stenn <stenn@ntp.org>
* Use the latest autogen's new copyright template code.
* Clean up the ntp.lic file.
(4.2.7p176) 2011/05/31 Released by Harlan Stenn <stenn@ntp.org>
* sntp documentation cleanup.
* autogen documentation template cleanup.
(4.2.7p175) 2011/05/30 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1936] Correctly set IPV6_MULTICAST_LOOP.
* cmd-doc.tlib cleanup from Bruce Korb.
* sntp documentation cleanup.
(4.2.7p174) 2011/05/28 Released by Harlan Stenn <stenn@ntp.org>
* ntpdc documentation cleanup.
* sntp documentation cleanup.
* Don't build libevent with openssl support.  Right now, libevent
  doesn't use pkg-config to find openssl's installation location.
(4.2.7p173) 2011/05/25 Released by Harlan Stenn <stenn@ntp.org>
* Typo in emalloc.c hides file and line number from emalloc() error msg.
* parsesolaris.c compile fails on SPARC Solaris with conflicting printf.
* ntp_util.c compile fails on AIX and OSF with conflicting statsdir.
(4.2.7p172) 2011/05/24 Released by Harlan Stenn <stenn@ntp.org>
* Remove hardcoded 1/960 s. fudge for <CR> transmission time at 9600 8n1
  from WWVB/Spectracom driver introduced in 4.2.7p169.
(4.2.7p171) 2011/05/23 Released by Harlan Stenn <stenn@ntp.org>
* Eliminate warnings about shadowing global "basename" on Linux.
* Use filegen_config() consistently when changing filegen options.
* mprintf() should go to stdout, not stderr.  DPRINTF() uses mprintf().
* Repair a few simulator problems (more remain).
* Documentation updates from Dave Mills.
(4.2.7p170) 2011/05/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1932] libevent/util_internal.h builtin_expect compile error with
  gcc 2.95.
* Use 64-bit scalars in LFPTOD() and DTOLFP() on more platforms by
  conditionalizing on HAVE_U_INT64 rather than UINT64_MAX.
(4.2.7p169) 2011/05/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1933] WWVB/Spectracom driver timestamps LFs, not CRs.
(4.2.7p168) 2011/05/16 Released by Harlan Stenn <stenn@ntp.org>
* Convert receive buffer queue from doubly-linked list to FIFO.
(4.2.7p167) 2011/05/14 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1927] io_closeclock() should purge pending recvbufs.
* [Bug 1931] cv always includes fudgetime1, never fudgetime2.
* Use acts_close() in acts_shutdown() to avoid leaving a stale lockfile
  if unpeered via runtime configuration while the modem is open.
* Correct acts_close() test of pp->io.fd to see if it is open.
* 4.2.7p164 documentation updates re: 'tos orphanwait' expanded scope.
(4.2.7p166) 2011/05/13 Released by Harlan Stenn <stenn@ntp.org>
* If we have local overrides for autogen template files, use them.
* Convert more of the sntp-opt.def documentation from man to mdoc.
(4.2.7p165) 2011/05/11 Released by Harlan Stenn <stenn@ntp.org>
* Convert snmp docs to mdoc format, which requires autogen 5.11.9.
* from 4.2.6p4-RC1: Require autogen 5.11.9.
(4.2.7p164) 2011/05/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 988] Local clock eats up -g option, so ntpd stops with large
  initial time offset.
* [Bug 1921] LOCAL, ACTS drivers with "prefer" excluded from initial
  candidate list.
* [Bug 1922] "tos orphanwait" applied incorrectly at startup.
* [Bug 1923] orphan parent favored over LOCAL, ACTS drivers.
* [Bug 1924] Billboard tally codes sometimes do not match operation,
  variables.
* Change "pool DNS" messages from msyslog to debug trace output.
* Remove unused FLAG_SYSPEER from peer->status.
* Respect "tos orphanwait" at startup.  Previously there was an
  unconditional 300 s. startup orphanwait, though other values were
  respected for subsequent orphan wait periods after no_sys_peer events.
* Apply "tos orphanwait" (def. 300 seconds) to LOCAL and ACTS reference
  clock drivers, in addition to orphan parent operation.  LOCAL and ACTS
  are not selectable during the orphanwait delay at startup and after
  each no_sys_peer event.  This prevents a particular form of clock-
  hopping, such as using LOCAL briefly at startup before remote peers
  are selectable.  This fixes the issue reported in [Bug 988].
* Documentation updates from Dave Mills.
(4.2.7p163) 2011/05/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1911] missing curly brace in libntp/ntp_rfc2553.c
(4.2.7p162) 2011/05/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1910] Support the Tristate Ltd. TS-GPSclock-01.
(4.2.7p161) 2011/05/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1904] 4.2.7p160 Windows build broken (POSIX_SHELL).
* [Bug 1906] 4.2.7p160 - libtool: compile: cannot determine name of
  library object in ./libevent
* Share a single sntp/libevent/build-aux directory between all three
  configure scripts.
* Add missing --enable-local-libevent help to top-level configure.
(4.2.7p160) 2011/05/01 Released by Harlan Stenn <stenn@ntp.org>
* from 4.2.6p4-RC1: Upgrade to libopts 35.0.10 from AutoGen 5.11.9pre8.
* [Bug 1901] Simulator does not set progname.
(4.2.7p159) 2011/04/28 Released by Harlan Stenn <stenn@ntp.org>
* Fix a couple of unused variable warnings.
* cleanup in timespecops.c / timevalops.c
(4.2.7p158) 2011/04/24 Released by Harlan Stenn <stenn@ntp.org>
* Update libevent --disable-libevent-regress handling to work when
  building libevent using mingw.
(4.2.7p157) 2011/04/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1890] 4.2.7p156 segfault in duplicate freeaddrinfo().
(4.2.7p156) 2011/04/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1851] freeaddrinfo() called after getaddrinfo() fails.
(4.2.7p155) 2011/04/18 Released by Harlan Stenn <stenn@ntp.org>
* Fix leak in refclock_datum.c start failure path.
(4.2.7p154) 2011/04/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1887] DNS fails on 4.2.7p153 using threads.
(4.2.7p153) 2011/04/16 Released by Harlan Stenn <stenn@ntp.org>
* A few more Coverity Scan cleanups.
(4.2.7p152) 2011/04/15 Released by Harlan Stenn <stenn@ntp.org>
* Update embedded libevent to current 2.1 git HEAD.
(4.2.7p151) 2011/04/14 Released by Harlan Stenn <stenn@ntp.org>
* Detect vsnprintf() support for "%m" and disable our "%m" expansion.
* Add --enable-c99-sprintf to configure args for -noopenssl variety of
  flock-build to avoid regressions in (v)snprintf() replacement.
* More msnprintf() unit tests.
* Coverity Scan error checking fixes.
* Log failure to fetch time from HOPF_P hardware.
* Check HOPF_S sscanf() conversion count before converted values.
(4.2.7p150) 2011/04/13 Released by Harlan Stenn <stenn@ntp.org>
* Remove never-used, incomplete ports/winnt/ntpd/refclock_trimbledc.[ch]
* On systems without C99-compliant (v)snprintf(), use C99-snprintf
  replacements (http://www.jhweiss.de/software/snprintf.html)
* Remove remaining sprintf() calls except refclock_ripencc.c (which is
  kept out of --enable-all-clocks as a result), upstream libs which use
  sprintf() only after careful buffer sizing.
(4.2.7p149) 2011/04/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1881] describe the {+,-,s} characters in configure --help output.
(4.2.7p148) 2011/04/09 Released by Harlan Stenn <stenn@ntp.org>
* Use _mkgmtime() as timegm() in the Windows port, rather than
  libntp/mktime.c's timegm().  Fixed [Bug 1875] on Windows using the old
  asn2ntp() code from before 4.2.7p147.
* ntp_crypto.c string buffer safety.
* Remove use of MAXFILENAME in mode 7 (ntpdc) on-wire structs.
* Change ntpd MAXFILENAME from 128 to 256 to match ntp-keygen.
* Buffer safety and sign extension fixes (thanks Coverity Scan).
(4.2.7p147) 2011/04/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1875] 'asn2ntp()' rewritten with 'caltontp()'; 'timegm()'
  substitute likely to crash with 64bit time_t.
(4.2.7p146) 2011/04/05 Released by Harlan Stenn <stenn@ntp.org>
* String buffer safety cleanup, converting to strlcpy() and strlcat().
* Use utmpname() before pututline() so repeated steps do not
  accidentally record into wtmp where utmp was intended.
* Use setutent() before each pututline() including first.
(4.2.7p145) 2011/04/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1840] ntp_lists.h FIFO macros buggy.
(4.2.7p144) 2011/04/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1874] ntpq -c "rv 0 sys_var_list" empty.
(4.2.7p143) 2011/03/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1732] ntpd ties up CPU on disconnected USB refclock.
* [Bug 1861] tickadj build failure using uClibc.
* [Bug 1862] in6addr_any test in configure fooled by arm gcc 4.1.3 -O2.
* Remove kernel line discipline driver code for clk and chu, deprecate
  related LDISC_ flags, and remove associated ntpd code to decode the
  timestamps, remove clktest line discipline test program.
* Remove "signal_no_reset: signal 17 had flags 4000000" logging, as it
  indicates no problem and is interpreted as an error.  Previously some
  bits had been ignored one-by-one, but Linux SA_RESTORER definition is
  unavailable to user headers.
(4.2.7p142) 2011/03/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1844] ntpd 4.2.7p131 NetBSD, --gc-sections links bad executable.
* Fix "make distcheck" break in libevent/sample caused by typo.
(4.2.7p141) 2011/03/20 Released by Harlan Stenn <stenn@ntp.org>
* Add "ntpq -c iostats" similar to "ntpdc -c iostats".
* Compare entire timestamp to reject duplicates in refclock_pps().
(4.2.7p140) 2011/03/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1848] ntpd 4.2.7p139 --disable-thread-support does not compile.
* Add --disable-thread-support to one flock-build variation.
* One more lock-while-init in lib/isc/task.c to quiet lock analysis.
(4.2.7p139) 2011/03/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1848] make check ntpd --saveconfigquit clutters syslog.
(4.2.7p138) 2011/03/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1846] MacOSX: debug symbol not found by propdelay or tickadj.
(4.2.7p137) 2011/03/07 Released by Harlan Stenn <stenn@ntp.org>
* Use TRACE() instead of DPRINTF() for libntp and utilities, which
  use the "debug" variable regardless of #ifdef DEBUG.
* Declare debug in libntp instead of each program.  Expose extern
  declaration to utilities, libntp, and DEBUG ntpd.
* Lock under-construction task, taskmgr objects to satisfy Coverity's
  mostly-correct assumptions about which variables are protected by
  which locks.
(4.2.7p136) 2011/03/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1839] 4.2.7p135 still installs libevent ev*.h headers.
(4.2.7p135) 2011/03/02 Released by Harlan Stenn <stenn@ntp.org>
* libevent: When building on systems with CLOCK_MONOTONIC available,
  separate the internal timeline (possibly counting since system boot)
  from the gettimeofday() timeline in event_base cached timevals.  Adds
  new event_base_tv_cached() to retrieve cached callback round start
  time on the internal timeline, and changes
  event_based_gettimeofday_cached() to always return times using the
  namesake timeline.  This preserves the benefit of using the never-
  stepped monotonic clock for event timeouts while providing clients
  with times consistently using gettimeofday().
* Correct event_base_gettimeofday_cached() workaround code in
  sntp to work with corrected libevent.
* Remove sntp l_fp_output() test now that it uses prettydate().
* [Bug 1839] 4.2.7p131 installs libevent ev*.h headers.
* Ensure CONFIG_SHELL is not empty before relying on it for #! scripts.
(4.2.7p134) 2011/02/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1837] Build fails on Win7 due to regedit requiring privilege.
* Provide fallback definitions for GetAdaptersAddresses() for Windows
  build environments lacking iphlpapi.h.
* Rename file containing 1.xxxx ChangeSet revision from version to
  scm-rev to avoid invoking GNU make implicit rules attempting to
  compile version.c into version.  Problem was with sntp/version.o
  during make distcheck after fix for spurious sntp rebuilds.
* Add INC_ALIGNED_PTR() macro to align pointers like malloc().
(4.2.7p133) 2011/02/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1834] ntpdate 4.2.7p131 aborts with assertion failure.
* Move sntp last in top-level Makefile.am SUBDIRS so that the libevent
  tearoff (if required) and sntp are compiled after the rest.
* Use a single set of Automake options for each package in configure.ac
  AM_INIT, remove Makefile.am AUTOMAKE_OPTIONS= lines.
* Correct spurious sntp rebuilds triggered by a make misperception
  sntp/version was out-of-date relative to phony target FRC.version.
* Do not cache paths to perl, test, or pkg-config, searching the PATH
  at configure time is worth it to pick up tool updates.
(4.2.7p132) 2011/02/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1832] ntpdate doesn't allow timeout > 2s.
* [Bug 1833] The checking sem_timedwait() fails without -pthread.
* ElectricFence was suffering bitrot - remove it.  valgrind works well.
* Enable all relevant automake warnings.
* Correct Solaris 2.1x PTHREAD_ONCE_INIT extra braces test to avoid
  triggering warnings due to excess braces.
* Remove libevent-cfg from sntp/Makefile.am.
* Provide bug report and URL options to Autoconf.
* Avoid relying on remake rules for routine build/flock-build for
  libevent as for the top-level and sntp subproject.
(4.2.7p131) 2011/02/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1087] -v/--normalverbose conflicts with -v/--version in sntp.
* [Bug 1088] sntp should (only) report the time difference without -s/-a.
* older autoconf sometimes dislikes [].
* Move "can't write KoD file" warning from sntp shutdown to startup.
* refclock_acts.c cleanup from Dave Mills.
* Convert sntp to libevent event-driven socket programming.  Instead of
  blocking name resolution and querying one NTP server at a time,
  resolve server names and send NTP queries without blocking.  Add
  sntp command-line options to adjust timing and optionally wait for all
  servers to respond instead of exiting after the first.
* Import libevent 2.0.10-stable plus local patches as a tearoff, used
  only if the target system lacks an installed libevent 2.0.9 or later.
* Move blocking worker and resolver to libntp from ntpd.
* Use threads rather than forked child processes for blocking worker
  when possible.  Override with configure --disable-thread-support.
* Move init_logging(), change_logfile(), and setup_logfile() from ntpd
  to libntp, use them in sntp.
* Test --without-sntp in flock-build script's -no-refclocks variety.
* Avoid invoking config.status twice in a row in build script.
* Move more m4sh tests needed by libntp to shared .m4 files.
* Split up ntp_libntp.m4 into smaller, more specific subsets.
* Enable gcc -Wcast-align, fix many instances of warnings when casting
  a pointer to a more-strictly-aligned underlying type.
(4.2.7p130) 2011/02/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1811] Update the download location in WHERE-TO-START.
(4.2.7p129) 2011/02/09 Released by Harlan Stenn <stenn@ntp.org>
* Add missing "break;" to ntp_control.c ctl_putsys() for caliberrs, used
  by ntpq -c kerninfo introduced in 4.2.7p104.
* Fix leak in ntp_control.c read_mru_list().
(4.2.7p128) 2011/01/30 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1799] ntpq mrv crash.
* [Bug 1801] ntpq mreadvar requires prior association caching.
(4.2.7p127) 2011/01/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1797] Restore stale timestamp check from the RANGEGATE cleanup.
(4.2.7p126) 2011/01/27 Released by Harlan Stenn <stenn@ntp.org>
* Fix unexposed fencepost error in format_time_fraction().
* Add more unit tests for timeval_tostr() and timespec_tostr().
(4.2.7p125) 2011/01/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1794] ntpq -c rv missing clk_wander information.
* [Bug 1795] ntpq readvar does not display last variable.
(4.2.7p124) 2011/01/25 Released by Harlan Stenn <stenn@ntp.org>
* sntp/Makefile.am needs any passed-in CFLAGS.
(4.2.7p123) 2011/01/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1788] tvtots.c tables inaccurate
(4.2.7p122) 2011/01/22 Released by Harlan Stenn <stenn@ntp.org>
* ACTS refclock cleanup from Dave Mills.
* Avoid shadowing the "group" global variable.
(4.2.7p121) 2011/01/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1786] Remove extra semicolon from ntp_proto.c .
(4.2.7p120) 2011/01/20 Released by Harlan Stenn <stenn@ntp.org>
* Change new timeval and timespec to string routines to use snprintf()
  rather than hand-crafted conversion, avoid signed int overflow there.
* Add configure support for SIZEOF_LONG_LONG to enable portable use of
  snprintf() with time_t.
* Grow ntpd/work_thread.c arrays as needed.
* Add DEBUG_* variants of ntp_assert.h macros which compile away using
  ./configure --disable-debugging.
* Fix tvalops.cpp unit test failures for 32-bit builds.
* Return to a single autoreconf invocation in ./bootstrap script.
* Fix warnings seen on FreeBSD 9.
* crypto group changes from Dave Mills.
* Lose the RANGEGATE check in PPS, from Dave Mills.
* ACTS refclock cleanup from Dave Mills.
* Documentation updates from Dave Mills.
* NMEA driver documentation update from Juergen Perlinger.
(4.2.7p119) 2011/01/18 Released by Harlan Stenn <stenn@ntp.org>
* added timespecops.{c,h} and tievalops.{c.h} to libntp and include
  added tspecops.cpp to tests/libntp
* Correct msyslog.c build break on Solaris 2.9 from #ifdef/#if mixup.
(4.2.7p118) 2011/01/15 Released by Harlan Stenn <stenn@ntp.org>
* Simplify the built-sources stuff in sntp/ .
* Fix check for -lipv6 on HP-UX 11.
(4.2.7p117) 2011/01/13 Released by Harlan Stenn <stenn@ntp.org>
* Add configure --without-sntp option to disable building sntp and
  sntp/tests.  withsntp=no in the environment changes the default.
* Build infrastructure cleanup:
  Move m4 directory to sntp/m4.
  Share a single set of genver output between sntp and the top level.
  Share a single set of autogen included .defs in sntp/include.
  Share a single set of build-aux scripts (e.g. config.guess, missing).
  Add ntp_libntp.m4 and ntp_ipv6.m4 to reduce configure.ac duplication.
  Warn and exit build/flock-build if bootstrap needs to be run.
(4.2.7p116) 2011/01/10 Released by Harlan Stenn <stenn@ntp.org>
* refclock_nmea.c refactoring by Juergen Perlinger.
(4.2.7p115) 2011/01/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1780] Windows ntpd 4.2.7p114 crashes in ioctl().
* [Bug 1781] longlong undefined in sntp handle_pkt() on Debian amd64.
(4.2.7p114) 2011/01/08 Released by Harlan Stenn <stenn@ntp.org>
* Fix for openssl pkg-config detection eval failure.
* Add erealloc_zero(), refactor estrdup(), emalloc(), emalloc_zero() to
  separate tracking callsite file/line from using debug MS C runtime,
  and to reduce code duplication.
(4.2.7p113) 2011/01/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1776] sntp mishandles -t/--timeout and -a/--authentication.
* Default to silent make rules, override with make V=1 or ./configure
  --disable-silent-rules.
* Correct --with-openssl-incdir defaulting with pkg-config.
* Correct ./build on systems without gtest available.
* Begin moving some of the low-level socket stuff to libntp.
(4.2.7p112) 2011/01/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1773] openssl not detected during ./configure.
* [Bug 1774] Segfaults if cryptostats enabled and built without OpenSSL.
* Use make V=0 in build script to increase signal/noise ratio.
(4.2.7p111) 2011/01/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1772] refclock_open() return value check wrong for ACTS.
* Default --with-openssl-libdir and --with-openssl-incdir to the values
  from pkg-config, falling back on our usual search paths if pkg-config
  is not available or does not have openssl.pc on PKG_CONFIG_PATH.
* Change refclock_open() to return -1 on failure like open().
* Update all refclock_open() callers to check for fd <= 0 indicating
  failure, so they work with older and newer refclock_open() and can
  easily backport.
* Initialize refclockproc.rio.fd to -1, harmonize refclock shutdown
  entrypoints to avoid crashing, particularly if refclock_open() fails.
* Enable tickadj-like taming of wildly off-spec Windows clock using
  NTPD_TICKADJ_PPM env. var. specifying baseline slew.
(4.2.7p110) 2011/01/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1771] algorithmic error in 'clocktime()' fixed.
* Unit tests extended for hard-coded system time.
* make V=0 and configure --enable-silent-rules supported.
* setvar modemsetup = ATE0... overrides ACTS driver default.
* Preserve last timecode in ACTS driver (ntpq -ccv).
* Tolerate previous ATE1 state when sending ACTS setup.
* Enable raw tty line discipline in Windows port.
* Allow tty open/close/open to succeed on Windows port.
* Enable ACTS and CHU reference clock drivers on Windows.
(4.2.7p109) 2011/01/02 Released by Harlan Stenn <stenn@ntp.org>
* Remove nearly all strcpy() and most strcat() from NTP distribution.
  One major pocket remains in ntp_crypto.c.  libopts & libisc also have
  (safe) uses of strcpy() and strcat() remaining.
* Documentation updates from Dave Mills.
(4.2.7p108) 2011/01/01 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1764] Move Palisade modem control logic to configure.ac.
* [Bug 1768] TIOCFLUSH undefined in linux for refclock_acts.
* Autokey multiple identity group improvements from Dave Mills.
* from 4.2.6p3: Update the copyright year.
(4.2.7p107) 2010/12/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1764] Palisade driver doesn't build on Linux.
* [Bug 1766] Oncore clock has offset/high jitter at startup.
* Move ntp_control.h variable IDs to ntp_control.c, remove their use by
  ntpq.  They are implementation details private to ntpd.  [Bug 597] was
  caused by ntpq's reliance on these IDs it need not know about.
* refclock_acts.c updates from Dave Mills.
(4.2.7p106) 2010/12/30 Released by Harlan Stenn <stenn@ntp.org>
* from 4.2.6p3: Update genCommitLog for the bk-5 release.
(4.2.7p105) 2010/12/29 Released by Harlan Stenn <stenn@ntp.org>
(4.2.7p104) 2010/12/28 Released by Harlan Stenn <stenn@ntp.org>
* from 4.2.6p3: Create and use scripts/check--help when generating
  .texi files.
* from 4.2.6p3: Update bk triggers for the bk-5 release.
* Support for multiple Autokey identity groups from Dave Mills.
* Documentation updates from Dave Mills.
* Add ntpq kerninfo, authinfo, and sysinfo commands similar to ntpdc's.
(4.2.7p103) 2010/12/24 Released by Harlan Stenn <stenn@ntp.org>
* Add ntpq pstats command similar to ntpdc's.
* Remove ntpq pstatus command, rv/readvar does the same and more.
* Documentation updates from Dave Mills.
(4.2.7p102) 2010/12/23 Released by Harlan Stenn <stenn@ntp.org>
* Allow ntpq &1 associd use without preceding association-fetching.
* Documentation updates from Dave Mills.
(4.2.7p101) 2010/12/22 Released by Harlan Stenn <stenn@ntp.org>
* from 4.2.6p3-RC12: Upgrade to libopts 34.0.9 from AutoGen 5.11.6pre7.
* from 4.2.6p3-RC12: Relax minimum Automake version to 1.10 with updated
  libopts.m4.
(4.2.7p100) 2010/12/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1743] from 4.2.6p3-RC12: Display timezone offset when showing
  time for sntp in the local timezone (documentation updates).
(4.2.7p99) 2010/12/21 Released by Harlan Stenn <stenn@ntp.org>
* Add unit tests for msnprintf().
(4.2.7p98) 2010/12/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1761] clockstuff/clktest-opts.h omitted from tarball.
* [Bug 1762] from 4.2.6p3-RC12: manycastclient responses interfere.
* Documentation updates from Dave Mills.
(4.2.7p97) 2010/12/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1458] from 4.2.6p3-RC12: Can not compile NTP on FreeBSD 4.7.
* [Bug 1760] from 4.2.6p3-RC12: ntpd Windows interpolation cannot be
  disabled.
* from 4.2.6p3-RC12: Upgrade to libopts 34.0.9 from AutoGen 5.11.6pre5.
* Documentation updates from Dave Mills.
(4.2.7p96) 2010/12/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1758] from 4.2.6p3-RC12: setsockopt IPV6_MULTICAST_IF with wrong
  ifindex.
* Documentation updates from Dave Mills.
(4.2.7p95) 2010/12/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1753] 4.2.7p94 faults on startup in newpeer(), strdup(NULL).
* [Bug 1754] from 4.2.6p3-RC12: --version output should be more verbose.
* [Bug 1757] from 4.2.6p3-RC12: oncore snprintf("%m") doesn't expand %m.
* from 4.2.6p3-RC12: Suppress ntp-keygen OpenSSL version display for
  --help, --version, display both build and runtime OpenSSL versions
  when they differ.
* from 4.2.6p3-RC12: Upgrade to libopts 33.5.8 from AutoGen 5.11.6pre3.
* Documentation updates from Dave Mills.
(4.2.7p94) 2010/12/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1751] from 4.2.6p3-RC12: Support for Atari FreeMiNT OS.
* Documentation updates from Dave Mills.
(4.2.7p93) 2010/12/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1510] from 4.2.6p3-RC12: Add modes 20/21 for driver 8 to support
  RAWDCF @ 75 baud.
* [Bug 1741] from 4.2.6p3-RC12: Enable multicast reception on each
  address (Windows).
* from 4.2.6p3-RC12: Other manycastclient repairs:
  Separate handling of scope ID embedded in many in6_addr from ifindex
  used for IPv6 multicasting ioctls.
  Add INT_PRIVACY endpt bit flag for IPv6 RFC 4941 privacy addresses.
  Enable outbound multicast from only one address per interface in the
  same subnet, and in that case prefer embedded MAC address modified
  EUI-64 IPv6 addresses first, then static, and last RFC 4941 privacy
  addresses.
  Use setsockopt(IP[V6]_MULTICAST_IF) before each send to multicast to
  select the local source address, using the correct socket is not
  enough.
* "server ... ident <groupname>" changes from Dave Mills.
* Documentation updates from Dave Mills.
(4.2.7p92) 2010/12/08 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1743] from 4.2.6p3-RC12: Display timezone offset when showing
  time for sntp in the local timezone.
(4.2.7p91) 2010/12/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1732] ntpd ties up CPU on disconnected USB device.
* [Bug 1742] form 4.2.6p3-RC12: Fix a typo in an error message in the
  "build" script.
(4.2.7p90) 2010/12/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1738] Windows ntpd has wrong net adapter name.
* [Bug 1740] ntpdc -c reslist packet count wrongly treated as signed.
(4.2.7p89) 2010/12/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1736] tos int, bool options broken in 4.2.7p66.
* from 4.2.6p3-RC12: Clean up the SNTP documentation.
(4.2.7p88) 2010/12/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1735] 'clocktime()' aborts ntpd on bogus input
(4.2.7p87) 2010/12/01 Released by Harlan Stenn <stenn@ntp.org>
* from 4.2.6p3-RC12: Clean up m4 quoting in configure.ac, *.m4 files,
  resolving intermittent AC_LANG_PROGRAM possibly undefined errors.
(4.2.7p86) 2010/11/29 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p85) 2010/11/24 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p84) 2010/11/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1618] Unreachable code in jjy_start().
* [Bug 1725] from 4.2.6p3-RC11: ntpd sends multicast from only one
  address.
* from 4.2.6p3-RC11: Upgrade libopts to 33.3.8.
* from 4.2.6p3-RC11: Bump minimum Automake version to 1.11, required for
  AM_COND_IF use in LIBOPTS_CHECK.
* An almost complete rebuild of the initial loopfilter configuration
  process, including the code that determines the interval between
  frequency file updates, from Dave Mills.
* Documentation updates from Dave Mills.
* Add ntp-keygen -l/--lifetime to control certificate expiry.
* JJY driver improvements for Tristate JJY01/02, including changes
  to its clockstats format.
* Add "nonvolatile" ntp.conf directive to control how often the
  driftfile is written.
(4.2.7p83) 2010/11/17 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1727] ntp-keygen PLEN, ILEN undeclared --without-crypto.
* Remove top-level libopts, use sntp/libopts.
* from 4.2.6p3-RC11: Remove log_msg() and debug_msg() from sntp in favor
  of msyslog().
* Documentation updates from Dave Mills.
(4.2.7p82) 2010/11/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1728] from 4.2.6p3-RC11: In ntp_openssl.m4, don't add
  -I/usr/include or -L/usr/lib to CPPFLAGS or LDFLAGS.
(4.2.7p81) 2010/11/14 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1681] from 4.2.6p3-RC10: More sntp logging cleanup.
* [Bug 1683] from 4.2.6p3-RC10: Non-localhost on loopback exempted from
  nic rules.
* [Bug 1719] Cleanup for ntp-keygen and fix -V crash, from Dave Mills.
(4.2.7p80) 2010/11/10 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1574] from 4.2.6p3-RC9: sntp doesn't set tv_usec correctly.
* [Bug 1681] from 4.2.6p3-RC9: sntp logging cleanup.
* [Bug 1683] from 4.2.6p3-RC9: Interface binding does not seem to work
  as intended.
* [Bug 1708] make check fails with googletest 1.4.0.
* [Bug 1709] from 4.2.6p3-RC9: ntpdate ignores replies with equal
  receive and transmit timestamps.
* [Bug 1715] sntp utilitiesTest.IPv6Address failed.
* [Bug 1718] Improve gtest checks in configure.ac.
(4.2.7p79) 2010/11/07 Released by Harlan Stenn <stenn@ntp.org>
* Correct frequency estimate with no drift file, from David Mills.
(4.2.7p78) 2010/11/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1697] filegen implementation should be improved.
* Refactor calendar functions in terms of new common code.
* Documentation updates from Dave Mills.
(4.2.7p77) 2010/11/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1692] packageinfo.sh needs to be "sourced" using ./ .
* [Bug 1695] ntpdate takes longer than necessary.
(4.2.7p76) 2010/11/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1690] Unit tests fails to build on some systems.
* [Bug 1691] Use first NMEA sentence each second.
* Put the sntp tests under sntp/ .
* ... and only build/run them if we have gtest.
* Documentation updates from Dave Mills.
(4.2.7p75) 2010/10/30 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
* Include Linus Karlsson's GSoC 2010 testing code.
(4.2.7p74) 2010/10/29 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1685] from 4.2.6p3-RC8: NMEA driver mode byte confusion.
* from 4.2.6p3-RC8: First cut at using scripts/checkChangeLog.
* Documentation updates from Dave Mills.
(4.2.7p73) 2010/10/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1680] Fix alignment of clock_select() arrays.
* refinements to new startup behavior from David Mills.
* For the bootstrap script, touch .html files last.
* Add 'make check' test case that would have caught [Bug 1678].
(4.2.7p72) 2010/10/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1679] Fix test for -lsocket.
* Clean up missing ;; entries in configure.ac.
(4.2.7p71) 2010/10/25 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1676] from 4.2.6p3-RC7: NMEA: $GPGLL did not work after fix
  for Bug 1571.
* [Bug 1678] "restrict source" treated as "restrict default".
* from 4.2.6p3-RC7: Added scripts/checkChangeLog.
(4.2.7p70) 2010/10/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1571] from 4.2.6p3-RC6: NMEA does not relate data to PPS edge.
* [Bug 1572] from 4.2.p63-RC6: NMEA time adjustment for GPZDG buggy.
* [Bug 1675] from 4.2.6p3-RC6: Prohibit includefile remote config.
* Enable generating ntpd/ntp_keyword.h after keyword-gen.c changes on
  Windows as well as POSIX platforms.
* Fix from Dave Mills for a rare singularity in clock_combine().
(4.2.7p69) 2010/10/23 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1671] Automatic delay calibration is sometimes inaccurate.
(4.2.7p68) 2010/10/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1669] from 4.2.6p3-RC5: NTP fails to compile on IBM AIX 5.3.
* [Bug 1670] Fix peer->bias and broadcastdelay.
* Documentation updates from Dave Mills.
* Documentation EOL cleanup.
(4.2.7p67) 2010/10/21 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1649] from 4.2.6p3-RC5: Require NMEA checksum if $GPRMC or
  previously seen.
(4.2.7p66) 2010/10/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1277] Provide and use O(1) FIFOs, esp. in the config tree code.
* Remove unused 'bias' configuration keyword.
(4.2.7p65) 2010/10/16 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1584] from 4.2.6p3-RC4: wrong SNMP type for precision,
  resolution.
* Remove 'calldelay' and 'sign' remnants from parser, ntp_config.c.
(4.2.7p64) 2010/10/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1584] from 4.2.6p3-RC3: ntpsnmpd OID must be mib-2.197.
* [Bug 1659] from 4.2.6p3-RC4: Need CLOCK_TRUETIME not CLOCK_TRUE.
* [Bug 1663] ntpdsim should not open net sockets.
* [Bug 1665] from 4.2.6p3-RC4: is_anycast() u_int32_t should be u_int32.
* from 4.2.6p3: ntpsnmpd, libntpq warning cleanup.
* Remove 'calldelay' and 'sign' keywords (Dave Mills).
* Documentation updates from Dave Mills.
(4.2.7p63) 2010/10/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1080] from 4.2.6p3-RC3: ntpd on ipv6 routers very chatty.
* Documentation nit cleanup.
* Documentation updates from Dave Mills.
(4.2.7p62) 2010/10/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 750] from 4.2.6p3-RC3: Non-existing device causes coredump with
  RIPE-NCC driver.
* [Bug 1567] from 4.2.6p3-RC3: Support Arbiter 1093C Satellite Clock on
  Windows.
* [Bug 1581] from 4.2.6p3-RC3: printf format string mismatch leftover.
* [Bug 1659] from 4.2.6p3-RC3: Support Truetime Satellite Clocks on
  Windows.
* [Bug 1660] from 4.2.6p3-RC3: On some systems, test is in /usr/bin, not
  /bin.
* [Bug 1661] from 4.2.6p3-RC3: Re-indent refclock_ripencc.c.
* Lose peer_count from ntp_peer.c and ntp_proto.c (Dave Mills).
* Documentation updates from Dave Mills.
(4.2.7p61) 2010/10/06 Released by Harlan Stenn <stenn@ntp.org>
* Documentation and code cleanup from Dave Mills. No more NTP_MAXASSOC.
(4.2.7p60) 2010/10/04 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p59) 2010/10/02 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
* Variable name cleanup from Dave Mills.
* [Bug 1657] darwin needs res_9_init, not res_init.
(4.2.7p58) 2010/09/30 Released by Harlan Stenn <stenn@ntp.org>
* Clock select bugfix from Dave Mills.
* [Bug 1554] peer may stay selected as system peer after becoming
  unreachable.
* [Bug 1644] from 4.2.6p3-RC3: cvo.sh should use lsb_release to identify
  linux distros.
* [Bug 1646] ntpd crashes with relative path to logfile.
(4.2.7p57) 2010/09/27 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p56) 2010/09/25 Released by Harlan Stenn <stenn@ntp.org>
* Clock combining algorithm improvements from Dave Mills.
* Documentation updates from Dave Mills.
* [Bug 1642] ntpdsim can't find simulate block in config file.
* [Bug 1643] from 4.2.6p3-RC3: Range-check the decoding of the RIPE-NCC
  status codes.
(4.2.7p55) 2010/09/22 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
* [Bug 1636] from 4.2.6p3-RC2: segfault after denied remote config.
(4.2.7p54) 2010/09/21 Released by Harlan Stenn <stenn@ntp.org>
* More Initial convergence improvements from Dave Mills.
* Documentation updates from Dave Mills.
* [Bug 1635] from 4.2.6p3-RC2: "filegen ... enable" is not default.
(4.2.7p53) 2010/09/20 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
* More Initial convergence improvements from Dave Mills.
(4.2.7p52) 2010/09/19 Released by Harlan Stenn <stenn@ntp.org>
* Initial convergence improvements from Dave Mills.
(4.2.7p51) 2010/09/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1344] from 4.2.6p3-RC1: ntpd on Windows exits without logging
  cause.
* [Bug 1629] 4.2.7p50 configure.ac changes invalidate config.cache.
* [Bug 1630] 4.2.7p50 cannot bootstrap on Autoconf 2.61.
(4.2.7p50) 2010/09/16 Released by Harlan Stenn <stenn@ntp.org>
* Cleanup NTP_LIB_M.
* [Bug 1628] Clean up -lxnet/-lsocket usage for (open)solaris.
(4.2.7p49) 2010/09/13 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p48) 2010/09/12 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
(4.2.7p47) 2010/09/11 Released by Harlan Stenn <stenn@ntp.org>
* Documentation updates from Dave Mills.
* [Bug 1588] finish configure --disable-autokey implementation.
* [Bug 1616] refclock_acts.c: if (pp->leap == 2) is always false.
* [Bug 1620] [Backward Incompatible] "discard minimum" value should be in
  seconds, not log2 seconds.
(4.2.7p46) 2010/09/10 Released by Harlan Stenn <stenn@ntp.org>
* Use AC_SEARCH_LIBS instead of AC_CHECK_LIB for NTP_LIB_M.
(4.2.7p45) 2010/09/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1578] Consistently use -lm when needed.
(4.2.7p44) 2010/08/27 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1573] from 4.2.6p3-beta1: Miscalculation of offset in sntp.
(4.2.7p43) 2010/08/26 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1602] Refactor some of the sntp/ directory to facililtate testing.
(4.2.7p42) 2010/08/18 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1593] ntpd abort in free() with logconfig syntax error.
* [Bug 1595] from 4.2.6p3-beta1: empty last line in key file causes
  duplicate key to be added
* [Bug 1597] from 4.2.6p3-beta1: packet processing ignores RATE KoD packets,
  Because of a bug in string comparison.
(4.2.7p41) 2010/07/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1581] from 4.2.6p3-beta1: ntp_intres.c size_t printf format
  string mismatch.
* [Bug 1586] ntpd 4.2.7p40 doesn't write to syslog after fork on QNX.
* Avoid race with parallel builds using same source directory in
  scripts/genver by using build directory for temporary files.
* orphanwait documentation updates.
(4.2.7p40) 2010/07/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1395] ease ntpdate elimination with ntpd -w/--wait-sync
* [Bug 1396] allow servers on ntpd command line like ntpdate
(4.2.7p39) 2010/07/09 Released by Harlan Stenn <stenn@ntp.org>
* Fix typo in driver28.html.
* [Bug 1581] from 4.2.6p2: size_t printf format string mismatches, IRIG
  string buffers undersized.  Mostly backported from earlier ntp-dev
  fixes by Juergen Perlinger.
(4.2.7p38) 2010/06/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1570] backported to 4.2.6p2-RC7.
* [Bug 1575] from 4.2.6p2-RC7: use 'snprintf' with LIB_BUFLENGTH in
  inttoa.c, tvtoa.c and utvtoa.c
* [Bug 1576] backported to 4.2.6p2-RC7.
* Typo fix in a comment in ntp_proto.c.
(4.2.7p37) 2010/06/19 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1576] sys/sysctl.h depends on sys/param.h on OpenBSD.
(4.2.7p36) 2010/06/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1560] Initial support for orphanwait, from Dave Mills.
* clock_filter()/reachability fixes from Dave Mills.
(4.2.7p35) 2010/06/12 Released by Harlan Stenn <stenn@ntp.org>
* Rewrite of multiprecision macros in 'ntp_fp.h' from J. Perlinger
  <perlinger@ntp.org>
* [Bug 715] from 4.2.6p2-RC6: libisc Linux IPv6 interface iteration
  drops multicast flags.
(4.2.7p34) 2010/06/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1570] serial clock drivers get outdated input from kernel tty
  line buffer after startup
(4.2.7p33) 2010/06/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1561] from 4.2.6p2-RC5: ntpq, ntpdc "passwd" prompts for MD5
  password w/SHA1.
* [Bug 1565] from 4.2.6p2-RC5: sntp/crypto.c compile fails on MacOS over
  vsnprintf().
* from 4.2.6p2-RC5: Windows port: do not exit in
  ntp_timestamp_from_counter() without first logging the reason.
(4.2.7p32) 2010/05/19 Released by Harlan Stenn <stenn@ntp.org>
* Copyright file cleanup from Dave Mills.
* [Bug 1555] from 4.2.6p2-RC4: sntp illegal C (mixed code and
  declarations).
* [Bug 1558] pool prototype associations have 0.0.0.0 for remote addr.
* configure.ac: add --disable-autokey, #define AUTOKEY to enable future
  support for building without Autokey, but with OpenSSL for its digest
  algorithms (hash functions).  Code must be modified to use #ifdef
  AUTOKEY instead of #ifdef OPENSSL where appropriate to complete this.
* include/ntp_crypto.h: make assumption AUTOKEY implies OPENSSL explicit.
(4.2.7p31) 2010/05/11 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1325] from 4.2.6p2-RC3: unreachable code sntp recv_bcst_data().
* [Bug 1459] from 4.2.6p2-RC3: sntp MD5 authentication does not work
  with ntpd.
* [Bug 1552] from 4.2.6p2-RC3: update and complete broadcast and crypto
  features in sntp.
* [Bug 1553] from 4.2.6p2-RC3: sntp/configure.ac OpenSSL support.
* from 4.2.6p2-RC3: Escape unprintable characters in a refid in ntpq -p
  billboard.
* from 4.2.6p2-RC3: Simplify hash client code by providing OpenSSL
  EVP_*() API when built without OpenSSL.  (already in 4.2.7)
* from 4.2.6p2-RC3: Do not depend on ASCII in sntp.
(4.2.7p30) 2010/05/06 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1526] ntpd DNS pipe read EINTR with no network at startup.
* Update the ChangeLog entries when merging items from -stable.
(4.2.7p29) 2010/05/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1542] ntpd mrulist response may have incorrect last.older.
* [Bug 1543] ntpq mrulist must refresh nonce when retrying.
* [Bug 1544] ntpq mrulist sscanf timestamp format mismatch on 64-bit.
* Windows compiling hints/winnt.html update from G. Sunil Tej.
(4.2.7p28) 2010/05/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1512] from 4.2.6p2-RC3: ntpsnmpd should connect to net-snmpd
  via a unix-domain socket by default.
  Provide a command-line 'socket name' option.
* [Bug 1538] from 4.2.6p2-RC3: update refclock_nmea.c's call to
  getprotobyname().
* [Bug 1541] from 4.2.6p2-RC3: Fix wrong keyword for "maxclock".
(4.2.7p27) 2010/04/27 Released by Harlan Stenn <stenn@ntp.org>
(4.2.7p26) 2010/04/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1465] from 4.2.6p2-RC2: Make sure time from TS2100 is not
  invalid (backport from -dev).
* [Bug 1528] from 4.2.6p2-RC2: Fix EDITLINE_LIBS link order for ntpq
  and ntpdc.
* [Bug 1531] Require nonce with mrulist requests.
* [Bug 1532] Remove ntpd support for ntpdc's monlist in favor of ntpq's
  mrulist.
* [Bug 1534] from 4.2.6p2-RC2: conflicts with VC++ 2010 errno.h.
* [Bug 1535] from 4.2.6p2-RC2: "restrict -4 default" and "restrict
  -6 default" ignored.
(4.2.7p25) 2010/04/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1528] from 4.2.6p2-RC2: Remove --with-arlib from br-flock.
* [Bug 1503] [Bug 1504] [Bug 1518] [Bug 1522] from 4.2.6p2-RC2:
  all of which were fixed in 4.2.7 previously.
(4.2.7p24) 2010/04/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1390] Control PPS on the Oncore M12.
* [Bug 1518] Windows ntpd should lock to one processor more
  conservatively.
* [Bug 1520] '%u' formats for size_t gives warnings with 64-bit builds.
* [Bug 1522] Enable range syntax "trustedkey (301 ... 399)".
* Documentation updates for 4.2.7p22 changes and additions, updating
  ntpdc.html, ntpq.html, accopt.html, confopt.html, manyopt.html,
  miscopt.html, and miscopt.txt.
* accopt.html: non-ntpport doc changes from Dave Mills.
* Modify full MRU list preemption when full to match "discard monitor"
  documentation, by removing exception for count == 1.
(4.2.7p23) 2010/04/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1516] unpeer by IP address fails, DNS name works.
* [Bug 1517] ntpq and ntpdc should verify reverse DNS before use.
  ntpq and ntpdc now use the following format for showing purported
  DNS names from IP address "reverse" DNS lookups when the DNS name
  does not exist or does not include the original IP address among
  the results: "192.168.1.2 (fake.dns.local)".
(4.2.7p22) 2010/04/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1432] Don't set inheritable flag for linux capabilities.
* [Bug 1465] Make sure time from TS2100 is not invalid.
* [Bug 1483] AI_NUMERICSERV undefined in 4.2.7p20.
* [Bug 1497] fudge is broken by getnetnum() change.
* [Bug 1503] Auto-enabling of monitor for "restrict ... limited" wrong.
* [Bug 1504] ntpdate tickles ntpd "discard minimum 1" rate limit if
  "restrict ... limited" is used.
* ntpdate: stop querying source after KoD packet response, log it.
* ntpdate: rate limit each server to 2s between packets.
* From J. N. Perlinger: avoid pointer wraparound warnings in dolfptoa(),
  printf format mismatches with 64-bit size_t.
* Broadcast client (ephemeral) associations should be demobilized only
  if they are not heard from for 10 consecutive polls, regardless of
  surviving the clock selection.  Fix from David Mills.
* Add "ntpq -c ifstats" similar to "ntpdc -c ifstats".
* Add "ntpq -c sysstats" similar to "ntpdc -c sysstats".
* Add "ntpq -c monstats" to show monlist knobs and stats.
* Add "ntpq -c mrulist" similar to "ntpdc -c monlist" but not
  limited to 600 rows, and with filtering and sorting options:
  ntpq -c "mrulist mincount=2 laddr=192.168.1.2 sort=-avgint"
  ntpq -c "mrulist sort=addr"
  ntpq -c "mrulist mincount=2 sort=count"
  ntpq -c "mrulist sort=-lstint"
* Modify internal representation of MRU list to use l_fp fixed-point
  NTP timestamps instead of seconds since startup.  This increases the
  resolution and substantially improves accuracy of sorts involving
  timestamps, at the cost of flushing all MRU entries when the clock is
  stepped, to ensure the timestamps can be compared with the current
  get_systime() results.
* Add ntp.conf "mru" directive to configure MRU parameters, such as
  "mru mindepth 600 maxage 64 maxdepth 5000 maxmem 1024" or
  "mru initalloc 0 initmem 16 incalloc 99 incmem 4".  Several pairs are
  equivalent with one in units of MRU entries and its twin in units of
  kilobytes of memory, so the last one used in ntp.conf controls:
  maxdepth/maxmem, initalloc/initmem, incalloc/incmem.  With the above
  values, ntpd will preallocate 16kB worth of MRU entries, allocating
  4kB worth each time more are needed, with a hard limit of 1MB of MRU
  entries.  Until there are more than 600 entries none would be reused.
  Then only entries for addresses last seen 64 seconds or longer ago are
  reused.
* Limit "ntpdc -c monlist" response in ntpd to 600 entries, the previous
  overall limit on the MRU list depth which was driven by the monlist
  implementation limit of one request with a single multipacket
  response.
* New "pool" directive implementation modeled on manycastclient.
* Do not abort on non-ASCII characters in ntp.conf, ignore them.
* ntpq: increase response reassembly limit from 24 to 32 packets, add
  discussion in comment regarding results with even larger MAXFRAGS.
* ntpq: handle "passwd MYPASSWORD" (without prompting) as with ntpdc.
* ntpdc: do not examine argument to "passwd" if not supplied.
* configure: remove check for pointer type used with qsort(), we
  require ANSI C which mandates void *.
* Reset sys_kodsent to 0 in proto_clr_stats().
* Add sptoa()/sockporttoa() similar to stoa()/socktoa() adding :port.
* Use memcpy() instead of memmove() when buffers can not overlap.
* Remove sockaddr_storage from our sockaddr_u union of sockaddr,
  sockaddr_in, and sockaddr_in6, shaving about 100 bytes from its size
  and substantially decreasing MRU entry memory consumption.
* Extend ntpq readvar (alias rv) to allow fetching up to three named
  variables in one operation:  ntpq -c "rv 0 version offset frequency".
* ntpq: use srchost variable to show .POOL. prototype associations'
  hostname instead of address 0.0.0.0.
* "restrict source ..." configures override restrictions for time
  sources, allows tight default restrictions to be used with the pool
  directive (where server addresses are not known in advance).
* Ignore "preempt" modifier on manycastclient and pool prototype
  associations.  The resulting associations are preemptible, but the
  prototype must not be.
* Maintain and use linked list of associations (struct peer) in ntpd,
  avoiding walking 128 hash table entries to iterate over peers.
* Remove more workarounds unneeded since we require ISO C90 AKA ANSI C:
  - remove fallback implementations for memmove(), memset, strstr().
  - do not test for atexit() or memcpy().
* Collapse a bunch of code duplication in ntpd/ntp_restrict.c added with
  support for IPv6.
* Correct some corner case failures in automatically enabling the MRU
  list if any "restrict ... limited" is in effect, and in disabling MRU
  maintenance. (ntp_monitor.c, ntp_restrict.c)
* Reverse the internal sort order of the address restriction lists, but
  preserve the same behavior.  This allows removal of special-case code
  related to the default restrictions and more straightforward lookups
  of restrictions for a given address (now, stop on first match).
* Move ntp_restrict.c MRU doubly-linked list maintenance code into
  ntp_lists.h macros, allowing more duplicated source excision.
* Repair ntpdate.c to no longer test HAVE_TIMER_SETTIME.
* Do not reference peer_node/unpeer_node after freeing when built with
  --disable-saveconfig and using DNS.
(4.2.7p21) 2010/03/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 2399] Reset sys_kodsent in proto_clr_stats().
* [Bug 1514] from 4.2.6p1-RC6: Typo in ntp_proto.c: fabs(foo < .4)
  should be fabs(foo) < .4.
* [Bug 1464] from 4.2.6p1-RC6: synchronization source wrong for
  refclocks ARCRON_MSF (27) and SHM (28).
* From 4.2.6p1-RC6: Correct Windows port's refclock_open() to
  return 0 on failure not -1.
* From 4.2.6p1-RC6: Correct CHU, dumbclock, and WWVB drivers to
  check for 0 returned from refclock_open() on failure.
* From 4.2.6p1-RC6: Correct "SIMUL=4 ./flock-build -1" to
  prioritize -1/--one.
* [Bug 1306] constant conditionals in audio_gain().
(4.2.7p20) 2010/02/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1483] hostname in ntp.conf "restrict" parameter rejected.
* Use all addresses for each restrict by hostname.
* Use async DNS to resolve trap directive hostnames.
(4.2.7p19) 2010/02/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1338] Update the association type codes in ntpq.html.
* [Bug 1478] from 4.2.6p1-RC5: linking fails: EVP_MD_pkey_type.
* [Bug 1479] from 4.2.6p1-RC5: not finding readline headers.
* [Bug 1484] from 4.2.6p1-RC5: ushort is not defined in QNX6.
(4.2.7p18) 2010/02/07 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1480] from 4.2.6p1-RC5: snprintf() cleanup caused
  unterminated refclock IDs.
* Stop using getaddrinfo() to convert numeric address strings to on-wire
  addresses in favor of is_ip_address() alone.
(4.2.7p17) 2010/02/05 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1477] from 4.2.6p1-RC5: First non-gmake make in clone
  w/VPATH can't make COPYRIGHT.
* Attempts to cure CID 108 CID 118 CID 119 TAINTED_SCALAR warnings.
* Broaden ylwrap workaround VPATH_HACK to all non-GNU make.
(4.2.7p16) 2010/02/04 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1474] from 4.2.6p1-RC4: ntp_keygen LCRYPTO after libntp.a.
* Include 4.2.6p1-RC4: Remove arlib.
(4.2.7p15) 2010/02/03 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1455] from 4.2.6p1: ntpd does not try /etc/ntp.audio.
* Include 4.2.6p1: Convert many sprintf() calls to snprintf(), also
  strcpy(), strcat().
* Include 4.2.6p1: Fix widely cut-n-pasted bug in refclock shutdown
  after failed start.
* Include 4.2.6p1: Remove some dead code checking for emalloc()
  returning NULL.
(4.2.7p14) 2010/02/02 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1338] ntpq displays incorrect association type codes.
* [Bug 1469] u_int32, int32 changes broke HP-UX 10.20 build.
* [Bug 1470] from 4.2.6p1: "make distdir" compiles keyword-gen.
* [Bug 1471] CID 120 CID 121 CID 122 is_ip_address() uninit family.
* [Bug 1472] CID 116 CID 117 minor warnings in new DNS code.
* [Bug 1473] from 4.2.6p1: "make distcheck" version.m4 error.
(4.2.7p13) 2010/01/31 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1467] from 4.2.6p1: Fix bogus rebuild of sntp/sntp.html.
(4.2.7p12) 2010/01/30 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1468] 'make install' broken for root on default NFS mount.
(4.2.7p11) 2010/01/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 47] Debugging and logging do not work after a fork.
* [Bug 1010] getaddrinfo() could block and thus should not be called by
  the main thread/process.
* New async DNS resolver in ntpd allows nonblocking queries anytime,
  instead of only once at startup.
(4.2.7p10) 2010/01/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1140] from 4.2.6p1-RC5: Clean up debug.html, decode.html,
  and ntpq.html.
* Include 4.2.6p1-RC3: Use TZ=UTC instead of TZ= when calling date in
  scripts/mkver.in .
* [Bug 1448] from 4.2.6p1-RC3: Some macros not correctly conditionally
  or absolutely defined on Windows.
* [Bug 1449] from 4.2.6p1-RC3: ntpsim.h in ntp_config.c should be used
  conditionally.
* [Bug 1450] from 4.2.6p1-RC3: Option to exclude warnings not
  unconditionally defined on Windows.
(4.2.7p9) 2010/01/13 Released by Harlan Stenn <stenn@ntp.org>
(4.2.7p8) 2010/01/12 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 702] ntpd service logic should use libopts to examine cmdline.
* [Bug 1451] from 4.2.6p1-RC3: sntp leaks KoD entry updating.
* [Bug 1453] from 4.2.6p1-RC3: Use $CC in config.cache filename.
(4.2.7p7) 2009/12/30 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 620] ntpdc getresponse() esize != *rsize s/b size != *rsize.
* [Bug 1446] 4.2.7p6 requires autogen, missing ntpd.1, *.texi, *.menu.
(4.2.7p6) 2009/12/28 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1443] Remove unnecessary dependencies on ntp_io.h
* [Bug 1442] Move Windows functions into libntp files
* [Bug 1127] from 4.2.6p1-RC3: Check the return of X590_verify().
* [Bug 1439] from 4.2.6p1-RC3: .texi gen after binary is linked.
* [Bug 1440] from 4.2.6p1-RC3: Update configure.ac to support kfreebsd.
* [Bug 1445] from 4.2.6p1-RC3: IRIX does not have -lcap or support
  linux capabilities.
(4.2.7p5) 2009/12/25 Released by Harlan Stenn <stenn@ntp.org>
* Include 4.2.6p1-RC2
(4.2.7p4) 2009/12/24 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1429] ntpd -4 option does not reliably force IPv4 resolution.
* [Bug 1431] System headers must come before ntp headers in ntp_intres.c .
(4.2.7p3) 2009/12/22 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1426] scripts/VersionName needs . on the search path.
* [Bug 1427] quote missing in ./build - shows up on NetBSD.
* [Bug 1428] Use AC_HEADER_RESOLV to fix breaks from resolv.h
(4.2.7p2) 2009/12/20 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1419] ntpdate, ntpdc, sntp, ntpd ignore configure --bindir.
* [Bug 1421] add util/tg2, a clone of tg that works on Linux, NetBSD, and
  FreeBSD
(4.2.7p1) 2009/12/15 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1348] ntpd Windows port should wait for sendto() completion.
* [Bug 1413] test OpenSSL headers regarding -Wno-strict-prototypes.
* [Bug 1418] building ntpd/ntpdc/ntpq statically with ssl fails.
(4.2.7p0) 2009/12/13 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1412] m4/os_cflags.m4 caches results that depend on $CC.
* [Bug 1414] Enable "make distcheck" success with BSD make.
(4.2.7) 2009/12/09 Released by Harlan Stenn <stenn@ntp.org>
* [Bug 1407] configure.ac: recent GNU Make -v does not include "version".



