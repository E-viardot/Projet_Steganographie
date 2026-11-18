#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct Image
{
	int width = 0;
	int height = 0;
	std::size_t row_size = 0;
	std::vector<std::uint8_t> header;
	std::vector<std::uint8_t> pixel;
};

bool FileExists(const std::string& path);
bool LoadBMP(const std::string& path, Image& image, std::string& error);
bool SaveBMP(const std::string& path, const Image& image, std::string& error);

std::size_t ComponentCount(const Image& image);
std::size_t ComponentIndex(const Image& image, std::size_t component);