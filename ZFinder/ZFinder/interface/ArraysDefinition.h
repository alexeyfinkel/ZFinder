#include <array>

const double EfficiencyEtaBins[6] = {0.0, 0.8, 1.4442, 1.566, 2.0, 2.5};
const int    EfficiencyETBins[7]  = {10, 15, 20, 30, 40, 50, 1000000};
const double Efficiency[5][6][2]  = {{{0.877, 0.021}, {0.937, 0.008}, {0.952, 0.002}, {0.967, 0.001}, {0.971, 0.001}, {0.975, 0.001}}, 
				   {{0.877, 0.021}, {0.937, 0.008}, {0.962, 0.002}, {0.972, 0.001}, {0.975, 0.001}, {0.977, 0.001}}, 
				   {{0.769, 0.108}, {0.731, 0.019}, {0.895, 0.011}, {0.936, 0.004}, {0.959, 0.003}, {0.948, 0.008}}, 
				   {{0.936, 0.031}, {0.904, 0.009}, {0.937, 0.003}, {0.953, 0.002}, {0.960, 0.001}, {0.964, 0.003}}, 
				   {{0.936, 0.031}, {0.904, 0.009}, {0.894, 0.004}, {0.913, 0.002}, {0.931, 0.002}, {0.933, 0.004}}};
const double phistarBins[] = {0, 10};
const double etaBins[] = {-2.5, 2.5};
