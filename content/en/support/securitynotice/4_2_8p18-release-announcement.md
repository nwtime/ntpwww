---
title: "4.2.8p18 Release Announcement"
description: "The NTP Project at Network Time Foundation publicly released NTP 4.2.8p18 on May 25, 2024. This release fixes 40 bugs and provides 40 improvement."
type: archives
---

The NTP Project, part of Network Time Foundation (NTF), is pleased to announce the release candidate for NTP 4.2.8p18, a Point Release of the Reference Implementation of the Network Time Protocol (NTP) software. It is available at https://downloads.nwtime.org/ntp/ or by pointing your ftp client to anonymous@ftp.nwtime.org.

* File-size: 7210799 bytes
* MD5 (ntp-4.2.8p18.tar.gz) = 516bdabd94ab7c824e9771390761a46c
* SHA256 (ntp-4.2.8p18.tar.gz) = cf84c5f3fb1a295284942624d823fffa634144e096cfc4f9969ac98ef5f468e5

ntp-4.2.8p18 is a RECOMMENDED upgrade for all users. It fixes 40 bugs and provides 40 other improvements:

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

Please report any bugs, issues, or desired enhancements via https://bugs.ntp.org/.

End-user and developer support for NTP, both community and professional, is [available](https://www.ntp.org/support/).

Additional resources and information about the NTP Project’s Reference Implementation of NTP is available at https://www.ntp.org/.

Support Network Time Foundation and the NTP Project - donate or join at https://www.nwtime.org/.
