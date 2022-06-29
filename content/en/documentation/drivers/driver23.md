---
title: "PTB Modem Time Service and other European Laboratories Time Services"
description: "The TB Modem Time Service driver supports the PTB Automated Computer Time Service (ACTS) and is a modified version of the NIST ACTS driver."
type: archives
---

#### Table of Contents
*  [Synopsis](/documentation/drivers/driver23/#synopsis)
*  [Description](/documentation/drivers/driver23/#description)
*  [Fudge Factors](/documentation/drivers/driver23/#fudge-factors)
*  [Additional Information](/documentation/drivers/driver23/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.23._u_</code>
: **Reference ID:** `PTB`
: **Driver ID:** `ACTS_PTB`
: **Serial Port:** <code>/dev/ptb*u*</code>; 1200 baud, 8-bits, no parity
: **Requires:** `/usr/include/sys/termios.h` header file with modem control

* * *

#### Description

This driver supports the PTB Automated Computer Time Service (ACTS) and is a modified version of the [NIST ACTS driver](/documentation/drivers/driver18/).

It periodically dials a prespecified telephone number, receives the PTB timecode data and calculates the local clock correction. It is designed primarily for use when neither a radio clock nor connectivity to Internet time servers is available. For the best accuracy, the individual telephone line/modem delay needs to be calibrated using outside sources.

The only change between this driver and the NIST one is the data format. In fact PTB data format is the following:

<pre>Data format  
0000000000111111111122222222223333333333444444444455555555556666666666777777777 7
0123456789012345678901234567890123456789012345678901234567890123456789012345678 9
1995-01-23 20:58:51 MEZ 10402303260219950123195849740+40000500 *
A B C D EF G H IJ K L M N O P Q R S T U V W XY Z&lsaquo;CR&rsaquo;&lsaquo;LF&rsaquo;
A year
B month
C day
D hour
E : normally
A for DST to ST switch first hour
B for DST to ST switch second hour if not marked in H
F minute
G second
H timezone
I day of week
J week of year
K day of year
L month for next ST/DST changes
M day
N hour
O UTC year
P UTC month
Q UTC day
R UTC hour
S UTC minute
T modified julian day (MJD)
U DUT1
V direction and month if leap second
W signal delay (assumed/measured)
X sequence number for additional text line in Y
Y additional text
Z on time marker (* - assumed delay / # measured delay)
&lsaquo;CR&rsaquo;!&lsaquo;LF&rsaquo; ! is second change !
</pre>

This format is an ITU-R Recommendation (ITU-R TF583.4) and is now available from the primary timing centres of the following countries: Austria, Belgium, Germany, Italy, The Netherlands, Poland, Portugal, Romania, Spain, Sweden, Switzerland, Turkey, United Kingdom. Some examples are:

*   In Germany by [Physikalisch-Technische Bundesanstalt (PTB)'s timecode service](https://www.ptb.de/cms/en/ptb/fachabteilungen/abtq/gruppe-q4/ref-q42/time-synchronization-of-computers-using-the-network-time-protocol-ntp.html). Phone number: +49 5 31 51 20 38.

*   In the UK by [National Physical Laboratory (NPL)'s TRUETIME service](https://www.npl.co.uk/products-services/time-frequency). Phone number: 0891 516 333

*   In Italy by [Istituto Elettrotecnico Nazionale "Galileo Ferrais" (IEN)'s](https://www.istc.int/) CTD service. Phone number: 166 11 46 15

*   In Switzerland by [Swiss Federal Office of Metrology 's timecode service](https://www.metas.ch/metas/en/home/fabe/zeit-und-frequenz.html). Phone number: 031 323 32 25

*   In Sweden by [SP Swedish National Testing and Research Institute's timecode service](https://www.ri.se/en/what-we-do/expertises/position-navigation-and-time). Phone number: +46 33 415783.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `PTB`.

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

A keyword in the ntp.conf file permits a direct connection to a serial port of source of time like IEN CTD signal. It is sufficient to use the string `DIRECT` in place of the phone number.

Example:

`server 127.127.23.1`

`phone DIRECT`

#### Additional Information

[Reference Clock Drivers](/documentation/4.2.0/refclock/)