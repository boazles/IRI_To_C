# iri
A C wrapper for the International Reference Ionosphere (IRI) 2016 model.

Model input is accomplished using a  configuration file called params folllowed by a number.

Enter  the following parameters seperated by a newline
1. 0 or 1 depending on coordinate system geographic or geomagnetic
2. Latitude
3. Longitude
4. Year in YYYY format
5. Month Day in MMDD format
6. time inUTC in hh.xx format
7. Minimum altitude in KM
8. Maximun altitude in KM
9. Altitude step. Total number Altitude data points  must be less then 1000

Currently only wraps the iri_sub function but can be easily adapted to  wrap the iri_web function as well.

Generates a gnplot for each input file.

Built on Ubuntu 18.04 LTE using the gfortran 7.5.0  and gcc 7.5.0 compilers with a dependency on gnuplot

To build:
1. type make clean
2. type make

To run:
1. type ./run file number

currently files numbers 1 and 2 are configured.