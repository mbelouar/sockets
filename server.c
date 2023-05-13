#include "header.h"

int main()
{
    printf("----------------SERVEUR-------------\n");
    int serverSOCKET=socket(AF_INET,SOCK_STREAM,0);

    if(serverSOCKET >= 0)
        printf("-->Socket cree avec ID:%d\n", serverSOCKET);
    else
    {
        printf("!!!Socket non cree!!!\n");
        exit(0);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5001);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSOCKET, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) >= 0)
        printf("-->Binded succesfully\n");
    else
    {
        printf("!!!Not Binded!!!\n");
        exit(0);
    }

    if (listen(serverSOCKET, 1) == 0)
        printf("-->Listening...\n");
   
    struct sockaddr_in connectedd;
    memset(&connectedd, 0, sizeof(connectedd));

    int clientaddrlen = 0;

    int connection = accept(serverSOCKET, (struct sockaddr*)&connectedd, &clientaddrlen);
    if (connection != -1)
        printf("serveur et client connecte\n");

    char type[20];
    char nom[20],mdp[20];
    char rMdp[20],rType[20];
    int choix,flag,i;
    contacts contact, contacte;

    char loginName[20];
    memset(loginName, 0, sizeof(loginName));

    recv(connection, loginName, 20, 0);
    
    FILE* f = fopen("comptes.txt","r");
    if (f == NULL)
        printf("fichier comptes non ouvert\n");

    while (!feof(f))
    {
            fscanf(f,"%s %s %s", nom,mdp,type);
            if (strcmp(nom, loginName) == 0)
            {
                strcpy(rMdp, mdp);
                strcpy(rType, type);
                break;
            }
    }

    printf("%s %s %s\n", loginName, rMdp, rType);

    send(connection, rMdp, 20, 0);
    send(connection, rType, 20, 0);
    fclose(f);

    if (strcmp(rType, "admin") == 0)
    {
        choix = 0;
        while (choix != 6)
        {
            recv(connection, &choix, 1, 0);
            switch (choix)
            {
                case 1:
                    recv(connection, &contact, sizeof(contact), 0);
                    FILE* contactsFile = fopen("contacts.txt", "a");

                    flag = fprintf(contactsFile,"%s %s %d %s %s %s %s\n", contact.nom, contact.prenom, contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                    fclose(contactsFile);

                    send(connection, &flag, sizeof(flag), 0);
                    break;
                case 2:
                    recv(connection, nom, sizeof(nom), 0);

                    FILE* contactFile = fopen("contacts.txt", "r");
                    if (contactFile == NULL)
                        printf("!!!!erreur!!!!\n");

                    flag = 0;
                    while (!feof(contactFile))
                    {
                        fscanf(contactFile,"%s %s %d %s %s %s %s", contact.nom, contact.prenom, &contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                        printf("%s\n", contact.nom);
                        if ((strcmp(contact.nom, nom)) == 0)
                        {
                            flag=1;
                            break;
                        }
                    }

                    send(connection, &flag, 1, 0);
                    if (flag == 1)
                         send(connection, &contact, sizeof(contact), 0);

                    fclose(contactFile);
                    break;
                case 3:
                    recv(connection, nom, sizeof(nom), 0);

                    FILE* f_in = fopen("contacts.txt", "r");
                    if (f_in == NULL)
                        printf("!!!erreur!!!\n");
                    FILE* f_out = fopen("tmp.txt","w");
                    if (f_out == NULL)
                        printf("!!!erreur!!!\n");

                    flag = 0;
                    while ((fscanf(f_in,"%s %s %d %s %s %s %s", contact.nom, contact.prenom, &contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays)) != EOF)
                    {    
                        if((strcmp(contact.nom, nom)) != 0)
                        {
                            fprintf(f_out,"%s %s %d %s %s %s %s\n", contact.nom, contact.prenom, contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                            flag = 1;
                        }
                    }

                    send(connection, &flag, sizeof(flag), 0);

                    fclose(f_in);
                    fclose(f_out);
                    remove("contacts.txt");
                    rename("tmp.txt", "contacts.txt");
                    break;
                case 4:
                    recv(connection, nom, sizeof(nom), 0);
                    recv(connection, &contacte, sizeof(contacte), 0);

                    FILE* f_IN = fopen("contacts.txt", "r");
                    FILE* f_OUT = fopen("tmp.txt", "w");

                    while ((fscanf(f_IN,"%s %s %d %s %s %s %s", contact.nom, contact.prenom, &contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays)) != EOF)
                    {
                        if (strcmp(contact.nom, nom) != 0)
                            fprintf(f_OUT,"%s %s %d %s %s %s %s\n", contact.nom, contact.prenom, contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                        else
                            fprintf(f_OUT,"%s %s %d %s %s %s %s\n", contacte.nom, contacte.prenom, contacte.gsm, contacte.email, contacte.adresse.rue, contacte.adresse.ville, contacte.adresse.pays); 
                    }

                    fclose(f_IN);
                    fclose(f_OUT);
                    remove("contacts.txt");
                    rename("tmp.txt", "contacts.txt");
                    break;
                case 5:
                    i = 1;
                    FILE* F = fopen("contacts.txt", "r");
                    //contacts *Contacts;
                    //Contacts=(contacts*)malloc(sizeof(contacts));
                    contacts Contacts[20];
                    while ((fscanf(F,"%s %s %d %s %s %s %s", contact.nom, contact.prenom, &contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays))!=EOF)
                    {
                        Contacts[i-1] = contact;
                        i++;
                       // Contacts=realloc(Contacts,i*sizeof(contacts));
                    }
        
                    send(connection, &i, sizeof(i), 0);
                    send(connection, Contacts, sizeof(Contacts), 0);
                    
                    fclose(F);
                    break;
            }
        }
    }
    if (strcmp(rType, "invite") == 0)
    {
        choix = 0;
        while (choix != 3)
        {
            recv(connection, &choix, 1, 0);
            switch (choix)
            {
                case 1:
                    recv(connection, nom, sizeof(nom), 0);

                    FILE* cfile = fopen("contacts.txt", "r");
                    if (cfile == NULL)
                        printf("!!!!erreur!!!!\n");

                    flag = 0;
                    while (!feof(cfile))
                    {
                        fscanf(cfile,"%s %s %d %s %s %s %s", contact.nom, contact.prenom, &contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                        printf("%s\n", contact.nom);
                        if ((strcmp(contact.nom, nom)) == 0)
                        {
                            flag = 1;
                            break;
                        }
                    }

                    send(connection, &flag, 1, 0);
                    send(connection, &contact, sizeof(contact), 0);

                    fclose(cfile);
                    break;
                case 2:
                    i = 1;
                    FILE* fi = fopen("contacts.txt", "r");
                    /*contacts *Contacts;
                    Contacts=(contacts*)malloc(sizeof(contacts));*/
                    contacts Contacts[20];
                    while((fscanf(fi,"%s %s %d %s %s %s %s", contact.nom, contact.prenom, &contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays)) != EOF)
                    {
                        Contacts[i-1] = contact;
                        i++;
                        //Contacts=realloc(Contacts,i*sizeof(contacts));
                    }
        
                    send(connection, &i, sizeof(i), 0);
                    send(connection, Contacts, sizeof(Contacts), 0);
                    
                    fclose(fi);
                    break;
            }
        }
    }

    close(serverSOCKET);
    close(connection);

    return 0;
}
