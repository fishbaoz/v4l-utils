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
#include <QProcess>

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

bool compare_widthxheight(char *r1, char *r2)
{
	printf("%s, %s\n", r1, r2);

	int r1_w, r1_h, r2_w, r2_h;

	r1_w = getw(r1);
	r1_h = geth(r1);
	r2_w = getw(r2);
	r2_h = geth(r2);

	printf("%d,%d,%d,%d,", r1_w, r1_h, r2_w, r2_h);
	if (r1_w < r2_w)
		return true;
	else if (r1_w==r2_w && r1_h < r2_h)
		return true;
	else
		return false;
}
void sort_xrandr(char xrandr[32][256])
{
	int i, j, num;
	char temp[32];

	for (i=0; i<32; i++) {
		if (xrandr[i][0] == 0)
			break;
	}
	num = i;
	for (i=0; i<num; i++) {
		for (j=i; j<num; j++) {
			if (compare_widthxheight(xrandr[i], xrandr[j])) {
				strcpy(temp, xrandr[i]);
				strcpy(xrandr[i], xrandr[j]);
				strcpy(xrandr[j], temp);
			}
		}
	}
}


PatternForm::PatternForm(QWidget *parent, ApplicationWindow *aw) :
	m_appWin(aw)
{
        sequencetabWidget = new QTabWidget(parent);
        sequencetabWidget->setObjectName(QString::fromUtf8("sequencetabWidget"));
        sequencetabWidget->setGeometry(QRect(40, 50, 251, 151));
        dvi1_seqtab = new QWidget();
        dvi1_seqtab->setObjectName(QString::fromUtf8("dvi1_seqtab"));
        resolution1_comboBox = new QComboBox(dvi1_seqtab);
        resolution1_comboBox->setObjectName(QString::fromUtf8("resolution1_comboBox"));
        resolution1_comboBox->setGeometry(QRect(90, 20, 131, 27));
        refreshrate1_comboBox = new QComboBox(dvi1_seqtab);
        refreshrate1_comboBox->setObjectName(QString::fromUtf8("refreshrate1_comboBox"));
        refreshrate1_comboBox->setGeometry(QRect(90, 70, 131, 27));
        label_3 = new QLabel(dvi1_seqtab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 20, 71, 17));
        label_4 = new QLabel(dvi1_seqtab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(-3, 70, 81, 20));
        sequencetabWidget->addTab(dvi1_seqtab, QString());
        dvi2_seqtab = new QWidget();
        dvi2_seqtab->setObjectName(QString::fromUtf8("dvi2_seqtab"));
        label_6 = new QLabel(dvi2_seqtab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 20, 68, 17));
        label_7 = new QLabel(dvi2_seqtab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 70, 81, 17));
        resolution2_comboBox = new QComboBox(dvi2_seqtab);
        resolution2_comboBox->setObjectName(QString::fromUtf8("resolution2_comboBox"));
        resolution2_comboBox->setGeometry(QRect(90, 20, 131, 27));
        refreshrate2_comboBox = new QComboBox(dvi2_seqtab);
        refreshrate2_comboBox->setObjectName(QString::fromUtf8("refreshrate2_comboBox"));
        refreshrate2_comboBox->setGeometry(QRect(90, 70, 131, 27));
        sequencetabWidget->addTab(dvi2_seqtab, QString());
        modetabWidget = new QTabWidget(parent);
        modetabWidget->setObjectName(QString::fromUtf8("modetabWidget"));
        modetabWidget->setGeometry(QRect(40, 240, 251, 131));
        dvi1_modetab = new QWidget();
        dvi1_modetab->setObjectName(QString::fromUtf8("dvi1_modetab"));
        mode1_comboBox = new QComboBox(dvi1_modetab);
        mode1_comboBox->setObjectName(QString::fromUtf8("mode1_comboBox"));
        mode1_comboBox->setGeometry(QRect(90, 20, 131, 27));
        label_5 = new QLabel(dvi1_modetab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 41, 21));
        modetabWidget->addTab(dvi1_modetab, QString());
        dvi2_modetab = new QWidget();
        dvi2_modetab->setObjectName(QString::fromUtf8("dvi2_modetab"));
        label_8 = new QLabel(dvi2_modetab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 30, 68, 17));
        mode2_comboBox = new QComboBox(dvi2_modetab);
        mode2_comboBox->setObjectName(QString::fromUtf8("mode2_comboBox"));
        mode2_comboBox->setGeometry(QRect(90, 20, 111, 27));
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

	QString mode_name("模式"), numString, modefile_name("modes/mode");
	int num;
	QFile mode_file;

	for (num=1; num<=255; num++) {
		numString.setNum(num, 10);
		//modefile_name.append(numString);
		mode_file.setFileName(modefile_name+numString+".png");
		if (mode_file.exists()) {
			mode1_comboBox->addItem(mode_name+numString);
			mode2_comboBox->addItem(mode_name+numString);
		} else
			break;
	}
	//mode1_comboBox->addItem(tr("模式1"));
	//mode1_comboBox->addItem(tr("模式2"));
	//mode1_comboBox->addItem(tr("模式3"));
	connect(mode1_comboBox, SIGNAL(activated(int)), SLOT(patOutput1Changed(int)));

	//mode2_comboBox->addItem("模式1");
	//mode2_comboBox->addItem("模式2");
	//mode2_comboBox->addItem("模式3");
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
	sort_xrandr(modes_table[1]);
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
	sort_xrandr(modes_table[2]);
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
	refreshrate1_comboBox->setCurrentIndex(1);
	connect(refreshrate1_comboBox, SIGNAL(activated(int)), SLOT(refreshOutput1Changed(int)));

	refreshrate2_comboBox->addItem("50");
	refreshrate2_comboBox->addItem("60");
	refreshrate2_comboBox->addItem("70");
	refreshrate2_comboBox->setCurrentIndex(1);
	connect(refreshrate2_comboBox, SIGNAL(activated(int)), SLOT(refreshOutput2Changed(int)));
	//for (;;);
}

