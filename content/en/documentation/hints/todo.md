---
title: "Todo"
type: archives
noindex: true 
sitemap_exclude: true
---

Ulrich Windl <Ulrich.Windl@rz.uni-regensburg.de>:
	
: Any change in a source file in the lib directory causes all files to be recompiled (because the objects are removed). Add a better rule for `make` to update the library. Maybe just remove `-rm -f $?`.
