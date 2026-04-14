# War on tags
This is a proposal repo which is trying to test out an alternative to using fixed numerical values as boundary condition tags. We hope to remove this dependence on tags and free these codes from years of servitude under the obstinacy of the numbers. 

# How it works:

Instead of assigning a single numeric tag to each boundary condition, we map each boundary condition to a dynamic list of tags. This allows users to extend the mapping at runtime and define their own tagging scheme.

By default, Tandem provides a predefined mapping to ensure backward compatibility. However, users can supply additional tags through a JSON configuration. These user-defined tags are appended to the defaults, giving more flexibility in how geometries are labeled.

In practice, this means you can associate multiple numeric tags with a specific boundary condition and use any of those tags when defining your geometry. This shifts control to the user, making it easier to adapt simulations to different tagging conventions.

Important Notes
Only boundary conditions with implemented numerical support are valid.
Adding a new name (e.g., "periodic") in the JSON configuration does not create a new boundary condition.
Unsupported boundary types will be ignored or rejected.
If a user uses conflicting tags, i.e., have the same number try to represent two different types of boundary conditions, the program will throw an error and exit.

In summary, users can customize how boundary conditions are tagged, but not define new boundary condition types beyond what Tandem currently supports.

## Build, run and clean

To build, use the make file

```
make build
```

To run, use
```
./tagFinder 
or
make run
```

and to clean, run

```
make clean
```

Eventually, if this is agreeable, we would use this in the ```GlobalSimplexMeshBuilder``` in tandem where we would just check if the tag is "in" the list that the particular BC is mapped to. Therefore, we would have the correct tags in the Lua file and the correct enum value in the BoundaryData map.