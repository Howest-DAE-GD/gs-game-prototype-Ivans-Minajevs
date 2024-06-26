#include "pch.h"
#include "CollectiblesManager.h"

#include "Thief.h"
#include "utils.h"
int CollectiblesManager::m_CollectedCollectiblesCount { 0 };

void CollectiblesManager::Add(Collectible* collectiblePtr)
{
	m_CollectiblesArray.push_back(collectiblePtr);
}

void CollectiblesManager::Draw() const
{
	for (const Collectible* collectiblePtr : m_CollectiblesArray)
	{
		
		if (collectiblePtr != nullptr)
		{
			if (!collectiblePtr->GetIsCollected())
			{
				collectiblePtr->Draw();
			}
		}
	}
}
void CollectiblesManager::Update(Thief* thiefPtr) const
{
	m_CollectedCollectiblesCount = 0;
	for (Collectible* collectiblePtr : m_CollectiblesArray)
	{
		if (collectiblePtr != nullptr)
		{
			if (utils::IsOverlapping(collectiblePtr->GetRect(), thiefPtr->GetCircle()))
			{
				if (!collectiblePtr->GetIsCollected())
				{
					collectiblePtr->SetIsCollected(true);
				}
			}
			if (collectiblePtr->GetIsCollected())
			{
				m_CollectedCollectiblesCount++;
			}
		}
	}
}

void CollectiblesManager::DeleteCollectible( const Collectible* collectiblePtr)
{
	for (Collectible*& collectible : m_CollectiblesArray)
	{
		if (collectible != nullptr)
		{
			if (collectible == collectiblePtr)
			{
				delete collectible;
				collectible = nullptr;
			}
		}
	}
}

void CollectiblesManager::DeleteCollectibles()
{
	for (Collectible*& collectible : m_CollectiblesArray)
	{
		if (collectible != nullptr)
		{
			delete collectible;
			collectible = nullptr;
		}
	}
}
void CollectiblesManager::ResetCollectibles( )
{
	for (Collectible*& collectible : m_CollectiblesArray)
	{
		if (collectible != nullptr)
		{
			collectible->SetIsCollected(false);
		}
	}
}

int CollectiblesManager::GetCollectedCollectiblesCount( )
{
	return m_CollectedCollectiblesCount;
}

std::vector<Collectible*> * CollectiblesManager::GetArray( )
{
	return &m_CollectiblesArray;
}
