# Linity OS

## Supported Architectures

| Architecture | Status | Boot Protocol |
|---|---|---|
| x86_64 | In development | Limine |
## Proje Durumu

Proje aktif geliştirme aşamasındadır. Şu anda bellek yönetimi üzerinde çalışıyorum.
## Proje Hedefleri

* Çoklu mimari desteği
* İşletim sistemi mantığını anlamak
* POSIX desteği
* UNIX felsefesine sadık kalmak
* DOOM çalıştırmak

## Planlanan Bileşenler
* Memory Management Unit
* Scheduler
* Driver Support
* Basic Drivers
* Shell
* POSIX Support

## Kaynak Kodunu İndirme

Projeyi Git ile klonlayın:

```bash
git clone https://github.com/Xolmir/Linity-OS.git
cd Linity-OS
```

## Gereksinimler

Projeyi derlemek için aşağıdaki araçlara ihtiyaç vardır:

* GCC
* GNU ld
* objcopy
* NASM
* QEMU
* xorriso
* tar
* curl
* make

> [!NOTE]
> Eğer kullandığınız derleyici araçları hedef mimari için kod üretemiyorsa, `gcc`, `ld` ve `objcopy` araçlarını uygun cross-compiler sürümleriyle değiştirmeniz gerekebilir.

## Make Hedefleri

| Komut         | Açıklama                                                   |
| ------------- | ---------------------------------------------------------- |
| `make`        | Projeyi derler                                             |
| `make run`    | İşletim sistemini QEMU ile çalıştırır                      |
| `make kernel` | Yalnızca çekirdeği derler                                  |
| `make iso`    | Önyüklenebilir ISO dosyasını oluşturur                     |
| `make doctor` | Eksik geliştirme araçlarını ve bağımlılıkları kontrol eder |
| `make clean`  | Derleme sonucunda oluşturulan dosyaları temizler           |

## Proje Dizinleri ve Dosyaları

| Dizin         | Açıklama                                                   |
| ------------- | ---------------------------------------------------------- |
| `arch/` | Mimariye özel kodları içerir |
| `boot/` | Önyükleme için kullanılacak mimariye özel dosyaları içerir |
| `include/` | Mimariye ve çekirdeğe ait başlık dosyalarını içerir |
| `kernel/` | Mümkün olduğunca donanımdan bağımsız çekirdek kodlarını içerir |
| `toolchain/` | Gerekli araç zincirleri bu dizine indirilir |
| `makefile` | Ana derleme dosyası |

## Kullanım Uyarısı
> [!WARNING]
> Linity OS henüz günlük kullanım için uygun değil. Gerçek donanımda test etmek tamamen sizin sorumluluğunuzdadır.

## Lisans

Bu proje **GNU General Public License v3.0** altında lisanslanmıştır.

Ayrıntılı bilgi için [`LICENSE`](LICENSE) dosyasına bakabilirsiniz.
