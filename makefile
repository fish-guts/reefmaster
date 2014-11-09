RM := rm -rf
INCLUDES = -Iinclude
SRCS := $(wildcard src/*.c)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.c=.o)))
OBJ_DIR := obj
LFLAGS = -Llib
LIBS = -ldl
USER_OBJS := lib/libconfuse.a lib/libsqlite3.so.0

CC = gcc
CFLAGS = -Wall -O2 -g -c

# All Target
all: services

# Tool invocations
services: $(OBJS)
	@echo 'Building target: $@'
	
	@echo 'Invoking: GCC C Linker'
	$(CC)  -o "services" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


obj/%.o: src/%.c
	@mkdir -p obj
	@echo 'Invoking C Compiler'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'
   
# Other Targets
clean:
	$(RM) $(OBJS) $(OBJ_DIR) $(EXECUTABLES) services
	@echo ' '

.PHONY: all clean dependents
.SECONDARY:
