# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/dropbear/. $(PROJECT_PATH)/components/dropbear/./port $(PROJECT_PATH)/components/dropbear/./libtomcrypt/src/headers $(PROJECT_PATH)/components/dropbear/./../libssh2/include $(PROJECT_PATH)/components/dropbear/./libtommath
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/dropbear -ldropbear
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += dropbear
component-dropbear-build: 
