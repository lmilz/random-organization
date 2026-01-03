# ==============================================================================
# Complete Project Makefile - Build, Test & Code Quality
# ==============================================================================

# Project configuration
PROJECT_NAME := random_organization
BUILD_DIR    := build
BUILD_TYPE   ?= Release

# Source directories
SRC_DIRS     := src 
INCLUDE_DIRS := include

# File extensions
C_EXTS       := .c
CXX_EXTS     := .cpp .cc
HEADER_EXTS  := .h .hpp .hh

# Find all source files
C_SOURCES    := $(shell find $(SRC_DIRS) -type f $(foreach ext,$(C_EXTS),-o -name '*$(ext)') 2>/dev/null)
CXX_SOURCES  := $(shell find $(SRC_DIRS) -type f $(foreach ext,$(CXX_EXTS),-o -name '*$(ext)') 2>/dev/null)
HEADERS      := $(shell find $(SRC_DIRS) $(INCLUDE_DIRS) -type f $(foreach ext,$(HEADER_EXTS),-o -name '*$(ext)') 2>/dev/null)

ALL_SOURCES  := $(C_SOURCES) $(CXX_SOURCES) $(HEADERS)

# Tools
CMAKE        := cmake
MAKE_TOOL    := make
CLANG_FORMAT := clang-format
CLANG_TIDY   := clang-tidy
CTEST        := ctest

# Build configuration
NPROC        := $(shell nproc)
CMAKE_FLAGS  := -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
BUILD_FLAGS  := -j$(NPROC)

# Files
COMPILE_DB   := $(BUILD_DIR)/compile_commands.json
CMAKE_CACHE  := $(BUILD_DIR)/CMakeCache.txt

# clang-tidy flags
TIDY_FLAGS   := -p $(BUILD_DIR)

# Colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
RESET  := \033[0m

# ==============================================================================
# Build Targets
# ==============================================================================

.PHONY: all configure build test clean distclean rebuild

# Default target - build everything
all: build

# Configure project with CMake
configure: $(CMAKE_CACHE)

$(CMAKE_CACHE):
	@echo "$(YELLOW)Configuring project...$(RESET)"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) ..
	@echo "$(GREEN)✓ Configuration complete$(RESET)"

# Build project
build: configure
	@echo "$(YELLOW)Building project...$(RESET)"
	@$(MAKE_TOOL) -C $(BUILD_DIR) $(BUILD_FLAGS)
	@echo "$(GREEN)✓ Build was successfully!$(RESET)"

# Run tests
test: build
	@echo "$(YELLOW)Running tests...$(RESET)"
	@cd $(BUILD_DIR) && $(CTEST) --output-on-failure
	@if [ $$? -eq 0 ]; then \
		echo "$(GREEN)✓ Tests were successfully!$(RESET)"; \
	else \
		echo "$(RED)✗ Tests failed!$(RESET)"; \
		exit 1; \
	fi

# Build and test in one step
all-test: build test
	@echo "$(GREEN)✓ Build and tests complete!$(RESET)"

# Clean build artifacts (keep configuration)
clean:
	@echo "$(YELLOW)Cleaning build artifacts...$(RESET)"
	@if [ -d "$(BUILD_DIR)" ]; then \
		$(MAKE_TOOL) -C $(BUILD_DIR) clean 2>/dev/null || true; \
	fi
	@find . -name '*.o' -o -name '*.tmp' -o -name '*~' | xargs rm -f 2>/dev/null || true
	@echo "$(GREEN)✓ Clean complete$(RESET)"

# Clean everything including CMake cache
distclean:
	@echo "$(YELLOW)Removing build directory...$(RESET)"
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)✓ Distclean complete$(RESET)"

# Rebuild from scratch
rebuild: distclean build
	@echo "$(GREEN)✓ Rebuild complete$(RESET)"

# Reconfigure (useful when CMakeLists.txt changes)
reconfigure:
	@echo "$(YELLOW)Reconfiguring project...$(RESET)"
	@rm -f $(CMAKE_CACHE)
	@$(MAKE) configure

