# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall -Iinclude

SRC_DIR=src
SCHEDULERS_DIR=$(SRC_DIR)/schedulers

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj

OBJ_COMMON=$(OBJ_DIR)/driver.o $(OBJ_DIR)/list.o $(OBJ_DIR)/CPU.o
OBJ_SCHEDULERS=$(BUILD_DIR)/fcfs.o $(BUILD_DIR)/sjf.o $(BUILD_DIR)/rr.o $(BUILD_DIR)/priority.o $(BUILD_DIR)/priority_rr.o

# Prevent make from deleting the object files
.PRECIOUS: $(OBJ_DIR)/%.o $(BUILD_DIR)/%.o

# Build rules for each executable
%: $(OBJ_COMMON) $(BUILD_DIR)/%.o
	$(CC) $(CFLAGS) -o $@ $(OBJ_COMMON) $(BUILD_DIR)/$@.o

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Pattern rule for .o files in the common source directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule for .o files in the schedulers directory
$(BUILD_DIR)/%.o: $(SCHEDULERS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) fcfs sjf rr priority priority_rr
