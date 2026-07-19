# SPDX-License-Identifier: GPL-3.0
#
# Maintained by: 
#   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
#
# This file is main mk file.

ARCH ?= x86_64

COLOR_RESET   = \033[0m
COLOR_GREEN   = \033[1;32m
COLOR_RED     = \033[1;31m
COLOR_BLUE    = \033[1;34m
COLOR_YELLOW  = \033[1;33m

.PHONY: all kernel iso run clean doctor

all: kernel iso

C_SRC :=
ASM_SRC :=

include arch/$(ARCH)/makefile
include kernel/makefile

C_OBJ = $(patsubst %.c,build/%.o,$(C_SRC))
ASM_OBJ = $(patsubst %.asm,build/%.asm.o,$(ASM_SRC))
DEPS := $(C_OBJ:.o=.d) $(ASM_OBJ:.o=.d)
-include $(DEPS)

kernel: $(KERNEL_$(ARCH))
	@printf "$(COLOR_GREEN)[*] Kernel Build is Completed$(COLOR_RESET)\n"

$(KERNEL_$(ARCH)): $(C_OBJ) $(ASM_OBJ)

iso: iso_$(ARCH)

run: run_$(ARCH)

clean:
	@printf "$(COLOR_YELLOW)[*] Clearing Old Build...$(COLOR_RESET)\n"
	@rm -rf build/
	@rm -rf iso/
	@rm -f Linity_OS.iso
	@printf "$(COLOR_GREEN)[*] Previous Build Files Removed.$(COLOR_RESET)\n"

define run_and_log
	@mkdir -p $(dir $2)
	@cmd_output=$$($3 2>&1); status=$$?; \
	if [ $$status -ne 0 ]; then \
		printf "\r\033[K$(COLOR_RED)$1 [X]$(COLOR_RESET)\n"; \
		printf "%s\n" "$$cmd_output"; \
		exit 1; \
	elif [ -n "$$cmd_output" ]; then \
		printf "\r\033[K$(COLOR_YELLOW)$1 [WARN]$(COLOR_RESET)\n"; \
		printf "%s\n" "$$cmd_output"; \
	else \
		printf "\r\033[K$(COLOR_GREEN)$1 [OK]$(COLOR_RESET)\n"; \
	fi
endef