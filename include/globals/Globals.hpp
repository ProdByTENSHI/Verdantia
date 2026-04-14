#pragma once

#include <memory>

#include "tenshiUtil/Types.h"
#include "world/WorldGenerator.hpp"
#include "globals/Constants.hpp"
#include "memory/RscManager.hpp"
#include "render/MasterRenderer.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

inline i32 g_WindowWidth = 1280;
inline i32 g_WindowHeight = 720;

inline Camera2D g_Camera;

inline std::unique_ptr<RscManager> g_RscManager;
inline std::unique_ptr<WorldGenerator> g_WorldGenerator;
inline std::unique_ptr<MasterRenderer> g_MasterRenderer;