/*
Copyright 2021 cpyberry
https://github.com/cpyberry/pathwrap

cpyberry
email: cpyberry222@gmail.com
github: https://github.com/cpyberry
*/


#ifndef _PATHWRAP_HPP
#define _PATHWRAP_HPP


#include <filesystem>
#include <optional>
#include <stdexcept>
#include <system_error>
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


inline namespace error_code {
	inline std::filesystem::path get_special_path(const int& csidl, std::error_code& code) noexcept
	{
		const auto [result, path] = get_result_path_pair(csidl);
		if (!result) {
			code = std::make_error_code(std::errc::io_error);
		}
		return std::filesystem::path(path);
	}
}  // namespace error_code


namespace optional {
	inline std::optional<std::filesystem::path> get_special_path(const int& csidl) noexcept
	{
		const auto [result, path] = get_result_path_pair(csidl);
		if (!result) {
			return std::nullopt;
		} else {
			return std::filesystem::path(path);
		}
	}
}  // namespace optional
}  // namespace pathwrap


#endif  // _PATHWRAP_HPP
