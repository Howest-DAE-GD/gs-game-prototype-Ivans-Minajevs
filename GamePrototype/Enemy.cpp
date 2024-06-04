#include "pch.h"
#include "Enemy.h"

#include "utils.h"

Enemy::Enemy( Point2f pos )
{
	m_Velocity = Point2f( 50.f, 50.f);
	m_Position = pos;
	m_RotationAngle = 0;
	m_Circle = Circlef(m_Position, m_RADIUS);
	m_Color = Color4f(1.f, 0.f, 0.f, 1.f);
	m_SpotZoneRect = Circlef(m_Position, float(m_RotationAngle));
	m_SpotZoneAngle = 50;

	m_Direction = Vector2f(1.f, 0.f);
}

void Enemy::Draw( ) const
{
	utils::SetColor(m_Color);

	utils::FillEllipse(m_Position, m_Circle.radius, m_Circle.radius);
	for (int angle { m_RotationAngle }; angle < m_RotationAngle + m_SpotZoneAngle; ++angle )
	{
		utils::DrawLine(m_Position, Point2f(m_Position.x + m_SPOT_ZONE_RADIUS * cosf(float(angle) * utils::g_Pi/ 180.f ) ,
													m_Position.y + m_SPOT_ZONE_RADIUS * sinf(float(angle) * utils::g_Pi/ 180.f)), 2);
	}

	utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
}
void Enemy::Update( float elapsedSec, const std::vector<std::vector<Point2f>>& vertices )
{
	m_RotationAngle++;
	m_Position.x += m_Direction.x * m_Velocity.x * elapsedSec;
	m_Position.y += m_Direction.y * m_Velocity.y * elapsedSec;

	utils::HitInfo hitInfo;
	for (const std::vector<Point2f>& segment : vertices)
	{
		if (utils::Raycast(segment, Point2f(m_Position.x, m_Position.y),
										Point2f(m_Position.x + m_Direction.x *  40.f, m_Position.y + m_Direction.y *  40.f), hitInfo))
		{
			int randXPos { rand() % 3 - 1 };
			m_Direction.x = float(randXPos);
			if (randXPos != 0)
			{
				m_Direction.y = 0;
			}
			else
			{
				int randYPos;
				do
				{
					randYPos = rand() % 3 - 1 ;
				}
				while (randYPos == 0);
				m_Direction.y = float(randYPos);
			}
			
		}
	}
}
std::vector<Point2f> Enemy::GetSpotZone( ) const
{
	std::vector<Point2f> m_SpotZoneVectorsArray;
	for (int angle { m_RotationAngle }; angle < m_RotationAngle + m_SpotZoneAngle; ++angle )
	{
		m_SpotZoneVectorsArray.push_back(Point2f(m_Position.x + m_SPOT_ZONE_RADIUS * cosf(float(angle) * utils::g_Pi/ 180.f ) ,
													m_Position.y + m_SPOT_ZONE_RADIUS * sinf(float(angle) * utils::g_Pi/ 180.f)));
	}
	return m_SpotZoneVectorsArray;
}

Point2f Enemy::GetPosition( ) const
{
	return m_Position;
}

Circlef Enemy::GetCircle( ) const
{
	return m_Circle;
}
