# Lignes pour compiler et lancer le programme
compile:
	@mkdir -p build
	@g++ --std=c++2a src/main.cpp -o build/ocean
	@build/ocean
