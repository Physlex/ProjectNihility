// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/TestInterface.h"

ITestInterface::ITestInterface() {
}

void ITestInterface::runTests() {
}

void ITestInterface::testFunc(bool (*function) (void), const FString test_name) {
    check(function != nullptr);
    checkCode( if (!function()) {
        UE_LOG(
            LogUObjectGlobals, Error,
            TEXT("Test %s has returned false"), *test_name
        );
    });
}
