cc=gcc
target=demo
obj=main.o fun.o start_mplayer.o console.o
cflgs=-Wall -std=c99

$(target):$(obj)
	$(cc) $^ -o $@ $(cflgs)
%.o:%.c
	$(cc) -c $< -o $@ $(cflgs)

clean:
	rm $(target) $(obj)