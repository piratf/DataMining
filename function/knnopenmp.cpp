#include "knnopenmp.h"
#include "Node.h"
#include "Group.h"
#include "Distance.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <omp.h>

const char EuclideanDisOfEachTestElementPath[] = "./data/DigitRecognizer/EuclideanDisOfEachTestElement.txt";
const char resultPath[] = "./data/DigitRecognizer/result.txt";
const char distancePath[] = "./data/DigitRecognizer/EuclideanDisOfEachTestElement.txt";
// const char runningTimePath[] = "data/DigitRecognizer/runningTimeFile.txt";

/**
 * knn algorithm with openmp multithreading
 * @author piratf
 */
void knnopenmp(const Group &train, const Group &test) {

    // prepare the distance output file
    // this is the answer fiile
    // std::ifstream distanceFile;
    // distanceFile.open(distancePath, std::ofstream::in);
    // std::ofstream disFile;
    // disFile.open("data/DigitRecognizer/EuclideanDisOfEachTestElement.txt", std::ofstream::out | std::ofstream::app);

    // std::ofstream resultTimeFile;
    // resultTimeFile.open(runningTimePath, std::ofstream::out | std::ofstream::app);

    // calculate the k value
    const int k = 54;
    // unsigned k = (static_cast<unsigned> (sqrt(train.nodes.size())) >> 2) + 1;
    printf("k = %d\n", k);
    fflush(stdout);
    std::ofstream disFile;
    disFile.open("data/DigitRecognizer/EuclideanDisOfEachTestElement.txt", std::ofstream::out | std::ofstream::app);
    std::ofstream resultFile;
    resultFile.open("data/DigitRecognizer/result.txt", std::ofstream::out | std::ios_base::app);
    disFile << k << std::endl;
    disFile.close();

    // for each element in test, calculate its distance with all elements in train
    // for each element need to write the distance list to file in one line.
    TestDistances testDis;
    int i = 0;
    int cnt = 0;
    const int len = test.nodes.size();
    int roundDis = 0;
    #pragma omp parallel for firstprivate(roundDis, testDis) shared(train, test, disFile, resultFile, std::cout, cnt) default(none)
    for (i = 0; i < len; ++i) {
        printf("cal: %d    \r", ++cnt);
        std::cout.flush();
        // fflush(stdout);
        // calculate the distances
        for (unsigned j = 0; j != train.nodes.size(); ++j) {
            testDis.disWithTrainElements.push_back({train.nodes[i].id, Distance::QuadraticEuclideanDistance(test.nodes[i], train.nodes[j])});
        }

        // read distance form file, If have one
        // unsigned id = 0;
        // double distance = 0;
        // for (unsigned j = 0; j != train.nodes.size(); ++j) {
        //     distanceFile >> id >> distance;
        //     testDis.disWithTrainElements.push_back({id, distance});
        // }

        // sort the line by distance
        std::sort(testDis.disWithTrainElements.begin(), testDis.disWithTrainElements.end());

        // write the distance file in one line
        #pragma omp critical
        {

            for (roundDis = 0; roundDis < k; ++roundDis) {
                disFile << testDis.disWithTrainElements[roundDis].id << ' ' << testDis.disWithTrainElements[roundDis].distance << ' ';
            }
            disFile << std::endl;
        }

        // for each of the first k element, calculate the class
        // build a array to storage the weight
        double weight[CLASSCOUNT] = {};
        for (roundDis = 0; roundDis < k; ++roundDis) {
            weight[testDis.disWithTrainElements[roundDis].id] += 1 / (testDis.disWithTrainElements[roundDis].distance + 1);
        }

        double maxValue = -1;
        int maxID = -1;
        // find the class number which have max value
        for (roundDis = 0; roundDis != CLASSCOUNT; ++roundDis) {
            if (weight[roundDis] > maxValue) {
                maxValue = weight[roundDis];
                maxID = roundDis;
            }
        }
        // write the one to file
        #pragma omp critical
        {
            resultFile << test.nodes[i].id << ' ' << maxID << std::endl;
        }

        // clear the array for next round
        testDis.disWithTrainElements.clear();
    }
    if (disFile.is_open()) {
        disFile.close();
    }
    if (resultFile.is_open()) {
        resultFile.close();
    }
}

