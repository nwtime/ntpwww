---
title: "NTPv3 refclocks"
type: archives
noindex: true 
sitemap_exclude: true
---

This is a short overview for the reference clocks currently supported by `xntp` V3. Ultimate wisdom can be obtained from `xntpd/refclock_*.c`. This page was derived from that information - unfortunately some comments in the files tend to get stale - so use with caution.

| Refclock address | Type |
| ----- | ----- |
| `127.127.0.x` | no clock (fails to configure) |
| `127.127.1.x` | local clock - use local clock as reference |
| `127.127.2.x` | no clock (fails to configure) |
| `127.127.3.x` | PSTI 1010/1020 WWV Clock |
| `127.127.4.x` | SPECTRACOM WWVB receiver 8170 and Netclock/2 |
| `127.127.5.x` | Kinimetric Truetime 468-DC GOES receiver |
| `127.127.6.x` | IRIG audio decode (Sun & modified BSD audio driver) |
| `127.127.7.x` | CHU Timecode (via normal receiver & Bell 103 modem) |
| `127.127.8.x` | PARSE (generic driver for a bunch of DCF/GPS clocks; can be extended for other clocks too). `x` can be:<br>`0-3`: Meinberg PZF535/TCXO<br> `4-7`:	Meinberg PZF535/OCXO<br> `8-11`: Meinberg DCF U/A 31<br> `12-15:` ELV DCF7000<br> `16-19`:	Walter Schmid DCF receiver (Kit)<br> `20-23`: Conrad DCF77 receiver module + level converter (Kit)<br> `24-27`:	TimeBrick (limited availability ask <time@informatik.uni-erlangen.de>)<br> `28-31`:	Meinberg GPS166<br> `32-35`	Trimble SV6 GPS receiver |
| `127.127.9.x`	| MX4200 GPS receiver |
| `127.127.10.x` | Austron 2201A GPS Timing Receiver |
| `127.127.11.x` | Kinemetrics Truetime OM-DC OMEGA Receiver |
| `127.127.12.x` | KSI/Odetecs TPRO-S IRIG-B / TPRO-SAT GPS |
| `127.127.13.x` | Leitch: CSD 5300 Master Clock System Driver |
| `127.127.14.x` | MSFEES |
| `127/127.15.x` | TrueTime GPS/TM-TMD |
| `127.127.16.x` | Bancomm GPS/IRIG Ticktock |
| `127.127.17.x` | Datum Programmable Time System |