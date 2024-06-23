#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <vector>
#include <string>
#include "../shapes/triangle.h"

bool loadOBJ(const std::string& path, std::vector<Triangle>& triangles);
#endif // OBJPARSER_H
