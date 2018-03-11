#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5
#define TURNS 10
#define PLAYERS 4


//INSTRUCTIONS MERCREDI
/*

* Il faut séparer le code pour le tester :
- isoler la partie deplacement
- isoler la partie action

* Vérifiez qu'elles ne présentent pas de défaillance et corrigez celles que vous décelez

* Il faut également créer deux IA un peu plus performantes pour réelement tester le code:
- ne doit pas sortir de la map
- ne doit pas aller sur la case morte (0,0)

* Pour le moment pas la peine de trop développer le côté action

*Possibilité de mettre en place un moyen de savoir qui a tué qui et de contabiliser les points

*/



//IA

int in_map(char move[1], int current,  int position[PLAYERS+1][PLAYERS+1])
{
int test[PLAYERS+1][PLAYERS+1];
int i,j;

for (i=0; i<PLAYERS+1; i++)
{
    for (j=0; j<PLAYERS+1; j++)
    {
        test[i][j]=position[i][j];
    }
}
switch(move[0])
    {
    case 'u':
        test[current][0]-=1;//augmenter la portée du déplacement ?
        break;
    case 'd':
        test[current][0]+=1;
        break;
    case 'l':
        test[0][current]-=1;
        break;
    case 'r':
        test[0][current]+=1;
        break;
    }
if ((test[current][0]>=SIZE)||(test[current][0]<0)||(test[0][current]>=SIZE)||(test[0][current]<0))
    {
        return(-1);
    }
else
    {
        return 0;
    }

}

void ia(char move[1], int action[2], int current,  int position[PLAYERS+1][PLAYERS+1])
{
int direct;
direct=rand() % 4;
int test=-1;
while(test==-1)
{
    direct=rand() % 4;
    switch(direct)
{
case 0:
    move[0]='u';
    break;
case 1:
    move[0]='d';
    break;
case 2:
    move[0]='l';
    break;
case 3:
    move[0]='r';
    break;
}
    test=in_map(move, current, position);
}

int act;
act=rand() % 2;
switch(act)
{
case 0:
    action[0]=0;
    break;
case 1:
    action[0]=1;
    int duel;
    duel=rand() % PLAYERS+1;
    action[1]=duel;
    break;
}
}


//FONCTIONS D'INITIALISATION
void visu(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1])
{
map[0][0]=0;
int i,j,k;
for(i=0; i<SIZE; i++)
  {
      for(j=0; j<SIZE; j++)
        {
            if ((map[i][j]!=0)&&((position[map[i][j]][0]==0)&&(position[0][map[i][j]]==0)))
            {
                printf("0");
            }
            else
            {
                printf("%d", map[i][j]);
            }
        }
    printf("\n");
  }
for (k=1; k<=PLAYERS; k++)
    {
        if((position[k][0]==0)&&(position[0][k]==0))
        {
            printf("\nPlayer %d dead", k);
        }
    }
printf("\n\n");
}

int check(int position[PLAYERS+1][PLAYERS+1], int x, int y, int current)//vérifie que deux joueurs ne sapawn pas u même endroit ou sur la case morte
{
int i;
for (i=1; i<=PLAYERS; i++)
    {
        if(((position[i][0]==x)&&(position[0][i]==y)&&(i!=current))||((x==0)&&(y==0)))//le fait que deux joueurs spawn au même endroit n'a enfait aucun impact sinon une question de réalisme et visibilité
        {
            return 1;
        }
    }
return 0;
}

void spawn(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1])
{
  int i,j,k;
  for(i=0; i<SIZE; i++)
  {
      for(j=0; j<SIZE; j++)
      {
        for (k=1; k<=PLAYERS; k++)
        {
            if ((i==position[k][0])&&(j==position[0][k]))
            {
                map[i][j]=k;
            }
        }
      }
  }
  visu(map, position);
}

void place(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1])
{
int i;
int ok;
srand(time(NULL));
for (i=1; i<=PLAYERS; i++)
    {
    ok=1;
    while (ok==1)
        {
        position[i][0]=rand() % SIZE;
        position[0][i]=rand() % SIZE;
        ok=check(position, position[i][0], position[0][i], i);
        }
    }
    spawn(map, position);
}

void init(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1], int statut[PLAYERS+1][PLAYERS+1])
{
int i,j;
for (i=0; i<PLAYERS+1; i++)
{
    for (j=0; j<PLAYERS+1; j++)
    {
        position[i][j]=0;
    }
}
for (i=0; i<SIZE; i++)
{
    for (j=0; j<SIZE; j++)
    {
        map[i][j]=0;
    }
}

place(map, position);

for (i=0; i<PLAYERS+1; i++)
{
    for (j=0; j<PLAYERS+1; j++)
    {
        statut[i][j]=0;
    }
}

}




//FONCTIONS D'ENGRENAGE DE DEPLACEMENT


void resetmap(int map[SIZE][SIZE])
{
    int i,j;
    for (i=0; i<SIZE; i++)
{
    for (j=0; j<SIZE; j++)
    {
        map[i][j]=0;
    }
}
}

