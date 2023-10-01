#pragma once

namespace Gonk {

	class Timestep 
	{
	public:
		Timestep(float time) : m_Time(time) {}

		operator float() { return m_Time; }

		Timestep& operator+=(const Timestep& other)
		{
			m_Time += other.m_Time;
			return *this;
		}

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000; }

	private:
		float m_Time;
	};

}
