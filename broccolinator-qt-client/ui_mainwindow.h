/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *type;
    QLabel *weight;
    QLabel *ok;
    QLabel *ko;
    QLabel *camera;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(502, 361);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(351, 73, 71, 23));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(351, 11, 49, 23));
        label_2->setFont(font);
        type = new QLabel(centralwidget);
        type->setObjectName(QString::fromUtf8("type"));
        type->setGeometry(QRect(351, 41, 131, 25));
        type->setFont(font);
        type->setFrameShape(QFrame::Box);
        type->setAlignment(Qt::AlignCenter);
        weight = new QLabel(centralwidget);
        weight->setObjectName(QString::fromUtf8("weight"));
        weight->setGeometry(QRect(351, 103, 131, 25));
        weight->setFont(font);
        weight->setFrameShape(QFrame::Box);
        weight->setFrameShadow(QFrame::Plain);
        weight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ok = new QLabel(centralwidget);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(10, 260, 481, 91));
        ok->setFont(font);
        ok->setStyleSheet(QString::fromUtf8("QLabel { \n"
"	background-color : 	green; \n"
"	color : white; \n"
"}"));
        ok->setFrameShape(QFrame::Box);
        ok->setAlignment(Qt::AlignCenter);
        ko = new QLabel(centralwidget);
        ko->setObjectName(QString::fromUtf8("ko"));
        ko->setGeometry(QRect(10, 260, 481, 91));
        ko->setFont(font);
        ko->setStyleSheet(QString::fromUtf8("QLabel { \n"
"	background-color : 	red; \n"
"	color : white; \n"
"}"));
        ko->setFrameShape(QFrame::Box);
        ko->setAlignment(Qt::AlignCenter);
        camera = new QLabel(centralwidget);
        camera->setObjectName(QString::fromUtf8("camera"));
        camera->setGeometry(QRect(10, 10, 320, 240));
        camera->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        camera->raise();
        label->raise();
        label_2->raise();
        type->raise();
        weight->raise();
        ok->raise();
        ko->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Weight:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        type->setText(QString());
        weight->setText(QString());
        ok->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        ko->setText(QCoreApplication::translate("MainWindow", "KO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
