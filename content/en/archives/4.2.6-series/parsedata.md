---
title: "NTP PARSE clock data formats"
type: archives
---

The parse driver currently supports several clocks with different query mechanisms. In order for you to find a sample that might be similar to a clock you might want to integrate into parse I'll sum up the major features of the clocks (this information is distributed in the `parse/clk_*.c` and `ntpd/refclock_parse.c` files).

* * *

#### Table of Contents

* [Meinberg clocks](/archives/4.2.6-series/parsedata/#meinberg-clocks)
* [Raw DCF77 Data via serial line](/archives/4.2.6-series/parsedata/#raw-dcf77-data-via-serial-line)
* [DCF77 raw time code](/archives/4.2.6-series/parsedata/#dcf77-raw-time-code)
* [Schmid clock](/archives/4.2.6-series/parsedata/#schmid-clock)
* [Trimble SV6 ASCII time code (TAIP)](/archives/4.2.6-series/parsedata/#trimble-sv6-ascii-time-code-taip)
* [ELV DCF7000](/archives/4.2.6-series/parsedata/#elv-dcf7000)
* [HOPF 6021 und Kompatible](/archives/4.2.6-series/parsedata/#hopf-6021-und-kompatible)
* [Diem Computime Clock](/archives/4.2.6-series/parsedata/#diem-computime-clock)
* [WHARTON 400A Series Clock with a 404.2 Serial interface](/archives/4.2.6-series/parsedata/#wharton-400a-series-clock-with-a-4042-serial-interface)

#### Meinberg clocks

<pre>Meinberg: start=<STX>, end=<ETX>, sync on start
      pattern="\2D:  .  .  ;T: ;U:  .  .  ;    \3"
      pattern="\2  .  .  ;  ;   :  :  ;        \3"
      pattern="\2  .  .  ;  ;   :  :  ;    :  ;        ;   .         .       "
</pre>

Meinberg is a German manufacturer of time code receivers. Those clocks have a pretty common output format in the stock version. In order to support NTP Meinberg was so kind to produce some special versions of the firmware for the use with NTP. So, if you are going to use a Meinberg clock please ask whether there is a special Uni Erlangen version. You can reach [Meinberg](http://www.meinberg.de/) via the Web. Information can also be ordered via eMail from [info@meinberg.de](mailto:%20info@meinberg.de)

**General characteristics:**
  
Meinberg clocks primarily output pulse per second and a describing ASCII string. This string can be produced in two modes: either upon the reception of a question mark or every second. NTP uses the latter mechanism. DCF77 AM clocks have a limited accuracy of a few milliseconds. The DCF77 PZF5xx variants provide higher accuracy and have a pretty good relationship between RS232 time code and the PPS signal. Except for early versions of the old GPS166 receiver type, Meinberg GPS receivers have a very good timing relationship between the datagram and the pulse. The beginning of the start bit of the first character has basically the same accuracy as the PPS signal, plus a jitter of up to 1 bit time depending on the selected baud rate, i.e. 52 μs @ 19200. PPS support should always be used, if possible, in order to yield the highest possible accuracy.

The preferred tty setting for Meinberg DCF77 receivers is 9600/7E2:

<pre>		CFLAG		(B9600|CS7|PARENB|CREAD|HUPCL)
		IFLAG		(IGNBRK|IGNPAR|ISTRIP)
		OFLAG		0
		LFLAG		0
        </pre>

The tty setting for Meinberg GPS16x/17x receivers is 19200/8N1:

<pre>		CFLAG		(B19200|CS8|PARENB|CREAD|HUPCL)
		IFLAG		(IGNBRK|IGNPAR|ISTRIP)
		OFLAG		0
		LFLAG		0
        </pre>

All clocks should be run at datagram once per second.  

Format of the Meinberg standard time string:

<pre>        **_<STX>_D:_dd.mm.yy_;T:_w_;U:_hh.mm.ss_;_uvxy__<ETX>_**
    pos:  0  000000001111111111222222222233  3
          1  234567890123456789012345678901  2

    _<STX>_         = start-of-text, ASCII code 0x02
    _dd.mm.yy_      = day of month, month, year of the century, separated by dots
    _w_             = day of week (1..7, Monday = 1)
    _hh:mm:ss_      = hour, minute, second, separated by dots
    _u_             = '#' for GPS receivers: time is **not** synchronized
                           '#' for older PZF5xx receivers: no correlation, not synchronized
                           '#' for other devices: never sync'ed since powerup
                           ' ' if nothing of the above applies
    _v_             = '*' for GPS receivers: position has **not** been verified
                           '*' for other devices: freewheeling based on internal quartz
                           ' ' if nothing of the above applies
    _x_             = 'U' if UTC time is transmitted
                           'S' if daylight saving time is active
                           ' ' if nothing of the above applies
    _y_             = '!' during the hour preceding start or end of daylight saving time
                           'A' during the hour preceding a leap second
                           ' ' if nothing of the above applies
    _<ETX>_         = end-of-text, ASCII code 0x03
</pre>

Format of the Uni Erlangen time string for PZF5xx receivers:

<pre>        **_<STX>__dd.mm.yy_; _w_; _hh:mm:ss_; _tuvxyza__<ETX>_**
    pos:  0  000000001111111111222222222233  3
          1  234567890123456789012345678901  2

    _<STX>_         = start-of-text, ASCII code 0x02
    _dd.mm.yy_      = day of month, month, year of the century, separated by dots
    _w_             = day of week (1..7, Monday = 1)
    _hh:mm:ss_      = hour, minute, second, separated by colons

    _t_             = 'U' if UTC time is transmitted, else ' '
    _u_             = '#' for older PZF5xx receivers: no correlation, not synchronized
                           '#' for PZF511 and newer: never sync'ed since powerup
                           ' ' if nothing of the above applies
    _v_             = '*' if freewheeling based on internal quartz, else ' '
    _x_             = 'S' if daylight saving time is active, else ' '
    _y_             = '!' during the hour preceding start or end of daylight saving time, else ' '
    _z_             = 'A' during the hour preceding a leap second, else ' '
    _a_             = 'R' alternate antenna (reminiscent of PZF5xx), usually ' ' for GPS receivers
    _<ETX>_         = end-of-text, ASCII code 0x03
</pre>

Format of the Uni Erlangen time string for GPS16x/GPS17x receivers:

<pre>        **_<STX>__dd.mm.yy_; _w_; _hh:mm:ss_; _+uu:uu_; _uvxyzab_; _ll.lllln_ _lll.lllle_ _hhhh_m_<ETX>_**
    pos:  0  0000000011111111112222222222333333333344444444445555555555666666  6
          1  2345678901234567890123456789012345678901234567890123456789012345  6

    _<STX>_         = start-of-text, ASCII code 0x02
    _dd.mm.yy_      = day of month, month, year of the century, separated by dots
    _w_             = day of week (1..7, Monday = 1)
    _hh:mm:ss_      = hour, minute, second, separated by colons
    _+uu:uu_        = offset to UTC in hours and minutes, preceded by + or -
    _u_             = '#' if time is **not** synchronized, else ' '
    _v_             = '*' if position has **not** been verified, else ' '
    _x_             = 'S' if daylight saving time is active, else ' '
    _y_             = '!' during the hour preceding start or end of daylight saving time, else ' '
    _z_             = 'A' during the hour preceding a leap second, else ' '
    _a_             = 'R' alternate antenna (reminiscent of PZF5xx), usually ' ' for GPS receivers
    _b_             = 'L' during a leap second, i.e. if the seconds field is 60, else ' '
    _ll.lllln_      = position latitude in degrees, 'n' can actually be 'N' or 'S', i.e. North or South
    _lll.lllle_     = position longitude in degrees, 'e' can actually be 'E' or 'W', i.e. East or West
    _hhhh_          = position altitude in meters, always followed by 'm'
    _<ETX>_         = end-of-text, ASCII code 0x03
</pre>

Examples for Uni Erlangen strings from GPS receivers:

<pre>        \x02 09.07.93; 5; 08:48:26; +00:00;        ; 49.5736N  11.0280E  373m \x03
        \x02 08.11.06; 3; 14:39:39; +00:00;        ; 51.9828N   9.2258E  176m \x03
</pre>

The Uni Erlangen formats should be used preferably. Newer Meinberg GPS receivers can be configured to transmit that format, for older devices there may be a special firmware version available.

For the Meinberg parse look into `clk_meinberg.c`.  

* * *

#### Raw DCF77 Data via serial line

RAWDCF: end=TIMEOUT>1.5s, sync each char (any char),generate pseudo time codes, fixed format

direct DCF77 code input

In Europe it is relatively easy/cheap the receive the german time code transmitter DCF77. The simplest version to process its signal is to feed the 100/200ms pulse of the demodulated AM signal via a level converter to an RS232 port at 50Baud. parse/clk_rawdcf.c holds all necessary decoding logic for the time code which is transmitted each minute for one minute. A bit of the time code is sent once a second.

<pre>	The preferred tty setting is:
		CFLAG           (B50|CS8|CREAD|CLOCAL)
		IFLAG		0
		OFLAG		0
 		LFLAG		0
</pre>

* * *

#### DCF77 raw time code

From "Zur Zeit", Physikalisch-Technische Bundesanstalt (PTB), Braunschweig und Berlin, März 1989  

Timecode transmission:

<pre>	AM:

	time marks are send every second except for the second before the
	next minute mark
	time marks consist of a reduction of transmitter power to 25%
	of the nominal level
	the falling edge is the time indication (on time)
	time marks of a 100ms duration constitute a logical 0
	time marks of a 200ms duration constitute a logical 1
</pre>

see the spec. (basically a (non-)inverted pseudo random phase shift) encoding:

<pre>	FM:

	Second	Contents
	0  - 10	AM: free, FM: 0
	11 - 14	free
	15		R     - alternate antenna
	16		A1    - expect zone change (1 hour before)
	17 - 18	Z1,Z2 - time zone
		 0  0 illegal
		 0  1 MEZ  (MET)
		 1  0 MESZ (MED, MET DST)
		 1  1 illegal
	19	A2    - expect leap insertion/deletion (1 hour before)
	20	S     - start of time code (1)
	21 - 24	M1    - BCD (lsb first) Minutes
	25 - 27	M10   - BCD (lsb first) 10 Minutes
	28	P1    - Minute Parity (even)
	29 - 32	H1    - BCD (lsb first) Hours
	33 - 34	H10   - BCD (lsb first) 10 Hours
	35	P2    - Hour Parity (even)
	36 - 39	D1    - BCD (lsb first) Days
	40 - 41	D10   - BCD (lsb first) 10 Days
	42 - 44	DW    - BCD (lsb first) day of week (1: Monday -> 7: Sunday)
	45 - 49	MO1   - BCD (lsb first) Month
	50	MO10  - 10 Months
	51 - 53	Y1    - BCD (lsb first) Years
	54 - 57	Y10   - BCD (lsb first) 10 Years
	58 	P3    - Date Parity (even)
	59	      - usually missing (minute indication), except for leap insertion
</pre>

* * *

#### Schmid clock

Schmid clock: needs poll, binary input, end='\xFC', sync start

The Schmid clock is a DCF77 receiver that sends a binary time code at the reception of a flag byte. The contents if the flag byte determined the time code format. The binary time code is delimited by the byte 0xFC.

<pre>	TTY setup is:
		CFLAG		(B1200|CS8|CREAD|CLOCAL)
		IFLAG		0
		OFLAG		0
 		LFLAG		0

</pre>

The command to Schmid's DCF77 clock is a single byte; each bit allows the user to select some part of the time string, as follows (the output for the lsb is sent first).

<pre>	Bit 0:	time in MEZ, 4 bytes *binary, not BCD*; hh.mm.ss.tenths
	Bit 1:	date 3 bytes *binary, not BCD: dd.mm.yy
	Bit 2:	week day, 1 byte (unused here)
	Bit 3:	time zone, 1 byte, 0=MET, 1=MEST. (unused here)
	Bit 4:	clock status, 1 byte,	0=time invalid,
					1=time from crystal backup,
					3=time from DCF77
	Bit 5:	transmitter status, 1 byte,
					bit 0: backup antenna
					bit 1: time zone change within 1h
					bit 3,2: TZ 01=MEST, 10=MET
					bit 4: leap second will be
						added within one hour
					bits 5-7: Zero
	Bit 6:	time in backup mode, units of 5 minutes (unused here)
</pre>

* * *

#### Trimble SV6 ASCII time code (TAIP)

Trimble SV6: needs poll, ascii timecode, start='>', end='<', query='>QTM<', eol='<'

Trimble SV6 is a GPS receiver with PPS output. It needs to be polled. It also need a special tty mode setup (EOL='<').

<pre>	TTY setup is:
		CFLAG            (B4800|CS8|CREAD)
		IFLAG            (BRKINT|IGNPAR|ISTRIP|ICRNL|IXON)
		OFLAG            (OPOST|ONLCR)
		LFLAG            (ICANON|ECHOK)
</pre>

Special flags are:

<pre>		PARSE_F_PPSPPS	    - use CIOGETEV for PPS time stamping
		PARSE_F_PPSONSECOND - the time code is not related to
				      the PPS pulse (so use the time code
				      only for the second epoch)

	Timecode
	0000000000111111111122222222223333333	/ char
	0123456789012345678901234567890123456	\ posn
	>RTMhhmmssdddDDMMYYYYoodnnvrrrrr;*xx<	Actual
	----33445566600112222BB7__-_____--99-	Parse
	>RTM                      1     ;*  < 	Check
</pre>

* * *

#### ELV DCF7000

ELV DCF7000: end='\r', pattern=" - - - - - - - \r"

The ELV DCF7000 is a cheap DCF77 receiver sending each second a time code (though not very precise!) delimited by '`r'

<pre>	Timecode
	  YY-MM-DD-HH-MM-SS-FF\r

		FF&0x1	- DST
		FF&0x2	- DST switch warning
		FF&0x4  - unsynchronised
</pre>

* * *

#### HOPF 6021 und Kompatible

HOPF Funkuhr 6021 mit serieller Schnittstelle Created by F.Schnekenbuehl <frank@comsys.dofn.de> from clk_rcc8000.c Nortel DASA Network Systems GmbH, Department: ND250 A Joint venture of Daimler-Benz Aerospace and Nortel.

<pre> hopf Funkuhr 6021 
      used with 9600,8N1,
      UTC via serial line
      "Sekundenvorlauf" ON
      ETX zum Sekundenvorlauf ON
      dataformat 6021
      output time and date
      transmit with control characters
      transmit evry second
 </pre>

Type 6021 Serial Output format

<pre>      000000000011111111 / char
      012345678901234567 \ position
      sABHHMMSSDDMMYYnre  Actual
       C4110046231195     Parse
      s              enr  Check

  s = STX (0x02), e = ETX (0x03)
  n = NL  (0x0A), r = CR  (0x0D)

  A B - Status and weekday

  A - Status

      8 4 2 1
      x x x 0  - no announcement
      x x x 1  - Summertime - wintertime - summertime announcement
      x x 0 x  - Wintertime
      x x 1 x  - Summertime
      0 0 x x  - Time/Date invalid
      0 1 x x  - Internal clock used 
      1 0 x x  - Radio clock
      1 1 x x  - Radio clock highprecision

  B - 8 4 2 1
      0 x x x  - MESZ/MEZ
      1 x x x  - UTC
      x 0 0 1  - Monday
      x 0 1 0  - Tuesday
      x 0 1 1  - Wednesday
      x 1 0 0  - Thursday
      x 1 0 1  - Friday
      x 1 1 0  - Saturday
      x 1 1 1  - Sunday
</pre>

* * *

#### Diem Computime Clock

The Computime receiver sends a datagram in the following format every minute

<pre>   
   Timestamp	T:YY:MM:MD:WD:HH:MM:SSCRLF 
   Pos          0123456789012345678901 2 3
		0000000000111111111122 2 2
   Parse        T:  :  :  :  :  :  :  \r\n

   T	Startcharacter "T" specifies start of the timestamp 
   YY	Year MM	Month 1-12 
   MD	Day of the month 
   WD	Day of week 
   HH	Hour 
   MM   Minute 
   SS   Second
   CR   Carriage return 
   LF   Linefeed
</pre>

* * *

#### WHARTON 400A Series Clock with a 404.2 Serial interface

The WHARTON 400A Series clock is able to send date/time serial messages in 7 output formats. We use format 1 here because it is the shortest. We set up the clock to send a datagram every second. For use with this driver, the WHARTON 400A Series clock must be set-up as follows :

<pre>  					Programmable	Selected
  					Option No	Option
	BST or CET display		3		9 or 11
	No external controller		7		0
	Serial Output Format 1		9		1
	Baud rate 9600 bps		10		96
	Bit length 8 bits		11		8
	Parity even			12		E
</pre>

WHARTON 400A Series output format 1 is as follows :

<pre>   Timestamp	STXssmmhhDDMMYYSETX
   Pos		0  12345678901234
  		0  00000000011111

   STX	start transmission (ASCII 0x02)
   ETX	end transmission (ASCII 0x03)
   ss	Second expressed in reversed decimal (units then tens)
   mm	Minute expressed in reversed decimal
   hh	Hour expressed in reversed decimal
   DD	Day of month expressed in reversed decimal
   MM	Month expressed in reversed decimal (January is 1)
   YY	Year (without century) expressed in reversed decimal
   S	Status byte : 0x30 +
		bit 0	0 = MSF source		1 = DCF source
		bit 1	0 = Winter time		1 = Summer time
		bit 2	0 = not synchronised	1 = synchronised
		bit 3	0 = no early warning	1 = early warning
</pre>
