//============================================================================
// # VOYAGER ENGINE #
// Name: DebugSlider.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: Custom Qt slider based on Jamie King's tutorials.
//============================================================================

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qlabel.h>

#include <Graphics/QtCustomWidgets/DebugSlider.h>

namespace Graphics
{
	DebugSlider::DebugSlider(float value, float min, float max, bool text_left_align, float granularity)
	{
		QLayout* layout;

		_min = min;
		_max = max;

		_slider_granularity = granularity;
		setLayout(layout = text_left_align ? (QLayout*)new QHBoxLayout : new QVBoxLayout);
		layout->addWidget(_label = new QLabel);
		_label->setMinimumWidth(35);
		layout->addWidget(_slider = new QSlider);
		_label->setAlignment(Qt::AlignCenter);
		_slider->setOrientation(Qt::Horizontal);
		_slider->setMinimum(0);
		_slider->setMaximum(_slider_granularity);
		connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged()));
		setValue(value);
	}

	float DebugSlider::value() const
	{
		return _min + (_max - _min) * (_slider->value() / _slider_granularity);
	}

	void DebugSlider::setValue(float new_value)
	{
		float spot = (new_value - _min) / (_max - _min);
		_slider->setValue(spot * _slider_granularity);
	}

	void DebugSlider::sliderValueChanged()
	{
		_label->setText(QString::number(value()));
		emit valueChanged(value());
	}
}