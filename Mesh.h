#pragma once
using namespace System::Collections::Generic;
using namespace System;
#include "Vector3.h"

namespace BoldarcManagedFbx
{
	public ref class Mesh
	{
	private:
		int m_iFaceCount;
		

	public:
		Mesh(String^ inName);
		void AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices, List<Vector3>^ inNormals );
		void OptimizePoints();
		bool IsEmpty();

	internal:
		property List<Vector3>^ Vertices;
		property List<int>^ Indices;
		property List<Vector3>^ Normals;
		property List<int>^ NormalIndices;
		property String^ Name;
		//property 
	};
}

