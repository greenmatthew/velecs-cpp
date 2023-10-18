// -------------------------------------------------------------------------------
// Filename:    Debug.h
// Created by:  mgreen
// Created on:  10/17/2023 17:35:35
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

#ifdef _DEBUG
	#define DEBUG_MODE
#endif

#ifdef DEBUG_MODE

	#define DEBUG_INPUTACTION
	#ifdef DEBUG_INPUTACTION
		// #define DEBUG_INPUTACTION_HELD
	#endif

#endif