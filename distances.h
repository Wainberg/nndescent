/**
 * @file distances.h
 *
 * @brief Distance functions.
 */

#pragma once

#include <map>
#include <utility>

/**
 * @brief Squared euclidean distance.
 */
template<class Iter0, class Iter1>
inline float squared_euclidean(Iter0 first0, Iter0 last0, Iter1 first1)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::move(result) + (*first0 - *first1)*(*first0 - *first1);
        ++first0;
        ++first1;
    }
    return result;
}

/**
 * @brief Standard euclidean distance.
 */
template<class Iter0, class Iter1>
inline float euclidean(Iter0 first0, Iter0 last0, Iter1 first1)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::move(result) + (*first0 - *first1)*(*first0 - *first1);
        ++first0;
        ++first1;
    }
    return std::sqrt(result);
}

/**
 * @brief Standardised euclidean distance.
 *
 * Euclidean distance standardised against a vector of standard
 * deviations per coordinate.
 *
 * \f[
 *     D(x, y) = \sqrt{\sum_i \frac{(x_i - y_i)**2}{v_i}}
 * \f]
 */
template<class Iter0, class Iter1, class Iter2>
inline float standardised_euclidean
(
    Iter0 first0, Iter0 last0, Iter1 first1, Iter2 first2
)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::move(result)
            + (*first0 - *first1)*(*first0 - *first1) / *first2;
        ++first0;
        ++first1;
        ++first2;
    }
    return std::sqrt(result);
}

/**
 * @brief Manhattan, taxicab, or l1 distance.
 *
 * \f[
 *     D(x, y) = \sum_i |x_i - y_i|
 * \f]
 */
template<class Iter0, class Iter1>
inline float manhattan(Iter0 first0, Iter0 last0, Iter1 first1)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::move(result) + std::abs(*first0 - *first1);
        ++first0;
        ++first1;
    }
    return result;
}

/**
 * @brief Chebyshev or l-infinity distance.
 *
 * \f[
 *     D(x, y) = \max_i |x_i - y_i|
 * \f]
 */
template<class Iter0, class Iter1>
inline float chebyshev(Iter0 first0, Iter0 last0, Iter1 first1)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::max(std::move(result), std::abs(*first0 - *first1));
        ++first0;
        ++first1;
    }
    return result;
}


/**
 * @brief Minkowski distance.
 *
 * \f[
 *     D(x, y) = \left(\sum_i |x_i - y_i|^p\right)^{\frac{1}{p}}
 * \f]
 *
 * This is a general distance. For p=1 it is equivalent to
 * manhattan distance, for p=2 it is Euclidean distance, and
 * for p=infinity it is Chebyshev distance. In general it is better
 * to use the more specialised functions for those distances.
 */
template<class Iter0, class Iter1>
inline float minkowski(Iter0 first0, Iter0 last0, Iter1 first1, float p)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::move(result) + std::pow(std::abs(*first0 - *first1), p);
        ++first0;
        ++first1;
    }
    return std::pow(result, 1.0f / p);
}


/**
 *  @brief A weighted version of Minkowski distance.
 *
 * \f[
       D(x, y) = \left(\sum_i w_i |x_i - y_i|^p\right)^{\frac{1}{p}}
 * \f]
 *
 * If weights w_i are inverse standard deviations of graph_data in each
 * dimension then this represented a standardised Minkowski distance (and
 * is equivalent to standardised Euclidean distance for p=1).
 */
template<class Iter0, class Iter1, class Iter2>
inline float weighted_minkowski
(
    Iter0 first0, Iter0 last0, Iter1 first1, Iter2 first2, float p
)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        result = std::move(result)
            + (*first2) * std::pow(std::abs(*first0 - *first1), p);
        ++first0;
        ++first1;
        ++first2;
    }
    return std::pow(result, 1.0f / p);
}




// @numba.njit(fastmath=True)
// def mahalanobis(x, y, vinv=_mock_identity):
    // result = 0.0

    // diff = np.empty(x.shape[0], dtype=np.float32)

    // for i in range(x.shape[0]):
        // diff[i] = x[i] - y[i]

    // for i in range(x.shape[0]):
        // tmp = 0.0
        // for j in range(x.shape[0]):
            // tmp += vinv[i, j] * diff[j]
        // result += tmp * diff[i]

    // return np.sqrt(result)

