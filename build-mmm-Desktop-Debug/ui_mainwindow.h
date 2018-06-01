/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QFrame *frame;
    QGroupBox *groupBox;
    QLineEdit *a2Edit;
    QLineEdit *a1Edit;
    QLineEdit *a0Edit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *TEdit;
    QLabel *label_4;
    QPushButton *UpdateButton;
    QGroupBox *groupBox_2;
    QLineEdit *freqEdit;
    QLineEdit *ampEdit;
    QLineEdit *phaseEdit;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *updateInputButton;
    QRadioButton *squareRadio;
    QRadioButton *triangleRadio;
    QRadioButton *sineRadio;
    QGroupBox *controlBox;
    QPushButton *resetButton;
    QPushButton *startStopButton;
    QPushButton *rescaleButton;
    QGroupBox *statusBox;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *a2Label;
    QLabel *a1Label;
    QLabel *a0Label;
    QLabel *phaseLabel;
    QLabel *freqLabel;
    QLabel *ampLabel;
    QLabel *label_27;
    QLabel *stableLabel;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *TLabel;
    QLabel *inputLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1222, 576);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(50, 30, 491, 291));
        frame = new QFrame(customPlot);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-1, -1, 491, 291));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(590, 20, 281, 151));
        a2Edit = new QLineEdit(groupBox);
        a2Edit->setObjectName(QStringLiteral("a2Edit"));
        a2Edit->setGeometry(QRect(30, 60, 41, 32));
        a1Edit = new QLineEdit(groupBox);
        a1Edit->setObjectName(QStringLiteral("a1Edit"));
        a1Edit->setGeometry(QRect(90, 60, 41, 32));
        a0Edit = new QLineEdit(groupBox);
        a0Edit->setObjectName(QStringLiteral("a0Edit"));
        a0Edit->setGeometry(QRect(150, 60, 41, 32));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(42, 30, 21, 18));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(102, 30, 21, 18));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(162, 30, 21, 18));
        TEdit = new QLineEdit(groupBox);
        TEdit->setObjectName(QStringLiteral("TEdit"));
        TEdit->setGeometry(QRect(210, 60, 41, 32));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(225, 30, 16, 18));
        UpdateButton = new QPushButton(groupBox);
        UpdateButton->setObjectName(QStringLiteral("UpdateButton"));
        UpdateButton->setGeometry(QRect(100, 104, 88, 34));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(890, 20, 321, 151));
        freqEdit = new QLineEdit(groupBox_2);
        freqEdit->setObjectName(QStringLiteral("freqEdit"));
        freqEdit->setGeometry(QRect(30, 60, 41, 32));
        ampEdit = new QLineEdit(groupBox_2);
        ampEdit->setObjectName(QStringLiteral("ampEdit"));
        ampEdit->setGeometry(QRect(90, 60, 41, 32));
        phaseEdit = new QLineEdit(groupBox_2);
        phaseEdit->setObjectName(QStringLiteral("phaseEdit"));
        phaseEdit->setGeometry(QRect(150, 60, 41, 32));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 30, 31, 18));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(80, 30, 71, 18));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(150, 30, 41, 18));
        updateInputButton = new QPushButton(groupBox_2);
        updateInputButton->setObjectName(QStringLiteral("updateInputButton"));
        updateInputButton->setGeometry(QRect(100, 104, 88, 34));
        squareRadio = new QRadioButton(groupBox_2);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(squareRadio);
        squareRadio->setObjectName(QStringLiteral("squareRadio"));
        squareRadio->setGeometry(QRect(230, 40, 81, 22));
        squareRadio->setChecked(true);
        triangleRadio = new QRadioButton(groupBox_2);
        buttonGroup->addButton(triangleRadio);
        triangleRadio->setObjectName(QStringLiteral("triangleRadio"));
        triangleRadio->setGeometry(QRect(230, 70, 81, 22));
        sineRadio = new QRadioButton(groupBox_2);
        buttonGroup->addButton(sineRadio);
        sineRadio->setObjectName(QStringLiteral("sineRadio"));
        sineRadio->setGeometry(QRect(230, 100, 81, 22));
        controlBox = new QGroupBox(centralWidget);
        controlBox->setObjectName(QStringLiteral("controlBox"));
        controlBox->setGeometry(QRect(590, 190, 281, 171));
        resetButton = new QPushButton(controlBox);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(10, 70, 88, 34));
        startStopButton = new QPushButton(controlBox);
        startStopButton->setObjectName(QStringLiteral("startStopButton"));
        startStopButton->setGeometry(QRect(10, 30, 88, 34));
        rescaleButton = new QPushButton(controlBox);
        rescaleButton->setObjectName(QStringLiteral("rescaleButton"));
        rescaleButton->setGeometry(QRect(180, 30, 88, 34));
        statusBox = new QGroupBox(centralWidget);
        statusBox->setObjectName(QStringLiteral("statusBox"));
        statusBox->setGeometry(QRect(890, 190, 321, 171));
        label_15 = new QLabel(statusBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(20, 40, 21, 18));
        label_16 = new QLabel(statusBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 60, 21, 18));
        label_17 = new QLabel(statusBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(20, 80, 21, 18));
        label_18 = new QLabel(statusBox);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(180, 80, 31, 18));
        label_19 = new QLabel(statusBox);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(180, 120, 51, 18));
        label_20 = new QLabel(statusBox);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(180, 100, 71, 18));
        a2Label = new QLabel(statusBox);
        a2Label->setObjectName(QStringLiteral("a2Label"));
        a2Label->setGeometry(QRect(90, 40, 58, 18));
        a1Label = new QLabel(statusBox);
        a1Label->setObjectName(QStringLiteral("a1Label"));
        a1Label->setGeometry(QRect(90, 60, 58, 18));
        a0Label = new QLabel(statusBox);
        a0Label->setObjectName(QStringLiteral("a0Label"));
        a0Label->setGeometry(QRect(90, 80, 58, 18));
        phaseLabel = new QLabel(statusBox);
        phaseLabel->setObjectName(QStringLiteral("phaseLabel"));
        phaseLabel->setGeometry(QRect(250, 120, 58, 18));
        freqLabel = new QLabel(statusBox);
        freqLabel->setObjectName(QStringLiteral("freqLabel"));
        freqLabel->setGeometry(QRect(250, 80, 58, 18));
        ampLabel = new QLabel(statusBox);
        ampLabel->setObjectName(QStringLiteral("ampLabel"));
        ampLabel->setGeometry(QRect(250, 100, 58, 18));
        label_27 = new QLabel(statusBox);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(180, 40, 51, 18));
        stableLabel = new QLabel(statusBox);
        stableLabel->setObjectName(QStringLiteral("stableLabel"));
        stableLabel->setGeometry(QRect(250, 40, 41, 18));
        stableLabel->setTextFormat(Qt::PlainText);
        label_29 = new QLabel(statusBox);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(180, 60, 51, 18));
        label_30 = new QLabel(statusBox);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(20, 100, 31, 18));
        TLabel = new QLabel(statusBox);
        TLabel->setObjectName(QStringLiteral("TLabel"));
        TLabel->setGeometry(QRect(90, 100, 58, 18));
        inputLabel = new QLabel(statusBox);
        inputLabel->setObjectName(QStringLiteral("inputLabel"));
        inputLabel->setGeometry(QRect(250, 60, 61, 18));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1222, 30));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Transmittance parameters", nullptr));
        a2Edit->setText(QApplication::translate("MainWindow", "2", nullptr));
        a1Edit->setText(QApplication::translate("MainWindow", "1", nullptr));
        a0Edit->setText(QApplication::translate("MainWindow", "1", nullptr));
        label->setText(QApplication::translate("MainWindow", "a2", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "a1", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "a0", nullptr));
        TEdit->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "T", nullptr));
        UpdateButton->setText(QApplication::translate("MainWindow", "Update", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Input parameters", nullptr));
        freqEdit->setText(QApplication::translate("MainWindow", "0.001", nullptr));
        ampEdit->setText(QApplication::translate("MainWindow", "-10", nullptr));
        phaseEdit->setText(QApplication::translate("MainWindow", "PI", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "freq", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "amplitude", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "phase", nullptr));
        updateInputButton->setText(QApplication::translate("MainWindow", "Update", nullptr));
        squareRadio->setText(QApplication::translate("MainWindow", "S&quare", nullptr));
        triangleRadio->setText(QApplication::translate("MainWindow", "Trian&gle", nullptr));
        sineRadio->setText(QApplication::translate("MainWindow", "Sine", nullptr));
        controlBox->setTitle(QApplication::translate("MainWindow", "Control", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        startStopButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        rescaleButton->setText(QApplication::translate("MainWindow", "Rescale Axes", nullptr));
        statusBox->setTitle(QApplication::translate("MainWindow", "Status", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "a2:", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "a1:", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "a0:", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "freq:", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "phase:", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "amplitude:", nullptr));
        a2Label->setText(QString());
        a1Label->setText(QString());
        a0Label->setText(QString());
        phaseLabel->setText(QString());
        freqLabel->setText(QString());
        ampLabel->setText(QString());
        label_27->setText(QApplication::translate("MainWindow", "Stable:", nullptr));
        stableLabel->setText(QString());
        label_29->setText(QApplication::translate("MainWindow", "Input:", nullptr));
        label_30->setText(QApplication::translate("MainWindow", "T:", nullptr));
        TLabel->setText(QString());
        inputLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
