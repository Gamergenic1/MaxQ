// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


#include "SpiceModule.h"
#include "Modules/ModuleManager.h"
extern "C"
{
#include "SpiceUsr.h"
}


// Ensure CSpice doesn't try to exit the process...
// ...it's probably the UE editor, and that's just annoying.
class OnLoad
{
public:
    OnLoad()
    {
        SpiceChar szBuffer[] = "REPORT";
        erract_c("SET", sizeof(szBuffer), szBuffer);
    }
};
static OnLoad StaticInitializer;

IMPLEMENT_GAME_MODULE(FSpiceModule, Spice);

