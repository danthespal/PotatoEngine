#pragma once
#include "ToolsCommon.h"

namespace PotatoEngine::tools {

struct mesh
{
	// initial data
	utl::vector<math::v3>				positions;
	utl::vector<math::v3>				normals;
	utl::vector<math::v4>				tangents;
	utl::vector<utl::vector<math::v2>>	uv_sets;

	utl::vector<u32>					raw_indices;

	// intermediate data

	// output data
};

struct lod_group
{
	std::string			name;
	utl::vector<mesh>	meshes;
};

struct scene
{
	std::string				name;
	utl::vector<lod_group>	lod_groups;
};

struct geometry_import_settings
{
	f32 smoothing_angle;
	u8	calculate_normals;
	u8	calculate_tangents;
	u8	reverse_handedness;
	u8	import_embeded_textures;
	u8	import_animations;
};

struct scene_data
{
	u8*							buffer;
	u32							buffer_size;
	geometry_import_settings	settings;
};
}