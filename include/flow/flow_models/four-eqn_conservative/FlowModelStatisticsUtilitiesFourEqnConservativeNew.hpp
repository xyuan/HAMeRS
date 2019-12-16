#ifndef FLOW_MODEL_STATISTICS_UTILITIES_FOUR_EQN_CONSERVATIVE_HPP
#define FLOW_MODEL_STATISTICS_UTILITIES_FOUR_EQN_CONSERVATIVE_HPP

#include "flow/flow_models/FlowModelStatisticsUtilities.hpp"
#include "util/mixing_rules/equations_of_bulk_viscosity/EquationOfBulkViscosityMixingRulesManager.hpp"
#include "util/mixing_rules/equations_of_mass_diffusivity/EquationOfMassDiffusivityMixingRulesManager.hpp"
#include "util/mixing_rules/equations_of_shear_viscosity/EquationOfShearViscosityMixingRulesManager.hpp"
#include "util/mixing_rules/equations_of_state/EquationOfStateMixingRulesManager.hpp"
#include "util/mixing_rules/equations_of_thermal_conductivity/EquationOfThermalConductivityMixingRulesManager.hpp"

class FlowModelStatisticsUtilitiesFourEqnConservative: public FlowModelStatisticsUtilities
{
    public:
        FlowModelStatisticsUtilitiesFourEqnConservative(
            const std::string& object_name,
            const tbox::Dimension& dim,
            const boost::shared_ptr<geom::CartesianGridGeometry>& grid_geometry,
            const int& num_species,
            const boost::shared_ptr<tbox::Database>& flow_model_db,
            const boost::shared_ptr<EquationOfStateMixingRules> equation_of_state_mixing_rules,
            const boost::shared_ptr<EquationOfMassDiffusivityMixingRules> equation_of_mass_diffusivity_mixing_rules,
            const boost::shared_ptr<EquationOfShearViscosityMixingRules> equation_of_shear_viscosity_mixing_rules,
            const boost::shared_ptr<EquationOfBulkViscosityMixingRules> equation_of_bulk_viscosity_mixing_rules,
            const boost::shared_ptr<EquationOfThermalConductivityMixingRules> equation_of_thermal_conductivity_mixing_rules):
                FlowModelStatisticsUtilities(
                    object_name,
                    dim,
                    grid_geometry,
                    num_species,
                    flow_model_db),
                d_equation_of_state_mixing_rules(equation_of_state_mixing_rules),
                d_equation_of_mass_diffusivity_mixing_rules(equation_of_mass_diffusivity_mixing_rules),
                d_equation_of_shear_viscosity_mixing_rules(equation_of_shear_viscosity_mixing_rules),
                d_equation_of_bulk_viscosity_mixing_rules(equation_of_bulk_viscosity_mixing_rules),
                d_equation_of_thermal_conductivity_mixing_rules(equation_of_thermal_conductivity_mixing_rules)
        {}
        
        /*
         * Output names of statistical quantities to output to a file.
         */
        void
        outputStatisticalQuantitiesNames(
            const std::string& stat_dump_filename);
        
