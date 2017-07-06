//===========================================================================
/*!
 *
 *
 * \brief       Objective function MOCMAES
 *
 *
 *
 * \author      T.Voss, T. Glasmachers, O.Krause
 * \date        2010-2011
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
//===========================================================================
#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_MOCMAES_H
#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_MOCMAES_H

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/ObjectiveFunctions/BoxConstraintHandler.h>
#include <vector>
#include <algorithm>
#include <limits>

#include "start.h"
#define PI 3.14



namespace shark {

/**
* \brief Implements the benchmark function MOCMAES.
*
* See: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.7531&rep=rep1&type=pdf
* The benchmark function exposes the following features:
*	- Scalable w.r.t. the searchspace and w.r.t. the objective space.
*	- Highly multi-modal.
*/
struct NOLA: public MultiObjectiveFunction
{
	NOLA(std::size_t numVariables = 0) : m_objectives(2), m_handler(SearchPointType(numVariables,0),SearchPointType(numVariables,1) ){
		announceConstraintHandler(&m_handler);
		m_features |= CAN_PROPOSE_STARTING_POINT;
	  s.startx=1;
	  s.starty=1;
	  s.endx=240;
	  s.endy=240;
	  s.image = imread("logo.png", 1 );
	}




	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "NOLA"; }

	std::size_t numberOfObjectives()const{
		return m_objectives;
	}
	bool hasScalableObjectives()const{
		return true;
	}
	void setNumberOfObjectives( std::size_t numberOfObjectives ){
		m_objectives = numberOfObjectives;
	}

	std::size_t numberOfVariables()const{
		return m_handler.dimensions();
	}

	bool hasScalableDimensionality()const{
		return true;
	}

	void proposeStartingPoint( SearchPointType & startingpoint){
		for (size_t i = 0; i !=startingpoint.size(); ++i) {
			/* code */
			startingpoint(i)=Rng::uni(0,1);
		}
	}


	/// \brief Adjusts the number of variables if the function is scalable.
	/// \param [in] numberOfVariables The new dimension.
	void setNumberOfVariables( std::size_t numberOfVariables ){
		m_handler.setBounds(
			SearchPointType(numberOfVariables,0),
			SearchPointType(numberOfVariables,1)
		);
	}

	ResultType eval( const SearchPointType & x ) const {
		m_evaluationCounter++;
		if(!m_handler.isFeasible(x))
			throw SHARKEXCEPTION("input point not feasible");

		RealVector value( numberOfObjectives() );
		//
		// std::vector<std::pair<double, double> > p;
		// std::vector <double> p1,p2;
		// double ll,ls;
		// std::vector <double>line_length, line_slope;
		//
		//
		// double delta=5;
		//
		double path_length=0.0;
		//
		// tk::spline spline_points;
		//
		// double current_x,current_y,previous_x,previous_y;
		//
		// p.push_back(std::make_pair(s.startx,s.starty));
		// // p1.push_back(s.startx);
		// // p2.push_back(s.starty);
		//
		// for (size_t i = 0; i < x.size(); i+=2) {
		// 	p.push_back(std::make_pair(round(x(i)*250),round(x(i+1)*250)));
		// 	// p1.push_back(round(x(i)*250));
		// 	// p2.push_back(round(x(++i)*250));
		// 	/* code */
		// }
		//
		// p.push_back(std::make_pair(s.endx,s.endy));
		// // p1.push_back(s.endx);
		// // p2.push_back(s.endy);
		//
		// std::sort(p.begin(), p.end(), boost::bind(&std::pair<double, double>::second, _1) < boost::bind(&std::pair<double, double>::second, _2));
		//
		// for(std::vector <std::pair <double, double> >::iterator  it = p.begin(); it != p.end(); ++it) {
		// 	p1.push_back(it->first);
		// 	p2.push_back(it->second);
		// }
		//
		// // spline_points.set_points(p1,p2);    // currently it is required that X is already sorted
		//
		//
		// for (size_t i = 0; i < p1.size()-1; i++) {
		// 	ll=sqrt(sqr(p1[i+1]-p1[i])+sqr(p2[i+1]-p2[i]));
		// 	line_length.push_back(ll);
		// 	ls=atan2((p2[i+1]-p2[i]),(p1[i+1]-p1[i]));
		// 	line_slope.push_back(ls);
		// }
		//
		// for (size_t i = 0; i < p1.size()-1; i++) {
		// 	previous_x=p1[i];
		// 	previous_y=p2[i];
		// 	for (size_t j = 1; j < line_length[i]; j+=delta) {
		// 		current_x=p1[i]+j*cos(line_slope[i]);
		// 		current_y=spline_points(current_x);
		// 		path_length+=sqrt(sqr(previous_x - current_x)+sqr(previous_y - current_y));
		// 		previous_y=current_y;
		// 		previous_x=current_x;
		// 	}
		// }
		value[0]=path_length;
		value[1]=path_length;

		// double angle;
		// double ll,ls;
		// std::vector <double>line_length, line_slope;
		// double slope_diff=0.0;
		// int intermediate_x,intermediate_y;
		// int infinite_flag;
		//
		// double delta=5;
		//
		// double path_length=0.0;
		// double smoothness=0.0;
		// double feasibility=0.0;
		//
		// //path Length
		// for (size_t i = 0; i < p1.size()-1; i++) {
		// 	ll=sqrt(sqr(p1[i+1]-p1[i])+sqr(p2[i+1]-p2[i]));
		// 	line_length.push_back(ll);
		// 	for (size_t j = 1; j < line_length[i]; j+=delta) {
		// 		p1[i]
		// 		p1[i]+j*cos(line_slope[i])
		// 		path_length+=sqrt(sqr(p1[i+1]-p1[i])+sqr(p2[i+1]-p2[i]));
		// 	}
		// }
		// value[0]=path_length;
		//
		// //smoothness
		// line_slope.push_back(atan2((p2[1]-p2[0]),(p1[1]-p1[0])));
		// for (size_t i = 1; i < p1.size()-1; i++) {
		// 	ls=atan2((p2[i+1]-p2[i]),(p1[i+1]-p1[i]));
		// 	line_slope.push_back(ls);
		// 	slope_diff=line_slope[i]-line_slope[i-1];
		// 	angle=abs(atan2(cos(slope_diff),sin(slope_diff)));
		// 	smoothness+=angle;
		// }
		// value[1]=smoothness;
		//
		// //feasiblity
		// for (size_t i = 0; i < p1.size()-1; i++) {
		// 	if(p1[i]>250||p2[i]>250){
		// 		infinite_flag=1;
		// 		value[0]=FLT_MAX;
		// 		value[1]=FLT_MAX;
		// 		break;
		// 	}
		// 	for (size_t j = 1; j < line_length[i]; j+=delta) {
		// 		intermediate_x=round(p1[i]+j*cos(line_slope[i]));
		// 		intermediate_y=round(p2[i]+j*sin(line_slope[i]));
		// 		if(s.image.at<double>(intermediate_x,intermediate_y)!=0.0){
		// 			infinite_flag=1;
		// 			value[0]=FLT_MAX;
		// 			value[1]=FLT_MAX;
		// 			break;
		// 		}
		// 	}
		// 	if(infinite_flag==1)
		// 		break;
		// }

				// double sum,minus,a,b;
				// int k;
				// sum=minus=0.0;
				// a=0.5;
				// b=3;
				// k=20;
				//
				// // Discus Function
				// sum = pow(10,6) * sqr(x(0));
				// for (std::size_t i = 1; i < x.size(); i++)
				// 	sum +=  sqr(x(i));
				//
				// value[0] = sum;
				//
				// sum=0.0;
				// // Weierstrass Function
				// for (std::size_t i = 1; i < x.size(); i++){
				// 	for (std::size_t j = 0; j < k; j++) {
				// 		sum+=pow(a,j)*cos(2*PI*pow(b,j)*(x(i)+0.5));
				// 	}
				// }
				// for(std::size_t j = 0; j < k; j++)
				// 	minus+=pow(a,j)*cos(2*PI*pow(b,j)*(0.5));
				// minus*=x.size();
				//
				// value[1] = sum-minus;
				//
				// sum=0.0;
				// //Rosenbrock's Function
				// for (std::size_t i = 0; i < x.size()-1; i++)
				// 	sum +=  (100*sqr(sqr(x(i))-sqr(x(i+1))))+sqr(x(i)-1);
				//
				// value[2]=sum;

		return value;
	}
private:
	start s;
	std::size_t m_objectives;
	BoxConstraintHandler<SearchPointType> m_handler;
};

}
#endif
