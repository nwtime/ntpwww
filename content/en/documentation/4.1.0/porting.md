---
title: "Porting Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/wingdorothy.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures/)

Porting Dorothy in Oz

* * *

{{% alert title="NOTE" color="warning" %}} 
The following procedures have been replaced by GNU <code>automake</code> and <code>autoconfigure</code>. This page is to be updated in the next release.
{{% /alert %}}

Porting to a new machine or operating system ordinarily requires updating the <code>./machines</code> directory and the <code>./compilers</code> directories in order to define the build environment and autoconfigure means. You will probably have to modify the <code>ntp_machines.h</code> file and <code>l_stdlib.h</code> files as well. The two most famous trouble spots are the I/O code in <code>./ntpd/ntp_io.c</code> and the clock adjustment code in <code>./ntpd/ntp_unixclock.c</code>.

These are the rules so that older bsd systems and the POSIX standard system can coexist together.

1.  If you use <code>select</code> then include <code>ntp_select.h</code>. <code>select</code> is not standard, since it is very system dependent as to where it is defined. The logic to include the right system dependent include file is in <code>ntp_select.h</code>.

2.  Always use POSIX definition of strings. Include <code>ntp_string.h</code> instead of <code><string.h></code>.

3.  Always include <code>ntp_malloc.h</code> if you use <code>malloc</code>.

4.  Always include <code>ntp_io.h</code> instead of <code><sys/file.h></code> or <code><fnctl.h></code> to get <code>O_*</code> flags.

5.  Always include <code>ntp_if.h</code> instead of <code><net/if.h></code>.

6.  Always include <code>ntp_stdlib.h</code> instead of <code><stdlib.h></code>.

7.  Define any special defines needed for a system in <code>./include/ntp_machine.h</code> based on system identifier. This file is included by the <code>ntp_types.h</code> file and should always be placed first after the <code><></code> defines.

8.  Define any special library prototypes left over from the system library and include files in the <code>l_stdlib.h</code> file. This file is included by the <code>ntp_stdlib.h</code> file and should ordinarily be placed last in the includes list.

9.  Don't define a include file by the same name as a system include file.

<code>l_stdlib.h</code> can contain any extra definitions that are needed so that <code>gcc</code> will shut up. They should be controlled by a system identifier and there should be a separate section for each system. Really this will make it easier to maintain.

See <code>include/ntp_machines.h</code> for the various compile time options.

When you are satisfied the port works and that other ports are not adversely affected, please send [patches](/documentation/4.1.0/patches/) for the system files you have changed, as well as any documentation that should be updated, including the advice herein.

Good luck.