/**
 * @brief Hamming distance
 */
template<class Iter0, class Iter1>
inline float hamming(Iter0 first0, Iter0 last0, Iter1 first1)
{
    int result = 0;
    int size = last0 - first0;
    while (first0 != last0)
    {
        if (*first0 != *first1)
        {
            ++result;
        }
        ++first0;
        ++first1;
    }
    return (float)(result) / size;
}


/**
 * @brief Canberra distance.
 */
template<class Iter0, class Iter1>
inline float canberra(Iter0 first0, Iter0 last0, Iter1 first1)
{
    float result = 0.0f;
    while (first0 != last0)
    {
        float denominator = std::abs(*first0) + std::abs(*first1);
        if (denominator > 0)
        {
            result = std::move(result)
                + std::abs(*first0 - *first1) / denominator;
        }
        ++first0;
        ++first1;
    }
    return result;
}

/**
 * @brief Bray–Curtis dissimilarity.
 */
template<class Iter0, class Iter1>
inline float bray_curtis(Iter0 first0, Iter0 last0, Iter1 first1)
{
    int numerator = 0;
    int denominator = 0;
    while (first0 != last0)
    {
        numerator = std::move(numerator) + std::abs(*first0 - *first1);
        denominator = std::move(denominator) + std::abs(*first0 + *first1);
        ++first0;
        ++first1;
    }
    if (denominator > 0)
    {
        return (float)(numerator)/denominator;
    }
    return 0.0f;
}


/**
 * @brief Jaccard distance.
 */
template<class Iter0, class Iter1>
inline float jaccard(Iter0 first0, Iter0 last0, Iter1 first1)
{
    int num_non_zero = 0;
    int num_equal = 0;
    while (first0 != last0)
    {
        bool first0_true = ((*first0) != 0);
        bool first1_true = ((*first1) != 0);
        num_non_zero = std::move(num_non_zero) + (first0_true || first1_true);
        num_equal = std::move(num_equal) + (first0_true && first1_true);
        ++first0;
        ++first1;
    }
    if (num_non_zero == 0)
    {
        return 0.0f;
    }
    return (float)(num_non_zero - num_equal) / num_non_zero;
}


// @numba.njit(
    // [
        // "f4(f4[::1],f4[::1])",
        // numba.types.float32(
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
        // ),
    // ],
    // fastmath=True,
    // locals={
        // "result": numba.types.float32,
        // "num_non_zero": numba.types.float32,
        // "num_equal": numba.types.float32,
        // "x_true": numba.types.uint8,
        // "y_true": numba.types.uint8,
        // "dim": numba.types.intp,
        // "i": numba.types.uint16,
    // },
// )
// def alternative_jaccard(x, y):
    // num_non_zero = 0.0
    // num_equal = 0.0
    // dim = x.shape[0]
    // for i in range(dim):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_non_zero += x_true or y_true
        // num_equal += x_true and y_true

    // if num_non_zero == 0.0:
        // return 0.0
    // else:
        // return -np.log2(num_equal / num_non_zero)


// @numba.vectorize(fastmath=True)
// def correct_alternative_jaccard(v):
    // return 1.0 - pow(2.0, -v)


// @numba.njit(fastmath=True)
// def matching(x, y):
    // num_not_equal = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_not_equal += x_true != y_true

    // return float(num_not_equal) / x.shape[0]


// @numba.njit(fastmath=True)
// def dice(x, y):
    // num_true_true = 0.0
    // num_not_equal = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_true_true += x_true and y_true
        // num_not_equal += x_true != y_true

    // if num_not_equal == 0.0:
        // return 0.0
    // else:
        // return num_not_equal / (2.0 * num_true_true + num_not_equal)


// @numba.njit(fastmath=True)
// def kulsinski(x, y):
    // num_true_true = 0.0
    // num_not_equal = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_true_true += x_true and y_true
        // num_not_equal += x_true != y_true

    // if num_not_equal == 0:
        // return 0.0
    // else:
        // return float(num_not_equal - num_true_true + x.shape[0]) / (
            // num_not_equal + x.shape[0]
        // )


