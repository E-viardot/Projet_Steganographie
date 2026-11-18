#include "BMP.h"
#include <cstdio>

static std::uint16_t ReadUInt16(const std::uint8_t* p)
{
	return static_cast<std::uint16_t>(p[0]) | (p[1] << 8);
}

static std::uint32_t ReadUInt32(const std::uint8_t* p)
{
	return static_cast<std::uint32_t>(p[0]) | (static_cast<std::uint32_t>(p[1]) << 8) |
		   (static_cast<std::uint32_t>(p[2]) << 16) | (static_cast<std::uint32_t>(p[3]) << 24);
}

bool FileExists(const std::string& path)
{
	FILE* file = std::fopen(path.c_str(), "rb");
	if (!file)
	{
		return false;
	}
	std::fclose(file);
	return true;
}

bool LoadBMP(const std::string& path, Image& image, std::string& error)
{
	FILE* file = std::fopen(path.c_str(), "rb");
	if (!file)
	{
		error = "Failed to open file: " + path;
		return false;
	}
	std::uint8_t h[54];
	if (std::fread(h, 1, 54, file) != 54)
	{
		std::fclose(file);
        error = "file truncated (headers)";
		return false;
	}

	if (h[0] != 'B' || h[1] != 'M')
	{
		std::fclose(file);
		error = "not a BMP file";
		return false;
	}

	std::uint32_t pixel_offset = ReadUInt32(h + 10);
	std::uint32_t info_size = ReadUInt32(h + 14);
	std::int32_t width = static_cast<std::int32_t>(ReadUInt32(h + 18));
	std::int32_t height = static_cast<std::int32_t>(ReadUInt32(h + 22));
	std::uint16_t bits_per_pixel = ReadUInt16(h + 28);
	std::uint32_t compression = ReadUInt32(h + 30);

	if (info_size < 40)
	{
		std::fclose(file);
		error = "invalid BMP info header";
		return false;
	}
	if (bits_per_pixel != 24)	
	{
		std::fclose(file);
		error = "only 24-bit BMP files are supported";
		return false;
	}
	if (compression != 0)
	{
		std::fclose(file);
		error = "compressed BMP files are not supported";
		return false;
	}
	if (width <= 0 || height <= 0)
	{
		std::fclose(file);
		error = "invalid BMP dimensions";
		return false;
	}
	if (pixel_offset < 54)
	{
		std::fclose(file);
		error = "invalid BMP pixel offset";
		return false;
	}

	std::uint64_t row_size = ((static_cast<std::uint64_t>(width) * 3 + 3) / 4) * 4;
	std::uint64_t data_size = row_size * static_cast<std::uint64_t>(height);
	if (data_size > (1ull << 30) || pixel_offset > (1u << 20))
	{
		std::fclose(file);
		error = "Image too large";
		return false;
	}

	image.width = width;
	image.height = height;
	image.row_size = static_cast<std::size_t>(row_size);

	image.header.assign(pixel_offset, 0);
	std::rewind(file);
	if (std::fread(image.header.data(), 1, pixel_offset, file) != pixel_offset)
	{
		std::fclose(file);
		error = "file truncated (header)";
		return false;
	}
