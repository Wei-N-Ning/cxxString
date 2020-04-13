# C++ String Manipulation

## Working with Boost in CMake

### How to determine the Boost library names for CMake

see: <https://stackoverflow.com/questions/26749461/how-to-determine-the-boost-library-names-for-cmake>

> Thus, it is sufficient to add ${Boost_INCLUDE_DIRS} to the include directories of your target.

### Boost components that ARE NOT header-only

see: <https://stackoverflow.com/questions/13604090/which-boost-libraries-are-header-only>

> If boost library is compiled, then component name is basically lowercase name of library without prefixes and suffixes
> (for example for boost_system-vc141-mt-x64-1_66.lib it would be 'system')

reference: <https://cmake.org/cmake/help/v3.15/module/FindBoost.html>
