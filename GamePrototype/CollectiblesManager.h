#pragma once
#include <vector>
#include "Collectible.h"
class CollectiblesManager
{

public:
	void Add( Collectible* collectiblePtr);
	void Draw() const;

	void Update();
	
	void DeleteCollectible( const Collectible* collectiblePtr);
	void DeleteCollectibles();


	static int GetCollectedCollectiblesCount();
	std::vector<Collectible*>* GetArray( );
private:
	std::vector<Collectible*> m_CollectiblesArray;
	static int m_CollectedCollectiblesCount;
};

