/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER of SAMRAI distribution.
 *
 * Copyright:     (c) 1997-2014 Lawrence Livermore National Security, LLC
 * Description:   Utility routines for manipulating Cartesian 2d boundary data
 *
 ************************************************************************/

#ifndef CARTESIAN_BOUNDARY_CONDITIONS_HPP
#define CARTESIAN_BOUNDARY_CONDITIONS_HPP

#include <iostream>
#include <map>

/*
 * Definitions for boundary types in 1d, 2d, and 3d:
 */

//@{
//! @name Definitions for boundary types in 1d, 2d, and 3d:
namespace BDRY
{
   enum TYPE
   {
      UNDEFINED = -1,
      
      FACE3D = 1,
      EDGE3D = 2,
      NODE3D = 3,
      
      EDGE2D = 1,
      NODE2D = 2,
      
      NODE1D = 1
   };
}
//@}


/*
 * Definitions for boundary array sizes in 1d, 2d, or 3d:
 */

//@{
//! @name Definitions for boundary array sizes in 1d, 2d, or 3d:
const int NUM_1D_NODES = 2;

const int NUM_2D_EDGES = 4;
const int NUM_2D_NODES = 4;

const int NUM_3D_FACES = 6;
const int NUM_3D_EDGES = 12;
const int NUM_3D_NODES = 8;
//@}


/*
 * Definitions for Face, Edge, and Node boundary locations:
 *
 * Note that these definitions are used only for:
 * - Node boundary locations in 1d (XLO, XHI only), or
 * - Edge boundary locations in 2d (XLO, XHI, YLO, YHI only), or
 * - Face boundary locations in 3d (XLO, XHI, YLO, YHI, ZLO and ZHI).
 */

//@{
//! @name Definitions for Face, Edge, and Node boundary locations (see source code for more information):
namespace BDRY_LOC
{
   enum TYPE
   {
      XLO = 0,
      XHI = 1,
      YLO = 2,
      YHI = 3,
      ZLO = 4,
      ZHI = 5
   };
}
//@}


/*
 * Definitions for Node boundary locations in 2d:
 */

//@{
//! @name Definitions for Node boundary locations in 2d:
namespace NODE_BDRY_LOC_2D
{
   enum TYPE
   {
      XLO_YLO = 0,
      XHI_YLO = 1,
      XLO_YHI = 2,
      XHI_YHI = 3
   };
}
//@}


/*
 * Definitions for Edge boundary locations in 3d:
 */

//@{
//! @name Definitions for Edge boundary locations in 3d:
namespace EDGE_BDRY_LOC_3D
{
   enum TYPE
   {
      XLO_YLO = 0,
      XHI_YLO = 1,
      XLO_YHI = 2,
      XHI_YHI = 3,
      XLO_ZLO = 4,
      XHI_ZLO = 5,
      XLO_ZHI = 6,
      XHI_ZHI = 7,
      YLO_ZLO = 8,
      YHI_ZLO = 9,
      YLO_ZHI = 10,
      YHI_ZHI = 11
   };
}
//@}


/*
 * Definitions for Node boundary locations in 3d:
 */

//@{
//! @name Definitions for Node boundary locations in 3d:
namespace NODE_BDRY_LOC_3D
{
   enum TYPE
   {
      XLO_YLO_ZLO = 0,
      XHI_YLO_ZLO = 1,
      XLO_YHI_ZLO = 2,
      XHI_YHI_ZLO = 3,
      XLO_YLO_ZHI = 4,
      XHI_YLO_ZHI = 5,
      XLO_YHI_ZHI = 6,
      XHI_YHI_ZHI = 7
   };
}
//@}


/*
 * Function to print out enum NODE_BDRY_LOC_2D::TYPE value as text.
 */
inline std::ostream& operator<<(std::ostream& os, const NODE_BDRY_LOC_2D::TYPE& value)
{
    static std::map<NODE_BDRY_LOC_2D::TYPE, std::string> strings;
    
    if (strings.size() == 0)
    {
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(NODE_BDRY_LOC_2D::XLO_YLO);
        INSERT_ELEMENT(NODE_BDRY_LOC_2D::XHI_YLO);
        INSERT_ELEMENT(NODE_BDRY_LOC_2D::XLO_YHI);
        INSERT_ELEMENT(NODE_BDRY_LOC_2D::XHI_YHI);
#undef INSERT_ELEMENT
    }
    
    return os << strings[value];
}


/*
 * Function to print out enum EDGE_BDRY_LOC_3D::TYPE value as text.
 */
inline std::ostream& operator<<(std::ostream& output, const EDGE_BDRY_LOC_3D::TYPE value)
{
    static std::map<EDGE_BDRY_LOC_3D::TYPE, std::string> strings;
    
    if (strings.size() == 0)
    {
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XLO_YLO);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XHI_YLO);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XLO_YHI);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XHI_YHI);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XLO_ZLO);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XHI_ZLO);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XLO_ZHI);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::XHI_ZHI);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::YLO_ZLO);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::YHI_ZLO);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::YLO_ZHI);
        INSERT_ELEMENT(EDGE_BDRY_LOC_3D::YHI_ZHI);
#undef INSERT_ELEMENT
    }
    
    return output << strings[value];
}


/*
 * Function to print out enum NODE_BDRY_LOC_3D::TYPE value as text.
 */
inline std::ostream& operator<<(std::ostream& output, const NODE_BDRY_LOC_3D::TYPE value)
{
    static std::map<NODE_BDRY_LOC_3D::TYPE, std::string> strings;
    
    if (strings.size() == 0)
    {
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XLO_YLO_ZLO);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XHI_YLO_ZLO);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XLO_YHI_ZLO);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XHI_YHI_ZLO);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XLO_YLO_ZHI);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XHI_YLO_ZHI);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XLO_YHI_ZHI);
        INSERT_ELEMENT(NODE_BDRY_LOC_3D::XHI_YHI_ZHI);
#undef INSERT_ELEMENT
    }
    
    return output << strings[value];
}

#endif /* CARTESIAN_BOUNDARY_CONDITIONS_HPP */
