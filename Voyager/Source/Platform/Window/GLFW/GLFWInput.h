#ifndef VE_GLFW_INPUT
#define VE_GLFW_INPUT

#include "Voyager/Core/Input.h"

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			class GLFWInput : public Core::Input
			{
			protected:
				virtual bool isKeyPressedImpl(int keycode) override;

				virtual bool isMouseButtonPressedImpl(int button) override;
				virtual std::pair<float, float> getMousePositionImpl() override;
				virtual float getMouseXImpl() override;
				virtual float getMouseYImpl() override;
			};
		}
	}
};

#endif