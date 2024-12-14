/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Kullanıcı komutunu parçalar ve argümanları ayırır.
// girdi: Kullanıcı tarafından girilen tam komut.
// argumanlar: Parçalanmış komut ve argümanların tutulduğu dizi.
void komut_ayikla(const char *girdi, char **argumanlar) {
    char *gecici = strdup(girdi);
    char *token = strtok(gecici, " \t\n");
    int indeks = 0;

    while (token != NULL) {
        argumanlar[indeks++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }
    argumanlar[indeks] = NULL;

    free(gecici);
}

// Girdi komutlarını ayırır.
// girdi: Kullanıcı tarafından girilen tam komut.
// komutlar: Noktalı virgül (;) ile ayrılmış komutların tutulduğu dizi.
void komutlari_ayir(const char *girdi, char ***komutlar) {
    char *gecici = strdup(girdi);
    char *token = strtok(gecici, ";");
    int indeks = 0;

    while (token != NULL) {
        komutlar[indeks++] = strdup(token);
        token = strtok(NULL, ";");
    }
    komutlar[indeks] = NULL;

    free(gecici);
}

// Argümanlar için tahsis edilen belleği temizler.
// argumanlar: Komut ve argümanların tutulduğu dizi.
void arguman_bosalt(char **argumanlar) {
    for (int i = 0; argumanlar[i] != NULL; i++) {
        free(argumanlar[i]);
    }
}

// Komutlar için tahsis edilen belleği temizler.
// komutlar: Ayrılmış komutların tutulduğu dizi.
void komutlari_bosalt(char ***komutlar) {
    for (int i = 0; komutlar[i] != NULL; i++) {
        free(komutlar[i]);
    }
}

