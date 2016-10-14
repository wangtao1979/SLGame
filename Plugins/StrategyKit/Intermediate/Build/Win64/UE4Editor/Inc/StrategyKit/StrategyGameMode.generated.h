// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef STRATEGYKIT_StrategyGameMode_generated_h
#error "StrategyGameMode.generated.h already included, missing '#pragma once' in StrategyGameMode.h"
#endif
#define STRATEGYKIT_StrategyGameMode_generated_h

#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetSeamlessTravelMidpointPause) \
	{ \
		P_GET_UBOOL(Z_Param_bNowPaused); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SetSeamlessTravelMidpointPause(Z_Param_bNowPaused); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsInSeamlessTravel) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->IsInSeamlessTravel(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSeamlessTravel) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_InURL); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SeamlessTravel(Z_Param_InURL); \
		P_NATIVE_END; \
	}


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetSeamlessTravelMidpointPause) \
	{ \
		P_GET_UBOOL(Z_Param_bNowPaused); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SetSeamlessTravelMidpointPause(Z_Param_bNowPaused); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsInSeamlessTravel) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->IsInSeamlessTravel(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSeamlessTravel) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_InURL); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->SeamlessTravel(Z_Param_InURL); \
		P_NATIVE_END; \
	}


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_EVENT_PARMS \
	struct StrategyGameMode_eventExGetSeamlessTravelActorList_Parms \
	{ \
		bool bToEntry; \
		TArray<AActor*> ReturnValue; \
	};


extern STRATEGYKIT_API  FName STRATEGYKIT_ExGetSeamlessTravelActorList;
extern STRATEGYKIT_API  FName STRATEGYKIT_OnSeamlessTravelFinlish;
#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_CALLBACK_WRAPPERS
#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAStrategyGameMode(); \
	friend STRATEGYKIT_API class UClass* Z_Construct_UClass_AStrategyGameMode(); \
	public: \
	DECLARE_CLASS(AStrategyGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, TEXT("/Script/StrategyKit"), NO_API) \
	DECLARE_SERIALIZER(AStrategyGameMode) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_INCLASS \
	private: \
	static void StaticRegisterNativesAStrategyGameMode(); \
	friend STRATEGYKIT_API class UClass* Z_Construct_UClass_AStrategyGameMode(); \
	public: \
	DECLARE_CLASS(AStrategyGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, TEXT("/Script/StrategyKit"), NO_API) \
	DECLARE_SERIALIZER(AStrategyGameMode) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStrategyGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStrategyGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStrategyGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStrategyGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStrategyGameMode(AStrategyGameMode&&); \
	NO_API AStrategyGameMode(const AStrategyGameMode&); \
public:


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStrategyGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStrategyGameMode(AStrategyGameMode&&); \
	NO_API AStrategyGameMode(const AStrategyGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStrategyGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStrategyGameMode); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStrategyGameMode)


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_11_PROLOG \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_EVENT_PARMS


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_RPC_WRAPPERS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_CALLBACK_WRAPPERS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_INCLASS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_CALLBACK_WRAPPERS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_INCLASS_NO_PURE_DECLS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h_14_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class StrategyGameMode."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
