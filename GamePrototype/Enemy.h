#pragma once
#include "vector"
#include "Vector2f.h"
class Enemy
{
public:
	Enemy(Point2f pos);
	void Draw() const;
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>> &vertices);

	std::vector<Point2f> GetSpotZone() const;
	
	Point2f GetPosition() const;
	Circlef GetCircle() const;
	const float m_RADIUS{ 15.f };
	const float m_SPOT_ZONE_RADIUS{ 40.f };
private:
	Point2f m_Velocity;
	int m_RotationAngle;
	Circlef m_Circle;
	Color4f m_Color;
	Point2f m_Position;
	Circlef m_SpotZoneRect;
	int m_SpotZoneAngle;

	Vector2f m_Direction;
};
