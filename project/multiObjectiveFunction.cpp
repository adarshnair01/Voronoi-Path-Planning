#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_MOCMAES_H
#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_MOCMAES_H

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/ObjectiveFunctions/BoxConstraintHandler.h>
#include <vector>
#include <algorithm>
#include <limits>
#include "spline.h"
// #include "common.h"

using namespace shark;
using namespace cv;
using namespace std;

namespace shark
{

int startx = 0;
int starty = 0;
int endx = 240;
int endy = 240;
Mat image = (imread("image.jpg", CV_LOAD_IMAGE_GRAYSCALE)) > 70;
Mat drawing, voronoi;
std::size_t outputs = 0;
std::vector<cv::Point> pixelPoints;
std::vector<int> pixelValues;
Mat prob = imread("prob.jpg", CV_LOAD_IMAGE_GRAYSCALE);

struct MOCMAES : public MultiObjectiveFunction
{
	//Constructor
	MOCMAES(std::size_t numVariables = 0) : m_objectives(2), m_handler(SearchPointType(numVariables, 0), SearchPointType(numVariables, 1))
	{
		announceConstraintHandler(&m_handler);
		m_features |= CAN_PROPOSE_STARTING_POINT;
		Size size(720, 480);
		resize(image, image, size);
		imwrite("image.jpg", image);
	}

	/// \brief From INameable: return the class name.
	std::string name() const
	{
		return "MOCMAES";
	}

	//Function to get number of objectives of this problem
	std::size_t numberOfObjectives() const
	{
		return m_objectives;
	}

	//Boolean function to know if having scalable objectives
	bool hasScalableObjectives() const
	{
		return true;
	}

	//Set number of objectives for this problem
	void setNumberOfObjectives(std::size_t numberOfObjectives)
	{
		m_objectives = numberOfObjectives;
	}

	//Get Number of variables
	std::size_t numberOfVariables() const
	{
		return m_handler.dimensions();
	}

	//Boolen return to know if is having scalable dimensionality
	bool hasScalableDimensionality() const
	{
		return true;
	}

	//Propose A starting point here if wanted
	SearchPointType proposeStartingPoint()
	{
		RealVector x(numberOfVariables());
		//   std::ofstream outfile;
		//   outfile.open("data.txt");
		//   outfile.precision(6);
		//
		//
		//
		// 	outfile<<"hello"<<endl;
		cv::Point p;
		x(0) = Rng::uni(0, 1);
		for (size_t i = 1; i != x.size(); i += 2)
		{
			// startingpoint(i)=Rng::uni(0,1);
			p = getPoints();
			// outfile<<p.x<<" "<<p.y<<endl;
			x(i) = p.x / image.cols;
			x(i + 1) = p.y / image.rows;
		}
		return x;
		// outfile.close();
	}

	//Set number of variables
	void setNumberOfVariables(std::size_t numberOfVariables)
	{
		m_handler.setBounds(
			SearchPointType(numberOfVariables, 0),
			SearchPointType(numberOfVariables, 1));
	}

	void setStartPoints(int sx, int sy, int ex, int ey)
	{
		startx = sx;
		starty = sy;
		endx = ex;
		endy = ey;
	}

	void setProbability()
	{
		unsigned char const *p = voronoi.ptr<unsigned char>();
		unsigned char const *q = image.ptr<unsigned char>();
		unsigned char const *r = prob.ptr<unsigned char>();
		long long int total;
		for (int i = 0; i < voronoi.rows * voronoi.cols; ++i, ++p, ++q, ++r)
		{
			if (*q != 0)
			{
				int x = i % voronoi.cols;
				int y = i / voronoi.cols;
				pixelPoints.push_back(cv::Point(x, y));
				pixelValues.push_back(*r);
				// if(*p==0)
				//   pixelValues.push_back(10);
				// else
				//   pixelValues.push_back(2);
				total += pixelValues.back();
			}
		}
		for (size_t i = 0; i < pixelValues.size(); i++)
		{
			pixelValues[i] /= total;
		}
	}

	cv::Point getPoints()
	{
		cv::Point p;
		double rndNumber = rand() / (double)RAND_MAX;
		double offset = 0.0;
		size_t result;

		for (size_t i = 0; i < pixelPoints.size(); i++)
		{
			offset += pixelValues[i];
			if (rndNumber < offset)
			{
				result = i;
				break;
			}
		}

		return pixelPoints[result];
	}

