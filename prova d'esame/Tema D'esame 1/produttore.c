#include "produttore.h"

void *thread_produttore(void *arg) {
    MonitorProdCons *m = (MonitorProdCons *)arg;
    int valori[5] = {10, 20, 30, 40, 50};

    produci_elementi(m, valori, 5);
    produci_elementi(m, valori, 4);
    produci_elementi(m, valori, 3);
    produci_elementi(m, valori, 2);
    produci_elementi(m, valori, 1);

    return NULL;
}