/*
-------------------------------------
|        LAB VIRUS SIMULATOR        |
|        -------------------        |
|        CREATED BY RILEA PETRU     |
|        CC 2018                    |
-------------------------------------
*/
//      ___       ___       ___       ___       ___
//     /\  \     /\__\     /\  \     /\__\     /\  \
//    /::\  \   /:/  /    /::\  \   /:/__/_   /::\  \
//   /::\:\__\ /:/__/    /::\:\__\ /::\/\__\ /::\:\__\
//   \/\::/  / \:\  \    \/\::/  / \/\::/  / \/\::/  /
//     /:/  /   \:\__\      \/__/    /:/  /    /:/  /
//     \/__/     \/__/               \/__/     \/__/
//
/***************************************************************
 * Name:      LAB VIRUS SIMULATOR
 * Purpose:   Simulation
 * Author:    Petru Rilea (dev El_Toro)
 * Created:   2018-07-27
 * Copyright: Petru ()
 * License: PROKKNG-0A2-FG3
 **************************************************************/
#include <iostream>
#define _WIN32_WINNT 0x0601
#include <ctime>
#include <time.h>
#include <windows.h>
#include <cwchar>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;
ofstream SEED_KEY("log_file1.txt",ios_base::out | ios_base::app );
ofstream logout("log_file2.txt",ios_base::out | ios_base::app );

//######################
//PROPRIETATI CONSOLA
//######################

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

//######################
//DECLARATII GLOBALE + DECLARATII FUNCTII
//#####################
int VEC_A[1000],ANAX=1;
int lab_mode();
int main_menu();
int main();
int bit,tip_zona;
int populatie=0,inceput=0;
int key_pass_uscat=0;
int key_pass_umed=0;
int verificare_conditii_ALL();
int calculare_suprafete_brut(float A, float B);
int functie_calculare_patter_zone_umede();
int functie_calculare_patter_zone_uscate();
int generare_pattern_zone_umede();
int harta[129][129],zone_mancare[129][129],zone_fauna[129][129],fauna[129][129];
int copie_harta[129][129];
int zone_temperatura[129][129];
int SEED_FINAL;
int nr_supraf_usc=0;
int nr_supraf_umd=0;
int x_analitic,y_analitic;
int x_USCAT=0,y_USCAT=0;
int x_UMED=0,y_UMED=0;
int copie_manipulabila_USCAT=0;
int copie_manipulabila_UMED=0;
int generare_fauna(int k);
int generare_pattern_zone_uscate();
int generare_zone_umplere_UMED();
int generare_zone_umplere_USCAT(int punct_origine_x,int punct_origine_y);
int verificare_punct_gasit(int x,int y);
int check_type_of_terrain();
int vector_x[]={0,1,0,-1,1,-1,-1,1};
int vector_y[]={1,0,-1,0,1,1,-1,-1};
int verificare_A=0,verificare_B=0;
void afisare_lista_virus();
void vizualizeaza_zonele_de_hrana();
void vizualizeaza_zonele_de_clima();
int tip_virus=0;
int number_of_simulation=0;
int inteligenta_artificiala_virus(int x_initial, int y_initial);
int generare_mancare_zone_mancare(int k);
int generare_clima();int algoritm_deploy();
int global_clima=0;
int modul_canibal(int x,int y);
int modul_eco(int x,int y);
int modul_evolution(int x,int y);
int SEED_KEY_GLB[10],SEED_KEY_GLBa[10];
int test_mode=0;
void vizualizeaza_zonele_de_fauna();
int selectare_categorie_virus();
int tip_virus_clima=0;
int numar_de_generatii=0;
int convertire_tip_virus=0;
int expansiune();
int functie_finala();
int afisare_harta();
int fitil_A=0;
int fitil_B=0;
int verificare_zone_mancare(int i, int j);
int adaptare_alfa=50;
int adaptare_beta=70;
int verificare_zone_fauna(int i,int j);
int verificare_statistici(int i,int j);
int generare_seed_STAT();
int INTELIGENTA=1; //SCALE 0-100 ;
int ADAPTARE=1;    //SCALE 0-100;
int PUTERE=1; //SCALE 0-10;
int analitic_mode();
int FILTRU_ANALITIC(int PLATON);
// 0 ZONE empty - asezare
// 5 virus
// 3 uscat
// 7 umed
//1==UMED
//2==USCAT
/*
ZONE CALDE
zone calde uscate - DESERT
zone calde umede - TROPICAL
*/
/*
    int nr_supraf_usc=0;
    int nr_supraf_umd=0;
ZONE RECI
*/
/* PROCENTAJ MEDIU ACVATIC || PROCENTAJ MEDIU USCAT */
//######################
//AFISARE STATISTICILE VIRUSULUI
//######################
int panou_de_siguranta_STATISTICE()
{
    if(INTELIGENTA<0 || INTELIGENTA>100)//SCALE 0-100 ;
        {
          SetConsoleTextAttribute(h, 12);
          cout<<"SYSTEM >";
          SetConsoleTextAttribute(h, 7);
          SetConsoleTextAttribute(h, 206);
          cout<<" INTELIGENTA PESTE LIMITELE ADMISE !"<<"\n";
          SetConsoleTextAttribute(h, 7);
          logout<<" INTELIGENTA PESTE LIMITELE ADMISE !"<<"\n";
          SetConsoleTextAttribute(h, 12);
          cout<<"SYSTEM >";
          SetConsoleTextAttribute(h, 7);
          cout<<"ERROR 0X1A"<<"\n";
          logout<<"ERROR 0X1A"<<"\n";
          system("pause");
          system("cls");
        }
    if(ADAPTARE<0 || ADAPTARE>100)
        {
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            SetConsoleTextAttribute(h, 206);
            cout<<"ADAPTARE PESTE LIMITELE ADMISE !"<<"\n";
            SetConsoleTextAttribute(h, 7);
            logout<<"ADAPTARE PESTE LIMITELE ADMISE !"<<"\n";
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            cout<<"ERROR 0X1B"<<"\n";
            logout<<"ERROR 0X1B"<<"\n";
            system("pause");
            system("cls");
        }
    if(PUTERE<0 || PUTERE>10)
        {
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            SetConsoleTextAttribute(h, 206);
            cout<<"PUTERE PESTE LIMITELE ADMISE !"<<"\n";
            SetConsoleTextAttribute(h, 7);
            logout<<"PUTERE PESTE LIMITELE ADMISE !"<<"\n";
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            cout<<"ERROR 0X1C"<<"\n";
            logout<<"ERROR 0X1C"<<"\n";
            system("pause");
            system("cls");
        }
}
void TRANSCRIERE_TIP_CLIMA_IN_CUVINTE()
{
    if(tip_zona==1)
        {
            cout<<" CALDA";
        }else cout<<" RECE";
}

void TRANSCRIERE_TIP_VIRUS_IN_CUVINTE()
{
    if(tip_virus==1 && convertire_tip_virus!=3)
        {
            cout<<" VIRUS DE APA";
        }else
        {
            if(convertire_tip_virus==3)
                {
                    cout<<" VIRUS AMFIBIAN";
                }else cout<<" VIRUS DE USCAT";
        }

}
void TRANSCRIERE_TIP_VIRUS_CLIMA()
{
    if(tip_virus_clima==45)
        {
            cout<<" VIRUS ADAPTAT LA CLIMA CALDA";
        }else cout<<" VIRUS ADAPTAT LA CLIMA RECE";
}
void meniu_afisare_status()
{
    cout<<"STATISTICI"<<"\n";
    logout<<"STATISTICI"<<"\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~"<<"\n";
    logout<<"~~~~~~~~~~~~~~~~~~~~"<<"\n";
    SetConsoleTextAttribute(h, 14);
    cout<<"INT";
    SetConsoleTextAttribute(h, 7);
    cout<<": "<<INTELIGENTA<<"\n";
    logout<<"INT: "<<INTELIGENTA<<"\n";
    SetConsoleTextAttribute(h, 14);
    cout<<"ADP";
    SetConsoleTextAttribute(h, 7);
    cout<<": "<<ADAPTARE<<"\n";
    logout<<"ADP: "<<ADAPTARE<<"\n";
    SetConsoleTextAttribute(h, 14);
    cout<<"POW";
    SetConsoleTextAttribute(h, 7);
    cout<<": "<<PUTERE<<"\n";
    logout<<"POW: "<<PUTERE<<"\n";
    SetConsoleTextAttribute(h, 14);
    cout<<"POPULATIE";
    SetConsoleTextAttribute(h, 7);
    cout<<": "<<populatie<<"\n";
    logout<<"POPULATIE: "<<populatie<<"\n";
    SetConsoleTextAttribute(h, 14);
    cout<<"CLIMA_TEREN";SetConsoleTextAttribute(h, 7);
    cout<<": ";TRANSCRIERE_TIP_CLIMA_IN_CUVINTE();
    cout<<"\n";
    SetConsoleTextAttribute(h, 14);
    cout<<"TIP_VIRUS";SetConsoleTextAttribute(h, 7);
    cout<<": ";TRANSCRIERE_TIP_VIRUS_IN_CUVINTE();
    cout<<" | ";TRANSCRIERE_TIP_VIRUS_CLIMA();
    cout<<"\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~"<<"\n";
    logout<<"~~~~~~~~~~~~~~~~~~~~"<<"\n";
}
//######################
//FUNCTIE DE LEGATURA INTRE AFISAREA HARTII SI AFISAREA STATISTICILOR VIRUSULUI
//######################

void AFISARE_TOTAL()
{
    meniu_afisare_status();
    afisare_harta();
}

//######################
//VERIFICAREA GENERARII ZONELOR uscate
//######################

