---
title: "Time, what Time?"
type: "archives"
---

This section discusses general topics related to time and time-keeping.

> **Note:** XXX _Note from the editor:_ This part is still incomplete. Please contribute!

* * *

* 2.1. [What is Time?](#21-what-is-time)
* 2.2. [What is UTC?](#22-what-is-utc)
* 2.3. [Is UTC the same as GMT?](#23-is-utc-the-same-as-gmt)
* 2.4. [What happens during a Leap Second?](#24-what-happens-during-a-leap-second)

* * *

#### 2.1. What is Time?

XXX _Note from the editor:_ Tough question, any volunteers?

In the meantime I'll throw in a quote from the back of my mind (a fortune cookie from Edition 7 I think): "Time has been invented in the universe so that everything would not happen at once."

There's another interesting relation between time and change: There is no change without the concept of time, and there is no movement without time.

[Philippe Eveque](mailto:philippe_eveque@grenoble.hp.com) contributed:

Nobody can tell what Time is. However everybody does know its effects. Time implies memory and this is specially strange to consider this, in the context of computer science. Reversely does memory implies time in some way?

* * *

#### 2.2. What is UTC?

UTC (Universal Time Coordinated, _Temps Universel Coordonné_) is an official standard for the current time. UTC evolved from the former GMT (Greenwich Mean Time) that once was used to set the clocks on ships before they left for a long journey. Later GMT had been adopted as the world's standard time. One of the reasons that GMT had been replaced as official standard time was the fact that it was based on the mean solar time. Newer methods of time measurement showed that the mean solar time varied a lot by itself.

The following list will explain the main components of UTC:

* _Universal_ means that the time can be used everywhere in the world, meaning that it is independent from time zones (i.e. it's not _local time_). To convert UTC to local time, one would have to add or subtract the local time zone.
* _Coordinated_ means that several institutions contribute their estimate of the current time, and UTC is built by combining these estimates.

The UTC second has been defined by the 13th General Conference of Weights and Measures in 1967 as "The second is the duration of 9,192,631,770 periods of the radiation corresponding to the transition between the two hyperfine levels of the ground state of the cesium-133 atom."

* * *

#### 2.3. Is UTC the same as GMT?

The observatory in Greenwich derived GMT from astronomical events like the solar day. UTC is based on a quantum resonance of a cesium atom, being quite more accurate.

Unfortunately the earth's rotation is not very much impressed by the definition of the UTC second. Having 86400 UTC seconds per day on an earth that's slowing down would mean that midnight would eventually fall in the middle of the day. As this is probably unacceptable, some extra seconds can be added or removed inside the UTC time-scale to keep synchronization. That patch work is named _leap seconds_.

To make things worse, leap seconds can be predicted as much as the earth's rotation, which is not at all. Therefore you can't easily make calculations for dates in the future using UTC; at least not with accuracy of a few seconds.

* * *

#### 2.4. What happens during a Leap Second?

During a leap second, either one second is removed from the current day, or a second is added. In both cases this happens at the end of the UTC day. If a leap second is inserted, the time in UTC is specified as `23:59:60`. In other words, it takes two seconds from `23:59:59` to `0:00:00` instead of one. If a leap second is deleted, time will jump from `23:59:58` to `0:00:00` in one second instead of two. See also [Section 5.2](NTP-s-algo-kernel.htm).