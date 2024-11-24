#include "consumatore.h"

void *thread_consumatore(void *arg) {
    MonitorProdCons *m = (MonitorProdCons *)arg;

    for (int i = 0; i < 5; ++i) {
        consuma_elemento(m);
    }

    return NULL;
}