int verificare_status_USCAT_TO_UMED()
{
    if(copie_manipulabila_USCAT<=0 && fitil_A==0)
        {
            system("cls");
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            SetConsoleTextAttribute(h, 10);
            cout<<" 100%";
            SetConsoleTextAttribute(h, 7);
            cout<<" IMPARTIRE ZONE USCATE"<<"\n";
            logout<<"SYSTEM > 100% IMPARTIRE ZONE USCATE"<<"\n";
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            afisare_harta();
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            cout<<"\n";logout<<"\n";
            key_pass_uscat=1;
            fitil_A=1;
        }

}
//######################
//VERIFICAREA GENERARII ZONELOR umede
//######################

int verificare_status_UMED()
{
    system("cls");
    if(copie_manipulabila_UMED<=0 )
        {
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            SetConsoleTextAttribute(h, 10);
            cout<<" 100%";
            SetConsoleTextAttribute(h, 7);
            cout<<" IMPARTIRE ZONE UMEDE"<<"\n";
            logout<<"SYSTEM > 100% IMPARTIRE ZONE UMEDE"<<"\n";
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            afisare_harta();
            cout<<"_____________________________________"<<"\n\n";
            logout<<"_____________________________________"<<"\n\n";
            if(test_mode!=3)
		    Sleep(3000);
            key_pass_umed=1;
        }
}

//######################
//FUNCTIE DE AFISARE A HARTII
//######################

int afisare_harta()
{
    int j=1;
    cout<<"\n";
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    if(harta[i][j]==3)
                        {
                            SetConsoleTextAttribute(h, 34);
                            cout<<harta[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                            logout<<harta[i][j]<<" ";
                        }else
                            {
                                if(harta[i][j]==7)
                                    {
                                        SetConsoleTextAttribute(h, 17);
                                        cout<<". ";
                                        SetConsoleTextAttribute(h, 7);
                                        logout<<". ";
                                    }
                                if(harta[i][j]==5)
                                    {
                                        SetConsoleTextAttribute(h, 71);
                                        cout<<"X ";
                                        SetConsoleTextAttribute(h, 7);
                                        logout<<"X ";
                                    }
                                if(harta[i][j]!=7 && harta[i][j]!=5 && harta[i][j]!=3)
                                    {
                                        SetConsoleTextAttribute(h, 135);
                                        cout<<"O ";
                                        SetConsoleTextAttribute(h, 7);
                                        logout<<"O ";
                                    }
                            }
                }
            cout<<"\n";
            logout<<"\n";
        }
}

//######################
//FUNCTIE MENIU PRINCIPAL !!
//######################

int functie_meniu_principal()
{
    int KONTROL_FONT=0;
    system("cls");
    cout<<"_____________________________________"<<"\n\n";
    cout<<"VIRUS LAB SIMULATOR alpha_V.0.5.1"<<"\n";
    cout<<"created by Rilea Petru @CC"<<"\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    cout<<"MARIME ZONA SIMULARE"<<"\n";
    cout<<"--------------------"<<"\n";
    cout<<"1. 32 BIT"<<"\n";
    cout<<"2. 64 BIT"<<"\n";
    cout<<"3. 128 BIT"<<"\n";
    cout<<"--------------------"<<"\n";
    SetConsoleTextAttribute(h, 10);
    cout<<"INPUT_!@>";
    SetConsoleTextAttribute(h, 7);
    cout<<" INSERT TOTAL SIZE (>=5 ; <=128): ";
    cin>>bit;
    SetConsoleTextAttribute(h, 10);
    cout<<"INPUT_!@>";
    SetConsoleTextAttribute(h, 7);
    cout<<" INSERT FONT SIZE: ";
    cin>>KONTROL_FONT;
    if(bit <5 )
        {
          cout<<"\n";
              SetConsoleTextAttribute(h, 12);cout<<"SYSTEM > ";SetConsoleTextAttribute(h, 7);
          cout<<"INTRODUCE-TI O VALOARE MAI MARE "<<"\n";
          system("pause");
          functie_meniu_principal();
        }
    selectare_categorie_virus();
    return 0;
}

//######################
//FUNCTIE DE GENERARE A HARTII BRUTE / GOALE
//######################

int generare_harta()
{
    int j=0;
    cout<<"\n";
    logout<<"\n";
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    harta[i][j]=0;
                    copie_harta[i][j]=harta[i][j];
                    cout<<harta[i][j]<<" ";
                    logout<<harta[i][j]<<" ";
                }
            cout<<"\n";
            logout<<"\n";
        }
}
int ACCES_KEY=0;

//######################
//ALGORITMUL DE GENERARE A ZONELOR ALEATORII USCATE
//######################

int generare_zone_umplere_USCAT(int punct_origine_x,int punct_origine_y)
{
    while(fitil_A==0 && copie_manipulabila_USCAT>0 )
        {
                if(fitil_A==0)
                {
                    if(fitil_A==0)
                        verificare_status_USCAT_TO_UMED();
                    Sleep(150);
                    srand(time(NULL));
                    int KEY_A=rand()%8+0;
                    system("cls");
                    cout<<"--------------------------------------------"<<"\n";
                    logout<<"--------------------------------------------"<<"\n";
                    SetConsoleTextAttribute(h, 12);
                    cout<<"SYSTEM >";
                    SetConsoleTextAttribute(h, 7);
                    cout<<" SE GENEREAZA TERENUL"<<"\n";
                    logout<<"SYSTEM > SE GENEREAZA TERENUL"<<"\n";
                    cout<<"--------------------------------------------"<<"\n";
                    logout<<"--------------------------------------------"<<"\n";
                    cout<<"USCAT"<<"\n";
                    logout<<"USCAT"<<"\n";
                    cout<<"KEY=> #"<<KEY_A<<"\n";
                    logout<<"KEY=> #"<<KEY_A<<"\n";
                    if(fitil_A==0 && harta[vector_x[KEY_A]+punct_origine_x][vector_y[KEY_A]+punct_origine_y]!=3 && copie_manipulabila_USCAT!=0 && punct_origine_x+vector_x[KEY_A]>0 && punct_origine_x+vector_x[KEY_A]<=bit && punct_origine_y+vector_y[KEY_A]>0 && punct_origine_y+vector_y[KEY_A]<=bit)
                        {
                            punct_origine_x=vector_x[KEY_A]+punct_origine_x;
                            punct_origine_y=vector_y[KEY_A]+punct_origine_y;
                            cout<<"BIT PLASAT ... "<<" ";
                            cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                            cout<<"--------------------------------------------"<<"\n";
                            harta[punct_origine_x][punct_origine_y]=3;
                            copie_manipulabila_USCAT--;
                            if(fitil_A==0)
                                verificare_status_USCAT_TO_UMED();
                        }else
                            {
                            for(int i=0;i<8;i++)
                                {
                                    if(fitil_A==0 && harta[vector_x[i]+punct_origine_x][vector_y[i]+punct_origine_y]!=3 && copie_manipulabila_USCAT!=0 && punct_origine_x+vector_x[i]>0 && punct_origine_x+vector_x[i]<=bit && punct_origine_y+vector_y[i]>0 && punct_origine_y+vector_y[i]<=bit)
                                        {
                                            punct_origine_x=punct_origine_x+vector_x[i];
                                            punct_origine_y=punct_origine_y+vector_y[i];
                                            harta[punct_origine_x][punct_origine_y]=3;
                                            copie_manipulabila_USCAT--;
                                            cout<<"BIT PLASAT ... "<<" ";
                                            cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                                            cout<<"--------------------------------------------"<<"\n";
                                            if(fitil_A==0)
                                                verificare_status_USCAT_TO_UMED();
                                            generare_zone_umplere_USCAT(punct_origine_x,punct_origine_y);
                                        }
                                }
                            if(fitil_A==0)
                                verificare_status_USCAT_TO_UMED();
                            int k=0;
                            if(fitil_A==0 && punct_origine_x>bit)
                                {
                                    for(int i=1;i<=bit;i++)
                                        {
                                            for(k=1;k<=bit;k++)
                                                {
                                                    if(harta[i][k]!=3)
                                                        {
                                                            punct_origine_x=i;
                                                            punct_origine_y=k;
                                                            harta[punct_origine_x][punct_origine_y]=3;
                                                            copie_manipulabila_USCAT--;
                                                            cout<<"BIT PLASAT ... "<<" ";
                                                            cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                                                            cout<<"--------------------------------------------"<<"\n";
                                                            if(fitil_A==0)
                                                            verificare_status_USCAT_TO_UMED();
                                                            generare_zone_umplere_USCAT(punct_origine_x,punct_origine_y);
                                                        }
                                                }
                                        }
                                }
                            if(fitil_A==0 && punct_origine_y>bit)
                                {
                                    for(int i=1;i<=bit;i++)
                                        {
                                            for(k=1;k<=bit;k++)
                                                {
                                                    if(harta[i][k]!=3)
                                                    {
                                                        punct_origine_x=i;
                                                        punct_origine_y=k;
                                                        harta[punct_origine_x][punct_origine_y]=3;
                                                        copie_manipulabila_USCAT--;
                                                        cout<<"BIT PLASAT ... "<<" ";
                                                        cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                                                        cout<<"--------------------------------------------"<<"\n";
                                                        if(fitil_A==0)
                                                            verificare_status_USCAT_TO_UMED();
                                                        generare_zone_umplere_USCAT(punct_origine_x,punct_origine_y);
                                                    }
                                                }
                                        }
                                }
                            if(fitil_A==0 && punct_origine_x<=0)
                                {
                                    for(int i=1;i<=bit;i++)
                                        {
                                            for(k=1;k<=bit;k++)
                                                {
                                                    if(harta[i][k]!=3)
                                                        {
                                                            punct_origine_x=i;
                                                            punct_origine_y=k;
                                                            harta[punct_origine_x][punct_origine_y]=3;
                                                            copie_manipulabila_USCAT--;
                                                            cout<<"BIT PLASAT ... "<<" ";
                                                            cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                                                            cout<<"--------------------------------------------"<<"\n";
                                                            if(fitil_A==0)
                                                                verificare_status_USCAT_TO_UMED();
                                                            generare_zone_umplere_USCAT(punct_origine_x,punct_origine_y);
                                                        }
                                                    }
                                        }
                                }
                            if(fitil_A==0 && punct_origine_y<=0)
                                {
                                    for(int i=1;i<=bit;i++)
                                        {
                                            for(k=1;k<=bit;k++)
                                                {
                                                    if(harta[i][k]!=3)
                                                        {
                                                            punct_origine_x=i;
                                                            punct_origine_y=k;
                                                            harta[punct_origine_x][punct_origine_y]=3;
                                                            copie_manipulabila_USCAT--;
                                                            cout<<"BIT PLASAT ... "<<" ";
                                                            cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                                                            cout<<"--------------------------------------------"<<"\n";
                                                            if(fitil_A==0)
                                                                verificare_status_USCAT_TO_UMED();
                                                            generare_zone_umplere_USCAT(punct_origine_x,punct_origine_y);
                                                        }
                                                }
                                        }
                                }
                        verificare_status_USCAT_TO_UMED();
                        for(int i=1;i<=bit;i++)
                            {
                            for(k=1;k<=bit;k++)
                                {
                                        if(fitil_A==0 && harta[i][k]!=3)
                                            {
                                                punct_origine_x=i;
                                                punct_origine_y=k;
                                                harta[punct_origine_x][punct_origine_y]=3;
                                                copie_manipulabila_USCAT--;
                                                cout<<"BIT PLASAT ... "<<" ";
                                                cout<<"COORDONATE: X["<<punct_origine_x<<"]"<<" Y["<<punct_origine_y<<"]"<<"  ZONE RAMASE="<<copie_manipulabila_USCAT<<"\n";
                                                cout<<"--------------------------------------------"<<"\n";
                                                if(fitil_A==0)
                                                    verificare_status_USCAT_TO_UMED();
                                                generare_zone_umplere_USCAT(punct_origine_x,punct_origine_y);
                                            }
                                }
                            }

                        }
                    }
        }
}

