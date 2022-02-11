---
title: "Autonomous Configuration"
type: archives
toc_hide: true
---

![gif](/archives/pic/rabbit.gif)

from [_Alice's Adventures in Wonderland_](/reflib/pictures/), Lewis Carroll

* * *

#### Table of Contents

*   [Importance of the Problem](/reflib/autocfg/#importance-of-the-problem)
*   [Brief Description of Work and Results](/reflib/autocfg/#brief-description-of-work-and-results)
*   [NTP Multicast/Manycast Support](/reflib/autocfg/#ntp-multicastmanycast-support)
*   [Present Status and Future Plans](/reflib/autocfg/#present-status-and-future-plans)
*   [Further Information](/reflib/autocfg/#further-information)
*   [Selected Publications](/reflib/autocfg/#selected-publications)

* * *

#### Importance of the Problem

The missions considered in this project involve autonomous sensors that might be deployed from a helicopter over a battlefield or from a space probe over a planetary surface. Once deployed, the sensor network must operate autonomously using an ad-hoc wireless infrastructure as sensors are deployed or destroyed or the network is damaged or compromised and then repaired. Appropriate algorithms and protocols must be developed to facilitate automatic, quasi-optimal configuration of sensor applications in response to network damage and repair and without requiring external management intervention.

* * *

#### Brief Description of Work and Results

Our approach involves IP multicasting and distributed, goal-oriented algorithms that survey the current service topology to discover, authenticate and configure a quasi-optimal forest of spanning trees rooted on the primary service providers. We have developed heuristic algorithms that attempt to minimize a distance metric corresponding to the most accurate time, subject to constraints designed to protect the server and network resources. These algorithms are designed to work in real time with minimal impact on other services that might share the sensor platform.

We have used the Network Time Protocol (NTP) software and the widely distributed NTP synchronization subnet in the Internet as a testbed for distributed protocol development and testing. The ad-hoc deployment, configuration and management of the NTP subnet have features in common with sensor applications, both because of a mostly casual management style, but also because the Internet is inherently unreliable with unpredictable failure and recovery scenarios.

A new paradigm called _Manycast_ has been developed for the automatic detection of NTP servers in the IP multicast near-neighborhood. It can use either symmetric key cryptography or the Autokey protocol described on the [Autonomous Authentication](/reflib/autokey/) page as an integral component in order to cryptographically verify server credentials. An executive summary of the paradigm and implementation is included below. The [Association Management](/archives/4.2.8-series/assoc/) and [Automatic Server Discovery Schemes](/archives/4.2.8-series/discover/) program documentation pages provide additional details.

* * *

#### NTP Multicast/Manycast Support

NTP broadcast mode does not extend beyond the local subnet. Where service is intended beyond the local subnet, IP multicasting can be used if supported by the network infrastructure. Various means have been developed using these methods to discover services and resolve addresses, for example. _manycasting_ is an automatic dynamic discovery and configuration paradigm. It is distinct from _anycasting_, where a single service provider is selected from a number that may respond to a multicast invitation. Manycasting is designed for highly robust services where multiply redundant respondents are continuously evaluated and quasi-optimal subsets mitigated using engineered algorithms. In general, NTP requires a plurality of servers in order for the mitigation algorithms, which are based on Byzantine agreement methods, to reliably cast out intruders and provide the best timekeeping performance.

The NTP Manycast scheme uses an expanding-ring search with pruning and variable poll rate in order to minimize network overhead. Servers and clients can use multiple group addresses with different scoping rules to segregate traffic. A client trolls the nearby network neighborhood looking for available manycast servers, authenticates them using either symmetric key or public key cryptography and then evaluates their time values with respect to other servers that might be already present or lurking in the vicinity. The intended result is that each manycast client mobilizes client associations with the "best" three nearest available manycast servers, yet automatically reconfigures to sustain this number should one or another degrade, fail or become compromised.

A manycast client begins sending multicast messages to the group address at a moderate rate and minimum time-to-live (TTL), depending on how many servers have already been found. A manycast server in scope and equal or lower stratum replies with its address, which causes the client to mobilize an ordinary unicast association, which then continues as if originally configured. If Autokey is enabled on the client, the NTP and Autokey protocols run concurrently until the server credentials are verified. When the protocols stabilize, the NTP mitigation algorithms discard all but the best three associations. If necessary, the client increases the TTL in steps until three acceptable associations are found, after which it polls at a lower sustaining rate to discover new servers that might come up.

* * *

#### Present Status and Future Plans

Manycast mode has been implemented and tested and is now in regular operation in our local networks and in the CAIRN research testbed. This support has been incorporated in the public NTP software distribution. The configuration files in all manycast servers and clients are identical and do not require per-host configuration. Initial experience in scenarios involving two dozen primary and secondary servers confirm that the manycast algorithms do in fact reconfigure properly in response to server failures and the NTP subnet reconfigures automatically while preserving good NTP performance.

In the current design, manycast servers respond to client messages at equal and higher strata and clients accept server messages at equal or lower strata. In order to reduce the implosion hazard in very large networks, the mitigation algorithms artificially increase the distance of servers with strata below a configured floor and above a configured ceiling. This scheme is only a preliminary cut at what should be a more sophisticated strategy. This problem was anticipated by Ajit Thyagarajan in his (unfinished) dissertation, but the schemes proposed therein are not practical in their present form. Future work is to evolve these schemes and how they could be implemented in the present framework.

It is likely that some sort of whisper campaign protocol will be necessary in order to balance the load among the available servers. Load leveling can be implemented using an extension field which carries, for example, a list of the current servers mobilized by the manycast client. A LRU list of recently heard servers is already available in the NTP reference implementation and used for access controls. Manycast servers can use the LRU list and combined extension field lists to compute a decision threshold for each server. Each server compares a random roll to its threshold to determine whether to respond to a client request. Details remain to be worked out.

* * *

#### Further Information

*   [Autonomous Authentication](/reflib/autokey/)
*   [Autokey Protocol](/reflib/proto/)
*   [Autokey Identity Schemes](/reflib/ident/)

* * *

#### Selected Publications

1.  Mills, D.L. Public key cryptography for the Network Time Protocol. Electrical Engineering Report 00-5-1, University of Delaware, May 2000\. 23 pp. Abstract: [PostScript](/reflib/reports/pkey/pkeya.ps) | [PDF](/reflib/reports/pkey/pkeya.pdf), Body: [PostScript](/reflib/reports/pkey/pkeyb.ps) | [PDF](/reflib/reports/pkey/pkeyb.pdf)
2.  Mills, D.L., and A. Thyagarajan. Network time protocol version 4 proposed changes. Electrical Engineering Department Report 94-10-2, University of Delaware, October 1994, 32 pp. Abstract: [PostScript](/reflib/reports/acts/actsa.ps) | [PDF](/reflib/reports/acts/actsa.pdf), Body: [PostScript](/reflib/reports/acts/actsb.ps) | [PDF](/reflib/reports/acts/actsb.pdf)