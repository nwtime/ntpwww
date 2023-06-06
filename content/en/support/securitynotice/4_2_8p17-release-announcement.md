---
title: "4.2.8p17 Release Announcement"
description: "The NTP Project at Network Time Foundation publicly released NTP 4.2.8p17 on June 6, 2023. This release fixes three bugs and provides 1 improvement."
type: archives
---

The NTP Project at Network Time Foundation publicly released ntp-4.2.8p17 on Tuesday, 06 Jun 2023.

This release fixes a regression which was reported in ntp-4.2.8p16. The regression only affects people who are running p16:

* [Bug 3822: `ntpd` significantly delays first poll of servers specified by name](https://bugs.ntp.org/3822).

This release also fixes 2 bugs:

* [Bug 3824: Spurious "ntpd: daemon failed to notify parent!" logged at `event_sync`](https://bugs.ntp.org/3824).
* [Bug 3821 4.2.8p16 misreads hex authentication keys, won't interop with 4.2.8p15 or earlier](https://bugs.ntp.org/3821).

and adds 1 improvement:

* Add `tests/libntp/digests.c` to catch regressions reading keys file or with symmetric authentication digest output.

<br>