        /*
         * Output statisitcal quantities to a file.
         */
        void
        outputStatisticalQuantities(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
    private:
        /*
         * Output averaged density with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedDensityWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output averaged mass fraction (first species) with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedMassFractionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output averaged mole fraction (first species) with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedMoleFractionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
         
        /*
         * Output averaged specific volume with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedSpecificVolumeWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
         
        /*
         * Output turbulent mass flux in x-direction with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedTurbMassFluxXWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output turbulent mass flux in y-direction with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedTurbMassFluxYWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output turbulent mass flux in z-direction with inhomogeneous x-direction to a file.
         */
        void
        outputAveragedTurbMassFluxZWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output Reynolds normal stress in x-direction with inhomogeneous x-direction to a file.
         */
        void
        outputReynoldsNormalStressInXDirectionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output Reynolds normal stress in y-direction with inhomogeneous x-direction to a file.
         */
        void
        outputReynoldsNormalStressInYDirectionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output Reynolds normal stress in z-direction with inhomogeneous x-direction to a file.
         */
        void
        outputReynoldsNormalStressInZDirectionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output Reynolds shear stress in xy-direction with inhomogeneous x-direction to a file.
         */
        void
        outputReynoldsShearStressInXYDirectionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output Reynolds shear stress in xz-direction with inhomogeneous x-direction to a file.
         */
        void
        outputReynoldsShearStressInXZDirectionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output Reynolds shear stress in yz-direction with inhomogeneous x-direction to a file.
         */
        void
        outputReynoldsShearStressInYZDirectionWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output variance of velocity component in x-direction with inhomogeneous x-direction to a file.
         */
        void
        outputVelocityComponentInXDirectionVarianceWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output variance of velocity component in y-direction with inhomogeneous x-direction to a file.
         */
        void
        outputVelocityComponentInYDirectionVarianceWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output variance of velocity component in z-direction with inhomogeneous x-direction to a file.
         */
        void
        outputVelocityComponentInZDirectionVarianceWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output correlation of density and velocity component square in x-direction with inhomogeneous x-direction to a file.
         */
        void
        outputDensityVelocityComponentSquareInXDirectionCorrelationWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output correlation of density and velocity component square in y-direction with inhomogeneous x-direction to a file.
         */
        void
        outputDensityVelocityComponentSquareInYDirectionCorrelationWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output correlation of density and velocity component square in z-direction with inhomogeneous x-direction to a file.
         */
        void
        outputDensityVelocityComponentSquareInZDirectionCorrelationWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        
        
        /*
         * Output density variance with inhomogeneous x-direction to a file.
         */
        void
        outputDensityVarianceWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        /*
         * Output density specific volume covariance with inhomogeneous x-direction to a file.
         */
        void
        outputDensitySpecificVolumeCovarianceWithInhomogeneousXDirection(
            const std::string& stat_dump_filename,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context,
            const double output_time);
        
        
        
        /*
         * Get number of points in the x-direction of the refined domain.
         */
        const int
        getRefinedDomainNumberOfPointsX(
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy) const;
        
        /*
         * Compute averaged value with only x direction as inhomogeneous direction.
         */
        std::vector<double> getAveragedQuantityWithInhomogeneousXDirection(
            const std::string quantity_name,
            const int component_idx,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context);
        
        /*
         * Compute averaged reciprocal of value with only x direction as inhomogeneous direction.
         */
        std::vector<double> getAveragedReciprocalOfQuantityWithInhomogeneousXDirection(
            const std::string quantity_name,
            const int component_idx,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context);
        
        /*
         * Compute averaged value with only x direction as inhomogeneous direction.
         */
        std::vector<double> getAveragedQuantityWithInhomogeneousXDirection(
            const std::vector<std::string>& quantity_names,
            const std::vector<int>& component_indices,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context);
        
        /*
         * Compute correlation with only x direction as inhomogeneous direction.
         */
        std::vector<double> getQuantityCorrelationWithInhomogeneousXDirection(
            const std::vector<std::string>& quantity_names,
            const std::vector<int>& component_indices,
            const std::vector<std::vector<double> >& averaged_quantities,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context);
        
        /*
         * Compute correlation with only x direction as inhomogeneous direction.
         */
        std::vector<double> getQuantityCorrelationWithInhomogeneousXDirection(
            const std::vector<std::string>& quantity_names,
            const std::vector<int>& component_indices,
            const std::vector<bool>& use_reciprocal,
            const std::vector<std::vector<double> >& averaged_quantities,
            const boost::shared_ptr<hier::PatchHierarchy>& patch_hierarchy,
            const boost::shared_ptr<hier::VariableContext>& data_context);
        
        /*
         * boost::shared_ptr to EquationOfStateMixingRules.
         */
        const boost::shared_ptr<EquationOfStateMixingRules>
            d_equation_of_state_mixing_rules;
        
        /*
         * boost::shared_ptr to EquationOfMassDiffusivityMixingRules.
         */
        const boost::shared_ptr<EquationOfMassDiffusivityMixingRules>
            d_equation_of_mass_diffusivity_mixing_rules;
        
        /*
         * boost::shared_ptr to EquationOfShearViscosityMixingRules.
         */
        const boost::shared_ptr<EquationOfShearViscosityMixingRules>
            d_equation_of_shear_viscosity_mixing_rules;
        
        /*
         * boost::shared_ptr to EquationOfBulkViscosityMixingRules.
         */
        const boost::shared_ptr<EquationOfBulkViscosityMixingRules>
            d_equation_of_bulk_viscosity_mixing_rules;
        
        /*
         * boost::shared_ptr to EquationOfThermalConductivityMixingRules.
         */
        const boost::shared_ptr<EquationOfThermalConductivityMixingRules>
            d_equation_of_thermal_conductivity_mixing_rules;
        
};

#endif /* FLOW_MODEL_STATISTICS_UTILITIES_FOUR_EQN_CONSERVATIVE_HPP */
