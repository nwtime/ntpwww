---
title: "MX4200 Receiver Data Format"
description: "This page provides an overview of the MX4200 Receiver Data Format, including the supported control port sentences, control port input sentences, and control port output sentences." 
type: archives
---

#### Table of Contents

*   [Control Port Sentences](/documentation/drivers/mx4200data/#control-port-sentences)
*   [Control Port Input Sentences](/documentation/drivers/mx4200data/#control-port-input-sentences)
*   [Control Port Output Sentences](/documentation/drivers/mx4200data/#control-port-output-sentences)

* * *

#### Control Port Sentences

The Control (CDU) Port is used to initialize, monitor, and control the receiver. The structure of the control port sentences is based on the <cite>NMEA-0183</cite> Standard for Interfacing Marine Electronics Navigation Devices (version 1.5). For more details, please refer to the <cite>NMEA-0183</cite> Specification available from the [National Marine Electronics Association](https://www.nmea.org/).

Reserved characters are used to indicate the beginning and the end of records in the data stream, and to delimit data fields within a sentence. Only printable ASCII characters (Hex 20 through 7F) may be used in a sentence. Table 2 lists the reserved characters and defines their usage. Table 1 illustrates the general Magnavox proprietary NMEA sentence format.

**Table 1. Magnavox Proprietary NMEA Sentence Format**

`$PMVXG,XXX,...................*CK`

| Character | Meaning |
| ----- | ----- |
| <code>`</code> | Sentence Start Character |
| `P` | Special ID (P = Proprietary) |
| `MVX` | Originator ID (MVX = Magnavox) |
| `G` | Interface ID (G = GPS) |
| `XXX` | Sentence Type |
| `...` | Data |
| `*` | Optional Checksum Field Delimiter |
| `CK` | Optional Checksum |

**Table 2. NMEA Sentence Reserved Characters**

| Character | Hex Value | Usage |
| ----- | ----- | ----- |
| ` | `24` | Start of Sentence Identifier |
| `{cr}{lf}` | `0D 0A` | End of Sentence Identifier |
| `,` | `2C` | Sentence Delimiter |
| `*` | `2A` | Optional Checksum Field Delimiter |

Following the start character `$`, are five characters which constitute the block label of the sentence. For Magnavox proprietary sentences, this label is always `PMVXG`. The next field after the block label is the sentence type, consisting of three decimal digits.

The data, delimited by commas, follows the sentence type. Note that the receiver uses a free-format parsing algorithm, so you need not send the exact number of characters shown in the examples. You will need to use the commas to determine how many bytes of data need to be retrieved.

The notation `CK` shown in Table 1 symbolically indicates the optional checksum in the examples. The checksum is computed by exclusive-ORing all of the bytes between the `$` and the `*` characters. The `$`, `*` and the checksum are not included in the checksum computation.

Checksums are optional for Control Port input sentences, but are highly recommended to limit the effects of communication errors. Magnavox receivers always generate checksums for Control Port output sentences.

ASCII data characters are transmitted in the following format:

| Bit Type | Number |
| ----- | ----- |
| Data | 8 (msb always 0) |
| Parity | None |
| Stop | 1 |

NULL fields are fields which do not contain any data. They would appear as two commas together in the sentence format, except for the final field. Some Magnavox proprietary sentences require that the format contain NULL fields. Mandatory NULL fields are identified by an `*` next to the respective field.

* * *

#### Control Port Input Sentences

These are the subset of the MX4200 control port input sentences sent by the NTP driver to the GPS receiver.

**$PMVXG,000**

**Initialization/Mode Control - Part A**

: Initializes the time, position and antenna height of the MX4200.

| Field | Description | Units | Format | Default | Range |
| ----- | ----- | ----- | ----- | ----- | ----- |
| `1` | Day | | Int | | 1-31 |
| `2` | Month | | Int | | 1-12 |
| `3` | Year | | Int | | 1991-9999 |
| `4` | GMT Time | HHMMSS | Int | | 000000-235959 |
| `5` | WGS-84 Latitude | DDMM.MMMM | Float | 0.0 | 0-8959.9999 |
| `6` | North/South Indicator | | Char | N | N, S |
| `7` | WGS-84 Longitude | DDDMM.MMMM | Float | 0.0 | 0-17959.9999 |
| `8` | East/West Indicator | | Char | E | E, W |
| `9` | Altitude (height above Mean Sea Level) in meters (WGS-84) | Meters | Float | 0.0 | +/-99999.0 |
| `10` | Not Used | | | |

Example:

`$PMVXG,000,,,,,,,,,,*48`  
`$PMVXG,000,,,,,5128.4651,N,00020.0715,W,58.04,*4F`

* * *

**$PMVXG,001**

**Initialization/Mode Control - Part B**

: Specifies various navigation parameters: altitude aiding, acceleration DOP limits, and satellite elevation limits.

| Field | Description | Units | Format | Default | Range |
| ----- | ----- | ----- | ----- | ----- | ----- |
| `*1` | Constrain Altitude | | Int | 1 | `0` 3D Only<br> `1` Auto<br> `2`2D Only |
| `2` | Not Used | | | | |
| `*3` | Horizontal Acceleration Factor | m/sec<sup>^</sup>2 | Float | 1.0 | 0.5-10.0 |
| `*4` | Not Used | | | | |
| `*5` | VDOP Limit | | Int | 10 | 1-9999 |
| `*6` | HDOP Limit | | Int | 10 | 1-9999 |
| `7`  | Elevation Limit | Deg | Int | 5 | 0-90 |
| `8`  | Time Output Mode | | Char | U | `U` UTC<br> `L` Local Time |
| `9`  | Local Time Offset | HHMM | Int | 0 | +/- 0-2359 |

Example:

`$PMVXG,001,3,,0.1,0.1,10,10,5,U,0*06`

* * *

**$PMVXG,007**

**Control Port Output Configuration**

: This message enables or disables output of the specified sentence and defines the output rate. The user sends this message for each sentence that the receiver is to output.

| Field | Description | Units | Format | Default | Range |
| ----- | ----- | ----- | ----- | ----- | ----- |
| `1` | Control Port Output Block Label | | Char | | |
| `2` | Clear Current Output List | | Int | | `0` No<br> `1` Yes |
| `3` | Add/Delete Sentence from List | | Int | | `1` Append<br> `2` Delete |
| `4` | Not Used | | | | |
| `5` | Sentence Output Rate | Sec | Int | | 1-9999 |
| `6` | # digits of Precision for CGA and GLL sentences | | Int | 2 | 2-4 |
| `7` | Not Used | | | | |
| `8` | Not Used | | | | |

Example:

`$PMVXG,007,022,0,1,,1,,,*4F`

* * *

**$PMVXG,023**

**Time Recovery Configuration**

: This message is used to enable/disable the time recovery feature of the receiver. The time synchronization for the 1PPS output is specified in addition to a user time bias and an error tolerance for a valid pulse. This record is accepted in units configured for time recovery. If the back panel contains a 1PPS outlet, the receiver is a time recovery unit.

| Field | Description | Units | Format | Default | Range |
| ----- | ----- | ----- | ----- | ----- | ----- |
| `*1`  | Time Recovery Mode | | Char | D | `D` Dynamic<br> `S` Static<br> `K` Known Position<br> `N` No Time Recovery |
| `2` | Time Synchronization | | Char | G | `U` UTC<br> `G` GPS |
| `3` | Time Mark Mode | | Char | A | `A` Always<br> `V` Valid Pulses Only |
| `4` | Maximum Time Error | Nsec | Int | 100 | 50-1000 |
| `5` | User Time Bias | Nsec | Int | 0 | +/- 99999 |
| `6` | ASCII Time Message Control | | Int | 0 | `0` No Output<br> `1` 830 to Control Port<br> `2` 830 to Equipment Port |
| `7` | Known Pos PRN | | Int | 0 | 1-32<br>  `0` Track All Sats |

Example:

`$PMVXG,023,S,U,A,500,0,1,*16`

* * *

**$CDGPQ,YYY**

**Query From a Remote Device / Request to Output a Sentence**

: Enables the controller to request a one-time transmission of a specific block label. To output messages at a periodic rate, refer to input sentence $PMVXG,007.

| Field | Description | Format | Range |
| ----- | ----- | ----- | ----- |
| `1:CD` | ID of Remote Device | Char | (See NMEA-0183) |
| `2:GP` | GPS | Char | (See NMEA-0183) |
| `3:Q` | Query | Char | (See NMEA-0183) |
| `4:YYY` | Label of Desired Sentence | Char | Any Valid NMEA or Magnavox Sentence Type |

Example:

`$CDGPQ,030*5E`

* * *

#### Control Port Output Sentences

These are the subset of the MX4200 control port output sentences recognized by the NTP driver.

**$PMVXG,000**

**Receiver Status**

: Returns the current status of the receiver including the operating mode, number of satellites visible, and the number of satellites being tracked.

| Field | Description | Units | Format | Range |
| ----- | ----- | ----- | ----- | ----- |
| `1`| Current Receiver Status | | Char | `ACQ` Reacquisition<br> `ALT` Constellation Selection<br> `IAC` Initial Acquisition<br> `IDL` Idle, No Satellites<br>  `NAV` Navigating<br> `STS` Search The Sky<br> `TRK` Tracking |
| `2` | Number of Satellites that should be Visible | | Int | 0-12 |
| `3` | Number of Satellites being Tracked | | Int | 0-12 |
| `4` | Time since Last Navigation | HHMM | Int | 0-2359 |
| `5` | Initialization Status | | Int | `0` Waiting for Initialization<br> `1` Initialization Complete |

Example:

`$PMVXG,000,TRK,3,3,0122,1*19`

* * *

**$PMVXG,021**

**Position, Height, Velocity**

: This sentence gives the receiver position, height, navigation mode and velocity north/east. _This sentence is intended for post-analysis applications._

| Field | Description | Units | Format | Range |
| ----- | ----- | ----- | ----- | ----- |
| `1` | UTC Measurement Time | Seconds into the week | Float | 0-604800.00 |
| `2` | WGS-84 Latitude | DDMM.MMMM | Float | 0-89.9999 |
| `3` | North/South Indicator | | Char | N, S |
| `4` | WGS-84 Longitude | DDDMM.MMMM | Float | 0-179.9999 |
| `5` | East/West Indicator | | Char | E, W |
| `6` | Altitude (MSL) | Meters | Float | |
| `7` | Geoidal Height | Meters | Float | |
| `8` | Velocity East | M/Sec | Float | |
| `9` | Velocity North | M/Sec | Float | |
| `10` | Navigation Mode | | Int | _Navigating_ <br> `1` Position From a Remote Device<br> `2` 2D<br> `3` 3D<br> `4` 2D differential<br> `5` 3D differential<br>  _Not Navigating_  <br> `51` Too Few Satellites<br> `52` DOPs too large<br> `53` Position STD too large<br> `54` Velocity STD too large<br> `55` Too many iterations for velocity<br> `56` Too many iterations for position<br> `57` 3 Sat Startup failed |

Example:

`$PMVXG,021,142244.00,5128.4744,N,00020.0593,W,00054.4,0047.4,0000.1,-000.2,03*66`

* * *

**$PMVXG,022**

**DOPs**

: This sentence reports the DOP (Dilution Of Precision) values actually used in the measurement processing corresponding to the satellites listed. The satellites are listed in receiver channel order. Fields 11-16 are output only on 12-channel receivers.

| Field | Description | Units | Format | Range |
| ----- | ----- | ----- | ----- | ----- |
| `1` | UTC Measurement Time | Seconds into the week | Float | 0-604800.00 |
| `2` | East DOP (EDOP) | | Float | |
| `3` | North DOP (NDOP) | | Float | |
| `4` | Vertical DOP (VDOP) | | Float | |
| `5` | PRN on Channel #1 | | Int | 1-32 |
| `6` | PRN on Channel #2 | | Int | 1-32 |
| `7` | PRN on Channel #3 | | Int | 1-32 |
| `8` | PRN on Channel #4 | | Int | 1-32 |
| `9` | PRN on Channel #5 | | Int | 1-32 |
| `10` | PRN on Channel #6 | | Int | 1-32 |
| `11` | PRN on Channel #7 | | Int | 1-32 |
| `12` | PRN on Channel #8 | | Int | 1-32 |
| `13` | PRN on Channel #9 | | Int | 1-32 |
| `14` | PRN on Channel #10 | | Int | 1-32 |
| `15` | PRN on Channel #11 | | Int | 1-32 |
| `16` | PRN on Channel #12 | | Int | 1-32 |

Example:

`$PMVXG,022,142243.00,00.7,00.8,01.9,27,26,10,09,13,23*77`

* * *

**$PMVXG,030**

**Software Configuration**

: This sentence contains the navigation processor and baseband firmware version numbers.

| Field | Description | Format |
| ----- | ----- | ----- |
| `1` | Nav Processor Version Number | Char |
| `2` | Baseband Firmware Version Number | Char |

Example:

`$PMVXG,030,DA35,015`

* * *

**$PMVXG,101**

**Control Sentence Accept/Reject**

: This sentence is returned (on the Control Port) for every `$PMVXG` and `$XXGPQ` sentence that is received.

| Field | Description | Units | Format | Range |
| ----- | ----- | ----- | ----- | ----- |
| `1` | Sentence ID | | Char | |
| `2` | Accept/Reject Status | | Int | `0` Sentence Accepted<br> `1` Bad Checksum<br> `2` Illegal Value<br> `3` Unrecognized ID<br> `4` Wrong # of fields<br> `5` Required Data Field Missing<br> `6` Requested Sentence Unavailable |
| `3` | Bad Field Index | | Int | |
| `4` | Requested Sentence ID (If field #1 = GPQ) | | Char | |

Example:

`$PMVXG,101,GPQ,0,,030*0D`

* * *

**$PMVXG,523**

**Time Recovery Configuration**

: This sentence contains the configuration of the time recovery function of the receiver.

| Field | Description | Units | Format | Range |
| ----- | ----- | ----- | ----- | ----- |
| `1` | Time Recovery Mode | | Char | `D` Dynamic<br> `S` Static<br> `K` Known Position<br> `N` No Time Recovery |
| `2` | Time Synchronization | | Char | `U` UTC Time<br> `G` GPS Time |
| `3` | Time Mark Mode | | Char | `A` Always Output Time Pulse<br> `V` Only when Valid |
| `4` | Maximum Time Error for which a time mark will be considered valid | Nsec | Int | |
| `5` | User Time Bias | Nsec | Int | |
| `6` | Time Message Control | | Int | `0` No Message<br> `1` 830 to Control Port<br> `2` 830 to Equipment Port |
| `7` | Not Used | | | |

Example:

`$PMVXG,523,S,U,A,0500,000000,1,0*23`

* * *

**$PMVXG,830**

**Time Recovery Results**

: This sentence is output approximately 1 second preceding the 1PPS output. It indicates the exact time of the next pulse, whether or not the time mark will be valid (based on operator-specified error tolerance), the time to which the pulse is synchronized, the receiver operating mode, and the time error of the **last** 1PPS output. The leap second flag (Field #11) is not output by older receivers.

| Field | Description | Units | Format | Range |
| ----- | ----- | ----- | ----- | ----- |
| `1` | Time Mark Valid | | Char | `T` Valid<br> `F` Not Valid |
| `2` | Year | | Int | 1993- |
| `3` | Month | | Int | 1-12 |
| `4` | Day | Nsec | Int | 1-31 |
| `5` | Time | HH:MM:SS | Int | 00:00:00-23:59:59 |
| `6` | Time Synchronization | | Char | `U` UTC<br> `G` GPS |
| `7` | Operating Mode | | Char | `D` Dynamic<br> `S` Static<br> `K` Known Position |
| `8` | Oscillator Offset - estimate of oscillator frequency error | PPB | Int | |
| `9` | Time Mark Error of last pulse | Nsec | Int | |
| `10` | User Time Bias | Nsec | Int | | 
| `11` | Leap Second Flag - indicates that a leap second will occur. This value is usually zero except during the week prior to a leap second occurrence, when this value will be set to +/-1. A value of `+1` indicates that GPS time will be 1 second further ahead of UTC time. | | Int | -1,0,1 |

Example:

`$PMVXG,830,T,1998,10,12,15:30:46,U,S,000298,00003,000000,01*02`