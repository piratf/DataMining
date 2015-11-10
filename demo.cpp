#include "general.h"
#include "kmeans.h"
#include "kmediods.h"
#include "Distance.h"
#include "Matrix.h"
#include "knn.h"
#include "knnopenmp.h"
#include "id3.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <omp.h>

using vecSizeT = std::vector<double>::size_type;
const double TIMES = 100000;

void inline unitTestKKMeansDensity(Group &test, std::ofstream &output) {
    // 数据归一化
    // normaliztion(test);

    // 输出读入的数据
    // puts("Print Input Data:");
    // puts("=====================================");
    // test.display();
    // puts("=====================================\n");

    // k 值
    const unsigned k = 3;

    /** 准备测试数据 */
    // Kmeans + Density initialize
    // std::vector<Group> centroid = buildInitialPointDensity(k, test);

    output << "===============================================" << std::endl;
    output << "buildInitialPointDensity" << std::endl;
    output << "===============================================" << std::endl;
    // 重复运行测试
    std::vector<Group> result;
    std::vector<double> avg(k);
    double SSE = 0;
    // 记录每次的 SSE 值
    std::vector<double> vecSSE;
    time_t start = std::clock();
    for (unsigned i = 0; i < TIMES; ++i) {
        printf("running: %d\r", i);
        result = KMeans(test, k, buildInitialPointDensity(k, test), false);
        SSE = 0;
        for (unsigned j = 0; j < result.size(); ++j) {
            SSE += result[j].getSumOfEuclideanDistance();
            vecSSE.push_back(SSE / result.size());
        }
    }
    time_t end = std::clock();
    output << "The average of SSE = " << getAverage(vecSSE) << std::endl;
    output << "The variance of SSE = " << getVariance(vecSSE) << std::endl;
    output << "The running time is: " << double(end - start) / CLOCKS_PER_SEC << std::endl;
    // printf("The average of SSE = %lf\n", getAverage(vecSSE));
    // printf("The variance of SSE = %lf\n", getVariance(vecSSE));
    printf("the running time is : %f\n", double(end - start) / CLOCKS_PER_SEC);
    output << "===============================================" << std::endl;
    // puts("===============================================");
    // KMedoids(test, k, centroid);
}

void inline unitTestKMeansNormal(Group &test, std::ofstream &output) {
    // 数据归一化
    // normaliztion(test);

    // 输出读入的数据
    // puts("Print Input Data:");
    // puts("=====================================");
    // test.display();
    // puts("=====================================\n");

    // k 值
    const unsigned k = 3;

    /** 准备测试数据 */
    // KMeans
    // std::vector<Group> centroid = buildInitialPoint(k, test);

    output << "===============================================" << std::endl;
    output << "buildInitialPoint" << std::endl;
    output << "===============================================" << std::endl;
    // 重复运行测试
    std::vector<Group> result;
    std::vector<double> avg(k);
    double SSE = 0;
    // 记录每次的 SSE 值
    std::vector<double> vecSSE;
    time_t start = std::clock();
    for (unsigned i = 0; i < TIMES; ++i) {
        printf("running: %d\r", i);
        result = KMeans(test, k, buildInitialPoint(k, test), false);
        SSE = 0;
        for (unsigned j = 0; j < result.size(); ++j) {
            SSE += result[j].getSumOfEuclideanDistance();
            vecSSE.push_back(SSE / result.size());
        }
    }
    time_t end = std::clock();
    output << "The average of SSE = " << getAverage(vecSSE) << std::endl;
    output << "The variance of SSE = " << getVariance(vecSSE) << std::endl;
    output << "The running time is: " << double(end - start) / CLOCKS_PER_SEC << std::endl;
    // printf("The average of SSE = %lf\n", getAverage(vecSSE));
    // printf("The variance of SSE = %lf\n", getVariance(vecSSE));
    printf("the running time is : %f\n", double(end - start) / CLOCKS_PER_SEC);
    output << "===============================================" << std::endl;
    // puts("===============================================");
    // KMedoids(test, k, centroid);
}

