#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Avvia 3 processi generatore
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            execl("./generatore", "generatore", NULL);
            perror("Errore avvio generatore");
            exit(1);
        }
    }

    // Avvia il filtro
    if (fork() == 0) {
        execl("./filtro", "filtro", NULL);
        perror("Errore avvio filtro");
        exit(1);
    }

    // Avvia il checksum
    if (fork() == 0) {
        execl("./checksum", "checksum", NULL);
        perror("Errore avvio checksum");
        exit(1);
    }

    // Avvia il visualizzatore
    if (fork() == 0) {
        execl("./visualizzatore", "visualizzatore", NULL);
        perror("Errore avvio visualizzatore");
        exit(1);
    }

    // Attendi la terminazione dei processi
    for (int i = 0; i < 7; i++) {
        wait(NULL);
    }

    return 0;
}