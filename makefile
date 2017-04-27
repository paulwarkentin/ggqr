EXEC = ggq
SRC_DIR = src
SRC_GGQR_DIR = src/ggqr
SRC_UTILS_DIR = src/utils
OBJ_DIR = obj
BIN_DIR = bin
OBJS = $(OBJ_DIR)/mpfr_class.o \
       $(OBJ_DIR)/mpfr_matrix.o \
	   $(OBJ_DIR)/mpfr_vector.o \
	   $(OBJ_DIR)/mpfr_polynomial.o \
	   $(OBJ_DIR)/ggqr.o \
	   $(OBJ_DIR)/ggqr_lu.o \
	   $(OBJ_DIR)/ggqr_lagrange.o \
       $(OBJ_DIR)/main.o
CC = g++
DEBUG = -g -D MPFR_USE_INTMAX_T
INC = -I/opt/local/include -I/usr/local/include
LIB = -L/opt/local/lib -lgmp -lmpfr -L/usr/local/lib
CFLAGS = -Wall -c $(DEBUG) $(INC)
LFLAGS = -Wall $(DEBUG) $(INC) $(LIB)

$(EXEC) : $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_DIR)/$(EXEC)

$(OBJ_DIR)/mpfr_class.o : $(SRC_UTILS_DIR)/mpfr_class.h $(SRC_UTILS_DIR)/mpfr_class.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_UTILS_DIR)/mpfr_class.cpp -o $@

$(OBJ_DIR)/mpfr_matrix.o : $(SRC_UTILS_DIR)/mpfr_matrix.h $(SRC_UTILS_DIR)/mpfr_matrix.cpp \
                           $(SRC_UTILS_DIR)/mpfr_class.h \
						   $(SRC_UTILS_DIR)/mpfr_vector.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_UTILS_DIR)/mpfr_matrix.cpp -o $@

$(OBJ_DIR)/mpfr_vector.o : $(SRC_UTILS_DIR)/mpfr_vector.h $(SRC_UTILS_DIR)/mpfr_vector.cpp \
                           $(SRC_UTILS_DIR)/mpfr_class.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_UTILS_DIR)/mpfr_vector.cpp -o $@

$(OBJ_DIR)/mpfr_polynomial.o : $(SRC_UTILS_DIR)/mpfr_polynomial.h $(SRC_UTILS_DIR)/mpfr_polynomial.cpp \
                               $(SRC_UTILS_DIR)/mpfr_class.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_UTILS_DIR)/mpfr_polynomial.cpp -o $@

$(OBJ_DIR)/ggqr.o : $(SRC_GGQR_DIR)/ggqr.h $(SRC_GGQR_DIR)/ggqr.cpp \
                    $(SRC_UTILS_DIR)/mpfr_class.h \
					$(SRC_UTILS_DIR)/mpfr_vector.h \
					$(SRC_UTILS_DIR)/mpfr_matrix.h \
					$(SRC_UTILS_DIR)/mpfr_polynomial.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_GGQR_DIR)/ggqr.cpp -o $@

$(OBJ_DIR)/ggqr_lu.o : $(SRC_GGQR_DIR)/ggqr_lu.h $(SRC_GGQR_DIR)/ggqr_lu.cpp \
                    $(SRC_UTILS_DIR)/mpfr_class.h \
					$(SRC_UTILS_DIR)/mpfr_vector.h \
					$(SRC_UTILS_DIR)/mpfr_matrix.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_GGQR_DIR)/ggqr_lu.cpp -o $@

$(OBJ_DIR)/ggqr_lagrange.o : $(SRC_GGQR_DIR)/ggqr_lagrange.h $(SRC_GGQR_DIR)/ggqr_lagrange.cpp \
                    $(SRC_UTILS_DIR)/mpfr_class.h \
					$(SRC_UTILS_DIR)/mpfr_vector.h \
					$(SRC_UTILS_DIR)/mpfr_polynomial.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_GGQR_DIR)/ggqr_lagrange.cpp -o $@

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp \
                    $(SRC_GGQR_DIR)/ggqr.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
