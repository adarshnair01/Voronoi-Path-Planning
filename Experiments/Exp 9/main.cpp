#include "dist.h"
using namespace shark;

int main(){
  Data<RealVector> points;
  ClassificationDataset dataset;
  voronoi distribution;
  unsigned int numberOfSamples = 1000;
  dataset = distribution.generateDataset(numberOfSamples);
}
