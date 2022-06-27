---
title: "Conrad parallel port radio clock"
description: "The Conrad parallel port radio clock driver supports the parallel port radio clock sold by Conrad Electronic under order numbers 967602 and 642002. It receives the legal German time from the DCF77 transmitter located near Frankfurt/Main and uses it to set its internal quartz clock."
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver35/#synopsis)
*   [Description](/documentation/drivers/driver35/#description)
*   [Monitor Data](/documentation/drivers/driver35/#monitor-data)
*   [Fudge factors](/documentation/drivers/driver35/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.35._u_</code>
: **Reference ID:** `PCF`
: **Driver ID:** `PCF`
: **Parallel Port:** <code>/dev/pcfclocks/*u*</code> or <code>/dev/pcfclock*u*</code>

* * *

#### Description

This driver supports the parallel port radio clock sold by [Conrad Electronic](https://www.conrad.com/) under order numbers 967602 and 642002. This clock is put between a parallel port and your printer. It receives the legal German time, which is either CET or CEST, from the DCF77 transmitter and uses it to set its internal quartz clock. The DCF77 transmitter is located near to Frankfurt/Main and covers a radius of more than 1500 kilometers.

The `pcfclock` device driver is required in order to use this reference clock driver. Currently device drivers for Linux and FreeBSD are available.

This driver uses C library functions to convert the received timecode to UTC and thus requires that the local timezone be CET or CEST. If your server is not located in Central Europe you have to set the environment variable TZ to CET before starting `ntpd`.

#### Monitor Data

Each timecode is written to the `clockstats` file in the format `YYYY MM DD HH MI SS`.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.1725.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `PCF`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: If set to 1, the radio clock's synchronisation status bit is ignored, ie the timecode is used without a check.

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver.