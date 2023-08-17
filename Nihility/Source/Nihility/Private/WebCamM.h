// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Camera/CameraActor.h"

#include "Matrix2D.h"

#include "WebCamM.generated.h"

UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class UWebCamM : public UActorComponent { GENERATED_BODY()
  public:
  	/**
  	 * @brief Construct a new AWebCamM object
  	 */
	UWebCamM();

	/**
	 * @brief Appends a camera to the camera list.
	 * 
	 * @param new_camera 
	 */
	UFUNCTION(BlueprintCallable, Category="WebCamM Callable Functions")
	void appendCamera(ACameraActor *new_camera);

	/**
	 * @brief the transition function takes the transition type
	 * 		| and transitions from the active camera to the next
	 * 		| camera attatched via the transition command if it
	 * 		| is properly specified via the connectCamearsByType func.
	 * 
	 * @param transition_type the type of transition meant to
	 * 		| occur on transition from the active camera.
	 * 		| Valid examples are "left", "right", "up", "down"
	 * 
	 * @return ACamera* a reference to a camera actor
	 * 		|  as described in the brief.
	 */
	UFUNCTION(BlueprintCallable, Category="WebCamM Callable Functions")
	ACameraActor* transition(const FString transition_command);

	/**
	 * @brief Connects two cameras by connection type.
	 * 
	 * @details connects the graph edge connection to be defined
	 * 		|   by a connection type representable as an integral
	 * 		|   value. IE:
	 * 		|   "up" = 0, "down" = 1, ... , "nth command" = n - 1
	 * 		|   this sequence is defined in the transition type map.
	 * 
	 * @param camera_id_one 
	 * @param camera_id_two 
	 * @param camera_connection_type 
	 */
	UFUNCTION(BlueprintCallable, Category="WebCamM Callable Functions")
	void connectCamerasByType(
		const int32 camera_id_one, const int32 camera_id_two,
		const FString camera_connection_type);

	/**
	 * @brief Returns a camera associated to a particular
	 * 		| number. Camera ID's are associated to the
	 * 		| order in which they are appended.
	 * 
	 * @param camera_id the camera ID, by order of appending
	 * 
	 * @return ACamera* the camera associated with the id.
	 * 		|  null if the camera DNE or is otherwise invalid.
	 */
	UFUNCTION(BlueprintCallable, Category="WebCamM Callable Functions")
	ACameraActor* getCameraByID(const int32 camera_id);

	/**
	 * @brief Get the current 'active camera'
	 * @details the active camera is the camera considered directly
	 * 		|   when determining the direction of other cameras.
	 * 
	 * @return ACameraActor* 
	 */
	UFUNCTION(BlueprintCallable, Category="Alexander Willet|WebCamM Callable Functions")
	ACameraActor* getActiveCamera();

	UFUNCTION(BlueprintCallable, Category="Alexander Willet|WebCamM Callable Functions")
	ACameraActor* getRootCamera();

  public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Alexander Willet|WebCamM Properties")
	ACameraActor *root_camera;

  private:
    UPROPERTY()
	int32 active_camera_id;

	UPROPERTY()
	UMatrix2D *camera_graph;

	UPROPERTY()
	TArray<ACameraActor*> camera_list;

	UPROPERTY()
	TMap<FString, int32> transition_type_map;
};