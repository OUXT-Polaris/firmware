# firmware

firmware for WAM-V and MiniV 2.0

## 使い方
```
mbed-tools deploy
```
でmbed-osフォルダをcloneする

```
mbed-tools compile -m NUCLEO_F767ZI -t GCC_ARM --profile develop -f
```
でビルドと書き込みが同時にできる

## Dockerでのビルド

注意！事前にDockerがインストールされているのを確認してください。
```
sh build.sh
```