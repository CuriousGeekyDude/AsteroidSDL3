#pragma once




struct SDL_Renderer;
struct SDL_Window;


namespace Asteroid
{
	

	namespace RenderSystem
	{

		enum class Colors;

		struct RenderingData;

		class Renderer
		{
		public:

			Renderer();

			bool Init(SDL_Window* l_window);

			bool SetClearColor(const Colors& l_clearColor);

			bool ClearWindow();

			bool RenderEntity(const RenderingData& l_renderData);

			bool PresentToWindow();

			SDL_Renderer* GetSDLRenderer();

			~Renderer();

		private:
			SDL_Renderer* m_renderer;
		};
	}
}