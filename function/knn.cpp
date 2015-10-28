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

    // calculate the k value
    const int k = 54;
    // unsigned k = (static_cast<unsigned> (sqrt(train.nodes.size())) >> 2) + 1;
    printf("k = %d\n", k);
    fflush(stdout);

    // prepare the distance output file
    std::ofstream disFile;
    disFile.open(EuclideanDisOfEachTestElementPath, std::ofstream::out | std::ofstream::app);
    // this is the answer fiile
    std::ofstream resultFile;
    resultFile.open(resultPath, std::ofstream::out | std::ofstream::app);
    std::ifstream distanceFile;
    distanceFile.open(distancePath, std::ofstream::in);

    std::cout << "open" << std::endl;
    // std::ofstream resultTimeFile;
    // resultTimeFile.open(runningTimePath, std::ofstream::out | std::ofstream::app);

    // for each element in test, calculate its distance with all elements in train
    // for each element need to write the distance list to file in one line.
    TestDistances testDis;
    int i = 0;
    // int len = test.nodes.size();
    for (i = 0; i < 28000; ++i) {
        printf("dis: i = %u\r", i);
        fflush(stdout);
        // calculate the distances
        // for (unsigned j = 0; j != train.nodes.size(); ++j) {
        //     testDis.disWithTrainElements.push_back({train.nodes[i].id, Distance::QuadraticEuclideanDistance(test.nodes[i], train.nodes[j])});
        // }

        // read distance form file
        unsigned id = 0;
        double distance = 0;
        for (unsigned j = 0; j != train.nodes.size(); ++j) {
            distanceFile >> id >> distance;
            testDis.disWithTrainElements.push_back({id, distance});
        }

        // sort the line by distance
        std::sort(testDis.disWithTrainElements.begin(), testDis.disWithTrainElements.end());

        // write the distance file in one line
        // disFile << testDis.disWithTrainElements.size();
        // for (const auto &var : testDis.disWithTrainElements) {
        //     disFile << var.id << ' ' << var.distance << ' ';
        // }
        // disFile << std::endl;

        // for each of the first k element, calculate the class
        // build a array to storage the weight
        double weight[CLASSCOUNT] = {};
        for (unsigned i = 0; i != k; ++i) {
            weight[testDis.disWithTrainElements[i].id] += 1 / (testDis.disWithTrainElements[i].distance + 1);
        }
        // find the class number which have max value
        double maxValue = -1;
        unsigned maxID = -1;
        for (unsigned i = 0; i != k; ++i) {
            if (weight[i] > maxValue) {
                maxValue = weight[i];
                maxID = i;
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