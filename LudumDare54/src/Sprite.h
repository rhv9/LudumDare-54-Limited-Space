#pragma once
#include <Gonk.h>

using namespace Gonk;

class Sprite
{
public:
	static const int SPRITE_SIZE = 16;

	enum Tex : int
	{
		 Spritesheet = 0,
	};

	enum Sub : int
	{
		Void = 0,
		Grass,
	};

	enum Gif : int
	{
		PlayerUp = 0,
	};

public:
	static void Init();

	static const Ref<Texture2D>& GetTex(Tex id);
	static const Ref<SubTexture2D>& GetSub(Sub id);
	static const std::vector<Ref<SubTexture2D>>& GetGif(Gif id);

private:
	static std::array<Ref<Texture2D>, 1> s_Textures;
	static std::array<Ref<SubTexture2D>, 10> s_SubTextures;
	static std::array<std::vector<Ref<SubTexture2D>>, 10> s_GifTextures;
};
