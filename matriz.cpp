/*

Resolve conjunto de equações (matriz)

Para entender, entre com os seguintes dados:

Exemplo 1:
2 (quantidade de variáveis)
1, 1, 2, 1, 3, 1  (primeira linha, equivale a  x + 2y = 3
4, 1, 5, 1, 9, 1   (segunda linha, equivale a 4x + 5y = 9
Os resultados serão x=1 e y=1

Exemplo 2:
3 (quantidade de variáveis)
1, 1, 2, 1, 3, 1, 14, 1  (primeira linha, equivale a  x + 2y + 3z = 14
4, 1, 5, 1, 9, 1, 41, 1   (segunda linha, equivale a 4x + 5y + 9z = 41
4, 1, 1, 1, 2, 1, 12, 1  (terceira linha, equivale a 4x +  y + 2z = 12
Os resultados serão x=1, y=2 e z=3

Exemplo 3:
3 (quantidade de variáveis)
1, 1, 2, 1, 3, 1, 14, 1  (primeira linha, equivale a    x + 2y + 3z = 14
4, 1, 5, 1, 9, 1, 41, 1   (segunda linha, equivale a   4x + 5y + 9z = 41
1, 4,-1, 1, 2, 1, 17, 4  (terceira linha, equivale a 1/4x -  y + 2z = 17/4 (4 1/4)
Os resultados serão x=1, y=2 e z=3

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <string.h>

#define MAXEXTENSO 100

using namespace std;

class TFracao {
	long Divisor, Dividendo;
	string Extenso;
public:
	TFracao( void);
	TFracao( long num);
	TFracao( long mul, long div);
	void copie( TFracao Fracao);
	void multiplique( long mul);
	void divida( long div);
	void some( long num);
	void diminua( long num);
	void copie( long num);
	void multiplique( TFracao Fracao);
	void divida( TFracao Fracao);
	void some( TFracao Fracao);
	void diminua( TFracao Fracao);
	void normalize( void);
	long double valor( void);
	long divisor( void);
	long dividendo( void);
	string extenso( void);
};


class TMatriz {
	TFracao *Matriz, *Resultado;
    long Tamanho; bool Prolixo;
public:
	TMatriz( long tam, bool pro);
	TMatriz( long tam);
	TMatriz( bool pro);
	TMatriz( void);
	~TMatriz( void);
	TFracao *matriz( long lin, long col);
	TFracao *resultado( long col);
	long tamanho( void);
	bool resolva( void);
	bool trocaiterativa( long lin);
	void calcula( long lin1, long lin2);	
};

// * Implementação das Classes

// Classe TFracao

TFracao::TFracao( void) {
	Dividendo = 1;
	Divisor = 1;
}

TFracao::TFracao( long num) {
	Dividendo = num;
	Divisor = 1;
}

TFracao::TFracao( long mul, long div) {
	Dividendo = mul;
	Divisor = div;
	normalize();
}

void TFracao::copie( TFracao Fracao) {
	Dividendo = Fracao.Dividendo;
	Divisor = Fracao.Divisor;
	normalize();
}

void TFracao::multiplique( long mul) {
	Dividendo *= mul;
	normalize();
}

void TFracao::divida( long div) {
	Divisor *= div;
	normalize();
}

void TFracao::some( long num) {
	normalize();
	Dividendo += num * Divisor;
	normalize();
}

void TFracao::diminua( long num) {
	normalize();
	Dividendo -= num * Divisor;
	normalize();
}

void TFracao::copie( long num) {
	Dividendo = num;
	Divisor = 1;
}

void TFracao::multiplique( TFracao Fracao) {
	Dividendo *= Fracao.Dividendo;
	Divisor *= Fracao.Divisor;
	normalize();
}

void TFracao::divida( TFracao Fracao) {
	Dividendo *= Fracao.Divisor;
	Divisor *= Fracao.Dividendo;
	normalize();
}

void TFracao::some( TFracao Fracao) {
	Fracao.normalize();
	normalize();
	Dividendo = Dividendo * Fracao.Divisor + Fracao.Dividendo * Divisor;
	Divisor *= Fracao.Divisor;
	normalize();
}

void TFracao::diminua( TFracao Fracao) {
	Fracao.normalize();
	normalize();
	Dividendo = Dividendo * Fracao.Divisor - Fracao.Dividendo * Divisor;
	Divisor *= Fracao.Divisor;
	normalize();
}

void TFracao::normalize( void) {
	long menor; char sinal;

	if( Divisor < 0) { Divisor *= -1; Dividendo *= -1; }
	if( Dividendo < 0) { Dividendo *= -1; sinal = -1; } else sinal = 1;
	menor = ( Divisor < Dividendo) ? Divisor : Dividendo;

	for( int cont = 2; cont <= menor; cont++)	{
		if( ( ( Divisor % cont) == 0) && ( ( Dividendo % cont) == 0) )		{
			Divisor /= cont;
			Dividendo /= cont;
			menor /= cont;
			cont--;
		}
	}

	Dividendo *= sinal;
}

long double TFracao::valor( void) {	return( ((long double) Dividendo) / ((long double) Divisor) ); }

long TFracao::divisor( void) { return( Divisor); }

long TFracao::dividendo( void) { return( Dividendo); }

string TFracao::extenso( void) {
	char chartemp[ MAXEXTENSO];
	if( Dividendo)
	{
		if( Divisor == 1)
			sprintf( chartemp, "%d", Dividendo);
		else
			if( Divisor > Dividendo)
				sprintf( chartemp, "%d/%d", Dividendo, Divisor);
			else
				sprintf( chartemp, "%d %d/%d", Dividendo / Divisor, Dividendo % Divisor, Divisor);
		Extenso = chartemp;
	} else Extenso = "0";
	return Extenso;
}


// Classe TMatriz

TMatriz::TMatriz( long tam, bool pro) {
	Prolixo = pro;
	Tamanho = tam;
	Matriz = new TFracao[ tam * tam + tam];
	Resultado = new TFracao[ tam + 1];
}

TMatriz::TMatriz( long tam){ TMatriz( tam, false); }

TMatriz::TMatriz( bool pro){ TMatriz( 2, pro); }

TMatriz::TMatriz( void){ TMatriz( 2, false); }

TMatriz::~TMatriz( void)
{
	delete Matriz;
	delete Resultado;
}

TFracao *TMatriz::matriz( long lin, long col) {	return( &Matriz[ (lin-1) + (col-1) * Tamanho] ); }

TFracao *TMatriz::resultado( long col) { return( &Resultado[ col-1] ); }

long TMatriz::tamanho( void) { return( Tamanho); }

bool TMatriz::resolva( void) {
	long divisor, dividendo;
	TFracao acumulador, temporario;

	for( long itera = 1; itera < Tamanho; itera++) {		// zerar abaixo da diagonal principal
		if( (*matriz( itera, itera)).dividendo() == 0)
			if( ! trocaiterativa( itera)) return false;

		for( long linha = itera + 1; linha <= Tamanho; linha++)
			if( (*matriz( linha, itera)).dividendo() != 0)
				calcula( linha, itera);
	}

	for( long linha = 1; linha <= Tamanho; linha++) {		// tornar a diagonal principal {1,...,1}
		temporario.copie( (*matriz( linha, linha)) );
		for( long coluna = linha; coluna <= (Tamanho+1); coluna++)
			(*matriz( linha, coluna)).divida( temporario);
	}

	(*resultado( Tamanho+1)).copie( -1);						// encontrar os resultados
	for( long linha = Tamanho; linha > 0; linha--) {
		acumulador.copie( 0);
		for( long coluna = linha + 1; coluna <= Tamanho + 1; coluna++) 		{
			temporario.copie( (*resultado( coluna)));
			temporario.multiplique( (*matriz( linha, coluna)));
			acumulador.diminua( temporario);
		}
		(*resultado( linha)).copie( acumulador);
	}
	return true;
}

bool TMatriz::trocaiterativa( long lin) {
	TFracao temp;

	for( long cont = lin+1; cont <= Tamanho; cont++)
		if( (*matriz( cont, lin)).dividendo() != 0) {
			if( Prolixo) cout << "Trocada iterativamente linha " << lin << " com linha " << cont << "...\n";
			for( long coluna = lin; coluna <= (Tamanho+1); coluna++) {
				temp.copie( (*matriz( lin, coluna)));
				(*matriz( lin, coluna)).copie( (*matriz( cont, coluna)));
				(*matriz( cont, coluna)).copie( temp);
			}
			return true;
		}
	return false;
}

void TMatriz::calcula( long lin1, long lin2) {
	TFracao mul1;

	if( Prolixo) cout << "Calculada linha " << lin1 << " - linha " << lin2 << "...\n";

	mul1.copie( (*matriz( lin2, lin2)));
	mul1.divida( (*matriz( lin1, lin2)));

	for( long coluna = lin2; coluna <= (Tamanho+1); coluna++) {
		(*matriz( lin1, coluna)).multiplique( mul1);
		(*matriz( lin1, coluna)).diminua( (*matriz( lin2, coluna)));
	}
}

// Corpo do Programa

int main( void)
{
	TMatriz *matriz;
	TFracao temporario;
	long temp1, temp2, tam;
	long lin, col;

	setlocale( LC_ALL, "");		// equal caracters in prompt

	cout <<  "\n\nDigite o número de linhas (variáveis): ";
	cin >> tam;
	if( tam < 2) {
		cout << "\nVocê precisa digitar um número maior ou igual a 2!\n\n";
		return 1;
	}

	matriz = new TMatriz( tam, true);

	cout << "\n\n\n";
	for( lin = 1; lin <= tam; lin++)	{
		cout << "\nLINHA " << lin << ":\n";
		for( col = 1; col <= (tam+1); col++) {
			cout << "\nDividendo da Coluna " << col << ": ";
			cin >> temp1;
			cout << "Divisor da Coluna " << col << ": ";
			cin >> temp2;
			(*(*matriz).matriz( lin, col)).multiplique( temp1);
			(*(*matriz).matriz( lin, col)).divida( temp2);
		}
	}

	cout << "\n\n\n";

	if( ! ( (*matriz).resolva() )) {
		cout << "\n\n\nNão foi possível encontrar um valor não nulo para a diagonal principal!\n\n";
		return 2;
	}


	cout << "\nMATRIZ RESULTADO:\n\n";
	for( lin = 1; lin <= tam; lin++)
	{
		for( col = 1; col <= (tam+1); col++)
			cout << (*(*matriz).matriz( lin, col)).extenso() << "\t";
		cout << "\n";
	}

	cout << "\n\n\n";
	cout << "\nRESULTADOS:\n\n";
	for( lin = 1; lin <= tam; lin++)
		cout <<  (*(*matriz).resultado( lin)).extenso() << "\t";

	cout << "\n";

	return 0;
}