#ifndef VE_TIMESTEP_H
#define VE_TIMESTEP_H

namespace VE
{
	namespace Core 
	{
		class Timestep
		{
		public:
			Timestep(float time = 0.0f) : _time(time)
			{
			}

			operator float() const { return _time; }

			float getSeconds() const { return _time; }
			float getMilliSeconds() const { return _time * 1000.0f; }

		private:
			float _time;
		};
	}
};

#endif