// Fill out your copyright notice in the Description page of Project Settings.


#include "Matrix2D.h"

#include "Kismet/KismetMathLibrary.h"

UMatrix2D::UMatrix2D() {
  this->num_rows = 0;
  this->num_cols = 0;
  this->flat_matrix.Init(0, 0);
}

void UMatrix2D::setSize(const int32 rows, const int32 cols) {
  this->num_rows = UKismetMathLibrary::Abs(rows);
  this->num_cols = UKismetMathLibrary::Abs(cols);
  const int32 new_size = num_rows * num_cols;
  this->flat_matrix.SetNum(new_size);
}

void UMatrix2D::clearSetSize(const int32 rows, const int32 cols) {
  this->clear();
  this->setSize(rows, cols);
}

void UMatrix2D::clear() {
  this->flat_matrix.Empty();
}

int32 UMatrix2D::setAtIndex(const int32 row, const int32 col, int32 element) {
  const int32 converted_coords = convertCoordsFlat(row, col);
  if (row < this->num_rows && col < this->num_cols) {
    return this->flat_matrix[converted_coords] = element;
  }

  return -1;
}

int32 UMatrix2D::getAtIndex(const int32 row, const int32 col) {
  const int32 converted_coords = convertCoordsFlat(row, col);
  if (row < this->num_rows && col < this->num_cols) {
    return this->flat_matrix[converted_coords];
  }

  return -1;
}

int32 UMatrix2D::convertCoordsFlat(const int32 row, const int32 col) {
  return (this->num_cols * row) + col;
}
