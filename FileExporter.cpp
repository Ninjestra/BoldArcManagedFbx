#include "stdafx.h"
#include "FileExporter.h"
using System::IntPtr;
using System::Runtime::InteropServices::Marshal;

namespace BoldarcManagedFbx
{
	FileExporter::FileExporter()
	{
		m_lMeshes = gcnew List<Mesh^>();
		m_dReplacements = gcnew Dictionary<String^, String^>();
		m_dReplacements->Add( "å", "a" );
		m_dReplacements->Add( "Å", "A" );
		m_dReplacements->Add( "ä", "a" );
		m_dReplacements->Add( "Ä", "A" );
		m_dReplacements->Add( "ö", "o" );
		m_dReplacements->Add( "Ö", "O" );
		m_dReplacements->Add( " ", "_" );
		m_dReplacements->Add( "/", "_" );
		m_dReplacements->Add( "\\", "_" );
		m_dReplacements->Add( "(", "_" );
		m_dReplacements->Add( ")", "_" );
		m_dReplacements->Add( ".", "_" );
		m_dReplacements->Add( ",", "_" );
		m_dReplacements->Add( "-", "_" );
		m_dReplacements->Add( "+", "_" );
		m_dReplacements->Add( ":", "_" );
		m_dReplacements->Add( ";", "_" );
		m_dReplacements->Add( "*", "x" );
		m_dReplacements->Add( "<", "" );
		m_dReplacements->Add( ">", "" );
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

		for ( int i = 0; i < m_lMeshes->Count; i++ )
		{
			FbxNode* _pNode = FbxNode::Create( _pScene, "MeshNode" );

			FbxMesh* _pMesh = FbxMesh::Create( _pScene, "TestMesh" );

			List<Vector3>^ _Vertices = m_lMeshes[i]->Vertices;
			List<int>^ _Indices = m_lMeshes[i]->Indices;
			List<Vector3>^ _Normals = m_lMeshes[i]->Normals;

			if ( _Vertices != nullptr && _Indices != nullptr )
			{

				_pMesh->InitControlPoints( _Vertices->Count );
				FbxVector4* _pControlPoints = _pMesh->GetControlPoints();
				for ( int j = 0; j < _Vertices->Count; j++ )
				{
					_pControlPoints[j] = _Vertices[j].ToFbxVector4();
				}

				//_pMesh->ReservePolygonVertexCount( m_lIndices->Count );
				//int* _pIndices = _pMesh->GetPolygonVertices();
				int _iIndexCount = _Indices->Count / 3;
				for ( int j = 0; j < _iIndexCount; j++ )
				{
					_pMesh->BeginPolygon();
					for ( int k = 0; k < 3; k++ )
					{
						_pMesh->AddPolygon( _Indices[j * 3 + k] );
					}
					_pMesh->EndPolygon();
				}

				if ( _Normals != nullptr )
				{
					FbxGeometryElementNormal* _GeometryElementNormal = _pMesh->CreateElementNormal();

					_GeometryElementNormal->SetMappingMode( FbxGeometryElement::eByControlPoint );

					_GeometryElementNormal->SetReferenceMode( FbxGeometryElement::eDirect );

					for each (Vector3 _norm in _Normals)
					{
						_GeometryElementNormal->GetDirectArray().Add( _norm.ToFbxVector4() );
					}

				}

				String^ _pName = FixName( m_lMeshes[i]->Name );
				const char* _pNewName = (const char*)(Marshal::StringToHGlobalAnsi( _pName )).ToPointer();
				//const char* _meshName = _name + "_mesh";
				//_pMesh->SetName( _name + "_mesh");
				
				_pNode->SetName( _pNewName );
				_pNode->AddNodeAttribute( _pMesh );
				_pScene->GetRootNode()->AddChild( _pNode );
			}
		}
		FbxExporter* _pExporter = FbxExporter::Create( m_pFbxManager, "Exporter" );
		_pExporter->Initialize( "D:\\Joel\\FBX\\exporter_test.fbx", -1, m_pFbxManager->GetIOSettings());
		_pExporter->Export( _pScene );
		_pExporter->Destroy();

	}

	void FileExporter::AddMesh( Mesh^ inMesh )
	{
		m_lMeshes->Add( inMesh );
	}

	String^ FileExporter::FixName( String^ inName )
	{
		String^ _s = inName;
		for each (KeyValuePair<String^, String^> _pair in m_dReplacements)
			_s = _s->Replace(_pair.Key, _pair.Value);

		return _s;
	}
}