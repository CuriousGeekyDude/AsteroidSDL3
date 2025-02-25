




#include "Systems/Renderer.hpp"
#include "Systems/Colors.hpp"
#include "Systems/RenderingData.hpp"
#include "Systems/GpuResouceManager.hpp"

#include <glm.hpp>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>



namespace Asteroid
{

	namespace RenderSystem
	{
		Renderer::Renderer(GpuResourceManager* l_gpuResManager)
			:m_renderer(nullptr)
			,m_gpuResourceManager(l_gpuResManager)
		{

		}


		bool Renderer::Init(SDL_Window* l_window)
		{
			m_renderer = SDL_CreateRenderer(l_window, nullptr);
			if (nullptr == m_renderer) {
				SDL_Log("SDL failed to create the renderer: %s", SDL_GetError());
				return false;
			}

			return true;
		}


		bool Renderer::SetClearColor(const Colors& l_clearColor)
		{
			glm::u8vec4 lv_color;

			switch (l_clearColor) {

			case Colors::BLACK:
				lv_color = glm::u8vec4{0, 0, 0, 1};
				break;
			case Colors::BLUE:
				lv_color = glm::u8vec4{0, 0, 1, 1};
				break;
			case Colors::GREEN:
				lv_color = glm::u8vec4{0, 1, 0, 1};
				break;
			case Colors::RED:
				lv_color = glm::u8vec4{1, 0, 0, 1};
				break;
			case Colors::WHITE:
				lv_color = glm::u8vec4{1, 1, 1, 1};
				break;

			}

			if (false == SDL_GetRenderDrawColor
			(m_renderer, &lv_color.r, &lv_color.g, &lv_color.b, &lv_color.a)) {
				SDL_Log("SDL failed to set the clear color to the requested one: %s\n", SDL_GetError());
				return false;
			}

			return true;
		}


		bool Renderer::ClearWindow()
		{
			if (false == SDL_RenderClear(m_renderer)) {
				SDL_Log("SDL failed to clear the swapchain: %s\n", SDL_GetError());
				return false;
			}

			return true;
		}

		bool Renderer::RenderEntity(const RenderingData& l_renderData)
		{

			auto* lv_sdlTexture = m_gpuResourceManager->RetrieveGpuTexture(l_renderData.m_entityTextureHandle);

			assert(lv_sdlTexture != nullptr);

			SDL_FRect lv_dstRect;
			lv_dstRect.x = l_renderData.m_entityPos.x;
			lv_dstRect.y = l_renderData.m_entityPos.y;
			lv_dstRect.w = (float)lv_sdlTexture->w;
			lv_dstRect.h = (float)lv_sdlTexture->h;

			if (false == SDL_RenderTexture(m_renderer
				, lv_sdlTexture, nullptr, &lv_dstRect)) {
				
				SDL_Log("SDL failed to render the requested entity: %s\n", SDL_GetError());
				return false;
			}

			return true;

		}


		bool Renderer::PresentToWindow()
		{
			if (false == SDL_RenderPresent(m_renderer)) {
				return false;
			}

			return true;
		}


		SDL_Renderer* Renderer::GetSDLRenderer()
		{
			return m_renderer;
		}


		Renderer::~Renderer()
		{
			SDL_DestroyRenderer(m_renderer);
		}
	}

}