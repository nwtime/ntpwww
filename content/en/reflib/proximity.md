---
title: "Time Synchronization for Space Data Links"
description: "The Consultive Committee on Space Data Systems has defined the Proximity-1 Protocol for use by space data links between vehicles in the vicinity of Mars or the Moon. However, the means to provide time synchronization require processing by the NASA/JPL Deep Space Network consisting of very large and expensive Earth stations. This document proposes NTP interleaved symmetric mode, which provides time synchronization without requiring Earth resources."
type: archives
---

![gif](/documentation/pic/pogo5.gif)

from [_Pogo_](/reflib/pictures/), Walt Kelly

Turtle wins the race.

* * *

#### Table of Contents

*  [Abstract](/reflib/proximity/#abstract)
*  [Introduction](/reflib/proximity/#introduction)
*  [Proximity-1 Protocol](/reflib/proximity/#proximity1-protocol)
*  [Proximity-1 Time Service](/reflib/proximity/#proximity1-time-service)
*  [Proposed Proximity-1 Interleaved Time Service (PITS)](/reflib/proximity/#proposed-proximity1-interleaved-time-service-pits)
*  [PITS Protocol Operations](/reflib/proximity/#pits-protocol-operations)
*  [Parting Shots](/reflib/proximity/#parting-shots)
*  [Further Reading](/reflib/proximity/#further-reading)
*  [References](/reflib/proximity/#references)

* * *

#### Abstract

The Consultive Committee on Space Data Systems (CCSDS) has defined the Proximity-1 Protocol for use by space data links between vehicles in the vicinity of Mars and in the vicinity of the Moon. However, the means to provide time synchronization require processing by the NASA/JPL Deep Space Network (DSN) consisting of very large and expensive Earth stations. This document proposes the interleaved symmetric mode of the Network Time Protocol (NTP), which provides a mechanism for time synchronization without requiring Earth resources.

* * *

#### Introduction

While NTP has been deployed on the seabed, onboard ships and on every continent for the past three decades, it is probably not widely known that it has been deployed in space almost as long. NTP first flew on an AMSAT Earth satellite in the early 1980s and on another AMSAT satellite in 2000. It flew on at least two NASA Shuttle missions and in simulation experiments for future Earth-Moon missions.

The NASA/JPL space community has established three regimes of accuracy requirements, precision (1 ns to 1 μs), fine (1 μs to 1 ms) and coarse (1 ms to 1 s). In space all three regimes require some form of hardware assist, as the errors due to packet transmission times can be relatively large compared to the current Internet deployment on Earth.

Precision timekeeping in space must account for relativistic effects (red shift and time dilation), as well as satellite motion during measurements (Sagnac effect). In extreme cases timekeeping must account for the effects of the Earth geoid, troposphere and ionosphere, the solar wind and the influence of other objects in the solar system.

By far the most important consideration in space timekeeping is that distances and roundtrip times can become huge. A roundtrip to the Moon takes over 2 s, while a roundtrip to Mars takes up to 40 min and a roundtrip to the outer planets of the solar system takes several hours. In principle, NTP can work well in the fine and coarse regimes for the Earth-Moon system and for other planetary systems, but something quite different might be required for missions between planets. However, many of the fundamental algorithms intrinsic in the NTP architecture and protocol suite are well suited for planetary and deep space missions, but packaged in a different way.

The purpose of the time transfer function in space is to synchronize vehicles moving in a gravitational field to a common timescale. In general, this functin depends on the range and range rate between vehicles, either measured or predicted by orbital mechanics. Due to relativity effects, these clocks are not syntonic; that is, they do not have a common rate as assumed on Earth. The rates can differ from nanoseconds per day to milliseconds per day and have both secular and time-varying components.

* * *

#### Proximity-1 Protocol

The Consulting Committee on Space Data Systems (CCSDS) has defined several protocols for communications over space links. In general, these protocols are designed for use where distance, and thus delays, are very large. On the other hand, our interest here is where distances are relatively small, as with Mars orbiters and landers. The CCSDS has designated the Proximity-1 architecture and protocol <sup>[1](#myfootnote1)</sup> for the transmission of commands, telemetry and science data between spacecraft on and near Mars (or the Moon for that matter).

The Proximity-1 specification includes six sublayers: I/O, Data Services, Frame, Coding and Synchronization (C&S), Physical (PHY) and Medium Access (MAC). All but the C&S and PHY layers are implemented in the spacecraft computer (SC). The C&S is implemented in dedicated chips and FPGAs, while the PHY is the RF modem itself.

The MAC is the main point of interaction for the time transfer function. It has means to instruct the C&S sublayer to intercept a 24-bit ASM marker used to delimit C&S frames and capture a time tag from the spacecraft clock (SCLK, pronounced "esclock"). In this narrative the term _time tag_ refers to a value derived from the SCLK, while the term _timestamp_ refers to a value derived from a coordinate timescale in a common inertial frame, such as Ephemeris Time (ET, aka J2000). This is important since the buffering and coding functions can delay a time tag in the frame data payload many and varying seconds. The MAC can also send and receive supervisory frames to and from the remote MAC for the space link.

User data units (U frames) are sent and received over the space link along with supervisory data units (P frames). There are two kinds of U frames, sequenced and expedited. Sequenced frames are used for reliable data that may be retransmitted in case of error. Sequenced frames carry sequence numbers modulo 256. Expedited frames are used for datagrams that are not retransmitted. Expedited frames carry sequence numbers modulo 8. Sequence numbers are visible to the C&S layer at both ends of the space link. The SC includes separate queues for each of these and in addition a SPDU (P frame) queue, which has no sequence numbers. The priority of these queues (leaving out some special cases) is SPDU, UPDU expedited and UPDU sequenced.

A sequenced U frame of maximum size 2048 octets transmitted at the minimum channel rate of 1000 b/s takes 32 s in transmission, so a SPDU or expedited frame might have to wait that long. Thus, it is imperative that time tags be captured at the C&S layer. The C&S time tag and associated sequence number can be captured and retained for later retrieval. Note that the MAC does not have direct access to the data stream and can only inject or capture SPDU frames and enable or disable C&S time tag capture. In particular, the MAC cannot inspect or overwrite sequenced or expedited frames.

* * *

#### Proximity-1 Time Service

The specification includes a Transmit Parameters SPDU to enable the remote MAC to capture a specified number of transmit time tags and a Receive Parameters SPDU to capture a specified number of local receive time tags These are retained in buffers for later retrieval as telemetry data. In addition, there is a Time Distribution SPDU to convey time tags from one MAC to another and to broadcast the time in CCSDS format <sup>[2](#myfootnote2)</sup>.

SPDU frames carry no sequence numbers, so time tags associated with these frames are not useful in the present design. The specification expects that the time tags and associated sequence numbers are captured only for expedited frames. To capture for both sequenced and expedited frames would create an ambiguity, as the sequence numbers are from different spaces. The C&S wiretaps the frame type and sequence number from the 5-octet frame header.

This is the same approach used with the [IEEE 1588 Precision Time Protocol (PTP)](/reflib/ptp/). The network interface card (NIC) reaches far into the packet to inspect the frame type, packet type (UDP/IP) and port number to determine whether this is a PTP packet and if so, captures a timestamp for later retrieval. In some designs the timestamp in the packet itself is overwritten. This of course causes a messy UDP checksum error unless explicitly corrected or disabled.

What would seem to be a prudent procedure is for the MAC to enable the C&S to capture a number of transmit and receive time tags and send SPDUs to the other end of the link to enable the C&S to do the same thing. Then, each end sends a number of expedited frames to the other.

While not in the specification, captured time tags and sequence numbers are telemetered to Earth and correlated by sequence numbers to select the transmit and receive time tags for the same packet in one direction and then the other. The time tags are latched from the SCLK, which counts at a rate peculiar to each vehicle from liftoff. The time tag must be converted to a coordinated-time timestamps for comparison with other vehicles. This results in four timestamps from which the clock offset and roundtrip delay can be determined as in NTP.

* * *

#### Proposed Proximity-1 Interleaved Time Service (PITS)

The current method for time synchronization in the Mars space fleet requires the correlation function for each SCLK to be done on Earth. As the fleet grows, this can put onerous burden on the deep space network (DSN) and operating procedures. This requires means to accurately measure and exchange time values between the vehicles of the fleet. These means should be an intrinsic, distributed and ubiquitous service of the fleet.

The proposed Proximity-1 Interleaved Time Service (PITS) does this using the Proximity-1 data link protocol with certain minor modifications. PITS is applicable in NTP-like configurations involving multiple spacecraft and space links. In this design the Earth-disciplined vehicles operate as PITS primary servers and the others as PITS secondary servers and clients as in NTP. However, servers can come and go relatively frequently, depending on Earth telemetry schedule and orbit crosslink opportunities.

The protocol is similar to the NTP interleaved symmetric mode described in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/), but using only two packet fields instead of three to carry the timestamps. As a consequence, , the PITS protocol itself cannot detect all instances of lost packets or packets that violate the interleaved rules. These protections must be provided by additional means.

In order to avoid conflict with the existing Proximity-1 provisions, we define a new, variable-length Timestamp SPDU (type 3). The C&S sublayer already sniffs the data stream for an expedited frame and captures the time tag and sequence number on request. In this proposal, the C&S sublayer sniffs the data stream for a Timestamp SPDU and captures a time tag (only). On transmit the C&S recognizes the Timestamp SPDU, captures a time tag and saves it in a buffer. On receive the C&S recognizes this SPDU, captures a time tag and saves it in a buffer. No sequence numbers are necessary and capture does not need to be enabled - it is always enabled for the Timestamp SPDU.

Timestamp SPDUs are exchanged over the link several times each pass for redundancy and in order to discipline the rate offset, if needed. The Timestamp SPDU has two 8-octet fields, one for the last transmit timestamp, the other for the last receive timestamp, both converted to coordinate time. At each end of the link this results in four timestamps which can be used by the PITS protocol described in the next section to compute the relative offset and roundtrip delay as in NTP and the [IEEE 1588 Precision Time Protocol (PTP)](/reflib/ptp/).

* * *

#### PITS Protocol Operations

The PITS state machine is very similar to the NTP interleaved symmetric mode state machine as described in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/). Pseudo-code is contained in a companion S briefing document [NTP Interleaved Protocol for LANs and Space Data Links](/reflib/brief/onwire/onwire.ppt). While NTP supports an interleaved broadcast mode, this mode is not appropriate for the current Mars space fleet configuration, but could be considered in a future study.

The basic idea is that the PITS primary servers synchronize to Earth by some means and in the process determines the coordinate time <code>_t_<sub>0</sub></code> and the offset <code>_T_ = _t_<sub>0</sub> - _S_</code>, where <code>_S_</code> is the SCLK time at <code>_t_<sub>0</sub></code>. Each time the SCLK is read, <code>_T_</code> is added to its value <code>_S_</code> to determine the coordinate time <code>_t_</code>. If necessary, the SCLK rate can be disciplined as in NTP. Coordinate time values are used in Timestamp SPDU fields, so operation continues as in NTP.

Note that the Timestamp SPDU packet has room for only two timestamp fields, while NTP headers require three. The need for this limitation is to avoid fracturing the Proximity-1 existing packet data formats. In PITS the origin timestamp field is not used, as its only function is to detect bogus packets, which are highly unlikely in the space environment where transmissions are point-to-point and there is no possibility of retransmission of the same packet. Where bogus detecting is required, the timestamps can be integrated with an ordinary NTP protocol implementation.

Implicit in this discussion is the need to convert coordinate time as received over the space data link to proper time as used by each spacecraft. The details on how to do this and correct for orbit mechanics, relativistic time dilation and red shift effects are beyond the scope of this document, but can be found in Chapter 17 of <sup>[3](#myfootnote3)</sup>.

* * *

#### Parting Shots

The synchronization method described in the previous section assumes the vehicles are stationary. This of course is not the case for vehicles in orbit or on the surface of a rotating planet. In general, this simplification results in timekeeping errors in the order of a few milliseconds to tens of milliseconds.

A more accurate synchronization method requires dynamic measurement or prediction of space vehicle position and velocity, such as could be achieved using Keplerian elements. Using these six elements, it is possible to determine the orbital position and velocity state vector as a function of coordinate time. If these elements could be uploaded to the space vehicles in advance, accuracies in the order of tens of microseconds could be achieved. This would require using an iterated procedure, as described in Chapter 17 of <sup>[3](#myfootnote3)</sup>.

In practice, multiple measurements of range and range rate (Doppler) are required in order to determine the Keplerian elements. These measurements are usually made using specialized optical or radio signals. For a given coordinate time, Keplerian elements determine the spacecraft state vector, including its position and velocity relative to the inertial frame of the elements.

For synchronization flow from vehicle A to vehicle B, the position vector and coordinate time of A must be included in the message to B. At B, the coordinate time of arrival must be accurately determined along with the position and velocity of B. Assuming A and B are in the same inertial frame, such as the Earth and its satellites, the iterated procedure then refines these estimates as in <sup>[3](#myfootnote3)</sup>. This results in a coordinate time at B. The success of this method depends on the orbit geometry of B and can result in ambiguity or degeneracy that must be resolved by other means.

If A and B are not in the same inertial frame, as when A is on the Earth surface and B is a Mars satellite, A and B must be transformed to the same inertial frame. In this case, A is transformed from Earth geographic coordinates to Earth planetocentric coordinate, then to Solar System barycentric (J2000) coordinates, while B is transformed from Mars planetocentric coordinates to J2000 coordinates. Then, the light time from A to B can be determined in J2000 coordinates.

Questions remain on how to implement this method as a practical matter. Computing the state vectors and coordinate transforms, given the Keplerian elements and the coordinate time, is not a trivial matter, especially if the spacecraft computer has no provisions for floating point arithmetic. The computation must be done in such a way that the coordinate time computed from the time tag can be transmitted in a following mesage, as required by the interleaved mode. If a SPDU frame is used to carry the state vector, a new and possibly awkward frame format must be used. Further study on these issues could be a topic for future research.

* * *

#### Further Reading

[Basics of Space Flight](https://solarsystem.nasa.gov/basics/)

[Rocket and Space Technology: Orbital Mechanics](http://www.braeunig.us/space/orbmech.htm)

* * *

#### References

<a name="myfootnote1">1</a>  CCSDS 210.0-G-1 Proximity-1 Space Link Protocol--Rationale, Architecture, and Scenarios. Green Book. Issue 1. August 2007.

<a name="myfootnote2">2</a>  CCSDS 301.0-B-3 Time Code Formats. Blue Book. Issue 3. January 2002.

<a name="myfootnote3">3</a>  Mills, D.L. [Network Time Synchronization: the Network Time Protocol on Earth and in Space, Second Edition](/reflib/book/), CRC Press 2011.