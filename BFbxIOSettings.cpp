#include "stdafx.h"
#include "BFbxIOSettings.h"
#include "BFbxManager.h"

namespace BoldarcManagedFbx
{
	void BFbxIOSettings::Create( BFbxManager^ inManager)
	{
		m_pFbxIOSettings = FbxIOSettings::Create( inManager->Get(), IOSROOT );
	}
}