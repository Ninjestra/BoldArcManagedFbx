#pragma once
using namespace System::Collections::Generic;
#include "Vector3.h"
#include "Mesh.h"

namespace BoldarcManagedFbx
{
	public ref class FileExporter
	{
	private:
		FbxManager* m_pFbxManager;
		List<Mesh^>^ m_lMeshes;
		List<Vector3>^ m_lControlPoints;
		List<int>^ m_lIndices;
		int m_iFaceCount;

	public:
		FileExporter();
		void ExportFile();
		void AddMesh( Mesh^ inMesh );
		void OptimizePoints();
		void AddGeometry( List<Vector3>^ inControlPoints, List<int>^ inIndices );

	};
}