# ==============================================================================
# Code Quality Targets
# ==============================================================================

.PHONY: format format-check format-c format-cpp tidy tidy-fix check-tools stats

# Generate compile_commands.json (only configure, no build)
$(COMPILE_DB): configure
	@if [ ! -f "$(COMPILE_DB)" ]; then \
		echo "$(RED)✗ compile_commands.json not generated$(RESET)"; \
		exit 1; \
	fi

# Format all files in-place
format:
	@echo "$(YELLOW)Formatting all source files...$(RESET)"
	@if [ -z "$(ALL_SOURCES)" ]; then \
		echo "$(YELLOW)No source files found$(RESET)"; \
	else \
		$(CLANG_FORMAT) -i -style=file $(ALL_SOURCES); \
		echo "$(GREEN)✓ Formatting complete$(RESET)"; \
	fi

# Check formatting without modifying files
format-check:
	@echo "$(YELLOW)Checking code formatting...$(RESET)"
	@if [ -z "$(ALL_SOURCES)" ]; then \
		echo "$(YELLOW)No source files found$(RESET)"; \
	else \
		$(CLANG_FORMAT) --dry-run --Werror -style=file $(ALL_SOURCES) && \
		echo "$(GREEN)✓ All files properly formatted$(RESET)" || \
		(echo "$(RED)✗ Formatting errors found. Run 'make format' to fix.$(RESET)" && exit 1); \
	fi

# Format C files only
format-c:
	@echo "$(YELLOW)Formatting C files...$(RESET)"
	@$(CLANG_FORMAT) -i -style=file $(C_SOURCES) $(filter %.h,$(HEADERS))
	@echo "$(GREEN)✓ Done!$(RESET)"

# Format C++ files only
format-cpp:
	@echo "$(YELLOW)Formatting C++ files...$(RESET)"
	@$(CLANG_FORMAT) -i -style=file $(CXX_SOURCES) $(filter %.hpp %.hh,$(HEADERS))
	@echo "$(GREEN)✓ Done!$(RESET)"

# Run clang-tidy (analysis only)
tidy: $(COMPILE_DB)
	@echo "$(YELLOW)Running clang-tidy analysis...$(RESET)"
	@if [ -z "$(C_SOURCES)$(CXX_SOURCES)" ]; then \
		echo "$(YELLOW)No source files found$(RESET)"; \
	else \
		$(CLANG_TIDY) $(TIDY_FLAGS) $(C_SOURCES) $(CXX_SOURCES) && \
		echo "$(GREEN)✓ Analysis complete$(RESET)" || \
		(echo "$(RED)✗ Issues found$(RESET)" && exit 1); \
	fi

# Run clang-tidy with automatic fixes
tidy-fix: $(COMPILE_DB)
	@echo "$(YELLOW)Running clang-tidy with automatic fixes...$(RESET)"
	@$(CLANG_TIDY) $(TIDY_FLAGS) -fix $(C_SOURCES) $(CXX_SOURCES)
	@echo "$(GREEN)✓ Fixes applied$(RESET)"

# Check for required tools
check-tools:
	@echo "$(YELLOW)Checking for required tools...$(RESET)"
	@which $(CMAKE) > /dev/null || (echo "$(RED)Error: cmake not found!$(RESET)" && exit 1)
	@which $(MAKE_TOOL) > /dev/null || (echo "$(RED)Error: make not found!$(RESET)" && exit 1)
	@which $(CLANG_FORMAT) > /dev/null || (echo "$(RED)Error: clang-format not found!$(RESET)" && exit 1)
	@which $(CLANG_TIDY) > /dev/null || (echo "$(RED)Error: clang-tidy not found!$(RESET)" && exit 1)
	@echo "$(GREEN)✓ All tools available$(RESET)"

