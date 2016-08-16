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

#include "exampleQt.h"

int main(int argc,char** argv){
  QApplication app(argc,argv);
  QMainWindow win;
  testarc glw;
  glw.resize(640,480);
  QToolBar* tb=win.addToolBar("main tool bar");
  QAction* act11 = tb->addAction("1:1",&glw,SLOT(reset11()));
  win.setCentralWidget(&glw);
  win.show();
  return app.exec();
}
