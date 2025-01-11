# Supported platforms

Despite efforts to make the program run in both windows and linux, the developers can just garantee a stable build and running proccess in Linux platforms

# Needed tools

- Make
- CMake

# Program description

A better explanation of behavior, models and idea are better explained at [here](https://docs.google.com/document/d/1Js71dv7YF3yZj3FRBJvXDuvRm4p_bj3-cLGME-FQ5Ec/edit?tab=t.0) 

# Build and Run 

At the root project folder:

```
mkdir build
cd build
cmake .. .

make 

# now you can run both smart and dummy agents

./smart path/to/grid

./dummy path/to/grid

# after running your agent, it is going to create a foulder with
# the process id and states progressions and logs 

```
