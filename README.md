# pathwrap

You can get the special path of windows in modern C++.

## Requirement

* C++17

## Usage

You can get the desktop path in the following cases.

If it fails, a runtime_error is thrown.

```c++
#include <filesystem>

#include <ShlObj.h>
#include "pathwrap.hpp"


std::filesystem::path path = pathwrap::get_special_path(CSIDL_DESKTOP);
```

If you don't want to be thrown an exception:

```c++
#include <filesystem>
#include <optional>
#include <system_error>

#include <ShlObj.h>
#include "pathwrap.hpp"


std::error_code code;
std::filesystem::path path_code = pathwrap::get_special_path(CSIDL_DESKTOP, code);
std::filesystem::path path_code = pathwrap::error_code::get_special_path(CSIDL_DESKTOP, code);
// this uses error_code instead of throwing an exception.
// The error_code namespace is an inline namespace, so both are the same.

std::optional<std::filesystem::path> path_optional = pathwrap::optional::get_special_path(CSIDL_APPDATA);
// You can also use std::optional.

if (!path_code) {
	// Processing when acquisition of special path is successful.
}

if (path_optional.has_value()) {
	// Processing when acquisition of special path is successful.
}
```

## Founder

* [cpyberry](https://github.com/cpyberry)

	email: cpyberry222@gmail.com
