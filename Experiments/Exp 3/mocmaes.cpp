/*!
 *
 *
 * \brief       Example for running MO-CMA-ES on an exemplary benchmark function.

 *
 *
 * \author      tvoss
 * \date        -
 *
 *
 * \par Copyright 1995-2015 Shark Development Team
 *
 * <BR><HR>
 * This file is part of Shark.
 * <http://image.diku.dk/shark/>
 *
 * Shark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Shark.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
//###begin<includes>
// Implementation of the MO-CMA-ES
#include <shark/Algorithms/DirectSearch/MOCMA.h>
// Access to benchmark functions
#include "Dextrous.cpp"
//###end<includes>

using namespace std;

int main( int argc, char ** argv ) {

	// Adjust the floating-point format to scientific and increase output precision.
	std::cout.setf( std::ios_base::scientific );
	std::cout.precision( 10 );

	// Instantiate both the problem and the optimizer.
//###begin<problem>
	shark::DEXTROUS dext;
	dext.setNumberOfObjectives( 2 );
	dext.setNumberOfVariables( 10 );
//###end<problem>

//###begin<optimizer>
	shark::MOCMA mocma;

	// Initialize the optimizer for the objective function instance.
	mocma.init( dext );
//###end<optimizer>

//###begin<loop>
	// Iterate the optimizer
	while( dext.evaluationCounter() < 25000 ) {
		mocma.step( dext );
	}
//###end<loop>

//###begin<print>
	// Print the optimal pareto front
	for( std::size_t i = 0; i < mocma.solution().size(); i++ ) {
		for( std::size_t j = 0; j < dext.numberOfObjectives(); j++ ) {
			std::cout<< mocma.solution()[ i ].value[j]<<" ";
		}
		cout<<endl<<mocma.solution()[i].point<<endl;
		std::cout << std::endl;
	}
//###end<print>
}
