---
title: "8. Troubleshooting"
type: "archives"
---

If you have set up your software, you usually want to know whether it works. This section discusses topics related to configuration, monitoring, troubleshooting, and debugging of <span class="PRODUCTNAME">xntp</span>.

#### 8.1. Monitoring

Without any doubt, troubleshooting requires monitoring. Somehow you must find out that something is wrong before you wonder how to fix it.

8.1.1. [If I think my NTP server is working fine, what could I do to confirm this?](#if-i-think-my-ntp-server-is-working-fine-what-could-i-do-to-confirm-this)  
8.1.2. [How do I use peerstats and loopstats?](#how-do-i-use-peerstats-and-loopstats)  
8.1.3. [How can I see the Time Difference between Client and Server?](#how-can-i-see-the-time-difference-between-client-and-server)  
8.1.4. [What does 257 mean as value for reach?](#what-does-257-mean-as-value-for-reach)  
8.1.5. [What can I use these statistics files for?](#what-can-i-use-these-statistics-files-for)

* * *

#### 8.1.1. If I think my NTP server is working fine, what could I do to confirm this?

One of the quickest commands to verify that `ntpd` is still up and running as desired is `ntpq -p`. That command will show all peers used and configured together with their corner performance data.

As the above command requires periodic invocation to monitor the performance, it is also recommended to enable statistic files in `ntpd`. See also [Q: 8.1.2.](NTP-s-trouble.htm#Q-TRB-MON-STATFIL) and [Q: 8.1.3.](NTP-s-trouble.htm#Q-TRB-MON-TIME-DIF).

* * *

#### 8.1.2. How do I use peerstats and loopstats?

I use the following lines in `/etc/ntp.conf` to enable loopfilter statistics (See the line starting with `statistics`). New files are created every day, and the current files are available as `/var/log/ntp/peers` and `/var/log/ntp/loops`. Older files are archived as <code>/var/log/ntp/peers*YYYYMMDD*</code> and <code>/var/log/ntp/loops.*YYYYMMDD*</code>:

<pre>statistics loopstats
statsdir /var/log/ntp/
filegen peerstats file peers type day link enable
filegen loopstats file loops type day link enable</pre>

Usually I only monitor the `loops` file. Table 3 lists the individual fields of each file. I'll show examples for `peerstats` and `loopstats` for version 3 and 4 following the table.

**Table 3. Statistic Files**

| File Type | Version | List of Fields|
| ----- | ----- | ----- |
| `loopstats` | 3 | day, second, offset, drift compensation, polling interval |
| | 4 | day, second, offset, drift compensation, estimated error, stability, polling interval |
| `peerstats` | 3 | day, second, address, status, offset, delay, dispersion |
| | 4 | day, second, address, status, offset, delay, dispersion, skew (variance) |

**Example: Peerstats version 3**
<pre>50560 73386.259 127.127.8.1 9695 -0.001186 0.00000 0.00961
50560 73450.260 127.127.8.1 9695 -0.002161 0.00000 0.00528
50560 73514.261 127.127.8.1 9695 -0.003087 0.00000 0.00333</pre>

**Example: Peerstats version 4**
<pre>50560 73386.259 -0.001186 16.8701 6
50560 73450.260 -0.002161 16.8619 6
50560 73514.374 -0.003087 16.8501 6
50560 73578.295 -0.003959 16.8350 6</pre>

**Example: Loopstats version 3**
<pre>51801 71273.247 127.0.0.1 2194 0.000000609 0.000000000 0.000001023 0.000000000
51801 71273.248 127.127.22.1 9714 0.000001290 0.000000000 0.000000000 0.000000018
51801 71304.037 127.127.8.1 9434 0.000000879 0.000000000 0.000000000 0.000000032
51801 71339.248 127.127.22.1 9714 -0.000000076 0.000000000 0.000000000 0.000000028
51801 71368.038 127.127.8.1 9434 -0.000000129 0.000000000 0.000000000 0.000000046</pre>

**Example: Loopstats version 4**
<pre>51801 71143.245 0.000000594 17.526474 0.000000021 0.019386 6
51801 71273.248 0.000000609 17.556229 0.000000025 0.022432 6
51801 71404.250 -0.000000036 17.538376 0.000000023 0.021379 6</pre>

* * *

#### 8.1.3. How can I see the Time Difference between Client and Server?

(By [Terje Mathisen](NTP-a-faq.htm#AU-TM)) Normally `ntpd` maintains an estimate of the time offset. To inspect these offsets, you can use the following commands:

*   `ntpq -p` will display the offsets for each reachable server in milliseconds (`ntpdc -p` uses seconds instead).
*   `ntpdc -c loopinfo` will display the combined offset in seconds, as seen at the last poll. If supported, `ntpdc -c kerninfo` will display the current remaining correction, just as `ntptime` does.

The first can be used to check what `ntpd` thinks the offset and jitter is currently, relative to the preferred/current server, the second can tell you something about the estimated offset/error all the way to the stratum 1 source. [Q: 8.1.2.](NTP-s-trouble.htm#Q-TRB-MON-STATFIL) describes a way to collect such data automatically.

If a PPS source is active (see [Q: 5.2.4.1.](NTP-s-algo-kernel.htm#Q-ALGO-KERNEL-PPS) and [Section 6.2.4](NTP-s-config-adv.htm#S-CONFIG-ADV-PPS)), the offset displayed with the second choice is updated periodically, maybe every second.

Sometimes things are wrong and you may want to compare time offsets directly. An easy way is to use <code>ntpdate -d _server_</code> to compare the local system time with the time taken from <code>_server_</code>.

* * *

#### 8.1.4. What does 257 mean as value for reach?

(Inspired by [Martin Burnicki](NTP-a-faq.htm#AU-MBU)) The value displayed in column `reach` is octal, and it represents the _reachability register_. One digit in the range of `0` to `7` represents three bits. The initial value of that register is `0`, and after every poll that register is shifted left by one position. If the corresponding time source sent a valid response, the rightmost bit is set.

During a normal startup the registers values are these: `0`, `1`, `3`, `7`, `17`, `37`, `77`, `177`, `377`

Thus `257` in the dual system is `10101111`, saying that two valid responses were not received during the last eight polls. However, the last four polls worked fine.

* * *

#### 8.1.5. What can I use these statistics files for?

You can do a lot of useful things with statistic files before you remove them. For example there is a utility named `summary.pl` written in Perl to compute mean values and standard deviation (RMS) from the loopfilter and peer statistics. It will also show exceptional conditions found in these files. Here's a short example output (you could have used `summary.pl --dir=/var/log/ntp --start=19990518 --end=19990604`):

<pre>loops.19990518
loop 110, -30+/-36.5, rms 6.7, freq 14.95+/-1.149, var 0.612
loops.19990519
loop 113, -26+/-40.3, rms 6.9, freq 12.95+/-3.240, var 1.378
loops.19990520
loop 107, -7+/-32.0, rms 5.7, freq 13.04+/-3.253, var 1.579
loops.19990522
loop 190, 3+/-18.5, rms 2.9, freq 15.48+/-3.715, var 0.604
loops.19990523
loop 146, -5+/-9.2, rms 1.9, freq 15.77+/-0.716, var 0.305
loops.19990604
loop 73, -27+/-29.8, rms 6.9, freq 16.81+/-0.327, var 0.140</pre>

Still another utility named `plot_summary.pl` can be used to make plots with these summary data. As an alternative you could plot the loopfilter file directly with `gnuplot`[<span class="footnote">[1]</span>](NTP-s-trouble.htm#FTN.AEN5099) using the command `plot "/var/log/ntp/loops"` using 2:3 with linespoints. Figure 6 had been produced with a little more complicated command. It shows `yerrorbars` with the estimated errors for offset and frequency respectively.

**Figure 6. Plot of estimated Offset and Frequency Error (DCF77)**

![](/ntpfaq/loopstat.png)

The reference clock, the antenna, and the computer system were located in an office room without air condition.

Now that we are looking at numbers and graphs, let us compare the data of a GPS clock (using PPS) with a typical low-cost clock (not using PPS). Figure 7 shows a very small offset for the GPS clock. The frequency is continuously adjusted. In comparison, the DCF77 clock shows a high variation for the offset, but the frequency is adjusted less drastically (Figure 6 shows values between those, using a better DCF77 receiver with PPS).

**Figure 7. Comparing Offset and Frequency Error of DCF77 and GPS**

![](/ntpfaq/GPSvsDCF.png)

* * *

#### Notes

[<span class="footnote">[1]</span>](NTP-s-trouble.htm#AEN5099)

"The "GNU" in gnuplot is NOT related to the Free Software Foundation, the naming is just a coincidence (and a long story). Thus gnuplot is not covered by the Gnu copyleft, but rather by its own copyright statement, included in all source code files." (see http://www.cs.dartmouth.edu/gnuplot_info.html)