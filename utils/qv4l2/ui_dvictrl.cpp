/*************************************************************************
	> File Name: ui_dvictrl.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 31 Oct 2016 04:18:14 PM CST
 ************************************************************************/

#include "ui_dvictrl.h"
#include <QApplication>

PatternForm::PatternForm(QWidget *aw)
{
	sequencetabWidget = new QTabWidget(aw);
        sequencetabWidget->setObjectName(QString::fromUtf8("sequencetabWidget"));
        sequencetabWidget->setGeometry(QRect(50, 50, 241, 131));
        dvi1_seqtab = new QWidget();
        dvi1_seqtab->setObjectName(QString::fromUtf8("dvi1_seqtab"));
        resolution1_comboBox = new QComboBox(dvi1_seqtab);
        resolution1_comboBox->setObjectName(QString::fromUtf8("resolution1_comboBox"));
        resolution1_comboBox->setGeometry(QRect(110, 20, 85, 27));
        refreshrate1_comboBox = new QComboBox(dvi1_seqtab);
        refreshrate1_comboBox->setObjectName(QString::fromUtf8("refreshrate1_comboBox"));
        refreshrate1_comboBox->setGeometry(QRect(110, 70, 85, 27));
        label_3 = new QLabel(dvi1_seqtab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 20, 71, 17));
        label_4 = new QLabel(dvi1_seqtab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(-3, 70, 91, 20));
        sequencetabWidget->addTab(dvi1_seqtab, QString());
        dvi2_seqtab = new QWidget();
        dvi2_seqtab->setObjectName(QString::fromUtf8("dvi2_seqtab"));
        label_6 = new QLabel(dvi2_seqtab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 20, 68, 17));
        label_7 = new QLabel(dvi2_seqtab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 60, 68, 17));
        resolution2_comboBox = new QComboBox(dvi2_seqtab);
        resolution2_comboBox->setObjectName(QString::fromUtf8("resolution2_comboBox"));
        resolution2_comboBox->setGeometry(QRect(110, 20, 85, 27));
        refreshrate2_comboBox = new QComboBox(dvi2_seqtab);
        refreshrate2_comboBox->setObjectName(QString::fromUtf8("refreshrate2_comboBox"));
        refreshrate2_comboBox->setGeometry(QRect(110, 60, 85, 27));
        sequencetabWidget->addTab(dvi2_seqtab, QString());
        modetabWidget = new QTabWidget(aw);
        modetabWidget->setObjectName(QString::fromUtf8("modetabWidget"));
        modetabWidget->setGeometry(QRect(50, 240, 241, 131));
        dvi1_modetab = new QWidget();
        dvi1_modetab->setObjectName(QString::fromUtf8("dvi1_modetab"));
        mode1_comboBox = new QComboBox(dvi1_modetab);
        mode1_comboBox->setObjectName(QString::fromUtf8("mode1_comboBox"));
        mode1_comboBox->setGeometry(QRect(80, 20, 85, 27));
        label_5 = new QLabel(dvi1_modetab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 41, 21));
        modetabWidget->addTab(dvi1_modetab, QString());
        dvi2_modetab = new QWidget();
        dvi2_modetab->setObjectName(QString::fromUtf8("dvi2_modetab"));
        label_8 = new QLabel(dvi2_modetab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 40, 68, 17));
        mode2_comboBox = new QComboBox(dvi2_modetab);
        mode2_comboBox->setObjectName(QString::fromUtf8("mode2_comboBox"));
        mode2_comboBox->setGeometry(QRect(90, 30, 85, 27));
        modetabWidget->addTab(dvi2_modetab, QString());
        label = new QLabel(aw);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 200, 68, 17));
        label_2 = new QLabel(aw);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 10, 81, 17));

		/*retranslate UI */
        label_3->setText(QApplication::translate("PatternForm", "resolution", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PatternForm", "refresh rate", 0, QApplication::UnicodeUTF8));
        sequencetabWidget->setTabText(sequencetabWidget->indexOf(dvi1_seqtab), QApplication::translate("PatternForm", "dvi1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PatternForm", "resolution", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PatternForm", "refresh rate", 0, QApplication::UnicodeUTF8));
        sequencetabWidget->setTabText(sequencetabWidget->indexOf(dvi2_seqtab), QApplication::translate("PatternForm", "dvi2", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PatternForm", "mode", 0, QApplication::UnicodeUTF8));
        modetabWidget->setTabText(modetabWidget->indexOf(dvi1_modetab), QApplication::translate("PatternForm", "dvi1", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PatternForm", "mode", 0, QApplication::UnicodeUTF8));
        modetabWidget->setTabText(modetabWidget->indexOf(dvi2_modetab), QApplication::translate("PatternForm", "dvi2", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PatternForm", "mode", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PatternForm", "sequence", 0, QApplication::UnicodeUTF8));


        sequencetabWidget->setCurrentIndex(0);
        modetabWidget->setCurrentIndex(1);

}

PatternForm::~PatternForm()
{

}
