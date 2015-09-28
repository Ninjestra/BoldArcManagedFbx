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
		String^ FixName( String^ inName );
		Dictionary<String^, String^>^ m_dReplacements;

	public:
		FileExporter();
		void ExportFile();
		void AddMesh( Mesh^ inMesh );


	};
}
