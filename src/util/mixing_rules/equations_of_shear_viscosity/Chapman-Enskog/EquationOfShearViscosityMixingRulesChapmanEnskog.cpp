#include "util/mixing_rules/equations_of_shear_viscosity/Chapman-Enskog/EquationOfShearViscosityMixingRulesChapmanEnskog.hpp"

EquationOfShearViscosityMixingRulesChapmanEnskog::EquationOfShearViscosityMixingRulesChapmanEnskog(
    const std::string& object_name,
    const tbox::Dimension& dim,
    const int& num_species,
    const MIXING_CLOSURE_MODEL::TYPE& mixing_closure_model,
    const boost::shared_ptr<tbox::Database>& equation_of_shear_viscosity_mixing_rules_db):
        EquationOfShearViscosityMixingRules(
            object_name,
            dim,
            num_species,
            mixing_closure_model,
            equation_of_shear_viscosity_mixing_rules_db)
{
    d_equation_of_shear_viscosity.reset(new EquationOfShearViscosityChapmanEnskog(
        "d_equation_of_shear_viscosity",
        dim));
    
    /*
     * Get the Lennard-Jones energy parameter of each species from the database.
     */
    
    if (equation_of_shear_viscosity_mixing_rules_db->keyExists("species_epsilon_by_k"))
    {
        size_t species_epsilon_by_k_array_size =
            equation_of_shear_viscosity_mixing_rules_db->getArraySize("species_epsilon_by_k");
        if (static_cast<int>(species_epsilon_by_k_array_size) == d_num_species)
        {
            d_species_epsilon_by_k =
                equation_of_shear_viscosity_mixing_rules_db->getDoubleVector("species_epsilon_by_k");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'species_epsilon_by_k' entries must be equal to 'num_species'."
                << std::endl);
        }
    }
    else if (equation_of_shear_viscosity_mixing_rules_db->keyExists("d_species_epsilon_by_k"))
    {
        size_t species_epsilon_by_k_array_size =
            equation_of_shear_viscosity_mixing_rules_db->getArraySize("d_species_epsilon_by_k");
        if (static_cast<int>(species_epsilon_by_k_array_size) == d_num_species)
        {
            d_species_epsilon_by_k =
                equation_of_shear_viscosity_mixing_rules_db->getDoubleVector("d_species_epsilon_by_k");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'd_species_epsilon_by_k' entries must be equal to 'd_num_species'."
                << std::endl);
        }
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Key data 'species_epsilon_by_k'/'d_species_epsilon_by_k'"
            << "not found in data for equation of shear viscosity mixing rules."
            << std::endl);
    }
    
    /*
     * Get the collision diameter of each species from the database.
     */
    
    if (equation_of_shear_viscosity_mixing_rules_db->keyExists("species_sigma"))
    {
        size_t species_sigma_array_size =
            equation_of_shear_viscosity_mixing_rules_db->getArraySize("species_sigma");
        if (static_cast<int>(species_sigma_array_size) == d_num_species)
        {
            d_species_sigma =
                equation_of_shear_viscosity_mixing_rules_db->getDoubleVector("species_sigma");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'species_sigma' entries must be equal to 'num_species'."
                << std::endl);
        }
    }
    else if (equation_of_shear_viscosity_mixing_rules_db->keyExists("d_species_sigma"))
    {
        size_t species_sigma_array_size =
            equation_of_shear_viscosity_mixing_rules_db->getArraySize("d_species_sigma");
        if (static_cast<int>(species_sigma_array_size) == d_num_species)
        {
            d_species_sigma =
                equation_of_shear_viscosity_mixing_rules_db->getDoubleVector("d_species_sigma");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'd_species_sigma' entries must be equal to 'num_species'."
                << std::endl);
        }
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Key data 'species_sigma'/'d_species_sigma'"
            << "not found in data for equation of shear viscosity mixing rules."
            << std::endl);
    }
    
    /*
     * Get the molecular weight of each species from the database.
     */
    
    if (equation_of_shear_viscosity_mixing_rules_db->keyExists("species_M"))
    {
        size_t species_M_array_size =
            equation_of_shear_viscosity_mixing_rules_db->getArraySize("species_M");
        if (static_cast<int>(species_M_array_size) == d_num_species)
        {
            d_species_M =
                equation_of_shear_viscosity_mixing_rules_db->getDoubleVector("species_M");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'species_M' entries must be equal to 'num_species'."
                << std::endl);
        }
    }
    else if (equation_of_shear_viscosity_mixing_rules_db->keyExists("d_species_M"))
    {
        size_t species_M_array_size =
            equation_of_shear_viscosity_mixing_rules_db->getArraySize("d_species_M");
        if (static_cast<int>(species_M_array_size) == d_num_species)
        {
            d_species_M =
                equation_of_shear_viscosity_mixing_rules_db->getDoubleVector("d_species_M");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'd_species_M' entries must be equal to 'num_species'."
                << std::endl);
        }
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Key data 'species_M'/'d_species_M'"
            << "not found in data for equation of shear viscosity mixing rules."
            << std::endl);
    }
}


/*
 * Print all characteristics of the equation of shear viscosity class.
 */
void
EquationOfShearViscosityMixingRulesChapmanEnskog::printClassData(
    std::ostream& os) const
{
    os << "\nPrint EquationOfShearViscosityMixingRulesChapmanEnskog object..."
       << std::endl;
    
    os << std::endl;
    os << "EquationOfShearViscosityMixingRulesChapmanEnskog: this = "
       << (EquationOfShearViscosityMixingRulesChapmanEnskog *)this
       << std::endl;
    
    os << "d_object_name = "
       << d_object_name
       << std::endl;
    
    os << "d_mixing_closure_model = "
       << d_mixing_closure_model
       << std::endl;
    
    /*
     * Print the Lennard-Jones energy parameter of each species.
     */
    
    os << "d_species_epsilon_by_k = ";
    for (int si = 0; si < d_num_species - 1; si++)
    {
        os << d_species_epsilon_by_k[si] << ", ";
    }
    os << d_species_epsilon_by_k[d_num_species - 1];
    os << std::endl;
    
    /*
     * Print the collision diameter of each species.
     */
    
    os << "d_species_sigma = ";
    for (int si = 0; si < d_num_species - 1; si++)
    {
        os << d_species_sigma[si] << ", ";
    }
    os << d_species_sigma[d_num_species - 1];
    os << std::endl;
    
    /*
     * Print the molecular weight of each species.
     */
    
    os << "d_species_M = ";
    for (int si = 0; si < d_num_species - 1; si++)
    {
        os << d_species_M[si] << ", ";
    }
    os << d_species_M[d_num_species - 1];
    os << std::endl;
}


/*
 * Put the characteristics of the equation of shear viscosity mixing rules class into the restart
 * database.
 */
