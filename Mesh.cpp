#include "stdafx.h"
#include "Mesh.h"

namespace BoldarcManagedFbx
{
	Mesh::Mesh(String^ inName)
	{
		Vertices = gcnew List<Vector3>();
		Indices = gcnew List<int>();
		Normals = gcnew List<Vector3>();
		NormalIndices = gcnew List<int>();
		Name = inName;

		m_iFaceCount = 0;
	}

	void Mesh::AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices, List<Vector3>^ inNormals )
	{

		Vertices->AddRange( inControlPoints );
		if ( inNormals->Count > 1 )
		{
			Normals->AddRange( inNormals );
		}
		else
		{
			for each (Vector3 _vert in inControlPoints)
			{
				Normals->Add( inNormals[0] );
			}
		}
		for each (int _index in inIndices)
		{
			Indices->Add( _index + m_iFaceCount );
		}

		m_iFaceCount += inControlPoints->Count;
	}

	//void Mesh::AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices, Vector3^ inNormal )
//	{

//	}

	void Mesh::OptimizePoints()
	{
		Dictionary<int, int>^ _pDictionary = gcnew Dictionary<int, int>();
		List<Vector3>^ _pList = gcnew List<Vector3>( Vertices->Count );
		for ( int i = 0; i < Indices->Count; i++ )
		{
			Vector3 _point = Vertices[Indices[i]];
			int hashCode = _point.GetHashCode();
			if ( _pDictionary->ContainsKey( hashCode ) )
			{
				Indices[i] = _pDictionary[hashCode];
			}
			else
			{
				_pList->Add( _point );
				int value = _pList->Count - 1;
				_pDictionary[hashCode] = value;
				Indices[i] = value;
			}
		}
		Vertices = _pList;
	}

	bool Mesh::IsEmpty()
	{
		if ( Vertices->Count > 0 )
			return false;
		else
			return true;
	}
}