---
title: "7. Reference Clocks"
type: "archives"
---

The NTP software supports different kinds of reference clocks. This section presents various reference clocks. For a more general discussion on the topic see [What is a _reference clock_?](NTP-s-algo.htm#Q-REFCLK).

According to a recent survey[<span class="footnote">[2]</span>](NTP-s-def.htm#FTN.FTN-NTP-SURVEY99), the most popular real reference clocks are:

* GPS
* DCF77
* WWVB

While not the cheapest solution, GPS offers high accuracy without a lot of trickery. DCF77 on the other hand offers very cheap solutions at moderate accuracy.

More information on reference clocks can be found in [Reference Clock Drivers](), http://www.ntp.org/hardware.html, and http://www.boulder.nist.gov/timefreq/general/receiverlist.htm.

1. [No reference clocks](#no-reference-clocks)  
7.1.1. [What is LCL, the Local Clock?](#what-is-lcl-the-local-clock)  
2. [GPS Receivers](#gps-receivers)  
7.2.1. [What should I know about various GPS Receivers?](#what-should-i-know-about-various-gps-receivers)  
7.2.2. [What are these dilution parameters PDOP, TDOP, and GDOP saying?](#what-are-these-dilution-parameters-pdop-tdop-and-gdop-saying)  
7.2.3. [What is NMEA?](#what-is-nmea)  
7.2.4. [What is TSIP?](#what-is-tsip)  
3. [DCF77 Receivers](#dcf77-receivers)  
7.3.1. [What should I know about DCF77 Receivers?](#what-should-i-know-about-dcf77-receivers)  
7.3.2. [What can make my DCF77 Receiver fail?](#what-can-make-my-dcf77-receiver-fail)  
4. [Others](#others)  
7.4.1. [What can make my MSF Receiver fail?](#what-can-make-my-msf-receiver-fail)  
7.4.2. [How can I find a low-cost Receiver for Low-Frequency Transmissions?](#how-can-i-find-a-low-cost-receiver-for-low-frequency-transmissions)

* * *

#### 1. No reference clocks

#### 7.1.1. What is LCL, the Local Clock?

The LCL is no reference clock in reality; instead it simply refers to the system time on the current machine. Therefore it should never be used, except when the system time is synchronized by some means not visible by `xntpd`.

On an isolated network one might set the time manually from time to time. Together with a frequency adjustment available as a [fudge factor](/archives/drivers/driver1/#fudge-factors) one may achieve an accuracy of a few seconds per week.

If you think you really must use LCL, here is how:

<pre>server 127.127.1.1		# LCL, local clock
fudge  127.127.1.1 stratum 12	# increase stratum</pre>

* * *

#### 2. GPS Receivers

#### 7.2.1. What should I know about various GPS Receivers?

GPS receivers have high accuracy, are simple to install, rather immune against electromagnetic noise, and they only need an antenna with free view to the sky, preferrably as much of the hemisphere as possible.[<span class="footnote">[1]</span>](NTP-s-refclk.htm#FTN.AEN4591) Most calibration happens automatically.

GPS, the Global Positioning System, a satellite based navigation aid originally developed for military use in the USA, can provide the receiver with accurate data about the current position, elevation, and time (See also [Section 9.1](NTP-s-related.htm#S-GPS-BACKGROUND)). Unfortunately many of these receivers were not designed with accurate time-keeping in mind. Therefore the time information provided in a stream of serial data sometimes is freely floating within one second, thereby losing the precision of the receiver (Accurate time is needed in the receiver to calculate the exact position. See also [How accurate will my Clock be?](NTP-s-algo.htm#Q-ACCURATE-CLOCK)).

Fortunately there are also receivers that were designed for precision timekeeping. Among these are:

**Table 1. Supported GPS receivers**

| Manufacturer | Model | Driver/Mode | Interface | PPS available |
| ----- | ----- | ----- | ----- | ----- |
| Arbiter | 1088A/B | [11](/archives/drivers/driver11) | serial; 9600 baud | Y |
| Austron | GPS-AS2201 | [10](/archives/drivers/driver10) | serial; 9600 baud | Y
| Garmin | GPS35(25) | [20](/archives/drivers/driver20) | serial, 4800 baud | Y (TTL) |
| [GPSclock](http://www.gpsclock.com/) | 200 | [20](/archives/drivers/driver20) (patched) | serial; 4800 baud | Y |
| Hewlett Packard | 58503A | [26](/archives/drivers/driver26) | serial; 9600 baud | Y |
| Magnavox | GPS-MX4200 | [9](/archives/drivers/driver9) | serial; 4800 baud | Y |
| [Meinberg](http://www.meinberg.de/) | GPS166, GPS167 | [8](/archives/drivers/driver8) | serial; 9600 baud | Y |
| Trak(?) | 8810, 8820 | [2](/archives/drivers/driver2) | serial; 9600 baud | Y |
| Trimble | Acutime 2000<sup>a</sup> | [8](/archives/drivers/driver8), [10](/archives/drivers/driver10), [29](/archives/drivers/driver29) | TSIP | Y (TTL |
| Trimble | Palisade<sup>b</sup> | [8](/archives/drivers/driver8), [10](/archives/drivers/driver10), [29](/archives/drivers/driver29) | serial; | ? |
| Trimble | SV6<sup>b</sup> | [8](/archives/drivers/driver8), [9](/archives/drivers/driver9), [10](/archives/drivers/driver10) | TAIP, TSIP | Y |

**<sup>a</sup>** This SmartAntenna is the replacement for both, the SV6 and the  Palisade.  

**<sup>b</sup>** The device is no longer manufactured.

XXX _Note from the editor:_ The table above is quite incomplete. Contributors for missing entries are very much invited.

* * *

#### 7.2.2. What are these dilution parameters PDOP, TDOP, and GDOP saying?

These parameters qualify the accuracy of a GPS receiver. The following is a translation of an explanation given by Martin Burnicki: "The _dilution_ values have no units, and they are computed from the position of the satellites relative to the position of the receiver's antenna. Small values express high precision. The values are computed using an inversion of a 4x4 matrix containing the cosinus values of the angles between the antenna and the satellites. There are four values `dx`, `dy`, `dz`, and `dt` that contribute to the dilution values in the following manner:"

**Table 2. Dilution of Precision**

| Parameter | Value |
| ----- | ----- |
| Horizontal | HDOP = sqrt(dx^2 + dy^2) |
| Vertical | VDOP = dz |
| Position | PDOP = sqrt(dx^2 + dy^2 + dz^2) |
| Time | TDOP = dt |
| General | GDOP = sqrt(dx^2 + dy^2 + dz^2 + dt^2) |


* * *

#### 7.2.3.What is NMEA?

Many GPS receivers use a standardized format of output called NMEA 0183. The acronym stands for National Marine Electronics Association, thus indicating the intended purpose of the protocol, namely the navigation of ships.

NMEA defines several message types, each message being an ASCII string transmitted at 4800 baud. Each message starts with `$` char and ends with <code>\<CR>\<LF></code>. A five-digit message identifier (for instance `$GPRMC`) specifies source and type of the message. Parameters for that message are separated by `,` (comma).

For the purpose of keeping time, the `GPRMC` (GPS recommended minimum data) message contains the current time in second resolution, receiver status, latitude, longitude, speed over ground, heading (track), date, magnetic variation in degrees, and a checksum. That message is either sent automatically every second, or upon request.

Message type `GPGSA` contains the receiver's mode, number of satellites, and quality of the solution (dilution of precision, DOP). Precise information about the position can be found in the `GPGGA` message.

NMEA is commonly used together with PPS, because the messages seem to be sent with low accuracy regarding the start of a second.

* * *

#### 7.2.4. What is TSIP?

TSIP stands for Trimble Standard Interface Protocol, and it is used in products from Trimble. The documented binary protocol exchanges packets over serial lines. This allows embedded devices to be monitored, queried and controlled exclusively by TSIP, not needing any switches or displays.

* * *

#### 3. DCF77 Receivers

#### 7.3.1. What should I know about DCF77 Receivers?

In comparison to GPS, DCF77 receivers are cheap, and they don't need an antenna with a view at the sky.

Germany has a highly accurate clock and a long-wave transmitter that sends out time data at 77.5kHz. This service is commonly known as DCF77. Time is taken from the German UTC contributor PTB (Physikalisch Technische Bundesanstalt) in Braunschweig. The sender located in Mainflingen (50:01N 9:00E)[<span class="footnote">[2]</span>](NTP-s-refclk.htm#FTN.AEN4810) can be received even in a distance of up to 1000km as the waves easily pass obstacles in the line of sight. The delay of the signal, a few milliseconds, caused by the distance between transmitter and receiver should be compensated manually.

In addition the demodulation of the time signal can be done easily in very cheap receivers (20DEM or similar). Thus these receivers are quite popular in Germany and its neighbourhood. That type of receivers are typically powered from a serial port, just like a serial mouse. The output signal carries pulses of 100 and 200ms, starting at the beginning of a second, and encoding one bit. There is no pulse for the last second of each minute. Those can be feed into an UART that decodes the pulses as characters received at 50 baud. The best signal quality can be achieved if the antenna of the receiver is oriented tangential to the transmitter's antenna.

Because of the simple AM modulation, the demodulation is sensitive to spikes and varying receive conditions. Accuracy is typically only around 3ms. Trying to make the resolution higher will increase the receiver's sensitivity for noise and spikes that are around anyway. There's also a FM[<span class="footnote">[3]</span>](NTP-s-refclk.htm#FTN.AEN4818) modulation (pseudo-random phase noise) in the signal that can be decoded by sophisticated and expensive receivers. These receivers can achieve a resolution of 50µs.

The data format transmits 59 bits per minute. These bits that start every second, only when the minute is complete no bit is transmitted. Therefore it takes at least one minute until the time and date have been successfully transmitted. As the data format has little redundancy, most receivers wait until two consistent time messages have been decoded without error. Typically it takes between two and three minutes until the receiver is synchronized.

* * *

#### 7.3.2. What can make my DCF77 Receiver fail?

Besides the fact that the huge[<span class="footnote">[4]</span>](NTP-s-refclk.htm#FTN.AEN4833) antenna (and its backup) of the sender is turned off for maintenance occasionally, there are a few other reasons why DCF77 reception may be impossible:[<span class="footnote">[5]</span>](NTP-s-refclk.htm#FTN.AEN4836)

*   The sending antenna may be turned off during thunderstorms to avoid the risk of electrical damage.
*   Lightning itself may cause spikes on the received signal.
*   High-power devices like refrigerators, ovens, etc. may cause spikes on the received signal when turning on or off.
*   Changes in the atmosphere (or is it ionosphere?) (especially during sunrise and sunset) are said to have a bad influence on the signal.
*   Electrical equipment close to the receiver's antenna may distort the signal. Such equipment can be:
    * video recorders (even when operating in standby mode<
    *  TV sets
    *  computer monitors operating at lower resolutions (Specifically so-called multi-sync monitors when switching frequencies can cause short spikes on the signal)
    * uninterruptible power supplies (especially those made by MGE UPS Systems, like the Comet S31 10kVA)
    * switching power supplies (operating near 60kHz)
*   Metal parts close to the ferrite loopstick may detune it
*   Huge metal constructions can have a negative impact on the signal reception inside (Faraday shield)

* * *

#### 4. Others

XXX _Note from the editor:_ Other types of reference clocks are still to come (are missing now). Contributors invited!

#### 7.4.1. What can make my MSF Receiver fail?

See [Q: 7.3.2.](NTP-s-refclk.htm#Q-REFCLK-DCF77-NOSIGNAL) for some basics.

* * *

#### 7.4.2. How can I find a low-cost Receiver for Low-Frequency Transmissions?

[Markus Kuhn](NTP-a-faq.htm#AU-MK) has set up a page describing low-frequency time standards (WWVB, MSF, DCF77, etc) and receiver designs at http://www.cl.cam.ac.uk/~mgk25/lf-clocks.html.

* * *

#### 7.1. Products

This section will provide rudimentary resources to find a reference clock for NTP.

* * *

#### 7.1.1. Where can I find a reference clock for NTP?

The easiest way to find a suitable reference clock seems to be the following:

*   Use one of the models mentioned in the documentation (e.g. Table 1).
*   Use a model that someone else is already using with success.

In addition to these hints and the [hardware[(/hardware) information, there are some additional resources like http://www.boulder.nist.gov/timefreq/general/receiverlist.htm and http://www.ieee-uffc.org/freqcontrol/piezo.html.

* * *

#### Notes

[<span class="footnote">[1]</span>](NTP-s-refclk.htm#AEN4591)

There is some planning software available at http://www.trimble.com/planningsoftware.html. That software could be used to explain periodic dropouts when only a limited view to the sky is available. An anonymous contributor added: "After installing the software be sure to import the ephemeris file using Almanac ->Import ->SSF and set your station location using File ->Station."

[<span class="footnote">[2]</span>](NTP-s-refclk.htm#AEN4810)

Near Frankfurt am Main

[<span class="footnote">[3]</span>](NTP-s-refclk.htm#AEN4818)

As [Mark Martinec](NTP-a-faq.htm#AU-MM) points out, it's actually PSK (phase shift keying) (see http://www.ptb.de/english/org/4/43/433/disse.htm. I'm assuming the typical audience will neither care nor be able to build such a thing, so please forgive me!.

[<span class="footnote">[4]</span>](NTP-s-refclk.htm#AEN4833)

Flying above Frankfurt, I once thought I've seen the two huge piles of the antenna.

[<span class="footnote">[5]</span>](NTP-s-refclk.htm#AEN4836)

The following list possibly applies to other low-frequency receivers (like MSF) as well.