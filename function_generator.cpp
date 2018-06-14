
#include "stdafx.h"
#include "function_generator.h"
#include <QTextStream>
#include <QFile>
#include <QDataStream>
using namespace std;


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
        return 0.0;
        break;
    }
}

double C_Generator::parseInputPI(QString input)
{
    QRegExp PIrx("-?PI|pi[//][0-9]+");
    QRegExp filter("[A-Z]|[a-z]");
    QString outD1,outD2, outStr;


    if(input.toUpper().contains(PIrx))
    {
       PIrx.indexIn(input);

        outStr = input.toUpper();
        outStr.replace("PI","3.14159");
        outStr.remove(filter);
        QStringList list1 = outStr.split('/');
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
    double functionWholeAngle = time * 2* PI * functionFrequency + initialFunctionPhase;
    double functionPeriodicAngle = fmod(functionWholeAngle, 2 * PI);
	
	if (functionPeriodicAngle < PI)  return functionAmplitude;
	else return ((-1)*functionAmplitude);
}



double C_Generator::getFunctionTriangleValue(double time)
{
    double functionWholeAngle = time * 2 * PI * functionFrequency + initialFunctionPhase;
    double functionPeriodicAngle = fmod(functionWholeAngle, 2 * PI);


    if      (functionPeriodicAngle < (PI/2))											 return (functionPeriodicAngle*functionAmplitude / (PI / 2));
	else if (functionPeriodicAngle > (PI / 2) && functionPeriodicAngle < (3 * PI / 2))	 return (2*functionAmplitude - functionPeriodicAngle*functionAmplitude / (PI / 2));
	else if (functionPeriodicAngle > (3*PI/2) && functionPeriodicAngle < (2*PI))		 return ((-1)*4*functionAmplitude + functionPeriodicAngle*functionAmplitude / (PI / 2));
    else qDebug( "Triangle function error!" );
    return 0.0;

}



double C_Generator::getFunctionSineValue(double time)
{
	return (sin(2 * PI * time * functionFrequency + initialFunctionPhase) * functionAmplitude);
}


double C_Generator::getFunctionFrequency()
{

	return functionFrequency;
}
