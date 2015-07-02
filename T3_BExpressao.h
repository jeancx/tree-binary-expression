#ifndef T3_BEXPRESSAO_H_INCLUDED
#define T3_BEXPRESSAO_H_INCLUDED

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

// Struct, Nós e Links
typedef struct No_T3
{
    char VxO; // Valor ou Operador
    No_T3 *Esq; // * Esquerda
    No_T3 *Dir; // * Direita
    No_T3 *Pai; // Pai do No
    int P; // Prioridade
} *Link, No;

//Salva posição para ordenação da arvore;
Link Bonsai, Raiz, aux;

// Variaveis para suporte;
int Mult=1, DebuCount=0;

bool vNumero(char C)
{
    if((C >= '0')&&(C <= '9'))
        return true;
    else
        return false;
}// Verifica se é numero

bool vOperador(char C)
{
    if((C == '+') || (C == '-') || (C == '*') || (C == '/'))
        return true;
    else
        return false;
}// Verifica se é Operador

int Prioridade(char C)
{
    if(C == ' ')
        return 0;
    else
    {
        if(C=='+' || C=='-')
            return 2*Mult;
        if(C=='/' || C=='*')
            return 4*Mult;
        else
            return 6*Mult;
    }
}//Verifica Prioridade de Cada Char

Link encontra(Link X,int P)
{
    if ((X->P > P) && (vOperador(X->VxO)))
    {
        return X;
    }
    else
    {
        if(X->Esq!=NULL)
            encontra(X->Esq,P);
        if(X->Dir!=NULL)
            encontra(X->Dir,P);

        if((X->Esq==NULL) && (X->Dir==NULL))
            return X;
    }
}

Link Novo_No(char C, int P)
{
    Link Novo = new No;

    DebuCount++;

    if (Bonsai == NULL)
    {
        Raiz = Novo;
        Bonsai = Novo;
    }

    Novo->VxO = C;
    Novo->Esq = NULL;
    Novo->Dir = NULL;
    Novo->Pai = NULL;
    Novo->P = P;
    return Novo;
}//Cria novo No com char e prioridade;

void Insere_T3(Link Temp)
{
    if(Temp == Raiz)
        return;

    //Se é um numero Temp
    if (vNumero(Temp->VxO))
    {
        Bonsai->Dir = Temp;
        return;
    }

    //Se Pai é um numero Bonsai
    if (vNumero(Bonsai->VxO))
    {
        Temp->Esq = Bonsai;
        Bonsai->Pai = Temp;
        Raiz = Temp;
        Bonsai = Temp;
    }

    // Se é um operador
    if (vOperador(Bonsai->VxO))
    {

        // Se prioridade do operador for menor
        // insere antes da raiz
        if (Temp->P < Bonsai->P)
        {
            Temp->Esq = Bonsai;
            Bonsai->Pai = Temp;
            Bonsai = Temp;
        }
        // Se prioridade do operador for menor ou igual
        // insere entre raiz e resto
        if (Temp->P <= Bonsai->P)
        {
            Temp->Esq = Bonsai->Dir;
            Bonsai->Dir = Temp;
            Temp->Pai = Bonsai;
            Bonsai = Temp;
        }

        // Se prioridade do operador for maior
        // procura local correto
        if (Temp->P > Bonsai->P)
        {
            Link Nav;
            // Insere no nivel correto
            Nav = encontra(Raiz,Temp->P);

            if(Nav->Dir == NULL)
            {
                Nav->Dir=Temp;
            }
            if(Nav->Esq == NULL)
            {
                Nav->Esq=Temp;
            }
        }
    }
}//Insere na arovre na posição correta

