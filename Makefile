# ── Simulador de Física — Makefile ────────────────────────────────────────────
#
# Targets:
#   make            build everything (launcher + all simulations)
#   make run        build and launch the CLI menu
#   make atwood     build only the atwood simulation
#   make block_slope build only the block_slope simulation
#   make clean      remove build artifacts

# ── Toolchain ─────────────────────────────────────────────────────────────────

CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -std=c11
LDFLAGS := -lraylib -lm

# Launcher links nothing extra (no raylib, no math)
LAUNCHER_LD :=

# ── Directories ───────────────────────────────────────────────────────────────

BUILD := build

# ── Subprojects ───────────────────────────────────────────────────────────────
# Add a line here for every new subproject folder.

SIMULATIONS := atwood block_slope

# Derive binary paths from subproject names
SIM_BINS := $(addprefix $(BUILD)/, $(SIMULATIONS))

# ── Phony targets ─────────────────────────────────────────────────────────────

.PHONY: all run clean $(SIMULATIONS)

# ── Default: build everything ─────────────────────────────────────────────────

all: out $(SIM_BINS)

# ── Launcher ──────────────────────────────────────────────────────────────────

out: main.c | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@ $(LAUNCHER_LD)

# ── Simulation binaries ───────────────────────────────────────────────────────
# Pattern rule: build/<name> comes from <name>/main.c

$(BUILD)/%: %/main.c | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# ── Per-name convenience targets ─────────────────────────────────────────────
# Lets you do: make block_slope

$(SIMULATIONS): %: $(BUILD)/%

# ── Run ───────────────────────────────────────────────────────────────────────

run: all
	./out

# ── Build dir ─────────────────────────────────────────────────────────────────

$(BUILD):
	mkdir -p $(BUILD)

# ── Clean ─────────────────────────────────────────────────────────────────────

clean:
	rm -rf $(BUILD)
