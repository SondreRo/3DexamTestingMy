#pragma once
#include "Mesh.h"
struct MeshImportExport
{
	static bool ReadFile(std::string FilePath, Mesh* inMesh); // Vertices and Indices from file will be transferred to the mesh, returns true if read is success
	static bool WriteFile(std::string FilePath, Mesh* inMesh); // Vertices and Indices from mesh will be written to the file, returns true if write is success

};

