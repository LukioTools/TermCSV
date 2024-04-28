

echo $1
path=$1
bname=$(basename $path)
fname=$(basename $path .cpp)
dir=$(echo $path | sed 's/^v3\/src\///' | sed 's/'$bname'$//')
out_dir="v3/bin/"$dir

mkdir -p $out_dir
#echo "path: "$path
#echo "bname: "$bname
#echo "fname: "$fname
#echo "dir: "$dir
#echo "out_dir: "$out_dir



c++ -Wall -std=c++20 -c $path -o $out_dir$fname".o"


