#pragma once

namespace BoldarcManagedFbx
{
	ref class BFbxManager;
	public ref class BFbxExporter
	{
	private:
		FbxExporter* m_pFbxExporter;
	public:
		BFbxExporter();
		void Create( BFbxManager^ inManager );
	};
}
