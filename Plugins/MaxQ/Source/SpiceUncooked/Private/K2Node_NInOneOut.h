// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Type.h"
#include "K2Node_CallFunction.h"
#include "SpiceTypes.h"
#include "K2PassThroughOp.h"
#include "K2Node_AddPinInterface.h"
#include "Chaos/Vector.h"
#include "K2Node_MathGenericInterface.h"
#include "K2Node_TwoInOneOut.h"
#include "K2Node_NInOneOut.generated.h"

#pragma once

#define LOCTEXT_NAMESPACE "K2Node_NInOneOut"

UCLASS(Abstract)
class SPICEUNCOOKED_API UK2Node_NInOneOut : public UK2Node_TwoInOneOut, public IK2Node_AddPinInterface
{
    GENERATED_UCLASS_BODY()

public:    

    // IK2Node_AddPinInterface interface
    virtual void AddInputPin(void) override;
    virtual bool CanAddPin() const override;
    virtual bool CanRemovePin(const UEdGraphPin* Pin) const override;
    virtual void RemoveInputPin(UEdGraphPin* Pin) override;
    // End of IK2Node_AddPinInterface interface

    // UEdGraphNode interface
    virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const;
    // End of UEdGraphNode interface
};


#undef LOCTEXT_NAMESPACE