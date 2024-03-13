# python_c_nvidia
just going for writing some python code

# build 

python build_nvc.py basic.c

nvc -fPIC -shared -fopenmp -mp=gpu -I$(python -c "import numpy; print(numpy.get_include())") basic.c -o basic.so $(python3-config --includes) $(python3-config --ldflags)




# demo

nsys profile --stats=true python demo.py

