/* qv4l2: a control panel controlling v4l2 devices.
 *
 * Copyright (C) 2006 Hans Verkuil <hverkuil@xs4all.nl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "pattern-win.h"

#include <QCloseEvent>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

#include <math.h>

#define MIN_WIN_SIZE_WIDTH 16
#define MIN_WIN_SIZE_HEIGHT 12

//bool PatternWin::m_enableScaling = true;
//double PatternWin::m_pixelAspectRatio = 1.0;
//CropMethod PatternWin::m_cropMethod = QV4L2_CROP_NONE;

PatternWin::PatternWin(ApplicationWindow *aw) :
	m_appWin(aw)
{
	setWindowTitle("V4L2 Pattern");
//	m_hotkeyClose = new QShortcut(Qt::CTRL+Qt::Key_W, this);
//	connect(m_hotkeyClose, SIGNAL(activated()), this, SLOT(close()));
//	connect(new QShortcut(Qt::Key_Q, this), SIGNAL(activated()), this, SLOT(close()));
//	m_hotkeyScaleReset = new QShortcut(Qt::CTRL+Qt::Key_F, this);
//	connect(m_hotkeyScaleReset, SIGNAL(activated()), this, SLOT(resetSize()));
//	connect(aw->m_resetScalingAct, SIGNAL(triggered()), this, SLOT(resetSize()));
//	m_hotkeyExitFullscreen = new QShortcut(Qt::Key_Escape, this);
//	connect(m_hotkeyExitFullscreen, SIGNAL(activated()), this, SLOT(escape()));
//	m_hotkeyToggleFullscreen = new QShortcut(Qt::Key_F, this);
//	connect(m_hotkeyToggleFullscreen, SIGNAL(activated()), aw->m_makeFullScreenAct, SLOT(toggle()));
//	m_exitFullScreen = new QAction(QIcon(":/fullscreenexit.png"), "Exit Fullscreen", this);
//	connect(m_exitFullScreen, SIGNAL(triggered()), this, SLOT(escape()));
//	m_enterFullScreen = new QAction(QIcon(":/fullscreen.png"), "Show Fullscreen", this);
//	connect(m_enterFullScreen, SIGNAL(triggered()), this, SLOT(fullScreen()));
//	m_frame.format = 0;
//	m_frame.size.setWidth(0);
//	m_frame.size.setHeight(0);
//	m_frame.planeData[0] = NULL;
//	m_frame.planeData[1] = NULL;
//	m_frame.planeData[2] = NULL;
//	m_crop.delta.setWidth(0);
//	m_crop.delta.setHeight(0);
//	m_crop.size.setWidth(0);
//	m_crop.size.setHeight(0);
//	m_crop.updated = 0;
//	m_scaledSize.setWidth(0);
//	m_scaledSize.setHeight(0);
//	m_origFrameSize.setWidth(0);
//	m_origFrameSize.setHeight(0);
//	m_windowSize.setWidth(0);
//	m_windowSize.setHeight(0);

	m_videoSurface = new QLabel(this);
	buildWindow(m_videoSurface);
	//QDesktopWidget *desktop = QApplication::desktop();
	QImage* img=new QImage;

	if(! ( img->load("mode1.png") ) ) //
	{
		qDebug("load image failed\n");
		delete img;
		return;
	}
	//QRect rect = desktop->screenGeometry(0);
	//QImage result = img->scaled(rect.width(), rect.height());
	//m_videoSurface->setPixmap(QPixmap::fromImage(result));

	screen_rect = desktop->screenGeometry(screen_num); //TODO:
}

void PatternWin::updatePattern(int mode)
{
	QImage* img=new QImage;
	m_videoSurface->clear();

//	mode ++;
	switch (mode) {
	case 1:
		if(! ( img->load("mode1.png") ) ) {
			qDebug("load image failed\n");
			delete img;
			return;
		}
		break;
	case 2:
		if(! ( img->load("mode2.png") ) ) {
			qDebug("load image failed\n");
			delete img;
			return;
		}
		break;
	case 3:
		if(! ( img->load("mode3.png") ) ) {
			qDebug("load image failed\n");
			delete img;
			return;
		}
		break;
	}
	m_image = img;
	screen_rect = desktop->screenGeometry(screen_num); //TODO:
	printf("width=%d, height=%d\n", screen_rect.width(), screen_rect.height());
	QImage result = img->scaled(screen_rect.width(), screen_rect.height());
	m_videoSurface->setPixmap(QPixmap::fromImage(result));
}

/* refresh after resolution is changed. */
void PatternWin::updateScreen()
{
	//screen_rect = desktop->screenGeometry(screen_num);
//	m_image->scaled(screen_rect.width(), screen_rect.height());
	buildWindow(m_videoSurface);
	resize(screen_rect.width(), screen_rect.height());
	QImage result = m_image->scaled(screen_rect.width(), screen_rect.height());
	m_videoSurface->setPixmap(QPixmap::fromImage(result));
//	screen_rect = desktop->screenGeometry(screen_num);
	move(screen_rect.left(), 0);

}

