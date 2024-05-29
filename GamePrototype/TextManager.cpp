#include "pch.h"
#include "TextManager.h"

#include "Texture.h"

TextManager::TextManager(const std::string& alphabet, const std::string& filePath)
	: m_Alphabet(alphabet)
{
	m_TextTexturePtr = new Texture(alphabet, filePath, 30, Color4f(0.f, 0.f, 0.f, 1.f));
}

TextManager::~TextManager( )
{
	delete m_TextTexturePtr;
}
void TextManager::Draw(Point2f position, const std::string& text ) const
{
	if (m_TextTexturePtr != nullptr)
	{
		for (char character : text)
		{
			if (character != ' ')
			{
				glPushMatrix();
					glTranslatef(position.x, position.y, 0.f);
					m_TextTexturePtr->Draw(Point2f(), GetCharacterSourceRect(character));
				glPopMatrix();
			}
			position.x += m_TextTexturePtr->GetWidth() / float(m_Alphabet.size());
		}
	}
}
Rectf TextManager::GetCharacterSourceRect(char character ) const
{
	for (int indexChar { 0 }; indexChar < m_Alphabet.size(); ++indexChar)
	{
		if (m_Alphabet[indexChar] == character)
		{
			return Rectf(indexChar * m_TextTexturePtr->GetWidth() / float(m_Alphabet.size()), 0.f,
				         m_TextTexturePtr->GetWidth()/ float(m_Alphabet.size()),  m_TextTexturePtr->GetHeight());
		}
	}
	return Rectf(-1.f, -1.f, -1.f, -1.f);
}
