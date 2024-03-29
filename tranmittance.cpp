
#include "stdafx.h"
#include "transmittance.h"



void WriteInMatrixFactors(tmat<double> &Matrix, double a2, double a1, double a0)
{
	Matrix(3, 1) = (-1)*a0;
	Matrix(3, 2) = (-1)*a1;
	Matrix(3, 3) = (-1)*a2;
}



C_Transmittance::C_Transmittance(double a2, double a1, double a0, double delayTime)
{

	A.resize(A_MATRIX_ROWS_NUMBER, A_MATRIX_COLUMNS_NUMBER);       // zadawanie rozmiarow tablicom
	B.resize(B_MATRIX_ROWS_NUMBER, B_MATRIX_COLUMNS_NUMBER);
	C.resize(C_MATRIX_ROWS_NUMBER, C_MATRIX_COLUMNS_NUMBER);
	D.resize(D_MATRIX_ROWS_NUMBER, D_MATRIX_COLUMNS_NUMBER);
	X.resize(X_MATRIX_ROWS_NUMBER, X_MATRIX_COLUMNS_NUMBER);
	Xd.resize(XD_MATRIX_ROWS_NUMBER, XD_MATRIX_COLUMNS_NUMBER);


	A = tfill(A_MATRIX_ROWS_NUMBER, A_MATRIX_COLUMNS_NUMBER, 0.0);    //czysczenie tablic
	B = tfill(B_MATRIX_ROWS_NUMBER, B_MATRIX_COLUMNS_NUMBER, 0.0);
	C = tfill(C_MATRIX_ROWS_NUMBER, C_MATRIX_COLUMNS_NUMBER, 0.0);
	D = tfill(D_MATRIX_ROWS_NUMBER, D_MATRIX_COLUMNS_NUMBER, 0.0);
	X = tfill(X_MATRIX_ROWS_NUMBER, X_MATRIX_COLUMNS_NUMBER, 0.0);
	Xd = tfill(XD_MATRIX_ROWS_NUMBER, XD_MATRIX_COLUMNS_NUMBER, 0.0);

	A(1, 2) = 1.0;														// ustawianie wartosci stalych elementow tablicy
	A(2, 3) = 1.0;
	loadDenominatorFactors(a2, a1, a0);         
	B(B_MATRIX_ROWS_NUMBER, B_MATRIX_COLUMNS_NUMBER) = 1.0;
	C(1, 1) = 1.0;
	
	loadDelayTime(delayTime);


}



void C_Transmittance::loadDenominatorFactors(double a2, double a1, double a0)
{  
	 a2Factor = a2;
     a1Factor = a1;
	 a0Factor = a0;

	WriteInMatrixFactors(A,a2,a1,a0);
}



void C_Transmittance::loadDelayTime(double time)	{ delayTime = time; }


void C_Transmittance::loadInputValue(double value)  
{
	delayedSamples.push(value);
}

void C_Transmittance::resetSimulation()
{
    A = tfill(A_MATRIX_ROWS_NUMBER, A_MATRIX_COLUMNS_NUMBER, 0.0);
    B = tfill(B_MATRIX_ROWS_NUMBER, B_MATRIX_COLUMNS_NUMBER, 0.0);
    C = tfill(C_MATRIX_ROWS_NUMBER, C_MATRIX_COLUMNS_NUMBER, 0.0);
    D = tfill(D_MATRIX_ROWS_NUMBER, D_MATRIX_COLUMNS_NUMBER, 0.0);
    X = tfill(X_MATRIX_ROWS_NUMBER, X_MATRIX_COLUMNS_NUMBER, 0.0);
    Xd = tfill(XD_MATRIX_ROWS_NUMBER, XD_MATRIX_COLUMNS_NUMBER, 0.0);
    A(1, 2) = 1.0;
    A(2, 3) = 1.0;
    loadDenominatorFactors(a2Factor, a1Factor, a0Factor);
    B(B_MATRIX_ROWS_NUMBER, B_MATRIX_COLUMNS_NUMBER) = 1.0;
    C(1, 1) = 1.0;

    loadDelayTime(delayTime);

}

void C_Transmittance::delayInputValue(double time)
{
	if (time >= delayTime)
	{
		u = delayedSamples.front();
		delayedSamples.pop();
	}
	else u = 0.0;
}
	


bool  C_Transmittance::isSystemStable()
{

	tmat<double> D1;
	tmat<double> D2;

	D1.resize(1, 1);
	D1(1, 1) = a2Factor;	

	D2.resize(A_MATRIX_ROWS_NUMBER-1, A_MATRIX_COLUMNS_NUMBER-1);
	D2 = tfill(A_MATRIX_ROWS_NUMBER-1, A_MATRIX_COLUMNS_NUMBER-1, 0.0);
	D2(1, 1) = a2Factor;
	D2(1, 2) = 1.0;
	D2(2, 1) = a0Factor;
	D2(2, 2) = a1Factor;													//macierz Hurwitza


    if (det(D2) > 0 && det(D1) > 0 )
        return true;
    else
        return false;
}



double C_Transmittance::getBodeMagnitude(double frequency)
{
    double w = 2 * PI*frequency;
    double buffer = sqrt(pow((a0Factor - a2Factor*pow(w, 2.0)), 2.0) + pow(((-1)*pow(w, 3) + a1Factor*w), 2.0)) /
                        (pow((a0Factor - a2Factor*pow(w, 2.0)), 2.0) + pow(((-1)*pow(w, 3) + a1Factor*w), 2.0));

	return 20*log10(buffer);
}



double C_Transmittance::getBodePhaseShift(double frequency)
{
    double w = 2 * PI*frequency;
    double buffer = atan2(-(( (-1)*pow(w, 3) + (w*a1Factor)) ) , (a0Factor - (a2Factor * pow(w, 2))) );
    return buffer;
}



void C_Transmittance::makeStep()
{ 
		Xd = mul(A, X) + mul(B, u);
        X = X + mul(Xd, timeStep);

		y = X(1, 1);
}


double C_Transmittance::getOutputValue() { return y; }
