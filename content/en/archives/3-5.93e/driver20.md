---
title: "Generic NMEA GPS Receiver"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver20/#synopsis)
*   [Description](/archives/3-5.93e/driver20/#description)
*   [Setting up the Garmin GPS-25XL](/archives/3-5.93e/driver20/#setting-up-the-garmin-gps-25xl)
*   [Monitor Data](/archives/3-5.93e/driver20/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver20/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver20/#additional-information)

* * *

#### Synopsis

Address: 127.127.20._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS_NMEA</tt>  
Serial Port: <tt>/dev/gps_u_</tt>; 4800 baud, 8-bits, no parity    
Features: <tt>tty_clk</tt>

* * *

#### Description

This driver supports GPS's with the <tt>$GPRMC</tt> NMEA output string. The driver expects the GPS to be set up to transmit a <tt>$GPRMC</tt> message every second. 

The accuracy depends on the GPS used. Inexpensive GPS models are available with a claimed PPS signal accuracy of 1 μs or better relative to the broadcast signal. However, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system.

The $GPRMC message that the GPS transmits look like this:

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

The driver will send a <tt>$PMOTG,RMC,0000*1D&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;</tt> message each time a $GPRMC string is needed. This is not needed on most GPS receivers because they automatically send the $GPRMC string every second and will only work on GPS receivers that understand the $PMOTG string. Others will just ignore it.

* * *

#### Setting up the Garmin GPS-25XL

Switch off all output by sending it the following string.

<pre>"$PGRMO,,2&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;"</pre>

Now switch only $GPRMC on by sending it the following string.

<pre>"$PGRMO,GPRMC,1&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;"</pre>

On some systems the PPS signal isn't switched on by default. It can be switched on by sending the following string.

<pre>"$PGRMC,,,,,,,,,,,,2&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;"</pre>

* * *

#### Monitor Data

The $GPRMC string that is used is written to the clockstats file. 

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></a></dt>

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

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)
