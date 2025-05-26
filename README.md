<div align="center">

  # Data Structures and Algorithms library
  
  dsa-library is open-source collection of self-made data structures and algorithms made in C++.


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

To using CMake you can do so using following commands

```
cmake -B build
cmake --build build
```

To run tests you can start output binary with `--test` argument

```
./build/out --test
```

Library uses namespace for each structure (_ds::structures_) and algorithm type (_ds:alogirthms_)

### Classes

[StaticArray](#dsstructuresarraysstaticarraytypename-t-size_t-size)

#### ds::structures::arrays::StaticArray<typename T, size_t size>

Private members:
- pElements - Pointer to heap allocated array of type _T_ with size of template parameter _size_

Public members:
- ValueType - Type alias to template type _T_
- ReferenceType - Type alias to reference of template type _T_
- ConstReferenceType - Type alias to const reference of template type _T_
- PointerIterator - Type alias to pointer of template type _T_
- Iterator - Type alias to [StaticArrayIterator](###ds::structures::arrays::StaticArrayIterator<typename StaticArray>)

Public methods:
- StaticArray() - Default constructor. Initializes pointer to this->pElements of size of template parameter _size_.
- StaticArray(const std::initializer_list<ValueType> list) - Parametric constructor. Allocates array of type _ValueType_ and size of template parameter _size_. If initializer list size does not match template parameter _size_, `std::runtime_error` will be thrown. Method can be used using following syntax.

```
ds::structures::arrays::StaticArray arr<int, 3>{1, 2, 3}
```

or

```
ds::structures::arrays::StaticArray<int, 3> arr({1, 2, 3})
```

- StaticArray(const StaticArray<ValueType, size>& other) - Copy constructor. Create deep copy of another StaticArray object. _ValueType_ of both arrays needs to match. Can be called using following syntax.

```
ds::structures::arrays::StaticArray<int, 3> arr1{1, 2, 3}; // Original array
ds::structures::arrays::StaticArray<int, 3> arr2(&arr1); // Copy of arr1. Copies content of this->pElements, not just copying pointer.
```

- StaticArray(StaticArray<ValueType, size>&& other) - Move constructor. Moves private members from `other` object to `this` object by setting `other` object private members to `NULL`. Can be used using following syntax.

```
ds::structures::arrays::StaticArray<int, 3> arr1{1, 2, 3}; // Original array
ds::structures::arrays::StaticArray<int, 3> arr2(&&arr1); // Moved this->pElements from arr1 to arr2. Now arr1->pElements is set to nullptr
```

- ~StaticArray() - Destructor. Deallocate `this->pElements` and sets it to `nullptr`.
- ReferenceType get(const size_t index) - Returns element at index as reference, meaning it can be modified. Can be used using following syntax.

```
ds::structures::arrays::StaticArray<int, 3> arr1{1, 2, 3};
arr1.get(1); // Returns 2
arr1.get(1) = 5; // Returns element at index 1 and sets it to 5
```

- ConstReferenceType get(const size_t index) const - Returns element at index as const reference, meaning it cannot be modified. Works on both non-const and const objects. Can be used using following syntax.

```
const ds::structures::arrays::StaticArray<int, 3> arr1{1, 2, 3};
arr1.get(1); // Returns 2
arr1.get(1) = 5; // ❎ Cannot be used since const variant of method is used
```

- constexpr int getSize() - Returns size of array. Return value is being evaluated at compile-time.
- ReferenceType operator[](const size_t index) - operator[] overload. Returns `this->get(index)` as reference, meaning it can be modified.
- ConstReferenceType operator[](const size_t index) const - operator[] overload. Returns `this->get(index)` as const reference, meaning it cannot be modified. Works on both non-const and const objects

## Contributing

Feel free to fork the project and submit pull requests. For major changes, please open an issue first.

## License

This project is licensed under the MIT License.

    
