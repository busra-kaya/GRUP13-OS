/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef EXECUTOR_H
#define EXECUTOR_H

// Tek bir komutu yürütür.
// argumanlar: Komut ve argümanların bulunduğu dizi.
void komut_yurut(char **argumanlar);

// Bir komutu arka planda yürütür.
// argumanlar: Komut ve argümanların bulunduğu dizi.
void arka_plan_komut_yurut(char **argumanlar);

#endif // EXECUTOR_H

