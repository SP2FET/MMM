
#include "stdafx.h"
#include "function_generator.h"
#include <QTextStream>
#include <QFile>
#include <QDataStream>
using namespace std;

#define PI 3.14159


C_Generator::C_Generator(double frequency, double amplitude, double phase)
{
	    setInitialFunctionPhase(phase);
		setFunctionFrequency(frequency);
		setFunctionAmplitude(amplitude);
}



void  C_Generator::setInitialFunctionPhase(double phase) { initialFunctionPhase = phase; }



void  C_Generator::setFunctionFrequency(double frequency) { functionFrequency = frequency;  }



void  C_Generator::setFunctionAmplitude(double amplitude){ functionAmplitude = amplitude; }

double C_Generator::getFunctionValue(enum fType functionType, double time)
{
    switch (functionType) {
    case sine:
        return getFunctionSineValue(time);
        break;
    case triangle:
        return getFunctionTriangleValue(time);
        break;
    case square:
        return getFunctionSquareValue(time);
        break;
    default:
        break;
    }
}

double C_Generator::parseInputPI(QString input)
{
    QRegExp PIrx("PI|pi[/]([0-9]+)");
    QRegExp filter("[A-Z]|[a-z]");
    QString outD1,outD2;


    if(input.contains(PIrx))
    {
       PIrx.indexIn(input);

        input.toUpper();
        input.replace("PI","3.14159");
        input.remove(filter);
        QStringList list1 = input.split('/');
        outD1 =  list1[0];
        if(list1.size() > 1)
        {
             outD2 =  list1[1];
             return outD1.toDouble()/outD2.toDouble();
        }
        else
            return outD1.toDouble();


    }
    return 0;

}


double C_Generator::getFunctionSquareValue(double time)
{
	double functionWholeAngle = time * 2* PI * functionFrequency + initialFunctionPhase;  // k¹t ca³kowity np 1339493 stopni
	double functionPeriodicAngle = fmod(functionWholeAngle, 2 * PI);                  // kat mieszczacy sie pd 0 do 2rad
	
	if (functionPeriodicAngle < PI)  return functionAmplitude;
	else return ((-1)*functionAmplitude);
}



double C_Generator::getFunctionTriangleValue(double time)
{
	double functionWholeAngle = time * 2 * PI * functionFrequency + initialFunctionPhase;  // k¹t ca³kowity np 1339493 stopni
	double functionPeriodicAngle = fmod(functionWholeAngle, 2 * PI);                  // kat mieszczacy sie pd 0 do 2rad


	if      (functionPeriodicAngle < (PI/2))											 return (functionPeriodicAngle*functionAmplitude / (PI / 2)); // fmod zwraca reszte z dzielenia - sprawdzam w jakim mijescu okresu jest funkcja
	else if (functionPeriodicAngle > (PI / 2) && functionPeriodicAngle < (3 * PI / 2))	 return (2*functionAmplitude - functionPeriodicAngle*functionAmplitude / (PI / 2));
	else if (functionPeriodicAngle > (3*PI/2) && functionPeriodicAngle < (2*PI))		 return ((-1)*4*functionAmplitude + functionPeriodicAngle*functionAmplitude / (PI / 2));
	else cout << "Triangle function error!" << endl;

}



double C_Generator::getFunctionSineValue(double time)
{
	return (sin(2 * PI * time * functionFrequency + initialFunctionPhase) * functionAmplitude);
}


double C_Generator::getFunctionFrequency()
{

	return functionFrequency;
}
