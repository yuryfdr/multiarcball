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

#include <QGLWidget>
#include "3dcontrols.h"
#include "basic_ball.h"


class QArcballWidget : public QGLWidget , public controls3d::basic_ball
{
    Q_OBJECT
public:
    explicit QArcballWidget(QWidget *parent = 0);
protected:
    virtual void paintGL(){};
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );
    Qt::KeyboardModifier mod;
public:
  virtual int view_width(){return width();}
  virtual int view_height(){return height();}

protected:
  virtual void stext(int size, GLfloat x, GLfloat y, GLfloat z,const char *str)const;

signals:
    
public slots:
    
};

#endif // CGLWIDGET_H
