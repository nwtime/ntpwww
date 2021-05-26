---
title: "TrueTime GPS/GOES/OMEGA/WWV Receivers"
type: archives
---

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver5/#synopsis)
*   [Description](/archives/drivers/driver5/#description)
*   [Monitor Data](/archives/drivers/driver5/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver5/#fudge-factors)
*   [Additional Information](/archives/drivers/driver5/#additional-information)

* * *

#### Synopsis

Address: 127.127.5._u_  
Reference ID: <tt>GPS, OMEGA, GOES, WWV</tt>  
Driver ID: <tt>TRUETIME</tt>  
Serial Port: <tt>/dev/true_u_</tt>; 9600 baud, 8-bits, no parity  
Features: <tt>tty_clk</tt>

* * *

#### Description

This driver supports several models models of Kinemetrics/TrueTime timing receivers, including 468-DC MK III GOES Synchronized Clock, GPS- DC MK III and GPS/TM-TMD GPS Synchronized Clock, XL-DC (a 151-602-210, reported by the driver as a GPS/TM-TMD), GPS-800 TCU (an 805-957 with the RS232 Talker/Listener module), OM-DC OMEGA Synchronized Clock, the TL-3 WWV receiver, and very likely others in the same model families that use the same timecode formats.

Most of this code is originally from refclock_wwvb.c with thanks. It has been so mangled that wwvb is not a recognizable ancestor.

Timecode format: <tt>ADDD:HH:MM:SSQCL</tt>  

* `A` - control A (this is stripped before we see it) 
* `Q` - Quality indication (see below) 
* `C` - Carriage return 
* `L` - Line feed

Quality codes indicate possible error of:

<dt>468-DC GOES Receiver  
GPS-TM/TMD Receiver</dt>

* `?` +/- 500 milliseconds 
* `#` +/- 50 milliseconds  
* `*` +/- 5 milliseconds 
* `.` +/- 1 millisecond  
* space: less than 1 millisecond

<dt>OM-DC OMEGA Receiver:</dt>

* `>` +/- 5 seconds  
* `?` +/- 500 milliseconds # +/- 50 milliseconds  
* `*` +/- 5 milliseconds . +/- 1 millisecond  
* `A-H` less than 1 millisecond. Character indicates which station is being received as follows:  A = Norway, B = Liberia, C = Hawaii, D = North Dakota, E = La Reunion, F = Argentina, G = Australia, H = Japan  
* The carriage return start bit begins on 0 seconds and extends to 1 bit time.</dd>

<dt>TL-3 WWV Receiver:</dt>

* `?` receiver is unlocked  
* space +/- 5 milliseconds  

**Notes on 468-DC and OMEGA receiver:**

Send the clock a <tt>R</tt> or <tt>C</tt> and once per second a timestamp will appear. Send a <tt>R</tt> to get the satellite position once (GOES only).

**Notes on the 468-DC receiver:**

Since the old east/west satellite locations are only historical, you can't set your clock propagation delay settings correctly and still use automatic mode. The manual says to use a compromise when setting the switches. This results in significant errors. The solution; use fudge time1 and time2 to incorporate corrections. If your clock is set for 50 and it should be 58 for using the west and 46 for using the east, use the line

<tt>fudge 127.127.5.0 time1 +0.008 time2 -0.004</tt>

This corrects the 4 milliseconds advance and 8 milliseconds retard needed. The software will ask the clock which satellite it sees.

The PCL720 from PC Labs has an Intel 8253 look-alike, as well as a bunch of TTL input and output pins, all brought out to the back panel. If you wire a PPS signal (such as the TTL PPS coming out of a GOES or other Kinemetrics/Truetime clock) to the 8253's GATE0, and then also wire the 8253's OUT0 to the PCL720's INPUT3.BIT0, then we can read CTR0 to get the number of microseconds since the last PPS upward edge, mediated by reading OUT0 to find out if the counter has wrapped around (this happens if more than 65535us (65ms) elapses between the PPS event and our being called.)

**Notes on the TL-3 receiver:**

The mini-DIN RS-232 port uses the Apple pinout.  

Send the clock ST1 to turn on continuous (1/sec) timecodes. You can also enable "mode C" via the front panel. ST0 turns off this mode.  

QV will return the firmware revision (and is useful in identifying this clock.)  

QW will return its weekly signal log, useful if you're testing antennas. You may wish to turn the loss interval down from 4h (04) to 1h (01), so the receiver declares itself unlocked sooner. When in holdover, drift can be on the order of 10 ms/hr since there is no high quality reference oscillator.

* * *

#### Monitor Data

When enabled by the <tt>flag4</tt> fudge flag, every received timecode is written as-is to the <tt>clockstats</tt> file.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, to be used for the West satellite, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>. Specifies the time offset calibration factor, in seconds and fraction, to be used for the East satellite, with default 0.0.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>TRUE</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Silence the clock side of ntpd, just reading the clock without trying to write to it.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Generate a debug file /tmp/true%d.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Enable verbose <tt>clockstats</tt> recording if set.</dd>

</dl>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock)