void inline unitTestKMeansRandomly(Group &test, std::ofstream &output) {
    // 数据归一化
    // normaliztion(test);

    // 输出读入的数据
    // puts("Print Input Data:");
    // puts("=====================================");
    // test.display();
    // puts("=====================================\n");

    // k 值
    const unsigned k = 3;

    /** 准备测试数据 */
    // KMeans++
    // std::vector<Group> centroid = buildInitialPointRandomly(k, test);
    // Kmeans + Density initialize
    // std::vector<Group> centroid = buildInitialPointDensity(k, test);
    // KMeans
    // std::vector<Group> centroid = buildInitialPoint(k, test);

    output << "===============================================" << std::endl;
    output << "buildInitialPointRandomly" << std::endl;
    output << "===============================================" << std::endl;
    // 重复运行测试
    std::vector<Group> result;
    std::vector<double> avg(k);
    double SSE = 0;
    // 记录每次的 SSE 值
    std::vector<double> vecSSE;
    time_t start = std::clock();
    // 重复实验的次数
    for (unsigned i = 0; i < TIMES; ++i) {
        printf("running: %d\r", i);
        result = KMeans(test, k, buildInitialPointRandomly(k, test), false);
        SSE = 0;
        for (unsigned j = 0; j < result.size(); ++j) {
            SSE += result[j].getSumOfEuclideanDistance();
            vecSSE.push_back(SSE / result.size());
        }
    }
    time_t end = std::clock();
    output << "The average of SSE = " << getAverage(vecSSE) << std::endl;
    output << "The variance of SSE = " << getVariance(vecSSE) << std::endl;
    output << "The running time is: " << double(end - start) / CLOCKS_PER_SEC << std::endl;
    // printf("The average of SSE = %lf\n", getAverage(vecSSE));
    // printf("The variance of SSE = %lf\n", getVariance(vecSSE));
    printf("the running time is : %f\n", double(end - start) / CLOCKS_PER_SEC);
    output << "===============================================" << std::endl;
    // puts("===============================================");
    // KMedoids(test, k, centroid);
}

void inline TestIris() {
    freopen("./data/iris.txt", "r", stdin);
    std::ofstream output("output.txt", std::ofstream::out | std::ofstream::app);
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        if (n == 0) {
            break;
        }
        // 数据集
        // std::vector<Node> test;
        Group test;
        double x = 0;
        for (int i = 0; i < n; ++i) {
            test.nodes.push_back(Node(i));
            for (int j = 0; j < m; ++j) {
                scanf("%lf", &x);
                test.nodes[i].id = i + 1;
                test.nodes[i].attribute.push_back(x);
            }
        }
        unitTestKMeansNormal(test, output);
        unitTestKMeansRandomly(test, output);
        unitTestKKMeansDensity(test, output);
    }
    output.close();
    fclose(stdin);
}

void inline matrixTest(Group &test) {
    Matrix mat = Matrix::getCovarianceMatrix(std::vector<std::vector<double> > {test.nodes[0].attribute, test.nodes[1].attribute});
    mat.printData();
    std::vector<Matrix> lu = mat.luDecomposition();
    lu[0].printData();
    lu[1].printData();
}   // unfinished, could cause error

unsigned inline readUnsigned(char &ch) {
    unsigned num = 0;
    while ((ch = getchar()) != ',' && ch != '\n') {
        num = num * 10 + ch;
    }
    // ungetc(ch, stdin);
    return num;
}

void inline readDigitRecognizerTrain(Group &train) {
    freopen("./data/DigitRecognizer/train.csv", "r", stdin);
    unsigned label = 0;
    char *head = new char[7000];
    char ch = 0;
    unsigned i = 0;
    fgets(head, 7000, stdin);
    // getchar();
    while (~scanf("%u,", &label)) {
        train.nodes.push_back(Node(label));
        for ( ; ; ) {
            train.nodes[i].attribute.push_back(readUnsigned(ch));
            if (ch == '\n') {
                break;
            }
        }
        ++i;
    }

    delete[] head;
#ifdef linux
    printf("size of train: %lu\n", train.nodes.size());
    printf("size of trainNode: %lu\n", train.nodes[0].attribute.size());
#endif
#ifdef _WIN32
    printf("size of train: %u\n", train.nodes.size());
    printf("size of trainNode: %u\n", train.nodes[0].attribute.size());
#endif
    fflush(stdout);
}

