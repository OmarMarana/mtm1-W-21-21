CC=gcc
OBJS= matamikya.o product.o order.o matamikya_print.c tests/matamikya_main.o tests/matamikya_tests.o
EXEC=matamikya
OBJ=matamikya.o
DEBUG=-g -DNDEBUG# now empty, assign -g for debug
CFLAGS=-std=c99 -Wall -pedantic-errors -Werror $(DEBUG)

$(EXEC) : $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $@ -L. -lmtm -lm -las
$(OBJ): $(OBJS)
	ld -r -o $(OBJ) $(OBJS)

matamikya.o: matamikya.c matamikya.h matamikya_print.h amount_set.h \
 order.h product.h set.h
product.o: product.c product.h matamikya.h amount_set.h
order.o: order.c order.h amount_set.h product.h matamikya.h
matamikya_print.o: matamikya_print.c matamikya_print.h
matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h \
 tests/test_utilities.h
matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h \
 tests/../matamikya.h tests/test_utilities.h


clean:
	rm -f $(OBJS) $(OBJ) $(EXEC)