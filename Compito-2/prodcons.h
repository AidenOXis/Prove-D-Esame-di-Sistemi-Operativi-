#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define DIM 4

typedef int Frame[2][2];

typedef struct {

    Frame vettore[DIM];

    /* TBD: Completare la struttura dati monitor */
    pthread_mutex_t mutex; 
    pthread_cond_t cv_produttore; 
    pthread_cond_t cv_consumatore; 
    int testa; 
    int coda; 
    int count; 

} MonitorStreaming;

void inizializza(MonitorStreaming * m);
int produci(MonitorStreaming * m, Frame f);
void consuma(MonitorStreaming * m, Frame f);
void flush(MonitorStreaming * m);
void distruggi(MonitorStreaming * m);

#endif