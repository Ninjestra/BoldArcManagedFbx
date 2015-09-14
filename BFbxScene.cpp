#include "stdafx.h"
#include "BFbxScene.h"
#include "BFbxManager.h"
namespace BoldarcManagedFbx
{
	BFbxScene::BFbxScene()
	{
	}
	void BFbxScene::Create( BFbxManager^ inManager )
	{
		m_pFbxScene = FbxScene::Create( inManager->Get(), "Scene" );
	}
}