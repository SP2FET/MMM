#include "bodedialog.h"
#include "mainwindow.h"
#include "ui_bodedialog.h"

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
    ui->customPlot->plotLayout()->addElement(0, 0, upperGraph); // insert axis rect in first row
    ui->customPlot->plotLayout()->addElement(1, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    QCPAxisRect *lowerGraph = new QCPAxisRect(ui->customPlot, true); // false means to not setup default axes
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
    bode1Graph->keyAxis()->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    bode1Graph->keyAxis()->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
    bode2Graph->keyAxis()->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    bode2Graph->keyAxis()->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
    bode1Graph->keyAxis()->setRangeLower(10e-4);
    bode2Graph->keyAxis()->setRangeLower(10e-4);
    bode1Graph->keyAxis()->grid()->setSubGridVisible(true);
    bode2Graph->keyAxis()->grid()->setSubGridVisible(true);

    QCPMarginGroup *group = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect(0)->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    ui->customPlot->axisRect(1)->setMarginGroup(QCP::msLeft|QCP::msRight, group);

    double maxValue = std::numeric_limits<double>::min();
    double wr;
    int index = 0, frIndex = 0;
    for(; index < y1Data.size();index++)
    {
        if(y1Data.at(index) > maxValue)
        {
            maxValue = y1Data.at(index);
            frIndex = index;
        }

    }
    ui->maxValueLabel->setText(QString::number(maxValue).append(" dB"));
    wr = xData.at(frIndex);
    ui->frLabel->setText(QString::number(wr).append(" Hz"));

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


    ui->customPlot->replot();
}
