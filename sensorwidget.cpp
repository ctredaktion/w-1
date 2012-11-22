// Copyright (c) 2012 Oliver Lau <ola@ct.de>
// All rights reserved.

#include <QPainter>
#include "sensorwidget.h"


SensorWidget::SensorWidget(QWidget* parent)
    : QWidget(parent)
    , mWindowAspectRatio(1.0)
    , mImageAspectRatio(1.0)
    , mFPS(0)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}


void SensorWidget::resizeEvent(QResizeEvent* e)
{
    mWindowAspectRatio = (qreal)e->size().width() / e->size().height();
}


void SensorWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    if (mWindowAspectRatio < mImageAspectRatio) {
        const int h = int(width() / mImageAspectRatio);
        mDestRect = QRect(0, (height()-h)/2, width(), h);
    }
    else {
        const int w = int(height() * mImageAspectRatio);
        mDestRect = QRect((width()-w)/2, 0, w, height());
    }
    if (!mDepthFrame.isNull()) {
        p.fillRect(rect(), QColor(20, 20, 20));
        p.drawImage(mDestRect, mDepthFrame);
        p.setOpacity(0.6);
        p.setPen(Qt::red);
        p.setBrush(Qt::transparent);
        p.drawLine(0, height()/2, width(), height()/2);
        p.drawLine(width()/2, 0, width()/2, height());
        p.setOpacity(1.0);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(Qt::white);
        p.drawText(mDestRect, Qt::AlignRight | Qt::AlignBottom, tr("%1 fps").arg(mFPS, 0, 'f', 1));
    }
    else {
        p.fillRect(rect(), QColor(44, 8, 7));
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QColor(220, 40, 30));
        p.drawText(rect(), Qt::AlignHCenter | Qt::AlignVCenter, tr("Initializing sensor ... please wait ...!"));
    }
}


void SensorWidget::setDepthFrame(const QImage& frame)
{
    mDepthFrame = frame;
    mImageAspectRatio = (qreal)mDepthFrame.width() / mDepthFrame.height();
    update();
}
