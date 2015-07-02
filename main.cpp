#include "T3_BExpressao.h"

using namespace std;

int main()
{
    Link Arvore = NULL;
    string Exp;
    cout << "Digite a Expresao que sera calculada: \nObs: somente aceito de 0 a 9, () ou + - / *, e sem espacos \n" << "> \n";
    cin>>Exp;
    //cout<<"Expressão: "<<"( 6 + 6 ) + 8 / ( 9 - 7 )"<<endl<<endl;

    cout<<"Debug=";
    Monta_T3(Arvore,Exp);
    cout<<"Resultado: "<<endl<<Calcula_T3(Arvore);

    return 0;
}
