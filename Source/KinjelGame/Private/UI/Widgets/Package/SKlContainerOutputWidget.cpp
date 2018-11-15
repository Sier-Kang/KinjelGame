// Fill out your copyright notice in the Description page of Project Settings.

#include "SKlContainerOutputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SKlContainerOutputWidget::Construct(const FArguments& InArgs)
{
	SKlContainerBaseWidget::Construct(
		SKlContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKlContainerOutputWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	if (ObjectIndex == 0) {
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	if (InputID == ObjectIndex && MultiplyAble(InputID))
	{
		OutputID = ObjectIndex;
		OutputNum = (InputNum + ObjectNum <= 64) ? (InputNum + ObjectNum) : 64;
		ObjectNum = (InputNum + ObjectNum <= 64) ? 0 : (InputNum + ObjectNum - 64);

		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);

		return;
	}


	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	CompoundOutput.ExecuteIfBound(ObjectIndex, ObjectNum);

	ThrowObject.ExecuteIfBound(InputID, InputNum);
}

void SKlContainerOutputWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	if (ObjectIndex == 0) {
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	if (InputID == 0) {
		OutputID = ObjectIndex;

		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);

		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);

		//ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);

		return;
	}

	if (InputID == ObjectIndex && MultiplyAble(InputID)) {
		OutputID = ObjectIndex;

		int PreOutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);

		OutputNum = (PreOutputNum + InputNum <= 64) ? (PreOutputNum + InputNum) : 64;

		ObjectNum = ObjectNum - (OutputNum - InputNum);

		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);

		//ResetContainerPara(ObjectNum == 0 ? 0 : ObjectIndex, ObjectNum);

		return;
	}

	OutputID = ObjectIndex;

	OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);

	CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);

	ThrowObject.ExecuteIfBound(InputID, InputNum);
}
