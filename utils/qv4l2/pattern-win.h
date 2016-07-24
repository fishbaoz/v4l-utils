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

#ifndef PATTERN_WIN_H
#define PATTERN_WIN_H

#include "qv4l2.h"

#include <QWidget>
#include <QShortcut>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QMenu>


class ApplicationWindow;

class PatternWin : public QWidget
{
	Q_OBJECT

public:
	PatternWin(ApplicationWindow *aw);
	~PatternWin();


public slots:
//	void resetSize();
//	void customMenuRequested(QPoint pos);

private slots:
//	void escape();
//	void fullScreen();

protected:
	void closeEvent(QCloseEvent *event);
//	void mouseDoubleClickEvent(QMouseEvent *e);

	/**
	 * @brief Get the amount of space outside the video frame.
	 *
	 * The margins are that of the window that encloses the displaying
	 * video frame. The sizes are total in both width and height.
	 *
	 * @return The margins around the video frame.
	 */
//	QSize getMargins();

	/**
	 * @brief Creates the content of the window.
	 *
	 * Construct the new window layout and adds the video display surface.
	 * @param videoSurface The widget that contains the renderer.
	 */
	void buildWindow(QWidget *videoSurface);

	/**
	 * @brief Calculate source size after pixel aspect scaling and cropping
	 *
	 */
//	void updateSize();

	/**
	 * @brief Frame information.
	 *
	 * @note Set and accessed from derived render dependent classes.
	 */
//	struct frame m_frame;
//	struct crop  m_crop;
//	QSize m_origFrameSize;  // int m_sourceWinWidth; int m_sourceWinHeight;
//	QSize m_windowSize;     // int m_curWinWidth; int m_curWinHeight;
//	QSize m_scaledSize;

	/**
	 * @brief Update frame information to renderer.
	 *
	 * @note Must be implemented by derived render dependent classes.
	 */
//	virtual void setRenderFrame() = 0;

	/**
	 * @brief Determines if scaling is to be applied to video frame.
	 */
//	static bool m_enableScaling;

signals:
	void close();

private:
	ApplicationWindow *m_appWin;
	QImage *m_image;
	QLabel *m_videoSurface;
//	static double m_pixelAspectRatio;
//	static CropMethod m_cropMethod;
//	QShortcut *m_hotkeyClose;
//	QShortcut *m_hotkeyScaleReset;
//	QShortcut *m_hotkeyExitFullscreen;
//	QShortcut *m_hotkeyToggleFullscreen;
	QVBoxLayout *m_vboxLayout;
	unsigned m_vboxSpacing;
};
#endif
