---
title: "4.2.6p4 Release Announcement"
description: "The release announcement for NTP 4.2.6p4, which was released on September 22, 2011."
type: archives
date: "2011-09-22"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.6p4, a Point Release of the NTP Reference Implementation from the
NTP Project, is now available.

#### Changes

* Distribute ntp-wait.html
* Update `config.guess` and `config.sub` for AIX
* Upgrade required version of `autogen` and `libopts` for building from our source code repository

* * *

#### ntpd

* Backported several fixes for Coverity warnings from ntp-dev
* Fix a rare boundry condition in `UNLINK_EXPR_SLIST()`
* Allow `logconfig =allall` configuration directive
* Bind tentative IPv6 addresses on Linux
* Correct WWVB/Spectracom driver to timestamp `CR` instead of `LF`
* Improved tally bit handling to prevent incorrect `ntpq peer status` reports
* Exclude the Undisciplined Local Clock and ACTS drivers from the initial candidate list unless they are designated a `prefer peer`
* Prevent the consideration of Undisciplined Local Clock or ACTS drivers for selection during the `tos orphanwait` period
* Prefer an Orphan Mode Parent over the Undisciplined Local Clock or ACTS drivers
* Improved support of the Parse Refclock `trusttime` flag in Meinberg mode
* Backport utility routines from ntp-dev: `mprintf()`, `emalloc_zero()`
* Added the `NTPD_TICKADJ_PPM` environment variable for specifying baseline clock slew on Microsoft Windows
* Code cleanup in `libntpq`

* * *

#### ntpdc
 
* Fix timerstats reporting

* * *

#### ntpdate

* Reduce time required to set clock
* Allow a timeout greater than 2 seconds

* * *

#### sntp

* Backward incompatible command-line option change:
  `-l/--filelog` changed `-l/--logfile` (to be consistent with `ntpd`)

#### Documentation

* Update `html2man`. Fix some tags in the .html files
* Fix checking for `struct rtattr`