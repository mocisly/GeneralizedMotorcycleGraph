#include <iostream>

#include "gui/Viewer.h"

#include <nsessentials/util/GLDebug.h>

int main()
{
	try
	{
#if _WIN32
		std::cout.imbue(std::locale("en-US"));
#else	
		std::cout.imbue(std::locale("en_US.utf8"));
#endif
	}
	catch (...)
	{
		std::cerr << "Warning: Could not set english locale." << std::endl;
	}

	nanogui::init();

	{
		nanogui::ref<Viewer> viewer = new Viewer();
		viewer->setVisible(true);

		nse::util::GLDebug::SetupDebugCallback();
		nse::util::GLDebug::IgnoreGLError(131185);

		try
		{
			nanogui::mainloop();
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
		}

	}

	nanogui::shutdown();

	return 0;
}

//#include <iostream>
//#include <string>
//#include <chrono>
//#include <cstring>
//#include <fstream>
//#include <cmath>
//#include <sys/stat.h>  // 用于检查文件是否存在
//
//#ifdef _WIN32
//#include <direct.h>    // Windows下的目录操作
//#define STAT _stat
//#else
//#include <unistd.h>    // Linux/Unix下的目录操作
//#define STAT stat
//#endif
//
//#include "Data.h"
//
//// 检查文件是否存在（替代std::filesystem::exists）
//bool fileExists(const std::string& filename) {
//    struct STAT buffer;
//    return (STAT(filename.c_str(), &buffer) == 0);
//}
//
//// 获取文件扩展名
//std::string getFileExtension(const std::string& filename) {
//    size_t dotPos = filename.find_last_of(".");
//    if (dotPos == std::string::npos) {
//        return "";
//    }
//    return filename.substr(dotPos + 1);
//}
//
//void printUsage(const char* programName) {
//    std::cout << "Usage: " << programName << " [options] -i <input_file> -o <output_file>\n";
//    std::cout << "Options:\n";
//    std::cout << "  -i, --input <file>        Input mesh file (.ply, .obj)\n";
//    std::cout << "  -o, --output <file>       Output file (.obj for textured, .ply for untextured)\n";
//    std::cout << "  --merge-triangles         Merge triangulated quads (default: false)\n";
//    std::cout << "  --angle-threshold <deg>   Angle threshold for merging (default: 20)\n";
//    std::cout << "  --quad-layout             Calculate quad layout (default: true)\n";
//    std::cout << "  --classify-singularities  Classify singularities (default: true)\n";
//    std::cout << "  --merge-regions           Merge fenced regions (default: true)\n";
//    std::cout << "  --split-non-rectangular   Split non-rectangular patches (default: true)\n";
//    std::cout << "  --parametrization         Calculate parametrization (default: true)\n";
//    std::cout << "  --parametric-edge-length <float> Target parametric edge length (default: 10.0)\n";
//    std::cout << "  --error-threshold <float> Parametrization error threshold (default: 50)\n";
//    std::cout << "  --time-limit <minutes>    Optimization time limit in minutes (default: 5, 0=unlimited)\n";
//    std::cout << "  --mip-level <level>       MIP level for texture (default: 0)\n";
//    std::cout << "  --invisible-seams         Use invisible seams (if available)\n";
//    std::cout << "  --pack-texture            Pack texture coordinates (default: true)\n";
//    std::cout << "  -h, --help                Show this help message\n";
//    std::cout << "\nExamples:\n";
//    std::cout << "  " << programName << " -i input.obj -o output.obj\n";
//    std::cout << "  " << programName << " -i input.ply -o output.obj --parametric-edge-length 8.0 --time-limit 10\n";
//    std::cout << "  " << programName << " -i input.obj -o output.ply --quad-layout --no-parametrization\n";
//}
//
//int main(int argc, char* argv[]) {
//    // 设置默认参数
//    std::string inputFile, outputFile;
//    bool mergeTriangles = false;
//    float angleThreshold = 20.0f; // 度
//    bool calculateQuadLayout = true;
//    bool classifySingularities = true;
//    bool mergeRegions = true;
//    bool splitNonRectangular = true;
//    bool calculateParametrization = true;
//    float parametricEdgeLength = 10.0f;
//    float errorThreshold = 50.0f;
//    float timeLimitMinutes = 5.0f;
//    int mipLevel = 0;
//    bool useInvisibleSeams = false;
//    bool packTexture = true;
//
//    // 解析命令行参数
//    for (int i = 1; i < argc; ++i) {
//        std::string arg = argv[i];
//
//        if (arg == "-i" || arg == "--input") {
//            if (i + 1 < argc) inputFile = argv[++i];
//        }
//        else if (arg == "-o" || arg == "--output") {
//            if (i + 1 < argc) outputFile = argv[++i];
//        }
//        else if (arg == "--merge-triangles") {
//            mergeTriangles = true;
//        }
//        else if (arg == "--angle-threshold") {
//            if (i + 1 < argc) angleThreshold = std::stof(argv[++i]);
//        }
//        else if (arg == "--no-quad-layout") {
//            calculateQuadLayout = false;
//        }
//        else if (arg == "--quad-layout") {
//            calculateQuadLayout = true;
//        }
//        else if (arg == "--no-classify-singularities") {
//            classifySingularities = false;
//        }
//        else if (arg == "--classify-singularities") {
//            classifySingularities = true;
//        }
//        else if (arg == "--no-merge-regions") {
//            mergeRegions = false;
//        }
//        else if (arg == "--merge-regions") {
//            mergeRegions = true;
//        }
//        else if (arg == "--no-split-non-rectangular") {
//            splitNonRectangular = false;
//        }
//        else if (arg == "--split-non-rectangular") {
//            splitNonRectangular = true;
//        }
//        else if (arg == "--no-parametrization") {
//            calculateParametrization = false;
//        }
//        else if (arg == "--parametrization") {
//            calculateParametrization = true;
//        }
//        else if (arg == "--parametric-edge-length") {
//            if (i + 1 < argc) parametricEdgeLength = std::stof(argv[++i]);
//        }
//        else if (arg == "--error-threshold") {
//            if (i + 1 < argc) errorThreshold = std::stof(argv[++i]);
//        }
//        else if (arg == "--time-limit") {
//            if (i + 1 < argc) timeLimitMinutes = std::stof(argv[++i]);
//        }
//        else if (arg == "--mip-level") {
//            if (i + 1 < argc) mipLevel = std::stoi(argv[++i]);
//        }
//        else if (arg == "--invisible-seams") {
//            useInvisibleSeams = true;
//        }
//        else if (arg == "--no-pack-texture") {
//            packTexture = false;
//        }
//        else if (arg == "--pack-texture") {
//            packTexture = true;
//        }
//        else if (arg == "-h" || arg == "--help") {
//            printUsage(argv[0]);
//            return 0;
//        }
//        else {
//            std::cerr << "Unknown option: " << arg << "\n\n";
//            printUsage(argv[0]);
//            return 1;
//        }
//    }
//
//    // 检查必需参数
//    if (inputFile.empty() || outputFile.empty()) {
//        std::cerr << "Error: Input and output files are required!\n\n";
//        printUsage(argv[0]);
//        return 1;
//    }
//
//    // 检查输入文件是否存在
//    if (!fileExists(inputFile)) {
//        std::cerr << "Error: Input file '" << inputFile << "' does not exist!\n";
//        return 1;
//    }
//
//    try {
//        // 设置locale
//        try {
//#if _WIN32
//            std::cout.imbue(std::locale("en-US"));
//#else    
//            std::cout.imbue(std::locale("en_US.utf8"));
//#endif
//        }
//        catch (...) {
//            std::cerr << "Warning: Could not set english locale." << std::endl;
//        }
//
//        std::cout << "Starting mesh processing...\n";
//        std::cout << "Input: " << inputFile << "\n";
//        std::cout << "Output: " << outputFile << "\n";
//
//        // 创建Data对象
//        Data data;
//
//        auto startTime = std::chrono::steady_clock::now();
//
//        // 1. 加载网格
//        std::cout << "Loading mesh...\n";
//        data.LoadMesh(inputFile, mergeTriangles, angleThreshold * (float)M_PI / 180.0f);
//
//        auto loadTime = std::chrono::steady_clock::now();
//        std::cout << "Mesh loaded in "
//            << std::chrono::duration_cast<std::chrono::milliseconds>(loadTime - startTime).count()
//            << " ms\n";
//        std::cout << "Vertices: " << data.Vertices().cols() << ", Faces: " << data.Faces().size() << "\n";
//
//        // 2. 计算四边形布局（对应ExtractQuadLayout函数）
//        if (calculateQuadLayout) {
//            std::cout << "Calculating quad layout...\n";
//
//            if (classifySingularities) {
//                std::cout << "Classifying singularities...\n";
//                data.ClassifyAllSingularities();
//            }
//
//            if (mergeRegions) {
//                std::cout << "Merging fenced regions...\n";
//                data.TryToMergePatches();
//            }
//
//            std::cout << "Calculating motorcycle graph...\n";
//            data.CalculateMotorcycleGraph(true); // deactivate unnecessary motorcycles
//
//            std::cout << "Extracting patches...\n";
//            auto stats = data.ExtractPatches(splitNonRectangular);
//
//            auto layoutTime = std::chrono::steady_clock::now();
//            std::cout << "Quad layout calculated in "
//                << std::chrono::duration_cast<std::chrono::milliseconds>(layoutTime - loadTime).count()
//                << " ms\n";
//
//            // 输出统计信息（对应原代码中的统计输出）
//            std::sort(stats.patchSizes.begin(), stats.patchSizes.end());
//            std::cout << "Patch statistics: " << stats << std::endl;
//
//            // 计算非原始边数量（对应原代码中的统计）
//            int nonOriginalEdges = 0;
//            if (data.Motorcycles() != nullptr) {
//                for (auto& patch : data.Motorcycles()->Patches()) {
//                    for (auto& side : patch.PatchSides()) {
//                        for (auto arcIdx : side) {
//                            auto& arc = data.Motorcycles()->Halfarcs()[arcIdx];
//                            for (auto p : arc) {
//                                auto e = data.Mesh().edge_handle(data.Motorcycles()->MotorcycleHalfedge(p));
//                                if (!data.IsEdgeOriginal(e))
//                                    ++nonOriginalEdges;
//                            }
//                        }
//                    }
//                }
//                std::cout << "Used " << nonOriginalEdges / 2 << " non-original edges." << std::endl;
//            }
//        }
//        else {
//            std::cout << "Skipping quad layout calculation.\n";
//        }
//
//        // 3. 计算参数化（对应parameterizationBtn回调函数）
//        if (calculateParametrization) {
//            // 检查四边形布局是否存在（对应原代码中的检查）
//            if (data.Motorcycles() == nullptr || data.Motorcycles()->Patches().size() == 0) {
//                std::cerr << "Error: A quad layout is needed to calculate the parametrization.\n";
//                std::cerr << "Please enable quad layout calculation with --quad-layout option.\n";
//                return 1;
//            }
//
//            std::cout << "Calculating parametrization...\n";
//
//            // 设置时间限制
//            std::chrono::steady_clock::duration timeLimit =
//                (timeLimitMinutes == 0) ?
//                std::chrono::steady_clock::duration::max() :
//                std::chrono::seconds(static_cast<int>(timeLimitMinutes * 60));
//
//            // 选择算法策略（对应原代码中的ArclengthStrategy选择）
//            ArclengthStrategy arclengthStrategy = useInvisibleSeams ?
//                ArclengthStrategy::GurobiGlobal : ArclengthStrategy::Simple;
//
//            int mipFactor = 1 << mipLevel;
//
//            // 计算参数化（对应原代码中的data.CalculateParametrization调用）
//            data.CalculateParametrization(
//                parametricEdgeLength / mipFactor,
//                errorThreshold,
//                timeLimit,
//                arclengthStrategy
//            );
//
//            // 评估参数化质量（对应原代码中的Statistics评估）
//            Statistics ratios, mips;
//            data.EvaluateParametrization(ratios, mips, true);
//
//            // 打包纹理（对应原代码中的data.PackTexture调用）
//            if (packTexture) {
//                std::cout << "Packing texture...\n";
//                data.PackTexture(mipFactor);
//                std::cout << "Texture packed.\n";
//            }
//
//            auto paramTime = std::chrono::steady_clock::now();
//            std::cout << "Parametrization calculated in "
//                << std::chrono::duration_cast<std::chrono::milliseconds>(paramTime - loadTime).count()
//                << " ms\n";
//        }
//        else {
//            std::cout << "Skipping parametrization calculation.\n";
//        }
//
//        // 4. 保存结果
//        std::cout << "Saving result...\n";
//        std::string ext = getFileExtension(outputFile);
//        if (ext == "obj") {
//            data.SaveMeshOBJ(outputFile);
//            std::cout << "Saved textured mesh as OBJ: " << outputFile << "\n";
//        }
//        else if (ext == "ply") {
//            data.SaveMeshPLY(outputFile);
//            std::cout << "Saved untextured mesh as PLY: " << outputFile << "\n";
//        }
//        else {
//            // 默认保存为OBJ
//            data.SaveMeshOBJ(outputFile);
//            std::cout << "Saved textured mesh as OBJ: " << outputFile << "\n";
//        }
//
//        auto endTime = std::chrono::steady_clock::now();
//        auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
//
//        std::cout << "Processing completed successfully in " << totalTime << " ms\n";
//
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error during processing: " << e.what() << std::endl;
//        return 1;
//    }
//    catch (...) {
//        std::cerr << "Unknown error occurred during processing." << std::endl;
//        return 1;
//    }
//
//    return 0;
//}
