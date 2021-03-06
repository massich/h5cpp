
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
// Created on: Oct 6, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/compound.hpp>
#include <h5cpp/datatype/float.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <cstdint>
#include <complex>
#include <vector>
#include "../fixture.hpp"

using namespace hdf5;
using namespace hdf5::datatype;

struct complex_struct
{
  double real;
  double imag;

};

class Pixel {
 public:
  Pixel() {}
  Pixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
      : red_(red)
      , green_(green)
      , blue_(blue)
  {}

  std::uint8_t red_ {0};
  std::uint8_t green_ {0};
  std::uint8_t blue_ {0};
};

namespace hdf5 {
namespace datatype {

template<typename BT>
struct complex_t
{
    BT real;
    BT imag;
};

template<typename T>
class TypeTrait<std::complex<T>>
{
  private:
    using complex_type = complex_t<T>;
  public:
    using TypeClass = Compound;

    static TypeClass create()
    {

      datatype::Compound type(sizeof(complex_struct));
      type.insert("real",HOFFSET(complex_type,real),datatype::create<T>());
      type.insert("imag",HOFFSET(complex_type,imag),datatype::create<T>());

      return type;
    }
};


template<>
class TypeTrait<Pixel>
{
 public:
  using TypeClass = Compound;

  static TypeClass create()
  {

    datatype::Compound type(sizeof(Pixel));
    type.insert("red",0,datatype::create<std::uint8_t>());
    type.insert("green",1,datatype::create<std::uint8_t>());
    type.insert("blue",2,datatype::create<std::uint8_t>());

    return type;
  }
};


}
}

class CompoundType : public BasicFixture
{
};


TEST_F(CompoundType, test_default_construction)
{
  datatype::Compound type;
  EXPECT_FALSE(type.is_valid());
  //EXPECT_THROW(type.field_index("real"),std::runtime_error);
  //EXPECT_THROW(type.field_index(0),std::runtime_error);

}

TEST_F(CompoundType, test_complex_number)
{
  Compound type(sizeof(complex_struct));
  EXPECT_NO_THROW(type.insert("real",HOFFSET(complex_struct,real),datatype::create<double>()));
  EXPECT_NO_THROW(type.insert("imag",HOFFSET(complex_struct,imag),datatype::create<double>()));
  EXPECT_TRUE(type.has_class(datatype::Class::FLOAT));
  EXPECT_FALSE(type.has_class(datatype::Class::INTEGER));

}

TEST_F(CompoundType, test_complex_number_io)
{
  std::complex<double> write_value(1.,3.);
  std::complex<double> read_value(0.,0.);
  attribute::Attribute a = root_.attributes.create<std::complex<double>>("hello");
  a.write(write_value);
  a.read(read_value);
  EXPECT_NEAR(write_value.real(),read_value.real(),0.0001);
  EXPECT_NEAR(write_value.imag(),read_value.imag(),0.0001);

}

TEST_F(CompoundType, test_pixel_type)
{
  Pixel write_pixel(1,2,3);
  Pixel read_pixel(0,0,0);

  auto type = datatype::create<Pixel>();
  attribute::Attribute a = root_.attributes.create<Pixel>("pixel");
  a.write(write_pixel);
  a.read(read_pixel);

  EXPECT_EQ(write_pixel.red_,read_pixel.red_);
  EXPECT_EQ(write_pixel.green_,read_pixel.green_);
  EXPECT_EQ(write_pixel.blue_,read_pixel.blue_);
  EXPECT_TRUE(type.has_class(datatype::Class::INTEGER));
  EXPECT_FALSE(type.has_class(datatype::Class::FLOAT));
}





