---
title: "Generic NMEA GPS Receiver"
type: archives
noindex: true
---

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver20/#synopsis)
*   [Description](/documentation/3-5.93e/driver20/#description)
*   [Setting up the Garmin GPS-25XL](/documentation/3-5.93e/driver20/#setting-up-the-garmin-gps-25xl)
*   [Monitor Data](/documentation/3-5.93e/driver20/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver20/#fudge-factors)
*   [Additional Information](/documentation/3-5.93e/driver20/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.20._u_</code> 
: **Reference ID:** <code>GPS</code>
: **Driver ID:** <code>GPS_NMEA</code>
: **Serial Port:** <code>/dev/gps\__u_</code>; 4800 baud, 8-bits, no parity
: **Features:** <code>tty_clk</code>

* * *

#### Description

This driver supports GPS's with the <code>$GPRMC</code> NMEA output string. The driver expects the GPS to be set up to transmit a <code>$GPRMC</code> message every second. 

The accuracy depends on the GPS used. Inexpensive GPS models are available with a claimed PPS signal accuracy of 1 μs or better relative to the broadcast signal. However, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system.

The <code>$GPRMC</code> message that the GPS transmits look like this:

<pre>$GPRMC,POS_UTC,POS_STAT,LAT,LAT_REF,LON,LON_REF,SPD,HDG,DATE,MAG_VAR,MAG_REF*CC&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;

  POS_UTC  - UTC of position. Hours, minutes and seconds. (hhmmss)
  POS_STAT - Position status. (A = Data valid, V = Data invalid)
  LAT      - Latitude (llll.ll)
  LAT_REF  - Latitude direction. (N = North, S = South)
  LON      - Longitude (yyyyy.yy)
  LON_REF  - Longitude direction (E = East, W = West)
  SPD      - Speed over ground. (knots) (x.x)
  HDG      - Heading/track made good (degrees True) (x.x)
  DATE     - Date (ddmmyy)
  MAG_VAR  - Magnetic variation (degrees) (x.x)
  MAG_REF  - Magnetic variation (E = East, W = West)
  CC       - Checksum (optional)
  &lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo; - Sentence terminator.
</pre>

The driver will send a <code>$PMOTG,RMC,0000\*1D\<cr>\<lf></code> message each time a <code>$GPRMC</code> string is needed. This is not needed on most GPS receivers because they automatically send the <code>$GPRMC</code> string every second and will only work on GPS receivers that understand the <code>$PMOTG</code> string. Others will just ignore it.

* * *

#### Setting up the Garmin GPS-25XL

Switch off all output by sending it the following string.

<code>"$PGRMO,,2\<cr>\<lf>"</code>

Now switch only <code>$GPRMC</code> on by sending it the following string.

<code>"$PGRMO,GPRMC,1\<cr>\<lf>"</code>

On some systems the PPS signal isn't switched on by default. It can be switched on by sending the following string.

<code>"$PGRMC,,,,,,,,,,,,2\<cr>\<lf>"</code>

* * *

#### Monitor Data

The <code>$GPRMC</code> string that is used is written to the clockstats file. 

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

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/3-5.93e/refclock/)