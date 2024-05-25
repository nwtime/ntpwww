---
title: "4.2.8-series Changelog"
description: "The changelogs for NTP versions 4.2.8 through 4.2.8p18."
type: archives
---

<details open>
<summary><b>Release versions:</b></summary>

* [4.2.8p18](#428p18)
* [4.2.8p17](#428p17)
* [4.2.8p16](#428p16)
* [4.2.8p15](#428p15)
* [4.2.8p14](#428p14)
* [4.2.8p13](#428p13)
* [4.2.8p12](#428p12)
* [4.2.8p11](#428p11)
* [4.2.8p10](#428p10)
* [4.2.8p9-win](#428p9-win)
* [4.2.8p9](#428p9)
* [4.2.8p8](#428p8)
* [4.2.8p7](#428p7)
* [4.2.8p6](#428p6)
* [4.2.8p5](#428p5)
* [4.2.8p4](#428p4)
* [4.2.8p3](#428p3)
* [4.2.8p3-RC3](#428p3-rc3)
* [4.2.8p2](#428p2)
* [4.2.8p1](#428p1)
* [4.2.8](#428)

</details>

* * *

#### 4.2.8p18

**Release Date:** 2024 May 25

* [Bug 3918 Tweak openssl header/library handling](https://bugs.ntp.org/3918). stenn@
* [Bug 3914 Spurious "Unexpected origin timestamp" logged after time stepped](https://bugs.ntp.org/3914). hart@
* [Bug 3913 Avoid duplicate IPv6 link-local manycast associations](https://bugs.ntp.org/3913). hart@
* [Bug 3912 Avoid rare math errors in `ntptrace`](https://bugs.ntp.org/3912). Brian Utterback
* [Bug 3910 Memory leak using openssl-3](https://bugs.ntp.org/3910). hart@
* [Bug 3909 Do not select multicast local address for unicast peer](https://bugs.ntp.org/3909). hart@
* [Bug 3903 `lib/isc/win32/strerror.c NTstrerror()` is not thread-safe](https://bugs.ntp.org/3903). hart@
* [Bug 3901 `LIB_GETBUF` isn't thread-safe](https://bugs.ntp.org/3901). hart@
* [Bug 3900 `fast_xmit()` selects wrong local addr responding to mcast on Windows](https://bugs.ntp.org/3900). hart@
* [Bug 3888 `ntpd` with multiple same-subnet IPs using manycastclient creates duplicate associations](https://bugs.ntp.org/3888). hart@
* [Bug 3872 Ignore restrict mask for hostname](https://bugs.ntp.org/3872). hart@
* [Bug 3871 4.2.8p17 build without hopf6021 refclock enabled fails](https://bugs.ntp.org/3871).
  * Reported by Hans Mayer. 
  * Moved `NONEMPTY_TRANSLATION_UNIT` declaration from `ntp_types.h` to `config.h`. hart@
* [Bug 3870 Server drops client packets with `ppoll` < 4](https://bugs.ntp.org/3870). stenn@
* [Bug 3869 Remove long-gone `calldelay` & `crypto sign` from docs](https://bugs.ntp.org/3869).
  * Reported by PoolMUC. hart@
* [Bug 3868 Cannot restrict a pool peer](https://bugs.ntp.org/3868). hart@ 
  * Thanks to Edward McGuire for tracking down the deficiency.
* [Bug 3864 `ntpd` IPv6 refid different for big-endian and little-endian](https://bugs.ntp.org/3864). hart@
* [Bug 3859 Use `NotifyIpInterfaceChange` on Windows `ntpd`](https://bugs.ntp.org/3859). hart@
* [Bug 3856 Enable Edit & Continue debugging with Visual Studio](https://bugs.ntp.org/3856). hart@
* [Bug 3855 `ntpq` lacks an equivalent to `ntpdc`'s `delrestrict`](https://bugs.ntp.org/3855). hart@
* [Bug 3854 `ntpd` 4.2.8p17 corrupts rawstats file with space in refid](https://bugs.ntp.org/3854). hart@
* [Bug 3853 Clean up warnings with modern compilers](https://bugs.ntp.org/3853). hart@
* [Bug 3852 `check-libntp.mf` and friends are not triggering rebuilds as intended](https://bugs.ntp.org/3852). hart@
* [Bug 3851 Drop pool server when no local address can reach it](https://bugs.ntp.org/3851). hart@
* [Bug 3850 `ntpq -c apeers` breaks column formatting s2 w/refclock refid](https://bugs.ntp.org/3850). hart@
* [Bug 3849 `ntpd --wait-sync` times out](https://bugs.ntp.org/3849). hart@
* [Bug 3847 SSL detection in configure should run-test if runpath is needed](https://bugs.ntp.org/3847). hart@
* [Bug 3846 Use `-Wno-format-truncation` by default](https://bugs.ntp.org/3846). hart@
* [Bug 3845 accelerate pool clock_sync when IPv6 has only link-local access](https://bugs.ntp.org/3845). hart@
* [Bug 3842 Windows `ntpd` PPSAPI DLL load failure crashes](https://bugs.ntp.org/3842). hart@
* [Bug 3841 4.2.8p17 build break w/ `gcc` 12 `-Wformat-security` without `-Wformat`](https://bugs.ntp.org/3841). Need to remove `--Wformat-security` when removing `-Wformat` to silence numerous `libopts` warnings. hart@
* [Bug 3837 NULL pointer deref crash when `ntpd` deletes last interface](https://bugs.ntp.org/3837).
  * Reported by renmingshuai. 
  * Correct `UNLINK_EXPR_SLIST()` when the list is empty. hart@
* [Bug 3835 `NTP_HARD_*FLAGS` not used by l`ibevent` tearoff](https://bugs.ntp.org/3835). hart@
* [Bug 3831 `pollskewlist` zeroed on runtime configuration](https://bugs.ntp.org/3831). hart@
* [Bug 3830 `configure` libevent check intersperses output with answer](https://bugs.ntp.org/3830). stenn@
* [Bug 3828 BK should ignore a git repo in the same directory](https://bugs.ntp.org/3828). burnicki@
* [Bug 3827 Fix build in case `CLOCK_HOPF6021` or `CLOCK_WHARTON_400A` is disabled](https://bugs.ntp.org/3827). burnicki@
* [Bug 3825 Don't touch HTML files unless building inside a BK repo](https://bugs.ntp.org/3825). Fix the script checkHtmlFileDates. burnicki@
* [Bug 3756 Improve OpenSSL library/header detection](https://bugs.ntp.org/3756).
* [Bug 3753 `ntpd` fails to start with FIPS-enabled OpenSSL 3](https://bugs.ntp.org/3753). hart@
* [Bug 2734 TEST3 prevents initial interleave sync](https://bugs.ntp.org/2734).
  * Fix from PoolMUC
* Remove extraneous `*/` from `libparse/ieee754io.c`.
* Fix `.datecheck` target line in `Makefile.am`. stenn@
* Log failures to allocate receive buffers. hart@
* Update the copyright year. stenn@
* Update `ntp.conf` documentation to add `delrestrict` and correct information about KoD rate limiting. hart@
* `html/clockopt.html` cleanup. stenn@
* `util/lsf-times` - added. stenn@
* Add DSA, DSA-SHA, and SHA to `tests/libntp/digests.c`. hart@
* Provide `ntpd` thread names to debugger on Windows. hart@
* Remove dead code `libntp/numtohost.c` and its unit tests. hart@
* Remove class A, B, C IPv4 distinctions in `netof()`. hart@
* Use `@configure_input@` in various `*.in` files to include a comment that the file is generated from another pointing to the `*.in`. hart@
* Correct underquoting, indents in `ntp_facilitynames.m4`. hart@
* Clean up a few warnings seen building with older `gcc`. hart@
* Fix build on older FreeBSD lacking `sys/procctl.h`. hart@
* Disable [Bug 3627](https://bugs.ntp.org/3627) workaround on newer FreeBSD which has the kernel fix that makes it unnecessary, re-enabling ASLR stack gap. hart@
* Use `NONEMPTY_COMPILATION_UNIT` in more conditionally-compiled files.
* Remove useless pointer to Windows Help from system error messages.
* Avoid newlines within Windows error messages. hart@
* Ensure unique association IDs if wrapped. hart@
* Simplify `calc_addr_distance()`. hart@
* Clamp min/maxpoll in edge cases in `newpeer()`. hart@
* Quiet local addr change logging when unpeering. hart@
* Correct missing arg for `%s printf` specifier in `send_blocking_resp_internal()`. hart@
* Suppress OpenSSL 3 deprecation warning clutter. hart@
* Correct OpenSSL usage in Autokey code to avoid warnings about discarding const qualifiers with OpenSSL 3. hart@
* Display KoD refid as text in recently added message. hart@
* Avoid running `checkHtmlFileDates` script repeatedly when no `html/*.html` files have changed. hart@
* Abort `configure` if `--enable-crypto-rand` given & unavailable. hart@
* Add `configure --enable-verbose-ssl` to trace SSL detection. hart@
* Add build test coverage for `--disable-saveconfig` to `flock-build` script. hart@
* Remove deprecated `configure --with-arlib` option. hart@
* Remove `configure` support for ISC UNIX ca. 1998. hart@
* Move `NTP_OPENSSL` and `NTP_CRYPTO_RAND` invocations from `configure.ac` files to `NTP_LIBNTP`. hart@
* Move `ENABLE_CMAC` to `ntp_openssl.m4`, enabling `sntp/tests` CMAC unit tests. hart@
* Remove dead code: `HAVE_U_INT32_ONLY_WITH_DNS`. hart@
* Eliminate `[v]snprintf` redefinition warnings on macOS. hart@
* Fix clang 14 cast increases alignment warning on Linux. hart@
* Use `NTP_HARD_CPPFLAGS` in `libopts` tearoff. hart@
* Wire in `--enable-build-framework-help`.

#### 4.2.8p17

**Release Date:** 2023 Jun 06

* [Bug 3824: Spurious "ntpd: daemon failed to notify parent!" logged at `event_sync`](https://bugs.ntp.org/3824).  Reported by Edward McGuire.  hart@
* [Bug 3822: `ntpd` significantly delays first poll of servers specified by name](https://bugs.ntp.org/3822). hart@
  * Miroslav Lichvar identified regression in 4.2.8p16.
* [Bug 3821 4.2.8p16 misreads hex authentication keys, won't interop with 4.2.8p15 or earlier](https://bugs.ntp.org/3821).  Reported by Matt Nordhoff, thanks to Miroslav Lichvar and Matt for rapid testing and identifying the problem. hart@
* Add `tests/libntp/digests.c` to catch regressions reading keys file or with symmetric authentication digest output.

***

#### 4.2.8p16

**Release Date:** 2023 May 30

* [Sec 3808: Assertion failure in `ntpq` on malformed RT-11 date](/support/securitynotice/ntpbug3808/). perlinger@
* [Sec 3807: `praecis_parse()` in `ntpd/refclock_palisade.c` can write out-of-bounds ](/support/securitynotice/ntpbug3807/). Reported by stenn@
* [Sec 3806: `libntp/mstolfp.c` needs bounds checking](/support/securitynotice/ntpbug3806/). perlinger@
  * solved numerically instead of using string manipulation
* [Sec 3767: An out-of-bounds KoD RATE `ppoll` value triggers an assertion abort in debug-enabled `ntpd`](/support/securitynotice/ntpbug3767/). stenn@
* [Bug 3817: Bounds-check `tos floor` configuration](https://bugs.ntp.org/3817). hart@
* [Bug 3814: First poll delay of new or cleared associations miscalculated](https://bugs.ntp.org/3814). hart@
* [Bug 3802: `ntp-keygen -I` default identity modulus bits too small for OpenSSL 3](https://bugs.ntp.org/3802). Reported by rmsh1216@163.com hart@
* [Bug 3801: `gpsdjson` refclock `gps_open()` device name mishandled](https://bugs.ntp.org/3801). hart@
* [Bug 3800: libopts-42.1.17 does not compile with Microsoft C](https://bugs.ntp.org/3800). hart@
* [Bug 3799: Enable `libopts` noreturn compiler advice for MSC](https://bugs.ntp.org/3799). hart@
* [Bug 3797: Windows `getaddrinfo w/AI_ADDRCONFIG` fails for localhost when disconnected, breaking `ntpq` and `ntpdc`](https://bugs.ntp.org/3797). hart@
* [Bug 3795: `pollskewlist` documentation uses `|` when it shouldn't](https://bugs.ntp.org/3795).
  * [`ntp.conf` manual page](/documentation/4.2.8-series/ntp.conf/) and [miscopt.html](/documentation/4.2.8-series/miscopt/) corrections. hart@
* [Bug 3793: Wrong variable type passed to `record_raw_stats()`](https://bugs.ntp.org/3793). hart@
  * Report and patch by [Yuezhen LUAN](mailto:wei6410@sina.com).
* [Bug 3786: Timer starvation on high-load Windows `ntpd`](https://bugs.ntp.org/3786). hart@
* [Bug 3784: high-load `ntpd` on Windows deaf after enough ICMP TTL exceeded](https://bugs.ntp.org/3784). hart@
* [Bug 3781: log "Unable to listen for broadcasts" for IPv4](https://bugs.ntp.org/3781). hart@
* [Bug 3774: mode 6 packets corrupted in `rawstats` file](https://bugs.ntp.org/3774). hart@
  * Reported by Edward McGuire, fix identified by [Yuezhen LUAN](mailto:wei6410@sina.com).
* [Bug 3758: Provide a `device` config statement for refclocks](https://bugs.ntp.org/3758). perlinger@
* [Bug 3757: Improve handling of Linux-PPS in NTPD](https://bugs.ntp.org/3757). perlinger@
* [Bug 3741: 4.2.8p15 can't build with glibc 2.34](https://bugs.ntp.org/3741). perlinger@
* [Bug 3725: Make copyright of `clk_wharton.c` compatible with Debian](https://bugs.ntp.org/3725). [Philippe De Muyter](mailto:phdm@macqel.be)
* [Bug 3724: `ntp-keygen` with openSSL 1.1.1 fails on Windows](https://bugs.ntp.org/3724). perlinger@
  * openssl applink needed again for openSSL-1.1.1
* [Bug 3719: `configure.ac` checks for `closefrom()` and `getdtablesize()` missing](https://bugs.ntp.org/3719). Reported by Brian Utterback, broken in 2010 by hart@.
* [Bug 3699: Problems handling drift file and restoring previous drifts](https://bugs.ntp.org/3699). perlinger@
  * command line options override config statements where applicable
  * make initial frequency settings idempotent and reversible
  * make sure kernel PLL gets a recovered drift componsation
* [Bug 3695: Fix memory leak with `ntpq` on Windows Server 2019](https://bugs.ntp.org/3695). perlinger@
* [Bug 3694: NMEA refclock seems to unnecessarily require location in messages](https://bugs.ntp.org/3694).
  * misleading title; essentially a request to ignore the receiver status. Added a mode bit for this. perlinger@
* [Bug 3693: Improvement of error handling key lengths](https://bugs.ntp.org/3693). perlinger@
  * original patch by Richard Schmidt, with mods & unit test fixes
* [Bug 3692: `/dev/gpsN` requirement prevents KPPS](https://bugs.ntp.org/3692). perlinger@
  * implement/wrap `realpath()` to resolve symlinks in device names
* [Bug 3691: Buffer Overflow reading GPSD output](https://bugs.ntp.org/3691).
  * original patch by [matt](mailto:ntpbr@mattcorallo.com)
  * increased max PDU size to 4k to avoid truncation
* [Bug 3690: newline in ntp clock variable (`parse`)](https://bugs.ntp.org/3690). perlinger@
  * patch by Frank Kardel
* [Bug 3689: Extension for MD5, SHA-1 and other keys](https://bugs.ntp.org/3689). perlinger@
  * `ntpq` and `ntpdc` now use the same password processing as `ntpd` does in the key file, so having a binary secret >= 11 bytes is possible for all keys. (This is a different approach to the problem than suggested)
* [Bug 3688: GCC 10 build errors in testsuite](https://bugs.ntp.org/3688). perlinger@
* [Bug 3687: `ntp_crypto_rand` RNG status not known](https://bugs.ntp.org/3687). perlinger@
  * patch by Gerry Garvey
* [Bug 3682: Fixes for warnings when compiled without OpenSSL](https://bugs.ntp.org/3682). perlinger@
  * original patch by Gerry Garvey
* [Bug 3677: additional peer events not decoded in associations listing](https://bugs.ntp.org/3677). perlinger@
  * original patch by Gerry Garvey
* [Bug 3676: compiler warnings (`CMAC`, `interrupt_buf`, `typo`, `fallthrough`)](https://bugs.ntp.org/3676).
  * applied patches by Gerry Garvey
* [Bug 3675: `ntpq ccmds[]` stores pointer to non-persistent storage](https://bugs.ntp.org/3675).
* [Bug 3674: `ntpq` command `execute only` using `~` prefix](https://bugs.ntp.org/3674). perlinger@
  * idea+patch by Gerry Garvey
* [Bug 3672: fix biased selection in median cut](https://bugs.ntp.org/3672). perlinger@
* [Bug 3666: avoid unlimited receive buffer allocation](https://bugs.ntp.org/3666). perlinger@
  * follow-up: fix inverted sense in check, reset shortfall counter
* [Bug 3660: Revert 4.2.8p15 change to manycast](https://bugs.ntp.org/3660). hart@
* [Bug 3640: document `discard monitor` and fix the code](https://bugs.ntp.org/3640). hart@
  * fixed bug identified by Edward McGuire perlinger@
* [Bug 3626: (SNTP) UTC offset calculation needs `dst` flag](https://bugs.ntp.org/3626). perlinger@
  * applied patch by Gerry Garvey
  * backport from -dev, plus some more work on warnings for unchecked results
* [Bug 3428: `ntpd` spinning consuming CPU on Linux router with full table](https://bugs.ntp.org/3428). Reported by Israel G. Lugo. hart@
* [Bug 3103: `libopts zsave_warn` format string too few arguments](https://bugs.ntp.org/3103). [Bruce Korb](mailto:bkorb@gnu.org)
* [Bug 2990: multicastclient incorrectly causes bind to broadcast address](https://bugs.ntp.org/2990). Integrated patch from Brian Utterback. hart@
* [Bug 2525: Turn on `automake subdir-objects` across the project](https://bugs.ntp.org/2525). hart@
* [Bug 2410: `syslog` an error message on panic exceeded](https://bugs.ntp.org/2410). [Brian Utterback](mailto:brian.utterback@oracle.com)
* Use correct rounding in `mstolfp()`. perlinger/hart
* `M_ADDF` should use `u_int32`. hart@
* Only define `tv_fmt_libbuf()` if we will use it. stenn@
* Use `recv_buffer` instead of the longer `recv_space.X_recv_buffer`. hart/stenn
* Make sure the value returned by `refid_str()` prints cleanly. stenn@
* If DEBUG is enabled, the startup banner now says that debug assertions are in force and that `ntpd` will abort if any are violated. stenn@
* `syslog` valid incoming KoDs. stenn@
* Rename a poorly-named variable. stenn@
* Disable "embedded NUL in string" messages in `libopts`, when we can. stenn@
* Use https in the `AC_INIT URLs` in `configure.ac`. stenn@
* Implement `NTP_FUNC_REALPATH`. stenn@
* Lose a `gmake` construct in `ntpd/Makefile.am`. stenn@
* upgrade to: autogen-5.18.16
* upgrade to: libopts-42.1.17
* upgrade to: autoconf-2.71
* upgrade to: automake-1.16.15
* Upgrade to libevent-2.1.12-stable. stenn@
* Support OpenSSL-3.0

***

#### 4.2.8p15

**Release Date:** 2020 Jun 23

* [Sec 3661: memory leak with AES128CMAC keys](/support/securitynotice/ntpbug3661/)
* [Bug 3670: Regression from bad merge of 3592 and 3596](https://bugs.ntp.org/show_bug.cgi?id=3670)
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
* [Bug 3432: refclocks that `write()` should check the result](https://bugs.ntp.org/3432). perlinger@

* * *

#### 4.2.8p14

**Release Date:** 2020 Mar 3

* [Sec 3610: process_control() should bail earlier on short packets](/support/securitynotice/ntpbug3610/)
  - Reported by Philippe Antoine
* [Sec 3596: Highly predictable timestamp attack](/support/securitynotice/ntpbug3596/)
  - Reported by Miroslav Lichvar
* [Sec 3592: DoS attack on client ntpd](/support/securitynotice/ntpbug3592/)
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

* [Sec 3565: Crafted null dereference attack in authenticated mode 6 packet](/support/securitynotice/ntpbug3565/)
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

* [Sec 3505: CVE-2018-12327 - Arbitrary Code Execution Vulnerability](/support/securitynotice/ntpbug3505/)
  - fixed stack buffer overflow in the `openhost()` command-line call of `ntpq/ntpdc`
* [Sec 3012: noepeer tweaks](/support/securitynotice/ntpbug3012p12/)
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

* [Sec 3454: Unauthenticated packet can reset authenticated interleave associations](/support/securitynotice/ntpbug3454/)
* [Sec 3453: Interleaved symmetric mode cannot recover from bad state](/support/securitynotice/ntpbug3453/)
* [Sec 3415: Permit blocking authenticated symmetric/passive associations](/support/securitynotice/ntpbug3415/)
  - Implement ippeerlimit
* [Sec 3414: ntpq: decodearr() can write beyond its 'buf' limits](/support/securitynotice/ntpbug3414/)
  - initial patch by Harlan Stenn, extended by JPerlinger
* [Sec 3412: ctl_getitem(): Don't compare names past NUL](/support/securitynotice/ntpbug3412/)
* [Sec 3012: Sybil vulnerability: noepeer support](/support/securitynotice/ntpbug3012/)
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

**Release Date:** 2017 Mar 21

* [Sec 3389: NTP-01-016: Denial of Service via Malformed Config](/support/securitynotice/ntpbug3389/)
* [Sec 3388: NTP-01-014: Buffer Overflow in DPTS Clock](/support/securitynotice/ntpbug3388/)
* [Sec 3387: NTP-01-012: Authenticated DoS via Malicious Config Option](/support/securitynotice/ntpbug3387/)
* [Sec 3386: NTP-01-011: ntpq_stripquotes() returns incorrect Value](/support/securitynotice/ntpbug3386/)
* [Sec 3385: NTP-01-010: ereallocarray()/eallocarray() underused](/support/securitynotice/ntpbug3385/)
* [Sec 3384: NTP-01-009: Privileged execution of User Library code](/support/securitynotice/ntpbug3384/)
* [Sec 3383: NTP-01-008: Stack Buffer Overflow from Command Line](/support/securitynotice/ntpbug3383/)
* [Sec 3382: NTP-01-007: Data Structure terminated insufficiently](/support/securitynotice/ntpbug3382/)
* [Sec 3380: NTP-01-005: Off-by-one in Oncore GPS Receiver](/support/securitynotice/ntpbug3380/)
* [Sec 3379: NTP-01-004: Potential Overflows in ctl_put() functions](/support/securitynotice/ntpbug3379/)
* [Sec 3378: NTP-01-003: Improper use of snprintf() in mx4200_send()](/support/securitynotice/ntpbug3378/)
* [Sec 3377: NTP-01-002: Buffer Overflow in ntpq when fetching reslist](/support/securitynotice/ntpbug3377/)
* [Sec 3376: Support build "hardening" flags](/support/securitynotice/ntpbug3376/)
* [Sec 3361: 0rigin (zero origin) DoS](/support/securitynotice/ntpbug3361/)
* [Bug 3393: clang scan-build findings](https://bugs.ntp.org/show_bug.cgi?id=3393)
* [Bug 3363: Support for openssl-1.1.0 without compatibility modes](https://bugs.ntp.org/show_bug.cgi?id=3363)
  - rework of patch set from ntp.org@eroen.eu.
* [Bug 3356: Bugfix 3072 breaks multicastclient](https://bugs.ntp.org/show_bug.cgi?id=3356)
* [Bug 3216: libntp audio ioctl() args incorrectly cast to int on 4.4BSD-Lite derived platforms](https://bugs.ntp.org/show_bug.cgi?id=3216)
  - original patch by Majdi S. Abbas
* [Bug 3215: `make distcheck` fails with new BK repo format](https://bugs.ntp.org/show_bug.cgi?id=3215)
* [Bug 3173: forking async worker: interrupted pipe I/O](https://bugs.ntp.org/show_bug.cgi?id=3173)
  - initial patch by Christos Zoulas
* [Bug 3139: (...) time_pps_create: Exec format error](https://bugs.ntp.org/show_bug.cgi?id=3139)
  - move loader API from `inline` to proper source
  - augment pathless `dlls` with absolute path to NTPD
  - use `msyslog()` instead of `printf()` for reporting trouble
* [Bug 3107: Incorrect Logic for Peer Event Limiting](https://bugs.ntp.org/show_bug.cgi?id=3107)
  - applied patch by Matthew Van Gundy
* [Bug 3065: Quiet warnings on NetBSD](https://bugs.ntp.org/show_bug.cgi?id=3065)
  - applied some of the patches provided by Havard. Not all of them still match the current code base, and I did not touch `libopt`.
* [Bug 3062: Change the process name of forked DNS worker](https://bugs.ntp.org/show_bug.cgi?id=3062)
  - applied patch by Reinhard Max. See bugzilla for limitations.
* [Bug 2923: Trap Configuration Fail](https://bugs.ntp.org/show_bug.cgi?id=2923)
  - fixed dependency inversion from [Bug 2837](https://bugs.ntp.org/show_bug.cgi?id=2387)
* [Bug 2896: Nothing happens if minsane < maxclock < minclock](https://bugs.ntp.org/show_bug.cgi?id=2896)
  - produce ERROR log message about dysfunctional daemon.
* [Bug 2851: allow -4/-6 on restrict line with mask](https://bugs.ntp.org/show_bug.cgi?id=2851)
  - applied patch by Miroslav Lichvar for ntp4.2.6 compat
* [Bug 2645: out-of-bound pointers in ctl_putsys and decode_bitflags](https://bugs.ntp.org/show_bug.cgi?id=2645)
  - Fixed these and some more locations of this pattern. Probably din't get them all, though.
* Update copyright year.
* `bk-7` trigger updates

* * *

#### 4.2.8p9-win

**Release Date:** 2017 Feb 01

* [Bug 3144: NTP does not build without openSSL](https://bugs.ntp.org/show_bug.cgi?id=3144)
  - added missed changeset for automatic openssl lib detection
  - fixed some minor warning issues
* [Bug 3095:  More compatibility with openssl 1.1](https://bugs.ntp.org/show_bug.cgi?id=3095)
* `configure.ac` cleanup.
* `openssl configure` cleanup.

* * *

#### 4.2.8p9

**Release Date:** 2016 Nov 21

* [Sec 3119: Trap crash](/support/securitynotice/ntpbug3119/)
* [Sec 3118: Mode 6 information disclosure and DDoS vector](/support/securitynotice/ntpbug3118/)
  - TRAP config via mode 6 packet requires `AUTH` now.
* [Sec 3114: Broadcast Mode Replay Prevention DoS](/support/securitynotice/ntpbug3114/)
  - applied patches by Matthew Van Gundy.
  - with `bcpollbstep`, tweaks and cleanup
* [Sec 3113: Broadcast Mode Poll Interval Enforcement DoS](/support/securitynotice/ntpbug3113/)
  - applied fix as suggested by Matthew Van Gundy
* [Sec 3110: Windows: ntpd DoS by oversized UDP packet](/support/securitynotice/ntpbug3110/)
  - fixed error handling for truncated UDP packets.
* [Sec 3102: Zero origin issues](/support/securitynotice/ntpbug3102/)
* [Sec 3082: null pointer dereference in _IO_str_init_static_internal()](/support/securitynotice/ntpbug3082/)
  - more hardening to `read_mru_list()`.
* [Sec 3072: Attack on interface selection](/support/securitynotice/ntpbug3072/)
  - implemented Miroslav Lichvar's suggestion to skip interface updates based on incoming packets
* [Bug 3142: bug in netmask prefix length detection](https://bugs.ntp.org/show_bug.cgi?id=3142)
* [Bug 3138: gpsdjson refclock should honor fudgetime1](https://bugs.ntp.org/show_bug.cgi?id=3138)
* [Bug 3129: Unknown hosts can put resolver thread into a hard loop](https://bugs.ntp.org/show_bug.cgi?id=3129)
  - moved retry decision where it belongs.
* [Bug 3125: NTPD doesn't fully start when ntp.conf entries are out of order using the loopback-ppsapi-provider.dll](https://bugs.ntp.org/show_bug.cgi?id=3125)
* [Bug 3116: unit tests for NTP time stamp expansion](https://bugs.ntp.org/show_bug.cgi?id=3116)
* [Bug 3100: ntpq can't retrieve daemon_version](https://bugs.ntp.org/show_bug.cgi?id=3100)
  - fixed extended `sysvar` lookup (bug introduced with [bug 3008](https://bugs.ntp.org/show_bug.cgi?id=3008) fix)
* [Bug 3095: Compatibility with openssl 1.1](https://bugs.ntp.org/show_bug.cgi?id=3095)
  - applied patches by Kurt Roeckx to source
  - added shim layer for SSL API calls with issues (both directions)
* [Bug 3089: Serial Parser does not work anymore for hopfser like device](https://bugs.ntp.org/show_bug.cgi?id=3089)
  - simplified / refactored hex-decoding in driver.
* [Bug 3084: update-leap mis-parses the leapfile name](https://bugs.ntp.org/show_bug.cgi?id=3084)
* [Bug 3068: Linker warnings when building on Solaris](https://bugs.ntp.org/show_bug.cgi?id=3068)
  - applied patch thanks to Andrew Stormont
* [Bug 3067: Root distance calculation needs improvement](https://bugs.ntp.org/show_bug.cgi?id=3067)
* [Bug 3066: NMEA clock ignores pps](https://bugs.ntp.org/show_bug.cgi?id=3066)
  - PPS-HACK works again.
* [Bug 3059: Potential buffer overrun from oversized hash](https://bugs.ntp.org/show_bug.cgi?id=3059)
  - applied patch by Brian Utterback
* [Bug 3053: ntp_loopfilter.c frequency calc precedence error](https://bugs.ntp.org/show_bug.cgi?id=3053)
* [Bug 3050:  Fix for bug #2960 causes [...] spurious error message](https://bugs.ntp.org/show_bug.cgi?id=3050)
  - patches by Reinhard Max and Havard Eidnes
* [Bug 3047: Fix refclock_jjy C-DEX JST2000](https://bugs.ntp.org/show_bug.cgi?id=3047)
  - Patch provided by Kuramatsu.
* [Bug 3021: unity_fixture.c needs pragma weak](https://bugs.ntp.org/show_bug.cgi?id=3021)
  - removed unnecessary & harmful decls of `setUp()` & `tearDown()`
* [Bug 3019: Windows: ERROR_HOST_UNREACHABLE block packet processing](https://bugs.ntp.org/show_bug.cgi?id=3019)
* [Bug 2998: sntp/tests/packetProcessing.c broken without openssl](https://bugs.ntp.org/show_bug.cgi?id=2998)
* [Bug 2961: sntp/tests/packetProcessing.c assumes AUTOKEY](https://bugs.ntp.org/show_bug.cgi?id=2961)
* [Bug 2959: refclock_jupiter: gps week correction](https://bugs.ntp.org/show_bug.cgi?id=2959)
  - fixed GPS week expansion to work based on build date. Special thanks to Craig Leres for initial patch and testing.
* [Bug 2951: ntpd tests fail: multiple definition of `send_via_ntp_signd`](https://bugs.ntp.org/show_bug.cgi?id=2951)
  - fixed `Makefile.am`
* [Bug 2689: ATOM driver processes last PPS pulse at startup, even if it is very old](https://bugs.ntp.org/show_bug.cgi?id=2689)
  - make sure PPS source is alive before processing samples
  - improve stability close to the 500ms phase jump (phase gate)
* Fix typos in `include/ntp.h`.
* Shim `X509_get_signature_nid()` if needed.
* `git` author attribution cleanup
* `bk ignore` file cleanup
* remove locks in Windows IO, use rpc-like thread synchronisation instead

* * *

#### 4.2.8p8

**Release Date:** 2016 Jun 2

* [Sec 3042: Broadcast Interleave](/support/securitynotice/ntpbug3042/)
* [Sec 3043: Autokey association reset](/support/securitynotice/ntpbug3043/)
  - validate origin timestamps on bad MACs, too
* [Sec 3044: Spoofed server packets are partially processed](/support/securitynotice/ntpbug3044/)
* [Sec 3045: Bad authentication demobilizes ephemeral associations](/support/securitynotice/ntpbug3045/)
* [Sec 3046: CRYPTO_NAK crash](/support/securitynotice/ntpbug3046/)
* [Bug 3038: NTP fails to build in VS2015](https://bugs.ntp.org/show_bug.cgi?id=3038)
  - provide build environment
  - `wint_t` and `struct timespec` defined by VS2015
  - fixed `print()/scanf()` format issues
* [Bug 3052: Add a .gitignore file](https://bugs.ntp.org/show_bug.cgi?id=3052)
* [Bug 3054: miscopt.html documents the allan intercept in seconds](https://bugs.ntp.org/show_bug.cgi?id=3054)
* [Bug 3058: fetch_timestamp() mishandles 64-bit alignment](https://bugs.ntp.org/show_bug.cgi?id=3058)
* Update the `NEWS` file for 4.2.8p8.
* Fix typo in `ntp-wait` and `plot_summary`.
* Make sure we have an `author` file for `git` imports.
* Update the `sntp` problem tests for MacOS.

* * *

#### 4.2.8p7

**Release Date:** 2016 Apr 26

* [Sec 2901: KoD packets must have non-zero transmit timestamps](/support/securitynotice/ntpbug2901/)
* [Sec 2936: Skeleton Key: Any system knowing the trusted key can serve time. Include passive servers in this check](/support/securitynotice/ntpbug2936/)
* [Sec 2945: Additional KoD packet checks](/support/securitynotice/ntpbug2945/)
* [Sec 2978: Interleave can be partially triggered](/support/securitynotice/ntpbug2978/)
* [Sec 3007: Validate crypto-NAKs](/support/securitynotice/ntpbug3007/)
* [Sec 3008: Always check the return value of ctl_getitem()](/support/securitynotice/ntpbug3008/)
  - initial work by HStenn
  - Additional cleanup of `ctl_getitem` by JPerlinger
* [Sec 3009: Crafted addpeer with hmode > 7 causes OOB error](/support/securitynotice/ntpbug3009/)
   - added more stringent checks on packet content
* [Sec 3010: remote configuration trustedkey/requestkey values are not properly validated](/support/securitynotice/ntpbug3010/)
  - sidekick: Ignore keys that have an unsupported MAC algorithm but are otherwise well-formed
* [Sec 3011: Duplicate IPs on unconfig directives will cause an assertion botch](/support/securitynotice/ntpbug3011/)
  - graciously accept the same IP multiple times.
* [Sec 3020: Refclock impersonation](/support/securitynotice/ntpbug3020/)
* [Bug 2831:  Segmentation Fault in DNS lookup during startup](https://bugs.ntp.org/show_bug.cgi?id=2831)
  - fixed yet another race condition in the threaded resolver code.
* [Bug 2858: bool support.  Use stdbool.h when available](https://bugs.ntp.org/show_bug.cgi?id=2858)
* [Bug 2879: Improve NTP security against timing attacks](https://bugs.ntp.org/show_bug.cgi?id=2879)
  - integrated patches by Loganaden Velvidron with some modifications & unit tests
* [Bug 2952: Symmetric active/passive mode is broken](https://bugs.ntp.org/show_bug.cgi?id=2952)
* [Bug 2960: async name resolution fixes for chroot() environments](https://bugs.ntp.org/show_bug.cgi?id=2960)
* [Bug 2994: Systems with HAVE_SIGNALED_IO fail to compile](https://bugs.ntp.org/show_bug.cgi?id=2994)
* [Bug 2995: Fixes to compile on Windows](https://bugs.ntp.org/show_bug.cgi?id=2995)
* [Bug 2999: out-of-bounds access in `is_safe_filename()`](https://bugs.ntp.org/show_bug.cgi?id=2999)
* [Bug 3013: Fix for ssl_init.c SHA1 test](https://bugs.ntp.org/show_bug.cgi?id=3013)
  - Patch provided by Ch. Weisgerber
* [Bug 3015: ntpq: config-from-file: "request contains an unprintable character"](https://bugs.ntp.org/show_bug.cgi?id=3015)
  - A change related to [Bug 2853](https://bugs.ntp.org/show_bug.cgi?id=2853) forbids trailing white space in remote `config` commands.
* [Bug 3019: NTPD stops processing packets after ERROR_HOST_UNREACHABLE](https://bugs.ntp.org/show_bug.cgi?id=3019)
  - report and patch from Aleksandr Kostikov.
  - Overhaul of Windows IO completion port handling.
* [Bug 3022: authkeys.c should be refactored](https://bugs.ntp.org/show_bug.cgi?id=3022)
  - fixed memory leak in access list (`auth[read]keys.c`)
  - refactored handling of key access lists (`auth[read]keys.c`)
  - reduced number of error branches (`authreadkeys.c`)
* [Bug 3023: ntpdate cannot correct dates in the future](https://bugs.ntp.org/show_bug.cgi?id=3023)
* [Bug 3030: ntpq needs a general way to specify refid output format](https://bugs.ntp.org/show_bug.cgi?id=3030)
* [Bug 3031: ntp broadcastclient unable to synchronize to an server when the time of server changed](https://bugs.ntp.org/show_bug.cgi?id=3031)
  - Check the initial delay calculation and reject/unpeer the broadcast server if the delay exceeds 50ms. Retry again after the next broadcast packet.
* [Bug 3036: autokey trips an INSIST in authistrustedip()](https://bugs.ntp.org/show_bug.cgi?id=3036)
* Document `ntp.key`'s optional IP list in authenetic.html. 
* Update html/xleave.html documentation.
* Update `ntp.conf` documentation.
* Fix some Credit: attributions in the `NEWS` file.
* Fix typo in html/monopt.html.
* Add `README.pullrequests`.
* Cleanup to `include/ntp.h`.

* * *

#### 4.2.8p6

**Release Date:** 2016 Jan 20

* [Sec 2935: Deja Vu: Replay attack on authenticated broadcast mode](/support/securitynotice/ntpbug2935/)
* [Sec 2936: Skeleton Key: Any trusted key system can serve time](/support/securitynotice/ntpbug2936/)
* [Sec 2937: ntpq: nextvar() missing length check](/support/securitynotice/ntpbug2937/)
* [Sec 2938: ntpq saveconfig command allows dangerous characters in filenames](/support/securitynotice/ntpbug2938/)
* [Sec 2939: reslist NULL pointer dereference](/support/securitynotice/ntpbug2939/)
* [Sec 2940: Stack exhaustion in recursive traversal of restriction list](/support/securitynotice/ntpbug2940/)
* [Sec 2942: Off-path DoS attack on auth broadcast mode](/support/securitynotice/ntpbug2942/)
* [Sec 2945: Zero Origin Timestamp Bypass](/support/securitynotice/ntpbug2945/)
* [Sec 2948: Potential Infinite Loop in ntpq ( and ntpdc)](/support/securitynotice/ntpbug2948/)
* [Bug 2772: adj_systime overflows tv_usec](https://bugs.ntp.org/show_bug.cgi?id=2772)
* [Bug 2814: msyslog deadlock when signaled](https://bugs.ntp.org/show_bug.cgi?id=2814)
  - applied patch by shenpeng11@huawei.com with minor adjustments
* [Bug 2882: Look at ntp_request.c:list_peers_sum()](https://bugs.ntp.org/show_bug.cgi?id=2882)
* [Bug 2891: Deadlock in deferred DNS lookup framework](https://bugs.ntp.org/show_bug.cgi?id=2891)
* [Bug 2892: Several test cases assume IPv6 capabilities even when IPv6 is disabled in the build](https://bugs.ntp.org/show_bug.cgi?id=2892)
  - Found this already fixed, but validation led to cleanup actions.
* [Bug 2905: DNS lookups broken](https://bugs.ntp.org/show_bug.cgi?id=2905)
  - added limits to stack consumption, fixed some return code handling
* [Bug 2971: ntpq bails on ^C: select fails: Interrupted system call](https://bugs.ntp.org/show_bug.cgi?id=2971)
  - changed stacked/nested handling of <kbd>CTRL-C</kbd>.
  - make <kbd>CTRL-C</kbd> work for retrieval and printing od MRU list.
* [Bug 2980: reduce number of warnings](https://bugs.ntp.org/show_bug.cgi?id=2980)
  - integrated several patches from Havard Eidnes
* [Bug 2985: bogus calculation in authkeys.c](https://bugs.ntp.org/show_bug.cgi?id=2985)
  - implement `auth_log2()` using integer bithack instead of float calculation
* Make `leapsec_query` debug messages less verbose.
* Disable incomplete `t-ntp_signd.c` test.

* * *

#### 4.2.8p5

**Release Date:** 2016 Jan 7

* [Sec 2956: small-step/big-step.  Close the panic gate earlier](/support/securitynotice/ntpbug2956/)
* CID 1339955: Free allocated memory in `caljulian` test.
* CID 1339962: Explicitly initialize variable in `caljulian` test.
* CID 1341527: Quiet a `CHECKED_RETURN` in `sntp/tests/t-log.c`.
* CID 1341533: Missing assertion in `sntp/tests/t-log.c`.
* CID 1341534: Resource leak in `tests/ntpd/t-ntp_signd.c`.
* CID 1341535: Resource leak in `tests/ntpd/t-ntp_signd.c`.
* CID 1341536: Resource leak in `tests/ntpd/t-ntp_signd.c`.
* CID 1341537: Resource leak in `tests/ntpd/t-ntp_signd.c`.
* CID 1341538: Memory leak in `tests/ntpd/ntp_prio_q.c:262`.
* CID 1341677: Nits in `sntp/tests/keyFile.c`.
* CID 1341678: Nits in `sntp/tests/keyFile.c`.
* CID 1341679: Nits in `sntp/tests/keyFile.c`.
* CID 1341680: Nits in `sntp/tests/keyFile.c`.
* CID 1341681: Nits in `sntp/tests/keyFile.c`.
* CID 1341682: Nit in `libntp/authreadkeys.c`.
* CID 1341684: Nit in `tests/ntpd/t-ntp_signd.c`.
* [Bug 2829: Look at pipe_fds in ntpd.c](https://bugs.ntp.org/show_bug.cgi?id=2829)
* [Bug 2887: stratum -1 config results as showing value 99](https://bugs.ntp.org/show_bug.cgi?id=2887)
  - `fudge stratum` should only accept values [0..16].
* [Bug 2932: Update leapsecond file info in miscopt.html](https://bugs.ntp.org/show_bug.cgi?id=2932)
* [Bug 2934: tests/ntpd/t-ntp_scanner.c has a magic constant wired in](https://bugs.ntp.org/show_bug.cgi?id=2934)
* [Bug 2944: errno is not preserved properly in ntpdate after sendto call](https://bugs.ntp.org/show_bug.cgi?id=2944)
  - applied patch by Christos Zoulas.
* [Bug 2952: Symmetric active/passive mode is broken](https://bugs.ntp.org/show_bug.cgi?id=2952)
* [Bug 2954: Version 4.2.8p4 crashes on startup with sig fault](https://bugs.ntp.org/show_bug.cgi?id=2954)
  - fixed data race conditions in threaded DNS worker.
  - limit threading warm-up to Linux; FreeBSD bombs on it.
* [Bug 2957: 'unsigned int' vs 'size_t' format clash](https://bugs.ntp.org/show_bug.cgi?id=2957)
  - accept key file only if there are no parsing errors
  - fixed `size_t/u_int` format clash
  - fixed wrong use of `strlcpy`
* [Bug 2958: ntpq: fatal error messages need a final newline](https://bugs.ntp.org/show_bug.cgi?id=2958)
* [Bug 2962: truncation of size_t/ptrdiff_t on 64bit targets](https://bugs.ntp.org/show_bug.cgi?id=2962)
  - fixed several other warnings (cast-alignment, missing const, missing prototypes)
  - promote use of `size_t` for values that express a size
  - use `ptr-to-const` for read-only arguments
  - make sure `SOCKET` values are not truncated (win32-specific)
  - format string fixes
* [Bug 2965: Local clock didn't work since 4.2.8p4](https://bugs.ntp.org/show_bug.cgi?id=2965)
* [Bug 2967: ntpdate command suffers an assertion failure](https://bugs.ntp.org/show_bug.cgi?id=2967)
  - fixed `ntp_rfc2553.c` to return proper address length.
* [Bug 2969:  Seg fault from ntpq/mrulist when looking at server with lots of clients](https://bugs.ntp.org/show_bug.cgi?id=2969)
* [Bug 2971: ntpq bails on ^C: select fails: Interrupted system call](https://bugs.ntp.org/show_bug.cgi?id=2971)
  - changed stacked/nested handling of <kbd>CTRL-C</kbd>.
  - make <kbd>CTRL-C</kbd> work for retrieval and printing of MRU list.
* Unity cleanup for FreeBSD-6.4.
* Unity test cleanup.
* Libevent `autoconf pthread` fixes for FreeBSD-10.
* Header cleanup in `tests/sandbox/uglydate.c`.
* Header cleanup in `tests/libntp/sfptostr.c`.
* Quiet a warning from `clang`.
* Update the `NEWS` file.
* Update `scripts/calc_tickadj/Makefile.am`.

#### 4.2.8p4

**Release Date:** 2015 Oct 21

* [Sec 1918: TALOS-CAN-0062: prevent directory traversal for VMS, too, when using `saveconfig` command](/support/securitynotice/ntpbug2918/)
* [Sec 2899: CVE-2014-9297](/support/securitynotice/ntpbug2899/)
* [Sec 2901: Drop invalid packet before checking KoD. Check for all KoDs](/support/securitynotice/ntpbug2901/)
  - Log incoming packets that fail TEST2.
* [Sec 2902: configuration directives "pidfile" and "driftfile" should be local-only](/support/securitynotice/ntpbug2902/)
* [Sec 2909: added missing call to 'free()' in ntp_crypto.c](/support/securitynotice/ntpbug2909/)
* [Sec 2913: TALOS-CAN-0052: crash by loop counter underrun](/support/securitynotice/ntpbug2913/)
* [Sec 2916: TALOS-CAN-0054: memory corruption in password store](/support/securitynotice/ntpbug2916/)
* [Sec 2917: TALOS-CAN-0055: Infinite loop if extended logging enabled and the logfile and keyfile are the same](/support/securitynotice/ntpbug2917/)
* [Sec 2919: TALOS-CAN-0063: avoid buffer overrun in ntpq](/support/securitynotice/ntpbug2919/)
* [Sec 2920: TALOS-CAN-0064: signed/unsiged clash could lead to buffer overun and memory corruption](/support/securitynotice/ntpbug2920/)
* [Sec 2921: TALOS-CAN-0065: password length memory corruption](/support/securitynotice/ntpbug2921/)
* [Sec 2922: decodenetnum() will ASSERT botch instead of returning FAIL on some bogus values](/support/securitynotice/ntpbug2922/)
* [Sec 2941: NAK to the Future: Symmetric association authentication bypass via crypto-NAK](/support/securitynotice/ntpbug2941/)
* [Bug 2332: (reopened) Exercise thread cancellation once before dropping privileges and limiting resources in NTPD removes the need to link forcefully against `libgcc_s` which does not always work](https://bugs.ntp.org/show_bug.cgi?id=2332)
* [Bug 2595: ntpdate man page quirks](https://bugs.ntp.org/show_bug.cgi?id=2595)
* [Bug 2625: Deprecate flag1 in local refclock](https://bugs.ntp.org/show_bug.cgi?id=2625)
* [Bug 2817: Stop locking ntpd into memory by default under Linux](https://bugs.ntp.org/show_bug.cgi?id=2817)
* [Bug 2821: minor build issues: fixed refclock_gpsdjson.c](https://bugs.ntp.org/show_bug.cgi?id=2821)
* [Bug 2823: ntpsweep with recursive peers option doesn't work](https://bugs.ntp.org/show_bug.cgi?id=2823)
* [Bug 2849: Systems with more than one default route may never synchronize](https://bugs.ntp.org/show_bug.cgi?id=2849)
  - Note that this patch might need to be reverted once [Bug 2043](https://bugs.ntp.org/show_bug.cgi?id=2043) has been fixed
* [Bug 2864: 4.2.8p3 fails to compile on Windows](https://bugs.ntp.org/show_bug.cgi?id=2864)
* [Bug 2866: segmentation fault at initgroups()](https://bugs.ntp.org/show_bug.cgi?id=2866)
* [Bug 2867: ntpd with autokey active crashed by `ntpq -crv`](https://bugs.ntp.org/show_bug.cgi?id=2867)
* [Bug 2873: libevent should not include .deps/ in the tarball](https://bugs.ntp.org/show_bug.cgi?id=2873)
* [Bug 2874: Don't distribute generated sntp/tests/fileHandlingTest.h](https://bugs.ntp.org/show_bug.cgi?id=2874)
* [Bug 2875: sntp/Makefile.am: Get rid of DIST_SUBDIRS.  libevent must be configured for the distribution targets](https://bugs.ntp.org/show_bug.cgi?id=2875)
* [Bug 2883: ntpd crashes on exit with empty driftfile](https://bugs.ntp.org/show_bug.cgi?id=2883)
* [Bug 2886: Mis-spelling: "outlyer" should be "outlier"](https://bugs.ntp.org/show_bug.cgi?id=2886)
* [Bug 2888: streamline calendar functions](https://bugs.ntp.org/show_bug.cgi?id=2888)
* [Bug 2889: ntp-dev-4.3.67 does not build on Windows](https://bugs.ntp.org/show_bug.cgi?id=2889)
* [Bug 2890: Ignore ENOBUFS on routing netlink socket](https://bugs.ntp.org/show_bug.cgi?id=2890)
* [Bug 2906: make check needs better support for pthreads](https://bugs.ntp.org/show_bug.cgi?id=2906)
* [Bug 2907: dist* build targets require our libevent/ to be enabled](https://bugs.ntp.org/show_bug.cgi?id=2907)
* [Bug 2912: no munlockall() under Windows](https://bugs.ntp.org/show_bug.cgi?id=2912)
* `libntp/emalloc.c`: Remove explicit include of `stdint.h`
* Put Unity `CPPFLAGS` items in `unity_config.h`
* `tests/ntpd/g_leapsec.cpp` typo fix.
* Phase 1 deprecation of google test in `sntp/tests/`.
* On some versions of HP-UX, `inttypes.h` does not include `stdint.h`.
* `top_srcdir` can change based on `ntp` v. `sntp`.
* `sntp/tests/` function parameter list cleanup.
* `tests/libntp/` function parameter list cleanup.
* `tests/ntpd/` function parameter list cleanup.
* `sntp/unity/unity_config.h`: handle `stdint.h`.
* `sntp/unity/unity_internals.h`: handle *`INTPTR_MAX` on old Solaris.
* `tests/libntp/timevalops.c` and `timespecops.c` fixed error printing.
* `tests/libntp/` improvements in code and fixed error printing.
* `tests/libntp: a_md5encrypt.c, authkeys.c, buftvtots.c, calendar.c, caljulian.c, caltontp.c, clocktime.c, humandate.c, hextolfp.c, decodenetnum.c` - fixed formatting; first declaration, then code (C90); deleted unnecessary comments; changed from `sprintf` to `snprintf`; fixed order of includes.
* `tests/libntp/lfpfunc.c` remove unnecessary include, remove old comments, fix formatting, cleanup.
* `tests/libntp/lfptostr.c` remove unnecessary include, add consts, fix formatting.
* `tests/libntp/statestr.c` remove empty functions, remove unnecessary include, fix formatting.
* `tests/libntp/modetoa.c` fixed formatting.
* `tests/libntp/msyslog.c` fixed formatting.
* `tests/libntp/numtoa.c` deleted unnecessary empty functions, fixed formatting.
* `tests/libntp/numtohost.c` added const, fixed formatting.
* `tests/libntp/refnumtoa.c` fixed formatting.
* `tests/libntp/ssl_init.c` fixed formatting.
* `tests/libntp/tvtots.c` fixed a bug, fixed formatting.
* `tests/libntp/uglydate.c` removed an unnecessary include.
* `tests/libntp/vi64ops.c` removed an unnecessary comment, fixed formatting.
* `tests/libntp/ymd3yd.c` removed an empty function and an unnecessary include, fixed formatting.
* `tests/libntp/timespecops.c` fixed formatting, fixed the order of includes, removed unnecessary comments, cleanup.
* `tests/libntp/timevalops.c` fixed the order of includes, deleted unnecessary comments, cleanup.
* `tests/libntp/sockaddrtest.h` making it agree to NTP's conventions of formatting.
* `tests/libntp/lfptest.h` cleanup.
* `tests/libntp/test-libntp.c` fix formatting.
* `sntp/tests/crypto.c` is now using proper Unity's assertions, fixed formatting.
* `sntp/tests/kodDatabase.c` added consts, deleted empty function, fixed formatting.
* `sntp/tests/kodFile.c` cleanup, fixed formatting.
* `sntp/tests/packetHandling.c` is now using proper Unity's assertions, fixed formatting, deleted unused variable.
* `sntp/tests/keyFile.c` is now using proper Unity's assertions, fixed formatting.
* `sntp/tests/packetProcessing.c` changed from `sprintf` to `snprintf`, fixed formatting.
* `sntp/tests/utilities.c` is now using proper Unity's assertions, changed the order of includes, fixed formatting, removed unnecessary comments.
* `sntp/tests/sntptest.h` fixed formatting.
* `sntp/tests/fileHandlingTest.h`.in fixed a possible buffer overflow problem, made one function do its job, deleted unnecessary prints, fixed formatting.
* `sntp/unity/Makefile.am` added a missing header.
* `sntp/unity/unity_config.h`: Distribute it.
* `sntp/libevent/evconfig-private.h`: remove generated file from SCM.
* `sntp/unity/Makefile.am`: fix some broken paths.
* `sntp/unity/unity.c`: Clean up a `printf()`. 
* Phase 1 deprecation of google test in `tests/libntp/`. 
* Don't build `sntp/libevent/sample/`.
* `tests/libntp/test_caltontp` needs `-lpthread`.
* `br-flock`: `--enable-local-libevent`.
* Wrote tests for `ntpd/ntp_prio_q.c`.
* `scripts/lib/NTP/Util.pm:` stratum output is version-dependent.
* Get rid of the `NTP_` prefix on our assertion macros.
* Code cleanup.
* `libntp/icom.c`: Typo fix.
* `util/ntptime.c`: initialization nit.
* `ntpd/ntp_peer.c:newpeer()`: added a `DEBUG_REQUIRE(srcadr)`.
* Add `std_unity`_tests to various `Makefile.am` files.
* `ntpd/ntp_restrict.c`: added a few assertions, created tests for this file.
* Changed `progname` to be const in many files - now it's consistent.
* Typo fix for `GCC` warning suppression.
* Added `tests/ntpd/ntp_scanner.c` test.
* Added declarations to all Unity tests, and did minor fixes to them. Reduced the number of warnings by half.
* Updated `generate_test_runner.rb` and updated the `sntp/unity/auto` directory with the latest Unity updates from Mark.
* Retire google test - phase I.
* Unity test cleanup: move declaration of `initializing`.
* Update the `NEWS` file.
* Autoconf cleanup.
* Unit test dist cleanup.
* Cleanup various test `Makefile.am` files.
* Pthread autoconf macro cleanup.
* Fix `progname` definition in unity runner scripts.
* Clean trailing whitespace in `tests/ntpd/Makefile.am`.
* Update the patch for [bug 2817](https://bugs.ntp.org/show_bug.cgi?id=2817).
* More updates for [bug 2817](https://bugs.ntp.org/show_bug.cgi?id=2817).
* Fix bugs in `tests/ntpd/ntp_prio_q.c`.
* `gcc` on older HPUX may need `+allowdups`.
* Adding missing `MCAST` protection.
* Disable certain test programs on certain platforms.
* Implement `--enable-problem-tests` (on by default).
* build system tweaks.

#### 4.2.8p3

**Release Date:** 2015 Jun 29

* [Sec 2853: Crafted remote config packet can crash some versions of ntpd](/support/securitynotice/ntpbug2853/)
  - Initial work on `tests/sec-2853/`.
* [Bug 1060: Buffer overruns in libparse/clk_rawdcf.c](https://bugs.ntp.org/show_bug.cgi?id=1060)
* [Bug 2846: Report 'unsynchronized' status during the leap second](https://bugs.ntp.org/show_bug.cgi?id=2846)
  - Fixed in Martin Burnicki's changes to [Bug 2855](https://bugs.ntp.org/show_bug.cgi?id=2855).
* [Bug 2859: Improve raw DCF77 robustness deconding](https://bugs.ntp.org/show_bug.cgi?id=2859)
* [Bug 2860: ntpq ifstats sanity check is too stringent](https://bugs.ntp.org/show_bug.cgi?id=2860)
* `README.leapsmear` added.
* `README.leapsmear` edited.
* `tests/libntp/msyslog.c`: fixed a `gcc` warning.
* `ntpd/ntp.conf.def`: Document DSCP and `leapsmearinterval`.
* html/miscopt.html: Document `leapsmearinterval`, other cleanup.

#### 4.2.8p3-RC3

**Release Date:** 2015 Jun 27

* [Bug 2855: Parser fix for conditional leap smear code](https://bugs.ntp.org/show_bug.cgi?id=2855)
  - Report leap smear in the REFID
* [Bug 2856: ntpd should wait() on terminated child processes](https://bugs.ntp.org/show_bug.cgi?id=2856)
* [Bug 2857: Stratus VOS does not support SIGIO](https://bugs.ntp.org/show_bug.cgi?id=2857)
* html/drivers/driver22.html: typo fix.
* `refidsmear` test cleanup.
* `refidsmear` function support and tests.
* `sntp/tests/Makefile.am`: remove `g_nameresolution.cpp` as it tested something that was only in the 4.2.6 `sntp`.
* Modified `tests/bug-2803/Makefile.am` so it builds Unity framework tests.
* Modified `tests/libtnp/Makefile.am` so it builds Unity framework tests.
* Modified `sntp/tests/Makefile.am` so it builds Unity framework tests.
* `tests/sandbox/smeartest.c`: Harlan Stenn, Damir Tomic, Juergen Perlinger.
* Converted from `gtest` to Unity: `tests/bug-2803/`.
* Converted from `gtest` to Unity: `tests/libntp/ a_md5encrypt, atoint.c, atouint.c, authkeys.c, buftvtots.c, calendar.c, caljulian.c, calyearstart.c, clocktime.c, hextoint.c, lfpfunc.c, modetoa.c, numtoa.c, numtohost.c, refnumtoa.c, ssl_init.c, statestr.c, timespecops.c, timevalops.c, uglydate.c, vi64ops.c, ymd2yd.c`.
* Converted from `gtest` to Unity: `sntp/tests/ kodDatabase.c, kodFile.c, networking.c, keyFile.c, utilities.cpp, sntptest.h, fileHandlingTest.h`.
* Converted from `gtest` to Unity: `sntp/tests/ caltontp.c, humandate.c, msyslog.c, prettydate.c, recvbuff.c, sfptostr.c, tstotv.c, tvtots.c, sntp/tests/packetProcessing.c`.

#### 4.2.8p3-RC2

**Release Date:** 2015 Jun 24

* [Bug 2778: Implement `apeers`  ntpq command to include associd](https://bugs.ntp.org/show_bug.cgi?id=2778)
* [Bug 2805: ntpd fails to join multicast group](https://bugs.ntp.org/show_bug.cgi?id=2805)
* [Bug 2824: Convert update-leap to perl](https://bugs.ntp.org/show_bug.cgi?id=2824)
  - also see [2769](https://bugs.ntp.org/show_bug.cgi?id=2769)
* [Bug 2830: ntpd doesn't always transfer the correct TAI offset via autokey](https://bugs.ntp.org/show_bug.cgi?id=2830)
  - NTPD transfers the current TAI (instead of an announcement) now. This might still needed improvement.
  - Update autokey data ASAP when `sys_tai` changes.
  - Fix unit test that was broken by changes for autokey update.
  - Avoid potential signature length issue and use `DPRINTF` where possible in `ntp_crypto.c`.
* [Bug 2832: refclock_jjy.c supports the TDC-300](https://bugs.ntp.org/show_bug.cgi?id=2832)
* [Bug 2834: Correct a broken html tag in html/refclock.html](https://bugs.ntp.org/show_bug.cgi?id=2834)
* [Bug 2836: DFC77 patches from Frank Kardel to make decoding more robust, and require 2 consecutive timestamps to be consistent](https://bugs.ntp.org/show_bug.cgi?id=2836)
* [Bug 2837: Allow a configurable DSCP value](https://bugs.ntp.org/show_bug.cgi?id=2837)
  - add test for DSCP to `ntpd/complete.conf`.
* [Bug 2842: Glitch in ntp.conf.def documentation stanza](https://bugs.ntp.org/show_bug.cgi?id=2842)
  - Bug in `mdoc2man`
* [Bug 2843: make check fails on 4.3.36](https://bugs.ntp.org/show_bug.cgi?id=2843)
  - Fixed compiler warnings about numeric range overflow. The original topic was fixed in a byplay to [bug 2830](https://bugs.ntp.org/show_bug.cgi?id=2830).
* [Bug 2845: Harden memory allocation in ntpd](https://bugs.ntp.org/show_bug.cgi?id=2845)
* [Bug 2852: 'make check' can't find unity.h](https://bugs.ntp.org/show_bug.cgi?id=2852)
* [Bug 2854: Missing brace in libntp/strdup.c](https://bugs.ntp.org/show_bug.cgi?id=2854)
* [Bug 2855: Implement conditional leap smear code](https://bugs.ntp.org/show_bug.cgi?id=2855)
  - leap smear cleanup
* Initial support for experimental leap smear code.
* Fixes to `sntp/tests/fileHandlingTest.h.in`.
* Report `select()` debug messages at debug level 3 now.
* `sntp/scripts/genLocInfo`: treat raspbian as debian.
* Unity test framework fixes. **Requires ruby for changes to tests**.
* Initial support for `PACKAGE_VERSION` tests.
* `sntp/libpkgver` belongs in `EXTRA_DIST`, not `DIST_SUBDIRS`.
* `tests/bug-2803/Makefile.am` must distribute `bug-2803.h`.
* automake-1.15 cleanup for `sntp/tests/fileHandlingTest.h.in`.

#### 4.2.8p3-RC1

**Release Date:** 2015 May 12

* CID 739725: Fix a rare resource leak in `libevent/listener.c`.
* CID 1295478: Quiet a pedantic potential error from the fix for [Bug 2776](https://bugs.ntp.org/show_bug.cgi?id=2776).
* CID 1296235: Fix `refclock_jjy.c` and correcting type of the driver40-ja.html.
* CID 1269537: Clean up a line of dead code in `getShmTime()`.
* [Bug 2590: autogen-5.18.5](https://bugs.ntp.org/show_bug.cgi?id=2590)
* [Bug 2612: restrict: Warn when `monitor` can't be disabled because of `limited`](https://bugs.ntp.org/show_bug.cgi?id=2612)
* [Bug 2650: fix includefile processing](https://bugs.ntp.org/show_bug.cgi?id=2650)
* [Bug 2745: ntpd -x steps clock on leap second](https://bugs.ntp.org/show_bug.cgi?id=2745)
  - Fixed an initial-value problem that caused misbehaviour in absence of any leapsecond information.
  - Do leap second stepping only of the step adjustment is beyond the proper jump distance limit and step correction is allowed at all.
* [Bug 2750: build for Win64](https://bugs.ntp.org/show_bug.cgi?id=2750)
  - Building for 32bit of loopback ppsapi needs `def` file
* [Bug 2776: Improve ntpq's `help keytype`](https://bugs.ntp.org/show_bug.cgi?id=2776)
* [Bug 2782: Refactor refclock_shm.c, add memory barrier protection](https://bugs.ntp.org/show_bug.cgi?id=2782)
* [Bug 2792: If the `IFF_RUNNING` interface flag is supported then an interface is ignored as long as this flag is not set since the interface is not usable (e.g., no link)](https://bugs.ntp.org/show_bug.cgi?id=2792)
* [Bug 2794: Clean up kernel clock status reports](https://bugs.ntp.org/show_bug.cgi?id=2794)
* [Bug 2800: refclock_true.c true_debug() can't open debug log because of incompatible open/fdopen parameters](https://bugs.ntp.org/show_bug.cgi?id=2800)
* [Bug 2804: install-local-data assumes GNU `find` semantics](https://bugs.ntp.org/show_bug.cgi?id=2804)
* [Bug 2806: refclock_jjy.c supports the Telephone JJY](https://bugs.ntp.org/show_bug.cgi?id=2806)
* [Bug 2808: GPSD_JSON driver enhancements, step 1](https://bugs.ntp.org/show_bug.cgi?id=2808)
  - Fix crash during cleanup if GPS device not present and `char` device.
  - Increase internal token buffer to parse all JSON data, even SKY.
  - Defer logging of errors during driver init until the first unit is started, so the `syslog` is not cluttered when the driver is not used.
  - Various improvements, see https://bugs.ntp.org/show_bug.cgi?id=2808 for details.
  - Changed `libjsmn` to a more recent version.
* [Bug 2810: refclock_shm.c memory barrier code needs tweaks for QNX](https://bugs.ntp.org/show_bug.cgi?id=2810)
* [Bug 2813: HP-UX needs -D__STDC_VERSION__=199901L and limits.h](https://bugs.ntp.org/show_bug.cgi?id=2813)
* [Bug 2815: net-snmp before v5.4 has circular library dependencies](https://bugs.ntp.org/show_bug.cgi?id=2815)
* [Bug 2821: Add a missing NTP_PRINTF and a missing const](https://bugs.ntp.org/show_bug.cgi?id=2821)
* [Bug 2822: New leap column in sntp broke NTP::Util.pm](https://bugs.ntp.org/show_bug.cgi?id=2822)
* [Bug 2825: Quiet file installation in html/](https://bugs.ntp.org/show_bug.cgi?id=2825)
* [Bug 2830: ntpd doesn't always transfer the correct TAI offset via autokey](https://bugs.ntp.org/show_bug.cgi?id=2830)
   - NTPD transfers the current TAI (instead of an announcement) now. This might still needed improvement.
* Add an assert to the `ntpq ifstats` code.
* Clean up the `RLIMIT_STACK` code.
* Improve the `ntpq` documentation around the `controlkey keyid`.
* `ntpq.c` cleanup.
* Windows port build cleanup.

#### 4.2.8p2

**Release Date:** 2015 Apr 07

* [Bug 2763: Fix for different thresholds for forward and backward steps](https://bugs.ntp.org/show_bug.cgi?id=2763)
* Initial import of the Unity test framework.

#### 4.2.8p2-RC2

**Release Date:** 2015 Apr 3

* [Bug 2592: FLAG_TSTAMP_PPS cleanup for refclock_parse.c](https://bugs.ntp.org/show_bug.cgi?id=2592)
* [Bug 2769: New script: update-leap](https://bugs.ntp.org/show_bug.cgi?id=2769)
  - cleanup for update-leap
* [Bug 2788: New flag -G (force_step_once)](https://bugs.ntp.org/show_bug.cgi?id=2788)
* [Bug 2794: Clean up kernel clock status reports](https://bugs.ntp.org/show_bug.cgi?id=2794)
* [Bug 2795: Cannot build without OpenSLL (on Win32)](https://bugs.ntp.org/show_bug.cgi?id=2795)
  - Provided a Win32 specific wrapper around `libevent/arc4random.c`.
  - Fixed some minor warnings.
* [Bug 2796: ntp-keygen crashes in `getclock()` on Win32](https://bugs.ntp.org/show_bug.cgi?id=2796)
* [Bug 2797: ntp-keygen trapped in endless loop for MD5 keys on big-endian machines](https://bugs.ntp.org/show_bug.cgi?id=2797)
* [Bug 2798: sntp should decode and display the leap indicator](https://bugs.ntp.org/show_bug.cgi?id=2798)
* Simple cleanup to html/build.html

#### 4.2.8p2-RC1

**Release Date:** 2015 Mar 30

* [Sec 2779: ntpd accepts unauthenticated packets with symmetric key crypto](/support/securitynotice/ntpbug2779/)
* [Sec 2781: Authentication doesn't protect symmetric associations against DoS attacks](/support/securitynotice/ntpbug2781/)
* [Bug 2794: Don't let reports on normal kernel status changes look like errors](https://bugs.ntp.org/show_bug.cgi?id=2794)
* [Bug 2788: New flag -G (force_step_once)](https://bugs.ntp.org/show_bug.cgi?id=2788)
* [Bug 2592: Account for PPS sources which can provide an accurate absolute time stamp, and status information](https://bugs.ntp.org/show_bug.cgi?id=2592)
  - Fixed indention and removed trailing whitespace.
* [Bug 1787: DCF77's formerly "antenna" bit is "call bit" since 2003](https://bugs.ntp.org/show_bug.cgi?id=1787)
* [Bug 1960: setsockopt IPV6_MULTICAST_IF: Invalid argument](https://bugs.ntp.org/show_bug.cgi?id=1960)
* [Bug 2346: "graceful termination" signals do not do peer cleanup](https://bugs.ntp.org/show_bug.cgi?id=2346)
* [Bug 2728: See if C99-style structure initialization works](https://bugs.ntp.org/show_bug.cgi?id=2728)
* [Bug 2747: Upgrade libevent to 2.1.5-beta](https://bugs.ntp.org/show_bug.cgi?id=2747)
* [Bug 2749: ntp/lib/NTP/Util.pm needs update for ntpq -w, IPv6, .POOL](https://bugs.ntp.org/show_bug.cgi?id=2749)
* [Bug 2751: jitter.h has stale copies of l_fp macros](https://bugs.ntp.org/show_bug.cgi?id=2751)
* [Bug 2756: ntpd hangs in startup with gcc 3.3.5 on ARM](https://bugs.ntp.org/show_bug.cgi?id=2756)
* [Bug 2757: Quiet compiler warnings](https://bugs.ntp.org/show_bug.cgi?id=2757)
* [Bug 2759: Expose nonvolatile/clk_wander_threshold to ntpq](https://bugs.ntp.org/show_bug.cgi?id=2759)
* [Bug 2763: Allow different thresholds for forward and backward steps](https://bugs.ntp.org/show_bug.cgi?id=2763)
* [Bug 2766: ntp-keygen output files should not be world-readable](https://bugs.ntp.org/show_bug.cgi?id=2766)
* [Bug 2767: ntp-keygen -M should symlink to ntp.keys](https://bugs.ntp.org/show_bug.cgi?id=2767)
* [Bug 2771: nonvolatile value is documented in wrong units](https://bugs.ntp.org/show_bug.cgi?id=2771)
* [Bug 2773: Early leap announcement from Palisade/Thunderbolt](https://bugs.ntp.org/show_bug.cgi?id=2773)
* [Bug 2774: Unreasonably verbose printout - leap pending/warning](https://bugs.ntp.org/show_bug.cgi?id=2774)
* [Bug 2775: ntp-keygen.c fails to compile under Windows](https://bugs.ntp.org/show_bug.cgi?id=2775)
* [Bug 2777: Fixed loops and decoding of Meinberg GPS satellite info](https://bugs.ntp.org/show_bug.cgi?id=2777)
  - Removed non-ASCII characters from some copyright comments.
  - Removed trailing whitespace.
  - Updated definitions for Meinberg clocks from current Meinberg header files.
  - Now use C99 fixed-width types and avoid non-ASCII characters in comments.
  - Account for updated definitions pulled from Meinberg header files.
  - Updated comments on Meinberg GPS receivers which are not only called GPS16x.
  - Replaced some constant numbers by defines from `ntp_calendar.h`.
  - Modified creation of parse-specific variables for Meinberg devices in `gps16x_message()`.
  - Reworked `mk_utcinfo()` to avoid printing of ambiguous leap second dates.
  - Modified `mbg_tm_str()` which now expects an additional parameter controlling if the time status shall be printed.
* [Bug 2783: Quiet autoconf warnings about missing AC_LANG_SOURCE](https://bugs.ntp.org/show_bug.cgi?id=2783)
* [Bug 2784: Fix for 2782 uses clock_gettime() instead of get_ostime()](https://bugs.ntp.org/show_bug.cgi?id=2784)
* [Bug 2789: Quiet compiler warnings from libevent](https://bugs.ntp.org/show_bug.cgi?id=2789)
* [Bug 2790: If ntpd sets the Windows MM timer highest resolution pause briefly before measuring system clock precision to yield correct results](https://bugs.ntp.org/show_bug.cgi?id=2790)
* Comment from Juergen Perlinger in `ntp_calendar.c` to make the code clearer.
* Use predefined function types for parse driver functions used to set up function pointers.
* Account for changed prototype of `parse_inp_fnc_t` functions.
* Cast parse conversion results to appropriate types to avoid compiler warnings.
* Let `ioctl()` for Windows accept a `(void *)` to avoid compiler warnings when called with pointers to different types.

#### 4.2.8p1

**Release Date:** 2015 Feb 04

* Update the `NEWS` file.
* [Sec 2671: vallen in extension fields are not validated](/support/securitynotice/ntpbug2671/)

#### 4.2.8p1-RC2

**Release Date:** 2015 Jan 29

* [Bug 2627: shm refclock allows only two units with owner-only access](https://bugs.ntp.org/show_bug.cgi?id=2627)
  - rework: reverted sense of mode bit (so default reflects previous behaviour) and updated ducumentation.
* [Bug 2732: Leap second not handled correctly on Windows 8](https://bugs.ntp.org/show_bug.cgi?id=2732)
  - use `GetTickCount()` to get the true elapsed time of slew. This should work for all versions of Windows >= W2K.
* [Bug 2738: Missing buffer initialization in refclocK_parse.c::parsestate()](https://bugs.ntp.org/show_bug.cgi?id=2738)
* [Bug 2739: Parse driver with PPS enabled occasionally evaluates](https://bugs.ntp.org/show_bug.cgi?id=2739)
  - PPS timestamp with wrong sign.
  - Removed some German umlauts.
* [Bug 2740: Removed some obsolete code from the parse driver](https://bugs.ntp.org/show_bug.cgi?id=2740)
* [Bug 2741: Incorrect buffer check in refclocK_parse.c::parsestatus()](https://bugs.ntp.org/show_bug.cgi?id=2741)

#### 4.2.8p1-RC1

**Release Date:** 2015 Jan 24

* [Sec 2672: Code cleanup: On some OSes ::1 can be spoofed](/support/securitynotice/ntpbug2672/)
* [Bug 2187: Update version number generation scripts](https://bugs.ntp.org/show_bug.cgi?id=2187)
* [Bug 2617: Fix sntp Usage documentation section](https://bugs.ntp.org/show_bug.cgi?id=2617)
* [Bug 2736: Show error message if we cannot open the config file](https://bugs.ntp.org/show_bug.cgi?id=2736)
* Copyright update.
* Fix the package name.

#### 4.2.8p1-beta5

**Release Date:** 2015 Jan 7

* [Bug 2695: Windows build: __func__ not supported under Windows](https://bugs.ntp.org/show_bug.cgi?id=2695)
* [Bug 2728: Work around C99-style structure initialization code](https://bugs.ntp.org/show_bug.cgi?id=2728)
  - for older compilers, specifically Visual Studio prior to VS2013.

#### 4.2.8p1-beta4

**Release Date:** 2015 Jan 04

* [Bug 1084: PPSAPI for ntpd on Windows with DLL backends](https://bugs.ntp.org/show_bug.cgi?id=1084)
* [Bug 2695: Build problem on Windows (sys/socket.h)](https://bugs.ntp.org/show_bug.cgi?id=2695)
* [Bug 2715: mdnstries option for ntp.conf from NetBSD](https://bugs.ntp.org/show_bug.cgi?id=2715)
* Fix a regression introduced to `timepps-Solaris.h` as part of [Bug 1206: Required compiler changes for Windows](https://bugs.ntp.org/show_bug.cgi?id=1206)

#### 4.2.8p1-beta3

**Release Date:** 2015 Jan 2

* [Bug 2627: shm refclock allows only two units with owner-only access](https://bugs.ntp.org/show_bug.cgi?id=2627)
  - Use mode bit 0 to select public access for units >= 2 (units 0 & 1 are always private).
* [Bug 2681: Fix display of certificate EOValidity dates on 32-bit systems](https://bugs.ntp.org/show_bug.cgi?id=2681)
* [Bug 2695: 4.2.8 does not build on Windows](https://bugs.ntp.org/show_bug.cgi?id=2695)
* [bug 2700: mrulist stopped working in 4.2.8](https://bugs.ntp.org/show_bug.cgi?id=2700)
* [Bug 2706: libparse/info_trimble.c build dependencies are broken](https://bugs.ntp.org/show_bug.cgi?id=2706)
* [Bug 2713: variable type/cast, parameter name, general cleanup from NetBSD](https://bugs.ntp.org/show_bug.cgi?id=2713)
* [Bug 2714: libevent may need to be built independently of any build of sntp](https://bugs.ntp.org/show_bug.cgi?id=2714)
* [Bug 2715: mdnstries option for ntp.conf from NetBSD](https://bugs.ntp.org/show_bug.cgi?id=2715)

#### 4.2.8p1-beta2

**Release Date:** 2014 Dec 27

* [Bug 2674: Install sntp in sbin on NetBSD](https://bugs.ntp.org/show_bug.cgi?id=2674)
* [Bug 2693: ntp-keygen doesn't build without OpenSSL and sntp](https://bugs.ntp.org/show_bug.cgi?id=2693)
* [Bug 2707: Avoid a C90 extension in libjsmn/jsmn.c](https://bugs.ntp.org/show_bug.cgi?id=2707)
* [Bug 2709: see if we have a C99 compiler (not yet required)](https://bugs.ntp.org/show_bug.cgi?id=2709)

#### 4.2.8p1-beta1

**Release Date:** 2014 Dec 23

* [Sec 2672: On some OSes ::1 can be spoofed, bypassing source IP ACLs](/support/securitynotice/ntpbug2672/)
* [Bug 2693: ntp-keygen doesn't build without OpenSSL](https://bugs.ntp.org/show_bug.cgi?id=2693)
* [Bug 2697: IN6_IS_ADDR_LOOPBACK build problems on some OSes](https://bugs.ntp.org/show_bug.cgi?id=2697)
* [Bug 2699: HAVE_SYS_SELECT_H is misspelled in refclock_gpsdjson.c](https://bugs.ntp.org/show_bug.cgi?id=2699)

#### 4.2.8

**Release Date:** 2014 Dec 19

* [Sec 730: Increase `RSA_generate_key` modulus](https://bugs.ntp.org/show_bug.cgi?id=730) / [CVE-2006-4339](https://nvd.nist.gov/vuln/detail/CVE-2006-4339)
* [Sec 2666: Use cryptographic random numbers for md5 key generation](/support/securitynotice/ntpbug2666/)
* [Sec 2667: buffer overflow in `crypto_recv()`](/support/securitynotice/ntpbug2667/)
* [Sec 2668: buffer overflow in `ctl_putdata()`](/support/securitynotice/ntpbug2668/)
* [Sec 2669: buffer overflow in `configure()`](/support/securitynotice/ntpbug2669/)
* [Sec 2670: Missing return; from error clause](/support/securitynotice/ntpbug2670/)
* [Sec 2671: `vallen` in extension fields are not validated](/support/securitynotice/ntpbug2671/)
* [Sec 2672: On some OSes ::1 can be spoofed, bypassing source IP ACLs](/support/securitynotice/ntpbug2672/)
* [Sec 2630: buffer overrun in `ntpq tokenize()`](https://bugs.ntp.org/show_bug.cgi?id=2630)
  - Limit the `ntpq` command buffer to 512 bytes.
* [Sec 2542: Strengthen the `mrulist` nonce](https://bugs.ntp.org/show_bug.cgi?id=2542)

* * *

* CID 1189401: Use `INSIST()` instead of a belt-and-suspenders pointer check.
* CID 1165098: Remove logically dead code from `refclock_true.c`.
* CID 1042586: Check the return value of `clock_gettime()` in `worker_sleep()`.
* CID 1009579: Check return status of `X509_add_ext()`.
* CID 984511: Some systems have different `printf` needs for `sizeof`.
* CID 975596: Copy/paste error: vallen should be `siglen`.
* CID 971094: Clean up time of check/time of use in `check_leap_file()`.
* CID 739724: Fix `printf arg` mismatch in a debug line.
* CID 739723: Print `sizeof` as unsigned.
* CID 739722: Change the way the extention and MAC fields are processed.
  - Clean up the definition of the `exten` field of `struct` pkt.
* CID 739715: Clean up `sockaddr_dump()`.
* CID 739714: Fix code indentation level.
* CID 739713: `devmask/recmask` copy/paste error.
* CID 739711: Ignore return status of `remove()` in `ntp-keygen.c`.
* CID 739710: Check return status of `mkdir()` in `sntp/kod_management.c`.
* CID 739709: Check return status of `fcntl()` in `refclock_datum.c`.
* CID 739708: Check return status of `fcntl()` in `refclock_arc.c`.
* CID 739559: Double close.
* CID 739558: Double close.
* CID 739473,739532: Out-of-bounds access/illegal address computation.
* CID 711660: Do a non-NULL pointer assertion check a bit earlier.
* CID 709207: Initialize `quality` for `ulink_receive`.
* CID 709185: `refclock_chu.c` will leak fd==0 (better fix)
  - refclock_chu.c will leak fd==0 (which should be impossible).
* CID 709173: Make sure a `libisc` function we do not use is called properly.
* CID 709169: check return from `open("/dev/null", 0)` and friends.
* CID 97377: `ntp-keygen.c`'s `followlink()` might not NUL-terminate.
* CID 97198: Check return from `ioctl()` calls in `refclock_acts.c`.
* CID 97194: Check return from `setsockopt()`.
* CID 97193: check return from `sscanf()` in `ntp_config.c`.
* CID 97123: Future-proof possible change to `refclock_nmea.c`.

* * *

* [Bug 2691: Wrong variable name in `refclock_ripencc.c`](https://bugs.ntp.org/show_bug.cgi?id=2691)
* [Bug 2687: RefClock 26/hpgps doesn't work at default line speed](https://bugs.ntp.org/show_bug.cgi?id=2687)
* [Bug 2686: `refclock_gpsdjson` needs `strtoll()`, which is not always present](https://bugs.ntp.org/show_bug.cgi?id=2686)
* [Bug 2685: Better document the KOD file for `sntp`](https://bugs.ntp.org/show_bug.cgi?id=2685)
* [Bug 2641: `sntp `is installed in the wrong location in Solaris](https://bugs.ntp.org/show_bug.cgi?id=2641)
* [Bug 2678: `nmea_control()` now checks `refclock_params()` result](https://bugs.ntp.org/show_bug.cgi?id=2678)
* [Bug 2314: Only enable PPS if kernel consumer binding succeeds](https://bugs.ntp.org/show_bug.cgi?id=2314)
  - Kernel PPS binding `EOPNOTSUPP` is a failure condition.
  - Rename `pps_enable` to `hardpps_enable`.
* [Bug 2677: `PATH_MAX` isn't `#define`'d under Windows](https://bugs.ntp.org/show_bug.cgi?id=2677)
  - Regression from the patch fixing [Bug 2639](https://bugs.ntp.org/show_bug.cgi?id=2639).
* [Bug 2651: Certificates with ASN timestamps w/ 4-digit years mis-parsed](https://bugs.ntp.org/show_bug.cgi?id=2651)
* [Bug 2639: Check return value of `ntp_adjtime()`](https://bugs.ntp.org/show_bug.cgi?id=2639)
* [Bug 2650: `includefile` processing broken](https://bugs.ntp.org/show_bug.cgi?id=2650)
* [Bug 2661: `ntpq` crashes with `mreadvar`](https://bugs.ntp.org/show_bug.cgi?id=2661)
* [Bug 2657: Document that `restrict nopeer` intereferes with `pool`](https://bugs.ntp.org/show_bug.cgi?id=2657)
* [Bug 2503: SHT utility outdated](https://bugs.ntp.org/show_bug.cgi?id=2503)
* [Bug 2654: `refclock_true.c` doesn't identify the Mk III](https://bugs.ntp.org/show_bug.cgi?id=2654)
* [Bug 2536: `ntpd` sandboxing support (`libseccomp2`) and cleanup](https://bugs.ntp.org/show_bug.cgi?id=2536)
* [Bug 2649: Clean up html/ page installation](https://bugs.ntp.org/show_bug.cgi?id=2649)
  - Fix `make install` leaves wrong owner for files in html/.
* [Bug 2556: `mrulist` is missing from the generated `ntpq` man page](https://bugs.ntp.org/show_bug.cgi?id=2556)
  - `ntpq` man page cleanup.
* [Bug 2652: Windows hates directory names that contain a `:`](https://bugs.ntp.org/show_bug.cgi?id=2652)
* [Bug 2502: Autogen text replacement errors.](https://bugs.ntp.org/show_bug.cgi?id=2502)
* [Bug 2640: `STA_NANO` can result in invalid `ntv.constant`](https://bugs.ntp.org/show_bug.cgi?id=2640)
* [Bug 2538: NTP programs print exit code in help/usage text](https://bugs.ntp.org/show_bug.cgi?id=2538)
* [Bug 2595: Man page quirks: `ntpdate` references in `ntpd`](https://bugs.ntp.org/show_bug.cgi?id=2595)
* [Bug 2613: www.ntp.org/bugs.html tells folks to email doc bugs to DLM](https://bugs.ntp.org/show_bug.cgi?id=2613)
* [Bug 2636: Clutter in `syslog` if `gpsd` not running](https://bugs.ntp.org/show_bug.cgi?id=2636)
   - found (hopefully) last cause for clutter in protocol version
   - log GPSD revision and release numbers with protocol version
   - Fix coverity warning from previous patch.
   - make driver work with GPSD protocol version 3.9
   - use exponential back-off for connection problems
   - implement rate-limit for `syslog` entries
* [Bug 2622: Synchronisation problem using SHM when time difference is more than four hours](https://bugs.ntp.org/show_bug.cgi?id=2622)
  - Add `control` function -- `fudge` values not available during start.
  - Change SHM driver so TOY restricted API is not used any more. (Plus some minor cleanup in logic and flow control)
* [Bug 1128: `ntp` truncates `remote` host information](https://bugs.ntp.org/show_bug.cgi?id=1128)
* [Bug 2633: Provide `stdnoreturn.h` for windows port](https://bugs.ntp.org/show_bug.cgi?id=2633)
* [Bug 2565: `ntpd` sometimes logs unexpected `getifaddrs()` errors](https://bugs.ntp.org/show_bug.cgi?id=2565)
  -* Handle `EINTR` on `getifaddrs()`.
* [Bug 2628: `mon_getmoremem()` relies on undefined behaviour](https://bugs.ntp.org/show_bug.cgi?id=2628)
* [Bug 2597: leap file processing loose ends](https://bugs.ntp.org/show_bug.cgi?id=2597)
  - uniform expiration check messages for config and timer triggered leap file loads
  - timer triggered loads log messages only once per day
  - fixed coverity issues
  - log daily warning when leap info less than 28 days to expiration or already expired; nag hourly on last day before expiration; log when leapfile name is invalid
* [Bug 2547: Automate update of "Last Update" datestamps in .html files](https://bugs.ntp.org/show_bug.cgi?id=2547)
  - Distribute the scripts needed for the fix
* [Bug 2623: Missing `{}` in `refclock_oncore.c`](https://bugs.ntp.org/show_bug.cgi?id=2623)
* [Bug 2621: Avoid use of indeterminate address after `free()`](https://bugs.ntp.org/show_bug.cgi?id=2621)
  - (minor C standard conformance issue)
* [Bug 2620: Use `version.pm` for checking version numbers in `NTP::Util`](https://bugs.ntp.org/show_bug.cgi?id=2620)
* [Bug 2624: Fix signed compare on `l_fp`](https://bugs.ntp.org/show_bug.cgi?id=2624)
* [Bug 2614: use `unsigned long` consistently in `ntp_random.c` to avoid possibly undefined behaviour in signed int overflow](https://bugs.ntp.org/show_bug.cgi?id=2614)
* [Bug 2619: Save a signed int copy of the return value of `i2d_DSA_SIG()`](https://bugs.ntp.org/show_bug.cgi?id=2619)
  - Provide missing `msyslog()` message in `crypto_alice()`.
* [Bug 2594: Update the year in `sntp/include/copyright.def`](https://bugs.ntp.org/show_bug.cgi?id=2594)
* [Bug 2589: Update VS2013 project files for `libntp`](https://bugs.ntp.org/show_bug.cgi?id=2589)
  - fix VS2009 compile problem.
* [Bug 2600: Fix "Undisicplined Local Clock" driver1.html page](https://bugs.ntp.org/show_bug.cgi?id=2600)
* [Bug 2570: cleanup: fix log format for successful leapfile load](https://bugs.ntp.org/show_bug.cgi?id=2570)
  - reduced logging noise, moved some functions into `libntp`.
  -refuse to load `leapsec` file with bad/missing SHA1 hash.
  - change reading the hash line code: NIST omits leading zeros.
* [Bug 2546: Windows build documentation updates](https://bugs.ntp.org/show_bug.cgi?id=2546)
* [Bug 2537: `ntpd` truncates symmetric keys to 20 bytes](https://bugs.ntp.org/show_bug.cgi?id=2537)
* [Bug 2311: Add more tags to `mdoc2xxx`](https://bugs.ntp.org/show_bug.cgi?id=2311)
* [Bug 2577: Update VS2013 solution and project files](https://bugs.ntp.org/show_bug.cgi?id=2577)
* [Bug 2572: cross-compiling fails for `--with-yielding-select`](https://bugs.ntp.org/show_bug.cgi?id=2572)
* [Bug 2170: Use `AC_PREPROC_IFELSE` instead of `AC_EGREP_CPP`](https://bugs.ntp.org/show_bug.cgi?id=2170)
* [Bug 2540: bootstrap script needs to `touch` files in finer-grained groups](https://bugs.ntp.org/show_bug.cgi?id=2540)
* [Bug 2576: `refclock_gpsdjson.c` doesn't compile if `CLOCK_GPSDJSON` is not enabled at `configure` time](https://bugs.ntp.org/show_bug.cgi?id=2576)
* [Bug 2562: Distribute the code in `libjsmn/`](https://bugs.ntp.org/show_bug.cgi?id=2562)
  - `GPSD_JSON`: fix solaris issues (`asprintf(), isfinite()`)
  - first release of the GPSD client clock (type 46)
* [Bug 2113: Warn about ignored extra args in `ntpq`](https://bugs.ntp.org/show_bug.cgi?id=2113)
* [Bug 2561: Allow wildcards in the target of the `interface` command](https://bugs.ntp.org/show_bug.cgi?id=2561)
* [Bug 2541: `ntpd` terminates itself with `SIGHUP` unexpectedly](https://bugs.ntp.org/show_bug.cgi?id=2541)
* [Bug 898: More documentation fixes](https://bugs.ntp.org/show_bug.cgi?id=898)
* [Bug 2555: Autogen `mdoc` man pages all stamped with SunOS 5.10](https://bugs.ntp.org/show_bug.cgi?id=2555)
* [Bug 492: Clearly document `ntpdate`'s pending deprecation](https://bugs.ntp.org/show_bug.cgi?id=492)
* [Bug 1186: `ntpd` fails with link local IPv6 addresses](https://bugs.ntp.org/show_bug.cgi?id=1186)
* [Bug 2466: Wrap NMEA timestamps in 1024 week cycles](https://bugs.ntp.org/show_bug.cgi?id=2466)
* [Bug 2551: `--disable-local-libevent` breaks the build](https://bugs.ntp.org/show_bug.cgi?id=2551)
* [Bug 2539: doc and code tweaks for NMEA driver](https://bugs.ntp.org/show_bug.cgi?id=2539)
* [Bug 2332: Be more careful about when we use `libgcc_s`](https://bugs.ntp.org/show_bug.cgi?id=2332)
  - Force reference to `libgcc_s` when using GCC, because threading+restricted user+locked memory otherwise fails on Linux.
* [Bug 792: TrueTime TL-3 WWV refclock support](https://bugs.ntp.org/show_bug.cgi?id=792)
* [Bug 930: `ntpdc` docs refer to `clockinfo`, but mean `clockstat`](https://bugs.ntp.org/show_bug.cgi?id=930)
* [Bug 1002: `ntp-keygen` option and documentation updates](https://bugs.ntp.org/show_bug.cgi?id=1002)
  - `-p/--pvt-passwd` is now `-p/--password`, and `-q/--get-pvt-passwd` is now `-q/--export-passwd`.
* [Bug 1349: `statistics` command not documented in HTML documentation](https://bugs.ntp.org/show_bug.cgi?id=1349)
  - In `html/monopt.html`, add statistics id, definition, description, and correct typo.
  - In `html/scripts/monopt.txt`, add statistics item, href, and comment.
  - In `ntpd/ntp.conf.def`, under statistics correct four to eight kinds.
  - In `ntpd/complete.conf.in`, add all eight kinds to statistics.
  - In `html/comdex.html`, remove duplicate footer.
* [Bug 1734: Include man page for `ntp.conf`](https://bugs.ntp.org/show_bug.cgi?id=1734)
* [Bug 2049: Clarify `ntpdate`'s `-d` option behavior](https://bugs.ntp.org/show_bug.cgi?id=2049)
* [Bug 2366: ntpdc.html: `burst/iburst` only work on servers](https://bugs.ntp.org/show_bug.cgi?id=2366)
* [Bug 2493: `ntptrace` needs a man page](https://bugs.ntp.org/show_bug.cgi?id=2493)
* [Bug 2545: Cleanup of `scripts/monitoring/ntptrap`](https://bugs.ntp.org/show_bug.cgi?id=2545)
* [Bug 2532: Note in `ntpdc` docs that `enable pps` only works on older `ntpd`](https://bugs.ntp.org/show_bug.cgi?id=2532)
* [Bug 2530: Fix documentation for enable/disable mode7 and pps](https://bugs.ntp.org/show_bug.cgi?id=2530)
* [Bug 2060: Warn about restrictions with `kod` but not `limited`](https://bugs.ntp.org/show_bug.cgi?id=2060)
* [Bug 2187: Update version number generation scripts](https://bugs.ntp.org/show_bug.cgi?id=2187)
* [Bug 2519: `mktime.c` does not compile on 64-bit Solaris but we do not need `timegm()` and the Solaris provides `mktime()`](https://bugs.ntp.org/show_bug.cgi?id=2519)
* [Bug 2522: Revert Bug 2513 fix - it breaks backward compatibility](https://bugs.ntp.org/show_bug.cgi?id=2522)
* [Bug 2521: `VPATH` tweaks for `perl -opts` files](https://bugs.ntp.org/show_bug.cgi?id=2521)
  - bootstrap script needs a tweak for `perl -opts` files.
* [Bug 2524: Add `ntpsweep` to `sntp/loc/*` files](https://bugs.ntp.org/show_bug.cgi?id=2524)
* [Bug 2526: Add `noinst` support to the `sntp/loc/` framework](https://bugs.ntp.org/show_bug.cgi?id=2526)
* [Bug 135: AIX5: "Address already in use" for IPv6 wildcard](https://bugs.ntp.org/show_bug.cgi?id=135)
* [Bug 2513: Remove any PIDFILE in `finish()`](https://bugs.ntp.org/show_bug.cgi?id=2513)
* [Bug 2516: Enable `clock_gettime()` support for AIX 5+](https://bugs.ntp.org/show_bug.cgi?id=2516)
* [Bug 2517: Fix peer status errors in decode.html](https://bugs.ntp.org/show_bug.cgi?id=2517)
* [Bug 2491: VS20xx compile fixes](https://bugs.ntp.org/show_bug.cgi?id=2491)
  - VS2013 project files.
* [Bug 2326: More leapsecond file notification cleanup](https://bugs.ntp.org/show_bug.cgi?id=2326)
  - Improve stale leapsecond notifications.
  - Check hourly for a new leapfile if the old one expired.
  - Notice when a new leapfile has been installed.
* [Bug 2506: make sure routing updates are always tracked](https://bugs.ntp.org/show_bug.cgi?id=2506)
* [Bug 2514: `secs/* #define` usage cleanup](https://bugs.ntp.org/show_bug.cgi?id=2514)
* [Bug 1050: Change ONCORE log message for leap second announcement to avoid misunderstandings](https://bugs.ntp.org/show_bug.cgi?id=1050)
* [Bug 2499: Win32 user-space/loopback ppsapi provider drops samples](https://bugs.ntp.org/show_bug.cgi?id=2499)
* [Bug 2256: Improve `configure`'s function searches in libraries](https://bugs.ntp.org/show_bug.cgi?id=2256)
* [Bug 2272: Use C99 integer types. `ntp_calendar.h` and `ntp_types.h`](https://bugs.ntp.org/show_bug.cgi?id=2272)
* [Bug 2375: Improve AIX compatibility](https://bugs.ntp.org/show_bug.cgi?id=2375)
  - AIX 7 doesn't like a `libevent` validation check.
* [Bug 2490: Fixed non-const initializer coming from Bug 2250 fix](https://bugs.ntp.org/show_bug.cgi?id=2490)
* [Bug 2250: Rework of leap second handling machine](https://bugs.ntp.org/show_bug.cgi?id=2250)
* [Bug 2419: (rc-nmea) Improve clockstats reporting when receiver sends data without valid GPS fix](https://bugs.ntp.org/show_bug.cgi?id=2419)
* [Bug 2482: Add and cleanup of droproot and jail support for Solaris](https://bugs.ntp.org/show_bug.cgi?id=2482)
* [Bug 2473: NTPD exits after clock is stepped backwards externally](https://bugs.ntp.org/show_bug.cgi?id=2473)
  - Avoid possible unsigned underrun for startup condition when testing for clock backstep.
* [Bug 2481: `ntpd` aborts when both user and group are specified with `-u`](https://bugs.ntp.org/show_bug.cgi?id=2481)
* [Bug 1642: `ntpdsim` can't find simnulate block in config file](https://bugs.ntp.org/show_bug.cgi?id=1642)
* [Bug 2472: (WinXP) Avoid self-termination of IO thread during `exit()`](https://bugs.ntp.org/show_bug.cgi?id=2472)
* [Bug 2085: Fix root distance and root dispersion calculations](https://bugs.ntp.org/show_bug.cgi?id=2085)
  - `clock_update() sys_rootdisp` calculation omits root delay.
* [Bug 2426: Possibly uninitialized data in `crypto_send()` - CID 975596](https://bugs.ntp.org/show_bug.cgi?id=2426)
* [Bug 2450: `--version` has bogus short option](https://bugs.ntp.org/show_bug.cgi?id=2450)
* [Bug 2454: Need way to set file descriptor limit](https://bugs.ntp.org/show_bug.cgi?id=2454)
* [Bug 2451: `rlimit` command is missing from the table of contents in miscopt.html](https://bugs.ntp.org/show_bug.cgi?id=2451)
* [Bug 2452: provide `io_handler/input_handler` only on non `HAVE_IO_COMPLETION_PORT` platforms](https://bugs.ntp.org/show_bug.cgi?id=2452)
* [Bug 2453: Need a way to avoid calling `mlockall`](https://bugs.ntp.org/show_bug.cgi?id=2453)
* [Bug 2458: `AM_CONFIG_HEADER` is obsolete](https://bugs.ntp.org/show_bug.cgi?id=2458)
* [Bug 2425: compile `io_handler()` in `ntp_io.c` unconditionally](https://bugs.ntp.org/show_bug.cgi?id=2425)
  - move part of input handler code from `ntpd.c` to `ntp_io.c` and fix `select()`-only platforms calling input_handler directly.
  - setup `SIGIO/SIGPOLL` for `asyncio` on the read side of a socketpair for the worker thread.
* [Bug 2448: Fix checks for `configure --with-stack-limit` and `--with-memlock` values](https://bugs.ntp.org/show_bug.cgi?id=2448)
* [Bug 2446: Quiet warnings from Oracle's Studio compiler](https://bugs.ntp.org/show_bug.cgi?id=2446)
* [Bug 2397: License/copyright cleanup](https://bugs.ntp.org/show_bug.cgi?id=2397)
* [Bug 2439: Fix check of `EscapeCommFunction()` in `ports/winnt/libntp/termios.c`](https://bugs.ntp.org/show_bug.cgi?id=2439)
* [Bug 2322: Oncore driver should send 0 PPS offset to GPS](https://bugs.ntp.org/show_bug.cgi?id=2322)
* [Bug 883: log warning arguments swapped in `refclock_gpsvme.c`](https://bugs.ntp.org/show_bug.cgi?id=883)
* [Bug 2413: Fix `make check` with automake >= 1.13](https://bugs.ntp.org/show_bug.cgi?id=2413)
* [Bug 2434: Line-buffer (v. block-buffer) stdout](https://bugs.ntp.org/show_bug.cgi?id=2434)
* [Bug 2368: make check troubles in `libevent`](https://bugs.ntp.org/show_bug.cgi?id=2368)
* [Bug 2427: `configure` fails to detect `recvmsg()` on Solaris](https://bugs.ntp.org/show_bug.cgi?id=2427)
* [Bug 1466: Oncore should set `FLAG_PPS`](https://bugs.ntp.org/show_bug.cgi?id=1466)
* [Bug 2423: Log command-line args at `LOG_INFO`](https://bugs.ntp.org/show_bug.cgi?id=2423)
* [Bug 2428: `do_unconf()` should reset `items` before the 2nd loop](https://bugs.ntp.org/show_bug.cgi?id=2428)
* [Bug 2415: `RES_LIMITED` flags check should use `&`, not `&&`](https://bugs.ntp.org/show_bug.cgi?id=2415)
* [Bug 2145: `ntpq` dumps core when displaying `sys_var_list` and more](https://bugs.ntp.org/show_bug.cgi?id=2145)
* [Bug 1485: Sometimes `ntpd` crashes](https://bugs.ntp.org/show_bug.cgi?id=1485)
* [Bug 2382: Implement `LOGTOD` using `ldexp()` instead of shifting](/support/securitynotice/ntpbug2382/)
* [Bug 1866: Disable some debugging output in `refclock_oncore`](https://bugs.ntp.org/show_bug.cgi?id=1866)
* [Bug 2149: Log an error message if `/proc/net/if_inet6` cannot be opened](https://bugs.ntp.org/show_bug.cgi?id=2149)
* [Bug 2357: `sntp/libopts/usage.c` sometimes needs `-lintl`](https://bugs.ntp.org/show_bug.cgi?id=2357)
* [Bug 2364: `sed -i` is not portable](https://bugs.ntp.org/show_bug.cgi?id=2364)
* [Bug 2365: `make check` fails in `libevent`](https://bugs.ntp.org/show_bug.cgi?id=2365)
* [Bug 2359: Fix `send_via_ntp_signd()` prototype](https://bugs.ntp.org/show_bug.cgi?id=2359)
* [Bug 2328: Don't apply small time adjustments on Windows versions which don't support this](https://bugs.ntp.org/show_bug.cgi?id=2328)
* [Bug 2321: Fixed Windows build, but `autogen` update still required](https://bugs.ntp.org/show_bug.cgi?id=2321)
* [Bug 2327: Rename `sntp/ag-tpl/:Old` to `sntp/ag-tpl/Old`](https://bugs.ntp.org/show_bug.cgi?id=2327)
* [Bug 2325: Re-enable `mlockall()` check under Linux post-1223 fix](https://bugs.ntp.org/show_bug.cgi?id=2325)
* [Bug 1223: reorganize inclusion of `sys/resource.h`](https://bugs.ntp.org/show_bug.cgi?id=1223)
  - Final cleanup for `rlimit` changes.
  - Allow configurable values for `RLIMIT_STACK` and `RLIMIT_MEMLOCK`.
* [Bug 2081 - **Backward Incompatible**: `rawstats` now logs everything](https://bugs.ntp.org/show_bug.cgi?id=2081)
* [Bug 2114: Update tests for `sntp`'s synch distance](https://bugs.ntp.org/show_bug.cgi?id=2114)
  - Correctly calculate `sntp`'s synch distance.
* [Bug 2278: ACTS `flag3` mismatch between code and driver18.html](https://bugs.ntp.org/show_bug.cgi?id=2278)
* [Bug 2024: Identify Events in the system status word in decode.html](https://bugs.ntp.org/show_bug.cgi?id=2024)
  - Remove unused system event code `EVNT_CLKHOP`.
* [Bug 2040: Provide a command-line option for the identity key bits](https://bugs.ntp.org/show_bug.cgi?id=2040)
* [Bug 1214: `proto: precision = ...` should be at `INFO`, not `NOTICE`](https://bugs.ntp.org/show_bug.cgi?id=1214)
* [Bug 2246: Clear `sys_leap` when voting says to disarm the leap](https://bugs.ntp.org/show_bug.cgi?id=2246)
* [Bug 2202: ntpq.html: there is no `acv` billboard](https://bugs.ntp.org/show_bug.cgi?id=2202)
* [Bug 2306: keep pps hack for Win32 even if user-mode/loopback](https://bugs.ntp.org/show_bug.cgi?id=2306)
  - PPS API is activated on a serial line.
  - Added user-mode/loop-back PPS API provider for Win32
* [Bug 2098: Install DLM's HTML documentation](https://bugs.ntp.org/show_bug.cgi?id=2098)
* [Bug 1320: Log `ntpd`'s initial command-line parameters](https://bugs.ntp.org/show_bug.cgi?id=1320)
* [Bug 2120: no `sysexits.h` under QNX](https://bugs.ntp.org/show_bug.cgi?id=2120)
* [Bug 2123: cleanup to html/leap.html](https://bugs.ntp.org/show_bug.cgi?id=2123)
* [Bug 969: Clarify ntpdate.html documentation about `-u` and `ntpd`](https://bugs.ntp.org/show_bug.cgi?id=969)
* [Bug 1217: `libisc/ifiter_sysctl.c:internal_current()`: Ignore RTM messages with wrong version](https://bugs.ntp.org/show_bug.cgi?id=1217)
* [Bug 2296: Fix compile problem with building with old OpenSSL](https://bugs.ntp.org/show_bug.cgi?id=2296)
  - Update fix for Bug 2294 to handle `--without-crypto`.
* [Bug 2301: Remove spurious debug output from `ntpq`](https://bugs.ntp.org/show_bug.cgi?id=2301)
* [Bug 922: Allow interspersed `-4` and `-6` flags on the `ntpq` command line](https://bugs.ntp.org/show_bug.cgi?id=922)
* [Bug 2294: `ntpd` crashes in FIPS mode](https://bugs.ntp.org/show_bug.cgi?id=2294)
* [Bug 2291: `sntp` should report why it cannot open `file.kod`](https://bugs.ntp.org/show_bug.cgi?id=2291)
* [Bug 2293: add support for `SO_BINTIME`, refine support for `SO_TIMESTAMPNS`](https://bugs.ntp.org/show_bug.cgi?id=2293)
* [Bug 938: The argument to the `-D` flag takes a number, not a string](https://bugs.ntp.org/show_bug.cgi?id=938)
* [Bug 1013: `ntpdate`'s HTML page claims wrong default version](https://bugs.ntp.org/show_bug.cgi?id=1013)
* [Bug 1374: Support `SO_TIMESTAMPNS`](https://bugs.ntp.org/show_bug.cgi?id=1374)
* [Bug 2266: Remove deprecated `refclock_trak.c` from Windows Makefile equivalents](https://bugs.ntp.org/show_bug.cgi?id=2266)
* [Bug 2274: Bring libopts/enum.c back to (old) ANSI C compliance](https://bugs.ntp.org/show_bug.cgi?id=2274)
* [Bug 2287: `ntpdate` returns 0 even if `adjtime()` call fails](https://bugs.ntp.org/show_bug.cgi?id=2287)
* [Bug 1997: Fix `sntp` broadcast timeouts](https://bugs.ntp.org/show_bug.cgi?id=1997)
* [Bug 2234: Fix incorrect `ntptrace` html documentation](https://bugs.ntp.org/show_bug.cgi?id=2234)
* [Bug 2262: Install html docs in `$htmldir`](https://bugs.ntp.org/show_bug.cgi?id=2262)
  - Install sntp.html into htmldir.
* [Bug 752: ToS cleanup from Mike Tatarinov](https://bugs.ntp.org/show_bug.cgi?id=752)
  - Use proper ToS network packet markings for IPv4 and IPv6.
* [Bug 1232: Convert SHM refclock to use struct timespec](https://bugs.ntp.org/show_bug.cgi?id=1232)
  - Add nanosecond support to SHM driver.
* [Bug 2258: Add `syslog` message about leap insertion](https://bugs.ntp.org/show_bug.cgi?id=2258)
* [Bug 2263: broadcast server doesn't work for host with `OS_MISSES_SPECIFIC_ROUTE_UPDATES`](https://bugs.ntp.org/show_bug.cgi?id=2263)
* [Bug 2271: Decode refclock types when built with `--disable-all-clocks`](https://bugs.ntp.org/show_bug.cgi?id=2271)
* [Bug 2276: `clk_sel240x.c #define`'s `_XOPEN_SOURCE`, breaking QNX6](https://bugs.ntp.org/show_bug.cgi?id=2276)
* [Bug 2264: Cleanup SEL240X Refclock](https://bugs.ntp.org/show_bug.cgi?id=2264)
* [Bug 2160: Log warning about expired leapseconds file](https://bugs.ntp.org/show_bug.cgi?id=2160)
* [Bug 2164: Greater precision needed for `ntpq` offset report](https://bugs.ntp.org/show_bug.cgi?id=2164)
* [Bug 2270: Install fails due to repeated man5 page names](https://bugs.ntp.org/show_bug.cgi?id=2270)
* [Bug 2242: `configure` fails to detect `getifaddrs` function on Solaris](https://bugs.ntp.org/show_bug.cgi?id=2242)
* [Bug 2249: Bad operator for `test` in `make check` of `libevent`](https://bugs.ntp.org/show_bug.cgi?id=2249)
* [Bug 2252: palisade: formats nanosecs to a 6-char field](https://bugs.ntp.org/show_bug.cgi?id=2252)
* [Bug 2247: Get rid of the TRAK refclock - deprecated since 2006](https://bugs.ntp.org/show_bug.cgi?id=2247)
* [Bug 1545: Note why we are logging the Version string](https://bugs.ntp.org/show_bug.cgi?id=1545)
* [Bug 1872: Remove legacy ppsclock fdpps, `#ifdef PPS`](https://bugs.ntp.org/show_bug.cgi?id=1872)
* [Bug 2075: Fix spelling of "incompatible"](https://bugs.ntp.org/show_bug.cgi?id=2075)
* [Bug 2241: MDNS registration should only happen if requested](https://bugs.ntp.org/show_bug.cgi?id=2241)
* [Bug 1454: Add parse clock support for the SEL-240x GPS products](https://bugs.ntp.org/show_bug.cgi?id=1454)
* [Bug 2227: Enable `mrulist` access control via `restrict ... nomrulist`](https://bugs.ntp.org/show_bug.cgi?id=2227)
* [Bug 2225: `libevent` configure hangs](https://bugs.ntp.org/show_bug.cgi?id=2225)
* [Bug 2224: Use-after-free in routing socket code after dropping root](https://bugs.ntp.org/show_bug.cgi?id=2224)
* [Bug 2211: `findbcastinter()`: possibly undefined variable `iface` used](https://bugs.ntp.org/show_bug.cgi?id=2211)
* [Bug 2220: Incorrect check for maximum association id in `ntpq`](https://bugs.ntp.org/show_bug.cgi?id=2220)
* [Bug 2204: Build with `--enable-getifaddrs=glibc` fails](https://bugs.ntp.org/show_bug.cgi?id=2204)
* [Bug 2178: `refclock_tsyncpci.c` reach register fails to shift](https://bugs.ntp.org/show_bug.cgi?id=2178)
* [Bug 2191: `dcfd -Y y2kcheck` on CentOS 6.2 x86_64 breaks `make check`](https://bugs.ntp.org/show_bug.cgi?id=2191)
* [Bug 2193: Building timestruct tests with Clang 3.1 fails](https://bugs.ntp.org/show_bug.cgi?id=2193)
* [Bug 2179: Remove `sntp/header.h`](https://bugs.ntp.org/show_bug.cgi?id=2179)
* [Bug 1744: Remove obsolete `ntpdate/ntptime*` items](https://bugs.ntp.org/show_bug.cgi?id=1744)
* [Bug 2174: `ntpd` rejects source UDP ports less than 123 as bogus](https://bugs.ntp.org/show_bug.cgi?id=2174)
* [Bug 2141: `handle_sigio()` calls get_`systime()`, which must be reentrant when `SIGIO` is used.
  - Sanity checks relative to the `prior get_systime()` are disabled in `ntpd` on systems with signaled I/O, but active in `sntp` and `ntpdate`.
* [Bug 1122: openssl detection via `pkg-config` fails when no additional `-Idir` flags are needed](https://bugs.ntp.org/show_bug.cgi?id=1122)
* [Bug 2156: clock instability with LOCAL driver, from Miroslav Lichvar](https://bugs.ntp.org/show_bug.cgi?id=2156)
* [Bug 2159: Windows `ntpd` using leapfile erroneous leap second 20120401](https://bugs.ntp.org/show_bug.cgi?id=2159)
* [Bug 2048: add the clock variable timecode to SHM refclock](https://bugs.ntp.org/show_bug.cgi?id=2048)
* [Bug 2148: `ntpd` 4.2.7p258 segfault with 0x0100000 bit in NMEA mode](https://bugs.ntp.org/show_bug.cgi?id=2148)
* [Bug 2140: Rework of Windows I/O completion port handling to avoid garbling serial input in UNIX line discipline emulation](https://bugs.ntp.org/show_bug.cgi?id=2140)
* [Bug 2143: NMEA driver: discard data if quality indication not good, add statistic counters (mode bit enabled) to `clockstats` file](https://bugs.ntp.org/show_bug.cgi?id=2143)
* [Bug 2135: defer calls to `io_input` to main thread under Windows](https://bugs.ntp.org/show_bug.cgi?id=2135)
* [Bug 2131: Set the system variable `settimeofday` only after clock step](https://bugs.ntp.org/show_bug.cgi?id=2131)
* [Bug 2134: `--enable-C99-snprintf` does not force `rpl_snprintf` use](https://bugs.ntp.org/show_bug.cgi?id=2134)
* [Bug 603: Only link with `nlist()`-related libraries when needed](https://bugs.ntp.org/show_bug.cgi?id=603)
* [Bug 2126: Compile error on Windows with `libopts` from Autogen 5.14](https://bugs.ntp.org/show_bug.cgi?id=2126)
* [Bug 2115: `ntptrace` should accept both `rootdispersion` and `rootdisp`](https://bugs.ntp.org/show_bug.cgi?id=2115)
* [Bug 2111: Remove `minpoll` delay before `iburst` for pool and manycastclient](https://bugs.ntp.org/show_bug.cgi?id=2111)
* [Bug 2109: `make clean check` is broken with `gtest` available](https://bugs.ntp.org/show_bug.cgi?id=2109)
* [Bug 2110: `systime.c` typo breaks build on microsecond clocks](https://bugs.ntp.org/show_bug.cgi?id=2110)
* [Bug 2104: `ntpdc` fault with oversize `-c` command](https://bugs.ntp.org/show_bug.cgi?id=2104)
* [Bug 2106: Fix warnings when using `-Wformat-security`](https://bugs.ntp.org/show_bug.cgi?id=2106)
* [Bug 2100: conversion problem with `timespec/timeval <--> l_fp` fixed; added tests to expose the bug](https://bugs.ntp.org/show_bug.cgi?id=2100)
* [Bug 2095: `ntptrace` now needs `rv` instead of `pstat`](https://bugs.ntp.org/show_bug.cgi?id=2095)
  - reported by Michael Tatarinov.
* [Bug 2015: Overriding `sys_tick` should recalculate `sys_precision`](https://bugs.ntp.org/show_bug.cgi?id=2015)
* [Bug 2037: Fuzzed non-interpolated clock may decrease](https://bugs.ntp.org/show_bug.cgi?id=2037)
* [Bug 2068: `tos ceiling` default and cap changed to 15](https://bugs.ntp.org/show_bug.cgi?id=2068)
  - from 4.2.6p5-RC2: `ntpd` sends nonprintable stratum 16 refid to `ntpq`.
* [Bug 2092: `clock_select()` selection jitter miscalculated](https://bugs.ntp.org/show_bug.cgi?id=2092)
* [Bug 2093: Reintroduce smaller stratum factor to system peer metric](https://bugs.ntp.org/show_bug.cgi?id=2093)
* [Bug 2082: from 4.2.6p5-RC3: 3-char refid sent by `ntpd` 4.2.6p5-RC2 ends with extra dot](https://bugs.ntp.org/show_bug.cgi?id=2082)
* [Bug 2086: from 4.2.6p5-RC3: `get_systime()` should not offset by `sys_residual`](https://bugs.ntp.org/show_bug.cgi?id=2086)
* [Bug 2087: from 4.2.6p5-RC3: `sys_jitter` calculation overweights `sys.peer` jitter](https://bugs.ntp.org/show_bug.cgi?id=2087)
* [Bug 2050: from 4.2.6p5-RC2: Orphan mode stratum counting to infinity](https://bugs.ntp.org/show_bug.cgi?id=2050)
* [Bug 2059: from 4.2.6p5-RC2: optional billboard column `server` does not honor `-n`](https://bugs.ntp.org/show_bug.cgi?id=2059)
* [Bug 2066: from 4.2.6p5-RC2: `ntpq lopeers ipv6 local` column overrun](https://bugs.ntp.org/show_bug.cgi?id=2066)
* [Bug 2069: from 4.2.6p5-RC2: broadcastclient, multicastclient spin up duplicate ephemeral associations without broadcastdelay](https://bugs.ntp.org/show_bug.cgi?id=2069)
* [Bug 2072: from 4.2.6p5-RC2: Orphan parent selection metric needs `ntohl()`](https://bugs.ntp.org/show_bug.cgi?id=2072)
* [Bug 2073: Correct `ntpq` billboard's `MODE_PASSIVE t` from `u` to `S`](https://bugs.ntp.org/show_bug.cgi?id=2073)
* [Bug 2052: Autokey `CRYPTO_ASSOC host@group vallen` needs checking](https://bugs.ntp.org/show_bug.cgi?id=2052)
* [Bug 1940: ignore auth key if hex decoding fails](https://bugs.ntp.org/show_bug.cgi?id=1940)
* [Bug 1995: fix wrong use of `ZERO()` macro in `ntp_calendar.c`](https://bugs.ntp.org/show_bug.cgi?id=1995)
  - add compile time stamp based era unfolding for `step_systime()` and necessary support to 'ntp-calendar.c'.
* [Bug 2036: `gcc` 2.95.3 preprocessor can't nest `#ifdef` in macro args](https://bugs.ntp.org/show_bug.cgi?id=2036)
* [Bug 2035: `ntpq -c mrulist` sleeps 1 sec between queries, not 5 msec](https://bugs.ntp.org/show_bug.cgi?id=2035)
* [Bug 2029: `make check` clutters `syslog`](https://bugs.ntp.org/show_bug.cgi?id=2029)
* [Bug 2025: Switching between daemon and kernel loops can doubly-correct drift](https://bugs.ntp.org/show_bug.cgi?id=2025)
* [Bug 2028: `ntpd -n` (nofork) redirects logging to `stderr`](https://bugs.ntp.org/show_bug.cgi?id=2028)
* [Bug 1945: `mbg_gps166.h` use of `_TM_DEFINED` conflicts with MS VC](https://bugs.ntp.org/show_bug.cgi?id=1945)
* [Bug 1946: `parse_start` uses open; does not work on Windows](https://bugs.ntp.org/show_bug.cgi?id=1946)
* [Bug 1947: Porting parse-based Wharton refclock driver to Windows](https://bugs.ntp.org/show_bug.cgi?id=1947)
* [Bug 2019: Allow selection of cipher for private key files](https://bugs.ntp.org/show_bug.cgi?id=2019)
* [Bug 2020: `ntp-keygen -s` no longer sets host in cert file name](https://bugs.ntp.org/show_bug.cgi?id=2020)
* [Bug 1981: Initial offset convergence applies frequency correction 2x with kernel discipline](https://bugs.ntp.org/show_bug.cgi?id=1981)
* [Bug 2008: Initial offset convergence degraded with 500 PPM `adjtime()`](https://bugs.ntp.org/show_bug.cgi?id=2008)
* [Bug 2009: `EVNT_NSET adj_systime()` mishandled by Windows `ntpd`](https://bugs.ntp.org/show_bug.cgi?id=2009)
* [Bug 1999: NMEA does not send `PMOTG` messages any more](https://bugs.ntp.org/show_bug.cgi?id=1999)
* [Bug 2003: from 4.2.6p4-RC3: `ntpq_read_assoc_peervars()` broken](https://bugs.ntp.org/show_bug.cgi?id=2003)
* [Bug 2000: `ntpd` worker threads must block signals expected in main thread](https://bugs.ntp.org/show_bug.cgi?id=2000)
  - Require `-D4` or higher for `ntpd SIGALRM` debug trace
* [Bug 2001: add `ntpq -c` timerstats like `ntpdc -c` timerstats](https://bugs.ntp.org/show_bug.cgi?id=2001)
  - from 4.2.6p4-RC3: `ntpdc` timerstats reports overruns as handled.
* [Bug 1993: `ntpd` Windows port `adj_systime()` broken in 4.2.7p203](https://bugs.ntp.org/show_bug.cgi?id=1993)
* [Bug 1992: `util/tg2` doesn't compile, needs `libntp`](https://bugs.ntp.org/show_bug.cgi?id=1992)
* [Bug 1988: Better `sntp` send failed error message needed](https://bugs.ntp.org/show_bug.cgi?id=1988)
* [Bug 1989: `sntp` manual page sometimes refers to SNTP as a program](https://bugs.ntp.org/show_bug.cgi?id=1989)
* [Bug 1990: `sntp` output should include stratum](https://bugs.ntp.org/show_bug.cgi?id=1990)
* [Bug 1986: Require Visual C++ 2005 or later compilers in Windows port](https://bugs.ntp.org/show_bug.cgi?id=1986)
* [Bug 1983: `--without-sntp` build breaks in `sntp` subdir](https://bugs.ntp.org/show_bug.cgi?id=1983)
* [Bug 1984: from 4.2.6p4-RC3: `ntp/libisc` fails to compile on OS X 10.7](https://bugs.ntp.org/show_bug.cgi?id=1984)
* [Bug 1985: from 4.2.6p4-RC3: `logconfig =allall` rejected](https://bugs.ntp.org/show_bug.cgi?id=1985)
* [Bug 1975: from 4.2.6p4-RC2: `libntp/mktime.c` won't work with 64-bit `time_t`](https://bugs.ntp.org/show_bug.cgi?id=1975)
* [Bug 1976: `genLocInfo` writes to srcdir break `make distcheck`](https://bugs.ntp.org/show_bug.cgi?id=1976)
* [Bug 1977: Fix flag/description mismatches in `ntp-keygen-opts.def`](https://bugs.ntp.org/show_bug.cgi?id=1977)
* [Bug 1972: from 4.2.6p4-RC2: checking for `struct rtattr` fails](https://bugs.ntp.org/show_bug.cgi?id=1972)
* [Bug 1973: Widen reference clock mode from 8 to 32 bits](https://bugs.ntp.org/show_bug.cgi?id=1973)
* [Bug 1608: from 4.2.6p4-RC2: Parse Refclock driver should honor `trusttime`](https://bugs.ntp.org/show_bug.cgi?id=1608)
* [Bug 1970: from 4.2.6p4-RC2: `UNLINK_EXPR_SLIST()` causes crash if list is empty](https://bugs.ntp.org/show_bug.cgi?id=1970)
* [Bug 1966: Broken `FILES` section for `ntp.keys.def`](https://bugs.ntp.org/show_bug.cgi?id=1966)
* [Bug 1948: Update man page section layout](https://bugs.ntp.org/show_bug.cgi?id=1948)
* [Bug 1963: add reset command for `ntpq :config`, similar to `ntpdc`'s](https://bugs.ntp.org/show_bug.cgi?id=1963)
* [Bug 1964: `--without-sntp` should not build `sntp`](https://bugs.ntp.org/show_bug.cgi?id=1964)
* [Bug 1961: from 4.2.6p4: `html2man` update: distribute `ntp-wait.html`](https://bugs.ntp.org/show_bug.cgi?id=1961)
* [Bug 1134: from 4.2.6p4-RC1: `ntpd` fails binding to tentative IPv6 addresses](https://bugs.ntp.org/show_bug.cgi?id=1134)
* [Bug 1790: from 4.2.6p4-RC1: Update `config.guess` and `config.sub` to detect AIX6](https://bugs.ntp.org/show_bug.cgi?id=1790)
* [Bug 1958: `genLocInfo` must export `PATH`](https://bugs.ntp.org/show_bug.cgi?id=1958)
* [Bug 1954: Fix typos in `[s]bin_PROGRAMS` in `ntpd/Makefile.am`](https://bugs.ntp.org/show_bug.cgi?id=1954)
* [Bug 1950: Control installation of `event_rpcgen.py`](https://bugs.ntp.org/show_bug.cgi?id=1950)
* [Bug 1304: Update sntp.html to reflect new implementation](https://bugs.ntp.org/show_bug.cgi?id=1304)
* [Bug 1938: `addr_eqprefix()` doesn't clear enough storage](https://bugs.ntp.org/show_bug.cgi?id=1938)
* [Bug 1936: Correctly set `IPV6_MULTICAST_LOOP`](https://bugs.ntp.org/show_bug.cgi?id=1936)
* [Bug 1932: `libevent/util_internal.h builtin_expect` compile error with `gcc` 2.95](https://bugs.ntp.org/show_bug.cgi?id=1932)
* [Bug 1933: WWVB/Spectracom driver timestamps `LF`s, not `CR`s](https://bugs.ntp.org/show_bug.cgi?id=1933)
* [Bug 1927: `io_closeclock()` should purge pending `recvbufs`](https://bugs.ntp.org/show_bug.cgi?id=1927)
* [Bug 1931: `cv` always includes `fudgetime1`, never `fudgetime2`](https://bugs.ntp.org/show_bug.cgi?id=1931)
* [Bug 988: Local clock eats up `-g` option, so `ntpd` stops with large initial time offset](https://bugs.ntp.org/show_bug.cgi?id=988)
* [Bug 1921: LOCAL, ACTS drivers with `prefer` excluded from initial candidate list](https://bugs.ntp.org/show_bug.cgi?id=1921)
* [Bug 1922: `tos orphanwait` applied incorrectly at startup](https://bugs.ntp.org/show_bug.cgi?id=1922)
* [Bug 1923: orphan parent favored over LOCAL, ACTS drivers](https://bugs.ntp.org/show_bug.cgi?id=1923)
* [Bug 1924: Billboard tally codes sometimes do not match operation, variables](https://bugs.ntp.org/show_bug.cgi?id=1924)
* [Bug 1911: missing curly brace in `libntp/ntp_rfc2553.c`](https://bugs.ntp.org/show_bug.cgi?id=1911)
* [Bug 1910: Support the Tristate Ltd. TS-GPSclock-01](https://bugs.ntp.org/show_bug.cgi?id=1910)
* [Bug 1904: 4.2.7p160 Windows build broken (`POSIX_SHELL`)](https://bugs.ntp.org/show_bug.cgi?id=1904)
* [Bug 1906: 4.2.7p160 - `libtool`: compile: cannot determine name of library object in `./libevent`](https://bugs.ntp.org/show_bug.cgi?id=1906)
* [Bug 1901: Simulator does not set `progname`](https://bugs.ntp.org/show_bug.cgi?id=1901)
* [Bug 1890: 4.2.7p156 segfault in duplicate `freeaddrinfo()`](https://bugs.ntp.org/show_bug.cgi?id=1890)
* [Bug 1851: `freeaddrinfo()` called after `getaddrinfo()` fails](https://bugs.ntp.org/show_bug.cgi?id=1851)
* [Bug 1887: DNS fails on 4.2.7p153 using threads](https://bugs.ntp.org/show_bug.cgi?id=1887)
* [Bug 1881: describe the `{+,-,s}` characters in `configure --help` output](https://bugs.ntp.org/show_bug.cgi?id=1881)
* [Bug 1875: `asn2ntp()` rewritten with `caltontp()`; `timegm()` substitute likely to crash with 64bit `time_t`](https://bugs.ntp.org/show_bug.cgi?id=1875)
* [Bug 1840: `ntp_lists.h FIFO` macros buggy](https://bugs.ntp.org/show_bug.cgi?id=1840)
* [Bug 1874: `ntpq -c rv 0 sys_var_list` empty](https://bugs.ntp.org/show_bug.cgi?id=1874)
* [Bug 1732: `ntpd` ties up CPU on disconnected USB refclock/device](https://bugs.ntp.org/show_bug.cgi?id=1732)
* [Bug 1861: `tickadj` build failure using `uClibc`](https://bugs.ntp.org/show_bug.cgi?id=1861)
* [Bug 1862: `in6addr_any` test in `configure` fooled by arm gcc 4.1.3 `-O2`](https://bugs.ntp.org/show_bug.cgi?id=1862)
* [Bug 1844: `ntpd` 4.2.7p131 NetBSD, `--gc-sections` links bad executable](https://bugs.ntp.org/show_bug.cgi?id=1844)
* [Bug 1848: `ntpd` 4.2.7p139 `--disable-thread-support` does not compile](https://bugs.ntp.org/show_bug.cgi?id=1848)
  - `make check ntpd --saveconfigquit` clutters `syslog`.
* [Bug 1846: MacOSX: debug symbol not found by `propdelay` or `tickadj`](https://bugs.ntp.org/show_bug.cgi?id=1846)
* [Bug 1839: 4.2.7p135 still installs `libevent ev*.h` headers](https://bugs.ntp.org/show_bug.cgi?id=1839)
* [Bug 1837: Build fails on Win7 due to `regedit` requiring privilege](https://bugs.ntp.org/show_bug.cgi?id=1837)
* [Bug 1834: `ntpdate` 4.2.7p131 aborts with assertion failure](https://bugs.ntp.org/show_bug.cgi?id=1834)
* [Bug 1832: `ntpdate` doesn't allow timeout > 2s](https://bugs.ntp.org/show_bug.cgi?id=1832)
* [Bug 1833: The checking `sem_timedwait()` fails without `-pthread`](https://bugs.ntp.org/show_bug.cgi?id=1833)
* [Bug 1087: `-v/--normalverbose` conflicts with `-v/--version` in `sntp`](https://bugs.ntp.org/show_bug.cgi?id=1087)
* [Bug 1088: `sntp` should (only) report the time difference without `-s/-a`](https://bugs.ntp.org/show_bug.cgi?id=1088)
* [Bug 1811: Update the download location in `WHERE-TO-START`](https://bugs.ntp.org/show_bug.cgi?id=1811)
* [Bug 1799: `ntpq mrv` crash](https://bugs.ntp.org/show_bug.cgi?id=1799)
* [Bug 1801: `ntpq mreadvar` requires prior association caching](https://bugs.ntp.org/show_bug.cgi?id=1801)
* [Bug 1797: Restore stale timestamp check from the `RANGEGATE` cleanup](https://bugs.ntp.org/show_bug.cgi?id=1797)
* [Bug 1794: `ntpq -c rv` missing `clk_wander` information](https://bugs.ntp.org/show_bug.cgi?id=1794)
* [Bug 1795: `ntpq readvar` does not display last variable](https://bugs.ntp.org/show_bug.cgi?id=1795)
* [Bug 1788: `tvtots.c` tables inaccurate](https://bugs.ntp.org/show_bug.cgi?id=1788)
* [Bug 1786: Remove extra semicolon from `ntp_proto.c`](https://bugs.ntp.org/show_bug.cgi?id=1786)
* [Bug 1780: Windows `ntpd` 4.2.7p114 crashes in `ioctl()`](https://bugs.ntp.org/show_bug.cgi?id=1780)
* [Bug 1781: `longlong` undefined in `sntp handle_pkt()` on Debian amd64](https://bugs.ntp.org/show_bug.cgi?id=1781)
* [Bug 1776: `sntp` mishandles `-t/--timeout` and `-a/--authentication`](https://bugs.ntp.org/show_bug.cgi?id=1776)
* [Bug 1773: openssl not detected during `./configure`](https://bugs.ntp.org/show_bug.cgi?id=1773)
* [Bug 1774: Segfaults if `cryptostats` enabled and built without OpenSSL](/support/securitynotice/ntpbug1774/)
* [Bug 1772: `refclock_open()` return value check wrong for ACTS](https://bugs.ntp.org/show_bug.cgi?id=1772)
* [Bug 1771: algorithmic error in `clocktime()` fixed](https://bugs.ntp.org/show_bug.cgi?id=1771)
* [Bug 1764: Move Palisade modem control logic to `configure.ac`](https://bugs.ntp.org/show_bug.cgi?id=1764)
  - Palisade driver doesn't build on Linux.
* [Bug 1768: `TIOCFLUSH` undefined in linux for `refclock_acts`](https://bugs.ntp.org/show_bug.cgi?id=1768)
* [Bug 1766: Oncore clock has offset/high jitter at startup](https://bugs.ntp.org/show_bug.cgi?id=1766)
* [Bug 1761: `clockstuff/clktest-opts.h` omitted from tarball](https://bugs.ntp.org/show_bug.cgi?id=1761)
* [Bug 1762: from 4.2.6p3-RC12: manycastclient responses interfere](https://bugs.ntp.org/show_bug.cgi?id=1762)
* [Bug 1458: from 4.2.6p3-RC12: Can not compile NTP on FreeBSD 4.7](https://bugs.ntp.org/show_bug.cgi?id=1458)
* [Bug 1760: from 4.2.6p3-RC12: `ntpd` Windows interpolation cannot be disabled](https://bugs.ntp.org/show_bug.cgi?id=1760)
* [Bug 1758: from 4.2.6p3-RC12: `setsockopt IPV6_MULTICAST_IF` with wrong `ifindex`](https://bugs.ntp.org/show_bug.cgi?id=1758)
* [Bug 1753: 4.2.7p94 faults on startup in `newpeer(), strdup(NULL)`](https://bugs.ntp.org/show_bug.cgi?id=1753)
* [Bug 1754: from 4.2.6p3-RC12: `--version` output should be more verbose](https://bugs.ntp.org/show_bug.cgi?id=1754)
* [Bug 1757: from 4.2.6p3-RC12: oncore `snprintf("%m")` doesn't expand `%m`](https://bugs.ntp.org/show_bug.cgi?id=1757)
* [Bug 1751: from 4.2.6p3-RC12: Support for Atari FreeMiNT OS](https://bugs.ntp.org/show_bug.cgi?id=1751)
* [Bug 1510: from 4.2.6p3-RC12: Add modes 20/21 for driver 8 to support RAWDCF @ 75 baud](https://bugs.ntp.org/show_bug.cgi?id=1510)
* [Bug 1741: from 4.2.6p3-RC12: Enable multicast reception on each address (Windows)](https://bugs.ntp.org/show_bug.cgi?id=1741)
* [Bug 1743: from 4.2.6p3-RC12: Display timezone offset when showing time for `sntp` in the local timezone](https://bugs.ntp.org/show_bug.cgi?id=1743)
* [Bug 1742: form 4.2.6p3-RC12: Fix a typo in an error message in the `build` script](https://bugs.ntp.org/show_bug.cgi?id=1742)
* [Bug 1738: Windows `ntpd` has wrong net adapter name](https://bugs.ntp.org/show_bug.cgi?id=1738)
* [Bug 1740: `ntpdc -c reslist` packet count wrongly treated as signed](https://bugs.ntp.org/show_bug.cgi?id=1740)
* [Bug 1736: `tos` int, bool options broken in 4.2.7p66](https://bugs.ntp.org/show_bug.cgi?id=1736)
* [Bug 1735: `clocktime()` aborts`ntp` on bogus input](https://bugs.ntp.org/show_bug.cgi?id=1735)
* [Bug 1618: Unreachable code in `jjy_start()`](https://bugs.ntp.org/show_bug.cgi?id=1618)
* [Bug 1725: from 4.2.6p3-RC11: `ntpd` sends multicast from only one address](https://bugs.ntp.org/show_bug.cgi?id=1725)
* [Bug 1727: `ntp-keygen PLEN, ILEN` undeclared `--without-crypto`](https://bugs.ntp.org/show_bug.cgi?id=1727)
* [Bug 1728: from 4.2.6p3-RC11: In `ntp_openssl.m4`, don't add `-I/usr/include` or `-L/usr/lib` to `CPPFLAGS` or `LDFLAGS`](https://bugs.ntp.org/show_bug.cgi?id=1728)
* [Bug 1681: `sntp` logging cleanup](https://bugs.ntp.org/show_bug.cgi?id=1681)
* [Bug 1683: from 4.2.6p3-RC10: Non-localhost on loopback exempted from nic rules](https://bugs.ntp.org/show_bug.cgi?id=1683)
  - from 4.2.6p3-RC9: Interface binding does not seem to work as intended.
* [Bug 1719: Cleanup for `ntp-keygen` and fix `-V` crash, from Dave Mills](https://bugs.ntp.org/show_bug.cgi?id=1719)
* [Bug 1574: from 4.2.6p3-RC9: `sntp` doesn't set `tv_usec` correctly](https://bugs.ntp.org/show_bug.cgi?id=1574)
* [Bug 1708: `make check` fails with googletest 1.4.0](https://bugs.ntp.org/show_bug.cgi?id=1708)
* [Bug 1709: from 4.2.6p3-RC9: `ntpdate` ignores replies with equal receive and transmit timestamps](https://bugs.ntp.org/show_bug.cgi?id=1709)
* [Bug 1715: `sntp utilitiesTest.IPv6Address` failed](https://bugs.ntp.org/show_bug.cgi?id=1715)
* [Bug 1718: Improve `gtest` checks in `configure.ac`](https://bugs.ntp.org/show_bug.cgi?id=1718)
* [Bug 1697: `filegen` implementation should be improved](https://bugs.ntp.org/show_bug.cgi?id=1697)
* [Bug 1692: `packageinfo.sh` needs to be "sourced" using `./`](https://bugs.ntp.org/show_bug.cgi?id=1692)
* [Bug 1695: `ntpdate` takes longer than necessary](https://bugs.ntp.org/show_bug.cgi?id=1695)
* [Bug 1690: Unit tests fails to build on some systems](https://bugs.ntp.org/show_bug.cgi?id=1690)
* [Bug 1691: Use first NMEA sentence each second](https://bugs.ntp.org/show_bug.cgi?id=1691)
* [Bug 1685: from 4.2.6p3-RC8: NMEA driver mode byte confusion](https://bugs.ntp.org/show_bug.cgi?id=1685)
* [Bug 1680: Fix alignment of `clock_select()` arrays](https://bugs.ntp.org/show_bug.cgi?id=1680)
* [Bug 1679: Fix test for `-lsocket`](https://bugs.ntp.org/show_bug.cgi?id=1679)
* [Bug 1676: from 4.2.6p3-RC7: NMEA: `$GPGLL` did not work after fix for Bug 1571](https://bugs.ntp.org/show_bug.cgi?id=1676)
* [Bug 1678: `restrict source` treated as `restrict default`](https://bugs.ntp.org/show_bug.cgi?id=1678)
* [Bug 1571: from 4.2.6p3-RC6: NMEA does not relate data to PPS edge](https://bugs.ntp.org/show_bug.cgi?id=1571)
* [Bug 1572: from 4.2.p63-RC6: NMEA time adjustment for `GPZDG` buggy](https://bugs.ntp.org/show_bug.cgi?id=1572)
* [Bug 1675: from 4.2.6p3-RC6: Prohibit `includefile` remote config](https://bugs.ntp.org/show_bug.cgi?id=1675)
* [Bug 1671: Automatic delay calibration is sometimes inaccurate](https://bugs.ntp.org/show_bug.cgi?id=1671)
* [Bug 1669: from 4.2.6p3-RC5: NTP fails to compile on IBM AIX 5.3](https://bugs.ntp.org/show_bug.cgi?id=1669)
* [Bug 1670: Fix peer->bias and broadcastdelay](https://bugs.ntp.org/show_bug.cgi?id=1670)
* [Bug 1649: from 4.2.6p3-RC5: Require NMEA checksum if `$GPRMC` or previously seen](https://bugs.ntp.org/show_bug.cgi?id=1649)
* [Bug 1277: Provide and use O(1) FIFOs, esp. in the config tree code](https://bugs.ntp.org/show_bug.cgi?id=1277)
* [Bug 1584: from 4.2.6p3-RC4: wrong SNMP type for precision, resolution](https://bugs.ntp.org/show_bug.cgi?id=1584)
  - from 4.2.6p3-RC3: `ntpsnmpd` OID must be mib-2.197.
* [Bug 1659: from 4.2.6p3-RC4: Need `CLOCK_TRUETIME` not `CLOCK_TRUE`](https://bugs.ntp.org/show_bug.cgi?id=16590)
  - from 4.2.6p3-RC3: Support Truetime Satellite Clocks on Windows.
* [Bug 1663: `ntpdsim` should not open net sockets](https://bugs.ntp.org/show_bug.cgi?id=1663)
* [Bug 1665: from 4.2.6p3-RC4: `is_anycast() u_int32_t` should be `u_int32`](https://bugs.ntp.org/show_bug.cgi?id=1665)
* [Bug 1080: from 4.2.6p3-RC3: `ntpd` on ipv6 routers very chatty](https://bugs.ntp.org/show_bug.cgi?id=1080)
* [Bug 750: from 4.2.6p3-RC3: Non-existing device causes coredump with RIPE-NCC driver](https://bugs.ntp.org/show_bug.cgi?id=750)
* [Bug 1567: from 4.2.6p3-RC3: Support Arbiter 1093C Satellite Clock on Windows](https://bugs.ntp.org/show_bug.cgi?id=1567)
* [Bug 1581: from 4.2.6p3-RC3: `printf` format string mismatch](https://bugs.ntp.org/show_bug.cgi?id=1581)
  - from 4.2.6p3-beta1: `ntp_intres.c size_t printf` format string mismatch.
  - from 4.2.6p2: IRIG string buffers undersized.
* [Bug 1660: from 4.2.6p3-RC3: On some systems, test is in `/usr/bin`, not `/bin`](https://bugs.ntp.org/show_bug.cgi?id=1660)
* [Bug 1661: from 4.2.6p3-RC3: Re-indent `refclock_ripencc.c`](https://bugs.ntp.org/show_bug.cgi?id=1661)
* [Bug 1657: darwin needs `res_9_init`, not `res_init`](https://bugs.ntp.org/show_bug.cgi?id=1657)
* [Bug 1554: peer may stay selected as system peer after becoming unreachable](https://bugs.ntp.org/show_bug.cgi?id=1554)
* [Bug 1644: from 4.2.6p3-RC3: `cvo.sh` should use `lsb_release` to identify linux distros](https://bugs.ntp.org/show_bug.cgi?id=1644)
* [Bug 1646: `ntpd` crashes with relative path to logfile](https://bugs.ntp.org/show_bug.cgi?id=1646)
* [Bug 1643: from 4.2.6p3-RC3: Range-check the decoding of the RIPE-NCC status codes](https://bugs.ntp.org/show_bug.cgi?id=1643)
* [Bug 1636: from 4.2.6p3-RC2: segfault after denied remote config](https://bugs.ntp.org/show_bug.cgi?id=1636)
* [Bug 1635: from 4.2.6p3-RC2: `filegen ... enable` is not default](https://bugs.ntp.org/show_bug.cgi?id=1635)
* [Bug 1344: from 4.2.6p3-RC1: `ntpd` on Windows exits without logging cause](https://bugs.ntp.org/show_bug.cgi?id=1344)
* [Bug 1629: 4.2.7p50 `configure.ac` changes invalidate `config.cache`](https://bugs.ntp.org/show_bug.cgi?id=1629)
* [Bug 1630: 4.2.7p50 cannot bootstrap on Autoconf 2.61](https://bugs.ntp.org/show_bug.cgi?id=1630)
* [Bug 1628: Clean up `-lxnet/-lsocket` usage for (open)solaris](https://bugs.ntp.org/show_bug.cgi?id=1628)
* [Bug 1588: finish `configure --disable-autokey` implementation](https://bugs.ntp.org/show_bug.cgi?id=1588)
* [Bug 1616: `refclock_acts.c`: `if (pp->leap == 2)` is always false](https://bugs.ntp.org/show_bug.cgi?id=1616)
* [Bug 1620: **Backward Incompatible** `discard minimum` value should be in seconds, not log2 seconds](https://bugs.ntp.org/show_bug.cgi?id=1620)
* [Bug 1578: Consistently use `-lm` when needed](https://bugs.ntp.org/show_bug.cgi?id=1578)
* [Bug 1573: from 4.2.6p3-beta1: Miscalculation of offset in `sntp`](https://bugs.ntp.org/show_bug.cgi?id=1573)
* [Bug 1602: Refactor some of the `sntp/` directory to facililtate testing](https://bugs.ntp.org/show_bug.cgi?id=1602)
* [Bug 1593: `ntpd` abort in `free()` with `logconfig` syntax error](/support/securitynotice/ntpbug1593/)
* [Bug 1595: from 4.2.6p3-beta1: empty last line in key file causes duplicate key to be added](https://bugs.ntp.org/show_bug.cgi?id=1595)
* [Bug 1597: from 4.2.6p3-beta1: packet processing ignores `RATE` KoD packets, because of a bug in string comparison](https://bugs.ntp.org/show_bug.cgi?id=1597)
* [Bug 1586: `ntpd` 4.2.7p40 doesn't write to `syslog` after fork on QNX](https://bugs.ntp.org/show_bug.cgi?id=1586)
* [Bug 1395: ease `ntpdate` elimination with `ntpd -w/--wait-sync`](https://bugs.ntp.org/show_bug.cgi?id=1395)
* [Bug 1396: allow servers on `ntpd` command line like `ntpdate`](https://bugs.ntp.org/show_bug.cgi?id=1396)
* [Bug 1570: serial clock drivers get outdated input from kernel tty line buffer after startup](https://bugs.ntp.org/show_bug.cgi?id=1570)
* [Bug 1575: from 4.2.6p2-RC7: use `snprintf` with `LIB_BUFLENGTH` in `inttoa.c, tvtoa.c` and `utvtoa.c`](https://bugs.ntp.org/show_bug.cgi?id=1575)
* [Bug 1576: `sys/sysctl.h` depends on `sys/param.h` on OpenBSD](https://bugs.ntp.org/show_bug.cgi?id=1576)
* [Bug 1560: Initial support for orphanwait, from Dave Mills](https://bugs.ntp.org/show_bug.cgi?id=1560)
* [Bug 715: from 4.2.6p2-RC6: `libisc` Linux IPv6 interface iteration drops multicast flags](https://bugs.ntp.org/show_bug.cgi?id=715)
* [Bug 1561: from 4.2.6p2-RC5: `ntpq, ntpdc passwd` prompts for MD5 password w/SHA1](https://bugs.ntp.org/show_bug.cgi?id=1561)
* [Bug 1565: from 4.2.6p2-RC5: `sntp/crypto.c` compile fails on MacOS over `vsnprintf()`](https://bugs.ntp.org/show_bug.cgi?id=1565)
* [Bug 1555: from 4.2.6p2-RC4: `sntp` illegal C (mixed code and declarations)](https://bugs.ntp.org/show_bug.cgi?id=1555)
* [Bug 1558: pool prototype associations have 0.0.0.0 for remote addr](https://bugs.ntp.org/show_bug.cgi?id=1558)
* [Bug 1325: from 4.2.6p2-RC3: unreachable code `sntp recv_bcst_data()`](https://bugs.ntp.org/show_bug.cgi?id=1325)
* [Bug 1459: from 4.2.6p2-RC3: `sntp` MD5 authentication does not work with `ntpd`](https://bugs.ntp.org/show_bug.cgi?id=1459)
* [Bug 1552: from 4.2.6p2-RC3: update and complete broadcast and crypto features in `sntp`](https://bugs.ntp.org/show_bug.cgi?id=1552)
* [Bug 1553: from 4.2.6p2-RC3: `sntp/configure.ac` OpenSSL support](https://bugs.ntp.org/show_bug.cgi?id=1553)
* [Bug 1526: `ntpd` DNS pipe read EINTR with no network at startup](https://bugs.ntp.org/show_bug.cgi?id=1526)
* [Bug 1542: `ntpd mrulist` response may have incorrect `last.older`](https://bugs.ntp.org/show_bug.cgi?id=1542)
* [Bug 1543: `ntpq mrulist` must refresh nonce when retrying](https://bugs.ntp.org/show_bug.cgi?id=1543)
* [Bug 1544: `ntpq mrulist sscanf` timestamp format mismatch on 64-bit](https://bugs.ntp.org/show_bug.cgi?id=1544)
* [Bug 1512: from 4.2.6p2-RC3: `ntpsnmpd` should connect to `net-snmpd` via a unix-domain socket by default](https://bugs.ntp.org/show_bug.cgi?id=1512)
  - Provide a command-line `socket name` option.
* [Bug 1538: from 4.2.6p2-RC3: update `refclock_nmea.c`'s call to `getprotobyname()`](https://bugs.ntp.org/show_bug.cgi?id=1538)
* [Bug 1541: from 4.2.6p2-RC3: Fix wrong keyword for `maxclock`](https://bugs.ntp.org/show_bug.cgi?id=1541)
* [Bug 1465: Make sure time from TS2100 is not invalid](https://bugs.ntp.org/show_bug.cgi?id=1465)
* [Bug 1528: from 4.2.6p2-RC2: Fix `EDITLINE_LIBS` link order for `ntpq` and `ntpdc`.](https://bugs.ntp.org/show_bug.cgi?id=1528)
  - from 4.2.6p2-RC2: Remove `--with-arlib` from `br-flock`.
* [Bug 1531: Require nonce with `mrulist` requests](https://bugs.ntp.org/show_bug.cgi?id=1531)
* [Bug 1532: Remove `ntpd` support for `ntpdc`'s `monlist` in favor of `ntpq`'s `mrulist`](https://bugs.ntp.org/show_bug.cgi?id=1532)
* [Bug 1534: from 4.2.6p2-RC2: conflicts with VC++ 2010 `errno.h`](https://bugs.ntp.org/show_bug.cgi?id=1534)
* [Bug 1535: from 4.2.6p2-RC2: `restrict -4 default` and `restrict -6 default` ignored](https://bugs.ntp.org/show_bug.cgi?id=1535)
* [Bug 1390: Control PPS on the Oncore M12](https://bugs.ntp.org/show_bug.cgi?id=1390)
* [Bug 1518: Windows `ntpd` should lock to one processor more conservatively](https://bugs.ntp.org/show_bug.cgi?id=1518)
* [Bug 1520: `%u` formats for `size_t` gives warnings with 64-bit builds](https://bugs.ntp.org/show_bug.cgi?id=1520)
* [Bug 1522: Enable range syntax `trustedkey (301 ... 399)`](https://bugs.ntp.org/show_bug.cgi?id=1522)
* [Bug 1516: unpeer by IP address fails, DNS name works](https://bugs.ntp.org/show_bug.cgi?id=1516)
* [Bug 1517: `ntpq` and `ntpdc` should verify reverse DNS before use](https://bugs.ntp.org/show_bug.cgi?id=1517)
  - `ntpq` and `ntpdc` now use the following format for showing purported DNS names from IP address "reverse" DNS lookups when the DNS name does not exist or does not include the original IP address among the results: `192.168.1.2 (fake.dns.local)`.
* [Bug 1432: Don't set inheritable flag for linux capabilities](https://bugs.ntp.org/show_bug.cgi?id=1432)
* [Bug 1483: `AI_NUMERICSERV` undefined in 4.2.7p20](https://bugs.ntp.org/show_bug.cgi?id=1483)
  - hostname in `ntp.conf restrict` parameter rejected.
* [Bug 1497: `fudge` is broken by `getnetnum()` change](https://bugs.ntp.org/show_bug.cgi?id=1497)
* [Bug 1503: Auto-enabling of monitor for `restrict ... limited` wrong](https://bugs.ntp.org/show_bug.cgi?id=1503)
* [Bug 1504: `ntpdate` tickles `ntpd discard minimum 1` rate limit if `restrict ... limited` is used](https://bugs.ntp.org/show_bug.cgi?id=1504)
* [Bug 2399: Reset `sys_kodsent` in `proto_clr_stats()`](https://bugs.ntp.org/show_bug.cgi?id=2399)
* [Bug 1514: from 4.2.6p1-RC6: Typo in `ntp_proto.c`: fabs(foo < .4) should be fabs(foo) < .4](https://bugs.ntp.org/show_bug.cgi?id=1514)
* [Bug 1464: from 4.2.6p1-RC6: synchronization source wrong for refclocks ARCRON_MSF (27) and SHM (28)](https://bugs.ntp.org/show_bug.cgi?id=1464)
* [Bug 1306: constant conditionals in `audio_gain()`](https://bugs.ntp.org/show_bug.cgi?id=1306)
* [Bug 1338: Update the association type codes in ntpq.html](https://bugs.ntp.org/show_bug.cgi?id=1338)
  - `ntpq` displays incorrect association type codes.
* [Bug 1478: from 4.2.6p1-RC5: linking fails: `EVP_MD_pkey_type`](https://bugs.ntp.org/show_bug.cgi?id=1478)
* [Bug 1479: from 4.2.6p1-RC5: not finding readline headers](https://bugs.ntp.org/show_bug.cgi?id=1479)
* [Bug 1484: from 4.2.6p1-RC5: `ushort` is not defined in QNX6](https://bugs.ntp.org/show_bug.cgi?id=1484)
* [Bug 1480: from 4.2.6p1-RC5: `snprintf()` cleanup caused unterminated refclock IDs](https://bugs.ntp.org/show_bug.cgi?id=1480)
* [Bug 1477: from 4.2.6p1-RC5: First non-gmake `make` in clone w/VPATH can't make COPYRIGHT](https://bugs.ntp.org/show_bug.cgi?id=1477)
* [Bug 1474: from 4.2.6p1-RC4: `ntp_keygen LCRYPTO` after `libntp.a`](https://bugs.ntp.org/show_bug.cgi?id=1474)
* [Bug 1455: from 4.2.6p1: `ntpd` does not try `/etc/ntp.audio`](https://bugs.ntp.org/show_bug.cgi?id=1455)
* [Bug 1469: `u_int32, int32` changes broke HP-UX 10.20 build](https://bugs.ntp.org/show_bug.cgi?id=1469)
* [Bug 1470: from 4.2.6p1: `make distdir` compiles `keyword-gen`](https://bugs.ntp.org/show_bug.cgi?id=1470)
* [Bug 1471: CID 120 CID 121 CID 122 `is_ip_address() uninit` family](https://bugs.ntp.org/show_bug.cgi?id=1471)
* [Bug 1472: CID 116 CID 117 minor warnings in new DNS code](https://bugs.ntp.org/show_bug.cgi?id=1472)
* [Bug 1473: from 4.2.6p1: `make distcheck version.m4` error](https://bugs.ntp.org/show_bug.cgi?id=1473)
* [Bug 1467: from 4.2.6p1: Fix bogus rebuild of `sntp/sntp.html`](https://bugs.ntp.org/show_bug.cgi?id=1467)
* [Bug 1468: `make install` broken for root on default NFS mount](https://bugs.ntp.org/show_bug.cgi?id=1468)
* [Bug 47: Debugging and logging do not work after a fork](https://bugs.ntp.org/show_bug.cgi?id=47)
* [Bug 1010: `getaddrinfo()` could block and thus should not be called by the main thread/process](https://bugs.ntp.org/show_bug.cgi?id=1010)
* [Bug 1140: from 4.2.6p1-RC5: Clean up debug.html, decode.html, and ntpq.html](https://bugs.ntp.org/show_bug.cgi?id=1140)
* [Bug 1448: from 4.2.6p1-RC3: Some macros not correctly conditionally or absolutely defined on Windows](https://bugs.ntp.org/show_bug.cgi?id=1448)
* [Bug 1449: from 4.2.6p1-RC3: `ntpsim.h` in `ntp_config.c` should be used conditionally](https://bugs.ntp.org/show_bug.cgi?id=1449)
* [Bug 1450: from 4.2.6p1-RC3: Option to exclude warnings not unconditionally defined on Windows](https://bugs.ntp.org/show_bug.cgi?id=1450)
* [Bug 702: `ntpd` service logic should use `libopts` to examine `cmdline`](https://bugs.ntp.org/show_bug.cgi?id=702)
* [Bug 1451: from 4.2.6p1-RC3: `sntp` leaks KoD entry updating](https://bugs.ntp.org/show_bug.cgi?id=1451)
* [Bug 1453: from 4.2.6p1-RC3: Use `$CC` in `config.cache` filename](https://bugs.ntp.org/show_bug.cgi?id=1453)
* [Bug 620: `ntpdc getresponse() esize != *rsize s/b size != *rsize`](https://bugs.ntp.org/show_bug.cgi?id=620)
* [Bug 1446: 4.2.7p6 requires `autogen`, missing `ntpd.1, *.texi, *.menu`](https://bugs.ntp.org/show_bug.cgi?id=1446)
* [Bug 1443: Remove unnecessary dependencies on `ntp_io.h`](https://bugs.ntp.org/show_bug.cgi?id=1443)
* [Bug 1442: Move Windows functions into `libntp` files](https://bugs.ntp.org/show_bug.cgi?id=1442)
* [Bug 1127: from 4.2.6p1-RC3: Check the return of `X590_verify()`](https://bugs.ntp.org/show_bug.cgi?id=1127)
* [Bug 1439: from 4.2.6p1-RC3: `.texi` gen after binary is linked](https://bugs.ntp.org/show_bug.cgi?id=1439)
* [Bug 1440: from 4.2.6p1-RC3: Update `configure.ac` to support `kfreebsd`](https://bugs.ntp.org/show_bug.cgi?id=1440)
* [Bug 1445: from 4.2.6p1-RC3: IRIX does not have `-lcap` or support linux capabilities](https://bugs.ntp.org/show_bug.cgi?id=1445)
* [Bug 1429: `ntpd -4` option does not reliably force IPv4 resolution](https://bugs.ntp.org/show_bug.cgi?id=1429)
* [Bug 1431: System headers must come before ntp headers in `ntp_intres.c`](https://bugs.ntp.org/show_bug.cgi?id=1431)
* [Bug 1426: `scripts/VersionName` needs `.` on the search path](https://bugs.ntp.org/show_bug.cgi?id=1426)
* [Bug 1427: quote missing in `./build` - shows up on NetBSD](https://bugs.ntp.org/show_bug.cgi?id=1427)
* [Bug 1428: Use `AC_HEADER_RESOLV` to fix breaks from `resolv.h`](https://bugs.ntp.org/show_bug.cgi?id=1428)
* [Bug 1419: `ntpdate, ntpdc, sntp, ntpd` ignore `configure --bindir`](https://bugs.ntp.org/show_bug.cgi?id=1419)
* [Bug 1421: add `util/tg2`, a clone of `tg` that works on Linux, NetBSD, and FreeBSD](https://bugs.ntp.org/show_bug.cgi?id=1421)
* [Bug 1348: `ntpd` Windows port should wait for `sendto()` completion](https://bugs.ntp.org/show_bug.cgi?id=1348)
* [Bug 1413: test OpenSSL headers regarding `-Wno-strict-prototypes`](https://bugs.ntp.org/show_bug.cgi?id=1413)
* [Bug 1418: building `ntpd/ntpdc/ntpq` statically with ssl fails](https://bugs.ntp.org/show_bug.cgi?id=1418)
* [Bug 1412: `m4/os_cflags.m4` caches results that depend on `$CC`](https://bugs.ntp.org/show_bug.cgi?id=1412)
* [Bug 1414: Enable `make distcheck` success with BSD make](https://bugs.ntp.org/show_bug.cgi?id=1414)
* [Bug 1407: `configure.ac`: recent GNU Make `-v` does not include `version`](https://bugs.ntp.org/show_bug.cgi?id=1407)

* * *

* Updates from [4.2.6p5](/support/securitynotice/4_2_6-series-changelog/#426p5).
* Sync with [ntp-4.2.6p4](/support/securitynotice/4_2_6-series-changelog/#426p4) (a no-op).
* Sync with [4.2.6p4-RC2](/support/securitynotice/4_2_6-series-changelog/#426p4-rc2).
* Include [4.2.6p1-RC4](/support/securitynotice/4_2_6-series-changelog/#426p1-rc4): Remove `arlib`.
* Include [4.2.6p1-RC2](/support/securitynotice/4_2_6-series-changelog/#426p1-rc2)

* * *

**Docs**

* `html/` updates from Dave Mills.
* html doc reconciliation with DLM's copy.
* `html/` cleanups from Hal Murray.
* Documentation cleanup from Mike T.
* Documentation EOL cleanup.
* Documentation nit cleanup.
* Documentation and code cleanup from Dave Mills. No more `NTP_MAXASSOC`.
* Make all of the `html/ .html` files use the same format for "Last update".
* Clean up last-update timestamps of `html/*.html` files.
* Fix the "Last update" entries in the `html/` subtree.
* Tweak the "Modified" line on appropriate html pages.
* Update documentation templates and definitions.
* Include missing `html/icons/sitemap.png`, reported by Michael Tatarinov.
* Documentation updates for 4.2.7p22 changes and additions, updating `ntpdc.html, ntpq.html, accopt.html, confopt.html, manyopt.html, miscopt.html`, and `miscopt.txt`.
* `accopt.html`: non-ntpport doc changes from Dave Mills.
* Reinstate doc fix to `authentic.html` from Mike T.
* Copyright file cleanup from Dave Mills.
* Fix typo in `html/confopt.html`
* Fix typos in `decode.html` and `debug.html`.
* Updates to `driver28.html`.
* Fix typo in `driver28.html`.
* Update `driver45.html` page.
* Initial cut at a basic `driver45.html` page.
* `ntp-wait, ntpd, ntpdc, ntpq, ntpsnmpd autogen` documentation updates.
* Add a reference to RFC 5907 in the `ntpsnmpd `documentation.
* `orphanwait` documentation updates.
* Fix typo in `html/select.html`.
* `sntp` documentation and documentation tag cleanup.
* `calc_tickadj/Makefile.am man/mdoc` page build cleanup.
* Fix the man page installation for the ``scripts/ files.
* Clean the `man5_MANS` in `ntpd/`.
* Prepare for `ntp.keys.5`.
* More `sntp.1` cleanups.
* Fix `mdoc2man`.
* `mdoc2man` improvements.
* Use patched `mdoc2man` script, from Eric Feng.
* Refactor and enhance `mdoc2texi`.
* `mdoc2texi` fixes: trailing punctuation.
* `mdoc2texi` fixes: `parseQuote`, closing of list item tables.
* `mdoc2texi` fixes: `Handle_ArCmFlIc, Handle_Fn, HandleQ`.
* from 4.2.6p3: Create and use `scripts/check--help` when generating `.texi` files.
* Autogen documentation cleanup.
* Require a version string for `perl` scripts that use `autogen`.
* Update several `.def` files to use autogen-5.17 feature set.
* Begin support for `autogen` maintaining `ntp.conf` and `ntp.keys` docs.
* Use `autogen` to produce `ntp-keygen` docs.
* Update the `autogen` include list for `scripts/Makefile.am`.
* Update `ntp-wait autogen` docs.
* Update the `ntpd autogen` docs.
* Update the `ntpsnmpd autogen` docs.
* Add "license name` to `ntp.lic` for autogen-5.11.10.
* Update `cmd-doc.tlib` to autogen-5.11.10pre5.
* `cmd-doc.tlib` cleanup from Bruce Korb.
* Use the latest `autogen`'s new copyright template code.
* `autogen` documentation template cleanup.
* If we have local overrides for `autogen` template files, use them.
* Convert `snmp` docs to `mdoc` format, which requires `autogen` 5.11.9.
* 4.2.7p164 documentation updates re: `tos orphanwait` expanded scope.

* * *

**Builds**

* Upgrade to autogen-5.18.5pre1
* from 4.2.6p3-RC11: Bump minimum Automake version to 1.11, required for `AM_COND_IF` use in `LIBOPTS_CHECK`.
* Automake-1.12 wants us to use `AM_PROG_AR`.
* Use a single set of Automake options for each package in `configure.ac AM_INIT`, remove `Makefile.am AUTOMAKE_OPTIONS=` lines.
* Enable all relevant `automake` warnings.
* from 4.2.6p3-RC12: Relax minimum Automake version to 1.10 with updated `libopts.m4`.
* Try bison-3.0.2 instead of bison-2.5.
* Upgrade to libevent-2.1.3-alpha-dev.
* Correct `event_base_gettimeofday_cached()` workaround code in `sntp` to work with corrected `libevent`.
* Allow for version suffix in `libevent` in `ntp_libevent.m4`.
* Fix `make distcheck` with `--enable-libevent-regress` problem with unwritable `$srcdir`.
* Don't build `libevent` with openssl support.  Right now, `libevent` doesn't use `pkg-config` to find openssl's installation location.
* Add missing `--enable-local-libevent` help to top-level configure.
* Update `libevent --disable-libevent-regress` handling to work when building `libevent` using `mingw`.
* Fix `make distcheck` break in `libevent/sample` caused by typo.
* `libevent`: When building on systems with `CLOCK_MONOTONIC` available, separate the internal timeline (possibly counting since system boot) from the `gettimeofday()` timeline in `event_base` cached timevals.  Adds new `event_base_tv_cached()` to retrieve cached callback round start time on the internal timeline, and changes `event_based_gettimeofday_cached()` to always return times using the namesake timeline.  This preserves the benefit of using the never-stepped monotonic clock for event timeouts while providing clients with times consistently using `gettimeofday()`.
* Update to libopts-40.2.15.
* From 4.2.6p4: `libopts/file.c` fix from Bruce Korb (`arg-type=file`).
* Move `m4` directory to `sntp/m4`.
* Share a single set of `genver` output between `sntp` and the top level.
* Share a single set of `autogen` included `.defs` in `sntp/include`.
* Share a single set of `build-aux` scripts (e.g. `config.guess, missing`).
* Add `ntp_libntp.m4` and `ntp_ipv6.m4` to reduce `configure.ac` duplication.
* Warn and exit `build/flock-build` if bootstrap needs to be run.
* Update the building of OS-specific programs.
* Add `--enable-c99-sprintf` to configure args for `-noopenssl` variety of `flock-build` to avoid regressions in `(v)snprintf()` replacement.
* Add `--disable-thread-support` to one `flock-build` variation.
* Avoid invoking `config.status` twice in a row in build script.
* Correct `msyslog.c` build break on Solaris 2.9 from `#ifdef/#if` mixup.
* Correct `./build` on systems without `gtest` available.
* Use `make V=0` in build script to increase signal/noise ratio.
* Avoid race with parallel builds using same source directory in `scripts/genver` by using build directory for temporary files.
* From 4.2.6p1-RC6: Correct `SIMUL=4 ./flock-build -1` to prioritize `-1/--one`.
* Fix warnings seen on FreeBSD 9.
* Fix check for `-lipv6` on HP-UX 11.
* Fix for openssl `pkg-config` detection eval failure.
* `make V=0` and `configure --enable-silent-rules` supported.
* Default to silent `make` rules, override with `make V=1` or `./configure --disable-silent-rules`.
* Correct `--with-openssl-incdir` defaulting with `pkg-config`.
* Default `--with-openssl-libdir` and `--with-openssl-incdir` to the values from `pkg-config`, falling back on our usual search paths if `pkg-config` is not available or does not have `openssl.pc` on `PKG_CONFIG_PATH`.
* Avoid overwriting user variable `LDFLAGS` with OpenSSL flags, instead they are added to `LDFLAGS_NTP`.
* Cleanup to the new `scripts/*/Makefile.am` files.
* Fix the `check-scm-rev` invocation in several `Makefile.am`s.
* Incorporate Oliver Kindernay's GSoC 2013 `scripts/` cleanup.
* from 4.2.6p3-RC8: First cut at using `scripts/checkChangeLog`.
* from 4.2.6p3-RC7: Added `scripts/checkChangeLog`.
* More cleanup to the bootstrap script.
* Handle additional man page sections in the bootstrap script.
* For the bootstrap script, touch `.html` files last.
* Add `make check` test case that would have caught [Bug 1678](https://bugs.ntp.org/show_bug.cgi?id=1678).
* A number of compiler warnings eliminated.
* FlexeLint cleanups.
* Remove extra `nlist` check from `configure.ac`.
* Clean up `configure.ac`.
* Cleanup `configure.ac`'s `TSYNC PCI` section.
* from 4.2.6p3-RC12: Clean up `m4` quoting in `configure.ac, *.m4` files, resolving intermittent `AC_LANG_PROGRAM` possibly undefined errors.
* Clean up missing `;;` entries in `configure.ac`.
* `configure.ac`: add `--disable-autokey, #define AUTOKEY` to enable future support for building without Autokey, but with OpenSSL for its digest
  algorithms (hash functions).  Code must be modified to use `#ifdef AUTOKEY` instead of `#ifdef OPENSSL` where appropriate to complete this.

* * *

**sntp**
* Improve `sntp` KoD data file `fopen()` error message.
* Fix `ntpsweep` to use `sntp` instead of `ntpdate`, from Oliver Kindernay.
* Bump `sntp/include/autogen-version.def`.
* `EEXIST` is OK for `mkdir()` in `sntp/kod_management.c`.
* Document a tricky `malloc()` of `dns_ctx` in `sntp`.
* Clean up testing/debugging of fix for [Bug 938](https://bugs.ntp.org/show_bug.cgi?id=938) from `sntp/main.c`.
* In `sntp/m4/ntp_openssl.m4`, Support multiple package names for the crypto library.  Add legacy support for `-Wl,-rpath`.
* Change the link order for `ntpsntpd`.
* Update `sntp` tests to track the change of root dispersion to synchronization distance.
* Restore the original `CLOCK_MONOTONIC` output format in `sntp`.
* `sntp` documentation and behavior improvements suggested by Steven Sommars.
* Have `sntp` report synchronization distance instead of root dispersion.
* `sntp`: change `-h/--headspace` to `-g/--gap`, and change the default gap from 10 to 50ms
* **Backward Incompatible** from 4.2.6p4: `sntp: -l/--filelog` -> `-l/--logfile`, to be consistent with `ntpd`.
* remove old `binsubdir` stuff from SNTP, as `NTP_LOCINFO` does that now.
* Fix warnings in `ntp_request.c` [Bug 1973](https://bugs.ntp.org/show_bug.cgi?id=1973) oversight and `sntp/main.c`.
  - (CID 159, apparent overrun due to union, actually correct).
* Rename file containing 1.xxxx ChangeSet revision from version to scm-rev to avoid invoking GNU make implicit rules attempting to compile `version.c` into version.  Problem was with `sntp/version.o` during `make distcheck` after fix for spurious `sntp` rebuilds.
* Move `sntp` last in top-level `Makefile.am SUBDIRS` so that the `libevent` tearoff (if required) and `sntp` are compiled after the rest.
* Correct spurious `sntp` rebuilds triggered by a `make` misperception `sntp/version` was out-of-date relative to phony target `FRC.version`.
* Remove `libevent-cfg` from `sntp/Makefile.am`.
* Avoid relying on remake rules for routine `build/flock-build` for `libevent` as for the top-level and `sntp` subproject.
* Move "can't write KoD file" warning from `sntp` shutdown to startup.
* Convert `sntp` to `libevent` event-driven socket programming.  Instead of blocking name resolution and querying one NTP server at a time, resolve server names and send NTP queries without blocking.  Add `sntp` command-line options to adjust timing and optionally wait for all servers to respond instead of exiting after the first.
* Move `init_logging(), change_logfile()`, and `setup_logfile()` from `ntpd` to `libntp`, use them in `sntp`.
* Test `--without-sntp` in `flock-build` script's `-no-refclocks` variety.
* `sntp/Makefile.am` needs any passed-in `CFLAGS`.
* Simplify the built-sources stuff in `sntp/`.
* Add `configure --without-sntp` option to disable building `sntp` and `sntp/tests`.  `withsntp=no` in the environment changes the default.
* Remove top-level `libopts`, use `sntp/libopts`.
* from 4.2.6p3-RC11: Remove `log_msg()` and `debug_msg()` from `sntp` in favor of `msyslog()`.
* Put the `sntp` tests under `sntp/` ... and only build/run them if we have `gtest`.
* from 4.2.6p2-RC3: Do not depend on ASCII in `sntp`.
* Move `sntp/include/mansec2subst.sed` to `sntp/scripts/mansec2subst.sed`.
* Convert more of the `sntp-opt.def` documentation from `man` to `mdoc`.
* Share a single `sntp/libevent/build-aux` directory between all three `configure` scripts.
* Finish conversion to `genLocInfo`.
* validate `MANTAGFMT` in `genLocInfo`.
* `ntp_locs.m4`: handle the case where . is not in the `PATH`.
* More `genLocInfo` improvements and cleanup.
* Added `ntp_locs.m4`.
* Add the man page tag "flavor" to the `loc.*` files.
* Add/distribute `genLocInfo`.
* Create `loc/darwin` for Mac OSX.
* Added `loc/debian`.
* Added `loc.freebsd` (and distribute it).
* Added `loc.legacy` (and distribute it).
* Added `loc/redhat`.
* Added `loc/solaris`.
* Move `loc/` to `sntp/loc/`.
* Added `sntp/loc/netbsd` based on info from Christos Zoulas.
* Update `sntp/loc/solaris` to conform to stock locations.
* If no "more specific" `loc` file is found for redhat* or fedora*, look for a `loc/redhat` file.
* If no "more specific" `loc` file is found and `uname` says this is Linux, look for a `loc/linux` file.
* Implement `--with-locfile=filename configure` argument.  If filename is empty we'll look under `loc/` for a good fit.  If the filename contains a `/` character, it will be treated as a "normal" pathname.  Otherwise, that explicit file will be searched for under `loc/`.
* Removed `sntp/m4/ntp_bindir.m4` - no longer needed.
* Move `scripts/cvo.sh` to `sntp/scripts/cvo.sh`.
* Move `scripts/genLocInfo` to `sntp/scripts/genLocInfo`.
* Remove hacks to get `NTP_LOCINFO`-related data to `sntp/`.
* Remove `sntp l_fp_output()` test now that it uses `prettydate()`.
* Do not force "legacy" when `--with-locfile` is not given, `genLocInfo` will find the correct default for the system.
* **DEFAULT INSTALLATION DIRECTORY CHANGES ON SOME OSes:** to get the old behavior, pass `--with-locfile=legacy` to `configure`
* Give `NTP_LOCINFO` an optional `path-to` argument.
* Improve the help text: `--with-locfile=XXX`.
* work around solaris `/bin/sh` issues for `genLocInfo`.

* * *

**refclocks**

* `refclock_acts.c` updates and cleanup from Dave Mills.
* Move refclock-specific scheduled timer code under `#ifdef REFCLOCK` and move "action" and "nextaction" data for same from struct `peer` to
  struct `refclockproc`.  These provide a way to schedule a callback some seconds in the future.
* ACTS refclock cleanup from Dave Mills.
* Use an enum for the ACTS state table.
* Apply `tos orphanwait` (def. 300 seconds) to LOCAL and ACTS reference clock drivers, in addition to orphan parent operation.  LOCAL and ACTS are not selectable during the `orphanwait` delay at startup and after each `no_sys_peer` event.  This prevents a particular form of clock-hopping, such as using LOCAL briefly at startup before remote peers are selectable.  This fixes the issue reported in [Bug 988](https://bugs.ntp.org/show_bug.cgi?id=988).
* `setvar modemsetup = ATE0...` overrides ACTS driver default.
* Preserve last timecode in ACTS driver (`ntpq -ccv`).
* Tolerate previous ATE1 state when sending ACTS setup.
* Enable ACTS and CHU reference clock drivers on Windows.
* Use `acts_close()` in `acts_shutdown()` to avoid leaving a stale lockfile if unpeered via runtime configuration while the modem is open.
* Correct `acts_close()` test of pp->io.fd to see if it is open.
* `refclock_nmea.c` merge cleanup thanks to Juergen Perlinger.
* `refclock_nmea.c` refactoring by Juergen Perlinger.
* Conditionalize NMEA serial open message under `clockevent`.
* Change some error logging to `syslog` to ignore `logconfig` mask, such as reporting PPSAPI failure in NMEA and WWVB refclocks.
* Added support for Garmin's `$PGRMF` sentence to NMEA driver.
* NMEA driver documentation update from Juergen Perlinger.
* From 4.2.6p1-RC6: Correct CHU, dumbclock, and WWVB drivers to check for 0 returned from `refclock_open()` on failure.
* Initialize `refclockproc.rio.fd` to -1, harmonize refclock shutdown entrypoints to avoid crashing, particularly if `refclock_open()` fails.
* Include 4.2.6p1: Fix widely cut-n-pasted bug in refclock shutdown after failed start.
* In `refclock_wwv.c` rename `SECOND` to `WWV_SEC` and `MINUTE` to `WWV_MIN`.
* Attempt to resolve strict-aliasing violation in `refclock_tsyncpci.c`.
* Add `refclock_tsyncpci.c` (driver 45) supporting Spectracom TSYNC timing boards.
* Fix && -> & typo in `refclock_palisade.c` debug statements.
* Log failure to fetch time from HOPF_P hardware.
* Check `HOPF_S sscanf()` conversion count before converted values.
* JJY driver improvements for Tristate JJY01/02, including changes to its clockstats format.
* Remove never-used, incomplete `ports/winnt/ntpd/refclock_trimbledc`.[ch]
* Remove kernel line discipline driver code for clk and chu, deprecate related `LDISC_ flags`, and remove associated `ntpd` code to decode the timestamps, remove `clktest` line discipline test program.
* Compare entire timestamp to reject duplicates in `refclock_pps()`.
* Change `refclock_open()` to return -1 on failure like `open()`.
* Update all `refclock_open()` callers to check for fd <= 0 indicating failure, so they work with older and newer `refclock_open()` and can easily backport.

* * *

**ntpq**

* Add `ntpq reslist` command to query access restrictions, similar to `ntpdc`'s `reslist`.
* Disable mode 7 (`ntpdc`) query processing in `ntpd` by default.  `ntpq` is believed to provide all functionality `ntpdc` did, and uses a less-fragile protocol that's safer and easier to maintain.  If you do find some management via `ntpdc` is needed, you can use `enable mode7` in the `ntpd` configuration.
* `ntpq mrulist` shows intermediate counts every five seconds while retrieving list, and allows <kbd>Ctrl-C</kbd> interruption of the retrieval, showing the incomplete list as retrieved.  Reduce delay between successive mrulist retrieval queries from 30 to 5 msec.  Do not give up mrulist retrieval when a single query times out.
* Add missing `break;` to `ntp_control.c ctl_putsys()` for caliberrs, used by `ntpq -c kerninfo` introduced in 4.2.7p104.
* Move `ntp_control.h` variable IDs to `ntp_control.c`, remove their use by `ntpq`.  They are implementation details private to `ntpd`.  [Bug 597](https://bugs.ntp.org/show_bug.cgi?id=597) was caused by `ntpq`'s reliance on these IDs it need not know about.
* Add `ntpq kerninfo, authinfo`, and `sysinfo` commands similar to `ntpdc`'s.
* Add `ntpq pstats` command similar to `ntpdc`'s.
* Remove `ntpq pstatus` command, `rv/readvar` does the same and more.
* Allow `ntpq &1 associd` use without preceding association-fetching.
* from 4.2.6p2-RC3: Escape unprintable characters in a refid in `ntpq -p` billboard.
* Add `ntpq -c iostats` similar to `ntpdc -c iostats`.
* Add `ntpq -c ifstats` similar to `ntpdc -c ifstats`.
* Add `ntpq -c sysstats` similar to `ntpdc -c sysstats`.
* Add `ntpq -c monstats` to show `monlist` knobs and stats.
* Add `ntpq -c mrulist` similar to `ntpdc -c monlist` but not limited to 600 rows, and with filtering and sorting options:
  - `ntpq -c "mrulist mincount=2 laddr=192.168.1.2 sort=-avgint"`
  - `ntpq -c "mrulist sort=addr"`
  - `ntpq -c "mrulist mincount=2 sort=count"`
  - `ntpq -c "mrulist sort=-lstint"`
* `ntpq`: increase response reassembly limit from 24 to 32 packets, add discussion in comment regarding results with even larger `MAXFRAGS`.
* `ntpq`: handle `passwd MYPASSWORD` (without prompting) as with `ntpdc`.
* Extend `ntpq readvar` (alias `rv`) to allow fetching up to three named variables in one operation:  `ntpq -c "rv 0 version offset frequency"`.
* `ntpq`: use `srchost` variable to show .POOL. prototype associations' hostname instead of address 0.0.0.0.
* Clean up an exit status in `ntpq.c`.
* Remove 1024 associations-per-server limit from `ntpq`.
* Remove blank line between `ntpq mreadvar` associations.
* `ntpq autogen` docs.
* Produce `ntpq.1` with the new `autogen` macros.
* Fix nits in the `ntpq` man page.
* Cleanup to `ntpq.texi`.

* * *

**ntpdc**

* Remove the deprecated `detail` stanza from `ntpdc-opts.def`.
* Remove use of `MAXFILENAME` in mode 7 (`ntpdc`) on-wire structs.
* Limit `ntpdc -c monlist` response in `ntpd` to 600 entries, the previous overall limit on the MRU list depth which was driven by the monlist implementation limit of one request with a single multipacket response.
* `ntpdc`: do not examine argument to `passwd` if not supplied.
* `ntpdc` documentation fixes and cleanup.
* Note the deprecation of `ntpdc` in its documentation.

* * *

**ntp-keygen**

* `ntp-keygen` private key cipher default now triple-key triple DES CBC.
* `ntp-keygen -M` is intended to ignore all other defaults and options, so do not attempt to open existing Autokey host certificate before generating symmetric keys and terminating.
* Restore IFF, MV, and GQ identity parameter filename convention to `ntpkey_<scheme>par_<group/host>` in `ntpd`, matching `ntp-keygen`.
* **Backward Incompatible** `ntp-keygen -i` option long name changed from misleading `--issuer-name` to `--ident`.
* Change `ntpd MAXFILENAME` from 128 to 256 to match `ntp-keygen`.
* from 4.2.6p3-RC12: Suppress `ntp-keygen` OpenSSL version display for `--help, --version`, display both build and runtime OpenSSL versions when they differ.
* Add `ntp-keygen -l/--lifetime` to control certificate expiry.
* Create `ntp-keygen.{html,texi}`.
* `ntp-keygen autogen` documentation updates.

* * *

**Windows**

* Treat zero counter as indication of precise system time in Windows PPSAPI helper function `pps_ntp_timestamp_from_counter()`, enabling PPSAPI providers to use the Windows 8 precise clock directly.
* Use `GetSystemTimePreciseAsFileTime()` on Windows 8.
* `ntp-keygen` on Windows XP and later systems will now create links expected by `ntpd`.  They are hardlinks on Windows, soft on POSIX.
* Force `.exe` minimum Windows version to 0x0400 to allow NT4 in `vs2005/*.vcproj` files.
* Use `_mkgmtime()` as `timegm()` in the Windows port, rather than `libntp/mktime.c`'s `timegm()`.  Fixed [Bug 1875](https://bugs.ntp.org/show_bug.cgi?id=1875) on Windows using the old `asn2ntp()` code from before 4.2.7p147.
* Provide fallback definitions for `GetAdaptersAddresses()` for Windows build environments lacking `iphlpapi.h`.
* Enable `tickadj`-like taming of wildly off-spec Windows clock using `NTPD_TICKADJ_PPM` env. var. specifying baseline slew.
* Enable raw `tty` line discipline in Windows port.
* Allow `tty` open/close/open to succeed on Windows port.
* Enable generating `ntpd/ntp_keyword.h` after `keyword-gen.c` changes on Windows as well as POSIX platforms.
* from 4.2.6p2-RC5: Windows port: do not exit in `ntp_timestamp_from_counter()` without first logging the reason.
* From 4.2.6p1-RC6: Correct Windows port's `refclock_open()` to return 0 on failure not -1.
* Windows compiling `hints/winnt.html` update from G. Sunil Tej.

* * *

**Linux**

* Eliminate warnings about shadowing global "basename" on Linux.
* Remove `signal_no_reset: signal 17 had flags 4000000` logging, as it indicates no problem and is interpreted as an error.  Previously some bits had been ignored one-by-one, but Linux `SA_RESTORER` definition is unavailable to user headers.

* * *

**unit tests**

* Add unit tests for `msnprintf()`.
* Add more unit tests for `timeval_tostr()` and `timespec_tostr()`.
* Fix `tvalops.cpp` unit test failures for 32-bit builds.
* Unit tests extended for hard-coded system time.

* * *

* Pass the configuration source into the parser as argument rather than through a global variable.
* Quiet warnings from `ntp_calendar.h`: avoid using argument names.
* Fix a variable lifetime issue.
* In `ntp_dir_sep.m4`, we care about `$host_os`, not `$target_os`.
* Add check for enable stats to `ntpd/complete.conf.in`
* Remove `\n`'s from `syslog` output strings.
* Have `NTP_LIBNTP` check for `time.h` and `clock_getres()`.
* Cleanup to `ntpsnmpd-opts.def`.
* Documentation cleanup to the `ntpd, ntpdc, ntpq` and `ntp-wait .def` files.
* In `ntp.conf.def`, cleanup SEE ALSO, document `rlimit` options.
* Make sure `agtexi-file.tpl` defines `label-str`.
* Cleanup to `ntp.conf.def`.
* Update the copyright year.
* Create `agtexi-file.tpl`.
* Remove extraneous parens.
* Add a missing `%s syslog` format string.
* Distribute `ntp.conf.def` and `ntp.keys.def`.
* Potential bugfix for `agtexi-cmd.tpl`.
* Look for `syslog`'s `facilitynames[]`.
* Cleanup `kclk_sel240x.o` rules in `libparse/Makefile.am`.
* Conditionalize `msyslog` messages about rejected mode 6 requests due to `nomodify` and `nomrulist` restrictions under `logconfig +sysinfo`.
* Increment `sys_restricted` in a few rejection paths due to `nomodify` restrictions where previosuly overlooked.
* `tickadj` may need to be linked with `PTHREAD_LIBS`.
* `U_INT32_MAX` cleanup in `include/ntp_types.h`.
* When linking, `ntp_keygen` and `tickadj` need `$(LIBM)`.
* Correct `authnumfreekeys` accounting broken in 4.2.7p262.
* `LCRYPTO` is gone - replace with `VER_SUFFIX`.
* Improve `ntpd` scalability for servers with many trusted keys.
* Update one of the license URLs.
* Fix build break triggered by updating `deps-ver` and `libntp/systime.c` at the same time by explicitly depending `systime_s.c` on `systime.c`.
* Refactor `timespecops.h` and `timevalops.h` into inline functions.
* Floor peer delay using system precision, as with jitter, reflecting inability to measure shorter intervals.
* from 4.2.6p5-RC3: Ensure NULL peer->dstadr is not accessed in orphan parent selection.
* from 4.2.6p5-RC2: Exclude not-yet-determined `sys_refid` from use in loopback TEST12 (from Dave Mills).
* from 4.2.6p5-RC2: Never send KoD rate limiting response to `MODE_SERVER`.
* Floor calculation of `sys_rootdisp` at `sys_mindisp` in `clock_update` (from Dave Mills).
* Restore 4.2.6 `clock_combine()` weighting to ntp-dev, reverting to pre-4.2.7p70 method while also avoiding divide-by-zero (from Dave Mills).
* Round `l_fp` traffic interval when converting to integer in rate limit and KoD calculation.
* Clean up `-libm` entries regarding `libntp.a`
* Update the `NEWS` file so we note the default disable of mode 7 requests.
* Clean up some bitrotted code in libntp/socket.c.
* Directly limit the number of datagrams in a `mrulist` response, rather than limiting the number of entries returned to indirectly limit the datagram count.
* Log signal description along with number on `ntpd` exit.
* Send all peer variables to trappers in `report_event()`.
* Fix the `CLOCK_MONOTONIC TRACE()` message.
* Cleanups for `ntp-wait-opts.def` and `ntp.keys.def`.
* Actually use long long for `(u_)int64` by correcting spelling of `SIZEOF_LONG_LONG` in `ntp_types.h`.
* Correct `init_logging()`'s `def_syslogmask` type to `u_int32` following change of `ntp_syslogmask` from `u_long` to `u_int32` in p202.
* Add support for installing programs and scripts to `libexec`.
* Match `addr_eqprefix() sizeof` and `memcpy` destination to make it clear to static analysis that there is no buffer overrun (CID 402).
* `ntp-wait`: some versions of `ntpd` spell `associd` differently.
* Update `.point-changed-filelist` for the new man pages.
* Update `.point-changed-filelist`.
* Upgrade local `autoopts` templates to 5.11.10pre5.
* Update the `std_def_list` to include the `ntp.lic` file.
* Distribute the `ntp.lic` file.
* Add ntp.org/license to the `ntp.lic` file.
* Clean up the `ntp.lic` file.
* Typo in `emalloc.c` hides file and line number from `emalloc()` error msg.
* `parsesolaris.c` compile fails on SPARC Solaris with conflicting `printf`.
* `ntp_util.c` compile fails on AIX and OSF with conflicting `statsdir`.
* Remove hardcoded 1/960 s. fudge for `<CR>` transmission time at 9600 8n1 from WWVB/Spectracom driver introduced in 4.2.7p169.
* Use `filegen_config()` consistently when changing `filegen` options.
* `mprintf()` should go to `stdout`, not `stderr.  DPRINTF()` uses `mprintf()`.
* Repair a few simulator problems (more remain).
* Use 64-bit scalars in `LFPTOD()` and `DTOLFP()` on more platforms by conditionalizing on `HAVE_U_INT64` rather than `UINT64_MAX`.
* Convert receive buffer queue from doubly-linked list to FIFO.
* Change `pool DNS` messages from `msyslog` to debug trace output.
* Remove unused `FLAG_SYSPEER` from peer->status.
* Respect `tos orphanwait` at startup.  Previously there was an unconditional 300 s. startup `orphanwait`, though other values were respected for subsequent orphan wait periods after `no_sys_peer` events.
* Fix a couple of unused variable warnings.
* cleanup in `timespecops.c / timevalops.c`
* Fix leak in `refclock_datum.c` start failure path.
* Coverity Scan cleanups and error checking fixes.
* Detect `vsnprintf()` support for `%m` and disable our `%m` expansion.
* On systems without C99-compliant `(v)snprintf()`, use `C99-snprintf` [replacements](http://www.jhweiss.de/software/snprintf.html)
* Remove remaining `sprintf()` calls except `refclock_ripencc.c` (which is kept out of `--enable-all-clocks` as a result), upstream libs which use `sprintf()` only after careful buffer sizing.
* `ntp_crypto.c` string buffer safety.
* Buffer safety and sign extension fixes (thanks Coverity Scan).
* String buffer safety cleanup, converting to `strlcpy()` and `strlcat()`.
* Use `utmpname()` before `pututline()` so repeated steps do not accidentally record into `wtmp` where `utmp` was intended.
* Use `setutent()` before each `pututline()` including first.
* One more lock-while-init in `lib/isc/task.c` to quiet lock analysis.
* Use `TRACE()` instead of `DPRINTF()` for `libntp` and utilities, which use the `debug` variable regardless of `#ifdef DEBUG`.
* Declare `debug` in `libntp` instead of each program.  Expose extern declaration to utilities, `libntp`, and `DEBUG ntpd`.
* Lock under-construction task, taskmgr objects to satisfy Coverity's mostly-correct assumptions about which variables are protected by which locks.
* Ensure `CONFIG_SHELL` is not empty before relying on it for `#!` scripts.
* Add `INC_ALIGNED_PTR()` macro to align pointers like `malloc()`.
* Do not cache paths to `perl, test`, or `pkg-config`, searching the `PATH` at configure time is worth it to pick up tool updates.
* ElectricFence was suffering bitrot - remove it.  `valgrind` works well.
* Correct Solaris 2.1x `PTHREAD_ONCE_INIT` extra braces test to avoid triggering warnings due to excess braces.
* Provide bug report and URL options to Autoconf.
* older `autoconf` sometimes dislikes `[]`.
* Move blocking worker and resolver to `libntp` from `ntpd`.
* Use threads rather than forked child processes for blocking worker when possible.  Override with `configure --disable-thread-support`.
* Move more `m4sh` tests needed by `libntp` to shared `.m4` files.
* Split up `ntp_libntp.m4` into smaller, more specific subsets.
* Enable `gcc -Wcast-align`, fix many instances of warnings when casting a pointer to a more-strictly-aligned underlying type.
* Fix leak in `ntp_control.c read_mru_list()`.
* Fix unexposed fencepost error in `format_time_fraction()`.
* Avoid shadowing the `group` global variable.
* Change new `timeval` and `timespec` to string routines to use `snprintf()` rather than hand-crafted conversion, avoid signed int overflow there.
* Add configure support for `SIZEOF_LONG_LONG` to enable portable use of `snprintf()` with `time_t`.
* Grow `ntpd/work_thread.c` arrays as needed.
* Add `DEBUG_*` variants of `ntp_assert.h` macros which compile away using `./configure --disable-debugging`.
* Return to a single `autoreconf` invocation in `./bootstrap` script.
* crypto group changes from Dave Mills.
* Lose the `RANGEGATE` check in PPS, from Dave Mills.
* added `timespecops.{c,h}` and `tievalops.{c.h}` to `libntp` and include added `tspecops.cpp` to `tests/libntp`
* Add `erealloc_zero()`, refactor `estrdup(), emalloc(), emalloc_zero()` to separate tracking callsite file/line from using debug MS C runtime, and to reduce code duplication.
* Begin moving some of the low-level socket stuff to `libntp`.
* Remove nearly all `strcpy()` and most `strcat()` from NTP distribution.
  - One major pocket remains in `ntp_crypto.c.  libopts` & `libisc` also have (safe) uses of `strcpy()` and `strcat()` remaining.
* Autokey multiple identity group improvements from Dave Mills.
* from 4.2.6p3: Update `genCommitLog` for the bk-5 release.
* from 4.2.6p3: Update `bk` triggers for the bk-5 release.
* Support for multiple Autokey identity groups from Dave Mills.
* from 4.2.6p3-RC12: Other `manycastclient` repairs:
  - Separate handling of scope ID embedded in many `in6_addr` from `ifindex` used for IPv6 multicasting ioctls.
  - Add `INT_PRIVACY` endpt bit flag for IPv6 [RFC 4941](https://www.rfc-editor.org/rfc/rfc4941) privacy addresses.
  - Enable outbound multicast from only one address per interface in the same subnet, and in that case prefer embedded MAC address modified EUI-64 IPv6 addresses first, then static, and last [RFC 4941](https://www.rfc-editor.org/rfc/rfc4941) privacy addresses.
  - Use `setsockopt(IP[V6]_MULTICAST_IF)` before each send to multicast to select the local source address, using the correct socket is not enough.
* `server ... ident <groupname>` changes from Dave Mills.
* An almost complete rebuild of the initial loopfilter configuration process, including the code that determines the interval between frequency file updates, from Dave Mills.
* Add `nonvolatile ntp.conf` directive to control how often the `driftfile` is written.
* Correct frequency estimate with no drift file, from David Mills.
* Refactor calendar functions in terms of new common code.
* Include Linus Karlsson's GSoC 2010 testing code.
* refinements to new startup behavior from David Mills.
* Fix from Dave Mills for a rare singularity in `clock_combine()`.
* Remove unused `bias` configuration keyword.
* Remove `calldelay` and `sign` remnants from parser, `ntp_config.c`.
* from 4.2.6p3: `ntpsnmpd, libntpq` warning cleanup.
* Remove `calldelay` and `sign` keywords (Dave Mills).
* Lose peer_count from `ntp_peer.c` and `ntp_proto.c` (Dave Mills).
* Variable name cleanup from Dave Mills.
* Clock select bugfix from Dave Mills.
* Clock combining algorithm improvements from Dave Mills.
* More Initial convergence improvements from Dave Mills.
* Cleanup `NTP_LIB_M`.
* Use `AC_SEARCH_LIBS` instead of `AC_CHECK_LIB` for `NTP_LIB_M`.
* Typo fix in a comment in `ntp_proto.c`.
* `clock_filter()`/reachability fixes from Dave Mills.
* Rewrite of multiprecision macros in `ntp_fp.h` from J. Perlinger
* `include/ntp_crypto.h`: make assumption `AUTOKEY` implies `OPENSSL` explicit.
* from 4.2.6p2-RC3: Simplify hash client code by providing `OpenSSL EVP_*()` API when built without OpenSSL.  (already in 4.2.7)
* Update the `ChangeLog` entries when merging items from -stable.
* Modify full MRU list preemption when full to match `discard monitor` documentation, by removing exception for `count == 1`.
* `ntpdate`: stop querying source after KoD packet response, log it.
* `ntpdate`: rate limit each server to 2s between packets.
* From J. N. Perlinger: avoid pointer wraparound warnings in `dolfptoa(), printf` format mismatches with 64-bit `size_t`.
* Broadcast client (ephemeral) associations should be demobilized only if they are not heard from for 10 consecutive polls, regardless of surviving the clock selection.  Fix from David Mills.
* Modify internal representation of MRU list to use `l_fp` fixed-point NTP timestamps instead of seconds since startup.  This increases the resolution and substantially improves accuracy of sorts involving timestamps, at the cost of flushing all MRU entries when the clock is stepped, to ensure the timestamps can be compared with the current `get_systime()` results.
* Add `ntp.conf mru` directive to configure MRU parameters, such as `mru mindepth 600 maxage 64 maxdepth 5000 maxmem 1024` or `mru initalloc 0 initmem 16 incalloc 99 incmem 4`.  Several pairs are equivalent with one in units of MRU entries and its twin in units of kilobytes of memory, so the last one used in `ntp.conf` controls: `maxdepth/maxmem, initalloc/initmem, incalloc/incmem`.  With the above values, `ntpd` will preallocate 16kB worth of MRU entries, allocating 4kB worth each time more are needed, with a hard limit of 1MB of MRU entries.  Until there are more than 600 entries none would be reused. Then only entries for addresses last seen 64 seconds or longer ago are reused.
* New `pool` directive implementation modeled on `manycastclient`.
* Do not abort on non-ASCII characters in `ntp.conf`, ignore them.
* `configure`: remove check for pointer type used with `qsort()`, we require ANSI C which mandates `void *`.
* Reset `sys_kodsent` to 0 in `proto_clr_stats()`.
* Add `sptoa()/sockporttoa()` similar to `stoa()/socktoa()` adding `:port`.
* Use `memcpy()` instead of `memmove()` when buffers can not overlap.
* Remove `sockaddr_storage` from our `sockaddr_u union` of `sockaddr, sockaddr_in`, and `sockaddr_in6`, shaving about 100 bytes from its size and substantially decreasing MRU entry memory consumption.
* `restrict source ...` configures override restrictions for time sources, allows tight default restrictions to be used with the pool directive (where server addresses are not known in advance).
* Ignore `preempt` modifier on `manycastclient` and `pool` prototype associations.  The resulting associations are preemptible, but the prototype must not be.
* Maintain and use linked list of associations (`struct peer`) in `ntpd`, avoiding walking 128 hash table entries to iterate over peers.
* Remove more workarounds unneeded since we require ISO C90 AKA ANSI C:
  - remove fallback implementations for `memmove(), memset, strstr()`.
  - do not test for `atexit()` or `memcpy()`.
* Collapse a bunch of code duplication in `ntpd/ntp_restrict.c` added with support for IPv6.
* Correct some corner case failures in automatically enabling the MRU list if any `restrict ... limited` is in effect, and in disabling MRU maintenance. (`ntp_monitor.c, ntp_restrict.c`)
* Reverse the internal sort order of the address restriction lists, but preserve the same behavior.  This allows removal of special-case code related to the default restrictions and more straightforward lookups of restrictions for a given address (now, stop on first match).
* Move `ntp_restrict.c` MRU doubly-linked list maintenance code into `ntp_lists.h` macros, allowing more duplicated source excision.
* Repair `ntpdate.c` to no longer test `HAVE_TIMER_SETTIME`.
* Do not reference peer_node/unpeer_node after freeing when built with `--disable-saveconfig` and using DNS.
* Use all addresses for each restrict by hostname.
* Use async DNS to resolve trap directive hostnames.
* Stop using `getaddrinfo()` to convert numeric address strings to on-wire addresses in favor of `is_ip_address()` alone.
* Attempts to cure CID 108 CID 118 CID 119 `TAINTED_SCALAR` warnings.
* Broaden `ylwrap` workaround `VPATH_HACK` to all non-GNU `make`.
* Include 4.2.6p1: Convert many `sprintf()` calls to `snprintf()`, also `strcpy(), strcat()`.
* Include 4.2.6p1: Remove some dead code checking for `emalloc()` returning NULL.
* New async DNS resolver in `ntpd` allows nonblocking queries anytime, instead of only once at startup.
* Include 4.2.6p1-RC3: Use `TZ=UTC` instead of `TZ=` when calling `date` in `scripts/mkver.in`.