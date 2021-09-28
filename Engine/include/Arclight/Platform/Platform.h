#pragma once

#if defined(__APPLE__)
#define ARCLIGHT_PLATFORM_MACOS
#endif

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(ARCLIGHT_PLATFORM_MACOS)
#define ARCLIGHT_PLATFORM_UNIX
#endif

#ifdef __linux__
#define ARCLIGHT_PLATFORM_LINUX
#endif

#ifdef __EMSCRIPTEN__
#define ARCLIGHT_PLATFORM_WASM
#endif

namespace Arclight::Platform {

void Initialize();
void Cleanup();

} // namespace Arclight::Platform
