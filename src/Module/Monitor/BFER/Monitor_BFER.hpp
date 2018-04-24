#ifndef MONITOR_STD_HPP_
#define MONITOR_STD_HPP_

#include <chrono>
#include <vector>
#include <functional>

#include "../Monitor.hpp"
//#include "Tools/Algo/Histogram.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float>
class Monitor_BFER : public Monitor
{
public:
	inline Task&   operator[](const mnt::tsk                  t) { return Module::operator[]((int)t);                                 }
	inline Socket& operator[](const mnt::sck::check_errors    s) { return Module::operator[]((int)mnt::tsk::check_errors   )[(int)s]; }
	inline Socket& operator[](const mnt::sck::get_mutual_info s) { return Module::operator[]((int)mnt::tsk::get_mutual_info)[(int)s]; }

protected:
	const unsigned max_fe;

	unsigned long long n_bit_errors;
	unsigned long long n_frame_errors;
	unsigned long long n_analyzed_frames;

	R MI_sum;

	std::vector<std::function<void(unsigned, int )>> callbacks_fe;
	std::vector<std::function<void(          void)>> callbacks_check;
	std::vector<std::function<void(          void)>> callbacks_fe_limit_achieved;
//	tools::Histogram<R> llrs0, llrs1;

public:
	Monitor_BFER(const int K, const int N, const unsigned max_fe, const int n_frames = 1);
	virtual ~Monitor_BFER() = default;

	/*!
	 * \brief Compares two messages and counts the number of frame errors and bit errors.
	 *
	 * Typically this method is called at the very end of a communication chain.
	 *
	 * \param U: the original message (from the Source or the CRC).
	 * \param Y: the decoded message (from the Decoder).
	 */
	template <class A = std::allocator<B>>
	int check_errors(const std::vector<B,A>& U, const std::vector<B,A>& Y, const int frame_id = -1)
	{
		if ((int)U.K() != this->K * this->n_frames)
		{
			std::stringstream message;
			message << "'U.K()' has to be equal to 'K' * 'n_frames' ('U.K()' = " << U.K()
			        << ", 'K' = " << this->K << ", 'n_frames' = " << this->n_frames << ").";
			throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
		}

		if ((int)Y.K() != this->K * this->n_frames)
		{
			std::stringstream message;
			message << "'Y.K()' has to be equal to 'K' * 'n_frames' ('Y.K()' = " << Y.K()
			        << ", 'K' = " << this->K << ", 'n_frames' = " << this->n_frames << ").";
			throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
		}

		if (frame_id != -1 && frame_id >= this->n_frames)
		{
			std::stringstream message;
			message << "'frame_id' has to be equal to '-1' or to be smaller than 'n_frames' ('frame_id' = "
			        << frame_id << ", 'n_frames' = " << this->n_frames << ").";
			throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
		}

		return this->check_errors(U.data(), Y.data(), frame_id);
	}

	template <class AB = std::allocator<B>, class AR = std::allocator<R>>
	R get_mutual_info(const std::vector<B,AB>& X, const std::vector<R,AR>& Y, const int frame_id = -1)
	{
		if ((int)X.K() != this->K * this->n_frames)
		{
			std::stringstream message;
			message << "'X.K()' has to be equal to 'K' * 'n_frames' ('X.K()' = " << X.K()
			        << ", 'K' = " << this->K << ", 'n_frames' = " << this->n_frames << ").";
			throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
		}

		if ((int)Y.K() != this->K * this->n_frames)
		{
			std::stringstream message;
			message << "'Y.K()' has to be equal to 'K' * 'n_frames' ('Y.K()' = " << Y.K()
			        << ", 'K' = " << this->K << ", 'n_frames' = " << this->n_frames << ").";
			throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
		}

		if (frame_id != -1 && frame_id >= this->n_frames)
		{
			std::stringstream message;
			message << "'frame_id' has to be equal to '-1' or to be smaller than 'n_frames' ('frame_id' = "
			        << frame_id << ", 'n_frames' = " << this->n_frames << ").";
			throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
		}

		return this->check_errors(X.data(), Y.data(), frame_id);
	}

	virtual int check_errors   (const B *U, const B *Y, const int frame_id = -1);
	virtual R   get_mutual_info(const B *X, const R *Y, const int frame_id = -1);

	virtual bool fe_limit_achieved();
	unsigned get_fe_limit() const;

	virtual unsigned long long get_n_analyzed_fra() const;
	virtual unsigned long long get_n_fe          () const;
	virtual unsigned long long get_n_be          () const;
	virtual R                  get_MI            () const;
	virtual R                  get_MI_sum        () const;
//	virtual const tools::Histogram<R>&  get_llrs0();
//	virtual const tools::Histogram<R>&  get_llrs1();

	float get_fer   () const;
	float get_ber   () const;

	virtual void add_handler_fe               (std::function<void(unsigned, int )> callback);
	virtual void add_handler_check            (std::function<void(          void)> callback);
	virtual void add_handler_fe_limit_achieved(std::function<void(          void)> callback);

	virtual void reset();
	virtual void clear_callbacks();

protected:
	virtual R   _get_mutual_info(const B *X, const R *Y, const int frame_id);
	virtual int _check_errors   (const B *U, const B *Y, const int frame_id);
};
}
}

#endif /* MONITOR_STD_HPP_ */
