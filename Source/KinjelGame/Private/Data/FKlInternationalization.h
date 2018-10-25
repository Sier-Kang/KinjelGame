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
FKlInternationalization::Register(LOCTEXT("Menu", "Menu")); // 菜单
FKlInternationalization::Register(LOCTEXT("StartGame", "StartGame")); // 开始游戏
FKlInternationalization::Register(LOCTEXT("GameOption", "GameOption")); // 游戏设置
FKlInternationalization::Register(LOCTEXT("QuitGame", "QuitGame")); // 退出游戏

/** Enter Game Widget*/
FKlInternationalization::Register(LOCTEXT("NewGame", "NewGame")); // 新游戏
FKlInternationalization::Register(LOCTEXT("LoadRecord", "LoadRecord")); // 加载存档
FKlInternationalization::Register(LOCTEXT("ChooseRecord", "ChooseRecord")); // 选择存档
FKlInternationalization::Register(LOCTEXT("RecordName", "RecordName")); // 存档名
FKlInternationalization::Register(LOCTEXT("EnterGame", "EnterGame")); // 进入游戏
FKlInternationalization::Register(LOCTEXT("EnterRecord", "EnterRecord")); // 进入存档
FKlInternationalization::Register(LOCTEXT("RecordNameHint", "RecordNameHint")); // 输入存档名
FKlInternationalization::Register(LOCTEXT("NameRepeatHint", "NameRepeatHint")); // 输入存档名

/** Game Option */
FKlInternationalization::Register(LOCTEXT("Chinese", "Chinese")); // 中文
FKlInternationalization::Register(LOCTEXT("English", "English")); // 英文
FKlInternationalization::Register(LOCTEXT("Music", "Music")); // 音乐
FKlInternationalization::Register(LOCTEXT("Sound", "Sound")); // 音效

/** Public */
FKlInternationalization::Register(LOCTEXT("GoBack", "GoBack")); // 返回

#endif LOCTEXT_NAMESPACE
