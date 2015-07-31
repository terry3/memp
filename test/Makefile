export VPATH =+ ../src/
MAKE = make
MAKE_CLEAN =make clean
T_EXE = memp_test
MEMP_OBJ_PATH = $(abspath ../obj)
CCFLAGS = -g -Wall
T_MEMP_CC = t_memp_l.cc t_memp_main.cc t_memp_m.cc t_memp.cc
T_MEMP_OBJS = t_memp_l.o t_memp_main.o t_memp_m.o t_memp.o
T_MEMP_ALL_OBJS = $(addprefix $(MEMP_OBJ_PATH)/, $(T_MEMP_OBJS))
T_MEMP_SRC_PATH = $(abspath ../src)
T_MEMP_SRC_PUB_PATH = $(abspath ../src/pub)
MEMP_OBJS = memp_l.o memp_f.o memp_i.o memp_v.o
MEMP_ALL_OBJS = $(addprefix $(MEMP_OBJ_PATH)/, $(MEMP_OBJS))

GTEST_DIR = /home/terry3/terry3/soft/gtest-1.7.0

$(T_EXE): $(T_MEMP_ALL_OBJS) $(MEMP_ALL_OBJS)
	g++ $(CCFLAGS)  $(MEMP_OBJ_PATH)/* -o  $@ -lgtest -lpthread

$(T_MEMP_ALL_OBJS): $(MEMP_OBJ_PATH)/%.o:%.cc
	g++ -isystem $(GTEST_DIR)/include -c $(CCFLAGS) $< -o $@ -I$(T_MEMP_SRC_PATH) -I$(T_MEMP_SRC_PUB_PATH)

$(MEMP_ALL_OBJS):$(MEMP_OBJ_PATH)/%.o:%.c %.h
	cd $(T_MEMP_SRC_PATH) && $(MAKE)

.PHONY : clean
clean :
	cd $(T_MEMP_SRC_PATH) && $(MAKE_CLEAN)
	-rm $(T_EXE)
