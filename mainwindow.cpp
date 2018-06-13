#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transmittance.h"
#include "function_generator.h"
#include "bodedialog.h"
#include <QTextStream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    generator = new C_Generator(0.0001, -10.0, PI);
    transmittance = new C_Transmittance(2,1,1,0);

    plotTimer = new QTimer(this);
    QObject::connect(plotTimer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    plotTimer->setInterval(20);



    cout << transmittance->getBodeMagnitude(0.774/(2*PI)) << endl;
    cout << transmittance->getBodePhaseShift(0.7/(2*PI) ) << endl;

    ui->customPlot->setFixedHeight(500);
    ui->customPlot->setFixedWidth(600);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    inputGraph = ui->customPlot->addGraph();
    inputGraph->setData(xData, yData);
    inputGraph->setPen(QPen(Qt::blue));
    inputGraph->rescaleAxes();

    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);




    QCPAxisRect *upperGraph = new QCPAxisRect(ui->customPlot);
    upperGraph->setupFullAxesBox(true);
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->customPlot->plotLayout()->addElement(0, 0, upperGraph);
    ui->customPlot->plotLayout()->addElement(1, 0, subLayout);
    QCPAxisRect *lowerGraph = new QCPAxisRect(ui->customPlot, true);
    subLayout->addElement(0, 0, lowerGraph);

    QCPMarginGroup *group = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect(0)->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    ui->customPlot->axisRect(1)->setMarginGroup(QCP::msLeft|QCP::msRight, group);


     outputGraph = ui->customPlot->addGraph(lowerGraph->axis(QCPAxis::atBottom), lowerGraph->axis(QCPAxis::atLeft));

}

MainWindow::~MainWindow()
{

    delete generator;
    delete transmittance;
    xData.clear();
    yData.clear();
    delete ui;
}


void MainWindow::timerEvent()
{

    static double timer = 0.0;
    if(counter == 0.0) timer= 0.0;
    transmittance->loadInputValue(generator->getFunctionValue(inputFunctionType,timer));
    transmittance->delayInputValue(timer);
    transmittance->makeStep();

    timer += transmittance->timeStep;
    yData.append(transmittance->getOutputValue());

    xData.append(timer);

    inputData.append(generator->getFunctionValue(inputFunctionType,timer));
    counter += 1 ;

     outputGraph->setData(xData, yData);
     outputGraph->rescaleAxes();
     inputGraph->setData(xData, inputData);
     inputGraph->setPen(QPen(Qt::red));
     inputGraph->rescaleAxes();
     ui->customPlot->replot();

}


void MainWindow::on_startStopButton_clicked()
{
    if (plotTimer->isActive())
     {
       plotTimer->stop();
       ui->startStopButton->setText("Start");
     }
     else
     {
       plotTimer->start(60 - simSpeed*10);
       ui->startStopButton->setText("Stop");
     }
}

void MainWindow::on_rescaleButton_clicked()
{
    outputGraph->rescaleAxes();
    ui->customPlot->replot();
}

void MainWindow::on_UpdateButton_clicked()
{
    double a2,a1,a0,t;
    bool convOK;
    try
    {
        a2 = ui->a2Edit->text().toDouble(&convOK);
        if(!convOK) throw 1;
        a1 = ui->a1Edit->text().toDouble(&convOK);
        if(!convOK) throw 1;
        a0 = ui->a0Edit->text().toDouble(&convOK);
        if(!convOK) throw 1;
        t = ui->TEdit->text().toDouble(&convOK);
        if(!convOK) throw 1;
     }
    catch(...)
    {
        qDebug("ERROR! Failed to convert to double");
        return;
    }
    transmittance->loadDenominatorFactors(a2,a1,a0);
    transmittance->loadDelayTime(t);

    ui->a0Label->setText(ui->a0Edit->text());
    ui->a1Label->setText(ui->a1Edit->text());
    ui->a2Label->setText(ui->a2Edit->text());
    ui->TLabel->setText(ui->TEdit->text());


    if (transmittance->isSystemStable())
    {
        ui->stableLabel->setText("YES");
        ui->stableLabel->setStyleSheet("QLabel { color : green; }");
    }
    else
    {
        ui->stableLabel->setText("NO!");
        ui->stableLabel->setStyleSheet("QLabel { color : red; }");
    }

}

