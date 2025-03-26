CC         = clang
TIDY      = clang-tidy
TIDY_OPTS = -checks=*

# Directories and versions
CAC_DIR    = .cache
OBJ_DIR    = $(CAC_DIR)/obj
LFT_DIR    = libft
MLX_DIR    = $(CAC_DIR)/minilibx
CRUST_DIR  = $(CAC_DIR)/crust
INC_DIR    = include/
SRC_DIR    = src/
BUILD_DIR  = build
VERSION    = 0.1.0

LFT_VER    = d04a425

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
		  -Wno-strict-prototypes -fPIC

# Linker flags
LDFLAGS = -L$(LFT_DIR) -L$(MLX_DIR) -lft -lmlx -lXext -lX11 -lm \
		  -Wl,--as-needed -Wl,-rpath,$(LFT_DIR) -Wl,-rpath,$(MLX_DIR) -Wl,-rpath,$(BUILD_DIR)

# Optimization flags based on build type

#	CCFLAGS += -O3 -march=native -flto -ffast-math -funroll-loops -fomit-frame-pointer
	CCFLAGS += -flto -O3 -g

LFT      = $(LFT_DIR)/libft.a
MLX      = $(MLX_DIR)/libmlx.a
CRUST    = $(CRUST_DIR)/build/libcrust.a

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

OBJ = $(addprefix $(OBJ_DIR)/so_long/, $(SRC:.c=.o))

all: $(NAME)

incl: $(BUILD_DIR)/include

$(NAME): $(LFT) $(MLX) $(CRUST) $(OBJ) $(OBJ_DIR)/so_long/src/so_long.o
	@$(CC) $(CCFLAGS) $(OBJ_DIR)/so_long/src/so_long.o $(OBJ) -o $(NAME) $(CRUST) $(LDFLAGS)
	@echo -e "$(GREEN)====================================\n      $(NAME) ready.\n====================================$(RESET)"

# Compile source files (dependency files generated alongside)
$(OBJ_DIR)/so_long/%.o: %.c $(LFT) $(MLX)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c $< -o $@
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

clean:
	@rm -rf $(OBJ_DIR)
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

help:
	@echo -e "$(BLUE)Usage: make [all|static|shared|clean|nclean|fclean|re|qre|incl|install|uninstall|test|help]$(RESET)"
	@echo -e "$(GREEN)all:$(RESET) Build both static and shared libraries."
	@echo -e "$(GREEN)tidy:$(RESET) Run clang-tidy on source files."
	@echo -e "$(YELLOW)clean:$(RESET) Remove object files only."
	@echo -e "$(YELLOW)nclean:$(RESET) Remove object files and the build directory."
	@echo -e "$(RED)fclean:$(RESET) Remove object files, build directory, and dependencies."
	@echo -e "$(MAG)re:$(RESET) Run fclean then build static and shared libraries."
	@echo -e "$(MAG)qre:$(RESET) Remove object files and build directory, then rebuild."

.PHONY: all static shared clean nclean fclean re qre install uninstall test help