PatternForm::~PatternForm()
{

}

// TODO: disable the unconnected screen.
void PatternForm::patOutput1Changed(int mode)
{
	//qDebug("pat output %d, %s", mode, qPrintable(m_patternOutput->currentText()));
	QString numString;
	numString.setNum(mode+1, 10);
//	if (m_appWin->screen_count >= 2)
//		m_appWin->m_pattern[1]->updatePattern(mode+1);
	QProcess nitrogen;
	QStringList arguments;

	printf("run nitrogen mode=%d\n", mode);
	arguments << "--force-setter=xinerama" << "--set-scaled" << ".//modes//mode"+numString +".png" << "--head=1";
	//arguments << "--force-setter=xinerama" << "--set-scaled" << ".//modes//modes1.png" << "--head=1";

	nitrogen.start("nitrogen", arguments);

	if (!nitrogen.waitForStarted()) {
		qDebug("start nitrogen failed");
		return ;
	}

	while (false == nitrogen.waitForFinished()) {
		qDebug("finish nitrogen failed");
		return;
	}
}

void PatternForm::patOutput2Changed(int mode)
{
	QString numString;
	numString.setNum(mode+1, 10);

//	qDebug("pat output %d, %s", mode, qPrintable(m_patternOutput->currentText()));
//	if (m_appWin->screen_count == 3)
//		m_appWin->m_pattern[2]->updatePattern(mode+1);
	QProcess nitrogen;
	QStringList arguments;

	printf("run nitrogen mode=%d\n", mode);
	arguments << "--force-setter=xinerama" << "--set-scaled" << ".//modes//mode"+numString +".png" << "--head=2";
	//arguments << "--force-setter=xinerama" << "--set-scaled" << ".//modes//modes1.png" << "--head=1";

	nitrogen.start("nitrogen", arguments);

	if (!nitrogen.waitForStarted()) {
		qDebug("start nitrogen failed");
		return ;
	}

	while (false == nitrogen.waitForFinished()) {
		qDebug("finish nitrogen failed");
		return;
	}
}


