/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "signals.h"

// Tek bir komutu yürütür.
// argumanlar: Komut ve argümanların bulunduğu dizi.
void komut_yurut(char **argumanlar) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork hatası");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Çocuk süreç içinde komut çalıştırılıyor.
        execvp(argumanlar[0], argumanlar);
        perror("Komut çalıştırılamadı");
        exit(EXIT_FAILURE);
    } else {
        // Ana süreç alt sürecin tamamlanmasını bekliyor.
        int durum;
        waitpid(pid, &durum, 0);
        if (WIFSIGNALED(durum)) {
            fprintf(stderr, "[PID %d] İşlem sinyal ile sonlandı, sinyal: %d\n", pid, WTERMSIG(durum));
        }
    }
}

// Bir komutu arka planda yürütür.
// argumanlar: Komut ve argümanların bulunduğu dizi.
void arka_plan_komut_yurut(char **argumanlar) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork hatası");
        return;
    }

    if (pid == 0) {
        // Çocuk süreç içinde komut çalıştırılıyor.
        execvp(argumanlar[0], argumanlar);
        perror("Komut çalıştırılamadı");
        exit(EXIT_FAILURE);
    } else {
        // Ana süreç arka plan işlem listesine PID ekliyor.
        arka_plan_islemi_ekle(pid);
    }
}

