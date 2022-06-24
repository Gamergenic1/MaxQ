# Principles

> There are no right or wrong solutions, only solutions optimized to differing criteria.

Most disagreements regarding software implementations are simple consequences of differing criteria each solution was optimized for.  Explicitly calling out a project's driving principles assists others who may utilize the project.

# MaxQ's key principles  
* Optimize higher level concepts first (conceptual clarity, etc)  
* Do not optimize lower-level concepts until a need is proven  

## Optimizations in service of principles
* Conceptual Clarity over Software Abstraction
* Low barriers to codebase entry over Latest Features & Libraries 
* Visible & Debuggable over Hidden Implementations
* Optimize for Aerospace domain users before Unreal-Engine domain users

### Conceptual Clarity

> Conceptual Clarity  
is often in opposition to:  
> Software Abstraction  

Every project has a maximum complexity level.  Upon reaching maximum complexity additional progress is nearly impossible.  Can you still see "the forest through the trees" in your code?  Or, do you just see a mass of low level operations absent any context around their usage?   Conceptual clarity increases the complexity cap of projects.

This is especially true for software interacting with or simulating physical processes.  

For example, consider:  
`FVector` with floating-point `x`, `y`, `z`.  
Is it a distance?  Yes?  Is it meters, or kilometers?  Is it an absolute position or relative distance?  What coordinate system does it belong to?  What is that coordinate system relative to in position and orientation, and are the axes left-handed or right handed?  Is it safe to assume x, y, and z are rectangular coordinates, or, does it sometimes carry spherical, cylindrical, geodetic, planetographic, lattiudinal, or other coordinate types?  
So it's not a distance?  Velocity?  Same questions as above.  Or, acceleration?  A Force? An impulse?  A torque?  Angular velocity?  Or maybe it's just a dimensionless vector?  A unit vector?  
`FVector` has an addition operator.  Who's responsible for ensuring "a+b" isn't summing a geodetic vector in degrees/degrees/meters with a rectangular coordinate?  The developer, or does the compiler help?  

**MaxQ**: Physical Quantity units/systems/etc should quickly discoverable without inspecting procedural implementations in order to deduce.
**MaxQ**: Enforce physical type/units/standard as compile time type-checking.  
**MaxQ**: Display units-of-measure (degrees, kilometers, seconds, etc) when editing values in the UE Inspector.  
**MaxQ**: Conceptual clarity lifts the maximum complexity a simulation-type project can reach, while many traditional software principles & axioms of abstraction etc act oppositely.  Prioritize the former first.  


### Low Barriers to Codebase Entry

> Minimizing a project's learning curves:  
...is often in conflict with:  
> utilitization of all latest language features, frameworks, and libraries  

Projects generally originate as prototypes and if successful undergo further refinement in preproduction.  Meeting aggressive timelines often requires rapidly scaling a development team before/during production.

Keeping your project's learning curve low is a great way to maximize it's potential scaling rate.  Each additional feature, framework, and library reduces the potential hiring pool and requires additional spin up time for new members.

**MaxQ**: Prioritize learning curve reductions.  
**MaxQ**: Consider tradeoff of the knowledge burden imposed on developers before adding dependencies on features/libraries/frameworks.  
**MaxQ**: Simplicity adds value - prioritize it.  

### Visible & Debuggable

Promotion of:  
> Visibility/insight into code operation (to developers) and ease of debugging  
...is commonly in opposition to:  
> "elegance", minimizing duplicative code, total codebase size, and other principles software engineers strive for.  

Hidden/"automatic"/elegance/abstraction are software development conceptual tools, and tools come with *both* "costs" and "benefits".  Would you choose a hammer for nails, screws, and bolts?   Yes!  It's a great choice when you're constrained to a single tool and 95% of the house needs built by nails.  Most software is a nail so by all means, hammer everything.  Physical simulation projects are more like engines constructed 95% with bolts.  So if you only get one, pick a wrench - you can still use it to pound nails and screws.  In the real world we're not limited to one choice so we optimize our tools to the needs.

Confused?  Then maybe you haven't had to debug deeply into c++ standard library header-file-only implementations.  The library is extremely elegant.  Its type abstractions are superb.  Boost is great.  So is having only one well-optimized vectorized double3 multiplication operator.

However, when the rotation the velocity of a space capsule is off by .5 km/s when transitioning your coordinate system from inertial to rotational/fixed-body having a separate implementation of velocity operations adds value.  Setting a breakpoint inside a velocity operator that does not break every time a distance, force, torque, etc is added/scaled etc adds value.

**MaxQ**: Prioritize practical benefits of visibility/debuggability above theoretical benefits of elegance, abstraction, and performance.  
**MaxQ**: You can always optimize for performance/elegance/etc when needs become clear later.


### Aerospace domain above software domain

MaxQ integrates technology of two domains - spaceflight, and real-time (game) engines.   It is potentially interesting for developers coming from either domain.

**MaxQ**: Optimize for developers coming from either software or aero/space domains.  When in conflict, optimize for users coming from aero/space domains utilizing Blueprints first and Unreal Engine C++ developers second.  

This has influence on MaxQ's terminology, parameter and return value conventions, appearance of consistency in blueprints above C++ implementation, etc.
