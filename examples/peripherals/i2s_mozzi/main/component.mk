#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

CFLAGS += -DESP32
CXXFLAGS += -DESP32

COMPONENT_ADD_INCLUDEDIRS := .
#COMPONENT_ADD_LDFLAGS
