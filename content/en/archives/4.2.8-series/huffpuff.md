---
title: "The Huff-n'-Puff Filter"
type: archives
---

Last update: 10-Mar-2014 05:09 UTC

* * *

In scenarios where a considerable amount of data are downloaded or uploaded using DSL or telephone modem lines, timekeeping quality can be seriously degraded. This occurs because the traffic volume, and thus the queuing delays, on the upload and download directions of transmission can be very different. In many cases the apparent time errors are so large as to exceed the step threshold and a step correction can occur during and after the data transfer.

The huff-n'-puff filter is designed to correct the apparent time offset in these cases. It depends on knowledge of the propagation delay when no other traffic is present, such as during other than work hours. The filter remembers the minimum delay over the most recent interval measured usually in hours. Under conditions of large delay, the filter corrects the apparent offset using the sign of the offset and the difference between the apparent delay and minimum delay. The name of the filter reflects the negative (huff) and positive (puff) correction, which depends on the sign of the offset. The filter is activated by the <code>tinker huffpuff</code> command, as described in the [Miscellaneous Options](/archives/4.2.8-series/miscopt) page.

* * *

![gif](/archives/pic/flt4.gif)

**Figure 1: Huff-n'-Puff Wedge Scattergram**

Figure 1 shows how the huff-n'-puff filter works. Recall from the [Clock Filter Algorithm](/archives/4.2.8-series/filter) page that the wedge scattergram plots sample points (_x_, _y_) corresponding to the measured delay and offset, and that the limb lines are at slope ±0.5. Note in the figure that the samples are clustered close to the upper limb line, representing heavy traffic in the download direction. The apparent offset <code>_y_<sub>0</sub></code> is near zero at the minimum delay <code>_x_<sub>0</sub></code>, which is near 0.1s. Thus, for a point <code>(_x_, _y_)</code>, the true offset is <code>\> θ = _y_ - (_x_ - _x_<sub>0</sub>) / 2</code> for <code>_y_ > _y_<sub>0</sub></code> at or near the upper limb line or <code>\> θ = _y_ + (_x_ - _x_<sub>0</sub>) / 2</code> for <code>_y_ < _y_<sub>0</sub></code> at or near the lower limb line.

In either case the associated delay is <code>δ = _x_</code>.

In the interior of the wedge scattergram far from the limb lines, the corrections are less effective and can lead to significant errors if the area between the limb lines is heavily populated.
