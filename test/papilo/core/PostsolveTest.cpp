/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*               This file is part of the program and library                */
/*    PaPILO --- Parallel Presolve for Integer and Linear Optimization       */
/*                                                                           */
/* Copyright (C) 2020  Konrad-Zuse-Zentrum                                   */
/*                     fuer Informationstechnik Berlin                       */
/*                                                                           */
/* This program is free software: you can redistribute it and/or modify      */
/* it under the terms of the GNU Lesser General Public License as published  */
/* by the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>.    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "papilo/core/Postsolve.hpp"
#include "catch/catch.hpp"
#include <boost/archive/binary_iarchive.hpp>


TEST_CASE( "finding-the-right-value-in-postsolve-for-a-column-fixed-neg-inf",
           "[core]" )
{

   papilo::Postsolve<double> postsolve{};

   std::ifstream inArchiveFile( "./resources/dual_fix_neg_inf.postsolve",
                                std::ios_base::binary );
   boost::archive::binary_iarchive inputArchive( inArchiveFile );
   inputArchive >> postsolve;
   inArchiveFile.close();
   papilo::Solution<double> reduced_solution{};
   papilo::Solution<double> original_solution{};

   REQUIRE( postsolve.undo( reduced_solution, original_solution ) ==
            papilo::PostsolveStatus::kOk );
   papilo::Vec<double> values = original_solution.primal;
   papilo::Vec<double> expected_values{ -11, -5, -5 };
   REQUIRE( values == expected_values );
}

TEST_CASE( "finding-the-right-value-in-postsolve-for-a-column-fixed-pos-inf",
           "[core]" )
{

   papilo::Postsolve<double> postsolve{};

   std::ifstream inArchiveFile( "./resources/dual_fix_pos_inf.postsolve",
                                std::ios_base::binary );
   boost::archive::binary_iarchive inputArchive( inArchiveFile );
   inputArchive >> postsolve;
   inArchiveFile.close();
   papilo::Solution<double> reduced_solution{};
   papilo::Solution<double> original_solution{};

   REQUIRE( postsolve.undo( reduced_solution, original_solution ) ==
            papilo::PostsolveStatus::kOk );
   papilo::Vec<double> values = original_solution.primal;
   papilo::Vec<double> expected_values{ 13, 9, -5, -2.5 };
   REQUIRE( values == expected_values );

}