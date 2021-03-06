# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := ev
DEFS_Default := 

# Flags passed to all source files.
CFLAGS_Default := -fPIC -Wall -g3

# Flags passed to only C files.
CFLAGS_C_Default := 

# Flags passed to only C++ files.
CFLAGS_CC_Default := 

INCS_Default := -Ideps/libev-4.11

OBJS := $(obj).target/$(TARGET)/deps/libev-4.11/ev.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE)) $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE)) $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Default := -Wl,-E -pg 

LIBS := 

$(obj).target/deps/libev.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/deps/libev.a: LIBS := $(LIBS)
$(obj).target/deps/libev.a: TOOLSET := $(TOOLSET)
$(obj).target/deps/libev.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink)

all_deps += $(obj).target/deps/libev.a
# Add target alias
.PHONY: ev
ev: $(obj).target/deps/libev.a

# Add target alias to "all" target.
.PHONY: all
all: ev

