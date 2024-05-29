#pragma once

class Texture;
class TextManager final
{
public:
	TextManager(const std::string& alphabet, const std::string& filePath);
	~TextManager( );
	
	void Draw(Point2f position, const std::string& text) const;
	
	//const int m_LETTERS_AMOUNT { 36 };
private:
	Texture* m_TextTexturePtr;
	std::string m_Alphabet;
	Rectf GetCharacterSourceRect(char character) const;
};
