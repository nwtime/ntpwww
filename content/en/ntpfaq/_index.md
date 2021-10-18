---
title: "The NTP FAQ and HOWTO"
type: "archives"
---

**Understanding and using the Network Time Protocol (A first try on a non-technical Mini-HOWTO and FAQ on NTP)**

Last update: 2006-11-21

* * *

#### Table of Contents

1. [About this Document](#1-about-this-document)  
1.1 [Credits](#11-credits)
2. [Time, what Time?](/ntpfaq/ntp-s-time)  
2.1. [What is Time?](/ntpfaq/ntp-s-time#21-what-is-time)  
2.2. [What is UTC?](/ntpfaq/ntp-s-time#22-what-is-utc)  
2.3. [Is UTC the same as GMT?](/ntpfaq/ntp-s-time#23-is-utc-the-same-as-gmt)  
2.4. [What happens during a Leap Second?](/ntpfaq/ntp-s-time#24-what-happens-during-a-leap-second)  
3. [How do Computer Clocks work?](/ntpfaq/ntp-s-sw-clocks)  
3.1 [Bits and Registers](/ntpfaq/ntp-s-sw-clocks/#31-bits-and-registers)  
3.2 [Making Time go on](/ntpfaq/ntp-s-sw-clocks-tick)  
3.3 [Clock Quality](/ntpfaq/ntp-s-sw-clocks-quality)  
3.3.1 [Frequency Error](/ntpfaq/ntp-s-sw-clocks/#331-frequency-error)  
3.3.1.1. [How bad is a Frequency Error of 500 PPM?](/ntpfaq/ntp-s-sw-clocks-quality/#3311-how-bad-is-a-frequency-error-of-500-ppm)  
3.3.1.2. [What is the Frequency Error of a good Clock?](/ntpfaq/ntp-s-sw-clocks-quality/#3312-what-is-the-frequency-error-of-a-good-clock)  
4. [What is NTP?](/ntpfaq/ntp-s-def)  
4.1. [Overview](/ntpfaq/ntp-s-def#41-overview)  
4.1.1. [What is NTP?](/ntpfaq/ntp-s-def/#411-what-is-ntp)  
4.1.2. [What is SNTP?](/ntpfaq/ntp-s-def/#412-what-is-sntp)  
4.1.3. [Why should Time be synchronized?](/ntpfaq/ntp-s-def/#413-why-should-time-be-synchronized)  
4.1.4. [What are the basic features of NTP?](/ntpfaq/ntp-s-def/#414-what-are-the-basic-features-of-ntp)  
4.1.5. [Which Operating Systems are supported?](/ntpfaq/ntp-s-def/#415-which-operating-systems-are-supported)  
4.1.6. [How many NTP servers are available in the Internet?](/ntpfaq/ntp-s-def/#416-how-many-ntp-servers-are-available-in-the-internet)  
4.1.7. [Which version of NTP should I use?](/ntpfaq/ntp-s-def/#417-which-version-of-ntp-should-i-use)  
4.1.8. [What's the difference between xntp and ntp?](/ntpfaq/ntp-s-def/#418-whats-the-difference-between-xntp-and-ntp)  
4.1.9. [What's new in Version 4?](/ntpfaq/ntp-s-def/#419-whats-new-in-version-4)  
4.1.10. [Where is NTP specified?](/ntpfaq/ntp-s-def/#4110-where-is-ntp-specified)  
4.2. [History](/ntpfaq/ntp-s-def-hist)  
4.3. [Implementations and Platforms](/ntpfaq/ntp-s-def-impl)  
4.3.1. [Official Providers](/ntpfaq/ntp-s-def-impl/#431-official-providers)  
4.3.1.1. [Can I get some Standard Time using NTP?](/ntpfaq/ntp-s-def-impl/#4311-can-i-get-some-standard-time-using-ntp)  
4.3.1.2. [Which Protocols are supported by the Reference Implementation?](/ntpfaq/ntp-s-def-impl/#4312-which-protocols-are-supported-by-the-reference-implementation)  
4.3.2. [UNIX Systems](/ntpfaq/ntp-s-def-impl/#432-unix-systems)  
4.3.2.1. [Which Implementations are available for UNIX?](/ntpfaq/ntp-s-def-impl/#4321-which-implementations-are-available-for-unix)  
4.3.3. [Microsoft Windows](/ntpfaq/ntp-s-def-impl/#433-microsoft-windows)  
4.3.3.1. [Is there any built-in Implementation?](/ntpfaq/ntp-s-def-impl/#4331-is-there-any-built-in-implementation)  
4.3.3.2. [Are there any other Implementations?](/ntpfaq/ntp-s-def-impl/#4332-are-there-any-other-implementations)  
4.3.4. [VMS](/ntpfaq/ntp-s-def-impl/#434-vms)  
4.3.4.1. [Which Implementations are available for VMS?](/ntpfaq/ntp-s-def-impl/#4341-which-implementations-are-available-for-vms)  
5. [How does it work?](/ntpfaq/ntp-s-algo/)  
5.1. [Basic Concepts](/ntpfaq/ntp-s-algo/#basic-concepts)  
5.1.1. [Time References](/ntpfaq/ntp-s-algo#511-time-references)  
5.1.1.1. [What is a reference clock?](/ntpfaq/ntp-s-algo/#5111-what-is-a-reference-clock)  
5.1.1.2. [How will NTP use a reference clock?](/ntpfaq/ntp-s-algo/#5112-how-will-ntp-use-a-reference-clock)  
5.1.1.3. [How will NTP know about Time Sources?](/ntpfaq/ntp-s-algo/#5113-how-will-ntp-know-about-time-sources)  
5.1.1.4. [What happens if the Reference Time changes?](/ntpfaq/ntp-s-algo/#5114-what-happens-if-the-reference-time-changes)  
5.1.1.5. [What is a stratum 1 Server?](/ntpfaq/ntp-s-algo/#5115-what-is-a-stratum-1-server)  
5.1.2. [Time Exchange](/ntpfaq/ntp-s-algo/#512-time-exchange)  
5.1.2.1. [How is Time synchronized?](/ntpfaq/ntp-s-algo/#5121-how-is-time-synchronized)  
5.1.2.2. [Which Network Protocols are used by NTP?](/ntpfaq/ntp-s-algo/#5122-which-network-protocols-are-used-by-ntp)  
5.1.2.3. [How is Time encoded in NTP?](/ntpfaq/ntp-s-algo/#5123-how-is-time-encoded-in-ntp)  
5.1.2.4. [When are the Servers polled?](/ntpfaq/ntp-s-algo/#5124-when-are-the-servers-polled)  
5.1.3. [Performance](/ntpfaq/ntp-s-algo/#513-performance)  
5.1.3.1. [How accurate will my Clock be?](/ntpfaq/ntp-s-algo/#5131-how-accurate-will-my-clock-be)  
5.1.3.2. [How frequently will the System Clock be updated?](/ntpfaq/ntp-s-algo/#5132-how-frequently-will-the-system-clock-be-updated)  
5.1.3.3. [How frequently are Correction Values updated?](/ntpfaq/ntp-s-algo/#5133-how-frequently-are-correction-values-updated)  
5.1.3.4. [How reliable are those Error-Estimates?](/ntpfaq/ntp-s-algo/#5134-how-reliable-are-those-error-estimates)  
5.1.3.5. [What is the Limit for the Number of Clients?](/ntpfaq/ntp-s-algo/#5135-what-is-the-limit-for-the-number-of-clients)  
5.1.4. [Robustness](/ntpfaq/ntp-s-algo/#514-robustness)  
5.1.4.1. [What is the stratum?](/ntpfaq/ntp-s-algo/#5141-what-is-the-stratum)  
5.1.4.2. [How are Synchronization Loops avoided?](/ntpfaq/ntp-s-algo/#5142-how-are-synchronization-loops-avoided)  
5.1.5. [Tuning](/ntpfaq/ntp-s-algo/#515-tuning)  
5.1.5.1. [What is the allowed range for minpoll and maxpoll?](/ntpfaq/ntp-s-algo/#5151-what-is-the-allowed-range-for-minpoll-and-maxpoll)  
5.1.5.2. [What is the best polling Interval?](/ntpfaq/ntp-s-algo/#5152-what-is-the-best-polling-interval)  
5.1.6. [Operating System Clock Interface](/ntpfaq/ntp-s-algo/#516-operating-system-clock-interface)  
5.1.6.1. [How will NTP discipline my Clock?](/ntpfaq/ntp-s-algo/#5161-how-will-ntp-discipline-my-clock)  
5.2. [The Kernel Discipline](/ntpfaq/ntp-s-algo-kernel)  
5.2.1. [Basic Functionality](/ntpfaq/ntp-s-algo-kernel/#521-basic-functionality)  
5.2.1.1. [What is special about the Kernel Clock?](/ntpfaq/ntp-s-algo-kernel/#5211-what-is-special-about-the-kernel-clock)  
5.2.1.2. [Does my Operating System have the Kernel Discipline?](/ntpfaq/ntp-s-algo-kernel/#5212-does-my-operating-system-have-the-kernel-discipline)  
5.2.1.3. [How can I verify the Kernel Discipline?](/ntpfaq/ntp-s-algo-kernel/#5213-how-can-i-verify-the-kernel-discipline)  
5.2.2. [Alternatives](/ntpfaq/ntp-s-algo-kernel/#522-alternatives)  
5.2.2.1. [Should the Kernel Discipline be used?](/ntpfaq/ntp-s-algo-kernel/#5221-should-the-kernel-discipline-be-used)  
5.2.3. [Monitoring](/ntpfaq/ntp-s-algo-kernel/#523-monitoring)  
5.2.3.1. [What are the individual monitoring values about?](/ntpfaq/ntp-s-algo-kernel/#5231-what-are-the-individual-monitoring-values-about)  
5.2.4. [PPS Processing](/ntpfaq/ntp-s-algo-kernel/#524-pps-processing)  
5.2.4.1. [What is PPS Processing?](/ntpfaq/ntp-s-algo-kernel/#5241-what-is-pps-processing)  
5.2.4.2. [How is PPS Processing related to the Kernel Discipline?](/ntpfaq/ntp-s-algo-kernel/#5242-how-is-pps-processing-related-to-the-kernel-discipline)  
5.2.4.3. [What does hardpps() do?](/ntpfaq/ntp-s-algo-kernel/#5243-what-does-hardpps-do)  
   5.3. [NTP in real Life](/ntpfaq/ntp-s-algo-real)  
   5.4. [Encryption](/ntpfaq/ntp-s-algo-crypt)  
   5.4.1. [The Basics of Autokey](#the-basics-of-autokey)

6. [Configuration of xntpd](/ntpfaq/ntp-s-config)  
   6.1. [Basic Configuration](#basic-configuration)  
   6.1.1. [Recommended Minimum](#recommended-minimum)  
   6.1.2. [Running an isolated Network](#running-an-isolated-network)  
   6.1.3. [Recommended Goodies](#recommended-goodies)  
   6.1.4. [Miscellaneous Hints](#miscellaneous-hints)  
   6.2. [Advanced Configuration](/ntpfaq/ntp-s-config-adv)  
   6.2.1. [Server Selection](#server-selection)  
   6.2.2. [Authentication](#authentication)  
   6.2.3. [Broadcasting, Multicasting, and Manycasting](#broadcasting-multicasting-and-manycasting)  
   6.2.4. [PPS Synchronization](#pps-synchronization)  
   6.2.5. [Automatic Configuration](#automatic-configuration)  
   6.2.6. [Offering Time Service](#offering-time-service)  
   6.3. [Various Tricks](/ntpfaq/ntp-s-config-tricks)  
   6.4. [Compatibility](/ntpfaq/ntp-s-compat)  
   6.4.1. [The Kernel PLL](#the-kernel-pll)

7. [Reference Clocks](/ntpfaq/ntp-s-refclk)  
   7.1. [Products](#products)

8. [Troubleshooting](/ntpfaq/ntp-s-trouble)  
   8.1. [Monitoring](#monitoring)  
   8.2. [General Issues](/ntpfaq/ntp-s-trbl-general)  
   8.2.1. [Messages](#messages)  
   8.3. [Specific Products](/ntpfaq/ntp-s-trbl-spec)  
   8.3.1. [PC Hardware](#pc-hardware)  
   8.3.2. [FreeBSD](#freebsd)  
   8.3.3. [Irix](#irix)  
   8.3.4. [Linux](#linux)  
   8.3.5. [Macintosh](#macintosh)  
   8.3.6. [Oncore Compatibles](#oncore-compatibles)  
   8.3.7. [Solaris](#solaris)  
   8.3.8. [Sun Hardware](#sun-hardware)  
   8.3.9. [Trimble Clocks](#trimble-clocks)  
   8.3.10. [TrueTime](#truetime)  
   8.3.11. [Windows/NT Family](#windows-nt-family)  
   8.4. [Reporting Bugs](/ntpfaq/ntp-s-trbl-bug-reports)
9. [Background and Related Information](/ntpfaq/ntp-s-related)  
   9.1. [GPS](#gps)  
   9.1.1. [Selective Availability revisited](#selective-availability-revisited)
10. [Common Terms and Acronyms](/ntpfaq/ntp-g-all)
 
> This document tries to explain the most basic features of NTP, and to answer many frequently asked questions. The intention is to help the average user to get a quick start with the official implementation of NTP. Technical issues and mathematics are avoided where possible. Instead the most common questions are tried to be answered, enabling everybody to get a working configuration.

All we do here is invent games to pass the time.
: John O' Donohue

* * *

#### 1. About this Document

Edited by:
: Ulrich Windl
: Dale R. Worley
: David Dalton, Hewlett-Packard  
: Marc Martinec, Josef Stefan Institute  
: Jamova 39  
: SI-1000 Ljubljana,  
: Slovenia

**Note from the editor:** This document is not as complete as it should be, but I decided to forward it to a wider audience. Any contributions are welcome. Most incomplete sections are marked with `XXX`. 

Copyright &copy; 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006 Ulrich Windl, et al. (see credits)

**Copyright**

The material in this document is covered by the respective contributor's copyright. © Copyright 1999 - 2005, by the contributors and editors of this document. For details see the list of editors and authors.

All editors and contributors (non-exclusively) grant a perpetual, irrevocable, and royalty free license to distribute this document under the terms of the ACRONYM General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This document is distributed in the hope that it will be useful, but _WITHOUT ANY WARRANTY_; without even the implied warranty of _MERCHANTABILITY_ or _FITNESS FOR A PARTICULAR PURPOSE_. See the GNU General Public License for more details.

If you don't already have the GNU General Public License at hand, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

* * *

This section tries to answer questions about the document itself. So we could call it Meta-FAQ. If you like, you can call it preface or foreword as well.

This document is intended for beginners as well as advanced users that are looking for for advice. However, basic skills in system administration are required to enjoy this tour. True experts on the subject will probably prefer the original documentation that comes with the software, or correct me where I'm wrong.

The impatient may want to go directly to [Section 2](#time-what-time) where fundamentals of timekeeping are discussed. The next section, [Section 3](#how-do-computer-clocks-work), introduces clocks that are implemented using computers. If you are reading sequentially, you should be ready for the section that presents NTP, ([Section 4](#what-is-ntp).

At that point focus is moving from a more theoretical treatment of the subject to practical aspects, starting with [Section 5](#how-does-it-work). Then in [Section 6](#configuration-of-xntpd) we are going into practice, namely configuration of the NTP software. The following section ([Section 7](#reference-clocks) will talk about reference clocks.

Real life is talked about in [Section 8](#troubleshooting) where procedures, tips and tricks for troubleshooting are presented. For the curious, [Section 9](#background-and-related-information) will provide further information and references to such. Finally, there is a [glossary](#common-terms-and-acronyms) with some terms explained.

Those who are still reading sequentially are asked to try some of the numerous hyperlinks found not only at the top and bottom of each section. If you got lost, you can always to back to the beginning where the table of contents is.

1. [Updating the FAQ](#1-updating-the-faq)  
   1.1.1. [Where can I get a new version of this document?](#111-where-can-i-get-a-new-version-of-this-document)  
   1.1.2. [When will a new version of this document be available?](#112-when-will-a-new-version-of-this-document-be-available)
2. [Naming](#naming)  
   1.2.1. [Why is this Document named FAQ?](#121-why-is-this-document-named-faq)  
   1.2.2. [Why is this Document named HOWTO?](#122-why-is-this-document-named-howto)
3. [Policies](#policies)  
   1.3.1. [Why can't I find information about ... in this FAQ?](#131-why-cant-i-find-information-about-in-this-faq)  
   1.3.2. [Where should a new Entry be put?](#132-where-should-a-new-entry-be-put)
4. [Making Contributions](#making-contributions)  
   1.4.1. [Why should I contribute?](#141-why-should-i-contribute)  
   1.4.2. [How can I contribute?](#142-how-can-i-contribute)  
   1.4.3. [In what format should I send contributions?](#143-in-what-format-should-i-send-contributions)  
   1.4.4. [Where should I send Contributions?](#144-where-should-i-send-contributions)  
   1.4.5. [I contributed to this FAQ, but my name is not mentioned anywhere. What's wrong?](#145-i-contributed-to-this-faq-but-my-name-is-not-mentioned-anywhere-whats-wrong)  
   1.4.6. [Why SGML and DocBook?](#146-why-sgml-and-docbook)  
   1.4.7. [How can I process the SGML source file?](#147-how-can-i-process-the-sgml-source-file)
5. [Appearance](#appearance)  
   1.5.1. [I don't like the look of the FAQ. What can I do?](#151-i-dont-like-the-look-of-the-faq-what-can-i-do)  
   1.5.2. [Which Browser is required to read this?](#152-which-browser-is-required-to-read-this)  
   1.5.3. [Why are Graphics stored in PNG Format?](#153-why-are-graphics-stored-in-png-format)  
   1.5.4. [Why are some Fonts that huge?](#154-why-are-some-fonts-that-huge)  
   1.5.5. [Why are there no Frames?](#155-why-are-there-no-frames)  
   1.5.6. [Why isn't there fancy Script Code?](#156-why-isnt-there-fancy-script-code)

* * *

#### 1. Updating the FAQ

#### 1.1.1 Where can I get a new version of this document?

The following procedure, developed for the UNIX operating system, should provide you with the current version of this document:

1.  Make sure you have a working version of CVS for your operating system, and that you can make connections to the Internet.
    If you are going to update an existing version, you may directly jump to step 5.
2.  For convenience let's set a variable in the shell using either `set FAQREPO=:pserver:anoncvs@www.ntp.org:/cvs/ntp` for the C shell, or `FAQREPO=:pserver:anoncvs@www.ntp.org:/cvs/ntp` for POSIX compatible shells.
3.  Log in to the NTP repository using `cvs -d $FAQREPO login`. The password is `anoncvs`. This will allow further commands.
4.  Create a subdirectory with all the files using `cvs -d $FAQREPO checkout ntpfaq`. Please consult the documentation on CVS for details and available options.
5.  To save time and bandwidth when updating, simply change to the directory containing the FAQ and type `cvs update`. That command will update your files according to the repository.

Please note that checking out the CVS sources will provide the SGML sources as well as the HTML pages. I cannot make a statement about what will be available via HTTP, but I expect that only the HTML files are there, and listing the directory will not work.

* * *

#### 1.1.2. When will a new version of this document be available?

I edit this document in my spare time. My spare time is quite rare. Therefore I rely on contributions to improve this work (see [Q: 1.4.2.](#142-how-can-i-contribute). Feel free to contact me if you want to make a contribution.

I hope to update this document as soon as important new stuff is available. The same applies for severe bug fixes.

* * *

#### 2. Naming

#### 1.2.1.Why is this Document named FAQ?

This document tries to answer frequently asked questions (FAQs) that can not (at least virtually) be answered easily from the standard documentation.

* * *

#### 1.2.2. Why is this Document named HOWTO?

In addition to just answering questions that users had, this document also tries to give a gentle introduction and guidelines to the newcomer. The authors believe that it's better to use NTP correctly right from the start rather than fixing all the problems after they occur.

"Gentle" in the paragraph above means "not too technical" and "not too theoretical". However some basic, non-trivial understanding of real-life is required at several points, so please accept these deviations from the goal.

* * *

#### 3. Policies

#### 1.3.1. Why can't I find information about ... in this FAQ?

Unless it simply has not been written yet, there may be other reasons:

1.  The editors don't want to copy documentation that is publicly available already. This is especially true for standards, specifications and manuals. The editors think that referring is better than copying. The intention is to avoid redundancy while saving labour at the same time.

2.  Either the problem or the solution is too vague to document it. This is true for very special configurations that are not at all common. After all, we want to answer _frequently_ asked questions here.

* * *

#### 1.3.2. Where should a new Entry be put?

The answer to this question is quite delicate! The guidelines are probably these:

* Try to understand the existing structure of the document.
* If there are similar entries there already, see where the new one fits best. Usually it's right near the existing one, or in a corresponding section. Possibly it makes sense to create a new section or division.

* * *

#### 4. Making Contributions

#### 1.4.1. Why should I contribute?

In "the good old times" the Internet was a valuable source of information, and people were happy to share their knowledge. These days, however, people think of E-Commerce, how to make money.

I started writing this FAQ not to make money, but to have a reference to refer to. Thus I hope I'll be able to provide the needed information to more people more quickly. Unfortunately I do not know everything. So if you have solved some problem that may be of interest to other people as well, please share your experience.

* * *

#### 1.4.2. How can I contribute?

Contributions are very much appreciated. Depending on your possibilities you can:

1.  Tell me about some error or incomplete information given. I call it a "minor contribution". If you want to be listed in the hall of fame (also called credits, just tell me when contributing. If you prefer anonymous contributions, they are welcome just the same.
2.  You can suggest an addition consisting of a question together with its answer. I call this a "major contribution". Major contributions are definitely worth being listed as author in the header of the document if you like. Of course you can downgrade your contribution to plain credits or nothing if you prefer.
    Contributions are accepted in any format, but I prefer plain US-ASCII or ISO-8859-1. If you can avoid it, don't send files in some text processing format.
3.  Supplying a valid patch against the source of this document will make the most appreciated contribution. This allows you to be listed as co-author. As before, you can downgrade your contribution as you like. For details see [In what format should I send contributions?](143-in-what-format-should-i-send-contributions).

* * *

#### 1.4.3. In what format should I send contributions?

This document is most likely not written in the format you are seeing. The document source is written in SGML (Structure Generalized Markup Language ISO-8879) using the DocBook DTD (Document Type Definition). Therefore the source document has a rather fixed structure, much unlike HTML. See also [Q: 1.4.6.](#146-why-docbook).

So the essence is: Try to learn writing documents conforming to the DocBook DTD. In the meantime I'll do my best converting your input to the proper format (See the more general discussion in [How can I contribute?](#142-how-can-i-contribute).

* * *

#### 1.4.4. Where should I send Contributions?

The sources controlled by CVS can be updated by various people, but contributions should be sent to the currently defined editor. Every HTML file contains a `mailto:` hyperlink to the editor. Many browsers allow sending comments to the author that way. Another method is to visit the file `ChangeLog` found where the sources are (See [Q: 1.1.1.](#111-where-can-i-get-a-new-version-of-this-document).

* * *

#### 1.4.5. I contributed to this FAQ, but my name is not mentioned anywhere. What's wrong?

Probably the fault of the editor. Maybe he thought you don't want to be listed, or he simply forgot. [Section 1.1](#11-credits) shows the names the editor was aware of.

* * *

#### 1.4.6. Why SGML and DocBook?

Well, I'm not getting paid for my work, so I tried to learn something new while writing this piece of documentation. SGML is one of the dinosaurs of information technology, an endangered species that may be killed by the more agile XML. So maybe feeding dinosaurs is just cool.

DocBook is just another monster that is used by even larger monsters like HP for documentation. Definitely it's also animal, because it's used by O'Reilly & Associates, Inc.[<span class="footnote">[2]</span>](#FTN.AEN423) Finally it's an open technology: All specifications (and many tools) are freely available.

Specific output formats are generated by applying style sheets within a framework consisting of [James Clark](NTP-a-faq.htm#AU-JJC)'s JADE (James' DSSSL Engine) and [Norman Walsh](NTP-a-faq.htm#AU-NDW)'s Modular DocBook Stylesheets. While this document probably will be used mostly in HTML format, other formats like TeX and RTF (Rich Text Format) can be generated as well.

* * *

#### 1.4.7. How can I process the SGML source file?

I'm editing this document with the Linux GNU operating system. Most Linux distributions come with the required tools. In my distribution these tools are in the following packages:

* `emaca` - GNU Emacs, the editor

* `docbook_4` - The DocBook DTD and related files

* `docbook-dsssl-stylesheets` - The modular style sheets for DocBook

* `openjade` - OpenJade, the follow-up to Jade by James Clark's DSSSL-Engine for SGML Documents

* `opensp` - The OpenJade Group's SGML and XML Parsing Tools

* `psgml` - Provides SGML knowledge for Emacs. I would not survive without that!

You might want to have a look at these packages as well: `docbook-css-stylesheets`, `docbook-tdg` (DocBook: The Definitive Guide).

So if you want to edit and validate any changes you are making, try to get the equivalent tools for your operating system as well. If you like the pain, you can use these tools on Microsoft Windows<sup>TM</sup> as well.

Basically the command to generate HTML files is `jade -t sgml -d NTP-FAQ.dsl#html NTP-FAQ.sgml` where the environment contains these special settings:

<pre>SGML_CATALOG_FILES=SGML_CATALOG_FILES=/var/lib/sgml/CATALOG.docbook_4
SGML_SEARCH_PATH=/usr/share/sgml/docbook/dsssl-stylesheets/html</pre>

* * *

#### 5. Appearance

#### 1.5.1. I don't like the look of the FAQ. What can I do?

You are lucky: Actually the source of the FAQ uses no formatting rules at all, even the DSSSL code relies on HTML classes and style sheets to do the rendering. All properties like borders, colours, and font attributes are taken from a cascading style sheet (CSS).

In practice, this means you don't have to change the HTML source to change the appearance. Instead simply provide your favourite user style sheet to do the formatting. If you prefer no fancy attributes at all, just empty the `docbook.css` file.[<span class="footnote">[3]</span>](#FTN.AEN497)

If the output looks extraordinarily odd, you may have a broken HTML browser. See also [Q: 1.5.2.](#152-which-browser-is-required-to-read-this).

If you think colours are inconsistently chosen, please make a suggestion for future improvement. If you dislike single colours or combinations thereof, please suggest a change. Doing that job is more an art than a science.

I'm aware that some elements are not rendered the best possibly way. As I don't waste much time (at least not even more time) with rendering of elements, I strongly rely on [Norman Walsh](NTP-a-faq.htm#AU-NDW)'s competence in JADE programming. I'm hoping that things will improve over time.

**Example 1. Style Sheet Entry**

<pre>*.ACRONYM { color: #5838d0 }</pre>

This entry causes all HTML elements with attribute `class="LITERAL"` (i.e. all acronyms) to be output in a kind of royal blue. The example shown does not use official WWW colours. It's strongly recommended to use official colours for portability.

If your browser goes mad, and your vendor allows you to report bugs, feel free to report the problems to them. If you think I went mad, feel free to tell me too ;-)

* * *

#### 1.5.2. Which Browser is required to read this?

This FAQ is intended to be read with the famous "any browser". It means that standard HTML is used, omitting any fancy extensions. Still individual browsers may implement different subsets of the standard.

I usually test the output using the following browsers in Linux (roughly ordered by fanciness):

* [Mozilla](http://www.mozilla.org/releases/)
* Amaya
* w3m - (text-oriented, supports tables)
* Emacs/W3 - (text-oriented, supports tables)
* Lynx - (text-oriented, `vi`-like)</td>

* * *

#### 1.5.3. Why are Graphics stored in PNG Format?

The popular GIF format supported by many browsers relies on a compression algorithm that is patented, and the owner of the patent wants to receive money from everyone making GIF files. PNG (Portable Network Graphics) uses a different algorithm for compression and does not require payment.

* * *

#### 1.5.4. Why are some Fonts that huge?

Netscape Navigator</span> (e.g. version 4.74) seems to have a bug with relative font scaling. Try to disable using stylesheets, or try a recent Mozilla. See also [Q: 1.5.1.](NTP-a-faq.htm#Q-META-CSS-STYLE).

* * *

#### 1.5.5. Why are there no Frames?

Sorry, I have my daily frustration with frames, so I don't want any more. Despite of that I think that most frames just consume valuable space on either your screen or on your print-out.

* * *

#### 1.5.6. Why isn't there fancy Script Code?

Currently scripting is neither fast nor portable, so I don't use it.

* * *

#### 1.1. Credits

If you contributed to this FAQ, and you could not find your name elsewhere, this is where it should be.

This is an alphabetical list of contributors:

* [Michael Andres](mailto:ma@suse.de)
* [Tom Van Baak](mailto:tvb@veritas.com)
* [Wolfgang Barth](mailto:wob@swobspace.rhein.de)
* [Lyle Batema](mailto:Lyle_Batema@Trimble.COM)
* [Eric W. Bates](mailto:ericx@vineyard.net)
* [Brian Bergstrand](mailto:brianb@mac.com)
* [Peter Boettcher](mailto:boettcher@ll.mit.edu)
* [Marc Brett](mailto:Marc.Brett@westgeo.com)
* [Bill Broadley](mailto:bill@sphere.math.ucdavis.edu)
* [Martin Burnicki](mailto:martin.burnicki@meinberg.de)
* [Jonathan A. Buzzard](mailto:jonathan@buzzard.org.uk)
* [chunkeey](mailto:chunkeey@web.de)
* James Clark
* [David Craggs](mailto:dcraggs@gotadsl.co.uk)
* David Dalton
* John DeDourek
* [Sven Dietrich](mailto:Sven_Dietrich@Trimble.COM)
* Casper H. Dik
* John K. Doyle, Jr.
* [Daniel Drucker](mailto:ddrucker@easylink.com)
* [Arthur Darren Dunham](mailto:add@netcom.com)
* [Philippe Eveque](mailto:philippe_eveque@grenoble.hp.com)
* [Jürgen Georgi](mailto:georgi@BelWue.DE)
* [Tim Granger](mailto:Tim.Granger@cl.cam.ac.uk)
* [Benjamin Greenwald](mailto:beng@lcs.mit.edu)
* [James & Charlotte Griffin](mailto:agriffin@cpcug.org)
* [Richard M. Hambly](mailto:rick@cnssys.com)
* [John Hay](mailto:John.Hay@mikom.csir.co.za)
* [Per Hedeland ](mailto:per@erix.ericsson.se)
* [Kees Hendrikse](mailto:kees@echelon.nl)
* [Martin Herbener](mailto:mherbene@kde.state.ky.us)
* [Doug Hogarth](mailto:DougHo@niceties.com)
* Andrew Hood
* [Theo Jakobus](mailto:jakobus@iaf.fhg.de)
* [Nicholas Jenkins](mailto:njenkins@mad.scientist.com)
* [Poul-Henning Kamp](mailto:phk@freebsd.dk)
* [James Kirkpatrick](mailto:jimkirk@uwyo.edu)
* Wolfgang Klische
* [Steve Kostecke](mailto:kostecke@ntp.org)
* [Markus Kuhn](mailto:mgk25@cl.cam.ac.uk)
* [Anand Kumria](mailto:akumria@acm.org)
* Judah Levine
* [Mark Martinec](mailto:mark.martinec@ijs.si)
* [Terje Mathisen](mailto:Terje.Mathisen@hda.hydro.com)
* [Frank Mayhar](mailto:frank@exit.com)
* [Professor David L. Mills](mailto:mills@udel.edu)
* [Nelson Minar](mailto:nelson@media.mit.edu)
* [Jeffrey Mogul](mailto:mogul@pa.dec.com)
* [Hal Murray](mailto:hmurray@suespammers.org)
* [Dirk A. Niggemann](mailto:dirk-n@dircon.co.uk)
* [Mike Nolan](mailto:mikeynolan@my-deja.com)
* [Johan Fredrik Øhman](mailto:johanfo@essay.org)
* [Rainer Orth](mailto:ro@TechFak.Uni-Bielefeld.DE)
* Don Payette
* [William R. Pennock](mailto:bill.pennock@transquest.com)
* [Bruce M. Penrod](mailto:bpenrod@nbn.com)
* [Nicolai E M Plum](mailto:nicolai@esperi.org)
* [John Sager](mailto:jcs@zoo.bt.co.uk)
* Hans P. Reiser
* [Thomas Schulz](mailto:schulz@adi.com)
* [Michael Sinatra](mailto:msinatra@uclink4.berkeley.edu)
* [Greg Smith](mailto:Greg.Smith@ci.seattle.wa.us)
* [Johan Swenker](mailto:Johan.Swenker@HetNet.NL)
* [Vladimir Smotlacha](mailto:vs@cesnet.cz)
* [Harlan Stenn](mailto:stenn@whimsy.udel.edu)
* [David J. Taylor](mailto:david-taylor@blueyonder.co.uk)
* [George Terrone](mailto:gterrone@itsco.com)
* Thomas Tornblom
* [Scott Tuttle](mailto:scott@crampinhand.com)
* [Brian Utterback](mailto:Brian.Utterback@East.Sun.COM)
* Gilles Vollant
* [Norman Walsh](mailto:ndw@nwalsh.com)
* [David Woolley](mailto:david@djwhome.demon.co.uk)
* [Dale R. Worley](mailto:worley@shell01.TheWorld.com)

#### Notes

[1]</span>](NTP-a-faq.htm#FTN-VOLATILE-URL)

Although specified, there's no guarantee that the URI shown will be still valid in the future. Important resource locations should not change if possible. If they still do, share your complaints with the webmaster of the site, and forward the new or corrected URL to the editor.

[2]</span>](NTP-a-faq.htm#AEN423)</td>

There's a book by [Norman Walsh](NTP-a-faq.htm#AU-NDW) called _DocBook: The definitive Guide_ (ISBN 1-56592-580-7). If you are really interested, you should have at least a look at the online version found at http://docbook.org.

[3]</span>](NTP-a-faq.htm#AEN497)</td>

Of course, this will only work if you have a local copy of the files.