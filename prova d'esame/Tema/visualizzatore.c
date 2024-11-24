#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "message.h"

int main(){
    int msgid = msgget(CHECKSUM_QUEUE_KEY,IPC_CREAT|0664); 
    if(msgid == -1){
        perror("Errore apertura coda di messaggi");
        exit(1); 
    }
    for(int i =0; i<6; i++){
        //Ricezione dei 6 messaggi
        Messaggio msg; 
        int ret; 
        ret=msgrcv(msgid,&msg,sizeof(Messaggio)-sizeof(long),0,0);
        if(ret ==-1){
            printf("Errore");
            exit(1); 
        }
        printf("Visualizzatore:ricevuto messaggio:\n");
        printf("Stringa: %s\n",msg.stringa);
        printf("Array: [%d,%d]\n",msg.array[0],msg.array[1]);
        printf("Checksum:%d\n",msg.checksum);
    }
    return 0; 
}