---
title: "Clock Cluster Algorithm"
type: archives
---

The clock cluster algorithm processes the truechimers produced by the clock select algorithm to produce a list of _survivors_. These survivors are used by the mitigation algorithms to discipline the system clock. The cluster algorithm operates in a series of rounds, where at each round the truechimer furthest from the offset centroid is pruned from the population. The rounds are continued until a specified termination condition is met. This page discusses the algorithm in detail.

First, the truechimer associations are saved on an unordered list with each candidate entry identified with index <code>_i_</code> (_i_ = 1, ..., _n)_, where <code>_n_</code> is the number of candidates. Let <code>θ(_i_)</code> be the offset and <code>λ(_i_)</code> be the root distance of the <code>_i_</code>th entry. Recall that the root distance is equal to the root dispersion plus half the root delay. For the <code>_i_</code>th candidate on the list, a statistic called the _select jitter_ relative to the <code>_i_</code>th candidate is calculated as follows. Let

<code>_d<sub>i</sub>_(_j_) = |θ(_j_) − θ(_i_)| λ(_i_),</code>

where <code>θ(_i)_</code> is the peer offset of the <code>_i_</code>th entry and <code>θ(_j_)</code> is the peer offset of the <code>_j_</code>th entry, both produced by the clock filter algorithm. The metric used by the cluster algorithm is the select jitter <code>φ<sub>S</sub>(_i_)</code> computed as the root mean square (RMS) of the <code>_d<sub>i</sub>_(_j_)</code> as <code>_j_</code> ranges from 1 to <code>_n_</code>. For the purpose of notation in the example to follow, let <code>φ<sub>R</sub>(_i_)</code> be the peer jitter computed by the clock filter algorithm for the <code>_i_</code>th candidate.

The object at each round is to prune the entry with the largest metric until the termination condition is met. Note that the select jitter must be recomputed at each round, but the peer jitter does not change. At each round the remaining entries on the list represent the survivors of that round. If the candidate to be pruned is preemptable and the number of candidates is greater than the _maxclock threshold_, the association is demobilized. This is useful in the schemes described on the [Automatic Server Discovery Schemes](/documentation/4.2.8-series/discover/) page. The maxclock threshold default is 10, but it can be changed using the <code>maxclock</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command. Further pruning is subject to the following termination conditions, but no associations will be automatically demobilized.

The termination condition has two parts. First, if the number of survivors is not greater than the _minclock threshold_ set by the <code>minclock</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command, the pruning process terminates. The <code>minclock</code> default is 3, but can be changed to fit special conditions, as described on the [Mitigation Rules and the prefer Keyword](/documentation/4.2.8-series/prefer/) page.

![gif](/documentation/pic/flt7.gif)

**Figure 1: Cluster Algorithm**

The second termination condition is more intricate. Figure 1 shows a round where a candidate of (a) is pruned to yield the candidates of (b). Let <code>φ<sub>_max_</sub></code> be the maximum select jitter and <code>φ<sub>_min_</sub></code> be the minimum peer jitter over all candidates on the list. In (a), candidate 1 has the highest select jitter, so <code>φ<sub>_max_</sub> = φ<sub>S</sub>(1)</code>. Candidate 4 has the lowest peer jitter, so <code>φ<sub>_min_</sub> = φ<sub>R</sub>(4)</code>. Since <code>φ<sub>_max_</sub> > φ<sub>_min_</sub></code>, select jitter dominates peer jitter,the algorithm prunes candidate 1. In (b), <code>φ<sub>_max_</sub> = φ<sub>S</sub>(3)</code> and <code>φ<sub>_min_ </sub>=φ<sub>R</sub>(4)</code>. Since <code>φ<sub>_max_</sub> < φ<sub>_min_</sub></code>, pruning additional candidates does not reduce select jitter, the algorithm terminates with candidates 2, 3 and 4 as survivors.

The survivor list is passed on to the mitigation algorithms, which combine the survivors, select a system peer, and compute the system statistics passed on to dependent clients. Note the use of root distance <code>λ</code> as a weight factor at each round in the clock cluster algorithm. This is to favor the survivors with the lowest root distance and thus the smallest maximum error.
