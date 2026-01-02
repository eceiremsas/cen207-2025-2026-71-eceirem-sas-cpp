# CEN207 Data Structures Project - Recipe and Nutrition Tracker
## Project Report

---

## 1. PROJECT SUMMARY

### 1.1 Overview
This project is a comprehensive **Recipe and Nutrition Tracker Application** developed for the midterm phase of the CEN207 Data Structures course. The project includes the practical implementation of 7 different data structures and algorithms.

### 1.2 Project Information
- **Project Name:** Recipe and Nutrition Tracker
- **Course:** CEN207 Data Structures
- **Academic Year:** 2025-2026
- **Project Type:** Midterm Project
- **Programming Languages:** C (C99) and C++ (C++17)
- **Build System:** CMake (>= 3.12)

### 1.3 Project Objectives
The project demonstrates the use of the following data structures and algorithms in a real-world scenario (recipe management):
1. Linked List
2. XOR Linked List
3. Stack
4. Queue
5. Hash Table
6. Graph - BFS and DFS algorithms
7. Heap - Min-Heap
8. Sparse Matrix

---

## 2. PROJECT STRUCTURE

### 2.1 Directory Structure
```
cen207-2025-2026-71-eceirem-sas-cpp-1/
├── include/              # C header files (.h)
│   ├── recipe.h
│   ├── linked_list.h
│   ├── xor_linked_list.h
│   ├── stack.h
│   ├── queue.h
│   ├── hash_table.h
│   ├── graph.h
│   ├── heap.h
│   ├── sparse_matrix.h
│   └── menu.h
├── src/                  # Source code files
│   ├── recipe.c          # Recipe management
│   ├── linked_list.c     # Linked list implementation
│   ├── xor_linked_list.c # XOR linked list implementation
│   ├── stack.c           # Stack implementation
│   ├── queue.c           # Queue implementation
│   ├── hash_table.c      # Hash table implementation
│   ├── graph.c           # Graph implementation (BFS/DFS)
│   ├── heap.c            # Min-Heap implementation
│   ├── sparse_matrix.c   # Sparse matrix implementation
│   ├── menu.c            # Menu management
│   ├── main.c            # Main C application
│   ├── recipe/           # C++ recipe module
│   │   ├── header/       # C++ header files
│   │   └── src/          # C++ source files
│   ├── recipeapp/         # C++ application module
│   └── utility/          # Utility functions
├── tests/                # Test files
│   ├── test_recipes.cpp  # GoogleTest tests
│   └── test_recipes_cpp.cpp
├── docs/                 # Documentation
│   ├── index.md
│   ├── architecture.md
│   ├── developers.md
│   └── security.md
├── build/                # Build outputs
├── assets/               # Images and badges
└── CMakeLists.txt        # Main CMake configuration
```

### 2.2 File Statistics
- **C Source Files:** 11 files (.c)
- **C++ Source Files:** 10 files (.cpp)
- **Header Files:** 10 files (.h/.hpp)
- **Test Files:** 2 files
- **Total Lines of Code:** Approximately 3000+ lines

---

## 3. DATA STRUCTURES AND ALGORITHMS USED

### 3.1 Recipe Structure
**Purpose:** Basic data structure for storing recipe information

**Features:**
- Unique ID
- Recipe name
- Category (e.g., "Dessert", "Main Course")
- Calorie count
- Preparation time (minutes)
- Ingredient list (maximum 50 ingredients)
- Preparation instructions

**Functions Used:**
- `recipe_create()` - Create new recipe
- `recipe_add_ingredient()` - Add ingredient
- `recipe_set_instructions()` - Set instructions
- `recipe_display()` - Display recipe information
- `recipe_copy()` - Deep copy
- `recipe_destroy()` - Memory cleanup

### 3.2 Linked List
**Purpose:** Store recipes in an ordered manner

**Features:**
- Singly linked list
- Insertion at head and tail
- Search and delete operations
- Traversal functions

**Complexity:**
- Insertion: O(1) (at head/tail)
- Search: O(n)
- Deletion: O(n)

### 3.3 XOR Linked List
**Purpose:** Memory-efficient doubly linked list (with single pointer)

**Features:**
- XOR pointer to store previous and next nodes in a single pointer
- Forward and backward traversal
- 50% memory savings (for doubly linked list)

**Complexity:**
- Insertion: O(1)
- Traversal: O(n)

### 3.4 Stack
**Purpose:** Manage recipe operations using LIFO (Last In First Out) principle

