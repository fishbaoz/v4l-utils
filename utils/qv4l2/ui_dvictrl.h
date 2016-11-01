/********************************************************************************
** Form generated from reading UI file 'dvictrl.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DVICTRL_H
#define UI_DVICTRL_H

#include "qv4l2.h"
#include <QWidget>
//#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QTabWidget>

class ApplicationWindow;

class PatternForm : public QWidget
{
    Q_OBJECT
private:
    QTabWidget *sequencetabWidget;
    QWidget *dvi1_tab;
    QWidget *dvi2_tab;

public:

    PatternForm(ApplicationWindow *aw);
    ~PatternForm();
    void setupUi(QWidget *PatternForm)
    {
        if (PatternForm->objectName().isEmpty())
            PatternForm->setObjectName(QString::fromUtf8("PatternForm"));
        PatternForm->resize(521, 518);
        sequencetabWidget = new QTabWidget(PatternForm);
        sequencetabWidget->setObjectName(QString::fromUtf8("sequencetabWidget"));
        sequencetabWidget->setGeometry(QRect(50, 50, 241, 131));
        dvi1_tab = new QWidget();
        dvi1_tab->setObjectName(QString::fromUtf8("dvi1_tab"));
        sequencetabWidget->addTab(dvi1_tab, QString());
        dvi2_tab = new QWidget();
        dvi2_tab->setObjectName(QString::fromUtf8("dvi2_tab"));
        sequencetabWidget->addTab(dvi2_tab, QString());

//        retranslateUi(PatternForm);

        sequencetabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PatternForm);
    } // setupUi

    void retranslateUi(QWidget *PatternForm)
    {
        PatternForm->setWindowTitle(QApplication::translate("PatternForm", "Form", 0, QApplication::UnicodeUTF8));
        sequencetabWidget->setTabText(sequencetabWidget->indexOf(dvi1_tab), QApplication::translate("PatternForm", "dvi1", 0, QApplication::UnicodeUTF8));
        sequencetabWidget->setTabText(sequencetabWidget->indexOf(dvi2_tab), QApplication::translate("PatternForm", "dvi2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};


#endif // UI_DVICTRL_H
