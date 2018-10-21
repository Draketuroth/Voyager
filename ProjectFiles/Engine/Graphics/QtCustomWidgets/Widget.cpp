//============================================================================
// # VOYAGER ENGINE #
// Name: Widget.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: Custom Qt widget based on Jamie King's tutorials.
//============================================================================

#include <QtWidgets/qboxlayout.h>
#include <QtCore/qdebug.h>

#include <Graphics/Window/GLWindow.h>
#include <Graphics/QtCustomWidgets/Widget.h>
#include <Graphics/QtCustomWidgets/DebugSlider.h>

namespace Graphics
{
	Widget::Widget(void)
	{
		this->setWindowTitle("Voyager by Fredrik Linde");

		QVBoxLayout* main_layout;
		setLayout(main_layout = new QVBoxLayout);

		_gl_window = std::make_unique<GLWindow>(&_model);

		QVBoxLayout* controls_layout;
		main_layout->addLayout(controls_layout = new QVBoxLayout);
		main_layout->addWidget(_gl_window.get());
		_gl_window->setFixedHeight(900);

		QHBoxLayout* light_position_layout;
		controls_layout->addLayout(light_position_layout = new QHBoxLayout);
		light_position_layout->addWidget(_light_x_slider = new DebugSlider(0.0f, -100.0f, 100.0f, true, 100.0f));
		light_position_layout->addWidget(_light_y_slider = new DebugSlider(3.0f, -100.0f, 100.0f, true, 100.0f));
		light_position_layout->addWidget(_light_z_slider = new DebugSlider(0.0f, -100.0f, 100.0f, true, 100.0f));
		light_position_layout->addWidget(_lerp_slider = new DebugSlider(0.0f, 0.0f, 1.0f, true, 40.0f));

		connect(_light_x_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
		connect(_light_y_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
		connect(_light_z_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
		connect(_lerp_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));

		sliderValueChanged();
	}
	Widget::~Widget(void)
	{

	}

	void Widget::sliderValueChanged()
	{
		_model.light_position.x = _light_x_slider->value();
		_model.light_position.y = _light_y_slider->value();
		_model.light_position.z = _light_z_slider->value();
		_model.lerp_value = _lerp_slider->value();
		_gl_window->repaint();
	}
}
