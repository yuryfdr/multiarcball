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

QArcballWidget::QArcballWidget(QWidget *parent) :
#if HAVE_QT4
    QGLWidget(parent)
#else
    QOpenGLWidget(parent)
#endif
{
}
void QArcballWidget::initializeGL(){
#if !HAVE_QT4
    initializeOpenGLFunctions();
#endif
}
void QArcballWidget::resizeGL(int w,int h){
    reshape();
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

void QArcballWidget::mousePressEvent ( QMouseEvent * event ){
    switch(event->button()){
      case Qt::MidButton:
        std::cerr<<event->modifiers()<<'\t'<<Qt::ShiftModifier<<'\t'<<(event->modifiers() & Qt::ShiftModifier) <<std::endl;
        if(event->modifiers() & Qt::ShiftModifier){
            mod=Qt::ShiftModifier;
            handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),true,false);
        }
        else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),true,false);
        update();
        break;
    }
}
void QArcballWidget::mouseReleaseEvent ( QMouseEvent * event ){
    switch(event->button()){
      case Qt::MidButton:
        std::cerr<<event->modifiers()<<'\t'<<Qt::ShiftModifier<<'\t'<<(event->modifiers() & Qt::ShiftModifier) <<std::endl;
        if(mod==Qt::ShiftModifier)handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,true);
        else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,true);
        update();
        mod=Qt::NoModifier;
        break;
    }
}
void QArcballWidget::mouseMoveEvent ( QMouseEvent * event ){
    if(event->buttons() & Qt::MidButton){
        if(mod==Qt::ShiftModifier)handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,false);
        else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,false);
        update();
    }
}
void QArcballWidget::wheelEvent ( QWheelEvent * event ){
    if(event->delta()<0)transform./*post_*/scale(mvct::XYZ(.9,.9,.9));
    else if(event->delta()>0)transform./*post_*/scale(mvct::XYZ(1.1,1.1,1.1));
    update();
}