//######################
// FUNCTIA DE LEGATURA INTRE GENERAREA HARTII (TOTALA) / panoul de control al generarii globale
//######################

int generare_zone_harta()
{
    system("cls");
    cout<<"_____________________________________"<<"\n"<<"\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE GENEREAZA HARTA ... "<<"\n\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    system("cls");
    check_type_of_terrain();
    functie_calculare_patter_zone_uscate();
    functie_calculare_patter_zone_umede();
    generare_clima();
    generare_mancare_zone_mancare(global_clima);
    generare_fauna(global_clima);
    return 0;
}

//######################
//GENERAREA DE STATISTICI PREALABILE ALEA HARTII
//######################

int check_type_of_terrain()
{
    cout<<"_____________________________________"<<"\n"<<"\n";
    logout<<"_____________________________________"<<"\n"<<"\n";
    cout<<"STATISTICI DESPRE HARTA"<<"\n";
    logout<<"STATISTICI DESPRE HARTA"<<"\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    logout<<"_____________________________________"<<"\n"<<"\n";
    float procentaj_mediu_static_acvatic=0;
    float procentaj_mediu_static_uscat=0;
    srand(time(NULL));
    Sleep(100);
    int rand_mediu_uscat=rand()%100+0;
    procentaj_mediu_static_uscat=rand_mediu_uscat;
    procentaj_mediu_static_acvatic=100-rand_mediu_uscat;
    cout<<"chunkuri_USCATE: "<<procentaj_mediu_static_uscat<<"%"<<"\n"<<"chunkuri_UMEDE: "<<procentaj_mediu_static_acvatic<<"%"<<"\n";
    logout<<"chunkuri_USCATE: "<<procentaj_mediu_static_uscat<<"%"<<"\n"<<"chunkuri_UMEDE: "<<procentaj_mediu_static_acvatic<<"%"<<"\n";
    calculare_suprafete_brut(procentaj_mediu_static_uscat,procentaj_mediu_static_acvatic);
    return 0;
}

//######################
//FUNCTIE DE STATISTICA DESPRE harta
//######################

int calculare_suprafete_brut(float brut_uscat, float brut_umed)
{
    nr_supraf_usc=(brut_uscat/100)*(bit*bit)+1;
    nr_supraf_umd=(brut_umed/100)*(bit*bit);
    cout<<"TOTAL: "<<nr_supraf_usc<<" + "<<nr_supraf_umd<<" = "<< nr_supraf_umd+nr_supraf_usc<<"\n";
    logout<<"TOTAL: "<<nr_supraf_usc<<" + "<<nr_supraf_umd<<" = "<< nr_supraf_umd+nr_supraf_usc<<"\n";
    cout<<"VERIFICARE: "<<nr_supraf_usc+nr_supraf_umd<<" / "<< bit<<" = "<<(nr_supraf_usc+nr_supraf_umd)/bit<<"\n";
    logout<<"VERIFICARE: "<<nr_supraf_usc+nr_supraf_umd<<" / "<< bit<<" = "<<(nr_supraf_usc+nr_supraf_umd)/bit<<"\n";
    cout<<"chunkuri_USCATE: "<<nr_supraf_usc<<" titles"<<"\n"<<"chunkuri_UMEDE: "<<nr_supraf_umd<<" titles"<<"\n";
    logout<<"chunkuri_USCATE: "<<nr_supraf_usc<<" titles"<<"\n"<<"chunkuri_UMEDE: "<<nr_supraf_umd<<" titles"<<"\n";
    copie_manipulabila_USCAT=nr_supraf_usc;
    copie_manipulabila_UMED=nr_supraf_umd;
    verificare_A=nr_supraf_usc;
    verificare_B=nr_supraf_umd;
    return 0;
}

//######################
//LEGATURA MOTORULUI DE GENERARE A ZONELOR USCATE
//######################

int functie_calculare_patter_zone_uscate()
{
    generare_pattern_zone_uscate();
    return 0;
}

//######################
//LEGATURA MOTORULUI DE GENERARE A ZONELOR UMEDE
//######################
int functie_calculare_patter_zone_umede()
{
    generare_pattern_zone_umede();
    return 0;
}

//######################
//MOTOR DE GENERARE A ZONELOR uscate
//######################

int generare_pattern_zone_uscate()
{
    srand(time(NULL));
    x_USCAT=rand()%bit+1;
    y_USCAT=rand()%bit+1;
    harta[x_USCAT][y_USCAT]=3;
    copie_manipulabila_USCAT--;
    cout<<x_USCAT<<" "<<y_USCAT<<"\n";
    if(test_mode!=3)
	    Sleep(3000);
    generare_zone_umplere_USCAT(x_USCAT,y_USCAT);
    return 0;
}

//######################
//MOTOR DE GENERARE A ZONELOR umede
//######################

int generare_pattern_zone_umede()
{
    while(harta[x_UMED][y_UMED]!=3)
        {
            srand(time(NULL));
            x_UMED=rand()%bit+1;
            y_UMED=rand()%bit+1;
            if(harta[x_UMED][y_UMED]!=3)
                {
                    harta[x_UMED][y_UMED]=7;
                    break;
                }
        }
    copie_manipulabila_UMED--;
    if(test_mode!=3)
    	Sleep(3000);
    generare_zone_umplere_UMED();
    return 0;
}

//######################
//ALGORTIMUL DE GENERARE A ZONELOR umede
//######################

int generare_zone_umplere_UMED()
{
    int k=0;
    cout<<"--------------------------------------------"<<"\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE GENEREAZA APA"<<"\n";
    cout<<"--------------------------------------------"<<"\n";
    for(int i=1;i<=bit;i++)
        {
            for(k=1;k<=bit;k++)
                {

                    if(harta[i][k]!=3 && harta[i][k]!=7)
                        {
                            harta[i][k]=7;
                            copie_manipulabila_UMED--;
                            cout<<copie_manipulabila_UMED<<" ";
                        }
                }

        }
    cout<<"\n";
    verificare_status_UMED();

}

//######################
//VERIFICARA GENERARII GLOBALE B
//######################

int verificare_TOTALA()
{
    if(key_pass_uscat!=1 && key_pass_umed!=1)
        {
            system("cls");
            SetConsoleTextAttribute(h, 206);
            cout<<"GENERAREA CORUPTA !"<<"\n";
            SetConsoleTextAttribute(h, 7);
            cout<<"RESTARTATI REGENERAREA... "<<"\n";
            system("pause");
            main();
        }
    int sum_A=0,sum_B=0,k=0;
    for(int i=1;i<=bit;i++)
        {
            for(k=1;k<=bit;k++)
                {
                    if(harta[i][k]==3)
                        sum_A++;
                    if(harta[i][k]==7)
                        sum_B++;
                }
        }
    if(sum_A==verificare_A)
        {
            cout<<"ZONE USCATE VERIFICATE ! 0% errors "<<"\n";
            cout<<"CALCULATE: "<<verificare_A<<"\n";
            cout<<"CITITE: "<<sum_A<<"\n";
        }else{
                cout<<"ZONE USCATE VERIFICATE !"<<verificare_A/sum_A<<"% errors"<<"\n";
                cout<<"CALCULATE: "<<verificare_A<<"\n";
                cout<<"CITITE: "<<sum_A<<"\n";
            }
    if(sum_B==verificare_B)
        {
            cout<<"ZONE UMEDE VERIFICATE ! 0% errors "<<"\n";
            cout<<"CALCULATE: "<<verificare_B<<"\n";
            cout<<"CITITE: "<<sum_B<<"\n";
        }else{
                cout<<"ZONE UMEDE VERIFICATE !"<<verificare_B/sum_B<<"% errors"<<"\n";
                cout<<"CALCULATE: "<<verificare_B<<"\n";
                cout<<"CITITE: "<<sum_B<<"\n";
            }
    cout<<"HASH_FINAL= sum("<<sum_A+sum_B<<")"<<" / "<<bit<<" = "<<(sum_A+sum_B)/bit<<"\n";
}

