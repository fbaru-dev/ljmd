#include "LJSimulation.hpp"

using namespace std;

int main(int argc, char** argv) 
{
  int N = 10;
  
  LJSimulation sim;
  
  sim.init(N);
  sim.start();

  return 0;
}