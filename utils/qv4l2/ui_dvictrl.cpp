/*************************************************************************
	> File Name: ui_dvictrl.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 31 Oct 2016 04:18:14 PM CST
 ************************************************************************/

#include "ui_dvictrl.h"
#include <QApplication>
#include<X11/extensions/Xrandr.h>
extern "C" {
#include "xrandr.h"
}

PatternForm::PatternForm(QWidget *parent, ApplicationWindow *aw) :
	m_appWin(aw)
{
	sequencetabWidget = new QTabWidget(parent);
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
        modetabWidget = new QTabWidget(parent);
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
        label = new QLabel(parent);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 200, 68, 17));
        label_2 = new QLabel(parent);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 10, 81, 17));

	/*retranslate UI */
	#if 0			/* English */
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
	#else
        label_3->setText(QApplication::translate("PatternForm", "分辨率", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PatternForm", "刷新率", 0, QApplication::UnicodeUTF8));
        sequencetabWidget->setTabText(sequencetabWidget->indexOf(dvi1_seqtab), QApplication::translate("PatternForm", "dvi1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PatternForm", "分辨率", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PatternForm", "刷新率", 0, QApplication::UnicodeUTF8));
        sequencetabWidget->setTabText(sequencetabWidget->indexOf(dvi2_seqtab), QApplication::translate("PatternForm", "dvi2", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PatternForm", "模式", 0, QApplication::UnicodeUTF8));
        modetabWidget->setTabText(modetabWidget->indexOf(dvi1_modetab), QApplication::translate("PatternForm", "dvi1", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PatternForm", "模式", 0, QApplication::UnicodeUTF8));
        modetabWidget->setTabText(modetabWidget->indexOf(dvi2_modetab), QApplication::translate("PatternForm", "dvi2", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PatternForm", "模式", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PatternForm", "时序", 0, QApplication::UnicodeUTF8));
	#endif


        sequencetabWidget->setCurrentIndex(0);
        modetabWidget->setCurrentIndex(1);

	mode1_comboBox->addItem(tr("模式1"));
	mode1_comboBox->addItem(tr("模式2"));
	mode1_comboBox->addItem(tr("模式3"));
	connect(mode1_comboBox, SIGNAL(activated(int)), SLOT(patOutput1Changed(int)));

	mode2_comboBox->addItem("模式1");
	mode2_comboBox->addItem("模式2");
	mode2_comboBox->addItem("模式3");
	connect(mode2_comboBox, SIGNAL(activated(int)), SLOT(patOutput2Changed(int)));
#if 0
	Display *dpy = XOpenDisplay(NULL);
	Window root = RootWindow(dpy, 0);
	int num_sizes;
	XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
	Rotation original_rotation;

	XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
	short original_rate          = XRRConfigCurrentRate(conf);
	SizeID original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);

	int width=xrrs[original_size_id].width;
	int height=xrrs[original_size_id].height;

	qDebug("width=%d, height=%d\n", width, height);
	XCloseDisplay(dpy);
#endif
	char *argv[]={"xrandr", "-d", ":0"};
	char modes_table[3][32][256]={0};
	char modes_name[3][32]={0};
	memset(modes_table, 0, /* sizeof(modes_table)*/3*32*256   );
	printf("sizeof argv=%d\n", sizeof(argv));
	xrandr(3, argv, modes_table, modes_name);
	char *mode= &(modes_table[1][0][0]);
	printf("names=%s,%s, %s\n", modes_name[0], modes_name[1], modes_name[2]);
	if (modes_name[1][0])
		strcpy(m_appWin->m_pattern[1]->mode_name, modes_name[1]);
	while (mode[0]) {
		printf("mode=%s\n", &mode[0]);
			resolution1_comboBox->addItem((char *)(&mode[0]));
		mode += 256;
	}
	connect(resolution1_comboBox, SIGNAL(activated(int)), SLOT(resolutionOutput1Changed(int)));

		//for (;;);
	mode = &(modes_table[2][0][0]);
	if (modes_name[2][0])
		strcpy(m_appWin->m_pattern[2]->mode_name, modes_name[2]);
	while (mode[0]) {
		printf("mode=%s\n", &mode[0]);
		resolution2_comboBox->addItem((char *)(&mode[0]));
		mode += 256;
	}
	connect(resolution2_comboBox, SIGNAL(activated(int)), SLOT(resolutionOutput2Changed(int)));

	//for (;;);
	refreshrate1_comboBox->addItem("50");
	refreshrate1_comboBox->addItem("60");
	refreshrate1_comboBox->addItem("70");
	connect(refreshrate1_comboBox, SIGNAL(activated(int)), SLOT(refreshOutput1Changed(int)));

	refreshrate2_comboBox->addItem("50");
	refreshrate2_comboBox->addItem("60");
	refreshrate2_comboBox->addItem("70");
	connect(refreshrate2_comboBox, SIGNAL(activated(int)), SLOT(refreshOutput2Changed(int)));
	//for (;;);
}

PatternForm::~PatternForm()
{

}

// TODO: disable the unconnected screen.
void PatternForm::patOutput1Changed(int mode)
{
//	qDebug("pat output %d, %s", mode, qPrintable(m_patternOutput->currentText()));
	m_appWin->m_pattern[1]->updatePattern(mode+1);
}

void PatternForm::patOutput2Changed(int mode)
{
//	qDebug("pat output %d, %s", mode, qPrintable(m_patternOutput->currentText()));
	m_appWin->m_pattern[2]->updatePattern(mode+1);
}

int getw(char *mode)
{
	int ret;
	char *beg = mode;
	while(*mode != 'x')
		mode ++;
	*mode = '\n';
	ret = atoi(beg);
	printf("get w=%d\n", ret);
	*mode = 'x';
	return ret;
}
int geth(char *mode)
{
	int ret;
	while(*mode != 'x')
		mode ++;
	mode ++;
	ret = atoi(mode);
	printf("get h=%d\n", ret);
	return ret;
}
void PatternForm::resolutionOutput1Changed(int mode)
{
//	qDebug("pat output %d, %s", mode, qPrintable(m_patternOutput->currentText()));
//	m_appWin->m_pattern[1]->updatePattern(mode+1);
	qDebug("resolution=%s\n", qPrintable(resolution1_comboBox->currentText()));
	char mode_name[32]="DFP4";
	char dest_mode[10]="1920x1080";
	//char *argv[]={"xrandr", "-d", ":0", "--output", "DisplayPort-0", "--mode", dest_mode, NULL};
	//char *argv[]={"xrandr", "-d", ":0", "--output", "DFP4", "--mode", dest_mode, NULL};
	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[1]->mode_name, "--mode", dest_mode, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_mode, qPrintable(resolution1_comboBox->currentText()));
	xrandr(7, argv, NULL, NULL);
	//xrandr(7, argv, NULL);
//	m_appWin->m_pattern[1]->updateScreen();
	m_appWin->m_pattern[1]->screen_rect.setWidth(getw(dest_mode));
	printf("width1=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
	m_appWin->m_pattern[1]->screen_rect.setHeight(geth(dest_mode));
	m_appWin->m_pattern[1]->screen_rect.setLeft(
		m_appWin->m_pattern[1]->screen_rect.width()
	);
	
	printf("width1=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
	m_appWin->m_pattern[2]->screen_rect.setLeft(
		m_appWin->m_pattern[0]->screen_rect.width() +
		m_appWin->m_pattern[1]->screen_rect.width()
	);
	printf("width1=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
	printf("1 set2Lefti=%d+%d\n", m_appWin->m_pattern[0]->screen_rect.width(), m_appWin->m_pattern[1]->screen_rect.width());
	
	m_appWin->m_pattern[1]->updateScreen();
	m_appWin->m_pattern[2]->updateScreen();
	//patOutput1Changed(1);
}

void PatternForm::resolutionOutput2Changed(int mode)
{
	qDebug("resolution=%s\n", qPrintable(resolution2_comboBox->currentText()));
	char dest_mode[10]="1920x1080";
	//char *argv[]={"xrandr", "-d", ":0", "--output", "DisplayPort-0", "--mode", dest_mode, NULL};
	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[2]->mode_name, "--mode", dest_mode, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_mode, qPrintable(resolution2_comboBox->currentText()));
	xrandr(7, argv, NULL, NULL);
	m_appWin->m_pattern[2]->screen_rect.setWidth(getw(dest_mode));
	m_appWin->m_pattern[2]->screen_rect.setHeight(geth(dest_mode));
	m_appWin->m_pattern[1]->screen_rect.setLeft(
		m_appWin->m_pattern[0]->screen_rect.width()
	);
	m_appWin->m_pattern[2]->screen_rect.setLeft(
		m_appWin->m_pattern[0]->screen_rect.width() +
		m_appWin->m_pattern[1]->screen_rect.width()
	);
	printf("2 set2Lefti=%d+%d\n", m_appWin->m_pattern[0]->screen_rect.width(), m_appWin->m_pattern[1]->screen_rect.width());
	
	m_appWin->m_pattern[1]->updateScreen();
	m_appWin->m_pattern[2]->updateScreen();
	//m_appWin->m_pattern[2]->updateScreen();
	//m_appWin->updateScreen();
	//patOutput2Changed(1);
}

void PatternForm::refreshOutput1Changed(int rate)
{
	char dest_rate[10]="60";
	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[1]->mode_name, "--rate", dest_rate, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_rate, qPrintable(refreshrate1_comboBox->currentText()));
	xrandr(7, argv, NULL, NULL);
	
}

void PatternForm::refreshOutput2Changed(int rate)
{
	char dest_rate[10]="60";
	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[2]->mode_name, "--rate", dest_rate, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_rate, qPrintable(refreshrate2_comboBox->currentText()));
	xrandr(7, argv, NULL, NULL);
}
