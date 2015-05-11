#ifndef _DIMENSIONS_H
#define _DIMENSIONS_H

#include <glm\glm.hpp>

using glm::vec2;

class Dimensions
{
public:
	static Dimensions& Instance()
	{
		static Dimensions instance;
		return instance;
	}

	void SetWindowDimensions(int a_Width, int a_Height)
	{
		m_WindowDimensions.x = (float)a_Width;
		m_WindowDimensions.y = (float)a_Height;
	}

	void SetWorldDimensions(int a_Width, int a_Height)
	{
		m_WorldDimensions.x = (float)a_Width;
		m_WorldDimensions.y = (float)a_Height;
	}

	vec2 GetWindowDimensions()
	{
		return m_WindowDimensions;
	}

	vec2 GetWorldDimensions()
	{
		return m_WorldDimensions;
	}

private:
	Dimensions()
	{
		m_WindowDimensions = vec2(1280, 720);
		m_WorldDimensions = vec2(3600, 2400);
	}

	Dimensions(Dimensions const&) = delete;
	void operator=(Dimensions const&) = delete;

	vec2 m_WindowDimensions;
	vec2 m_WorldDimensions;
};

#endif