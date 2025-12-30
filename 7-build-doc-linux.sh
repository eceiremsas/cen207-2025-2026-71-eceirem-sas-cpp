#!/bin/bash
# chmod +x 7-build-doc-linux.sh
# ./7-build-doc-linux.sh

# Get the current directory path
currentDir=$(dirname "$(readlink -f "$0")")

echo "Delete and Create the 'docs' folder and its contents"
rm -rf "docs/coverxygenliblinux"
rm -rf "docs/coverxygentestlinux"
rm -rf "docs/doxygenliblinux"
rm -rf "docs/doxygentestlinux"
mkdir -p "docs"
mkdir -p "docs/coverxygenliblinux"
mkdir -p "docs/coverxygentestlinux"
mkdir -p "docs/doxygenliblinux"
mkdir -p "docs/doxygentestlinux"

echo "Folders are Recreated successfully."

echo "Generate HTML/LATEX/RTF/XML Documentation for Library (No Source Code Only Headers)"
STRIP_FROM_PATH="$currentDir"
doxygen DoxyfileLibLinux

echo "Generate HTML/LATEX/RTF/XML Documentation for Unit Tests (Test Sources and Test Data Sets)"
doxygen DoxyfileTestLinux

echo "Not: coverxygen uses doxygen xml output for coverage"

if command -v python3 &> /dev/null && python3 -m coverxygen --help &> /dev/null; then
    echo "Run Documentation Coverage Data Collector for Library (No Source Code Only Headers)"
    python3 -m coverxygen --xml-dir ./docs/doxygenliblinux/xml --src-dir ./ --format lcov --output ./docs/coverxygenliblinux/lcov_doxygen_lib_linux.info

    echo "Run Documentation Coverage Data Collector for Unit Tests (Test Sources and Test Data Sets)"
    python3 -m coverxygen --xml-dir ./docs/doxygentestlinux/xml --src-dir ./ --format lcov --output ./docs/coverxygentestlinux/lcov_doxygen_test_linux.info

    if command -v reportgenerator &> /dev/null; then
        echo "Run Documentation Coverage Report Generator for Library"
        reportgenerator "-title:Recipe Library Documentation Coverage Report (Linux)" "-reports:**/lcov_doxygen_lib_linux.info" "-targetdir:docs/coverxygenliblinux" "-reporttypes:Html" "-filefilters:-*.md;-*.xml;-*[generated];-*build*" "-historydir:report_doc_lib_hist_linux"
        reportgenerator "-reports:**/lcov_doxygen_lib_linux.info" "-targetdir:assets/doccoverageliblinux" "-reporttypes:Badges" "-filefilters:-*.md;-*.xml;-*[generated];-*build*"

        echo "Run Documentation Coverage Report Generator for Unit Tests"
        reportgenerator "-title:Recipe Library Test Documentation Coverage Report (Linux)" "-reports:**/lcov_doxygen_test_linux.info" "-targetdir:docs/coverxygentestlinux" "-reporttypes:Html" "-filefilters:-*.md;-*.xml;-*[generated];-*build*" "-historydir:report_doc_test_hist_linux"
        reportgenerator "-reports:**/lcov_doxygen_test_linux.info" "-targetdir:assets/doccoveragetestlinux" "-reporttypes:Badges" "-filefilters:-*.md;-*.xml;-*[generated];-*build*"
    else
        echo "Warning: reportgenerator not found, skipping coverage report generation"
    fi
else
    echo "Warning: coverxygen not found, skipping documentation coverage analysis"
fi

echo "Copy the 'assets' folder and its contents to 'docs' recursively"
if [ -d "assets" ]; then
    cp -R assets "docs/assets"
fi

echo "Copy the 'README.md' file to 'docs/index.md'"
if [ -f "README.md" ]; then
    cp README.md "docs/index.md"
fi

echo "Files and folders copied successfully."

echo "...................."
echo "Documentation Generation Completed!"