void
EquationOfShearViscosityMixingRulesChapmanEnskog::putToRestart(
    const boost::shared_ptr<tbox::Database>& restart_db) const
{
    restart_db->putDoubleVector("d_species_epsilon_by_k", d_species_epsilon_by_k);
    restart_db->putDoubleVector("d_species_sigma", d_species_sigma);
    restart_db->putDoubleVector("d_species_M", d_species_M);
}


/*
 * Compute the shear viscosity of the mixture with isothermal and isobaric equilibria assumptions.
 */
double
EquationOfShearViscosityMixingRulesChapmanEnskog::getShearViscosity(
    const double* const pressure,
    const double* const temperature,
    const std::vector<const double*>& mass_fractions) const
{
#ifdef HAMERS_DEBUG_CHECK_DEV_ASSERTIONS
    TBOX_ASSERT((d_mixing_closure_model == MIXING_CLOSURE_MODEL::ISOTHERMAL_AND_ISOBARIC) ||
                (d_mixing_closure_model == MIXING_CLOSURE_MODEL::NO_MODEL && d_num_species == 1));
    TBOX_ASSERT((static_cast<int>(mass_fractions.size()) == d_num_species) ||
                (static_cast<int>(mass_fractions.size()) == d_num_species - 1));
#endif
    
    double mu = double(0);
    
    double num = double(0);
    double den = double(0);
    
    /*
     * Initialize the container and pointers to the container for the molecular properties
     * of a species.
     */
    
    std::vector<double> species_molecular_properties;
    std::vector<double*> species_molecular_properties_ptr;
    std::vector<const double*> species_molecular_properties_const_ptr;
    
    const int num_molecular_properties = getNumberOfSpeciesMolecularProperties();
    
    species_molecular_properties.resize(num_molecular_properties);
    species_molecular_properties_ptr.reserve(num_molecular_properties);
    species_molecular_properties_const_ptr.reserve(num_molecular_properties);
    
    for (int mi = 0; mi < num_molecular_properties; mi++)
    {
        species_molecular_properties_ptr.push_back(&species_molecular_properties[mi]);
        species_molecular_properties_const_ptr.push_back(&species_molecular_properties[mi]);
    }
    
    if (static_cast<int>(mass_fractions.size()) == d_num_species)
    {
        for (int si = 0; si < d_num_species; si++)
        {
            getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
            
            const double mu_i = d_equation_of_shear_viscosity->
                getShearViscosity(
                    pressure,
                    temperature,
                    species_molecular_properties_const_ptr);
            
            const double weight = *(mass_fractions[si])/(sqrt(species_molecular_properties[2]));
            
            num += mu_i*weight;
            den += weight;
        }
    }
    else if (static_cast<int>(mass_fractions.size()) == d_num_species - 1)
    {
        double Y_last = double(1);
        
        for (int si = 0; si < d_num_species - 1; si++)
        {
            getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
            
            const double mu_i = d_equation_of_shear_viscosity->
                getShearViscosity(
                    pressure,
                    temperature,
                    species_molecular_properties_const_ptr);
            
            const double weight = *(mass_fractions[si])/(sqrt(species_molecular_properties[2]));
            
            num += mu_i*weight;
            den += weight;
            
            // Compute the mass fraction of the last species.
            Y_last -= *(mass_fractions[si]);
        }
        
        /*
         * Add the contribution from the last species.
         */
        
        getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
        const double mu_last = d_equation_of_shear_viscosity->
            getShearViscosity(
                pressure,
                temperature,
                species_molecular_properties_const_ptr);
        
        const double weight = Y_last/(sqrt(species_molecular_properties[2]));
        
        num += mu_last*weight;
        den += weight;
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Number of mass fractions provided is not"
            << " equal to the total number of species or (total number of species - 1)."
            << std::endl);
    }
    
    mu = num/den;
    
    return mu;
}


/*
 * Compute the shear viscosity of the mixture with isothermal and isobaric equilibria assumptions.
 */
