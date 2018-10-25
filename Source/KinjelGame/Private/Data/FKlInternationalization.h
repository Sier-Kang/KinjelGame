// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FKlInternationalization
{
public:
	static void Register(FText vlaue) {
		return;
	}
};

#define LOCTEXT_NAMESPACE "KlMenu"

/** Menu Widget */
FKlInternationalization::Register(LOCTEXT("Menu", "Menu")); // �˵�
FKlInternationalization::Register(LOCTEXT("StartGame", "StartGame")); // ��ʼ��Ϸ
FKlInternationalization::Register(LOCTEXT("GameOption", "GameOption")); // ��Ϸ����
FKlInternationalization::Register(LOCTEXT("QuitGame", "QuitGame")); // �˳���Ϸ

/** Enter Game Widget*/
FKlInternationalization::Register(LOCTEXT("NewGame", "NewGame")); // ����Ϸ
FKlInternationalization::Register(LOCTEXT("LoadRecord", "LoadRecord")); // ���ش浵
FKlInternationalization::Register(LOCTEXT("ChooseRecord", "ChooseRecord")); // ѡ��浵
FKlInternationalization::Register(LOCTEXT("RecordName", "RecordName")); // �浵��
FKlInternationalization::Register(LOCTEXT("EnterGame", "EnterGame")); // ������Ϸ
FKlInternationalization::Register(LOCTEXT("EnterRecord", "EnterRecord")); // ����浵
FKlInternationalization::Register(LOCTEXT("RecordNameHint", "RecordNameHint")); // ����浵��
FKlInternationalization::Register(LOCTEXT("NameRepeatHint", "NameRepeatHint")); // ����浵��

/** Game Option */
FKlInternationalization::Register(LOCTEXT("Chinese", "Chinese")); // ����
FKlInternationalization::Register(LOCTEXT("English", "English")); // Ӣ��
FKlInternationalization::Register(LOCTEXT("Music", "Music")); // ����
FKlInternationalization::Register(LOCTEXT("Sound", "Sound")); // ��Ч

/** Public */
FKlInternationalization::Register(LOCTEXT("GoBack", "GoBack")); // ����

#endif LOCTEXT_NAMESPACE
