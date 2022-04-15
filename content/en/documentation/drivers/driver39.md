---
title: "hopf PCI-Bus Receiver (6039 GPS/DCF77)"
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver39/#synopsis)
*   [Description](/documentation/drivers/driver39/#description)
*   [Operating System Compatibility](/documentation/drivers/driver39/#operating-system-compatibility)
*   [O/S System Configuration](/documentation/drivers/driver39/#os-system-configuration)
*   [Fudge Factors](/documentation/drivers/driver39/#fudge-factors)
*   [Questions or Comments](/documentation/drivers/driver39/#questions-or-comments)

* * *

#### Synopsis

**Address:** <code>127.127.39._X_</code>
: **Reference ID:** `hopf` (default), `GPS`, `DCF`
: **Driver ID:** `HOPF_P`

![gif](/documentation/pic/fg6039.jpg)

* * *

#### Description

The `refclock_hopf_pci` driver supports the [hopf](https://www.hopf.com/index.php) PCI-bus interface 6039 GPS/DCF77.

Additional software and information about the software drivers as well as the latest NTP driver source, executables, and documentation is maintained at http://www.atlsoft.de/ntp-tcp-netzwerkzeit/.

* * *

#### Operating System Compatibility

The hopf clock driver has been tested on the following software and hardware platforms:

| Platform | Operating System |
| ----- | ----- |
| i386 (PC) | Linux |
| i386 (PC) | Windows NT |
| i386 (PC) | Windows 2000 |

* * *

#### O/S System Configuration

**UNIX**

The driver attempts to open the device `/dev/hopf6039 REFID`. The device entry will be made by the installation process of the kernel module for the PCI-bus board. The driver sources belongs to the delivery equipment of the PCI-board.

**Windows NT/2000**

The driver attempts to open the device by calling the function `OpenHopfDevice()`. This function will be installed by the Device Driver for the PCI-bus board. The driver belongs to the delivery equipment of the PCI-board.

* * *

#### Fudge Factors

<code>**refid _string_**</code>

: Specifies the driver reference identifier, `GPS` or `DCF`.

<code>**flag1 0 | 1**</code>

: When set to 1, driver syncs even if only crystal driven.

* * *

#### Questions or Comments

[Bernd Altmeier](mailto:altmeier@atlsoft.de), [Ing.-Büro für Software www.ATLSoft.de](http://www.ATLSoft.de)