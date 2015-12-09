CROSS=arm-linux-

CC=$(CROSS)gcc
CPP=$(CROSS)g++
LD=$(CROSS)ld
AS=$(CROSS)as
OBJCOPY=$(CROSS)objcopy

EXEC=eh_server

INSTALLDIR=../apps/bin

ifeq ($(strip $(CROSS)),)
LIBDIR=/usr
else
LIBDIR=../libs
endif

LDFLAGS = -rdynamic $(LIBLDFLAGS) -pthread -ldl -L${LIBDIR}/lib -lemi 

CFLAGS =  -Wall -I. -DDEBUG  -D_GNU_SOURCE -g -I$(LIBDIR)/include/ -I./include


COPY        := cp
MKDIR       := mkdir -p
MV          := mv
RM          := rm -f
DIRNAME     := dirname


OBJDIR=./.obj

#PATHDIR=$(shell find -type d) 
PATHDIR=.
SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.c)) 
PATHOBJS=$(subst ./,,$(SRCS:.c=.o))
OBJS=$(patsubst %,$(OBJDIR)/%,$(PATHOBJS))

$(EXEC):$(OBJS)
	@$(CC) $(STATIC) $(OBJS) -o $@ $(LDFLAGS) 

$(OBJS):$(OBJDIR)/%.o:%.c
	@$(MKDIR) `$(DIRNAME) $@`
	@echo COMPILING $(notdir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

install:
	@echo "installing"
	@$(MKDIR) $(INSTALLDIR)
	@$(COPY) -av $(EXEC) $(INSTALLDIR)

clean:
	rm -rf $(EXEC) $(OBJDIR)
