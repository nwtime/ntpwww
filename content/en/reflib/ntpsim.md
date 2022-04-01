---
title: "NTP Discrete Event Simulator"
type: archives
toc_hide: true
---

![gif](/documentation/pic/pogo6.gif)

from [_pogo_](/reflib/pictures/), Walt Kelly

Researchers involved: David Mills, graduate student Harish Nair

Funding: Defense Advanced Research Projects Agency (DARPA) and Jet Propulsion Laboratory/NASA

* * *

#### Table of Contents

*  [Briefing Slides](/reflib/ntpsim/#briefing-slides)
*  [Importance of the Problem](/reflib/ntpsim/#importance-of-the-problem)
*  [Brief Description of Work and Results](/reflib/ntpsim/#brief-description-of-work-and-results)
*  [Future Work](/reflib/ntpsim/#future-work)

* * *

#### Briefing Slides

*   NTP Architecture, Protocol And Algorithms [PDF](/reflib/brief/arch/arch.pdf)
*   NTP Clock Discipline algorithm [PDF](/reflib/brief/clock/clock.pdf)

* * *

#### Importance of the Problem

Evaluating NTP performance has always been a time consuming process, as the measurement periods can be long - in the order of days in some cases - and the data collected must be processed and converted to a useful form. Previously, special purpose simulators of one kind or another have been built for specific purposes. For example, a special purpose simulator was built to test the NTP mitigation and discipline algorithms and another to test the nanokernel discipline algorithms. These simulators were very useful to verify the transfer functions and explore the performance envelope. The most useful simulators have been those that used the actual code developed for the operational software, but encapsulated in a virtual environment. This reduces the potential for errors and allows exploration of a wide operational envelope including various error scenarios. This is the approach taken in the nanokernel simulator, which proved very valuable for these purposes.

None of the NTP simulators developed to date have used the actual code from the public software distribution, only glosses representing the actual code. We felt the need to develop a simulator that could exercise as much of the actual code as practical in a simulation environment. The primary motivation for this is the need to explore the response to various forms of network jitter and path asymmetries, oscillator wander and configuration parameters such as poll interval and various thresholds. A secondary motivation is the first step toward an enhanced simulator that can operate in a simulated space environment where NTP nodes are moving and accelerating.

A discrete event simulator (DES) is a computer program that can emulate the behavior of an interconnected network of real processes in response to designated inputs, or events. Many real world systems can be modeled as a DES where internal and external events occurring at specific times cause the system to change from one state to another, possibly generating outputs and events to occur at a future time. A DES includes a set of nodes and an event queue which holds a number of events, each of which is directed to a specific node and the time which it is to occur. The queue server processes each event in turn, which increments a virtual clock and executes the program resident in the particular node. This may result in a new event, which is placed on the queue at the point where it is to be executed, and possibly an output function.

Identifying the events involved in the system is the first step in designing a DES. Once the events are identified a data structure is defined to represent the event queue for the system, ordinarily a linked list of structures. Each structure includes a link to the routine that executes the event, a set of arguments specific to that event, a link to the next event in the queue and the time the event is to be executed. Events are inserted into the event queue in order of increasing event time. Upon execution, the event is removed from the queue. It is important to note that an event can schedule other events in future.

* * *

#### Brief Description of Work and Results

We have constructed a prototype DES for NTP. It includes all of the algorithms used to mitigate the time and discipline the local clock. These algorithms use the same NTP Version 4 software distribution, some with minor changes, to support synthetic network and clock hardware. The DES simulates one actual node in the NTP subnet as driven by another synthetic node with a given time and frequency offset. The offsets can be programmed by command arguments or generated using stochastic pseudo-random number generators with characteristics matching typical computer clock oscillators.

In its current form the DES simulates a single NTPv4 client operating with a single NTPv4 server. The NTPv4 software I/O functions are modified such that a NTP packet sent by the client is processed by the DES server and linked on the client receive queue. . AIn addition, the NTPv4 software timer functions that read, set and adjust the system time are modified to implement a synthetic system clock with nanosecond precision. Two pseudorandom noise generators produce exponentially distributed network delay samples and random-walk frequency wander samples. No changes have been made in the clock filter, selection and combining algorithms or in the clock discipline algorithm. The statistics recording functions remain, as well as the debug trace and logging functions. Further information can be found in the briefings listed at the top of this page and on the [`ntpdsim` - Network Time Protocol (NTP) simulator](/documentation/4.2.8-series/ntpdsim/) program documentation page.

We have used the simulator to test NTP performance over a wide range of operating conditions, some of which are possible but extremely rare in the real world. The purpose of these tests is to study the system behavior under conditions requiring very long convergence times and clock state machine transitions difficult to study in the real world. The tests have resulted in a number of incremental improvents in several algorithms, in particular the clock discipline algorithm. As virtual time runs some 16,000 times faster than real time, testing convergence regimes at very long poll intervals runs in seconds, rather than days.

* * *

#### Future Work

It would be interesting to explore the use of multiple NTP clients and servers in separate virtual environments on the same or different machines. This way the operation of an entire NTP subnet could be explored under conditions of stress, instability and threat. This also makes it practical to develop and test new discovery and synchronization paradigms without harnessing dedicated test network resources.