/**
 * knn algorithm with openmp multithreading
 * round test in 10 part
 * 9 for training, 1 for test
 * calculate the power of each class of first k item
 * @author piratf
 */
void knnopenmpRoundTest(const int nRound, const Group &train, const Group &test) {
    // calculate the k value
    char resultPath[100] = {};
    const int k = (static_cast<int> (sqrt(train.nodes.size()))) + 1;
    printf("k = %d\n", k);
    fflush(stdout);
    std::ofstream resultFile;

    // for each element in test, calculate its distance with all elements in train
    // for each element need to write the distance list to file in one line.
    TestDistances testDis;
    int i = 0;
    int cnt = 0;
    const int len = test.nodes.size();
    int roundDis = 0;
    #pragma omp parallel for firstprivate(roundDis, testDis, resultPath) shared(train, test, resultFile, std::cout, cnt) default(none)
    for (i = 0; i < len; ++i) {
        printf("cal: test - %d    \r", ++cnt);
        std::cout.flush();
        // fflush(stdout);
        // calculate the distances
        for (unsigned j = 0; j != train.nodes.size(); ++j) {
            testDis.disWithTrainElements.push_back({train.nodes[i].id, Distance::QuadraticEuclideanDistance(test.nodes[i], train.nodes[j])});
        }

        // sort the line by distance
        std::sort(testDis.disWithTrainElements.begin(), testDis.disWithTrainElements.end());

        // for each of the first k element, calculate the class
        // build a array to storage the weight
        double weight[CLASSCOUNT] = {};
        for (roundDis = 0; roundDis < k; ++roundDis) {
            weight[testDis.disWithTrainElements[roundDis].id] += 1 / (testDis.disWithTrainElements[roundDis].distance + 1);
        }

        double maxValue = -1;
        int maxID = -1;
        // find the class number which have max value
        for (roundDis = 0; roundDis != CLASSCOUNT; ++roundDis) {
            if (weight[roundDis] > maxValue) {
                maxValue = weight[roundDis];
                maxID = roundDis;
            }
        }
        // write the one to file
        #pragma omp critical
        {
            sprintf(resultPath, "data/DigitRecognizer/result%d.txt", nRound);
            resultFile.open(resultPath, std::ofstream::out | std::ios_base::app);
            resultFile << test.nodes[i].id << ' ' << maxID << std::endl;
            resultFile.close();
        }

        // clear the array for next round
        testDis.disWithTrainElements.clear();
    }
    if (resultFile.is_open()) {
        resultFile.close();
    }
}

/**
 * knn algorithm with openmp multithreading
 * roundTest, split data in 10 part
 * count the highest occurrence class
 * @author piratf
 */
