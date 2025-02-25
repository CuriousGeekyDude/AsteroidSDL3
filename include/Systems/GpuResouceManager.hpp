#pragma once




#include <vector>
#include <unordered_map>
#include <string>


struct SDL_Texture;
struct SDL_Renderer;

namespace Asteroid
{
	class GpuResourceManager
	{
	public:

		GpuResourceManager() = default;

		SDL_Texture* CreateGpuTextureReturnResource(SDL_Renderer* l_renderer
			,const std::string& l_texturePath
			, const std::string& l_nameToAssociateTextureWith);
		uint32_t CreateGpuTextureReturnHandle(SDL_Renderer* l_renderer
			,const std::string& l_texturePath
			, const std::string& l_nameToAssociateTextureWith);


		SDL_Texture* RetrieveGpuTexture(const std::string& l_textureName);
		SDL_Texture* RetrieveGpuTexture(const uint32_t l_textureHandle);

		uint32_t RetrieveGpuTextureHandle(const std::string& l_textureName);

		~GpuResourceManager();

	private:

		//Allocated textures on gpu by SDL
		std::vector<SDL_Texture*> m_gpuTextures;

		//Every allocated texture on gpu has its name associated to 
		//its index in m_gpuTextures
		std::unordered_map<std::string, uint32_t> m_textureNamesMappedToIndices;

	};
}