---
title: "NTP Timestamp Calculations"
type: archives
toc_hide: true
---

![gif](/documentation/pic/wingdorothy.gif)

from [_The Wizard of Oz_](/reflib/pictures/), L. Frank Baum

Public transport in Oz

* * *

#### Table of Contents

*  [Abstract](/reflib/time/#abstract)
*  [1. Introduction](/reflib/time/#1-introduction)
*  [2. Data Formats](/reflib/time/#2-data-formats)
*  [3. Datestamps and Timestamps as Finite Groups](/reflib/time/#3-datestamps-and-timestamps-as-finite-groups)
*  [4. Time Difference Calculations](/reflib/time/#4-time-difference-calculations)
*  [5. On-Wire Protocol Implications](/reflib/time/#5-on-wire-protocol-implications)

* * *

#### Abstract

This document presents a mathematical analysis of the principles of clock offset and roundtrip delay calculations used by the Network Time Protocol (NTP). The analysis is based on the properties of finite additive groups using two's complement arithmetic. An important conclusion is that the correct time synchronization is assured if the NTP client is set reliably within 68 years when first started.

* * *

#### 1. Introduction

The timestamp calculations described in this document are used by the NTP protocol machine and clock discipline algorithms to adjust the time of the client clock to align with the time of the server clock. The calculations are not designed to set the client clock directly, only to provide an offset correction relative to the server clock and without respect to any arbitrary epoch.

The conclusion in this document is so important as to be previewed here.

> If the client clock is set within 68 years of the server clock before the NTP protocol is started, the NTP algorithms will set the client clock to the server clock with accuracy and without ambiguity.

The discussion in this document is designed to support and confirm this statement before, at and beyond the timescale overflow event that will occur in 2036.

* * *

#### 2. Data Formats

_Time_ is an abstraction that establishes an ordering of events relative to a _timescale_. In NTP, a _date_ is a point on the timescale expressed in one of two formats, _datestamp_ and _timestamp._ As shown in Figure 1, a datestamp is a 128-bit, signed fixed-point number in seconds and fraction, with the decimal point to the left of bit 64. Dates are relative to the _prime epoch,_ 0 h, 1 January 1900; dates prior to the prime epoch have negative values, while dates since then have positive values. A timestamp is a 64-bit, unsigned fixed-point number in seconds and fraction with the decimal point to the left of bit 32. Datestamps are used in internal calculations where extended range and freedom from overflow are important, while timestamps are used in packet headers where economy of storage is important.

![gif](/documentation/pic/time1.gif)

**Figure 1. NT Data Formats**

Datestamps span the age of the Universe with a precision less than the time light transits an atom. Timestamps span a 136-year interval , called an _era_, with a precision of 232 ps. The datestamp format includes a timestamp field that specifies the seconds and fraction of an era, together with an era number field that specifies the timestamp origin. There is a special convention in both timestamp and datestamp formats where the value zero represents an undefined or unknown date that should not be used in time related calculations.

* * *

#### 3. Datestamps and Timestamps as Finite Groups

In the remainder of this document, the decimal point in datestamps and timestamps formats is not significant and the numbers are interpreted as 128-bit or 64-bit integers. Datestamps and timestamps are elements of additive groups consisting of integers and the operations of two's complement arithmetic. There are only two operations in the NTP additive group, addition and complement, each modulo 2<sup>128</sup> for the datestamps group and 2<sup>64</sup> for the timestamp group, but otherwise the operations are the same. Datestamps are a signed data type, while timestamps are an unsigned data type.

Let <code>_A_</code> and <code>_B_</code> be elements of an additive group of integers <code>modulo 2<sup>_n</sup>_</code> for some <code>_n_</code>. Addition is defined <code>_A_ + _B_ = _B_ + _A_ mod 2<sup>_n</sup>_</code>. The identity 0 is defined such that <code>_A_ + 0 = 0 + _A_ = _A_ mod 2<sup>_n</sup>_</code>. The complement (inverse) <code>-_A_</code> is defined such that <code>_A_ + (-_A_) = 0 mod 2<sup>_n</sup>_</code>. To form the complement <code>-_A_</code>, first invert each bit of <code>_A_</code>, then add the constant 1 to the result. Equivalently, <code>-_A_ = 2<sup>_n</sup>_ - _A_</code>. Finally, the _offset_ of <code>_B_</code> relative to <code>_A_</code> is defined <code>_A_ + (-_B_) mod 2<sup>_n</sup>_</code>. This is the only allowable operation involving datestamp or timestamp operands and results in a signed data type.

* * *

#### 4. Time Difference Calculations

For the additive group of <code>2<sup>_n</sup>_</code> elements, the arithmetic logic unit (ALU) consists of a straight binary adder that does not distinguish the sign of the operands or result. However, in two's complement notation, the sign is implicit in the most significant bit <code>_S_</code>. The ALU produces an <code>_n_</code>-bit result together with a carry bit <code>_C_</code> representing the <code>_n_+1</code>th bit. For timestamp calculations, the <code>_C_</code> bit is in effect the least significant bit of the era number of the datestamp, but most often it is implicit in the calculation of offset.

The mathematics involved in additive group calculations can be illustrated with the following examples. Let <code>_A_</code> and <code>_B_</code> be unsigned integers <code>modulo 2<sup>_n</sup>_</code>, where<code> _n_ = 4</code>. The integers 0-7 with <code>_S_ = 0</code> are positive, while the integers 8-15 with <code>_S_ = 1</code> are negative. Let <code>_A_ = 7</code> and <code>_B_ = 5</code>, then the offset <code>_A_ + (-_B_) = 7 + (-5) = 7 + 11 = 2 mod 16</code>. Reversing the operands, let <code>_A_ = 5</code> and <code>_B_ = 7</code>, then <code>_A_ + (-_B_) = 5 + (-7) = 5 + 9 = -2 mod 16</code>. Note that, while the operands are unsigned type, the resulting offset is interpreted as signed type. This represents typical cases when the operands are in the same era. If, for example, <code>_A_</code> is in the next era later than <code>_B_</code>, let <code>_A_ = 2</code> and <code>_B_ =14</code>. Then,<code> _A_ + (-_B_) = 2 + (-14) = 4 mod 16</code>. Note that the modular operations can be performed before, during and after the calculation. Similar examples can be contrived for other values of <code>_n_, _A_,</code> and <code>_B_</code>, as long as the offset is less than <code>2<sup>_n</sup>_<sup>-1</sup>= 8</code> in these examples.

Returning to the interpretation of timestamps as fixed-point numbers, note that the integer portion represents an era of 136 years. This suggests the following general rule.

> Let the system clock be set within 68 years of the correct time, even if the correct time is not known exactly. Then, the offset can be correctly computed by the on-wire protocol and used to adjust the system clock to the correct time relative to an external source.

As a practical example, consider an NTP client started somewhere in 2012. In principle, the system clock can be initially set any time between after 1944 in era 0 and before 2080 in era 1. However, since an era is 136 years, 1944 in era 0 corresponds to timestamp year 44, while 2080 in era 1 also corresponds to timestamp year 44. To avoid possible ambiguity, the time should be initially set within a more narrow range than 68 years, perhaps 50 years. In such cases, the NTP on-wire protocol and clock discipline will eventauly align the system clock to the correct time in 2012.

* * *

#### 5. On-Wire Protocol Implications

Timestamp calculations are carefully constructed to avoid overflow while preserving precision. The only arithmetic operation permitted on raw timestamps is subtraction, which produces signed 64-bit timestamp differences from 68 years in the past to 68 years in the future.

All of the timestamp calculations discussed in this document involve differences between timestamps recorded at events such as the arrival or departure of an NTP packet. As described in previous sections of this document, the calculations apply whether or not the differences span none, one or more eras. The crucial distinction is whether the client clock is set within 68 years of the server clock before the protocol is started.

As in the protocol specification, let <code>_T_<sub>1</sub></code> be the client timestamp on the request packet, <code>_T_<sub>2</sub></code> the server timestamp upon arrival, <code>_T_<sub>3</sub></code> the server timestamp on departure of the reply packet and <code>_T_<sub>4</sub></code> the client timestamp upon arrival. The NTP on-wire protocol calculates the clock offset

<code>_offset_ = [(_T_<sub>2</sub> - _T_<sub>1</sub>) + (_T_<sub>3</sub> - _T_<sub>4</sub>)] / 2</code>

and roundtrip delay

<code>_delay_ = (_T_<sub>4</sub> - _T_<sub>1</sub>) - (_T_<sub>3</sub> - _T_<sub>2</sub>)</code>

In both the offset and delay equations, the calculations require raw timestamp differences that span no more than 68 years in the future to 68 years in the past. The previous discussion in this document confirms these differences can be computed correctly regardless of whether they span between two eras, as long as the eras are adjacent.

The offset and delay calculations require sums and differences of these raw timestamp differences that can span no more than from 34 years in the future to 34 years in the past without overflow. This is a fundamental limitation in 64-bit integer calculations.

In the NTPv4 reference implementation, all calculations involving offset and delay values use 64-bit floating double arithmetic, with the exception of raw timestamp subtraction, as mentioned above. The raw timestamp differences are then converted to 64-bit floating double format without loss of precision or chance of overflow in subsequent calculations.

While this design benefits present and future NTP versions, it will not of course benefit previous versions that may be etched in hardware or firmware. Previous versions of the public NTP software, including NTP Version 3 (`xntpd`) will have the same problem, but these versions use integer arithmetic throughout and are much harder to update.

NTP Version 3 has in addition well known ambiguities due to 16-bit overflows in some cases and is not recommended for new systems. However, it is important to note that Simple Network Time Protocol (SNTP) clients that set the clock directly and do not include the offset and delay calculations described in this document do not have the overflow problem and can continue to be used without hazard, at least until 2036.