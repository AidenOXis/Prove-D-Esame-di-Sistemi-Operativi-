#include "monitor.h"
#include <stdio.h>
#include <unistd.h>

// Inizializza il monitor
void init_monitor(MonitorProdCons *m) {
    for (int i = 0; i < 5; ++i) {
        m->stato[i] = LIBERO;
    }
    m->elementi_liberi = 5;
    m->elementi_occupati = 0;
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cond_produttore, NULL);
    pthread_cond_init(&m->cond_consumatore, NULL);
}

// Distrugge il monitor
void destroy_monitor(MonitorProdCons *m) {
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->cond_produttore);
    pthread_cond_destroy(&m->cond_consumatore);
}

// Funzione del produttore
void produci_elementi(MonitorProdCons *m, int valori[], int numero_valori) {
    pthread_mutex_lock(&m->mutex);

    while (m->elementi_liberi < numero_valori) {
        pthread_cond_wait(&m->cond_produttore, &m->mutex);
    }

    int posizioni[5];
    int count = 0;
    for (int i = 0; i < 5 && count < numero_valori; ++i) {
        if (m->stato[i] == LIBERO) {
            m->stato[i] = IN_USO;
            posizioni[count++] = i;
        }
    }
    m->elementi_liberi -= numero_valori;

    pthread_mutex_unlock(&m->mutex);

    for (int i = 0; i < count; ++i) {
        int pos = posizioni[i];
        m->elementi[pos] = valori[i];
        sleep(1);
        printf("Prodotto valore %d in posizione %d\n", valori[i], pos);
    }

    pthread_mutex_lock(&m->mutex);
    for (int i = 0; i < count; ++i) {
        m->stato[posizioni[i]] = OCCUPATO;
    }
    m->elementi_occupati += numero_valori;

    pthread_cond_broadcast(&m->cond_consumatore);
    pthread_mutex_unlock(&m->mutex);
}

// Funzione del consumatore
int consuma_elemento(MonitorProdCons *m) {
    pthread_mutex_lock(&m->mutex);

    while (m->elementi_occupati == 0) {
        pthread_cond_wait(&m->cond_consumatore, &m->mutex);
    }

    int valore = -1, pos = -1;
    for (int i = 0; i < 5; ++i) {
        if (m->stato[i] == OCCUPATO) {
            pos = i;
            valore = m->elementi[i];
            m->stato[i] = LIBERO;
            break;
        }
    }
    m->elementi_occupati--;
    m->elementi_liberi++;

    pthread_cond_signal(&m->cond_produttore);
    pthread_mutex_unlock(&m->mutex);

    sleep(1);
    printf("Consumato valore %d dalla posizione %d\n", valore, pos);
    return valore;
}