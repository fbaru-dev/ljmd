#include "LJSimulation.hpp"

LJSimulation :: LJSimulation()
{
  std::cout << "Initialize MD simulation of a Lennard Jones liquid" << std::endl;
  set_npart(27); 
  set_density(0.5); 
  set_tstep(0.001); 
  set_rcut(1.e20);
  set_Tinit(1.0);
  set_sfreq(100);
  set_nsteps(10);
}

void LJSimulation :: preset()
{ 
  real_type scale_length;
  real_type L;
  //computed  
  set_n3(2);
  L = pow( (get_npart()/get_density()) ,0.3333333);
  set_sideLength( L );
  // The particles are assigned in a cubic lattice
  // According to the number of particles, we find the lowest
  // perfect cube, greater than or equal to the number of particles
  int n3 = get_n3();
  while ((n3*n3*n3)<get_npart()) n3++;
  set_n3(n3);
}

void LJSimulation :: init()  
{
  preset();
}

void LJSimulation :: set_number_of_particles(int N)  
{
  set_npart(N);
  preset();
}

void LJSimulation :: set_number_of_steps(int N)  
{
  set_nsteps(N);
}

void LJSimulation :: init_positions()  
{
  int pos_x = 0;
  int pos_y = 0;
  int pos_z = 0;    
  
  Vec3D<real_type> pos; 
  real_type L = get_sideLength();
  real_type x,y,z;
  int n3 = get_n3();
  // Assign the particles in a cubic lattice
  for(int i=0; i<get_npart(); ++i)
  {
    x = (real_type)(pos_x) + 0.5;
    y = (real_type)(pos_y) + 0.5;
    z = (real_type)(pos_z) + 0.5;
    
    pos.setItem(0,x*L/n3);
    pos.setItem(1,y*L/n3);
    pos.setItem(2,z*L/n3);

    particles[i].setPos(pos);
    pos_x++;
    if(pos_x==n3)
    {
      pos_x=0;
      pos_y++;
      if(pos_y==n3)
      {
	pos_y=0;
	pos_z++;
      }
    }
  }
  
}

void LJSimulation :: init_velocities()  
{
  Vec3D<real_type> vel; 
  Vec3D<real_type> cmv;		//center of mass
  real_type k_energy;		//kinetic energy
  
  std::random_device rd;	//random number generator
  std::mt19937 gen(42);      
  std::exponential_distribution<real_type> exp_d(1);
  
  int N = get_npart();
  for(int i=0; i<N; ++i)
  {
    vel.setItem(0,exp_d(gen));
    vel.setItem(1,exp_d(gen));
    vel.setItem(2,exp_d(gen));
    
    vel.setItem(0,0.1);
    vel.setItem(1,0.2);
    vel.setItem(2,0.3);
  
    particles[i].setVel(vel);   
  }

  //Take away any center of mass drift and compute initial kinetic energy
  for(int i=0; i<N; ++i)
  {
    cmv += particles[i].getVel();
  }
  k_energy = 0;
  for(int i=0; i<N; ++i)
  {
    particles[i].vel() -= (cmv/N);
    k_energy += (particles[i].getVel()*particles[i].getVel());
  }
  k_energy *= 0.5;
  if (get_Tinit()>0.0)
  {
    real_type temp = 2.0/3.0 * k_energy/N;
    real_type fac = sqrt(get_Tinit()/temp);
    k_energy = 0;
    for(int i=0; i<N; ++i)
    {
      particles[i].vel() *= fac;
      k_energy += (particles[i].getVel()*particles[i].getVel());
    }
    k_energy *= 0.5;
  }
 
  _kenergy = k_energy;
  real_type _penergy = calculate_forces();
  _ikenergy = _kenergy + _penergy;
  
// Examples of random number generators    
//     std::map<int, int> hist1,hist2;
//     for(int n=0; n<10000; ++n) {
//         ++hist1[2*exp_d(gen)];
//     }
//     for(auto p : hist1) {
//         std::cout << std::fixed << std::setprecision(1) 
//                   << p.first/2.0 << '-' << (p.first+1)/2.0 <<
//                 ' ' << std::string(p.second/200, '*') << '\n';
//     }
    
//     std::random_device rd;	
//     std::mt19937 gen(rd());      
//     std::normal_distribution<> nd(5,2);
//  
//     for(int n=0; n<10000; ++n) {
//         ++hist2[std::round(nd(gen))];
//     }
//     for(auto p : hist2) {
//         std::cout << std::fixed << std::setprecision(1) << std::setw(2)
//                   << p.first << ' ' << std::string(p.second/200, '*') << '\n';
//     }
  
}

void LJSimulation :: start() 
{
  //allocate particles
  particles = new Particle[get_npart()];
  bc = new Vec3D<int>[get_npart()];
  
  init_positions();	
  init_velocities();
  init_forces();
  print_header();
  
  real_type dt = get_tstep(); 
  real_type dt2 = dt*dt;
  real_type L = get_sideLength();
  
  print_xyz(99);
  
  for (int s=0; s<get_nsteps(); ++s)
  {
    // First integration half step
    for(int i=0; i<get_npart() ; ++i)
    {
      particles[i].pos() += particles[i].vel()*dt + particles[i].f()*0.5*dt2;
      particles[i].vel() += particles[i].f()*0.5*dt;
      
      //apply periodic boundary conditions
      if (particles[i].pos().at(0) < 0.0) { particles[i].pos().at(0) += L; bc[i].at(0)--; }
      if (particles[i].pos().at(0) > L  ) { particles[i].pos().at(0) -= L; bc[i].at(0)++; }
      
      if (particles[i].pos().at(1) < 0.0) { particles[i].pos().at(1) += L; bc[i].at(1)--; }
      if (particles[i].pos().at(1) > L  ) { particles[i].pos().at(1) -= L; bc[i].at(1)++; }
      
      if (particles[i].pos().at(2) < 0.0) { particles[i].pos().at(2) += L; bc[i].at(2)--; }
      if (particles[i].pos().at(2) > L  ) { particles[i].pos().at(2) -= L; bc[i].at(2)++; }
    }
   _penergy = calculate_forces();
   
    // Second integration half step
   real_type k_energy=0;
   for(int i=0; i<get_npart(); ++i)
   {
     particles[i].vel() += particles[i].f()*0.5*dt;
     k_energy += (particles[i].getVel()*particles[i].getVel());
   }
   _kenergy = k_energy * 0.5;
   _tenergy = _kenergy + _penergy;

   print_out(s);
   if(!(s%get_sfreq())) print_xyz(s);
      
  }
  
}

