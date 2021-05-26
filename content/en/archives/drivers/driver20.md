---
title: "Generic NMEA GPS Receiver"
type: archives
---

Last update: 13-Jan-2020 07:12 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver20/#synopsis)
*   [Description](/archives/drivers/driver20/#description)
*   [NMEA Talker IDs](/archives/drivers/driver20/#nmea-talker-ids)
*   [The 'mode' byte](/archives/drivers/driver20/#the-mode-byte)
*   [About distrusting NMEA date stamps](/archives/drivers/driver20/#about-distrusting-nmea-date-stamps)
*   [Monitor Data](/archives/drivers/driver20/#monitor-data)
*   [Setting up the Garmin GPS-25XL](/archives/drivers/driver20/#setting-up-the-garmin-gps-25xl)
*   [Fudge Factors](/archives/drivers/driver20/#fudge-factors)
*   [Additional Information](/archives/drivers/driver20/#additional-information)

* * *

#### Synopsis

Address: 127.127.20._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS_NMEA</tt>  
Serial Port: <tt>/dev/gps_u_</tt>; 4800 - 115200 bps, 8-bits, no parity  
Serial Port: <tt>/dev/gpspps_u_</tt>; for just the PPS signal (this is tried first for PPS, before <tt>/dev/gps_u_</tt>)  
Serial Port: <tt>/dev/gps_u_</tt>; symlink to server:port (for nmead)  
Features: <tt>tty_clk</tt>

* * *

#### Description

This driver supports GPS receivers with the <tt>$GPRMC</tt>, <tt>$GPGLL</tt>, <tt>$GPGGA</tt>, <tt>$GPZDA</tt> and <tt>$GPZDG</tt> NMEA sentences by default.  Note that Accord's custom NMEA sentence <tt>$GPZDG</tt> reports using the GPS timescale, while the rest of the sentences report UTC.  The difference between the two is a whole number of seconds which increases with each leap second insertion in UTC.  To avoid problems mixing UTC and GPS timescales, the driver disables processing of UTC sentences once <tt>$GPZDG</tt> is received.  
{{% alert title="Caveat" color="warning" %}}  
Please see [Talker IDs](/archives/drivers/driver20/#nmea-talker-ids) when using non-GPS or multi-system receivers.
{{% /alert %}}

The driver expects the receiver to be set up to transmit at least one supported sentence every second.

The accuracy depends on the receiver used. Inexpensive GPS models are available with a claimed PPS signal accuracy of 1 μs or better relative to the broadcast signal. However, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system.

If the Operating System supports PPSAPI ([RFC 2783](http://www.ietf.org/rfc/rfc2783.txt)), fudge flag1 1 enables its use.

The various GPS sentences that this driver recognises look like this:  
(others quietly ignored)

**Accepted NMEA sentences**

| Sentence | Vendor |
| ----- | ----- |
| `$GPRMC,UTC,POS_STAT,LAT,LAT_REF,LON,LON_REF,SPD,HDG,DATE,MAG_VAR,MAG_REF*CS` | |
| `$GPGLL,LAT,LAT_REF,LON,LON_REF,UTC,POS_STAT*CS` ||
| `$GPGGA,UTC,LAT,LAT_REF,LON,LON_REF,FIX_MODE,SAT_USED,HDOP,ALT,ALT_UNIT,GEO,G_UNIT,D_AGE,D_REF*CS` ||
| `$GPZDA,UTC,DD,MM,YYYY,TH,TM,*CS` ||
| `$GPZDG,GPSTIME,DD,MM,YYYY,AA.BB,V*CS` | Accord |
| `$PGRMF,gpsWk,gpsTow,DATE,UTC,LEAPS,LAT,LAT_REF,LON,LON_REF,TYPE,MODE,SPD,HDOP,TDOP*CS` | Garmin |
| `$PUBX,04,UTC,DATE,utcTow,utcWk,LEAPS,clkBias,clkDrift,tpGran,*CS` | UBLOX |

**NMEA data items**

| Symbol | Meaning and Format |
| ----- | ----- |
| `ALT` | Antenna Altitude | 
| `ALT_UNIT` | Altitude Units (Metres/Feet) | 
| `DATE` | Date (ddmmyy) | 
| `DD` | Day of the month (1-31) | 
| `D_AGE` | Age of last DGPS Fix | 
| `D_REF` | Reference ID of DGPS station | 
| `FIX_MODE` | Position Fix Mode (0 = Invalid, >0 = Valid) | 
| `GEO` | Geoid/Elipsoid separation | 
| `GPSTIME` | Time of day on GPS timescale. Hours, minutes and seconds [fraction (opt.)] (hhmmss[.f]) | 
| `gpsTow` | GPS week time, seconds since start of GPS week (0..604799) | 
| `gpsWk` | Week number in the GPS time scale (may exceed 1024) | 
| `G_UNIT` | Geoid units (M/F) | 
| `HDG` | Heading/track made good (degrees True) (x.x) | 
| `HDOP` | Horizontal Dilution of Precision | 
| `LAT` | Latitude (llll.ll) | 
| `LAT_REF` | Latitude direction (N = North, S = South) | 
| `LEAPS` | Leap seconds or difference between GPS time scale and UTC | 
| `LON` | Longitude (yyyyy.yy) | 
| `LON_REF` | Longitude direction (E = East, W = West) | 
| `MAG_REF` | Magnetic variation (E = East, W = West) | 
| `MAG_VAR` | Magnetic variation (degrees) (x.x) | 
| `MM` | Month of the year (1-12) | 
| `POS_STAT` | Position status. (A = Data valid, V = Data invalid) | 
| `SAT_USED` | Number of Satellites used in solution | 
| `SPD` | Speed over ground. (knots) (x.x) | 
| `UTC` | Time of day on UTC timescale. Hours, minutes and seconds [fraction (opt.)] (hhmmss[.fff]) | 
| `YYYY` | Year | 
| `WEEK` | GPS week (0-1023) | 
| `WSEC` | Seconds since start of week (0-604799) | 
| `LEAP` | GPS leap seconds, that is, seconds ahead of UTC | 
| `AA.BB` | Denotes the signal strength (should be < 05.00) | 
| `V` | GPS sync status<br>  `0` => INVALID time<br> `1` => accuracy of +/- 20ms<br> `2` => accuracy of +/- 100ns | 
| `CS` | Checksum` | 
| | Sentence terminator. | 

* * *

#### NMEA Talker IDs

GNSS receivers use a distinct talker ID for the GNSS they process. Receivers capable of tracking different systems at the same time can emit <tt>$GPRMC</tt> (GPS), <tt>$GLRMC</tt> (GLONASS), <tt>$GARMC</tt> (Galileo), <tt>$GNRMC</tt> (generic/combined) and others all in one data stream.

The driver supports this to a certain degree by ignoring the talker ID on the standard sentences RMC, GLL, GGA, ZDA and ZDG. (It possibly should not do that on the latter, but for now, that's the way it is.) So whenever <tt>$GPRMC</tt> is mentioned in this document, substitute any possible talker ID your receiver might emit -- it will still match.

This approach has a drawback. It is easy to use for single-system receivers, but it cannot separate the data streams for multi-system receiver modules. It is therefore undefined which GNSS actually provides the data, and this can lead to strange behavior. This is especially true if the different GNSS provide very different signal quality to the receiver; the driver is not able to cherry-pick the best source and might actually end up in using the worst available. It is therefore recommended to set up such a receiver to either use just a single GNSS (which would defeat its purpose) or to emit only the combined data, which usually has the <tt>GN</tt> talker ID defined by the NMEA standard.

* * *

#### The 'mode' byte

Specific GPS sentences and bitrates may be selected by setting bits of the 'mode' in the server configuration line:  
  <tt>server 127.127.20.x mode X</tt>

**mode byte bits and bit groups**

| Bit | Decimal | Hex | Meaning |
| ----- | ----- | ----- | ----- |
| `0` | `1` | `1` | process `$GPRMC` |
| `1` | `2` | `2` | process `$GPGGA` |
| `2` | `4` | `4` | process `$GPGLL` |
| `3` | `8` | `8` | process `$GPZDA` or `$GPZDG` |
| `4-6` | `0` | `0` | linespeed 4800 bps |
| | `16` | `0x10` | linespeed 9600 bps |
| | `32` | `0x20` | linespeed 19200 bps |
| | `48` | `0x30` | linespeed 38400 bps |
| | `64` | `0x40` | linespeed 57600 bps |
| | `80` | `0x50` | linespeed 115200 bps |
| `7` | `128` | `0x80` | Write the sub-second fraction of the receive time stamp to the clockstat file for all recognised NMEA sentences. This can be used to get a useful value for fudge time2. **Caveat:** This will fill your clockstat file rather fast. Use it only temporarily to get the numbers for the NMEA sentence of your choice. |
| `8` | `256` | `0x100` | process `$PGRMF` |
| `9` | `512` | `0x200` | process `$PUBX,04` |
| `10-15` |  | `0xFC00` | reserved - leave 0 |
| `16` | `65536` | `0x10000` | Append extra statistics to the clockstats line. Details below. |
| `17` | `131072` | `0x20000` | "Silent PPS" mode. Use the PPS channel (if enabled with fudge flag 1) to get precise receive time stamps. **Do not** set the PPS flag in the clock status, so the clock is not considered as PPS peer. |
| `18` | `262144` | `0x40000` | Trust the date delivered via NMEA. Do this only if you _really_ trust the receiver! See [below](/archives/drivers/driver20/#about-distrusting-nmea-date-stamps). **Caveat:** This (hitherto undocumented) bit has moved! |

The default (mode 0) is to process all supported sentences at a linespeed of 4800 bps, which results in the first one received and recognised in each cycle being used.  If only specific sentences should be recognised, then the mode byte must be chosen to enable only the selected ones.  Multiple sentences may be selected by adding their mode bit values, but of those enabled still only the first received sentence in a cycle will be used.  Using more than one sentence per cycle is impossible, because

*   There is only [fudge time2](/archives/drivers/driver20/#fudge-factors) available to compensate for transmission delays but every sentence would need a different one, and
*   using more than one sentence per cycle overstuffs the internal data filters.

The driver uses 4800 bits per second by default, but faster bitrates can be selected using bits 4 to 6 of the mode field.

{{% alert title="Caveat" color="warning" %}}
 Using higher line speeds does not necessarily increase the precision of the timing device.  Higher line speeds are not necessarily helpful for the NMEA driver, either.  They can be used to accomodate for an amount of data that does not fit into a 1-second cycle at 4800 bps, but high-speed high-volume NMEA data is likely to cause trouble with the serial line driver since NMEA supports no protocol handshake.  Any device that is exclusively used for time synchronisation purposes should be configured to transmit the relevant data only, e.g. one <tt>$GPRMC</tt> or <tt>$GPZDA</tt> per second, at a linespeed of 4800 bps or 9600 bps.
{{% /alert %}}

* * *

#### About distrusting NMEA date stamps

Trusting the calendar dates delivered via NMEA is a risky thing, and by default these dates are handled with a huge dose of skepticism. Many receivers deliver a correct calendar date for a period of just 1024 weeks, with a starting point baked somewhere into their firmware. Beyond that, they warp back to the begin of their era and simply provide wrong date information. To battle this widely observed effect, the date delivered is by default reduced to GPS time again and then (re-)mapped according to the base date, either the implicit value or the value set via "tos basedate". If the receiver can _really_ be trusted to deliver the right date (which is not impossible, just more expensive for the manufacturer), then mode bit 18 can be used to bypass the era mapping. Setting this bit is not needed under most circumstances, and setting it with an unreliable receiver can have severe effects. Handle with care.

{{% alert title="Note" color="warning" %}} 
This functionality was available for some time as an undocumented feature, with a different bit value. It was moved in the process of becoming officially acknowledged to avoid excessive scattering of the mode bit mask.
{{% /alert %}}

* * *

#### Monitor Data

The last GPS sentence that is accepted or rejected is written to the clockstats file and available with `ntpq -c clockvar`. (Logging the rejected sentences lets you see/debug why they were rejected.) Filtered sentences are not logged.

If the 0x10000 mode bit is on and clockstats is enabled, several extra counters will be appended to the NMEA sentence that gets logged. For example:

<pre>56299 76876.691 127.127.20.20 $GPGGA,212116.000,3726.0785,N,12212.2605,W,1,05,2.0,17.0,M,-25.7,M,,0000*5C  228 64 0 0 64 0
</pre>

**Clockstats**

| Column | Sample | Meaning |
| -----  | -----  | -----   |
| 1      | 56299  | MJD     |
| 2      | 76876.691 | Time of day in seconds |
| 3      | 127.127.20.20 | IP Address from server config line |
| 4      | `$GPGGA,...0*5C` | NMEA Sentence |
| 5      | 228    | Number of sentences received |
| 6      | 64     | Number of sentences accepted and used for timekeeping |
| 7      | 0      | Number of sentences rejected because they were marked invalid (poor signal) |
| 8      | 0      | Number of sentences rejected because of bad checksum or invalid date/time |
| 9      | 64     | Number of sentences filtered by mode bits or same second |
| 10     | 0      | Number of PPS pulses used, overrides NMEA sentences |

Sentences like `$GPGSV` that don't contain the time will get counted in the total but otherwise ignored.</a>

[Configuring NMEA Refclocks](https://support.ntp.org/bin/view/Support/ConfiguringNMEARefclocks) might give further useful hints for specific hardware devices that exhibit strange or curious behaviour.

To make a specific setting, select the corresponding decimal values from the mode byte table, add them all together and enter the resulting decimal value into the clock configuration line.

* * *

#### Setting up the Garmin GPS-25XL

Switch off all output with by sending it the following string.

<pre>"$PGRMO,,2<cr><lf>"</pre>

Now switch only $GPRMC on by sending it the following string.

<pre>"$PGRMO,GPRMC,1<cr><lf>"</pre>

On some systems the PPS signal isn't switched on by default. It can be switched on by sending the following string.

<pre>"$PGRMC,,,,,,,,,,,,2<cr><lf>"</pre>

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the PPS time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><a name="fudgetime2"><tt>time2 _time_</tt></a></dt>

<dd>Specifies the serial end of line time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>GPS</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Disable PPS signal processing if 0 (default); enable PPS signal processing if 1.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>If PPS signal processing is enabled, capture the pulse on the rising edge if 0 (default); capture on the falling edge if 1.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>If PPS signal processing is enabled, use the <tt>ntpd</tt> clock discipline if 0 (default); use the kernel discipline if 1.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Obscures location in timecode: 0 for disable (default), 1 for enable.</dd>

</dl>

* * *

#### Additional Information

<tt>flag1</tt>, <tt>flag2</tt>, and <tt>flag3</tt> are ignored under Windows.

[Reference Clock Drivers](/archives/4.2.8-series/refclock)
