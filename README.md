
# PotatoEngine [alhpa-stage]
 **PotatoEngine** is a low level C++ game engine


## Engine Structure

```mermaid
graph LR
A[PotatoEngine-Lib C++] -- DLL --> B[PotatoEngine-LevelEditor WPF]
B --> D{GameCode C++}
A --> D
```

## Project Structure
```mermaid
graph LR
A[Project] --> B[Scenes]
B --> C[GameEntities]
C --> D[Componentes]
```
**Project** - central data structure, contains everything
**Scenes** - Is a game level or a chunk of the world

