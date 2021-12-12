CC = gcc
OBJS = order.o product.o matamikya.o tests/matamikya_tests.o
EXECCS = matamikya
EXECMP = amount_set
ORDER = order.h order.c
PRODUCT = product.h product.c
AMOUNT_SET = amount_set.c amount_set.h
NODE = node.c node.h
MATAMIKYA = matamikya.c matamikya.h
LIBS = -L. -lamount_set

DEBUG_FLAG= #now empty, assign -g for debug
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

	
all:  $(EXECCS) $(EXECMP)

$(EXECCS) : $(OBJS) 
	$(CC)  $(COMP_FLAG) $(OBJS) -o matamikya $(LIBS)
	
$(EXECMP) : amount_set.o amount_set_str_tests.o
	$(CC) $(COMP_FLAG) amount_set.o amount_set_str_tests.o -o $@

node.o : $(node)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) amount_set.c

amount_set.o : $(AMOUNT_SET)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) amount_set.c

product.o : $(PRODUCT) product.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)  $*.c

order.o : $(ORDER) order.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

matamikya.o : $(MATAMIKYA) player.h tournament.h game.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

tests/matamikya_tests.o :  tests/matamikya_tests.c player.h test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $*.o
	
amount_set_str_tests.o : amount_set_str_tests.c test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $*.o
	
clean: 
	rm -f $(OBJS) $(EXECEM) $(EXECPQ) amount_set_str_tests.o matamikya.o amount_set.o
