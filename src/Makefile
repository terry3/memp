export VPATH =+ ./pub/
MEMP_INC_PATH = -I./pub
MEMP_OBJ_PATH = ../obj
CFLAGS = -Wall -g
MEMP_OBJS = memp_l.o memp_f.o memp_i.o memp_v.o
MEMP_ALL_OBJS = $(addprefix $(MEMP_OBJ_PATH)/, $(MEMP_OBJS))
MEMP_PUB_HDR =$(wildcard ./pub/*.h)


all:$(MEMP_ALL_OBJS)
	@echo $(notdir $(MEMP_ALL_OBJS))

$(MEMP_ALL_OBJS):$(MEMP_OBJ_PATH)/%.o:%.c %.h $(MEMP_PUB_HDR)
		$(CC) -c $(CFLAGS) $< -o $@ $(MEMP_INC_PATH)

.PHONY : clean
clean :
	-rm  $(MEMP_ALL_OBJS)
