// Copyright (c) 2012 Oliver Lau <oliver@von-und-fuer-lau.de>
// All rights reserved.

#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_

#include <QMainWindow>
#include <QCloseEvent>
#include <QShowEvent>
#include <QTimerEvent>
#include <QTime>
#include <QImage>

#include <XnCppWrapper.h>

#include "3dwidget.h"
#include "sensorwidget.h"
#include "sensormotor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent*);
    void timerEvent(QTimerEvent*);

private:
    Ui::MainWindow *ui;
    SensorWidget* mSensorWidget;
    ThreeDWidget* mThreeDWidget;
    SensorMotor mSensorMotor;
    int mFrameTimerId;
    int mRegressTimerId;
    xn::ScriptNode mScriptNode;
    xn::Context mContext;
    xn::DepthGenerator mDepthGenerator;
    xn::ImageGenerator mVideoGenerator;
    xn::DepthMetaData mDepthMetaData;
    xn::ImageMetaData mVideoMetaData;
    qreal hA;
    qreal hB;
    QTime mT0;
    int mFrameCount;
    QImage mVideoImage;
    QImage mDepthImage;

private: // methods
    void initSensor(void);
    void startSensor(void);
    void stopSensor(void);
    void regressH(void);

    void saveSettings(void);
    void restoreSettings(void);

private slots:

};

#endif // __MAINWINDOW_H_