void knnopenmpRoundTest2(const int nRound, const Group &train, const Group &test) {
    // calculate the k value
    char resultPath[100] = {};
    const int k = (static_cast<int> (sqrt(train.nodes.size())) >> 2) + 1;
    printf("k = %d\n", k);
    fflush(stdout);
    std::ofstream resultFile;

    // for each element in test, calculate its distance with all elements in train
    // for each element need to write the distance list to file in one line.
    TestDistances testDis;
    int i = 0;
    int cnt = 0;
    const int len = test.nodes.size();
    int roundDis = 0;
    #pragma omp parallel for firstprivate(roundDis, testDis, resultPath) shared(train, test, resultFile, std::cout, cnt) default(none)
    for (i = 0; i < len; ++i) {
        printf("cal: test - %d    \r", ++cnt);
        std::cout.flush();
        // fflush(stdout);
        // calculate the distances
        for (unsigned j = 0; j != train.nodes.size(); ++j) {
            testDis.disWithTrainElements.push_back({train.nodes[i].id, Distance::QuadraticEuclideanDistance(test.nodes[i], train.nodes[j])});
        }

        // sort the line by distance
        std::sort(testDis.disWithTrainElements.begin(), testDis.disWithTrainElements.end());

        // for each of the first k element, calculate the class
        // build a array to storage the weight
        unsigned weight[CLASSCOUNT] = {};
        // statistics tags appears times
        for (roundDis = 0; roundDis < k; ++roundDis) {
            ++weight[testDis.disWithTrainElements[roundDis].id];
        }

        unsigned maxValue = -1;
        int maxID = -1;
        // find the class number which have max value
        for (roundDis = 0; roundDis != CLASSCOUNT; ++roundDis) {
            if (weight[roundDis] > maxValue) {
                maxValue = weight[roundDis];
                maxID = roundDis;
            }
        }
        // write the one to file
        #pragma omp critical
        {
            sprintf(resultPath, "data/DigitRecognizer/result%d.txt", nRound);
            resultFile.open(resultPath, std::ofstream::out | std::ios_base::app);
            resultFile << test.nodes[i].id << ' ' << maxID << std::endl;
            resultFile.close();
        }

        // clear the array for next round
        testDis.disWithTrainElements.clear();
    }
    if (resultFile.is_open()) {
        resultFile.close();
    }
}

/**
 * compare result label to rawData, round by round
 * @author piratf
 * @param  round   No. round
 * @param  rawData total data
 */
void compare(const int i, int head, Group &rawData) {
    char resultPath[100] = {};
    // char comparePath[100] = {};
    char compareResult[100] = {};
    std::ifstream resultFile;
    sprintf(resultPath, "data/DigitRecognizer/result%d.txt", i);
    resultFile.open(resultPath, std::ofstream::in);
    std::ofstream compareFile;
    // sprintf(comparePath, "data/DigitRecognizer/compare%d.txt", i);
    compareFile.open("data/DigitRecognizer/compareResult5.txt", std::ofstream::out | std::ofstream::app);

    // get length of the opened file
    // #pragma omp critical
    // {
    //     // print length of file
    //     int temp = resultFile.tellg(); // 记录下当前位置
    //     resultFile.seekg(0, std::ios_base::end); // 移动到文件尾
    //     std::cout << resultFile.tellg() << std::endl; // 取得当前位置的指针长度 即文件长度
    //     resultFile.seekg(temp); // 移动到原来的位置
    // }

    // read result vector
    unsigned id = 0;
    unsigned label = 0;
    std::vector<resultSort> vecResult;
    while (resultFile >> id >> label) {
        vecResult.push_back(resultSort{id, label});
    }
    resultFile.close();

    // sort by there original id
    std::sort(vecResult.begin(), vecResult.end());

    // write sorted data in file
    std::ofstream resultSorted;
    sprintf(resultPath, "data/DigitRecognizer/resultSorted%d.txt", i);
    resultSorted.open(resultPath, std::ofstream::out | std::ofstream::app);
    for (const auto &var : vecResult) {
        resultSorted << var.id << ' ' << var.label << std::endl;        
    }
    resultSorted.close();

    unsigned cnt = 0;
    // count how many equal
    for (unsigned roundResult = 0; roundResult != vecResult.size(); ++roundResult, ++head) {
        if (vecResult[roundResult].label == rawData.nodes[head].id) {
            ++cnt;
        }
    }

    // write compare result in one line
#ifdef _WIN32
    sprintf(compareResult, "In %d's round, success %u times, total %u data, the proportion is %lf", i, cnt, vecResult.size(), (cnt * 1.0) / (vecResult.size() * 1.0));
#else
    sprintf(compareResult, "In %d's round, success %u times, total %lu data, the proportion is %lf", i, cnt, vecResult.size(), (cnt * 1.0) / (vecResult.size() * 1.0));
#endif

    #pragma omp critical
    compareFile << compareResult << std::endl;
    // close file stream
    compareFile.close();

    std::cout << "round " << i << " completed" << std::endl;

}