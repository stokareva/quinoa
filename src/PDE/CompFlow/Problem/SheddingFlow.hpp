// *****************************************************************************
/*!
  \file      src/PDE/CompFlow/Problem/SheddingFlow.hpp
  \copyright 2012-2015 J. Bakosi,
             2016-2018 Los Alamos National Security, LLC.,
             2019-2021 Triad National Security, LLC.
             All rights reserved. See the LICENSE file for details.
  \brief     Problem configuration for shedding flow over triangular wedge
  \details   This file defines a policy class for the compressible flow
    equations, defined in PDE/CompFlow/CompFlow.h. See PDE/CompFlow/Problem.h
    for general requirements on Problem policy classes for CompFlow.
*/
// *****************************************************************************
#ifndef CompFlowProblemSheddingFlow_h
#define CompFlowProblemSheddingFlow_h

#include <string>
#include <unordered_set>

#include "Types.hpp"
#include "Fields.hpp"
#include "FunctionPrototypes.hpp"
#include "Inciter/Options/Problem.hpp"
#include "Inciter/InputDeck/InputDeck.hpp"
#include "EoS/EOS.hpp"

namespace inciter {

//! CompFlow system of PDEs problem: Shedding flow
class CompFlowProblemSheddingFlow {

  protected:
    using ncomp_t = tk::ncomp_t;
    using eq = tag::compflow;

  public:
    //! Initialize numerical solution
    static tk::InitializeFn::result_type
    initialize( ncomp_t, const std::vector< EOS >&,
                tk::real x, tk::real, tk::real, tk::real );

    //! Evaluate analytical solution at (x,y,z,t) for all components
    static tk::InitializeFn::result_type
    analyticSolution( ncomp_t, const std::vector< EOS >&,
                      tk::real, tk::real, tk::real, tk::real ) { return {}; }

    //! Compute and return source term for this problem
    //! \param[in,out] sv Source term vector
    //! \note The function signature must follow tk::SrcFn
    static tk::SrcFn::result_type
    src( ncomp_t, const std::vector< EOS >&, tk::real, tk::real,
         tk::real, tk::real, std::vector< tk::real >& sv )
    {
      Assert(sv.size() == 5, "Incorrect source vector size");
      sv[0] = sv[1] = sv[2] = sv[3] = sv[4] = 0.0;
    }

    //! \brief Query all side set IDs the user has configured for all components
    //!   in this PDE system
    void side( std::unordered_set< int >& conf ) const;

    //! Return analytic field names to be output to file
    std::vector< std::string > analyticFieldNames( ncomp_t ) const { return {}; }

    //! Return names of integral variables to be output to diagnostics file
    std::vector< std::string > names( ncomp_t ) const;

    //! Return problem type
    static ctr::ProblemType type() noexcept
    { return ctr::ProblemType::SHEDDING_FLOW; }
};

} // inciter::

#endif // CompFlowProblemSheddingFlow_h
