---
title: "Changes"
type: archives
---

Ulrich Windl <Ulrich.Windl@rz.uni-regensburg.de>

<code>**xntpd/refclock_parse.c**</code>
: * Added support to supply power from RS232 with `CLOCK_RAWDCF`.
: * Known to work with Linux 1.2.
: * Made Linux ignore parity errors with `CLOCK_RAWDCF`.

<code>**parse/util/dcfd.c**</code>
: * Removed conflicting prototype for Linux (`sscanf`).
: * Corrected spelling error.
: * Made Linux ignore parity errors.
: * Added support to supply power from RS232 with `CLOCK_RAWDCF`.

<code>**parse/util/testdcf.c**</code>
: * Made Linux ignore parity errors.