void inline readDigitRecognizerTest(Group &test, const unsigned size = 0) {
    freopen("./data/DigitRecognizer/test.csv", "r", stdin);
    char *head = new char[7000];
    char ch = 0;
    unsigned i = 0;
    fgets(head, 7000, stdin);
    getchar();
    // gets(head);
    for ( ; ; ) {
        // with a increment id
        test.nodes.push_back(Node(i));
        for ( ; ; ) {
            test.nodes[i].attribute.push_back(readUnsigned(ch));
            if (ch == '\n') {
                break;
            }
        }
        ++i;
        if ((ch = getchar()) == 'E') {
            break;
        }
        ungetc(ch, stdin);
    }

    delete[] head;

#ifdef linux
    printf("size of test: %lu\n", test.nodes.size());
    printf("size of testNode: %lu\n", test.nodes[0].attribute.size());
#endif
#ifdef _WIN32
    printf("size of test: %u\n", test.nodes.size());
    printf("size of testNode: %u\n", test.nodes[0].attribute.size());
#endif
}

void inline unitTestKNN() {
    Group train;
    readDigitRecognizerTrain(train);
    Group test;
    readDigitRecognizerTest(test);

    knnopenmp(train, test);
}

void inline roundTestKNN(const int k = 10) {
    const int totalPart = 10;
    Group rawData;
    readDigitRecognizerTrain(rawData);
    int partSize = rawData.nodes.size() / totalPart;
    int head = 0, tail = 0;
    Group test, train;
    // initial test data with new label
    int roundID = -1;
    for (int i = 0; i < k; ++i) {
        head = i * partSize;
        tail = (i + 1) * partSize;
        // initial test and train data;
        test.nodes.insert(test.nodes.begin(), rawData.nodes.begin() + head, rawData.nodes.begin() + tail);
        train.nodes.insert(train.nodes.begin(), rawData.nodes.begin() + 0, rawData.nodes.begin() + head);
        if (head == 0) {
            train.nodes.clear();
            train.nodes.insert(train.nodes.begin(), rawData.nodes.begin() + tail, rawData.nodes.end());
        }
        else {
            train.nodes.insert(train.nodes.end(), rawData.nodes.begin() + tail, rawData.nodes.end());
        }

        roundID = -1;
        // clear label in test
        for (Node &node : test.nodes) {
            node.id = ++roundID;
        }

        // using data to running knn
        printf("round: %d\n", i);
        std::cout << test.nodes.size() << ' ' << train.nodes.size() << std::endl;
        std::cout << test.nodes[1].attribute.size() << ' ' << train.nodes[1].attribute.size() << std::endl;
        knnopenmpRoundTest(i, train, test);
        test.nodes.clear();
        train.nodes.clear();
    }
    for (int i = 0; i < k; ++i) {
        head = i * partSize;
        compare(i, head, rawData);
    }
}

void inline testKNN() {
    // prepare for write running time to file
    // ====================================================================
    const char runningTimePath[] = "data/DigitRecognizer/runningTimeFile.txt";
    std::ofstream resultTimeFile;
    resultTimeFile.open(runningTimePath, std::ofstream::out | std::ofstream::app);
    // ====================================================================

    time_t start = std::clock();

    // test function part
    // ====================================================================
    // unitTestKNN();
    roundTestKNN(10);
    // ====================================================================

    time_t end = std::clock();
    double sec = double(end - start) / CLOCKS_PER_SEC;
    printf("the running time of main is : %f\n", sec);
    resultTimeFile << "the running time of main is : " << sec << std::endl;
    resultTimeFile.close();
}

void inline testID3() {
    ID3Group id3G;
    char inputFilePath[] = "./data/DecisionTree/buyComputer1.txt";
    readGroup(id3G, inputFilePath);
}

int main() {
#ifdef linux
    nice(-20);
#endif
    puts("==================start algorithm===================\n");
    fflush(stdout);
    roundTestKNN(10);
    return 0;
}
