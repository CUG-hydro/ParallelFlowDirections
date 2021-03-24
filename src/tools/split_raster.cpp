#include <assert.h>
#include <paradem/gdal.h>
#include <paradem/memory.h>
#include <paradem/raster.h>
#include <paradem/timeInfo.h>
#include <paradem/timer.h>
#include <paradem/tool.h>

#include <CLI/CLI.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <exception>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

void split_tiles(string infile, string outdir, int tileHeight, int tileWidth) {
    dir_valid(outdir);
    generateTiles(infile.c_str(), tileHeight, tileWidth, outdir.c_str());
}

// split and merge again
// merge works now
int main(int argc, char** argv) {

    string infile = "test_data/dem.tif";
    string outdir = "OUTPUT/dem_tiles/";

    // string indir = "test_data/tileDEM";
    // string inputFile = indir + "/tileInfo.txt";
    split_tiles(infile, outdir, 300, 400);

    string infile_tiles = outdir + "/tileInfo.txt";
    GridInfo gridInfo;
    std::vector<TileInfo> tileInfos;
    readTXTInfo(infile_tiles, tileInfos, gridInfo);

    /** test  for merge files*/
    // gridInfo.tileHeight = tileHeight;
    // gridInfo.tileWidth = tileWidth;
    std::string outfile = "OUTPUT/merge.tif";
    merge_tiles(tileInfos, gridInfo, outfile.c_str());

    // compare results
    comPareResults(infile, outfile);
    // string infile = "/home/kong/github/ParallelFlowDirections/test_data/tileDEM/0_0.tif";
    // std::cout << "3.------Divided tiles!------" << std::endl;
    // generateTiles(outputDEMFile.c_str(), tileHeight, tileWidth, outputtileDEMfolder.c_str());
    // gdalinfo(infile.c_str());
    return 0;
}

// void raster_merge(string indir_tiles, string outputFile) {
//     std::cout << "5.------Merge images!-----" << std::endl;
//     GridInfo gridInfo;
//     std::string inputFile = indir_tiles + "/" + "tileInfo.txt";

//     std::vector<TileInfo> tileInfos;
//     readTXTInfo(inputFile, tileInfos, gridInfo);

//     gridInfo.grandHeight = height;
//     gridInfo.grandWidth = width;
//     gridInfo.tileHeight = tileHeight;
//     gridInfo.tileWidth = tileWidth;

//     std::string outputFile = outputPath + "/merge.tif";
//     mergeTiles(gridInfo, outputFile.c_str());
// }

// void hello(){
//     if (argc < 3) {
//         std::cout << "Too few arguments." << std::endl;
//         std::cout << "This program can run test cases on randomly generated DEMs." << std::endl;
//         std::cout << "To run test cases on randomly generated DEMs, use the following command: " << std::endl;
//         std::cout << "mpirun -np <PROCESSES_NUMBER> test <OUTPUT_PATH_OF_DEM> <HEIGHT_OF_THE_DEM > <WIDTH_OF_THE_DEM> <OUTPUT_PATH_OF_SEQUENTIAL_FLOW_DIRECTIONS> <TILE_HEIGHT> <TILE_WIDTH> <DIVIDE_FOLDER> <OUTPUT_FOLDER_OF_PARALLEL_FLOW_DIRECIOTNS>" << std::endl;
//         std::cout << "This command first generates a Perlin noise DEM with given height and width. Then, Calculating the flow directions of the DEM using the sequential Barnes algorithm and our proposed parallel algorithm. Finally, Comparing the flow directions of the two algorithms. " << std::endl;
//         std::cout << "Example usage: mpirun -np 4 test ./test_data/dem.tif 2000 3000 ./test_data/seqFlow/seqFlow.tif 500 800 ./test_data/tileDEM ./test_data/paraFlow " << std::endl;
//         return -1;
//     }

//     //---------generate DEM with perling DEM--------
//     // CLI::App app("Parallel-Flow-Directions Test Program");
//     // std::cout << "generate DEM with perling DEM" << size << std::endl;
//     std::string outputDEMFile;
//     std::string outputsequentialFlow;
//     int height, width;
//     int tileHeight, tileWidth;
//     std::string outputtileDEMfolder, outputPath;
//     app.add_option("outputDEMFile", outputDEMFile, "Path of GeoTif output file")->required();
//     app.add_option("height", height, "The height of the generated DEM is a numeric constant")->required();
//     app.add_option("width", width, "The width of the generated DEM is a numeric constant")->required();
//     app.add_option("GeoTif of flow-directions", outputsequentialFlow, "Path of GeoTif output file")->required();
//     app.add_option("tileHeight", tileHeight, "The height of the divied tile is a numeric constant")->required();
//     app.add_option("tileWidth", tileWidth, "The width of the divied tile is a numeric constant")->required();
//     app.add_option("outputDEMFolder", outputtileDEMfolder, "Path of DEMs output folder")->required();
//     app.add_option("outputPath", outputPath, "Path of flow-directions output folder")->required();

//     CLI11_PARSE(app, argc, argv);
//     std::cout << "The program is running  with test mode." << std::endl;
//     std::cout << "Path of DEM output file: " << outputDEMFile << std::endl;
//     std::cout << "Height of DEM: " << height << std::endl;
//     std::cout << "Width of DEM: " << width << std::endl;
//     std::cout << "Output file of flow-directions: " << outputsequentialFlow << std::endl;
//     std::cout << "Height of tile: " << tileHeight << std::endl;
//     std::cout << "Width of tile: " << tileWidth << std::endl;
//     std::cout << "Path of DEMs output folder: " << outputtileDEMfolder << std::endl;
//     std::cout << "Path of flow-directions output folder: " << outputPath << std::endl;

//     // check directory
//     dir_valid(dirname(outputDEMFile));
//     dir_valid(dirname(outputsequentialFlow));
//     dir_valid(outputtileDEMfolder);
//     dir_valid(outputPath);

//     std::cout << "1.------Generate DEM!------" << std::endl;
//     createPerlinNoiseDEM(outputDEMFile, height, width);

//     //----------sequential Barnes flow direction--------
//     std::cout << "2.------Sequential flow directions!------" << std::endl;
//     PerformAlgorithm(outputDEMFile, outputsequentialFlow);

//     //-----------divide tiles--------------------
//     std::cout << "3.------Divided tiles!------" << std::endl;
//     generateTiles(outputDEMFile.c_str(), tileHeight, tileWidth, outputtileDEMfolder.c_str());

//     // std::cout << "4.------Parallel computing!------" << std::endl;
//     // Timer timer_master;
//     // timer_master.start();
//     // Timer timer_overall;
//     // timer_overall.start();
//     // gridInfo.inputFolder = outputtileDEMfolder;
//     // gridInfo.outputFolder = outputPath;
//     // timer_overall.stop();
//     // std::cerr << "Preparer time = " << timer_overall.elapsed() << "s" << std::endl;
//     // ObjectFactory objectFactory;
//     // hostProcess(gridInfo, tileInfos, &objectFactory);
// }
