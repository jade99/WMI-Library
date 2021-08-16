#pragma once

#ifndef _DLLDEFINITION_H
#define _DLLDEFINITION_H

#ifdef BUILD_DLL
#define DLLDECL __declspec(dllexport)
#else
#define DLLDECL __declspec(dllimport)
#endif

#endif