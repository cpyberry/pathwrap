#ifndef _PATHWRAP_HPP
#define _PATHWRAP_HPP


#include <filesystem>
#include <stdexcept>
#include <utility>

#include <ShlObj.h>


namespace pathwrap {
using PathType = std::pair<const bool, const std::filesystem::path>;


inline PathType get_result_path_pair(const int& csidl) noexcept
{
	char path[MAX_PATH] = {};
	bool result = SHGetSpecialFolderPathA(nullptr, path, csidl, false);
	return std::make_pair(result, std::filesystem::path(path));
}


inline std::filesystem::path get_special_path(const int& csidl)
{
	const auto [result, path] = get_result_path_pair(csidl);
	if (result) {
		return std::filesystem::path(path);
	} else {
		throw std::runtime_error("Failed to get directory path");
	}
}
}  // namespace pathwrap


#endif  // _PATHWRAP_HPP
