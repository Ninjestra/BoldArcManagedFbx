#include "stdafx.h"
#include "FileExporter.h"

namespace BoldarcManagedFbx
{
	FileExporter::FileExporter()
	{
	}
	void FileExporter::ExportFile()
	{
		if ( m_pFbxManager == nullptr )
			m_pFbxManager = FbxManager::Create();

		FbxScene* _pScene = FbxScene::Create( m_pFbxManager, "RevitScene" );

		FbxNode* _pNode = FbxNode::Create( _pScene, "MeshNode" );

		FbxMesh* _pMesh = FbxMesh::Create( _pScene, "TestMesh" );

		if ( m_lControlPoints != nullptr && m_lIndices != nullptr )
		{
			_pMesh->InitControlPoints( m_lControlPoints->Count );
			FbxVector4* _pControlPoints = _pMesh->GetControlPoints();
			for ( int i = 0; i < m_lControlPoints->Count; i++ )
			{
				_pControlPoints[i] = m_lControlPoints[i].ToFbxVector4();
			}

			_pMesh->ReservePolygonVertexCount( m_lIndices->Count );
			int* _pIndices = _pMesh->GetPolygonVertices();
			for ( int i = 0; i < m_lIndices->Count; i++ )
			{
				_pIndices[i] = m_lIndices[i];
			}

			_pNode->AddNodeAttribute( _pMesh );
			_pScene->GetRootNode()->AddChild( _pNode );

			FbxExporter* _pExporter = FbxExporter::Create( m_pFbxManager, "Exporter" );
			_pExporter->Initialize( "D:\\Joel\\FBX\\exporter_test.fbx", -1, m_pFbxManager->GetIOSettings());
			_pExporter->Export( _pScene );
			_pExporter->Destroy();
		}
	}
	void FileExporter::SetGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices )
	{
		m_lControlPoints = inControlPoints;
		m_lIndices = inIndices;
	}
}