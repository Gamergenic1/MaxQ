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


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "K2Node_MathGenericInterface.generated.h"

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class SPICEUNCOOKED_API UK2Node_MathGenericInterface : public UInterface
{
	GENERATED_BODY()
};

class UEdGraphPin;

/**
* Interface is used for rippling type changes through a network of mMaxQ math connections.
*/
class SPICEUNCOOKED_API IK2Node_MathGenericInterface
{
	GENERATED_BODY()

public:

	virtual void NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection);
};
