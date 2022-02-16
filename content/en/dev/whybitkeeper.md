---
title: "Why BitKeeper?"
type: archives
---

For many years, the NTP source code was kept in a frequently-backed-up directory on a machine. The only "snapshots" we had of previous releases were whatever tarballs we kept of previous releases. In early '99, Harlan and Dave came to an agreement about how a code repository would have to behave and Harlan was finally able to import the codebase into CVS (knowing full well what the limitations of CVS were).

In less than a year, the pains of using CVS were becoming unbearable, and the search began for a replacement. Over a period of 2 years' time, all open source Source Code Management (SCM) Systems were explored and tested and several commercial solutions were examined (to various degrees) as well. Fairly quickly, it became obvious that [BitKeeper](https://www.bitkeeper.org/) was, hands-down and very clearly, the best SCM available for NTP. Its features included:

* distributed (and disconnected) operation
* integration areas
* useful triggers/hooks
* great merge capability
* the ability to have multiple active repositories (eg, one repo per bugfix)
* good performance
* rock-solid stability
* great support
* quick, simple and easy to use
* behaves well and, generally, "as expected" 

Originally, the complete `bk` software/executable was available to anybody who wanted to use it to work on opensource projects. A series of events happened that resulted in increased restrictions on the ability of many open source projects to continue to use BitKeeper. Harlan remains Very Pleased that NTP managed to stay clear of that situation, and believes the NTP Project has benefited greatly from its use of BitKeeper. 