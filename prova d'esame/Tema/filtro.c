#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "message.h"

int main(){
    int input_queue= msgget(MESSAGE_QUEUE_KEY,IPC_CREAT|0666); //ottenere la coda di messaggi
    if(input_queue == -1){
        perror("Errore apertura coda di input"); 
        exit(1);
    }
    int output_queue = msgget(FILTER_QUEUE_KEY,IPC_CREAT|0666); //prendere la coda di messaggi per il filtro 
    if(output_queue == -1){
        perror("Errore apertura di coda di output");
        exit(1); 
    }
    for(int i =0; i<6;i++){
        //ricezione dei 6 messaggi
        Messaggio msg; 
        int ret; 
        ret = msgrcv(input_queue,&msg,sizeof(Messaggio)-sizeof(long),0,0);
        if(ret ==-1)
        {
            perror("Errore ricezione del messaggio"); 
            exit(1);
        }
        if(strchr(msg.stringa,'x')==NULL){
            ret = msgsnd(output_queue,&msg,sizeof(Messaggio)-sizeof(long),0);
            if(ret == -1){
                perror("Errore invio messaggio"); 
                exit(1); 
            }
            printf("Filtro: inoltrato messaggio con stringa %s\n",msg.stringa); 
        }else {
            printf("Filtro: scartato messaggio con stringa %s\n",msg.stringa);
        }
    }
    return 0 ; 

}