// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TestInterface.h"
#include "GameFramework/Actor.h"

#include "WebCamMTest.generated.h"

UCLASS()
class AWebCamMTest : public AActor, public ITestInterface { GENERATED_BODY()
  public:
	/**
	 * @brief Construct a new AWebCamMTest object
	 */
	AWebCamMTest();

	/**
	 * @brief AWebCamMTest implementation of tests
	 */
	virtual void runTests() override;
};
