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
1. Qt Creator açınız
2. Proje Açınız, proje dizinine gelerek CMakeLists.txt dosyasını seçiniz.
3. derleme yöntemi seçiminde MinGW 64/32 bit seçiniz.
4. Derleme tuşuna basınız.


