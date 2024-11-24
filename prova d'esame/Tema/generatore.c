#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "message.h"

//Genera una stringa causale
void genera_stringa_casuale(char *str){
    for(int i = 0; i<9; i++){
        str[i]=(rand()%94)+32; 
    }
    str[9]='\0'; //Carattere terminatore
}
int main(){
    int msgid = msgget(MESSAGE_QUEUE_KEY,IPC_CREAT |0664); //Ottenere la coda dei messaggi
    if(msgid==-1){
        perror("Errore generazione msgid"); 
        exit(1); 
    }
    for(int i=0; i<2; i++){
        //Invio di 2 messaggi
        Messaggio msg; 
        msg.type=1; 
        genera_stringa_casuale(msg.stringa); 
        msg.array[0]=rand()%10; 
        msg.array[1]=rand()%10; 
        msg.checksum=0; 
        int ret= msgsnd(msgid,&msg,sizeof(Messaggio)-sizeof(long),0); //Inviare il messaggio 
        if(ret < 0 ){
            perror("Errore invio messaggio");
            exit(1); 
        }
    printf("Generatore: inviato messaggio con stringa %s\n",msg.stringa); 
    }
    return 0; 
}