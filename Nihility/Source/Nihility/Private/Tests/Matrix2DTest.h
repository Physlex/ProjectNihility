// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TestInterface.h"
#include "UObject/NoExportTypes.h"

#include "Matrix2DTest.generated.h"

UCLASS()
class UMatrix2DTest : public UObject, public ITestInterface { GENERATED_BODY()
  public:
    /**
     * @brief Construct a new UMatrix2DTest object
     */
	UMatrix2DTest();

	/**
	 * @brief Matrix2D implementation of tests
	 */
	virtual void runTests() override;
};
