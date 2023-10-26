#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

std::optional<std::string> LoadTextFile(const std::string& filename);
 