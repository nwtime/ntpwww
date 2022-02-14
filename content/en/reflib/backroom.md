---
title: "Backroom Test Facility"
type: archives
toc_hide: true
---

![gif](/archives/pic/beaver.gif)

[_pogo_](/reflib/pictures/), Walt Kelly

In case of fan failure

* * *

#### Table of Contents

*  [The Backroom](/reflib/backroom/#the-backroom)
*  [Network Facilities](/reflib/backroom/#network-facilities)
*  [References](/reflib/backroom/#references)

* * *

#### The Backroom

The Backroom Test Facility (BTF) is located at 43 The Horseshoe, Newark, DE 19711, geographic coordinates 39:42:02.915N, 75:46:52.046W. The BTF presently includes five Unix workstations, three Windows/XP PCs, a Windows/XP laptop, color laser printer, high resolution scanner and assorted hubs and routers connected together with 100-Mb Ethernet fiber segments and a 54-Mb WiFi backup. Four UPS systems keep the computers afloat during power glitches. This is where we conduct the most dangerous experiments requiring a containment facility. We keep five of the computers quarantined in the basement (below) to resist incidental radiation when a hacker is zapped.

![gif](/archives/pic/basement.jpg)

Representative Network Time Protocol (NTP) servers throughout the world are monitored from the BTF on a regular basis and the data recorded for later analysis. Together, the workstations and PCs have 9 GB of RAM and 1900 GB of disk resources. On many occasions, the BTF has been useful in diagnosing improper network configuration and operation.

![jpg](/archives/pic/fuzzballb.jpg)

This is also the main facility for program development and testing, as well as the final resting place for the last known LSI-11 Fuzzball <sup>[1](#myfootnote1)</sup>, once prominent in Internet research projects.

![jpg](/archives/pic/w3hcf4.jpg) 

The BTF also includes [two-way voice and data radio transmission equipment](/archives/pic/w3hcf3.jpg) covering HF, VHF and UHF amateur bands. The [antenna farm on the roof](/archives/pic/43_front.jpg) is a local landmark. Any of four radios and several voice and data modes can be remotely controlled and accessed using standard Internet data and multicast audio tools. The radios can run for extended periods without external power for emergency and disaster communications.

![gif](/archives/pic/stack.gif)

The BTF is equipped to receive GPS, CDMA, WWVB, WWV/H and CHU transmissions. Receivers for WWVB and WWV are shown, including a specially designed DSP demodulator/decoder for WWV <sup>[2](#myfootnote2)</sup>. Any of five communications receivers for WWV/H and CHU can be connected to a workstation sound card and controlled by program. [NTP drivers](/archives/4.2.8-series/audio/) for WWV/H and CHU demodulate and decode the receiver audio signal and automatically select the best transmitter frequency.

For the most accurate and precise timekeeping, a GPS receiver, rubidium frequency standard and cesium clock standard are used to discipline the computer clock in one of the Unix workstations, as well as calibrate the radio transmit and receive frequencies. If for any reason the heavens and the atoms fail, the system can fall back to more primitive means.

[//]: <> (DL July/2021: remove reference to /wav/bbc.wav)

* * *

#### Network Facilities

![gif](/archives/pic/backroom.gif)

The BTF DCnet subnet is connected to the [campus DCnet subnet](/reflib/dcnet/) via a 2x64 kb ISDN link and Cisco routers. The various radios and workstations are also used by the NTP volunteer developer corps to test and validate new NTP versions. More information is in the briefing slides: DCnet Research Network [PDF](/reflib/brief/dcnet/dcnet.pdf).

[_Sunshine_](/reflib/fam/) is our Guard Kitten. If a rogue ICMP Destination Unreachable packet shows up here, he barks. He has his own computer, complete with keyboard and mouse.

![jpg](/archives/pic/yellow3.jpg)![jpg](/archives/pic/mouse.jpg)

* * *

#### References

<a name="myfootnote1">1</a>  Mills, D.L. The Fuzzball. _Proc. ACM SIGCOMM 88 Symposium_ (Palo Alto CA, August 1988), 115-122\. [PostScript](/reflib/papers/fuzz.ps) | [PDF](/reflib/papers/fuzz.pdf)

<a name="myfootnote2">2</a>  Mills, D.L. A precision radio clock for WWV transmissions. Electrical Engineering Report 97-8-1, University of Delaware, August 1997, 25 pp. Abstract: [PDF](/reflib/reports/wwv/wwva.pdf), Body: [PDF](/reflib/reports/wwv/wwvb.pdf)