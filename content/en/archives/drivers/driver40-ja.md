---
title: "JJY Receivers"
type: archives
---
Last update: 12-Oct-2017 09:05 UTC          
[ENGLISH（英語）](/archives/drivers/driver40)   

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver40-ja/#synopsis)
*   [Description](/archives/drivers/driver40-ja/#description)
*   [Mode-1](/archives/drivers/driver40-ja/#mode-1)
*   [Mode-2](/archives/drivers/driver40-ja/#mode-2)
*   [Mode-3](/archives/drivers/driver40-ja/#mode-3)
*   [Mode-4](/archives/drivers/driver40-ja/#mode-4)
*   [Mode-5](/archives/drivers/driver40-ja/#mode-5)
*   [Mode-6](/archives/drivers/driver40-ja/#mode-6)
*   [Mode-100](/archives/drivers/driver40-ja/#mode-100)
*   [Monitor Data](/archives/drivers/driver40-ja/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver40-ja/#fudge-factors)

* * *

#### Synopsis

Address: `127.127.40._u_`  
Reference ID: `JJY`  
Driver ID: `JJY`  
Serial Port: `/dev/jjy_u_`; それぞれのJJY受信機、GPS時計、テレフォンJJYを参照して下さい。

* * *

#### Description

このドライバーは、以下の、日本で販売されている JJY受信機、GPS時計と、電話回線による時刻配信サービスをサポートしています。

| Model | Mode | Language |
| ----- | ----- | ----- |
| [トライステート   TS-JJY01, TS-JJY02](http://www.tristate.ne.jp/) | [1](/archives/drivers/driver40-ja/#mode-1) | 日本語 |  
| [シーデックス   JST2000](http://www.c-dex.co.jp/) | [2](/archives/drivers/driver40-ja/#mode-2) | 日本語 | 
| エコー計測器   LT-2000 | [3](/archives/drivers/driver40-ja/#mode-3) | | 
| [シチズンTIC   JJY-200](http://www.tic-citizen.co.jp/) | [4](/archives/drivers/driver40-ja/#mode-4) | 日本語 |  
| [トライステート   TS-GPSclock-01](http://www.tristate.ne.jp/) | [5](/archives/drivers/driver40-ja/#mode-5) | 日本語 |  
| [セイコー タイム システム   TDC-300](http://www.seiko-sts.co.jp/) | [6](/archives/drivers/driver40-ja/#mode-6) | 英語と日本語 |  
[テレフォンJJY](http://jjy.nict.go.jp/) | [100](/archives/drivers/driver40-ja/#mode-100) | 英語と日本語 |  

* * *

#### Mode-1


**NTPの設定 (ntp.conf)**

`server   127.127.40.X   mode 1`

`fudge   127.127.40.X   time1 0.NNN   flag1 0|1   flag2 0|1   time2 H`

 Time1 は、受信機からの時刻に加算する調整時間を、固定小数点形式の秒で設定します。  
 この受信機には、数10ミリ秒 ( 0.0NN秒 ) から百数10ミリ秒 ( 0.1NN秒 ) の調整時間を設定すると良いでしょう。

 Time2 は、STUSコマンドの応答が adjusted ではなくなってからの猶予時間を時単位で指定します。  
 この猶予時間は、flag1 と flag2 を共に 1 に設定したときに有効です。

 Flag1 は、flag2 を 1 に設定しない限り、時刻同期には無関係です。Flag1 を 1 に設定すると、状態を問い合わせるコマンドを DATE コマンドと STIM コマンドの前に発行して、応答を clockstats ファイルに記録します。

**fudge flag1**

| Value | Description |
| ----- | ----- |
| `0` (Default | DCST と STUS コマンドは、発行しません。 |
| `1` | DCST と STUS コマンドを、発行します。 |

Flag2 は STUSコマンドの応答が adjusted の時だけ、時刻同期処理を行う指定です。この機能を使うときは、flag1 も同時に 1 に設定する必要があります。

**fudge flag2**

| Value | Description |
| ----- | ----- |
| `0` (Default) | 常に、時刻同期処理 |
| `1` | adjusted の時だ、け時刻同期委処理 |

**インターフェース**

RS-232C, 9600 BPS, 8ビット, パリティなし, 1ストップ・ビット

**日時データの形式**

| コマンド | 応答 |
| ----- | ----- |
| `dcst{CR}{LF}` | `valid{CR}{LF} \| invalid{CR}{LF}` |
| `stus{CR}{LF}` | `adjusted{CR}{LF} \| unadjusted{CR}{LF}` |
| `time{CR}{LF}` | `HH:MM:SS{CR}{LF}` |
| `date{CR}{LF}` | `YYYY/MM/DD WWW{CR}{LF}` |
| `stim{CR}{LF}` | `HH:MM:SS{CR}{LF}` |

日付と時刻は、別々に問い合わせます。日付が深夜０時の前か後かの不確定をチェックするため、日付の問い合わせの前後に時刻を問い合わせています。
	
* * *

#### Mode-2

**NTPの設定 (ntp.conf)**

`server   127.127.40.X   mode 2`

`fudge   127.127.40.X   time1 0.NNN`

**インターフェース**

RS-232C, 9600 BPS, 8ビット, パリティなし, 1ストップ・ビット

**日時データの形式**

| コマンド | 応答 |
| ----- | ----- |
| `{ENQ}1J{ETX}` | `{STX}JYYMMDDWHHMMSSS{ETX}` |
	
* * *

#### Mode-3 

エコー計測器株式会社は解散しました。2015年7月に、一部の事業は、フレックタイム株式会社に継承されました。

**NTPの設定 (ntp.conf)**

`server   127.127.40.X   mode 3`

`fudge   127.127.40.X   time1 0.NNN`

**Interface**

RS-232C, 9600 BPS, 8ビット, パリティなし, 1ストップ・ビット

**Time code format**

| コマンド | 応答 |
| ----- | ----- |
| `C` | ( Mode 2 : Continuous ) |
| ( Every second before 0.5 second ) | `YYMMDDWHHMMSS{ST1}{ST2}{ST3}{ST4}{CR}` |
| `#` | ( Mode 1 : Request&Send ) |
	
* * *

#### Mode-4

JJY-200 は、2013年に販売終了となりました。

**>NTPの設定 (ntp.conf)**

`server   127.127.40.X   mode 4`

`fudge   127.127.40.X   time1 0.NNN`

**インターフェース**

RS-232C, 4800 BPS, 8ビット, パリティなし, 1ストップ・ビット

**日時データの形式**

| コマンド | 応答 |
| ----- | ----- |
| (Every second) | `'XX YY/MM/DD W HH:MM:SS{CR}` |
	
* * *

#### Mode-5

このドライバーは、JJY受信機ではないGPS時計のトライステート TS-GPSclock-01 のコマンド・レスポンス・モードをサポートします。  
TS-GPSclock-01 は、オンボードのスイッチとメニューでコマンド・レスポンス・モードとタイム・ゾーンをJST（日本標準時）に設定しなければなりまん。  
この Type 40 のドライバーの他, TS-GPSclock-01 のNMEAモードは、[一般 NMEA GPS ドライバー ( Type 20 )](/archives/drivers/driver20) でも利用することができます。

**NTPの設定 (ntp.conf)**

`server   127.127.40.X   mode 5`

`fudge   127.127.40.X   time1 0.NNN   flag1 0|1`

Time1 は、受信機からの時刻に加算する調整時間を、固定小数点形式の秒で設定します

Flag1 は、時刻同期には無関係です。Flag1 を 1 に設定すると、状態を問い合わせるコマンドを DATE コマンドと STIM コマンドの前に発行して、応答を clockstats ファイルに記録します。

**fudge flag1**

| Value | Description |
| ----- | ----- |
| `0` (Default) | STUS コマンドは、発行しません。 |
| `1` | STUS コマンドを、発行します。 |

**インターフェース**

USB (`/dev/ttyACM_0_`)

**日時データの形式**

| コマンド | 応答 |
| ----- | ----- |
| `stus{CR}{LF}` | `*R{CR}{LF} \| *G{CR}{LF} \| *U{CR}{LF} \| +U{CR}{LF}` |
| `time{CR}{LF}` | `HH:MM:SS{CR}{LF}` |
| `date{CR}{LF}` | `YYYY/MM/DD{CR}{LF}` |

日付と時刻は、別々に問い合わせます。日付が深夜０時の前か後かの不確定をチェックするため、日付の問い合わせの前後に時刻を問い合わせています。
	
* * *

#### Mode-6

TDC-300 は、フロント・パネルのメニュー表示とスイッチで type 3 のデータ形式に設定しなければなりません。

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 6`

`fudge   127.127.40.X   time1 0.NNN`

**インターフェース**

RS-232C, 2400 BPS, 8-bits, no parity, 1 stop bit

**日時データの形式**

| コマンド | 応答 |
| ----- | ----- |
| | `{STX}YYMMDDWHHMMSS{ETX}` | 
| (5 to 10 mSec. before second) |`{STX}{xE5}{ETX}` | 
	
* * *

#### Mode-100

テレフォンJJYは、電話回線による時刻配信サービスです。  
このサービスは、国立研究開発法人　情報通信研究機構が提供しています。

注意：　このモード（テレフォンJJY）は、refclock_acts ( Type 18 ) のドライバーと同時に利用することはできません。 設定ファイルの phone は、server と関係付けられていないため、ドライバーの refclock_acts ( type 18 ) も、この refclock_jjy ( type 40, mode 100 to 180 ) のいずれも、 複数の phone のうち、どれが自分に関係するものか識別できないからです。

**NTPの設定 (ntp.conf)**

`server   127.127.40.X   mode (100, 101 to 180)   minpoll N`

モード 100 を設定した場合、このドライバーは、遅延を計測するためのループバック・コマンドは発行せず、電話回線とシステムの処理による遅延は調整しません。  
モード 101 から 180 を設定した場合、このドライバーは、ループバック・コマンドを発行して、テレフォンJJYのループバック回路を通して電話回線とシステムの処理による遅延を計測します。  
テレフォンJJYのループバック回路を経由した往復の時間は、5回、計測されます。 それぞれの遅延時間のうち、700ミリ秒を超えたものは、平均遅延時間の計算より除外されます。 また、700ミリ秒以下の有効な遅延時間が、3回以上の場合は、そのうち、最大の遅延時間は、平均遅延時間の計算より除外され、 4回以上の場合は、そのうち、最小の遅延時間は、平均遅延時間の計算より除外されます。 調整時間は、往復時間　×　( モード番号 - 100 ) % で計算し、同期する時刻に加算されます。  
モード 101 から 180 を設定して自動遅延補正を選択するなら、モード 145 から 165 が良いでしょう。

デフォルトの日時問い合わせ処理間隔 6 ( 64 秒 ) は、このモードには、短すぎます。　"minpoll" は、8 ( 256 秒, 約 4 分 ) 以上を設定して下さい。  
日時問い合わせ処理間隔は、秒数を 2 のべき乗で指定します。　minpoll の値が、12 なら 4096 秒（約1時間）、14 なら 16384 秒（約4.5時間）、16 なら 65536 秒（約18時間）となります。

`fudge   127.127.40.X   flag1 0|1   flag2 0|1   flag3 0|1   flag4 0|1`

Time1 は、受信機からの時刻に加算する調整時間を、固定小数点形式の秒で設定します。  
mode 100 の場合は、time1 で調整する時間を設定したほうが良いでしょう。  
 mode 101 から 180 の場合は、このドライバーが計測したループバックの遅延時間の一定の割合を同期時刻に加算しますので、time1 は設定しないほうが良いでしょう。

**fudge flag1**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | タッチ・トーン | `ATDWTnn...nn` |
| `1` | ダイヤル・パルス | `ATDWPnn...nn` |

Flag2 は、エラー訂正プロトコルを指定します。

**fudge flag2**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | ノーマル（エラー訂正なし） | `AT\N0` |
| `1` | V42, MNP, ノーマルの自動選択 | `AT\N3` |

Flag3 は、スピーカーのオン／オフを指定します。

**fudge flag3**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | オフ | `ATM0Ln` |
| `1` | オン | `ATM2Ln` |

Flag4 は、スピーカーの音量を指定します。

**fudge flag4**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | 低 | `ATMnL1` |
| `1` | 中 | `ATMnL2` |

**phone 042NNNNNNN**

電話番号は、[http://jjy.nict.go.jp/](http://jjy.nict.go.jp/) で公開されています。  
電話番号の桁数をチェックしています。もし、日本国外から発信するために国際電話アクセス番号と国番号を付加すると、桁数制限を超えます。  
また、電話番号の最初の2桁や3桁をチェックしています。日本の緊急番号や特別のサービスの番号を指定することはできません。  
内線から外線に発信する時は、"0," ( ゼロとカンマ ) を先頭に付加して下さい。外線発信番号は、チェックしていて、それ以外の外線発信番号を指定することはできません。

**インターフェース**

RS-232C 又は USB, 2400 BPS, 8ビット, パリティなし, 1ストップ・ビット

モデム制御コマンド:  

`ATE0Q0V1, ATMnLn, AT&K4, AT+MS=V22B, AT%C0, AT\Nn, ATH1, ATDWxnn...nn`  
`+++, ATH0`

**日時データの形式**

| プロンプト | コマンド | 応答 |
| ----- | ----- | ----- |
| `Name{SP}?{SP}` | `TJJY{CR}` | Welcome messages |
| `>` | `LOOP{CR}` | Switch to the loopback circuit |
| | `(One char.)` | `(One char.)` |
| | `COM{CR}` | Exit from the loopback circuit |
| `>` | `TIME{CR}` | `HHMMSS{CR}HHMMSS{CR}HHMMSS{CR}` 3 times on second |
| `>` | `4DATE{CR}` | `YYYYMMDD{CR}` |
| `>` | `LEAPSEC{CR}` | `{SP}0{CR} \| +1{CR} \| -1{CR}` |
| `>` | `BYE{CR}` | Sayounara messages |

日付と時刻は、別々に問い合わせます。日付が深夜０時の前か後かの不確定をチェックするため、日付の問い合わせの前後に時刻を問い合わせています。  
うるう秒は、処理していません。情報として clockstats ファイルに記録しているだけです。

JJY は、長波で日本標準時(JST)を送信している無線局で、国立研究開発法人　情報通信研究機構が運用しています。JJY の運用情報などは、 [http://www.nict.go.jp/](http://www.nict.go.jp/)（英語と日本語）や [http://jjy.nict.go.jp/](http://jjy.nict.go.jp/)（英語と日本語）で提供されています。

実際のシリアル・ポートのデバイスにシンボリック・リンクを作成して下さい。シンボリック・リンクを作成するコマンドは、以下のとおりです。

`ln -s /dev/ttyS0 /dev/jjy0`

RS-232C から USB への変換ケーブルを利用して、JJY受信機、GPS時計、モデムをRS-232Cポートではなく、USBに接続することができます。この場合のシンボリック・リンクを作成するコマンドは、以下のとおりです。

`ln -s /dev/ttyUSB0 /dev/jjy0`

Windows NT の場合は、 COM_X_: の数字部分がドライバーのユニット番号に使用されます。 ドライバーのユニット 1 は、COM1: にユニット 3 は、COM3: に対応します。

* * *

#### Monitor Data

このドライバーは、JJY受信機、GPS時計、モデムとの送受信データを `clockstats` ファイルに記録します。

`statsdir /var/log/ntpd/  
filegen clockstats file clockstats type day enable`

**レコード中のマークについて**

| Data | Meaning |
| ----- | ----- |
| `JJY` | 情報（このドライバーの開始または終了） |
| `-->`  | 送信データ |
| `<--` | 受信データ |
| `---` | 情報 |
| `===` | 情報（ポーリングの開始、および、同期時刻） |
| `-W-` | 警告メッセージ |
| `-X-` | エラー・メッセージ |

* * *

#### Fudge Factors

`time1 _time_`

<dd>受信機からの時刻に対する調整時間を、固定小数点形式の秒で設定します。デフォルトは、0.0秒です。</dd>

`time2 _time_`

<dd>未使用。</dd>

`stratum _number_`

<dd>NTPの階層番号を 0 から 15 で指定します。デフォルトは、0です。</dd>

`refid _string_`

<dd>ドライバーIDで、ASCII の1文字から4文字で指定します。デフォルトは、`JJY` です。</dd>

`flag1 0 | 1`

<dd>それぞれのモードを参照して下さい。</dd>

`flag2 0 | 1`

<dd>それぞれのモードを参照して下さい。</dd>

`flag3 0 | 1`

<dd>それぞれのモードを参照して下さい。</dd>

`flag4 0 | 1`

<dd>それぞれのモードを参照して下さい。</dd>

</dl>
