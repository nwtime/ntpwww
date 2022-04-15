---
title: "Clock State Machine"
type: archives
---

#### Table of Contents

*   [General Overview](/documentation/4.2.8-series/clock/#general-overview)
*   [Panic Threshold](/documentation/4.2.8-series/clock/#panic-threshold)
*   [Step and Stepout Thresholds](/documentation/4.2.8-series/clock/#step-and-stepout-thresholds)
*   [Hold Timer](/documentation/4.2.8-series/clock/#hold-timer)
*   [Operating Intervals](/documentation/4.2.8-series/clock/#operating-intervals)
*   [State Transition Function](/documentation/4.2.8-series/clock/#state-transition-function)

* * *

#### General Overview

In the NTPv4 specification and reference implementation a state machine is used to manage the system clock under exceptional conditions, as when the daemon is first started or when encountering severe network congestion. This page describes the design and operation of the state machine in detail.

The state machine is activated upon receipt of an update by the clock discipline algorithm. Its primary purpose is to determine whether the clock is slewed or stepped and how the initial time and frequency are determined using three thresholds: _panic_, _step_ and _stepout_, and one timer: _hold_.

* * *

#### Panic Threshold

Most computers today incorporate a time-of-year (TOY) chip to maintain the time when the power is off. When the computer is restarted, the chip is used to initialize the operating system time. In case there is no TOY chip or the TOY time is different from NTP time by more than the panic threshold, the daemon assumes something must be terribly wrong, so exits with a message to the system operator to set the time manually. With the <code>-g</code> option on the command line, the daemon sets the clock to NTP time at the first update, but exits if the offset exceeds the panic threshold at subsequent updates. The panic threshold default is 1000 s, but it can be changed with the <code>panic</code> option of the [<code>tinker</code>](/documentation/4.2.8-series/miscopt/) command.

* * *

#### Step and Stepout Thresholds

Under ordinary conditions, the clock discipline gradually slews the clock to the correct time, so that the time is effectively continuous and never stepped forward or backward. If, due to extreme network congestion, an offset spike exceeds the step threshold, by default 128 ms, the spike is discarded. However, if offset spikes greater than the step threshold persist for an interval more than the stepout threshold, by default 300 s, the system clock is stepped to the correct time.

In practice, the need for a step has been extremely rare and almost always the result of a hardware failure or operator error. The step threshold and stepout threshold can be changed using the <code>step</code> and <code>stepout</code> options of the [<code>tinker</code>](/documentation/4.2.8-series/miscopt/) command, respectively. If the step threshold is set to zero, the step function is entirely disabled and the clock is always slewed. The daemon sets the step threshold to 600 s using the <code>-x</code> option on the command line. If the <code>-g</code> option is used or the step threshold is set greater than 0.5 s, the precision time kernel support is disabled.

Historically, the most important application of the step function was when a leap second was inserted in the Coordinated Universal Time (UTC) timescale and the kernel precision time support was not available. This also happened with older reference clocks that indicated an impending leap second, but the radio itself did not respond until it resynchronized some minutes later. Further details are on the [Leap Second Processing](/documentation/4.2.8-series/leap/) page.

In some applications the clock can never be set backward, even it accidentally set forward a week by some evil means. The issues should be carefully considered before using these options. The slew rate is fixed at 500 parts-per-million (PPM) by the Unix kernel. As a result, the clock can take 33 minutes to amortize each second the clock is outside the acceptable range. During this interval the clock will not be consistent with any other network clock and the system cannot be used for distributed applications that require correctly synchronized network time.

* * *

#### Hold Timer

When the daemon is started after a considerable downtime, it could be the TOY chip clock has drifted significantly from NTP time. This can cause a transient at system startup. In the past, this has produced a phase transient and resulted in a frequency surge that could take some time, even hours, to subside. When the highest accuracy is required, some means is necessary to manage the startup process so that the clock is quickly set correctly and the frequency is undisturbed. The hold timer is used to suppress frequency adjustments during the training and startup intervals described below. At the beginning of the interval the hold timer is set to the stepout threshold and decrements at one second intervals until reaching zero. However, the hold timer is forced to zero if the residual clock offset is less than 0.5 ms. When nonzero, the discipline algorithm uses a small time constant (equivalent to a poll exponent of 2), but does not adjust the frequency. Assuming that the frequency has been set to within 1 PPM, either from the frequency file or by the training interval described later, the clock is set to within 0.5 ms in less than 300 s.

* * *

#### Operating Intervals

The state machine operates in one of four nonoverlapping intervals.

**Training interval**

: This interval is used at startup when the frequency file is not present at startup. It begins when the first update is received by the discipline algorithm and ends when an update is received following the stepout threshold. The clock phase is steered to the offset presented at the beginning of the interval, but without affecting the frequency. During the interval further updates are ignored. At the end of the interval the frequency is calculated as the phase change during the interval divided by the length of the interval. This generally results in a frequency error less than 0.5 PPM. Note that, if the intrinsic oscillator frequency error is large, the offset will in general have significant error. This is corrected during the subsequent startup interval.

**Startup interval**

: This interval is used at startup to amortize the residual offset while not affecting the frequency. If the frequency file is present, it begins when the first update is received by the discipline. If not, it begins after the training interval. It ends when the hold timer decrements to zero or when the residual offset falls below 0.5 ms.

**Step interval**

: This interval is used as a spike blanker during periods when the offsets exceed the step threshold. The interval continues as long as offsets are received that are greater than the step threshold, but ends when either an offset is received less than the step threshold or until the time since the last valid update exceeds the stepout threshold.

**Sync Interval**

: This interval is implicit; that is, it is used when none of the above intervals are used.

* * *

#### State Transition Function

The state machine consists of five states. An event is created when an update is received by the discipline algorithm. Depending on the state and the offset magnitude, the machine performs some actions and transitions to the same or another state. Following is a short description of the states.

**FSET - The frequency file is present**

: Load the frequency file, initialize the hold timer and continue in SYNC state.

**NSET - The frequency file is not present**

: Initialize the hold timer and continue in FREQ state.

**FREQ - Frequency training state**

: Disable the clock discipline until the time since the last update exceeds the stepout threshold. When this happens, calculate the frequency, initialize the hold counter and transition to SYNC state.

**SPIK - Spike state**

: A update greater than the step threshold has occurred. Ignore the update and continue in this state as long as updates greater than the step threshold occur. If a valid update is received, continue in SYNC state. When the time since the last valid update was received exceeds the stepout threshold, step the system clock and continue in SYNC state.

**SYNC - Ordinary clock discipline state**

: Discipline the system clock time and frequency using the hybrid phase/frequency feedback loop. However, do not discipline the frequency if the hold timer is nonzero.