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
		m_dReplacements->Add( "®", "" );
	}

	void FileExporter::ExportFile( Dictionary<int, Material>^ inMaterialDict )
	{
		if ( m_pFbxManager == nullptr )
			m_pFbxManager = FbxManager::Create();

		FbxScene* _pScene = FbxScene::Create( m_pFbxManager, "RevitScene" );
		FbxAxisSystem _axisSystem(FbxAxisSystem::EUpVector::eZAxis,
			FbxAxisSystem::EFrontVector::eParityOdd,
			FbxAxisSystem::eLeftHanded );
		_axisSystem.ConvertScene( _pScene );

		if (inMaterialDict->Count > 0 )
			CreateMaterials( _pScene, inMaterialDict );

		for ( int i = 0; i < m_lMeshes->Count; i++ )
		{
			FbxNode* _pNode = FbxNode::Create( _pScene, "MeshNode" );

			FbxMesh* _pMesh = FbxMesh::Create( _pScene, "TestMesh" );

			List<Vector3>^ _Vertices = m_lMeshes[i]->Vertices;
			List<int>^ _Indices = m_lMeshes[i]->Indices;
			List<Vector3>^ _Normals = m_lMeshes[i]->Normals;
			Dictionary<int, int>^ _MaterialIDPerFace = m_lMeshes[i]->MaterialIDPerFace;
			Dictionary<int, int>^ _NodeMaterialPerFace = gcnew Dictionary<int, int>();

			if ( _MaterialIDPerFace != nullptr && m_dMaterialDict != nullptr )
			{
				for each(int _key in _MaterialIDPerFace->Keys)
				{
					if ( m_dMaterialDict->ContainsKey( _MaterialIDPerFace[_key] ) )
					{
						FbxGeometryElementMaterial* lMaterialElement = _pMesh->CreateElementMaterial();
						lMaterialElement->SetMappingMode( FbxGeometryElement::eByPolygon );
						lMaterialElement->SetReferenceMode( FbxGeometryElement::eIndexToDirect );

						FbxSurfacePhong* _pMat = (FbxSurfacePhong*)((void*)m_dMaterialDict[_MaterialIDPerFace[_key]]);

						int _iMatIndex = _pNode->GetMaterialIndex( _pMat->GetName() );
						if ( _iMatIndex == -1 )
						{
							_pNode->AddMaterial( _pMat );
							_NodeMaterialPerFace->Add( _key, _pNode->GetMaterialIndex( _pMat->GetName() ) );
						}
						else
							_NodeMaterialPerFace->Add( _key, _iMatIndex );
					}
					else
						_NodeMaterialPerFace->Add( _key, -1 );
				}
			}

			if ( _Vertices != nullptr && _Indices != nullptr )
			{

				_pMesh->InitControlPoints( _Vertices->Count );
				FbxVector4* _pControlPoints = _pMesh->GetControlPoints();
				for ( int j = 0; j < _Vertices->Count; j++ )
				{
					_pControlPoints[j] = _Vertices[j].ToFbxVector4();
				}

				int _iIndexCount = _Indices->Count / 3;
				int _iFaceNum = 0;
				int _iVertNum = 0;
				for ( int j = 0; j < _iIndexCount; j++ )
				{

					 _pMesh->BeginPolygon( _NodeMaterialPerFace[_iFaceNum] );
					for ( int k = 0; k < 3; k++ )
					{
						_pMesh->AddPolygon( _Indices[j * 3 + k] );
					}
					_pMesh->EndPolygon();
					_iVertNum++;

					if ( _iVertNum >= m_lMeshes[i]->PolysPerFace[_iFaceNum] )
					{
						_iFaceNum++;
						_iVertNum = 0;
					}

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

				_pNode->LclTranslation.Set( m_lMeshes[i]->Position->ToFbxDouble3() );
				//_pNode->LclRotation.Set( m_lMeshes[i]->Rotation->ToFbxDouble3() );
				FbxDouble3 _temp = (FbxDouble3)m_lMeshes[i]->Scale;
				_pNode->LclScaling.Set( _temp );
				_pNode->AddNodeAttribute( _pMesh );

				/*
				FbxDouble3 _zero;
				_pNode->GeometricRotation.Set( _zero );
				_pNode->GeometricScaling.Set( _zero );
				_pNode->GeometricTranslation.Set( _zero );
				*/
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

	void FileExporter::CreateMaterials( FbxScene* inScene, Dictionary<int, Material>^ inMaterialDict )
	{
		m_dMaterialDict = gcnew Dictionary<int, IntPtr>();

		for each(int _key in inMaterialDict->Keys)
		{
			String^ _pMatName = FixName( inMaterialDict[_key].Name );
			const char* _pNewMatName = (const char*)(Marshal::StringToHGlobalAnsi( _pMatName )).ToPointer();

			FbxString _sShadingName = "Phong";
			FbxDouble3 _dColor = FbxDouble3( inMaterialDict[_key].Red / 256.0, inMaterialDict[_key].Green / 256.0, inMaterialDict[_key].Blue / 256.0 );
			FbxSurfacePhong *_pMat = FbxSurfacePhong::Create( inScene, _pNewMatName );

			_pMat->Emissive.Set( _dColor );
			_pMat->Ambient.Set( _dColor );
			_pMat->Diffuse.Set( _dColor );
			_pMat->TransparencyFactor.Set( inMaterialDict[_key].Transparency / 100.0 );
			_pMat->ShadingModel.Set( _sShadingName );
			_pMat->Shininess.Set( inMaterialDict[_key].Shininess );
			//lMaterial->BumpFactor.Set( _Material->Smoothness );

			IntPtr _val = (IntPtr)((void*)_pMat);

			m_dMaterialDict->Add( _key, _val);
		}
	}

	String^ FileExporter::FixName( String^ inName )
	{
		String^ _s = inName;
		for each (KeyValuePair<String^, String^> _pair in m_dReplacements)
			_s = _s->Replace(_pair.Key, _pair.Value);

		return _s;
	}
}