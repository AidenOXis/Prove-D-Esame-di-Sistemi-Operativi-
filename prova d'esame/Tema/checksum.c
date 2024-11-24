#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "message.h"

int main(){
    int input_queue = msgget(FILTER_QUEUE_KEY,IPC_CREAT | 0664); //ottenere la coda di messaggi dal filtro 
    if(input_queue ==-1){
        perror("Errore apertura coda di input"); 
        exit(1); 
    }
    int output_queue=msgget(CHECKSUM_QUEUE_KEY,IPC_CREAT |0664); 
    if(output_queue==-1){
        perror("Errore apertura coda di output"); 
        exit(1); 
    }
    for(int i=0; i<6; i++){
        //Ricezione di 6 messaggi 
        Messaggio msg; 
        int ret; 
        ret = msgrcv(input_queue,&msg,sizeof(Messaggio)-sizeof(long),0,0); 
        if(ret == -1){
            perror("Errore ricezione messaggio"); 
            exit(1); 
        }
        int somma = 0 ; 
        for(int j=0; j<9; j++){
            somma += msg.stringa[j]; 
        }
        somma += msg.array[0] + msg.array[1]; 
        msg.checksum = somma; 
        ret = msgsnd(output_queue,&msg,sizeof(Messaggio)-sizeof(long),0);
        if(ret ==-1){
            perror("Errore"); 
            exit(1); 
        }
        printf("Checksum: elaborato messaggio con checksum %d\n",msg.checksum);
    }
    return 0; 
}