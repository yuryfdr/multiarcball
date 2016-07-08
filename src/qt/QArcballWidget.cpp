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
#include "QArcballWidget.h"

#include <QtGui/QMouseEvent>
#include "../data/move.xpm"
#include "../data/rot.xpm"
#include "../data/rot_x.xpm"
#include "../data/rot_y.xpm"
#include "../data/rot_z.xpm"
#include "../data/zoom.xpm"
#include "../data/zoom_w.xpm"

namespace{
  bool cur_init=false;
  QCursor cur_move;
  QCursor cur_rotate;
  QCursor cur_zoom;
  QCursor cur_rotate_x;
  QCursor cur_rotate_y;
  QCursor cur_rotate_z;
  QCursor cur_zoom_w;
};
QArcballWidget::QArcballWidget(QWidget *parent) :
#if HAVE_QT4
  QGLWidget(parent)
#else
  QOpenGLWidget(parent)
#endif
{
  setMouseTracking(true);
  if(!cur_init){
    cur_move=QCursor(QPixmap(move_xpm),15,15);
    cur_rotate=QCursor(QPixmap(rot_xpm),15,15);
    cur_zoom=QCursor(QPixmap(zoom_xpm),15,15);
    cur_rotate_x=QCursor(QPixmap(rot_x_xpm),15,15);
    cur_rotate_y=QCursor(QPixmap(rot_y_xpm),15,15);
    cur_rotate_z=QCursor(QPixmap(rot_z_xpm),15,15);
    cur_zoom_w=QCursor(QPixmap(zoom_w_xpm),15,15);
    cur_init=true;
  }
}
void QArcballWidget::initializeGL(){
#if !HAVE_QT4
    initializeOpenGLFunctions();
#endif
}
void QArcballWidget::resizeGL(int w,int h){
    reshape();
}

void QArcballWidget::text(double x, double y, double z,const QString& str){
  renderText(x,y,z,str);
}
void QArcballWidget::stext(int size,GLfloat x, GLfloat y, GLfloat z,const char *str)const{
#if HAVE_QT4
  (const_cast<QArcballWidget*>(this))->renderText(x,y,z,str);
#else
  QPainter p(const_cast<QArcballWidget*>(this));
  QFont fnt=p.font();
  p.setPen(QPen(Qt::white));
  fnt.setPixelSize(size);
  double * mpr = new double[16];// projection
  double * mmd = new double[16];// model view
  int viewport[4];
  viewport[0] = 0;
  viewport[1] = 0;
  viewport[2] = width();//drw->w();
  viewport[3] = height();//drw->h();
  glGetDoublev(GL_PROJECTION_MATRIX,mpr);
  glGetDoublev(GL_MODELVIEW_MATRIX,mmd);
  double ox,oy,oz;
  gluProject(x,y,z,mmd,mpr,viewport,&ox,&oy,&oz);
  p.drawText(x,y,str);
#endif
}

void QArcballWidget::cursor(const Cursors3D cur){
  switch(cur){
    case CursorMove:
      setCursor(cur_move);
      break;
    case CursorRotate:
      setCursor(cur_rotate);
      break;
    case CursorRotateX:
      setCursor(cur_rotate_x);
      break;
    case CursorRotateY:
      setCursor(cur_rotate_y);
      break;
    case CursorRotateZ:
      setCursor(cur_rotate_z);
      break;
    case CursorZoom:
      setCursor(cur_zoom);
      break;
    case CursorZoomW:
      setCursor(cur_zoom_w);
      break;

    case CursorDefault:
    default:
      setCursor(Qt::ArrowCursor);
  }
}

void QArcballWidget::keyPressEvent(QKeyEvent * event){
  switch(event->key()){
    case Qt::Key_Left:
      transform.translate(Rmax * 0.1, 0, 0.);
      update();
      break;
    case Qt::Key_Right:
      transform.translate(-Rmax * 0.1, 0, 0.);
      update();
      break;
  }
}

void QArcballWidget::mousePressEvent ( QMouseEvent * event ){
    switch(event->button()){
      case Qt::MidButton:
        if(event->modifiers() & Qt::ShiftModifier){
            mod=Qt::ShiftModifier;
            handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),true,false);
        }
        else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),true,false);
        update();
        break;
      case Qt::LeftButton:
        cursor(CursorZoomW);
        b_zoom_frame=true;
        mouse.x = d.x = event->x();
        mouse.y = d.y = event->y();
        break;
    }
}
void QArcballWidget::mouseReleaseEvent ( QMouseEvent * event ){
    switch(event->button()){
      case Qt::MidButton:
        if(mod==Qt::ShiftModifier)handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,true);
        else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,true);
        update();
        mod=Qt::NoModifier;
        break;
      case Qt::LeftButton:
        b_zoom_frame=false;
        double sx =::fabs(d.x-mouse.x);
        double sy =::fabs(d.y-mouse.y);
        double zx;
        if(sx > 5 && sy > 5 && sx / sy < 13. && sy / sx < 13.){
           if (sx / sy >= view_width() / view_height()) zx = view_width() / sx;
           else zx = view_height() / sy;
           transform.translate(2.*Rmax*(view_width()-(mouse.x+d.x))/2./view_height(),
                              -2.*Rmax*(view_height()-(mouse.y + d.y))/2./view_height(),0.);
           transform.scale (zx, zx, zx);
        }
        update();
        cursor();
        break;

    }
}
void QArcballWidget::mouseMoveEvent ( QMouseEvent * event ){
  if(event->buttons() & Qt::MidButton){
    if(mod==Qt::ShiftModifier)handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,false);
    else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,false);
    update();
  }
  if(b_zoom_frame){
    cursor(CursorZoomW);
    d.x=event->x();
    d.y=event->y();
    update();
  }
}
void QArcballWidget::wheelEvent ( QWheelEvent * event ){
    if(event->delta()<0)transform./*post_*/scale(mvct::XYZ(.9,.9,.9));
    else if(event->delta()>0)transform./*post_*/scale(mvct::XYZ(1.1,1.1,1.1));
    update();
}