void PatternForm::resolutionOutput1Changed(int mode)
{
//	qDebug("pat output %d, %s", mode, qPrintable(m_patternOutput->currentText()));
//	m_appWin->m_pattern[1]->updatePattern(mode+1);
	qDebug("resolution=%s\n", qPrintable(resolution1_comboBox->currentText()));
	char mode_name[32]="DFP4";
	char dest_mode[10]="1920x1080";
	char dest_mode2[10]="1920x1080";
	//char *argv[]={"xrandr", "-d", ":0", "--output", "DisplayPort-0", "--mode", dest_mode, NULL};
	//char *argv[]={"xrandr", "-d", ":0", "--output", "DFP4", "--mode", dest_mode, NULL};
	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[1]->mode_name, "--mode", dest_mode, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_mode, qPrintable(resolution1_comboBox->currentText()));
	if (m_appWin->screen_count == 3)
		strcpy(dest_mode2, qPrintable(resolution2_comboBox->currentText()));
	//xrandr(7, argv, NULL, NULL);
	QProcess xrandr;
	QStringList arguments;

	//if (m_appWin->screen_count == 3)
	arguments << "-d" << ":0" << "--output" << m_appWin->m_pattern[1]->mode_name << "--mode" << dest_mode  << "--output" << m_appWin->m_pattern[2]->mode_name << "--mode" << dest_mode2;
	xrandr.start("xrandr", arguments);

	if (!xrandr.waitForStarted()) {
		qDebug("start xrandr failed");
		return;
	}
	while (false == xrandr.waitForFinished()) {
		qDebug("finished xrandr failed");
		return;
	}
	//char *argv2[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[2]->mode_name, "--mode", dest_mode, NULL};
  	//printf("sizeof argv=%d\n", sizeof(argv));
	//strcpy(dest_mode, qPrintable(resolution2_comboBox->currentText()));
	//xrandr(7, argv, NULL, NULL);
	//xrandr(7, argv, NULL);
//	m_appWin->m_pattern[1]->updateScreen();
//	m_appWin->m_pattern[1]->screen_rect.setWidth(getw(dest_mode));
//	printf("width1=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
//	m_appWin->m_pattern[1]->screen_rect.setHeight(geth(dest_mode));
//	printf("width1.2=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
//	if (m_appWin->screen_count >= 2)
//		m_appWin->m_pattern[1]->screen_rect.setLeft(
//			m_appWin->m_pattern[0]->screen_rect.width()
//		);
	
//	printf("width1.3=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
//	if (m_appWin->screen_count == 3) {
//		m_appWin->m_pattern[2]->screen_rect.setLeft(
//			m_appWin->m_pattern[0]->screen_rect.width() +
//			m_appWin->m_pattern[1]->screen_rect.width()
//		);
//	}
//	printf("width1.4=%d\n", m_appWin->m_pattern[1]->screen_rect.width());
//	printf("1 set2Lefti=%d+%d\n", m_appWin->m_pattern[0]->screen_rect.width(), m_appWin->m_pattern[1]->screen_rect.width());
	
	//m_appWin->m_pattern[1]->updateScreen();
	//if (m_appWin->screen_count == 3)
	//	m_appWin->m_pattern[2]->updateScreen();
	//patOutput1Changed(1);
	int resetmode = mode1_comboBox->currentIndex();
	patOutput1Changed(resetmode);
	resetmode = mode2_comboBox->currentIndex();
	patOutput2Changed(resetmode);
}

void PatternForm::resolutionOutput2Changed(int mode)
{
	qDebug("resolution=%s\n", qPrintable(resolution2_comboBox->currentText()));
	char dest_mode[10]="1024x768";
	char dest_mode1[10]="1024x768";
	//char *argv[]={"xrandr", "-d", ":0", "--output", "DisplayPort-0", "--mode", dest_mode, NULL};
	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[2]->mode_name, "--mode", dest_mode, NULL};
  	//printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_mode, qPrintable(resolution2_comboBox->currentText()));
	strcpy(dest_mode1, qPrintable(resolution1_comboBox->currentText()));
	//xrandr(7, argv, NULL, NULL);
	//char *argv1[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[1]->mode_name, "--mode", dest_mode, NULL};
	//strcpy(dest_mode, qPrintable(resolution1_comboBox->currentText()));
