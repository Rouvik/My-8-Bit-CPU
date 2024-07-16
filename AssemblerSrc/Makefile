.SILENT:

init:
	echo "Compiling..."
	g++ assembler.cpp -o rasm
	echo "Compiled successfully!"
	echo "Setting up!"
	rm "../Programs/rasm"
	cp rasm "../Programs"

clean:
	echo "Deleting executable..."
	rm rasm
	echo "Cleanup successfull"
