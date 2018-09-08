//============================================================================
// # VOYAGER ENGINE #
// Name: DebugSlider.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: Custom Qt slider based on Jamie King's tutorials.
//============================================================================

#ifndef VE_GRAPHICS_DEBUGSLIDER_H
#define VE_GRAPHICS_DEBUGSLIDER_H

#include <QtWidgets/qwidget.h>
class QSlider;
class QLabel;

#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	class DECLDIR_R DebugSlider : public QWidget
	{
		Q_OBJECT

	public:
		DebugSlider(float value = 0.0f, float min = -1.0f, float max = 10.0f, bool text_left_align = false, float granularity = 40.0);
		float value() const;
		void setValue(float new_value);

	private slots:
		void sliderValueChanged();

	signals:
		void valueChanged(float new_value);

	private:
		QSlider* _slider;
		QLabel* _label;
		float _slider_granularity;
		float _min;
		float _max;
	};
}

#endif
