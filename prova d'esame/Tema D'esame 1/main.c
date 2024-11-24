#include "monitor.h"
#include "produttore.h"
#include "consumatore.h"
#include <pthread.h>
#include <stdio.h>

int main() {
    pthread_t produttore, consumatori[3];
    MonitorProdCons monitor;

    init_monitor(&monitor);

    pthread_create(&produttore, NULL, thread_produttore, (void *)&monitor);
    for (int i = 0; i < 3; ++i) {
        pthread_create(&consumatori[i], NULL, thread_consumatore, (void *)&monitor);
    }

    pthread_join(produttore, NULL);
    for (int i = 0; i < 3; ++i) {
        pthread_join(consumatori[i], NULL);
    }

    destroy_monitor(&monitor);

    return 0;
}