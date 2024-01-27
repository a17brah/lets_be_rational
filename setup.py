import sys

try:
    from skbuild import setup
except ImportError:
    print("The preferred way to invoke 'setup.py' is via pip, as in 'pip "
          "install .'. If you wish to run the setup script directly, you must "
          "first install the build dependencies listed in pyproject.toml!",
          file=sys.stderr)
    raise

from setuptools import find_packages

setup(
    name="py_lets_be_rational",
    version="0.0.1",
    description="A port of letsBeRational",
    author="Ali Brahimi",
    license="BSD",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    cmake_install_dir="src/py_lets_be_rational",
    include_package_data=True,
    python_requires=">=3.8"
)