from distutils.core import setup, Extension
# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

ARGS = ['-O3', '-Wall', '-IINCLUDE', '-DTWO_LEVEL_TREE','-g']
# ARGS = []

example_module = Extension('_EAX',
                           sources=["cross.cpp", "EAX.cpp", "environment.cpp", "evaluator.cpp", "indi.cpp", "kopt.cpp"
                                    , "randomize.cpp", "sort.cpp", "EAX_wrap.cxx"],
                           include_dirs=["INCLUDE", numpy_include],
                           extra_compile_args=ARGS,)

setup(name='EAX',
      version='0.1',
      author="SWIG Docs",
      description="""Simple swig example from docs""""",
      ext_modules=[example_module],
      py_modules=["EAX"],
      )
