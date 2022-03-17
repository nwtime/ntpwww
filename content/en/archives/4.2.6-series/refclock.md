---
title: "Reference Clock Drivers"
type: archives
noindex: true
---

![gif](/archives/pic/stack1a.jpg) Master Time Facility at the [UDel Internet Research Laboratory](/reflib/lab/)

Last update:  20:45 UTC Thursday, January 03, 2008

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.6-series/refclock/#introduction)
*   [Driver Calibration](/archives/4.2.6-series/refclock/#driver-calibration)
*   [Comprehensive List of Clock Drivers](/archives/4.2.6-series/refclock/#comprehensive-list-of-clock-drivers)

* * *

#### Introduction

Drivers for most radio and modem reference clocks is included by default in the NTP distribution. Individual drivers can be activated using <code>server</code> commands as described in the [<code>ntpd</code> program manual page](/archives/4.2.6-series/ntpd/). Drivers have addresses in the form <code>127.127._t.u_</code>, where <code>_t_</code> is the driver type and <code>_u_</code> is a unit number in the range 0-3 to distinguish multiple instances of the same driver. Most drivers require a serial or parallel port or special bus peripheral, but some can work directly from an audio codec or sound card when availble. The particular device is specified by adding a soft link from the name used by the driver to the device name.

All radio clock drivers require that the radio be set for Coordinated Universal Time (UTC) only. Timezone and standard/daylight adjustments are performed by the kernel. There are difference in the various Unix and Windows port interfaces detected at configuration time, so it is important that the NTP daemon and utilities be compiled on the target system or clone.

When a pulse-per-second (PPS) signal is available, the [PPS Clock Discipline](/archives/drivers/driver22/) driver can be used. It normally works in conjunction with the reference clock that produces the signal, but can work with another driver or remote server. When PPS kernel features are present, the driver can redirect the PPS signal to the kernel.

In general, performance can be improved, especially when more than one driver is supported, to use the prefer peer function described in the [Mitigation Rules and the <code>prefer</code> Keyword](/archives/4.2.6-series/prefer/) page. The prefer peer is ordinarily designated the remote peer or local clock driver which provides the best quality time. All other things equal, only the prefer peer is used to discipline the system clock and jitter-producing "clockhopping" between sources is avoided. This is especially valuable when the PPS clock discipline driver is available.

There are audio drivers for each of the NIST time stations WWV and WWVH, Canadian time station CHU and generic IRIG signals. Currently, support for FreeBSD, Solaris and SunOS is in the distribution. It is left to the volunteer corps to confirm this works in other systems. Further information on hookup, debugging and monitoring is given in the [Audio Drivers](/archives/4.2.6-series/audio/) page.

The [Undisciplined Local Clock](/archives/drivers/driver1/) driver can simulate a reference clock when no external synchronization sources are available. If a server with this driver is connected directly or indirectly to the public Internet, there is some danger that it can destabilize other clients. It is not recommended that the local clock driver be used in this way, as the orphan mode descibed on the [Association Management](/archives/4.2.6-series/assoc/) page provides a generic backup capability.

The local clock driver can also be used when an external synchronization source such as the IEEE 1588 Precision Time Protocol or NIST Lockclock directly synchronizes the computer time. Further information is on the [External Clock Discipline and the Local Clock Driver](/archives/4.2.6-series/extern/) page.

* * *

#### Driver Calibration

Some drivers depending on longwave or shortwave radio services need to know the radio propagation time from the transmitter to the receiver. This must be calculated for each specific receiver location and requires the geographic coordinates of both the transmitter and receiver. The transmitter coordinates for various radio services are given in the [Time and Frequency Standard Station Information](/reflib/qth/) page. Receiver coordinates can be obtained locally or from Google Earth. The actual calculations are beyond the scope of this document.

Depending on interface type, port speed, etc., a reference clock can have a small residual offset relative to another. To reduce the effects of jitter when switching from one driver to the another, it is useful to calibrate the drivers to a common ensemble offset. The <code>enable calibrate</code> configuration command described on the [Miscellaneous Options](/archives/4.2.6-series/miscopt/) page activates a special feature which automatically calculates a correction factor for each driver relative to an association designated the prefer peer.

* * *

#### Comprehensive List of Clock Drivers

Following is a list showing the type and title of each driver currently implemented. The compile-time identifier for each is shown in parentheses. Click on a selected type for specific description and configuration documentation, including the clock address, reference ID, driver ID, device name and serial line speed. For those drivers without specific documentation, please contact the author listed in the [Copyright Notice](/archives/4.2.6-series/copyright/) page.

*   [Type 1](/archives/drivers/driver1/) Undisciplined Local Clock (<code>LOCAL</code>)
*   [Type 2](/archives/drivers/driver2/) Trak 8820 GPS Receiver (<code>GPS_TRAK</code>
*   [Type 3](/archives/drivers/driver3/) PSTI/Traconex 1020 WWV/WWVH Receiver (<code>WWV_PST</code>)
*   [Type 4](/archives/drivers/driver4/) Spectracom WWVB/GPS Receivers (<code>WWVB_SPEC</code>)
*   [Type 5](/archives/drivers/driver5/) TrueTime GPS/GOES/OMEGA Receivers (<code>TRUETIME</code>)
*   [Type 6](/archives/drivers/driver6/) IRIG Audio Decoder (<code>IRIG_AUDIO</code>)
*   [Type 7](/archives/drivers/driver7/) Radio CHU Audio Demodulator/Decoder (<code>CHU</code>)
*   [Type 8](/archives/drivers/driver8/) Generic Reference Driver (<code>PARSE</code>)
*   [Type 9](/archives/drivers/driver9/) Magnavox MX4200 GPS Receiver (<code>GPS_MX4200</code>)
*   [Type 10](/archives/drivers/driver10/) Austron 2200A/2201A GPS Receivers (<code>GPS_AS2201</code>)
*   [Type 11](/archives/drivers/driver11/) Arbiter 1088A/B GPS Receiver (<code>GPS_ARBITER</code>)
*   [Type 12](/archives/drivers/driver12/) KSI/Odetics TPRO/S IRIG Interface (<code>IRIG_TPRO</code>)
*   Type 13 Leitch CSD 5300 Master Clock Controller (<code>ATOM_LEITCH</code>)
*   Type 14 EES M201 MSF Receiver (<code>MSF_EES</code>)
*   Type 15 reserved
*   [Type 16](/archives/drivers/driver16/) Bancomm GPS/IRIG Receiver (<code>GPS_BANCOMM</code>)
*   Type 17 Datum Precision Time System (<code>GPS_DATUM</code>)
*   [Type 18](/archives/drivers/driver18/) NIST/USNO/PTB Modem Time Services (<code>ACTS_MODEM</code>)
*   [Type 19](/archives/drivers/driver19/) Heath WWV/WWVH Receiver (<code>WWV_HEATH</code>)
*   [Type 20](/archives/drivers/driver20/) Generic NMEA GPS Receiver (<code>NMEA</code>)
*   Type 21 TrueTime GPS-VME Interface (<code>GPS_VME</code>)
*   [Type 22](/archives/drivers/driver22/) PPS Clock Discipline (<code>PPS</code>)
*   Type 23 reserved
*   Type 24 reserved
*   Type 25 reserved
*   [Type 26](/archives/drivers/driver26/) Hewlett Packard 58503A GPS Receiver (<code>GPS_HP</code>)
*   [Type 27](/archives/drivers/driver27/) Arcron MSF Receiver (<code>MSF_ARCRON</code>)
*   [Type 28](/archives/drivers/driver28/) Shared Memory Driver (<code>SHM</code>)
*   [Type 29](/archives/drivers/driver29/) Trimble Navigation Palisade GPS (<code>GPS_PALISADE</code>)
*   [Type 30](/archives/drivers/driver30/) Motorola UT Oncore GPS <code>GPS_ONCORE</code>)
*   [Type 31](/archives/drivers/driver31/) Rockwell Jupiter GPS (<code>GPS_JUPITER</code>)
*   [Type 32](/archives/drivers/driver32/) Chrono-log K-series WWVB receiver (<code>CHRONOLOG</code>)
*   [Type 33](/archives/drivers/driver33/) Dumb Clock (<code>DUMBCLOCK</code>)
*   [Type 34](/archives/drivers/driver34/) Ultralink WWVB Receivers (<code>ULINK</code>)
*   [Type 35](/archives/drivers/driver35/) Conrad Parallel Port Radio Clock (<code>PCF</code>)
*   [Type 36](/archives/drivers/driver36/) Radio WWV/H Audio Demodulator/Decoder (<code>WWV</code>)
*   [Type 37](/archives/drivers/driver37/) Forum Graphic GPS Dating station (<code>FG</code>)
*   [Type 38](/archives/drivers/driver38/) hopf GPS/DCF77 6021/komp for Serial Line (<code>HOPF_S</code>)
*   [Type 39](/archives/drivers/driver39/) hopf GPS/DCF77 6039 for PCI-Bus (<code>HOPF_P</code>)
*   [Type 40](/archives/drivers/driver40/) JJY Receivers (<code>JJY</code>)
*   Type 41 TrueTime 560 IRIG-B Decoder
*   [Type 42](/archives/drivers/driver42/) Zyfer GPStarplus Receiver
*   [Type 43](/archives/drivers/driver43/) RIPE NCC interface for Trimble Palisade
*   [Type 44](/archives/drivers/driver44/) NeoClock4X - DCF77 / TDF serial line