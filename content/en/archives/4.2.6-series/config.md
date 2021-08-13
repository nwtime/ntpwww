---
title: "Build Options"
type: archives
---


![gif](/archives/pic/pogo3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

Gnu autoconfigure tools are in the backpack.

Last update: Monday, December 15, 2008 20:54 UTC

* * *

Most modern software distributions include an autoconfigure utility which customizes the build and install configuration according to the specific hardware, operating system and file system conventions. For NTP this utility is called <tt>configure</tt>, which is run before building and installing the program components. For most installations no additional actions are required other than running <tt>configure</tt> with no options. However, it is possible to customize the build and install configuration through the use of <tt>configure</tt> options.

The available options, together with a concise description, can be displayed by running <tt>configure</tt> with the <tt>--help</tt> option. Various options can be used to reduce the memory footprint, adjust the scheduling priority, enable or disable debugging support or reference clock driver support. The options can be used to specify where to install the program components or where to find various libraries if they are not in the default place.