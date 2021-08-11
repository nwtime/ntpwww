---
title: "Reference Clock Support"
type: archives
---

![gif](/archives/pic/stack1a.jpg) Master Time Facility at the [UDel Internet Research Laboratory](/reflib/lab)

Last update: 10-Mar-2014 05:20 UTC

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.8-series/refclock/#introduction)
*   [Special Considerations](/archives/4.2.8-series/refclock/#special-considerations)
*   [List of Reference Clock Drivers](/archives/4.2.8-series/refclock/#list-of-reference-clock-drivers)

* * *

#### Introduction

NTP Version 4 supports almost four dozen satellite, radio and telephone modem reference clocks plus several audio devices for instrumentation signals. A general description of the reference clock support is on this page. Additional information about each reference clock driver can be found via links from this page. Additional information is on the [Debugging Hints for Reference Clock Drivers](/archives/4.2.8-series/rdebug) and [How To Write a Reference Clock Driver](/archives/4.2.8-series/howto) pages. Information on how to support pulse-per-second (PPS) signals produced by some devices is on the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.8-series/pps) page. All reference clock drivers require that the reference clock use only Coordinated Universal Time (UTC). Timezone and standard/daylight adjustments are performed by the operating system kernel.

A reference clock will generally (though not always) be a radio timecode receiver synchronized to standard time as provided by NIST and USNO in the US, NRC in Canada and their counterparts elsewhere in the world. A device driver specific to each reference clock must be compiled in the distribution; however, most common radio, satellite and telephone modem clocks are included by default and are activated by configuration commands.

Reference clocks are supported in the same way as ordinary NTP clients and use the same filter, select, cluster and combine algorithms. Drivers have addresses in the form 127.127._t.u_, where _t_ is the driver type and _u_ is a unit number in the range 0-3 to distinguish multiple instances of the same driver. The connection to the computer is device dependent, usually a serial port, parallel port or special bus peripheral, but some can work directly from an audio codec or sound card. The particular device is specified by adding a soft link from the name used by the driver to the particular device name.

The <tt>server</tt> command is used to configure a reference clock. Only the <tt>mode</tt>, <tt>minpoll</tt>, <tt>maxpoll</tt>, and <tt>prefer</tt> options are supported for reference clocks, as described on the [Reference Clock Commands](/archives/4.2.8-series/clockopt) page. The <tt>prefer</tt> option is discussed on the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.8-series/prefer) page. Some of these options have meaning only for selected clock drivers.

The <tt>fudge</tt> command can be used to provide additional information for individual drivers and normally follows immediately after the <tt>server</tt> command. The reference clock stratum is by default 0, so that the server stratum appears to clients as 1. The <tt>stratum</tt> option can be used to set the stratum to any value in the range 0 through 15. The <tt>refid</tt> option can be used to change the reference identifier, as might in the case when the driver is disciplined by a pulse-per-second (PPS) source. The device-dependent <tt>mode</tt>, <tt>time</tt> and <tt>flag</tt> options can provide additional driver customization.

* * *

#### Special Considerations

The [Audio Drivers](/archives/4.2.8-series/audio) page describes three software drivers that process audio signals from an audio codec or sound card. One is for the NIST time and frequency stations WWV and WWVH, another for the Canadian time and frequency station CHU. These require an external shortwave radio and antenna. A third is for the generic IRIG signal produced by some timing devices. Currently, these are supported in FreeBSD, Solaris and SunOS and likely in other system as well.

The [Undisciplined Local Clock](/archives/drivers/driver1) driver can simulate a reference clock when no external synchronization sources are available. If a server with this driver is connected directly or indirectly to the public Internet, there is some danger that it can destabilize other clients. It is not recommended that the local clock driver be used in this way, as the orphan mode described on the [Association Management](/archives/4.2.8-series/assoc) page provides a generic backup capability.

The local clock driver can also be used when an external synchronization source such as the IEEE 1588 Precision Time Protocol or NIST Lockclock directly synchronizes the computer time. Further information is on the [External Clock Discipline and the Local Clock Driver](/archives/4.2.8-series/extern) page.

Several drivers make use of the pulse-per-second (PPS) signal discipline, which is part of the generic driver interface, so require no specific configuration. For those drivers that do not use this interface, the [PPS Clock Discipline](/archives/drivers/driver22) driver can be can provide this function. It normally works in conjunction with the reference clock that produces the timecode signal, but can work with another driver or remote server. When PPS kernel features are present, the driver can redirect the PPS signal to the kernel.

Some drivers depending on longwave or shortwave radio services need to know the radio propagation time from the transmitter to the receiver. This must be calculated for each specific receiver location and requires the geographic coordinates of both the transmitter and receiver. The transmitter coordinates for various radio services are given in the [Time and Frequency Standard Station Information](/reflib/qth) page. Receiver coordinates can be obtained locally or from Google Earth. The actual calculations are beyond the scope of this document.

Depending on interface type, port speed, etc., a reference clock can have a small residual offset relative to another. To reduce the effects of jitter when switching from one driver to the another, it is useful to calibrate the drivers to a common ensemble offset. The <tt>enable calibrate</tt> configuration command described on the [Miscellaneous Options](/archives/4.2.8-series/miscopt) page activates a special feature which automatically calculates a correction factor for each driver relative to an association designated the prefer peer.

* * *

#### List of Reference Clock Drivers

