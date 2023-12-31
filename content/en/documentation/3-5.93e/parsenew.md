---
title: "How to build new PARSE clocks"
type: archives
noindex: true 
sitemap_exclude: true
---

Here is an attempt to sketch out what you need to do in order to add another clock to the parse driver: Currently the implementation is being cleaned up - so not all information in here is completely correct. Refer to the included code where in doubt.

* * *

Prerequisites:

*   Does the system you want the clock connect to have the include files termio.h or termios.h ? (You need that for the parse driver)

What to do:

Make a conversion module (<code>libparse/clk_\*.c</code>)

1.  What is the time code format ?

    Find year, month, day, hour, minute, second, status (synchronised or not), possibly time zone information (you need to give the offset to UTC). You will have to convert the data from a string into a <code>struct clocktime</code>:

<pre>      struct clocktime                /* clock time broken up from time code */
              {
        	long day;
        	long month;
        	long year;
        	long hour;
        	long minute;
        	long second;
        	long usecond;
        	long utcoffset;       /* in seconds */
        	time_t utcoffset;     /* true utc time instead of date/time */
        	long flags;           /* current clock status */
              };
</pre>

Conversion is usually simple and straight forward. For the flags following values can be OR'ed together:

<pre>     PARSEB_ANNOUNCE           switch time zone warning (informational only)
             PARSEB_POWERUP            no synchronisation - clock confused (must set then)
             PARSEB_NOSYNC             timecode currently not confirmed (must set then)
                                       usually on reception error when there is still a
                                       chance the the generated time is still ok.

             PARSEB_DST                DST in effect (informational only)
             PARSEB_UTC                timecode contains UTC time (informational only)
             PARSEB_LEAPADD            LEAP addition warning (prior to leap happening - must set when imminent)
        			       also used for time code that do not encode the
        			       direction (as this is currently the default).
             PARSEB_LEAPDEL            LEAP deletion warning (prior to leap happening - must set when imminent)
             PARSEB_ALTERNATE          backup transmitter (informational only)
             PARSEB_POSITION           geographic position available (informational only)
             PARSEB_LEAPSECOND         actual leap second (this time code is the leap
                                       second - informational only)
</pre>

These are feature flags denoting items that are supported by the clock:

<pre>     PARSEB_S_LEAP             supports LEAP - might set PARSEB_LEAP
             PARSEB_S_ANTENNA          supports ANTENNA - might set PARSEB_ALTERNATE
             PARSEB_S_PPS              supports PPS time stamping
             PARSEB_S_POSITION         supports position information (GPS)
</pre>

If the <code>utctime</code> field is non-zero this value will be take as time code value. This allows for conversion routines that already have the utc time value. The <code>utctime</code> field gives the seconds since Jan 1st 1970, 0:00:00. The <code>useconds</code> field gives the respective <code>usec</code> value. The fields for date and time (down to second resolution) will be ignored.

Conversion is done in the <code>cvt_\*</code> routine in <code>parse/clk_\*.c</code> files, look in them for examples. The basic structure is:

