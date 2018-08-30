//============================================================================
// # VOYAGER ENGINE #
// Name: main.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Graphics module entry point
//============================================================================

#include <QtWidgets\qapplication.h>

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication app(argc, argv);
	return app.exec();
}