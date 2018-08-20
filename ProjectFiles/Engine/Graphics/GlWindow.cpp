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
#include <QtCore/qdebug.h>
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
	Vector3D shipVerts[] =
	{
		Vector3D(+0.0f, 0.14142135623f, 1.0f),
		Vector3D(-0.1f, -0.1f, 1.0f),
		Vector3D(+0.1f, -0.1f, 1.0f),
	};

	Vector3D boundaryVerts[] =
	{
		Vector3D(+0.0f, +1.0f, +0.0f),
		Vector3D(-1.0f, +0.0f, +0.0f),
		Vector3D(+0.0f, -1.0f, +0.0f),
		Vector3D(+1.0f, +0.0f, +0.0f),
	};

	GLushort boundary_indices[] = { 0, 1, 1, 2, 2, 3, 3, 0 };

	// 6 * float (4 bytes) = 24 bytes 
	// (*shipVerts) = size of first element in array. 1 2D Vector = 2 floats = 8 bytes
	// NUM_SHIP_VERTS = 24 / 8 = 3
	const unsigned int NUM_SHIP_VERTS = sizeof(shipVerts) / sizeof(*shipVerts);
	const unsigned int NUM_BOUNDARY_VERTS = sizeof(boundaryVerts) / sizeof(*boundaryVerts);
	GLuint ship_buf_ID;
	GLuint boundary_buf_ID;
	GLuint boundary_index_buf_ID;

	Vector3D transformed_verts[NUM_SHIP_VERTS];
	Vector3D ship_pos;
	Vector3D old_ship_pos;
	Vector3D ship_vel;
	float ship_orient = 0.0f;
	Clock internal_clock;
}

void GlWindow::initializeGL()
{
	// Catch error code if glew could not be initialized properly.
	GLenum error_code = glewInit();
	assert(error_code == 0);

	glEnableVertexAttribArray(0);

	// 1. Specifies the number of buffer object names to be generated.
	// 2. Specifies an array in which the generated buffer object names are stored. 
	glGenBuffers(1, &ship_buf_ID);

	// Bind a named buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, ship_buf_ID);

	// Set NULL, we provide the size ourselves later.
	glBufferData(GL_ARRAY_BUFFER, sizeof(shipVerts), NULL, GL_DYNAMIC_DRAW);

	connect(&timer, SIGNAL(timeout()), this, SLOT(_winupdate()));

	glGenBuffers(1, &boundary_buf_ID);
	glBindBuffer(GL_ARRAY_BUFFER, boundary_buf_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundaryVerts), boundaryVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &boundary_index_buf_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundary_index_buf_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boundary_indices), boundary_indices, GL_STATIC_DRAW);

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
	old_ship_pos = ship_pos;
	ship_pos += ship_vel * internal_clock.lastLapTime();
	handleBoundaries();
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

	glBindBuffer(GL_ARRAY_BUFFER, ship_buf_ID);
	glBufferSubData(
	GL_ARRAY_BUFFER, 
	0,
	sizeof(transformed_verts),
	transformed_verts);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, boundary_buf_ID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, 0);
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
		scale = Matrix2DH::scale(1, aspect_ratio);
	}

	Matrix2DH op;
	{
		PROFILE("Matrix Multiplication");
		op = translator * scale * rotator;
	}

	{
		PROFILE("Vector Transformation");
		for (unsigned int i = 0; i < NUM_SHIP_VERTS; ++i)
		{
			transformed_verts[i] = op * shipVerts[i];
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

void GlWindow::handleBoundaries()
{
	bool coll = false;
	for (uint i = 0; i < NUM_BOUNDARY_VERTS; i++)
	{
		const Vector3D& first = boundaryVerts[i];
		const Vector3D& second = boundaryVerts[(i + 1) % NUM_BOUNDARY_VERTS];

		Vector3D wall = second - first;
		Vector3D normal = wall.perpCCwXy().normalized();
		Vector3D respective_ship_pos = ship_pos - first;
		float dotResult = normal.dot(respective_ship_pos);
		coll |= (dotResult < 0);

		if (dotResult < 0)
		{
			ship_vel = ship_vel - 2 * ship_vel.dot(normal) * normal;
			ship_pos = old_ship_pos;
		}
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
