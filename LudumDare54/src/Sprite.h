#pragma once
#include <Gonk.h>

using namespace Gonk;

class Sprite
{
public:
	static constexpr glm::vec2 SIZE = glm::vec2{16.0f, 16.0f};

	enum class Tex : int
	{
		Void = 0,
		Spritesheet,
	};

	enum class Sub : int
	{
		Void = 0,
		Grass,
	};

	enum class Gif : int
	{
		Void = 0,
		PlayerUp,
		Water,
	};

public:
	static void Init();

	static const Ref<Texture2D>& GetTex(Tex id);
	static const Ref<SubTexture2D>& GetSub(Sub id);
	static const std::vector<Ref<SubTexture2D>>& GetGif(Gif id);

};
