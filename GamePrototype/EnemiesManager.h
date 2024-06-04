#pragma once
#include "Thief.h"
#include "vector"

class CollectiblesManager;
class Enemy;
class EnemiesManager
{
public:
	void Update(const std::vector<std::vector<Point2f>>& mapVertices, float elapsedSec,  Thief* thiefPtr, CollectiblesManager* collectiblesManagerPtr);
	void Draw() const;

	void Add(Enemy* enemyPtr);

	void DeleteEnemies();

	std::vector<Enemy*>& GetEnemiesArray();

	int GetScore() const;

private:
	int m_Score { 0 };
	std::vector<Enemy*> m_EnemiesPtrArr;

	void AddScore(int score);
};
