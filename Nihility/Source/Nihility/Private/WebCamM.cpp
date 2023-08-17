/**
 * @file WebCamM.cpp
 * @date 2023-07-05
 * @copyright Copyright Alexander Williams-Letondre (c) 2023
 */

#include "WebCamM.h"

#include "Matrix2D.h"

#include "Kismet/KismetMathLibrary.h"

/// PUBLIC ///

UWebCamM::UWebCamM() {
	this->active_camera_id = -1;
	this->root_camera = nullptr;

	// Create all commands to allow translation to graph
	const FString up_command = TEXT("up");
	this->transition_type_map.Add(up_command, 0);
	const FString down_command = TEXT("down");
	this->transition_type_map.Add(down_command, 1);
	const FString left_command = TEXT("left");
	this->transition_type_map.Add(left_command, 2);
	const FString right_command = TEXT("right");
	this->transition_type_map.Add(right_command, 3);
}

void UWebCamM::appendCamera(ACameraActor *new_camera) {
	check(new_camera != nullptr);

	camera_list.Add(new_camera);
	const int32 number_of_cameras = this->camera_list.Num();
	if (number_of_cameras == 1) {
		this->active_camera_id = 0;
		this->root_camera = new_camera;
		this->camera_graph = NewObject<UMatrix2D>();
		check(this->camera_graph != nullptr);
	}

	const int32 number_of_commands = 4;
	this->camera_graph->setSize(number_of_cameras, number_of_commands);
	for (int i = 0; i < number_of_commands; i++) {
		int32 result = this->camera_graph->setAtIndex(number_of_cameras - 1, i, -1);
	}
}

ACameraActor* UWebCamM::transition(FString transition_command) {
	if (this->camera_graph == nullptr) {
		return nullptr;
	}

	const int32 mapped_command = this->transition_type_map[transition_command];
	const int32 maximum_mapping_value = this->camera_graph->getNumCols();
	if (mapped_command < maximum_mapping_value) {	
		int32 new_active_camera = this->camera_graph->getAtIndex(
			this->active_camera_id, mapped_command
		);

		if (new_active_camera != -1) {
			this->active_camera_id = new_active_camera;
		}

		return getActiveCamera();
	} else {
		return nullptr;
	}
}

void UWebCamM::connectCamerasByType(
	const int32 camera_id_one, const int32 camera_id_two,
	const FString camera_connection_type) {

	// START OF FUNCTION

	// Checking validity of the cameras chosen to be connected
	if (this->camera_graph == nullptr) {
		return;
	}

	const int32 number_of_cameras = this->camera_graph->getNumRows();

	const int32 clean_camera_one = UKismetMathLibrary::Abs(camera_id_one);
	checkCode(if (clean_camera_one >= number_of_cameras) {
		UE_LOG(LogUObjectGlobals, Fatal,
		TEXT("Camera one out of bounds."));
	});

	const int32 clean_camera_two = UKismetMathLibrary::Abs(camera_id_two);
	checkCode(if (clean_camera_two >= number_of_cameras) {
		UE_LOG(LogUObjectGlobals, Fatal,
		TEXT("Camera two out of bounds."));
	});

	// Checking the validity of the transition type / command to be used to connect the cameras
	const int32 command_mapping = this->transition_type_map[camera_connection_type];

	const int32 number_of_commands = this->camera_graph->getNumCols();
	checkCode(if (command_mapping >= number_of_commands) {
		UE_LOG(LogUObjectGlobals, Fatal,
		TEXT("Camera command invalid."));
	});

	// If everything above is clean, and we aren't going oob, then:
	// assign camera one to be connected to camera two via the command mapping
	this->camera_graph->setAtIndex(
		clean_camera_one, command_mapping, clean_camera_two
	);
}

ACameraActor* UWebCamM::getCameraByID(const int32 camera_id) {
	if (camera_id < 0) {
		return nullptr;
	}
	
	const int32 number_of_cameras = this->camera_list.Num();
	if (number_of_cameras <= 0) {
		return nullptr;
	} else if (camera_id <= number_of_cameras) {
		return this->camera_list[camera_id];
	} else {
		return nullptr;
	}
}

ACameraActor* UWebCamM::getActiveCamera() {
	return getCameraByID(this->active_camera_id);
}

ACameraActor* UWebCamM::getRootCamera() {
	return this->root_camera;
}
