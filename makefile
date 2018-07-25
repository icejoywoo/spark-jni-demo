CC=g++
CFLAGS=-Wall
OBJS=Base64.o
all: libbase64.so

Base64.o: Base64.cpp
	$(CC) $(CFLAGS) -I${JAVA_HOME}/include \
	        -I${JAVA_HOME}/include/linux \
	  -fpic -c $< -o $@

libbase64.so: $(OBJS)
	g++ -shared -o $@ $(OBJS)
	rm -f $(OBJS)
.PHONY : clean
clean:
	rm -f $(OBJS) libbase64.so
