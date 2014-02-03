
const double EfficiencyEtaBins[6] = {0.0, 0.8, 1.4442, 1.566, 2.0, 2.5};
const int    EfficiencyETBins[7]  = {10, 15, 20, 30, 40, 50, 1000000};
const double Efficiency[5][6][2]  = {{{0.877, 0.021}, {0.937, 0.008}, {0.952, 0.002}, {0.967, 0.001}, {0.971, 0.001}, {0.975, 0.001}}, 
				     {{0.877, 0.021}, {0.937, 0.008}, {0.962, 0.002}, {0.972, 0.001}, {0.975, 0.001}, {0.977, 0.001}}, 
				     {{0.769, 0.108}, {0.731, 0.019}, {0.895, 0.011}, {0.936, 0.004}, {0.959, 0.003}, {0.948, 0.008}}, 
				     {{0.936, 0.031}, {0.904, 0.009}, {0.937, 0.003}, {0.953, 0.002}, {0.960, 0.001}, {0.964, 0.003}}, 
				     {{0.936, 0.031}, {0.904, 0.009}, {0.894, 0.004}, {0.913, 0.002}, {0.931, 0.002}, {0.933, 0.004}}};
const double EfficiencySF[5][6][3]  = {{{0.977,0.024,0.054}, {0.997,0.009,0.031}, {0.982,0.003,0.012}, {0.988,0.001,0.008}, {0.990,0.001,0.004}, {0.990,0.001,0.004}}, 
				       {{0.977,0.024,0.054}, {0.997,0.009,0.031}, {0.993,0.002,0.012}, {0.993,0.001,0.008}, {0.993,0.001,0.004}, {0.991,0.001,0.004}}, 
				     {{1.076,0.152,0.095}, {0.952,0.025,0.070}, {1.016,0.012,0.020}, {0.985,0.004,0.009}, {0.987,0.004,0.004}, {0.974,0.009,0.006}}, 
				     {{1.096,0.036,0.060}, {1.008,0.010,0.031}, {0.988,0.003,0.012}, {0.993,0.002,0.008}, {0.992,0.001,0.004}, {0.990,0.003,0.004}}, 
				     {{1.096,0.036,0.060}, {1.008,0.010,0.031}, {1.002,0.004,0.012}, {1.004,0.002,0.008}, {1.005,0.002,0.004}, {0.998,0.004,0.004}}};
const double phistarBins[] = {0, 1,2,10};
const double etaBins[] = {-5.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,5.0};

int BinInArray(double val, const double *array, int size){
  if (val<array[0]||val>array[size]) return -1;
  int bin=0;
  for (int i_bin=0; i_bin<size-1;i_bin++){
    if (val<array[i_bin+1]) return bin;
    bin++;
  }
  return -1;
}

int BinInArray(double val, const int *array, int size){
  if (val<array[0]||val>array[size]) return -1;
  int bin=0;
  for (int i_bin=0; i_bin<size-1;i_bin++){
    if (val<array[i_bin+1]) return bin;
    bin++;
  }
  return -1;
}