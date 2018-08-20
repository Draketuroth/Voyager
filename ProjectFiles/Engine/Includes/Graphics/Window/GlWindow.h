/*
* GlWindow.h
* Basic GL Window
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#ifndef VE_SANDBOX_GL_WINDOW_H
#define VE_SANDBOX_GL_WINDOW_H
#include <QtOpenGL\qgl.h>
#include <QtCore\qtimer.h>

class GlWindow : public QGLWidget
{
	Q_OBJECT

	QTimer timer;

protected:

	// This function is called once before the first call to paintGL or resizeGL. 
	// This function should set up any required OpenGL context rendering flags, display lists, etc. 
	void initializeGL();

	// This function is called whenever the widget has been resized.
	// The new size is passed in width and height.
	void resizeGL(int width, int height);

	// This function is called whenever the widget need to be painted. 
	void paintGL();

private slots:
	void winupdate();
	void updateVelocity();
	void rotateShip();
	void handleBoundaries();
private:
	void update();
	void draw();
	void doGl();

public:
	bool initialize();
	bool shutdown();
};

#endif