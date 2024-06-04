#pragma once
#include <vector>
#include "Collectible.h"
class Thief;
class CollectiblesManager
{

public:
	void Add( Collectible* collectiblePtr);
	void Draw() const;

	void Update(Thief* thiefPtr) const;
	
	void DeleteCollectible( const Collectible* collectiblePtr);
	void DeleteCollectibles();

	void ResetCollectibles();

	static int GetCollectedCollectiblesCount();
	std::vector<Collectible*>* GetArray( );
private:
	std::vector<Collectible*> m_CollectiblesArray;
	static int m_CollectedCollectiblesCount;
};

