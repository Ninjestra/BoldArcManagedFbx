#pragma once

namespace BoldarcManagedFbx
{
	ref class BFbxManager;
	public ref class BFbxIOSettings
	{
	private:
		FbxIOSettings* m_pFbxIOSettings;
	public:
		void Create( BFbxManager^ inManager);
		
		void Destroy()
		{
			if ( m_pFbxIOSettings != NULL )
				m_pFbxIOSettings->Destroy();
		}
		FbxIOSettings* Get()
		{
			return m_pFbxIOSettings;
		}
	};
}


