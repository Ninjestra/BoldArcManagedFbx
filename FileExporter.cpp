#include "stdafx.h"
#include "FileExporter.h"

namespace BoldarcManagedFbx
{
	FileExporter::FileExporter()
	{
		m_lMeshes = gcnew List<Mesh^>();
		m_lControlPoints = gcnew List<Vector3>();
		m_lIndices = gcnew List<int>();
		m_iFaceCount = 0;
	}
	void FileExporter::ExportFile()
	{
		if ( m_pFbxManager == nullptr )
			m_pFbxManager = FbxManager::Create();

		FbxScene* _pScene = FbxScene::Create( m_pFbxManager, "RevitScene" );
		FbxAxisSystem _axisSystem(FbxAxisSystem::EUpVector::eZAxis,
			FbxAxisSystem::EFrontVector::eParityOdd,
			FbxAxisSystem::eLeftHanded );
		_axisSystem.ConvertScene( _pScene );


		FbxNode* _pNode = FbxNode::Create( _pScene, "MeshNode" );

		FbxMesh* _pMesh = FbxMesh::Create( _pScene, "TestMesh" );

		if ( m_lControlPoints != nullptr && m_lIndices != nullptr )
		{
			OptimizePoints();

			_pMesh->InitControlPoints( m_lControlPoints->Count );
			FbxVector4* _pControlPoints = _pMesh->GetControlPoints();
			for ( int i = 0; i < m_lControlPoints->Count; i++ )
			{
				_pControlPoints[i] = m_lControlPoints[i].ToFbxVector4();
			}

			//_pMesh->ReservePolygonVertexCount( m_lIndices->Count );
			//int* _pIndices = _pMesh->GetPolygonVertices();
			int _iIndexCount = m_lIndices->Count / 3;
			for ( int i = 0; i < _iIndexCount; i++ )
			{
				_pMesh->BeginPolygon();
				for ( int j = 0; j < 3; j++ )
				{
					_pMesh->AddPolygon( m_lIndices[i * 3 + j] );
				}
				_pMesh->EndPolygon();
			}

			_pNode->AddNodeAttribute( _pMesh );
			_pScene->GetRootNode()->AddChild( _pNode );

			FbxExporter* _pExporter = FbxExporter::Create( m_pFbxManager, "Exporter" );
			_pExporter->Initialize( "D:\\Joel\\FBX\\exporter_test.fbx", -1, m_pFbxManager->GetIOSettings());
			_pExporter->Export( _pScene );
			_pExporter->Destroy();
		}
	}

	void FileExporter::AddMesh( Mesh^ inMesh )
	{
		m_lMeshes->Add( inMesh );
	}

	void FileExporter::OptimizePoints()
	{
		Dictionary<int, int>^ _pDictionary = gcnew Dictionary<int, int>();
		List<Vector3>^ _pList = gcnew List<Vector3>( m_lControlPoints->Count );
		for ( int i = 0; i < m_lIndices->Count; i++ )
		{
			Vector3 _point = m_lControlPoints[m_lIndices[i]];
			int hashCode = _point.GetHashCode();
			if ( _pDictionary->ContainsKey( hashCode ) )
			{
				m_lIndices[i] = _pDictionary[hashCode];
			}
			else
			{
				_pList->Add( _point );
				int value = _pList->Count - 1;
				_pDictionary[hashCode] = value;
				m_lIndices[i] = value;
			}
		}
		m_lControlPoints = _pList;
	}

	void FileExporter::AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices )
	{

		m_lControlPoints->AddRange( inControlPoints );
		for ( int i = 0; i < inIndices->Count; i++ )
		{
			m_lIndices->Add( inIndices[i] + m_iFaceCount );
		}
		m_iFaceCount += inControlPoints->Count;

	}
}