---
title: "Radio WWV/H Audio Demodulator/Decoder"
description: "The Radio WWV/H Audio Demodulator/Decoder driver synchronizes the computer time using shortwave radio transmissions from NIST time/frequency stations WWV in Ft. Collins, CO, and WWVH in Kauai, HI."
type: archives
---

Author: [David L. Mills](https://www.nwtime.org/tribute-to-david-l-mills/)

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver36/#synopsis)
*   [Description](/documentation/drivers/driver36/#description)
*   [Technical Overview](/documentation/drivers/driver36/#technical-overview)
*   [Baseband Signal Processing](/documentation/drivers/driver36/#baseband-signal-processing)
*   [Maximum-Likelihood Decoder](/documentation/drivers/driver36/#maximum-likelihood-decoder)
*   [Master Clock Discipline](/documentation/drivers/driver36/#master-clock-discipline)
*   [Station Identification](/documentation/drivers/driver36/#station-identification)
*   [Performance](/documentation/drivers/driver36/#performance)
*   [Program Operation](/documentation/drivers/driver36/#program-operation)
*   [Autotune](/documentation/drivers/driver36/#autotune)
*   [Debugging Aids](/documentation/drivers/driver36/#debugging-aids)
*   [Monitor Data](/documentation/drivers/driver36/#monitor-data)
*   [Fudge factors](/documentation/drivers/driver36/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.36._u_</code>

**Reference ID:** <code>WV*f*</code> or <code>WH*f*</code>

**Driver ID:** `WWV_AUDIO`

**Autotune Port:** `/dev/icom`; 1200/9600 baud, 8-bits, no parity

**Audio Device:** `/dev/audio` and `/dev/audioctl`

* * *

#### Description

This driver synchronizes the computer time using shortwave radio transmissions from NIST time/frequency stations [WWV](https://www.nist.gov/pml/time-and-frequency-division/time-distribution/radio-station-wwv) in Ft. Collins, CO, and [WWVH](https://tf.nist.gov/stations/wwvh.htm) in Kauai, HI. Transmissions are made continuously on 2.5, 5, 10 and 15 MHz from both stations and on 20 MHz from WWV. An ordinary shortwave receiver can be tuned manually to one of these frequencies or, in the case of ICOM receivers, the receiver can be tuned automatically by the driver as propagation conditions change throughout the day and season. The radio is connected via an optional attenuator and cable to either the microphone or line-in port of a workstation or PC.

The driver requires an audio codec or sound card with sampling rate 8 kHz and μ-law companding to demodulate the data. This is the same standard as used by the telephone industry and is supported by most hardware and operating systems, including Solaris, FreeBSD and Linux, among others. In this implementation only one audio driver and codec can be supported on a single machine. In order to assure reliable signal capture, the codec frequency error must be less than 187 PPM (.0187 percent). If necessary, the `tinker codec` configuration command can be used to bracket the codec frequency to this range.

In general and without calibration, the driver is accurate within 1 ms relative to the broadcast time when tracking a station. However, variations up to 0.3 ms can be expected due to diurnal variations in ionospheric layer height and ray geometry. In Newark DE, 2479 km from the transmitter, the predicted two-hop propagation delay varies from 9.3 ms in sunlight to 9.0 ms in moonlight. When not tracking the station the accuracy depends on the computer clock oscillator stability, ordinarily better than 0.5 PPM.

After calibration relative to the PPS signal from a GPS receiver, the mean offset with a 2.4-GHz P4 running FreeBSD 6.1 is generally within 0.1 ms short-term with 0.4 ms jitter. The long-term mean offset varies up to 0.3 ms due to propagation path geometry variations. The processor load due to the driver is 0.4 percent on the P4.

The driver performs a number of error checks to protect against overdriven or underdriven input signal levels, incorrect signal format or improper hardware configuration. The specific checks are detailed later in this page. Note that additional checks are done elsewhere in the reference clock interface routines.

This driver incorporates several features in common with other audio drivers such as described in the [Radio CHU Audio Demodulator/Decoder](/documentation/drivers/driver7/) and the [IRIG Audio Decoder](/documentation/drivers/driver6/) pages. They include automatic gain control (AGC), selectable audio codec port and signal monitoring capabilities. For a discussion of these common features, as well as a guide to hookup, debugging and monitoring, see the [Reference Clock Audio Drivers](/documentation/4.2.8-series/audio/) page.

* * *

#### Technical Overview

The driver processes 8-kHz μ-law companded codec samples using maximum-likelihood techniques which exploit the considerable degree of redundancy available in the broadcast signal. The WWV signal format is described in [NIST Special Publication 432](https://www.nist.gov/system/files/documents/2017/04/28/SP-432-NIST-Time-and-Frequency-Services-2012-02-13.pdf) and at the [WWV/H web site](https://www.nist.gov/pml/time-and-frequency-division/time-distribution/radio-station-wwv/wwv-and-wwvh-digital-time-code). It consists of three elements, a 5-ms, 1000-Hz pulse, which occurs at the beginning of each second, a 800-ms, 1000-Hz pulse, which occurs at the beginning of each minute, and a pulse-width modulated 100-Hz subcarrier for the data bits, one bit per second. The WWVH format is identical, except that the 1000-Hz pulses are sent at 1200 Hz. Each minute encodes nine BCD digits for the time of century plus seven bits for the daylight savings time (DST) indicator, leap warning indicator and DUT1 correction.

The demodulation and decoding algorithms used by this driver are based on a machine language program developed for the TAPR DSP93 DSP unit, which uses the TI 320C25 DSP chip. The analysis, design and performance of the program for this unit is described in: Mills, D.L. [A precision radio clock for WWV transmissions](/reflib/reports/wwv/wwv.pdf). Electrical Engineering Report 97-8-1, University of Delaware, August 1997, 25 pp. For use in this driver, the original program was rebuilt in the C language and adapted to the NTP driver interface. The algorithms have been modified to improve performance, especially under weak signal conditions and to provide an automatic frequency and station selection feature.

As in the original program, the clock discipline is modelled as a Markov process, with probabilistic state transitions corresponding to a conventional clock and the probabilities of received decimal digits. The result is a performance level with very high accuracy and reliability, even under conditions when the minute beep of the signal, normally its most prominent feature, can barely be detected by ear using a communications receiver.

* * *

#### Baseband Signal Processing

The 1000/1200-Hz pulses and 100-Hz subcarrier are first separated using a 600-Hz bandpass filter centered on 1100 Hz and a 150-Hz lowpass filter. The minute pulse is extracted using an 800-ms synchronous matched filter and pulse grooming logic which discriminates between WWV and WWVH signals and noise. The second pulse is extracted using a 5-ms FIR matched filter for each station and a single 8000-stage comb filter.

The phase of the 100-Hz subcarrier relative to the second pulse is fixed at the transmitter; however, the audio stage in many radios affects the phase response at 100 Hz in unpredictable ways. The driver adjusts for each radio using two 170-ms synchronous matched filters. The I (in-phase) filter is used to demodulate the subcarrier envelope, while the Q (quadrature-phase) filter is used in a type-1 phase-lock loop (PLL) to discipline the demodulator phase.

A bipolar data signal is determined from the matched filter subcarrier envelope using a pulse-width discriminator. The discriminator samples the I channel at 15 ms (<code>_n_</code>), 200 ms (<code>_s_<sub>0</sub></code>) and 500 ms (<code>_s_<sub>1</sub></code>), and the envelope (RMS I and Q channels) at 200 ms (<code>_e_<sub>1</sub></code>) and the end of the second (<code>_e_<sub>0</sub></code>). The bipolar data signal is expressed <code>2s<sub>1</sub> - s<sub>0</sub> - n</code>, where positive values correspond to data 1 and negative values correspond to data 0. Note that, since the signals <code>s<sub>0</sub></code> and <code>s<sub>1</sub></code> include the noise <code>_n_</code>, the noise component cancels out. The data bit SNR is calculated as <code>20 log<sub>10</sub>(_e_<sub>1</sub> / _e_<sub>0</sub>)</code>. If the driver has not synchronized to the minute pulse, or if the data bit amplitude <code>_e_<sub>1</sub></code> or SNR are below thresholds, the bit is considered invalid and the bipolar signal is forced to zero.

The bipolar signal is exponentially averaged in a set of 60 accumulators, one for each second, to determine the semi-static miscellaneous bits, such as DST indicator, leap second warning and DUT1 correction. In this design a data average value larger than a positive threshold is interpreted as +1 (hit) and a value smaller than a negative threshold as a -1 (miss). Values between the two thresholds, which can occur due to signal fades, are interpreted as an erasure and result in no change of indication.

* * *

#### Maximum-Likelihood Decoder

The BCD digit in each digit position of the timecode is represented as four data bits. The bits are correlated with the bits corresponding to each of the valid decimal digits in this position. If any of the four bits are invalid, the correlated value for all digits in this position is assumed zero. In either case, the values for all digits are exponentially averaged in a likelihood vector associated with this position. The digit associated with the maximum over all averaged values then becomes the maximum-likelihood candidate for this position and the ratio of the maximum over the next lower value represents the digit SNR.

The decoding matrix contains nine row vectors, one for each digit position. Each row vector includes the maximum-likelihood digit, likelihood vector and other related data. The maximum-likelihood digit for each of the nine digit positions becomes the maximum-likelihood time of the century. A built-in transition function implements a conventional clock with decimal digits that count the minutes, hours, days and years, as corrected for leap seconds and leap years. The counting operation also rotates the likelihood vector corresponding to each digit as it advances. Thus, once the clock is set, each clock digit should correspond to the maximum-likelihood digit as transmitted.

Each row of the decoding matrix also includes a compare counter and the most recently determined maximum-likelihood digit. If a digit likelihood exceeds the decision level and compares with previous digits for a number of successive minutes in any row, the maximum-likelihood digit replaces the clock digit in that row. When this condition is true for all rows and the second epoch has been reliably determined, the clock is set (or verified if it has already been set) and delivers correct time to the integral second. The fraction within the second is derived from the logical master clock, which runs at 8000 Hz and drives all system timing functions.

* * *

#### Master Clock Discipline

The logical master clock is derived from the audio codec clock. Its frequency is disciplined by a frequency-lock loop (FLL) which operates independently of the data recovery functions. The maximum value of the 5-ms pulse after the comb filter represents the on-time epoch of the second. At averaging intervals determined by the measured jitter, the frequency error is calculated as the difference between the epoches over the interval divided by the interval itself. The sample clock frequency is then corrected by this amount divided by a time constant of 8.

When first started, the frequency averaging interval is 8 seconds, in order to compensate for intrinsic codec clock frequency offsets up to 125 PPM. Under most conditions, the averaging interval doubles in stages from the initial value to 1024 s, which results in an ultimate frequency resolution of 0.125 PPM, or about 11 ms/day.

The data demodulation functions operate using the subcarrier clock, which is independent of the epoch. However, the data decoding functions are driven by the epoch. The decoder is phase-locked to the epoch in such a way that, when the clock state machine has reliably decoded the broadcast time to the second, the epoch timestamp of that second becomes a candidate to set the system clock.

The comb filter can have a long memory and is vulnerable to noise and stale data, especially when coming up after a long fade. Therefore, a candidate is considered valid only if the 5-ms signal amplitude and SNR are above thresholds. In addition, the system clock is not set until after one complete averaging interval has passed with valid candidates.

* * *

#### Station Identification

It is important that the logical clock frequency is stable and accurately determined, since in many applications the shortwave radio will be tuned to a fixed frequency where WWV or WWVH signals are not available throughout the day. In addition, in some parts of the US, especially on the west coast, signals from either or both WWV and WWVH may be available at different times or even at the same time. Since the propagation times from either station are almost always different, each station must be reliably identified before attempting to set the clock.

Reliable station identification requires accurate discrimination between very weak signals in noise and noise alone. The driver very aggressively soaks up every scrap of signal information, but has to be careful to avoid making pseudo-sense of noise alone. The signal quality metric depends on the minute pulse amplitude and SNR measured in second 0 of the minute, together with the data subcarrier amplitude and SNR measured in second 1. If all four values are above defined thresholds a hit is declared, otherwise a miss. In principle, the data pulse in second 58 is usable, but the AGC in most radios is not fast enough for a reliable measurement.

The number of hits declared in the last 6 minutes for each station represents the high order bits of the metric, while the current minute pulse amplitude represents the low order bits. Only if the metric is above a defined threshold is the station signal considered acceptable. The metric is also used by the autotune function described below and reported in the timecode string.

* * *

#### Performance

It is the intent of the design that the accuracy and stability of the indicated time be limited only by the characteristics of the ionospheric propagation medium. Conventional wisdom is that manual synchronization via oscilloscope and HF medium is good only to a millisecond under the best propagation conditions. The performance of the NTP daemon disciplined by this driver is clearly better than this, even under marginal conditions.

The figure below shows the measured offsets over a typical day near the bottom of the sunspot cycle ending in October, 2006. Variations up to ±0.4 ms can be expected due to changing ionospheric layer height and ray geometry over the day and night.

![gif](/documentation/pic/offset1211.gif)

The figure was constructed using a 2.4-GHz P4 running FreeBSD 6.1. For these measurements the computer clock was disciplined within a few microseconds of UTC using a PPS signal and GPS receiver and the measured offsets determined from the `filegen peerstats` data.

The predicted propagation delay from the WWV transmitter at Boulder, CO, to the receiver at Newark, DE, varies over 9.0-9.3 ms. In addition, the receiver contributes 4.7 ms and the 600-Hz bandpass filter 0.9 ms. With these values, the mean error is less than 0.1 ms and varies ±0.3 ms over the day as the result of changing ionospheric height and ray geometry.

* * *

#### Program Operation

The driver begins operation immediately upon startup. It first searches for one or both of the stations WWV and WWVH and attempts to acquire minute synch. This may take some fits and starts, as the driver expects to see several consecutive minutes with good signals and low jitter. If the autotune function is active, the driver will rotate over all five frequencies and both WWV and WWVH stations until finding a station and frequency with acceptable metric.

While this is going on the driver acquires second synch, which can take up to several minutes, depending on signal quality. When minute synch has been acquired, the driver accumulates likelihood values for the unit (seconds) digit of the nine timecode digits, plus the seven miscellaneous bits included in the WWV/H transmission format. When a good unit digit has been found, the driver accumulates likelihood values for the remaining eight digits of the timecode. When three repetitions of all nine digits have decoded correctly, which normally takes 15 minutes with good signals, and up to 40 minutes when buried in noise, and the second synch has been acquired, the clock is set (or verified) and is selectable to discipline the system clock.

Once the clock is set, it continues to provide correct timecodes as long as the signal metric is above threshold, as described in the previous section. As long as the clock is correctly set or verified, the system clock offsets are provided once each minute to the reference clock interface, where they are processed using the same algorithms as with other reference clocks and remote servers.

It may happen as the hours progress around the clock that WWV and WWVH signals may appear alone, together or not at all. When the driver has mitigated which station and frequency is best, it sets the reference identifier to the string <code>WV*f*</code> for WWV and <code>WH*f*</code> for WWVH, where <code>_f_</code> is the frequency in megahertz. If the propagation delays have been properly set with the `fudge time1` (WWV) and `fudge time2` (WWVH) commands in the configuration file, handover from one station to the other is seamless.

Operation continues as long as the signal metric from at least one station on at least one frequency is acceptable. A consequence of this design is that, once the clock is set, the time and frequency are disciplined only by the second synch pulse and the clock digits themselves are driven by the clock state machine. If for some reason the state machine drifts to the wrong second, it would never resynchronize. To protect against this most unlikely situation, if after two days with no signals, the clock is considered unset and resumes the synchronization procedure from the beginning.

Once the system clock been set correctly it will continue to read correctly even during the holdover interval, but with increasing dispersion. Assuming the system clock frequency can be disciplined within 1 PPM, it can coast without signals for several days without exceeding the NTP step threshold of 128 ms. During such periods the root distance increases at 15 μs per second, which makes the driver appear less likely for selection as time goes on. Eventually, when the distance due all causes exceeds 1 s, it is no longer suitable for synchronization. Ordinarily, this happens after about 18 hours with no signals. The `tinker maxdist` configuration command can be used to change this value.

* * *

#### Autotune

The driver includes provisions to automatically tune the radio in response to changing radio propagation conditions throughout the day and night. The radio interface is compatible with the ICOM CI-V standard, which is a bidirectional serial bus operating at TTL levels. The bus can be connected to a standard serial port using a level converter such as the CT-17. Further details are on the [Reference Clock Audio Drivers](/documentation/4.2.8-series/audio/) page.

If specified, the driver will attempt to open the device `/dev/icom` and, if successful will activate the autotune function and tune the radio to each operating frequency in turn while attempting to acquire minute synch from either WWV or WWVH. However, the driver is liberal in what it assumes of the configuration. If the `/dev/icom` link is not present or the open fails or the CI-V bus is inoperative, the driver quietly gives up with no harm done.

Once acquiring minute synch, the driver operates as described above to set the clock. However, during seconds 59, 0 and 1 of each minute it tunes the radio to one of the five broadcast frequencies to measure the signal metric as described above. Each of the five frequencies are probed in a five-minute rotation to build a database of current propagation conditions for all signals that can be heard at the time. At the end of each probe a mitigation procedure scans the database and retunes the radio to the best frequency and station found. For this to work well, the radio should be set for a fast AGC recovery time. This is most important while tracking a strong signal, which is normally the case, and then probing another frequency, which may have much weaker signals.

The mitigation procedure selects the frequency and station with the highest valid metric, ties going first to the highest frequency and then to WWV in order. A station is considered valid only if the metric is above a specified threshold; if no station is above the metric, the rotating probes continue until a valid station is found.

The behavior of the autotune function over a typical day is shown in the figure below.

![gif](/documentation/pic/freq1211.gif)

As expected, the lower frequencies prevail when the ray path is in moonlight (0100-1300 UTC) and the higher frequencies when the path is in sunlight (1300-0100 UTC). Note three periods in the figure show zero frequency when signals are below the minimum for all frequencies and stations.

* * *

#### Debugging Aids

The most convenient way to track the driver status is using the `ntpq` program and the `clockvar` command. This displays the last determined timecode and related status and error counters, even when the driver is not disciplining the system clock. If the debugging trace feature (`-d` on the `ntpd` command line) is enabled, the driver produces detailed status messages as it operates. If the `fudge flag 4` is set, these messages are written to the `clockstats` file. All messages produced by this driver have the prefix `wwv` for convenient filtering with the Unix `grep` command.

The autotune process produces diagnostic information along with the timecode. This is very useful for evaluating the performance of the algorithms, as well as radio propagation conditions in general. The message is produced once each minute for each frequency in turn after minute synch has been acquired.

`wwv5 status agc epoch secamp/secsnr datamp/datsnr wwv wwvh`

where the fields after the `wwv5` identifier are: `status` contains status bits, `agc` audio gain, `epoch` second epoch, `secamp/secsnr` second pulse amplitude/SNR, and `wwv` and `wwvh` are two sets of fields, one each for WWV and WWVH. Each of the two fields has the format

`ident score metric minamp/minsnr`

where `ident` encodes the station (`WV` for WWV, `WH` for WWVH) and frequency (2, 5, 10, 15 or 20), `score` 32-bit shift register recording the hits (1) and misses (0) of the last 32 probes (hits and misses enter from the right), `metric` is described above, and `minamp/minsnr` is the minute pulse ampliture/SNR. An example is:

`wwv5 000d 111 5753 3967/20.1 3523/10.2 WV20 bdeff 100 8348/30.0 WH20 0000 1 22/-12.4`

There are several other messages that can occur; these are documented in the source listing.

* * *

#### Monitor Data

When enabled by the `filegen` facility, every received timecode is written to the `clockstats` file in the following format:

`sq yyyy ddd hh:mm:ss l d du lset agc ident metric errs freq avg`

The fields beginning with `yyyy` and extending through `du` are decoded from the received data and are in fixed-length format. The remaining fields are in variable-length format. The fields are as follows:

| Field | Description | Value |
| ----- | ----- | ----- |
| `s` | The synch indicator is initially `?` before the clock is set, but turns to space when all nine digits of the timecode are correctly set and the decoder is synchronized to the station within 125 μs. | |
| `q` | The quality character is a four-bit hexadecimal code showing which alarms have been raised. Each bit is associated with a specific alarm condition. It is important to note that one or more of the alarms does not necessarily indicate a clock error, but only that the decoder has detected a marginal condition | `0x8` synch alarm. The decoder is not synchronized to the station within 125 μs.<br> `0x4` Digit error alarm. Less than nine decimal digits were found in the last minute.<br> `0x2` Error alarm. More than 40 data bit errors were found in the last minute.<br> `0x1` Compare alarm. A maximum-likelihood digit failed to agree with the current associated clock digit in the last minute. |
| `yyyy ddd hh:mm:ss` | The timecode format itself is self explanatory. Since the driver latches the on-time epoch directly from the second synch pulse, the seconds fraction is always zero. Although the transmitted timecode includes only the year of century, the Gregorian year is augmented by 2000. | |
| `l` | The leap second warning is normally space, but changes to `L` if a leap second is to occur at the end of the month. | |
| `d` | The DST state | `S` standard time<br> `D` daylight time<br> `I` daylight time is about to go into effect<br> `O` daylight time is about to go out of effect |
| `du` | The DUT sign and magnitude shows the current UT1 offset relative to the displayed UTC time, in deciseconds. | |
| `lset` | Before the clock is set, the interval since last set is the number of minutes since the driver was started; after the clock is set, this is number of minutes since the decoder was last synchronized to the station within 125 μs. | |
| `agc` | The audio gain shows the current codec gain setting in the range 0 to 255. Ordinarily, the receiver audio gain control should be set for a value midway in this range. | |
| `ident` | Station identifier | <code>WV*f*</code> for WWV<br> <code>WH*f*</code> for WWVH<br> frequency `f` being tracked<br> If neither station is heard on any frequency, the reference identifier shows `NONE`. |
| `metric` | Signal metric described above from 0 (no signal) to 100 (best). | |
| `errs` | The bit error counter is useful to determine the quality of the data signal received in the most recent minute. It is normal to drop a couple of data bits even under good signal conditions and increasing numbers as conditions worsen. While the decoder performs moderately well even with half the bits are in error in any minute, usually by that point the metric drops below threshold and the decoder switches to a different frequency. | |
| `freq` | The frequency offset is the current estimate of the codec frequency offset to within 0.1 PPM. This may wander a bit over the day due to local temperature fluctuations and propagation conditions. | |
| `avg` | The averaging time is the interval between frequency updates in powers of two to a maximum of 1024 s. Attainment of the maximum indicates the driver is operating at the best possible resolution in time and frequency. | |

An example timecode is:

`0 2000 006 22:36:00 S +3 1 115 WV20 86 5 66.4 1024`

Here the clock has been set and no alarms are raised. The year, day and time are displayed along with no leap warning, standard time and DUT +0.3 s. The clock was set on the last minute, the AGC is safely in the middle of the range 0-255, and the receiver is tracking WWV on 20 MHz. Good receiving conditions prevail, as indicated by the metric 86 and 5 bit errors during the last minute. The current frequency is 66.4 PPM and the averaging interval is 1024 s, indicating the maximum precision available.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the propagation delay for WWV (40:40:49.0N 105:02:27.0W), in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Specifies the propagation delay for WWVH (21:59:26.0N 159:46:00.0W), in seconds and fraction, with default 0.0.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Ordinarily, this field specifies the driver reference identifier; however, the driver sets the reference identifier automatically as described above.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Specifies the microphone port if set to zero or the line-in port if set to one. It does not seem useful to specify the compact disc player port.

<code>**flag3 0 | 1**</code>

: Enables audio monitoring of the input signal. For this purpose, the speaker volume must be set before the driver is started.

<code>**flag4 0 | 1**</code>

: Enable verbose `clockstats` recording if set.