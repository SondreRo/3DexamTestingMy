#include "MeshImportExport.h"

#include <fstream>
#include <sstream>

bool MeshImportExport::ReadFile(std::string FilePath, Mesh* inMesh)
{
	// All files needs to be in the asset folder
	std::string DefaultPath = "Assets/";
	DefaultPath.append(FilePath);
	// Read the file
	std::ifstream file(DefaultPath);

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (line.find("v ") != std::string::npos)
			{
				// Vertex
				std::string vertex = line.substr(2);

				// Position
				std::string x = vertex.substr(0, vertex.find(" "));
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string y = vertex.substr(0, vertex.find(" "));
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string z = vertex.substr(0, vertex.find(" "));

				// Normal
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string Nx = vertex.substr(0, vertex.find(" "));
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string Ny = vertex.substr(0, vertex.find(" "));
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string Nz = vertex.substr(0, vertex.find(" "));

				// Color
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string Cx = vertex.substr(0, vertex.find(" "));
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string Cy = vertex.substr(0, vertex.find(" "));
				vertex = vertex.substr(vertex.find(" ") + 1);
				std::string Cz = vertex.substr(0, vertex.find(" "));

				inMesh->vertices.emplace_back(
					glm::vec3(std::stof(x), std::stof(y), std::stof(z)), 
					glm::vec3(std::stof(Nx), std::stof(Ny), std::stof(Nz)),
					glm::vec3(std::stof(Cx), std::stof(Cy), std::stof(Cz)));
			}
			else if (line.find("f ") != std::string::npos)
			{
				// Face
				std::string face = line.substr(2);
				std::string v1 = face.substr(0, face.find(" "));
				face = face.substr(face.find(" ") + 1);
				std::string v2 = face.substr(0, face.find(" "));
				face = face.substr(face.find(" ") + 1);
				std::string v3 = face;
				inMesh->triangles.emplace_back(std::stoi(v1), std::stoi(v2), std::stoi(v3));
			}
		}
		std::cout << DefaultPath << " File read with " << inMesh->vertices.size() << " vertices and " << inMesh->triangles.size() << " triangles." << std::endl;
		file.close();
		return true;

	}
	else
	{
		std::cout << "File at " << DefaultPath << " is not open" << std::endl;
	}
	return false;

}

bool MeshImportExport::WriteFile(std::string FilePath, Mesh* inMesh)
{
	// All files needs to be in the asset folder
	std::string DefaultPath = "Assets/";
	DefaultPath.append(FilePath);
	DefaultPath.append(".txt");
	// Write the file
	std::ofstream file(DefaultPath);

	if (file.is_open())
	{
		for (auto& vertex : inMesh->vertices)
		{
			file << "v " << vertex.Position.x << " " << vertex.Position.y << " " << vertex.Position.z << " " << // Position
				vertex.Normal.x << " " << vertex.Normal.y << " " << vertex.Normal.z << std::endl;				// Normal
		}
		for (auto& triangle : inMesh->triangles)
		{
			file << "f " << triangle.P1 << " " << triangle.P2 << " " << triangle.P3 << std::endl;
		}
		file.close();
		std::cout << DefaultPath << " written to with " << inMesh->vertices.size() << " vertices and " << inMesh->triangles.size() << " triangles." << std::endl;
		return true;
	}
	else
	{
		std::cout << "File at " << DefaultPath << " is not open" << std::endl;
	}
	return false;
}
