---
title: "Porting Hints"
type: archives
---

![gif](/archives/pic/wingdorothy.gif)[from _The Wizard of Oz_, L. Frank Baum](http://www.eecis.udel.edu/%7emills/pictures.html)

Porting Dorothy in Oz

Last update: 20:17 UTC Monday, December 02, 2002

* * *

{{% alert title="NOTE" color="warning" %}} 
The following procedures have been replaced by GNU <tt>automake</tt> and <tt>autoconfigure</tt>. This page is to be updated in the next release.
{{% /alert %}}

Porting to a new machine or operating system ordinarily requires updating the <tt>./machines</tt> directory and the <tt>./compilers</tt> directories in order to define the build environment and autoconfigure means. You will probably have to modify the <tt>ntp_machines.h</tt> file and <tt>"l_stdlib.h"</tt> files as well. The two most famous trouble spots are the I/O code in <tt>./ntpd/ntp_io.c</tt> and the clock adjustment code in <tt>./ntpd/ntp_unixclock.c</tt>.

These are the rules so that older bsd systems and the POSIX standard system can coexist together.

1.  If you use <tt>select</tt> then include <tt>"ntp_select.h"</tt>. <tt>select</tt> is not standard, since it is very system dependent as to where it is defined. The logic to include the right system dependent include file is in <tt>"ntp_select.h"</tt>.
2.  Always use POSIX definition of strings. Include <tt>"ntp_string.h"</tt> instead of <tt><string.h></tt>.
3.  Always include <tt>"ntp_malloc.h"</tt> if you use <tt>malloc</tt>.
4.  Always include <tt>"ntp_io.h"</tt> instead of <tt><sys/file.h></tt> or <tt><fnctl.h></tt> to get <tt>O_*</tt> flags.
5.  Always include <tt>"ntp_if.h"</tt> instead of <tt><net/if.h></tt>.
6.  Always include <tt>"ntp_stdlib.h"</tt> instead of <tt><stdlib.h></tt>.
7.  Define any special defines needed for a system in <tt>./include/ntp_machine.h</tt> based on system identifier. This file is included by the <tt>"ntp_types.h"</tt> file and should always be placed first after the <tt><></tt> defines.
8.  Define any special library prototypes left over from the system library and include files in the <tt>"l_stdlib.h"</tt> file. This file is included by the <tt>"ntp_stdlib.h"</tt> file and should ordinarily be placed last in the includes list.
9.  Don't define a include file by the same name as a system include file.

<tt>"l_stdlib.h"</tt> can contain any extra definitions that are needed so that <tt>gcc</tt> will shut up. They should be controlled by a system identifier and there should be a separate section for each system. Really this will make it easier to maintain.

See <tt>include/ntp_machines.h</tt> for the various compile time options.

When you are satisfied the port works and that other ports are not adversely affected, please send [patches](/archives/4.2.0/patches) for the system files you have changed, as well as any documentation that should be updated, including the advice herein.

Good luck.