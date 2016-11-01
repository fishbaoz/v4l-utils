/*************************************************************************
	> File Name: ui_dvictrl.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 31 Oct 2016 04:18:14 PM CST
 ************************************************************************/

#include "ui_dvictrl.h"
#include <QApplication>

PatternForm::PatternForm(ApplicationWindow *aw) :
	dvi1_tab(NULL),
	dvi2_tab(NULL)
{
	sequencetabWidget = new QTabWidget(aw);
	dvi1_tab = new QWidget();
        dvi1_tab->setObjectName(QString::fromUtf8("dvi1_tab"));
        sequencetabWidget->addTab(dvi1_tab, QString());
        dvi2_tab = new QWidget();
        dvi2_tab->setObjectName(QString::fromUtf8("dvi2_tab"));
        sequencetabWidget->addTab(dvi2_tab, QString());
}

PatternForm::~PatternForm()
{

}
