// #include <assert.h>
// #include <paradem/gdal.h>
// #include <paradem/memory.h>
// #include <paradem/raster.h>
// #include <paradem/timeInfo.h>
// #include <paradem/timer.h>
#include <paradem/tool.h>

// #include <CLI/CLI.hpp>
// #include <cereal/archives/binary.hpp>
// #include <cereal/types/map.hpp>
// #include <cereal/types/vector.hpp>
// #include <exception>
// #include <iostream>
// #include <map>
// #include <vector>

using namespace std;

// split and merge again
// merge works now
int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "[usage]: ratser_compare file1 file2" << endl;
        return -1;
    }

    string file1 = argv[1];
    string file2 = argv[2];

    cout << file1 << "," << file2 << endl;
    // compare results
    comPareResults(file1, file2);
    // string infile = "/home/kong/github/ParallelFlowDirections/test_data/tileDEM/0_0.tif";
    // std::cout << "3.------Divided tiles!------" << std::endl;
    // generateTiles(outputDEMFile.c_str(), tileHeight, tileWidth, outputtileDEMfolder.c_str());
    // gdalinfo(infile.c_str());
    return 0;
}
