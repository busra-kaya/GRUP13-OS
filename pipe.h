/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef PIPE_H
#define PIPE_H

#include <stdbool.h>

// Pipe (boru) kullanarak birden fazla komutu sıralı bir şekilde yürütür.
// komutlar: Pipe ile bağlanacak komutların listesi (dizi olarak).
// komut_sayisi: Yürütülecek toplam komut sayısı.
// Başarılı olursa true, hata durumunda false döner.
bool pipe_komutlari_yurut(char* komutlar[], int komut_sayisi);

#endif // PIPE_H

