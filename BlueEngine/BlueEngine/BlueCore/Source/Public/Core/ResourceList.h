#pragma once
#include <map>
#include <string>

static std::map < std::string, std::string> sMeshFilePaths =
{
	{"cube", "Assets/Models/Cube.obj"},
	{"capsule", "Assets/Models/Capsule.obj"},
	{"plane", "Assets/Models/Plane.obj"},
	{"sphere", "Assets/Models/Sphere.obj" }
};


static std::map < std::string, std::string> sTexutresFilePaths =
{
	{ "default", "Assets/Textures/Default.png" },
	{"debug", "Assets/Textures/.png"}
};