---
title: "Gadget Box PPS Level Converter and CHU Modem"
type: archives
noindex: true 
sitemap_exclude: true
---

![webp](/documentation/pic/gadget.webp)A Gadget Box built by Chuck Hanavin

* * *

Many radio clocks used as a primary reference source for NTP servers produce a pulse-per-second (PPS) signal that can be used to improve accuracy to a high degree. However, the signals produced are usually incompatible with the modem interface signals on the serial ports used to connect the signal to the host. The gadget box consists of a handful of electronic components assembled in a small aluminum box. It includes level converters and a optional radio modem designed to decode the radio timecode signals transmitted by the Canadian time and frequency station CHU. A complete set of schematics, PCB artwork, drill templates can be obtained as [gadget.tar.Z](/reflib/software/gadget.tar.Z).

The gadget box is assembled in a 5"x3"x2" aluminum minibox containing the level converter and modem circuitry. It includes two subcircuits. One of these converts a TTL positive edge into a fixed-width pulse at EIA levels and is for use with a timecode receiver or oscillator including a TTL PPS output. The other converts the timecode modulation broadcast by Canadian time/frequency standard station CHU into a 300-bps serial character stream at EIA levels and is for use with the [Radio CHU Audio Demodulator/Decoder](/documentation/drivers/driver7/) driver.
