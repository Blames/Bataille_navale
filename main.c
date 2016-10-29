#include <stdio.h>
#include <stdlib.h>
#define IA_VS_IA 2
#define MAP_H 18
#define MAP_W 24

void affichage_plateau(int plateau[2][MAP_H][MAP_W], int joueur){
    char alph[]="ABCDEFGHIJKLMONPQRSTU";
    int i=joueur;
    int j=0;
    int k=0;
    printf("\n\nPlateau du joueur %d :", joueur+1);
    printf("\n  inserez ici chiffres syles");
    for(j=0;j<18;j++){
        printf("\n%c ", alph[j]);
        for(k=0;k<24;k++){
            printf("%d ", plateau[joueur][j][k]);
        }
    }
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int doRand(int startVal, int endVal){
    waitFor(0.05);
    srand(time(NULL)*rand());
    if(startVal == 0 && endVal == 1){
        return rand() % 2;
    }else{
        return (rand() % ((endVal + startVal -1)) + startVal);
    }
}

void placer(int plateau[2][MAP_H][MAP_W],int bateau[3],int joueur){
    int ID_bateau=bateau[0];
    int taille=bateau[1];
    int nb=bateau[2];
    int x=0;
    int y=0;
    int i=0;
    int j=0;
    int trigger=0;
    int taille_verif=0;
    int limite=0;
    while (i<nb){
        int hor_vert=doRand(0,1);
        x=doRand(0,MAP_H-1);
        y=doRand(0,MAP_W-1);

        //VERIFICATION DE DISPONIBILITE
        while (trigger !=99){
            trigger=0;
            for(j=0;j<taille;j++){
                if (hor_vert==0){
                    trigger+=plateau[joueur][x+j][y];

                //VERIFICATION PLACE VERTICALE:
                    taille_verif=(x+taille);
                    limite=18;
                }
                if (hor_vert==1){
                    trigger+=plateau[joueur][x][y+j];

                    //VERIFICATION PLACE HORIZONTALE :
                    taille_verif=(y+taille);
                    limite=24;
                }
            }
            if ((trigger==0)&&(taille_verif<limite)){
                trigger=99;
            }else{
                x=doRand(0,MAP_H-1);
                y=doRand(0,MAP_W-1);
            }
        }
        //PLACEMENT BATEAUX
        for(j=0;j<taille;j++){
            if (hor_vert==0){
                plateau[joueur][x+j][y]=ID_bateau;
            }
            if (hor_vert==1){
                plateau[joueur][x][y+j]=ID_bateau;
            }
        }
    i++;
    }
}

void phase_de_tir_automatique(int tir_ver, int tir_hor,int player, int ID_joueur, int plateau[2][MAP_H][MAP_W], int points[player][1]){
        printf("\nAu tour du joueur %d:\n", player+1);

        //PHASE DE TIR
        tir_hor=doRand(0,MAP_W-1);
        tir_ver=doRand(0,MAP_H-1);
        printf("\ncoordonnees chiffres:%d \n",tir_hor+1);
        printf("coordonnees lettres:%d \n", tir_ver+1);

//VERIFICATION DE LA COORDONNEE VISEE
        while (plateau[ID_joueur][tir_ver][tir_hor]>7){
            printf("\ntir impossible, nouveau tir...");
            tir_hor++;
            if (tir_hor>MAP_W){
                tir_hor=0;
                tir_ver++;
                if (tir_ver>MAP_H){
                    tir_ver=0;
                }
            }

            printf("\ncoordonnees chiffres:%d \n",tir_hor+1);
            printf("coordonnees lettres:%d \n", tir_ver+1);
        }

//SI COORD OK, CHANGEMENT D'ETAT DU PLATEAU
                //TOUCHE
        if (plateau[ID_joueur][tir_ver][tir_hor]>0){
            plateau[ID_joueur][tir_ver][tir_hor]=9;
            printf("BOUM !!! C'EST UNE TOUCHE !!!");// VIRE TOUS LES "!!!"
            points[player][0]++;
            printf("\n Joueur %d || Points=%d",player+1 , points[player][0]);
                //MANQUE
        }else if (plateau[ID_joueur][tir_ver][tir_hor]==0){printf("\n Joueur %d || Points=%d",player+1 , points[player][0]);
            plateau[ID_joueur][tir_ver][tir_hor]=8;
            printf("PLOUF... C'EST DANS l'EAU");
        }

        affichage_plateau(plateau,ID_joueur);
}

void phase_de_tir_manuelle(int tir_ver, int tir_hor,int player, int ID_joueur, int plateau[2][MAP_H][MAP_W], int points[player][1]){
        printf("\nAu tour du joueur %d:\n", player+1);

        //PHASE DE TIR

        fflush(stdin);
        printf("\nEntrez coordonnées lettres :\n");
        scanf("%d", &tir_ver);
        tir_ver--;
        printf("%d",tir_ver);
        while ((tir_ver<0)||(tir_ver>17)){
            printf("Tir impossible, veuillez recommencer.");
            scanf("%d", &tir_ver);
            tir_ver--;
            printf("%d",tir_ver);
        }

        fflush(stdin);
        printf("\nEntrez coordonnées chiffres :\n");
        scanf("%d",&tir_hor);
        tir_hor--;
        printf("%d",tir_hor);
        while ((tir_hor<0)||(tir_hor>23)){
            printf("Tir impossible, veuillez recommencer.");
            scanf("%d",&tir_hor);
            tir_hor--;
            printf("%d",tir_hor);
        }

//VERIFICATION DE LA COORDONNEE VISEE
        while (plateau[ID_joueur][tir_ver][tir_hor]>7){
            printf("\n Vous avez deja tire la. Recommencez s'il vous plait ");

            fflush(stdin);
            printf("\nEntrez coordonnées lettres :\n");
            scanf("%d", &tir_ver);
            tir_ver--;
            printf("%d",tir_ver);
            while ((tir_ver<0)||(tir_ver>17)){
                printf("Tir impossible, veuillez recommencer.");
                scanf("%d", &tir_ver);
                tir_ver--;
                printf("%d",tir_ver);
            }

            fflush(stdin);
            printf("\nEntrez coordonnées chiffres :\n");
            scanf("%d",&tir_hor);
            tir_hor--;
            printf("%d",tir_hor);
            while ((tir_hor<0)||(tir_hor>23)){
                printf("Tir impossible, veuillez recommencer.");
                scanf("%d",&tir_hor);
                tir_hor--;
                printf("%d",tir_hor);
            }
        }

//SI COORD OK, CHANGEMENT D'ETAT DU PLATEAU
                //TOUCHE
        if (plateau[ID_joueur][tir_ver][tir_hor]>0){
            plateau[ID_joueur][tir_ver][tir_hor]=9;
            printf("BOUM !!! C'EST UNE TOUCHE !!!");// VIRE TOUS LES "!!!"
            points[player][0]++;
            printf("\n Joueur %d || Points=%d",player+1 , points[player][0]);
                //MANQUE
        }else if (plateau[ID_joueur][tir_ver][tir_hor]==0){printf("\n Joueur %d || Points=%d",player+1 , points[player][0]);
            plateau[ID_joueur][tir_ver][tir_hor]=8;
            printf("PLOUF... C'EST DANS l'EAU");
        }
        printf("\n+++FIN DU TOUR+++");
        printf("\n+++APPUYEZ SUR UNE TOUCHE POUR CONTINUER+++\n\n");
        fflush(stdin);
        getchar();
//AFFICHAGE DU PLATEAU DU JOUEUR SUIVANT
        affichage_plateau(plateau,ID_joueur);
}

void load(int plateau [2][MAP_H][MAP_W]){
    char c;
    int k;
    int i;
    int j;

    FILE *save=fopen("./save.txt","r");

        for(k=0;k<2;k++){
            for(i=0; i<18; i++){
                for(j=0;j<24;j++){
                    c=fgetc(save);
                    plateau[k][i][j]=c-'0';
                }
            }
        }
        fclose(save);
}

void sauvegarde(int plateau [2][MAP_H][MAP_W]){

    FILE *save=fopen("./save.txt","w+");
    int i=0;
    int j=0;
    int k=0;

    for(k=0;k<2;k++){
        for(i=0; i<18; i++){
            for(j=0;j<24;j++){
                fputc(plateau [k][i][j]+'0', save);
            }
        }
    }

    fclose(save);
}


int main(){

    int ID_joueur=0; // ATTENTION : DANS LA FONCTION TIR = LE JOUEUR CIBLE
    int player=0; // ATTENTION : DANS LA FONCTION TIR = LE JOUEUR QUI FAIT FEU
    int i=0;
    int nb_joueurs=2;
    int tir_x=0;
    int tir_y=0;
    int nb_pts=0;
    int menu=0;
    int choix=0;
    int points[2][1]={0};
//DECLARATION DES BATOOOOOOOWS
//ID , TAILLE , NOMBRE
    int corvette[3]={1,1,1};
    int destroyer[3]={2,3,2};
    int croiseur[3]={3,4,2};
    int porte_avion[3]={5,6,1};

    int plateau [IA_VS_IA][MAP_H][MAP_W]={0};


//PLACEMENT DES BATEAUX
            //JOUEUR1
    ID_joueur=0;
    placer(plateau,corvette,ID_joueur);
    placer(plateau,destroyer,ID_joueur);
    placer(plateau,croiseur,ID_joueur);
    placer(plateau,porte_avion,ID_joueur);
            //JOUEUR 2
    ID_joueur=1;
    placer(plateau,corvette,ID_joueur);
    placer(plateau,destroyer,ID_joueur);
    placer(plateau,croiseur,ID_joueur);
    placer(plateau,porte_avion,ID_joueur);

// PHASE DE CHARGEMENT
    printf("\nVoulez vous charger une partie ? \nOUI=[1] || NON =[0]\n");
    scanf("%d", &choix);
    if (choix==1){
        load(plateau);
    }else if (choix==0){
        printf("coucou");
    }

//MENU

    printf("\nBataille navale :\n 1= J1vsJ2 || 2= J1vsIA || 3= IAvsIA\n");
    scanf("%d", &menu);
    switch(menu){

case 1:
    while (points[player][0]<21){
            //PHASE DE TIR
        ID_joueur=0;
        player=1;
        sauvegarde(plateau);
        phase_de_tir_manuelle(tir_x,tir_y,player,ID_joueur, plateau, points);
        if (points[player][0]==21){
            printf("\n\nJEU TERMINE ! Victoire du joueur %d", player+1);
            break;
        }
        ID_joueur=1;
        player=0;
        phase_de_tir_manuelle(tir_x,tir_y,player,ID_joueur, plateau, points);
        if (points[player][0]==21){
            printf("\n\nJEU TERMINE ! Victoire du joueur %d", player+1);
            break;
        }
        printf("\n   Tour n.%d \n",i+1);
        i++;
        }

case 2:
    while (points[player][0]<21){
        ID_joueur=0;
        player=1;
        phase_de_tir_manuelle(tir_x,tir_y,player,ID_joueur, plateau, points);
        if (points[player][0]==21){
            printf("\n\nJEU TERMINE ! Victoire du joueur %d", player+1);
            break;
        }
        ID_joueur=1;
        player=0;
        phase_de_tir_automatique(tir_x,tir_y,player,ID_joueur, plateau, points);
        if (points[player][0]==21){
            printf("\n\nJEU TERMINE ! Victoire du joueur %d", player+1);
            break;
        }
        printf("\n   Tour n.%d \n",i+1);
        i++;
    }

case 3:
    while (points[player][0]<21){
            //PHASE DE TIR
        ID_joueur=0;
        player=1;
        phase_de_tir_automatique(tir_x,tir_y,player,ID_joueur, plateau, points);
        if (points[player][0]==21){
            printf("\n\nJEU TERMINE ! Victoire du joueur %d", player+1);
            break;
        }
        ID_joueur=1;
        player=0;
        phase_de_tir_automatique(tir_x,tir_y,player,ID_joueur, plateau, points);
        if (points[player][0]==21){
            printf("\n\nJEU TERMINE ! Victoire du joueur %d", player+1);
            break;
        }
        printf("\n   Tour n.%d \n",i+1);
        i++;
        }
// RECAPITULATIF DE LA PARTIE
    printf("\n      |||  Scores   |||     \n");
    player=0;
    printf("\n Joueur %d || Points=%d",player+1 , points[player][0]);
    player=1;
    printf("\n Joueur %d || Points=%d",player+1 , points[player][0]);

    }
}
