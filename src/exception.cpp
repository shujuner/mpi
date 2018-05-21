// Copyright (C) 2007 Trustees of Indiana University

// Authors: Douglas Gregor
//          Andrew Lumsdaine

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/mpi/exception.hpp>
#include <boost/mpi/error_string.hpp>

namespace boost { namespace mpi {

exception::exception(const char* routine, int result_code)
  : routine_(routine), result_code_(result_code)
{
  message.append(routine_);
  message.append(": ");
  message.append(error_string(result_code));
}

exception::~exception() throw() { }

#ifndef BOOST_MPI_SEQ
int exception::error_class() const
{ 
  int result;
  MPI_Error_class(result_code_, &result);
  return result;
}
#else // BOOST_MPI_SEQ
int exception::error_class() const
{ 
  // This approximation should do in sequential mode.
  return result_code_;
}
#endif // BOOST_MPI_SEQ
} } // end namespace boost::mpi