// @numba.njit(fastmath=True)
// def rogers_tanimoto(x, y):
    // num_not_equal = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_not_equal += x_true != y_true

    // return (2.0 * num_not_equal) / (x.shape[0] + num_not_equal)


// @numba.njit(fastmath=True)
// def russellrao(x, y):
    // num_true_true = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_true_true += x_true and y_true

    // if num_true_true == np.sum(x != 0) and num_true_true == np.sum(y != 0):
        // return 0.0
    // else:
        // return float(x.shape[0] - num_true_true) / (x.shape[0])


// @numba.njit(fastmath=True)
// def sokal_michener(x, y):
    // num_not_equal = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_not_equal += x_true != y_true

    // return (2.0 * num_not_equal) / (x.shape[0] + num_not_equal)


// @numba.njit(fastmath=True)
// def sokal_sneath(x, y):
    // num_true_true = 0.0
    // num_not_equal = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_true_true += x_true and y_true
        // num_not_equal += x_true != y_true

    // if num_not_equal == 0.0:
        // return 0.0
    // else:
        // return num_not_equal / (0.5 * num_true_true + num_not_equal)


// @numba.njit(fastmath=True)
// def haversine(x, y):
    // if x.shape[0] != 2:
        // raise ValueError("haversine is only defined for 2 dimensional graph_data")
    // sin_lat = np.sin(0.5 * (x[0] - y[0]))
    // sin_long = np.sin(0.5 * (x[1] - y[1]))
    // result = np.sqrt(sin_lat**2 + np.cos(x[0]) * np.cos(y[0]) * sin_long**2)
    // return 2.0 * np.arcsin(result)


// @numba.njit(fastmath=True)
// def yule(x, y):
    // num_true_true = 0.0
    // num_true_false = 0.0
    // num_false_true = 0.0
    // for i in range(x.shape[0]):
        // x_true = x[i] != 0
        // y_true = y[i] != 0
        // num_true_true += x_true and y_true
        // num_true_false += x_true and (not y_true)
        // num_false_true += (not x_true) and y_true

    // num_false_false = x.shape[0] - num_true_true - num_true_false - num_false_true

    // if num_true_false == 0.0 or num_false_true == 0.0:
        // return 0.0
    // else:
        // return (2.0 * num_true_false * num_false_true) / (
            // num_true_true * num_false_false + num_true_false * num_false_true
        // )


// @numba.njit(fastmath=True)
// def cosine(x, y):
    // result = 0.0
    // norm_x = 0.0
    // norm_y = 0.0
    // for i in range(x.shape[0]):
        // result += x[i] * y[i]
        // norm_x += x[i] ** 2
        // norm_y += y[i] ** 2

    // if norm_x == 0.0 and norm_y == 0.0:
        // return 0.0
    // elif norm_x == 0.0 or norm_y == 0.0:
        // return 1.0
    // else:
        // return 1.0 - (result / np.sqrt(norm_x * norm_y))


// @numba.njit(
    // [
        // "f4(f4[::1],f4[::1])",
        // numba.types.float32(
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
        // ),
    // ],
    // fastmath=True,
    // locals={
        // "result": numba.types.float32,
        // "norm_x": numba.types.float32,
        // "norm_y": numba.types.float32,
        // "dim": numba.types.intp,
        // "i": numba.types.uint16,
    // },
// )
// def alternative_cosine(x, y):
    // result = 0.0
    // norm_x = 0.0
    // norm_y = 0.0
    // dim = x.shape[0]
    // for i in range(dim):
        // result += x[i] * y[i]
        // norm_x += x[i] * x[i]
        // norm_y += y[i] * y[i]

    // if norm_x == 0.0 and norm_y == 0.0:
        // return 0.0
    // elif norm_x == 0.0 or norm_y == 0.0:
        // return FLOAT32_MAX
    // elif result <= 0.0:
        // return FLOAT32_MAX
    // else:
        // result = np.sqrt(norm_x * norm_y) / result
        // return np.log2(result)


// @numba.njit(
    // "f4(f4[::1],f4[::1])",
    // fastmath=True,
    // locals={
        // "result": numba.types.float32,
        // "dim": numba.types.intp,
        // "i": numba.types.uint16,
    // },
