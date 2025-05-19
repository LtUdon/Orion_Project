# TO DO
## Short-Term
* Update the `Orbiter.cpp` code to orbit a specific object.
    - At the moment, a revolution speed, rotation speed, and range are the only available headers to change offering little control as to what parent object to orbit.
* Adapt this updated version of `Orbiter.cpp` and/or `Orbiter.h` to **Orion Project**.
## Long Term
### 🔁 <u>Build Actor Classes in context of Purpose</u>
- Rather than haphazardly placing models into the viewport and attempting to add the actors afterward:
    1. Add the Actor (*C++ class*).
    2. Attach the appropriate mesh.
- Focus on the purpose of an object (based on class) first rather than the model/mesh itself.