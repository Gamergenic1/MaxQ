# MaxQ
### A spaceflight Toolkit for Unreal Engine 5

Gamergenic has integrated **NASA**'s **SPICE** Toolkit for with **Epic Games**' realtime content creation platform **Unreal Engine 5**.  The **MaxQ** Spaceflight Toolkit for Unreal Engine 5 empowers anyone to easily build exciting, authentic spaceflight visualizations or cutting edge space-based gameplay, no programming experience or astronautical engineering degree required.  The toolkit solves challenging space flight problems in a real-time visualization environment - opening up new opportunities across an exciting spectrum of applications.

MaxQ features both a C++ and Unreal Engine Blueprints API, with 1:1 feature parity.

The toolkit is available to content creators under the MIT license, available as of December 25, 2021.  The MIT license allows anyone to use these tools free of charge for all projects, commercial or otherwise.

## About NASA's SPICE Toolkit

**MaxQ** is powered by the **SPICE Toolkit** software released by NASA/JPL/NAIF, which is the industry standard Space Flight toolset for space flight planning and analysis.  This toolkit is used by JPL and other organizations to plan and analyze real-life space missions and operations.

SPICE is described by NAIF as "a large collection of user-level application program interfaces (APIs) and underlying subroutines and functions", including significant technical reference documents and additional user-focused documentation.  NAIF has released versions of the SPICE toolkit for FORTRAN, MATLAB, C, and other scientifically-oriented programming languages.

More information about the tookit can be found on the [NASA/NAIF/JPL Website](https://naif.jpl.nasa.gov/naif/toolkit.html).

## About Unreal Engine 5

Unreal Engine 5 "will empower creators across all industries to deliver stunning real-time content and experiences", and targets game development and cinematography in particular.  Currently in Early Access, it contains many advanced features such as Nanite and Lumen to deliver photorealistic experiences.

For an example of what Uneal Engine 5 is capable of, see [The Matrix Awakens: An Unreal Engine 5 Experience](https://www.unrealengine.com/en-US/wakeup).


Additional information about Early Access to Unreal Engine 5 can be found on [Epic Games Unreal Engine 5 portal](https://www.unrealengine.com/en-US/unreal-engine-5).

### Unreal Engine 5 Blueprints

Unreal Engine Blueprints are a Visual Scripting System included in Unreal Engine.  Blueprints allow anyone to express logic visually, no programming experience required.  Blueprints are based on the concept of using a node-based interface to create  elements from within Unreal Editor similar to flowcharting.

For more information about Blueprints, see the [Unreal Engine "Blueprints - Essential Concepts" online learning course](https://www.unrealengine.com/en-US/onlinelearning-courses/blueprints---essential-concepts).

## Additional MaxQ Information

MaxQ project page:  
https://www.gamergenic.com/project/maxq/  

Unreal Engine Plugin Source Code on GitHub:
https://github.com/Gamergenic1/MaxQ

Documentation:  
https://maxq.gamergenic.com/  

Walkthrough of project development:  
https://gamedevtricks.com/tags/third-party-libs-series/

Example Projects:
https://github.com/gamergenic/ASATDebrisVisualization

## Implementation Principles
See [PRINCIPLES](PRINCIPLES.md) file.

---

# NOTICE
## Project conversion to Plugin in-progress
* This project is currently undergoing conversion to source code for an Unreal Engine plugin, as opposed to simply being a host application.
* The Plugin will be distributed via the Unreal Engine marketplace, vastly simplifying distribution.
* The Plugin will contain new tutorials directly in the Plugin itself (in progress).
* Due to the amount of work that's in progress the documentation and Plugin source project are in a state of flux.
* The easiest way to use MaxQ for now is would be to map the Plugins directory of this project to the Plugins directory of your own project.  You'd then enable MaxQ under plugins (category = SpaceFlight).
* Look for MaxQ to be released in the UE Marketplace by mid-June.

### Plugin Tutorials
### Location
* **C++**: /Plugins/MaxQ/Content/CppSamples/Maps
* **Blueprints**: /Plugins/MaxQ/Content/BlueprintSamples/Maps

### Content
* **Sample01**: Initialization and kernel data  
* **Sample02**: Time manipulation
* **Sample03**: SPK Positioning
* (Additional Tutorials in progress)

