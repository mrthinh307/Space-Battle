all:
	g++	-I src/include -L src/lib -o run run.cpp Common.cpp BaseObject.cpp TankObject.cpp BulletObject.cpp ThreatsObject.cpp ExplosionObject.cpp FontText.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	./run