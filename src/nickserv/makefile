RM := rm -rf
INCLUDES = -Iinclude
SRCS := $(wildcard src/*.c)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.c=.o)))
OBJ_DIR := ../../obj
CC = gcc
CFLAGS = -Wall -O2 -g -c

# All Target
all: nickserv

# Tool invocations
nickserv: $(OBJS)
	@echo 'Building target: $@'
	
	@echo 'Invoking: GCC C Linker'
	$(CC)  -o "services" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


../../obj/%.o: %.c
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
