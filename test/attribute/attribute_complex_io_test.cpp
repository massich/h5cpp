//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Oct 5, 2017
//
#include "../fixture.hpp"
#include <complex>

using namespace hdf5;

namespace hdf5 {
namespace datatype {

template<typename T> class TypeTrait<std::complex<T>>
{
  public:
};

}
}

class AttributeComplexIO : public BasicFixture
{};

TEST_F(AttributeComplexIO, test_complex_scalar)
{

}

TEST_F(AttributeComplexIO, test_complex_vector)
{

}