Following is a list showing the type and title of each driver currently implemented. The compile-time identifier for each is shown in parentheses. Click on a selected type for specific description and configuration documentation, including the clock address, reference ID, driver ID, device name and serial line speed. For those drivers without specific documentation, please contact the author listed in the [Copyright Notice](/archives/4.2.8-series/copyright) page.

*   [Type 1](/archives/drivers/driver1) Undisciplined Local Clock (<tt>LOCAL</tt>)
*   Type 2 Deprecated: was Trak 8820 GPS Receiver
*   [Type 3](/archives/drivers/driver3) PSTI/Traconex 1020 WWV/WWVH Receiver (<tt>WWV_PST</tt>)
*   [Type 4](/archives/drivers/driver4) Spectracom WWVB/GPS Receivers (<tt>WWVB_SPEC</tt>)
*   [Type 5](/archives/drivers/driver5) TrueTime GPS/GOES/OMEGA Receivers (<tt>TRUETIME</tt>)
*   [Type 6](/archives/drivers/driver6) IRIG Audio Decoder (<tt>IRIG_AUDIO</tt>)
*   [Type 7](/archives/drivers/driver7) Radio CHU Audio Demodulator/Decoder (<tt>CHU</tt>)
*   [Type 8](/archives/drivers/driver8) Generic Reference Driver (<tt>PARSE</tt>)
*   [Type 9](/archives/drivers/driver9) Magnavox MX4200 GPS Receiver (<tt>GPS_MX4200</tt>)
*   [Type 10](/archives/drivers/driver10) Austron 2200A/2201A GPS Receivers (<tt>GPS_AS2201</tt>)
*   [Type 11](/archives/drivers/driver11) Arbiter 1088A/B GPS Receiver (<tt>GPS_ARBITER</tt>)
*   [Type 12](/archives/drivers/driver12) KSI/Odetics TPRO/S IRIG Interface (<tt>IRIG_TPRO</tt>)
*   Type 13 Leitch CSD 5300 Master Clock Controller (<tt>ATOM_LEITCH</tt>)
*   Type 14 EES M201 MSF Receiver (<tt>MSF_EES</tt>)
*   Type 15 reserved
*   [Type 16](/archives/drivers/driver16) Bancomm GPS/IRIG Receiver (<tt>GPS_BANCOMM</tt>)
*   Type 17 Datum Precision Time System (<tt>GPS_DATUM</tt>)
*   [Type 18](/archives/drivers/driver18) NIST/USNO/PTB Modem Time Services (<tt>ACTS_MODEM</tt>)
*   [Type 19](/archives/drivers/driver19) Heath WWV/WWVH Receiver (<tt>WWV_HEATH</tt>)
*   [Type 20](/archives/drivers/driver20) Generic NMEA GPS Receiver (<tt>NMEA</tt>)
*   Type 21 TrueTime GPS-VME Interface (<tt>GPS_VME</tt>)
*   [Type 22](/archives/drivers/driver22) PPS Clock Discipline (<tt>PPS</tt>)
*   Type 23 reserved
*   Type 24 reserved
*   Type 25 reserved
*   [Type 26](/archives/drivers/driver26) Hewlett Packard 58503A GPS Receiver (<tt>GPS_HP</tt>)
*   [Type 27](/archives/drivers/driver27) Arcron MSF Receiver (<tt>MSF_ARCRON</tt>)
*   [Type 28](/archives/drivers/driver28) Shared Memory Driver (<tt>SHM</tt>)
*   [Type 29](/archives/drivers/driver29) Trimble Navigation Palisade GPS (<tt>GPS_PALISADE</tt>)
*   [Type 30](/archives/drivers/driver30) Motorola UT Oncore GPS <tt>GPS_ONCORE</tt>)
*   [Type 31](/archives/drivers/driver31) Rockwell Jupiter GPS (<tt>GPS_JUPITER</tt>)
*   [Type 32](/archives/drivers/driver32) Chrono-log K-series WWVB receiver (<tt>CHRONOLOG</tt>)
*   [Type 33](/archives/drivers/driver33) Dumb Clock (<tt>DUMBCLOCK</tt>)
*   [Type 34](/archives/drivers/driver34) Ultralink WWVB Receivers (<tt>ULINK</tt>)
*   [Type 35](/archives/drivers/driver35) Conrad Parallel Port Radio Clock (<tt>PCF</tt>)
*   [Type 36](/archives/drivers/driver36) Radio WWV/H Audio Demodulator/Decoder (<tt>WWV</tt>)
*   [Type 37](/archives/drivers/driver37) Forum Graphic GPS Dating station (<tt>FG</tt>)
*   [Type 38](/archives/drivers/driver38) hopf GPS/DCF77 6021/komp for Serial Line (<tt>HOPF_S</tt>)
*   [Type 39](/archives/drivers/driver39) hopf GPS/DCF77 6039 for PCI-Bus (<tt>HOPF_P</tt>)
*   [Type 40](/archives/drivers/driver40) JJY Receivers (<tt>JJY</tt>)
*   Type 41 TrueTime 560 IRIG-B Decoder
*   [Type 42](/archives/drivers/driver42) Zyfer GPStarplus Receiver
*   [Type 43](/archives/drivers/driver43) RIPE NCC interface for Trimble Palisade
*   [Type 44](/archives/drivers/driver44) NeoClock4X - DCF77 / TDF serial line
*   [Type 45](/archives/drivers/driver45) Spectracom TSYNC PCI
*   [Type 46](/archives/drivers/driver46) GPSD NG client protocol
