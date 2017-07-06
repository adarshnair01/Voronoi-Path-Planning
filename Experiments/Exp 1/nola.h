#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/ObjectiveFunctions/BoxConstraintHandler.h>
#include <cmath>
// #include <shark/Rng/GlobalRng.h>


using namespace shark;

class NOLA : public MultiObjectiveFunction
{
public:
    NOLA(double a = 2, std::size_t dimensions = 3, std::size_t objectives = 2)
    :m_a(a),m_dimensions(dimensions), m_objectives(objectives){
    }
    std::string name() {
        return "Nola";
    }
    std::size_t numberOfVariables()const{
        return m_dimensions;
    }
    bool hasScalableDimensionality()const{
        return true;
    }
    void setNumberOfVariables( std::size_t numberOfVariables ){
        m_dimensions = numberOfVariables;
    }
    std::size_t numberOfObjectives()const{
        return m_objectives;
    }
    bool hasScalableObjectives()const{
        return true;
    }
    void setNumberOfObjectives( std::size_t numberOfObjectives ){
        m_objectives = numberOfObjectives;
    }

    ResultType eval( const SearchPointType & input )const {
        SIZE_CHECK(input.size() == m_dimensions );
        ResultType result(m_objectives);
        result(0) = input(1);
        //more objectives here...
        return result;
    }
private:
    double m_a;
    std::size_t m_dimensions;
    std::size_t m_objectives;
};
