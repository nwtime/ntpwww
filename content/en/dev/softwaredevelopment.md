---
title: "NTP Software Development"
description: "Developer instructions for using the NTP bug tracker, obtaining source code, building code, and using the BitKeeper client."
type: archives
date: 2019-02-12
---

#### Table of Contents

* [Bugzilla](#bugzilla)
* [NTP Source Code](#ntp-source-code)
* [Tools Needed to Build from a Repository](#tools-needed-to-build-from-a-repository)
* [Using the BitKeeper Client](#using-the-bitkeeper-client)

* * *

#### Bugzilla

Tracking of NTP bugs or enhancement requests is done using Bugzilla, an open-source bug tracking system developed by the the Mozilla team. Our Bugzilla server is located at https://bugs.ntp.org/. Users are encouraged to create an account and to report bugs or suggest enhancements. 

* * *

#### NTP Source Code

The NTP source is maintained in two branches. The `-stable` branch, which has an even release number, and a `dev`, or master branch, which has an odd release number.

The NTP repository and branches are published at https://bk.ntp.org.

* * *

#### Tools Needed to Build from a Repository

To build from a repository you must have the following tools installed:

* `autoconf` - Version 2.61 or later. We use the latest version.
* `automake` - Version 1.11 or later. We use the latest version.
* `libtool` - Version 1.5.something (this is a guess - we use something recent).
* `lynx` - Any version. We use this to generate the COPYRIGHT file. 

The following tools are only needed if you are planning to hack on the `.def` files which produce our command-line parsing and our generated documentation. Almost nobody will ever need these:

* `autogen` - Version 5.18.5 or later. We are currently using 5.18.5.
* `guile` - needed by autogen. 

The instructions above assume your computer already has basic developer tools on it. If that is not the case (for example, many Linux distributions do not include developer tools, libraries, or headers by default), you will need to have a proper developer toolchain installed as well.

For some Linux distributions, these tools can be loaded with something like:

`apt-get build-dep ntp`

* * *

#### Using the BitKeeper Client

The NTP Project uses the open-source BitKeeper product.

You can get pre-compiled or source tarballs from https://www.bitkeeper.org/download.html.

More information is available to NTP Project Committers.

Once you have installed BitKeeper, you can clone the NTP repositories using the following commands:

For the ntp-stable repository:

`bk clone bk://bk.ntp.org/ntp-stable`

For the ntp-dev repository:

`bk clone bk://bk.ntp.org/ntp-dev`

Once you have obtained the sources, `cd` to the directory the repository was downloaded to and run `./bootstrap` to generate the `configure` and `Makefile.in` files.

For information about hacking on the codebase, please see [MaintainerIssues](https://support.ntp.org/Dev/MaintainerIssues).

You can keep your `bk` repository up to date by running this command in the repository directory:

`bk pull -v`

For help on any `bk` command (e.g. `clone`), use `bk clone --help`.