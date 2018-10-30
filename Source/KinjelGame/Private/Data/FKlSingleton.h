// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class T>
class FKlSingleton
{
public:
	static TSharedPtr<T> Get();

private:
	static void Initialize();

	static TSharedRef<T> Create();

private:
	static TSharedPtr<T> TInstance;
};

template<class T>
TSharedPtr<T> FKlSingleton<T>::TInstance = nullptr;

template<class T>
TSharedPtr<T> FKlSingleton<T>::Get()
{
	Initialize();

	return TInstance;
}

template<class T>
void FKlSingleton<T>::Initialize()
{
	if (!TInstance.IsValid())
	{
		TInstance = Create();
	}
}

template<class T>
TSharedRef<T> FKlSingleton<T>::Create()
{
	TSharedRef<T> TRef = MakeShareable(new T());

	return TRef;
}

