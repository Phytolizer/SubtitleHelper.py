#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <type_traits>
#include <vector>

class Audio
{
	std::vector<Uint8> m_buffer;

  public:
	void FillBuffer(const void* buffer, int length)
	{
		size_t oldSize = m_buffer.size();
		m_buffer.resize(oldSize + length);
		SDL_memcpy(m_buffer.data() + oldSize, buffer, length);
	}
};

void AudioInputCallback(void* userData, Uint8* stream, int len)
{
	auto* audio = reinterpret_cast<Audio*>(userData);
	audio->FillBuffer(stream, len);
}

static_assert(std::is_same_v<decltype(&AudioInputCallback), SDL_AudioCallback>,
              "AudioInputCallback is not a SDL_AudioCallback");

int main()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	TTF_Font* font24 = TTF_OpenFont("FreeSans.ttf", 24);
	if (font24 == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open FreeSans.ttf: %s", TTF_GetError());
		return 1;
	}
	Audio audio;
	SDL_AudioSpec wantIn;
	SDL_zero(wantIn);
	wantIn.freq = 44100;
	wantIn.format = AUDIO_F32;
	wantIn.channels = 1;
	wantIn.samples = 4096;
	wantIn.callback = AudioInputCallback;
	wantIn.userdata = &audio;
	SDL_AudioDeviceID device = SDL_OpenAudioDevice(nullptr, 1, &wantIn, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
	SDL_PauseAudioDevice(device, 0);
	SDL_Window* window =
	    SDL_CreateWindow("Subtitle Helper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);
	bool run = true;
	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					run = false;
				}
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
