#include <math.h>
#include <iostream>
#include <locale.h>
#include <conio.h>


using namespace std;

void AllocMatrix(int N, long double **&A, long double *&X, long double *&Ei, long double *&Ai, long double *&Bi, long double *&D)
{
	X = new long double[N];
	Ei = new long double[N];
	Ai = new long double[N];
	Bi = new long double[N];
	D = new long double[N];
	A = new long double *[N];
	for (int i = 0; i < N; i++)
		A[i] = new long double[N + 1];
}
void FreeMatrix(int N, long double **A, long double *&X, long double *&Ei, long double *&Ai, long double *&Bi, long double *&D)
{
	delete[] X;
	delete[] Ei;
	delete[] Ai;
	delete[] Bi;
	delete[] D;
	for (int i = 0; i < N; i++)
		delete[] A[i];
	delete[] A;
}

int main()
{
	setlocale(LC_ALL, "rus");

	int N;
	long double *X=0, *Ei=0, *Ai=0, *Bi=0, *D=0, **A=0;
	long double sum=0;

	cout<< "Введите число строк"<<endl<<"->";
	cin >> N;

	AllocMatrix(N, A, X, Ei, Ai, Bi, D);

	cout << "Введите систему:\n";
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N + 1; j++)
	{
		cin >> A[i][j];
	}
	system("cls");

	for (int i = 0; i < N; i++)
	{
		D[i] = A[i][N];
		Ai[i] = 0;
		Bi[i] = 0;
		X[i] = 0;
	}
	////////////////////
	cout << "--------------------------------"<< endl;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++)
			cout << A[i][j]<< " ";
		cout<< endl;
	}
	cout<< "--------------------------------"<< endl;
	for (int i = 0; i < N; i++)
		cout << D[i] << "\t" << endl;
	cout << "--------------------------------"<< endl;
	////////////////////////
	//Прямой ход
	Ei[0] = A[0][0];
	Ai[0] = -(A[0][1] / Ei[0]);
	Bi[0] = D[0] / Ei[0];

	for (int i = 1; i <= N - 1; i++)
	{
		Ei[i] = A[i][i - 1] * Ai[i - 1] + A[i][i];
		Ai[i] = -(A[i][i + 1] / Ei[i]);
		Bi[i] = (D[i] - Bi[i - 1] * A[i][i - 1]) / Ei[i];
	}

	Ei[N - 1] = A[N - 1][N - 1] + A[N - 1][N - 2] * Ai[N - 2];
	Bi[N - 1] = (D[N - 1] - A[N - 1][N - 2] * Bi[N - 2]) / Ei[N - 1];

	cout<< "------------------------------------------------------"<< endl;
	for (int i = 0; i < N; i++)
		cout<< "Ei["<< i<< "]"<< " = "<< Ei[i]<< "\t"<< "Ai["<< i<< "]"<< " = "<< Ai[i] << "\t" << "Bi[" << i << "]" << " = " << Bi[i] << endl;
	cout << "------------------------------------------------------" << endl;

	//Обратный ход
	X[N - 1] = Bi[N - 1];
	for (int i = N - 2; i >= 0; i--)
		X[i] = (Ai[i] * X[i + 1] + Bi[i]);

	for (int j = N - 1; j >= 0; j--)
		cout << "\t" << "x" << "["<< j << "]" << " = " << X[j] << "\n";

	for (int i = 0; i < N; i++){
		for ( int j = 0; j < N; j++)
			sum += A[i][j] * X[j];

		if (abs(sum - A[i][N])<1e-10)
			printf("\n %f = %f ", sum, A[i][N]);
		else  {
			printf("Ошибка %f != %f", sum, A[i][N]);
			system("pause");
			return (0);
		}
		sum = 0;
	}


	FreeMatrix(N, A, X, Ei, Ai, Bi, D);

	_getch();
	return 0;
}