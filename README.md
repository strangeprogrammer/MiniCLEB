# MiniCLEB

### Introduction

A limited implementation of an **int** to **LEB128** bytes string converter for **python** that uses a **C** backend for speed.

More information on **LEB128** can be found at [wikipedia](https://en.wikipedia.org/wiki/LEB128).

### Package Creation

Use the following command to create a source distribution of this package from within the project's root directory:

```bash
./setup.py sdist
```

The source package will then be a **.tar** file located within the **dist/** directory.

### Installation Requirements

This project requires [SWIG](http://swig.org/) to be installed in order to build the project.

### Package Installation

Please read the **Installation Requirements** section before continuing to this one. Suppose that you have downloaded or created the corresponding package for this project as **MiniCLEB.tar**. You may then install it with the following command:

```bash
pip3 install ./MiniCLEB.tar
```

Alternatively, due to **pip3** being a smart tool, you can run the following tool from the project's root directory:

```bash
pip3 install .
```

### Additional Information

This project is currently in development and is very unstable as a result. This project is currently only released as a source distribution.

### License

This project is licensed using the '0BSD' license. See the file 'LICENSE.txt' for details. Visit [The Open Source Initiative](https://opensource.org/licenses/0BSD) or read the [wikipedia entry](https://en.wikipedia.org/wiki/BSD_licenses#0-clause_license_(%22Zero_Clause_BSD%22)) for more information about the '0BSD' license.
