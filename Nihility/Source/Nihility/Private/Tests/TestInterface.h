// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestInterface.generated.h"

/**
 * UTest is an interface for other test classes.
 * It is not to be used as more than a defn for
 * the test framework.
*/
UINTERFACE(MinimalAPI, BlueprintType)
class UTestInterface : public UInterface { GENERATED_BODY()
};

/**
 * @brief interface for all test objects
 */
class ITestInterface { GENERATED_BODY()
  public:
	/**
	 * @brief Construct a default ITestInterface object
	 */
	ITestInterface();

	/**
	 * @brief Runs and logs all tests as defined per class.
	 */
	virtual void runTests();

  protected:
    /**
     * @brief Default impl. of testFunc wrapper.
	 * 		| Wraps a passed func into a checkCode
	 * 		| with a named callout on assert.
	 * 
	 * @param func the pointer to the function used
	 * 		| used in the test.
	 * @param test_name the name of the test.
     */
	virtual void testFunc(bool (*function) (void), const FString test_name);
};
