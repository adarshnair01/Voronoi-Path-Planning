// Implementation of the MO-CMA-ES
#include <shark/Algorithms/DirectSearch/MOCMA.h>
// #include <shark/Algorithms/DirectSearch/RealCodedNSGAII.h>
// #include <shark/Algorithms/DirectSearch/SMS-EMOA.h>
// #include <shark/Algorithms/DirectSearch/SteadyStateMOCMA.h>

#include <opencv2/opencv.hpp>
#include "multiObjectiveFunction.cpp"
#include <fstream>
#include <string>

#include <sys/time.h>
typedef unsigned long long timestamp_t;

using namespace shark;
using namespace cv;
using namespace std;

static timestamp_t
get_timestamp()
{
  struct timeval now;
  gettimeofday(&now, NULL);
  return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

int main(int argc, char **argv)
{

  if (argc != 5)
  {
    cout << "4 Arguements Needed." << endl
         << "Usage: ./mocmaes 1 1 720 480";
    return 0;
  }
  MOCMAES mocmaes;
  std::ofstream outfile;
  outfile.open("results.csv");
  outfile.precision(6);

  mocmaes.setNumberOfObjectives(3);
  mocmaes.setNumberOfVariables(15);

  mocmaes.setStartPoints(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
  mocmaes.calculateClearance();
  mocmaes.setProbability();

  //###begin<optimizer>
  shark::MOCMA mocma;
  // shark::RealCodedNSGAII nsga;
  // shark::SMSEMOA smsemoa;
  // shark::SteadyStateMOCMA ssmocma;
  timestamp_t t0 = get_timestamp();
  // Initialize the optimizer for the objective function instance.
  mocma.init(mocmaes);
  //###end<optimizer>

  //###begin<loop>
  // Iterate the optimizer
  while (mocmaes.evaluationCounter() < 25000)
  {
    mocma.step(mocmaes);
  }
  //###end<loop>

  timestamp_t t1 = get_timestamp();
  for (std::size_t i = 0; i < mocma.solution().size(); i++)
  {
    mocmaes.calcPathLength(mocma.solution()[i].point);
    for (std::size_t j = 0; j < mocmaes.numberOfObjectives(); j++)
    {
      outfile << mocma.solution()[i].value[j] << " ";
    }
    outfile << endl;
  }
  outfile.close();

  double secs = (t1 - t0) / 1000000.0L;
  cout << endl
       << "time: " << secs << endl;
}
