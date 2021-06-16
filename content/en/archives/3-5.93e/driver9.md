---
title: "Magnavox MX4200 GPS Receiver"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver9/#synopsis)
*   [Description](/archives/3-5.93e/driver9/#description)
*   [Operating Modes](/archives/3-5.93e/driver9/#operating-modes)
*   [Monitor Data](/archives/3-5.93e/driver9/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver9/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver9/#additional-information)

* * *

#### Synopsis

Address: 127.127.9._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS_MX4200</tt>  
Serial Port: <tt>/dev/gps_u_</tt>; 4800 baud, 8-bits, no parity  
Features: <tt>ppsclock</tt> (required)

* * *

#### Description

This driver supports the Magnavox MX 4200 Navigation Receiver adapted to precision timing applications. It requires the <tt>ppsclock</tt> line discipline or streams module described in the [Line Disciplines and Streams Drivers](/archives/3-5.93e/ldisc) page. It also requires a gadget box and 1-PPS level converter, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/3-5.93e/pps) page.

This driver supports all compatible receivers such as the 6-channel MX 4200, MX 4200D, and the 12-channel MX 9212, MX 9012R, MX 9112. 

* * *

#### Operating Modes

This driver supports two modes of operation, static and mobile, controlled by clock flag 2.

In static mode (the default) the driver assumes that the GPS antenna is in a fixed location. The receiver is initially placed in a "Static, 3D Nav" mode, where latitude, longitude, elevation and time are calculated for a fixed station. A DOP-weighted running average position is calculated from this data. After 24 hours, the receiver is placed into a "Known Position" mode, initialized with the calculated position, and then solves only for time. The position averaging algorithm does not take into account boundary conditions, so this mode of operation very near the international date line or the poles is not recommended.

In mobile mode, the driver assumes the GPS antenna is mounted on a moving platform such as a car, ship, or aircraft. The receiver is placed in "Dynamic, 3D Nav" mode and solves for position, altitude and time while moving. No position averaging is performed. 

#### Monitor Data

The driver writes each timecode as received to the <tt>clockstats</tt> file. 

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<dt><tt>time2 _time_</tt></dt>

Not used by this driver.

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>GPS</tt>.

<dt><tt>flag1 0 | 1</tt></dt>

Not used by this driver.

<dt><tt>flag2 0 | 1</tt></dt>

Assume GPS receiver is on a mobile platform if set.

<dt><tt>flag3 0 | 1</tt></dt>

Not used by this driver.

<dt><tt>flag4 0 | 1</tt></dt>

Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock) 