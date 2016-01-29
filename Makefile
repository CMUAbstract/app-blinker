LIBRARIES = \
	mementos \

TOOLCHAINS = \
	gcc \
	clang \
	mementos \

include maker/Makefile

# Not clear why export from maker/Makefile.env does not propagate
export LLVM_ROOT

# Paths to toolchains here if not in or different from defaults in Makefile.env

export MEMENTOS_ROOT ?= $(LIB_ROOT)/mementos
