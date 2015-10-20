# DataMining
Some original code on data mining.(unfinished)

Usage: use `make` command to compile files

complier version: `g++ 4.9.2`
- Use `-std=c++11`(recommend: `-pedantic -Wall`) flag for compiling.

You can modify it in `makefile`.

run `demo.exe` to test data files.

more details in file `demo.cpp`

---

Algorithm can be used:

> + Kmeans

    declaration:
        std::vector<Group> KMeans(Group &v, unsigned k, std::vector<Group> &centroid);

There are three different type optimization about initial points.

    > 1. std::vector<Group> centroid = buildInitialPointRandomly(k, test);

Randomly select initial points, but let the points which has longer distance to current center has a greater possibility

    > 2. std::vector<Group> centroid = buildInitialPointDensity(k, test);

Using buildInitialPointRandomly, but first screen the point set and removal outlier.

    > 3. std::vector<Group> centroid = buildInitialPoint(k, test);

Default initial points
    

> + K-mediods

Using existing node to represent next center point.

    declaration:
        std::vector<Group> KMedoids(Group& v, unsigned k, std::vector<Group> &centroid);

Three different type optimization on `KMeans` could use at here too.
