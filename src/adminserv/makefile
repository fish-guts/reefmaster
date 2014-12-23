RM := rm -rf
INCLUDES = -I../../include/
INICKSERV = -I../../include/nickserv/
ICHANSERV = -I../../include/chanserv/ 
IBOTSERV = -I../../include/botserv/ 
IPOPERSERV = -I../../include/operserv/ 
IADMINSERV = -I../../include/adminserv/ 
SRCS := $(wildcard *.c)
OBJS := $(addprefix ../../obj/,$(notdir $(SRCS:.c=.o)))
OBJ_DIR := ../../obj
CC = gcc
CFLAGS = -Wall -O2 -g -c

# All Target
all: adminserv

# Tool invocations
adminserv: $(OBJS)
	@echo 'Building target: $@'

../../obj/%.o: %.c
	@mkdir -p ../../obj
	@echo 'Invoking C Compiler'
	$(CC) $(CFLAGS) $(INCLUDES) $(INICKSERV) $(ICHANSERV) $(IBOTSERV) $(IOPERSERV) $(IADMINSERV) -o $@ $<
	@echo 'done...'
   
# Other Targets
clean:
	$(RM) $(OBJS) $(OBJ_DIR) 
	@echo ' '