---
title: "4.2.4p6 Release Announcement"
description: "The release announcement for NTP 4.2.4p6, which was released on January 8, 2009."
type: archives
date: "2009-01-08"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.4p6, a Point Release of the NTP Reference Implementation from the NTP Project, is now available.

This release fixes [CVE-2009-0021](https://nvd.nist.gov/vuln/detail/CVE-2009-0021), a vulnerability affecting the OpenSSL library relating to the incorrect checking of the return value of `EVP_VerifyFinal` function.

Credit for finding this issue goes to the Google Security Team for finding the original issue with OpenSSL, and to https://ocert.org/ for finding the problem in NTP and telling us about it.