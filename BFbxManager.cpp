// This is the main DLL file.

#include "stdafx.h"
#include "BFbxManager.h"
#include "BFbxIOSettings.h"

namespace BoldarcManagedFbx
{
	void BFbxManager::SetIOSettings( BFbxIOSettings^ inSettings )
	{
		m_pFbxManager->SetIOSettings( inSettings->Get() );
	}
}