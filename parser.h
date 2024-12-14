/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef PARSER_H
#define PARSER_H

// Kullanıcı komutunu parçalar ve argümanları ayırır.
// girdi: Kullanıcı tarafından girilen komut.
// argumanlar: Parçalanmış komut ve argümanların dizisi.
void komut_ayikla(const char *girdi, char **argumanlar);

// Girdi komutlarını ayırır.
// girdi: Kullanıcıdan alınan tam komut.
// komutlar: Noktalı virgül (;) ile ayrılmış komutlar dizisi.
void komutlari_ayir(const char *girdi, char ***komutlar);

// Argümanlar için tahsis edilen belleği temizler.
// argumanlar: Komut ve argümanlar dizisi.
void arguman_bosalt(char **argumanlar);

// Komutlar için tahsis edilen belleği temizler.
// komutlar: Ayrılmış komutlar dizisi.
void komutlari_bosalt(char ***komutlar);

#endif // PARSER_H

