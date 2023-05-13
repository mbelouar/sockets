#include "header.h"

contacts ajouter()
{
    contacts contact;
    printf("\nentrer le nom:\t");
    scanf("%s",contact.nom);

    printf("entrer le prenom:\t");
    scanf("%s", contact.prenom);

    printf("entrer le  GSM:\t");
    scanf("%d", &contact.gsm);

    printf("entrer l'email:\t");
    scanf("%s", contact.email);

    printf("\n--->entrer l'adresse:");

    printf("\nentrer la rue:\t");
    scanf("%s", contact.adresse.rue);

    printf("entrer la ville:\t");
    scanf("%s", contact.adresse.ville);

    printf("entrer le pays:\t");
    scanf("%s", contact.adresse.pays);

    return contact;
}

int main()
{
    int SOCKET;
    SOCKET = socket(AF_INET, SOCK_STREAM, 0);
    if(SOCKET != -1)
        printf("socket cree avev ID:%d\n", SOCKET);

    struct sockaddr_in addrport;
    memset(&addrport, 0, sizeof(addrport));

    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(5001);
    addrport.sin_addr.s_addr = inet_addr("169.254.59.166");
    inet_pton(AF_INET, "169.254.59.166", &(addrport.sin_addr));
    if (connect(SOCKET, (struct sockaddr*)&addrport, sizeof(addrport)) == 0)
        printf("bien connecte\n");
    else
    {
        printf("non connecte\n");
        exit(0);
    }

    
    char nom[20],loginMdp[20],type[20],mdp[20],loginName[20],userType[10];
    char buff[20];
    int choix,i,flag,j;
    contacts contact;
    contacts Contacts[20];

    printf("\n-->Entrer votre login:\t");
    scanf("%s", loginName);
    
    send(SOCKET, loginName, strlen(loginName), 0);

    recv(SOCKET, mdp,20,0);
    recv(SOCKET, type,20,0);
   
    i = 1;
    while (i < 4)
    {
        printf("-->Enter votre mot de passe:\t");
        scanf("%s", loginMdp);
  
        if (strcmp(mdp, loginMdp) == 0)
        {
            printf("--->Bonjour %s\n",loginName);
            break;
        }
        i++;
    }

    if (i == 4)
    {
        printf("!!! 3 Attemptes incorretctes!!!!\n");
        exit(0);
    }



    if(strcmp(type, "admin") == 0)
    {
        printf("------------------VOUS ETES ADMINISTRATEUR------------\n");
        while(choix != 6)
        {
            printf("\n********MENU********\n");
            printf("1-Ajouter un contact\n2-Recherer un contact\n3-supprimer un contact\n4-Modifier un contact\n5-Afficher tous les contacts\n6-Quitter\n");
            printf("---->entrer votre choix:\t");
            scanf("%d", &choix);
            send(SOCKET, &choix, 1, 0);
            
            switch (choix)
            {
                case 1:
                    contact = ajouter();

                    send(SOCKET, &contact, sizeof(contact), 0);
                    recv(SOCKET, &flag, sizeof(flag), 0);

                    if(flag < 0)
                        printf("!!!!contacte non ajoutee!!!\n");
                    else
                        printf("--->contact ajouter avec succes\n");
                    break;
                case 2:
                    printf("\n--->entrer le nom:\t");
                    scanf("%s", nom);
                    send(SOCKET, nom, sizeof(nom), 0);
                    recv(SOCKET, &flag, 1, 0);
                    if (flag == 1)
                    {
                        recv(SOCKET,&contact,sizeof(contact),0);
                        printf("--->le contacte recherche est:\n");
                        printf("%s %s %d %s %s %s %s\n", contact.nom, contact.prenom, contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                    }
                    else
                        printf("!!!!contacte non trouvee!!!\n");
                    break;
                case 3:
                    printf("\nentrer le nom:\t");
                    scanf("%s", nom);

                    send(SOCKET, nom, sizeof(nom), 0);
                    recv(SOCKET, &flag, sizeof(flag), 0);

                    if (flag == 1)
                        printf("--->contacte supprimer\n");
                    else
                        printf("--> contacte non supprimer!!!\n");
                    break;
                case 4:
                    printf("\n-->nentrer le nom:\t");
                    scanf("%s", nom);
                    send(SOCKET, nom, sizeof(nom), 0);
                    printf("\n--->enter les nouvelles info:\n");
                    contact = ajouter();
                    send(SOCKET, &contact, sizeof(contact), 0);
                    printf("--->contacte modifier\n");
                    break;
                case 5:
                    recv(SOCKET, &i, sizeof(i), 0);
                    recv(SOCKET, Contacts, sizeof(Contacts), 0);
                    printf("\n---->les contacts:\n");
                    for(j = 0 ; j < i-1 ; j++)
                       printf("%s %s %d %s %s %s %s\n", Contacts[j].nom, Contacts[j].prenom, Contacts[j].gsm, Contacts[j].email, Contacts[j].adresse.rue, Contacts[j].adresse.ville, Contacts[j].adresse.pays);
                    break;
            }        
        }
    }

    if (strcmp(type, "invite") == 0)
    {
        printf("------------------VOUS ETES INVITE-----------\n");
        while(choix != 3)
        {
            printf("\n********MENU********\n");
            printf("1-Recherer un contact\n2-Afficher tous les contacts\n3-Quitter\n");
            printf("---->entrer votre choix:\t");
            scanf("%d", &choix);
            send(SOCKET, &choix, 1, 0);
        
            switch (choix)
            {
                case 1:
                    printf("\n--->entrer le nom:\t");
                    scanf("%s", nom);
                    send(SOCKET, nom, sizeof(nom), 0);
                    recv(SOCKET, &flag, 1, 0);
                    if (flag == 1)
                    {
                        recv(SOCKET, &contact, sizeof(contact), 0);
                        printf("--->le contacte recherche est:\n");
                        printf("%s %s %d %s %s %s %s\n", contact.nom, contact.prenom, contact.gsm, contact.email, contact.adresse.rue, contact.adresse.ville, contact.adresse.pays);
                    }
                    else
                        printf("!!!!contacte non trouvee!!!\n");
                    break;
                case 2:
                    recv(SOCKET, &i, sizeof(i), 0);
                    recv(SOCKET, Contacts, sizeof(Contacts), 0);
                    printf("\n---->les contacts:\n");
                    for(j = 0 ; j < i-1 ; j++)
                       printf("%s %s %d %s %s %s %s\n", Contacts[j].nom, Contacts[j].prenom, Contacts[j].gsm, Contacts[j].email, Contacts[j].adresse.rue, Contacts[j].adresse.ville, Contacts[j].adresse.pays);
                    break;
            }
        }
    }
   /* else if(strcmp(userType,"no")==0)
    		printf("\tutilisateur n'existe pas!!!!");*/
   close(SOCKET);

   return (0);
}
