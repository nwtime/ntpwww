---
title: "FreeBSD Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

If you are compiling under FreeBSD and see messages in the syslogs that indicate that the `ntpd` process is trying to use unavailable `sched_` calls, it means you are running a kernel that does not have the POSIX scheduling calls enabled.

You have two choices:
: * Ignore the messages.
: * Generate a new kernel, where the kernel configuration file contains the lines:

        options		"P1003_1B"
        options		"_KPOSIX_PRIORITY_SCHEDULING"
        options		"_KPOSIX_VERSION=199309L"