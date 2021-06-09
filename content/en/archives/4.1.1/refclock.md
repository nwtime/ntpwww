---
title: "Reference Clock Drivers"
type: archives
---

![gif](/archives/pic/stack1a.jpg) Master Time Facility at the [UDel Internet Research Laboratory](http://www.eecis.udel.edu/%7emills/lab.html)

* * *

#### Table of Contents

*   [Reference Clock Drivers](/archives/4.1.1/refclock/#reference-clock-drivers)
*   [Driver Calibration](/archives/4.1.1/refclock/#driver-calibration)
*   [Performance Enhancements](/archives/4.1.1/refclock/#performance-enhancements)
*   [Comprehensive List of Clock Drivers](/archives/4.1.1/refclock/#comprehensive-list-of-clock-drivers)

* * *

#### Reference Clock Drivers

Support for most of the commonly available radio and modem reference clocks is included in the default configuration of the NTP daemon for Unix <tt>ntpd</tt>. Individual clocks can be activated by configuration file commands, specifically the <tt>server</tt> and <tt>fudge</tt> commands described in the [<tt>ntpd</tt> program manual page](/archives/4.1.1/ntpd). The following discussion presents Information on how to select and configure the device drivers in a running Unix system.

Many radio reference clocks can be set to display local time as adjusted for timezone and daylight saving mode. For use with NTP the clock must be set for Coordinated Universal Time (UTC) only. Ordinarily, these adjustments are performed by the kernel, so the fact that the clock runs on UTC will be transparent to the user.

Radio and modem clocks by convention have addresses in the form 127.127._t.u_, where _t_ is the clock type and _u_ is a unit number in the range 0-3 used to distinguish multiple instances of clocks of the same type. Most of these clocks require support in the form of a serial port or special bus peripheral, but some can work directly from the audio codec found in some workstations. The particular device is normally specified by adding a soft link <tt>/dev/device_u_</tt> to the particular hardware device involved, where _<tt>u</tt>_ correspond to the unit number above.

Most clock drivers communicate with the reference clock using a serial port, usually at 9600 bps. There are several application program interfaces (API) used in the various Unix and NT systems, most of which can be detected at configuration time. Thus, it is important that the NTP daemon and utilities be compiled on the target system or clone. In some cases special features are available, such as timestamping in the kernel or pulse-per-second (PPS) interface. In most cases these features can be detected at configuration time as well; however, the kernel may have to be recompiled in order for them to work.

The audio drivers are a special case. These include support for the NIST time/frequency stations WWV and WWVH, the Canadian time/frequency station CHU and generic IRIG signals. Currently, support for the Solaris and SunOS audio API is included in the distribution. It is left to the volunteer corps to extend this support to other systems. Further information on hookup, debugging and monitoring is given in the [Audio Drivers](/archives/4.1.1/audio) page.

The local clock driver is also a special case. A server configured with this driver can operate as a primary server to synchronize other clients when no other external synchronization sources are available. If the server is connected directly or indirectly to the public Internet, there is some danger that it can adversely affect the operation of unrelated clients. Carefully read the [Undisciplined Local Clock](/archives/drivers/driver1) page and respect the stratum limit.

The local clock driver also supports an external synchronization source such as a high resolution counter disciplined by a GPS receiver, for example. Further information is on the [External Clock Discipline and the Local Clock Driver](/archives/4.1.1/extern) page.

* * *

#### Driver Calibration

Some drivers depending on longwave and shortwave radio services need to know the radio propagation time from the transmitter to the receiver, which can amount to some tens of milliseconds. This must be calculated for each specific receiver location and requires the geographic coordinates of both the transmitter and receiver. The transmitter coordinates for various radio services are given in the [Stations, Frequencies and Geographic Coordinates ](/archives/4.1.1/qth) page. Receiver coordinates can be obtained or estimated from various sources. The actual calculations are beyond the scope of this document.

When more than one clock driver is supported, it is often the case that each shows small systematic offset differences relative to the rest. To reduce the effects of jitter when switching from one driver to the another, it is useful to calibrate the drivers to a common ensemble offset. The <tt>enable calibrate</tt> configuration command in the [Miscellaneous Options](/archives/4.1.1/miscopt) page is useful for this purpose. The calibration function can also be enabled and disabled using the <tt>ntpdc</tt> program utility.

Most clock drivers use the <tt>time1</tt> value specified in the <tt>fudge</tt> configuration command to provide the calibration correction when this cannot be provided by the clock or interface. When the calibration function is enabled, the <tt>time1</tt> value is automatically adjusted to match the offset of the remote server or local clock driver selected for synchronization. Ordinarily, the NTP selection algorithm chooses the best from among all sources, usually the best radio clock determined on the basis of stratum, synchronization distance and jitter. The calibration function adjusts the <tt>time1</tt> values for all clock drivers except this source so that their indicated offsets tend to zero. If the selected source is the kernel PPS discipline, the <tt>fudge time1</tt> values for all clock drivers are adjusted.

The adjustment function is an exponential average designed to improve accuracy, so the function takes some time to converge. The recommended procedure is to enable the function, let it run for an hour or so, then edit the configuration file using the <tt>time1</tt> values displayed by the <tt>ntpq</tt> utility and <tt>clockvar</tt> command. Finally, disable the calibration function to avoid possible future disruptions due to misbehaving clocks or drivers.

* * *

#### Performance Enhancements

In general, performance can be improved, especially when more than one clock driver is supported, to use the prefer peer function described in the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.1.1/prefer) page. The prefer peer is ordinarily designated the remote peer or local clock driver which provides the best quality time. All other things equal, only the prefer peer source is used to discipline the system clock and jitter-producing "clockhopping" between sources is avoided. This is valuable when more than one clock driver is present and especially valuable when the PPS clock driver (type 22) is used. Support for PPS signals is summarized in the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.1.1/pps) page.

Where the highest performance is required, generally better than one millisecond, additional hardware and/or software functions may be required. Kernel modifications for precision time are described in the [A Kernel Model for Precision Timekeeping](/archives/4.1.1/kern) page. Special line discipline and streams modules for use in capturing precision timestamps are described in the [Line Disciplines and Streams Drivers](/archives/4.1.1/ldisc) page.

* * *

#### Comprehensive List of Clock Drivers

Following is a list showing the type and title of each driver currently implemented. The compile-time identifier for each is shown in parentheses. Click on a selected type for specific description and configuration documentation, including the clock address, reference ID, driver ID, device name and serial line speed. For those drivers without specific documentation, please contact the author listed in the [Copyright Notice](/archives/4.1.1/copyright) page.

*   [Type 1](/archives/drivers/driver1) Undisciplined Local Clock (<tt>LOCAL</tt>)
*   [Type 2](/archives/drivers/driver2) Trak 8820 GPS Receiver (<tt>GPS_TRAK</tt>
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
*   [Type 15](/archives/drivers/driver5) * TrueTime generic receivers 
*   [Type 16](/archives/drivers/driver16) Bancomm GPS/IRIG Receiver (<tt>GPS_BANCOMM</tt>)
*   Type 17 Datum Precision Time System (<tt>GPS_DATUM</tt>)
*   [Type 18](/archives/drivers/driver18) NIST/USNO/PTB Modem Time Services (<tt>ACTS_MODEM</tt>)
*   [Type 19](/archives/drivers/driver19) Heath WWV/WWVH Receiver (<tt>WWV_HEATH</tt>)
*   [Type 20](/archives/drivers/driver20) Generic NMEA GPS Receiver (<tt>NMEA</tt>)
*   Type 21 TrueTime GPS-VME Interface (<tt>GPS_VME</tt>)
*   [Type 22](/archives/drivers/driver22) PPS Clock Discipline (<tt>PPS</tt>)
*   [Type 23](/archives/drivers/driver23) PTB Modem Time Service (<tt>ACTS_PTB</tt>) 
*   [Type 24](/archives/drivers/driver24) USNO Modem Time Service (<tt>ACTS_USNO</tt>)
*   [Type 25](/archives/drivers/driver5) * TrueTime generic receivers
*   [Type 26](/archives/drivers/driver26) Hewlett Packard 58503A GPS Receiver (<tt>GPS_HP</tt>)
*   [Type 27](/archives/drivers/driver27) Arcron MSF Receiver (<tt>MSF_ARCRON</tt>)
*   [Type 28](/archives/drivers/driver28) Shared Memory Driver (<tt>SHM</tt>)
*   [Type 29](/archives/drivers/driver29) Trimble Navigation Palisade GPS (<tt>GPS_PALISADE</tt>)
*   [Type 30](/archives/drivers/driver30) Motorola UT Oncore GPS <tt>GPS_ONCORE</tt>)
*   Type 31 Rockwell Jupiter GPS (<tt>GPS_JUPITER</tt>)
*   [Type 32](/archives/drivers/driver32) Chrono-log K-series WWVB receiver (<tt>CHRONOLOG</tt>)
*   [Type 33](/archives/drivers/driver33) Dumb Clock (<tt>DUMBCLOCK</tt>)
*   [Type 34](/archives/drivers/driver34) Ultralink WWVB Receivers (<tt>ULINK</tt>)
*   [Type 35](/archives/drivers/driver35) Conrad Parallel Port Radio Clock (<tt>PCF</tt>)
*   [Type 36](/archives/drivers/driver36) Radio WWV/H Audio Demodulator/Decoder (<tt>WWV</tt>)
*   [Type 37](/archives/drivers/driver37) Forum Graphic GPS Dating station (<tt>FG</tt>)
*   [Type 38](/archives/drivers/driver38) hopf GPS/DCF77 6021/komp for Serial Line (<tt>HOPF_S</tt>)
*   [Type 39](/archives/drivers/driver39) hopf GPS/DCF77 6039 for PCI-Bus (<tt>HOPF_P</tt>)
*   [Type 40](/archives/drivers/driver40) JJY Receivers (<tt>JJY</tt>)

\* All TrueTime receivers are now supported by one driver, type 5. Types 15 and 25 will be retained only for a limited time and may be reassigned in future.