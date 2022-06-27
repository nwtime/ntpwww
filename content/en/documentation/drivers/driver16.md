---
title: "Bancomm bc635VME Time and Frequency Processor"
description: "The Bancomm bc635VME Time and Frequency Processor driver for the Bancomm bc635VME Time and Frequency Processor. It requires the BANCOMM bc635VME bc350VXI Time and Frequency Processor Module Driver for SunOS 4.x/SunOS 5.x UNIX Systems."
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver16/#synopsis)
*   [Description](/documentation/drivers/driver16/#description)
*   [Additional Information](/documentation/drivers/driver16/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.16._u_</code>
: **Reference ID:** `BTFP`
: **Driver ID:** `GPS_BANCOMM`
: **Bancomm Device:** `/dev/btfp0`
: **Requires:** Bancomm `bc635` TFP device module driver for SunOS 4.x/SunOS 5.x

* * *

#### Description

This is the clock driver for the Bancomm bc635VME Time and Frequency Processor. It requires the BANCOMM bc635VME bc350VXI Time and Frequency Processor Module Driver for SunOS 4.x/SunOS 5.x UNIX Systems.

Most of this code is originally from `refclock_bancomm.c` with thanks. It has been modified and tested on an UltraSparc IIi-cEngine running Solaris 2.6. A port for HPUX is not available henceforth.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/4.2.8-series/refclock/)

