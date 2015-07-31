lib=memp.so
CFLAGS = -Wall -g
OBJS = memp_core.o


all:$(OBJS)
	$(CC) -o memp.so

$(OBJS):%.o:%.c %.h $(PUB_HDR)
		$(CC) -c $(CFLAGS) $< -o $@

$(lib):$(OBJS)
	$(CC) -o $@ -shared $^

.PHONY : clean
clean :
	-rm  $(MEMP_ALL_OBJS)
#TODO: FINISH THIS MAKEFILE!
