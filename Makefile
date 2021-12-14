CC=gcc
OBJS=matamikya.o matamikya_order.o matamikya_product.o matamikya_print.o tests/matamikya_main.o tests/matamikya_tests.o
OBJS2= amount_set_str.o amount_set_str_node.o amount_set_str_main.o amount_set_str_tests.o 
EXEC=matamikya
EXEC2= amount_set_str 
# OBJ=mtmiya.o
DEBUG=-g -DNDEBUG# now empty, assign -g for debug
CFLAGS=-std=c99 -Wall -pedantic-errors -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@ -L. -lmtm -lm -las
# $(OBJ): $(OBJS)
# 	ld -r -o $(OBJ) $(OBJS)

$(EXEC2) : $(OBJS2)
	$(CC) $(CFLAG) $(OBJS2) -o $@ 

matamikya.o: matamikya.c matamikya.h matamikya_print.h amount_set.h \
 matamikya_order.h matamikya_product.h set.h

matamikya_product.o: matamikya_product.c matamikya_product.h matamikya.h \
amount_set.h

matamikya_order.o: matamikya_order.c matamikya_order.h amount_set.h \
 matamikya_product.h matamikya.h

matamikya_print.o: matamikya_print.c matamikya_print.h

matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h \
 tests/test_utilities.h
 
matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h \
 matamikya.h tests/test_utilities.h

amount_set_str.o: amount_set_str.c amount_set_str.h amount_set_str_node.h

amount_set_str_main.o: amount_set_str_main.c amount_set_str_tests.h \
 tests/test_utilities.h

amount_set_str_tests.o: amount_set_str_tests.c amount_set_str_tests.h \
 amount_set_str.h tests/test_utilities.h

amount_set_str_node.o: amount_set_str_node.c amount_set_str_node.h \
 amount_set_str.h


clean:
	rm -f $(OBJS) $(EXEC) $(OBJS2) $(EXEC2) 