// BoldarcManagedFbx.h

#pragma once

using namespace System;

namespace BoldarcManagedFbx 
{
	ref class BFbxIOSettings;
	public ref class BFbxManager
	{
	private:
		FbxManager* m_pFbxManager;

	public:
		void Create()
		{
			m_pFbxManager = FbxManager::Create();
		}
		void Destroy()
		{
			if ( m_pFbxManager != NULL )
				m_pFbxManager->Destroy();
		}
		void SetIOSettings( BFbxIOSettings^ inSettings );

		FbxManager* Get()
		{
			return m_pFbxManager;
		}
	};
}
