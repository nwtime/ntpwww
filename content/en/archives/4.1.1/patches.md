---
title: "Patching Procedures"
type: archives
---

![gif](/archives/pic/alice38.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/%7emills/pictures.html)

The Mad Hatter needs patches.

* * *

A distribution so widely used as this one eventually develops numerous barnacles as the result of [porting](/archives/4.1.1/porting) to new systems, idiosyncratic new features and just plain bugs. In order to help keep order and make maintenance bearable, we ask that proposed changes to the distribution be submitted in the following form.

1.  Please submit patches to [bugs@mail.ntp.org](mailto:bugs@mail.ntp.org) in the form of either unified-diffs (<tt>diff -u</tt>) or context-diffs (<tt>diff -c</tt>).
2.  Please include the **output** from <tt>config.guess</tt> in the description of your patch. If <tt>config.guess</tt> does not produce any output for your machine, please fix that, too!
3.  Please base the patch on the root directory of the distribution. The preferred procedure here is to copy your patch to the root directory and mumble

    `patch -p <your_patch>`

4.  Please avoid patching the RCS subdirectories; better yet, clean them out before submitting patches.
5.  If you have whole new files, as well as patches, wrap the files and patches in a shell script. If you need to compress it, use either GNU <tt>gzip</tt> or the stock Unix <tt>compress</tt> utility.
6.  Don't forget the documentation that may be affected by the patch. Send us patches for the <tt>./htm</tt> files as well.
7.  We would be glad to include your name, electric address and descriptive phrase in the [Copyright](/archives/4.1.1/copyright) page, if you wish.

Prior to ntp3-5.83 (releases up to and including ntp3.5f) a complete patch history back to the dark ages was kept in the <tt>./patches</tt> directory, which might have been helpful to see if the same problem occurred in another port, etc. Patches were saved in that directory with file name in the form <tt>patch._nnn_</tt>, where _nnn_ was approaching 200. All patches in that directory have been made; so, if yours was there, it was in the distribution.

Since we have been getting multiple patches for some bugs, plus many changes are implemented locally, no two maintainers here use the same tools, and since we're not using any bug-tracking software or even source code control, there is currently no tracking of specific changes.

The best way to see what's changed between two distributions is to run a <tt>diff</tt> against them.

Thanks for your contribution and happy chime.
