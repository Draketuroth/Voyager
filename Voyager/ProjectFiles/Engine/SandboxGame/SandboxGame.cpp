/*
* SandboxGame.cpp
* Game initialization
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <QtWidgets\qapplication.h>
#include <QtWidgets\qwidget.h>
#include <Graphics\GlWindow.h>
#include <Windows.h>
#include <QtCore\qdebug.h>

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	GlWindow gl_window;
	if (!gl_window.initialize())
	{
		return -1;
	}
	gl_window.show();
	int error_code =  application.exec();
	if (!gl_window.shutdown())
	{
		error_code |= 1;
	}
	return error_code;
}