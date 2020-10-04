#ifndef VE_TIMESTEP_H
#define VE_TIMESTEP_H

namespace VE
{
	namespace Core 
	{
		class Timestep
		{
		public:
			Timestep(double time = 0.0) : _time(time)
			{
			}

			operator double() const { return _time; }

			double toSeconds() const { return _time / 1000.0; }
			float toSecondsFloat() const { return static_cast<float>(_time) / 1000.0f; }

		private:
			double _time;
		};
	}
};

#endif