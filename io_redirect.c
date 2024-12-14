/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "io_redirect.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Giriş yönlendirme işlemi yapar (< operatörü).
// dosya_adi: Girdinin alınacağı dosya adı.
// Başarılı olursa true, başarısız olursa false döner.
bool giris_yonlendirme(const char *dosya_adi) {
    int dosya = open(dosya_adi, O_RDONLY); // Dosyayı yalnızca okuma modunda aç
    if (dosya == -1) {
        perror("Giriş dosyası açılamadı");
        return false;
    }

    if (dup2(dosya, STDIN_FILENO) == -1) {
        perror("Giriş yönlendirme başarısız");
        close(dosya);
        return false;
    }

    close(dosya); // Dosya tanımlayıcısını kapat
    return true;
}

// Çıkış yönlendirme işlemi yapar (> operatörü).
// dosya_adi: Çıktının yazılacağı dosya adı.
// Başarılı olursa true, başarısız olursa false döner.
bool cikis_yonlendirme(const char *dosya_adi) {
    int dosya = open(dosya_adi, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dosya == -1) {
        perror("Çıkış dosyası açılamadı");
        return false;
    }

    if (dup2(dosya, STDOUT_FILENO) == -1) {
        perror("Çıkış yönlendirme başarısız");
        close(dosya);
        return false;
    }

    close(dosya);
    return true;
}

// Append (>> operatörü) için çıkış yönlendirme işlemi yapar.
// dosya_adi: Çıktının ekleneceği dosya adı.
// Başarılı olursa true, başarısız olursa false döner.
bool ekle_yonlendirme(const char *dosya_adi) {
    int dosya = open(dosya_adi, O_WRONLY | O_CREAT | O_APPEND, 0644); // Dosyayı yazma modunda aç veya ekleme modunda oluştur
    if (dosya == -1) {
        perror("Çıkış dosyası açılamadı");
        return false;
    }

    // Standart çıktıyı (STDOUT) dosyaya yönlendir
    if (dup2(dosya, STDOUT_FILENO) == -1) {
        perror("Ekleme yönlendirmesi başarısız");
        close(dosya); // Deskriptörü kapat
        return false;
    }

    close(dosya); // Kullanımdan sonra dosya deskriptörünü kapat
    return true;
}

