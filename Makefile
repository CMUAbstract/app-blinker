# Override any paths to toolchains here if different from defaults in Makefile.env

LIBRARIES = \
	mementos \

TOOLCHAINS = \
	gcc \
	clang \

include maker/Makefile

# Not clear why export from maker/Makefile.env does not propagate
export LLVM_ROOT
