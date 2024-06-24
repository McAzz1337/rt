#include "objparser.h"

#include <iostream>
#include <fstream>
#include <sstream>

bool loadOBJ(const std::string& path, std::vector<Triangle>& triangles) {
    std::vector<Vec3> vertices;
    std::vector<std::vector<unsigned int>> faceIndices;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {

        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;
        if (prefix == "v") {

            Vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "f") {

            std::vector<unsigned int> faceVertexIndices;
            std::string faceIndicesStr;
            while (ss >> faceIndicesStr) {

                std::istringstream faceStream(faceIndicesStr);
                unsigned int vertexIndex;
                char delimiter;
                faceStream >> vertexIndex;
                if (faceStream.fail()) {

                    std::cerr << "Invalid face definition: " << faceIndicesStr << std::endl;
                    continue;
                }
                faceVertexIndices.push_back(vertexIndex - 1); // Adjust for 1-based to 0-based index
            }
            if (faceVertexIndices.size() >= 3) {
                faceIndices.push_back(faceVertexIndices);
            }
        }
    }

    file.close();

    // Create triangles from face indices
    for (const auto& face : faceIndices) {
        if (face.size() >= 3) {
            unsigned int idx1 = face[0];
            unsigned int idx2 = face[1];
            unsigned int idx3 = face[2];

            if (idx1 < vertices.size() && idx2 < vertices.size() && idx3 < vertices.size()) {

                triangles.emplace_back(vertices[idx1], vertices[idx2], vertices[idx3]);
            } else {

                std::cerr << "Invalid vertex index detected in face definition." << std::endl;
                std::cerr << "Indices: " << idx1 << " " << idx2 << " " << idx3 << std::endl;
                std::cerr << "Vertices size: " << vertices.size() << std::endl;
            }
        }
    }

    std::cout << "Number of triangles loaded: " << triangles.size() << std::endl;

    return true;
}




