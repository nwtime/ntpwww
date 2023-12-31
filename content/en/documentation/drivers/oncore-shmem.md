---
title: "Motorola ONCORE - The Shared Memory Interface"
description: "An overview of the shared memory interface used by the Motorola Oncore GPS receiver."
type: archives
---

#### Table of Contents

*   [Introduction](/documentation/drivers/oncore-shmem/#introduction)
*   [Activating the Interface](/documentation/drivers/oncore-shmem/#activating-the-interface)
*   [Storage of Messages in Shared Memory](/documentation/drivers/oncore-shmem/#storage-of-messages-in-shared-memory)
*   [Opening the Shared Memory File](/documentation/drivers/oncore-shmem/#opening-the-shared-memory-file)
*   [Accessing the data](/documentation/drivers/oncore-shmem/#accessing-the-data)
*   [Examples](/documentation/drivers/oncore-shmem/#examples)

* * *

#### Introduction

In NMEA mode, the Oncore GPS receiver provides the user with the same information as other GPS receivers. In BINARY mode, it can provide a lot of additional information.

In particular, you can ask for satellite positions, satellite health, signal levels, the ephemeris and the almanac, and you can set many operational parameters. In the case of the VP, you can get the pseudorange corrections necessary to act as a DGPS base station, and you can see the raw satellite data messages themselves.

When using the Oncore GPS receiver with NTP, this additional information is usually not available since the receiver is only talking to the oncore driver in NTPD. To make this information available for use in other programs, (say graphic displays of satellites positions, plots of SA, etc.), a shared memory interface (SHMEM) has been added to the `refclock_oncore` driver on those operating systems that support shared memory.

To make use of this information you will need an Oncore Reference Manual for the Oncore GPS receiver that you have. The Manual for the VP only exists as a paper document, the UT+/GT+/M12 manuals are available at [Synergy](https://synergy-gps.com/motorola/).

This interface was written by [Poul-Henning Kamp](mailto:phk@FreeBSD.org), and modified by Reg Clemens. The interface is known to work in FreeBSD, Linux, and Solaris.

* * *

#### Activating the Interface

Although the Shared Memory Interface will be compiled into the Oncore driver on those systems where Shared Memory is supported, to activate this interface you must include a `STATUS` or `SHMEM` line in the `/etc/ntp.oncore` data file that looks like

<code>STATUS \<_file_name_></code>

or

<code>SHMEM \<_file_name_></code>

Thus a line like

`SHMEM /var/adm/ntpstats/ONCORE`

would be acceptable. This file name will be used to access the Shared Memory.

In addition, one the two keywords `Posn2D` and `Posn3D` can be added to see `@@Ea` records containing the 2D or 3D position of the station (see below). Thus to activate the interface, and see 3D positions, something like

`SHMEM /var/adm/ntpstats/ONCORE`

`Posn3D`

would be required.

* * *

#### Storage of Messages in Shared Memory

With the shared memory interface, the oncore driver (`refclock_oncore`) allocates space for all of the messages that it is configured to receive, and then puts each message in the appropriate slot in shared memory as it arrives from the receiver. Since there is no easy way for a client program to know when the shared memory has been updated, a sequence number is associated with each message, and is incremented when a new message arrives. With the sequence number it is easy to check through the shared memory segment for messages that have changed.

The Oncore binary messages are kept in their full length, as described in the Reference manual, that is everything from the `@@` prefix thru the <code>\<checksum>\<CR>\<LF></code>.

The data starts at location ONE of SHMEM (NOT location ZERO).

The messages are stacked in a series of variable length structures, that look like

<pre>        struct message {
                u_int   length;
                u_char  sequence;
                u_char  message[length];
        }
</pre>

if something like that were legal. That is, there are two bytes (caution, these may NOT be aligned with word boundaries, so the field needs to be treated as a pair of `u_char`), that contains the length of the next message. This is followed by a `u_char` sequence number, that is incremented whenever a new message of this type is received. This is followed by `length` characters of the actual message.

The next structure starts immediately following the last char of the previous message (no alignment). Thus, each structure starts a distance of `length+3` from the previous structure.

Following the last structure, is a `u_int` containing a zero length to indicate the end of the data.

The messages are recognized by reading the headers in the data itself, viz `@@Ea` or whatever.

There are two special cases.

1. The almanac takes a total of 34 submessages all starting with `@@Cb`. 35 slots are allocated in shared memory. Each `@@Cb` message is initially placed in the first of these locations, and then later it is moved to the appropriate location for that submessage. The submessages can be distinguished by the first two characters following the `@@Cb` header, and new data is received only when the almanac changes.

2. The `@@Ea` message contains the calculated location of the antenna, and is received once per second. However, when in timekeeping mode, the receiver is normally put in 0D mode, with the position fixed, to get better accuracy. In 0D mode no position is calculated.

When the SHMEM option is active, and if one of `Posn2D` or `Posn3D` is specified, one `@@Ea` record is hijacked each 15s, and the receiver is put back in 2D/3D mode so the current location can be determined (for position determination, or for tracking SA). The timekeeping code is careful NOT to use the time associated with this (less accurate) 2D/3D tick in its timekeeping functions.

Following the initial `@@Ea` message are 3 additional slots for a total of four. As with the almanac, the first gets filled each time a new record becomes available, later in the code, the message is distributed to the appropriate slot. The additional slots are for messages containing 0D, 2D and 3D positions. These messages can be distinguished by different bit patterns in the last data byte of the record.

* * *

#### Opening the Shared Memory File

The shared memory segment is accessed through a file name given on a **SHMEM** card in the `/etc/ntp.oncore` input file. The following code could be used to open the Shared Memory Segment:

<pre>        char *Buf, *file;
        int size, fd;
        struct stat statbuf;

        file = "/var/adm/ntpstats/ONCORE";  /* the file name on my ACCESS card */
        if ((fd=open(file, O_RDONLY)) < 0) {
                fprintf(stderr, "Cant open %s\n", file);
                exit(1);
        }

        if (stat(file, &statbuf) < 0) {
                fprintf(stderr, "Cant stat %s\n", file);
                exit(1);
        }

        size = statbuf.st_size;
        if ((Buf=mmap(0, size, PROT_READ, MAP_SHARED, fd, (off_t) 0)) < 0) {
                fprintf(stderr, "MMAP failed\n");
                exit(1);
        }
</pre>

* * *

#### Accessing the data

The following code shows how to get to the individual records.

<pre>        void    oncore_msg_Ea(), oncore_msg_As(), oncore_msg_Bb();

        struct Msg {
            char         c[5];
            unsigned int seq;
            void         (*go_to)(uchar *);
        };

        struct Msg Hdr[] = { {"@@Bb", 0, &oncore_msg_Bb},
                             {"@@Ea", 0, &oncore_msg_Ea},
                             {"@@As", 0, &oncore_msg_As}};

        void
        read_data()
        {
            int     i, j, k, n, iseq, jseq;
            uchar   *cp, *cp1;

            for(cp=Buf+1; (n = 256*(*cp) + *(cp+1)) != 0;  cp+=(n+3)) {
                for (k=0; k < sizeof(Hdr)/sizeof(Hdr[0]);  k++) {
                    if (!strncmp(cp+3, Hdr[k].c, 4)) {      /* am I interested? */
                        iseq = *(cp+2);
                        jseq = Hdr[k].seq;
                        Hdr[k].seq = iseq;
                        if (iseq > jseq) {              /* has it changed? */
                            /* verify checksum */
                            j = 0;
                            cp1 = cp+3;             /* points to start of oncore response */
                            for (i=2; i < n-3; i++)
                                j ^= cp1[i];
                            if (j == cp1[n-3]) {    /* good checksum */
                                    Hdr[k].go_to(cp1);
                            } else {
                                fprintf(stderr, "Bad Checksum for %s\n", Hdr[k].c);
                                break;
                            }
                        }
                    }
                }
                if (!strncmp(cp+3, "@@Ea", 4))
                    cp += 3*(n+3);
                if (!strncmp(cp+3, "@@Cb", 4))
                    cp += 34*(n+3);
            }
        }

        oncore_msg_Bb(uchar *buf)
        {
                /* process Bb messages */
        }

        oncore_msg_Ea(uchar *buf)
        {
                /* process Ea messages */
        }

        oncore_msg_As(uchar *buf)
        {
                /* process As messages */
        }
</pre>

The structure Hdr contains the Identifying string for each of the messages that we want to examine, and the name of a program to call when a new message of that type is arrives. The loop can be run every few seconds to check for new data.

* * *

#### Examples

There are two complete examples available. The first plots satellite positions and the station position as affected by SA, and keeps track of the mean station position, so you can run it for periods of days to get a better station position. The second shows the effective horizon by watching satellite tracks. The examples will be found in the [GNU-zipped tar file](/reflib/software/OncorePlot.tar.gz).

Try the new interface, enjoy.