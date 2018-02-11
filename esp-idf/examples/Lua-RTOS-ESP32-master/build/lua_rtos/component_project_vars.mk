# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/lua_rtos/. $(PROJECT_PATH)/components/lua_rtos/.. $(PROJECT_PATH)/components/lua_rtos/Lua/adds $(PROJECT_PATH)/components/lua_rtos/Lua/common $(PROJECT_PATH)/components/lua_rtos/Lua/modules $(PROJECT_PATH)/components/lua_rtos/Lua/platform $(PROJECT_PATH)/components/lua_rtos/Lua/src $(PROJECT_PATH)/components/lua_rtos/./lwip/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/lua_rtos -Wl,--whole-archive -llua_rtos -Wl,--no-whole-archive -L$(PROJECT_PATH)/components/lua_rtos/ld -T lua_rtos.ld
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += lua_rtos
component-lua_rtos-build: 
