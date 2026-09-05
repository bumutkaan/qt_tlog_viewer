# Tlog Görüntüleme Programı

Bu proje [mavlink paket yapısı](https://mavlink.io/en/guide/serialization.html) ile  [bu yöntem kullanılarak]("https://docs.qgroundcontrol.com/v4.4.3/en/qgc-dev-guide/file_formats/mavlink.html) kayıt alıntına alınmış telemetry verilerini
harita üzerinde görüntülemek ve verileri incelemek üzere geliştirilmiştir.

# Windows Derleme
## Derleme gereksinimleri
- Qt 5.15.2
  - QtLocation
  - QtPositioning
  - QtQml
  - QtQuick 2
  - QtWidgets
- Qt Creator (20.0.1)
- MinGW Derleyici

## Derleme Adımları
1. Qt Maintenance tools'dan 5.15.2 için gerekli mödüllerin kurulu olduğunu kontrol ediniz.
2. Qt Creator açınız
3. Proje Açınız, proje dizinine gelerek CMakeLists.txt dosyasını seçiniz.
4. derleme yöntemi seçiminde MinGW 64/32 bit seçiniz.
5. Derleme tuşuna basınız.

# Linux-Ubuntu Derleme
## Derleme Gereksinimleri
1. Git
2. C++ 17
3. G++ 11.4
4. Cmake 3.16
5. Qt 5.15.2 Developer araçları
    1. base
    2. base-tools
    3. chooser
    5. qmake
    6. declarative
    7. location
    8. positionning
    9. qml-location
    10. qml-position
    11. QtQml
    12. QtQuick 2.15

## Derleme Adımları
1. Derleme Gereksinimlerini Kurunuz.
```
sudo apt install -y \
    git \
    cmake \
    build-essential 

sudo apt install -y \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtchooser \
    qt5-qmake \
    qtdeclarative5-dev \
    qtlocation5-dev \
    qtpositioning5-dev

sudo apt install -y \
    qml-module-qtqml \
    qml-module-qtquick2 \
    qml-module-qtlocation \
    qml-module-qtpositioning \
```
2. Git üzerinden kodu indiriniz.
```
sudo apt install git
git clone https://github.com/bumutkaan/qt_tlog_viewer.git
cd qt_tlog_viewer
```
3. Derleyiniz
```
mkdir build
cd build
cmake ..
make
```
4. Çalıştırınız
```
./tlog_viewer
```

# Proje Geliştirilirken Kullanılan Kaynak Dokümanlar
- [Tlog Dosya Yapısı 1](https://github.com/flocked-agriculture/mavlink_log/blob/main/docs/tlog_file_format.md)
- [Mavlink Mesaj Paketi Yapısı](https://mavlink.io/en/guide/serialization.html)
- [Mavlink Mesaj Paketi SDK dokümanı](https://mavlink.io/en/mavgen_c/)
- [Mavlink Mesaj Paketi SDK](https://github.com/mavlink/c_library_v2)
- [.tlog Dosyası Üretilme Yöntemi](https://docs.qgroundcontrol.com/master/en/qgc-dev-guide/file_formats/mavlink.html)
- [Qt6 Qml Anlatım Dokümanları](https://doc.qt.io/qt-6/qtqml-index.html)
- [Qt 5.15.2 Qml Dokümanları](https://doc.qt.io/archives/qt-5.15/qmltypes.html)
- [Qt 5.15.2 C++ Dokümanları](https://doc.qt.io/archives/qt-5.15/classes.html)
