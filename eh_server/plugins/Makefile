CROSS=arm-linux-

CC=$(CROSS)gcc
CPP=$(CROSS)g++
LD=$(CROSS)ld
AS=$(CROSS)as
OBJCOPY=$(CROSS)objcopy

EXEC=lib

INSTALLDIR=../../apps
INSTALL_RECIEVER_DIR=$(INSTALLDIR)/reciever
INSTALL_TRIGGER_DIR=$(INSTALLDIR)/trigger

ifeq ($(strip $(CROSS)),)
LIBDIR=/usr
else
LIBDIR=../../libs
endif

LDFLAGS = -shared -L$(LIBDIR)/lib -lemi -lcrypt

CFLAGS = -fPIC -Wall -O2 -I. -DDEBUG -g -I$(LIBDIR)/include/ -I./include -I../include


COPY        := cp
MKDIR       := mkdir -p
MV          := mv
RM          := rm -f
DIRNAME     := dirname


OBJDIR=./.objs

RECIEVER_PATHDIR=reciever
RECIEVER_SRCS= $(foreach dir,$(RECIEVER_PATHDIR),$(wildcard $(dir)/*.c)) 
RECIEVER_OBJS=$(patsubst %,$(OBJDIR)/%,$(subst ./,,$(RECIEVER_SRCS:.c=.o)))
RECIEVER_SOBJS=$(RECIEVER_OBJS:.o=.so)

TRIGGER_PATHDIR=trigger
TRIGGER_SRCS= $(foreach dir,$(TRIGGER_PATHDIR),$(wildcard $(dir)/*.c)) 
TRIGGER_OBJS=$(patsubst %,$(OBJDIR)/%,$(subst ./,,$(TRIGGER_SRCS:.c=.o)))
TRIGGER_SOBJS=$(TRIGGER_OBJS:.o=.so)

SOOBJS=$($(notdir RECIEVER_OBJS):.o=.so) $($(notdir TRIGGER_OBJS):.o=.so)


$(EXEC):$(SOOBJS)

$(SOOBJS):%.so:%.o
	@$(CC) $(LDFLAGS)  -o $@ $<

$(TRIGGER_OBJS):$(OBJDIR)/%.o:%.c
	@$(MKDIR) `$(DIRNAME) $@`
	@echo COMPILING $(notdir $@)
	@$(CC)  $(CFLAGS) -c -o $@ $<

$(RECIEVER_OBJS):$(OBJDIR)/%.o:%.c
	@$(MKDIR) `$(DIRNAME) $@`
	@echo COMPILING $(notdir $@)
	@$(CC)  $(CFLAGS) -c -o $@ $<


install:
	@echo "installing"
	@$(RM)	$(INSTALL_RECIEVER_DIR)/*
	@$(RM)	$(INSTALL_TRIGGER_DIR)/*
	@$(MKDIR) $(INSTALL_RECIEVER_DIR)
	@cp -av $(RECIEVER_SOBJS) $(INSTALL_RECIEVER_DIR)
	@$(MKDIR) $(INSTALL_TRIGGER_DIR)
	@cp -av $(TRIGGER_SOBJS) $(INSTALL_TRIGGER_DIR)


clean:
	rm -rf $(EXEC) $(OBJDIR)