// )
// def dot(x, y):
    // result = 0.0
    // dim = x.shape[0]
    // for i in range(dim):
        // result += x[i] * y[i]

    // if result <= 0.0:
        // return 1.0
    // else:
        // return 1.0 - result


// @numba.njit(
    // [
        // "f4(f4[::1],f4[::1])",
        // numba.types.float32(
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
        // ),
    // ],
    // fastmath=True,
    // locals={
        // "result": numba.types.float32,
        // "dim": numba.types.intp,
        // "i": numba.types.uint16,
    // },
// )
// def alternative_dot(x, y):
    // result = 0.0
    // dim = x.shape[0]
    // for i in range(dim):
        // result += x[i] * y[i]

    // if result <= 0.0:
        // return FLOAT32_MAX
    // else:
        // return -np.log2(result)


// @numba.vectorize(fastmath=True)
// def correct_alternative_cosine(d):
    // return 1.0 - pow(2.0, -d)


// @numba.njit(fastmath=True)
// def tsss(x, y):
    // d_euc_squared = 0.0
    // d_cos = 0.0
    // norm_x = 0.0
    // norm_y = 0.0
    // dim = x.shape[0]

    // for i in range(dim):
        // diff = x[i] - y[i]
        // d_euc_squared += diff * diff
        // d_cos += x[i] * y[i]
        // norm_x += x[i] * x[i]
        // norm_y += y[i] * y[i]

    // norm_x = np.sqrt(norm_x)
    // norm_y = np.sqrt(norm_y)
    // magnitude_difference = np.abs(norm_x - norm_y)
    // d_cos /= norm_x * norm_y
    // theta = np.arccos(d_cos) + np.radians(10)  # Add 10 degrees as an "epsilon" to
    // # avoid problems
    // sector = ((np.sqrt(d_euc_squared) + magnitude_difference) ** 2) * theta
    // triangle = norm_x * norm_y * np.sin(theta) / 2.0
    // return triangle * sector


// @numba.njit(fastmath=True)
// def true_angular(x, y):
    // result = 0.0
    // norm_x = 0.0
    // norm_y = 0.0
    // dim = x.shape[0]
    // for i in range(dim):
        // result += x[i] * y[i]
        // norm_x += x[i] * x[i]
        // norm_y += y[i] * y[i]

    // if norm_x == 0.0 and norm_y == 0.0:
        // return 0.0
    // elif norm_x == 0.0 or norm_y == 0.0:
        // return FLOAT32_MAX
    // elif result <= 0.0:
        // return FLOAT32_MAX
    // else:
        // result = result / np.sqrt(norm_x * norm_y)
        // return 1.0 - (np.arccos(result) / np.pi)


// @numba.vectorize(fastmath=True)
// def true_angular_from_alt_cosine(d):
    // return 1.0 - (np.arccos(pow(2.0, -d)) / np.pi)


// @numba.njit(fastmath=True)
// def correlation(x, y):
    // mu_x = 0.0
    // mu_y = 0.0
    // norm_x = 0.0
    // norm_y = 0.0
    // dot_product = 0.0

    // for i in range(x.shape[0]):
        // mu_x += x[i]
        // mu_y += y[i]

    // mu_x /= x.shape[0]
    // mu_y /= x.shape[0]

    // for i in range(x.shape[0]):
        // shifted_x = x[i] - mu_x
        // shifted_y = y[i] - mu_y
        // norm_x += shifted_x**2
        // norm_y += shifted_y**2
        // dot_product += shifted_x * shifted_y

    // if norm_x == 0.0 and norm_y == 0.0:
        // return 0.0
    // elif dot_product == 0.0:
        // return 1.0
    // else:
        // return 1.0 - (dot_product / np.sqrt(norm_x * norm_y))


// @numba.njit(
    // [
        // "f4(f4[::1],f4[::1])",
        // numba.types.float32(
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
        // ),
    // ],
    // fastmath=True,
    // locals={
        // "result": numba.types.float32,
        // "l1_norm_x": numba.types.float32,
        // "l1_norm_y": numba.types.float32,
        // "dim": numba.types.intp,
        // "i": numba.types.uint16,
    // },
