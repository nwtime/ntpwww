---
title: "6.4. Compatibility"
type: "archives"
---

An ideal world has no compatibility issues. This section deals with known incompatibilities.

6.4.1 [The Kernel PLL](#641-the-kernel-pll)  
6.4.1.1 [How many different kernel models and implementations exist?](#6411-how-many-different-kernel-models-and-implementations-exist)  
6.4.1.2 [What's new in each Version?](#6412-whats-new-in-each-version)  
6.4.1.3 [Are the individual kernel models compatible?](#6413-are-the-individual-kernel-models-compatible)   
6.4.1.4 [Is the Linux implementation different?](#6414-is-the-linux-implementation-different)

* * *

#### 6.4.1 The Kernel PLL

#### 6.4.1.1 How many different kernel models and implementations exist?

There are two major versions for the kernel PLL: the model for NTPv3, and the model for NTPv4.

* * *

#### 6.4.1.2 What's new in each Version?

The history of the earlier kernel clock models is somewhat obscure. The basic features are described in [Q: 5.2.1.1](/ntpfaq/ntp-s-algo-kernel/#5211-what-is-special-about-the-kernel-clock).

The clock model designed for NTPv4 has these features:

*   Timestamps are represented with 64 bits (instead of 32) to represent a sub-nanosecond resolution. There is also a new interface to control these nanoseconds. The higher precision results in a more continuous flow of time.
*   A new status bit, `STA_MODE`, controls a hybrid PLL/FLL mode, avoiding instabilities.
*   The minimum interval between adjustments has been reduced from 16 seconds to one second, while the maximum interval has been extended from about one hour to 36 hours. Unfortunately `constant` has an [incompatible meaning](#6413-are-the-individual-kernel-models-compatible).
*   PPS processing has been significantly revised. The calibration range has been extended, and the robustness towards spikes and jitter has been improved. Sampling intervals have been reduced to achieve a faster response to offset and frequency errors.

Revision 3 of the nanokernel introduced a shorter default calibration interval when correcting the frequency with PPS. At the same time the maximum interval can be adjusted using `MOD_PPSMAX`. Selection of PLL and FLL mode is done automatically now.

Revision 4 of the nanokernel features more direct response to PPS offset errors, more realistic error estimates, and a new mode bit (`MOD_TAI`) to define the offset between UTC and TAI.

A later revision featured a longer default calibration interval for PPS and a partial state reset when `STA_PLL` is cleared.

* * *

#### 6.4.1.3 Are the individual kernel models compatible?

The most recent version known as nanokernel has different semantics for the `time_constant`. When used with the old version 3 `xntpd` daemon, the PLL has a tendency to oscillate, because the damping is too low.

When the old kernel implementation is used with the new version 4 daemon, the PLL is too stiff, causing a slow adjustment to frequency changes.

When the NTPv4 daemon sets the `STA_NANO` bit, the old NTPv3 daemon gets completely confused by nanoseconds which are believed to be microseconds. As it seems, the daemon does not clear `STA_NANO` during startup, so the only solution is to reboot or clear that flag by other means.

[Professor David L. Mills](mailto:mills@udel.edu) wrote:

The old and new kernel code use different time constant ranges. The current `ntpd` and API do understand and adjust accordingly. The old `xntpd` will probably be off by a factor of 16 in the time constant. That is absolutely certain to cause unstable operation.

If you have an even older implementation, you probably can't compile the daemon, or the daemon will not use the kernel PLL.

* * *

#### 6.4.1.4 Is the Linux implementation different?

Yes, it is. One reason is that the original nanokernel was found to be broken with respect to `STA_PPSWANDER`. According to [Professor David L. Mills](mailto:mills@udel.edu) the current nanokernel is no longer showing that defect:

Professor David L. Mills wrote: "`MAXWANDER` is 100 in the current nanokernel, not 500. This value was adjusted due to simulation experience."

When used with a PPS signal, the Linux implementation (as of PPSkit-0.7) also computes uncommon values for `tolerance` as I explained to Professor David L. Mills:

Another feature is that the maximum error is limited in Linux: it's either 16s or 2s, depending on your version of the kernel. Whenever that value is reached, the `STA_UNSYNC` flag is set in the kernel clock.