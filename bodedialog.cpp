#include "bodedialog.h"
#include "mainwindow.h"
#include "ui_bodedialog.h"
#include <cmath>

BodeDialog::BodeDialog(QVector<double> xData, QVector<double> y1Data, QVector<double> y2Data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BodeDialog)
{
    ui->setupUi(this);
    this->xData = xData;
    this->y1Data = y1Data;
    this->y2Data = y2Data;

    ui->customPlot->setFixedHeight(500);
    ui->customPlot->setFixedWidth(600);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    bode1Graph = ui->customPlot->addGraph();
    bode1Graph->setData(xData, y1Data);
    bode1Graph->setPen(QPen(Qt::blue));
    bode1Graph->rescaleAxes();

    QCPAxisRect *upperGraph = new QCPAxisRect(ui->customPlot);
    upperGraph->setupFullAxesBox(true);
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->customPlot->plotLayout()->addElement(0, 0, upperGraph);
    ui->customPlot->plotLayout()->addElement(1, 0, subLayout);
    QCPAxisRect *lowerGraph = new QCPAxisRect(ui->customPlot, true);
    subLayout->addElement(0, 0, lowerGraph);

    bode2Graph = ui->customPlot->addGraph(lowerGraph->axis(QCPAxis::atBottom), lowerGraph->axis(QCPAxis::atLeft));
    bode2Graph->setData(xData, y2Data);
    bode2Graph->setPen(QPen(Qt::blue));
    bode2Graph->rescaleAxes();

    bode1Graph->keyAxis()->setScaleType(QCPAxis::stLogarithmic);
    bode2Graph->keyAxis()->setScaleType(QCPAxis::stLogarithmic);

    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    bode1Graph->keyAxis()->setTicker(logTicker);
    bode2Graph->keyAxis()->setTicker(logTicker);
    bode1Graph->keyAxis()->setNumberFormat("eb");
    bode1Graph->keyAxis()->setNumberPrecision(0);
    bode2Graph->keyAxis()->setNumberFormat("eb");
    bode2Graph->keyAxis()->setNumberPrecision(0);
    bode1Graph->keyAxis()->setRangeLower(10e-4);
    bode2Graph->keyAxis()->setRangeLower(10e-4);
    bode1Graph->keyAxis()->grid()->setSubGridVisible(true);
    bode2Graph->keyAxis()->grid()->setSubGridVisible(true);

    QCPMarginGroup *group = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect(0)->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    ui->customPlot->axisRect(1)->setMarginGroup(QCP::msLeft|QCP::msRight, group);
//////////////////////////////////////////////////////////
    double maxValue = std::numeric_limits<double>::min();
    double fr,fpc,fgc;
    int index = 0, frIndex = 0, fpcIndex = 0,fgcIndex = 0;
    double absGainValue = 0.01;
    double absPhaseValue = 0.1;

    for(; index < y1Data.size();index++)
    {
        if(y1Data.at(index) < absGainValue && y1Data.at(index) > -absGainValue) fpcIndex = index;

        if(y1Data.at(index) > maxValue)
        {
            maxValue = y1Data.at(index);
            frIndex = index;
        }

    }

    ui->maxValueLabel->setText(QString::number(maxValue).append(" dB"));

        fr = xData.at(frIndex);
        ui->frLabel->setText(QString::number(fr).append(" Hz"));



        fpc = fabs(y2Data.at(fpcIndex));
         QString deg = QChar(0x00B0);
        ui->phaseMarginLabel->setText(QString::number(180 - fpc).append(" ").append(deg));


    for(index = 0; index < y2Data.size();index++)
    {
        if(y2Data.at(index) < (-180.0 + absPhaseValue) && y2Data.at(index) > (-180.0 - absPhaseValue))
        {
            fgcIndex = index;
        }

    }


         ui->GainMarginLabel->setText(QString::number(fabs(y1Data.at(fgcIndex))).append(" dB"));
    if(fgcIndex == y2Data.size())
         ui->GainMarginLabel->setText("Infinity");


}

BodeDialog::~BodeDialog()
{
    delete ui;
}

void BodeDialog::on_pushButton_clicked()
{
     bode2Graph->rescaleAxes();
     bode1Graph->rescaleAxes();
     bode1Graph->keyAxis()->setRangeLower(10e-4);
     bode2Graph->keyAxis()->setRangeLower(10e-4);

//     bode1Graph->keyAxis()->setRangeUpper(10);
//     bode2Graph->keyAxis()->setRangeUpper(10);

    ui->customPlot->replot();
}
