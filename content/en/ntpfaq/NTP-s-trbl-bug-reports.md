---
title: "8.4. Reporting Bugs"
type: "archives"
---

Originally I would not believe that such a section is necessary, but there are actually reports like: "I'm using your software, but it doesn't work."

8.4.1. [When should I report a Problem?](#when-should-i-report-a-problem)  
8.4.2. [What should I report?](#what-should-i-report)  
8.4.3. [Where should I report?](#where-should-i-report)  
8.4.4. [What should never be sent?](#what-should-never-be-sent)  

* * *

#### 8.4.1. When should I report a Problem?

Before reporting a problem, make sure that it is not a known bug, or maybe even a feature. Also try to make sure that the mistake is not at your side.

Then you could try to find out whether the problem has been reported before, and maybe you might even find a solution or helpful advise for your problem. Today's Internet search engines should make it easy to find such public reports in news://comp.protocols.time.ntp.

If it turns out that there is a newer version of the software, try it! Most likely you will be asked to exactly do that. Maybe your problem has already been solved.

* * *

#### 8.4.2. What should I report?

Simply report what you have (hardware, operating system (name, vendor, version, patch revision), NTP software release, anything unusual), what you did (compilation protocols, configuration files, etc), what you got (syslog messages, error messages, unusual output, monitoring data), and what you expected (be as precise as possible).

For the first contact try to include the most essential data. Personally I think it's better to leave out any lengthy data you don't understand, than to include it. Most likely someone will ask for such data. So possibly save most data for later reference, but don't include it all in the first contact.

* * *

#### 8.4.3. Where should I report?

If you are using a precompiled binary, and you can contact the vendor or maker of it, do so. This is specifically true if you have a support contract, warranty, etc.

When using the open-source software, it's best to make a public report in news://comp.protocols.time.ntp. Many people will see it, and chances are high that someone either has the same problem, or maybe a solution already. It's also a good place if you feel unsure about the nature of the problem (bug or feature).

Only if you are confident that you have found a new problem, you should send electronic mail to the address found in the HTML documentation of the distribution.

Finally: When posting to news://comp.protocols.time.ntp, don't use "NTP" as subject. Similarly don't use the subject "NTP bug" when sending to a mailing list named ntp-bugs. Use a crispy short description of the problem. Instead of "software problem" write "CPU emits blue smoke every 1024 seconds" (if that's your problem) ;-)

* * *

#### 8.4.4. What should never be sent?

Please do not send SPAM, advertising, basic configuration questions, computer viruses, or otherwise rotten material to the mailing list. You may be completely ignored in the future when doing so.

Any article sent to news://comp.protocols.time.ntp should be related to NTP.