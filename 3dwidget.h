// Copyright (c) 2012 Oliver Lau <oliver@von-und-fuer-lau.de>
// All rights reserved.

#ifndef __3DWIDGET_H_
#define __3DWIDGET_H_

#define USE_SHADER

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QVector2D>
#include <QVector3D>
#include <QGLWidget>
#include <gl/GLU.h>
#ifdef USE_SHADER
#include <QGLShaderProgram>
#endif


class ThreeDWidget : public QGLWidget
{
    Q_OBJECT

public: // methods
    explicit ThreeDWidget(QWidget* parent = NULL);
    QSize minimumSizeHint(void) const { return QSize(320, 240); }
    QSize sizeHint(void) const { return QSize(640, 480); }

    void setXRotation(int);
    void setYRotation(int);
    void setZoom(float);

    int xRotation(void) const { return mXRot; }
    int yRotation(void) const { return mYRot; }
    float zoom(void) const { return mZoom; }

    static const float DefaultZoom;
    static const float DefaultXRot;
    static const float DefaultYRot;

public slots:
    void videoFrameReady(const QImage&);

private: // variables
    static const QVector3D mVertices[4];
    static const QVector2D mTexCoords[4];

    int mXRot;
    int mYRot;
    float mXTrans;
    float mYTrans;
    float mZTrans;
    float mZoom;
    QPoint mLastPos;
    GLuint mTextureHandle;
#ifdef USE_SHADER
    QGLShaderProgram* mShaderProgram;
#endif

protected: // methods
    void initializeGL(void);
    void resizeGL(int, int);
    void paintGL(void);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    void keyPressEvent(QKeyEvent*);

private: // methods

};

#endif // __3DWIDGET_H_
