//============================================================================
// # VOYAGER ENGINE #
// Name: Widget.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: Custom Qt widget based on Jamie King's tutorials.
//============================================================================

#ifndef VE_GRAPHICS_WIDGET_H
#define VE_GRAPHICS_WIDGET_H

#include <QtWidgets/qwidget.h>
#include <Graphics/Datatypes/Model.h>

#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	class DebugSlider;
	class GLWindow;

	class DECLDIR_R Widget : public QWidget
	{
		Q_OBJECT
	public:
		Widget(void);
		~Widget(void);

	private slots:
		void sliderValueChanged();

	private:
		DebugSlider* _light_x_slider;
		DebugSlider* _light_y_slider;
		DebugSlider* _light_z_slider;

		GLWindow* _gl_window;

		Model _model;
	};
}

#endif