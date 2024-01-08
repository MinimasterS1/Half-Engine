#pragma once

#ifndef HEADERPANEL_H
#define HEADERPANEL_H

#include "hlEditor.h"


class EDITOR_API HeaderPanel : public Editor

{

public:

	HeaderPanel();

	~HeaderPanel();


	void DrawHeaderPanel();

	enum SelectedTab {
		NONE,
		LEVEL,
		MATERIAL,
		PARTICLE,
		ANIMATION
	};

	SelectedTab currentTab = LEVEL;


	enum FileType {
		FILE_PART,
		FILE_LVL,
		FILE_MAT,

	};

	FileType currentFileType = FILE_PART;

	SelectedTab GetCurrentTab() const;


	void SetCurrentTab(SelectedTab tab);

private:


	bool ShowLoadFileDialog = false;
	bool ShowSaveFileDialog = false;




};

#endif