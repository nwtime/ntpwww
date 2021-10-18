---
title: "6.4. Compatibility"
type: "archives"
---

An ideal world has no compatibility issues. However, this section deals with the existing ones.

#### 6.4.1. The Kernel PLL

6.4.1.1. [How many different kernel models and implementations exist?](#how-many-different-kernel-models-and-implementations-exist)  
6.4.1.2. [What's new in each Version?](#whats-new-in-each-version)  
6.4.1.3. [Are the individual kernel models compatible?](#are-the-individual-kernel-models-compatible)  
6.4.1.4. [How can I find out which kernel is in effect?](#how-can-i-find-out-which-kernel-is-in-effect)  
6.4.1.5. [Is the Linux implementation different?](#is-the-linux-implementation-different)

* * *

#### 6.4.1.1. How many different kernel models and implementations do exist?

There are definitely at least two major versions for the kernel PLL: The model for NTP version 3, and the model for NTP version 4. Maybe there is a model for older versions too, but I don't know.

In addition to these major versions there are minor variants of these models. Unfortunately these minor variants can't easily be distinguished, because their inventor and chief designer, [Professor David L. Mills](NTP-a-faq.htm#AU-DLM), did not like version control systems or version numbers in the past (see also [Q: 6.4.1.4.](NTP-s-compat.htm#Q-KERNEL-PLL-VERSION)).

* * *

#### 6.4.1.2. What's new in each Version?

As said in [Q: 6.4.1.1.](NTP-s-compat.htm#Q-COMPAT-PLL-NUM-IMPLEM) the history of the earlier kernel clock models are somewhat obscure. The basic features are described in [Q: 5.2.1.1.](NTP-s-algo-kernel.htm#Q-ALGO-KERNEL-CLOCK).

The new clock model designed during development of NTP version 4 has the following new features:

*   Timestamps are represented with 64 bit (instead of 32) to represent a sub-nanosecond resolution. There is also a new interface to control these nanoseconds. The higher precision results in a more continuous flow of time.
*   A new status bit, `STA_MODE`, controls a hybrid PLL/FLL mode, avoiding instabilities.
*   The minimum interval between adjustments has been reduced from 16 seconds to one second, while the maximum interval has been extended from about one hour to 36 hours. Unfortunately `constant` has an incompatible meaning (See [Q: 6.4.1.3.](NTP-s-compat.htm#Q-COMPAT)).
*   PPS processing has been significantly revised as well. The calibration range has been extended, and the robustness towards spikes and jitter has been improved. Sampling intervals have been reduced to achieve a faster response to offset and frequency errors.

Revision 3 of the nanokernel introduced a shorter default calibration interval when correcting the frequency with PPS. At the same time the maximum interval can be adjusted using `MOD_PPSMAX`. Selection of PLL and FLL mode is done automatically now.

Revision 4 of the nanokernel features more direct response to PPS offset errors, more realistic error estimates, and a new mode bit (`MOD_TAI`) to define the offset between UTC and TAI.

A later revision featured a longer default calibration interval for PPS and a partial state reset when `STA_PLL` is cleared.

* * *

#### 6.4.1.3. Are the individual kernel models compatible?

The most recent version known as nanokernel has different semantics for the `time_constant`. When used with the old version 3 daemon, the PLL has a tendency to oscillate, because the damping is too low.

When the old kernel implementation is used with the new version 4 daemon, the PLL is too stiff, causing a slow adjustment to frequency changes.

When the new version 4 daemon has set the `STA_NANO` bit, the old version 3 daemon gets completely confused by nanoseconds which are believed to be microseconds. As it seems, the daemon does not clear `STA_NANO` during startup, so the only solution is to reboot or clear that flag by other means.

[Professor David L. Mills](NTP-a-faq.htm#AU-DLM) wrote:

The old and new kernel code does use different time constant ranges. The current ntpd and API do understand and adjust accordingly. The old xntpd will probably be off by a factor of 16 in the time constant. That is absolutely certain to cause unstable operation.

If you have an even older implementation, you probably can't compile the daemon, or the daemon will not use the kernel PLL.

* * *

#### 6.4.1.4. How can I find out which kernel is in effect?

As indicated before, this is not quite easy. Maybe the following procedure can help you.

1.  If <code>#include \<sys/timex.h></code> defines the symbol `NTP_API` you are lucky. This symbol appeared in the kernel simulator dated 1999-08-28, and the symbol's value was `3` there. So any newer version should define a different value. It's quite unlikely that older implementations define the same symbol set to a smaller value.

    1.  If you can set `STA_NANO` via `ntp_adjtime()`, your implementation provides a nanosecond resolution.

    2.  Otherwise your implementation provides microsecond resolution.

2.  If <code>#include \<sys/timex.h></code> defines the symbol `STA_NANO` you may have the newer clock model for NTPv4.

3.  If you still had no success with this procedure, you have a kernel implementation for NTPv3 or even older.

If your `NTP_API` is set to `4` or higher, the following procedure may identify the sub-releases:

1.  When the default upper limit for the PPS calibration interval is 256 seconds (not 128 seconds), and the length of the calibration interval is reset to 4 seconds whenever `STA_PLL` makes a one-to-zero transition, you have a nanokernel revision of at least 2000-10-25.

2.  Otherwise your revision is from 2000-08-29 or older.

XXX _Note from the editor:_ The procedures above can probably be improved. Contributions welcome!

* * *

#### 6.4.1.5. Is the Linux implementation different?

Yes, it is. One reason is that the original nanokernel (after it had been said to work well and be stable) was found to be broken with respect to `STA_PPSWANDER`. According to [Professor David L. Mills](NTP-a-faq.htm#AU-DLM) the current nanokernel is no longer showing that defect. As I was not aware of that change, I did something different.

[Professor David L. Mills](NTP-a-faq.htm#AU-DLM) wrote: `MAXWANDER` is 100 in the current nanokernel, not 500. This value was adjusted due to simulation experience."

When used with a PPS signal, the Linux implementation (as of PPSkit-0.7) also computes uncommon values for `tolerance` as I explained to [Professor David L. Mills](NTP-a-faq.htm#AU-DLM):

Secondly my code starts out at 500 PPM (because that's what the nanokernel simulator used that I had). Only if a PPS signal is active and within bounds (`pps_shift` >= 5 in my case, rather arbitrary), I watch the interval of PPS frequencies and make the maximum width of that interval the new `tolerance` (clamped at 500 PPM, of course). Then I use that value of `tolerance` as limit for the "wander". As the first interval is quite narrow (close to zero), the calibration interval will get stuck at 2^5 seconds if the frequency adjustment increases, or maybe even it will be reduced until the wander either within the current bounds. Only if the calibration interval is at its minimum possible length with a desire to decrease still, the wander will be adjusted (otherwise you might end with a maximum wander of 1 PPM and the PPS frequency will bump up and down by that limit).

In PPSkit-0.9 the tolerance appears as fixed 496 ppm, but the maximum of the observed wander is still computed and used internally. It is used to advance the maximum error by a more reasonable amount.

Another feature is that the maximum error is limited in Linux: It's either 16s or 2s, depending on your version of the kernel. Whenever that value is reached, the `STA_UNSYNC` flag is set in the kernel clock.