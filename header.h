#ifndef HEADER_H
# define HEADER_H

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct{
    char rue[20];
    char ville[20];
    char pays[20];
}adresses;

typedef struct{
    char nom[20];
    char prenom[20];
    int gsm;
    char email[50];
    adresses adresse;
}contacts;

contacts ajouter();

#endif