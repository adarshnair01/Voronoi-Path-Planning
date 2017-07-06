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
// Implementation of the MO-CMA-ES
#include <shark/Algorithms/DirectSearch/MOCMA.h>
// Access to benchmark functions
// #include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>
#include "nola.h"

int main( int argc, char ** argv ) {

	// Adjust the floating-point format to scientific and increase output precision.
	std::cout.setf( std::ios_base::scientific );
	std::cout.precision( 10 );

	// Instantiate both the problem and the optimizer.
	NOLA nola;
	nola.setNumberOfObjectives( 2 );
	nola.setNumberOfVariables( 10 );

	shark::MOCMA mocma;

	// Initialize the optimizer for the objective function instance.
	mocma.init( nola );

	// Iterate the optimizer
	while( nola.evaluationCounter() < 2 ) {
		mocma.step( nola );
	}

	// Print the optimal pareto front
	for( std::size_t i = 0; i < mocma.solution().size(); i++ ) {
		for( std::size_t j = 0; j < nola.numberOfObjectives(); j++ ) {
			std::cout<< mocma.solution()[ i ].value[j]<<" "<<std::endl;
		}
    std::cout<<mocma.solution()[i].point<<std::endl;
		std::cout << std::endl;
	}
}
