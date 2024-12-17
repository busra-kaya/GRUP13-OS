/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "pipeparser.h"
#include "pipe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "parser.h"
#include "executor.h"
#include "signals.h"
#include "io_redirect.h"
#include "builtin.h"
#include <fcntl.h>  // O_RDONLY gibi dosya erişim modları için
#include <unistd.h> // dup2 ve diğer sistem çağrıları için

#define MAX_KOMUT_UZUNLUGU 1024
#define MAX_ARGUMAN_SAYISI 128
#define MAX_KOMUT_SAYISI 128

// Prompt yazdırma fonksiyonu
void prompt_yazdir() {
    printf("> ");
    fflush(stdout);
}

int main() {
    char girdi[MAX_KOMUT_UZUNLUGU];
    char *argumanlar[MAX_ARGUMAN_SAYISI];
    char *komutlar[MAX_KOMUT_SAYISI];

    // Sinyal işleyicilerini ayarla
    sinyal_yoneticisi_ayarla();

    printf("Basit Kabuk Uygulaması\n");
    printf("Çıkış yapmak için 'quit' komutunu kullanabilirsiniz.\n");

    while (1) {
        // Prompt yazdır
        prompt_yazdir();

        // Kullanıcıdan giriş al
        if (fgets(girdi, sizeof(girdi), stdin) == NULL) {
            perror("Girdi alınamadı");
            break;
        }

        // Komuttaki gereksiz boşlukları ve satır sonunu temizle
        if (strlen(girdi) > 0 && girdi[strlen(girdi) - 1] == '\n') {
            girdi[strlen(girdi) - 1] = '\0';
        }

        // Eğer komut boşsa tekrar prompt göster
        if (strlen(girdi) == 0) {
            continue;
        }

        // Pipe işlemi kontrolü ve işleme
        char* pipe_commands[10];
        int pipe_command_count = 0;
        pipe_komut_ayristir(girdi, pipe_commands, &pipe_command_count);

        if (pipe_command_count > 1) {
            // Pipe ile bağlanmış komutları çalıştır
            if (!pipe_komutlari_yurut(pipe_commands, pipe_command_count)) {
                fprintf(stderr, "Pipe işlemi başarısız oldu.\n");
            }
            continue; // Pipe işlemi tamamlandığında diğer işlemleri atla
        }

        // Komutları ayır
        komutlari_ayir(girdi, komutlar);

        // Ayrılmış her komutu sırayla işle
        for (int i = 0; komutlar[i] != NULL; i++) {
            // Argümanları ayıkla
            komut_ayikla(komutlar[i], argumanlar);

            // Yerleşik komutları kontrol et
            if (yerlesik_komut_mu(argumanlar[0])) {
                quit_komutunu_isle();
                continue;
            }

            // Giriş/çıkış yönlendirme işlemleri
            int stdin_kopya = dup(STDIN_FILENO); // stdin yedeği
            int stdout_kopya = dup(STDOUT_FILENO); // stdout yedeği
            bool yonlendirme_basarili = true;

            for (int j = 0; argumanlar[j] != NULL; j++) {
                if (strcmp(argumanlar[j], "<") == 0) {
                    // Giriş dosyası yönlendirmesi
                    int girdi_dosyasi = open(argumanlar[j + 1], O_RDONLY);
                    if (girdi_dosyasi == -1) {
                        fprintf(stderr, "%s giriş dosyası bulunamadı.\n", argumanlar[j + 1]);
                        yonlendirme_basarili = false;
                        break;
                    }
                    dup2(girdi_dosyasi, STDIN_FILENO);
                    close(girdi_dosyasi);
                    argumanlar[j] = NULL; // Yönlendirme işaretini temizle
                } else if (strcmp(argumanlar[j], ">") == 0) {
                    // Çıkış dosyası yönlendirmesi
                    if (!cikis_yonlendirme(argumanlar[j + 1])) {
                        fprintf(stderr, "Çıkış yönlendirme başarısız oldu: %s\n", argumanlar[j + 1]);
                        yonlendirme_basarili = false;
                        break;
                    }
                    argumanlar[j] = NULL; // Yönlendirme işaretini temizle
                } else if (strcmp(argumanlar[j], ">>") == 0) {
                    // Ekleme yönlendirme işlemi
                    if (!ekle_yonlendirme(argumanlar[j + 1])) {
                        fprintf(stderr, "Ekleme yönlendirme başarısız oldu: %s\n", argumanlar[j + 1]);
                        yonlendirme_basarili = false;
                        break;
                    }
                    argumanlar[j] = NULL; // Yönlendirme işaretini temizle
                }
            }

            if (!yonlendirme_basarili) {
                // Orijinal stdin ve stdout'u geri yükle
                dup2(stdin_kopya, STDIN_FILENO);
                dup2(stdout_kopya, STDOUT_FILENO);
                close(stdin_kopya);
                close(stdout_kopya);
                continue;
            }

            // Arka plan işlemleri kontrolü
            int arguman_sayisi = 0;
            while (argumanlar[arguman_sayisi] != NULL) {
                arguman_sayisi++;
            }

            if (arguman_sayisi > 1 && strcmp(argumanlar[arguman_sayisi - 1], "&") == 0) {
                // Arka planda çalıştır
                argumanlar[arguman_sayisi - 1] = NULL;
                arka_plan_komut_yurut(argumanlar);
            } else {
                // Komut çalıştır
                komut_yurut(argumanlar);
            }

            // Orijinal stdin ve stdout'u geri yükle
            dup2(stdin_kopya, STDIN_FILENO);
            dup2(stdout_kopya, STDOUT_FILENO);
            close(stdin_kopya);
            close(stdout_kopya);

            // Argümanları temizle
            arguman_bosalt(argumanlar);
        }

        // Ayrılmış komutları temizle
        komutlari_bosalt(komutlar);
    }

    printf("Kabuk kapatılıyor...\n");
    return 0;
}


