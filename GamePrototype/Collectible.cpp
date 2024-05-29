#include "pch.h"
#include "Collectible.h"
#include <utils.h>

Collectible::Collectible(Point2f pos) : m_Position(pos)
{
	m_IsCollected = false;
	m_RectTexture = Rectf(m_Position.x, m_Position.y, 15.f, 15.f);
}


void Collectible::Draw() const
{
	utils::SetColor(Color4f(0.f, 0.8f, 0.f, 1.f));
	utils::FillRect(m_RectTexture);
}

void Collectible::SetIsCollected()
{
	m_IsCollected = true;
}

bool Collectible::GetIsCollected() const
{
	return m_IsCollected;
}

Rectf Collectible::GetRect() const
{
	return m_RectTexture;
}