//######################
//SELECTAREA SI INTRODUCEREA IN SISTEM A ALEGERII DE VIRUSUL
//######################

int selectare_categorie_virus()
{
    system("cls");
    cout<<"--------------------"<<"\n";
    cout<<"SELECTEAZA TIPUL DE VIRUS"<<"\n";
    cout<<"--------------------"<<"\n";
    Sleep(100);
    int alegere=0;
    afisare_lista_virus();
    cout<<"--------------------"<<"\n";
    cout<<"\n";
    SetConsoleTextAttribute(h, 10);
    cout<<"INPUT_!@>";
    SetConsoleTextAttribute(h, 7);
    cin>>alegere;
    if(alegere!=1 && alegere!=2)
        {
            selectare_categorie_virus();
        }
    tip_virus=alegere;
    if(tip_virus==1)
        {

        }else{
            if(tip_virus==2)
                {

                }
            }
        SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE GENEREAZA IDENTITATEA VIRUSULUI ";
    Sleep(500);
    for(int i=1;i<=10;i++)
        {
            cout<<"-\b";
            Sleep(50);
            cout<<"|\b";
            Sleep(50);
            cout<<"/\b";
            Sleep(50);
        }
    cout<<"\n";
    SetConsoleTextAttribute(h, 10);
    cout<<"INPUT_!@>";
    SetConsoleTextAttribute(h, 7);
    cout<<" VIRUS CLIMA CALDA(45) / RECE(46):";
    cin>>tip_virus_clima;
    if(tip_virus_clima!=45 && tip_virus_clima!=46)
        selectare_categorie_virus();
    //SE GENEREAZA ATRIBUTIILE VIRUSULUI SI SE SALVEAZA IN FISIER CU UN ANUMIT SEED/ID CARE VA FI COMPARAT LA FIECARE INITIALIZARE
    //DACA SEEDUL EXISTA SE VA RELUAT GENERAREA PANA LA UN NOU SEED;
    generare_seed_STAT();
    Sleep(3000);
    return 0;
}
int generare_seed_STAT()
{
    int ok=0;
    srand(time(NULL));
    INTELIGENTA=rand()%100+0;
    ADAPTARE=rand()%100+0;
    PUTERE=rand()%10+0;
    SEED_KEY_GLB[1]=INTELIGENTA;
    SEED_KEY_GLB[2]=ADAPTARE;
    SEED_KEY_GLB[3]=PUTERE;
    logout<<"SYSTEM -> SEED_KEY={";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SEED_KEY={";
    for(int i=1;i<=3;i++)
        {
            cout<<SEED_KEY_GLB[i];
            logout<<SEED_KEY_GLB[i];
            SEED_KEY<<SEED_KEY_GLB[i]<<".";
            logout<<SEED_KEY_GLB[i]<<".";
        }
    int random_identifique=rand()%9999+0;
    SEED_KEY<<random_identifique;
    logout<<random_identifique;
    logout<<"}"<<"\n";
    cout<<"}"<<"\n";
    SEED_KEY<<"\n";
    //COMPARARE IN FISIERUL DE STOCARE SEED
}
//######################
//AFISARE LISTA CU TIPUL DE VIRUS
//######################

void afisare_lista_virus()
{
    cout<<"1. VIRUS ACVATIC"<<"\n";
    cout<<"2. VIRUS TERESTRU"<<"\n";
}
int copie_orgine=0;

//######################
//FUNCTIE DE PLASARE VIRUS PE HARTA ; ACEASTA ACCESEAZA INTELIGENTA ARTIFICIALA A VIRUSULUI
//######################

int plasare_virus()
{
    system("pause");
    system("cls");
    int optiune;
    meniu_afisare_status();
    cout<<"=========================="<<"\n";
    afisare_harta();cout<<"\n";
    cout<<"=========================="<<"\n\n";
    cout<<"1.VIZUALIZEAZA ZONELE DE FAUNA"<<"\n";
    cout<<"2.VIZUALIZEAZA ZONELE DE HRANA"<<"\n";
    cout<<"3.VIZUALIZEAZA CLIMA"<<"\n";
    cout<<"4.PLASEAZA VIRUSUL"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cin>>optiune;
    switch(optiune)
        {
            case 1:
                vizualizeaza_zonele_de_fauna();
                break;
            case 2:
                vizualizeaza_zonele_de_hrana();
                break;
            case 3:
                vizualizeaza_zonele_de_clima();
                break;
            case 4:
                algoritm_deploy();
                break;
        }
}
void vizualizeaza_zonele_de_fauna()
{
    system("pause");
    system("cls");
    int optiune,j;
    meniu_afisare_status();
    cout<<"=Z=O=N=E===F=A=U=N=A======"<<"\n";
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    cout<<fauna[i][j]<<" ";
                }
            cout<<"\n";
        }
    cout<<"\n";
    cout<<"=Z=O=N=E===F=A=U=N=A======"<<"\n";
    cout<<"1.AFISEAZA HARTA"<<"\n";
    cout<<"2.VIZUALIZEAZA ZONELE DE HRANA"<<"\n";
    cout<<"3.VIZUALIZEAZA CLIMA"<<"\n";
    cout<<"4.PLASEAZA VIRUSUL"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cin>>optiune;
    switch(optiune)
        {
            case 1:
                plasare_virus();
                break;
            case 2:
                vizualizeaza_zonele_de_hrana();
                break;
            case 3:
                vizualizeaza_zonele_de_clima();
                break;
            case 4:
                algoritm_deploy();
                break;
        }
}
void vizualizeaza_zonele_de_hrana()
{
    system("pause");
    system("cls");
    int optiune,j;
    meniu_afisare_status();
    cout<<"=========================="<<"\n";
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    cout<<zone_mancare[i][j]<<" ";
                }
            cout<<"\n";
        }
    cout<<"\n";
    cout<<"=Z=O=N=E===H=R=A=N=A======"<<"\n";
    cout<<"1.AFISEAZA HARTA"<<"\n";
    cout<<"2.VIZUALIZEAZA ZONELE DE FAUNA"<<"\n";
    cout<<"3.VIZUALIZEAZA CLIMA"<<"\n";
    cout<<"4.PLASEAZA VIRUSUL"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cin>>optiune;
    switch(optiune)
        {
            case 1:
                plasare_virus();
                break;
            case 2:
                vizualizeaza_zonele_de_fauna();
                break;
            case 3:
                vizualizeaza_zonele_de_clima();
                break;
            case 4:
                algoritm_deploy();
                break;
        }
}
void vizualizeaza_zonele_de_clima()
{
    system("pause");
    system("cls");
    int optiune,j;
    meniu_afisare_status();
    cout<<"=========================="<<"\n";
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    cout<<zone_temperatura[i][j]<<" ";
                }
            cout<<"\n";
        }
    cout<<"\n";
    cout<<"=Z=O=N=E===C=L=I=M=A======"<<"\n";
    cout<<"1.AFISEAZA HARTA"<<"\n";
    cout<<"2.VIZUALIZEAZA ZONELE DE FAUNA"<<"\n";
    cout<<"3.VIZUALIZEAZA ZONELE DE HRANA"<<"\n";
    cout<<"4.PLASEAZA VIRUSUL"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cin>>optiune;
    switch(optiune)
        {
            case 1:
                plasare_virus();
                break;
            case 2:
                vizualizeaza_zonele_de_fauna();
                break;
            case 3:
                vizualizeaza_zonele_de_hrana();
                break;
            case 4:
                algoritm_deploy();
                break;
        }
}
int algoritm_deploy()
{
    int x_virus,y_virus;
    cout<<"DEPLOY VIRUS -> "<<" X:";
    cin>>x_virus;
    cout<<"DEPLOY VIRUS -> "<<" Y:";
    cin>>y_virus;
    if(x_virus<bit || x_virus>=0 || y_virus<bit || y_virus>=0)
        {

        }else{
                SetConsoleTextAttribute(h, 12);
                cout<<"SYSTEM >";
                SetConsoleTextAttribute(h, 7);
                cout<<" IN AFARA GRANITELOR HARTII  ! "<<"\n";
                system("pause");
                plasare_virus();
            }
    cout<<"\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" VIRUS DEPLOYED !"<<"\n";
    copie_orgine=harta[x_virus][y_virus];
    harta[x_virus][y_virus]=5;
    populatie++;
    numar_de_generatii++;
    inceput=1;
    Sleep(250);
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" INITIALIZARE ALGORITM VIRUS ";
    Sleep(500);
    for(int i=1;i<=10;i++)
        {
            cout<<"-\b";
            Sleep(50);
            cout<<"|\b";
            Sleep(50);
            cout<<"/\b";
            Sleep(50);
        }
    cout<<"\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" ALGORITM INCARCAT ! "<<"\n";
    Sleep(250);
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE INCEPE SIMULAREA ! "<<"\n";
    Sleep(3000);
    inteligenta_artificiala_virus(x_virus,y_virus);
}
int inteligenta_artificiala_virus(int x_initial,int y_initial)
{
    if(populatie<=0)
        {
            cout<<"\n";
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM > ";
            SetConsoleTextAttribute(h, 7);
            SetConsoleTextAttribute(h, 142);
            cout<<"POPULATIE = 0 ! "<<"\n\n";
            SetConsoleTextAttribute(h, 7);
            logout<<"SYSTEM > POPULATIE = 0 ! "<<"\n\n";
            SetConsoleTextAttribute(h, 12);
            cout<<"SYSTEM >";
            SetConsoleTextAttribute(h, 7);
            cout<<" END OF SIMULATION ! "<<"\n";
            logout<<"SYSTEM > END OF SIMULATION ! ";
            functie_finala();
        }
    int curent_x=x_initial;
    int curent_y=y_initial;
    //SE INCEPE SIMULAREA
    int directie_x[]={0,1,0,-1,1,-1,-1,1};
    int directie_y[]={1,0,-1,0,1,1,-1,-1};
    int FTL=0;
    srand(time(NULL));
    int seed_int_art=rand()%8+0;
    Sleep(50);
    if(curent_x+directie_x[seed_int_art]<=bit && curent_y+directie_y[seed_int_art]<=bit && curent_x+directie_x[seed_int_art]>0 && curent_y+directie_y[seed_int_art]>0)
        {
            if(harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]!=5 && harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]!=99)
                {
                    if(harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]!=5)
                        {
                            if(tip_virus==1)
                                {
                                    if(harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]==7)
                                        {
                                            //VIRUS OK
                                            harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]=5;
                                            SetConsoleTextAttribute(h, 12);
                                            cout<<"SYSTEM >";
                                            SetConsoleTextAttribute(h, 7);
                                            cout<<" POPULATIE";
                                            SetConsoleTextAttribute(h, 142);
                                            cout<<" INCREASE+1";
                                            SetConsoleTextAttribute(h, 7);
                                            cout<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                            logout<<"SYSTEM > POPULATIE INCREASE+1"<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                            if(test_mode!=3)
						    Sleep(500);
                                            populatie++;
                                            ADAPTARE++;
                                            numar_de_generatii++;
                                            curent_x=curent_x+directie_x[seed_int_art];
                                            curent_y=curent_y+directie_y[seed_int_art];
                                        }else{
                                                if(harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]==3 && convertire_tip_virus!=3)
                                                    {
                                                        int sansa_de_adaptare_la_uscat=rand()%20+1;
                                                        int SUMA_DE_CRITERIU=0;
                                                        SUMA_DE_CRITERIU=ADAPTARE+INTELIGENTA;
                                                        if(sansa_de_adaptare_la_uscat==10 && SUMA_DE_CRITERIU>=90)
                                                            {
                                                                //VIRUS OK -> SE ADAPTEAZA LA AMBELE REGIUNI
                                                                convertire_tip_virus=3;
                                                                harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]=5;
                                                                SetConsoleTextAttribute(h, 12);
                                                                cout<<"SYSTEM >";
                                                                SetConsoleTextAttribute(h, 7);
                                                                SetConsoleTextAttribute(h, 10);
                                                                cout<<"VIRUSUL S-A ADAPTAT PE USCAT!";
                                                                SetConsoleTextAttribute(h, 7);
                                                                cout<<" POPULATIE";
                                                                SetConsoleTextAttribute(h, 142);
                                                                cout<<" INCREASE+1";
                                                                SetConsoleTextAttribute(h, 7);
                                                                cout<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                logout<<"SYSTEM > POPULATIE INCREASE+1"<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                               	if(test_mode!=3)
									Sleep(500);
                                                                populatie++;
                                                                ADAPTARE++;
                                                                numar_de_generatii++;
                                                                curent_x=curent_x+directie_x[seed_int_art];
                                                                curent_y=curent_y+directie_y[seed_int_art];
                                                            }else{
                                                                    //VIRUSUL MOARE
                                                                    harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]=99;
                                                                    SetConsoleTextAttribute(h, 12);
                                                                    cout<<"SYSTEM >";
                                                                    SetConsoleTextAttribute(h, 7);
                                                                    SetConsoleTextAttribute(h, 10);
                                                                    cout<<"VIRUSUL NU S-A PUTUT ADAPTA PE USCAT!";
                                                                    SetConsoleTextAttribute(h, 7);
                                                                    cout<<" POPULATIE";
                                                                    SetConsoleTextAttribute(h, 142);
                                                                    cout<<" DECREASE -1";
                                                                    SetConsoleTextAttribute(h, 7);
                                                                    cout<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                    logout<<"SYSTEM > POPULATIE DECREASE -1"<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                    if(test_mode!=3)
									    Sleep(500);
                                                                    numar_de_generatii++;
                                                                    curent_x=curent_x+directie_x[seed_int_art];
                                                                    curent_y=curent_y+directie_y[seed_int_art];
                                                                }
                                                        }
                                            }
                                        verificare_conditii_ALL();
                                    }else{
                                            if(harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]==3)
                                                {
                                                    //VIRUS OK
                                                    harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]=5;
                                                    SetConsoleTextAttribute(h, 12);
                                                    cout<<"SYSTEM >";
                                                    SetConsoleTextAttribute(h, 7);
                                                    cout<<" POPULATIE";
                                                    SetConsoleTextAttribute(h, 142);
                                                    cout<<" INCREASE+1";
                                                    SetConsoleTextAttribute(h, 7);
                                                    cout<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                    logout<<"SYSTEM > POPULATIE INCREASE+1"<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                    if(test_mode!=3)
							    Sleep(500);
                                                    ADAPTARE++;
                                                    populatie++;
                                                    numar_de_generatii++;
                                                    curent_x=curent_x+directie_x[seed_int_art];
                                                    curent_y=curent_y+directie_y[seed_int_art];
                                                }else{
                                                        if(harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]==3 && convertire_tip_virus!=3)
                                                            {
                                                                int sansa_de_adaptare_la_uscat=rand()%20+1;
                                                                int SUMA_DE_CRITERIU=0;
                                                                SUMA_DE_CRITERIU=ADAPTARE+INTELIGENTA;
                                                                if(sansa_de_adaptare_la_uscat==10 && SUMA_DE_CRITERIU>=90)
                                                                    {
                                                                        //VIRUS OK -> SE ADAPTEAZA LA AMBELE REGIUNI
                                                                        convertire_tip_virus=3;
                                                                        harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]=5;
                                                                        SetConsoleTextAttribute(h, 12);
                                                                        cout<<"SYSTEM >";
                                                                        SetConsoleTextAttribute(h, 7);
                                                                        SetConsoleTextAttribute(h, 10);
                                                                        cout<<"VIRUSUL S-A ADAPTAT PE APA!";
                                                                        SetConsoleTextAttribute(h, 7);
                                                                        cout<<" POPULATIE";
                                                                        SetConsoleTextAttribute(h, 142);
                                                                        cout<<" INCREASE+1";
                                                                        SetConsoleTextAttribute(h, 7);
                                                                        cout<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                        logout<<"SYSTEM > POPULATIE INCREASE+1"<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                        Sleep(500);
                                                                        populatie++;
                                                                        ADAPTARE++;
                                                                        numar_de_generatii++;
                                                                        curent_x=curent_x+directie_x[seed_int_art];
                                                                        curent_y=curent_y+directie_y[seed_int_art];
                                                                    }else{
                                                                            //VIRUSUL MOARE
                                                                            harta[curent_x+directie_x[seed_int_art]][curent_y+directie_y[seed_int_art]]=99;
                                                                            SetConsoleTextAttribute(h, 12);
                                                                            cout<<"SYSTEM >";
                                                                            SetConsoleTextAttribute(h, 7);
                                                                            SetConsoleTextAttribute(h, 10);
                                                                            cout<<"VIRUSUL NU S-A PUTUT ADAPTA PE APA!";
                                                                            SetConsoleTextAttribute(h, 7);
                                                                            cout<<" POPULATIE";
                                                                            SetConsoleTextAttribute(h, 142);
                                                                            cout<<" DECREASE -1";
                                                                            SetConsoleTextAttribute(h, 7);
                                                                            cout<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                            logout<<"SYSTEM > POPULATIE DECREASE -1"<<" X["<<curent_x+directie_x[seed_int_art]<<"]"<<"Y["<<curent_y+directie_y[seed_int_art]<<"]"<<"\n";
                                                                            Sleep(500);
                                                                            numar_de_generatii++;
                                                                            curent_x=curent_x+directie_x[seed_int_art];
                                                                            curent_y=curent_y+directie_y[seed_int_art];
                                                                        }
                                                                }
                                                    }

                                                                                                                        verificare_conditii_ALL();
                                            }

                         //==============
                         //CONDITII MEDIU
                         //==============
                         /*
                         ==============
                         CONDITII MEDIU
                         ==============

                                    *->EXISTA O SANSA DE 5% >>INVERSE|DACA VIRUSUL ESTE TIP TERESTRU SI INTRA PE O BUCATA DE APA SE VA PROCEDA PE O SANSA DINTRE 0 SI 100, LA CARE SE ADAUGA
                                      SI ADAPTABILITATEA SI INTELIGENTA, DACA REZULTATUL FINAL ESTE MAI MARE SAU EGAL CU 90% VIRUSUL VA PUTEA SUPRAVIETUI/ SE
                                      POATE MUTA PE ACEL BLOC, ALTFEL MOARE INSTANTANEU.

                                    *->EXISTA O SANSA DE 5% >>INVERSE|DACA VIRUSUL ESTE DE TIP CALD SI TEMPERATURA ESTE SUB 0 GRADE SE VA PROCEDA AIDOMA CONDITIEI DE MAI SUS, NUMAI CA PROCENTAJUL
                                      DE ACEASTA DATA VA INCLUDE SI PUTEREA, ASADAR, DACA INTELIGENTA+ADAPTABILITATE+PUTERE >= 150%, ATUNCI VIRUSUL VA PUTEA SUPRAVIETUI,
                                      ALTFEL VIRUSUL MOARE INSTANT.

                                    *-> EXISTA O SANSA DE 10% |DACA VIRUSUL ARE PUTEREA MAI MARE DECAT CELALALTE STATISTICI, SE VA INTRA IN MODUL CANIBAL, ASTA INSEAMNA CA DACA EXISTA UN VIRUS MORT
                                       LASAT, ACEL VIRUS VA PRIMI PE HARTA 10 UNITATI DE HRANA SI VA FI DISPONIBILA PENTRU RASPANDIRE // PUTERE++; INTELIGENTA--;

                                    *-> EXISTA O SANSA DE 10% |DACA VIRUSUL ARE ADAPTABILITATEA CEA MAI MARE, AIDOMA MODULUI CANIBAL, SE VA INTRA IN MODUL ECO, ALTFEL UN VIRUS MORT LASAT IN SPATE,
                                       ACEL VIRUS VA PRIMI PE HARTA 10 UNITATI DE HRANA SI VA FI DISPONIBILA PENTRU RASPANDIRE // ADAPTABILITATE++; INTELIGENTA--; PUTERE--;

                                    -> EXISTA O SANSA DE 10% |DACA VIRUSUL ARE INTELIGENTA CEA MAI MARE, AIDOMA MODULUI ECO, SE VA INTRA IN MODUL EVOLUTION, IAR UN VIRUS MORT VA FI LASAT IN SPATE,
                                       SI VA PRIMI ACEA BUCATA 10 UNITATI DE HRANA SI VA FI DISPONIBILA PENTRU RASPANDIRE //INTELIGENTA++; PUTERE--;

                         ==============
                         CONDITII MEDIU
                         ==============
                         */

                                }else{
                                    if(ADAPTARE>adaptare_alfa)
                                        {
                                            int sansa_de_recalculare=rand()%2+1;
                                            if(sansa_de_recalculare==1)
                                                {
                                                    inteligenta_artificiala_virus(curent_x,curent_y);
                                                }
                                        }
                                    if(ADAPTARE>adaptare_beta)
                                        inteligenta_artificiala_virus(curent_x,curent_y);

                                }
                    }else{
                        if(ADAPTARE>adaptare_alfa)
                            {
                                int sansa_de_recalculare=rand()%2+1;
                                if(sansa_de_recalculare==1)
                                    {
                                        inteligenta_artificiala_virus(curent_x,curent_y);
                                    }
                            }
                        if(ADAPTARE>adaptare_beta)
                            inteligenta_artificiala_virus(curent_x,curent_y);
                    }
        }else inteligenta_artificiala_virus(x_initial,y_initial);
    system("cls");
    AFISARE_TOTAL();
    verificare_conditii_ALL();
    Sleep(150);
    inteligenta_artificiala_virus(curent_x,curent_y);
}
int verificare_conditii_ALL()
{
    int fitil_GLOBAL=1;
    int j=1;
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    if(harta[i][j]==5)
                        {
                            verificare_statistici(i,j);
                            verificare_zone_mancare(i,j);
                            verificare_zone_fauna(i,j);
                        }
                    //MODUL CANIBAL
                    if(harta[i][j]==99 && PUTERE>INTELIGENTA && PUTERE>ADAPTARE)
                        {
                            modul_canibal(i,j);
                        }else{
                            if(harta[i][j]==99 && ADAPTARE>INTELIGENTA && ADAPTARE>PUTERE)
                                {
                                    modul_eco(i,j);
                                }else{
                                    if(harta[i][j]==99 && INTELIGENTA>ADAPTARE && INTELIGENTA>PUTERE)
                                        {
                                            modul_evolution(i,j);
                                        }
                                    }
                            }
                }
                if(i==bit && j==bit)
                    fitil_GLOBAL=2;
        }
        if(fitil_GLOBAL==2)
            {
                expansiune();
            }
    system("cls");
    AFISARE_TOTAL();

}
int expansiune()
{
    srand(time(NULL));
    int inds=rand()%bit+1;
    int indx=rand()%bit+1;
    if(harta[inds][indx]==5)
    {
        inteligenta_artificiala_virus(inds,indx);
    }else expansiune();
}
int modul_canibal(int i,int j)
{
    srand(time(NULL));
    int x=10;
    int sansa_de_adaptare_la_canibalism=rand()%x+1;
    if(sansa_de_adaptare_la_canibalism==1)
    {
        zone_mancare[i][j]=zone_mancare[i][j]+10;
        harta[i][j]=copie_harta[i][j];
        PUTERE++;
        INTELIGENTA--;
        SetConsoleTextAttribute(h, 12);
        cout<<"SYSTEM >";
        SetConsoleTextAttribute(h, 7);
        SetConsoleTextAttribute(h, 10);
        cout<<"VIRUSUL S-A ADAPTAT LA";
        SetConsoleTextAttribute(h, 7);
        SetConsoleTextAttribute(h, 142);
        cout<<"CANIBALISM!";
        SetConsoleTextAttribute(h, 7);
        cout<<" PUTERE";
        SetConsoleTextAttribute(h, 142);
        cout<<" INCREASE +1";
        SetConsoleTextAttribute(h, 7);
        cout<<" INTELIGENTA";
        SetConsoleTextAttribute(h, 142);
        cout<<" DECREASE -1";
        SetConsoleTextAttribute(h, 7);
        Sleep(500);
        cout<<"\n";
        if(x>1)
            x--;
        adaptare_alfa+=2;
        adaptare_beta+=2;
    }

}
int modul_eco(int i,int j)
{
    srand(time(NULL));
    int x=10;
    int sansa_de_adaptare_la_eco=rand()%x+1;
    if(sansa_de_adaptare_la_eco==1)
    {
        zone_mancare[i][j]=zone_mancare[i][j]+10;
        harta[i][j]=copie_harta[i][j];
        ADAPTARE++;
        PUTERE--;
        SetConsoleTextAttribute(h, 12);
        cout<<"SYSTEM >";
        SetConsoleTextAttribute(h, 7);
        SetConsoleTextAttribute(h, 10);
        cout<<"VIRUSUL S-A ADAPTAT LA";
        SetConsoleTextAttribute(h, 7);
        SetConsoleTextAttribute(h, 142);
        cout<<"MODUL ECO!";
        SetConsoleTextAttribute(h, 7);
        cout<<" ADAPTARE";
        SetConsoleTextAttribute(h, 142);
        cout<<" INCREASE +1";
        SetConsoleTextAttribute(h, 7);
        cout<<" PUTERE";
        SetConsoleTextAttribute(h, 142);
        cout<<" DECREASE -1";
        SetConsoleTextAttribute(h, 7);
        Sleep(500);
        cout<<"\n";
        if(x>1)
            x--;
        adaptare_alfa+=2;
        adaptare_beta+=2;
    }
}
int modul_evolution(int i,int j)
{
    srand(time(NULL));
    int x=10;
    int sansa_de_adaptare_la_evolution=rand()%x+1;
    if(sansa_de_adaptare_la_evolution==1)
    {
        zone_mancare[i][j]=zone_mancare[i][j]+10;
        harta[i][j]=copie_harta[i][j];
        PUTERE--;
        INTELIGENTA++;
        SetConsoleTextAttribute(h, 12);
        cout<<"SYSTEM >";
        SetConsoleTextAttribute(h, 7);
        SetConsoleTextAttribute(h, 10);
        cout<<"VIRUSUL S-A ADAPTAT LA";
        SetConsoleTextAttribute(h, 7);
        SetConsoleTextAttribute(h, 142);
        cout<<"MODUL EVOLUTION!";
        SetConsoleTextAttribute(h, 7);
        cout<<" INTELIGENTA";
        SetConsoleTextAttribute(h, 142);
        cout<<" INCREASE +1";
        SetConsoleTextAttribute(h, 7);
        cout<<" PUTERE";
        SetConsoleTextAttribute(h, 142);
        cout<<" DECREASE -1";
        SetConsoleTextAttribute(h, 7);
        Sleep(500);
        cout<<"\n";
        if(x>1)
            x--;
        adaptare_alfa+=2;
        adaptare_beta+=2;
    }

}
int verificare_zone_mancare(int x,int y)
{
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE VERIFICA ZONA DE MANCARE DE PE X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
    logout<<"SYSTEM > SE VERIFICA ZONA DE MANCARE DE PE X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
    if(zone_mancare[x][y]!=0 && harta[x][y]!=99)
        {
            zone_mancare[x][y]--;
            INTELIGENTA++;
            PUTERE++;
                SetConsoleTextAttribute(h, 12);
                cout<<"SYSTEM >";
                SetConsoleTextAttribute(h, 7);
            cout<<" ZONA DE MANCARE -1 // X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
            logout<<"SYSTEM > ZONA DE MANCARE -1 // X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
        }else {
            if(zone_mancare[x][y]==0)
                {
                    harta[x][y]=99;
                    populatie--;
                    SetConsoleTextAttribute(h, 12);
                    cout<<"SYSTEM >";
                    SetConsoleTextAttribute(h, 7);
                    cout<<" ZONA DE MANCARE GOALA!";
                    SetConsoleTextAttribute(h, 142);
                    cout<<"POPULATIE -1";
                    SetConsoleTextAttribute(h, 7);
                    cout<<" // X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
                    logout<<"SYSTEM > ZONA DE MANCARE GOALA! POPULATIE -1 // X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
                }else{
                    if(zone_mancare[x][y]==0)
                        {
                            //se incepe moartea virusului
                            if(INTELIGENTA>=50)
                                {
                                    if(zone_fauna[x][y]>=2)
                                        {
                                            zone_mancare[x][y]=zone_mancare[x][y]+1;
                                            INTELIGENTA++;
                                            PUTERE++;
                                            SetConsoleTextAttribute(h, 12);
                                            cout<<"SYSTEM >";
                                            SetConsoleTextAttribute(h, 7);
                                            cout<<" VIRUSUL PRODUCE DIN FAUNA MANCARE!";
                                            SetConsoleTextAttribute(h, 142);
                                            cout<<" INTELIGENTA>=50 //"<<"\n"<<"[INTELIGENTA]=["<<INTELIGENTA<<"]"<<"\n";
                                            SetConsoleTextAttribute(h, 7);
                                            logout<<"SYSTEM > VIRUSUL PRODUCE DIN FAUNA MANCARE! INTELIGENTA>=50 //"<<"\n"<<"[INTELIGENTA]=["<<INTELIGENTA<<"]"<<"\n";
                                            SetConsoleTextAttribute(h, 12);
                                            cout<<"SYSTEM >";
                                            SetConsoleTextAttribute(h, 7);
                                            cout<<" INTELIGENTA +1 // POPULATIE +1 // ZONA MANCARE +1 X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
                                            logout<<"SYSTEM > INTELIGENTA +1 // POPULATIE +1 // ZONA MANCARE +1 X["<<x<<"]"<<"Y["<<y<<"]"<<"\n";
                                        }else harta[x][y]=99;
                                }else harta[x][y]=99;
                        }
                }
        }
    Sleep(200);
}
int delimitare_de_tip_fauna[100][100]; //la 3 verificari elimina virusul
int verificare_zone_fauna(int x,int y)
{
    if(zone_fauna[x][y]!=0)
        {
            if(zone_fauna[x][y]>3 && harta[x][y]!=99)
                {
                    if(PUTERE<4)
                        {
                                //virusul moare
                                harta[x][y]=99;
                                populatie--;
                                SetConsoleTextAttribute(h, 12);
                                cout<<"SYSTEM >";
                                SetConsoleTextAttribute(h, 7);
                                cout<<" FAUNA PREA RIGIDA PENTRU PENETRARE //";
                                SetConsoleTextAttribute(h, 142);
                                cout<<" POPULATIE -1 ! "<<"\n";
                                SetConsoleTextAttribute(h, 7);
                                logout<<"SYSTEM > FAUNA PREA RIGIDA PENTRU PENETRARE // POPULATIE -1 ! "<<"\n";
                        }else{
                                if(zone_fauna[x][y]>0)
                                    {
                                        zone_fauna[x][y]--;
                                        INTELIGENTA++;
                                        PUTERE++;
                                        SetConsoleTextAttribute(h, 12);
                                        cout<<"SYSTEM >";
                                        SetConsoleTextAttribute(h, 7);
                                        cout<<" FAUNA PENETRABILA //";
                                        SetConsoleTextAttribute(h, 142);
                                        cout<<" PUTERE +1"<<"\n";
                                        SetConsoleTextAttribute(h, 7);
                                        logout<<"SYSTEM > FAUNA PENETRABILA // PUTERE +1"<<"\n";
                                        cout<<"[PUTERE]=["<<PUTERE<<"]"<<"\n";
                                        logout<<"[PUTERE]=["<<PUTERE<<"]"<<"\n";
                                    }else {
                                            SetConsoleTextAttribute(h, 12);
                                            cout<<"SYSTEM >";
                                            SetConsoleTextAttribute(h, 7);
                                            cout<<" FAUNA = 0 ! // FAUNA TIP DESERT ! "<<"\n";
                                            logout<<"SYSTEM > FAUNA = 0 ! // FAUNA TIP DESERT ! "<<"\n";
                                        }
                            }
                }
        }
    Sleep(500);
    system("cls");
    AFISARE_TOTAL();
}
int verificare_statistici(int x, int y)
{
        if(populatie>0)
    {

    }else{
        if(populatie<=0)
            {
                cout<<"\n";
                SetConsoleTextAttribute(h, 12);
                cout<<"SYSTEM > ";
                SetConsoleTextAttribute(h, 7);
                SetConsoleTextAttribute(h, 142);
                cout<<"POPULATIE = 0 ! "<<"\n\n";
                SetConsoleTextAttribute(h, 7);
                logout<<"SYSTEM > POPULATIE = 0 ! "<<"\n\n";
                SetConsoleTextAttribute(h, 12);
                cout<<"SYSTEM >";
                SetConsoleTextAttribute(h, 7);
                cout<<" END OF SIMULATION ! "<<"\n";
                logout<<"SYSTEM > END OF SIMULATION ! ";
                functie_finala();
            }

    }
    srand(time(NULL));
    //CLIMA CALDA
    if(tip_virus_clima==45)
        {
            if(zone_temperatura[x][y]>0)
                {
                    //VIRUS OK
                }else{
                        int sansa_de_adaptare_la_temperatura=rand()%20+1;
                        int SUMA_DE_CRITERIU=0;
                        SUMA_DE_CRITERIU=ADAPTARE+INTELIGENTA+PUTERE;
                        if(sansa_de_adaptare_la_temperatura==10 && SUMA_DE_CRITERIU>=150)
                            {
                                //VIRUSUL SE ADAPTEAZA SI ESTE OK
                                SetConsoleTextAttribute(h, 12);
                                cout<<"SYSTEM >";
                                SetConsoleTextAttribute(h, 7);
                                SetConsoleTextAttribute(h, 10);
                                cout<<"VIRUSUL S-A ADAPTAT LA";
                                SetConsoleTextAttribute(h, 7);
                                SetConsoleTextAttribute(h, 142);
                                cout<<"TEMPERATURA!";
                                SetConsoleTextAttribute(h, 7);
                                cout<<"\n";
                                if(test_mode!=3)
					Sleep(500);
                            }else
                                    {
                                        SetConsoleTextAttribute(h, 12);
                                        cout<<"SYSTEM >";
                                        SetConsoleTextAttribute(h, 7);
                                        SetConsoleTextAttribute(h, 10);
                                        cout<<"VIRUSUL NU S-A ADAPTAT LA";
                                        SetConsoleTextAttribute(h, 7);
                                        SetConsoleTextAttribute(h, 142);
                                        cout<<"TEMPERATURA!";
                                        SetConsoleTextAttribute(h, 7);
                                        cout<<" POPULATIE";
                                        SetConsoleTextAttribute(h, 142);
                                        cout<<" DECREASE -1";
                                        SetConsoleTextAttribute(h, 7);
                                        populatie--;
                                        cout<<"\n";
                                        if(test_mode!=3)
						Sleep(500);
                                        harta[x][y]=99;
                                        verificare_conditii_ALL();
                                    }
                }
        }
    //CLIMA RECE
    if(tip_virus_clima==46)
        {
            if(zone_temperatura[x][y]<0)
                {
                //VIRUS OK
                }else{
                        int sansa_de_adaptare_la_temperatura=rand()%20+1;
                        int SUMA_DE_CRITERIU=0;
                        SUMA_DE_CRITERIU=ADAPTARE+INTELIGENTA+PUTERE;
                        if(sansa_de_adaptare_la_temperatura==10 && SUMA_DE_CRITERIU>=150)
                            {
                                //VIRUSUL SE ADAPTEAZA SI ESTE OK
                                SetConsoleTextAttribute(h, 12);
                                cout<<"SYSTEM >";
                                SetConsoleTextAttribute(h, 7);
                                SetConsoleTextAttribute(h, 10);
                                cout<<"VIRUSUL S-A ADAPTAT LA";
                                SetConsoleTextAttribute(h, 7);
                                SetConsoleTextAttribute(h, 142);
                                cout<<"TEMPERATURA!";
                                SetConsoleTextAttribute(h, 7);
                                cout<<"\n";
                                if(test_mode!=3)
					Sleep(500);
                            }else
                                {
                                    SetConsoleTextAttribute(h, 12);
                                    cout<<"SYSTEM >";
                                    SetConsoleTextAttribute(h, 7);
                                    SetConsoleTextAttribute(h, 10);
                                    cout<<"VIRUSUL NU S-A ADAPTAT LA";
                                    SetConsoleTextAttribute(h, 7);
                                    SetConsoleTextAttribute(h, 142);
                                    cout<<"TEMPERATURA!";
                                    SetConsoleTextAttribute(h, 7);
                                    cout<<" POPULATIE";
                                    SetConsoleTextAttribute(h, 142);
                                    cout<<" DECREASE -1";
                                    SetConsoleTextAttribute(h, 7);
                                    populatie--;
                                    cout<<"\n";
                                    if(test_mode!=3)
					    Sleep(500);
                                    harta[x][y]=99;
                                    verificare_conditii_ALL();

                                }
                    }
        }
        system("cls");
        AFISARE_TOTAL();
}

