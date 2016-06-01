#include "LJSimulation.hpp"

using namespace std;

int main(int argc, char** argv) 
{
  int N = 216;
  int nstep = 100;
  
  LJSimulation sim;
  
  sim.init();
  sim.set_number_of_particles(N);  //check what happen when I do not give this as input
  
  sim.start(nstep);

  return 0;
}