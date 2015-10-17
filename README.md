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
        std::vector<Group> KMeans(std::vector<Node>& v, unsigned k, bool plus == false)

> + Kmeans++

    declaration:
        std::vector<Group> KMeans(std::vector<Node>& v, unsigned k, bool plus == false)
        // send true to plus to call kmeans++(randomized optimization)

> + Kmedious

    declaration:
        std::vector<Group> KMedoids(std::vector<Node>& v, unsigned k, 
            bool plus = false);
        // send true to plus to call randomized optimization on kmedoids