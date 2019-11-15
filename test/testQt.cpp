/*
   Copyright 2007-2009 by the Yury Fedorchenko.

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

#include "draw_cube.h"
#include <QMainWindow>
#include <QApplication>

class testarc : public QArcballWidget{
public:
testarc(QWidget*p=0):QArcballWidget(p){
}
void paintGL(){
  glClearColor(0.25,0.5,0.5, 1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //reshape();
  glPushMatrix();
  arcball_transform();
  //draw_axis();
  drawCube();
  //draw_3d_orbit();
  glPopMatrix();
  draw_zoom_frame();
}
};

int main(int argc,char** argv){
  QApplication app(argc,argv);
  QMainWindow win;
  testarc glw;
  glw.resize(640,480);
  win.setCentralWidget(&glw);
  win.show();
  return app.exec();
}
