#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include "device.h"
#include "ResManager.h"


CTextureManager * CTextureManager::Manager;
CFontManager * CFontManager::Manager;
CImageManager * CImageManager::Manager;
CSpriteManager * CSpriteManager::Manager;



class DisplayProgram : Window
{
public:
	static int main(const std::vector<std::string> &args)
	{
	

	
		CDevice device(DEVICE_STANDARD);
	
device.Run();
		return 0;
	}
};
 
// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
Application app(&DisplayProgram::main);