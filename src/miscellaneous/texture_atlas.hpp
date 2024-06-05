#pragma once

#include <sparkle.hpp>

class TextureAtlas : public spk::Singleton<TextureAtlas>, public spk::TextureAtlas, public spk::FontAtlas
{
	friend class spk::Singleton<TextureAtlas>;
private:
	TextureAtlas();

public:
};