**Features:**
- Push (insert) and Pop (remove) operations
- Operation history tracking
- Undo functionality

**Use Case:**
- Undoing recipe add/delete operations

**Complexity:**
- Push: O(1)
- Pop: O(1)
- Peek: O(1)

### 3.5 Queue
**Purpose:** FIFO (First In First Out) structure for weekly meal planning

**Features:**
- Circular queue implementation
- Enqueue (insert) and Dequeue (remove) operations
- Weekly recipe scheduling

**Use Case:**
- Creating weekly meal plans

**Complexity:**
- Enqueue: O(1)
- Dequeue: O(1)

### 3.6 Hash Table
**Purpose:** Fast recipe search and grouping by categories

**Features:**
- Collision resolution with chaining
- Fast access with hash function
- Category-based grouping

**Complexity:**
- Average: O(1)
- Worst case: O(n)

### 3.7 Graph
**Purpose:** Model relationships between recipes (similar ingredients, similar categories)

**Features:**
- Directed graph
- BFS (Breadth-First Search) algorithm
- DFS (Depth-First Search) algorithm
- Finding related recipes

**Use Cases:**
- Similar recipe recommendations
- Ingredient-based relationship network

**Complexity:**
- BFS: O(V + E)
- DFS: O(V + E)
- V: Number of vertices, E: Number of edges

### 3.8 Heap (Min-Heap)
**Purpose:** Sorting by calories or preparation time

**Features:**
- Min-Heap implementation
- Prioritizing lowest calorie/preparation time recipes
- Heapify operations

**Use Case:**
- Low-calorie recipe recommendations
- Quick preparation recipes

**Complexity:**
- Insertion: O(log n)
- Find minimum: O(1)
- Deletion: O(log n)

### 3.9 Sparse Matrix
**Purpose:** Efficiently store recipe-ingredient relationships

**Features:**
- Store only non-zero values
- Memory efficiency
- Linked list-based implementation

**Use Case:**
- Showing which ingredients are used in which recipes

**Complexity:**
- Insertion: O(1)
- Search: O(n)

---

## 4. TECHNICAL DETAILS

### 4.1 Programming Languages and Standards
- **C Standard:** C99
- **C++ Standard:** C++17
- **Compiler Warnings:** -Wall -Wextra -Wunused-function

### 4.2 Build System
**CMake Configuration:**
- Minimum CMake version: 3.12
- Platform support: Windows, Linux (WSL), macOS
- Build types: Debug and Release
- Automatic GoogleTest integration
- Doxygen documentation support

### 4.3 Testing Infrastructure
**GoogleTest Framework:**
- Automatic test discovery
- Unit tests
- Test coverage reports
- JUnit XML format output

**Test Coverage:**
- Comprehensive tests for all data structures
- Edge cases (boundary conditions)
- Memory management tests
- Algorithm validation tests

### 4.4 Documentation
**Doxygen:**
- Automatic API documentation
- Inline code comments
- HTML and LaTeX outputs
- Documentation coverage reports

**MkDocs:**
- Web-based documentation
- Markdown support
- Automatic site generation

### 4.5 Code Quality
**Tools:**
- **AStyle:** Code formatting
- **OpenCppCoverage (Windows):** Test coverage
- **gcov/lcov (Linux):** Test coverage
- **ReportGenerator:** Coverage reports

**Coverage Metrics:**
- Line Coverage
- Branch Coverage
- Method Coverage

---

## 5. PLATFORM SUPPORT

### 5.1 Supported Platforms
- ✅ **Windows** (Visual Studio Community Edition)
- ✅ **Linux** (WSL - Ubuntu 20.04)
- ✅ **macOS** (Xcode/Clang)

### 5.2 Build Scripts
**Windows:**
- `7-build-app-windows.bat` - Full build process (11-15 minutes)
- `7-build-doc-windows.bat` - Documentation only
- `8-build-test-windows.bat` - Tests only
- `9-clean-project.bat` - Project cleanup

**Linux/WSL:**
- `7-build-app-linux.sh` - Full build process
- `8-build-test-linux.sh` - Test operations

### 5.3 GitHub Actions
- Automatic CI/CD pipeline
- Multi-platform testing
- Windows, macOS, Linux support

---

## 6. APPLICATION FEATURES

