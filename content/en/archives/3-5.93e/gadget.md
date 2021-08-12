---
title: "Gadget Box PPS Level Converter and CHU Modem"
type: archives
---

#### Table of Contents

*  [Introduction](/archives/3-5.93e/gadget/#introduction)
*  [Circuit Description](/archives/3-5.93e/gadget/#circuit-description)
*  [Files](/archives/3-5.93e/gadget/#files)

* * *

#### Introduction

Many radio clocks used as a primary reference source for NTP servers produce a pulse-per-second (PPS) signal that can be used to improve accuracy to a high degree. However, the signals produced are usually incompatible with the modem interface signals on the serial ports used to connect the signal to the host. The gadget box consists of a handful of electronic components assembled in a small aluminum box. It includes level converters and a optional radio modem designed to decode the radio timecode signals transmitted by the Canadian time and frequency station CHU. A complete set of schematics, PCB artwork, drill templates is in the [gadget.tar.Z](/reflib/software/gadget.tar.Z) file.

The gadget box is assembled in a 5"x3"x2" aluminum minibox containing the level converter and modem circuitry. It includes two subcircuits. One of these converts a TTL positive edge into a fixed- width pulse at EIA levels and is for use with a timecode receiver or oscillator including a TTL PPS output. The other converts the timecode modulation broadcast by Canadian time/frequency standard station CHU into a 300-bps serial character stream at EIA levels and is for use with the <tt>tty_clk</tt> and <tt>chu_tty</tt> line disciplines in the xntp3 distribution. 

This archive contains complete construction details for the gadget box, including schematic, parts list and artwork for a two-sided, printed-circuit board. All files are in PostScript, with the exception of this file and an information file, which are in ASCII. The artwork is in the 1:1 scale and is suitable for direct printing on photographic resist for each side of the board. While a plated-through-holes process is most convenient, it is possible to bridge the two sides using soldered wires where necessary. 

* * *

#### Circuit Description

Following is a brief functional description of the device. See the schematic diagram gadget.s01 for reference. The audio output of a shortwave radio tuned to CHU at 3330, 7335 or 14670 kHz is connected to J2. A level of at least 30 mV peak-peak is required, such as provided by the recorder output on many receivers. The input level is adjusted by potentiometer R8 so that the timecode modulation broadcast at 31-39 seconds past the minute reliably lights green LED1, but the signals broadcast during other seconds of the minute do not.

Opamp U4A provides low-impedance drive for the bridged-tee bandpass filter U4B. The filter has a bandpass of about 600 Hz at the 6-dB points and a center frequency of about 2150 Hz. It is designed to avoid aliasing effects with receivers of relatively wide bandpass characteristics. The modem itself is implemented by U2 and its associated circuitry. Resistors R4 and R1 are a 40-dB pad which matches the filter output to the modem input. U2 is a TTL/EIA level converter with integral power supply for bipolar signals. The modem output is available at pin 3 (receive data) of DB25 connector J1.

The TTL PPS signal is connected via J3 to a retriggerable one-shot U3A, which generates a TTL pulse of width determined by potentiometer R7. The pulse width is determined by the bit rate of the attached serial port. In the common case the width is one bit-time, such as 26 us for 38.4 kbps, for example. This appears to the port as a single start bit of zero followed by eight bits of ones and a stop bit of one. The second one-shot U3B generates a 200-ms pulse suitable for driving the amber LED3 as a visual monitor. The output of U3A is converted to EIA levels by U1 and appears at pin 12 (secondary receive data) of J1.

If only the PPS circuit is required, U2 and U4 can be deleted and the gadget box powered from the EIA modem-control signal at pin 20 (terminal ready) of J1, assuming this signal is placed in the on (positive voltage) condition by the computer program. J1 is wired to keep most finicky UARTs and terminal-driver programs happy. If the CHU circuit is required, an external 12-volt AC transformer or 9-12-volt DC supply connected to J4 is required. Red LED2 indicates power is supplied to the box.

* * *

#### Files

Following is a list of files included in this archive. All files are in PostScript, except the <tt>README</tt> and <tt>gadget.lst</tt> files, which are in ASCII. The files <tt>gadget.s01, gadget.s02</tt> and <tt>gadget.lst</tt> were generated using the Schema schematic-capture program from Omation. The printed-circuit files <tt>*.lpr</tt> were generated using Schema-PCB, also from Omation.

<tt>README</tt> - helpful information  
<tt>gadget.s01</tt> - circuit schematic  
<tt>gadget.s02</tt> - minibox assembly drawing  
<tt>gadget.lst</tt> - net list, pin list, parts list, etc.  
<tt>gen0102.lpr</tt> - pcb x-ray diagram  
<tt>art01.lpr</tt> - pcb artword side 1  
<tt>art02.lpr</tt> - pcb artwork side 2  
<tt>adt0127.lpr</tt> - pcb assembly drawing  
<tt>dd0124.lpr</tt> - pcb drill drawing  
<tt>sm0228.lpr</tt> - pcb solder mask (side 2)  
<tt>sst0126.lpr</tt> - pcb silkscreen mask (side 1)