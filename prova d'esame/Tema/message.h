#ifndef MESSAGE_H
#define MESSAGE_H

//definisco delle macro 
#define MESSAGE_QUEUE_KEY 12345
#define FILTER_QUEUE_KEY 12346
#define CHECKSUM_QUEUE_KEY 12347

#include <sys/types.h>
 
//Creiamo la struttura del messaggio 
typedef struct {
    long type; //necessario per le code dei messaggi
    char stringa[10]; 
    int array[2]; 
    int checksum;
} Messaggio; 
#endif