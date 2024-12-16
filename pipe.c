/*Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

Dursun Özer - B231210301 - 1. Öğretim A Grubu

Büşra Kaya – B201210045 – 1. Öğretim C Grubu
*/

#include "pipe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Pipe (boru) kullanarak birden fazla komutu sıralı bir şekilde yürütür.
// komutlar: Yürütülecek komutların bulunduğu dizi.
// komut_sayisi: Yürütülecek toplam komut sayısı.
// Başarılı olursa true, hata durumunda false döner.
bool pipe_komutlari_yurut(char* komutlar[], int komut_sayisi) {
    int pipe_fds[2]; // Pipe okuma ve yazma uçları
    int onceki_fd = -1; // Önceki komutun çıkışı için kullanılacak dosya tanımlayıcı

    for (int i = 0; i < komut_sayisi; i++) {
        if (pipe(pipe_fds) == -1) {
            perror("Boru oluşturulamadı");
            return false;
        }

        pid_t surec_id = fork();
        if (surec_id < 0) {
            perror("fork başarısız");
            return false;
        }

        if (surec_id == 0) {
            // Alt süreç (child process)
            if (onceki_fd != -1) {
                // Önceki komutun çıkışını bu komutun girdisine bağla
                if (dup2(onceki_fd, STDIN_FILENO) == -1) {
                    perror("dup2 (stdin) başarısız");
                    exit(EXIT_FAILURE);
                }
            }

            if (i < komut_sayisi - 1) {
                // Çıktıyı pipe'ın yazma ucuna bağla
                if (dup2(pipe_fds[1], STDOUT_FILENO) == -1) {
                    perror("dup2 (stdout) başarısız");
                    exit(EXIT_FAILURE);
                }
            }

            // Kullanılmayan dosya tanımlayıcılarını kapat
            close(pipe_fds[0]);
            close(pipe_fds[1]);

            // Komutu çalıştır
            char* argumanlar[10];
            char* bolum = strtok(komutlar[i], " ");
            int j = 0;
            while (bolum != NULL && j < 9) {
                argumanlar[j++] = bolum;
                bolum = strtok(NULL, " ");
            }
            argumanlar[j] = NULL;

            if (execvp(argumanlar[0], argumanlar) == -1) {
                perror("execvp başarısız");
                exit(EXIT_FAILURE);
            }
        } else {
            // Ana süreç (parent process)
            waitpid(surec_id, NULL, 0); // Alt sürecin tamamlanmasını bekle
            close(pipe_fds[1]);         // Yazma ucunu kapat
            if (onceki_fd != -1) {
                close(onceki_fd);       // Önceki dosya tanımlayıcısını kapat
            }
            onceki_fd = pipe_fds[0];    // Okuma ucunu bir sonraki komut için sakla
        }
    }

    return true;
}

