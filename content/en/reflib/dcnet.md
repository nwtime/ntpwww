---
title: "DCnet Research Network"
type: archives
toc_hide: true
---

![gif](/documentation/pic/dartlogoa.gif)

* * *

#### Table of Contents

*  [Briefing Slides](/reflib/dcnet/#briefing-slides)
*  [Network Infrastructure](/reflib/dcnet/#network-infrastructure)
*  [Precision Timekeeping and Timecasting](/reflib/dcnet/#precision-timekeeping-and-timecasting)

* * *

#### Briefing Slides

*   CAIRN/DARTnet Collaboration [PDF](/reflib/brief/dartnet/dartnet.pdf)
*   DCnet Research Network [PDF](/reflib/brief/dcnet/dcnet.pdf)

* * *

#### Network Infrastructure

![icon](/documentation/pic/dcnet.gif)

We use our DCnet laboratory network (128.4 subnets 1-9) for protocol development, experiments and performance evaluation, as well as day-to-day videoconferencing with our collaborators throughout the US and western Europe. About two dozen workstations and PCs provide over 9.6 GB of RAM and 1900 GB of disk resources. Since the DCnet subnets can be isolated from the rest of the Internet, we can develop, refine and experiment with innovative network architectures and management protocols without threatening ongoing operations in other networks.

![icon](/documentation/pic/backroom.gif)

Our [Backroom Test Facility (BTF)](/reflib/backroom/) is a remote facility modelled after one once used in support of the DARPA Atlantic Satellite Program. It is populated by several Unix and Windows workstations and a mean collection of radio clocks, all connected by an ISDN link. This is where we conduct the most dangerous experiments requiring a containment facility.

![icon](/documentation/pic/route.gif)

DCnet is directly connected by dual redundant routers to the UDELnet campus backbone network and the EECISnet interdepartmental network, and indirectly to the Abilene Internet-2 backbone. DCnet is indirectly connected to the 6BONE network to support collaborative projects in high speed networking and development of innovative multicasting applications. We can support desktop applications between DCnet workstations and comparably provisioned networks connected to Abilene at full 100-Mb speeds.

* * *

#### Precision Timekeeping and Timecasting

![icon](/documentation/pic/clocks.gif)

Three of the campus file servers and routers and one of the Backroom file servers are specially equipped to function as precision time servers with nominal accuracies in the order of a few microseconds relative to Coordinated Universal Time (UTC). These servers are synchronized to GPS and WWVB receivers and frequency-stabilized by cesium oscillators. They provide synchronization to the 6BONE and DCnet research networks, the EECISnet and UDELnet campus networks, and the Internet at large using the [Network Time Protocol (NTP)](/reflib/ntp/) developed in our laboratory. They are coordinated with other NTP servers operated by the US Naval Observatory (USNO), National Institute of Science and Technology (NIST), and the national standards laboratories of several other countries. Collectively, they provide synchronization to a total of well over 100,000 clients scattered throughout the world.		