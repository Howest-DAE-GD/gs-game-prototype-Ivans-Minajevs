#include "pch.h"
#include "Thief.h"
#include <utils.h>

Thief::Thief(Point2f pos) : m_Position(pos)
{
	m_Velocity = Point2f(0.f, 0.f);
	m_Circle = Circlef(m_Position, m_RADIUS);
	m_IsSpotted = false;
	m_Color = Color4f(0.5f, 0.5f, 0.f, 1.f);
}

void Thief::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Position, m_RADIUS, m_RADIUS);
}

void Thief::Update(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<Point2f>> &vertices)
{
	m_Velocity.x = 125.f;
	m_Velocity.y = 125.f;
	
	//const Uint8* pStates = SDL_GetKeyboardState(nullptr);


	utils::HitInfo hitInfo;
	
	for (const std::vector<Point2f>& segment : vertices)
	{
		if (utils::Raycast(segment, Point2f(m_Position.x - m_RADIUS, m_Position.y), Point2f(m_Position.x + m_RADIUS, m_Position.y), hitInfo))
		{
			//m_Velocity.x = 0;
			if (m_Position.x > hitInfo.intersectPoint.x)
			{
				m_Position.x = hitInfo.intersectPoint.x + m_RADIUS;
			} 
			else
			{
				m_Position.x = hitInfo.intersectPoint.x - m_RADIUS;
			}
		}
		if (utils::Raycast(segment, Point2f(m_Position.x, m_Position.y - m_RADIUS), Point2f(m_Position.x, m_Position.y + m_RADIUS), hitInfo))
		{
			if (m_Position.y > hitInfo.intersectPoint.y)
			{
				m_Position.y = hitInfo.intersectPoint.y + m_RADIUS;
			}
			else
			{
				m_Position.y = hitInfo.intersectPoint.y - m_RADIUS;
			}
		}
	}

	if (pStates[SDL_SCANCODE_W]) m_Position.y += m_Velocity.y * elapsedSec;
	if (pStates[SDL_SCANCODE_A]) m_Position.x -= m_Velocity.x * elapsedSec;
	if (pStates[SDL_SCANCODE_S]) m_Position.y -= m_Velocity.y * elapsedSec;
	if (pStates[SDL_SCANCODE_D]) m_Position.x += m_Velocity.x * elapsedSec;

}

Point2f Thief::GetPosition()
{
	return m_Position;
}

