/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdbool.h>

// Kullanıcının girdiği komutun yerleşik bir komut olup olmadığını kontrol eder.
// komut: Kullanıcının girdiği komut metni.
// true dönerse komut yerleşik bir komuttur, false dönerse değildir.
bool yerlesik_komut_mu(const char *komut);

// Yerleşik bir komutun işlenmesini sağlar.
// argumanlar: Komutun argümanlarının bulunduğu dizi.
void yerlesik_komut_isle(char **argumanlar);

// "quit" komutunu işler ve kabuk uygulamasını güvenli bir şekilde kapatır.
// Eğer arka plan işlemleri varsa, tamamlanana kadar beklenir.
void quit_komutunu_isle();

#endif // BUILTIN_H
