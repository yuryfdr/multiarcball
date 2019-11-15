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
#include "data/move.xpm"
#include "data/rot.xpm"
#include "data/rot_x.xpm"
#include "data/rot_y.xpm"
#include "data/rot_z.xpm"
#include "data/zoom.xpm"
#include "data/zoom_w.xpm"

namespace{
  bool cur_init=false;
  QCursor cur_move;
  QCursor cur_rotate;
  QCursor cur_zoom;
  QCursor cur_rotate_x;
  QCursor cur_rotate_y;
  QCursor cur_rotate_z;
  QCursor cur_zoom_w;
}

QArcballWidget::QArcballWidget(QWidget *parent) :
  #if __LEGACY__
  QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
#else
  QOpenGLWidget(parent)
#endif
,fovy(45.0), aspect_ratio(1), near_cp(1.0), far_cp(1000.0),
  umin(-1.0), umax(1.0), vmin(-1.0), vmax(1.0),
  cenx(0), ceny(0), cenz(0), eyex(0), eyey(0), eyez(50.0), upx(0), upy(1), upz(0),
  Rmax(1),pushed(false),
  projtype(Orthographic),
  transform(), currenttr(controls3d::NoTransform),
  arcball(mvct::XYZ(0,0,0),1.0), trcontrol(), zoomcontrol(), dollycontrol(10.0),
  b_zoom_frame(0)
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
  transform.reset();
}
void QArcballWidget::initializeGL(){
  initializeOpenGLFunctions();
}
void QArcballWidget::resizeGL(int w,int h){
  m_window_normalised_matrix.setToIdentity();
  m_window_normalised_matrix.translate(width()/2.,height()/2.);
  m_window_normalised_matrix.scale(width()/2.,-height()/2.);

  double w__=w,h__=h;
  cenx = 0.0 ,ceny = 0.0;
  cenz = 0.0;
  eyex = 0.0, eyey = 0.0;
  eyez = 1;//20.0 * Rmax();
  upx = 0.0,upz = 0.0;
  upy = 1.0;

  aspect_ratio = w__/h__;
  near_cp = -1000.0* Rmax;
  far_cp = 1000.0* Rmax;

  //fovy,vmin,vmax,umin,umax;
  if(Perspective == projtype){
    // Perspective projection
    fovy = 145.0;
    projtype = Perspective;
    near_cp = -1. * Rmax;
    far_cp = 10.0* Rmax;
  }else{
    // Orthographic projection
    if (aspect_ratio >= 1.) {
      vmin = -1*Rmax;
      vmax = 1*Rmax;
      umin = vmin * aspect_ratio;
      umax = vmax * aspect_ratio;
    } else {
      vmin = -1*Rmax/ aspect_ratio;
      vmax = 1*Rmax / aspect_ratio;
      umin = vmin * aspect_ratio;
      umax = vmax * aspect_ratio;
    }
    projtype = Orthographic;
  }
  // GL calls.
  glViewport(0, 0, w__, h__);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if ( projtype == Perspective )
    gluPerspective(fovy,aspect_ratio,near_cp,far_cp);
  else if ( projtype == Orthographic)
    glOrtho(umin,umax,vmin,vmax,near_cp,far_cp);
  m_proj.setToIdentity();
  m_proj.ortho(umin,umax,vmin,vmax,near_cp,far_cp);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyex,eyey,eyez,cenx,ceny,cenz,upx,upy,upz);
  //m_view.setToIdentity();
  //m_view.lookAt(QVector3D(eyex,eyey,eyez),QVector3D(cenx,ceny,cenz),QVector3D(upx,upy,upz));
  dist = sqrt( mvct::pow2(cenx-eyex) + mvct::pow2(ceny-eyey) + mvct::pow2(cenz-eyez) );
}

