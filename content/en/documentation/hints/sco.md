---
title: "SCO Unix Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Older SCO Unix versions

NTP 4.0.x does not run on SCO Unix prior to version 3.2.5.0.0. If you need NTP on an older SCO Unix system and don't mind modifying your kernel, use 3.5.91 which has patches for SCO Unix 3.2.4.x.

---

#### Compiling NTP

Delete the old SCO supplied NTP programs using the `custom` utility. Run the NTP configure program with <code>CFLAGS="-b elf -K _processor-type_"</code> for best results.

---

#### Running NTP

Run `tickadj -As` after every reboot to set the variables `clock_drift` and `track_rtc` to the right values.

Run `ntpd` with a high negative nice-value, i.e. `nice --19 ntpd` for best results.

Kees Hendrikse, January 1999