---
title: "Hewlett Packard 58503A GPS Receiver"
type: archives
noindex: true
---

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver26/#synopsis)
*   [Description](/documentation/3-5.93e/driver26/#description)
*   [Monitor Data](/documentation/3-5.93e/driver26/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver26/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.26._u_</code>  
: **Reference ID:** <code>GPS</code>
: **Driver ID:** <code>GPS_HP</code>
: **Serial Port:** <code>/dev/hpgps\__u_</code>; 9600 baud, 8-bits, no parity

* * *

#### Description

This driver supports the HP 58503A Time and Frequency Reference Receiver. It uses HP SmartClock (TM) to implement an Enhanced GPS receiver. The receiver accuracy when locked to GPS in normal operation is better than 1 usec. The accuracy when operating in holdover is typically better than 10 us per day. It receiver should be operated with factory default settings. Initial driver operation: expects the receiver to be already locked to GPS, configured and able to output timecode format 2 messages. 

The driver uses the poll sequence <code>:PTIME:TCODE?</code> to get a response from the receiver. The receiver responds with a timecode string of ASCII printing characters, followed by a &lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;, followed by a prompt string issued by the receiver, in the following format:

<code>T#yyyymmddhhmmssMFLRVcc\<cr>\<lf></code>

The driver processes the response at the <code>\<cr></code> and <code>\<lf></code>, so what the driver sees is the prompt from the previous poll, followed by this timecode. The prompt from the current poll is (usually) left unread until the next poll. So (except on the very first poll) the driver sees this: 

<code>T#yyyymmddhhmmssMFLRVcc\<cr>\<lf></code>

The <code>T</code> is the on-time character, at 980 msec. before the next 1PPS edge. The `#` is the timecode format type. We look for format 2. Without any of the CLK or PPS stuff, then, the receiver buffer timestamp at the `<cr>` is 24 characters later, which is about 25 msec. at 9600 bps, so the first approximation for <code>fudge time1</code> is nominally -0.955 seconds. This number probably needs adjusting for each machine / OS type, so far: -0.955000 on an HP 9000 Model 712/80 HP-UX 9.05 -0.953175 on an HP 9000 Model 370 HP-UX 9.10 

This receiver also provides a 1-PPS signal, but I haven't figured out how to deal with any of the CLK or PPS stuff yet. Stay tuned. 

* * *

#### Monitor Data

When enabled by the <code>flag4</code> fudge flag, every received timecode is written as-is to the <code>clockstats</code> file. 

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>GPS</code>.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set. 

<code>**flag4 0 | 1**</code>

: Enable <code>clockstats</code> recording if set.