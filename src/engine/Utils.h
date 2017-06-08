#pragma once

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
#include <imgui.h>
#include <memory>
#include <limits>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <string>
#include <typeindex>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#if defined(GLES2)
#include <GLES2/gl2.h>
#elif defined(GLES3)
#include <GLES3/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#define SAFE_DELETE(x) \
                { \
        delete x; \
        x = NULL; \
                }

// Array deletion macro
#define SAFE_DELETE_ARRAY(x) \
                { \
        delete[] x; \
        x = NULL; \
                }

#ifndef M_PI
#define M_PI 3.1415926f
#endif // M_PI