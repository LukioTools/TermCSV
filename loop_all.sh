echo "Compiling sources: "
find v3/src/ -name "*.cpp" -exec ./compile_one.sh {} \;
 

echo "Merging objects: "
echo "ar rcs v3/bin/libTermCSV.a \$(find v3/bin -name \"*.o\")"
ar rcs v3/bin/libTermCSV.a $(find v3/bin -name "*.o")
echo "created: v3/bin/libTermCSV.a"

echo "include 'v3/bin/libTermCSV.a' while compiling your executeable"


