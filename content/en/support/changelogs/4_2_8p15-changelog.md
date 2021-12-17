---
title: "4.2.8p15 Changelog"
type: archives
---

**Release Date:** 2020 Jun 23

* * *

#### Security Fixes

* [3661: memory leak with AES128CMAC keys](/support/securitynotice/ntpbug3661)

* * *

#### Bug Fixes

* [3670: Regression from bad merge of 3592 and 3596](https://bugs.ntp.org/show_bug.cgi?id=3670)
  - fixed a bad merge that happened before 4.2.8-p14
* [3667: decodenetnum fails with numeric port](https://bugs.ntp.org/show_bug.cgi?id=3667)
  - rewrite `decodenetnum()` in terms of `inet_pton`
* [3666: avoid unlimited receive buffer allocation](https://bugs.ntp.org/show_bug.cgi?id=3666)
  - limit number of receive buffers, with an iron reserve for refclocks
* [3664: Enable openSSL CMAC support on Windows](https://bugs.ntp.org/show_bug.cgi?id=3664)
* [3662: Fix build errors on Windows with VS2008](https://bugs.ntp.org/show_bug.cgi?id=3662)
* [3660: Manycast orphan mode startup discovery problem](https://bugs.ntp.org/show_bug.cgi?id=3660)
  - integrated patch from Charles Claggett
* [3659: Move definition of psl[] from ntp_config.h to ntp_config.h](https://bugs.ntp.org/show_bug.cgi?id=3659)
* [3657: Wrong "Autokey group mismatch" debug message](https://bugs.ntp.org/show_bug.cgi?id=3657)
* [3655: ntpdc memstats hash counts](https://bugs.ntp.org/show_bug.cgi?id=3655)
  - fix by Gerry garvey
* [3653: Refclock jitter RMS calculation](https://bugs.ntp.org/show_bug.cgi?id=3653)
  - thanks to Gerry Garvey
* [3646: Avoid sync with unsync orphan](https://bugs.ntp.org/show_bug.cgi?id=3646)
  - patch by Gerry Garvey
* [3644: Unsynchronized server [...] selected as candidate](https://bugs.ntp.org/show_bug.cgi?id=3644)
* [3639: refclock_jjy: TS-JJY0x can skip time sync depending on the STUS reply](https://bugs.ntp.org/show_bug.cgi?id=3639)
  - applied patch by Takao Abe



