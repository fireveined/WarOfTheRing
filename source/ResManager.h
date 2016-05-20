#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "common/Common.h"
#include <map>
//#include <ext/hash_map>

using namespace clan;

class CFontManager
{

protected:

	map<string, Font> Resources;
	static CFontManager *Manager;

public:

	static CFontManager* GetFontManager()
	{

		if (Manager == 0)Manager = new CFontManager();
		return Manager;
	}

	void AddFont(Font f, const std::string& name) { Resources[name] = f; }

	Font& zGetFont(const string& name);


};



class CImageManager
{

protected:

	map<string, Image> Resources;
	static CImageManager *Manager;

public:

	static CImageManager* GetImageManager()
	{

		if (Manager == 0)Manager = new CImageManager();
		return Manager;
	}

	void zAddImage(Image f, const std::string& name) { Resources[name] = f; }

	Image& zGetImage(const string& name);



};



class CSpriteManager
{

protected:

	map<string, Sprite> Resources;
	static CSpriteManager *Manager;

public:

	static CSpriteManager* GetSpriteManager()
	{

		if (Manager == 0)Manager = new CSpriteManager();
		return Manager;
	}

	void zAddImage(Sprite f, const std::string& name) { Resources[name] = f; }

	Sprite& zGetImage(const string& name);



};


class CTextureManager
{

protected:

	map<string, Texture> Resources;
	static CTextureManager *Manager;

public:

	static CTextureManager* GetTextureManager()
	{

		if (Manager == 0)Manager = new CTextureManager();
		return Manager;
	}

	void zAddTexture(Texture f, const std::string& name) { Resources[name] = f; }

	Texture& zGetTexture(const string& name);



};

#define GetImage(x) CImageManager::GetImageManager()->zGetImage(x)
#define AddImage(x,y) CImageManager::GetImageManager()->zAddImage(x,y)

#define GetSprite(x) CSpriteManager::GetSpriteManager()->zGetImage(x)
#define AddSprite(x,y) CSpriteManager::GetSpriteManager()->zAddImage(x,y)

#define GetTexture(x) CTextureManager::GetTextureManager()->zGetTexture(x)
#define AddTexture(x,y) CTextureManager::GetTextureManager()->zAddTexture(x,y)

#define GetFont(x) CFontManager::GetFontManager()->zGetFont(x)
#define AddFont(x,y) CFontManager::GetFontManager()->AddFont(x,y)



#endif // RESOURCE_H_INCLUDED