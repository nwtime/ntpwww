---
title: "Release Numbering Scheme"
description: "An explanation of the current release numbering scheme and the new release numbering scheme for the upcoming 4.3.x releases."
type: archives
---

#### Table of Contents

* [ntp-4.3.0 (new)](#ntp-430-new)
* [ntp-4.2.2 thru ntp-4.2.8 (current)](#ntp-422-thru-ntp-428-current)
* [Prior to 06-Jun-2006](#prior-to-06-jun-2006)

* * *

#### ntp-4.3.0 (new)

Once ntp-4.2.8 has been released we will be changing to a new numbering system, one that is much closer to the one used before ntp-4.2.2.

Discussion on the release numbering scheme should be done at [ReleaseNumberingSchemeDiscussion](https://support.ntp.org/Dev/ReleaseNumberingSchemeDiscussion).

Releases after 4.2.8:
: * The first development release will be ntp-4.3.0
: * The first stable release will be ntp-4.4.0 
: * The first development release tarball will be named `ntp-dev-4.3.0.tar.gz`.
: * The first stable release tarball will be named `ntp-4.4.0.tar.gz`.
: * The first development release tarball after ntp-4.4.0 will be named `ntp-dev-4.5.0.tar.gz`.

Syntax
: `Protocol_Version.Release_Version.Point_Version[Release_Tags]`

Point Version
: An increasing number indicates a Point (i.e. incremental) Release.
: * The `-stable` release series point releases are used for bug fixes.
: * The `-dev` (development) release series point releases are incremental snapshot releases which checkpoint the development process.

Release Tags
: `[Special][Status]`

Special
: Tags not described here may be used for internal projects.

Status
: For `-stable`, one of:
: * `-beta` followed by an increasing number indicates a Beta release
: * `-RC` followed by an increasing number indicates a Release Candidate 

For `-dev`:
: * `-RC` indicating a Release Candidate 

Stable vs Development Releases
: * Stable releases have an even Release number
: * Development releases have an odd Release number 

**Examples**

<pre>
ntp-4.3.142  NTP Protocol 4 v3.142 (development snapshot release)
ntp-4.4.0    NTP Protocol 4 v4.0   (stable release, version 4 at patch level 0 - ie, with no patches)
ntp-4.4.2    NTP Protocol 4 v4.2   (stable release, version 4 with 2 patches)
</pre>

* * *

#### ntp-4.2.2 thru ntp-4.2.8 (current)

The following release numbering scheme was implemented with the release of ntp-4.2.2 on June 6, 2006.

Syntax
: `Protocol_Version.Major_Version.Minor_Version[Release_Tags]`

Release Tags
: `[Point][Special][Release Candidate]`

Point
: * The letter `p` followed by an increasing number indicates a Point (i.e. incremental) Release.
: * The `-stable` release series point releases are used for bug fixes.
: * The `-dev` (development) release series point releases are incremental snapshot releases which checkpoint the development process.

Special
: Tags not described here may be used for internal projects.

Release Candidate
: The string `-RC` followed by an increasing number indicates a Release Candidate.

Stable vs Development Releases
: * Stable releases have an even Minor Release number
: * Development releases have an odd Minor Release number 

**Examples**

<pre>
4.2.7p142  NTP Protocol 4 v2.7.142 (developement snapshot release)
4.2.6p3    NTP Protocol 4 v2.6.3   (stable release)
4.2.2      NTP Protocol 4 v2.2     (stable release)
</pre>

* * *

#### Prior to 06-Jun-2006

Syntax
: `Protocol_Version.Minor_Version.Release_Tag`

Release Tags
: The tag is optional an is the patch / bug fix number.

* `0-69` for releases on the A.B.C series.
* `70-79` for alpha releases of the A.B+1.0 series.
* `80+` for beta releases of the A.B+1.0 series.

Additional following this number indicates that this is an interim release.

Interim releases almost always have a `C` portion consisting of a number followed by an increasing letter, optionally followed by `-rcX`, where `X` is an increasing number. The `-rcX` indicates a Release Candidate.

Release Tag examples:
: * `4.1.0`: A production release from the ntp-stable repository.
: * `4.1.0b-rc1`: A release candidate for 4.1.1 from the ntp-stable repository.
: * `4.1.71`: An alpha release of 4.20 from the ntp-dev repository.

The goal of this scheme is to produce version numbers that collate properly with the output of the `ls` command.