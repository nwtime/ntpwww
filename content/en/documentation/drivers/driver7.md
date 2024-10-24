---
title: "Radio CHU Audio Demodulator/Decoder"
description: "The Radio CHU Audio Demodulator/Decoder driver synchronizes the computer time using shortwave radio transmissions from Canadian time/frequency station CHU in Ottawa, Ontario."
type: archives
---
Author: [David L. Mills](https://www.nwtime.org/tribute-to-david-l-mills/)

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver7/#synopsis)
*   [Description](/documentation/drivers/driver7/#description)
*   [Technical Overview](/documentation/drivers/driver7/#technical-overview)
*   [Baseband Signal Processing](/documentation/drivers/driver7/#baseband-signal-processing)
*   [Majority Decoder](/documentation/drivers/driver7/#majority-decoder)
*   [Autotune](/documentation/drivers/driver7/#autotune)
*   [Debugging Aids](/documentation/drivers/driver7/#debugging-aids)
*   [Monitor Data](/documentation/drivers/driver7/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver7/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.7._u_</code>

**Reference ID:** `CHU`

**Driver ID:** `CHU`

**Modem Port:** <code>/dev/chu*u*</code>; 300 baud, 8-bits, no parity

**Autotune Port:** `/dev/icom`; 1200/9600 baud, 8-bits, no parity

**Audio Device:** `/dev/audio` and `/dev/audioctl`

* * *

#### Description

This driver synchronizes the computer time using shortwave radio transmissions from Canadian time/frequency station [CHU](https://nrc.canada.ca/en/certifications-evaluations-standards/canadas-official-time/nrc-shortwave-station-broadcasts-chu) in Ottawa, Ontario. CHU transmissions are made continuously on 3.330, 7.850 and 14.670 MHz in upper sideband, compatible AM mode. An ordinary shortwave receiver can be tuned manually to one of these frequencies or, in the case of ICOM receivers, the receiver can be tuned automatically as propagation conditions change throughout the day and season.

The driver can be compiled to use either an audio codec or soundcard, or a Bell 103-compatible, 300-b/s modem or modem chip, as described on the [Pulse-per-second (PPS) Signal Interfacing](/documentation/4.2.8-series/pps/) page. If compiled for a modem, the driver uses it to receive the radio signal and demodulate the data. If compiled for the audio codec, it requires a sampling rate of 8 kHz and μ-law companding to demodulate the data. This is the same standard as used by the telephone industry and is supported by most hardware and operating systems, including Solaris, FreeBSD and Linux, among others. The radio is connected via an optional attenuator and cable to either the microphone or line-in port of a workstation or PC. In this implementation, only one audio driver and codec can be supported on a single machine.

In general and without calibration, the driver is accurate within 1 ms relative to the broadcast time when tracking a station. However, variations up to 0.3 ms can be expected due to diurnal variations in ionospheric layer height and ray geometry. In Newark DE, 625 km from the transmitter, the predicted one-hop propagation delay varies from 2.8 ms in sunlight to 2.6 ms in moonlight. When not tracking the station the accuracy depends on the computer clock oscillator stability, ordinarily better than 0.5 PPM.

After calibration relative to the PPS signal from a GPS receiver, the mean offset with a 2.4-GHz P4 running FreeBSD 6.1 is generally within 0.2 ms short-term with 0.4 ms jitter. The long-term mean offset varies up to 0.3 ms due to propagation path geometry variations. The processor load due to the driver is 0.4 percent on the P4.

The driver performs a number of error checks to protect against overdriven or underdriven input signal levels, incorrect signal format or improper hardware configuration. The specific checks are detailed later in this page. Note that additional checks are done elsewhere in the reference clock interface routines.

This driver incorporates several features in common with other audio drivers such as described in the [Radio WWV/H Audio Demodulator/Decoder](/documentation/drivers/driver36/) and the [IRIG Audio Decoder](/documentation/drivers/driver6/) pages. They include automatic gain control (AGC), selectable audio codec port and signal monitoring capabilities. For a discussion of these common features, as well as a guide to hookup, debugging and monitoring, see the [Reference Clock Audio Drivers](/documentation/4.2.8-series/audio/) page.

* * *

#### Technical Overview

The driver processes 8-kHz μ-law companded codec samples using maximum-likelihood techniques which exploit the considerable degree of redundancy available in each broadcast message or burst. As described below, every character is sent twice and, in the case of format A bursts, the burst is sent eight times every minute. The single format B burst is considered correct only if every character matches its repetition in the burst. For the eight format A bursts, a majority decoder requires more than half of the 16 repetitions for each digit decode to the same value. Every character in every burst provides an independent timestamp upon arrival with a potential total of 60 timestamps for each minute.

The CHU timecode format is described on the [CHU website](https://nrc.canada.ca/en/certifications-evaluations-standards/canadas-official-time/nrc-shortwave-station-broadcasts-chu). A timecode is assembled when all bursts have been received in each minute. The timecode is considered valid and the clock set when at least one valid format B burst has been decoded and the majority decoder declares success. Once the driver has synchronized for the first time, it will appear reachable and selectable to discipline the system clock. It is normal on occasion to miss a minute or two due to signal fades or noise. If eight successive minutes are missed, the driver is considered unreachable and the system clock will free-wheel at the latest determined frequency offset. Since the signals are almost always available during some period of the day and the NTP clock discipline algorithms are designed to work well even with long intervals between updates, it is unlikely that the system clock will drift more than a few milliseconds during periods of signal loss.

* * *

#### Baseband Signal Processing

The program consists of four major parts: the DSP modem, maximum-likelihood UART, burst assembler and majority decoder. The DSP modem demodulates Bell 103 modem answer-frequency signals; that is, frequency-shift keyed (FSK) tones of 2225 Hz (mark) and 2025 Hz (space). It consists of a 500-Hz bandpass filter centered on 2125 Hz followed by a limiter/discriminator and raised-cosine lowpass filter optimized for the 300-b/s data rate.

The maximum likelihood UART is implemented using a set of eight 11-stage shift registers, one for each of eight phases of the 300-b/s bit clock. At each phase a new baseband signal from the DSP modem is shifted into the corresponding register and the maximum and minimum over all 11 samples computed. This establishes a span (difference) and slice level (average) over all 11 stages. For each stage, a signal level above the slice is a mark (1) and below that is a space (0). A quality metric is calculated for each register with respect to the slice level and the a-priori signal consisting of a start bit (space), eight arbitrary information bits and two stop bits (mark).

The shift registers are processed in round-robin order as the phases of each bit arrive. At the end of each bit all eight phases are searched for valid framing bits, sufficient span and best metric. The best candidate found in this way represents the maximum-likelihood character. The process then continues for all ten characters in the burst.

The burst assembler processes characters either from the maximum-likelihood UART or directly from the serial port as configured. A burst begins when a character is received and is processed after a timeout interval when no characters are received. If the interval between characters is greater than two characters, but less than the timeout interval, the burst is rejected as a runt and a new burst begun. As each character is received, a timestamp is captured and saved for later processing.

A valid burst consists of ten characters in two replicated five-character blocks, each block representing ten 4-bit BCD digits. The format B blocks sent in second 31 contain the year and other information in ten digits. The eight format A blocks sent in seconds 32-39 contain the timecode in ten digits, the first of which is a framing code (6). The burst assembler must deal with cases where the first character of a format A burst is lost or is noise. This is done using the framing codes to correct the discrepancy, either one character early or one character late.

The burst distance is incremented by one for each bit in the first block that matches the corresponding bit in the second block and decremented by one otherwise. In a format B burst the second block is bit-inverted relative to the first, so a perfect burst of five 8-bit characters has distance -40. In a format A burst the two blocks are identical, so a perfect burst has distance +40. Format B bursts must be perfect to be acceptable; however, format A bursts, which are further processed by the majority decoder, are acceptable if the distance is at least 28.

* * *

#### Majority Decoder

Each minute of transmission includes eight format A bursts containing two timecodes for each second from 32 through 39. The majority decoder uses a decoding matrix of ten rows, one for each digit position in the timecode, and 16 columns, one for each 4-bit code combination that might be decoded at that position. In order to use the character timestamps, it is necessary to reliably determine the second number of each burst. In a valid burst, the last digit of the two timecodes in the burst must match and the value must be in the range 2-9 and greater than in the previous burst.

As each digit of a valid burst is processed, the value at the row corresponding to the digit position in the timecode and column corresponding to the code found at that position is incremented. At the end of the minute, each row of the decoding matrix encodes the number of occurrences of each code found at the corresponding position.

The maximum over all occurrences at each digit position is the distance for that position and the corresponding code is the maximum-likelihood digit. If the distance is not more than half the total number of occurrences, the decoder assumes a soft error and discards all information collected during the minute. The decoding distance is defined as the sum of the distances over the first nine digits; the tenth digit varies over the seconds and is uncounted.

The result of the majority decoder is a nine-digit timecode representing the maximum-likelihood candidate for the transmitted timecode in that minute. Note that the second and fraction within the minute are always zero and that the actual reference point to calculate timestamp offsets is backdated to the first second of the minute. At this point the timecode block is reformatted and the year, days, hours and minutes extracted along with other information from the format B burst, including DST state, DUT1 correction and leap warning. The reformatting operation checks the timecode for invalid code combinations that might have been left by the majority decoder and rejects the entire timecode if found.

If the timecode is valid, it is passed to the reference clock interface along with the backdated timestamps accumulated over the minute. A perfect set of eight bursts could generate as many as 80 timestamps, but the maximum the interface can handle is 60. These are processed using a median filter and trimmed-mean average, so the resulting system clock correction is usually much better than would otherwise be the case with radio noise, UART jitter and occasional burst errors.

* * *

#### Autotune

The driver includes provisions to automatically tune the radio in response to changing radio propagation conditions throughout the day and night. The radio interface is compatible with the ICOM CI-V standard, which is a bidirectional serial bus operating at TTL levels. The bus can be connected to a standard serial port using a level converter such as the CT-17. Further details are on the [Reference Clock Audio Drivers](/documentation/4.2.8-series/audio/) page.

If specified, the driver will attempt to open the device `/dev/icom` and, if successful will tune the radio to 3.331 MHz. The 1-kHz offset is useful with a narrowband SSB filter where the passband includes the carrier and modem signals. However, the driver is liberal in what it assumes of the configuration. If the `/dev/icom` link is not present or the open fails or the CI-V bus is inoperative, the driver continues in single-frequency mode.

As long as no bursts are received, the driver cycles over the three frequencies in turn, one minute for each station. When bursts are received from one or more stations, the driver operates in a five-minute cycle. During the first four minutes it tunes to the station with the highest metric. During the last minute it alternates between the other two stations in turn in order to measure the metric.

* * *

#### Debugging Aids

The most convenient way to track the program status is using the `ntpq` program and the `clockvar` command. This displays the last determined timecode and related status and error counters, even when the program is not disciplined by the system clock. If the debugging trace feature (`-d` on the `ntpd` command line) is enabled, the program produces detailed status messages as it operates. If the `fudge flag 4` is set, these messages are written to the `clockstats` file. All messages produced by this driver have the prefix `chu` for convenient filtering with the Unix `grep` command.

With debugging enabled the driver produces messages in the following formats: A single message beginning with `chuB` is produced for each format B burst received in second 31, while eight messages beginning with `chuA` are produced for each format A burst received in seconds 32 through 39 of the minute. The first four fields are

`stat sig n b`

where `stat` is the status code, `sig` the character span, `n` the number of characters in the burst (9-11), and `b` the burst distance (0-40). Good bursts will have spans of 800 or more and the other numbers near the top of the range specified. See the source for the interpretation of the remaining data in the burst. Note that each character of the burst is encoded as two digits in nibble-swapped order.

If the CI-V interface for ICOM radios is active, a debug level greater than 1 will produce a trace of the CI-V command and response messages. Interpretation of these messages requires knowledge of the CI-V protocol, which is beyond the scope of this document.

* * *

#### Monitor Data

When enabled by the `filegen` facility, every received timecode is written to the `clockstats` file in the following format:

<pre>        sq yyyy ddd hh:mm:ss lw dst du lset agc rfrq bcnt dist tsmp

        s       sync indicator
        q       quality character
        yyyy    Gregorian year
        ddd     day of year
        hh      hour of day
        mm      minute of hour
        ss      second of minute
        lw      leap second warning
        dst     DST state
        dut     DUT sign and magnitude in deciseconds
        lset    minutes since last set
        agc     audio gain (0-255)
        ident   CHU identifier code
        dist    decoder distance
        tsmp    timestamps captured
</pre>

The fields beginning with `year` and extending through `dut` are decoded from the received data and are in fixed-length format. The `agc` and `lset` fields, as well as the following driver-dependent fields, are in variable-length format.

<code>**s**</code>

: The sync indicator is initially `?` before the clock is set, but turns to `space` when the clock has been correctly set.

<code>**q**</code>

: The quality character is a four-bit hexadecimal code showing which alarms have been raised during the most recent minute. Each bit is associated with a specific alarm condition according to the following:

: | Bit | Description |
| ----- | ----- |
| `8` | Timestamp alarm. Fewer than 20 timestamps have been determined. |
| `4` | Decoder alarm. A majority of repetitions for at least one digit of the timecode fails to agree. |
| `2` | Format alarm. One or more bursts contained invalid data or was improperly formatted. |
| `1` | Frame alarm. One or more bursts was improperly framed or contained too many repetition errors. |

: The timestamp and decoder alarms are fatal; the data accumulated during the minute are not used to set the clock. The format and frame alarm are nonfatal; only the data in the burst are discarded.

<code>**yyyy ddd hh:mm:ss**</code>

: The timecode format itself is self explanatory. Note that the Gregorian year is decoded directly from the transmitted timecode.

<code>**lw**</code>

: The leap second warning is normally `space`, but changes to `L` if a leap second is to occur at the end of the month.

<code>**dst**</code>

: The DST code for Canada encodes the state for all provinces. It is encoded as two hex characters.

<code>**dut**</code>

: The DUT sign and magnitude shows the current UT1 offset relative to the displayed UTC time, in deciseconds. It is encoded as one digit preceded by sign.

<code>**lset**</code>

: Before the clock is set, this is the number of minutes since the program was started; after the clock is set, this is the number of minutes since the time was last verified relative to the broadcast signal.

<code>**agc**</code>

: The audio gain shows the current codec gain setting in the range 0 to 255. Ordinarily, the receiver audio gain control should be set for a value midway in this range.

<code>**ident**</code>

: The CHU identifier `CHU` followed by the current radio frequency code, if the CI-V interface is active, or `CHU` if not. The radio frequncy is encoded as 0 for 3.330 MHz, 1 for 7.850 MHz and 2 for 14.670 MHz.

<code>**dist**</code>

: The decoding distance determined during the most recent minute bursts were received. The values range from 0 to 160, with the higher values indicating better signals. The decoding algorithms require the distance at least 50; otherwise all data in the minute are discarded.

<code>**tsmp**</code>

: The number of timestamps determined during the most recent minute bursts were received. The values range from 0 to 60, with the higher values indicating better signals. The decoding algorithms require at least 20 timestamps in the minute; otherwise all data in the minute are discarded.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the propagation delay for CHU (45:18N 75:45N), in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `CHU`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: When the audio driver is compiled, this flag selects the audio input port, where 0 is the mike port (default) and 1 is the line-in port. It does not seem useful to select the compact disc player port.

<code>**flag3 0 | 1**</code>

: When the audio driver is compiled, this flag enables audio monitoring of the input signal. For this purpose, the speaker volume must be set before the driver is started.

<code>**flag4 0 | 1**</code>

: Enable verbose `clockstats` recording if set.