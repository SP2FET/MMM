#pragma once
#include <QString>
enum fType {square, triangle, sine};

class C_Generator
{

private:

	double functionFrequency;         
	double initialFunctionPhase;      // w radianach
	double functionAmplitude;
    double getFunctionSquareValue(double time);
    double getFunctionTriangleValue(double time);
    double getFunctionSineValue(double time);
public:

	C_Generator(double frequency, double amplitude ,double phase);

	void   setFunctionFrequency(double frequency);
	void   setInitialFunctionPhase(double phase);
	void   setFunctionAmplitude(double amplitude);
    double getFunctionValue(enum fType functionType, double time);
	double getFunctionFrequency();
    double parseInputPI(QString input);

};
