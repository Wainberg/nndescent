/*
 * Tests all implemented functions of nndescent. The values are the same
 * as in the corresponding py file.
 */


#include <iostream>
#include <vector>

#include "../src/distances.h"
#include "../src/dtypes.h"

using namespace nndescent;

int main()
{
    std::vector<float> v0 = {9,5,6,7,3,2,1,0,8,-4};
    std::vector<float> v1 = {6,8,-2,3,6,5,4,-9,1,0};
    std::vector<float> v2 = {-1,3,5,1,0,0,-7,6,5,0};

    const int N = 100;
    std::vector<float> w0(N);
    std::vector<float> w1(N);
    std::vector<float> w2(N);

    std::iota(w0.begin(), w0.end(), 0);
    std::iota(w1.begin(), w1.end(), -10);
    std::iota(w2.begin(), w2.end(), 5);

    std::cout << "Test distances for:\n"
        << "v0 = " << v0 << "\n"
        << "v1 = " << v1 << "\n"
        << "v2 = " << v2 << "\n"
        << "\n"
        << "w0 = " << "[" << w0[0] << ", " << w0[1] << ", " << w0[2] << ",..., "
            << *(w0.end() - 1) << "], size = " << w0.size() << "\n"
        << "w1 = " << "[" << w1[0] << ", " << w1[1] << ", " << w1[2] << ",..., "
            << *(w1.end() - 1) << "], size = " << w1.size() << "\n"
        << "w2 = " << "[" << w2[0] << ", " << w2[1] << ", " << w2[2] << ",..., "
            << *(w2.end() - 1) << "], size = " << w2.size() << "\n"
        << "\n"
        << "\n"
        << "euclidean(v0, v1) = "
            << euclidean(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "euclidean(v0, v2) = "
            << euclidean(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "euclidean(v1, v2) = "
            << euclidean(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "euclidean(w0, w1) = "
            << euclidean(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "euclidean(w0, w2) = "
            << euclidean(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "euclidean(w1, w2) = "
            << euclidean(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        << "\n"
        << "sqeuclidean(v0, v1) = "
            << squared_euclidean(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "sqeuclidean(v0, v2) = "
            << squared_euclidean(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "sqeuclidean(v1, v2) = "
            << squared_euclidean(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "sqeuclidean(w0, w1) = "
            << squared_euclidean(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "sqeuclidean(w0, w2) = "
            << squared_euclidean(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "sqeuclidean(w1, w2) = "
            << squared_euclidean(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        << "\n"
        << "dot(v0, v1) = "
            << dot(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "dot(v0, v2) = "
            << dot(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "dot(v1, v2) = "
            << dot(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "dot(w0, w1) = "
            << dot(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "dot(w0, w2) = "
            << dot(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "dot(w1, w2) = "
            << dot(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        << "\n"
        << "alternative_dot(v0, v1) = "
            << alternative_dot(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "alternative_dot(v0, v2) = "
            << alternative_dot(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "alternative_dot(v1, v2) = "
            << alternative_dot(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "alternative_dot(w0, w1) = "
            << alternative_dot(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "alternative_dot(w0, w2) = "
            << alternative_dot(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "alternative_dot(w1, w2) = "
            << alternative_dot(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        << "\n"
        << "cosine(v0, v1) = "
            << cosine(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "cosine(v0, v2) = "
            << cosine(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "cosine(v1, v2) = "
            << cosine(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "cosine(w0, w1) = "
            << cosine(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "cosine(w0, w2) = "
            << cosine(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "cosine(w1, w2) = "
            << cosine(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        << "\n"
        << "hamming(v0, v1) = "
            << hamming(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "hamming(v0, v2) = "
            << hamming(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "hamming(v1, v2) = "
            << hamming(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "hamming(w0, w1) = "
            << hamming(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "hamming(w0, w2) = "
            << hamming(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "hamming(w1, w2) = "
            << hamming(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        << "\n"
        << "jaccard(v0, v1) = "
            << jaccard(v0.begin(), v0.end(), v1.begin()) << "\n"
        << "jaccar(v0, v2) = "
            << jaccard(v0.begin(), v0.end(), v2.begin()) << "\n"
        << "jaccar(v1, v2) = "
            << jaccard(v1.begin(), v1.end(), v2.begin()) << "\n"
        << "\n"
        << "jaccard(w0, w1) = "
            << jaccard(w0.begin(), w0.end(), w1.begin()) << "\n"
        << "jaccar(w0, w2) = "
            << jaccard(w0.begin(), w0.end(), w2.begin()) << "\n"
        << "jaccar(w1, w2) = "
            << jaccard(w1.begin(), w1.end(), w2.begin()) << "\n"
        << "\n"
        ;
    return 0;
}

