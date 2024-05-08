
if [ "$1" = "all" ]
then
	echo "Chose to build 'all'"

	mkdir -pv build/obj

	echo "Compiling..."
	gcc -c -o build/obj/main.o src/main.c -Wall -Wextra
	gcc -c -o build/obj/evm.o src/evm.c -Wall -Wextra
	gcc -c -o build/obj/instr.o src/instr.c -Wall -Wextra
	gcc -c -o build/obj/loader.o src/loader.c -Wall -Wextra

	echo "Linking..."
	gcc -o build/evm build/obj/main.o build/obj/evm.o build/obj/instr.o build/obj/loader.o

	echo "Done!"
fi

if [ "$1" = "clean" ]
then
	echo "Cleaning build files..."
	rm -rv build
fi
