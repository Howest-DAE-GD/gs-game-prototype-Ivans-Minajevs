#include "pch.h"
#include "EnemiesManager.h"

#include "CollectiblesManager.h"
#include "Enemy.h"
#include "utils.h"

void EnemiesManager::Update(const std::vector<std::vector<Point2f>>& mapVertices, float elapsedSec, Thief* thiefPtr,  CollectiblesManager* collectiblesManagerPtr)
{
	for (Enemy*& enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			enemyPtr->Update(elapsedSec, mapVertices);

			for (Point2f vectorEndPoint : enemyPtr->GetSpotZone())
			{
				if (utils::IsOverlapping(enemyPtr->GetPosition(), vectorEndPoint, thiefPtr->GetCircle()))
				{
					thiefPtr->ResetPosition();
					collectiblesManagerPtr->ResetCollectibles();
				}
			}
		}
	}
}

void EnemiesManager::Draw( ) const
{
	for (Enemy* enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			enemyPtr->Draw();
		}
	}
}

void EnemiesManager::Add( Enemy* enemyPtr )
{
	m_EnemiesPtrArr.push_back(enemyPtr);
}


void EnemiesManager::DeleteEnemies( )
{
	for (Enemy*& enemyPtr : m_EnemiesPtrArr)
	{
		if (enemyPtr != nullptr)
		{
			delete enemyPtr;
			enemyPtr = nullptr;
		}
	}
}

std::vector<Enemy*>& EnemiesManager::GetEnemiesArray( )
{
	return m_EnemiesPtrArr;
}

int EnemiesManager::GetScore( ) const
{
	return m_Score;
}

void EnemiesManager::AddScore(int score)
{
	m_Score += score;
}
