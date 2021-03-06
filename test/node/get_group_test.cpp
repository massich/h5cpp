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
// Created on: Nov 22, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include "../fixture.hpp"

using namespace hdf5;

class GetGroupTest : public BasicFixture
{

};

TEST_F(GetGroupTest, test_with_default_node)
{
  EXPECT_THROW(node::get_group(node::Node(),"/data"),std::runtime_error);
}

TEST_F(GetGroupTest, test_with_dataset)
{
  node::Dataset dset(root_,"data",datatype::create<int>());
  EXPECT_THROW(node::get_group(root_,"/data"),std::runtime_error);
}

TEST_F(GetGroupTest, test_with_non_existing_child)
{
  EXPECT_THROW(node::get_group(root_,"/run_01"),std::runtime_error);
  EXPECT_THROW(node::get_group(root_,"run_01"),std::runtime_error);
}

TEST_F(GetGroupTest, test_with_direct_child)
{
  node::Group(root_,"run_001");
  node::Group(root_,"/run_002");

  EXPECT_EQ(node::get_group(root_,"/run_001").link().path().name(),"run_001");
  EXPECT_EQ(node::get_group(root_,"run_002").link().path().name(),"run_002");
}

TEST_F(GetGroupTest,test_with_indirect_child)
{
  node::Group run(root_,"run_0001");
  node::Group(run,"instrument");

  EXPECT_EQ(node::get_group(root_,"run_0001/instrument").link().path(),"/run_0001/instrument");
  EXPECT_EQ(node::get_group(root_,"/run_0001/instrument").link().path(),"/run_0001/instrument");
}