void
EquationOfShearViscosityMixingRulesChapmanEnskog::computeShearViscosity(
    boost::shared_ptr<pdat::CellData<double> >& data_shear_viscosity,
    const boost::shared_ptr<pdat::CellData<double> >& data_pressure,
    const boost::shared_ptr<pdat::CellData<double> >& data_temperature,
    const boost::shared_ptr<pdat::CellData<double> >& data_mass_fractions,
    const hier::Box& domain) const
{
#ifdef HAMERS_DEBUG_CHECK_ASSERTIONS
    TBOX_ASSERT((d_mixing_closure_model == MIXING_CLOSURE_MODEL::ISOTHERMAL_AND_ISOBARIC) ||
                (d_mixing_closure_model == MIXING_CLOSURE_MODEL::NO_MODEL && d_num_species == 1));
    
    TBOX_ASSERT(data_shear_viscosity);
    TBOX_ASSERT(data_pressure);
    TBOX_ASSERT(data_temperature);
    TBOX_ASSERT(data_mass_fractions);
    
    TBOX_ASSERT((data_mass_fractions->getDepth() == d_num_species) ||
                (data_mass_fractions->getDepth() == d_num_species - 1));
#endif
    
    // Get the dimensions of box that covers the interior of patch.
    const hier::Box interior_box = data_shear_viscosity->getBox();
    const hier::IntVector interior_dims = interior_box.numberCells();
    
#ifdef HAMERS_DEBUG_CHECK_ASSERTIONS
    TBOX_ASSERT(data_pressure->getBox().numberCells() == interior_dims);
    TBOX_ASSERT(data_temperature->getBox().numberCells() == interior_dims);
    TBOX_ASSERT(data_mass_fractions->getBox().numberCells() == interior_dims);
#endif
    
    /*
     * Get the numbers of ghost cells and the dimensions of the ghost cell boxes.
     */
    
    const hier::IntVector num_ghosts_shear_viscosity = data_shear_viscosity->getGhostCellWidth();
    const hier::IntVector ghostcell_dims_shear_viscosity =
        data_shear_viscosity->getGhostBox().numberCells();
    
    const hier::IntVector num_ghosts_pressure = data_pressure->getGhostCellWidth();
    const hier::IntVector num_ghosts_temperature = data_temperature->getGhostCellWidth();
    
    const hier::IntVector num_ghosts_mass_fractions = data_mass_fractions->getGhostCellWidth();
    const hier::IntVector ghostcell_dims_mass_fractions =
        data_mass_fractions->getGhostBox().numberCells();
    
    /*
     * Get the minimum number of ghost cells and the dimensions of the ghost cell box for denominator
     * and numerator.
     */
    
    hier::IntVector num_ghosts_min(d_dim);
    
    num_ghosts_min = num_ghosts_shear_viscosity;
    num_ghosts_min = hier::IntVector::min(num_ghosts_pressure, num_ghosts_min);
    num_ghosts_min = hier::IntVector::min(num_ghosts_temperature, num_ghosts_min);
    num_ghosts_min = hier::IntVector::min(num_ghosts_mass_fractions, num_ghosts_min);
    
    const hier::IntVector ghostcell_dims_min = interior_dims + num_ghosts_min*2;
    
    /*
     * Get the local lower indices and number of cells in each direction of the domain.
     */
    
    hier::IntVector domain_lo(d_dim);
    hier::IntVector domain_dims(d_dim);
    
    if (domain.empty())
    {
        hier::Box ghost_box = interior_box;
        ghost_box.grow(num_ghosts_min);
        
        domain_lo = -num_ghosts_min;
        domain_dims = ghost_box.numberCells();
    }
    else
    {
#ifdef HAMERS_DEBUG_CHECK_DEV_ASSERTIONS
        TBOX_ASSERT(data_shear_viscosity->getGhostBox().contains(domain));
        TBOX_ASSERT(data_pressure->getGhostBox().contains(domain));
        TBOX_ASSERT(data_temperature->getGhostBox().contains(domain));
        TBOX_ASSERT(data_mass_fractions->getGhostBox().contains(domain));
#endif
        
        domain_lo = domain.lower() - interior_box.lower();
        domain_dims = domain.numberCells();
    }
    
    /*
     * Delcare data containers for shear viscosity of a species, denominator, numerator and species
     * molecular properties.
     */
    
    boost::shared_ptr<pdat::CellData<double> > data_shear_viscosity_species(
        new pdat::CellData<double>(interior_box, 1, num_ghosts_min));
    
    boost::shared_ptr<pdat::CellData<double> > data_den(
        new pdat::CellData<double>(interior_box, 1, num_ghosts_min));
    
    boost::shared_ptr<pdat::CellData<double> > data_num(
        new pdat::CellData<double>(interior_box, 1, num_ghosts_min));
    
    std::vector<double> species_molecular_properties;
    std::vector<double*> species_molecular_properties_ptr;
    std::vector<const double*> species_molecular_properties_const_ptr;
    
    const int num_molecular_properties = getNumberOfSpeciesMolecularProperties();
    
    species_molecular_properties.resize(num_molecular_properties);
    species_molecular_properties_ptr.reserve(num_molecular_properties);
    species_molecular_properties_const_ptr.reserve(num_molecular_properties);
    
    for (int mi = 0; mi < num_molecular_properties; mi++)
    {
        species_molecular_properties_ptr.push_back(&species_molecular_properties[mi]);
        species_molecular_properties_const_ptr.push_back(&species_molecular_properties[mi]);
    }
    
    /*
     * Get the pointers to the cell data of mixture shear viscosity, species shear viscosity, denominator
     * and numerator.
     */
    
    double* mu = data_shear_viscosity->getPointer(0);
    double* mu_i = data_shear_viscosity_species->getPointer(0);
    double* den = data_den->getPointer(0);
    double* num = data_num->getPointer(0);
    
    /*
     * Fill zeros for denominator and numerator.
     */
    
    if (domain.empty())
    {
        data_den->fillAll(double(0));
        data_num->fillAll(double(0));
    }
    else
    {
        data_den->fillAll(double(0), domain);
        data_num->fillAll(double(0), domain);
    }
    
    if (data_mass_fractions->getDepth() == d_num_species)
    {
        /*
         * Get the pointers to the cell data of mass fractions.
         */
        
        std::vector<double*> Y;
        Y.reserve(d_num_species);
        for (int si = 0; si < d_num_species; si++)
        {
            Y.push_back(data_mass_fractions->getPointer(si));
        }
        
        if (d_dim == tbox::Dimension(1))
        {
            /*
             * Get the local lower index, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_dim_0 = domain_dims[0];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_0_mass_fractions = num_ghosts_mass_fractions[0];
            
            // Compute the mixture shear viscosity field.
            for (int si = 0; si < d_num_species; si++)
            {
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature,
                        species_molecular_properties_const_ptr,
                        domain);
                
                const double factor = double(1)/(sqrt(species_molecular_properties[2]));
                
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_min = i + num_ghosts_0_min;
                    const int idx_mass_fractions = i + num_ghosts_0_mass_fractions;
                    
                    const double weight = Y[si][idx_mass_fractions]*factor;
                    
                    num[idx_min] += mu_i[idx_min]*weight;
                    den[idx_min] += weight;
                }
            }
            
#ifdef HAMERS_ENABLE_SIMD
            #pragma omp simd
#endif
            for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
            {
                // Compute the linear indices.
                const int idx_shear_viscosity = i + num_ghosts_0_shear_viscosity;
                const int idx_min = i + num_ghosts_0_min;
                
                mu[idx_shear_viscosity] = num[idx_min]/den[idx_min];
            }
        }
        else if (d_dim == tbox::Dimension(2))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            
            const int num_ghosts_0_mass_fractions = num_ghosts_mass_fractions[0];
            const int num_ghosts_1_mass_fractions = num_ghosts_mass_fractions[1];
            const int ghostcell_dim_0_mass_fractions = ghostcell_dims_mass_fractions[0];
            
            // Compute the mixture shear viscosity field.
            for (int si = 0; si < d_num_species; si++)
            {
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature,
                        species_molecular_properties_const_ptr,
                        domain);
                
                const double factor = double(1)/(sqrt(species_molecular_properties[2]));
                
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                        
                        const int idx_mass_fractions = (i + num_ghosts_0_mass_fractions) +
                            (j + num_ghosts_1_mass_fractions)*ghostcell_dim_0_mass_fractions;
                        
                        const double weight = Y[si][idx_mass_fractions]*factor;
                        
                        num[idx_min] += mu_i[idx_min]*weight;
                        den[idx_min] += weight;
                    }
                }
            }
            
            for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
            {
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                        (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity;
                    
                    const int idx_min = (i + num_ghosts_0_min) +
                        (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                    
                    mu[idx_shear_viscosity] = num[idx_min]/den[idx_min];
                }
            }
        }
        else if (d_dim == tbox::Dimension(3))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_lo_2 = domain_lo[2];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            const int domain_dim_2 = domain_dims[2];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int num_ghosts_2_shear_viscosity = num_ghosts_shear_viscosity[2];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            const int ghostcell_dim_1_shear_viscosity = ghostcell_dims_shear_viscosity[1];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int num_ghosts_2_min = num_ghosts_min[2];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            const int ghostcell_dim_1_min = ghostcell_dims_min[1];
            
            const int num_ghosts_0_mass_fractions = num_ghosts_mass_fractions[0];
            const int num_ghosts_1_mass_fractions = num_ghosts_mass_fractions[1];
            const int num_ghosts_2_mass_fractions = num_ghosts_mass_fractions[2];
            const int ghostcell_dim_0_mass_fractions = ghostcell_dims_mass_fractions[0];
            const int ghostcell_dim_1_mass_fractions = ghostcell_dims_mass_fractions[1];
            
            // Compute the mixture shear viscosity field.
            for (int si = 0; si < d_num_species; si++)
            {
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature,
                        species_molecular_properties_const_ptr,
                        domain);
                
                const double factor = double(1)/(sqrt(species_molecular_properties[2]));
                
                for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
                {
                    for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                    {
#ifdef HAMERS_ENABLE_SIMD
                        #pragma omp simd
#endif
                        for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                        {
                            // Compute the linear indices.
                            const int idx_min = (i + num_ghosts_0_min) +
                                (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                                (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                    ghostcell_dim_1_min;
                            
                            const int idx_mass_fractions = (i + num_ghosts_0_mass_fractions) +
                                (j + num_ghosts_1_mass_fractions)*ghostcell_dim_0_mass_fractions +
                                (k + num_ghosts_2_mass_fractions)*ghostcell_dim_0_mass_fractions*
                                    ghostcell_dim_1_mass_fractions;
                            
                            const double weight = Y[si][idx_mass_fractions]*factor;
                            
                            num[idx_min] += mu_i[idx_min]*weight;
                            den[idx_min] += weight;
                        }
                    }
                }
            }
            
            for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
            {
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                            (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity +
                            (k + num_ghosts_2_shear_viscosity)*ghostcell_dim_0_shear_viscosity*
                                ghostcell_dim_1_shear_viscosity;
                        
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                            (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                ghostcell_dim_1_min;
                        
                        mu[idx_shear_viscosity] = num[idx_min]/den[idx_min];
                    }
                }
            }
        }
    }
    else if (data_mass_fractions->getDepth() == d_num_species - 1)
    {
        boost::shared_ptr<pdat::CellData<double> > data_mass_fractions_last(
            new pdat::CellData<double>(interior_box, 1, num_ghosts_mass_fractions));
        
        if (domain.empty())
        {
            data_mass_fractions_last->fillAll(double(1));
        }
        else
        {
            data_mass_fractions_last->fillAll(double(1), domain);
        }
        
        /*
         * Get the pointers to the cell data of mass fractions.
         */
        
        std::vector<double*> Y;
        Y.reserve(d_num_species - 1);
        for (int si = 0; si < d_num_species - 1; si++)
        {
            Y.push_back(data_mass_fractions->getPointer(si));
        }
        
        double* Y_last = data_mass_fractions_last->getPointer(0);
        
        if (d_dim == tbox::Dimension(1))
        {
            /*
             * Get the local lower index, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_dim_0 = domain_dims[0];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_0_mass_fractions = num_ghosts_mass_fractions[0];
            
            // Compute the mixture shear viscosity field.
            for (int si = 0; si < d_num_species - 1; si++)
            {
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature,
                        species_molecular_properties_const_ptr,
                        domain);
                
                const double factor = double(1)/(sqrt(species_molecular_properties[2]));
                
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_min = i + num_ghosts_0_min;
                    const int idx_mass_fractions = i + num_ghosts_0_mass_fractions;
                    
                    const double weight = Y[si][idx_mass_fractions]*factor;
                    
                    num[idx_min] += mu_i[idx_min]*weight;
                    den[idx_min] += weight;
                    
                    // Compute the mass fraction of the last species.
                    Y_last[idx_mass_fractions] -= Y[si][idx_mass_fractions];
                }
            }
            
            getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
            d_equation_of_shear_viscosity->
                computeShearViscosity(
                    data_shear_viscosity_species,
                    data_pressure,
                    data_temperature,
                    species_molecular_properties_const_ptr,
                    domain);
            
            const double factor = double(1)/(sqrt(species_molecular_properties[2]));
            
#ifdef HAMERS_ENABLE_SIMD
            #pragma omp simd
#endif
            for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
            {
                // Compute the linear indices.
                const int idx_shear_viscosity = i + num_ghosts_0_shear_viscosity;
                const int idx_min = i + num_ghosts_0_min;
                const int idx_mass_fractions = i + num_ghosts_0_mass_fractions;
                
                const double weight = Y_last[idx_mass_fractions]*factor;
                
                num[idx_min] += mu_i[idx_min]*weight;
                den[idx_min] += weight;
                
                mu[idx_shear_viscosity] = num[idx_min]/den[idx_min];
            }
        }
        else if (d_dim == tbox::Dimension(2))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            
            const int num_ghosts_0_mass_fractions = num_ghosts_mass_fractions[0];
            const int num_ghosts_1_mass_fractions = num_ghosts_mass_fractions[1];
            const int ghostcell_dim_0_mass_fractions = ghostcell_dims_mass_fractions[0];
            
            // Compute the mixture shear viscosity field.
            for (int si = 0; si < d_num_species - 1; si++)
            {
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature,
                        species_molecular_properties_const_ptr,
                        domain);
                
                const double factor = double(1)/(sqrt(species_molecular_properties[2]));
                
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                        
                        const int idx_mass_fractions = (i + num_ghosts_0_mass_fractions) +
                            (j + num_ghosts_1_mass_fractions)*ghostcell_dim_0_mass_fractions;
                        
                        const double weight = Y[si][idx_mass_fractions]*factor;
                        
                        num[idx_min] += mu_i[idx_min]*weight;
                        den[idx_min] += weight;
                        
                        // Compute the mass fraction of the last species.
                        Y_last[idx_mass_fractions] -= Y[si][idx_mass_fractions];
                    }
                }
            }
            
            getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
            d_equation_of_shear_viscosity->
                computeShearViscosity(
                    data_shear_viscosity_species,
                    data_pressure,
                    data_temperature,
                    species_molecular_properties_const_ptr,
                    domain);
            
            const double factor = double(1)/(sqrt(species_molecular_properties[2]));
            
            for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
            {
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                        (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity;
                    
                    const int idx_min = (i + num_ghosts_0_min) +
                        (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                    
                    const int idx_mass_fractions = (i + num_ghosts_0_mass_fractions) +
                        (j + num_ghosts_1_mass_fractions)*ghostcell_dim_0_mass_fractions;
                    
                    const double weight = Y_last[idx_mass_fractions]*factor;
                    
                    num[idx_min] += mu_i[idx_min]*weight;
                    den[idx_min] += weight;
                    
                    mu[idx_shear_viscosity] = num[idx_min]/den[idx_min];
                }
            }
        }
        else if (d_dim == tbox::Dimension(3))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_lo_2 = domain_lo[2];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            const int domain_dim_2 = domain_dims[2];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int num_ghosts_2_shear_viscosity = num_ghosts_shear_viscosity[2];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            const int ghostcell_dim_1_shear_viscosity = ghostcell_dims_shear_viscosity[1];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int num_ghosts_2_min = num_ghosts_min[2];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            const int ghostcell_dim_1_min = ghostcell_dims_min[1];
            
            const int num_ghosts_0_mass_fractions = num_ghosts_mass_fractions[0];
            const int num_ghosts_1_mass_fractions = num_ghosts_mass_fractions[1];
            const int num_ghosts_2_mass_fractions = num_ghosts_mass_fractions[2];
            const int ghostcell_dim_0_mass_fractions = ghostcell_dims_mass_fractions[0];
            const int ghostcell_dim_1_mass_fractions = ghostcell_dims_mass_fractions[1];
            
            // Compute the mixture shear viscosity field.
            for (int si = 0; si < d_num_species - 1; si++)
            {
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature,
                        species_molecular_properties_const_ptr,
                        domain);
                
                const double factor = double(1)/(sqrt(species_molecular_properties[2]));
                
                for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
                {
                    for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                    {
#ifdef HAMERS_ENABLE_SIMD
                        #pragma omp simd
#endif
                        for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                        {
                            // Compute the linear indices.
                            const int idx_min = (i + num_ghosts_0_min) +
                                (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                                (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                    ghostcell_dim_1_min;
                            
                            const int idx_mass_fractions = (i + num_ghosts_0_mass_fractions) +
                                (j + num_ghosts_1_mass_fractions)*ghostcell_dim_0_mass_fractions +
                                (k + num_ghosts_2_mass_fractions)*ghostcell_dim_0_mass_fractions*
                                    ghostcell_dim_1_mass_fractions;
                            
                            const double weight = Y[si][idx_mass_fractions]*factor;
                            
                            num[idx_min] += mu_i[idx_min]*weight;
                            den[idx_min] += weight;
                            
                            // Compute the mass fraction of the last species.
                            Y_last[idx_mass_fractions] -= Y[si][idx_mass_fractions];
                        }
                    }
                }
            }
            
            getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
            d_equation_of_shear_viscosity->
                computeShearViscosity(
                    data_shear_viscosity_species,
                    data_pressure,
                    data_temperature,
                    species_molecular_properties_const_ptr,
                    domain);
            
            const double factor = double(1)/(sqrt(species_molecular_properties[2]));
            
            for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
            {
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                            (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity +
                            (k + num_ghosts_2_shear_viscosity)*ghostcell_dim_0_shear_viscosity*
                                ghostcell_dim_1_shear_viscosity;
                        
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                            (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                ghostcell_dim_1_min;
                        
                        const int idx_mass_fractions = (i + num_ghosts_0_mass_fractions) +
                            (j + num_ghosts_1_mass_fractions)*ghostcell_dim_0_mass_fractions +
                            (k + num_ghosts_2_mass_fractions)*ghostcell_dim_0_mass_fractions*
                                ghostcell_dim_1_mass_fractions;
                        
                        const double weight = Y_last[idx_mass_fractions]*factor;
                        
                        num[idx_min] += mu_i[idx_min]*weight;
                        den[idx_min] += weight;
                        
                        mu[idx_shear_viscosity] = num[idx_min]/den[idx_min];
                    }
                }
            }
        }
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Number of components in the data of mass fractions provided is not"
            << " equal to the total number of species or (total number of species - 1)."
            << std::endl);
    }
}


/*
 * Compute the shear viscosity of the mixture with isobaric equilibrium assumption.
 */
double
EquationOfShearViscosityMixingRulesChapmanEnskog::getShearViscosity(
    const double* const pressure,
    const std::vector<const double*>& species_temperatures,
    const std::vector<const double*>& mass_fractions,
    const std::vector<const double*>& volume_fractions) const
{   
#ifdef HAMERS_DEBUG_CHECK_DEV_ASSERTIONS
    TBOX_ASSERT(d_mixing_closure_model == MIXING_CLOSURE_MODEL::ISOBARIC);
    TBOX_ASSERT((static_cast<int>(species_temperatures.size()) == d_num_species));
    TBOX_ASSERT((static_cast<int>(volume_fractions.size()) == d_num_species) ||
                (static_cast<int>(volume_fractions.size()) == d_num_species - 1));
#endif
    
    NULL_USE(mass_fractions);
    
    double mu = double(0);
    
    /*
     * Initialize the container and pointers to the container for the molecular properties
     * of a species.
     */
    
    std::vector<double> species_molecular_properties;
    std::vector<double*> species_molecular_properties_ptr;
    std::vector<const double*> species_molecular_properties_const_ptr;
    
    const int num_molecular_properties = getNumberOfSpeciesMolecularProperties();
    
    species_molecular_properties.resize(num_molecular_properties);
    species_molecular_properties_ptr.reserve(num_molecular_properties);
    species_molecular_properties_const_ptr.reserve(num_molecular_properties);
    
    for (int mi = 0; mi < num_molecular_properties; mi++)
    {
        species_molecular_properties_ptr.push_back(&species_molecular_properties[mi]);
        species_molecular_properties_const_ptr.push_back(&species_molecular_properties[mi]);
    }
    
    if (static_cast<int>(volume_fractions.size()) == d_num_species)
    {
        for (int si = 0; si < d_num_species; si++)
        {
            getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
            
            const double mu_i = d_equation_of_shear_viscosity->
                getShearViscosity(
                    pressure,
                    species_temperatures[si],
                    species_molecular_properties_const_ptr);
            
            mu += *(volume_fractions[si])*mu_i;
        }
    }
    else if (static_cast<int>(volume_fractions.size()) == d_num_species - 1)
    {
        double Z_last = double(1);
        
        for (int si = 0; si < d_num_species - 1; si++)
        {
            getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
            
            const double mu_i = d_equation_of_shear_viscosity->
                getShearViscosity(
                    pressure,
                    species_temperatures[si],
                    species_molecular_properties_const_ptr);
            
            mu += *(volume_fractions[si])*mu_i;
            
            // Compute the volume fraction of the last species.
            Z_last -= *(volume_fractions[si]);
        }
        
        /*
         * Add the contribution from the last species.
         */
        
        getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
        const double mu_last = d_equation_of_shear_viscosity->
            getShearViscosity(
                pressure,
                species_temperatures[d_num_species - 1],
                species_molecular_properties_const_ptr);
        
        mu += Z_last*mu_last;
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Number of volume fractions provided is not"
            << " equal to the total number of species or (total number of species - 1)."
            << std::endl);
    }
    
    return mu;
}


/*
 * Compute the shear viscosity of the mixture with isobaric equilibrium assumption.
 */
void
EquationOfShearViscosityMixingRulesChapmanEnskog::computeShearViscosity(
    boost::shared_ptr<pdat::CellData<double> >& data_shear_viscosity,
    const boost::shared_ptr<pdat::CellData<double> >& data_pressure,
    const boost::shared_ptr<pdat::CellData<double> >& data_species_temperatures,
    const boost::shared_ptr<pdat::CellData<double> >& data_mass_fractions,
    const boost::shared_ptr<pdat::CellData<double> >& data_volume_fractions,
    const hier::Box& domain) const
{
#ifdef HAMERS_DEBUG_CHECK_DEV_ASSERTIONS
    TBOX_ASSERT(d_mixing_closure_model == MIXING_CLOSURE_MODEL::ISOBARIC);
    
    TBOX_ASSERT(data_shear_viscosity);
    TBOX_ASSERT(data_pressure);
    TBOX_ASSERT(data_species_temperatures);
    TBOX_ASSERT(data_volume_fractions);
    
    TBOX_ASSERT(data_species_temperatures->getDepth() == d_num_species);
    TBOX_ASSERT((data_volume_fractions->getDepth() == d_num_species) ||
                (data_volume_fractions->getDepth() == d_num_species - 1));
#endif
    
    NULL_USE(data_mass_fractions);
    
    // Get the dimensions of box that covers the interior of patch.
    const hier::Box interior_box = data_shear_viscosity->getBox();
    const hier::IntVector interior_dims = interior_box.numberCells();
    
#ifdef HAMERS_DEBUG_CHECK_ASSERTIONS
    TBOX_ASSERT(data_pressure->getBox().numberCells() == interior_dims);
    TBOX_ASSERT(data_species_temperatures->getBox().numberCells() == interior_dims);
    TBOX_ASSERT(data_volume_fractions->getBox().numberCells() == interior_dims);
#endif
    
    /*
     * Get the numbers of ghost cells and the dimensions of the ghost cell boxes.
     */
    
    const hier::IntVector num_ghosts_shear_viscosity = data_shear_viscosity->getGhostCellWidth();
    const hier::IntVector ghostcell_dims_shear_viscosity =
        data_shear_viscosity->getGhostBox().numberCells();
    
    const hier::IntVector num_ghosts_pressure = data_pressure->getGhostCellWidth();
    const hier::IntVector num_ghosts_species_temperatures = data_species_temperatures->getGhostCellWidth();
    
    const hier::IntVector num_ghosts_volume_fractions = data_volume_fractions->getGhostCellWidth();
    const hier::IntVector ghostcell_dims_volume_fractions =
        data_volume_fractions->getGhostBox().numberCells();
    
    /*
     * Get the minimum number of ghost cells and the dimensions of the ghost cell box for denominator
     * and numerator.
     */
    
    hier::IntVector num_ghosts_min(d_dim);
    
    num_ghosts_min = num_ghosts_shear_viscosity;
    num_ghosts_min = hier::IntVector::min(num_ghosts_pressure, num_ghosts_min);
    num_ghosts_min = hier::IntVector::min(num_ghosts_species_temperatures, num_ghosts_min);
    num_ghosts_min = hier::IntVector::min(num_ghosts_volume_fractions, num_ghosts_min);
    
    const hier::IntVector ghostcell_dims_min = interior_dims + num_ghosts_min*2;
    
    /*
     * Get the local lower indices and number of cells in each direction of the domain.
     */
    
    hier::IntVector domain_lo(d_dim);
    hier::IntVector domain_dims(d_dim);
    
    if (domain.empty())
    {
        hier::Box ghost_box = interior_box;
        ghost_box.grow(num_ghosts_min);
        
        domain_lo = -num_ghosts_min;
        domain_dims = ghost_box.numberCells();
    }
    else
    {
#ifdef HAMERS_DEBUG_CHECK_DEV_ASSERTIONS
        TBOX_ASSERT(data_shear_viscosity->getGhostBox().contains(domain));
        TBOX_ASSERT(data_pressure->getGhostBox().contains(domain));
        TBOX_ASSERT(data_species_temperatures->getGhostBox().contains(domain));
        TBOX_ASSERT(data_volume_fractions->getGhostBox().contains(domain));
#endif
        
        domain_lo = domain.lower() - interior_box.lower();
        domain_dims = domain.numberCells();
    }
    
    /*
     * Delcare data containers for shear viscosity and temperature of a species and species molecular
     * properties.
     */
    
    boost::shared_ptr<pdat::CellData<double> > data_shear_viscosity_species(
        new pdat::CellData<double>(interior_box, 1, num_ghosts_min));
    
    boost::shared_ptr<pdat::CellData<double> > data_temperature_species(
        new pdat::CellData<double>(interior_box, 1, num_ghosts_species_temperatures));
    
    std::vector<double> species_molecular_properties;
    std::vector<double*> species_molecular_properties_ptr;
    std::vector<const double*> species_molecular_properties_const_ptr;
    
    const int num_molecular_properties = getNumberOfSpeciesMolecularProperties();
    
    species_molecular_properties.resize(num_molecular_properties);
    species_molecular_properties_ptr.reserve(num_molecular_properties);
    species_molecular_properties_const_ptr.reserve(num_molecular_properties);
    
    for (int mi = 0; mi < num_molecular_properties; mi++)
    {
        species_molecular_properties_ptr.push_back(&species_molecular_properties[mi]);
        species_molecular_properties_const_ptr.push_back(&species_molecular_properties[mi]);
    }
    
    /*
     * Get the pointers to the cell data of mixture shear viscosity, species shear viscosity, denominator
     * and numerator.
     */
    
    double* mu = data_shear_viscosity->getPointer(0);
    double* mu_i = data_shear_viscosity_species->getPointer(0);
    
    /*
     * Fill zeros for mixture shear viscosity.
     */
    
    if (domain.empty())
    {
        data_shear_viscosity->fillAll(double(0));
    }
    else
    {
        data_shear_viscosity->fillAll(double(0), domain);
    }
    
    if (data_volume_fractions->getDepth() == d_num_species)
    {
        /*
         * Get the pointers to the cell data of volume fractions.
         */
        
        std::vector<double*> Z;
        Z.reserve(d_num_species);
        for (int si = 0; si < d_num_species; si++)
        {
            Z.push_back(data_volume_fractions->getPointer(si));
        }
        
        if (d_dim == tbox::Dimension(1))
        {
            /*
             * Get the local lower index, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_dim_0 = domain_dims[0];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_0_volume_fractions = num_ghosts_volume_fractions[0];
            
            for (int si = 0; si < d_num_species; si++)
            {
                data_temperature_species->copyDepth(0, *data_species_temperatures, si);
                
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature_species,
                        species_molecular_properties_const_ptr,
                        domain);
                
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_shear_viscosity = i + num_ghosts_0_shear_viscosity;
                    const int idx_min = i + num_ghosts_0_min;
                    const int idx_volume_fractions = i + num_ghosts_0_volume_fractions;
                    
                    mu[idx_shear_viscosity] += mu_i[idx_min]*Z[si][idx_volume_fractions];
                }
            }
        }
        else if (d_dim == tbox::Dimension(2))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            
            const int num_ghosts_0_volume_fractions = num_ghosts_volume_fractions[0];
            const int num_ghosts_1_volume_fractions = num_ghosts_volume_fractions[1];
            const int ghostcell_dim_0_volume_fractions = ghostcell_dims_volume_fractions[0];
            
            for (int si = 0; si < d_num_species; si++)
            {
                data_temperature_species->copyDepth(0, *data_species_temperatures, si);
                
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature_species,
                        species_molecular_properties_const_ptr,
                        domain);
                
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                            (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity;
                        
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                        
                        const int idx_volume_fractions = (i + num_ghosts_0_volume_fractions) +
                            (j + num_ghosts_1_volume_fractions)*ghostcell_dim_0_volume_fractions;
                        
                        mu[idx_shear_viscosity] += mu_i[idx_min]*Z[si][idx_volume_fractions];
                    }
                }
            }
        }
        else if (d_dim == tbox::Dimension(3))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_lo_2 = domain_lo[2];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            const int domain_dim_2 = domain_dims[2];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int num_ghosts_2_shear_viscosity = num_ghosts_shear_viscosity[2];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            const int ghostcell_dim_1_shear_viscosity = ghostcell_dims_shear_viscosity[1];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int num_ghosts_2_min = num_ghosts_min[2];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            const int ghostcell_dim_1_min = ghostcell_dims_min[1];
            
            const int num_ghosts_0_volume_fractions = num_ghosts_volume_fractions[0];
            const int num_ghosts_1_volume_fractions = num_ghosts_volume_fractions[1];
            const int num_ghosts_2_volume_fractions = num_ghosts_volume_fractions[2];
            const int ghostcell_dim_0_volume_fractions = ghostcell_dims_volume_fractions[0];
            const int ghostcell_dim_1_volume_fractions = ghostcell_dims_volume_fractions[1];
            
            for (int si = 0; si < d_num_species; si++)
            {
                data_temperature_species->copyDepth(0, *data_species_temperatures, si);
                
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature_species,
                        species_molecular_properties_const_ptr,
                        domain);
                
                for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
                {
                    for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                    {
#ifdef HAMERS_ENABLE_SIMD
                        #pragma omp simd
#endif
                        for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                        {
                            // Compute the linear indices.
                            const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                                (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity +
                                (k + num_ghosts_2_shear_viscosity)*ghostcell_dim_0_shear_viscosity*
                                    ghostcell_dim_1_shear_viscosity;
                            
                            const int idx_min = (i + num_ghosts_0_min) +
                                (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                                (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                    ghostcell_dim_1_min;
                            
                            const int idx_volume_fractions = (i + num_ghosts_0_volume_fractions) +
                                (j + num_ghosts_1_volume_fractions)*ghostcell_dim_0_volume_fractions +
                                (k + num_ghosts_2_volume_fractions)*ghostcell_dim_0_volume_fractions*
                                    ghostcell_dim_1_volume_fractions;
                            
                            mu[idx_shear_viscosity] += mu_i[idx_min]*Z[si][idx_volume_fractions];
                        }
                    }
                }
            }
        }
    }
    else if (data_volume_fractions->getDepth() == d_num_species - 1)
    {
        boost::shared_ptr<pdat::CellData<double> > data_volume_fractions_last(
            new pdat::CellData<double>(interior_box, 1, num_ghosts_volume_fractions));
        
        if (domain.empty())
        {
            data_volume_fractions_last->fillAll(double(1));
        }
        else
        {
            data_volume_fractions_last->fillAll(double(1), domain);
        }
        
        /*
         * Get the pointers to the cell data of volume fractions.
         */
        
        std::vector<double*> Z;
        Z.reserve(d_num_species - 1);
        for (int si = 0; si < d_num_species - 1; si++)
        {
            Z.push_back(data_volume_fractions->getPointer(si));
        }
        
        double* Z_last = data_volume_fractions_last->getPointer(0);
        
        if (d_dim == tbox::Dimension(1))
        {
            /*
             * Get the local lower index, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_dim_0 = domain_dims[0];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_0_volume_fractions = num_ghosts_volume_fractions[0];
            
            for (int si = 0; si < d_num_species - 1; si++)
            {
                data_temperature_species->copyDepth(0, *data_species_temperatures, si);
                
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature_species,
                        species_molecular_properties_const_ptr,
                        domain);
                
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_shear_viscosity = i + num_ghosts_0_shear_viscosity;
                    const int idx_min = i + num_ghosts_0_min;
                    const int idx_volume_fractions = i + num_ghosts_0_volume_fractions;
                    
                    mu[idx_shear_viscosity] += mu_i[idx_min]*Z[si][idx_volume_fractions];
                    
                    // Compute the volume fraction of the last species.
                    Z_last[idx_volume_fractions] -= Z[si][idx_volume_fractions];
                }
            }
            
            data_temperature_species->copyDepth(0, *data_species_temperatures, d_num_species - 1);
            
            getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
            d_equation_of_shear_viscosity->
                computeShearViscosity(
                    data_shear_viscosity_species,
                    data_pressure,
                    data_temperature_species,
                    species_molecular_properties_const_ptr,
                    domain);
            
#ifdef HAMERS_ENABLE_SIMD
            #pragma omp simd
#endif
            for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
            {
                // Compute the linear indices.
                const int idx_shear_viscosity = i + num_ghosts_0_shear_viscosity;
                const int idx_min = i + num_ghosts_0_min;
                const int idx_volume_fractions = i + num_ghosts_0_volume_fractions;
                
                mu[idx_shear_viscosity] += mu_i[idx_min]*Z_last[idx_volume_fractions];
            }
        }
        else if (d_dim == tbox::Dimension(2))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            
            const int num_ghosts_0_volume_fractions = num_ghosts_volume_fractions[0];
            const int num_ghosts_1_volume_fractions = num_ghosts_volume_fractions[1];
            const int ghostcell_dim_0_volume_fractions = ghostcell_dims_volume_fractions[0];
            
            for (int si = 0; si < d_num_species - 1; si++)
            {
                data_temperature_species->copyDepth(0, *data_species_temperatures, si);
                
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature_species,
                        species_molecular_properties_const_ptr,
                        domain);
                
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                            (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity;
                        
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                        
                        const int idx_volume_fractions = (i + num_ghosts_0_volume_fractions) +
                            (j + num_ghosts_1_volume_fractions)*ghostcell_dim_0_volume_fractions;
                        
                        mu[idx_shear_viscosity] += mu_i[idx_min]*Z[si][idx_volume_fractions];
                        
                        // Compute the volume fraction of the last species.
                        Z_last[idx_volume_fractions] -= Z[si][idx_volume_fractions];
                    }
                }
            }
            
            data_temperature_species->copyDepth(0, *data_species_temperatures, d_num_species - 1);
            
            getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
            d_equation_of_shear_viscosity->
                computeShearViscosity(
                    data_shear_viscosity_species,
                    data_pressure,
                    data_temperature_species,
                    species_molecular_properties_const_ptr,
                    domain);
            
            for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
            {
#ifdef HAMERS_ENABLE_SIMD
                #pragma omp simd
#endif
                for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                {
                    // Compute the linear indices.
                    const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                        (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity;
                    
                    const int idx_min = (i + num_ghosts_0_min) +
                        (j + num_ghosts_1_min)*ghostcell_dim_0_min;
                    
                    const int idx_volume_fractions = (i + num_ghosts_0_volume_fractions) +
                        (j + num_ghosts_1_volume_fractions)*ghostcell_dim_0_volume_fractions;
                    
                    mu[idx_shear_viscosity] += mu_i[idx_min]*Z_last[idx_volume_fractions];
                }
            }
        }
        else if (d_dim == tbox::Dimension(3))
        {
            /*
             * Get the local lower indices, numbers of cells in each dimension and numbers of ghost cells.
             */
            
            const int domain_lo_0 = domain_lo[0];
            const int domain_lo_1 = domain_lo[1];
            const int domain_lo_2 = domain_lo[2];
            const int domain_dim_0 = domain_dims[0];
            const int domain_dim_1 = domain_dims[1];
            const int domain_dim_2 = domain_dims[2];
            
            const int num_ghosts_0_shear_viscosity = num_ghosts_shear_viscosity[0];
            const int num_ghosts_1_shear_viscosity = num_ghosts_shear_viscosity[1];
            const int num_ghosts_2_shear_viscosity = num_ghosts_shear_viscosity[2];
            const int ghostcell_dim_0_shear_viscosity = ghostcell_dims_shear_viscosity[0];
            const int ghostcell_dim_1_shear_viscosity = ghostcell_dims_shear_viscosity[1];
            
            const int num_ghosts_0_min = num_ghosts_min[0];
            const int num_ghosts_1_min = num_ghosts_min[1];
            const int num_ghosts_2_min = num_ghosts_min[2];
            const int ghostcell_dim_0_min = ghostcell_dims_min[0];
            const int ghostcell_dim_1_min = ghostcell_dims_min[1];
            
            const int num_ghosts_0_volume_fractions = num_ghosts_volume_fractions[0];
            const int num_ghosts_1_volume_fractions = num_ghosts_volume_fractions[1];
            const int num_ghosts_2_volume_fractions = num_ghosts_volume_fractions[2];
            const int ghostcell_dim_0_volume_fractions = ghostcell_dims_volume_fractions[0];
            const int ghostcell_dim_1_volume_fractions = ghostcell_dims_volume_fractions[1];
            
            for (int si = 0; si < d_num_species - 1; si++)
            {
                data_temperature_species->copyDepth(0, *data_species_temperatures, si);
                
                getSpeciesMolecularProperties(species_molecular_properties_ptr, si);
                
                d_equation_of_shear_viscosity->
                    computeShearViscosity(
                        data_shear_viscosity_species,
                        data_pressure,
                        data_temperature_species,
                        species_molecular_properties_const_ptr,
                        domain);
                
                for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
                {
                    for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                    {
#ifdef HAMERS_ENABLE_SIMD
                        #pragma omp simd
#endif
                        for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                        {
                            // Compute the linear indices.
                            const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                                (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity +
                                (k + num_ghosts_2_shear_viscosity)*ghostcell_dim_0_shear_viscosity*
                                    ghostcell_dim_1_shear_viscosity;
                            
                            const int idx_min = (i + num_ghosts_0_min) +
                                (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                                (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                    ghostcell_dim_1_min;
                            
                            const int idx_volume_fractions = (i + num_ghosts_0_volume_fractions) +
                                (j + num_ghosts_1_volume_fractions)*ghostcell_dim_0_volume_fractions +
                                (k + num_ghosts_2_volume_fractions)*ghostcell_dim_0_volume_fractions*
                                    ghostcell_dim_1_volume_fractions;
                            
                            mu[idx_shear_viscosity] += mu_i[idx_min]*Z[si][idx_volume_fractions];
                            
                            // Compute the volume fraction of the last species.
                            Z_last[idx_volume_fractions] -= Z[si][idx_volume_fractions];
                        }
                    }
                }
            }
            
            data_temperature_species->copyDepth(0, *data_species_temperatures, d_num_species - 1);
            
            getSpeciesMolecularProperties(species_molecular_properties_ptr, d_num_species - 1);
            
            d_equation_of_shear_viscosity->
                computeShearViscosity(
                    data_shear_viscosity_species,
                    data_pressure,
                    data_temperature_species,
                    species_molecular_properties_const_ptr,
                    domain);
            
            for (int k = domain_lo_2; k < domain_lo_2 + domain_dim_2; k++)
            {
                for (int j = domain_lo_1; j < domain_lo_1 + domain_dim_1; j++)
                {
#ifdef HAMERS_ENABLE_SIMD
                    #pragma omp simd
#endif
                    for (int i = domain_lo_0; i < domain_lo_0 + domain_dim_0; i++)
                    {
                        // Compute the linear indices.
                        const int idx_shear_viscosity = (i + num_ghosts_0_shear_viscosity) +
                            (j + num_ghosts_1_shear_viscosity)*ghostcell_dim_0_shear_viscosity +
                            (k + num_ghosts_2_shear_viscosity)*ghostcell_dim_0_shear_viscosity*
                                ghostcell_dim_1_shear_viscosity;
                        
                        const int idx_min = (i + num_ghosts_0_min) +
                            (j + num_ghosts_1_min)*ghostcell_dim_0_min +
                            (k + num_ghosts_2_min)*ghostcell_dim_0_min*
                                ghostcell_dim_1_min;
                        
                        const int idx_volume_fractions = (i + num_ghosts_0_volume_fractions) +
                            (j + num_ghosts_1_volume_fractions)*ghostcell_dim_0_volume_fractions +
                            (k + num_ghosts_2_volume_fractions)*ghostcell_dim_0_volume_fractions*
                                ghostcell_dim_1_volume_fractions;
                        
                        mu[idx_shear_viscosity] += mu_i[idx_min]*Z_last[idx_volume_fractions];
                    }
                }
            }
        }
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Number of components in the data of volume fractions provided is not"
            << " equal to the total number of species or (total number of species - 1)."
            << std::endl);
    }
}


/*
 * Get the molecular properties of a species.
 */
void
EquationOfShearViscosityMixingRulesChapmanEnskog::getSpeciesMolecularProperties(
    std::vector<double*>& species_molecular_properties,
    const int species_index) const
{
#ifdef HAMERS_DEBUG_CHECK_DEV_ASSERTIONS
    TBOX_ASSERT(static_cast<int>(species_molecular_properties.size()) >= 3);
    TBOX_ASSERT(species_index >= 0);
    TBOX_ASSERT(species_index < d_num_species);
#endif
    
    *(species_molecular_properties[0]) = d_species_epsilon_by_k[species_index];
    *(species_molecular_properties[1]) = d_species_sigma[species_index];
    *(species_molecular_properties[2]) = d_species_M[species_index];
}
