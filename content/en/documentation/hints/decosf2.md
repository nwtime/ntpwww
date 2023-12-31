---
title: "DEC OSF/1 V2.0 Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Problems with DEC OSF/1 V2.0

Compilation using `gcc` fails with `ntp_config.c`. The problem is an apparent error in the `/usr/include/sys/procset.h` and `/usr/include/sys/wait.h` include files.

<pre>
cowbird:/usr/include/sys# diff -c wait.h.orig wait.h
*** wait.h.orig Tue Feb 22 02:41:38 1994
--- wait.h      Thu Aug 25 14:52:57 1994
***************
*** 298,304 ****
  #else

  _BEGIN_CPLUSPLUS
! extern int waitid(idtype_t, id_t, siginfo_t *, int);
  _END_CPLUSPLUS
  #endif /* _NO_PROTO */

--- 298,304 ----
  #else

  _BEGIN_CPLUSPLUS
! extern int waitid(idtype_t, pid_t, siginfo_t *, int);
  _END_CPLUSPLUS
  #endif /* _NO_PROTO */

cowbird:/usr/include/sys# diff -c procset.h.orig procset.h
*** procset.h.orig      Tue Feb 22 02:41:44 1994
--- procset.h   Thu Aug 25 14:43:52 1994
***************
*** 86,95 ****
                                 */

        idtype_t p_lidtype;     /* The id type for the left set. */
!       id_t p_lid;             /* The id for the left set. */

        idtype_t p_ridtype;     /* The id type of for right set. */
!       id_t p_rid;             /* The id of the right set. */
  } procset_t;

--- 86,95 ----
                                 */

        idtype_t p_lidtype;     /* The id type for the left set. */
!       pid_t p_lid;            /* The id for the left set. */

        idtype_t p_ridtype;     /* The id type of for right set. */
!       pid_t p_rid;            /* The id of the right set. */
  } procset_t;
</pre>

Also, if using `gcc` from the freeware disk, either replace `syscall.h` in the directory `/usr/local/lib/gcc-lib/alpha-dec-osf1/2.3.3/include` or replace with a link to `/usr/include/sys/syscall.h`.
