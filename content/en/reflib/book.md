---
title: "Network Time Synchronization: the Network Time Protocol on Earth and in Space, Second Edition"
description: "This book, written by Prof. David L. Mills, speaks to the technological infrastructure of time dissemination, distribution and synchronization, specifically the architecture, protocols and algorithms of the Network Time Protocol (NTP). "
type: archives
---

![webp](/documentation/pic/10753_cover.webp)

Mills, David L. _Computer Network Time Synchronization: the Network Time Protocol on Earth and in Space, Second Edition_, CRC Press 2011, 466 pp.

ISBN 978-1-4398-1463-5


[//]: <> (DL: this page was empty July/2021 Please contribute to the [Errata](errata.html) page.)

[//]: <> (DL: this resource was unavailable July/2021: [Romanian Translation](http://www.azoft.com/people/seremina/edu/network-time-synchronization.html))

#### Author

David L. Mills, PhD
: Electrical and Computer Engineering Department and Computer and Information Systems Department
: University of Delaware, Newark, DE 19716

Dr. David L. Mills is Professo Emeritus of Electrical and Computer Engineering and Computer and Information Sciences at the University of Delaware. He has been an active contributor for many years in Internet technology and in particular computer network time synchronization. He is the original developer of the Network Time Protocol and has authored over 30 papers and technical reports on the subject, including the current operative standards documents. His PhD degree in Computer Science was conferred by the University of Michigan in 1971. He is a member of the National Academy of Engineering and a Fellow in both the Association for Computing Machinery and the Institute of Electrical and Electronic Engineering

This work was partially funded by the Jet Propulsion Laboratory, California Institute of Technology, under a contract with the National Aeronautics and Space Administration.

#### Preface

_Mumpsimus_ (n): Middle English noun denoting an incorrigible dogmatic old pendant - jokingly called a foolosopher about 1550 - which grew to include any incorrect opinion stubbornly clung to.  
Jeffrey Kacirk _Forgotten English_, 1997

This book is all about wrangling a herd of network computers so that all display the correct time. This may seem like a really narrow business, but the issues go far beyond winding the clock on your display taskbar. Carefully coordinated, reliable and accurate time is vital for traffic control in the air and on the ground, buying and selling things and TV network programming. Even worse, ill-gotten time might cause DNS caches to expire and the entire Internet to implode on the root servers, which was considered a serious threat on the eve of the Millennium in 1999. Critical data files might expire before they are created, and an electronic message might arrive before it was sent. Reliable and accurate computer time is necessary for any real-time distributed computer application, which is what much of our public infrastructure has become.

This book speaks to the technological infrastructure of time dissemination, distribution and synchronization, specifically the architecture, protocols and algorithms of the Network Time Protocol (NTP). NTP has been active in one form or another for over almost three decades on the public Internet and numerous private networks on the nether side of firewalls. Just about everything today that can be connected to a network wire has support for NTP - print servers, wi-fi access points, routers and printers of every stripe and even battery backup systems. NTP subnets are in space, on the seabed, onboard warships and on every continent, including Antarctica. NTP comes with most flavors of Windows as well as all flavors of Unix. About 25 million clients implode on the NTP time servers at NIST alone.

This book is designed primarily as a reference book, but is suitable for a specialized university course at the senior and graduate level in both computer engineering and computer science departments. Some chapters may go down more easily for an electrical engineer, especially those dealing with mathematical concepts; others more easily for a computer scientist, especially those dealing with computing theory, but each will learn from the other. There are things for mathematicians, cryptographers and spacefarers, even something for historians.

Welcome to the second edition of this book. The original 16 chapters of the first edition remain, but some have been rewritten, updated and new material added. Four new chapters have been added, two of which discuss timekeeping in space missions. The presentation begins in Chapter 1 with a general overview of the architecture, protocols and algorithms for computer network timekeeping. This includes how time flows from national time standards via radio, satellite and telephone modem to hundreds of primary time servers, then via NTP subnets to millions of secondary servers and clients at increasing stratum levels. Chapter 2 describes the principal components of an NTP client and how it works with redundant servers and diverse network paths. Chapter 3 contains an in-depth description of the critical algorithms so important for consistency, accuracy and reliability which any good computer scientist will relish.

The actual algorithm used to adjust the computer clock is so special that Chapter 4 is completely dedicated to its description and operation. As the word network is prominent in the title of this book, Chapter 5 presents an overview of the engineering principles guiding network configuration and resource discovery.

Along about now, you should ask how well the contraption works. Chapter 6 evaluates the performance of typical NTP subnets with respect to network delay variations and clock frequency errors. It shows the results of a survey of NTP servers and clients to determine typical time and frequency error distributions. It then analyzes typical NTP configurations to determine such things as processor and network overhead and engineered defenses against flood attacks.

An NTP subnet ultimately depends on national and international means to disseminate standard time to the general population, including Internet computers. Chapter 7 describes a number of systems and drivers for current radio, satellites and telephone modem dissemination means. Chapter 8 describes specialized kernel software used in some computer systems to improve timekeeping accuracy and precision ultimately to the order of nanoseconds.

In modern experience we have learned that computer security is a very serious business, and timekeeping networks are not exempt. What may be different for NTP subnets is that by their very nature, the data exchanged are public values transmitted from public servers over public networks, so servers and clients of public networks might be seen as very inviting targets for tempo-terrorists. In addition, there are devilishly intricate issues when dated material such as cryptographic certificates must be verified by the protocol that uses them. Chapter 9 describes the NTP security model and authentication protocol, which shares headers with NTP, while Chapter 10 describes a number of cryptographic algorithms designed to prove industrial-strength group membership.

Computer network timekeeping, like many other physical systems is not without errors, both deterministic and stochastic. Chapter 11 contains an intricate analysis of errors inherent in reading the system clock and disciplining its time and frequency relative to the clock in another computer. Chapter 12 is on modelling and analysis of the computer clock, together with a mathematical description of its characteristics. Timekeeping on the global scale is a discipline all its own. Chapter 13 describes how we reckon the time according to the stars and atoms. It explains the relationships between the international timescales TAI, UTC and JDN dear to physicists and navigators and the NTP timescale. If we use NTP for historic and future dating, there are issues of rollover and precision. Even the calendar gets in the act, as the astronomers have their ways and the historians theirs. Since the topic of history comes up, Chapter 19 reveals the events of historic interest since computer network timekeeping started almost three decades ago. Finally, Chapter 20 is a bibliography of papers, reports and other documents relevant to computer network timekeeping.

While a detailed description of the NTP reference implementation is beyond the scope of this book, it may be of some interest to explore its general architecture, organization and operation. Chapter 14 includes a set of flow charts, state variables, processes and routines of the current public software implementation, together with an explanation of how it operates.

The next four chapters 15 through 18 are new to this edition. Chapter 15 includes an intricate cocktail of hardware and software algorithms to implement a truly awesome and precise system clock. It introduces the notions of softstamp, drivestamp and hardstamp and includes an overview of the IEEE 1588 Precision Time Protocol (PTP) and how it might interoperate with NTP. Chapter 16 describes the interleave modes new to NTP and how these new concepts can be exploited.

The next two chapters 17 and 18 have motivated the subtitle of this book, "on Earth and in Space".

Chapter 17 explains why timekeeping is so different from Earthlings to Martians, as now we must consider light-time and relativistic effects. This chapter also discusses space hardware issues and the Proximity-1 space data link protocol. that might boost NTP to a Mars orbiter fleet. Finally, Chapter 18 discusses time transfer issues for deep space missions at and beyond Mars.

The book in its entirety would certainly be of interest to an NTP administrator as a reference volume. It is would be useful as a case study involving a widely deployed, distributed application with technology drawn from diverse interdisciplinary fields. The algorithms described in various chapters could be useful as a companion to a computer science book on algorithms. As a case study in cryptographic techniques, the material in Chapters 9 and 10 is particularly relevant, as the security model for NTP is complicated by the need to authenticate the server and reckon the time simultaneously. Astronomers and physicists will find the clock discipline algorithm described in Chapter 4 similar to but different from the algorithms they are used to. Engineers will find Chapters 4, 11 and 12 relevant to a course on control feedback systems. Planetary scientists and space navigators might find the material in Chapters 17 and 18 useful in the design of new spacecraft hardware and instruments.

The development, deployment and maintenance of NTP in the Internet has been a daunting task made possible by over four dozen volunteers from several professions and from several countries. NTP enthusiasts have much in common with radio amateurs (including me, W3HCF), even if the boss sees little need to wind the clock to the nanosecond. We have been fortunate that several manufacturers have donated radio and satellite receivers, computers and cool gadgets over the years. Especially valued is the mutual support of Judah Levine at NIST and Richard Schmidt at USNO, intrepid timekeepers in their own right. Many thanks to Interneteers Danny Mayer and Dave Hart of the NTP Public Services Project, who reviewed the entire book, and to Simon Wu and John Veregge of NASA Jet Propulsion Laboratory, who reviewed the new chapters. Finally, a word about the Parting Shots sections sprinkled at the end of most chapters. While the main text explores the timescape up to the cutting edge of the cliff, these sections rappel over the edge. Some are speculative, others offer proposals and still others present an alternate view. All in all, they have been great fun.

David L. Mills
: September 2009

#### Abbreviated Table of Contents

1. Basic Concepts
2. How NTP Works
3. In the Belly of the Beast
4. Clock Discipline Algorithm
5. NTP System Engineering and Configuration
6. NTP Performance in the Internet
7. Primary Servers and Reference Clocks
8. Kernel Timekeeping Support
9. Cryptographic Authentication
10. Identity Schemes
11. Analysis of Errors
12. Modeling and Analysis of Computer Clocks
13. Metrology and Chronometry of the NTP Timescale
14. NTP Reference Implementation
15. 15.3Precision System Clock Architecture
16. NTP Interleaved Modes
17. Time Transfer for Space Data Links
18. Time Transfer for Deep Space Missions
19. Technical History of NTP
20. Bibliography on Computer Network Time Synchronization