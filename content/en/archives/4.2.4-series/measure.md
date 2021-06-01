---
title: "Time and Time Interval Measurement with Application to Computer and Network Performance Evaluation"
type: archives
--- 

Last update: Thursday, July 28, 2005

* * *

The technical memorandum: <cite>Time and Time Interval Measurement with Application to Computer and Network Performance Evaluation</cite> [(PostScript)](http://www.eecis.udel.edu/%7emills/database/memos/memo96a.ps) describes a number of techniques for conducting experiments typical of computer network and transmission systems engineering.

In most experiments in which time is involved, it is necessary to develop estimates of time, frequency and measurement errors from a series of time measurements between the clocks of a number of computers and ancillary devices interconnected by some kind of computer network. However, time is not a physical quantity, such as mass, nor can it be measured relative to an absolute frame of reference, such as velocity. The only way to measure time in our universe is to compare the reading of one clock, which runs according to its own timescale, with another clock, which runs according to a given timescale, at some given instant or epoch. The errors arise from the precision of time comparisons and the accuracy of frequency estimates between the timescales involved.

The usual data collected during a performance run of some experiment might include time offsets, time delays, frequency offsets and various error statistics. While time offsets between two clocks can be measured directly, frequency offsets can be estimated only from two or more time offsets made over some time interval in the experiment. In practice, a sequence of time comparisons can be performed over the lifetime of the experiment and the instantaneous frequency estimated either in real time with a recurrence relation, or retrospectively with a polynomial fit to the data.

Estimating time and frequency errors in real time has been studied by a distinct subspecies of physicists who have made a career of the technology involved. Various means including autoregressive models, Kalman filters and simple weighted-average algorithms are used extensively by national standards laboratories to model cesium-clock ensembles. These techniques have been adapted to computer network and transmission engineering problems as well. This memorandum explores issues in performing experiments of this type and summarizes various techniques found useful in practice.		

