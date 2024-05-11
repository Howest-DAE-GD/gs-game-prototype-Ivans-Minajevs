#include "pch.h"
#include "Game.h"
#include <iostream>
#include <utils.h>
#include <SVGParser.h>
#include "Camera.h"
#include <algorithm>
using namespace std;
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{

	m_Maze.resize(m_ROWS);
	for (int index{ 0 }; index < m_ROWS; ++index)
	{
		m_Maze[index].resize(m_COLS, false);
	}
	GenerateMaze();

	m_Camera = new Camera(GetViewPort().width, GetViewPort().height);

	m_ThiefPtr = new Thief(Point2f(450.f, 20.f));
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
}

void Game::GenerateMaze()
{
	MazePoint startCoord{ 0, 0 }; // Starting point at top-left corner
	MazePoint endCoord{ m_ROWS - 1, m_COLS - 1 }; // Ending point at bottom-right corner

	// Mark the starting and ending points as visited
	m_Maze[startCoord.x][startCoord.y] = true;
	m_Maze[endCoord.x][endCoord.y] = true;

	GenerateMazeRecursive(int(startCoord.x), int(startCoord.y));
	//while (true) {
	//	bool done = true;
	//	for (int i = 1; i < m_ROWS - 1; i += 2) {
	//		for (int j = 1; j < m_COLS - 1; j += 2) {
	//			if (!m_Maze[i][j]) {
	//				done = false;
	//				int dir = rand() % 4;
	//				int newX = i + (dir == 0) - (dir == 1);
	//				int newY = j + (dir == 2) - (dir == 3);
	//				if (newX >= 0 && newX < m_ROWS && newY >= 0 && newY < m_COLS && !m_Maze[newX][newY]) {
	//					m_Maze[newX][newY] = true;
	//					m_Maze[i + (newX - i) / 2][j + (newY - j) / 2] = true;
	//				}
	//			}
	//		}
	//	}
	//	if (done) break;
	//}
	//srand(time(NULL));
	//int startX = rand() % m_ROWS;
	//int startY = rand() % m_COLS;
	//m_Maze[startX][startY] = true;
	//
	//while (true) {
	//	bool done = true;
	//	for (int i = 1; i < m_ROWS - 1; i += 2) {
	//		for (int j = 1; j < m_COLS - 1; j += 2) {
	//			if (!m_Maze[i][j]) {
	//				done = false;
	//				int dir = rand() % 4;
	//				int newX = i + (dir == 0) - (dir == 1);
	//				int newY = j + (dir == 2) - (dir == 3);
	//				if (newX >= 0 && newX < m_ROWS && newY >= 0 && newY < m_COLS && !m_Maze[newX][newY]) {
	//					m_Maze[newX][newY] = true;
	//					m_Maze[static_cast<std::vector<std::vector<bool, std::allocator<bool>>, std::allocator<std::vector<bool, std::allocator<bool>>>>::size_type>(i) + (newX - i) / 2]
	//						[static_cast<std::vector<bool, std::allocator<bool>>::size_type>(j) + (newY - j) / 2] = true;
	//				}
	//			}
	//		}
	//	}
	//	if (done)
	//	{
	//		break;
	//	}
	//}
}

void Game::GenerateMazeRecursive(int x, int y)
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
}

void Game::Cleanup( )
{
	delete m_ThiefPtr;
	m_ThiefPtr = nullptr;

	delete m_Camera;
	m_Camera = nullptr;
}

void Game::Update( float elapsedSec )
{
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	m_ThiefPtr->Update(elapsedSec, pStates, m_MazeMapVertices);
}

void Game::Draw( ) const
{
	
	m_Camera->Aim(GetViewPort().width, m_HEIGHT * m_SCALE + 100.f, m_ThiefPtr->GetPosition());

	ClearBackground( );

	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	//glLineWidth(3.0);
	//glBegin(GL_LINES);
	//for (int i = 0; i < m_ROWS ; ++i) {
	//	for (int j = 0; j < m_COLS ; ++j) {
	//		if (!m_Maze[i][j]) {
	//			if (j>0 && m_Maze[i][j - 1]) { // Left wall
	//				glVertex2i(j * m_CELL_SIZE, i * m_CELL_SIZE);
	//				glVertex2i(j * m_CELL_SIZE, (i + 1) * m_CELL_SIZE);
	//			}
	//			if (j < m_COLS - 1 && m_Maze[i][j + 1]) { // Right wall
	//				glVertex2i((j + 1) * m_CELL_SIZE, i * m_CELL_SIZE);
	//				glVertex2i((j + 1) * m_CELL_SIZE, (i + 1) * m_CELL_SIZE);
	//			}
	//			if ( i > 0 && m_Maze[i - 1][j]) { // Top wall
	//				glVertex2i(j * m_CELL_SIZE, (i ) * m_CELL_SIZE);
	//				glVertex2i((j + 1) * m_CELL_SIZE, (i) * m_CELL_SIZE);
	//			}
	//			if ( i < m_ROWS - 1  && m_Maze[i + 1][j]) { // Bottom wall
	//				glVertex2i(j * m_CELL_SIZE, (i + 1) * m_CELL_SIZE);
	//				glVertex2i((j + 1) * m_CELL_SIZE, (i + 1) * m_CELL_SIZE);
	//			}
	//		}
	//	}
	//}
	//glEnd();
	//glFlush();

	glPushMatrix();
	{
		//glTranslatef(250.f, 100.f, 0.f);
		for (std::vector<Point2f> segment : m_MazeMapVertices)
		{
			utils::DrawPolygon(segment, true, 2.f);
		}
	}
	glPopMatrix();
	m_ThiefPtr->Draw();

	m_Camera->Reset();
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
