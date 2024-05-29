#pragma once
#include <vector>

#include "CollectiblesManager.h"
class Thief
{
public:
	Thief(Point2f pos);
	void Draw() const;
	void Update(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<Point2f>> &vertices);
	Point2f GetPosition() const;
	Circlef GetCircle() const;
	const float m_RADIUS{ 15.f };
private:
	Point2f m_Velocity;
	Circlef m_Circle;
	Color4f m_Color;
	Point2f m_Position;
	bool m_IsSpotted;
};

