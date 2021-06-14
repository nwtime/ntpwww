---
title: "Reference Clock Drivers"
type: archives
---

#### Reference Clock Drivers

Support for most of the commonly available radio and modem clocks is included in the default configuration of the NTP daemon for Unix <tt>xntpd</tt>. Individual clocks can be activated by configuration file commands, specifically the <tt>server</tt> and <tt>fudge</tt> commands described in the [<tt>xntpd</tt> program manual page](/archives/3-5.93e/xntpd). The following discussion presents Information on how to select and configure the device drivers in a running Unix system.

Radio and modem clocks by convention have addresses in the form 127.127._t.u_, where _t_ is the clock type and _u_ is a unit number in the range 0-3 used to distinguish multiple instances of clocks of the same type. Most of these clocks require support in the form of a serial port or special bus peripheral. The particular device is normally specified by adding a soft link <tt>/dev/device_u_</tt> to the particular hardware device involved, where _<tt>u</tt>_ correspond to the unit number above.

Following is a list showing the type and title of each driver currently implemented. The compile-time identifier for each is shown in parentheses. Click on a selected type for specific description and configuration documentation, including the clock address, reference ID, driver ID, serial port device name and speed, and features (line disciplines, etc.). For those drivers without specific documentation, please contact the author listed in the [Copyright Notice](/archives/3-5.93e/copyright) page.

*   [Type 1](/archives/3-5.93e/driver1) Local Clock Driver (<tt>LOCAL_CLOCK</tt>)
*   [Type 2](/archives/drivers/driver2) Trak 8820 GPS Receiver (<tt>TRAK</tt>
*   [Type 3](/archives/drivers/driver3) PSTI/Traconex 1020 WWV/WWVH Receiver (<tt>PST</tt>)
*   [Type 4](/archives/3-5.93e/driver4) Spectracom 8170 and Netclock/2 WWVB Receivers (<tt>WWVB</tt>)
*   [Type 5](/archives/3-5.93e/driver5) TrueTime GPS/GOES/OMEGA Receivers (<tt>TRUETIME</tt>)
*   [Type 6](/archives/3-5.93e/driver6) IRIG Audio Decoder (Sun only) (<tt>IRIG</tt>)
*   [Type 7](/archives/3-5.93e/driver7) Scratchbuilt CHU Receiver (<tt>CHU</tt>)
*   [Type 8](/archives/3-5.93e/driver8) Generic Reference Driver (<tt>PARSE</tt>)
*   [Type 9](/archives/3-5.93e/driver9) Magnavox MX4200 GPS Receiver (<tt>MX4200</tt>)
*   [Type 10](/archives/3-5.93e/driver10) Austron 2200A/2201A GPS Receivers (<tt>GPS_AS2201</tt>)
*   [Type 11](/archives/3-5.93e/driver11) Arbiter 1088A/B GPS Receiver (<tt>ARBITER</tt>)
*   [Type 12](/archives/3-5.93e/driver12) KSI/Odetics TPRO/S IRIG Interface (Sun only) (<tt>TPRO</tt>)
*   Type 13 Leitch CSD 5300 Master Clock Controller (<tt>LEITCH</tt>)
*   Type 14 EES M201 MSF Receiver (<tt>MSFEES</tt>)
*   [Type 15](/archives/3-5.93e/driver5) * TrueTime TM-TMD GPS Receiver
*   Type 16 Bancomm GPS/IRIG Receiver (HP only) (<tt>BANC</tt>)
*   Type 17 Datum Precision Time System (<tt>DATUM</tt>)
*   [Type 18](/archives/3-5.93e/driver18) NIST Modem Time Services (<tt>ACTS</tt>)
*   [Type 19](/archives/3-5.93e/driver19) Heath WWV/WWVH Receiver (<tt>WWV_HEATH</tt>)
*   [Type 20](/archives/3-5.93e/driver20) Generic NMEA GPS Receiver (<tt>NMEA</tt>)
*   Type 21 TrueTime GPS-VME Interface (HP only) (<tt>GPSVME</tt>)
*   [Type 22](/archives/3-5.93e/driver22) PPS Clock Discipline (<tt>ATOM</tt>)
*   [Type 23](/archives/3-5.93e/driver23) PTB Modem Time Service (<tt>PTBACTS</tt>) 
*   [Type 24](/archives/3-5.93e/driver24) USNO Modem Time Service (<tt>USNO</tt>)
*   [Type 25](/archives/3-5.93e/driver5) * TrueTime generic receivers
*   [Type 26](/archives/3-5.93e/driver26) Hewlett Packard 58503A GPS Receiver (<tt>HPGPS</tt>)
*   [Type 27](/archives/3-5.93e/driver27) Arcron MSF Receiver (<tt>ARCRON_MSF</tt>)
*   [Type 28](/archives/3-5.93e/driver28) Shared Memory Driver (<tt>SHM</tt>)

\* All TrueTime receivers are now supported by one driver, type 5. Types 15 and 25 will be retained only for a limited time and may be reassigned in future.