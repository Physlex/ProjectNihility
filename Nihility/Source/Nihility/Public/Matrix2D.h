// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Matrix2D.generated.h"

UCLASS(Blueprintable, BlueprintType)
class NIHILITY_API UMatrix2D : public UObject { GENERATED_BODY()
  public:
    /**
     * @brief Construct a default UMatrix2D object
     * 
    */
    UMatrix2D();

    /**
     * @brief Sets the new size of the matrix
     * 
     * @param rows the new number of rows in the matrix
     * @param cols the new number of cols in the matrix
    */
    UFUNCTION(BlueprintCallable)
    void setSize(const int32 rows, const int32 cols);

    /**
     * @brief Sets the size of the matrix after setting all
     *      | elements to default.
     * 
     * @param rows the new number of rows in the matrix
     * @param cols the new number of cols in the matrix
     */
    UFUNCTION(BlueprintCallable)
    void clearSetSize(const int32 rows, const int32 cols);

    /**
     * @brief Clears all elements in matrix by setting default values 
     */
    UFUNCTION()
    void clear();

    /**
     * @brief Set the element at row, col.
     * 
     * @param row row index 
     * @param col col index
     * 
     * @return int32 the element at this pos. -1 if invalid.
     */
    UFUNCTION(BlueprintCallable)
    int32 setAtIndex(const int32 row, const int32 col, int32 element);

    /**
     * @brief Get the element at row, col.
     * 
     * @param row row index 
     * @param col col index
     * 
     * @return int32 the element at this pos. -1 if invalid.
     */
    UFUNCTION(BlueprintCallable)
    int32 getAtIndex(const int32 row, const int32 col);

    // START OF GETTERS

    UFUNCTION(BlueprintCallable)
    inline int32 getNumRows() {
      return this->num_rows;
    }

    UFUNCTION(BlueprintCallable)
    inline int32 getNumCols() {
      return this->num_cols;
    }

    UFUNCTION(BlueprintCallable)
    inline int32 getSize() {
      return this->flat_matrix.Num();
    }

    // END OF GETTERS

  protected:
    /**
     * @brief Calculates the coverted coordinate from a 2D matrix to
     *      | a flat array representation.
     * 
     * @param row the row index
     * @param col the col index
     * 
     * @return const int32 the result
     */
    UFUNCTION(BlueprintCallable)
    int32 convertCoordsFlat(const int32 row, const int32 col);

  private:
    int32 num_rows;
    int32 num_cols;
    TArray<int32> flat_matrix;
};