real_type LJSimulation :: calculate_forces() 
{
  int n = get_npart();
  real_type L = get_sideLength();
  real_type halfL = L/2.0;
  real_type energy = 0;
  real_type cutoff2 = get_rcut()*get_rcut();
  Vec3D<real_type> dist;
  
  _virial = 0;
  for(int i=0; i<n; ++i) { particles[i].setF(0.0); }
  
  //A simple N^2 algorithm to compute the forces and the potential energy
  //of the full particle system
  for(int i=0; i<n-1; ++i)
  {
    for(int j=i+1; j<n; ++j)
    {
      dist = particles[i].getPos() - particles[j].getPos();
      
      //the minimum image convention is used for applying the
      //boundary conditions to the system
      if(dist.at(0) > halfL) 		dist.at(0) -=L;
      else if(dist.at(0) < -halfL)	dist.at(0) +=L;
      
      if(dist.at(1) > halfL)		dist.at(1) -=L;
      else if(dist.at(1) < -halfL)	dist.at(1) +=L;
      
      if(dist.at(2) > halfL)		dist.at(2) -=L;
      else if(dist.at(2) < -halfL)	dist.at(2) +=L;
      
      //compute the distance square
      real_type dist2 = dist.sqr();
      if(dist2<cutoff2)
      {
	energy += LJpot.compute_energy(dist2);
	real_type ffactor = LJpot.compute_force(dist2);
	
	particles[i].f() += dist * ffactor / dist2;
	particles[j].f() -= dist * ffactor / dist2;
	
	_virial +=  ffactor;

      }
    }
  }
  return energy;
}

void LJSimulation :: print_header()
{
  std::cout << "L = " << get_sideLength() << "; " 
	    << "rho = " << get_density()  << "; "
	    << "N = " << get_npart() << "; "
	    << "rc = " << get_rcut() << std::endl;
	    
  std::cout << "nSteps = " << get_nsteps() << "; " 
	    << "dt = " << get_tstep()  << std::endl;
	    
  std::cout <<  std::left << std::setw(8)  << "#"
	    <<  std::left << std::setw(8)  << "step"
	    <<  std::left << std::setw(12) << "PE"
	    <<  std::left << std::setw(12) << "KE"
	    <<  std::left << std::setw(15) << "TE"
	    <<  std::left << std::setw(15) << "drift"
	    <<  std::left << std::setw(12) << "T"
	    <<  std::left << std::setw(12) << "P"
	    <<  std::endl;
}

void LJSimulation :: print_out(int step)
{
  std::cout <<  std::left << std::setw(8)  << step
	    <<  std::left << std::setprecision(5) << std::setw(8)  << step*get_tstep()
	    <<  std::left << std::setprecision(8) << std::setw(12) << _penergy
	    <<  std::left << std::setprecision(8) << std::setw(12) << _kenergy
	    <<  std::left << std::setprecision(8) << std::setw(15) << _tenergy
	    <<  std::left << std::setprecision(8) << std::setw(15) << (_tenergy - _ikenergy )/ _ikenergy
	    <<  std::left << std::setprecision(8) << std::setw(12) << 2./3.*_kenergy/get_npart() 
	    <<  std::left << std::setprecision(8) << std::setw(12) <<
	        2./3.*_kenergy*get_density()/get_npart()+
	        _virial/3.0/(get_npart()/get_density())
	    <<  std::endl;
}

void LJSimulation :: print_xyz(int step)
{
  FILE * out;
  char * wrt_code_str = "w";
  char * init_cfg_file = NULL;
  real_type L = get_sideLength();
  char fn[20];
  
  sprintf(fn,"%i.xyz",!strcmp(wrt_code_str,"a")?0:step);
  out=fopen(fn,wrt_code_str);
  
  int i;
  int z=16;
  fprintf(out,"%i\n\n",get_npart());
   /* Writes the coordinates in XYZ format to the output stream fp.
   The integer "z" is the atomic number of the particles, required
   for the XYZ format. The array ix contains the number of x-dir 
   periodic boundary crossings a particle has performed; thus,
   the "unfolded" coordinate is rx[i]+ix[i]*L. */
  for (i=0;i<get_npart();i++) {
    fprintf(out,"%i %.8lf %.8lf %.8lf ",z,
	    particles[i].pos().at(0)+bc[i].at(0)*L,
	    particles[i].pos().at(1)+bc[i].at(1)*L,
	    particles[i].pos().at(2)+bc[i].at(2)*L);
    
    fprintf(out,"%.8lf %.8lf %.8lf",
	    particles[i].vel().at(0),
	    particles[i].vel().at(1),
	    particles[i].vel().at(2));
    fprintf(out,"\n");
  }
}

LJSimulation :: ~LJSimulation()
{
  delete particles;
  delete bc;
}