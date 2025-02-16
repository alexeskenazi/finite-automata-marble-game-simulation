CXX = g++
CXXFLAGS = -Wall -g -std=c++11


# Specify the target
all: eskenazi_p2

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
eskenazi_p2 : eskenazi_p2.o 
	$(CXX) $(CXXFLAGS) eskenazi_p2.o -o eskenazi_p2 

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o eskenazi_p2

run: clean eskenazi_p2
	./eskenazi_p2 LLLL  0000