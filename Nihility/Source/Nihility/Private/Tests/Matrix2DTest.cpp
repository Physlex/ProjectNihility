// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/Matrix2DTest.h"

#include "Matrix2D.h"

// TEST DEFINITIONS
bool runDefaultTests();
bool runSetSizeTests();
bool runClearSetSizeTests();
bool runClearTests();
bool runSetAtIndexTests();
bool runGetAtIndexTests();
bool runConvertCoordsFlatTests();
bool runMappingTests();

// MATRIX2DTEST

UMatrix2DTest::UMatrix2DTest() {
}

void UMatrix2DTest::runTests() {
	testFunc(&runDefaultTests, "Default_Test");
	testFunc(&runSetSizeTests, "Set_Size_Test");
	testFunc(&runClearSetSizeTests, "Clear_Set_Size_Test");
	testFunc(&runClearTests, "Clear_Test");
	testFunc(&runSetAtIndexTests, "Set_Index_Test");
	testFunc(&runMappingTests, "Mapping_Test");
}


// TEST IMPLEMENTATIONS

bool runDefaultTests() {
	UMatrix2D* myTestMatrix = NewObject<UMatrix2D>();
	check(myTestMatrix != nullptr);

	// Test size
	if (myTestMatrix->getSize() != 0) {
		return false;
	}

	// Test rows and cols
	if ((myTestMatrix->getNumRows() != 0) || (myTestMatrix->getNumCols() != 0)) {
		return false;
	}

	return true;
}

bool runSetSizeTests() {
	UMatrix2D *myTestMatrix = NewObject<UMatrix2D>();
	check(myTestMatrix != nullptr);

	// Set size
	myTestMatrix->setSize(10, 100);
	if (myTestMatrix->getSize() != (10 * 100)) {
		return false;
	}

	myTestMatrix->setSize(-1, 199);
	if (myTestMatrix->getSize() != (1 * 199)) {
		return false;
	}

	return true;
}

bool runClearSetSizeTests() {
	UMatrix2D *myMatrix2D = NewObject<UMatrix2D>();
	check(myMatrix2D != nullptr);

	myMatrix2D->setSize(10, 10);
	int32 num_rows = myMatrix2D->getNumRows();
	int32 num_cols = myMatrix2D->getNumCols();
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			if (myMatrix2D->getAtIndex(i, j) != 0) {
				return false;
			}
		}
	}

	for (int i = 0; i < num_rows; i++) {
		myMatrix2D->setAtIndex(i, 0, 10);
	}

	for (int i = 0; i < num_rows; i++) {
		int32 returned_element = myMatrix2D->getAtIndex(i, 0);
		if (returned_element != 10) {
			return false;
		}
	}

	myMatrix2D->clearSetSize(2, 2);
	if (myMatrix2D->getSize() != 4) {
		return false;
	}

	for (int i = 0; i < myMatrix2D->getNumRows(); i++) {
		for (int j = 0; j < myMatrix2D->getNumCols(); j++) {
			int32 returned_element = myMatrix2D->getAtIndex(i, j);
			if (returned_element != 0) {
				return false;
			}
		}
	}

	return true;
}

bool runClearTests() {
	UMatrix2D *myMatrix2D = NewObject<UMatrix2D>();
	check(myMatrix2D != nullptr);

	myMatrix2D->setSize(10, 10);
	if (myMatrix2D->getSize() != 100) {
		return false;
	}

	myMatrix2D->clear();
	if (myMatrix2D->getSize() != 0) {
		return false;
	}

	return true;
}

bool runSetAtIndexTests() {
	UMatrix2D *myMatrix2D = NewObject<UMatrix2D>();
	check(myMatrix2D != nullptr);

	int32 invalid_element = myMatrix2D->setAtIndex(0, 0, 1);
	if (invalid_element != -1) {
		return false;
	}

	/// Bounds Testing

	myMatrix2D->setSize(2, 2);

	int32 out_of_range_row_element = myMatrix2D->setAtIndex(2, 0, 1);
	if (out_of_range_row_element != -1) {
		return false;
	}

	int32 out_of_range_col_element = myMatrix2D->setAtIndex(0, 2, 1);
	if (out_of_range_col_element != -1) {
		return false;
	}

	int32 bounded_row_element = myMatrix2D->setAtIndex(0, 1, 1);
	if (bounded_row_element != 1) {
		return false;
	}

	int32 bounded_col_element = myMatrix2D->setAtIndex(1, 0, 1);
	if (bounded_col_element != 1) {
		return false;
	}

	return true;
}

bool runMappingTests() {
	UMatrix2D *myMatrix2D = NewObject<UMatrix2D>();
	check(myMatrix2D != nullptr);

	myMatrix2D->setSize(2,2);

	const int32 num_rows = myMatrix2D->getNumRows();
	if (num_rows != 2) {
		return false;
	}

	const int32 num_cols = myMatrix2D->getNumCols();
	if (num_cols != 2) {
		return false;
	}

	myMatrix2D->setAtIndex(0, 0, 0);
	myMatrix2D->setAtIndex(0, 1, 1);
	myMatrix2D->setAtIndex(1, 0, 2);
	myMatrix2D->setAtIndex(1, 1, 3);

	int32 counter = 0;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			if (myMatrix2D->getAtIndex(i, j) != counter) {
				return false;
			}
			counter++;
		}
	}

	return true;
}
