// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef STRATEGYKIT_StrategyController_generated_h
#error "StrategyController.generated.h already included, missing '#pragma once' in StrategyController.h"
#endif
#define STRATEGYKIT_StrategyController_generated_h

#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execForceSelecteActor) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_NewSelectedActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ForceSelecteActor(Z_Param_NewSelectedActor); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execClearSelectedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ClearSelectedActor(); \
		P_NATIVE_END; \
	}


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execForceSelecteActor) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_NewSelectedActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ForceSelecteActor(Z_Param_NewSelectedActor); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execClearSelectedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ClearSelectedActor(); \
		P_NATIVE_END; \
	}


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAStrategyController(); \
	friend STRATEGYKIT_API class UClass* Z_Construct_UClass_AStrategyController(); \
	public: \
	DECLARE_CLASS(AStrategyController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), 0, TEXT("/Script/StrategyKit"), NO_API) \
	DECLARE_SERIALIZER(AStrategyController) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_INCLASS \
	private: \
	static void StaticRegisterNativesAStrategyController(); \
	friend STRATEGYKIT_API class UClass* Z_Construct_UClass_AStrategyController(); \
	public: \
	DECLARE_CLASS(AStrategyController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), 0, TEXT("/Script/StrategyKit"), NO_API) \
	DECLARE_SERIALIZER(AStrategyController) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStrategyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStrategyController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStrategyController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStrategyController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStrategyController(AStrategyController&&); \
	NO_API AStrategyController(const AStrategyController&); \
public:


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStrategyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStrategyController(AStrategyController&&); \
	NO_API AStrategyController(const AStrategyController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStrategyController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStrategyController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStrategyController)


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_15_PROLOG
#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_RPC_WRAPPERS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_INCLASS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_INCLASS_NO_PURE_DECLS \
	SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h_18_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class StrategyController."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SummonMaster_Plugins_StrategyKit_Source_StrategyKit_Public_StrategyController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
