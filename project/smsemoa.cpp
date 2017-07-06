// Implementation of the MO-CMA-ES
// #include <shark/Algorithms/DirectSearch/MOCMA.h>
// #include <shark/Algorithms/DirectSearch/RealCodedNSGAII.h>
#include <shark/Algorithms/DirectSearch/SMS-EMOA.h>
// #include <shark/Algorithms/DirectSearch/SteadyStateMOCMA.h>

#include <opencv2/opencv.hpp>
#include "multiObjectiveFunction.cpp"
#include <fstream>
#include <string>

using namespace shark;
using namespace cv;
using namespace std;

int main( int argc, char ** argv ) {

  if(argc!=5){
    cout<<"4 Arguements Needed."<<endl<<"Usage: ./mocmaes 1 1 720 480";
    return 0;
  }
  MOCMAES mocmaes;
  std::ofstream outfile;
  outfile.open("results.csv");
  outfile.precision(6);

  mocmaes.setNumberOfObjectives( 3 );
  mocmaes.setNumberOfVariables( 15 );

  mocmaes.setStartPoints(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
  mocmaes.calculateClearance();
  mocmaes.setProbability();

  //###begin<optimizer>
  // shark::MOCMA mocma;
  // shark::RealCodedNSGAII nsga;
  shark::SMSEMOA smsemoa;
  // shark::SteadyStateMOCMA ssmocma;

  // Initialize the optimizer for the objective function instance.
  smsemoa.init( mocmaes );
  //###end<optimizer>

  //###begin<loop>
  // Iterate the optimizer
  while( mocmaes.evaluationCounter() < 5000) {
    smsemoa.step( mocmaes );
  }
  //###end<loop>

  for( std::size_t i = 0; i < smsemoa.solution().size(); i++ ) {
      mocmaes.calcPathLength(smsemoa.solution()[i].point);
      for(std::size_t j= 0; j < mocmaes.numberOfObjectives(); j++ ){
        outfile<<smsemoa.solution()[ i ].value[j]<<" ";
      }
      outfile<<endl;
  }
  outfile.close();
}
