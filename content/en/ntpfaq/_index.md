---
title: "The NTP FAQ and HOWTO"
description: "This document tries to explain the basic features of NTP, and to answer many frequently asked questions. The intention is to help the average user get a quick start with a working configuation for the official implementation of NTP. Technical issues and mathematics are avoided where possible."
type: "archives"
---

**Understanding and using the Network Time Protocol (A first try on a non-technical Mini-HOWTO and FAQ on NTP)**

* * *

#### Table of Contents

1. [About this Document](#1-about-this-document)  
1.1 [Preface](#11-preface)  
1.2 [Why is this Document named FAQ and HOWTO?](#12-why-is-this-document-named-faq-and-howto)  
1.3 [Where is the source of this document?](#13-where-is-the-source-of-this-document)  
1.4 [Why can't I find information about xyz in this FAQ?](#14-why-cant-i-find-information-about-xyz-in-this-faq)  
1.5 [Where should a new Entry be put?](#15-where-should-a-new-entry-be-put)  
1.6 [Why should I contribute?](#16-why-should-i-contribute)  
1.7 [How can I contribute?](#17-how-can-i-contribute)    
1.8 [I contributed to this FAQ, but my name is not mentioned anywhere. What's wrong?](#18-i-contributed-to-this-faq-but-my-name-is-not-mentioned-anywhere-whats-wrong)  
1.9 [Why are Graphics stored in PNG Format?](#19-why-are-graphics-stored-in-png-format)  
1.10 [Credits](#110-credits)

2. [Time, what Time?](/ntpfaq/ntp-s-time/)  
2.1 [What is Time?](/ntpfaq/ntp-s-time/#21-what-is-time)  
2.2 [What is UTC?](/ntpfaq/ntp-s-time/#22-what-is-utc)  
2.3 [Is UTC the same as GMT?](/ntpfaq/ntp-s-time/#23-is-utc-the-same-as-gmt)  
2.4 [What happens during a Leap Second?](/ntpfaq/ntp-s-time/#24-what-happens-during-a-leap-second)  

3. [How do Computer Clocks work?](/ntpfaq/ntp-s-sw-clocks/)  
3.1 [Bits and Registers](/ntpfaq/ntp-s-sw-clocks/#31-bits-and-registers)  
3.2 [Making Time go on](/ntpfaq/ntp-s-sw-clocks-tick/)  
3.3 [Clock Quality](/ntpfaq/ntp-s-sw-clocks-quality/)  
3.3.1 [Frequency Error](/ntpfaq/ntp-s-sw-clocks-quality/#331-frequency-error)  
3.3.1.1 [How bad is a Frequency Error of 500 PPM?](/ntpfaq/ntp-s-sw-clocks-quality/#3311-how-bad-is-a-frequency-error-of-500-ppm)  
3.3.1.2 [What is the Frequency Error of a good Clock?](/ntpfaq/ntp-s-sw-clocks-quality/#3312-what-is-the-frequency-error-of-a-good-clock)  

4. [What is NTP?](/ntpfaq/ntp-s-def/)  
4.1 [Overview](/ntpfaq/ntp-s-def/#41-overview)  
4.1.1 [What is NTP?](/ntpfaq/ntp-s-def/#411-what-is-ntp)  
4.1.2 [What is SNTP?](/ntpfaq/ntp-s-def/#412-what-is-sntp)  
4.1.3 [Why should Time be synchronized?](/ntpfaq/ntp-s-def/#413-why-should-time-be-synchronized)  
4.1.4 [What are the basic features of NTP?](/ntpfaq/ntp-s-def/#414-what-are-the-basic-features-of-ntp)  
4.1.5 [Which Operating Systems are supported?](/ntpfaq/ntp-s-def/#415-which-operating-systems-are-supported)  
4.1.6 [How many NTP servers are available in the Internet?](/ntpfaq/ntp-s-def/#416-how-many-ntp-servers-are-available-in-the-internet)  
4.1.7 [Which version of NTP should I use?](/ntpfaq/ntp-s-def/#417-which-version-of-ntp-should-i-use)  
4.1.8 [What's the difference between xntp and ntp?](/ntpfaq/ntp-s-def/#418-whats-the-difference-between-xntp-and-ntp)    
4.2. [History](/ntpfaq/ntp-s-def-hist/)  
4.3. [Implementations and Platforms](/ntpfaq/ntp-s-def-impl/)  
4.3.1 [Official Providers](/ntpfaq/ntp-s-def-impl/#431-official-providers)    
4.3.2 [UNIX Systems](/ntpfaq/ntp-s-def-impl/#432-unix-systems)   
4.3.3 [Microsoft Windows](/ntpfaq/ntp-s-def-impl/#433-microsoft-windows)    
   
5. [How does it work?](/ntpfaq/ntp-s-algo/)  
5.1 [Basic Concepts](/ntpfaq/ntp-s-algo/#basic-concepts)  
5.1.1 [Time References](/ntpfaq/ntp-s-algo/#511-time-references)  
5.1.1.1 [What is a reference clock?](/ntpfaq/ntp-s-algo/#5111-what-is-a-reference-clock)  
5.1.1.2 [How will NTP use a reference clock?](/ntpfaq/ntp-s-algo/#5112-how-will-ntp-use-a-reference-clock)  
5.1.1.3 [How will NTP know about Time Sources?](/ntpfaq/ntp-s-algo/#5113-how-will-ntp-know-about-time-sources)  
5.1.1.4 [What happens if the Reference Time changes?](/ntpfaq/ntp-s-algo/#5114-what-happens-if-the-reference-time-changes)  
5.1.1.5 [What is a stratum 1 Server?](/ntpfaq/ntp-s-algo/#5115-what-is-a-stratum-1-server)  
5.1.2 [Time Exchange](/ntpfaq/ntp-s-algo/#512-time-exchange)  
5.1.2.1 [How is Time synchronized?](/ntpfaq/ntp-s-algo/#5121-how-is-time-synchronized)  
5.1.2.2 [Which Network Protocols are used by NTP?](/ntpfaq/ntp-s-algo/#5122-which-network-protocols-are-used-by-ntp)  
5.1.2.3 [How is Time encoded in NTP?](/ntpfaq/ntp-s-algo/#5123-how-is-time-encoded-in-ntp)  
5.1.2.4 [When are the Servers polled?](/ntpfaq/ntp-s-algo/#5124-when-are-the-servers-polled)  
5.1.3 [Performance](/ntpfaq/ntp-s-algo/#513-performance)  
5.1.3.1 [How accurate will my Clock be?](/ntpfaq/ntp-s-algo/#5131-how-accurate-will-my-clock-be)  
5.1.3.2 [How frequently will the System Clock be updated?](/ntpfaq/ntp-s-algo/#5132-how-frequently-will-the-system-clock-be-updated)  
5.1.3.3 [How frequently are Correction Values updated?](/ntpfaq/ntp-s-algo/#5133-how-frequently-are-correction-values-updated)  
5.1.3.4 [What is the Limit for the Number of Clients?](/ntpfaq/ntp-s-algo/#5135-what-is-the-limit-for-the-number-of-clients)  
5.1.4 [Robustness](/ntpfaq/ntp-s-algo/#514-robustness)  
5.1.4.1 [What is the stratum?](/ntpfaq/ntp-s-algo/#5141-what-is-the-stratum)  
5.1.4.2 [How are Synchronization Loops avoided?](/ntpfaq/ntp-s-algo/#5142-how-are-synchronization-loops-avoided)  
5.1.5 [Tuning](/ntpfaq/ntp-s-algo/#515-tuning)  
5.1.5.1 [What is the allowed range for minpoll and maxpoll?](/ntpfaq/ntp-s-algo/#5151-what-is-the-allowed-range-for-minpoll-and-maxpoll)  
5.1.5.2 [What is the best polling Interval?](/ntpfaq/ntp-s-algo/#5152-what-is-the-best-polling-interval)  
5.1.6 [Operating System Clock Interface](/ntpfaq/ntp-s-algo/#516-operating-system-clock-interface)  
5.1.6.1 [How will NTP discipline my Clock?](/ntpfaq/ntp-s-algo/#5161-how-will-ntp-discipline-my-clock)  
5.2. [The Kernel Discipline](/ntpfaq/ntp-s-algo-kernel/)  
5.2.1 [Basic Functionality](/ntpfaq/ntp-s-algo-kernel/#521-basic-functionality)  
5.2.1.1 [What is special about the Kernel Clock?](/ntpfaq/ntp-s-algo-kernel/#5211-what-is-special-about-the-kernel-clock)  
5.2.1.2 [Does my Operating System have the Kernel Discipline?](/ntpfaq/ntp-s-algo-kernel/#5212-does-my-operating-system-have-the-kernel-discipline)  
5.2.1.3 [How can I verify the Kernel Discipline?](/ntpfaq/ntp-s-algo-kernel/#5213-how-can-i-verify-the-kernel-discipline)    
5.2.2 [Monitoring](/ntpfaq/ntp-s-algo-kernel/#522-monitoring/)   
5.2.3 [PPS Processing](/ntpfaq/ntp-s-algo-kernel/#523-pps-processing)  
5.2.3.1 [What is PPS Processing?](/ntpfaq/ntp-s-algo-kernel/#5231-what-is-pps-processing)  
5.2.3.2 [How is PPS Processing related to the Kernel Discipline?](/ntpfaq/ntp-s-algo-kernel/#5232-how-is-pps-processing-related-to-the-kernel-discipline)  
5.2.3.3 [What does hardpps() do?](/ntpfaq/ntp-s-algo-kernel/#5233-what-does-hardpps-do)  
5.3. [NTP in real Life](/ntpfaq/ntp-s-algo-real/)  
5.3.1 [What if I write my own SNTP Server?](/ntpfaq/ntp-s-algo-real/#531-what-if-i-write-my-own-sntp-server)  
5.3.2 [Why should I have more than one clock?](/ntpfaq/ntp-s-algo-real/#532-why-should-i-have-more-than-one-clock)  
5.3.3 [Does the reference time depend on all configured servers, or is it based on which ever responds first?](/ntpfaq/ntp-s-algo-real/#533-does-the-reference-time-depend-on-all-configured-servers-or-is-it-based-on-which-ever-responds-first)  
5.3.4 [What happens during a Leap Second?](/ntpfaq/ntp-s-algo-real/#534-what-happens-during-a-leap-second)  
5.4. [Encryption](/ntpfaq/ntp-s-algo-crypt/)  
5.4.1 [What is Encryption used for in NTP?](/ntpfaq/ntp-s-algo-crypt/#541-what-is-encryption-used-for-in-ntp)  
5.4.1.1 [How is Authenticity verified?](/ntpfaq/ntp-s-algo-crypt/#5411-how-is-authenticity-verified)  
5.4.1.2 [Where are authenticated Messages used in NTP?](/ntpfaq/ntp-s-algo-crypt/#5412-where-are-authenticated-messages-used-in-ntp)  
5.4.1.3 [How is Performance affected by Encryption?](/ntpfaq/ntp-s-algo-crypt/#5413-how-is-performance-affected-by-encryption)  
5.4.2 [The Basics of Autokey](/ntpfaq/ntp-s-algo-crypt/#542-the-basics-of-autokey)  
5.4.2.1 [Authentic and Proventic](/ntpfaq/ntp-s-algo-crypt/#5421-authentic-and-proventic)  
5.4.2.2 [Secure Group and Trusted Host](/ntpfaq/ntp-s-algo-crypt/#5422-secure-group-and-trusted-host)  
5.4.2.3 [Identity Schemes](/ntpfaq/ntp-s-algo-crypt/#5423-identity-schemes)  
5.4.2.4 [Proventic Trail](/ntpfaq/ntp-s-algo-crypt/#5424-proventic-trail)  
5.2.4.5 [Session Keys](/ntpfaq/ntp-s-algo-crypt/#5425-session-keys)

6. [Configuration](/ntpfaq/ntp-s-config/)  
6.1. [Basic Configuration](/ntpfaq/ntp-s-config/#61-basic-configuration)  
6.1.1 [Can't I just run ntpdate?](/ntpfaq/ntp-s-config/#611-cant-i-just-run-ntpdate)  
6.1.2 [Recommended Minimum](/ntpfaq/ntp-s-config/#612-recommended-minimum)  
6.1.2.1 [What is the minimum configuration?](/ntpfaq/ntp-s-config/#6121-what-is-the-minimum-configuration)  
6.1.2.2 [Is the minimum configuration a typical one?](/ntpfaq/ntp-s-config/#6122-is-the-minimum-configuration-a-typical-one)  
6.1.2.3 [What is the correct Pseudo IP Address for my reference clock?](/ntpfaq/ntp-s-config/#6123-what-is-the-correct-pseudo-ip-address-for-my-reference-clock)  
6.1.2.4 [What is a drift file?](/ntpfaq/ntp-s-config/#6124-what-is-a-drift-file)  
6.1.2.5 [Should I use IP addresses or host names?](/ntpfaq/ntp-s-config/#6125-should-i-use-ip-addresses-or-host-names)  
6.1.3 [Running an isolated Network](/ntpfaq/ntp-s-config/#613-running-an-isolated-network)  
6.1.3.1 [Can I use my system clock as reference clock?](/ntpfaq/ntp-s-config/#6131-can-i-use-my-system-clock-as-reference-clock)  
6.1.3.2 [Can I avoid manual time adjustments in a network without reference clock?](/ntpfaq/ntp-s-config/#6132-can-i-avoid-manual-time-adjustments-in-a-network-without-reference-clock)  
6.1.4 [Recommended Goodies](/ntpfaq/ntp-s-config/#614-recommended-goodies)  
6.1.4.1 [How can I configure the amount of logging information?](/ntpfaq/ntp-s-config/#6141-how-can-i-configure-the-amount-of-logging-information)  
6.1.4.2 [How can I speed up initial Synchronization?](/ntpfaq/ntp-s-config/#6142-how-can-i-speed-up-initial-synchronization)  
6.1.4.3 [How do I configure remote administration?](/ntpfaq/ntp-s-config/#6143-how-do-i-configure-remote-administration)  
6.1.4.4 [How do I use authentication keys?](/ntpfaq/ntp-s-config/#6144-how-do-i-use-authentication-keys)  
6.1.4.5 [What are all the different Keys used for?](/ntpfaq/ntp-s-config/#6145-what-are-all-the-different-keys-used-for)  
6.1.4.6 [How do I use autokey?](/ntpfaq/ntp-s-config/#6146-how-do-i-use-autokey)  
6.1.5 [Miscellaneous Hints](/ntpfaq/ntp-s-config/#615-miscellaneous-hints)  
6.1.5.1 [What is the preferred etiquette when synchronizing to a public server?](/ntpfaq/ntp-s-config/#6151-what-is-the-preferred-etiquette-when-synchronizing-to-a-public-server)  
6.1.5.2 [Where can I find public Time Servers?](/ntpfaq/ntp-s-config/#6152-where-can-i-find-public-time-servers)  
6.2. [Advanced Configuration](/ntpfaq/ntp-s-config-adv/)  
6.2.1 [Server Selection](/ntpfaq/ntp-s-config-adv/#621-server-selection)  
6.2.1.1 [What is the rule of thumb for number of servers to synchronize to?](/ntpfaq/ntp-s-config-adv/#6211-what-is-the-rule-of-thumb-for-number-of-servers-to-synchronize-to)  
6.2.1.2 [Should the servers be a mix of primary and secondary servers?](/ntpfaq/ntp-s-config-adv/#6212-should-the-servers-be-a-mix-of-primary-and-secondary-servers)  
6.2.1.3 [How should I provide NTP services for a huge network?](/ntpfaq/ntp-s-config-adv/#6213-how-should-i-provide-ntp-services-for-a-huge-network)  
6.2.2 [Authentication](/ntpfaq/ntp-s-config-adv/#622-authentication)  
6.2.2.1 [Why Authentication?](/ntpfaq/ntp-s-config-adv/#6221-why-authentication)  
6.2.2.2 [How is Authentication applied?](/ntpfaq/ntp-s-config-adv/#6222-how-is-authentication-applied)  
6.2.2.3 [How do I create a key?](/ntpfaq/ntp-s-config-adv/#6223-how-do-i-create-a-key)  
6.2.2.4 [How does Authentication work?](/ntpfaq/ntp-s-config-adv/#6224-how-does-authentication-work)  
6.2.2.5 [Can I add Authentication without restarting ntpd?](/ntpfaq/ntp-s-config-adv/#6225-can-i-add-authentication-without-restarting-ntpd)  
6.2.2.6 [How do I use Public-Key Authentication (autokey)?](/ntpfaq/ntp-s-config-adv/#6226-how-do-i-use-public-key-authentication-autokey)  
6.2.3 [Broadcasting, Multicasting, and Manycasting](/ntpfaq/ntp-s-config-adv/#623-broadcasting-multicasting-and-manycasting)   
6.2.3.1 [How do I configure a Broadcast Server?](/ntpfaq/ntp-s-config-adv/#6231-how-do-i-configure-a-broadcast-server)  
6.2.3.2 [How do I configure a Broadcast Client?](/ntpfaq/ntp-s-config-adv/#6232-how-do-i-configure-a-broadcast-client)  
6.2.3.3 [Why doesn't Broadcasting work with LCL?](/ntpfaq/ntp-s-config-adv/#6233-why-doesnt-broadcasting-work-with-lcl)   
6.2.3.4 [How do I configure Multicast Servers and Clients?](/ntpfaq/ntp-s-config-adv/#6234-how-do-i-configure-multicast-servers-and-clients)    
6.2.3.5 [What is Manycasting?](/ntpfaq/ntp-s-config-adv/#6235-what-is-manycasting)  
6.2.4. [PPS Synchronization](/ntpfaq/ntp-s-config-adv/#624-pps-synchronization)    
6.2.4.1 [Which components are required to use PPS synchronization?](/ntpfaq/ntp-s-config-adv/#6241-which-components-are-required-to-use-pps-synchronization)  
6.2.4.2 [What changes are required in ntp.conf?](/ntpfaq/ntp-s-config-adv/#6242-what-changes-are-required-in-ntpconf)  
6.2.4.3 [How do I verify that everything is working?](/ntpfaq/ntp-s-config-adv/#6243-how-do-i-verify-that-everything-is-working)  
6.2.4.4 [Special Drivers](/ntpfaq/ntp-s-config-adv/#6244-special-drivers)  
6.2.4.4.1 [What is a PPS peer?](/ntpfaq/ntp-s-config-adv/#62441-what-is-a-pps-peer)  
6.2.4.4.2 [How do I use PPS with the Motorola Oncore driver?](/ntpfaq/ntp-s-config-adv/#62442-how-do-i-use-pps-with-the-motorola-oncore-driver)  
6.2.4.4.3 [How do I use PPS with the NMEA driver?](/ntpfaq/ntp-s-config-adv/#62443-how-do-i-use-pps-with-the-nmea-driver)  
6.2.4.5 [What is the PPS API?](/ntpfaq/ntp-s-config-adv/#6245-what-is-the-pps-api)  
6.2.4.6 [What is the shortest Width for a Pulse connected to the DCD Pin of an RS-232 Interface?](/ntpfaq/ntp-s-config-adv/#6246-what-is-the-shortest-width-for-a-pulse-connected-to-the-dcd-pin-of-an-rs-232-interface)  
6.2.5 [Automatic Configuration](/ntpfaq/ntp-s-config-adv/#625-automatic-configuration)  
6.2.5.1 [How can I define the address of an NTP server in a BOOTP reply?](/ntpfaq/ntp-s-config-adv/#6251-how-can-i-define-the-address-of-an-ntp-server-in-a-bootp-reply)  
6.2.5.2 [How do I use information about NTP servers given in a BOOTP reply?](/ntpfaq/ntp-s-config-adv/#6252-how-do-i-use-information-about-ntp-servers-given-in-a-bootp-reply)  
6.2.6 [Offering Time Service](/ntpfaq/ntp-s-config-adv/#626-offering-time-service)  
6.2.6.1 [Is there any way to configure ntpd to attach to a specific Interface?](/ntpfaq/ntp-s-config-adv/#6261-is-there-any-way-to-configure-ntpd-to-attach-to-a-specific-interface)  
6.2.6.2 [Should Access be restricted?](/ntpfaq/ntp-s-config-adv/#6262-should-access-be-restricted)  
6.2.6.3 [What should be done before announcing public NTP service?](/ntpfaq/ntp-s-config-adv/#6263-what-should-be-done-before-announcing-public-ntp-service)  
6.3. [Various Tricks](/ntpfaq/ntp-s-config-tricks/)  
6.3.1 [Mixing Time Protocols](/ntpfaq/ntp-s-config-tricks/#631-mixing-time-protocols)   
6.3.2 [Avoiding Time Steps](/ntpfaq/ntp-s-config-tricks/#632-avoiding-time-steps)    
6.3.3 [Using the Echo Feature in PPS API](/ntpfaq/ntp-s-config-tricks/#633-using-the-echo-feature-in-pps-api)  
6.4. [Compatibility](/ntpfaq/ntp-s-compat/)  
6.4.1 [The Kernel PLL](/ntpfaq/ntp-s-compat/#641-the-kernel-pll)  
6.4.1.1 [How many different kernel models and implementations exist?](/ntpfaq/ntp-s-compat/#6411-how-many-different-kernel-models-and-implementations-exist)  
6.4.1.2 [What's new in each Version?](/ntpfaq/ntp-s-compat/#6412-whats-new-in-each-version)  
6.4.1.3 [Are the individual kernel models compatible?](/ntpfaq/ntp-s-compat/#6413-are-the-individual-kernel-models-compatible)   
6.4.1.4 [Is the Linux implementation different?](/ntpfaq/ntp-s-compat/#6414-is-the-linux-implementation-different)

7. [Reference Clocks](/ntpfaq/ntp-s-refclk/)  
7.1 [What is LCL, the Local Clock?](/ntpfaq/ntp-s-refclk/#71-what-is-lcl-the-local-clock)  
7.2 [GPS Receivers](/ntpfaq/ntp-s-refclk/#72-gps-receivers)  
7.2.1 [What should I know about various GPS Receivers?](/ntpfaq/ntp-s-refclk/#721-what-should-i-know-about-various-gps-receivers)  
7.2.2 [What are PDOP, TDOP, and GDOP?](/ntpfaq/ntp-s-refclk/#722-what-are-pdop-tdop-and-gdop)  
7.2.3 [What is NMEA?](/ntpfaq/ntp-s-refclk/#723-what-is-nmea)  
7.2.4 [What is TSIP?](/ntpfaq/ntp-s-refclk/#724-what-is-tsip)  
7.3 [DCF77 Receivers](/ntpfaq/ntp-s-refclk/#73-dcf77-receivers)  
7.3.1 [What should I know about DCF77 Receivers?](/ntpfaq/ntp-s-refclk/#731-what-should-i-know-about-dcf77-receivers)  
7.3.2 [What can make my DCF77 Receiver fail?](/ntpfaq/ntp-s-refclk/#732-what-can-make-my-dcf77-receiver-fail)  
7.4 [Other Receivers](/ntpfaq/ntp-s-refclk/#74-other-receivers/)  
7.4.1 [What can make my MSF Receiver fail?](/ntpfaq/ntp-s-refclk/#741-what-can-make-my-msf-receiver-fail)  
7.4.2 [How can I find a low-cost Receiver for Low-Frequency Transmissions?](/ntpfaq/ntp-s-refclk/#742-how-can-i-find-a-low-cost-receiver-for-low-frequency-transmissions)   
7.5 [Products](/ntpfaq/ntp-s-refclk/#75-products)  
7.5.1 [Where can I find a reference clock for NTP?](/ntpfaq/ntp-s-refclk/#751-where-can-i-find-a-reference-clock-for-ntp) 

8. [Troubleshooting](/ntpfaq/ntp-s-trouble/)  
8.1 [Monitoring](/ntpfaq/ntp-s-trouble/#81-monitoring)  
8.1.1 [How do I confirm my NTP server is working fine?](/ntpfaq/ntp-s-trouble/#811-how-do-i-confirm-my-ntp-server-is-working-fine)  
8.1.2 [How do I use peerstats and loopstats?](/ntpfaq/ntp-s-trouble/#812-how-do-i-use-peerstats-and-loopstats)  
8.1.3 [How can I see the Time Difference between Client and Server?](/ntpfaq/ntp-s-trouble/#813-how-can-i-see-the-time-difference-between-client-and-server)  
8.1.4 [What does 257 mean as value for reach?](/ntpfaq/ntp-s-trouble/#814-what-does-257-mean-as-value-for-reach)  
8.1.5 [How do I use statistics files?](/ntpfaq/ntp-s-trouble/#815-how-do-i-use-statistics-files)    

8.2. [General Issues](/ntpfaq/ntp-s-trbl-general/)  
8.2.1 [Starting, running, querying](/ntpfaq/ntp-s-trbl-general/#821-starting-running-querying)  
8.2.1.1 [How can I check that ntpd is up and running?](/ntpfaq/ntp-s-trbl-general/#8211-how-can-i-check-that-ntpd-is-up-and-running)  
8.2.1.2 [Why does ntpd only run for about 10 to 20 minutes??](/ntpfaq/ntp-s-trbl-general/#8212-why-does-ntpd-only-run-for-about-10-to-20-minutes)  
8.2.2 [Cabling and Interfacing](/ntpfaq/ntp-s-trbl-general/#822-cabling-and-interfacing)  
8.2.2.1 [Why does my Serial Interface hang when I connect a PPS Signal to DCD?](/ntpfaq/ntp-s-trbl-general/#8221-why-does-my-serial-interface-hang-when-i-connect-a-pps-signal-to-dcd)  
8.2.2.2 [Why is the PPS API only detecting one Edge?](/ntpfaq/ntp-s-trbl-general/#8222-why-is-the-pps-api-only-detecting-one-edge)  
8.2.3 [Exchanging Time](/ntpfaq/ntp-s-trbl-general/#823-exchanging-time)  
8.2.3.1 [Is a remote server providing time?](/ntpfaq/ntp-s-trbl-general/#8231-is-a-remote-server-providing-time)  
8.2.3.2 [My server is up and running, but it is unusable for clients](/ntpfaq/ntp-s-trbl-general/#8232-my-server-is-up-and-running-but-it-is-unusable-for-clients)    
8.2.4 [Cryptography](/ntpfaq/ntp-s-trbl-general/#824-cryptography)  
8.2.4.1 [No time received when using autokey](/ntpfaq/ntp-s-trbl-general/#8241-no-time-received-when-using-autokey)  
8.2.5 [Time Errors](/ntpfaq/ntp-s-trbl-general/#825-time-errors)  
8.2.5.1 [Why does my server change time references quite frequently?](/ntpfaq/ntp-s-trbl-general/#8251-why-does-my-server-change-time-references-quite-frequently)  
8.2.5.2 [My server periodically loses synchronization](/ntpfaq/ntp-s-trbl-general/#8252-my-server-periodically-loses-synchronization)  
8.2.5.3 [Why does my system step several times a day?](/ntpfaq/ntp-s-trbl-general/#8253-why-does-my-system-step-several-times-a-day)  
8.2.6 [Other](/ntpfaq/ntp-s-trbl-general/#826-other)  
8.2.6.1 [How do I set the correct value for tick?](/ntpfaq/ntp-s-trbl-general/#8261-how-do-i-set-the-correct-value-for-tick)   
8.2.6.2 [How do I set the precision?](/ntpfaq/ntp-s-trbl-general/#8262-how-do-i-set-the-precision)   
8.2.6.3 [ntpd periodically opens a dial-out connection. Can I avoid that?](/ntpfaq/ntp-s-trbl-general/#8263-ntpd-periodically-opens-a-dial-out-connection-can-i-avoid-that)  
8.2.6.4 [Any more Hints?](/ntpfaq/ntp-s-trbl-general/#8264-any-more-hints)  
8.2.7 [Errors and Warnings](/ntpfaq/ntp-s-trbl-general/#827-errors-and-warnings)  
8.2.7.1 [ntpq: read: connection refused](/ntpfaq/ntp-s-trbl-general/#8271-ntpq-read-connection-refused)  
8.2.7.2 [127.0.0.1: timed out, nothing received, Request timed out](/ntpfaq/ntp-s-trbl-general/#8272-127001-timed-out-nothing-received-request-timed-out)  
8.2.7.3 [ntpdate: no server suitable for synchronization found](/ntpfaq/ntp-s-trbl-general/#8273-ntpdate-no-server-suitable-for-synchronization-found)   
8.2.7.4 [configure: keyword "precision" unknown, line ignored](/ntpfaq/ntp-s-trbl-general/#8274-configure-keyword-precision-unknown-line-ignored)   
8.2.7.5 [Previous time adjustment didn't complete](/ntpfaq/ntp-s-trbl-general/#8275-previous-time-adjustment-didnt-complete)   
8.2.7.6 [sendto: Overlapped I/O operation is in progress.](/ntpfaq/ntp-s-trbl-general/#8276-sendto-overlapped-io-operation-is-in-progress)

8.3. [Troubleshooting Specific Products](/ntpfaq/ntp-s-trbl-spec/)  
8.3.1 [PC Hardware](/ntpfaq/ntp-s-trbl-spec/#831-pc-hardware)  
8.3.1.1 [How accurate is the CMOS clock?](/ntpfaq/ntp-s-trbl-spec/#8311-how-accurate-is-the-cmos-clock)  
8.3.1.2 [How can I set the CMOS clock?](/ntpfaq/ntp-s-trbl-spec/#8312-how-can-i-set-the-cmos-clock)  
8.3.1.3 [How can I read or write the CMOS clock?](/ntpfaq/ntp-s-trbl-spec/#8313-how-can-i-read-or-write-the-cmos-clock)  
8.3.1.4 [How can SMM affect Interrupt Processing?](/ntpfaq/ntp-s-trbl-spec/#8314-how-can-smm-affect-interrupt-processing)  
8.3.2 [Linux](/ntpfaq/ntp-s-trbl-spec/#832-linux)  
8.3.2.1 [What does set_rtc_mmss: can't update from 54 to 5 mean?](/ntpfaq/ntp-s-trbl-spec/#8321-what-does-set_rtc_mmss-cant-update-from-54-to-5-mean)  
8.3.2.2 [Why does my Linux system lose several milliseconds every once in a while.](/ntpfaq/ntp-s-trbl-spec/#8322-why-does-my-linux-system-lose-several-milliseconds-every-once-in-a-while)   
8.3.4 [Serial Port](/ntpfaq/ntp-s-trbl-spec/#834-serial-port)   
8.3.4.1 [Do Multiport Serial Cards cause Trouble?](/ntpfaq/ntp-s-trbl-spec/#8341-do-multiport-serial-cards-cause-trouble)  
8.3.4.2 [Why does my DCF77 Receiver not get Power from the serial Port?](/ntpfaq/ntp-s-trbl-spec/#8342-why-does-my-dcf77-receiver-not-get-power-from-the-serial-port)  
8.3.5 [Oncore Compatibles](/ntpfaq/ntp-s-trbl-spec/#835-oncore-compatibles)  
8.3.5.1 [Will the M12 work with the Oncore driver?](/ntpfaq/ntp-s-trbl-spec/#8351-will-the-m12-work-with-the-oncore-driver)  
8.3.5.2 [Why is the UT+ reporting clk_noreply?](/ntpfaq/ntp-s-trbl-spec/#8352-why-is-the-ut-reporting-clk_noreply)   
8.3.6 [Solaris](/ntpfaq/ntp-s-trbl-spec/#836-solaris)     
8.3.6.1 [What is dosyncdr?](/ntpfaq/ntp-s-trbl-spec/#8361-what-is-dosyncdr)  
8.3.6.2 [What causes occasional 2s Time Steps?](/ntpfaq/ntp-s-trbl-spec/#8362-what-causes-occasional-2s-time-steps)  
8.3.7 [Trimble Clocks](/ntpfaq/ntp-s-trbl-spec/#837-trimble-clocks)  
8.3.7.1 [Only one Edge of my Trimble Acutime's PPS Pulse is detected](/ntpfaq/ntp-s-trbl-spec/#8371-only-one-edge-of-my-trimble-acutimes-pps-pulse-is-detected)
  
8.4. [Reporting Bugs](/ntpfaq/ntp-s-trbl-bug-reports/)  
8.4.1 [When should I report a Problem?](/ntpfaq/ntp-s-trbl-bug-reports/#841-when-should-i-report-a-problem)  
8.4.2 [What should I report?](/ntpfaq/ntp-s-trbl-bug-reports/#842-what-should-i-report)

9. [Background and Related Information](/ntpfaq/ntp-s-related/)  
9.1 [Miscellaneous](/ntpfaq/ntp-s-related/#91-miscellaneous)  
9.1.1 [What is Mills-speak?](/ntpfaq/ntp-s-related/#911-what-is-mills-speak)  
9.1.2 [How can I convert a date to NTP format?](/ntpfaq/ntp-s-related/#912-how-can-i-convert-a-date-to-ntp-format)  
9.1.3 [How can I convert an NTP Timestamp to UNIX Time?](/ntpfaq/ntp-s-related/#913-how-can-i-convert-an-ntp-timestamp-to-unix-time)  
9.1.4 [Where can I find more Information?](/ntpfaq/ntp-s-related/#914-where-can-i-find-more-information)  
9.2 [GPS](/ntpfaq/ntp-s-related/#92-gps)  
9.2.1 [Selective Availability revisited](/ntpfaq/ntp-s-related/#921-selective-availability-revisited)

10. [Common Terms and Acronyms](/ntpfaq/ntp-g-all/)
 
> This document tries to explain the most basic features of NTP, and to answer many frequently asked questions. The intention is to help the average user to get a quick start with the official implementation of NTP. Technical issues and mathematics are avoided where possible. Instead the most common questions are tried to be answered, enabling everybody to get a working configuration.

All we do here is invent games to pass the time.
: John O' Donohue

* * *

#### 1. About this Document

{{% pageinfo %}}
The NTP FAQ and HOWTO was originally edited by:
: Ulrich Windl
: Dale R. Worley
: David Dalton, Hewlett-Packard  
: Marc Martinec, Josef Stefan Institute

with this copyright notice:

Copyright &copy; 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006 Ulrich Windl, et al. (see [credits](#110-credits))

The material in this document is covered by the respective contributor's copyright. &copy; Copyright 1999 - 2005, by the contributors and editors of this document. For details see the list of editors and authors.

All editors and contributors (non-exclusively) grant a perpetual, irrevocable, and royalty free license to distribute this document under the terms of the General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This document is distributed in the hope that it will be useful, but _WITHOUT ANY WARRANTY_; without even the implied warranty of _MERCHANTABILITY_ or _FITNESS FOR A PARTICULAR PURPOSE_. See the GNU General Public License for more details.

If you don't already have the GNU General Public License at hand, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
{{% /pageinfo %}}

It is now maintained by [Network Time Foundation](https://www.nwtime.org/). Contributions to update the material are most appreciated and contributors will continue to be added to the credits.

* * *

#### 1.1 Preface

This section tries to answer questions about the document itself. This document is intended for beginners as well as advanced users that are looking for advice. However, basic skills in system administration are required to enjoy this tour. True experts on the subject will probably prefer the original documentation that comes with the software, or make corrections where it is wrong.

The impatient may want to go directly to [Section 2](/ntpfaq/ntp-s-time/) where fundamentals of timekeeping are discussed. [Section 3](/ntpfaq/ntp-s-sw-clocks/) introduces clocks that are implemented using computers. If you are reading sequentially, you should be ready for the section that presents NTP, [Section 4](/ntpfaq/ntp-s-def/).

At that point focus moves from a more theoretical treatment of the subject to practical aspects, starting with [Section 5](/ntpfaq/ntp-s-algo/). Then [Section 6](/ntpfaq/ntp-s-config/) moves into configuration of the NTP software. [Section 7](/ntpfaq/ntp-s-refclk/) will talk about reference clocks.

Real life is talked about in [Section 8](/ntpfaq/ntp-s-trouble/) where procedures, tips, and tricks for troubleshooting are presented. For the curious, [Section 9](/ntpfaq/ntp-s-related/) provides further information and references. Finally, there is a [glossary](/ntpfaq/ntp-g-all/) of terms.

* * *

#### 1.2 Why is this Document named FAQ and HOWTO?

This document tries to answer frequently asked questions (FAQs) that can not (at least virtually) be answered easily from the standard documentation.

In addition to just answering user questions, this document also tries to give a gentle introduction and guidelines to the newcomer. The authors believe that it's better to use NTP correctly right from the start rather than fixing all the problems after they occur.

"Gentle" means "not too technical" and "not too theoretical". However, some basic non-trivial understanding of real life is required at several points, so please accept these deviations from the goal.

* * *

#### 1.3 Where is the source of this document?

The source files for the FAQ can be found [here](https://bitbucket.nwtime.org/projects/WEBSITES/repos/ntpwww/browse/content/en/ntpfaq). The repository also contains the [HTML files for the FAQ](https://bitbucket.nwtime.org/projects/WEBSITES/repos/ntpwww/browse/public/ntpfaq) and a [README](https://bitbucket.nwtime.org/projects/WEBSITES/repos/ntpwww/browse/README.md) for obtaining the source files.

* * *

#### 1.4 Why can't I find information about xyz in this FAQ?

Unless it simply has not been written yet, there may be other reasons:

1.  The editors don't want to copy documentation that is already publicly available. This is especially true for standards, specifications, and manuals. The editors think that referring to is better than copying. The intention is to avoid redundancy while saving labour.
2.  Either the problem or the solution is too vague to document it. This is true for uncommon configurations. After all, we want to answer _frequently_ asked questions here.

* * *

#### 1.5 Where should a new Entry be put?

The answer to this question is quite delicate! The guidelines are probably these:

* Try to understand the existing structure of the document.
* If there are similar entries, see where the new one fits best. Usually it's right near the existing one, or in a corresponding section. Possibly it makes sense to create a new section.

* * *

#### 1.6 Why should I contribute?

In "the good old times" the Internet was a valuable source of information, and people were happy to share their knowledge. These days, however, people think of E-Commerce, how to make money.

This FAQ was written not to make money, but to have a reference to refer to and to provide information to more people. If you have solved some NTP problem that may be of interest to other people, please share your experience.

* * *

#### 1.7 How can I contribute?

Contributions are very much appreciated. You can:

1.  Correct errors or incomplete information.
2.  Suggest an addition consisting of a question together with its answer.
3.  Update examples so they match the current NTP version.

* * *

#### 1.8 I contributed to this FAQ, but my name is not mentioned anywhere. What's wrong?

Probably the fault of the editor. Maybe he thought you don't want to be listed, or simply forgot. [Section 1.10](#110-credits) shows the names the editor was aware of.

* * *

#### 1.9 Why are Graphics stored in PNG Format?

The popular GIF format supported by many browsers relies on a compression algorithm that is patented, and the owner of the patent wants to receive money from everyone making GIF files. PNG (Portable Network Graphics) uses a different algorithm for compression and does not require payment.

* * *

#### 1.10 Credits

If you contributed to this FAQ, and you could not find your name elsewhere, this is where it should be.

This is an alphabetical list of contributors:

* [Michael Andres](mailto:ma@suse.de)
* [Tom Van Baak](mailto:tvb@veritas.com)
* [Wolfgang Barth](mailto:wob@swobspace.rhein.de)
* [Lyle Batema](mailto:Lyle_Batema@Trimble.COM)
* [Eric W. Bates](mailto:ericx@vineyard.net)
* [Brian Bergstrand](mailto:brianb@mac.com)
* [Peter Boettcher](mailto:boettcher@ll.mit.edu)
* Marc Brett
* Bill Broadley
* [Martin Burnicki](mailto:martin.burnicki@meinberg.de)
* Jonathan A. Buzzard
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
* [J&#252;rgen Georgi](mailto:georgi@BelWue.DE)
* [Tim Granger](mailto:Tim.Granger@cl.cam.ac.uk)
* [Benjamin Greenwald](mailto:beng@lcs.mit.edu)
* James & Charlotte Griffin]
* [Richard M. Hambly](mailto:rick@cnssys.com)
* John Hay
* [Per Hedeland ](mailto:per@erix.ericsson.se)
* [Kees Hendrikse](mailto:kees@echelon.nl)
* Martin Herbener
* [Doug Hogarth](mailto:DougHo@niceties.com)
* Andrew Hood
* [Theo Jakobus](mailto:jakobus@iaf.fhg.de)
* Nicholas Jenkins
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
* Jeffrey Mogul
* Hal Murray
* [Dirk A. Niggemann](mailto:dirk-n@dircon.co.uk)
* Mike Nolan
* Johan Fredrik &Oslash;hman
* [Rainer Orth](mailto:ro@TechFak.Uni-Bielefeld.DE)
* Don Payette
* [William R. Pennock](mailto:bill.pennock@transquest.com)
* Bruce M. Penrod
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
* Scott Tuttle
* Brian Utterback
* Gilles Vollant
* [Norman Walsh](mailto:ndw@nwalsh.com)
* David Woolley
* [Dale R. Worley](mailto:worley@shell01.TheWorld.com)