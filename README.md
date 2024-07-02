![PotatoEngine-Logo](https://i.ibb.co/Gcx0pvS/Potato-Engine-Logo.png)
***<p style="text-align: center;">a low level C++ game engine</p>***
<br />

## Engine Structure
```mermaid
graph LR
A[PotatoEngine-Lib C++] -- DLL --> B[PotatoEngine-LevelEditor WPF]
B --> D{GameCode C++}
A --> D
```
<br />

## Project Structure
```mermaid
graph LR
A[Project] --> B[Scenes]
B --> C[GameEntities]
C --> D[Components]
```

**Project** - central data structure, contains everything.<br />
**Scenes** - Is a game level or a chunk of the world.
<br />

## GameEntity Structure
```mermaid
graph LR
A[GameEntity] --> B[Entity Type 1]
A --> C[Entity Type 2]
A --> D[Entity Type 3]
A --> E[Components]
E --> F[Transform]
E --> G[Script]
E --> H[Geometry]
E --> I[RigiBody]
```

## Multiselect GameEntity Structure
```mermaid
graph LR
A[Multiselect GameEntity] --> B[Multiselect Entity Type 1]
A --> C[Multiselect  Entity Type 2]
A --> D[Multiselect  Entity Type 3]
A --> E[Multiselect Components]
E --> F[MSTransform]
E --> G[MSScript]
E --> H[MSGeometry]
E --> I[MSRigiBody]
```

## PotatoEngine-Lib (Data Oriented Design)
| Entity ids    | 001 | 002 | 003 | 004 | 005 | 006 | 007 | 008 | 009 | etc |
|---------------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
| Transform ids | 001 | 002 | 003 | 004 | 005 | 006 | 007 | 008 | 009 | etc |
| Script ids    | -1  | -1  | 001 | -1  | 002 | -1  | -1  | 003 | -1  | etc |
| Geometry ids  | 001 | 002 | -1  | 003 | 004 | 005 | 006 | -1  | -1  | etc |
| Rigibody ids  | -1  | -1  | -1  | 001 | 002 | -1  | 003 | -1  | -1  | etc |
