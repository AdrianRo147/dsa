<div align="center">
  <h1>Data Structures and Algorithms library</h1>
  
  <p>dsa-library is open-source collection of self-made data structures and algorithms made in C++.</p>

  <img src="https://badgen.net/github/license/adrianro147/dsa">
  <img src="https://badgen.net/github/stars/adrianro147/dsa">
  <img src="https://badgen.net/github/contributors/adrianro147/dsa">
  <img src="https://badgen.net/github/commits/adrianro147/dsa">
</div>

## Repository Details

- **Primary Language:** C++
- **Build Tool:** Visual Studio solution, CMake v3.30.5
- **External libraries used:** Google Testing Framework
- **License:** MIT License

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

Clone the repository:

~~~bash
git clone https://github.com/AdrianRo147/dsa
~~~

## Usage

To build using CMake you can do so using following commands

```
cmake -B build
cmake --build build
```

To build using Visual Studio all you need to do is to build project. Before that make sure you have already setted up [vcpkg](https://learn.microsoft.com/sk-sk/vcpkg/get_started/get-started-msbuild?pivots=shell-powershell)

To run tests you can start output binary with `--test` argument

```
./build/out --test
```

Library uses namespace for each structure (_ds::structures_) and algorithm type (_ds:alogirthms_)

For detailed documentation about library structures and algorithms see [Wiki](https://github.com/AdrianRo147/dsa/wiki/Library-Documentation)

## Contributing

Feel free to fork the project and submit pull requests. For major changes, please open an issue first.

## License

This project is licensed under the MIT License.

    
