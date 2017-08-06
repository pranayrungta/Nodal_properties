#include "btc_clc_degree.cpp"

int main()
{using namespace parameter;

	Processor process(datafile);
	for(const double c:cRange)
	{
		process.openfiles(c);
		for(const int pc : perturbCountRange)
			process.write_to_file(pc,c);
		process.closefiles();
	}
}

