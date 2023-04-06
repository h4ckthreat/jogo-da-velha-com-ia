#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "hackthreat.h"
using namespace std;

//char tst123[250];
//#define MB(x...) sprintf(tst123,x);MessageBox(0,tst123,"Debug",MB_OK);

#define BOTAO_ESC   27
#define BOTAO_CIMA  72
#define BOTAO_BAIX  80          
#define BOTAO_ESQD  75
#define BOTAO_DIRT  77                                
#define BOTAO_ENTR  13

#define VAZIO 0
#define XIS 1
#define CIRCULO 2

int HUMANO,COMPUTADOR,QUEMCOMECOU;
int sal=9247;
int tabuleiro[10]={0,0,0,0,0,0,0,0,0,0},jogadorDaVez=1,marcados=0,vit=0;
char nome_jogador[3][15]={"","",""};
bool humano_comecou_no_centro=false, humano_comecou_no_canto=false,humano_comecou_na_lateral=false;

int aleatorio(int minimo, int maximo);
void copia_vet(int *destino, int *origem);
int verifica_vitoria(int*);
int verifica_posicao_vencedora(int JOGADOR);
void computador_marca();
void MB(char * texto);

int main()
{
    bool fimDoJogo=false;
    char resposta;
    int sel=1,opcao=0,i,pos=1,pos2=1,botao2=0;    
    int coordenadas[10][10]={{0,0},
                             {32,8} ,{37,8} ,{42,8} ,
                             {32,11},{37,11},{42,11},
                             {32,14},{37,14},{42,14}
                            };
                            
    colorizar(VERDE_C);                        
    pula(21,8);printf("DESEJA JOGAR COM  O  CIRCULO OU  X ?");
    do
    {       
        if(botao2 == BOTAO_ENTR) break;
        if(botao2 == BOTAO_ESQD) sel--;
        if(botao2 == BOTAO_DIRT) sel++;
        if(sel < 1) sel = 1;
        if(sel > 2) sel = 2;
        
        colorizar(VERDE_E);
           
        if(sel == 1) colorizar(VERDE_C);        
        pula(22,10);printf("\311\315\315\315\315\273");
        pula(22,11);printf("\272\040/\\\040\272");
        pula(22,12);printf("\272\040\\/\040\272");
        pula(22,13);printf("\310\315\315\315\315\274");
        colorizar(VERDE_E); 
        
        if(sel == 2) colorizar(VERDE_C);
        pula(50,10);printf("\311\315\315\315\315\273");
        pula(50,11);printf("\272\040\\/\040\272");
        pula(50,12);printf("\272\040/\\\040\272");
        pula(50,13);printf("\310\315\315\315\315\274");
        colorizar(VERDE_E);         
                             
        
    }while(botao2 = getch());
    
    if(sel == 1)
    {
        HUMANO = CIRCULO;
        COMPUTADOR = XIS;  
        QUEMCOMECOU = HUMANO;
    }else{
        HUMANO = XIS;
        COMPUTADOR = CIRCULO;
        QUEMCOMECOU = COMPUTADOR;        
    }
    
    botao2 = 0;
    jogadorDaVez = QUEMCOMECOU;
    system("cls");
    
    while(true)
    {
        if(CIRCULO == HUMANO)
        {
            strcpy(nome_jogador[CIRCULO],"HUMANO");
            strcpy(nome_jogador[XIS],"COMPUTADOR");                
        }else{
            strcpy(nome_jogador[CIRCULO],"COMPUTADOR");  
            strcpy(nome_jogador[XIS],"HUMANO");             
        }       
               
        while(opcao != BOTAO_ESC)
        {       
            colorizar(VERDE_E);    
            pula(32,8);cout << "    \272    \272";
            pula(32,9);cout << "    \272    \272";
            pula(32,10);cout << "\315\315\315\315\316\315\315\315\315\316\315\315\315\315";
            pula(32,11);cout << "    \272    \272";
            pula(32,12);cout << "    \272    \272";
            pula(32,13);cout << "\315\315\315\315\316\315\315\315\315\316\315\315\315\315";
            pula(32,14);cout << "    \272    \272";
            pula(32,15);cout << "    \272    \272";   
            
         
                switch(opcao)
                {             
                    case BOTAO_CIMA:
                         pos -= 3;
                         break;
                    case BOTAO_BAIX:
                         pos += 3;                 
                         break;                 
                    case BOTAO_ESQD:
                         pos -= 1;                 
                         break;                 
                    case BOTAO_DIRT:                                  
                         pos += 1;                 
                         break;                 
                    case BOTAO_ENTR:                                  
                         if(tabuleiro[pos] == VAZIO)
                         {
                             tabuleiro[pos] = HUMANO;
                             Beep(400,100);
                             jogadorDaVez = COMPUTADOR;
                             marcados++;                     
                         }else{
                             Beep(800,200);       
                         }                 
                         opcao = 0;
                         break;                    
                }
            
            
            if(pos < 1) pos += 9;
            if(pos > 9) pos -= 9;        
            
            if(jogadorDaVez == 1) colorizar(VERDE_C);
            pula(22,5);printf("\311\315\315\315\315\273");
            pula(22,6);printf("\272\040\\/\040\272");
            pula(22,7);printf("\272\040/\\\040\272");
            pula(22,8);printf("\310\315\315\315\315\274");
            colorizar(VERDE_E);
    
            if(jogadorDaVez == 2) colorizar(VERDE_C);        
            pula(50,5);printf("\311\315\315\315\315\273");
            pula(50,6);printf("\272\040/\\\040\272");
            pula(50,7);printf("\272\040\\/\040\272");
            pula(50,8);printf("\310\315\315\315\315\274");
            colorizar(VERDE_E);        
                       
            for(i=1; i<=9; i++)
            {   
                colorizar(VERDE_E);
                if(i == pos) colorizar(F_VERDE_C);
                
                if(tabuleiro[i] != 0) //se tem algo marcado nessa posição.
                {
                    if(tabuleiro[i] == XIS)
                    {
                        pula(coordenadas[i][0],coordenadas[i][1]);
                        cout << " \\/ ";
                        pula(coordenadas[i][0],coordenadas[i][1]+1);
                        cout << " /\\ ";                    
                    }    
                    else if(tabuleiro[i] == CIRCULO)
                    {
                        pula(coordenadas[i][0],coordenadas[i][1]);
                        cout << " /\\ ";
                        pula(coordenadas[i][0],coordenadas[i][1]+1);
                        cout << " \\/ ";                                        
                    }
                }else{
                    pula(coordenadas[i][0],coordenadas[i][1]);
                    cout << "    ";
                    pula(coordenadas[i][0],coordenadas[i][1]+1);
                    cout << "    ";                                                    
                }         
                colorizar(VERDE_E);         
            }
            pula(0,0);
            vit = verifica_vitoria(tabuleiro);
            if(vit == 1)
            {
                pula(31,18);cout << nome_jogador[1] << " VENCEU!";
                Beep(800,100);                           
                Beep(800,100);                           
                Beep(800,100);                                                   
                Sleep(1000);
                fimDoJogo = true;
            }else if(vit ==2){
                pula(31,18);cout << nome_jogador[2] << " VENCEU!";             
                Beep(800,100);                           
                Beep(800,100);                           
                Beep(800,100);
                Sleep(1000);                                                       
                fimDoJogo = true;            
            }
            
            if(marcados == 9 && vit == 0)
            {              
                pula(36,18);cout << "VELHOU!";             
                Beep(800,500);                           
                Beep(500,500);                           
                Beep(300,800);
                Sleep(1000);     
                fimDoJogo = true;                                
            }
            
            if(fimDoJogo) break;
            
            if(jogadorDaVez == HUMANO)
            {
                opcao = getch();
            }else{  //SE jogadorDaVez == COMPUTADOR. 
                computador_marca();
                Beep(900,100);
                marcados++;
                jogadorDaVez = HUMANO;      
            }
        }        
        MB(" ");     
        fflush(stdin);colorizar(VERDE_C);
        pula(0,0);printf("DESEJA RECOMECAR O JOGO?");
        do
        {       
            if(botao2 == BOTAO_ENTR) break;
            if(botao2 == BOTAO_CIMA) pos2--;
            if(botao2 == BOTAO_BAIX) pos2++;
            if(pos2 < 1) pos2 = 1;
            if(pos2 > 2) pos2 = 2;
            
            if(pos2 == 1) colorizar(VERDE_C|F_VERDE_E);
            pula(0,1);printf("RECOMECAR");
            colorizar(VERDE_C);
            if(pos2 == 2) colorizar(VERDE_C|F_VERDE_E);
            pula(0,2);printf("  SAIR   ");            
            colorizar(VERDE_C);                        
        }while(botao2 = getch());
        
        system("cls");
        
        switch(pos2)
        {
            case 1:                
                for (i=0;i<10;i++)
                    tabuleiro[i] = 0;
                marcados = 0;
                jogadorDaVez = QUEMCOMECOU;
                vit = 0;
                pos = 1;
                system("cls");
                botao2 = 0;
                fimDoJogo = false;
                opcao = 0;
                humano_comecou_no_centro=false;
                humano_comecou_no_canto=false;
                humano_comecou_na_lateral=false;                
                break;     
            default:
                Sleep(300);
                exit(0);                     
        }
    }
}

