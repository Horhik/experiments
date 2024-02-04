cd ./build/
make sine
make phasor
make mouse

nix-jack ./sine &
nix-jack ./phasor &
nix-jack ./mouse &