//######################
//GENERARE ZONE DE MANCARE
//######################

int generare_mancare_zone_mancare(int k)
{
    system("cls");
    cout<<"_____________________________________"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE GENEREAZA ZONELE DE MANCARE ! "<<"\n";
    cout<<"_____________________________________"<<"\n\n";
    cout<<"_____________________________________"<<"\n\n";
    srand(time(NULL));
    int j=0;
    int zona=0;
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    if(k==1)
                        {
                            if(harta[i][j]==3)
                                {
                                    SetConsoleTextAttribute(h, 2);
                                }else SetConsoleTextAttribute(h, 9);
                            zona=rand()%10+0;
                            Sleep(50);
                            zone_mancare[i][j]=zona;
                            cout<<zone_mancare[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                        }
                    if(k==2)
                        {
                            if(harta[i][j]==3)
                                {
                                    SetConsoleTextAttribute(h, 2);
                                }else SetConsoleTextAttribute(h, 9);
                            zona=rand()%3+0;
                            Sleep(50);
                            zone_mancare[i][j]=zona;
                            cout<<zone_mancare[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                        }
                }
            cout<<"\n";
        }
    cout<<"_____________________________________"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" ZONE HRANA GENERATE";SetConsoleTextAttribute(h, 10);cout<<" 100%";SetConsoleTextAttribute(h, 7);cout<<"\n";
    if(test_mode!=3)
	    Sleep(3000);
}