void Insere_T3_2 (Link Temp)
{
    // Se Raiz == Temp então temp ja foi o primeiro inserido
    if (Temp == Raiz){
            cout<<"_A   ";
        return;
    }

    //Se Temp->VxO é um numero
    if (vNumero(Temp->VxO))
    {
        Bonsai->Dir = Temp;
        cout<<"_B   ";
        return;
    }

    //Se Bonsai->VxO é um numero
    if (vNumero(Bonsai->VxO))
    {
        Temp->Esq = Bonsai;
        Bonsai->Pai = Temp;
        Raiz = Temp;
        Bonsai = Temp;
        cout<<"_C   ";
    }
    else// Se é um operador
    {
        if (Temp->P > Bonsai->P)//Se Temp->P maior que Bonsai->P insere.
        {
            Temp->Esq = Bonsai->Dir;
            Bonsai->Dir = Temp;
            Temp->Pai = Bonsai;
            Bonsai = Temp;
            cout<<"_D   ";
        }
        else
        {
            // Acha o Nivel correto de acordo com a prioridade
            while(1)
            {
                if (Bonsai->Pai == NULL)//Se pai do Bonsai é nulo quebra while
                {
                    cout<<"_E   ";
                    Bonsai->Pai = Temp;
                    Temp->Esq = Bonsai;
                    Bonsai = Temp;
                    Raiz = Temp;
                    break;
                }
                else
                {
                    if (Temp->P < Bonsai->P)//Se Temp->P menor que Bonsai->P
                    {
                        if (Temp->P > Bonsai->Pai->P){//Se Temp->P maior que Bonsai->Pai->P
                            cout<<"_F   ";
                            break;//Quebra while
                        }
                        else
                        {
                            cout<<"_G   ";
                            Bonsai = Bonsai->Pai;//Volta Bonsai para Pai
                        }
                    }
                    else////Se Temp->P maior que Bonsai->P
                    {
                        cout<<"_H   ";
                        break;//Quebra while
                    }
                    cout<<"_I   ";
                    Temp->Esq = Bonsai;//Temp->Esq se torna Bonsai
                    if (Bonsai == Raiz)//Se Bonsai igual Raiz, Raiz se torna Temp;
                    {
                        cout<<"_J   ";
                        Raiz = Temp;
                    }
                    else//Caso Bonsai não seja Raiz
                    {
                        if (Bonsai->Pai->Esq == Bonsai)//Se Bonsai->Pai>Esq igual Bonsai
                        {
                            cout<<"_K   ";
                            Bonsai->Pai->Esq = Temp;//Temp se torna Bonsai->Pai->Esq
                        }
                        else//Se Bonsai->Pai>Esq diferente de Bonsai
                        {
                            cout<<"_L   ";
                            Bonsai->Pai->Dir = Temp;//Temp se torna Bonsai->Pai->Dir
                        }
                        cout<<"_M   ";
                        Temp->Pai = Bonsai->Pai;
                        Bonsai->Pai = Temp;//Temp se torna pai de Bonsai
                    }
                }
                cout<<"_N   ";
                Bonsai = Temp;
            }
        }
    }
} // TExp_Insere

void Monta_T3(Link&Arvore, string Exp)
{
    Arvore = NULL;
    Link Temp;

    for(int i=0; i<Exp.size(); i++)  //Separa Prioridades
    {
        if(Exp[i] == '(' or Exp[i] == ')')
        {
            if(Exp[i] == '(')
            {
                Mult *= 10;
            }
            if(Exp[i] == ')')
            {
                Mult /= 10;
            }
        }
        else if(Exp[i] != ' ')
        {
            Temp = Novo_No(Exp[i],Prioridade(Exp[i]));
            cout<<Temp->VxO;
            Insere_T3_2(Temp);
        }
    }
    Arvore = Raiz;
}//Constroi Arovore

int Calcula(Link L)
{
    int A, B;

    if(L!=NULL)
    {
        if (vNumero(L->VxO))
            return L->VxO-'0';

        if((L->Esq == NULL) && (L->Dir == NULL))
            return 0;
        else
        {
            A=Calcula(L->Esq);
            B=Calcula(L->Dir);

            switch (L->VxO)
            {
            case '+':
                return (A+B);
            case '-':
                return (A-B);
            case '*':
                return (A*B);
            case '/':
                return (A/B);
            }
        }
    }
    return 0;
}//Calcula;

void imprime(Link h)
{
    if (h == NULL) return;
    imprime(h->Esq);
    cout<< h->VxO;
    imprime(h->Dir);
}


int Calcula_T3(Link Arvore)
{
    int r;
    cout<<"\n\nArvore Apos Inserida: ";
    imprime(Arvore);
    cout<<endl;
    r=Calcula(Arvore);
    return r;
}



#endif // T3_BEXPRESSAO_H_INCLUDED
