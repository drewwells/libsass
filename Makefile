

build: sassc.cpp document.cpp node.cpp token.cpp prelexer.cpp
	g++ -o bin/sassc sassc.cpp document.cpp node.cpp token.cpp prelexer.cpp

test: build
	ruby spec.rb spec/basic/

clean:
	rm -rf *.o
	rm -rf bin/*