//######################
//GENERARE FAUNA
//######################
int generare_fauna(int k)
{
    system("cls");
    cout<<"_____________________________________"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE GENEREAZA FAUNA ! "<<"\n";
    cout<<"_____________________________________"<<"\n\n";
    cout<<"_____________________________________"<<"\n\n";
    srand(time(NULL));
    int j=0;
    int zona=0;
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    if(k==1)
                        {
                            if(harta[i][j]==3)
                                {
                                    SetConsoleTextAttribute(h, 2);
                                }else SetConsoleTextAttribute(h, 9);
                            zona=rand()%10+0;
                            Sleep(50);
                            fauna[i][j]=zona;
                            cout<<fauna[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                        }
                    if(k==2)
                        {
                            if(harta[i][j]==3)
                                {
                                    SetConsoleTextAttribute(h, 2);
                                }else SetConsoleTextAttribute(h, 9);
                            zona=rand()%4+0;
                            Sleep(50);
                            fauna[i][j]=zona;
                            cout<<fauna[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                        }
                }
            cout<<"\n";
        }
    cout<<"_____________________________________"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" FAUNA GENERATA";SetConsoleTextAttribute(h, 10);
    cout<<" 100%";SetConsoleTextAttribute(h, 7);cout<<"\n";
    if(test_mode!=3)
	    Sleep(3000);
}

