//============================================================================
// # VOYAGER ENGINE #
// Name			: SandboxGame.cpp
// Module		: SandboxGame
// Author		: Fredrik Linde
// Created on	: Aug 14, 2018
// Description	: Experimental module entry point
//============================================================================

#include <QtWidgets\qapplication.h>
#include <QtWidgets\qwidget.h>
#include <QtCore\qdebug.h>
#include <Windows.h>

#include <Graphics/Window/GLWindow.h>

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	Graphics::GLWindow window;
	window.resize(QSize(1024, 768));
	window.show();

	int error_code = application.exec();

	return error_code;
}