---
title: "md5 - generate message digest"
type: archives
--- 

#### Table of Contents

*  [Synopsis](/archives/3-5.93e/md5cert/#synopsis)
*  [Description](/archives/3-5.93e/md5cert/#description)
*  [Options](/archives/3-5.93e/md5cert/#options)

* * *

#### Synopsis

<tt>md5 [ -0123456789 ] [ -h] _file_</tt>

* * *

#### Description

This program generates the message digest of the given _file_ using the RSA Message Digest 5 (MD5) and other selected algorithms. If _file_ is not given, the program uses the standard input.

* * *

#### Options

<dt><tt>-0123456789</tt></dt>

Select algorithm from the following list  
<tt>-0</tt> null  
<tt>-1</tt> MD5  
<tt>-2</tt> SNEFRU  
<tt>-3</tt> CRC32  
<tt>-4</tt> CRC16  
<tt>-5</tt> MD4  
<tt>-6</tt> MD2  
<tt>-7</tt> SHA  
<tt>-8</tt> HAVAL  
<tt>-9</tt> null

<dt><tt>-h</tt></dt>

Display the result in hex; the default is base-64.