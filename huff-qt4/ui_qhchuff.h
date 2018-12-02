/********************************************************************************
** Form generated from reading UI file 'qhchuff.ui'
**
** Created: Sun Dec 24 10:44:21 2017
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHCHUFF_H
#define UI_QHCHUFF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qhchuff
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QProgressBar *progressBar;
    QLabel *label;
    QTextEdit *textEdit;
    QLabel *label_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qhchuff)
    {
        if (Qhchuff->objectName().isEmpty())
            Qhchuff->setObjectName(QString::fromUtf8("Qhchuff"));
        Qhchuff->resize(600, 400);
        centralWidget = new QWidget(Qhchuff);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 200, 161, 51));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 200, 161, 51));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 270, 521, 31));
        progressBar->setValue(24);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 330, 221, 16));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(90, 150, 391, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 90, 181, 31));
        Qhchuff->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Qhchuff);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Qhchuff->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Qhchuff);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Qhchuff->setStatusBar(statusBar);

        retranslateUi(Qhchuff);

        QMetaObject::connectSlotsByName(Qhchuff);
    } // setupUi

    void retranslateUi(QMainWindow *Qhchuff)
    {
        Qhchuff->setWindowTitle(QApplication::translate("Qhchuff", "Qhchuff", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Qhchuff", "\345\216\213\347\274\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Qhchuff", "\350\247\243\345\216\213\347\274\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Qhchuff", "designed by qhc  \302\251 2017", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Qhchuff", "\350\276\223\345\205\245\346\226\207\344\273\266\345\220\215\346\235\245\344\275\277\347\224\250\346\255\244\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Qhchuff: public Ui_Qhchuff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHCHUFF_H
