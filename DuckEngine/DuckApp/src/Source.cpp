#include "da/app/app.h"
#include "da/editor/editor.h"

int main(int argc, char* argv[])
{
	bool editor_mode = true;
	if(editor_mode)
		da::Editor::init();
	else
		da::App::init();
	return 0;
}