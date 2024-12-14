/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Arka plan işlemlerini tutacak yapı.
static pid_t arka_plan_islemleri[128];
static int arka_plan_islem_sayisi = 0;

// SIGINT (Ctrl+C) sinyalini işler.
// sinyal: SIGINT sinyal değeri.
void sigint_isleyici(int sinyal) {
    printf("\nCtrl+C sinyali alındı. Ancak kabuk çalışmaya devam ediyor.\n");
    printf("> ");
    fflush(stdout);
}

// SIGCHLD sinyalini işler. Arka plan işlemlerinin durumunu kontrol eder.
// sinyal: SIGCHLD sinyal değeri.
void sigchld_isleyici(int sinyal) {
    int durum;
    pid_t tamamlanan_pid;

    while ((tamamlanan_pid = waitpid(-1, &durum, WNOHANG)) > 0) {
        if (WIFEXITED(durum)) {
            printf("\n[PID %d] retval: %d\n", tamamlanan_pid, WEXITSTATUS(durum));
        } else if (WIFSIGNALED(durum)) {
            printf("\n[PID %d] İşlem sinyal ile sonlandı, sinyal: %d\n", tamamlanan_pid, WTERMSIG(durum));
        }

        // Prompt yeniden yazdır.
        printf("> ");
        fflush(stdout);

        // Arka plan listesinden işlem kaldır.
        for (int i = 0; i < arka_plan_islem_sayisi; i++) {
            if (arka_plan_islemleri[i] == tamamlanan_pid) {
                arka_plan_islemleri[i] = 0;
                break;
            }
        }
    }
}

// Sinyal işleyicilerini ayarlar.
void sinyal_yoneticisi_ayarla() {
    struct sigaction sigint_ayari;
    struct sigaction sigchld_ayari;

    // SIGINT (Ctrl+C) ayarı.
    sigint_ayari.sa_handler = sigint_isleyici;
    sigemptyset(&sigint_ayari.sa_mask);
    sigint_ayari.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sigint_ayari, NULL) == -1) {
        perror("SIGINT sinyali ayarlanamadı");
        exit(EXIT_FAILURE);
    }

    // SIGCHLD (Çocuk süreçlerin tamamlanması) ayarı.
    sigchld_ayari.sa_handler = sigchld_isleyici;
    sigemptyset(&sigchld_ayari.sa_mask);
    sigchld_ayari.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sigchld_ayari, NULL) == -1) {
        perror("SIGCHLD sinyali ayarlanamadı");
        exit(EXIT_FAILURE);
    }
}

// Yeni bir arka plan işlemi ekler.
// pid: Arka plan işleminin PID'si.
void arka_plan_islemi_ekle(pid_t pid) {
    if (arka_plan_islem_sayisi < 128) {
        arka_plan_islemleri[arka_plan_islem_sayisi++] = pid;
    } else {
        fprintf(stderr, "Arka plan işlemleri kapasitesi doldu. Lütfen mevcut işlemlerin tamamlanmasını bekleyin.\n");
    }
}

// Arka plan işlemlerinin listesini düzenler ve tamamlananları kaldırır.
void arka_plan_islemleri_kontrol_et() {
    int yeni_sayac = 0;
    for (int i = 0; i < arka_plan_islem_sayisi; i++) {
        if (arka_plan_islemleri[i] != 0) {
            arka_plan_islemleri[yeni_sayac++] = arka_plan_islemleri[i];
        }
    }
    arka_plan_islem_sayisi = yeni_sayac;
}

// Arka plan işlem sayısını döndürür.
// return: Arka plan işlemlerinin sayısı.
int arka_plan_islem_sayisini_getir(void) {
    return arka_plan_islem_sayisi;
}