<pre>     struct clockformat <yourclock>_format = {
               lots of fields for you to fill out (see below)
             };

             static cvt_<yourclock>()
               ...
             {
               if (<I do not recognize my time code>) {
                 return CVT_NONE;
               } else {
                 if (<conversion into clockformat is ok>) {
                   <set all necessary flags>;
                   return CVT_OK;
                 } else {
                   return CVT_FAIL|CVT_BADFMT;
                 }
               }
</pre>

The <code>struct clockformat</code> is the interface to the rest of the parse driver - it holds all information necessary for finding the clock message and doing the appropriate time stamping.

<pre>struct clockformat
        {
          u_long (*input)();
          /* input routine - your routine - cvt_<yourclock> */
          u_long (*convert)();
          /* conversion routine - your routine - cvt_<yourclock> */
          /* routine for handling RS232 sync events (time stamps) - usually sync_simple */
          u_long (*syncpps)(); 
          /* PPS input routine - usually pps_one */
          void           *data;
          /* local parameters - any parameters/data/configuration info your conversion
             routine might need */
          char           *name;
          /* clock format name - Name of the time code */
          unsigned short  length;
          /* maximum length of data packet for your clock format */
          u_long   flags;
         /* information for the parser what to look for */
        };
</pre>

The above should have given you some hints on how to build a <code>clk_\*.c</code> file with the time code conversion. See the examples and pick a clock closest to yours and tweak the code to match your clock.

In order to make your <code>clk_\*.c</code> file usable a reference to the clockformat structure must be put into <code>parse_conf.c</code>.

2. TTY setup and initialisation/configuration will be done in <code>ntpd/refclock_parse.c</code>.

   Find out the exact tty settings for your clock (baud rate, parity, stop bits, character size, ...) and note them in terms of <code>termio\*.h</code> c_cflag macros.

   In <code>ntpd/refclock_parse.c</code> fill out a new the struct clockinfo element (that allocates a new "IP" address - see comments) (see all the other clocks for example).

<pre>   struct clockinfo
             {
              u_long  cl_flags;             /* operation flags (io modes) */
        	 PARSE_F_PPSPPS       use loopfilter PPS code (CIOGETEV)
        	 PARSE_F_PPSONSECOND  PPS pulses are on second
        	 usually flags stay 0 as they are used only for special setups

            void  (*cl_poll)();           /* active poll routine */
                 The routine to call when the clock needs data sent to it in order to
                 get a time code from the clock (e.g. Trimble clock)

            int   (*cl_init)();           /* active poll init routine */
                 The routine to call for very special initializations.

            void  (*cl_event)();          /* special event handling (e.g. reset clock) */
                 What to do, when an event happens - used to re-initialize clocks on timeout.

            void  (*cl_end)();            /* active poll end routine */
                 The routine to call to undo any special initialisation (free memory/timers)

            void   *cl_data;              /* local data area for "poll" mechanism */
                 local data for polling routines

            u_fp    cl_rootdelay;         /* rootdelay */
                 NTP rootdelay estimate (usually 0)

        	     u_long  cl_basedelay;         /* current offset - unsigned l_fp
                                                      fractional part (fraction) by
                                                      which the RS232 time code is
                                                      delayed from the actual time. */

            u_long  cl_ppsdelay;          /* current PPS offset - unsigned l_fp fractional
                 time (fraction) by which the PPS time stamp is delayed (usually 0)
           part */

            char   *cl_id;                /* ID code (usually "DCF") */
                 Refclock id - (max 4 chars)

            char   *cl_description;       /* device name */
                 Name of this device.

            char   *cl_format;            /* fixed format */
                 If the data format cann not ne detected automatically this is the name
        	 as in clk_*.c clockformat.

            u_char  cl_type;              /* clock type (ntp control) */
                 Type if clock as in clock status word (ntp control messages) - usually 0

            u_long  cl_maxunsync;         /* time to trust oscillator after losing synch
          */
                 seconds a clock can be trusted after losing synchronisation.

            u_long  cl_speed;             /* terminal input & output baudrate */
            u_long  cl_cflag;             /* terminal io flags */
            u_long  cl_iflag;             /* terminal io flags */
            u_long  cl_oflag;             /* terminal io flags */
            u_long  cl_lflag;             /* terminal io flags */
                 termio*.h tty modes.

            u_long  cl_samples;           /* samples for median filter */
            u_long  cl_keep;              /* samples for median filter to keep */
                 median filter parameters - smoothing and rejection of bad samples
          } clockinfo[] = {
          ...,<other clocks>,...
          { < your parameters> },
          };
</pre>

Well, this is very sketchy, I know. But I hope it helps a little bit. The best way is to look which clock comes closest to your and tweak that code.

Two sorts of clocks are used with parse. Clocks that automatically send their time code (once a second) do not need entries in the poll routines because they send the data all the time. The second sort are the clocks that need a command sent to them in order to reply with a time code (like the Trimble clock).

For questions: [kardel@acm.org](mailto:%20kardel@acm.org).

Please include an exact description on how your clock works. (initialisation, TTY modes, strings to be sent to it, responses received from the clock).