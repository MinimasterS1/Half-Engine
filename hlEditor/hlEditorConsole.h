#pragma once


#ifndef EDITORCONSOLE_H
#define EDITORCONSOLE_H

#include "hlEditor.h"

class ENGINE_API Console : public Editor

{

public:

	Console();

	~Console();

	void DrawConsole();

};
#endif
