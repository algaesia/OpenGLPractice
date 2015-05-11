#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include <map>
#include <iostream>
#include <SOIL\SOIL.h>

struct TextureData
{
	unsigned int handle;
	int width;
	int height;
};

class TextureManager
{
public:
	static TextureManager& Instance()
	{
		static TextureManager instance;
		return instance;
	}

	//used for all at once loading, 
	//instead of when it's required
	//reduces lag when in game
	void LoadTextures()
	{
		unsigned int textureHandle;

		Insert("resources/blankSquare.png", &textureHandle);
		Insert("resources/desert.jpg", &textureHandle);
		Insert("resources/chrysanthemum.jpg", &textureHandle);
		Insert("resources/koala.jpg", &textureHandle);
		Insert("resources/lighthouse.jpg", &textureHandle);
		Insert("resources/jellyfish.jpg", &textureHandle);
		Insert("resources/tulips.jpg", &textureHandle);
		Insert("resources/calibri_light_0.png", &textureHandle);
	}

	//returns false if it fails to create the image correctly
	//otherwise returns true, returns valid texture handle
	bool Insert(const char* a_TextureFileName, unsigned int* a_TextureHandle, int* a_TextureWidth = nullptr, int* a_TextureHeight = nullptr)
	{
		//looked through map and haven't reached the end before returning
		if (m_TextureMap.find(a_TextureFileName) != m_TextureMap.end())
		{
			//an entry exists with the file name, so can
			//assign the handle out to be used
			*a_TextureHandle = m_TextureMap[a_TextureFileName].handle;

			if (a_TextureWidth != nullptr && a_TextureHeight != nullptr)
			{
				*a_TextureWidth = m_TextureMap[a_TextureFileName].width;
				*a_TextureHeight = m_TextureMap[a_TextureFileName].height;
			}

			return true;
		}

		int textureID, textureWidth, textureHeight, BPP;
		if (a_TextureFileName != nullptr)
		{
			unsigned char* imageData = SOIL_load_image(a_TextureFileName,
														&textureWidth,
														&textureHeight,
														&BPP,
														SOIL_LOAD_AUTO);
			if (imageData)
			{
				textureID = SOIL_create_OGL_texture(imageData, textureWidth, textureHeight, BPP,
					SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS		 | 
										SOIL_FLAG_INVERT_Y		 | 
										SOIL_FLAG_NTSC_SAFE_RGB  | 
										SOIL_FLAG_COMPRESS_TO_DXT);

				m_TextureMap[a_TextureFileName].width = textureWidth;
				m_TextureMap[a_TextureFileName].height = textureHeight;

				if (a_TextureWidth != nullptr && a_TextureHeight != nullptr)
				{
					*a_TextureWidth = m_TextureMap[a_TextureFileName].width;
					*a_TextureHeight = m_TextureMap[a_TextureFileName].height;
				}

				SOIL_free_image_data(imageData);
			}

			if (textureID == 0)
			{
				std::cerr << "SOIL LOADING ERROR: " << SOIL_last_result() << std::endl;
				return false;
			}

			//couldn't find texture of same name
			m_TextureMap[a_TextureFileName].handle = textureID;
			*a_TextureHandle = m_TextureMap[a_TextureFileName].handle;
			return true;
		}

		return false;
	}

	bool Find(const char* a_TextureFileName, int* a_TextureHandle)
	{
		if (m_TextureMap.find(a_TextureFileName) != m_TextureMap.end())
		{
			*a_TextureHandle = m_TextureMap[a_TextureFileName].handle;
			return true;
		}
		
		*a_TextureHandle = -1;
		return false;
	}

	~TextureManager()
	{
		glDeleteTextures(1, &m_TextureMap["resources/blankSquare.png"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/desert.jpg"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/chrysanthemum.jpg"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/koala.jpg"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/lighthouse.jpg"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/jellyfish.jpg"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/tulips.jpg"].handle);
		glDeleteTextures(1, &m_TextureMap["resources/calibri_light_0.png"].handle);
	}

private:
	TextureManager()
	{

	}

	//file name and texture handle
	//std::map<const char*, unsigned int> m_TextureMap;
	std::map<const char*, TextureData> m_TextureMap;
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
};

#endif