// )
// def hellinger(x, y):
    // result = 0.0
    // l1_norm_x = 0.0
    // l1_norm_y = 0.0
    // dim = x.shape[0]

    // for i in range(dim):
        // result += np.sqrt(x[i] * y[i])
        // l1_norm_x += x[i]
        // l1_norm_y += y[i]

    // if l1_norm_x == 0 and l1_norm_y == 0:
        // return 0.0
    // elif l1_norm_x == 0 or l1_norm_y == 0:
        // return 1.0
    // else:
        // return np.sqrt(1 - result / np.sqrt(l1_norm_x * l1_norm_y))


// @numba.njit(
    // [
        // "f4(f4[::1],f4[::1])",
        // numba.types.float32(
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
            // numba.types.Array(numba.types.float32, 1, "C", readonly=True),
        // ),
    // ],
    // fastmath=True,
    // locals={
        // "result": numba.types.float32,
        // "l1_norm_x": numba.types.float32,
        // "l1_norm_y": numba.types.float32,
        // "dim": numba.types.intp,
        // "i": numba.types.uint16,
    // },
// )
// def alternative_hellinger(x, y):
    // result = 0.0
    // l1_norm_x = 0.0
    // l1_norm_y = 0.0
    // dim = x.shape[0]

    // for i in range(dim):
        // result += np.sqrt(x[i] * y[i])
        // l1_norm_x += x[i]
        // l1_norm_y += y[i]

    // if l1_norm_x == 0 and l1_norm_y == 0:
        // return 0.0
    // elif l1_norm_x == 0 or l1_norm_y == 0:
        // return FLOAT32_MAX
    // elif result <= 0:
        // return FLOAT32_MAX
    // else:
        // result = np.sqrt(l1_norm_x * l1_norm_y) / result
        // return np.log2(result)


// @numba.vectorize(fastmath=True)
// def correct_alternative_hellinger(d):
    // return np.sqrt(1.0 - pow(2.0, -d))


// @numba.njit()
// def rankdata(a, method="average"):
    // arr = np.ravel(np.asarray(a))
    // if method == "ordinal":
        // sorter = arr.argsort(kind="mergesort")
    // else:
        // sorter = arr.argsort(kind="quicksort")

    // inv = np.empty(sorter.size, dtype=np.intp)
    // inv[sorter] = np.arange(sorter.size)

    // if method == "ordinal":
        // return (inv + 1).astype(np.float64)

    // arr = arr[sorter]
    // obs = np.ones(arr.size, np.bool_)
    // obs[1:] = arr[1:] != arr[:-1]
    // dense = obs.cumsum()[inv]

    // if method == "dense":
        // return dense.astype(np.float64)

    // # cumulative counts of each unique value
    // nonzero = np.nonzero(obs)[0]
    // count = np.concatenate((nonzero, np.array([len(obs)], nonzero.dtype)))

    // if method == "max":
        // return count[dense].astype(np.float64)

    // if method == "min":
        // return (count[dense - 1] + 1).astype(np.float64)

    // # average method
    // return 0.5 * (count[dense] + count[dense - 1] + 1)


// @numba.njit(fastmath=True)
// def spearmanr(x, y):
    // x_rank = rankdata(x)
    // y_rank = rankdata(y)

    // return correlation(x_rank, y_rank)


// @numba.njit(nogil=True)
// def kantorovich(x, y, cost=_dummy_cost, max_iter=100000):

    // row_mask = x != 0
    // col_mask = y != 0

    // a = x[row_mask].astype(np.float64)
    // b = y[col_mask].astype(np.float64)

    // a_sum = a.sum()
    // b_sum = b.sum()

    // # if not isclose(a_sum, b_sum):
    // #     raise ValueError(
    // #         "Kantorovich distance inputs must be valid probability distributions."
    // #     )

    // a /= a_sum
    // b /= b_sum

    // sub_cost = cost[row_mask, :][:, col_mask]

    // node_arc_data, spanning_tree, graph = allocate_graph_structures(
        // a.shape[0], b.shape[0], False
    // )
    // initialize_supply(a, -b, graph, node_arc_data.supply)
    // initialize_cost(sub_cost, graph, node_arc_data.cost)
    // # initialize_cost(cost, graph, node_arc_data.cost)
    // init_status = initialize_graph_structures(graph, node_arc_data, spanning_tree)
    // if init_status == False:
        // raise ValueError(
            // "Kantorovich distance inputs must be valid probability distributions."
        // )
    // solve_status = network_simplex_core(node_arc_data, spanning_tree, graph, max_iter)
    // # if solve_status == ProblemStatus.MAX_ITER_REACHED:
    // #     print("WARNING: RESULT MIGHT BE INACCURATE\nMax number of iteration reached!")
    // if solve_status == ProblemStatus.INFEASIBLE:
        // raise ValueError(
            // "Optimal transport problem was INFEASIBLE. Please check inputs."
        // )
    // elif solve_status == ProblemStatus.UNBOUNDED:
        // raise ValueError(
            // "Optimal transport problem was UNBOUNDED. Please check inputs."
        // )
    // result = total_cost(node_arc_data.flow, node_arc_data.cost)

    // return result


