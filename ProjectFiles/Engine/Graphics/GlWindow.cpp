/*
* GlWindow.cpp
* Basic GL Window
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <gl\glew.h>
#include <Graphics/Window/GlWindow.h>
#include <cassert>
#include <QtGui\qevent.h>
#include <Math\Vector\Vector3D.h>
#include <Math\Matrix\Matrix2DH.h>
#include <Core\DebugTools\Profiling\Profile.h>
#include <Core\DebugTools\Profiling\Profiler.h>
#include <Core\Timing\Clock.h>
using Math::Vector3D;
using Math::Matrix2DH;
using Timing::Clock;
using Profiling::Profiler;

namespace
{
	// Makes it private to the compilation unit.
	Vector3D verts[] =
	{
		Vector3D(+0.0f, 0.14142135623f, 1),
		Vector3D(-0.1f, -0.1f, 1),
		Vector3D(+0.1f, -0.1f, 1),
	};

	// 6 * float (4 bytes) = 24 bytes 
	// (*verts) = size of first element in array. 1 2D Vector = 2 floats = 8 bytes
	// NUM_VERTS = 24 / 8 = 3
	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector3D transformed_verts[NUM_VERTS];
	Vector3D ship_pos;
	Vector3D ship_vel;
	float ship_orient = 0.0f;
	Clock internal_clock;
}

void GlWindow::initializeGL()
{
	// Catch error code if glew could not be initialized properly.
	GLenum error_code = glewInit();
	assert(error_code == 0);

	// 1. Specifies the number of buffer object names to be generated.
	// 2. Specifies an array in which the generated buffer object names are stored. 
	glGenBuffers(1, &vertexBufferID);

	// Bind a named buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// Set NULL, we provide the size ourselves later.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), NULL, GL_DYNAMIC_DRAW);

	connect(&timer, SIGNAL(timeout()), this, SLOT(_winupdate()));

	timer.start(0);
}

void GlWindow::resizeGL(int width, int height)
{
	// Setup viewport.
	//glViewport(0, 0, (GLint)width, (GLint)height);
}

void GlWindow::update()
{
	// UPDATE
	// Euler integration
	// P = Position + velocity times delta
	// V = Velocity + acceleration times delta
	// ship_pos = P + V * times delta
	internal_clock.lap();
	profiler.newFrame();

	rotateShip();
	updateVelocity();
	checkBoundaries();
	ship_pos += ship_vel * internal_clock.lastLapTime();
}

void GlWindow::doGl()
{
	// VIEWPORT SETUP
	// int min_size = std::min(width(), height());
	// Vector3D viewport_location;
	// viewport_location.x = width() / 2 - min_size / 2;
	// viewport_location.y = height() / 2 - min_size / 2;
	// glViewport(viewport_location.x, viewport_location.y, min_size, min_size);

	glViewport(0, 0, width(), height());

	// DATAPOINTERS SETUP
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// SEND DATA TO OPENGL
	glBufferSubData(
		GL_ARRAY_BUFFER, 0,
		sizeof(transformed_verts),
		transformed_verts);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GlWindow::draw()
{
	// PAINT
	Matrix2DH translator = Matrix2DH::translate(ship_pos.x, ship_pos.y);
	Matrix2DH rotator = Matrix2DH::rotateZ(ship_orient);

	float aspect_ratio = static_cast<float>(width()) / height();
	Matrix2DH scale;

	if (aspect_ratio > 1)
	{
		scale = Matrix2DH::scale(1 / aspect_ratio, 1);
	}
	else
	{
		scale = Matrix2DH(1, aspect_ratio);
	}

	Matrix2DH op;
	{
		PROFILE("Matrix Multiplication");
		op = translator * scale * rotator;
	}

	{
		PROFILE("Vector Transformation");
		for (unsigned int i = 0; i < NUM_VERTS; ++i)
		{
			transformed_verts[i] = op * verts[i];
		}
	}
	doGl();
}

void GlWindow::paintGL()
{
	update();
	draw();
}

void GlWindow::rotateShip()
{
	const float angular_movement = 0.01f;
	if (GetAsyncKeyState(VK_RIGHT))
	{
		ship_orient -= angular_movement;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		ship_orient += angular_movement;
	}
}

void GlWindow::updateVelocity()
{
	const float acceleration = 0.4f * internal_clock.lastLapTime();

	Vector3D dir(-sin(ship_orient), cos(ship_orient));

	Vector3D up(0, 1);
	Matrix2DH op = Matrix2DH::rotateZ(ship_orient);
	Vector3D dir_acc = op * up;

	if (GetAsyncKeyState(VK_UP))
	{
		ship_vel += dir_acc * acceleration;
	}
}

void GlWindow::checkBoundaries()
{
	if (ship_pos.x < -1 || ship_pos.x > 1)
	{
		ship_vel.x *= -1;
	}
	if (ship_pos.y < -1 || ship_pos.y > 1)
	{
		ship_vel.y *= -1;
	}
}

bool GlWindow::initialize()
{
	bool ret = true;
	profiler.initialize("profiles.csv");
	ret &= internal_clock.initialize();
	return ret;
}

bool GlWindow::shutdown()
{
	bool ret = true;
	profiler.shutdown();
	ret &= internal_clock.shutdown();
	return ret;
}

void GlWindow::winupdate()
{
	repaint();
}