int aleatorio(int minimo, int maximo)
{    
    time_t segundos;
    time(&segundos);
    srand((unsigned int)(segundos + (sal++ - (rand() % 10000 ))));    
    return rand() % maximo + minimo;
}

void copia_vet(int *destino, int *origem)
{
    int i;
    for(i=0; i<10; i++)
    {
        destino[i] = origem[i];         
    }
}

int verifica_vitoria(int *t)
{
    int i,vitoria = 0;
    for(i=1;i<=2;i++)
    {
        if(t[1] == i && t[2] == i && t[3] == i) vitoria = i;
        if(t[4] == i && t[5] == i && t[6] == i) vitoria = i;
        if(t[7] == i && t[8] == i && t[9] == i) vitoria = i;
        if(t[1] == i && t[4] == i && t[7] == i) vitoria = i;
        if(t[2] == i && t[5] == i && t[8] == i) vitoria = i;
        if(t[3] == i && t[6] == i && t[9] == i) vitoria = i;
        if(t[1] == i && t[5] == i && t[9] == i) vitoria = i;
        if(t[3] == i && t[5] == i && t[7] == i) vitoria = i;                                                        
    }
    return vitoria;
}

int verifica_posicao_vencedora(int JOGADOR)
{
    int tabuleiro2[10]={0},i,v;
    
    for(i=1;i<10;i++) //1->9
    {
        if(tabuleiro[i] == 0) //se encontrou uma posição vazia.
        {
            copia_vet(tabuleiro2,tabuleiro); //faz uma cópia do tabuleiro.
            tabuleiro2[i] = JOGADOR; //marca no tabuleiro temporario;
            v = verifica_vitoria(tabuleiro2); //verifica se o jogador venceu com essa posição.
            if(v == JOGADOR) return i; //retorna a posiçao onde acontecera a vitoria do jogador.
        }
    }
    
    //se não houver nenhuma posição de vitória, retornar negativo:
    return -1;
}

