#pragma once
class Collectible
{
public:
	Collectible(Point2f pos);
	

	void Draw() const;
	void SetIsCollected();

	bool GetIsCollected() const;
	Rectf GetRect() const;


private:
	Rectf m_RectTexture;
	Point2f m_Position;
	bool m_IsCollected;

};

