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
		MaterialIDPerFace = gcnew Dictionary<int, int>();
		PolysPerFace = gcnew List<int>();
		Name = inName;

		m_iFaceVertexCount = 0;
		FaceCount = 0;
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
			Indices->Add( _index + m_iFaceVertexCount );
		}

		m_iFaceVertexCount += inControlPoints->Count;
		PolysPerFace->Add( inIndices->Count / 3 );
		FaceCount++;
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

	void Mesh::FixPosition()
	{
		Vector3^ _pos = gcnew Vector3();
		
		for ( int i = 0; i < Vertices->Count; i++ )
		{
			Vertices[i] = (Vertices[i] - Position);
		}

		Scale = Scale * 30.0; // 30 is hard coded because everything is so dang small coming out of revit.
		Position = Position * Scale;
	}

	bool Mesh::IsEmpty()
	{
		if ( Vertices->Count > 0 )
			return false;
		else
			return true;
	}

	int Mesh::GetVertexCount()
	{
		return Vertices->Count;
	}
}