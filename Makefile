# Lignes pour compiler et lancer le programme
compile:
	@mkdir -p build
	@g++ --std=c++2a -D_USE_MATH_DEFINES -Ofast src/main.cpp -o build/ocean
	@build/ocean
