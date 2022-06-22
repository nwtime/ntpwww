---
title: "CAIRN/DARTnet Collaboration"
type: archives
toc_hide: true
---

![gif](/documentation/pic/pogo6.gif)

Researchers involved: David Mills, Jon Crowcroft (UCL), Kenneth Carlberg (SAIC)

Funding: Defense Advanced Research Projects Agency

Status: This project was completed in 2001. This page is for historic record.

* * *

#### Table of Contents

*  [Briefing Slides](/reflib/dartnet/#briefing-slides)
*  [Importance of the Problem](/reflib/dartnet/#importance-of-the-problem)
*  [Brief Description of Work and Results](/reflib/dartnet/#brief-description-of-work-and-results)
*  [Future Plans](/reflib/dartnet/#future-plans)

* * *

#### Briefing Slides

* CAIRN/DARTnet Collaboration [PDF](/reflib/brief/dartnet/dartnet.pdf)
* DCnet Research Network [PDF](/reflib/brief/dcnet/dcnet.pdf)

* * *

#### Importance of the Problem

![webp](/documentation/pic/cairn_marquee.webp)

Provision of good real-time, multicast services using a best-effort infrastructure like the Internet is generally considered difficult at best. The work now under way in the research community involves a suite of routing and reservation tools, together with enhancements to existing host and router software. However, this approach, which is based on a layered architecture and the existing Internet infrastructure, comes with considerable complexity, overhead and inefficient use of shared resources. The approach favored in this project, which is a collaborative effort with University College London (UCL) and Science Applications International Corporation (SAIC), involves the analysis, implementation and testing of unusual multicast infrastructure models specifically optimized for good performance and efficient resource sharing.

* * *

#### Brief Description of Work and Results

Our participation in this collaboration follows from previous work on other projects, specifically the [Network Time Synchronization Project](/reflib/ntp/), in which the multicast paradigm plays a pivotal role. Current work in this project is centered on technology which automatically launches, deploys and authenticates sources in a very large, survivable network. The technology involves inputs from the [Autonomous Configuration and Authentication in Very Large Networks](/reflib/autonet/) project. This technology uses intelligent multicast discovery algorithms, as well as span-limited add/drop heuristics which automatically reconfigure the hierarchical server/client subnet in response to failures and repairs. This technology is the outgrowth of previous work on DARTnet, an 18-site network operating at 1.544 Mbps.

![gif](/documentation/pic/dartnet.gif)

An important feature of Defense Advanced Research Technology Network (DARTnet) and its follow-on Collaborative Advanced Interagency Research Network (CAIRN) is the ability to bring up experimental applications that cannot be safely deployed in an operational network. This feature has been exploited many times in the development of the NTP infrastructure, especially the capability to configure the routers in various error scenarios and verify that the intricate discovery, configuration and optimization algorithms work as designed.

![gif](/documentation/pic/cairn.gif)

DARTnet has since evolved to CAIRN, which presently connects 27 institutions in the US and Britain. The network links operate at speeds from T1 (1.544 Mbps) to OC3 (155 Mbps), as shown in the figure. Our collaborators at University College London are connected to CAIRN via a dedicated transatlantic link and also to several European research networks. SAIC and UDEL are presently connected with T1 links, although these may be upgraded in future. In addition, UDEL is connected by the UDELnet campus net to Abilene and vBNS. The interconnected research networks, together covering major portions of the globe, are intended for network research projects involving high speed, real-time applications and supporting infrastructure.

The CAIRN backbone and research networks constitute a testbed for the development of experimental architectures, protocols and algorithms for real-time multimedia applications and related technology. Applications developed in this testbed include distributed audio and video conferencing systems, such as used in the MBONE, as well as real-time interactive simulation systems.

Our participation in the CAIRN program is now concentrated on the development of time synchronization technology and its incorporation in real-time applications. We have developed the protocols and engineered the current NTP synchronization subnet used in CAIRN and DARTnet and continue to monitor its behavior on a daily basis. The expanded CAIRN infrastructure is ideal for testing the discovery and configuration algorithms in multicast modes. In addition, we support ongoing experiments and evaluation of prototype software using modified kernels and special network instrumentation tools. These facilities are in regular use for faculty and students for audio/video conferences to interact with collaborators at many locations in the world.

* * *

#### Future Plans

Our prime focus in the new collaboration is the analysis and synthesis of multicast routing algorithms, specifically those based on shared, asymmetric trees and using quasi-optimal heuristics. We expect to continue participation in the CAIRN program specifically in the implementation and testing of these algorithms with our partners at UCL and SAIC. In addition, we expect to continue the development of time synchronization techniques specifically optimized for high speed networks. We also plan to participate in deployment exercises using IPv6 and new versions of experimental routing protocols and multimedia conferencing applications.