void MainWindow::on_updateInputButton_clicked()
{
    double freq,amp,phase;
    bool convOK;
    try
    {
        freq = ui->freqEdit->text().toDouble(&convOK);
        if(!convOK) throw 1;
        amp = ui->ampEdit->text().toDouble(&convOK);
        if(!convOK) throw 1;
        if(generator->parseInputPI(ui->phaseEdit->text()) != 0)
            phase = generator->parseInputPI(ui->phaseEdit->text());
        else
            phase = ui->phaseEdit->text().toDouble(&convOK);
        if(!convOK) throw 1;

     }
    catch(...)
    {
        qDebug("ERROR! Failed to convert to double");
        return;
    }

    generator->setFunctionAmplitude(amp);
    generator->setFunctionFrequency(freq);
    generator->setInitialFunctionPhase(phase);

    if(ui->sineRadio->isChecked())
    {
        inputFunctionType = sine;
        ui->inputLabel->setText("Sine");
    }
    else if(ui->squareRadio->isChecked())
    {
        inputFunctionType = square;
        ui->inputLabel->setText("Square");

    }
    else if(ui->triangleRadio->isChecked())
    {
        inputFunctionType = triangle;
        ui->inputLabel->setText("Triangle");

    }

    ui->ampLabel->setText(ui->ampEdit->text());
    ui->freqLabel->setText(ui->freqEdit->text());

    ui->phaseLabel->setText(cleanStringFromGarbage(ui->phaseEdit->text()));



}

QString MainWindow::cleanStringFromGarbage(QString str)
{
    QRegExp filter("[A-Z]|[a-z]");
    QString outStr;
    QString pi = QChar(0x03C0);
    outStr = str.toUpper();
    outStr.replace("PI","3.14159");
    outStr.remove(filter);
    outStr.replace("3.14159",pi);
    return outStr;
}
void MainWindow::on_resetButton_clicked()
{
    xData.clear();
    yData.clear();
    inputData.clear();
    transmittance->resetSimulation();
    outputGraph->setData(xData,yData);
    inputGraph->setData(xData,inputData);
    ui->customPlot->replot();
    plotTimer->setInterval(60 - simSpeed*10);
    counter = 0;
}

void MainWindow::on_bodeButton_clicked()
{
    QVector<double> xData, y1Data, y2Data;
    double phaseValue;
    bool phaseInvert;

    xData.clear();
    y1Data.clear();
    y2Data.clear();

    for (double index = 0; index < 100; index= index+0.001) {
        y1Data.append(transmittance->getBodeMagnitude(index/(2*PI)));
        phaseValue = qRadiansToDegrees(transmittance->getBodePhaseShift(index/(2*PI)));

        if(phaseValue > 179.9) phaseInvert = true;

        if(phaseInvert)
            y2Data.append(phaseValue-360);
        else
            y2Data.append(phaseValue);

        xData.append(index);


    }

    BodeDialog *bodeDialog = new BodeDialog(xData,y1Data,y2Data);


#ifdef DEBUG

    QFile dataFile("abcxyz.txt");
    double xStep = 0;

    dataFile.open(QIODevice::ReadWrite);

        qDebug("otwarty");
        QTextStream out(&dataFile);

        for(int index = 0; index < xData.size();index++)
        {
            out << xData.at(index) << " " << y1Data.at(index) << " " << y2Data.at(index)<<endl;
        }
        dataFile.close();
#endif

    bodeDialog->exec();

}

void MainWindow::on_updateSpeedButton_clicked()
{
       float samplesPerPeriod;
       simSpeed= ui->simSpeedEdit->text().toDouble();
       if(simSpeed > 59) simSpeed = 59;
       plotTimer->setInterval(60 - simSpeed*10);
       ui->simSpeedLabel->setText(ui->simSpeedEdit->text().append(" x"));

       if(ui->fixedButton->isChecked())
       {
           samplesPerPeriod = ui->intEdit->text().toDouble();
           transmittance->timeStep = samplesPerPeriod;
       }

       else if(ui->variableButton_2->isChecked())
       {
           samplesPerPeriod = ui->constIntEdit->text().toDouble();
           transmittance->timeStep = samplesPerPeriod/generator->getFunctionFrequency();
       }
       else transmittance->timeStep = 0.05;



}


