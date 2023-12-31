---
title: "Reference Clock Audio Drivers"
type: archives
noindex: true 
sitemap_exclude: true
---

![webp](/documentation/pic/radio2.webp) ICOM R-72 shortwave receiver and Sure audio mixer

* * *

#### Table of Contents

*   [Sound Card Drivers](/documentation/4.1.2/audio/#sound-card-drivers)
*   [Shortwave Radio Drivers](/documentation/4.1.2/audio/#shortwave-radio-drivers)
*   [Debugging Aids](/documentation/4.1.2/audio/#debugging-aids)

* * *

#### Sound Card Drivers

There are some applications in which the computer time can be disciplined to an audio signal, rather than a serial timecode and communications port or special purpose bus peripheral. This is useful in such cases where the audio signal is sent over a telephone circuit, for example, or received directly from a shortwave receiver. In such cases the audio signal can be connected via an ordinary sound card or baseboard audio codec. The suite of NTP reference clock drivers currently includes three drivers suitable for these applications. They include a driver for the Inter Range Instrumentation Group (IRIG) signals produced by many radio clocks and timing devices, another for the Canadian time/frequency radio station CHU and a third for the NIST time/frequency radio stations WWV and WWVH. The radio drivers are designed to work with ordinary inexpensive shortwave radios and may be one of the least expensive ways to build a good primary time server.

All three drivers make ample use of sophisticated digital signal processing algorithms designed to efficiently extract timing signals from noise and interference. The radio station drivers in particular implement optimum linear demodulation and decoding techniques, including maximum likelihood and soft-decision methods. The documentation page for each driver contains an in-depth discussion on the algorithms and performance expectations. In some cases the algorithms are further analyzed, modelled and evaluated in a technical report.

Currently, the audio drivers are compatible with Sun operating systems, including Solaris and SunOS, and the native audio codec interface supported by these systems. In fact, the interface is quite generic and support for other systems, in particular the various Unix generics, should not be difficult. Volunteers are solicited.

The audio drivers include a number of common features designed to groom input signals, suppress spikes and normalize signal levels. An automatic gain control (AGC) feature provides protection against overdriven or underdriven input signals. It is designed to maintain adequate demodulator signal amplitude while avoiding occasional noise spikes. In order to assure reliable operation, the signal level must be in the range where the audio gain control is effective. In general, this means the input signal level must be such as to cause the AGC to set the gain somewhere in the middle of the range from 0 to 255, as indicated in the timecode displayed by the <code>ntpq</code> program.

The drivers operate by disciplining a logical clock based on the codec sample clock to the audio signal as received. This is done by stuffing or slipping samples as required to maintain exact frequency to the order of 0.1 PPM. In order for the driver to reliably lock on the audio signal, the sample clock frequency tolerance must be less than 250 PPM (.025 percent) for the IRIG driver and half that for the radio drivers. The largest error observed so far is about 60 PPM, but it is possible some sound cards or codecs may exceed that value.

The drivers include provisions to select the input port and to monitor the input signal. The <code>fudge flag 2</code> selects the microphone port if set to zero or the line-in port if set to one. It does not seem useful to specify the compact disc player port. The <code>fudge flag 3</code> enables the input signal monitor using the previously selected output port and output gain. Both of these flags can be set in the configuration file or remotely using the <code>ntpdc</code> utility program.

* * *

#### Shortwave Radio Drivers

The WWV/H and CHU audio drivers require an external shortwave radio with the radio output - speaker or headphone jack - connected to either the microphone or line-in port on the computer. There is some degree of art in setting up the radio and antenna and getting the setup to work. While the drivers are highly sophisticated and efficient in extracting timing signals from noise and interference, it always helps to have as clear a signal as possible.

The most important factor affecting the radio signal is the antenna. It need not be long - even 15 feet is enough if it is located outside of a metal frame building, preferably on the roof, and away from metallic objects. An ordinary CB whip mounted on a PVC pipe and wooden X-frame on the roof should work well with most portable radios, as they are optimized for small antennas.

The radio need not be located near the computer; in fact, it generally works better if the radio is outside the near field of computers and other electromagnetic noisemakers. It can be in the elevator penthouse connected by house wiring, which can also be used to power the radio. A couple of center-tapped audio transformers will minimize noise pickup and provide phantom power to the radio with return via the AC neutral wire.

The WWV/H and CHU transmitters operate on several frequencies simultaneously, so that in most parts of North America at least one frequency supports propagation to the receiver location at any given hour. While both drivers support the ICOM CI-V radio interface and can tune the radio automatically, computer-tunable radios are expensive and probably not cost effective compared to a GPS receiver. So, the radio frequency must usually be fixed and chosen by compromise.

Shortwave (3-30 MHz) radio propagation phenomena are well known to shortwave enthusiasts. The phenomena generally obey the following rules:

* The optimum frequency is higher in daytime than nighttime, stays high longer on summer days and low longer on winter nights.
* Transitions between daytime and nightime conditions generally occur somewhat after sunrise and sunset at the midpoint of the path from transmitter to receiver.
* Ambient noise (static) on the lower frequencies follows the thunderstorm season, so is higher on summer afternoons and evenings.
* The lower frequency bands are best for shorter distances, while the higher bands are best for longer distances.
* The optimum frequencies are higher at the peak of the 11-year sunspot cycle and lower at the trough. The current sunspot cycle should peak in the first couple of years beginning the century. 

The best way to choose a frequency is to listen at various times over the day and determine the best highest (daytime) and lowest (nighttime) frequencies. Then, assuming one is available, choose the highest frequency between these frequencies. This strategy assumes that the high frequency is more problematic than the low, that the low frequency probably comes with severe multipath and static, and insures that probably twice a day the chosen frequency will work. For instance, on the east coast the best compromise CHU frequency is probably 7335 kHz and the best WWV frequency is probably 15 MHz.

* * *

#### Debugging Aids

The audio drivers include extensive setup and debugging support to help hook up the audio signals and monitor the driver operations. The documentation page for each driver describes the various messages that can be produced either in real time or written to the <code>clockstats</code> file for later analysis. Of particular help in verifying signal connections and compatibility is a provision to monitor the signal via headphones or speaker.

The drivers write a synthesized timecode to the <code>clockstats</code> file each time the clock is set or verified and at other times if verbose monitoring is enabled. The format includes several fixed-length fields defining the Gregorian time to the millisecond, together with additional variable-length fields specific to each driver. The data include the intervals since the clock was last set or verified, the audio gain and various state variables and counters specific to each driver.