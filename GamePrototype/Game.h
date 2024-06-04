#pragma once
#include "BaseGame.h"
#include <vector>
#include "Thief.h"
class EnemiesManager;
class TextManager;
class Camera;
class CollectiblesManager;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

	struct MazePoint
	{
		int x;
		int y;
	};

	float m_SCALE{ 5.f };

	const float m_WIDTH{ 162.f };
	const float m_HEIGHT{ 162.f };
	//const int m_CELL_SIZE = 20;
	//const int m_ROWS{ m_HEIGHT / m_CELL_SIZE };
	//const int m_COLS{ m_WIDTH / m_CELL_SIZE };
private:
	std::vector<std::vector<bool>> m_Maze;
	Thief* m_ThiefPtr;
	Camera* m_Camera;
	CollectiblesManager* m_CollectibleManagerPtr;
	EnemiesManager* m_EnemiesManagerPtr;
	std::vector<std::vector<Point2f>> m_MazeMapVertices;
	std::string m_Alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/:"};
	TextManager* m_TextManagerPtr;
	// FUNCTIONS
	void Initialize();
	//void GenerateMaze();
	//void GenerateMazeRecursive(int x, int y);
	void Cleanup( );
	void ClearBackground( ) const;
};