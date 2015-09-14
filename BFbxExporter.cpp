#include "stdafx.h"
#include "BFbxExporter.h"
#include "BFbxManager.h"

namespace BoldarcManagedFbx
{
	BFbxExporter::BFbxExporter()
	{
	}
	void BFbxExporter::Create( BFbxManager^ inManager )
	{
		m_pFbxExporter = FbxExporter::Create( inManager->Get(), "Exporter" );
	}
}