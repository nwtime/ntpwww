---
title: "7. Reference Clocks"
description: "The NTP software supports different kinds of reference clocks. This section of the NTP FAQ presents various reference clocks."
type: "archives"
---

7.1 [What is LCL, the Local Clock?](#71-what-is-lcl-the-local-clock)  
7.2 [GPS Receivers](#72-gps-receivers)  
7.2.1 [What should I know about various GPS Receivers?](#721-what-should-i-know-about-various-gps-receivers)  
7.2.2 [What are PDOP, TDOP, and GDOP?](#722-what-are-pdop-tdop-and-gdop)  
7.2.3 [What is NMEA?](#723-what-is-nmea)  
7.2.4 [What is TSIP?](#724-what-is-tsip)  
7.3 [DCF77 Receivers](#73-dcf77-receivers)  
7.3.1 [What should I know about DCF77 Receivers?](#731-what-should-i-know-about-dcf77-receivers)  
7.3.2 [What can make my DCF77 Receiver fail?](#732-what-can-make-my-dcf77-receiver-fail)  
7.4 [Other Receivers](#74-other-receivers)  
7.4.1 [What can make my MSF Receiver fail?](#741-what-can-make-my-msf-receiver-fail)  
7.4.2 [How can I find a low-cost Receiver for Low-Frequency Transmissions?](#742-how-can-i-find-a-low-cost-receiver-for-low-frequency-transmissions)  
7.5 [Products](#75-products)  
7.5.1 [Where can I find a reference clock for NTP?](#751-where-can-i-find-a-reference-clock-for-ntp)  

* * *

The NTP software supports different kinds of [reference clocks](/ntpfaq/ntp-s-algo/#5111-what-is-a-reference-clock). This section presents various reference clocks.

According to a [survey](/reflib/reports/ntp-survey99-minar.pdf), the most popular real reference clocks are:

* [GPS](/ntpfaq/ntp-s-related/#91-gps/)
* [DCF77](https://en.wikipedia.org/wiki/DCF77)
* [WWVB](https://en.wikipedia.org/wiki/WWVB)

While not the cheapest solution, GPS offers high accuracy without a lot of trickery. DCF77 on the other hand offers very cheap solutions at moderate accuracy.

More information on reference clocks can be found in [Reference Clock](/documentation/4.2.8-series/refclock/) and [NIST's list of receiver manufacturers](https://www.nist.gov/pml/time-and-frequency-division/time-distribution/radio-station-wwv/manufacturers-time-and-frequency).

* * *

#### 7.1 What is LCL, the Local Clock?

The [LCL](/documentation/drivers/driver1/) is not an actual reference clock; instead it simply refers to the system time on the current machine. Therefore it should never be used, except when the system time is synchronized by some means not visible by `ntpd`.

On an isolated network one might set the time manually from time to time. Together with a frequency adjustment available as a [fudge factor](/documentation/drivers/driver1/#fudge-factors) one may achieve an accuracy of a few seconds per week.

If you think you really must use LCL, here is how:

<pre>server 127.127.1.1		# LCL, local clock
fudge  127.127.1.1 stratum 12	# increase stratum</pre>

* * *

#### 7.2 GPS Receivers

#### 7.2.1 What should I know about various GPS Receivers?

GPS receivers have high accuracy, are simple to install, rather immune against electromagnetic noise, and they only need an antenna with free view to the sky, preferrably as much of the hemisphere as possible. Most calibration happens automatically.

[GPS](/ntpfaq/ntp-s-related/#91-gps), the Global Positioning System, a satellite based navigation aid originally developed for military use in the USA, can provide the receiver with accurate data about the current position, elevation, and time. Unfortunately many of these receivers were not designed with accurate time-keeping in mind. Therefore the time information provided in a stream of serial data sometimes is freely floating within one second, thereby losing the precision of the receiver. [Accurate time](/ntpfaq/ntp-s-algo/#5131-how-accurate-will-my-clock-be) is needed in the receiver to calculate the exact position.

Fortunately there are also receivers that were designed for precision timekeeping. Among these are:

**Table 7.2a: Supported GPS receivers**

| Manufacturer | Model | Driver/Mode | Interface | PPS available |
| ----- | ----- | ----- | ----- | ----- |
| Arbiter | 1088A/B | [11](/documentation/drivers/driver11/) | serial; 9600 baud | Y |
| Austron | GPS-AS2201 | [10](/documentation/drivers/driver10/) | serial; 9600 baud | Y
| Garmin | GPS35(25) | [20](/documentation/drivers/driver20/) | serial, 4800 baud | Y (TTL) |
| [GPSclock](http://www.gpsclock.com/) | 200 | [20](/documentation/drivers/driver20/) (patched) | serial; 4800 baud | Y |
| Hewlett Packard | 58503A | [26](/documentation/drivers/driver26/) | serial; 9600 baud | Y |
| Magnavox | GPS-MX4200 | [9](/documentation/drivers/driver9/) | serial; 4800 baud | Y |
| [Meinberg](https://www.meinberg.de/) | GPS166, GPS167 | [8](/documentation/drivers/driver8/) | serial; 9600 baud | Y |
| Trak(?) | 8810, 8820 | [2](/documentation/drivers/driver2/) | serial; 9600 baud | Y |
| Trimble | Acutime 2000<sup>a</sup> | [8](/documentation/drivers/driver8/), [10](/documentation/drivers/driver10/), [29](/documentation/drivers/driver29/) | TSIP | Y (TTL) |
| Trimble | Palisade<sup>b</sup> | [8](/documentation/drivers/driver8/), [10](/documentation/drivers/driver10/), [29](/documentation/drivers/driver29/) | serial; | ? |
| Trimble | SV6<sup>b</sup> | [8](/documentation/drivers/driver8/), [9](/documentation/drivers/driver9/), [10](/documentation/drivers/driver10/) | TAIP, TSIP | Y |

**<sup>a</sup>** This SmartAntenna is the replacement for both, the SV6 and the  Palisade.  

**<sup>b</sup>** The device is no longer manufactured.

* * *

#### 7.2.2 What are PDOP, TDOP, and GDOP?

These dilution parameters qualify the accuracy of a GPS receiver. The following is a translation of an explanation given by Martin Burnicki: "The _dilution_ values have no units, and they are computed from the position of the satellites relative to the position of the receiver's antenna. Small values express high precision. The values are computed using an inversion of a 4x4 matrix containing the cosinus values of the angles between the antenna and the satellites. There are four values `dx`, `dy`, `dz`, and `dt` that contribute to the dilution values in the following manner:"

**Table 7.2b: Dilution of Precision**

| Parameter | Value |
| ----- | ----- |
| Horizontal | HDOP = sqrt(dx<sup>^</sup>2 + dy<sup>^</sup>2) |
| Vertical | VDOP = dz |
| Position | PDOP = sqrt(dx<sup>^</sup>2 + dy<sup>^</sup>2 + dz<sup>^</sup>2) |
| Time | TDOP = dt |
| General | GDOP = sqrt(dx<sup>^</sup>2 + dy<sup>^</sup>2 + dz<sup>^</sup>2 + dt<sup>^</sup>2) |


* * *

#### 7.2.3 What is NMEA?

Many GPS receivers use a standardized format of output called [NMEA 0183](https://en.wikipedia.org/wiki/NMEA_0183). The acronym stands for National Marine Electronics Association which indicates the intended purpose of the protocol: the navigation of ships.

NMEA defines several message types, each message being an ASCII string transmitted at 4800 baud. Each message starts with `$` char and ends with <code>\<CR>\<LF></code>. A five-digit message identifier (for instance `$GPRMC`) specifies source and type of the message. Parameters for that message are separated by a `,` (comma).

For the purpose of keeping time, the `GPRMC` (GPS recommended minimum data) message contains the current time in second resolution, receiver status, latitude, longitude, speed over ground, heading (track), date, magnetic variation in degrees, and a checksum. That message is either sent automatically every second, or upon request.

Message type `GPGSA` contains the receiver's mode, number of satellites, and quality of the solution (dilution of precision, DOP). Precise information about the position can be found in the `GPGGA` message.

NMEA is commonly used together with [PPS](/ntpfaq/ntp-s-algo-kernel/#523-pps-processing) because the messages seem to be sent with low accuracy regarding the start of a second.

* * *

#### 7.2.4 What is TSIP?

TSIP stands for Trimble Standard Interface Protocol, and it is used in products from [Trimble](https://www.trimble.com/). The documented binary protocol exchanges packets over serial lines. This allows embedded devices to be monitored, queried and controlled exclusively by TSIP, not needing any switches or displays.

* * *

#### 7.3 DCF77 Receivers

#### 7.3.1 What should I know about DCF77 Receivers?

In comparison to GPS, DCF77 receivers are inexpensive and they don't need an antenna with a view at the sky.

Germany has a highly accurate clock and a long-wave transmitter that sends out time data at 77.5kHz. This service is commonly known as DCF77. Time is taken from the German UTC contributor [PTB](https://www.ptb.de/cms/en.html) (Physikalisch Technische Bundesanstalt) in Braunschweig. The sender located in Mainflingen (50:01N 9:00E) (near Frankfurt am Main) can be received even in a distance of up to 1000km as the waves easily pass obstacles in the line of sight. The delay of the signal, a few milliseconds, caused by the distance between transmitter and receiver should be compensated manually.

Since the demodulation of the time signal can be done easily using cheap receivers, these receivers are quite popular in Germany. Receivers are typically powered from a serial port. The output signal carries pulses of 100 and 200ms, starting at the beginning of a second, and encoding one bit. There is no pulse for the last second of each minute. Those can be fed into an UART that decodes the pulses as characters received at 50 baud. The best signal quality can be achieved if the antenna of the receiver is oriented tangential to the transmitter's antenna.

Because of the simple AM modulation, the demodulation is sensitive to spikes and varying receive conditions. Accuracy is typically only around 3ms. Trying to make the resolution higher will increase the receiver's sensitivity to noise and spikes. There's also a FM modulation (pseudo-random phase noise) in the signal that can be decoded by sophisticated and expensive receivers. These receivers can achieve a resolution of 50&mu;s.

> As [Mark Martinec](mailto:mark.martinec@ijs.si) points out, it's actually PSK (phase shift keying). Refer to [Time and Frequency Dissemination with DCF77](https://www.ptb.de/cms/fileadmin/internet/fachabteilungen/abteilung_4/4.4_zeit_und_frequenz/pdf/2011_PTBMitt_50a_DCF77_engl.pdf) for the technical details.

The data format transmits 59 bits per minute: one every second, except for the last second of the minute. Therefore it takes at least one minute until the time and date have been successfully transmitted. As the data format has little redundancy, most receivers wait until two consistent time messages have been decoded without error. Typically it takes between two and three minutes until the receiver is synchronized.

* * *

#### 7.3.2 What can make my DCF77 Receiver fail?

Occasionally the huge antenna and its backup are turned off for maintenance. There are a few other reasons why DCF77 reception may be impossible. The following list possibly applies to other low-frequency receivers (like MSF) as well:

*   The sending antenna may be turned off during thunderstorms to avoid the risk of electrical damage.
*   Lightning itself may cause spikes on the received signal.
*   High-power devices like refrigerators or ovens may cause spikes on the received signal when turned on or off.
*   Changes in the atmosphere or ionosphere, especially during sunrise and sunset, can influence the signal.
*   Electrical equipment close to the receiver's antenna may distort the signal. Such equipment can be:
    * video recorders (even when operating in standby mode)
    *  TV sets
    *  computer monitors operating at lower resolutions; specifically multi-sync monitors when switching frequencies can cause short spikes on the signal
    * uninterruptible power supplies (especially those made by MGE UPS Systems, like the Comet S31 10kVA)
    * switching power supplies (operating near 60kHz)
*   Metal parts close to the ferrite loopstick may detune it.
*   Huge metal constructions can have a negative impact on the signal reception inside (Faraday shield).

* * *

#### 7.4 Other Receivers


#### 7.4.1 What can make my MSF Receiver fail?

See [Q: 7.3.2](/ntpfaq/ntp-s-refclk/#732-what-can-make-my-dcf77-receiver-fail) for some basics.

* * *

#### 7.4.2 How can I find a low-cost Receiver for Low-Frequency Transmissions?

[Markus Kuhn](mailto:mgk25@cl.cam.ac.uk) has set up a [page](https://www.cl.cam.ac.uk/~mgk25/time/lf-clocks/) describing low-frequency time standards (WWVB, MSF, DCF77) and receiver designs.

* * *

#### 7.5 Products

This section will provide rudimentary resources to find a reference clock for NTP.

* * *

#### 7.5.1 Where can I find a reference clock for NTP?

The easiest way to find a suitable reference clock seems to be the following:

*   Use one of the models mentioned in the documentation or [Table 7.2a](#721-what-should-i-know-about-various-gps-receivers).
*   Use a model that someone else is already using with success.