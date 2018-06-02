#ifndef BODEDIALOG_H
#define BODEDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class BodeDialog;
}

class BodeDialog : public QDialog
{
    Q_OBJECT

public:
     BodeDialog(QWidget *parent = 0);
     BodeDialog(QVector<double> xData, QVector<double> y1Data,QVector<double> y2Data, QWidget *parent = 0);
    ~BodeDialog();
      QCPGraph *bode1Graph, *bode2Graph;

private slots:
      void on_pushButton_clicked();

private:
    Ui::BodeDialog *ui;
    QVector<double> xData,y1Data,y2Data;
};

#endif // BODEDIALOG_H