// @numba.njit(fastmath=True)
// def sinkhorn(x, y, cost=_dummy_cost, regularization=1.0):
    // row_mask = x != 0
    // col_mask = y != 0

    // a = x[row_mask].astype(np.float64)
    // b = y[col_mask].astype(np.float64)

    // a_sum = a.sum()
    // b_sum = b.sum()

    // a /= a_sum
    // b /= b_sum

    // sub_cost = cost[row_mask, :][:, col_mask]

    // transport_plan = sinkhorn_transport_plan(
        // x, y, cost=sub_cost, regularization=regularization
    // )
    // dim_i = transport_plan.shape[0]
    // dim_j = transport_plan.shape[1]
    // result = 0.0
    // for i in range(dim_i):
        // for j in range(dim_j):
            // result += transport_plan[i, j] * cost[i, j]

    // return result


// @numba.njit()
// def jensen_shannon_divergence(x, y):
    // result = 0.0
    // l1_norm_x = 0.0
    // l1_norm_y = 0.0
    // dim = x.shape[0]

    // for i in range(dim):
        // l1_norm_x += x[i]
        // l1_norm_y += y[i]

    // l1_norm_x += FLOAT32_EPS * dim
    // l1_norm_y += FLOAT32_EPS * dim

    // pdf_x = (x + FLOAT32_EPS) / l1_norm_x
    // pdf_y = (y + FLOAT32_EPS) / l1_norm_y
    // m = 0.5 * (pdf_x + pdf_y)

    // for i in range(dim):
        // result += 0.5 * (
            // pdf_x[i] * np.log(pdf_x[i] / m[i]) + pdf_y[i] * np.log(pdf_y[i] / m[i])
        // )

    // return result


// @numba.njit()
// def wasserstein_1d(x, y, p=1):
    // x_sum = 0.0
    // y_sum = 0.0
    // for i in range(x.shape[0]):
        // x_sum += x[i]
        // y_sum += y[i]

    // x_cdf = x / x_sum
    // y_cdf = y / y_sum

    // for i in range(1, x_cdf.shape[0]):
        // x_cdf[i] += x_cdf[i - 1]
        // y_cdf[i] += y_cdf[i - 1]

    // return minkowski(x_cdf, y_cdf, p)


// @numba.njit()
// def circular_kantorovich(x, y, p=1):
    // x_sum = 0.0
    // y_sum = 0.0
    // for i in range(x.shape[0]):
        // x_sum += x[i]
        // y_sum += y[i]

    // x_cdf = x / x_sum
    // y_cdf = y / y_sum

    // for i in range(1, x_cdf.shape[0]):
        // x_cdf[i] += x_cdf[i - 1]
        // y_cdf[i] += y_cdf[i - 1]

    // mu = np.median((x_cdf - y_cdf) ** p)

    // # Now we just want minkowski distance on the CDFs shifted by mu
    // result = 0.0
    // if p > 2:
        // for i in range(x_cdf.shape[0]):
            // result += np.abs(x_cdf[i] - y_cdf[i] - mu) ** p

        // return result ** (1.0 / p)

    // elif p == 2:
        // for i in range(x_cdf.shape[0]):
            // val = x_cdf[i] - y_cdf[i] - mu
            // result += val * val

        // return np.sqrt(result)

    // elif p == 1:
        // for i in range(x_cdf.shape[0]):
            // result += np.abs(x_cdf[i] - y_cdf[i] - mu)

        // return result

    // else:
        // raise ValueError("Invalid p supplied to Kantorvich distance")


