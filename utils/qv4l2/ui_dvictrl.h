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
#include <QComboBox>

class ApplicationWindow;

class PatternForm : public QWidget
{
    Q_OBJECT
private:
    QTabWidget *sequencetabWidget;
    QWidget *dvi1_seqtab;
    QComboBox *resolution1_comboBox;
    QComboBox *refreshrate1_comboBox;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *dvi2_seqtab;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *resolution2_comboBox;
    QComboBox *refreshrate2_comboBox;
    QTabWidget *modetabWidget;
    QWidget *dvi1_modetab;
    QComboBox *mode1_comboBox;
    QLabel *label_5;
    QWidget *dvi2_modetab;
    QLabel *label_8;
    QComboBox *mode2_comboBox;
    QLabel *label;
    QLabel *label_2;

    ApplicationWindow *m_appWin;

public:

    PatternForm(QWidget *parent, ApplicationWindow *aw);
    ~PatternForm();

private slots:
    void patOutputChanged(int);
};


#endif // UI_DVICTRL_H
