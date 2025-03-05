# ComputerVision

## Compile Notes
MacOS: clang++ -arch arm64 -std=c++17 source.cpp -o program \
    -I/opt/homebrew/include/opencv4 \
    -L/opt/homebrew/lib \
    -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
