---
title: "The Fuzzball"
description: "The Fuzzball is an operating system and package of applications for the DEC PDP11. The package was conceived in 1971 as a replacement for the RAMP operating system for the DEC PDP8. It later evolved as a virtual machine supporting the DEC RT-11 operating system and early developmental versions of TCP/IP. Prototype versions of Telnet, FTP, DNS, EGP, and SMTP were first implemented and tested on the Fuzzball."
images: ["/documentation/pic/lsi11.webp"]
type: archives
---

![webp](/documentation/pic/lsi11.webp)

![webp](/documentation/pic/periph.webp)

![webp](/documentation/pic/fuzzball.webp)

The last known Fuzzball (1990)

#### The Fuzzball

The Fuzzball is an operating system and a package of applications for the Digital Equipment Corporation (DEC) PDP11 family of computers, including the LSI-11 board-level components. The package was conceived in 1971 as a replacement for the RAMP operating system for the DEC PDP8 <sup>[3](#myfootnote3)</sup>. It later was evolved as a virtual machine supporting the DEC RT-11 operating system and early developmental versions of the TCP/IP protocol and applications suite. Prototype versions of popular Internet tools, including Telnet, FTP, DNS, EGP and SMTP were first implemented and tested on the Fuzzball. _Fuzzball_ is now in the [Computing Dictionary](https://encyclopedia2.thefreedictionary.com/fuzzball) and remembered in the [NSF history archives (PDF)](https://www.nsf.gov/about/history/nsf0050/pdf/internet.pdf).

Fuzzballs were deployed extensively in the DARPA SATNET program during the 1970s. Fuzzball nests were deployed at the INTELSAT earth stations in the US, UK, Germany, Norway and Italy. Perhaps the best known role of the Fuzzball was as routers for the NSFNET Phase-I Backbone Network <sup>[2](#myfootnote2)</sup>, which was deployed during the 1986-1988 time period. There were five routers co-located at the five NSF supercomputer centers and connected by 56-kbps data circuits. The Fuzzballs carried traffic between the centers, the center users and the adjacent college campuses. To say the network was gloriously overloaded is an understatement, but the system did present an opportunity to study methods to defend against massive overload.

The Fuzzball archive consists of some 16 MB of source code and binaries written for the PDP11 Macro Assembler. The last update to the archive was in 1992, but it [survives to the present](/reflib/software/fuzzball.tar.gz) for curious seekers.

The Fuzzball itself is described in <sup>[1](#myfootnote1)</sup> while the lessons learned with NSFNET are discussed in <sup>[2](#myfootnote2)</sup>. Perhaps the most important lesson learned was that the best way to defend against supercomputer elephants in the company of mice is to find the biggest elephant in the forest, shoot it and do this recursively until the forest is safe for mice.

#### References

<a name="myfootnote1">1</a>  Mills, D.L. The Fuzzball. _Proc. ACM SIGCOMM 88 Symposium_ (Palo Alto CA, August 1988), 115-122. [PostScript](/reflib/papers/fuzz.ps) | [PDF](/reflib/papers/fuzz.pdf)

<a name="myfootnote2">2</a>  Mills, D.L., and H.-W. Braun. The NSFNET Backbone Network. _Proc. ACM SIGCOMM 87 Symposium_ (Stoweflake VT, August 1987), 191-196. [PDF](/reflib/papers/bone.pdf)

<a name="myfootnote3">3</a>  Mills, D.L. Multiprogramming in a small-systems environment. _Proc. ACM Second Symposium on Operating Systems Principles_ (Princeton, New Jersey, October 1969), 286-310.
