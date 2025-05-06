#pragma once





#include "Components/AnimationMetaData.hpp"
#include <string>
#include <vector>
#include <utility>

namespace Asteroid
{
	namespace Utilities
	{
		AnimationMetaData ProcessFileOfRelativePathsOfTextures(const std::string& l_fileOfRelativePathsTextures
			, std::vector<std::pair<std::string, std::string>>& l_mappedTextureNamesToTheirPaths, const AnimationType l_type
		,const int l_widthToRender, const int l_heightToRender);
	}
}