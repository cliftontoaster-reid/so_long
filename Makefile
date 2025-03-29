CC         = clang
TIDY      = clang-tidy
TIDY_OPTS = -checks=*

# Directories and versions
CAC_DIR    = .cache
OBJ_DIR    = $(CAC_DIR)/obj
LFT_DIR    = libft
MLX_DIR    = $(CAC_DIR)/minilibx
CRUST_DIR  = $(CAC_DIR)/crust
OPUS_DIR   = $(CAC_DIR)/opus-1.5.2
OPENAL_DIR = $(CAC_DIR)/openal-soft

OPENAL_INC = $(OPENAL_DIR)/include
OPUS_INC = $(OPUS_DIR)/include

INC_DIR    = include/
SRC_DIR    = src/
BUILD_DIR  = build
VERSION    = 0.1.1-$(shell git rev-parse --short HEAD)

LFT_VER    = aaf4737

# ANSI Color Variables
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
MAG    = \033[0;35m
CYAN   = \033[0;36m
RESET  = \033[0m

# Compiler and flags
# Build configuration
DEBUG ?= 0
SANITIZE ?= 0

# Base compiler flags
CCFLAGS = -Wall -Wextra -Werror -Wpedantic -MMD -MP \
		  -I$(INC_DIR) -I$(LFT_DIR) -I$(MLX_DIR) -I$(CRUST_DIR)/build/include \
		  -Wno-strict-prototypes -fPIC -I$(OPENAL_INC) -I$(OPUS_INC) \
		  -DVERSION=\"$(VERSION)\" \

# Linker flags
LDFLAGS = -L$(LFT_DIR) -L$(MLX_DIR) -lft -lmlx -lXext -lX11 -lm \
		  -L$(OPUS_DIR)/.libs -lopus \
		  -Wl,--as-needed -Wl,-rpath,$(LFT_DIR) -Wl,-rpath,$(MLX_DIR) -Wl,-rpath,$(BUILD_DIR)

# Optimization flags based on build type

CCFLAGS += -O3 -march=native -flto -ffast-math -funroll-loops -fomit-frame-pointer
CCFLAGS += -flto -O3 -g

LFT      = $(LFT_DIR)/libft.a
MLX      = $(MLX_DIR)/libmlx.a
CRUST    = $(CRUST_DIR)/build/libcrust.a
OPUS     = $(OPUS_DIR)/.libs/libopus.a
OPENAL   = $(OPENAL_DIR)/build/libopenal.so

NAME     = so_long

# Allow user override for parallelism.
NPROC ?= $(shell nproc)

# Source files
SRC = \
	$(SRC_DIR)map/map_is_size_valid.c \
	$(SRC_DIR)map/map_is_char_valid.c \
	$(SRC_DIR)map/map_is_closed.c \
	$(SRC_DIR)map/map_is_player.c \
	$(SRC_DIR)map/map_is_collectible.c \
	$(SRC_DIR)map/map_is_exit.c \
	$(SRC_DIR)map/map_run_checks.c \
	$(SRC_DIR)map/map_from_str.c \
	$(SRC_DIR)map/map_free.c \
	$(SRC_DIR)map/map_is_valid.c \
	$(SRC_DIR)map/find_neibours.c \
	$(SRC_DIR)map/map_find_player.c \
	$(SRC_DIR)map/map_find_exit.c \
	$(SRC_DIR)map/map_find_collectibles.c \
	$(SRC_DIR)map/map_walllst.c \
	$(SRC_DIR)map/map_wallvar.c \
	\
	$(SRC_DIR)utils/fs_exists.c \
	$(SRC_DIR)utils/fs_read_file.c \
	$(SRC_DIR)utils/ft_strerr.c \
	$(SRC_DIR)utils/log_error.c \
	$(SRC_DIR)utils/log_info.c \
	$(SRC_DIR)utils/log_warning.c \
	$(SRC_DIR)utils/log_debug.c \
	$(SRC_DIR)utils/key_hook.c \
	$(SRC_DIR)utils/kthxbye.c \
	$(SRC_DIR)utils/move.c \
	$(SRC_DIR)utils/setup_ass.c \
	\
	$(SRC_DIR)data/del.c \
	\
	$(SRC_DIR)render/pos_scale.c \
	$(SRC_DIR)render/random.c \
	$(SRC_DIR)render/render_floor.c \
	$(SRC_DIR)render/render_cosmetic.c \
	$(SRC_DIR)render/render_exit.c \
	$(SRC_DIR)render/render_wall.c \
	$(SRC_DIR)render/compute_wall_connections.c \
	$(SRC_DIR)render/get_neighbour_count.c \
	$(SRC_DIR)render/find_neibours.c \
	$(SRC_DIR)render/render_guy.c \
	$(SRC_DIR)render/render.c \
	$(SRC_DIR)render/cosmetic_init.c \
	$(SRC_DIR)render/render_dummy.c \
	\
	$(SRC_DIR)render/wall/lgbt.c \
	$(SRC_DIR)render/wall/utils.c \
	$(SRC_DIR)render/wall/hull.c \
	$(SRC_DIR)render/wall/tbone.c \
	$(SRC_DIR)render/wall/t600.c \
	$(SRC_DIR)render/wall/t600_con.c \
	$(SRC_DIR)render/wall/t600_corn.c \
	$(SRC_DIR)render/wall/t600_lon.c \
	$(SRC_DIR)render/wall/bi.c \
	\
	$(SRC_DIR)artificial_stupidity/didummy_reach_player.c \
	$(SRC_DIR)artificial_stupidity/move_dummy.c \
	$(SRC_DIR)artificial_stupidity/setup_dummies.c \
	\
	$(SRC_DIR)text/draw_char.c \
	$(SRC_DIR)text/draw_text.c \
	$(SRC_DIR)text/create_text.c \

OBJ = $(addprefix $(OBJ_DIR)/so_long/, $(SRC:.c=.o))

all:
# Preparing build environment
	@echo -e "$(YELLOW)====================================\n      Preparing build environment...\n====================================$(RESET)"
	@docker build -t solongbuilder -f tools/Dockerfile . &> /dev/null
	@echo -e "$(YELLOW)====================================\n      Build environment ready.\n====================================$(RESET)"
	@docker run --rm -v $$(pwd):/app:Z --user $$(id -u):$$(id -g) -w /app solongbuilder make build -j$(NPROC)

build: $(NAME)

incl: $(BUILD_DIR)/include

$(NAME): $(OPENAL) $(OPUS) $(LFT) $(MLX) $(CRUST) $(OBJ) $(OBJ_DIR)/so_long/src/so_long.o
	@$(CC) $(CCFLAGS) -DLOG_LEVEL=$(DEBUG) $(OBJ_DIR)/so_long/src/so_long.o $(OBJ) -o $(NAME) $(CRUST) $(LDFLAGS)
	@echo -e "$(GREEN)====================================\n      $(NAME) ready.\n====================================$(RESET)"

# Compile source files (dependency files generated alongside)
$(OBJ_DIR)/so_long/%.o: %.c $(LFT) $(MLX)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -DLOG_LEVEL=$(DEBUG) -c $< -o $@
	@echo -e "$(MAG)Compiled: $<$(RESET)"

$(LFT):
	@if [ ! -d "$(LFT_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n      Cloning libft...\n====================================$(RESET)"; \
		git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); \
	fi
	@cd $(LFT_DIR) && current_commit=$$(git rev-parse HEAD); \
		if [ "$$current_commit" != "$(LFT_VER)" ]; then \
			git fetch origin; \
		fi
	@cd $(LFT_DIR) && git checkout $(LFT_VER) &>/dev/null
	@$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft CFLAGS+=" -fPIC" -j$(NPROC)
	@echo -e "$(GREEN)====================================\n       libft ready.\n====================================$(RESET)"

$(MLX):
	@mkdir -p $(CAC_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n    Cloning minilibx...\n====================================$(RESET)"; \
		git clone https://github.com/42Paris/minilibx-linux $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR) CFLAGS+=" -fPIC -I$(abspath $(MLX_DIR))" -j$(NPROC)
	@echo -e "$(GREEN)====================================\n    minilibx ready.\n====================================$(RESET)"

$(CRUST):
	@mkdir -p $(CAC_DIR)
	@if [ ! -d "$(CRUST_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n    Cloning crust...\n====================================$(RESET)"; \
		git clone https://github.com/cliftontoaster-reid/crust $(CRUST_DIR); \
	fi
	@$(MAKE) -C $(CRUST_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/crust CFLAGS+=" -fPIC" -j$(NPROC)
	@echo -e "$(GREEN)====================================\n    crust ready.\n====================================$(RESET)"

$(OPUS):
	@mkdir -p $(CAC_DIR)
# Download tar ball
	@echo -e "$(YELLOW)====================================\n    Downloading opus...\n====================================$(RESET)"
	@curl -o $(CAC_DIR)/opus.tar.gz https://ftp.osuosl.org/pub/xiph/releases/opus/opus-1.5.2.tar.gz
# Extract tar ball
	@echo -e "$(YELLOW)====================================\n    Extracting opus...\n====================================$(RESET)"
	@tar -xzf $(CAC_DIR)/opus.tar.gz -C $(CAC_DIR)
# Build opus
	@echo -e "$(YELLOW)====================================\n    Building opus...\n====================================$(RESET)"
	@cd $(CAC_DIR)/opus-1.5.2 && cmake .
	@cd $(CAC_DIR)/opus-1.5.2 && ./configure --enable-static --disable-shared
	@cd $(CAC_DIR)/opus-1.5.2 && make -j$(NPROC)
	@echo -e "$(GREEN)====================================\n    opus ready.\n====================================$(RESET)"

$(OPENAL):
	@mkdir -p $(CAC_DIR)
	# Clone OpenAL Soft repository
	@echo -e "$(YELLOW)====================================\n    Cloning OpenAL Soft...\n====================================$(RESET)"
	@if [ ! -d "$(OPENAL_DIR)" ]; then \
		git clone https://github.com/kcat/openal-soft $(OPENAL_DIR); \
	fi
	@cd $(OPENAL_DIR)/build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cd $(OPENAL_DIR)/build && make -j$(NPROC)
	@echo -e "$(GREEN)====================================\n    OpenAL Soft ready.\n====================================$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
# If opus / openal directories are not empty, run make clean
	@if [ -d "$(OPUS_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n    Cleaning opus...\n====================================$(RESET)"; \
		cd $(OPUS_DIR) && make clean || true; \
	fi
	@if [ -d "$(OPENAL_DIR)" ]; then \
		echo -e "$(YELLOW)====================================\n    Cleaning OpenAL Soft...\n====================================$(RESET)"; \
		cd $(OPENAL_DIR)/build && make clean || true; \
	fi
	@echo -e "$(RED)====================================\n   Cleaned object files.\n====================================$(RESET)"

nclean: clean
	@rm -rf $(BUILD_DIR)
	@echo -e "$(RED)====================================\nCleaned objects and build directory.\n====================================$(RESET)"

fclean: nclean
	@rm -rf $(LFT_DIR) $(CAC_DIR)
	@echo -e "$(RED)====================================\n Fully cleaned dependencies and artifacts.\n====================================$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all -j$(NPROC)

qre:
	@$(MAKE) nclean
	@$(MAKE) all -j$(NPROC)

install: all
	@echo -e "$(YELLOW)====================================\n        Installing $(NAME)...\n====================================$(RESET)"
	@sudo cp -r $(BUILD_DIR)/include/* /usr/local/include/
	@sudo cp $(BUILD_DIR)/$(NAME)-$(VERSION).a /usr/local/lib/
	@sudo cp $(BUILD_DIR)/$(NAME)-$(VERSION).so /usr/local/lib/
	@sudo ln -sf $(NAME)-$(VERSION).a /usr/local/lib/$(NAME).a
	@sudo ln -sf $(NAME)-$(VERSION).so /usr/local/lib/$(NAME).so
	@echo -e "$(GREEN)====================================\n      Installation complete.\n====================================$(RESET)"

uninstall:
	@echo -e "$(YELLOW)====================================\n      Uninstalling $(NAME)...\n====================================$(RESET)"
	@echo -e "$(BLUE)====================================\n   Deleting include files...\n====================================$(RESET)"
	@for file in $(shell ls $(BUILD_DIR)/include); do \
		sudo rm -rf /usr/local/include/$$file; \
	done
	@sudo rm -f /usr/local/lib/$(NAME).a
	@sudo rm -f /usr/local/lib/$(NAME).so
	@echo -e "$(GREEN)====================================\n    Uninstallation complete.\n====================================$(RESET)"

test: all
	@$(MAKE) -C $(abspath tests) \
		OBJ_DIR=$(abspath $(OBJ_DIR))/tests \
		CAC_DIR=$(abspath $(CAC_DIR)) \
		LFT_DIR=$(abspath $(LFT_DIR)) \
		MLX_DIR=$(abspath $(MLX_DIR)) \
		BUILD_DIR=$(abspath $(BUILD_DIR)) \
		INC_DIR=$(abspath $(INC_DIR)) \
		CRUST_DIR=$(abspath $(CRUST_DIR)) \
		EXT_OBJ="$(abspath $(OBJ))" \
		-j$(NPROC)

	@echo -e "$(CYAN)====================================\n         Tests executed.\n====================================$(RESET)"


# Add this rule near your other targets
tidy:
	@echo -e "$(YELLOW)====================================\n      Running clang-tidy...\n====================================$(RESET)"
	@$(TIDY) $(TIDY_OPTS) $(SRC) -- $(CCFLAGS)
	@echo -e "$(GREEN)====================================\n      clang-tidy complete.\n====================================$(RESET)"

bonus:
	@if ! git rev-parse --is-inside-work-tree &>/dev/null; then \
		echo -e "$(RED)Not in a git repository. Cannot switch to bonus branch.$(RESET)"; \
		exit 1; \
	fi
	@echo -e "$(YELLOW)====================================\n      Switching to bonus branch...\n====================================$(RESET)"
	@if git diff --quiet && git diff --cached --quiet; then \
		echo -e "$(BLUE)Working directory clean, no need to stash.$(RESET)"; \
	else \
		echo -e "$(BLUE)Stashing changes before switching branches...$(RESET)"; \
		git stash save "Auto-stash before switching to bonus branch"; \
	fi
	@if git show-ref --verify --quiet refs/heads/bonus; then \
		echo -e "$(BLUE)Bonus branch found locally, switching...$(RESET)"; \
		git checkout bonus; \
	else \
		echo -e "$(BLUE)Bonus branch not found locally, checking remotes...$(RESET)"; \
		remote=$$(git remote | head -n1); \
		if [ -z "$$remote" ]; then \
			echo -e "$(RED)No git remotes found. Cannot get bonus branch.$(RESET)"; \
			exit 1; \
		fi; \
		if git fetch $$remote bonus:bonus; then \
			echo -e "$(GREEN)Bonus branch fetched, switching...$(RESET)"; \
			git checkout bonus; \
		else \
			echo -e "$(RED)Could not find bonus branch in remote.$(RESET)"; \
			exit 1; \
		fi; \
	fi
	@$(MAKE) re

bundle: all
	@mkdir -p $(BUILD_DIR)
	@echo -e "$(YELLOW)====================================\n      Bundling $(NAME)...\n====================================$(RESET)"
	@tar -czf $(BUILD_DIR)/$(NAME).tar.gz $(NAME) ./assets ./LICENCE ./README.md

help:
	@echo -e "$(BLUE)Usage: make [all|static|shared|clean|nclean|fclean|re|qre|incl|install|uninstall|test|help]$(RESET)"
	@echo -e "$(GREEN)all:$(RESET) Build both static and shared libraries."
	@echo -e "$(GREEN)tidy:$(RESET) Run clang-tidy on source files."
	@echo -e "$(GREEN)bonus:$(RESET) Switch to the bonus branch."
	@echo -e "$(GREEN)bundle:$(RESET) Create a tarball of the project."
	@echo -e "$(YELLOW)clean:$(RESET) Remove object files only."
	@echo -e "$(YELLOW)nclean:$(RESET) Remove object files and the build directory."
	@echo -e "$(RED)fclean:$(RESET) Remove object files, build directory, and dependencies."
	@echo -e "$(MAG)re:$(RESET) Run fclean then build static and shared libraries."
	@echo -e "$(MAG)qre:$(RESET) Remove object files and build directory, then rebuild."

.PHONY: all static shared clean nclean fclean re qre install uninstall test help
