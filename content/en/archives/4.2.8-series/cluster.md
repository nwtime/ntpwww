---
title: "Clock Cluster Algorithm"
type: archives
---

Last update: 15-Nov-2012 06:02 UTC

* * *

The clock cluster algorithm processes the truechimers produced by the clock select algorithm to produce a list of _survivors_. These survivors are used by the mitigation algorithms to discipline the system clock. The cluster algorithm operates in a series of rounds, where at each round the truechimer furthest from the offset centroid is pruned from the population. The rounds are continued until a specified termination condition is met. This page discusses the algorithm in detail.

First, the truechimer associations are saved on an unordered list with each candidate entry identified with index _i_ (_i_ = 1, ..., _n)_, where _n_ is the number of candidates. Let θ(_i_), be the offset and λ(_i_) be the root distance of the _i_th entry. Recall that the root distance is equal to the root dispersion plus half the root delay. For the _i_th candidate on the list, a statistic called the _select jitter_ relative to the _i_th candidate is calculated as follows. Let

<div align="center">

_d<sub>i</sub>_(_j_) = |θ(_j_) − θ(_i_)| λ(_i_),

</div>

where θ(_i)_ is the peer offset of the _i_th entry and θ(_j_) is the peer offset of the _j_th entry, both produced by the clock filter algorithm. The metric used by the cluster algorithm is the select jitter φ<sub>S</sub>(_i_) computed as the root mean square (RMS) of the _d<sub>i</sub>_(_j_) as _j_ ranges from 1 to _n_. For the purpose of notation in the example to follow, let φ<sub>R</sub>(_i_) be the peer jitter computed by the clock filter algorithm for the _i_th candidate.

The object at each round is to prune the entry with the largest metric until the termination condition is met. Note that the select jitter must be recomputed at each round, but the peer jitter does not change. At each round the remaining entries on the list represent the survivors of that round. If the candidate to be pruned is preemptable and the number of candidates is greater than the _maxclock threshold_, the association is demobilized. This is useful in the schemes described on the [Automatic Server Discovery Schemes](/archives/4.2.8-series/discover) page. The maxclock threshold default is 10, but it can be changed using the <tt>maxclock</tt> option of the [<tt>tos</tt>](/archives/4.2.8-series/miscopt) command. Further pruning is subject to the following termination conditions, but no associations will be automatically demobilized.

The termination condition has two parts. First, if the number of survivors is not greater than the_minclock threshold_ set by the <tt>minclock</tt> option of the [<tt>tos</tt>](/archives/4.2.8-series/miscopt) command, the pruning process terminates. The <tt>minclock</tt> default is 3, but can be changed to fit special conditions, as described on the [Mitigation Rules and the prefer Keyword](/archives/4.2.8-series/prefer) page.

![gif](/archives/pic/flt7.gif)

**Figure 1: Cluster Algorithm**

The second termination condition is more intricate. Figure 1 shows a round where a candidate of (a) is pruned to yield the candidates of (b). Let φ<sub>_max_</sub> be the maximum select jitter and φ<sub>_min_</sub> be the minimum peer jitter over all candidates on the list. In (a), candidate 1 has the highest select jitter, so φ<sub>_max_</sub> = φ<sub>S</sub>(1). Candidate 4 has the lowest peer jitter, so φ<sub>_min_</sub> = φ<sub>R</sub>(4). Since φ<sub>_max_</sub> > φ<sub>_min_</sub>, select jitter dominates peer jitter,the algorithm prunes candidate 1. In (b), φ<sub>_max_</sub> = φ<sub>S</sub>(3) and φ<sub>_min_ </sub>=φ<sub>R</sub>(4). Since φ<sub>_max_</sub> < φ<sub>_min_</sub>, pruning additional candidates does not reduce select jitter, the algorithm terminates with candidates 2, 3 and 4 as survivors.

The survivor list is passed on to the the mitigation algorithms, which combine the survivors, select a system peer, and compute the system statistics passed on to dependent clients. Note the use of root distance λ as a weight factor at each round in the clock cluster algorithm. This is to favor the survivors with the lowest root distance and thus the smallest maximum error.
