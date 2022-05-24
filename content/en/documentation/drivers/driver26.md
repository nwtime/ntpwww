---
title: "Hewlett Packard 58503A GPS Receiver and HP Z3801A"
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver26/#synopsis)
*   [Description](/documentation/drivers/driver26/#description)
*   [Fudge Factors](/documentation/drivers/driver26/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.26._u_</code>
: **Reference ID:** `GPS`
: **Driver ID:** `GPS_HP`
: **Serial Port:** <code>/dev/hpgps*u*</code>; 9600 baud, 8-bits, no parity, 19200 baud 7-bits, odd parity for the HP Z3801A

* * *

#### Description

This driver supports the HP 58503A Time and Frequency Reference Receiver and HP Z3801A GPS Receiver which use HP SmartClock (TM) to implement an Enhanced GPS receiver. The receiver accuracy when locked to GPS in normal operation is better than 1 μs. The accuracy when operating in holdover is typically better than 10 μs per day. Its receiver should be operated with factory default settings. Initial driver operation expects the receiver to be already locked to GPS, configured and able to output timecode format 2 messages.

The driver uses the poll sequence `:PTIME:TCODE?` to get a response from the receiver. The receiver responds with a timecode string of ASCII printing characters, followed by a <code>\<cr>\<lf></code>, followed by a prompt string issued by the receiver in the following format:

<pre>T#yyyymmddhhmmssMFLRVcc&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;scpi ></pre>

The driver processes the response at the <code>\<cr></code> and <code>\<lf></code>, so what the driver sees is the prompt from the previous poll, followed by this timecode. The prompt from the current poll is (usually) left unread until the next poll. So (except on the very first poll) the driver sees this:

<pre>scpi >T#yyyymmddhhmmssMFLRVcc&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;</pre>

The `T` is the on-time character, at 980 ms before the next 1PPS edge. The `#` is the timecode format type. We look for format 2. Without any of the CLK or PPS stuff, then, the receiver buffer timestamp at the <code>\<cr></code> is 24 characters later, which is about 25 ms at 9600 bps, so the first approximation for `fudge time1` is nominally -0.955 seconds. This number probably needs adjusting for each machine and operating system type. So far, -0.955000 on an HP 9000 Model 712/80 HP-UX and 9.05 -0.953175 on an HP 9000 Model 370 HP-UX 9.10.

This driver will probably work with the 58503B and 59551A if they are setup appropriately.

To use an HP Z3801A, specify `mode 1` on the server config line to setup the right line parameters.

The timekeeping portion of HP's business was sold to Symmetricom which was later acquired by [Microchip](https://www.microchip.com/en-us/products/clock-and-timing).

* * *

#### Fudge Factors

<code>**_time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `GPS`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver.