#include <QPainter>
#include <QStaticText>
void QArcballWidget::text(double x, double y, double z, const QString& str, const Qt::GlobalColor &pen,float scale){
#if 0
  renderText(x,y,z,str);
#else
  QPainter p(this);
  /*  double * mpr = new double[16];// projection
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

  QMatrix4x4 m_window_normalised_matrix;
  m_window_normalised_matrix.setToIdentity();
  QMatrix4x4 m_t;
  m_t.translate(QVector3D(ox,height()-oy,oz));
  p.setTransform(m_t.toTransform(),true);*/
  QMatrix4x4 mm=m_window_normalised_matrix*m_proj*m_model;
  QVector4D vec(x,y,z,1);
  vec=mm*vec;
  //p.setTransform(mm.toTransform());
  p.setPen(pen);
  QFont fnt("Sans",12);
  p.setFont(fnt);
  /*QStaticText strt(str);
  QMatrix4x4 mmst;
  mmst.scale(0.2*scale,-0.2*scale,0.2*scale);
  mmst.rotate(180,1,0,0);
  strt.prepare(mmst.toTransform(),p.font());
  p.drawStaticText(vec.x(),vec.y(),strt);
  p.end();*/
  //std::cerr<<str.toStdString()<<std::endl;
  p.drawText(vec.x(), vec.y(), str);
  //delete[] mpr;
  //delete[] mmd;
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
  pushed=true;
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
      if(mouseMode==Zoom){
        cursor(CursorZoomW);
        b_zoom_frame=true;
        mouse.x = d.x = event->x();
        mouse.y = d.y = event->y();
      }else if(mouseMode==Select){
        b_zoom_frame=true;
        mouse.x = d.x = event->x();
        mouse.y = d.y = event->y();
      }
    break;
  }
}
void QArcballWidget::mouseReleaseEvent ( QMouseEvent * event ){
  pushed=false;
  switch(event->button()){
    case Qt::MidButton:
      if(mod==Qt::ShiftModifier)handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,true);
      else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,true);
      update();
      mod=Qt::NoModifier;
    break;
    case Qt::LeftButton:
      if(b_zoom_frame){
        if(mouseMode==Zoom){
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
            update();
          }
        }
        update();
      }
    break;
  }
  cursor();
}
void QArcballWidget::mouseMoveEvent ( QMouseEvent * event ){
  if(event->buttons() & Qt::MidButton){
    if(mod==Qt::ShiftModifier)handle_pan(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,false);
    else handle_rotate(mvct::XY((double)event->x()/width(),(double)event->y()/height()),false,false);
    update();
  }
  if(b_zoom_frame){
    if(mouseMode==Zoom)cursor(CursorZoomW);
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

void QArcballWidget::handle_rotate(mvct::XY mouse,bool push,bool release){
  if ( currenttr != controls3d::NoTransform && currenttr != controls3d::Rotate ) return;
  currenttr = controls3d::Rotate;
  // Transform coords to lie between -1 to 1
  double y = ( -2.*mouse.y ) + 1.0;
  double x = ( 2.*mouse.x ) - 1.0;
  static double my;
  static double mx;
  if( mouse.y<0.05 ){
    if(push){
      cursor(CursorRotateZ);
      mx=x;
    }else{
      double angle=M_PI*(x-mx);
      transform.rotate_z(angle);
      mx=x;
    }
  }else if( mouse.y>0.95 ){
    if(push){
      mx=x;
      cursor(CursorRotateY);
    }else{
      double angle=-M_PI*(x-mx);
      transform.rotate_y(angle);
      mx=x;
    }
  }else if( mouse.x<0.05 || mouse.x>0.95 ){
    if(push){
      my=y;
      cursor(CursorRotateX);
    }else{
      double angle=M_PI*(y-my);
      transform.rotate_x(angle);
      my=y;
    }
  }else{
    arcball.mouse(mvct::XYZ(x,y,0));

    if( push ){
      arcball.begin_drag();
      cursor(CursorRotate);
    } else if ( release ) {
      arcball.end_drag();
      transform.rotate(arcball.quaternion_value());
      arcball.reset(); currenttr = controls3d::NoTransform;
      cursor();
    }
  }
  if( release ) cursor();
}

void QArcballWidget::handle_pan(mvct::XY mouse,bool push,bool release){
  if ( currenttr != controls3d::NoTransform && currenttr != controls3d::Pan ) return;
  currenttr = controls3d::Pan;
  // Transform coords to lie between -1 to 1
  double x = ( 2.*mouse.x ) - 1.0;
  double y = ( -2.*mouse.y ) + 1.0;

  // Adjust the x and y values so that moving mouse by 1 pixel
  // on screen moves point under mouse by 1 pixel
  double tx=0, ty=0;
  if ( projtype == Orthographic ) {
    // Orthographic projection
    tx = umin*(1.0-x)*0.5 + umax*(1.0+x)*0.5;
    ty = vmin*(1.0-y)*0.5 + vmax*(1.0+y)*0.5;
  }
  else if ( projtype == Perspective ) {
    // Perspective projection
    tx = x*dist*tan(mvct::deg2rad(fovy*aspect_ratio*0.5));
    ty = y*dist*tan(mvct::deg2rad(fovy*0.5));
  }
  trcontrol.mouse(mvct::XYZ(tx,ty,0));

  if( push ){
    trcontrol.begin_drag();
    cursor(CursorMove);
  }else if( release ){
    trcontrol.end_drag();
    transform.translate(trcontrol.trans_value());// Update the combined transformation
    trcontrol.reset(); currenttr = controls3d::NoTransform;
    cursor();
  }

}
void QArcballWidget::handle_zoom(mvct::XY mouse,bool push,bool release){
  if ( currenttr != controls3d::NoTransform && currenttr != controls3d::Zoom ) return;
  currenttr = controls3d::Zoom;
  // Transform coords to lie between -1 to 1
  double z = ( 2.*mouse.x ) - 1.0;

  zoomcontrol.mouse(mvct::XYZ(z,z,z));

  if ( push ){
    zoomcontrol.begin_drag();
    cursor(CursorZoom);
  }else if ( release ){
    zoomcontrol.end_drag();
    transform.scale(zoomcontrol.zoom_value());
    zoomcontrol.reset(); currenttr = controls3d::NoTransform;
    cursor();
  }

}
void QArcballWidget::handle_dolly(mvct::XY mouse,bool push,bool release){
  if ( currenttr != controls3d::NoTransform && currenttr != controls3d::Dolly ) return;
  currenttr = controls3d::Dolly;
  // Transform coords to lie between -1 to 1
  //z = ( double(Fl::event_x() << 1) / w() ) - 1.0;
  double z = ( 2.*mouse.x ) - 1.0;
  dollycontrol.mouse(mvct::XYZ(0,0,z));// dollycontrol.update();

  if ( push ) dollycontrol.begin_drag();
  else if ( release ) {
    dollycontrol.end_drag();
    // Shouldn't reset since the value is directly used for transformations
    // separate from other transformations
    currenttr = controls3d::NoTransform;
  }

}

void QArcballWidget::arcball_transform(){                     // Apply the arcball transformation
  double mat[16];

  // Do the dollying separately before everything else
  glTranslated(0,0,dollycontrol.dolly_value());
  switch ( currenttr ) {
    case controls3d::Pan :
      trcontrol.value().fill_array_row_major(mat);
      glMultMatrixd(mat);
    break;
    case controls3d::Zoom :
      zoomcontrol.value().fill_array_row_major(mat);
      glMultMatrixd(mat);
    break;
    case controls3d::Rotate :
      arcball.value().fill_array_row_major(mat);
      glMultMatrixd(mat);
    break;
    default:
    break;
  }
  //transform.apply();
  //double mat[16];
  transform.fill_array_column_major(mat);
  glMultMatrixd(mat);
}

void QArcballWidget::draw_zoom_frame(){
  if(b_zoom_frame){
    glDisable (GL_DEPTH_TEST);
    glMatrixMode (GL_PROJECTION);
    glPushMatrix ();
    glLoadIdentity ();
    glOrtho(0,view_width(),view_height(),0,-1,1);
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix ();
    glLoadIdentity ();
    glBegin (GL_LINE_LOOP);
    glColor4d (0., 0., 0., 0.9);
    glVertex3d (mouse.x-1, mouse.y-1, 0);
    glVertex3d (d.x-1, mouse.y-1, 0);
    glVertex3d (d.x-1, d.y-1, 0);
    glVertex3d (mouse.x-1, d.y-1, 0);
    glEnd ();
    glBegin (GL_LINE_LOOP);
    glColor4d (1., 1., 1., 0.9);
    glVertex3d (mouse.x, mouse.y, 0);
    glVertex3d (d.x, mouse.y, 0);
    glVertex3d (d.x, d.y, 0);
    glVertex3d (mouse.x, d.y, 0);
    glEnd ();
    glPopMatrix ();
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    glMatrixMode (GL_MODELVIEW);
    glEnable (GL_DEPTH_TEST);
  }
}
