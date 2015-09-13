BOFDemo
--------
A simple buffer overflow vulnerability demo for IA-32

## テスト環境

* CPU: Intel Core i7
* OS: Linux (Ubuntu 14.04LTS), 32-bit
* C-compiler: gcc 4.8.4
* libc: glibc 2.19

## ビルド

    make

問題なくコンパイルできた場合，`demo` および `mkattack` という実行形式と，
`shellcode.bin` というバイナリファイルが作成されるはずです．なお，
`shellcode.bin` の作成には `objcopy` が必要です．これは通常 `binutils`
というパッケージに含まれています．

## 実行

実行前にスタックアドレスのランダム化機能をoffにします．

    sudo sysctl -w kernel.randomize_va_space=0

プログラム `demo` は，ファイルに書き込まれた10進数値の二乗を出力するだけの
簡単なプログラムです．

    echo 1234 > normal.dat
    ./demo normal.dat

以下のようにすると，実行中のスタックを出力します．

    ./demo -d normal.dat

このスタックの出力を参考にして，プログラム `mkattack` を使って攻撃用のデータを
作成します．このプログラムの第1引数は `shellcode.bin`，第2引数はバッファ(`buf`)
の先頭からベースポインタまでのオフセット(32ビットワードの個数)，第3引数は
ベースポインタが指しているスタック上の値(旧ベースポインタ)，第4引数は `buf` の
先頭アドレスです．

    ./mkattack shellcode.bin 17 0xbfffefe8 0xbfffeb80 > attack.dat

こうして作られた攻撃用データを与えるとシェルが起動するはずです．

    ./demo attack.dat
