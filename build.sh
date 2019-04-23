set -e    # if error, stop the build
g++ src/main.cpp src/common.cpp src/tile.cpp src/prints.cpp -o pingo-edit -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./pingo-edit