# Show project statistics
stats:
	@echo "$(BLUE)Project Statistics:$(RESET)"
	@echo "==================="
	@echo "Build type:    $(BUILD_TYPE)"
	@echo "C files:       $(words $(C_SOURCES))"
	@echo "C++ files:     $(words $(CXX_SOURCES))"
	@echo "Header files:  $(words $(HEADERS))"
	@echo "Total files:   $(words $(ALL_SOURCES))"
	@echo ""
	@if [ -n "$(ALL_SOURCES)" ]; then \
		echo "Lines of code:"; \
		cat $(ALL_SOURCES) 2>/dev/null | wc -l; \
	fi

# ==============================================================================
# Combined Workflows
# ==============================================================================

.PHONY: check ci install

# Pre-commit check: format + tidy
check: format-check tidy
	@echo "$(GREEN)✓ All checks passed!$(RESET)"

# CI workflow: check + build + test
ci: format-check build test tidy
	@echo "$(GREEN)✓ CI workflow complete!$(RESET)"

# Install built artifacts (if CMake install is configured)
install: build
	@echo "$(YELLOW)Installing...$(RESET)"
	@$(MAKE_TOOL) -C $(BUILD_DIR) install
	@echo "$(GREEN)✓ Installation complete$(RESET)"

# ==============================================================================
# Debug Targets
# ==============================================================================

.PHONY: debug release debug-build release-build

# Build with debug symbols
debug:
	@$(MAKE) BUILD_TYPE=Debug build

# Build optimized release
release:
	@$(MAKE) BUILD_TYPE=Release build

# Debug build + test
debug-test:
	@$(MAKE) BUILD_TYPE=Debug all-test

# Release build + test
release-test:
	@$(MAKE) BUILD_TYPE=Release all-test

# ==============================================================================
# Help
# ==============================================================================

.PHONY: help

help:
	@echo "$(BLUE)Project Makefile - Build, Test & Code Quality$(RESET)"
	@echo "=============================================="
	@echo ""
	@echo "$(YELLOW)Build Targets:$(RESET)"
	@echo "  all            - Build the project (default)"
	@echo "  configure      - Run CMake configuration"
	@echo "  build          - Compile the project"
	@echo "  test           - Run tests"
	@echo "  all-test       - Build and run tests"
	@echo "  clean          - Remove build artifacts (keep configuration)"
	@echo "  distclean      - Remove entire build directory"
	@echo "  rebuild        - Clean and rebuild from scratch"
	@echo "  reconfigure    - Reconfigure CMake (when CMakeLists.txt changes)"
	@echo ""
	@echo "$(YELLOW)Code Quality Targets:$(RESET)"
	@echo "  format         - Format all source files in-place"
	@echo "  format-check   - Check formatting without modifying files"
	@echo "  format-c       - Format only C files"
	@echo "  format-cpp     - Format only C++ files"
	@echo "  tidy           - Run clang-tidy analysis"
	@echo "  tidy-fix       - Run clang-tidy with automatic fixes"
	@echo "  check          - Run format-check + tidy"
	@echo ""
	@echo "$(YELLOW)Build Type Targets:$(RESET)"
	@echo "  debug          - Build with Debug configuration"
	@echo "  release        - Build with Release configuration"
	@echo "  debug-test     - Debug build + tests"
	@echo "  release-test   - Release build + tests"
	@echo ""
	@echo "$(YELLOW)Utility Targets:$(RESET)"
	@echo "  check-tools    - Verify required tools are installed"
	@echo "  stats          - Show project statistics"
	@echo "  ci             - Full CI workflow (format-check + build + test + tidy)"
	@echo "  install        - Install built artifacts"
	@echo ""
	@echo "$(YELLOW)Variables:$(RESET)"
	@echo "  BUILD_TYPE     - Build type: Debug or Release (default: Release)"
	@echo ""
	@echo "$(YELLOW)Examples:$(RESET)"
	@echo "  make                    # Build project"
	@echo "  make test               # Build and run tests"
	@echo "  make format             # Format all code"
	@echo "  make check              # Pre-commit checks"
	@echo "  make ci                 # Full CI workflow"
	@echo "  make BUILD_TYPE=Debug   # Build in debug mode"
	@echo "  make rebuild            # Clean rebuild"