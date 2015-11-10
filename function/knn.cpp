#include "knn.h"
#include "Node.h"
#include "Group.h"
#include "Distance.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

const char EuclideanDisOfEachTestElementPath[] = "./data/DigitRecognizer/EuclideanDisOfEachTestElement.txt";
const char resultPath[] = "./data/DigitRecognizer/result.txt";
const char distancePath[] = "./data/DigitRecognizer/EuclideanDisOfEachTestElement.txt";
// const char runningTimePath[] = "data/DigitRecognizer/runningTimeFile.txt";

/**
 * knn algorithm
 * @author piratf
 */
void knn(Group &train, Group &test) {

    // prepare the distance output file
    std::ofstream disFile;
    disFile.open("data/DigitRecognizer/EuclideanDisOfEachTestElement.txt", std::ofstream::out | std::ios_base::trunc);
    // this is the answer fiile
    std::ofstream resultFile;
    resultFile.open("data/DigitRecognizer/result.txt", std::ofstream::out | std::ios_base::trunc);
    // std::ifstream distanceFile;
    // distanceFile.open(distancePath, std::ofstream::in);

    // std::ofstream resultTimeFile;
    // resultTimeFile.open(runningTimePath, std::ofstream::out | std::ofstream::app);

    // calculate the k value
    const int k = 54;
    // unsigned k = (static_cast<unsigned> (sqrt(train.nodes.size())) >> 2) + 1;
    printf("k = %d\n", k);
    fflush(stdout);
    disFile << k << std::endl;

    // for each element in test, calculate its distance with all elements in train
    // for each element need to write the distance list to file in one line.
    TestDistances testDis;
    int i = 0;
    int len = test.nodes.size();
    int roundDis = 0;
    double weight[CLASSCOUNT] = {};
    double maxValue = -1;
    int maxID = -1;
    for (i = 0; i < len; ++i) {
        printf("cal: i = %d\r", i);
        fflush(stdout);
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
        for (roundDis = 0; roundDis < k; ++roundDis) {
            disFile << testDis.disWithTrainElements[roundDis].id << ' ' << testDis.disWithTrainElements[roundDis].distance << ' ';
        }
        disFile << std::endl;

        // for each of the first k element, calculate the class
        // build a array to storage the weight
        for (roundDis = 0; roundDis < k; ++roundDis) {
            weight[testDis.disWithTrainElements[roundDis].id] += 1 / (testDis.disWithTrainElements[roundDis].distance + 1);
        }
        // find the class number which have max value
        for (roundDis = 0; roundDis != CLASSCOUNT; ++roundDis) {
            if (weight[roundDis] > maxValue) {
                maxValue = weight[roundDis];
                maxID = roundDis;
            }
        }
        // write the one to file
        resultFile << maxID << std::endl;

        // clear the array for next round
        testDis.disWithTrainElements.clear();
    }
    disFile.close();
    resultFile.close();
}

/**
 * knn algorithm with openmp multithreading
 * @author piratf
 */
void knnRoundTest(const int nRound, const Group &train, const Group &test) {
    // calculate the k value
    char resultPath[100] = {};
    const int k = (static_cast<int> (std::sqrt(train.nodes.size())) >> 2) + 1;
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
    for (i = 0; i < len; ++i) {
        printf("cal: test - %d    \r", ++cnt);
        fflush(stdout);
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
            weight[testDis.disWithTrainElements[roundDis].id] += 1 / (testDis.disWithTrainElements[roundDis].distance + 1);
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
        sprintf(resultPath, "data/DigitRecognizer/Nresult%d.txt", nRound);
        resultFile.open(resultPath, std::ofstream::out | std::ios_base::app);
        resultFile << test.nodes[i].id << ' ' << maxID << std::endl;
        resultFile.close();

        // clear the array for next round
        testDis.disWithTrainElements.clear();
    }
    if (resultFile.is_open()) {
        resultFile.close();
    }
}