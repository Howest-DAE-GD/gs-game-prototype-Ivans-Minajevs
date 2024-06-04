#include "pch.h"
#include "Game.h"
#include <iostream>
#include <utils.h>
#include <SVGParser.h>
#include "Camera.h"
#include "Collectible.h"
#include "CollectiblesManager.h"
#include <algorithm>
#include "TextManager.h"
#include "EnemiesManager.h"
#include "Enemy.h"
using namespace std;
Game::Game( const Window& window ) 
	:BaseGame{ window }, m_CollectibleManagerPtr(nullptr)
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_CollectibleManagerPtr = new CollectiblesManager();

	m_EnemiesManagerPtr = new EnemiesManager();
	m_Camera = new Camera(GetViewPort().width, GetViewPort().height);

	m_ThiefPtr = new Thief(Point2f(450.f, 40.f));
	SVGParser::GetVerticesFromSvgFile("maze_10x10.svg", m_MazeMapVertices);
	for (std::vector<Point2f>& segment : m_MazeMapVertices)
	{
		for (Point2f& point : segment)
		{
			point.x = int(point.x) * m_SCALE;
			
			point.y = int(point.y) * m_SCALE;
			std::cout << point.x << " " << point.y;
		}
	}
	
	m_CollectibleManagerPtr->Add(new Collectible(Point2f(700.f, 40.f)));
	m_CollectibleManagerPtr->Add(new Collectible(Point2f(700.f, 750.f)));
	m_CollectibleManagerPtr->Add(new Collectible(Point2f(250.f, 350.f)));
	m_CollectibleManagerPtr->Add(new Collectible(Point2f(400.f, 355.f)));
	m_CollectibleManagerPtr->Add(new Collectible(Point2f(40.f, 80.f)));

	m_EnemiesManagerPtr->Add(new Enemy(Point2f(40.f, 80.f)));
	m_EnemiesManagerPtr->Add(new Enemy(Point2f(250.f, 350.f)));
	m_EnemiesManagerPtr->Add(new Enemy(Point2f(50.f, 750.f)));
	m_EnemiesManagerPtr->Add(new Enemy(Point2f(700.f, 40.f)));
	
	m_TextManagerPtr = new TextManager(m_Alphabet, "game_font.ttf");
}
/*void Game::GenerateMazeRecursive(int x, int y)
{
	vector<MazePoint> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	random_shuffle(directions.begin(), directions.end());

	for (auto direction : directions) {
		int newX = x + direction.x * 2;
		int newY = y + direction.y * 2;

		if (newX >= 0 && newX < m_ROWS && newY >= 0 && newY < m_COLS && !m_Maze[newX][newY]) {
			m_Maze[newX][newY] = true;
			m_Maze[x + direction.x][y + direction.y] = true;
			GenerateMazeRecursive(newX, newY);
		}
	}
}*/

void Game::Cleanup( )
{
	delete m_ThiefPtr;
	m_ThiefPtr = nullptr;

	delete m_Camera;
	m_Camera = nullptr;

	m_CollectibleManagerPtr->DeleteCollectibles();
	
	delete m_CollectibleManagerPtr;
	m_CollectibleManagerPtr = nullptr;

	delete m_TextManagerPtr;
	delete m_EnemiesManagerPtr;
}

void Game::Update( float elapsedSec )
{
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	m_ThiefPtr->Update(elapsedSec, pStates, m_MazeMapVertices);
	m_EnemiesManagerPtr->Update(m_MazeMapVertices, elapsedSec, m_ThiefPtr, m_CollectibleManagerPtr);
	m_CollectibleManagerPtr->Update(m_ThiefPtr);
}

void Game::Draw( ) const
{

	m_Camera->Aim(GetViewPort().width, m_HEIGHT * m_SCALE + 100.f, m_ThiefPtr->GetPosition());

	ClearBackground( );

	glPushMatrix();
	{
		for (int inx { 0 }; inx < int(m_MazeMapVertices.size()); ++inx)
		{
			if (inx >= 4)
			{
				if (CollectiblesManager::GetCollectedCollectiblesCount() < 5)
				{
					utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
				}
				else
				{
					utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
				}
				
				utils::FillPolygon(m_MazeMapVertices[inx]);
			}
			else
			{
				utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
				utils::DrawPolygon(m_MazeMapVertices[inx], true, 2.f);
			}
		}
	}
	glPopMatrix();
	m_CollectibleManagerPtr->Draw();
	m_ThiefPtr->Draw();

	m_EnemiesManagerPtr->Draw();
	
	m_Camera->Reset();
	
	utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	utils::FillRect(GetViewPort().width - 450.f, GetViewPort().height - 100.f, 450.f, 100.f);
	m_TextManagerPtr->Draw(Point2f(GetViewPort().width - 400.f, GetViewPort().height - 60.f), "COLLECTED:" + std::to_string(CollectiblesManager::GetCollectedCollectiblesCount()) +
		"/5");
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.85f, 0.85f, 0.85f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
