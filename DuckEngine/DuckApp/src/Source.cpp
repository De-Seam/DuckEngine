#include "da/app/app.h"
#include "da/editor/editor.h"
#include "da/dll_loader.h"

int main(int argc, char* argv[])
{
	for(int i = 0; i < argc; i++)
	{
		std::string dll_name = argv[1];
		if(dll_name.find(".dll") != std::string::npos)
		{
			da::DllLoader::load_dll(dll_name);
		}
	}

	bool editor_mode = true;
	if(editor_mode)
		da::Editor::init();
	else
		da::App::init();
	return 0;
}