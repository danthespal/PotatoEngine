#pragma once

// C/C++
#include <stdint.h>
#include <assert.h>
#include <typeinfo>
#include <memory>
#include <unordered_map>
#include <string>

#if defined(_WIN64)
#include <DirectXMath.h>
#endif

// common headers
#include "PrimitiveTypes.h"
#include "..\Utilities\Math.h"
#include "..\Utilities\Utilities.h"
#include "..\Utilities\MathTypes.h"
#include "PrimitiveTypes.h"
#include "Id.h"

#ifdef _DEBUG
#define DEBUG_OP(x) x
#else
#define DEBUG_OP(x) (void(0))
#endif