# DataMining
Some original code on data mining.(still learning)

Usage: use `make` command to compile files

complier version: `g++ 4.9.2`
- Use `-std=c++11`(recommend: `-pedantic -Wall`) flag for compiling.

You can modify it in `makefile`.

---

**:->**Trying `openmp` in `knnopenmp.cpp` now, most of gcc compiler already have this feature.

If you don't want to use that, notice that don't link the knnopenmp.o and remove the `$(openmpFlags)` in `makefile`.

if you got error `version 'CXXABI_1.3.8' not found` when compiling, may this link could help: [How to fix: [program name] /usr/lib/x86_64-linux-gnu/libstdc++.so.6: version CXXABI_1.3.8' not found (required by [program name])](http://stackoverflow.com/questions/20357033/how-to-fix-program-name-usr-lib-x86-64-linux-gnu-libstdc-so-6-version-cxx)

---

more details in file `demo.cpp`, use it to test the algorithms.

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
