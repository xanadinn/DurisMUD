# CircleMUD 3.0 Makefile
#
# This makefile should work with no changes for compiling under SunOS, Ultrix,
# NeXTSTEP, HP/UX, DG/UX, and Linux.  If you're using AIX, IRIX, some version
# of SVR4 or Solaris, uncomment the appropriate lines below.  If you're using
# some other operating system not mentioned, just type 'make' and cross your
# fingers..

#compiler name and flags
CC = gcc
MYFLAGS = -g -Wall

#flags for profiling (see hacker.doc for more information)
PROFILE = 

#remove the hash marks below if compiling under AIX
#CC = cc

#remove the hash marks below if compiling under IRIX
#CC = cc -cckr -fullwarn
#MYFLAGS = -g
#LIBS = -lmalloc

#remove the hash mark below if compiling under SVR4 or Solaris, or if your
#linker complains that the socket functions such as 'connect()', 'bind()',
#etc are undefined.
#LIBS = -lsocket -lnsl

#############################################################################

CFLAGS = $(MYFLAGS) $(PROFILE)

ACTOBJ = oldconst.o actwld.o utils.o main.o random.o

all : act 

act : $(ACTOBJ)

../bin/circle : $(OBJFILES)

actwld.o : actwld.c act.h
	$(CC) -c $(CFLAGS) actwld.c
unactwld.o : unactwld.c act.h
	$(CC) -c $(CFLAGS) unactwld.c

actobj.o : actobj.c act.h
	$(CC) -c $(CFLAGS) actobj.c
unactobj.o : unactobj.c act.h
	$(CC) -c $(CFLAGS) unactobj.c

actmob.o : actmob.c act.h
	$(CC) -c $(CFLAGS) actmob.c
unactmob.o : unactmob.c act.h
	$(CC) -c $(CFLAGS) unactmob.c

oldconst.o : oldconst.c 
	$(CC) -c $(CFLAGS) oldconst.c
constants.o : constants.c structs.h
	$(CC) -c $(CFLAGS) constants.c

utils.o : utils.c act.h
	$(CC) -c $(CFLAGS) utils.c
main.o : main.c act.h
	$(CC) -c $(CFLAGS) main.c

random.o : random.c act.h
	$(CC) -c $(CFLAGS) random.c

act :
	$(CC) -o add_resources $(PROFILE) $(ACTOBJ) $(LIBS)
unact :
	$(CC) -o unact $(PROFILE) $(UNACTOBJ) $(LIBS)
