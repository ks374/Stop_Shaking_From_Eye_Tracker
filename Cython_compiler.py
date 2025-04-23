from setuptools import setup, Extension
from Cython.Build import cythonize

ext = Extension(
    name = "sit_still_cython",
    sources=["sit_still_cython.pyx", "Sit_still.c","psems.c"],  # Replace with your real .c file name
    include_dirs=["."],
    libraries=["rt"],  # Add your libraries if needed, e.g. ["rt"]
)

setup(
    ext_modules=cythonize([ext])
)