#ifndef SIMULATION_BFER_STD_THREADS_HPP_
#define SIMULATION_BFER_STD_THREADS_HPP_

#include "Factory/Simulation/BFER/BFER_std.hpp"
#include "Simulation/Legacy/BFER/Standard/BFER_std.hpp"

namespace aff3ct
{
namespace simulation
{
template <typename B = int, typename R = float, typename Q = R>
class BFER_std_threads : public BFER_std<B,R,Q>
{
public:
	explicit BFER_std_threads(const factory::BFER_std &params_BFER_std);
	virtual ~BFER_std_threads() = default;

protected:
	virtual void _launch();

private:
	void sockets_binding(const int tid = 0, const bool unbind = false);
	void simulation_loop(const int tid = 0                           );
	void start_thread   (const int tid = 0                           );
};
}
}

#endif /* SIMULATION_BFER_STD_THREADS_HPP_ */
