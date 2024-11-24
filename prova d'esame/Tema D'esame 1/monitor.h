#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>

// Definizione degli stati
#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

// Struttura del monitor
typedef struct {
    int elementi[5];
    int stato[5];
    int elementi_liberi;
    int elementi_occupati;

    pthread_mutex_t mutex;
    pthread_cond_t cond_produttore;
    pthread_cond_t cond_consumatore;
} MonitorProdCons;

// Dichiarazione delle funzioni
void init_monitor(MonitorProdCons *m);
void destroy_monitor(MonitorProdCons *m);
void produci_elementi(MonitorProdCons *m, int valori[], int numero_valori);
int consuma_elemento(MonitorProdCons *m);

#endif