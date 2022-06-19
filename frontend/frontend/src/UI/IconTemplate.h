#pragma once
#include <Siv3D.hpp>

class IconTemplate {
public:
	const static Array<ColorF> colors;

	static Array<Texture> textures;

	static void Init() {
		for (const ColorF& color : colors) {
			textures << Texture(Image(100, 100, color), TextureDesc::Mipped);
		}
	}

	IconTemplate() {
		for (const ColorF& color : colors) {
			textures << Texture(Image(100, 100, color), TextureDesc::Mipped);
		}
	}
};



