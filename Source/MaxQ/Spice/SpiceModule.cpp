// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ /


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

IMPLEMENT_MODULE(FSpiceModule, Spice);