### 6.1 Main Menu Features
1. **Add Recipe:** Create and save new recipes
2. **Search Recipe:** Search by ID, name, or category
3. **List Recipes:** Display all recipes
4. **Delete Recipe:** Remove recipe operations
5. **Category Filtering:** Filter by category
6. **Calorie-based Sorting:** Sorting using Heap
7. **Graph Traversal:** Find similar recipes using BFS/DFS
8. **Hash Table Operations:** Fast search and grouping
9. **Weekly Plan:** Weekly planning using Queue
10. **Operation History:** Undo functionality using Stack

### 6.2 User Interface
- Console-based interactive menu
- Colored output (platform-dependent)
- Error messages and validation
- User-friendly prompts

---

## 7. TEST RESULTS

### 7.1 Test Coverage
The project includes comprehensive unit tests for all data structures:

**Tested Components:**
- ✅ Recipe structure and functions
- ✅ Linked List all operations
- ✅ XOR Linked List traversal
- ✅ Stack push/pop operations
- ✅ Queue enqueue/dequeue operations
- ✅ Hash Table insertion/search
- ✅ Graph BFS/DFS algorithms
- ✅ Heap insertion/deletion/peek
- ✅ Sparse Matrix operations

**Test Scenarios:**
- Normal cases (happy path)
- Edge cases (empty list, single element, etc.)
- Memory management (memory leaks)
- Error conditions (null pointer, overflow, etc.)

### 7.2 Coverage Metrics
Coverage reports are generated separately for Windows and Linux platforms. Detailed coverage information can be viewed in the badges in the `assets/` folder.

---

## 8. PROJECT DEVELOPMENT PROCESS

### 8.1 Development Environment Setup
1. **Git Hooks Configuration:** Pre-commit and pre-push checks
2. **Package Managers:** Chocolatey and Scoop (Windows)
3. **Required Tools:** CMake, Doxygen, GoogleTest, etc.
4. **WSL Setup:** Linux development environment

### 8.2 Development Workflow
1. Code writing (C/C++)
2. Code formatting (AStyle)
3. Build and test
4. Coverage analysis
5. Documentation update
6. Commit and push

### 8.3 Quality Control
- Automatic checks with pre-commit hooks
- Mandatory code formatting
- Mandatory testing
- Documentation checks

---

## 9. CONCLUSION AND EVALUATION

### 9.1 Project Achievements
✅ **7 data structures successfully implemented**
✅ **Comprehensive test coverage achieved**
✅ **Multi-platform support added**
✅ **Professional documentation prepared**
✅ **CI/CD pipeline established**
✅ **Memory management correctly implemented**
✅ **High code quality maintained**

### 9.2 Concepts Learned
- Practical applications of data structures
- Algorithm complexity analysis
- Memory management (malloc/free)
- Test-driven development
- Documentation standards
- Cross-platform development
- Build systems (CMake)
- Version control (Git)

### 9.3 Technical Gains
- Advanced programming in C and C++ languages
- Real-world applications of data structures and algorithms
- Professional software development processes
- Testing and documentation culture
- Build automation and CI/CD

### 9.4 Future Improvements
- GUI (Graphical User Interface) can be added
- Database integration
- Web API support
- Mobile application
- User authentication
- Multi-language support

---

## 10. RESOURCES AND REFERENCES

### 10.1 Libraries Used
- **GoogleTest:** Unit testing framework
- **Doxygen:** API documentation generator
- **CMake:** Build system generator
- **MkDocs:** Documentation site generator

### 10.2 References
- CEN207 Data Structures course notes
- Cormen, Leiserson, Rivest, Stein - "Introduction to Algorithms"
- Doxygen documentation
- CMake documentation
- GoogleTest documentation

---

## 11. ADDITIONAL INFORMATION

### 11.1 Project Files
- **README.md:** General project information
- **CMakeLists.txt:** Build configuration
- **Doxyfile:** Documentation settings
- **mkdocs.yml:** Web documentation settings

### 11.2 Build Outputs
- **release_win/:** Windows release files
- **release_linux/:** Linux release files
- **docs/:** HTML documentation
- **site/:** MkDocs website

### 11.3 Test Reports
- **report_test_hist_win/:** Windows test history
- **report_test_hist_linux/:** Linux test history
- **recipe_tests_unit_win_cobertura.xml:** Coverage report

---

## 12. PROJECT TEAM

**Advisor:**
- Dr. Uğur CORUH - R&D Engineer and System Architecture

**Developer:**
- Ece İrem ŞAŞ - Project Developer

---

**Report Date:** 2025
**Project Version:** 1.0
**Status:** Completed ✅

---

*This report was prepared for the CEN207 Data Structures course midterm project.*
