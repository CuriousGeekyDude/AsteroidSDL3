





#include "Utilities/UtilityFunctions.hpp"
#include <vector>
#include <array>
#include <fstream>
#include "Systems/LogSystem.hpp"

namespace Asteroid
{
	namespace Utilities
	{
		AnimationMetaData ProcessFileOfRelativePathsOfTextures(const std::string& l_fileOfRelativePathsTextures
			, std::vector<std::pair<std::string, std::string>>& l_mappedTextureNamesToTheirPaths,const AnimationType l_type
			, const int l_widthToRender, const int l_heightToRender)
		{

			using namespace LogSystem;

			AnimationMetaData lv_data{};
			lv_data.m_totalNumFrames = UINT32_MAX;
			lv_data.m_firstTextureIndex = UINT32_MAX;
			lv_data.m_heightToRenderTextures = l_heightToRender;
			lv_data.m_widthToRenderTextures = l_widthToRender;
			lv_data.m_type = l_type;


			if (true == l_fileOfRelativePathsTextures.empty()) {
				return lv_data;
			}
			else {

				std::vector<std::string> lv_relativePaths{};
				std::ifstream lv_file{l_fileOfRelativePathsTextures};

				if (false == lv_file.is_open()) {
					LOG(Severity::FAILURE, Channel::INITIALIZATION, "Failed to open the following file: %s", l_fileOfRelativePathsTextures.c_str());
					std::runtime_error("Failed to open a file containing relative path of textures to be initialized at the init of the engine.");
				}
				else {
					
					std::array<char, 2048> lv_tempRelPathOfTexture{};

					size_t lv_totalNumLines{};

					while (false == lv_file.eof()) {
						lv_file.getline(lv_tempRelPathOfTexture.data(), lv_tempRelPathOfTexture.size());
						++lv_totalNumLines;
					}

					lv_data.m_totalNumFrames = (uint32_t)lv_totalNumLines-1U;
					lv_file.clear();
					lv_file.seekg(0, std::ios::beg);

					lv_relativePaths.resize(lv_data.m_totalNumFrames);
					for (auto& l_relPathTexture : lv_relativePaths) {
						l_relPathTexture.resize(lv_tempRelPathOfTexture.size());
					}

					size_t lv_i = 0;
					while (false == lv_file.eof()) {
						if (lv_i < lv_relativePaths.size()) {
							lv_file.getline(lv_relativePaths[lv_i].data(), lv_relativePaths[lv_i].size());
						}
						else {
							break;
						}
						++lv_i;
					}

					lv_file.close();


					lv_data.m_firstTextureIndex = (uint32_t)l_mappedTextureNamesToTheirPaths.size();

					for (auto& l_relPathTexture : lv_relativePaths) {
						size_t lv_posLast = l_relPathTexture.find_last_of('/');

						if (std::string::npos == lv_posLast) {
							LOG(Severity::FAILURE, Channel::INITIALIZATION, "Failed to find last occurence of /");
							std::runtime_error("Failed to find last occurence of /");
						}

						std::string lv_textureName = l_relPathTexture.substr(lv_posLast+1);

						l_mappedTextureNamesToTheirPaths.emplace_back(std::make_pair<std::string, std::string>(std::move(lv_textureName), std::move(l_relPathTexture)));
					}

					return lv_data;

				}

			}

		}
	}
}