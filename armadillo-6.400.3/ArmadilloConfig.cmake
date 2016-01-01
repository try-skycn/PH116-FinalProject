# - Config file for the Armadillo package
# It defines the following variables
#  ARMADILLO_INCLUDE_DIRS - include directories for Armadillo
#  ARMADILLO_LIBRARY_DIRS - library directories for Armadillo (normally not used!)
#  ARMADILLO_LIBRARIES    - libraries to link against

# Tell the user project where to find our headers and libraries
set(ARMADILLO_INCLUDE_DIRS "/home/xxj/Documents/PH116-FinalProject-master/armadillo-6.400.3;/home/xxj/Documents/PH116-FinalProject-master/armadillo-6.400.3")
set(ARMADILLO_LIBRARY_DIRS "/home/xxj/Documents/PH116-FinalProject-master/armadillo-6.400.3")

# Our library dependencies (contains definitions for IMPORTED targets)
include("/home/xxj/Documents/PH116-FinalProject-master/armadillo-6.400.3/ArmadilloLibraryDepends.cmake")

# These are IMPORTED targets created by ArmadilloLibraryDepends.cmake
set(ARMADILLO_LIBRARIES armadillo)

