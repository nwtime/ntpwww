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

Address: 127.127.7._u_  
Reference ID: <tt>CHU</tt>  
Driver ID: <tt>CHU</tt>  
Modem Port: <tt>/dev/chu_u_</tt>; 300 baud, 8-bits, no parity  
Features: <tt>chu_clk</tt>

* * *

#### Description

This driver supports a shortwave receiver and special modem circuitry described in the ./gadget directory of the xntp3 distribution. It requires the <tt>chu_clk</tt> line discipline or streams module described in the [Line Disciplines and Streams Drivers](/archives/3-5.93e/ldisc) page. It also requires a gadget box and 300-bps modem, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/3-5.93e/pps) page.

Unlike the NIST time services, whose timecode requires quite specialized hardware to interpret, the CHU timecode can be received directly via a serial port after demodulation. While there are currently no known commercial CHU receivers, the hardware required to receive the CHU timecode is fairly simple to build. While it is possible to configure several CHU units simultaneously, this is in general not useful.

The <tt>time1</tt> fudge option can be used to set the CHU propagation delay, compensate for inherent latencies in the serial port hardware and operating system. The default value is 0.0025 seconds, which is about right for Toronto. Values for other locations can be calculated using the propdelay program in the util directory of the xntp3 distribution or equivalent means.

The <tt>time2</tt> fudge option can also be used to compensate for inherent latencies in the serial port hardware and operating system. The value, which defaults to zero, is in addition to the propagation delay provided by the time1 option. The default value is 0.0002 seconds, which is about right for typical telephone modem chips.

The <tt>flag1</tt> option can be used to modify the averaging algorithm used to smooth the clock indications. Ordinarily, the algorithm picks the median of a set of samples, which is appropriate under conditions of poor to fair radio propagation conditions. If the clock is located relatively close to the WWV or WWVH transmitters, setting this flag will cause the algorithm to average the set of samples, which can reduce the residual jitter and improve accuracy.

* * *

#### Monitor Data

When enabled by the <tt>flag4</tt> fudege flag, every received timecode is written to the <tt>clockstats</tt> file. 

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

Specifies the ime offset calibration factor, in seconds and fraction, with default 0.0.

<dt><tt>time2 _time_</tt></dt>

Not used by this driver.

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>CHU</tt>.

<dt><tt>flag1 0 | 1</tt></dt>

See above.

<dt><tt>flag2 0 | 1</tt></dt>

Not used by this driver. 

<dt><tt>flag3 0 | 1</tt></dt>

Enable <tt>ppsclock</tt> line discipline/streams module if set. 

<dt><tt>flag4 0 | 1</tt></dt>

Enable <tt>clockstats</tt> recording if set.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)