// @numba.njit()
// def symmetric_kl_divergence(x, y):
    // result = 0.0
    // l1_norm_x = 0.0
    // l1_norm_y = 0.0
    // dim = x.shape[0]

    // for i in range(dim):
        // l1_norm_x += x[i]
        // l1_norm_y += y[i]

    // l1_norm_x += FLOAT32_EPS * dim
    // l1_norm_y += FLOAT32_EPS * dim

    // pdf_x = (x + FLOAT32_EPS) / l1_norm_x
    // pdf_y = (y + FLOAT32_EPS) / l1_norm_y

    // for i in range(dim):
        // result += pdf_x[i] * np.log(pdf_x[i] / pdf_y[i]) + pdf_y[i] * np.log(
            // pdf_y[i] / pdf_x[i]
        // )

    // return result




// named_distances = {
    // # general minkowski distances
    // "euclidean": euclidean,
    // "l2": euclidean,
    // "sqeuclidean": squared_euclidean,
    // "manhattan": manhattan,
    // "taxicab": manhattan,
    // "l1": manhattan,
    // "chebyshev": chebyshev,
    // "linfinity": chebyshev,
    // "linfty": chebyshev,
    // "linf": chebyshev,
    // "minkowski": minkowski,
    // # Standardised/weighted distances
    // "seuclidean": standardised_euclidean,
    // "standardised_euclidean": standardised_euclidean,
    // "wminkowski": weighted_minkowski,
    // "weighted_minkowski": weighted_minkowski,
    // "mahalanobis": mahalanobis,
    // # Other distances
    // "canberra": canberra,
    // "cosine": cosine,
    // "dot": dot,
    // "correlation": correlation,
    // "haversine": haversine,
    // "braycurtis": bray_curtis,
    // "spearmanr": spearmanr,
    // "tsss": tsss,
    // "true_angular": true_angular,
    // # Distribution distances
    // "hellinger": hellinger,
    // "kantorovich": kantorovich,
    // "wasserstein": kantorovich,
    // "wasserstein_1d": wasserstein_1d,
    // "wasserstein-1d": wasserstein_1d,
    // "kantorovich-1d": wasserstein_1d,
    // "kantorovich_1d": wasserstein_1d,
    // "circular_kantorovich": circular_kantorovich,
    // "circular_wasserstein": circular_kantorovich,
    // "sinkhorn": sinkhorn,
    // "jensen-shannon": jensen_shannon_divergence,
    // "jensen_shannon": jensen_shannon_divergence,
    // "symmetric-kl": symmetric_kl_divergence,
    // "symmetric_kl": symmetric_kl_divergence,
    // "symmetric_kullback_liebler": symmetric_kl_divergence,
    // # Binary distances
    // "hamming": hamming,
    // "jaccard": jaccard,
    // "dice": dice,
    // "matching": matching,
    // "kulsinski": kulsinski,
    // "rogerstanimoto": rogers_tanimoto,
    // "russellrao": russellrao,
    // "sokalsneath": sokal_sneath,
    // "sokalmichener": sokal_michener,
    // "yule": yule,
// }

// # Some distances have a faster to compute alternative that
// # retains the same ordering of distances. We can compute with
// # this instead, and then correct the final distances when complete.
// # This provides a list of distances that have such an alternative
// # along with the alternative distance function and the correction
// # function to be applied.
// fast_distance_alternatives = {
    // "euclidean": {"dist": squared_euclidean, "correction": np.sqrt},
    // "l2": {"dist": squared_euclidean, "correction": np.sqrt},
    // "cosine": {"dist": alternative_cosine, "correction": correct_alternative_cosine},
    // "dot": {"dist": alternative_dot, "correction": correct_alternative_cosine},
    // "true_angular": {
        // "dist": alternative_cosine,
        // "correction": true_angular_from_alt_cosine,
    // },
    // "hellinger": {
        // "dist": alternative_hellinger,
        // "correction": correct_alternative_hellinger,
    // },
    // "jaccard": {"dist": alternative_jaccard, "correction": correct_alternative_jaccard},
// }
