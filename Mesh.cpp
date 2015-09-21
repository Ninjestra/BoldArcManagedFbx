#include "stdafx.h"
#include "Mesh.h"

namespace BoldarcManagedFbx
{
	Mesh::Mesh()
	{
		m_lVertices = gcnew List<Vector3>();
		m_lIndices = gcnew List<int>();
		m_iFaceCount = 0;
	}

	void Mesh::AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices )
	{

		m_lVertices->AddRange( inControlPoints );
		for ( int i = 0; i < inIndices->Count; i++ )
		{
			m_lIndices->Add( inIndices[i] + m_iFaceCount );
		}
		m_iFaceCount += inControlPoints->Count;

		OptimizePoints();



	}

	void Mesh::OptimizePoints()
	{
		Dictionary<int, int>^ _pDictionary = gcnew Dictionary<int, int>();
		List<Vector3>^ _pList = gcnew List<Vector3>( m_lVertices->Count );
		for ( int i = 0; i < m_lIndices->Count; i++ )
		{
			Vector3 _point = m_lVertices[m_lIndices[i]];
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
		m_lVertices = _pList;
	}
}