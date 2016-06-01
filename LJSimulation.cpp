#include "LJSimulation.hpp"

LJSimulation :: LJSimulation()
{
  std::cout << "Start Simulation!" << std::endl;
}

void LJSimulation :: init()  
{
  init_parameters();
  init_compute();
}

void LJSimulation :: set_number_of_particles(int N)  
{
  set_npart(N);
  
  //allocate particles
  particles = new Particle[get_npart()];
  
  init_positions();	
  init_velocities();
  init_forces();
}

void LJSimulation :: init_parameters()  
{  
//from the simulation input
  if (get_npart() <= 27) { set_density(512); }
  if (get_density() <= 0) { set_density(0.5); }
  if (get_tstep() <= 0)     { set_tstep(0.001); }
  set_rcut(1.e20);
  set_Tinit(1.0);
  set_sfreq(100);      
}

void LJSimulation :: init_compute()
{
  real_type scale_length;
  
  //computed  
  set_n3(2);
  set_sideLength( pow(get_npart()/get_density(),0.3333333) );
  // The particles are assigned in a cubic lattice
  // According to the number of particles, we find the lowest
  // perfect cube, greater than or equal to the number of particles
  int n3 = get_n3();
  while ((n3*n3*n3)<get_npart()) n3++;
  set_n3(n3);
  
}

void LJSimulation :: init_positions()  
{
  int pos_x = 0;
  int pos_y = 0;
  int pos_z = 0;    
  
  Vec3D<real_type> pos; 
  
  // Assign the particles in a cubic lattice
  
  for(int i=0; i<get_npart(); ++i)
  {
    pos.setItem(0,(real_type)(pos_x) + 0.5);
    pos.setItem(1,(real_type)(pos_y) + 0.5);
    pos.setItem(2,(real_type)(pos_z) + 0.5);

    pos *= ( get_sideLength() / get_n3() );
    
    particles[i].setPos(pos);
    
    pos_x++;
    if(pos_x == get_n3())
    {
      pos_x = 0;
      pos_y++;
      if(pos_y == get_n3())
      {
	pos_y = 0;
	pos_z++;
      }
    }
  }
  
}

void LJSimulation :: init_velocities()  
{
  Vec3D<real_type> vel; 
  Vec3D<real_type> cmv;		//center of mass
  real_type k_energy=0;		//kinetic energy
  
  std::random_device rd;	//random number generator	
  std::mt19937 gen(rd());      
  std::exponential_distribution<> exp_d(1);
    
  for(int i=0; i<get_npart(); ++i)
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
  for(int i=0; i<get_npart(); ++i)
  {
    cmv += particles[i].getVel();
  }

  for(int i=0; i<get_npart(); ++i)
  {
    particles[i].vel() -= cmv/get_npart();
    k_energy += (particles[i].getVel()*particles[i].getVel());
  }
  k_energy *= 0.5;
  
  //TODO Maybe better to create a new class that holds the physics
  if (get_Tinit()>0.0)
  {
    real_type temp = k_energy/get_npart()*2./3.;
    real_type fac = sqrt(get_Tinit()/temp);
    k_energy = 0;
    for(int i=0; i<get_npart(); ++i)
    {
      particles[i].vel() *= fac;
      k_energy += (particles[i].getVel()*particles[i].getVel());
    }
    k_energy *= 0.5;
  }
  
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

void LJSimulation :: start(int nsteps) 
{
  set_nsteps(nsteps);
  Vec3D<int> *bc;	//boundary cross counter

  bc = new Vec3D<int>[get_npart()];
  
  std::cout << "START" << std::endl;
  real_type L = get_sideLength();
  real_type dt; //DA DEFINIRE
  
  for (int s=0; s<get_nsteps(); ++s)
  {
    // First integration half step
    for(int i=0; i<get_npart() ; ++i)
    {
      particles[i].pos() += particles[i].vel()*dt + particles[i].f()*0.5*dt*dt;
      particles[i].vel() += particles[i].f()*0.5*dt;
      
      //apply periodic boundary conditions
      if (particles[i].pos().at(0) < 0.0) { particles[i].pos().at(0) += L; bc[i].at(0)--; }
      if (particles[i].pos().at(0) > L  ) { particles[i].pos().at(0) -= L; bc[i].at(0)++; }
      
      if (particles[i].pos().at(1) < 0.0) { particles[i].pos().at(1) += L; bc[i].at(1)--; }
      if (particles[i].pos().at(1) > L  ) { particles[i].pos().at(1) -= L; bc[i].at(1)++; }
      
      if (particles[i].pos().at(2) < 0.0) { particles[i].pos().at(2) += L; bc[i].at(2)--; }
      if (particles[i].pos().at(2) > L  ) { particles[i].pos().at(2) -= L; bc[i].at(2)++; }
    }
    
    real_type PE = calculate_forces();
    
    // Second integration half step
   real_type KE=0;
    for(int i=0; i<get_npart(); ++i)
    {
      particles[i].vel() += particles[i].f()*0.5*dt;
      KE += (particles[i].getVel()*particles[i].getVel());
    }
    KE *= 0.5;
    real_type TE=KE+PE;
    
//     print_out();
  }
  
  delete bc;
}

real_type LJSimulation :: calculate_forces() 
{
  real_type energy = 0;
  //A simple N^2 algorithm to compute the forces and the potential energy
  //of the full particle system
  for(int i=0; i<get_npart(); ++i)
  {
    for(int j=i+1; j<get_npart(); ++j)
    {
      Vec3D<real_type> dist;
      dist = particles[i].pos() - particles[j].pos();
      real_type dist2 = dist.sqr();
      real_type cutoff2=10;
      if(dist2<cutoff2)
      {
	energy += LJpot.compute_energy(dist2);
	real_type ffactor = LJpot.compute_force(dist2);
	
	particles[i].f().at(0) += dist.at(0) * ffactor / dist2;
	particles[j].f().at(0) -= dist.at(0) * ffactor / dist2;
	particles[i].f().at(1) += dist.at(1) * ffactor / dist2;
	particles[j].f().at(1) -= dist.at(1) * ffactor / dist2;
	particles[i].f().at(2) += dist.at(2) * ffactor / dist2;
	particles[j].f().at(2) -= dist.at(2) * ffactor / dist2;
      }
    }
  }
  return energy;
}

LJSimulation :: ~LJSimulation()
{
  delete particles;
}