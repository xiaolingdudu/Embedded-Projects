TARGET:=main	#可执行文件
SOURCES:=  #指定所有源文件.c
OBJS:= #指定所有的中间文件.o
CC:=arm-linux-gcc       #指定编译器 如果需要在开发板上运行 这里改成arm-linux-gcc
INCS:=-I ./inc#指定头文件搜索路径
INCS+=-I /usr/local/arm/arm_libs/include #jpeg头文件搜索路径
INCS+=-I ./inc/libxml2
LIBS:=-L ./lib #指定库文件搜索路径
LIBS+=-L /usr/local/arm/arm_libs/lib #jpeg库搜索路径
LIBNAME:=-l pthread #指定库名字
#LIBNAME+=-l jpeg
LIBNAME+=-lxml2
LIBNAME+=-lz
LIBNAME+=-lm
LIBNAME+=-ljpeg
SOURCES+=$(wildcard src/*.c)#展开所有的.c文件 赋值给SOURCES
OBJS+=$(patsubst %.c,%.o,$(SOURCES))

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(INCS) $(LIBS) $(LIBNAME)
	
%.o:%.c
	$(CC) -c $< -o $@ $(INCS) $(LIBS) $(LIBNAME)

clean:
	rm -rf $(TARGET) $(OBJS) #递归删除 删除文件夹