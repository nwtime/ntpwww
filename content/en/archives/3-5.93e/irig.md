---
title: "IRIG Support Using Sun SPARC Audio"
type: archives
---

#### Table of Contents

*   [Introduction](/archives/3-5.93e/#introduction)
*   [Programming Interface](/archives/3-5.93e/#programming-interface)
*   [Programming Example](/archives/3-5.93e/#programming-example)
*   [Implementation and Configuration Notes](/archives/3-5.93e/#implementation-and-configuration-notes)

* * *

#### Introduction

A companion software distribution [bsd_audio.tar.Z](/reflib/software/ntp3/bsd_audio.tar.Z) includes modifications to the BSD audio driver for the Sun SPARCstation written by Van Jacobson and collaborators at Lawrence Berkeley National Laboratory. The modifications provide for the connection of a standard Inter-Range Instrumentation Group (IRIG) timecode signal generator and the decoding of the signal to produce data sufficient to synchronize a host clock to the IRIG signal. There are several timing receivers now on the market that can produce IRIG signals, including those made by Austron, TrueTime, Odetics and Spectracom, among others. These data can be used to precisely synchronize the host computer clock to within a few microseconds without requiring level converters or pulse generators necessary with the pulse-per-second signals also produced by these receivers. The current implementation of the Network Time Protocol Version 3 supports the modified BSD driver when installed in the SunOS 4.1.x kernel.

The specific IRIG signal format supported by the driver is designated IRIG-B. It consists of an amplitude-modulated 1000-Hz sinewave, where each symbol is encoded as ten full carrier cycles, or 10 ms in duration. The symbols are distinguished using a pulse-width code, where 2 ms corresponds to logic zero, 5 ms to logic one and 8 ms to a position identifier used for symbol synchronization. The complete IRIG-B message consists of a frame of ten fields, each field consisting of a nine information symbols followed by a position identifier for a total frame duration of one second. The first symbol in the frame is also a position identifier to facilitate frame synchronization.

The IRIG-B signal encodes the day of year and time of day in binary- coded decimal (BCD) format, together with a set of control functions, which are not used by the driver, but included in the raw binary timecode. Either the BCD timecode or the combined raw timecode and BCD timecode can be returned in response to a <tt>read()</tt> system call. The BCD timecode is in handy ASCII format: <tt>ddd hh:mm:ss*</tt> for convenience in client programs. In this format the `*` status character is `" "` when the driver is operating normally and `?` when errors may be present (see below). In order to reduce residual errors to the greatest extent possible, the driver computes a timestamp based on the value of the kernel clock at the on-time epoch of the IRIG-B signal. In addition, the driver automatically adjusts for slowly varying amplitude levels of the IRIG-B signal and suppresses noise transients.

In operation the IRIG driver interprets the IRIG-B signal in real time, synchronizes to the signal, demodulates the data bits and prepares the data to be read later. At the on-time epoch a timestamp is captured from the kernel clock and adjusted for the phase of the IRIG carrier signal relative to the 8-kHz codec sample clock. When a client program issues a <tt>read()</tt> request, the most recent timecode data, including a status byte and the corrected timestamp, are stored in a structure and returned to the caller. Depending on the frequency with which the driver is called, this may result in old data or duplicate data or even invalid data, should the driver be called before it has computed its first timestamp.

In practice, the resulting ambiguity causes few problems. The caller converts the ASCII timecode returned by a <tt>read()</tt> system call to Unix timeval format and subtracts it from the kernel timestamp provided by the driver. The result is an adjustment that can be subtracted from the kernel time, as returned in a <tt>gettimeofday()</tt> call, for example, to correct for the deviation between IRIG time and kernel time. The result can always be relied on to within plus/minus 128 microseconds, the audio codec sampling interval, and ordinarily to within a few microseconds, as determined by the interpolation algorithm.

* * *

#### Programming Interface

The IRIG driver modifications are integrated in the BSD audio driver <tt>bsd_audio.c</tt> without affecting its usual functions in transmitting and receiving ordinary speech, except when enabled by specific <tt>ioctl()</tt> system calls. However, the driver cannot be used for both speech and IRIG signals at the same time. Once activated by a designated <tt>ioctl()</tt> call, the driver remains active until it is explicitly deactivated by another <tt>ioctl()</tt> call. This allows applications to configure the audio device and pass the pre-configured driver to other applications. Since the driver is currently only a receiver, it does not affect the operation of the BSD audio output driver.

Data are read using the standard <tt>read()</tt> system call. Since the output formats have constant lengths, the application receives the data into a fixed-length buffer or structure. The <tt>read()</tt> call never blocks; it simply returns the most recent IRIG data received during the last second. It may happen that, due to unavoidable race conditions in the kernel, data for other than the most recent second are returned. The driver's internal data structure is updated as an atomic unit; thus, the entire structure is valid, even if it contains old data. This should cause no problems, since in the intended application the driver is called at regular intervals by a time-synchronization daemon such as NTP. The daemon can determine the validity of the time indication by checking the timecode or status byte returned with the data.

The header file <tt>bsd_audioirig.h</tt> defines the irig_time structure and <tt>ioctl()</tt> codes used by the driver. Following are those codes specific to the IRIG function of the driver. Unless indicated otherwise, the (third) argument of the <tt>ioctl()</tt> system call points to an integer or string.

<dt><tt>audio_IRIG_OPEN</tt></dt>

This command activates the IRIG receiver. The audio driver must be opened with this command before other commands can be issued. The argument is ignored. When the IRIG receiver is initialized, all internal data are purged and any buffered data are lost.

<dt><tt>audio_IRIG_CLOSE</tt></dt>

This command deactivates the IRIG receiver. The argument is ignored. The buffers are purged and any buffered time data are lost. The original BSD audio driver functions are enabled and it resumes operating normally.

<dt><tt>audio_IRIG_SETFORMAT</tt></dt>

The argument is a pointer to an integer designating the output format for the IRIG data. There are currently two formats defined, 0 (default) and 1. If an invalid format is selected, the default format is used.

The data returned by a <tt>read()</tt> system call in format 0 is a character string in the format `ddd hh:mm:ss*\n`, which consists of 13 ASCII characters followed by a `\n` terminator for a total of 14 characters. The `*` status character is an ASCII space if the status byte determined by the driver is zero and `?` if not. This format is intended to be used with simple user programs that care only about the time to the nearest second.

The data returned by a <tt>read()</tt> system call in format 1 is a structure defined in the <tt>bsd_audioirig.h</tt> header file:

<pre>        struct irig_time {
                struct timeval stamp;   /* timestamp */
                u_char bits[13];                /* 100 irig data bits */
                u_char status;                  /* status byte */
                char    time[14];                       /* time string
*/
        };
</pre>

The <tt>irig_time.stamp</tt> is a pair of 32-bit longwords in Unix <tt>timeval</tt> format, as defined in the <tt>/usr/include/sys/time.h</tt> header file. The first word is the number of seconds since 1 January 1970, while the second is the number of microseconds in the current second. The timestamp is captured at the most recent on-time epoch of the IRIG timecode and applies to all other values returned in the <tt>irig_time</tt> structure.

The <tt>irig_time.bits[13]</tt> is a vector of 13 bytes to hold the 100-bit, zero-padded raw binary timecode, packed 8 symbols per byte. The symbol encoding maps IRIG one to 1 and both IRIG zero and IRIG position identifier to 0. The order of encoding is illustrated by the following diagram (the padding bits are represented by `xxxx`, which are set to zero):

<pre>IRIG symbol number      00000000001111111111 . . . 8888889999999999xxxx
                                01234567890123456789 . . .
4567890123456789xxxx
                                ----------------------------------------
-------
bits byte       number  <--00--><--01--><----     ----
><--11--><--12-->
bits bit in byte        01234567012345670123 . . . 45670123456701234567
</pre>

The <tt>irig_time.status</tt> is a single byte with bits defined in the <tt>bsd_audioirig.h</tt> header file. In ordinary operation all bits of the status byte are zero and the ASCII space status character is set in the ASCII timecode. If any of these bits are nonzero, the `?` status character is set in the ASCII timecode.

<dt><tt>audio_IRIG_BADSIGNAL</tt></dt>

The signal amplitude is outside tolerance limits, either in amplitude or modulation depth. The indicated time may or may not be in error. If the signal is too high, it may be clipped by the codec, so that the pulse width cannot be reliably determined. If too low, it may be obscured by noise. The nominal expectation is that the peak amplitude of the signal be maintained by the codec AGC at about 10 dB below the clipping level and that the modulation index be at least 0.5 (6 dB).

<dt><tt>audio_IRIG_BADDATA</tt></dt>

An invalid hex code (A through F) has been found where BCD data is expected. The ASCII representation of the invalid code is set to `?`. Errors of this type are most likely due to noise on the IRIG signal due to ground loops, coupling to other noise sources, etc.

<dt><tt>audio_IRIG_BADSYNC</tt></dt>

A code element has been found where a position identifier should be or a position identifier has been found where a code element should be. The time is meaningless and should be disregarded. Errors of this type can be due to severe noise on the IRIG signal due to ground loops, coupling to other noise sources, etc., or during initial acquisition of the signal.

<dt><tt>audio_IRIG_BADCLOCK</tt></dt>

Some IRIG timecode generators can indicate whether or not the generator is operating correctly or synchronized to its source of standard time using a designated field in the raw binary timecode. Where such information is available and the IRIG decoder can detect it, this bit is set when the generator reports anything except normal operating conditions.

<dt><tt>audio_IRIG_OLDDATA</tt></dt>

The IRIG time has not changed since the last time it was returned in a <tt>read()</tt> call. This is not normally considered an error, unless it persists for longer than a few seconds, in which case it probably indicates a hardware problem.

The <tt>irig_time.time[14]</tt> vector is a character string in the format `ddd hh:mm:ss*\0`, which consists of 13 ASCII characters followed by a zero terminator. The * status character is an ASCII space if the status byte is zero and `?` if not. This format is identical to format 0, except that in format 1 the time string is null-terminated.

* * *

#### Programming Example

The following pseudo-code demonstrates how the IRIG receiver may be used by a simple user program. Of course, real code should include error checking after each call to ensure the driver is communicating properly. It should also verify that the correct fields in the structure are being filled by the <tt>read()</tt> call.

<pre>        include "bsd_audioirig.h"

        int format = 1;
        struct irig_time it;

        Audio_fd = open("/dev/audio", O_RDONLY);
        ioctl(Audio_fd, AUDIO_IRIG_OPEN, NULL);
        ioctl(Audio_fd, AUDIO_IRIG_SETFORMAT,&format);
        while (condition)
                read(Audio_fd, &it, sizeof(it);
                printf("%s\n", it.time);
        ioctl(Audio_fd, AUDIO_IRIG_CLOSE, NULL);
        close(Audio_fd);
</pre>

* * *

#### Implementation and Configuration Notes

The signal level produced by most IRIG-equipped radios is on the order of a few volts peak-peak, which is far larger than the audio codec can accept; therefore, an attenuator in the form of a voltage divider is needed. The codec can handle IRIG signals at the microphone input from 4.2 mV to 230 mV peak-peak. A suitable attenuator conists of a series- connected 100K-Ohm resistor at the input and a parallel-connected 1K-Ohm resistor at the output, both contained along with suitable connectors in a small aluminum box. The exact values of these resistors are not critical, since the IRIG driver includes an automatic level-adjustment capability.

For the most accurate time using the IRIG signal and a particular radio, it may be necessary to adjust the <tt>time1</tt> parameter of the <tt>fudge</tt> command to compensate for the codec delay and any additional delay due to IRIG processing in the radio itself. Since the codec samples at an 8-kHz rate, the average delay is about 62 us; however, the delays due to the radios and IRIG signals themselves can vary. For instance, in the Austron recievers the IRIG delay is essentially zero, while in the Spectracom receivers the delay is about 240 usec relative to the PPS signal. In addition, the poll interval can be reduced from the usual 64 seconds to 16 seconds to reduce wander of the local hardware clock. Finally, the <tt>prefer</tt> keyword can be used to bias the clock-selection algorithm to favor the IRIG time, which is ordinarily the best time available. The [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/3-5.93e/prefer) page describes the operation of this keyword. For example, the following two lines in the NTP configuration file <tt>ntp.conf</tt> are appropriate for the Spectracom Netclock/1 WWVB Synchronized Clock with IRIG Option:

<pre>server 127.127.6.0 prefer minpoll 4 maxpoll 4 # irig audio decoder
fudge 127.127.6.0 time1 0.0005
</pre>

The <tt>time1</tt> value of .0005 s (500 us) was determined by actual measurement. Since the IRIG delay in Austron receivers is essentially zero, the <tt>fudge</tt> command is not necessary with these receivers. The correct value in case of other radios may have to be determined by actual measurement. A convenient way of doing this is to configure the <tt>ppsclock</tt> streams module. This module can be built from the [ppsclock.tar.Z distribution.](/reflib/software/ppsclock.tar.Z) It can be used to adjust <tt>time1</tt> until the PPS signal and IRIG signal both show the same offset. The <tt>ppsclock</tt> streams module is described in the [Line Disciplines and Streams Drivers](/archives/3-5.93e/ldisc) page.

The modified BSD driver includes both the modified driver itself bsd_audio.c and the IRIG header file <tt>bsd_audioirig.h</tt>, as well as modified header files <tt>bsd_audiovar.h</tt> and <tt>bsd_audioio.h</tt>. The driver is installed in the same way as described in the BSD driver documentation, with the addition of the following define in the kernel configuration file:

<pre>options AUDIO_IRIG              # IRIG driver
</pre>

This causes the IRIG code to be included in the BSD driver, as well as a C-coded codec interrupt routine which replaces the assembly-coded routine and provides the IRIG functionality. While the C-coded routine is somewhat slower than the assembly-coded routine, the extra overhead is not expected to be significant. Note that the IRIG driver calls the kernel routine <tt>microtime()</tt> as included in the <tt>ppsclock.tar.Z</tt> distribution. It is highly recommended that this routine be installed in the kernel configuration as well. The instructions for doing this are contained in the <tt>ppsclock</tt> directory of the <tt>xntp3</tt> distribution.