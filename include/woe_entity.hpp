#pragma once

#include "sparkle.hpp"

struct Entity
{
	using ID = size_t;
	enum class Shape
	{
		Triangle,
		Square,
		Pentagon,
		Circle
	};

	ID id;
	Shape shape;
	spk::Vector2 position;
	spk::Vector2 velocity; // Expressed in unit / millisecond
	float rotation;
};