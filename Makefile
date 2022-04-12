CC = gcc
CFLAGS = $(shell python3-config --cflags)
CFLAGS += -c -fPIC
LDFLAGS = $(shell python3-config --embed --ldflags)
LDFLAGS += -shared
LIBPATH = -lpython3.8
MODULENAME = orafana
SRCFILE = $(MODULENAME).c
OBJFILE = $(MODULENAME).o
LIBFILE = $(MODULENAME).so

USERINCLUDES = -I/usr/include/python3.8
USERINCLUDES += -I/u01/app/ogg

$(LIBFILE):$(OBJFILE)
	$(CC) $(LDFLAGS) $(OBJFILE) -o $(LIBFILE)


$(OBJFILE):$(SRCFILE)
	$(CC) $(CFLAGS) $(USERINCLUDES) $(SRCFILE) -o $(OBJFILE)


clean:
	rm -rf $(OBJFILE) $(LIBFILE)