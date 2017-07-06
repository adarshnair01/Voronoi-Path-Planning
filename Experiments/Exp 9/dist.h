#include <shark/Data/Dataset.h>
#include <shark/Data/DataDistribution.h>
#include <shark/Data/Csv.h>
#include <shark/Data/SparseData.h>
using namespace shark;

class voronoi: LabeledDataDistribution<RealVector, unsigned int>{
    public:
        void draw(RealVector& input, unsigned int& label) const
        {
            input.resize(2);
            label = Rng::coinToss();
            input(0) = Rng::uni(-1,1);
            input(1) = Rng::uni(-1,1) + label;
        }
};
