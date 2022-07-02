// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceUncooked
// K2 Node Compilation
// See comments in Spice/SpiceK2.h.
//------------------------------------------------------------------------------


#include "K2Node_MathGenericInterface.h"
#include "EdGraphSchema_K2.h"


void IK2Node_MathGenericInterface::NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection)
{
    auto& PinType = Pin->PinType;
    auto& ConnectedPinType = Connection->PinType;

    // Only consider flipping if this type is a wildcard, but the other one isn't...
    if (PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard && ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
    {
        CastChecked<UK2Node>(this)->NodeConnectionListChanged();
    }
}
