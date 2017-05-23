#ifndef CELL_CORNERS_VARIABLE_FILL_PATTERN
#define CELL_CORNERS_VARIABLE_FILL_PATTERN

#include "HAMeRS_config.hpp"

#include "SAMRAI/hier/BoxGeometry.h"
#include "SAMRAI/hier/BoxOverlap.h"
#include "SAMRAI/xfer/VariableFillPattern.h"

#include "boost/shared_ptr.hpp"

/*!
 * @brief Class CellCornersVariableFillPattern is a concrete implementation of the abstract base
 * class VariableFillPattern.
 *
 * It is used to calculate overlaps according to a pattern which limits the overlaps to the corner
 * cell-centered ghost regions surrounding a patch.
 */

class CellCornersVariableFillPattern:
    public SAMRAI::xfer::VariableFillPattern
{
    public:
        /*!
         * @brief Constructor
         *
         * @param[in] dim          Dimension
         * @param[in] layer_width  Width of layer
         */
        explicit CellCornersVariableFillPattern(
            const SAMRAI::tbox::Dimension& dim,
            const SAMRAI::hier::IntVector& layer_width);
        
        /*!
         * @brief Destructor
         */
        virtual ~CellCornersVariableFillPattern();
        
        /*!
         * @brief Calculate overlap between the destination and source geometries representing the
         * fill pattern.
         *
         * This will return the portion of the intersection of the geometries that lies in the corner
         * ghost regions.  The patch is identified by the argument dst_patch_box.
         *
         * @param[in] dst_geometry        geometry object for destination box
         * @param[in] src_geometry        geometry object for source box
         * @param[in] dst_patch_box       box for the destination patch
         * @param[in] src_mask            the source mask, the box resulting from transforming the
         *                                source box
         * @param[in] fill_box            the box to be filled
         * @param[in] overwrite_interior  controls whether or not to include the destination box
         *                                interior in the overlap.  This has no effect in this
         *                                implementation, since all calculated overlaps will be on
         *                                the destination box exterior.
         * @param[in] transformation      the transformation from source to destination index space.
         *
         * @return                        boost::shared_ptr to the calculated overlap object
         *
         * @pre dst_patch_box.getDim() == src_mask.getDim()
         */
        boost::shared_ptr<SAMRAI::hier::BoxOverlap>
        calculateOverlap(
           const SAMRAI::hier::BoxGeometry& dst_geometry,
           const SAMRAI::hier::BoxGeometry& src_geometry,
           const SAMRAI::hier::Box& dst_patch_box,
           const SAMRAI::hier::Box& src_mask,
           const SAMRAI::hier::Box& fill_box,
           const bool overwrite_interior,
           const SAMRAI::hier::Transformation& transformation) const;
        
        /*!
         * @brief Computes a BoxOverlap object which defines the space to be filled by a refinement
         * operation.
         *
         * For this implementation, that space is the intersection between fill_boxes (computed by
         * the RefineSchedule), data_box, which specifies the extent of the destination data, and
         * the ghost region that defines the stencil of this fill pattern.
         *
         * @param[in] fill_boxes       list representing the all of the space on a patch or its ghost
         *                             region that may be filled by a refine operator (cell-centered
         *                             represtentation)
         * @param[in] node_fill_boxes  node-centered represenation of fill_boxes
         * @param[in] patch_box        box representing the patch where a refine operator will fill
         *                             data. (cell-centered representation)
         * @param[in] data_box         box representing the full extent of the region covered by a
         *                             patch data object, including all ghosts (cell-centered
         *                             representation)
         * @param[in] pdf              patch data factory for the data that is to be filled
         */
        boost::shared_ptr<SAMRAI::hier::BoxOverlap>
        computeFillBoxesOverlap(
           const SAMRAI::hier::BoxContainer& fill_boxes,
           const SAMRAI::hier::BoxContainer& node_fill_boxes,
           const SAMRAI::hier::Box& patch_box,
           const SAMRAI::hier::Box& data_box,
           const SAMRAI::hier::PatchDataFactory& pdf) const;
        
        /*!
         * @brief Returns the stencil width in all directions.
         */
        const SAMRAI::hier::IntVector&
        getStencilWidth();
        
        /*!
         * @brief Returns a string name identifier
         * "FIRST_LAYER_CELL_NO_CORNERS_FILL_PATTERN".
         */
        const std::string&
        getPatternName() const;
        
    private:
        /*!
         * @brief Computes a BoxContainer defining the stencil around a given box for this fill
         * pattern
         *
         * The computed BoxContainer will cover corner ghost regions of d_layer_width around dst_box.
         *
         * @param[out] stencil_boxes   The computed stencil BoxContainer.
         * @param[in]  dst_box         Input box around which stencil is computed.
         *
         * @pre stencil_boxes.size() == 0
         */
        void
        computeStencilBoxes(
            SAMRAI::hier::BoxContainer& stencil_boxes,
            const SAMRAI::hier::Box& dst_box) const;
        
        /*!
         * @brief The dimension of this object.
         */
        const SAMRAI::tbox::Dimension d_dim;
        
        /*!
         * @brief Number of ghost cells in the layer.
         */
        const SAMRAI::hier::IntVector d_layer_width;
        
        /*!
         * @brief Static string holding name identifier for this class.
         */
        static const std::string s_name_id;
        
};

#endif /* CELL_CORNERS_VARIABLE_FILL_PATTERN */
