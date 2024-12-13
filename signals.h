/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#ifndef SIGNALS_H
#define SIGNALS_H

#include <sys/types.h> // pid_t tipi için gerekli

// SIGINT (Ctrl+C) sinyal işleyicisinin prototipi.
// sinyal: SIGINT sinyal değeri.
void sigint_isleyici(int sinyal);

// SIGCHLD sinyal işleyicisinin prototipi.
// sinyal: SIGCHLD sinyal değeri.
void sigchld_isleyici(int sinyal);

// Sinyal işleyicilerini ayarlar.
void sinyal_yoneticisi_ayarla(void);

// Yeni bir arka plan işlemini listeye ekler.
// pid: Arka plan işleminin PID'si.
void arka_plan_islemi_ekle(pid_t pid);

// Arka plan işlemlerini kontrol eder ve tamamlananları kaldırır.
void arka_plan_islemleri_kontrol_et(void);

// Arka plan işlem sayısını döndürür.
// return: Arka plan işlemlerinin sayısı.
int arka_plan_islem_sayisini_getir(void);

#endif // SIGNALS_H

