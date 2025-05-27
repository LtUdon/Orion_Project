# TO DO
## 📝 Short-Term
- Develop the subclasses for the `Orbiter` actor (Shown in `Diagrams.drawio`).
    - Research more about C++/Blueprint conventions between classes/subclasses.
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
### 🟦 <u>Blueprint (BL) and C++ Considerations</u>
- Given some class hierarchy, for best practice, classes/subclasses on the Parent-side is best implemented in C++ while subclasses on the Child-side is where Blueprint (BL) implementation is acceptable.
- This organization offers better performance while still accommodating simpler editing.
### 🎮 <u>Actor/Pawn Implementation</u>
- Orbiter Nodes &rarr; **Actors**
- Ship Nodes &rarr; **Pawns**

    **Actor**: The base class for all objects that can be placed or spawned in a level. Actors provide basic functionality such as transformation (location, rotation, scale), and can contain components (meshes, lights, etc.).

    **Pawn**: A subclass of Actor that is intended to be "possessed" and controlled by a player or NPC. Pawns are used for entities that require input or autonomous behavior (e.g., player characters, NPC).

    > **Summary:**  
    > - Use **Actor** for general objects in the world.  
    > - Use **Pawn** when you need an object to be controllable by a player or NPC.