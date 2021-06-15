---
title: "Hewlett Packard 58503A GPS Receiver"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver26/#synopsis)
*   [Description](/archives/3-5.93e/driver26/#description)
*   [Monitor Data](/archives/3-5.93e/driver26/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver26/#fudge-factors)

* * *

#### Synopsis

Address: 127.127.26._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS_HP</tt>  
Serial Port: <tt>/dev/hpgps_u_</tt>; 9600 baud, 8-bits, no parity

* * *

#### Description

This driver supports the HP 58503A Time and Frequency Reference Receiver. It uses HP SmartClock (TM) to implement an Enhanced GPS receiver. The receiver accuracy when locked to GPS in normal operation is better than 1 usec. The accuracy when operating in holdover is typically better than 10 us per day. It receiver should be operated with factory default settings. Initial driver operation: expects the receiver to be already locked to GPS, configured and able to output timecode format 2 messages. 

The driver uses the poll sequence <tt>:PTIME:TCODE?</tt> to get a response from the receiver. The receiver responds with a timecode string of ASCII printing characters, followed by a &lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;, followed by a prompt string issued by the receiver, in the following format:

<pre>T#yyyymmddhhmmssMFLRVcc&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;</pre>

The driver processes the response at the &lsaquo;cr&rsaquo; and &lsaquo;lf&rsaquo;, so what the driver sees is the prompt from the previous poll, followed by this timecode. The prompt from the current poll is (usually) left unread until the next poll. So (except on the very first poll) the driver sees this: 

<pre>T#yyyymmddhhmmssMFLRVcc&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;</pre>

The T is the on-time character, at 980 msec. before the next 1PPS edge. The # is the timecode format type. We look for format 2. Without any of the CLK or PPS stuff, then, the receiver buffer timestamp at the &lsaquo;cr&rsaquo; is 24 characters later, which is about 25 msec. at 9600 bps, so the first approximation for fudge time1 is nominally -0.955 seconds. This number probably needs adjusting for each machine / OS type, so far: -0.955000 on an HP 9000 Model 712/80 HP-UX 9.05 -0.953175 on an HP 9000 Model 370 HP-UX 9.10 

This receiver also provides a 1-PPS signal, but I haven't figured out how to deal with any of the CLK or PPS stuff yet. Stay tuned. 

* * *

#### Monitor Data

When enabled by the <tt>flag4</tt> fudge flag, every received timecode is written as-is to the <tt>clockstats</tt> file. 

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>GPS</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Enable <tt>ppsclock</tt> line discipline/streams module if set. </dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Enable <tt>clockstats</tt> recording if set.</dd>