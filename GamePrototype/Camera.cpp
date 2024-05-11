#include "pch.h"
#include "Camera.h"
Camera::Camera(float screenWidth, float screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
}

void Camera::Aim(float levelW, float levelH, Point2f trackCenter)
{
	float cameraY{ trackCenter.y - m_ScreenHeight / 2.f };

	if (cameraY < 0) cameraY = 0;
	else if (cameraY > levelH - m_ScreenHeight) cameraY = levelH - m_ScreenHeight;

	glPushMatrix();
	glTranslatef(0.f, -cameraY, 0.0f);

}

void Camera::Reset()
{
	glPopMatrix();
}