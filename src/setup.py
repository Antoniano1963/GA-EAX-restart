from distutils.core import setup, Extension
import glob

FILES = glob.glob("*.c")

print (FILES)

# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.

ARGS = ['-O3', '-Wall', '-IINCLUDE', '-DTWO_LEVEL_TREE', '-g']
# ARGS = []

example_module = Extension('_EAX',
                           sources=FILES,
                           extra_compile_args=ARGS,)

setup(name='EAX',
      version='0.1',
      author="SWIG Docs",
      description="""Simple swig example from docs""""",
      ext_modules=[example_module],
      py_modules=["EAX"],
      )