	void calculateClearance()
	{
		Mat rect(image.size(), CV_8UC1);
		drawing = image.clone();

		rect = Scalar(0, 0, 0);
		rectangle(rect, Point(0, 0), Point(drawing.cols, drawing.rows), Scalar(255, 255, 255), +50, 4);
		bitwise_or(drawing, rect, drawing);
		voronoi = drawing.clone();
		//Get contours and apply contour border to get clearance value
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(drawing, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		//Create a new matrix with same size and draw contour and fill its area
		// Mat drawing( bw.size(), CV_8UC1 );
		drawing = Scalar(25, 25, 25);
		for (size_t j = 25; j > 0; j--)
		{
			for (int i = 0; i < contours.size(); i++)
			{
				if (contourArea(contours[i]) > 100)
				{
					drawContours(drawing, contours, i, Scalar(j, j, j), j, 8, hierarchy, 0, Point());
					if (i != 0)
						drawContours(drawing, contours, i, Scalar(0, 0, 0), CV_FILLED, 8, hierarchy, 0, Point());
				}
			}
		}

		//Get the clearance value for border of image
		resize(rect, rect, cvSize(drawing.cols - 50, drawing.rows - 50));
		rect = Scalar(255, 255, 255);
		for (size_t i = 25; i > 0; i--)
		{
			copyMakeBorder(rect, rect, 1, 1, 1, 1, BORDER_CONSTANT, i);
		}
		drawing = min(drawing, rect);
		// imwrite("clearance.jpg",drawing);

		findContours(voronoi, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (size_t j = 217; j > 0; j--)
		{
			for (int i = 0; i < contours.size(); i++)
			{
				if (contourArea(contours[i]) > 100)
				{
					drawContours(voronoi, contours, i, Scalar(j, j, j), j * 2, 8, hierarchy, 0, Point());
					if (i != 0)
						drawContours(voronoi, contours, i, Scalar(0, 0, 0), CV_FILLED, 8, hierarchy, 0, Point());
				}
			}
		}
		rect = Scalar(255, 255, 255);
		subtract(rect, voronoi, voronoi);
		adaptiveThreshold(voronoi, voronoi, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
		// imwrite("voronoi.jpg",voronoi);

		// imshow( "Result window", drawing );

		// imwrite("clearance.jpg",drawing);
		// imshow("s",s.image);
	}

	void calculatePathLength(const SearchPointType &x, RealVector &r) const
	{
		std::vector<double> t;
	std:
		size_t skip = 0;
		double ll, sm;
		double current_x, current_y, previous_x, previous_y, ls, previous_ls;
		double path_length = 0.0;
		double clearance = 0.0;
		double smoothness = 0.0;
		tk::spline spline_points_x, spline_points_y;
		double obstacle_count = 0;
		std::vector<double> p1, p2;
		int n = x(0) * ((x.size() - 1) / 2);

		p1.push_back(startx);
		p2.push_back(starty);
		for (size_t i = 0; i < 2 * n; i += 2)
		{
			if (x(i) == x(i + 2) || x(i + 1) == x(i + 3))
			{
				r[0] = DBL_MAX;
				r[1] = DBL_MAX;
				r[2] = DBL_MAX;
				return;
			}
			p1.push_back(abs(round(x(i) * image.cols)));
			p2.push_back(abs(round(x(i + 1) * image.rows)));
		}
		p1.push_back(endx);
		p2.push_back(endy);

		// Get another variale in order to get incremental x axis for spline interpolation
		t.push_back(0);
		for (size_t i = 0; i < p1.size() - 1; i++)
		{
			ll = sqrt(sqr(p1[i + 1] - p1[i]) + sqr(p2[i + 1] - p2[i]));
			path_length += ll;
			t.push_back(path_length);
		}
		for (size_t i = 0; i < t.size(); i++)
		{
			t[i] /= path_length;
		}

		spline_points_x.set_points(t, p1); // currently it is required that X is already sorted for finding spline points
		spline_points_y.set_points(t, p2);

		path_length = 0.0;
		previous_x = round(spline_points_x(0));
		previous_y = round(spline_points_y(0));
		current_x = round(spline_points_x(0.01));
		current_y = round(spline_points_y(0.01));

		path_length += sqrt(sqr(previous_x - current_x) + sqr(previous_y - current_y));

		previous_ls = atan2((current_y - previous_y), (current_x - previous_x));

		//Find points of spline and calculate first objective function(path length)
		for (double i = 0.02; i < 1; i += 0.01)
		{
			current_x = round(spline_points_x(i));
			current_y = round(spline_points_y(i));
			if (current_x < 0 || current_y < 0 || current_x > image.cols || current_y > image.rows)
			{
				obstacle_count++;
			}
			else
			{
				clearance += (static_cast<int>(drawing.at<uchar>(Point(current_x, current_y))));
				if (!(static_cast<int>(image.at<uchar>(Point(current_x, current_y)))))
				{
					cout << obstacle_count << endl;
					obstacle_count++;
				}
			}

			ls = atan2((current_y - previous_y), (current_x - previous_x));
			sm = abs(atan2(cos(ls - previous_ls), sin(ls - previous_ls)));
			smoothness = min(smoothness, sm);
			previous_ls = ls;

			path_length += sqrt(sqr(previous_x - current_x) + sqr(previous_y - current_y));

			previous_x = current_x;
			previous_y = current_y;
		}

		// if(isnan(abs(smoothness))||isnan(abs(clearance))||isnan(abs(path_length))){
		// 	r[0]=DBL_MAX;
		// 	r[1]=DBL_MAX;
		// 	r[2]=DBL_MAX;
		// 	return;
		// }

		r[0] = path_length + 99999999999999999 * obstacle_count;
		r[1] = -clearance + 99999999999999999 * obstacle_count;
		r[2] = smoothness + 99999999999999999 * obstacle_count;
		// return path_length+99999999999999999*obstacle_count;
	}

	double calcPathLength(const SearchPointType &x) const
	{
		std::ofstream outfile;
		string filename;
		std::stringstream sstm;
		sstm.str(std::string());
		sstm << "../p5js/Exp1/public/paths/path" << outputs << ".json";
		filename = sstm.str();
		outfile.open(filename.c_str());
		outfile.precision(6);
		std::vector<double> t;
		double ll;
		std::vector<double> line_length;
		double path_length = 0.0;
		tk::spline spline_points_x, spline_points_y;

		std::vector<double> p1, p2;
		int n = x(0) * ((x.size() - 1) / 2);

		p1.push_back(startx);
		p2.push_back(starty);
		for (size_t i = 0; i < 2 * n; i += 2)
		{
			if (x(i) == x(i + 2) || x(i + 1) == x(i + 3))
			{
				return DBL_MAX;
			}
			p1.push_back(abs(round(x(i) * image.cols)));
			p2.push_back(abs(round(x(i + 1) * image.rows)));
		}
		p1.push_back(endx);
		p2.push_back(endy);

		t.push_back(0);
		for (size_t i = 0; i < p1.size() - 1; i++)
		{
			ll = sqrt(sqr(p1[i + 1] - p1[i]) + sqr(p2[i + 1] - p2[i]));
			line_length.push_back(ll);
			path_length += ll;
			t.push_back(path_length);
		}
		for (size_t i = 0; i < t.size(); i++)
		{
			t[i] /= path_length;
		}

		spline_points_x.set_points(t, p1);
		spline_points_y.set_points(t, p2);
		outfile << "{\n\"points\":[\n";
		for (double i = 0; i < 1; i += 0.01)
		{
			outfile << "\t{\"x\":\"" << spline_points_x(i) << "\", \"y\":\"" << spline_points_y(i) << "\"},\n";
		}
		outfile << "\t{\"x\":\"" << spline_points_x(1) << "\", \"y\":\"" << spline_points_y(1) << "\"}\n";
		outfile << "]}";
		outfile.close();
		outputs++;
		//cout<<static_cast<int>(drawing.at<uchar>(Point(spline_points_x(1),spline_points_y(1))))<<endl;
	}

	//Main eval function to get fitness values
	ResultType eval(const SearchPointType &x) const
	{
		m_evaluationCounter++;
		if (!m_handler.isFeasible(x))
			throw SHARKEXCEPTION("input point not feasible");
		RealVector value(numberOfObjectives());
		calculatePathLength(x, value);
		return value;
	}

  private:
	std::size_t m_objectives;
	BoxConstraintHandler<SearchPointType> m_handler;
};
}
#endif
