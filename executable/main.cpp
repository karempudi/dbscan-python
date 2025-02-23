#include "dbscan/point.h"
#include "dbscan/geometryIO.h"
#include "dbscan/pbbs/parallel.h"
#include "dbscan/pbbs/gettime.h"
#include "dbscan/pbbs/parseCommandLine.h"

#include "Caller.h"

int main(int argc, char* argv[]) {
  commandLine P(argc,argv,"[-o <outFile>] [-eps <p_epsilon>] [-minpts <p_minpts>] <inFile>");
  char* iFile = P.getArgument(0);
  char* oFile = P.getOptionValue("-o");
  size_t rounds = P.getOptionIntValue("-r",1);
  double p_epsilon = P.getOptionDoubleValue("-eps",1);
  size_t p_minpts = P.getOptionIntValue("-minpts",1);
  double p_rho = P.getOptionDoubleValue("-rho",-1);

  int dim = readHeader(iFile);
  _seq<double> PIn = readDoubleFromFile(iFile, dim);

  bool* coreFlag = new bool[PIn.n / dim];
  int* cluster = new int[PIn.n / dim];
  double* data = PIn.A;

  auto clusterer = Wrapper::Caller(data, dim, PIn.n / dim);
  clusterer.computeDBSCAN(p_epsilon, p_minpts, coreFlag, cluster);

  if (oFile != NULL) {
    writeArrayToFile("cluster-id", cluster, PIn.n / dim, oFile);
  }

  PIn.del();
  delete[] coreFlag;
  delete[] cluster;
  return 0;
}
