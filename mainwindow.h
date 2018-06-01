#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "function_generator.h"
#include "transmittance.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QCPGraph *outputGraph, *inputGraph, *bode1Graph, *bode2Graph;
    ~MainWindow();

private slots:
    void timerEvent();


    void on_startStopButton_clicked();

    void on_rescaleButton_clicked();

    void on_UpdateButton_clicked();

    void on_updateInputButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *plotTimer;
    C_Generator *generator;
    C_Transmittance *transmittance;
    enum fType inputFunctionType;
    QVector<double> xData, yData, inputData;
    int	   counter = 0;


protected:

};

#endif // MAINWINDOW_H
