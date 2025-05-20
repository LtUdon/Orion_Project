# TO DO
## Short-Term
An *Orbiter (Blueprint Class)* `Orbiter.uasset` works properly and can apply to different meshes.
* Create and apply *Orbiter (Blueprint Class)* subclasses to other meshes.
* Continue saveing these subclasses in the *Asset* Folder.

The star (no *Blueprint* nor *C++ code* is attached) seems to disappear when the *Orbiter* class has no reference.
* Create a new blueprint called *Star* (Empty blueprint).
## Long Term
### 🔁 <u>Build Actor Classes in context of Purpose</u>
- Rather than haphazardly placing models into the viewport and attempting to add the actors afterward, instead:
    1. Add the Actor (*C++ class* or *Blueprint class*).
    2. Attach the appropriate mesh.
- Focus on the purpose of an object (based on class) first rather than the model/mesh itself.