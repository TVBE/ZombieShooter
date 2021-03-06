// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_AddPinInterface.h"
#include "KismetCompilerMisc.h"
#include "K2Node_LowEntry_MakeContainer.generated.h"

class FBlueprintActionDatabaseRegistrar;
class UEdGraphPin;

class FKCHandler_LowEntry_MakeContainer : public FNodeHandlingFunctor
{
public:
	FKCHandler_LowEntry_MakeContainer(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext)
		, CompiledStatementType(KCST_Nop) {}

	virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;
	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;

protected:
	EKismetCompiledStatementType CompiledStatementType;
};


UCLASS(MinimalAPI, abstract)
class UK2Node_LowEntry_MakeContainer : public UK2Node, public IK2Node_AddPinInterface
{
	GENERATED_UCLASS_BODY()
	/** The number of input pins to generate for this node */
	UPROPERTY()
	int32 NumInputs;

public:
	LOWENTRYEXTENDEDSTANDARDLIBRARYEDITOR_API virtual void RemoveInputPin(UEdGraphPin* Pin) override;

	LOWENTRYEXTENDEDSTANDARDLIBRARYEDITOR_API UEdGraphPin* GetOutputPin() const;

	/** returns a reference to the output array pin of this node, which is responsible for defining the type */
	virtual FName GetOutputPinName() const PURE_VIRTUAL(UK2Node_LowEntry_MakeContainer::GetOutputPinName, return NAME_None;);
	virtual FName GetPinName(int32 PinIndex) const;
	virtual void GetKeyAndValuePins(TArray<UEdGraphPin*>& KeyPins, TArray<UEdGraphPin*>& ValuePins) const;

public:
	// UEdGraphNode interface
	virtual void AllocateDefaultPins() override;
	virtual void PostReconstructNode() override;
	// End of UEdGraphNode interface

	// UK2Node interface
	virtual bool IsNodePure() const override { return true; }
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override PURE_VIRTUAL(UK2Node_LowEntry_MakeContainer::CreateNodeHandler, return nullptr;);
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual int32 GetNodeRefreshPriority() const override { return Low_UsesDependentWildcard; }
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
	// End of UK2Node interface

	// IK2Node_AddPinInterface interface
	LOWENTRYEXTENDEDSTANDARDLIBRARYEDITOR_API virtual void AddInputPin() override;
	// End of IK2Node_AddPinInterface interface

protected:
	friend class FKismetCompilerContext;

	/** If needed, will clear all pins to be wildcards */
	void ClearPinTypeToWildcard();

	bool CanResetToWildcard() const;

	/** Helper function for context menu add pin to ensure transaction is set up correctly. */
	void InteractiveAddInputPin();

	/** Propagates the pin type from the output (set) pin to the inputs, to make sure types are consistent */
	void PropagatePinType();

	void SyncPinNames();

	EPinContainerType ContainerType;
};
