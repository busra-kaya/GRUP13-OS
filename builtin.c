/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include "signals.h"

// Kullanıcının girdiği komutun yerleşik bir komut olup olmadığını kontrol eder.
// Eğer "quit" komutu girilmişse true, aksi takdirde false döner.
bool yerlesik_komut_mu(const char *komut) {
    return (strcmp(komut, "quit") == 0);
}

// "quit" komutunun işlenmesi.
// Arka planda çalışan işlemler varsa, işlemler tamamlanana kadar beklenir.
// Ardından kabuk uygulaması güvenli bir şekilde sonlandırılır.
void quit_komutunu_isle() {
    printf("Quit komutu alındı. Arka plan işlemleri bekleniyor...\n");

    // Yeni komut kabul etmeyi durdur.
    printf("Yeni komut kabul edilmiyor.\n");

    // Arka plan işlemlerinin tamamlanmasını bekle.
    while (arka_plan_islem_sayisini_getir() > 0) {
        arka_plan_islemleri_kontrol_et();
        sleep(1); // Arka plan işlemleri için kısa süre bekle.
    }

    printf("Tüm arka plan işlemleri tamamlandı. Kabuk kapatılıyor...\n");
    exit(0); // Kabuktan çıkış.
}