//============================================================
// computador_marca()
//============================================================
void computador_marca()
{
    int ale,pos,bordas=0; 
    
    Sleep(500);
    
    if(marcados == 0 && QUEMCOMECOU == COMPUTADOR)
    {
        //MB("O computador comeca, marcando no centro..."); 
        tabuleiro[5] = COMPUTADOR;            
        return;                     
    }
    
    if(marcados == 1 && QUEMCOMECOU == HUMANO)
    {
    
        if(tabuleiro[1] == HUMANO) humano_comecou_no_canto=true;
        else if(tabuleiro[3] == HUMANO) humano_comecou_no_canto=true;
        else if(tabuleiro[7] == HUMANO) humano_comecou_no_canto=true;
        else if(tabuleiro[9] == HUMANO) humano_comecou_no_canto=true;            

        if(tabuleiro[2] == HUMANO) humano_comecou_na_lateral=true;    
        else if(tabuleiro[4] == HUMANO) humano_comecou_na_lateral=true;     
        else if(tabuleiro[6] == HUMANO) humano_comecou_na_lateral=true;   
        else if(tabuleiro[8] == HUMANO) humano_comecou_na_lateral=true;       
        
        if(humano_comecou_no_canto||humano_comecou_na_lateral)
        {
            //MB("O centro nao foi marcado pelo humano, marcando..."); 
            tabuleiro[5] = COMPUTADOR;            
            return;                                                 
        }                                                                                       
        
        if(tabuleiro[5] == HUMANO) humano_comecou_no_centro=true;
        //MB("o usuario marcou no meio, marcando nos cantos...");
        
        ale = aleatorio(1,4);
        switch(ale)
        {
            case 1:
                tabuleiro[1] = COMPUTADOR;  //canto superior esquerdo.  
            break;   
            case 2:
                tabuleiro[3] = COMPUTADOR;  //canto superior direito.                      
            break;                     
            case 3:
                tabuleiro[7] = COMPUTADOR;  //canto inferior esquerdo.                      
            break;                     
            case 4:   
                tabuleiro[9] = COMPUTADOR;  //canto inferior direito                       
            break;                                                                                 
        }
        
        return;             
    }
    
    if(marcados == 2 && QUEMCOMECOU == COMPUTADOR)
    {
    
        if(tabuleiro[1] == HUMANO) humano_comecou_no_canto=true;
        else if(tabuleiro[3] == HUMANO) humano_comecou_no_canto=true;
        else if(tabuleiro[7] == HUMANO) humano_comecou_no_canto=true;
        else if(tabuleiro[9] == HUMANO) humano_comecou_no_canto=true;            

        if(tabuleiro[2] == HUMANO) humano_comecou_na_lateral=true;    
        else if(tabuleiro[4] == HUMANO) humano_comecou_na_lateral=true;     
        else if(tabuleiro[6] == HUMANO) humano_comecou_na_lateral=true;   
        else if(tabuleiro[8] == HUMANO) humano_comecou_na_lateral=true;                
    }
     
    //Se ja puder vencer neste movimento, marcar.
    pos = verifica_posicao_vencedora(COMPUTADOR);
    if(pos > 0)
    {
           //MB("O computador consegue vencer, marcando...");           
           tabuleiro[pos] = COMPUTADOR;
           return;
    }
    
    //Se o humano for vencer no proximo movimento, marcar no lugar dele.   
    pos = verifica_posicao_vencedora(HUMANO);
    if(pos > 0)
    {
           //MB("O humano iria vencer, bloqueando...");                      
           tabuleiro[pos] = COMPUTADOR;
           return;
    }
    
    
      
    if(humano_comecou_no_canto)
    {
        //Se o humano controlar dois cantos tentar marcar.
        //em uma lateral vazia para forçá-lo a contra-atacar.
        if(tabuleiro[1] == HUMANO) bordas++;
        if(tabuleiro[3] == HUMANO) bordas++;
        if(tabuleiro[7] == HUMANO) bordas++;
        if(tabuleiro[9] == HUMANO) bordas++;  
        
        if(bordas >= 2)
        {                
            if(tabuleiro[2] == VAZIO){
                //MB("Humano controla duas ou mais bordas, forcando-o a marcar na lateral...");                             
                tabuleiro[2] = COMPUTADOR;
                return;
            }else if(tabuleiro[4] == VAZIO){
                //MB("Humano controla duas ou mais bordas, forcando-o a marcar na lateral...");                                         
                tabuleiro[4] = COMPUTADOR;
                return;
            }else if(tabuleiro[6] == VAZIO){
                //MB("Humano controla duas ou mais bordas, forcando-o a marcar na lateral...");                                             
                tabuleiro[6] = COMPUTADOR;
                return;
            }else if(tabuleiro[8] == VAZIO){
                //MB("Humano controla duas ou mais bordas, forcando-o a marcar na lateral...");                                           
                tabuleiro[8] = COMPUTADOR;
                return;
            }       
        }
             
    }
    
    if(humano_comecou_no_centro){
        //Se o humano começar no centro e controlar um canto, ele deve estar
        //tentando criar uma armadilha, portanto marcar um outro canto forçando
        //ele a marca nas laterais.
    
        if(tabuleiro[1] == HUMANO) bordas++;
        if(tabuleiro[3] == HUMANO) bordas++;
        if(tabuleiro[7] == HUMANO) bordas++;
        if(tabuleiro[9] == HUMANO) bordas++;  
        
        if(bordas >= 1)
        {             
            if(tabuleiro[1] == VAZIO){
                //MB("Humano tem o centro e um canto, marcando outro canto para forcar contra ataque");                                          
                tabuleiro[1] = COMPUTADOR;
                return;
            }else if(tabuleiro[3] == VAZIO){
                //MB("Humano tem o centro e um canto, marcando outro canto para forcar contra ataque");                                                            
                tabuleiro[3] = COMPUTADOR;
                return;
            }else if(tabuleiro[7] == VAZIO){
                //MB("Humano tem o centro e um canto, marcando outro canto para forcar contra ataque");                                                            
                tabuleiro[7] = COMPUTADOR;
                return;
            }else if(tabuleiro[9] == VAZIO){
                //MB("Humano tem o centro e um canto, marcando outro canto para forcar contra ataque");                                                            
                tabuleiro[9] = COMPUTADOR;
                return;
            }                       
        }
    }
    
    if(humano_comecou_na_lateral){
        //Se o humano marcar duas laterais marcar o ponto entre elas.
        if(tabuleiro[2] == HUMANO && tabuleiro[4] == HUMANO && tabuleiro[1] == VAZIO)
        {
            //MB("Humano marcou duas laterais, bloqueando o ataque...");             
            tabuleiro[1] = COMPUTADOR;
            return;
        }
        else if(tabuleiro[2] == HUMANO && tabuleiro[6] == HUMANO && tabuleiro[3] == VAZIO)
        {
            //MB("Humano marcou duas laterais, bloqueando o ataque...");  
            tabuleiro[3] = COMPUTADOR;
            return;        
        }
        else if(tabuleiro[6] == HUMANO && tabuleiro[8] == HUMANO && tabuleiro[9] == VAZIO)
        {
            //MB("Humano marcou duas laterais, bloqueando o ataque...");  
            tabuleiro[9] = COMPUTADOR;
            return;        
        }
        else if(tabuleiro[4] == HUMANO && tabuleiro[8] == HUMANO && tabuleiro[7] == VAZIO)
        {
            //MB("Humano marcou duas laterais, bloqueando o ataque..."); 
            tabuleiro[7] = COMPUTADOR;
            return;        
        }                                   
        
    }             
    
    if(!humano_comecou_no_centro)
    {
        if(tabuleiro[7] == HUMANO && tabuleiro[6] == HUMANO && tabuleiro[9] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");             
            tabuleiro[9] = COMPUTADOR;
            return;
        }
        else if(tabuleiro[1] == HUMANO && tabuleiro[8] == HUMANO && tabuleiro[7] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");             
            tabuleiro[7] = COMPUTADOR;
            return;        
        }
        else if(tabuleiro[2] == HUMANO && tabuleiro[7] == HUMANO && tabuleiro[1] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");             
            tabuleiro[1] = COMPUTADOR;
            return;        
        }
        else if(tabuleiro[1] == HUMANO && tabuleiro[6] == HUMANO && tabuleiro[3] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");              
            tabuleiro[3] = COMPUTADOR;
            return;        
        }       
        else if(tabuleiro[4] == HUMANO && tabuleiro[9] == HUMANO && tabuleiro[7] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");             
            tabuleiro[7] = COMPUTADOR;
            return;        
        }
        else if(tabuleiro[2] == HUMANO && tabuleiro[9] == HUMANO && tabuleiro[3] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");             
            tabuleiro[3] = COMPUTADOR;
            return;        
        }
        else if(tabuleiro[3] == HUMANO && tabuleiro[8] == HUMANO && tabuleiro[9] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");              
            tabuleiro[9] = COMPUTADOR;
            return;        
        }       
        else if(tabuleiro[4] == HUMANO && tabuleiro[3] == HUMANO && tabuleiro[1] == VAZIO)
        {
            //MB("Humano marcou uma lateral e um canto em forma de L, bloqueando...");              
            tabuleiro[1] = COMPUTADOR;
            return;        
        }                  
    }                      
    
    //Se nenhum dos critérios acima for cumprido, marcar em um
    //espaço vazio aleatório.
    //MB("Marcando posicao aleatoria");      
    do{
        pos = aleatorio(1,9);
    }while(tabuleiro[pos] != 0);
    
    tabuleiro[pos] = COMPUTADOR;
    return;
    
     
}

void MB(char * texto)
{
    pula(0,0);printf("                                                                                ");
    colorizar(VERDE_C); 
    pula(0,0);printf("%s",texto);
    colorizar(VERDE_E);    
}
