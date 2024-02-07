---
title: "Generic NMEA GPS Receiver"
type: archives
---

Last update: 13-Jan-2020 07:12 UTC

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver20/#synopsis)
*   [Description](/documentation/drivers/driver20/#description)
*   [NMEA Talker IDs](/documentation/drivers/driver20/#nmea-talker-ids)
*   [The 'mode' byte](/documentation/drivers/driver20/#the-mode-byte)
*   [About distrusting NMEA date stamps](/documentation/drivers/driver20/#about-distrusting-nmea-date-stamps)
*   [Monitor Data](/documentation/drivers/driver20/#monitor-data)
*   [Setting up the Garmin GPS-25XL](/documentation/drivers/driver20/#setting-up-the-garmin-gps-25xl)
*   [Fudge Factors](/documentation/drivers/driver20/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver20/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.20._u_</code>
: **Reference ID:** `GPS`
: **Driver ID:** `GPS_NMEA`
: **Serial Port:** <code>/dev/gps*u*</code>; 4800 - 115200 bps, 8-bits, パリティーなし
: **Serial Port:** <code>/dev/gpspps*u*</code>; PPS信号 (<code>/dev/gps*u*</code> より先に処理)
: **Serial Port:** <code>/dev/gps*u*</code>; このドライバー nmead のシンボリック・リンク
: **Features:** `tty_clk`

* * *

#### Description

このドライバーは、GPS受信機のNMEAセンテンスの `$GPRMC, $GPGLL, $GPGGA, $GPZDA, $GPZDG` をデフォルトで処理対象にしています。 Accord社のNMEAセンテンス `$GPZDG` は、他のセンテンスがUTC時刻を通知するのに対し、GPS時刻を通知することに注意して下さい。 UTC時刻とGPS時刻の違いは、UTC時刻にはうるう秒が挿入されることです。 UTC時刻とGPS時刻の混在による問題を回避するため、このドライバーは、UTC時刻の <tt>$GPZDG</tt> を受信したら処理を無効にします。

> **注意：** GPS以外のGNSS（衛星測位システム）や複数のGPS受信機を利用するときは、後述の [Talker IDs](/documentation/drivers/driver20/#nmea-talker-ids) をご参照下さい。

GPS受信は このドライバーがサポートしているNMEAセンテンスの少なくとも一つを出力するように設定する必要があります。

時刻同期の精度は、GPS受信機に依存します。 安価なGPSモジュールでもPPS信号は、NMEAセンテンスの送信情報と比較して精度が良く、１マイクロ秒程度の精度があります。 多くの場合、時刻同期の精度は、時刻情報のシリアル・ラインによる転送遅延時間とシステムの処理時間で制限されます。

OSが PPSAPI ([RFC 2783](http://www.ietf.org/rfc/rfc2783.txt)) をサポートしているなら、 設定ファイルの `fudge flag1 1` と指定することにより有効化して利用することができます。

このドライバーが認識するNMEAセンテンスは以下とおりです。 これ以外のNMEAセンテンスは無視されます。

**Accepted NMEA sentences**

| Sentence | Vendor |
| ----- | ----- |
| `$GPRMC,UTC,POS_STAT,LAT,LAT_REF,LON,LON_REF,SPD,HDG,DATE,MAG_VAR,MAG_REF*CS` | |
| `$GPGLL,LAT,LAT_REF,LON,LON_REF,UTC,POS_STAT*CS` ||
| `$GPGGA,UTC,LAT,LAT_REF,LON,LON_REF,FIX_MODE,SAT_USED,HDOP,ALT,ALT_UNIT,GEO,G_UNIT,D_AGE,D_REF*CS` ||
| `$GPZDA,UTC,DD,MM,YYYY,TH,TM,*CS` ||
| `$GPZDG,GPSTIME,DD,MM,YYYY,AA.BB,V*CS` | Accord |
| `$PGRMF,gpsWk,gpsTow,DATE,UTC,LEAPS,LAT,LAT_REF,LON,LON_REF,TYPE,MODE,SPD,HDOP,TDOP*CS` | Garmin |
| `$PUBX,04,UTC,DATE,utcTow,utcWk,LEAPS,clkBias,clkDrift,tpGran,*CS` | UBLOX |

**NMEA data items**

| Symbol | Meaning and Format |
| ----- | ----- |
| `ALT` | 高度 |
| `ALT_UNIT` | 高度単位 (Metres/Feet) |
| `DATE` | 日付 (ddmmyy) |
| `DD` | 日 (1-31) |
| `D_AGE` | DGPSのエイジ |
| `D_REF` | DGPSのID |
| `FIX_MODE` | 位置特定 (0 = 無効, >0 = 有効) |
| `GEO` | ジオイド高 |
| `GPSTIME` | GPS時刻 `[fraction (opt.)] (hhmmss[.f])` |
| `gpsTow` | GPS週開始からの経過秒 (0..604799) |
| `gpsWk` | GPS週番号 (may exceed 1024) |
| `G_UNIT` | ジオイド高単位 (M/F) |
| `HDG` | 磁北と真北の偏角 (x.x) |
| `HDOP` | 水平測位精度 |
| `LAT` | 緯度 (llll.ll) |
| `LAT_REF` | 緯度方向 (N = 北緯, S = 南緯) |
| `LEAPS` | うるう秒、または、GPS時刻とUTCの差 |
| `LON` | 経度 (yyyyy.yy) |
| `LON_REF` | 経度方向 (E = 東経, W = 西経) |
| `MAG_REF` | 磁北と真北の偏角方向 (E = 東, W = 西) |
| `MAG_VAR` | 磁北と真北の偏角 (x.x) |
| `MM` | 月 (1-12) |
| `POS_STAT` | ステータス (A = 有効, V = 無効) |
| `SAT_USED` | 利用衛星数 |
| `SPD` | 移動速度 (knots) (x.x) |
| `UTC` | UTC時刻 `[fraction (opt.)] (hhmmss[.fff])` |
| `YYYY` | 年 |
| `WEEK` | GPS週番号 (0-1023) |
| `WSEC` | GPS週開始からの経過秒 (0-604799) |
| `LEAP` | GPSうるう秒（UTCからの進み秒） |
| `AA.BB` | 信号強度 (should be < 05.00) |
| `V` | GPS同期状態<br>  `0` => 時刻は無効<br> `1` => 時刻同期精度 +/- 20ms<br> `2` => 時刻同期精度 +/- 100ns |
| `CS` | チェックサム |
| <code>\<cr>\<lf><code> | 行末 |

* * *

#### NMEA Talker IDs

GNSS受信機（衛星測位システム受信機）は、処理するGNSS固有の talker ID を使用します。 複数の衛星測位システムを同時に処理する受信機は、`$GPRMC` (GPS), `$GLRMC` (GLONASS), `$GARMC` (Galileo), `$GNRMC` (generic/combined) など、 他のNMEAセンテンスも一つのデータ・ストリームで出力します。

このドライバーは、NMEAセンテンスの talker ID を無視して `RMC, GLL, GGA, ZDA, ZDG` を処理します。 できれば、このように処理すべきではなかったことは後述しますが、現在は、このように処理しています。 この文書で `$GPRMC` という記述は、それ以外の talker ID も同様に該当すると読み替えて下さい。

この方法には欠点があります。一つの受信機で簡単にいろいろなGNSSを扱える半面、複数の受信機でGNSSを分けて扱うことができません。 GNSSが実際にデータを提供するかは定義されていなので、不都合な動作につながる可能性があります。 これは、異なるGNSSが大きく異なる信号品質を受信機に提供する場合に特に当てはまります。 ドライバーは最良の時刻ソースを選択することができず、実際には利用可能な最悪の時刻ソースを使用することになった場合です。  従って、このような場合、受信機を一つのGNSSだけを処理するように設定するか、または、 NMEA標準で定義された `GN` talker ID に結合されたデータのみを出力するように設定して下さい。


    
#### The 'mode' byte
    
 処理対象のNMEAセンテンスやシリアル通信速度は、設定ファイルの server ステートメントの `mode` で指定します。 

`server 127.127.20.x mode X`

**mode byte bits and bit groups**

| Bit | Decimal | Hex | Meaning |
| ----- | ----- | ----- | ----- |
| `0` | `1` | `1` | 処理対象 `$GPRMC` |
| `1` | `2` | `2` | 処理対象 `$GPGGA` |
| `2` | `4` | `4` | 処理対象 `$GPGLL` |
| `3` | `8` | `8` | 処理対象 `$GPZDA` or `$GPZDG` |
| `4-6` | `0` | `0` | シリアル通信速度 4800 bps |
| | `16` | `0x10` | シリアル通信速度 9600 bps |
| | `32` | `0x20` | シリアル通信速度 19200 bps |
| | `48` | `0x30` | シリアル通信速度 38400 bps |
| | `64` | `0x40` | シリアル通信速度 57600 bps |
| | `80` | `0x50` | シリアル通信速度 115200 bps |
| `7` | `128` | `0x80` | 全てのNMEAセンテンスについて、秒以下のタイムスタンプを clockstat に出力します。 これは、fudge time2 の値を取得するのに使うことができます。 **注意：** これにより、clockstats ファイルがかなり速くいっぱいになります。 一時的にのみ使用して、選択したNMEAセンテンスの番号を取得します。</ |
| `8` | `256` | `0x100` | 処理対象 `$PGRMF` |
| `9` | `512` | `0x200` | 処理対象 `$PUBX,04` |
| `10-15` |  | `0xFC00` | 予約（0 に設定） |
| `16` | `65536` | `0x10000` | 追加の統計情報を clockstats 行に出力。後述。 |
| `17` | `131072` | `0x20000` | "Silent PPS" モード。 PPS信号（`fudge flag1` で有効に設定している場合）を使用して、正確な受信タイムスタンプを取得します。 クロックはPPSピアとは見なさないため、クロック・ステータスにPPSフラグを設定しないで下さい。 |
| `18` | `262144` | `0x40000` | NMEAで配信された日付を信頼します。 受信機が本当に信頼できる場合のみ、使用して下さい。 [>参照](/documentation/drivers/driver20/#about-distrusting-nmea-date-stamps). **注意：** このビットは移動されています。 |


デフォルトの mode 0 は、シリアル通信速度4800bpsで、このドライバーがサポートする全てのNMEAセンテンスを処理します。 これにより、同期処理の各サイクルで最初に受信および認識されたNMEAセンテンスの結果となります。  もし特定のNMEAセンテンスを処理したい場合は、mode の該当するものだけを有効に設定して下さい。 複数のNMEAセンテンスを処理対象として設定することはできますが、同期処理のサイクルで最初に受信したNMEAセンテンスだけが処理されます。 同期処理のサイクルで複数のNMEAセンテンスを処理することができない理由は、以下のとおりです。 [fudge time2](/documentation/drivers/driver20/#fudge-factors) でNMEAセンテンスの通信遅延時間を補償・調整しますが、複数のNMEAセンテンスではその時間が異なります。 同期処理のサイクルごとに複数の文を使用すると、内部のデータ・フィルター処理が過剰になります。
      
このドライバーのデフォルトのシリアル通信速度は 4800 bpsですが、mode のビット 4 から 6 で速い通信速度を指定することができます。

> **注意：** 早いシリアル通信速度は、時刻同期の精度向上に必須ではなく、このNMEAドライバーにとっても必ずしも役立つとは限りません。  早いシリアル通信速度は、4800bpsで1秒のサイクルに収まらない量のデータに対応するために使用できます。  NMEAはプロトコルでハンドシェイクをサポートしていないため、高速で大量のNMEAデータはシリアル・ライン・ドライバーでバッファー・オーバーフローなどの問題を引き起こす可能性があります。 時間同期の目的でのみ使用されるデバイスは、関連するデータのみを送信するように構成する必要があります。 例えば、`$GPRMC` あるいは `$GPZDA` を１秒に１回だけ 4800 bps か 9600 bps で出力する、など。


#### About distrusting NMEA date stamps

NMEAで配信されるカレンダー日付を信頼することは危険です。 デフォルトでは、これらの日付は非常に懐疑的に扱われます。 多くの受信機は、ファームウェアに焼き付けられた開始点から、わずか1024週間しか正しいカレンダー日付を配信できません。
それを超えると、開始点に戻って、誤った日付情報を配信します。 良く見られるこの問題に対処するため、デフォルトで、GPS時間に再び戻って、暗黙の日付かファームウェアに焼き付けられた基準日に再マッピングされた日付が配信されます。 正しい日付を配信する受信機を製造することは不可能ではなく高価になります。 受信機が正しい日付を配信することを本当に信頼できる場合は、mode のビット 18 でGPS週の世代のマッピングをバイパスできます。 ほとんどの場合、このビットを設定する必要はありません。 信頼性の低い受信機で設定すると、深刻な影響を与える可能性があります。取り扱い注意。

> **経緯：** この機能は、ビット値が異なる、文書化されていない機能としてしばらくの間利用可能でした。 mode のビットマスクの過度の散乱を避けるために、このビットは公式に承認される過程で移動されました。
    
    
#### Monitor Data

受信または拒否された最後のNMEAセンテンスが clockstats ファイルに書き込まれ、`ntpq -c clockvar` で使用できます。 拒否された記録は、拒否された原因を調べたりデバッグするために利用できます。 フィルターされたNMEAセンテンスは記録されません。

mode のビット 0x10000 をオンにすると clockstats ファイルのログに記録されるNMEAセンテンスには、いくつかのカウンターが追加されます。 例えば、

`56299 76876.691 127.127.20.20 $GPGGA,212116.000,3726.0785,N,12212.2605,W,1,05,2.0,17.0,M,-25.7,M,,0000*5C  228 64 0 0 64 0`

**Clockstats**

| Column | Sample | Meaning |
| -----  | -----  | -----   |
| 1      | `56299`  | MJD     |
| 2      | `76876.691` | １日の通算秒 |
| 3      | `127.127.20.20` | IPアドレス |
| 4      | `$GPGGA,...0*5C` | NMEAセンテンス |
| 5      | `228`    | 受信したセンテンス数 |
| 6      | `64`     | 有効で時刻同期に使用されたセンテンス数 |
| 7      | `0`      | 時刻同期には有効でないと判定されたセンテンス数 |
| 8      | `0`      | チェックサム・エラーや有効でな日時で無効なセンテンス数 |
| 9      | `64`     | mode の設定によりフィルターまたは同時刻のセンテンス数 |
| 10     | `0`      | NMEAセンテンスのかわりに使用されたPPS信号数 |


`$GPGSV` のように時間が含まれていない文は、合計にカウントされますが、それ以外の場合は無視されます。 

[Configuring NMEA Refclocks](https://support.ntp.org/bin/view/Support/ConfiguringNMEARefclocks)  で、奇妙な動作を示す特定のハードウェア・デバイスについて役立つヒントが得られる場合があります。 

特定の設定を行うには、mode のバイト・テーブルから対応する10進値を選択し、それらをすべて合計して、 結果の10進値を設定ファイルの server ステートメントの mode に設定します。

#### Setting up the Garmin GPS-25XL

次の文字列を送信して、すべての出力をオフにします

<code>$PGRMO,,2\<cr>\<lf></code>

次の文字列を送信して、`$GPRMC` の出力をオンにします。

<code>$PGRMO,GPRMC,1\<cr>\<lf></code>

一部のシステムでは、PPS信号はデフォルトでオンになりません。 次の文字列を送信することでオンにできます。

<code>$PGRMC,,,,,,,,,,,,2\<cr>\<lf></code>

#### Fudge Factors

<code>**time1 _time_**</code>
: PPS信号の調整時間、単位：秒（小数点以下も可）、デフォルト 0.0秒

<code>**time2 _time_**</code>
: シリアル通信の調整時間、単位：秒（小数点以下も可）、デフォルト 0.0秒

<code>**stratum _number_**</code>
: 階層番号、0 から 15 の整数、デフォルト 0

<code>**refid _string_**</code>
: ドライバーのREFID、ASCIIの1文字から４文字、デフォルト `GPS`

<code>**flag1 0 | 1**</code>
: 0（デフォルト）： PPS信号は処理しない　／　1： PPS信号を処理する

<code>**flag2 0 | 1**</code>
: 0（デフォルト）： PPS信号の立ち上がりが正秒　／　1： PPS信号の立ち下がりが正秒

<code>**flag3 0 | 1**</code>
: 0（デフォルト）： <tt>ntpd</tt> clock discipline　／　1： kernel discipline

<code>**flag4 0 | 1**</code>
: 0（デフォルト）： タイムコード内の場所を隠さない　／　1： タイムコード内の場所を隠す

#### Additional Information

`flag1, flag2`, and `flag3` は、Windows においては無視されます。

[Reference Clock Drivers](/documentation/4.2.8-series/refclock)