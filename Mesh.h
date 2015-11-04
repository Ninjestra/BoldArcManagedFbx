#pragma once
using namespace System::Collections::Generic;
using namespace System;
#include "Vector3.h"
#include "Material.h"

namespace BoldarcManagedFbx
{
	public ref class Mesh
	{
	private:
		int m_iFaceVertexCount;
		

	public:
		Mesh(String^ inName);
		void AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices, List<Vector3>^ inNormals );
		int GetVertexCount();
		void OptimizePoints();
		void FixPosition();
		bool IsEmpty();
		
		property Vector3^ Position;
		property Vector3^ Rotation;
		property double Scale;
		property String^ Name;

		// Key = FaceNum, Val = MaterialID
		property Dictionary<int, int>^ MaterialIDPerFace;
		property List<int>^ PolysPerFace;
		property int FaceCount;

	internal:
		property List<Vector3>^ Vertices;
		property List<int>^ Indices;
		property List<Vector3>^ Normals;
		property List<int>^ NormalIndices;
		
		//property 
	};
}

