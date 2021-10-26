obj-m := lab1_2.o

KDIR := /home/bac3k/Загрузки/linux-5.14.14

all:
	cppcheck --enable=all --inconclusive --library=posix lab1_2.c
	/home/bac3k/Загрузки/linux-5.14.14/scripts/checkpatch.pl -f lab1_2.c
	$(MAKE) -C $(KDIR) M=$$PWD 



clean:
	rm -rf lab1_2 *.o *.ko *.mod *.dwo *.mod.c Module.symvers modules.order
	rm -rf lab1 *.o *.ko *.mod *.dwo *.mod.c Module.symvers modules.order
