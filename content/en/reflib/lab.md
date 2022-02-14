---
title: "Internet Research Laboratory"
type: archives
toc_hide: true
---

![gif](/archives/pic/pogo1a.gif)[_The Okefenokee Swamp_, Walt Kelly](/reflib/pictures/)

![gif](/archives/pic/pogo.gif)[_Pogo Possum_](/reflib/pictures/), our mascot, was created by Walt Kelly, who invented a delicious menagerie of swamp creatures. All of the machines on our DCnet research network 128.4 are named after these creatures. The initials DC stand for District of Columbia, Distributed Computing, Drastically Corrupted or Direct Current, depending on the mood of the audience and voltage of the speaker.

* * *

#### Table of Contents

*  [Briefing Slides](/reflib/lab/#briefing-slides)
*  [General Description](/reflib/lab/#general-description)

* * *

#### Briefing Slides

*   CAIRN/DARTnet Collaboration [PDF](/reflib/brief/dartnet/dartnet.pdf)
*   DCnet Research Network [PDF](/reflib/brief/dcnet/dcnet.pdf)

* * *

#### General Description

![jpg](/archives/pic/evans2a.jpg)

The Internetworking Research Laboratory (IRL) is in 121 [Evans Hall](/reflib/gallery/gallery3/), geographic coordinates 39:40:48.425N, 75:45:02.392W. It includes workstations and laboratory equipment in a configuration specially designed for precision time and frequency measurements with a total of 9.6 GB of RAM and 1900 GB of disk resources. Three Unix file/time/web servers with UPS backup support over a dozen Unix workstations and PCs in 102 and 121 Evans. These machines and four routers are interconnected by a 10/100-Mb Ethernet. The laboratory is generously populated with laser printers, big monitors and high resolution scanners.

![jpg](/archives/pic/vic3.jpg)

The Unix workstations are used for general purpose program development and experiments. Technical staff members and students usually use one workstation for personal mail/web browsing and another for experimental operating system and network software development. The personal workstations are equipped with cameras and microphones to support videoconferencing and related multimedia applications. The view at left is out an office window with a computer-controlled camera.

![jpg](/archives/pic/radio2.jpg)

A computer-controlled shortwave radio provides entertainment, as well as a reliable source of audio for remote testing. The mixer is not computer-controlled yet. There are several other computer controlled devices to pique students interests.

An integral component of the laboratory is the [DCnet research network](/reflib/dcnet/), including the [Backroom test facility](/reflib/backroom/). DCnet has a rich history in the development of Internet technology and has been the witches brew from which many present day protocols have boiled over. It is probably best known as the home base for the Network Time Protocol (NTP) and a flock of time servers that wind their springs on this network. The various subnets are dedicated to network research functions that can be isolated when necessary for testing. DCnet is directly connected to the EECIS department network and the CAIRN research network.

![jpg](/archives/pic/stack1a.jpg)

The [stack on the left](/archives/pic/stack1b.jpg) shows our Master Time Facility (MTF). It includes dual-redundant primary and secondary GPS receivers, dual-redundant primary and secondary WWVB receivers, a primary cesium beam frequency standard and a secondary quartz frequency standard. Another stack including GPS and WWVB receivers and a cesium beam frequency standard is used at the Backroom. The WWVB receivers are twenty years old, but still function as well as new. The frequency standards are even older, but survive with loving care.

GPS receivers are the primary source of UTC time; WWVB receivers function as primary backup and WWV and CHU receivers as secondary backup. Cesium beam frequency standards provide precision pulse-per-second (PPS) signals, while LORAN receivers function as backup. This equipment as an ensemble can realize absolute accuracies relative to the antenna farm less than 50 nanoseconds, which is equivalent to a positional accuracy of about 15 meters. Using differential techniques, the accuracy can be improved to the picosecond range.

![jpg](/archives/pic/stack2a.jpg)

A distribution panel and multiplexor provide RS232, IRIG and PPS signals from the primary and secondary receivers to several NTP primary (stratum 1) servers for the laboratory, the ECE/CIS departments and the public at large. The multiplexor is used by public primary time server _rackety_ to receive these signals and to control auxiliary devices. We also have a pair of TrueTime GPS primary servers for the public at large.

![jpg](/archives/pic/ant_farm2.jpg)

There are several other NTP primary and secondary servers used for experiments and program development. By administrative decree all DCnet machines run only on UTC just like the aviation and maritime communities. The primary servers are synchronized by GPS, WWVB, WWV and CHU radio services and the ACTS telephone modem service. The [antenna farm](/archives/pic/ant_farm1.jpg) for these receivers atop an adjacent utility building is a local campus landmark.

![jpg](/archives/pic/loran1a.jpg)

![gif](/archives/pic/lorana.gif)

Following is an inventory of precision laboratory equipment used for time synchronization. We are indebted to the NIST, Naval Observatory, Coast Guard and several companies who generously provided most of this gear on indefinite loan or outright gift. The UDel LORAN-C Timing Receiver was built in our laboratory as a demonstration that a good timing source can be built with a handful of components and a junkbox PC.

*   Arbiter 1088A GPS Receiver
*   Austron 2200A GPS Timing Receiver
*   Austron 2201A GPS Timing Receiver with LORAN-C Assist and IRIG Generator
*   (2) Spectracom 8183 GPS Receiver
*   (2) PSI/Traconex 1020 WWV Receiver
*   (3) Spectracom 8170 WWVB Receiver
*   Spectracom Netclock/2 WWVB Receiver with IRIG Generator
*   TrueTime NTS-100 GPS Receiver/NTP Server
*   TrueTime NTS-200 GPS Receiver/NTP Server
*   EndRun Technologies Cntp CDMA Receiver/NTP Server
*   Austron 2000 LORAN-C Timing Receiver
*   UDel LORAN-C Timing Receiver
*   (3) Hewlett Packard 5061A Cesium Beam Frequency Standard
*   Datum 8048 Rubidium Frequency Standard
*   KSI/Odetics TPRO IRIG Interface