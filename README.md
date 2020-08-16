# lpms_me1_sample
Sample code for LPMS-ME1 IMU sensor

## Quick description
LPMS-ME1 IMUセンサからi2c通信によりデータを取得し，printfするだけのプログラム．  
データとしては，タイムスタンプ，加速度，ジャイロ，地磁気，オイラー角，クオータニオンが出力される．  
pc側がwindowsであればteraterm，linuxであればターミナルで値を確認できる．  
センサとの通信のコアのところはlpme1.c, lpme1_driver.cを見ればわかる．  

## 開発環境

|    | Description |
| --- | --- |
| CPU | STM32f303k8 |
| IDE | STM32CubeIDE 1.3.0 |
| Sensor kit | LPMS-ME1-DK Ver.1.2 |
| Communication | I2C |

## For more infomation
Sensor brief description: See [LPMS-ME1](https://lp-research.com/lpms-me1/)  
Sensor detailed spec: See [LpmsMe1Manual20171002.pdf](https://github.com/jiei/lpms_me1_sample/blob/master/Document/LpmsMe1Manual20171002.pdf)  
LPMS-ME1 development kit manual: See [20191114LPMS-ME1_DKManual.pdf](https://github.com/jiei/lpms_me1_sample/blob/master/Document/20191114LPMS-ME1_DKManual.pdf)  
Sample code produced by LP-RESEARCH: See [LpmsME1Example](https://bitbucket.org/lpresearch/lpmsme1example/src/master/)  

## 個人的に気になったこと
LPRESEARCHが提供しているライブラリ(lpme1.c,h, lpme1_driver.c,h)を眺めていて，  
個人的に非常に勉強になった部分があったので，コーディングのテクニカルなtipsとしてここに共有しておく．  
(組み込みで通信のプログラミングをするなら常識なのかもしれないが...)  
  
通信によってデータのやり取りをする際，16ビットとか32ビットの生データを8ビットに分解して送って，  
送った先でまた逆の操作をしてデータの復元をするという操作が必要になる．  
そのような時に僕がよくやるのが，  
```C
void float_to_uint8(float input, uint8_t *output)
```
とか
```C
float uint8_to_float(uint8_t *data)
```
みたいな関数を変換ごとに定義して，型変換を行っていた．  
変換の方法を定義するのに，「上位8ビット下位8ビットで分けて配列に格納して...」とか「符号は2個めの配列の8ビット目で表現して...」みたいなことを考えなければならない．こんなの考えるのめんどいし，バグの原因にもなる．
  
一方でこのライブラリでは別の方法で型変換を行っている．  
例えば加速度値の取得を行う関数はlpme1.cに以下のように記述されている  
```C
lpme1_status_t lpme1_get_acc(float *acc)
{
    DataDecoder data[3];
    if(lpme1_read_buffer(ACC_X_0, (uint8_t *)data[0].u8vals, 12) == LPME1_OK)
    {
        for(uint8_t i = 0; i<3; i++)
        {
            *(acc+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;

}
```
8ビットのデータの配列を`(uint8_t *)data[0].u8vals`として吸い出し，float型のaccに`*(acc+i) = data[i].fval`で格納している．  
これで変換は終了である．  
この操作のキモは`DataDecoder`というデータの型の定義の仕方にある．lpme1.hに記述されている．  
```C
typedef union
{
    uint8_t u8vals[4];
    uint32_t u32val;
    float fval;
} DataDecoder;
```
union型(共用体)としてデータタイプを定義している．  
union型とはざっくり言うと「メンバは複数あるが，全体でひとつの値しか記憶できない型」である．  
つまりどういうことか？  
8ビットのデータが4つ格納されている配列を，メモリの先頭からそのまま32ビット読めば自然とfloat型のデータになっているわけである．  
逆にfloat型として格納したデータを8ビットごとに分けて読めばuint8型になる．  
わざわざ変換のための関数を作ってデータの型変換を行うよりは，とても操作がシンプルだし，  
メモリのコストも計算のコストも遥かに節約できて，非常にエレガントである．  
