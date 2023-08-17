// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/WebCamMTest.h"

#include "Components/ActorComponent.h"
#include "WebCamM.h"

// GLOBALS

ACameraActor *test_camera_one_global;
ACameraActor *test_camera_two_global;

// TEST DEFINITIONS

bool defaultConstructorTests();
bool appendCameraTests();
bool basicTransitionTests();
bool invalidTransitionTests();

// END TEST DEFINITIONS

AWebCamMTest::AWebCamMTest () {
}

void AWebCamMTest::runTests() {
    UWorld* world = GetWorld();
    if (world != nullptr) {
        ACameraActor *test_camera_one = world->SpawnActor<ACameraActor>();
        test_camera_one_global = test_camera_one;

        ACameraActor *test_camera_two = world->SpawnActor<ACameraActor>();
        test_camera_two_global = test_camera_two;
    } else {
        test_camera_one_global = nullptr;
        test_camera_two_global = nullptr;
    }

    testFunc(&defaultConstructorTests, "Default Constructor Test");
    testFunc(&appendCameraTests, "Append Camera Test");
    testFunc(&basicTransitionTests, "Basic Transition Test");
    testFunc(&invalidTransitionTests, "Invalid Transition Test");
}

bool defaultConstructorTests() {
    UWebCamM *camera_manager = NewObject<UWebCamM>();
    check(camera_manager != nullptr);

    ACameraActor *inactive = camera_manager->getActiveCamera();
    if (inactive != nullptr) {
        return false;
    }

    ACameraActor *active_ptr = camera_manager->getActiveCamera();
    if (active_ptr != nullptr) {
        return false;
    }

    ACameraActor *root_ptr = camera_manager->getActiveCamera();
    if (root_ptr != nullptr) {
        return false;
    }

    return true;
}

bool appendCameraTests() {
    UWebCamM *camera_manager = NewObject<UWebCamM>();
    check(camera_manager != nullptr);

    ACameraActor *bad_root = camera_manager->getRootCamera();
    if (bad_root != nullptr) {
        return false;
    }

    camera_manager->appendCamera(test_camera_one_global);
    ACameraActor *root = camera_manager->getRootCamera();
    if (root == nullptr) {
        return false;
    }

    return true;
}

bool basicTransitionTests() {
    UWebCamM *camera_manager = NewObject<UWebCamM>();
    check(camera_manager != nullptr);

    camera_manager->appendCamera(test_camera_one_global);
    camera_manager->appendCamera(test_camera_two_global);
    camera_manager->connectCamerasByType(0, 1, "up");
    camera_manager->connectCamerasByType(1, 0, "down");

    ACameraActor *root = camera_manager->getActiveCamera();
    if (root != test_camera_one_global) {
        return false;
    }

    camera_manager->transition("up");
    ACameraActor *camera_two = camera_manager->getActiveCamera();
    if (camera_two != test_camera_two_global) {
        return false;
    }

    camera_manager->transition("down");
    ACameraActor *camera_one = camera_manager->getActiveCamera();
    if (camera_one != test_camera_one_global) {
        return false;
    }

    return true;
}

bool invalidTransitionTests() {
    UWebCamM *camera_manager = NewObject<UWebCamM>();
    check(camera_manager != nullptr);

    // Try to transition the camera without assigning a second one to transition to.
    camera_manager->appendCamera(test_camera_one_global);
    camera_manager->transition("down");
    ACameraActor *invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("up");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("left");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("right");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    // Try to transition to a camera that with no valid connection
    camera_manager->appendCamera(test_camera_two_global);
    camera_manager->transition("down");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("up");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("left");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("right");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    // Allow one connection...
    camera_manager->connectCamerasByType(0, 1, "up");
    camera_manager->transition("down");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("left");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("right");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    camera_manager->transition("up");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != test_camera_two_global) {
        return false;
    }

    // Allow the other
    camera_manager->connectCamerasByType(1, 0, "down");
    camera_manager->transition("down");
    invalid_camera = camera_manager->getActiveCamera();
    if (invalid_camera != camera_manager->getRootCamera()) {
        return false;
    }

    return true;
}
