import sys

try:
    from skbuild import setup
    import nanobind
except ImportError:
    print("The preferred way to invoke 'setup.py' is via pip, as in 'pip "
          "install .'. If you wish to run the setup script directly, you must "
          "first install the build dependencies listed in pyproject.toml!",
          file=sys.stderr)
    raise

from setuptools import find_packages

# read the contents of your README file (https://packaging.python.org/en/latest/guides/making-a-pypi-friendly-readme/)
from pathlib import Path

this_directory = Path(__file__).parent
readme = (this_directory / "ReadMe.md").read_text()

setup(
    name="lets_be_rational",
    version="1.0.0",
    description="",
    author="Ali B",
    license="BSD",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    cmake_install_dir="src/lets_be_rational",
    include_package_data=True,
    python_requires=">=3.10",
    long_description=readme,
    long_description_content_type="text/markdown"
)