//	xrandr(7, argv, NULL, NULL);
	QProcess xrandr;
	QStringList arguments;

	arguments << "-d" << ":0" << "--output" << m_appWin->m_pattern[2]->mode_name << "--mode" << dest_mode << "--output" << m_appWin->m_pattern[1]->mode_name << "--mode" << dest_mode1;
	xrandr.start("xrandr", arguments);

	if (!xrandr.waitForStarted()) {
		qDebug("start xrandr failed");
		return;
	}
	while (false == xrandr.waitForFinished()) {
		qDebug("finished xrandr failed");
		return;
	}
//	m_appWin->m_pattern[2]->screen_rect.setWidth(getw(dest_mode));
//	m_appWin->m_pattern[2]->screen_rect.setHeight(geth(dest_mode));
//	m_appWin->m_pattern[1]->screen_rect.setLeft(
//		m_appWin->m_pattern[0]->screen_rect.width()
//	);
//	m_appWin->m_pattern[2]->screen_rect.setLeft(
//		m_appWin->m_pattern[0]->screen_rect.width() +
//		m_appWin->m_pattern[1]->screen_rect.width()
//	);
//	printf("2 set2Lefti=%d+%d\n", m_appWin->m_pattern[0]->screen_rect.width(), m_appWin->m_pattern[1]->screen_rect.width());
	
	//m_appWin->m_pattern[1]->updateScreen();
	//if (m_appWin->screen_count >= 2)
	//	m_appWin->m_pattern[2]->updateScreen();
	//m_appWin->m_pattern[2]->updateScreen();
	//m_appWin->updateScreen();
	//patOutput2Changed(1);
	int resetmode = mode2_comboBox->currentIndex();
	patOutput2Changed(resetmode);

	resetmode = mode1_comboBox->currentIndex();
	patOutput1Changed(resetmode);
}

void PatternForm::refreshOutput1Changed(int rate)
{
	char dest_rate[10]="60";
	char dest_mode[10]="1920x1080";

	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[1]->mode_name, "--mode", dest_mode, "--rate", dest_rate, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_mode, qPrintable(resolution1_comboBox->currentText()));
	strcpy(dest_rate, qPrintable(refreshrate1_comboBox->currentText()));
	if (m_appWin->screen_count >= 2) {
		//xrandr(9, argv, NULL, NULL);
		QProcess xrandr;
		QStringList arguments;

		arguments << "-d" << ":0" << "--output" << m_appWin->m_pattern[1]->mode_name << "--mode" << dest_mode << "--rate" << dest_rate;
		xrandr.start("xrandr", arguments);

		if (!xrandr.waitForStarted()) {
			qDebug("start xrandr failed");
			return;
		}
		while (false == xrandr.waitForFinished()) {
			qDebug("finished xrandr failed");
			return;
		}
	}
}

void PatternForm::refreshOutput2Changed(int rate)
{
	char dest_rate[10]="60";
	char dest_mode[10]="1920x1080";

	char *argv[]={"xrandr", "-d", ":0", "--output", m_appWin->m_pattern[2]->mode_name, "--mode", dest_mode, "--rate", dest_rate, NULL};
  	printf("sizeof argv=%d\n", sizeof(argv));
	strcpy(dest_mode, qPrintable(resolution2_comboBox->currentText()));
	strcpy(dest_rate, qPrintable(refreshrate2_comboBox->currentText()));
	if (m_appWin->screen_count == 3) {
		//xrandr(9, argv, NULL, NULL);
		QProcess xrandr;
		QStringList arguments;

		arguments << "-d" << ":0" << "--output" << m_appWin->m_pattern[2]->mode_name << "--mode" << dest_mode << "--rate" << dest_rate;
		xrandr.start("xrandr", arguments);

		if (!xrandr.waitForStarted()) {
			qDebug("start xrandr failed");
			return;
		}
		while (false == xrandr.waitForFinished()) {
			qDebug("finished xrandr failed");
			return;
		}
	}
}
