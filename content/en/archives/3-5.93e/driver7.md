---
title: "Scratchbuilt CHU Receiver"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver7/#synopsis)
*   [Description](/archives/3-5.93e/driver7/#description)
*   [Monitor Data](/archives/3-5.93e/driver7/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver7/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver7/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.7._u_</code>  
: **Reference ID:** <code>CHU</code>  
: **Driver ID:** <code>CHU</code>  
: **Modem Port:** <code>/dev/chu\__u_</code>; 300 baud, 8-bits, no parity  
: **Features:** <code>chu_clk</code>

* * *

#### Description

This driver supports a shortwave receiver and special modem circuitry described in the ./gadget directory of the xntp3 distribution. It requires the <code>chu_clk</code> line discipline or streams module described in the [Line Disciplines and Streams Drivers](/archives/3-5.93e/ldisc/) page. It also requires a gadget box and 300-bps modem, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/3-5.93e/pps/) page.

Unlike the NIST time services, whose timecode requires quite specialized hardware to interpret, the CHU timecode can be received directly via a serial port after demodulation. While there are currently no known commercial CHU receivers, the hardware required to receive the CHU timecode is fairly simple to build. While it is possible to configure several CHU units simultaneously, this is in general not useful.

The <code>time1</code> fudge option can be used to set the CHU propagation delay, compensate for inherent latencies in the serial port hardware and operating system. The default value is 0.0025 seconds, which is about right for Toronto. Values for other locations can be calculated using the propdelay program in the util directory of the xntp3 distribution or equivalent means.

The <code>time2</code> fudge option can also be used to compensate for inherent latencies in the serial port hardware and operating system. The value, which defaults to zero, is in addition to the propagation delay provided by the time1 option. The default value is 0.0002 seconds, which is about right for typical telephone modem chips.

The <code>flag1</code> option can be used to modify the averaging algorithm used to smooth the clock indications. Ordinarily, the algorithm picks the median of a set of samples, which is appropriate under conditions of poor to fair radio propagation conditions. If the clock is located relatively close to the WWV or WWVH transmitters, setting this flag will cause the algorithm to average the set of samples, which can reduce the residual jitter and improve accuracy.

* * *

#### Monitor Data

When enabled by the <code>flag4</code> fudege flag, every received timecode is written to the <code>clockstats</code> file. 

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the ime offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>CHU</code>.

<code>**flag1 0 | 1**</code>

: See above.

<code>**flag2 0 | 1**</code>

: Not used by this driver. 

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set. 

<code>**flag4 0 | 1**</code>

: Enable <code>clockstats</code> recording if set.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock/)