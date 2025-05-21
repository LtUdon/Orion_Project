# TO DO
## 📝 Short-Term
* Redesign the *Orbiter class* hierarchy based on the `Diagrams.drawio` "Orbiter_Class" page.
* Once the *Orbiter* subclasses have been defined, then adding the mesh (for assets) will be applicable.

## 💡 Considerations
### 🔁 <u>Build Actor Classes in context of Purpose</u>
- Rather than haphazardly placing models into the viewport and attempting to add the actors afterward, instead:
    1. Add the Actor (*C++ class* or *Blueprint class*).
    2. Attach the appropriate mesh.
- Focus on the purpose of an object (based on class) first rather than the model/mesh itself.
### 🌿 <u>Develop a consistent class hierarchy before developing the class system</u>
- Before creating a new class, create a diagram for that class, no matter how layered it will be in the future.
- Define each class and it succeeding subclass(es).
- This allows you to see a clear path on how the classes are defined and prevents confusion.
- You can use a `.drawio` file for this.
### 🎮 <u>Actor/Pawn Implementation</u>
- Orbiter Nodes &rarr; **Actors**
- Ship Nodes &rarr; **Pawns**

    **Actor**: The base class for all objects that can be placed or spawned in a level. Actors provide basic functionality such as transformation (location, rotation, scale), and can contain components (meshes, lights, etc.).

    **Pawn**: A subclass of Actor that is intended to be "possessed" and controlled by a player or AI. Pawns are used for entities that require input or autonomous behavior (e.g., player characters, AI-controlled bots).

    > **Summary:**  
    > - Use **Actor** for general objects in the world.  
    > - Use **Pawn** when you need an object to be controllable by a player or AI.