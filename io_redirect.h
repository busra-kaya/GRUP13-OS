/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef IO_REDIRECT_H
#define IO_REDIRECT_H

#include <stdbool.h>

// Giriş yönlendirme işlemi (< operatörü).
// dosya_adi: Girdinin alınacağı dosya adı.
// Başarılı olursa true, başarısız olursa false döner.
bool giris_yonlendirme(const char *dosya_adi);

// Çıkış yönlendirme işlemi (> operatörü).
// dosya_adi: Çıktının yazılacağı dosya adı.
// Başarılı olursa true, başarısız olursa false döner.
bool cikis_yonlendirme(const char *dosya_adi);

// Append (>> operatörü) için çıkış yönlendirme işlemi.
// dosya_adi: Çıktının ekleneceği dosya adı.
// Başarılı olursa true, başarısız olursa false döner.
bool ekle_yonlendirme(const char *dosya_adi);

#endif // IO_REDIRECT_H
