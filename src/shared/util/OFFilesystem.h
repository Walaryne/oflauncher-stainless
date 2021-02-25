//
// Created by int on 29/01/21.
//

#if __cplusplus >= 201703L || _MSVC_LANG >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
