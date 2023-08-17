// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TestInterface.h"
#include "Templates/UniquePtr.h"

#include "TestFramework.generated.h"

UCLASS(Blueprintable, Category="TestFramework")
class ATestFramework : public AActor { GENERATED_BODY()
  public:
    /**
     * @brief Creates Default TestFramework Object
     */
	ATestFramework();

  protected:
	/**
	 * @brief overriden from beginplay in aactor class.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Construct a new run All Tests object
	 * 
	 * @return true if all tests return true
	 * @return false if at least one returns false
	 */
	void runAllTests();

	/**
	 * @brief Appends a test to be run in the test framework.
	 * 
	 * @param test some test object
	 */
	void appendTest(ITestInterface *new_test);

  private:
    UPROPERTY()
	TArray<ITestInterface*> tests_vector;
};
