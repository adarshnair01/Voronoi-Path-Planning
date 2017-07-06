// Implementation of the MO-CMA-ES
#include <shark/Algorithms/DirectSearch/MOCMA.h>
#include <opencv2/opencv.hpp>
#include "multiObjectiveFunction.cpp"
#include <fstream>
#include <string>

using namespace shark;
using namespace cv;
using namespace std;

int main( int argc, char ** argv ) {

  if(argc!=5){
    cout<<"4 Arguements Needed."<<endl<<"Usage: ./mocmaes startx starty endx endy";
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

  //###begin<optimizer>
  shark::MOCMA mocma;

  // Initialize the optimizer for the objective function instance.
  mocma.init( mocmaes );
  //###end<optimizer>

  //###begin<loop>
  // Iterate the optimizer
  while( mocmaes.evaluationCounter() < 25000) {
    mocma.step( mocmaes );
  }
  //###end<loop>

  for( std::size_t i = 0; i < mocma.solution().size(); i++ ) {
      mocmaes.calcPathLength(mocma.solution()[i].point);
      for(std::size_t j= 0; j < mocmaes.numberOfObjectives(); j++ ){
        outfile<<mocma.solution()[ i ].value[j]<<" ";
      }
      outfile<<endl;
  }
  outfile.close();
}
