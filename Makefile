CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -MMD -MP

TARGET_EXEC := add-masterc

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

.PHONY: all build

all: build

build: $(BUILD_DIR)/$(TARGET_EXEC)
# ----------------------------------------

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: memcheck
memcheck: $(BUILD_DIR)/$(TARGET_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--errors-for-leak-kinds=all -s --log-file=valgrind.log \
		$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: test
test: build
	@echo "Executando testes..."
	@tests/run-tests.sh

-include $(DEPS)
