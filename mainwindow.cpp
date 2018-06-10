#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transmittance.h"
#include "function_generator.h"
#include "bodedialog.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // simulationSpeed = 0.001;
//    C_Generator generator(0.0001, 10.0, PI);		// param: czestotliwosc, amplituda, faza poczatkowa(rad)
//    C_Transmittance transmittance(2, 1, 1, 0);  // param: a2,a1,a0, czas opoznienia (e^-t),

    generator = new C_Generator(0.0001, -10.0, PI);
    transmittance = new C_Transmittance(2,1,1,0);

    plotTimer = new QTimer(this);
    QObject::connect(plotTimer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    plotTimer->setInterval(20);



    cout << transmittance->getBodeMagnitude(0.774/(2*PI)) << endl;    // dzielienie w argumencie powoduje, �e podaje pulsacje a nie czestotliwosc
    cout << transmittance->getBodePhaseShift(0.7/(2*PI) ) << endl;

    //Sleep(2000);
    ui->customPlot->setFixedHeight(500);
    ui->customPlot->setFixedWidth(600);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    inputGraph = ui->customPlot->addGraph();
    inputGraph->setData(xData, yData);
    inputGraph->setPen(QPen(Qt::blue));
    inputGraph->rescaleAxes();
  //  ui->customPlot->yAxis->setRange(-1.45, 1.65);
    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);




    QCPAxisRect *upperGraph = new QCPAxisRect(ui->customPlot);
    upperGraph->setupFullAxesBox(true);
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->customPlot->plotLayout()->addElement(0, 0, upperGraph); // insert axis rect in first row
    ui->customPlot->plotLayout()->addElement(1, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    QCPAxisRect *lowerGraph = new QCPAxisRect(ui->customPlot, true); // false means to not setup default axes
    subLayout->addElement(0, 0, lowerGraph);

    QCPMarginGroup *group = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect(0)->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    ui->customPlot->axisRect(1)->setMarginGroup(QCP::msLeft|QCP::msRight, group);


     outputGraph = ui->customPlot->addGraph(lowerGraph->axis(QCPAxis::atBottom), lowerGraph->axis(QCPAxis::atLeft));


   // subRectRight->setMaximumSize(150, 150); // make bottom right axis rect size fixed 150x150
   // subRectRight->setMinimumSize(150, 150); // make bottom right axis rect size fixed 150x150
//    // add the bracket at the top:
//    QCPItemBracket *bracket = new QCPItemBracket(ui->customPlot);
//    bracket->left->setCoords(-8, 1.1);
//    bracket->right->setCoords(8, 1.1);
//    bracket->setLength(13);

//    // add the text label at the top:
//    QCPItemText *wavePacketText = new QCPItemText(ui->customPlot);
//    wavePacketText->position->setParentAnchor(bracket->center);
//    wavePacketText->position->setCoords(0, -10); // move 10 pixels to the top from bracket center anchor
//    wavePacketText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
//    wavePacketText->setText("Wavepacket");
//    wavePacketText->setFont(QFont(font().family(), 10));

//    // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
//    QCPItemTracer *phaseTracer = new QCPItemTracer(ui->customPlot);
//    //r = phaseTracer; // so we can access it later in the bracketDataSlot for animation
//    phaseTracer->setGraph(graph);
//    phaseTracer->setGraphKey((M_PI*1.5-phase)/k);
//    phaseTracer->setInterpolating(true);
//    phaseTracer->setStyle(QCPItemTracer::tsCircle);
//    phaseTracer->setPen(QPen(Qt::red));
//    phaseTracer->setBrush(Qt::red);
//    phaseTracer->setSize(7);

//    // add label for phase tracer:
//    QCPItemText *phaseTracerText = new QCPItemText(ui->customPlot);
//    phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
//    phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
//    phaseTracerText->position->setCoords(1.0, 0.95); // lower right corner of axis rect
//    phaseTracerText->setText("Points of fixed\nphase define\nphase velocity vp");
//    phaseTracerText->setTextAlignment(Qt::AlignLeft);
//    phaseTracerText->setFont(QFont(font().family(), 9));
//    phaseTracerText->setPadding(QMargins(8, 0, 0, 0));

//    // add arrow pointing at phase tracer, coming from label:
//    QCPItemCurve *phaseTracerArrow = new QCPItemCurve(ui->customPlot);
//    phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);
//    phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
//    phaseTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
//    phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
//    phaseTracerArrow->end->setCoords(10, 10);
//    phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
//    phaseTracerArrow->endDir->setCoords(30, 30);
//    phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
//    phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPosition().y()-phaseTracerText->top->pixelPosition().y())*0.85));

//    // add the group velocity tracer (green circle):
//    QCPItemTracer *groupTracer = new QCPItemTracer(ui->customPlot);
//    groupTracer->setGraph(graph);
//    groupTracer->setGraphKey(5.5);
//    groupTracer->setInterpolating(true);
//    groupTracer->setStyle(QCPItemTracer::tsCircle);
//    groupTracer->setPen(QPen(Qt::green));
//    groupTracer->setBrush(Qt::green);
//    groupTracer->setSize(7);

//    // add label for group tracer:
//    QCPItemText *groupTracerText = new QCPItemText(ui->customPlot);
//    groupTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
//    groupTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
//    groupTracerText->position->setCoords(1.0, 0.20); // lower right corner of axis rect
//    groupTracerText->setText("Fixed positions in\nwave packet define\ngroup velocity vg");
//    groupTracerText->setTextAlignment(Qt::AlignLeft);
//    groupTracerText->setFont(QFont(font().family(), 9));
//    groupTracerText->setPadding(QMargins(8, 0, 0, 0));

//    // add arrow pointing at group tracer, coming from label:
//    QCPItemCurve *groupTracerArrow = new QCPItemCurve(ui->customPlot);
//    groupTracerArrow->start->setParentAnchor(groupTracerText->left);
//    groupTracerArrow->startDir->setParentAnchor(groupTracerArrow->start);
//    groupTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
//    groupTracerArrow->end->setCoords(5.5, 0.4);
//    groupTracerArrow->endDir->setParentAnchor(groupTracerArrow->end);
//    groupTracerArrow->endDir->setCoords(0, -40);
//    groupTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
//    groupTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (groupTracerText->bottom->pixelPosition().y()-groupTracerText->top->pixelPosition().y())*0.85));

//    // add dispersion arrow:
//    QCPItemCurve *arrow = new QCPItemCurve(ui->customPlot);
//    arrow->start->setCoords(1, -1.1);
//    arrow->startDir->setCoords(-1, -1.3);
//    arrow->endDir->setCoords(-5, -0.3);
//    arrow->end->setCoords(-10, -0.2);
//    arrow->setHead(QCPLineEnding::esSpikeArrow);

//    // add the dispersion arrow label:
//    QCPItemText *dispersionText = new Q1CPItemText(ui->customPlot);
//    dispersionText->position->setCoords(-6, -0.9);
//    dispersionText->setRotation(40);
//    dispersionText->setText("Dispersion with\nvp < vg");
//    dispersionText->setFont(QFont(font().family(), 10));

    // setup a timer that repeatedly calls MainWindow::bracketDataSlot:
    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));
    //dataTimer.start(0); // Interval 0 means to refresh as fast as possible
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
    qDebug() << "Update...";

    static double timer = 0.0;
    if(counter == 0.0) timer= 0.0;
    transmittance->loadInputValue(generator->getFunctionValue(inputFunctionType,timer));
    transmittance->delayInputValue(timer);
    transmittance->makeStep();

    timer += transmittance->timeStep;
    yData.append(transmittance->getOutputValue());

