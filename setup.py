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

from pathlib import Path
this_directory = Path(__file__).parent
readme = (this_directory / "README.md").read_text()

setup(
    name="py_lets_be_rational",
    version="1.0.0",
    description="A port of letsBeRational",
    author="Ali B.",
    license="BSD",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    cmake_install_dir="src/py_lets_be_rational",
    include_package_data=True,
    python_requires=">=3.8",
    long_description=readme,
    long_description_content_type="text/markdown"
)