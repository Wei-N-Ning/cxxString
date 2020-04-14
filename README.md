# C++ String Manipulation

## Working with Boost in CMake

aka. can boost not suck?

### How to correctly turn on static linking

make sure the boost I'm using has its static libraries built; I've documented
that in `cxxConcurrency` - **download and build boost**; I've also made a helper
script to automated most tedious stuffs - see `vendor/get-boost.sh`

the place where I set `Boost_USE_STATIC_LIBS` DVar **really matters**; and in cmake
the true-ish value is `ON` or `TRUE`, **uppercase**

this post helped me: <<https://stackoverflow.com/questions/11237092/error-linking-boost-libraries>

> set the Boost_USE_STATIC_LIBS variable to TRUE (before find_package!)

see also: <https://stackoverflow.com/questions/3176035/link-the-static-versions-of-the-boost-libraries-using-cmake>

### How to use FindBoost - which actually is find_package(Boost) - correctly

I had some problems there since I had a previously installed boost 1.65.1
in my system lib location, and cmake **strongly prefers to use this version**,
before it told it otherwise.

this post helped me: <https://stackoverflow.com/questions/3016448/how-can-i-get-cmake-to-find-my-alternative-boost-installation>

> Anyway, it looks like all the BOOSTROOT, BOOST_ROOT, and Boost_DIR stuff would get
> annoyed unless one also sets Boost_NO_BOOST_CMAKE

therefore, combined with the previous static linking setting, the 
cmake statements look like: 

```cmake
set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/vendor/boost-1.72.0)
find_package(Boost 1.72.0 REQUIRED COMPONENTS regex)
```

### How to set boost header include path correctly

NOTE: failing to do so correctly **will cause linking error**

```text
undefined reference to `boost::re_detail::perl_matcher<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >
```

(again cmake strongly prefers to use the system installation, if there is one)

I **must tell my target where is the right boost header include path** by
calling `target_include_directories`, otherwise the linker, guided by a strongly
opinionated cmake, will link the 1.72.0 libraries with the 1.65.1-included 
object files

```cmake
add_executable(capitalize capitalize.cpp)
target_link_libraries(capitalize doctest ${Boost_LIBRARIES})
target_include_directories(capitalize PUBLIC ${Boost_INCLUDE_DIRS})
```

### How to determine the Boost library names for CMake

see: <https://stackoverflow.com/questions/26749461/how-to-determine-the-boost-library-names-for-cmake>

> Thus, it is sufficient to add ${Boost_INCLUDE_DIRS} to the include directories of your target.

### How to determine which boost component(s) I need 

In the case of regex, it's a single component. **There is no need to 
pull in system and other stuffs.**

### How to derive the component name from boost library name

it is best to look at the boost doc, but because I keep a local installation
in the vendor directory, it doesn't harm to figure it out myself.

`libboost_<component>`

see: <https://stackoverflow.com/questions/13604090/which-boost-libraries-are-header-only>

> If boost library is compiled, then component name is basically lowercase name of library without prefixes and suffixes
> (for example for boost_system-vc141-mt-x64-1_66.lib it would be 'system')

reference: <https://cmake.org/cmake/help/v3.15/module/FindBoost.html>
