#pragma once
using namespace System::Collections::Generic;
#include "Vector3.h"

namespace BoldarcManagedFbx
{
	public ref class FileExporter
	{
	private:
		FbxManager* m_pFbxManager;
		List<Vector3>^ m_lControlPoints;
		List<int>^ m_lIndices;

	public:
		FileExporter();
		void ExportFile();
		
		void SetGeometry(List<Vector3>^ inControlPoints, List<int>^ inIndices);
	};
}