//void PatternWin::updateScreens()
//{
//}
PatternWin::PatternWin(ApplicationWindow *aw, QDesktopWidget *d, int n) :
	m_appWin(aw),
	desktop(d),
	screen_num(n)
{
	setWindowTitle("V4L2 Pattern");
//	m_hotkeyClose = new QShortcut(Qt::CTRL+Qt::Key_W, this);
//	connect(m_hotkeyClose, SIGNAL(activated()), this, SLOT(close()));
//	connect(new QShortcut(Qt::Key_Q, this), SIGNAL(activated()), this, SLOT(close()));
//	m_hotkeyScaleReset = new QShortcut(Qt::CTRL+Qt::Key_F, this);
//	connect(m_hotkeyScaleReset, SIGNAL(activated()), this, SLOT(resetSize()));
//	connect(aw->m_resetScalingAct, SIGNAL(triggered()), this, SLOT(resetSize()));
//	m_hotkeyExitFullscreen = new QShortcut(Qt::Key_Escape, this);
//	connect(m_hotkeyExitFullscreen, SIGNAL(activated()), this, SLOT(escape()));
//	m_hotkeyToggleFullscreen = new QShortcut(Qt::Key_F, this);
//	connect(m_hotkeyToggleFullscreen, SIGNAL(activated()), aw->m_makeFullScreenAct, SLOT(toggle()));
//	m_exitFullScreen = new QAction(QIcon(":/fullscreenexit.png"), "Exit Fullscreen", this);
//	connect(m_exitFullScreen, SIGNAL(triggered()), this, SLOT(escape()));
//	m_enterFullScreen = new QAction(QIcon(":/fullscreen.png"), "Show Fullscreen", this);
//	connect(m_enterFullScreen, SIGNAL(triggered()), this, SLOT(fullScreen()));
//	m_frame.format = 0;
//	m_frame.size.setWidth(0);
//	m_frame.size.setHeight(0);
//	m_frame.planeData[0] = NULL;
//	m_frame.planeData[1] = NULL;
//	m_frame.planeData[2] = NULL;
//	m_crop.delta.setWidth(0);
//	m_crop.delta.setHeight(0);
//	m_crop.size.setWidth(0);
//	m_crop.size.setHeight(0);
//	m_crop.updated = 0;
//	m_scaledSize.setWidth(0);
//	m_scaledSize.setHeight(0);
//	m_origFrameSize.setWidth(0);
//	m_origFrameSize.setHeight(0);
//	m_windowSize.setWidth(0);
//	m_windowSize.setHeight(0);

	m_videoSurface = new QLabel(this);
	buildWindow(m_videoSurface);
	screen_rect = desktop->screenGeometry(screen_num);
	resize(screen_rect.width(), screen_rect.height());
	printf("%s, w=%d, h=%d\n", __func__, screen_rect.width(), screen_rect.height());
//	move (0, 0);
	updatePattern(1);
}

PatternWin::~PatternWin()
{
	if (layout() == NULL)
		return;

	layout()->removeWidget(this);
	delete layout();
//	delete m_hotkeyClose;
//	delete m_hotkeyScaleReset;
}


void PatternWin::buildWindow(QWidget *videoSurface)
{
	int l, t, r, b;
	if (m_vboxLayout)
		m_vboxLayout = new QVBoxLayout(this);
	m_vboxLayout->getContentsMargins(&l, &t, &r, &b);
	m_vboxLayout->setMargin(0);
	m_vboxLayout->addWidget(videoSurface, 1000, Qt::AlignCenter);

	setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));
}


void PatternWin::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
	emit close();
}
