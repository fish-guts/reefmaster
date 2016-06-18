RM := rm -rf
INCLUDES = -Iinclude 
SRCS := $(wildcard src/*.c src/nickserv/*.c src/chanserv/*.c src/botserv/*.c src/operserv/*.c src/adminserv/*.c src/db/*.c)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.c=.o))) 
OBJ_DIR := obj
LFLAGS = -Llib
LIBS = -ldl
USER_OBJS := lib/libconfuse.a lib/libsqlite3.so.0

CC = gcc
CFLAGS = -Wall -O2 -g -c
CD = @cd
DBDIR = db
FIXTURE_FILE = db/fixture.sql
DATABASE = db/services.db

# All Target
   all: db.loadSchema services 

# Tool invocations
services: $(OBJS) 
	@echo 'Building target: $@'
	
	@echo 'Invoking: GCC C Linker'
	$(CC)  -o "services" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

obj/%.o: src/nickserv/%.c
	@mkdir -p obj
	@echo 'Compiling Nickserv'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'
	
obj/%.o: src/chanserv/%.c
	@mkdir -p obj
	@echo 'Compiling Chanserv'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'
		
obj/%.o: src/botserv/%.c
	@mkdir -p obj
	@echo 'Compiling Botserv'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'

obj/%.o: src/operserv/%.c
	@mkdir -p obj
	@echo 'Compiling Operserv'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'
	
obj/%.o: src/adminserv/%.c
	@mkdir -p obj
	@echo 'Compiling Adminserv'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

	@echo 'done...'

obj/%.o: src/db/%.c
	@mkdir -p obj
	@echo 'Compiling Database Files'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'

obj/%.o: src/%.c
	@mkdir -p obj
	@echo 'Compiling Main Files'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<
	@echo 'done...'
   
# Other Targets
clean:
	$(RM) $(OBJS) $(OBJ_DIR) $(EXECUTABLES) services
	@echo ' '

.PHONY: all clean dependents
.SECONDARY:


# build fixture database
db.loadFixture:	
	@echo "Loading fixture Database..."
	@echo "Removing old schema"
	@rm -f $(DATABASE)
	@echo "Initializing fixture data"
	@sqlite3 -init $(FIXTURE_FILE) $(DATABASE) &
	@echo ""
	@echo "Build successful!"
	
# build default schema with no recrods
db.loadSchema:
	@echo "Loading Database..."
	@echo "Removing old schema"
	@rm -f $(DATABASE)
	@echo "Initializing database schema"
	@sqlite3 -init $(SCHEMA_FILE) $(DATABASE) &
	@echo "Build successful!"