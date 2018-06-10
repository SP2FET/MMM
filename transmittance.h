#pragma once

#include "stdafx.h"

#define A_MATRIX_ROWS_NUMBER        3
#define A_MATRIX_COLUMNS_NUMBER		3

#define B_MATRIX_ROWS_NUMBER		3
#define B_MATRIX_COLUMNS_NUMBER		1

#define C_MATRIX_ROWS_NUMBER		1
#define C_MATRIX_COLUMNS_NUMBER		3

#define D_MATRIX_ROWS_NUMBER		1
#define D_MATRIX_COLUMNS_NUMBER		3
 /*
#define U_MATRIX_ROWS_NUMBER		1
#define U_MATRIX_COLUMNS_NUMBER		1

#define Y_MATRIX_ROWS_NUMBER		1
#define Y_MATRIX_COLUMNS_NUMBER		1

*/
#define X_MATRIX_ROWS_NUMBER		3
#define X_MATRIX_COLUMNS_NUMBER		1

#define XD_MATRIX_ROWS_NUMBER		3
#define XD_MATRIX_COLUMNS_NUMBER	1

using namespace std;

class C_Transmittance

{
private:

	//double stepDurationTime;

	double a2Factor;           // wpolczynniki mianownika transmitancji
	double a1Factor;
	double a0Factor;

	tmat<double> A;            //macierze z modelu stanowego
	tmat<double> B;
	tmat<double> C;
	tmat<double> D;

	tmat<double> X;
	tmat<double> Xd;

	double u;				    // zmienne wej-wyj
    queue<double> delayedSamples;
	double y;

	double delayTime;

public:

	C_Transmittance(double a2, double a1, double a0, double delayTime);

	//void   setStepDurationTime(double time);
	void   loadDenominatorFactors(double a2, double a1, double a0);
	void   loadDelayTime(double time);
	void   loadInputValue(double value);
	void   delayInputValue(double time);
	double getOutputValue();
    void   resetSimulation();
    void   makeStep();
    bool   isSystemStable();

	double getBodeMagnitude(double frequency);       // zwraca wartosci w dB, jako argument podaje czestotliwosc, nie pulsacje
	double getBodePhaseShift(double frequency);      // zwraca wartosci tylko od -pi/2 do pi/2, podaje czestotliwosc
    double timeStep = 0.05;

};
