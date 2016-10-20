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
    while (i<nb){
        int hor_vert=doRand(0,1);
        x=doRand(0,MAP_H-1);
        y=doRand(0,MAP_W-1);

        //VERIFICATION DE DISPONIBILITE
        while (trigger !=1){
            trigger=0;
            for(j=0;j<taille;j++){
                if (hor_vert==0){
                trigger+=plateau[joueur][x+j][y];
                }
                if (hor_vert==1){
                trigger+=plateau[joueur][x][y+j];
                }
            }
            if (trigger==0){
                trigger=1;
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

int main(){

    int ID_joueur=0;
    int i=0;
    int nb_joueurs=2;
    int tir_ver=0;
    int tir_hor=0;
//DECLARATION DES BATOOOOOOOWS
//ID , TAILLE , NOMBRE
    int corvette[3]={1,1,1};
    int destroyer[3]={2,3,2};
    int croiseur[3]={3,4,2};
    int porte_avion[3]={5,6,1};

    int plateau [IA_VS_IA][MAP_H][MAP_W]={0};

        //PLACEMENT DE BATEAUX
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

    while (i!=3){// INTEGRER ICI CONDITIONS DE VICTOIRE

        //PHASE DE TIR
        printf("Au tour du joueur %d:\n", ID_joueur+1);
        printf("\ncoordonnees lettres");
        scanf("%d", &tir_ver);
        tir_ver--;
        printf("\ncoordonnees chiffres");
        scanf("%d", &tir_hor);
        tir_hor--;

        //PERMUTATION JOUEUR
        if (ID_joueur==0){
        ID_joueur=1;
        }else{
        ID_joueur=0;
        } // FIN DE LA PERMUT
        plateau[ID_joueur][tir_ver][tir_hor]=9;// CA FAIT UN 5 QUAND PLOUF !


        affichage_plateau(plateau,ID_joueur);
        printf("\n+++FIN DU TOUR+++\n\n");
        getchar(); // MARCHE PAS. SAIS PAS POURQUOI.
        i++; // TRIGGER PERMUTATION JOUEUR
    }

}
