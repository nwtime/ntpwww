---
title: "Solaris Symptoms and Resolutions Article 19195"
type: archives
---

{{% alert color="warning" %}}
This content is from SunSolve Article 19195 which once lived on the Sun Microsystems website.
{{% /alert %}}

| SRDB ID | Synopsis | Date |
| ----- | ----- | ----- |
| 19195 | Upgraded to 2.6, using xntpd, but the system clock is drifting. Worked fine | 4 Sep 1999 |

* * *

#### Problem Description

Ever since upgrading to Solaris 2.6, the system clock has been drifting and
there are messages like 'synchronisation lost', 'Previous time adjustment
didn't complete' and 'time reset (step)' a lot in the /var/adm/messages 
file. The system either was previously working fine with the freeware
xntpd or the configuration was copied from another system that was 
using the freeware version.

-- 23-Apr-99 08:22 US/Eastern --

* * *

#### Problem Solution

The common lore for setting up xntpd on Solaris using
the freeware version included the warning to set the 
kernel variable <font color="red">dosynctodr</font> to 0 in the /etc/system 
file thus: set <font color="red">dosynctodr</font>=0

When using NTP on Solaris 2.6 or later, the kernel 
variable MUST be left at the default value of 1\. Prior 
to 2.6 this variable controlled whether or not to rein  
in the softclock using the hardware clock, with the result 
that NTP and the hardware clock would fight for control of 
the soft clock; thus before 2.6 you had to set <font color="red">dosynctodr</font> 
to 0\. At 2.6, every system call that adjusts the softclock 
also sets the hard clock, thus while NTP controls the soft 
clock, the hard clock is also controlled. Setting 
<font color="red">dosynctodr</font> to 0 reverts the behavior back to the pre 2.6 
defaulkt behavior, having exactly the opposite effect 
as that intended.

Do not set <font color="red">dosynctodr</font> to 0.

* * *

**Product Area** 	Bundled Network

**Product** 	NTP

**OS** 	Solaris 2.6

**Hardware** 	Ultra 2

**Document Content** 	with freeware xntpd.
