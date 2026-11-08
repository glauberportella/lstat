CC      ?= gcc
CFLAGS  ?= -O2 -g -Wall -Wextra -Werror -Isrc
LDLIBS  ?= -lm

# make OPENMP=1: paraleliza
# com OpenMP. Não muda o comportamento do build padrão.
ifeq ($(OPENMP),1)
  CFLAGS += -fopenmp -DLLA_OPENMP
  LDLIBS += -lm -lpthread
endif

LIB_SRC = src/utils.c src/descritive.c
LIB_NAME = lstat

OBJ_DIR  = obj
LIB_OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC))

.PHONY: all build libs static shared run clean

all: build libs

# objetos com -fPIC, usados pelos dois formatos de biblioteca
obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

build: $(LIB_SRC) src/main.c
	$(CC) $(CFLAGS) $^ -o lstat $(LDLIBS)

libs: static shared
static: $(LIB_OBJS)
	ar rcs lib$(LIB_NAME).a $(LIB_OBJS)

shared: $(LIB_OBJS)
	$(CC) -shared $(LIB_OBJS) -o lib$(LIB_NAME).so $(LDLIBS)

run: build
	./lstat

clean:
	rm -f lstat lib$(LIB_NAME).a lib$(LIB_NAME).so
	rm -rf lstat.dSYM $(OBJ_DIR)
