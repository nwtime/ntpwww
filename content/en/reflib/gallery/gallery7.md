---
title: "Data Concentrator Project"
type: archives
toc_hide: true
---

I was chief nerd for several projects in the fifteen years I was with U Michigan, first in electrical engineering and then in computer science. This is one of them.

In the late 60s IBM was the crushing giant, while Digital Equipment Corporation (DEC) was yet a pipsqueak. The U Michigan Computing Center had a giant - a two-processor System 360 Model 67 processor with a dazzling one megabyte of core memory. This machine could support only dumb user terminals made by IBM and Teletype Corporation. I managed to get my hands on a pipsqueak - a DEC PDP8 - to serve as the nucleus for a controller to support other fancier user terminals and remote data communications. I was chief designer for a team that built the thing, which we called the Data Concentrator <sup>[5](#myfootnote5)</sup>. It was hardly a paragon of miniaturization, as evident in the photo below. It consisted of four six-foot racks populated with DEC Flip-Chip modules. We were lucky to get three NAND gates or two flipflops on one 5.25" plug-in card.

![webp](/documentation/pic/dataconce.webp)

On the far left is a Teletype Model 35 with paper tape reader/punch. It made a sturdy operator console, but topped out at 10 char/sec. The leftmost rack contains the PDP8, 8192 words of 12-bit core memory and power supplies. The machine had eight instructions and no multiply/divide hardware. We used to say it was the smallest machine just larger than a Turing machine that was potentially useful. The next rack to the right contains an awesomely fast and noisy paper tape punch at the top. Just below that are control panels for the two IBM multiplexor channel interfaces. More about that later. Below that is a high speed (1000 byte/sec) paper tape reader.

Paper tape was then the modern way to load programs and data. We had to find some way to signal the machine operators, who were normally at the other end of the rather large machine room, to replenish the paper tape. We had two programmable noisemakers, a obnoxiously loud siren and a Ford Model-T ooga horn. We got to use the piercing siren only once.

The next rack to the right contains the two IBM multiplexor channel interfaces and multiplexor gear for 24 asynchronous serial interfaces for dial-in modems used by various terminals on campus. Its equivalent today is a handful of IC chips. The next and last rack on the right contains the multiplexor gear for four synchronous serial interfaces for dial-in modems used by other machines on campus.

The teddy bear perched above the rack has a little story of its own. DEC at that time was emphasizing how cute their products were (relative to IBM mainframes) in an ad campaign featuring a toy stuffed bear. So, we placed an order for one Ursus Theodorus, part number and price to be determined. The local DEC office thought this was pretty funny, so they forwarded a formal purchase order for one stuffed bear as per advertised to Maynard. Well, the rest is history and the bear in the photo has a DEC part number and identification tag.

Some idea of the scale of integration is evident in the photo below. Here DEC technicians are working on the PDP8 CPU. The black box near the top contains the core memory. The green cards contain the core memory select and sense amplifiers. The red ones implement a handful of 12-bit data registers, an arithmetic/logic unit and the input/output bus interface. Much later, the entire PDP8 was implemented on a single IC chip.

The PDP8 instruction set had only seven instructions, a single accumulator and no index registers. Nevertheless, the homegrown operating system called RAMP [7] ran the show with a few cycles left over. Later, RAMP was used in real-time systems for audio switching <sup>[4](#myfootnote4)</sup> and automotive test cell control.

![webp](/documentation/pic/dataconcb.webp)

Just about the only terminal type the Data Concentrator didn't deal with was the IBM 1050 Data Terminal shown below circa 1970. This one had a keyboard, printer and punched card reader. It used the six-bit Binary Coded Decimal (BCD) code at 134.5 bps. A bunch of these shared the same telephone line with each one selected by a special prefix code. It had no internal memory, so the operator had to retype a line of data if the checksum failed. The last one I saw was buried in the Negev Desert in 1971.

![webp](/documentation/pic/1052.webp)

As it happened, the IBM multiplexor channel interface was the first such interface not designed by IBM, so it caused a fair amount of interest <sup>[6](#myfootnote6)</sup>. There were actually two of them, one for each Model 67 processor. It was carefully designed to emulate either of two IBM communications controllers used to connect remote terminals and remote jobstations, but could also emulate the operator console. It could and sometimes did switch in when the operator console broke. The control panels for the two interfaces are shown in the photo below.

![webp](/documentation/pic/dataconcc.webp)

The Data Concentrator shown here operated for some years through the early and middle '70s. It was eventually replaced by a more modern PDP11 and microprogrammed interfaces. One of the technicians bought the PDP8 and so far as I know has it still running in his basement. I expect the only extant copies of the 30-year old reports are in my office, but the lessons learned were later bottled in journal and symposium papers <sup>[1, 2, 3](#myfootnote1)</sup>.

#### References

<a name="myfootnote1">1</a>  Mills, D.L. Communications software. _Proc. IEEE 60, 11_ (November 1972), 1333-1341. Also in: Green, P.E., and R.W. Lucky, (Eds.). _Computer Communications_. IEEE Press, New York, New York, 1975. Also in: Abrams, M., R.P. Blanc, and I.W. Cotton, (Eds.). _Computer Networks: a Tutorial_ (Revised 1975). IEEE Press, New York, New York, 1975.

<a name="myfootnote2">2</a>  Mills, D.L. Preprocessors in a data communication computer environment. _Proc. ACM Symposium on the Optimization of Data Communications Systems_ (Pine Mountain, Georgia, October 1969), 112-109.

<a name="myfootnote3">3</a>  Mills, D.L. Multiprogramming in a small-systems environment. _Proc. ACM Second Symposium on Operating Systems Principles_ (Princeton, New Jersey, October 1969), 286-310.

<a name="myfootnote4">4</a>  Mills, D.L. A random-access multiple-program system for the University of Michigan Language Laboratory. _Foreign Language Courier_, University of Michigan Press, June 1969.

<a name="myfootnote5">5</a>  Mills, D.L. The Data Concentrator. CONCOMP Project Technical Report 8, University of Michigan, May 1968.

<a name="myfootnote6">6</a>  Mills, D.L. System/360 interface engineering report. CONCOMP Project Memorandum 13, University of Michigan, March 1968.

<a name="myfootnote7">7</a>  Mills, D.L. RAMP: a multiprogramming system for real-time device control. CONCOMP Project Memorandum 5, University of Michigan, May 1967.


					