/*
void replace(int map[SIZE][SIZE], int current, char move[1], int position[PLAYERS+1][PLAYERS+1])
{//fonction classique abscisse ordonnée
int out;
switch(move[0])
    {
    case 'u':
        position[0][current]+=1;//augmenter la portée du déplacement ?
        break;
    case 'd':
        position[current][0]=position[current][0]-1;
        break;
    case 'l':
        position[0][current]=position[0][current]-1;
        break;
    case 'r':
        position[current][0]+=1;
        break;
    }
    if((position[current][0]>=SIZE)||(position[0][current]>=SIZE))
        {
            position[current][0]=0;
            position[0][current]=0;
        }
    else if((position[current][0]<0)||(position[0][current]<0))
        {
            position[current][0]=0;
            position[0][current]=0;
        }
}
*/
void respawn(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1])
{
  resetmap(map);
  int i,j,k;
  for(i=0; i<SIZE; i++)
  {
      for(j=0; j<SIZE; j++)
      {
        for (k=1; k<=PLAYERS; k++)
        {
            if ((i==position[k][0])&&(j==position[0][k]))
            {   if(map[i][j]==0)
                {
                    map[i][j]=k;
                }
            else
                {
                position[k][0]=0;
                position[0][k]=0;
                position[map[i][j]][0]=0;
                position[0][map[i][j]]=0;
                }
            }
        }
      }
   }
}

void replace(int map[SIZE][SIZE], int current, char move[1], int position[PLAYERS+1][PLAYERS+1])
{//fonction ajustée pour la visibilité du codeur
switch(move[0])
    {
    case 'u':
        position[current][0]=position[current][0]-1;//augmenter la portée du déplacement ?
        break;
    case 'd':
        position[current][0]+=1;
        break;
    case 'l':
        position[0][current]=position[0][current]-1;
        break;
    case 'r':
        position[0][current]+=1;
        break;
    }
    if((position[current][0]>=SIZE)||(position[0][current]>=SIZE))
        {
            position[current][0]=0;
            position[0][current]=0;
        }
    else if((position[current][0]<0)||(position[0][current]<0))
        {
            position[current][0]=0;
            position[0][current]=0;
        }
}



//FONCTIONS D'ENGRENAGE D'ACTION
/*
tab statut : premier indice  :joueur
            deuxieme indice : 0 --> statut 0 guard 1 shot
                              1 --> récurence 0 ou 1 si saturé ou non
                              2 --> ciblé 1 non ciblé 0
*/

int radar(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1], int current, int action[2])
{
int i,j;

for(i=position[current][0]-2; i<=position[current][0]+2; i++)
{
    for (j=position[0][current]-2; j<=position[0][current]+2; j++)
    {
        if((map[i][j]!=0)&&( map[i][j]==action[1]))
        {
             return 1;
        }
    }
}
return 0;
}

void stats(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1], int current, int action[2], int statut[PLAYERS+1][PLAYERS+1])
{
int shoot;
switch(action[0])
    {
    case 0://guard
        switch(statut[current][0])
            {
            case 0:
                if(statut[current][1]!=1)
                {
                    statut[current][0]=0;
                    statut[current][1]=1;
                }
                else
                {
                    statut[current][0]=-1;
                }
                break;

            case 1:
                statut[current][0]=0;
                statut[current][1]=0;
                break;
            }
        break;

    case 1://shot
        switch(statut[current][0])
            {
            case 0:
                statut[current][0]=1;
                statut[current][1]=0;
                break;
            case 1:
                if(statut[current][1]!=1)
                {
                    statut[current][0]=1;
                    statut[current][1]=1;
                    shoot=radar(map, position, current, action);
                }
                else
                {
                    statut[current][0]=-1;
                }

                if((statut[current][0]==1)&&(shoot==1))
                {
                    statut[action[1]][2]=1; //as TARGETED BITCH !
                }
                break;
            }
        break;
    }

}

void maj(int position[PLAYERS+1][PLAYERS+1], int statut[PLAYERS+1][PLAYERS+1])
{
int i;
for (i=1; i<=PLAYERS+1; i++)
{
    if((position[i][0]!=0)||(position[0][i]!=0))
    {
       if(statut[i][2]==1)
        {
            switch(statut[i][0])
            {
            case 0:
                statut[i][2]=0;
                break;
            case 1:
                position[i][0]=0;
                position[0][i]=0;
                printf("\nPlayer %d s'est pris une bastos\n", i);
                statut[i][2]=0;
                break;
            case -1:
                position[i][0]=0;
                position[0][i]=0;
                statut[i][2]=0;
                printf("\nPlayer %d s'est pris une bastos\n", i);
                break;
            }
        }
    }
    }
}


//CORPS DU JEU

void phase(int map[SIZE][SIZE], int position[PLAYERS+1][PLAYERS+1], int statut[PLAYERS+1][PLAYERS+1])
{
int i;
int current;
char move[1];
int action[2];
for(i=1; i<=PLAYERS; i++)
    {
    current=i;
    if((position[current][0]!=0)||(position[0][current]!=0))
    {
    ia(move, action, current,  position);
    replace(map, current, move, position);
    stats(map, position, current, action, statut);
    }
    }
maj(position, statut);
respawn(map, position);
visu(map, position);
}

void jeu()
{
int i;
int statut[PLAYERS+1][PLAYERS+1];
int position[PLAYERS+1][PLAYERS+1];
int map[SIZE][SIZE];

init(map, position, statut);
for(i=0; i<TURNS; i++)
{
     phase(map, position, statut);//phase de déplacement : rectifier les morts alone au milieu de la map et les annoces de décès prématurées

}

}




//MAIN

int main()
{
    jeu();
    return 0;
}
