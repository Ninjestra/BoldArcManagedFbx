#pragma once
using namespace System::Collections::Generic;
#include "Vector3.h"
#include "Mesh.h"
#include "Material.h"

namespace BoldarcManagedFbx
{
	public ref class FileExporter
	{
	private:
		FbxManager* m_pFbxManager;
		List<Mesh^>^ m_lMeshes;
		String^ FixName( String^ inName );
		Dictionary<String^, String^>^ m_dReplacements;
		Dictionary<int, IntPtr>^ m_dMaterialDict;
		void CreateMaterials( FbxScene* inScene, Dictionary<int, Material>^ inMaterialDict );

	public:
		FileExporter();
		void ExportFile( Dictionary<int, Material>^ inMaterialDict );
		void AddMesh( Mesh^ inMesh );
		


	};
}