//######################
//GENERARE CLIMA
//######################
int generare_clima()
{
    system("cls");
    cout<<"_____________________________________"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" SE GENEREAZA CLIMA ! "<<"\n";
    cout<<"_____________________________________"<<"\n\n";
    Sleep(100);
    srand(time(NULL));
    int j=0;
    if(test_mode==1 || test_mode==3)
    {
        tip_zona=rand()%2+1;
    }
    int zona=0;
    if(tip_zona==1)
        {
            //zona calda
            cout<<"CLIMA CALDA"<<"\n";
        }
    if(tip_zona==2)
        {
            //zona artica
            cout<<"CLIMA RECE"<<"\n";
        }
    cout<<"_____________________________________"<<"\n\n";
    int semyorka=0;
    for(int i=1;i<=bit;i++)
        {
            for(j=1;j<=bit;j++)
                {
                    if(tip_zona==1)
                        {
                            //zona calda
                            zona=rand()%60+5;
                            Sleep(50);
                            zone_temperatura[i][j]=zona;
                            if(harta[i][j]==3)
                                {
                                    SetConsoleTextAttribute(h, 2);
                                }else SetConsoleTextAttribute(h, 9);
                            if(zone_temperatura[i][j]>9)
                                {
                                    cout<<zone_temperatura[i][j]<<" ";
                                }else cout<<" "<<zone_temperatura[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                        }
                    if(tip_zona==2)
                        {
                            //zona artica
                            zona=rand()%60+5;
                            Sleep(50);
                            zone_temperatura[i][j]=-zona;
                            if(harta[i][j]==3)
                                {
                                    SetConsoleTextAttribute(h, 2);
                                }else SetConsoleTextAttribute(h, 9);
                            if(zone_temperatura[i][j]<-1*9)
                                {
                                    cout<<zone_temperatura[i][j]<<" ";
                                }else cout<<" "<<zone_temperatura[i][j]<<" ";
                            SetConsoleTextAttribute(h, 7);
                        }
                }
            cout<<"\n";
        }
    cout<<"_____________________________________"<<"\n\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" CLIMA GENERATA ";SetConsoleTextAttribute(h, 10);cout<<" 100%\n";SetConsoleTextAttribute(h, 7);
   if(test_mode!=3)
	   Sleep(3000);
    global_clima=tip_zona;
}

//######################
//MAIN
//######################

int functie_finala()
{
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM > ";
    SetConsoleTextAttribute(h, 7);
    cout<<"NUMAR DE GENRATII= ";
    SetConsoleTextAttribute(h, 142);
    cout<<numar_de_generatii<<"\n";
    SetConsoleTextAttribute(h, 7);
    logout<<"NUMAR DE GENERATII= "<<numar_de_generatii<<"\n";
    SetConsoleTextAttribute(h, 12);
    cout<<"SYSTEM >";
    SetConsoleTextAttribute(h, 7);
    cout<<" GOOD BYE !"<<"\n";
    logout<<"GOOD BYE !"<<"\n";
    cout<<":) Prokaryotick Kingdom, LONG LIVE THE KING <8toro8>"<<"\n";
    logout<<":) Prokaryotick Kingdom, LONG LIVE THE KING <8toro8>"<<"\n";
    if(test_mode!=3)
    exit(0);
    number_of_simulation--;
    VEC_A[ANAX]=numar_de_generatii;
    ANAX++;
    FILTRU_ANALITIC(number_of_simulation);

}
int main_menu()
{
    system("cls");
    cout<<"_____________________________________"<<"\n\n";
    cout<<"VIRUS LAB SIMULATOR alpha_V.0.5.1"<<"\n";
    cout<<"created by Rilea Petru @CC"<<"\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    cout<<"1. SIMULARE"<<"\n";
    cout<<"2. LAB MODE"<<"\n";
    cout<<"3. ANALITIC MODE"<<"\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    SetConsoleTextAttribute(h, 10);
    cout<<"INPUT_!@>";
    SetConsoleTextAttribute(h, 7);
    cin>>test_mode;
    if(test_mode==1)
    {
            functie_meniu_principal();
    }else
    {
        if(test_mode==2)
        {
            functie_meniu_principal();
            lab_mode();
        }else {
		if(test_mode==3)
			functie_meniu_principal();
		analitic_mode();

	}
    }


}
int lab_mode()
{
    system("cls");
    cout<<"_____________________________________"<<"\n\n";
    cout<<"VIRUS LAB SIMULATOR alpha_V.0.5.1"<<"\n";
    cout<<"created by Rilea Petru @CC"<<"\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    cout<<"CLIMA CALDA (1)"<<"\n";
    cout<<"CLIMA RECE  (2)"<<"\n";
    cout<<"_____________________________________"<<"\n"<<"\n";
    SetConsoleTextAttribute(h, 10);
    cout<<"INPUT_!@>";
    SetConsoleTextAttribute(h, 7);
    cin>>tip_zona;
    if(tip_zona!=1 && tip_zona!=2)
        lab_mode();

}
int analitic_mode()
{
	system("cls");
    	cout<<"_____________________________________"<<"\n\n";
	cout<<"ANALITIC MODE"<<"\n";
        cout<<"_____________________________________"<<"\n\n";
	cout<<"NUMBER OF SIMULATION:";
	cin>>number_of_simulation;
	cout<<"\n";
	cout<<"DEPLOYMET OF VIRUS FOR EVERY SIMULATION"<<"\n";
	cout<<"[X]=";cin>>x_analitic;cout<<"\n";
	cout<<"[Y]=";cin>>y_analitic;cout<<"\n";
	cout<<"_____________________________________"<<"\n\n";

}

int FILTRU_ANALITIC(int PLATON)
{
	if(PLATON>0)
	{
		generare_harta();
		generare_zone_harta();
		verificare_TOTALA();
    		for(int i=1;i<=bit;i++)
   		 {
       			 for(int j=1;j<=bit;j++)
        			{
            				copie_harta[i][j]=harta[i][j];
        			}
   		 }
    	if(x_analitic<bit || x_analitic>=0 || y_analitic<bit || y_analitic>=0)
        {

        }else{
                SetConsoleTextAttribute(h, 12);
                cout<<"SYSTEM >";
                SetConsoleTextAttribute(h, 7);
                cout<<" IN AFARA GRANITELOR HARTII  ! "<<"\n";
                system("pause");
                plasare_virus();
            }
	    cout<<"\n";
   	    SetConsoleTextAttribute(h, 12);
   	    cout<<"SYSTEM >";
    	    SetConsoleTextAttribute(h, 7);
    	    cout<<" VIRUS DEPLOYED !"<<"\n";
    	    copie_orgine=harta[x_analitic][y_analitic];
    	    harta[x_analitic][y_analitic]=5;
    	    populatie++;
   	    numar_de_generatii++;
		inteligenta_artificiala_virus(x_analitic,y_analitic);

	}else{
		if(PLATON<=0)
		{
			cout<<"SIMULATIONS 100%"<<"\n";
			for(int i=1;i<=ANAX;i++)
			{
				cout<<"SIM_nr_["<<i<<"] -> "<<VEC_A[i]<<"\n";
			}
			exit(0);
		}
	}
}

int main()
{
    main_menu();
    if(test_mode==1 || test_mode==2)
    {
    generare_harta();
    generare_zone_harta();
    verificare_TOTALA();
    for(int i=1;i<=bit;i++)
    {
        for(int j=1;j<=bit;j++)
        {
            copie_harta[i][j]=harta[i][j];
        }
    }
    plasare_virus();
    }else {
    	    //ANALITIC MODE
	 	FILTRU_ANALITIC(number_of_simulation);
    }
    return 0;
    // :) Prokaryotick Kingdom, LONG LIVE THE KING <8toro8>
}
