# iri
A C wrapper to the International Reference Ionosphere (IRI) ionosphere model.
Input is a configuration file called params folllowed by a number.
with the following parameters seperated by a newline
0
Latitude
Longitude
Year in YYYY format
Month Day in MMDD format
time inUTC in hh.xx format
Minimum altitude in KM
Maximun altitude in KM
Altitude step must be less then 1000

Currently only wrapped the iri_sub function but can easily wrap the iri_web function as well
Generates a gnplot for each input file.
To build:
Built on Ubuntu 18.04 LTE using the gfortran 7.5.0  and gcc 7.5.0 compilers with a dependency on gnuplot
to build
1. type make clean
2. type make
to run
1. type ./run