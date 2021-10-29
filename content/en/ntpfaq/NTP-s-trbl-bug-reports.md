---
title: "8.4. Reporting Bugs"
type: "archives"
---

8.4.1 [When should I report a Problem?](#841-when-should-i-report-a-problem)  
8.4.2 [What should I report?](#842-what-should-i-report)   

* * *

#### 8.4.1 When should I report a Problem?

Before [reporting a problem](/bugs), make sure that it is not a known bug or already requested feature. Also try to make sure that the mistake is not at your side.

[Search the bugs database](https://bugs.ntp.org/query.cgi) to see whether the problem has been reported or if there is an existing solution. An Internet search may also help determine if there is a known solution.

If it turns out that there is a newer version of the software, try it! The new version might solve your problem.

* * *

#### 8.4.2 What should I report?

If it turns out that noone has reported the bug yet, [report a bug](https://bugs.ntp.org/enter_bug.cgi) and include these details in the **Description:** hardware, operating system (name, vendor, version, patch revision), NTP software release, what steps are needed to recreate the error, and the exact text of any error messages or monitoring data.

To make it easier for other users searching for a similar issue, use a short, keyword description for the **Summary**. For example, "NTP bug" is not helpful for searching but "ntp client sending traps even after configuring "restrict default notrap"" is quite descriptive.

> **NOTE:** If you are using a pre-compiled binary, and you can contact the vendor or maker of it, do so. This is specifically true if you have a support contract or warranty.