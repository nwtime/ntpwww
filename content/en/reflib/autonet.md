---
title: "Autonomous Networks"
type: archives
toc_hide: true
---

![gif](/archives/pic/rabbit.gif)

from [_Alice's Adventures in Wonderland_](/reflib/pictures/), Lewis Carroll

* * *

#### Table of Contents

*   [Importance of the Problem](/reflib/autonet/#importance-of-the-problem)
*   [Approach](/reflib/autonet/#approach)
*   [Further Information](/reflib/autonet/#further-information)

* * *

#### Importance of the Problem

The Network Time Protocol (NTP) is widely used in the Internet to synchronize computer clocks. It is supported by well over a hundred primary time servers located in many countries, together with a hierarchical, distributed subnetwork of well over 100,000 servers and clients scattered all over the globe. Management and configuration of this network has become almost unworkable. As the network is still growing rapidly, a means is required to automatically configure and authenticate the hierarchy in response to changing network topology and available server and network resources.

There are many points in common between NTP in the Internet and autonomous sensor networks that might be deployed on the battlefield or planetary surface. Both missions must operate in ad-hoc networking environments with diverse, redundant network paths where nodes and links can be damaged or compromised and connectivity restored without management intervention. Both missions must survive cryptographic attacks including replay, masquerade and flooding. Therefore, we use NTP and the NTP subnet as a convenient vehicle for protocol development, testing and evaluation.

* * *

#### Approach

There are two broad areas of effort on this project, each supporting the other, but funded as separate DARPA contracts. Each has its own project description, briefing slides and status reports. The [Autonomous Configuration](/reflib/autocfg/) effort explores how a broadly distributed service such as NTP can be deployed and maintained autonomously in a very large network without manual configuration engineering. The [Autonomous Authentication](/reflib/autokey/) effort explores how a autonomously configured NTP subnet can be cryptographically authenticated relative to certified public values. The technology developed can be reused for battlefield and planetary exploration missions and other protocols and services to be deployed in very large, ad hoc networks.

A vital component of our research program is the [Internetworking Research Laboratory](/reflib/lab/), [DCnet Research Network](/reflib/dcnet/) and [CAIRN/DARTnet Collaboration](/reflib/dartnet/). These provide connectivity between our collaborators as well as isolation from the Internet at large so we can conduct experiments in routing paradigms and traffic management without danger to the general Internet community.

As immediately evident in the project descriptions is the application of the developing technology to the [Network Time Synchronization Project](/reflib/ntp/). While not funded specifically by this and related contracts, the Network Time Protocol (NTP) has been a highly useful testbed for distributed, self-organizing and secure applications in the Internet and ad hoc sensor networks.

* * *

#### Further Information

*   [Autonomous Configuration](/reflib/autocfg/)
*   [Autonomous Authentication](/reflib/autokey/)
*   [Autokey Protocol](/reflib/proto/)
*   [Autokey Identity Schemes](/reflib/ident/)