/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef PIPEPARSER_H
#define PIPEPARSER_H

// Kullanıcı girişini analiz ederek pipe ile bağlanmış komutları ayrıştırır.
// giris: Kullanıcıdan alınan tam komut metni.
// komutlar: Ayrıştırılmış komutların tutulacağı dizi.
// komut_sayisi: Ayrıştırılan toplam komut sayısını döndürmek için bir işaretçi.
void pipe_komut_ayristir(char* giris, char* komutlar[], int* komut_sayisi);

#endif // PIPEPARSER_H