//    cout << counter << "   ";
//    cout << timer<<"   ";
//    cout << "Input value: " << generator->getFunctionValue(inputFunctionType,timer) << "   ";
//    cout << "Output value: " << transmittance->getOutputValue() << endl;

    xData.append(timer);


    inputData.append(generator->getFunctionValue(inputFunctionType,timer));
    counter += 1 ;


     outputGraph->setData(xData, yData);
     outputGraph->rescaleAxes();
     inputGraph->setData(xData, inputData);
     inputGraph->setPen(QPen(Qt::red));
     inputGraph->rescaleAxes();
     ui->customPlot->replot();
   //  if(counter > 800) plotTimer->stop();
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
       //plotTimer->setInterval(60 - simSpeed*10);
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

    xData.clear();
    y1Data.clear();
    y2Data.clear();

    for (double index = 0; index < 100; index= index+0.001) {
        y1Data.append(transmittance->getBodeMagnitude((index)/2*PI));
        y2Data.append(qRadiansToDegrees(transmittance->getBodePhaseShift((index)/2*PI)));
        xData.append((index)/2*PI);


    }

    BodeDialog *bodeDialog = new BodeDialog(xData,y1Data,y2Data);
    //bodeDialog->setParent(this);

    bodeDialog->exec();

}

void MainWindow::on_updateSpeedButton_clicked()
{

       simSpeed= ui->simSpeedEdit->text().toDouble();
       if(simSpeed > 59) simSpeed = 59;
       plotTimer->setInterval(60 - simSpeed*10);
       ui->simSpeedLabel->setText(ui->simSpeedEdit->text().append(" x"));
}


