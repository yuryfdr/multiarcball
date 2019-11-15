/*
  Copyright 2012 by the Yury Fedorchenko.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with main.c; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA

  Please report all bugs and problems to "yuryfdr@users.sourceforge.net".

*/
#ifndef CGLWIDGET_H
#define CGLWIDGET_H
#ifdef _MSC_VER
#include <WinSock2.h>
#else
#define HAVE_GLU_LIB 1
#endif

#include <qglobal.h>

#define __LEGACY__ 0
#if __LEGACY__
#include <QGLWidget>
#else
#include <QOpenGLWidget>
#define QGLWidget QOpenGLWidget
#endif
#include <QPainter>
#include <QOpenGLFunctions_2_1>
#include "3dcontrols.h"
#ifdef HAVE_GLU_LIB // strange bug with msvc
#include <GL/glu.h>
#endif
using namespace mvct;
#include <QMatrix4x4>

class QArcballWidget : public QGLWidget ,public QOpenGLFunctions_2_1
{
    Q_OBJECT
public:
#ifndef HAVE_GLU_LIB
#include "glulocal.cpp"
#endif
    explicit QArcballWidget(QWidget *parent = 0);
    //from basic_ball
    /// For perspective projection
    double fovy;                                      //< Field-of-view in degrees in y
    double aspect_ratio;                              //< Ratio of width to height
    double near_cp;                                   //< Near clipping plane
    double far_cp;                                    //< Far clipping plane

    /// For orthographic projection
    double umin,umax,vmin,vmax;                       //< Viewing frustum

    double cenx, ceny, cenz;                          //< Center point for gluLookAt
    double eyex, eyey, eyez;                          //< Eye point for gluLookAt
    double upx, upy, upz;                             //< Up vector for gluLookAt
    double dist;                                      //< Dist from eye pt to center pt
    double Rmax;
    bool pushed;
    QMatrix4x4 m_window_normalised_matrix,m_proj,m_model;
    // View/projection parameters
    enum ProjectionType { Orthographic=0, Perspective=1 };
    ProjectionType projtype;                          ///< Ortho/Perspective projection (Perspective not fully realized)
    controls3d::Transformation transform;   ///< Combined transformation
    controls3d::TransformsType currenttr;   ///< Current transformation

    controls3d::ArcballCntrl arcball;    ///< The arcball controller
    controls3d::PanCntrl trcontrol;      ///< Translation controller
    controls3d::ZoomCntrl zoomcontrol;   ///< Zoom controller
    controls3d::DollyCntrl dollycontrol; ///< Dolly controller (10.0 scale)

    bool b_zoom_frame;
    XY d,mouse;
    virtual void handle_rotate(mvct::XY mouse,bool push,bool release);//< @par mouse - XY mouse coords dividing by widget W/H
    virtual void handle_pan(mvct::XY mouse,bool push,bool release);//< @par mouse - XY mouse coords dividing by widget W/H
    virtual void handle_zoom(mvct::XY mouse,bool push,bool release);//< @par mouse - XY mouse coords dividing by widget W/H
    virtual void handle_dolly(mvct::XY mouse,bool push,bool release);//< @par mouse - XY mouse coords dividing by widget W/H

    //transformations
    void arcball_transform();   //< Apply the arcball transformation
    void reset(bool reset_rotation=true) { //< Reset transformation @par reset_rotation - if false only zoom to initial value
      transform.reset();
    }
    void zoom_in(){transform.scale(1.1, 1.1, 1.1);}
    void zoom_out(){transform.scale(.9, .9, .9);}

    enum MouseMode{
      NoneMM,
      Select,
      SelectO,
      SelectB,
      Rotate,
      Pan,
      Zoom,
      Dist
    }mouseMode;
    enum Views3D{Nochange=0,Left,Right,Top,Bottom,Front,Back,
      LeftTopFront,RightTopFront,LeftBottomFront,RightBottomFront,
      LeftTopBack,RightTopBack,LeftBottomBack,RightBottomBack};
    void views3D(Views3D cv)
    {
      controls3d::Transformation transRotate;
      if(Nochange!=cv){
        transRotate.reset();
      }
      switch(cv) {
      case Left:
        break;
      case Right:
        transRotate.post_rotate(mvct::Quaternion(M_PI,XYZ(0,1.,0)));
        break;
      case Top:
        transRotate.post_rotate(mvct::Quaternion(M_PI_2,XYZ(1,0,0)));
        break;
      case Bottom:
        transRotate.post_rotate(mvct::Quaternion(-M_PI_2,XYZ(1,0,0)));
        break;
      case Front:
        transRotate.rotate(mvct::Quaternion(M_PI_2,XYZ(0,1,0)));
        break;
      case Back:
        transRotate.rotate(mvct::Quaternion(-M_PI_2,XYZ(0,1,0)));
        break;
      case LeftTopFront:
        transRotate.post_rotate(mvct::Quaternion(M_PI_4,XYZ(0,1,0)));
        transRotate.post_rotate(mvct::Quaternion(asin(1./sqrt(3.)),XYZ(1,0,1)));
        break;
      case RightTopFront:
        transRotate.rotate(mvct::Quaternion(3.*M_PI_4,XYZ(0,1,0))*mvct::Quaternion(-asin(1./sqrt(3.)),XYZ(1,0,-1)));
        break;
      case LeftBottomFront:
        transRotate.rotate(mvct::Quaternion(M_PI_4,XYZ(0,1,0))*mvct::Quaternion(-asin(1./sqrt(3.)),XYZ(1,0,1)));
        break;
      case RightBottomFront:
        transRotate.rotate(mvct::Quaternion(3.*M_PI_4,XYZ(0,1,0))*mvct::Quaternion(asin(1./sqrt(3.)),XYZ(1,0,-1)));
        break;
      case LeftTopBack:
        transRotate.rotate(mvct::Quaternion(-M_PI_4,XYZ(0,1,0))*mvct::Quaternion(asin(1./sqrt(3.)),XYZ(1,0,-1)));
        break;
      case RightTopBack:
        transRotate.rotate(mvct::Quaternion(-3.*M_PI_4,XYZ(0,1,0))*mvct::Quaternion(-asin(1./sqrt(3.)),XYZ(1,0,1)));
        break;
      case LeftBottomBack:
        transRotate.rotate(mvct::Quaternion(-M_PI_4,XYZ(0,1,0))*mvct::Quaternion(-asin(1./sqrt(3.)),XYZ(1,0,-1)));
        break;
      case RightBottomBack:
        transRotate.rotate(mvct::Quaternion(-3.*M_PI_4,XYZ(0,1,0))*mvct::Quaternion(asin(1./sqrt(3.)),XYZ(1,0,1)));
        break;
      }
      transform = transRotate;
      //queue_draw();
    }

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );
    void keyPressEvent(QKeyEvent * event);
    Qt::KeyboardModifier mod;
    virtual void text(double x, double y, double z, const QString& str, const Qt::GlobalColor &pen, float scale=1);
    void draw_zoom_frame();
public:
  virtual int view_width(){return width();}
  virtual int view_height(){return height();}

  enum Cursors3D{ CursorNone=0,CursorDefault=1,CursorMove,CursorZoom,CursorRotate,CursorRotateX,
      CursorRotateY,CursorRotateZ,CursorZoomW};

  virtual void cursor(const Cursors3D cur=CursorDefault);

signals:

public slots:
  void zoom11(){reset();update();}
};

#endif // CGLWIDGET_H
