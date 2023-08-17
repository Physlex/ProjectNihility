// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/TestFramework.h"

#include "TestInterface.h"

#include "Matrix2DTest.h"
#include "WebCamMTest.h"

ATestFramework::ATestFramework() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATestFramework::BeginPlay() {
	Super::BeginPlay();
	UWorld* test_world = GetWorld();

	UMatrix2DTest *Matrix2DTest = NewObject<UMatrix2DTest>();
	appendTest(Matrix2DTest);

	if (test_world != nullptr) {
		AWebCamMTest *WebCamMTest = test_world->SpawnActor<AWebCamMTest>();
		appendTest(WebCamMTest);
	}

	runAllTests();
}

void ATestFramework::runAllTests() {
	for (auto test : this->tests_vector) {
		checkCode(if (test == nullptr) {
			UE_LOG(LogUObjectGlobals, Fatal,
			TEXT("Error: Test is assigned as nullptr."));
		});

		test->runTests();
	}
}

void ATestFramework::appendTest(ITestInterface *new_test) {
	check(new_test != nullptr);

	// Find all duplicates (those that share the same mem address)
	bool is_duplicate = false;
	for (auto &curr_test : this->tests_vector) {
		is_duplicate = (curr_test == new_test);
		if (is_duplicate) {
			break;
		}
	}

	// If duplicate found, crash.
	checkCode(if (is_duplicate) {
		UE_LOG(LogUObjectGlobals, Fatal,
		TEXT("Error: duplicate test found in test framwork."));
	});
	tests_vector.Add(new_test);
}
