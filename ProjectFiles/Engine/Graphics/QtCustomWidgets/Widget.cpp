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
		QVBoxLayout* main_layout;
		setLayout(main_layout = new QVBoxLayout);

		QVBoxLayout* controls_layout;
		main_layout->addLayout(controls_layout = new QVBoxLayout);
		main_layout->addWidget(_gl_window = new GLWindow(&_model));

		QHBoxLayout* light_position_layout;
		controls_layout->addLayout(light_position_layout = new QHBoxLayout);
		light_position_layout->addWidget(_light_x_slider = new DebugSlider);
		light_position_layout->addWidget(_light_y_slider = new DebugSlider(3, 0));
		light_position_layout->addWidget(_light_z_slider = new DebugSlider);

		connect(_light_x_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
		connect(_light_y_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
		connect(_light_z_slider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));

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
		_gl_window->repaint();
	}
}
