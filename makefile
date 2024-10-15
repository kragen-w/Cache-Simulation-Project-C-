# Target to build the executable
firstTest: Memory.o Simulation.o Cache.o Set.o Block.o AddressDecoder.o PerformanceCounter.o
	g++ Memory.o Simulation.o Cache.o Set.o Block.o AddressDecoder.o PerformanceCounter.o -o firstTest

# Rule to build Memory.o
Memory.o: Memory.cc Memory.h
	g++ Memory.cc -c

# Rule to build Simulation.o
Simulation.o: Simulation.cc Memory.h Cache.h
	g++ Simulation.cc -c

# Rule to build Cache.o
Cache.o: Cache.cc Cache.h Set.h AddressDecoder.h PerformanceCounter.h
	g++ Cache.cc -c

# Rule to build Set.o
Set.o: Set.cc Set.h Block.h
	g++ Set.cc -c

# Rule to build Block.o
Block.o: Block.cc Block.h
	g++ Block.cc -c

# Rule to build AddressDecoder.o
AddressDecoder.o: AddressDecoder.cc AddressDecoder.h
	g++ AddressDecoder.cc -c

PerformanceCounter.o: PerformanceCounter.cc PerformanceCounter.h
	g++ PerformanceCounter.cc -c

# Clean rule
clean:
	rm -f *.o
	rm -f firstTest