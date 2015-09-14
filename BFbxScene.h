#pragma once

namespace BoldarcManagedFbx
{
	ref class BFbxManager;
	public ref class BFbxScene
	{
	private:
		FbxScene* m_pFbxScene;
	public:
		BFbxScene();
		void Create( BFbxManager^ inManager );
	};
}
