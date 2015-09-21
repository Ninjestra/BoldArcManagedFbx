#pragma once
using namespace System::Collections::Generic;
#include "Vector3.h"

namespace BoldarcManagedFbx
{
	public ref class Mesh
	{
	private:
		int m_iFaceCount;
		List<Vector3>^ m_lVertices;
		List<int>^ m_lIndices;

	public:
		Mesh();
		void AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices );
		void OptimizePoints();

	internal:
		property FbxMesh* FbxMesh;

	};
}

