---
title: "Clock Discipline Algorithm"
description: "At the heart of the NTP specification and reference implementation is the clock discipline algorithm, an intricately crafted algorithm that automatically adapts for optimum performance while minimizing network overhead."
type: archives
aliases:
    - /current-stable/discipline/
---

#### Table of Contents

*   [General Overview](/documentation/4.2.8-series/discipline/#general-overview)
*   [Clock Discipline Operations](/documentation/4.2.8-series/discipline/#clock-discipline-operations)
*   [Loop Dynamics](/documentation/4.2.8-series/discipline/#loop-dynamics)
*   [Clock Initialization and Management](/documentation/4.2.8-series/discipline/#clock-initialization-and-management)

* * *

#### General Overview

At the heart of the NTP specification and reference implementation is the clock discipline algorithm, which is best described as an adaptive parameter, hybrid phase/frequency-lock feedback loop. It is an intricately crafted algorithm that automatically adapts for optimum performance while minimizing network overhead. Operation is in two modes, phase-lock loop (PLL), which is used at poll intervals below the Allan intercept, by default 2048 s, and frequency-lock loop (FLL), which is used above that.

* * *

#### Clock Discipline Operations

A block diagram of the clock discipline is shown in Figure 1. The timestamp of a reference clock or remote server is compared with the timestamp of the system clock, represented as a variable frequency oscillator (VFO), to produce a raw offset sample <code>_V<sub>d</sub>_</code>. Offset samples are processed by the clock filter to produce a filtered update <code>_V<sub>s</sub>_</code>. The loop filter implements a type-2 proportional-integrator controller (PIC). The PIC can minimize errors in both time and frequency using predictors <code>_x_</code> and <code>_y_</code>, respectively. The clock adjust process samples these predictors once each second for the daemon discipline or once each tick interrupt for the kernel discipline to produce the system clock update <code>_V<sub>c</sub>_</code>.

![gif](/documentation/pic/discipline.gif)

**Figure 1: Clock Discipline Algorithm**

In PLL mode the frequency predictor is an integral of the offset over past updates, while the phase predictor is the offset amortized over time in order to avoid setting the clock backward. In FLL mode the phase predictor is not used, while the frequency predictor is similar to the NIST _lockclock_ algorithm. In this algorithm, the frequency predictor is computed as a fraction of the current offset divided by the time since the last update in order to minimize the offset at the next update.

The discipline response in PLL mode is determined by the _time constant_, which results in a "stiffness" depending on the jitter of the available sources and the wander of the system clock oscillator. The scaled time constant is also used as the poll interval described on the [Poll Program](/documentation/4.2.8-series/poll/) page. However, in NTP symmetric mode, each peer manages its own poll interval and the two might not be the same. In such cases either peer uses the minimum of its own poll interval and that of the other peer, which is included in the NTP packet header.

* * *

#### Loop Dynamics

It is necessary to verify that the clock discipline algorithm is stable and satisfies the Nyquist criterion, which requires that the sampling rate be at least twice the bandwidth. In this case the bandwidth can be approximated by the reciprocal of the time constant. In the NTP specification and reference implementation, time constants and poll intervals are expressed as exponents of 2. By construction, the time constant exponent is five times the poll interval exponent. Thus, the default poll exponent of 6 corresponds to a poll interval of 64 s and a time constant of 2048 s. A change in the poll interval changes the time constant by a corresponding amount.. The Nyquist criterion requires the sample interval to be not more than half the time constant or 1024 s. The clock filter guarantees at least one sample in eight poll intervals, so the sample interval is not more than 512 s. This would be described as oversampling by a factor of two. Finally, the PLL parameters have been chosen for a damping factor of 2, which results in a much faster risetime than with critical damping, but results in modest overshoot of 6 percent.

It is important to understand how the dynamics of the PLL are affected by the time constant and poll interval. At the default poll interval of 64 s and a step offset change of 100 ms, the time response crosses zero in about 50 min and overshoots about 6 ms, as per design. Ordinarily, a step correction would causes a temporary frequency surge of about 5 PPM, which along with the overshoot slowly dissipates over a few hours.

However, the clock state machine used with the discipline algorithm avoids this transient at startup. It does this using a previously saved frequency file, if present, or by measuring the oscillator frequency, if not. It then quickly amortizes the residual offset at startup without affecting the oscillator frequency. In this way the offset error is less than 0.5 ms within 5 min, if the file is present, and within 10 min if not. See the [Clock State Machine](/documentation/4.2.8-series/clock/) page for further details.

Since the PLL is linear, the response with different offset step amplitudes and poll intervals has the same characteristic shape, but scaled differently in amplitude and time. The response scales exactly with step amplitude, so that the response to a 10-ms step has the same shape as at 64 s, but with amplitude compressed by one-tenth. The response scales exactly with poll interval, so that response at a poll interval of 8 s has the same shape as at 64 s, but with time compressed by one-eighth.

The optimum time constant, and thus the poll interval, depends on the network time jitter and the oscillator frequency wander. Errors due to jitter decrease as the time constant increases, while errors due to wander decrease as the time constant decreases. For typical Internet paths, the two error characteristics intersect at a point called the _Allan intercept_, which represents the optimum time constant. With a compromise Allan intercept of 2048 s, the optimum poll interval is about 64 s, which corresponds to a compromise poll exponent of 6. For fast LANs with modern computers, the Allan intercept is somewhat lower at around 512 s, so a compromise poll exponent of 4 (16 s) is appropriate. An intricate, heuristic algorithm is used to manage the actual poll interval within a specified range. Details are on the [Poll Program](/documentation/4.2.8-series/poll/) page.

In the NTPv4 specification and reference implementation a state machine is used to manage the system clock under exceptional conditions, as when the daemon is first started or when encountering severe network congestion. In extreme cases not likely to be encountered in normal operation, the system time can be stepped forward or backward more than 128 ms. Further details are on the [Clock State Machine](/documentation/4.2.8-series/clock/) page.

* * *

#### Clock Initialization and Management

If left running continuously, an NTP client on a fast LAN in a home or office environment can maintain synchronization nominally within one millisecond. When the ambient temperature variations are less than a degree Celsius, the clock oscillator frequency is disciplined to within one part per million (PPM), even when the clock oscillator native frequency offset is 100 PPM or more.

For laptops and portable devices when the power is turned off, the battery backup clock offset error can increase as much as one second per day. When power is restored after several hours or days, the clock offset and oscillator frequency errors must be resolved by the clock discipline algorithm, but this can take several hours without specific provisions.

The provisions described in this section insure that, in all but pathological situations, the startup transient is suppressed to within nominal levels in no more than five minutes after a warm start or ten minutes after a cold start. Following is a summary of these provisions. A detailed discussion of these provisions is on the [Clock State Machine](/documentation/4.2.8-series/clock/) page.

The reference implementation measures the clock oscillator frequency and updates a frequency file at intervals of one hour or more, depending on the measured frequency wander. This design is intended to minimize write cycles in NVRAM that might be used in a laptop or portable device. In a warm start, the frequency is initialized from this file, which avoids a possibly lengthy convergence time. In a cold start when no frequency file is available, the reference implementation first measures the oscillator frequency over a five-min interval. This generally results in a residual frequency error less than 1 PPM. The measurement interval can be changed using the <code>stepout</code> option of the [<code>tinker</code>](/documentation/4.2.8-series/miscopt/) command.

In order to reduce the clock offset error at restart, the reference implementation next disables oscillator frequency discipline and enables clock offset discipline with a small time constant. This is designed to quickly reduce the clock offset error without causing a frequency surge. This configuration is continued for an interval of five-min, after which the clock offset error is usually no more than a millisecond. The measurement interval can be changed using the <code>stepout</code> option of the [<code>tinker</code>](/documentation/4.2.8-series/miscopt/) command.

Another concern at restart is the time necessary for the select and cluster algorithms to refine and validate the initial clock offset estimate. Normally, this takes several updates before setting the system clock. As the default minimum poll interval in most configurations is about one minute, it can take several minutes before setting the system clock. The <code>iburst</code> option of the [<code>server</code>](/documentation/4.2.8-series/confopt/#server-command-options) command changes the behavior at restart and is recommended for client/server configurations. When this option is enabled, the client sends a volley of six requests at intervals of two seconds. This usually insures a reliable estimate is available in about ten seconds before setting the clock. Once this initial volley is complete, the procedures described above are executed.

As a result of the above considerations, when a backup source, such as the local clock driver, ACTS modem driver or orphan mode is included in the system configuration, it may happen that one or more of them are selectable before one or more of the regular sources are selectable. When backup sources are included in the configuration, the reference implementation waits an interval of several minutes without regular sources before switching to backup sources. This is generally enough to avoid startup transients due to premature switching to backup sources. The interval can be changed using the <code>orphanwait</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command.