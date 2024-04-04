/*!
 * \file
 * \brief Class tools::RS_polynomial_generator.
 */
#ifndef RS_POLYNOMIAL_GENERATOR_HPP
#define RS_POLYNOMIAL_GENERATOR_HPP

#include <vector>

#include "Tools/Math/Galois.hpp"

/* source : http://www.eccpage.com/  */

namespace aff3ct
{
namespace tools
{
class RS_polynomial_generator : public Galois<int>
{
protected:
	const int t;
	const int d;
	const int m_iniroot;

	std::vector<int> g; // coefficients of the generator polynomial, g(x)

public:
	//p is the primitive polynominal.if g(x) = x4+x+1;p={1,1,0,0,1};
	//default iniroot is 1--> alpha
	RS_polynomial_generator(const int& N, const int& t,const std::vector<int> p = {},int iniroot = 1);
	virtual ~RS_polynomial_generator() = default;

	int get_d      () const;
	int get_t      () const; // get the correction power
	int get_n_rdncy() const; // get the number of redundancy bits

	const std::vector<int>& get_g() const; // get the coefficients of the generator polynomial

private:
	void compute_polynomial();
};
}
}

#endif /* RS_POLYNOMIAL_GENERATOR_HPP */
